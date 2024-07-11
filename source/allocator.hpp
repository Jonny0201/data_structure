/*
    * Copyright © [2019 - 2024] [Jonny]
    *
    * Licensed under the Apache License, Version 2.0 (the "License");
    * you may not use this file except in compliance with the License.
    * You may obtain a copy of the License at
    *
    *     http://www.apache.org/licenses/LICENSE-2.0
    *
    * Unless required by applicable law or agreed to in writing, software
    * distributed under the License is distributed on an "AS IS" BASIS,
    * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    * See the License for the specific language governing permissions and
    * limitations under the License.
*/

#ifndef DATA_STRUCTURE_ALLOCATOR_HPP
#define DATA_STRUCTURE_ALLOCATOR_HPP

#include "type_traits.hpp"

namespace data_structure {

/*
 * The allocator in data structure project is different from std::allocator. If you want
 * to customize your own allocator, it's essential to follow the detailed specifications :
 * (1) The nothrow attribution of member function `allocate` is determined by the first
 *     non-type template parameter `NoThrow`, the default value of `NoThrow` is false;
 * (2) The allocator should support reallocation by providing member function `reallocate`;
 * (3) The member function `deallocate` should be marked as noexcept, and if there exists
 *     deallocating memory in other member functions, the operation should also be nothrow;
 * (4) The copy and move operations of allocator, size_type, difference_type, pointer,
 *     const_pointer, reference, const_reference and rvalue_reference should be nothrow;
 * (5) If the allocation size is zero, no memory should be allocated and nullptr is the
 *     returning value. Especially note that if the reallocation size is zero, the source
 *     memory should be deallocated.
*/
__DATA_STRUCTURE_START(universal allocator)
// Todo : consider the move operation on limited memory range
template <typename T>
class allocator {
public:
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using value_type = T;
public:
    constexpr allocator() noexcept = default;
    constexpr allocator(const allocator &) noexcept = default;
    constexpr allocator(allocator &&) noexcept = default;
    constexpr ~allocator() noexcept = default;
public:
    constexpr allocator &operator=(const allocator &) noexcept = default;
    constexpr allocator &operator=(allocator &&) noexcept = default;
public:
    template <bool NoThrow = false>
    [[nodiscard]]
    static constexpr T *allocate(size_t n) noexcept(NoThrow) {
        if(n == 0) {
            return nullptr;
        }
        if constexpr(is_trivially_copyable_v<T>) {
            auto memory {static_cast<T *>(ds::memory_allocation(n * sizeof(T)))};
            if constexpr(not NoThrow) {
                if(not memory) {
                    throw std::bad_alloc {};
                }
            }
            return memory;
        }
        if constexpr(NoThrow) {
            return static_cast<T *>(::operator new(n * sizeof(T), ds::nothrow));
        }
        return static_cast<T *>(::operator new(n * sizeof(T)));
    }
    template <bool NoThrow = false>
    [[nodiscard]]
    static constexpr T *reallocate(void *source, size_t n) noexcept(NoThrow) requires is_trivially_copyable_v<T> {
        if(n == 0) {
            ds::memory_free(source);
            return nullptr;
        }
        auto memory {static_cast<T *>(ds::memory_reallocation(source, n * sizeof(T)))};
        if constexpr(not NoThrow) {
            if(not memory) {
                throw std::bad_alloc {};
            }
        }
        return memory;
    }
    static constexpr void deallocate(void *p) noexcept {
        if constexpr(is_trivially_copyable_v<T>) {
            return ds::memory_free(p);
        }
        ::operator delete(p, ds::nothrow);
    }
    static constexpr void deallocate(void *p, size_t) noexcept {
        allocator::deallocate(p);
    }
};
template <typename T, typename U>
[[nodiscard]]
inline consteval bool operator==(const allocator<T> &, const allocator<U> &) noexcept {
    return true;
}
template <typename T, typename U>
[[nodiscard]]
inline consteval bool operator!=(const allocator<T> &, const allocator<U> &) noexcept {
    return false;
}
__DATA_STRUCTURE_END(universal allocator)

__DATA_STRUCTURE_START(allocator traits)
template <typename Allocator>
struct allocator_traits {
    using size_type = typename Allocator::size_type;
    using difference_type = typename Allocator::difference_type;
    using value_type = typename Allocator::value_type;
    using reference = typename __dsa::traits_reference<Allocator, value_type &>::type;
    using const_reference = typename __dsa::traits_const_reference<Allocator, const value_type &>::type;
    using rvalue_reference = typename __dsa::traits_rvalue_reference<Allocator, value_type &&>::type;
    using pointer = typename __dsa::traits_pointer<Allocator, value_type *>::type;
    using const_pointer = typename __dsa::traits_const_pointer<Allocator, const value_type *>::type;
    template <typename U>
    using rebind = typename class_template_traits<Allocator>::template rebind<U>;
};
__DATA_STRUCTURE_END(allocator traits)

__DATA_STRUCTURE_START(inner tools for data structure library)
namespace __data_structure_auxiliary {

__DATA_STRUCTURE_START(concept for node allocator, tag in class named linked_after_allocation)
template <typename Allocator>
concept IsLinkedAfterAllocation = requires {
    requires Allocator::linked_after_allocation == true;
};
__DATA_STRUCTURE_END(concept for node allocator, tag in class named linked_after_allocation)

__DATA_STRUCTURE_START(data structure node-based structure allocator)
template <typename T, template <typename> typename NodeTemplate, typename Allocator = allocator<T>,
        typename NodeAllocator = typename allocator_traits<Allocator>::template rebind<NodeTemplate<T>>>
class node_allocator : public Allocator, public NodeAllocator {
    template <typename U, typename V>
    friend constexpr bool operator==(const allocator<U> &, const allocator<V> &) noexcept;
public:
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using value_type = T;
private:
    struct shared_block {
        union free_node {
            NodeTemplate<T> *node;
            free_node *next;
        } *free_list;
        size_t node_size;
        size_t strong_count;
        struct recorder_list {
            struct {
                NodeTemplate<T> *recorde;
                size_t size;
            };
            recorder_list *next;
        } *recorder;
    } *shared_list;
public:
    constexpr static auto linked_after_allocation {true};
private:
    constexpr void release_this() noexcept {
        if(this->shared_list and --this->shared_list->strong_count == 0) {
            for(auto it {this->shared_list->recorder}; it;) {
                auto backup {it};
                it = it->next;
                this->NodeAllocator::deallocate(backup->recorde, backup->size);
            }
            ::delete this->shared_list;
        }
    }
public:
    constexpr node_allocator() : Allocator(), NodeAllocator(), shared_list {::new shared_block {.strong_count {1}}} {}
    explicit constexpr node_allocator(const Allocator &allocator) : Allocator(allocator), NodeAllocator(),
            shared_list {::new shared_block {.strong_count {1}}} {}
    constexpr node_allocator(const node_allocator &rhs) noexcept : Allocator(rhs), NodeAllocator(rhs),
            shared_list {rhs.shared_list} {
        ++this->shared_list->strong_count;
    }
    constexpr node_allocator(node_allocator &&rhs) noexcept : Allocator(ds::move(rhs)), NodeAllocator(ds::move(rhs)),
            shared_list {rhs.shared_list} {
        rhs.shared_list = nullptr;
    }
    constexpr ~node_allocator() noexcept {
        this->release_this();
    }
public:
    constexpr node_allocator &operator=(const node_allocator &rhs) noexcept {
        if(this not_eq &rhs) {
            this->release_this();
            this->shared_list = rhs.shared_list;
            ++this->shared_list->strong_count;
            this->Allocator::operator=(rhs);
            this->NodeAllocator::operator=(rhs);
        }
        return *this;
    }
    constexpr node_allocator &operator=(node_allocator &&rhs) noexcept {
        if(this not_eq &rhs) {
            this->release_this();
            this->shared_list = rhs.shared_list;
            rhs.shared_list = nullptr;
            this->Allocator::operator=(ds::move(rhs));
            this->NodeAllocator::operator=(ds::move(rhs));
        }
        return *this;
    }
public:
    template <bool NoThrow = false>
    [[nodiscard]]
    constexpr NodeTemplate<T> *allocate(size_t n, NodeTemplate<T> *link_to = {}) noexcept(NoThrow) {
        if(n == 0) {
            return nullptr;
        }
        const auto result {this->shared_list->free_list};
        if(n < this->shared_list->node_size) {
            this->shared_list->node_size -= n;
            auto cursor {result};
            do {
                cursor = cursor->next;
            }while(--n not_eq 0);
            this->shared_list->free_list = cursor;
            return reinterpret_cast<NodeTemplate<T> *>(result);
        }
        n -= this->shared_list->node_size;
        this->shared_list->node_size = 0;
        if(n == 0) {
            this->shared_list->free_list = nullptr;
            return reinterpret_cast<NodeTemplate<T> *>(result);
        }
        const auto nodes {this->NodeAllocator::allocate(n)};
        if constexpr(NoThrow) {
            if(not nodes) {
                return nullptr;
            }
            auto new_record {::new (ds::nothrow) shared_block::recorder_list {{nodes, n}, this->shared_list->recorder}};
            if(new_record) {
                this->shared_list->recorder = new_record;
            }else {
                this->NodeAllocator::deallocate(nodes, n);
                return nullptr;
            }
        }else {
            try {
                auto new_record {::new shared_block::recorder_list {{nodes, n}, this->shared_list->recorder}};
                this->shared_list->recorder = new_record;
            }catch(...) {
                this->NodeAllocator::deallocate(nodes, n);
                throw;
            }
        }
        const auto last_position {n - 1};
        for(auto i {0}; i < last_position; ++i) {
            nodes[i].next = nodes + (i + 1);
        }
        nodes[last_position].next = link_to;
        auto cursor {this->shared_list->free_list};
        for(; cursor->next; cursor = cursor->next);
        cursor->next = reinterpret_cast<shared_block::free_node *>(nodes);
        this->shared_list->free_list = nullptr;
        return reinterpret_cast<NodeTemplate<T> *>(result);
    }
    template <bool = false>
    [[nodiscard]]
    constexpr void *reallocate(void *source, size_t n) noexcept {
        if(n == 0) {
            ds::memory_free(source);
        }
        return nullptr;
    }
    constexpr void deallocate(void *p) noexcept {
        this->deallocate(static_cast<NodeTemplate<T> *>(p));
    }
    constexpr void deallocate(void *p, size_t n) noexcept {
        this->deallocate(static_cast<NodeTemplate<T> *>(p), n);
    }
    constexpr void deallocate(void *begin, void *end) noexcept {
        this->deallocate(static_cast<NodeTemplate<T> *>(begin), static_cast<NodeTemplate<T> *>(end));
    }
    constexpr void deallocate(void *begin, void *end, size_t n) noexcept {
        this->deallocate(static_cast<NodeTemplate<T> *>(begin), static_cast<NodeTemplate<T> *>(end), n);
    }
    constexpr void deallocate(NodeTemplate<T> *node) noexcept {
        if(node) {
            const auto free_node {reinterpret_cast<shared_block::free_node *>(node)};
            free_node->next = this->shared_list->free_list;
            this->shared_list->free_list = free_node;
            ++this->shared_list->node_size;
        }
    }
    constexpr void deallocate(NodeTemplate<T> *node, size_t n) noexcept {
        if(node) {
            auto it {node};
            this->shared_list->node_size += n;
            for(; n not_eq 1; it = it->next->node(), static_cast<void>(--n));
            reinterpret_cast<shared_block::free_node *>(it)->next = this->shared_list->free_list;
            this->shared_list->free_list = reinterpret_cast<shared_block::free_node *>(node);
        }
    }
    constexpr void deallocate(NodeTemplate<T> *begin, NodeTemplate<T> *end) noexcept {
        if(begin) {
            auto n {1uz};
            for(auto it {begin}; it not_eq end; it = it->next, static_cast<void>(++n));
            this->shared_list->node_size += n;
            reinterpret_cast<shared_block::free_node *>(end)->next = this->shared_list->free_list;
            this->shared_list->free_list = reinterpret_cast<shared_block::free_node *>(begin);
        }
    }
    constexpr void deallocate(NodeTemplate<T> *begin, NodeTemplate<T> *end, size_t n) noexcept {
        if(begin and n > 0) {
            this->shared_list->node_size += n;
            reinterpret_cast<shared_block::free_node *>(end)->next = this->shared_list->free_list;
            this->shared_list->free_list = reinterpret_cast<shared_block::free_node *>(begin);
        }
    }
};
template <typename T, typename U>
[[nodiscard]]
inline constexpr bool operator==(const allocator<T> &lhs, const allocator<U> &rhs) noexcept {
    return lhs.shared_list == rhs.shared_list;
}
template <typename T, typename U>
[[nodiscard]]
inline constexpr bool operator!=(const allocator<T> &lhs, const allocator<U> &rhs) noexcept {
    return not(lhs == rhs);
}
__DATA_STRUCTURE_END(inner tools for data structure library)

}       // namespace data_structure::__data_structure_auxiliary
__DATA_STRUCTURE_START(inner tools for data structure library)

}       // namespace data_structure

#endif      // DATA_STRUCTURE_ALLOCATOR_HPP