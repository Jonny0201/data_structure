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

#include "utility.hpp"
#include "iterator.hpp"

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

__DATA_STRUCTURE_START(forward list node allocator)
template <typename T, template <typename> typename NodeTemplate, typename Allocator = allocator<T>,
        typename NodeAllocator = typename allocator_traits<Allocator>::template rebind<NodeTemplate<T>>>
class forward_list_node_allocator : public Allocator, public NodeAllocator {
    friend constexpr bool operator==(const forward_list_node_allocator &, const forward_list_node_allocator &) noexcept;
private:
    struct free_list_exception_handler {
        NodeTemplate<T> *begin;
        NodeTemplate<T> *end;
        constexpr void operator()() noexcept {
            while(this->begin not_eq this->end) {
                ds::destroy(ds::address_of(this->begin->value));
                this->begin = this->begin->next->node();
            }
        }
    };
    struct allocation_exception_handler {
        NodeTemplate<T> *nodes;
        size_t n;
        size_t i;
        NodeAllocator &allocator;
        constexpr allocation_exception_handler(NodeTemplate<T> *nodes, size_t n, NodeAllocator &allocator)
                noexcept : nodes {nodes}, n {n}, i {0}, allocator(allocator) {}
        constexpr void operator()() noexcept {
            for(auto j {0}; j < this->i; ++j) {
                ds::destroy(ds::address_of(this->nodes[j].value));
            }
            this->allocator.deallocate(this->nodes, this->n);
        }
    };
public:
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using value_type = T;
    static_assert(is_same_v<T, typename allocator_traits<Allocator>::value_type>,
            "The value type of forward_list_node_allocator must be same as original allocator!");
private:
    struct shared_block {
        struct {
            NodeTemplate<T> *free_list;
            size_t node_size;
        };
        size_t strong_count;
        struct recorder_list {
            struct {
                NodeTemplate<T> *record;
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
                this->NodeAllocator::deallocate(backup->record, backup->size);
                ::delete backup;
            }
            ::delete this->shared_list;
        }
    }
public:
    constexpr forward_list_node_allocator() : Allocator(), NodeAllocator(),
            shared_list {::new shared_block {.strong_count {1}}} {}
    explicit constexpr forward_list_node_allocator(const Allocator &allocator) : Allocator(allocator), NodeAllocator(),
            shared_list {::new shared_block {.strong_count {1}}} {}
    constexpr forward_list_node_allocator(const forward_list_node_allocator &rhs) noexcept : Allocator(rhs),
            NodeAllocator(rhs), shared_list {rhs.shared_list} {
        ++this->shared_list->strong_count;
    }
    constexpr forward_list_node_allocator(forward_list_node_allocator &&rhs) noexcept : Allocator(ds::move(rhs)),
            NodeAllocator(ds::move(rhs)), shared_list {rhs.shared_list} {
        rhs.shared_list = nullptr;
    }
    constexpr ~forward_list_node_allocator() noexcept {
        this->release_this();
    }
public:
    constexpr forward_list_node_allocator &operator=(const forward_list_node_allocator &rhs) noexcept {
        if(this not_eq &rhs) {
            this->release_this();
            this->shared_list = rhs.shared_list;
            ++this->shared_list->strong_count;
            this->Allocator::operator=(rhs);
            this->NodeAllocator::operator=(rhs);
        }
        return *this;
    }
    constexpr forward_list_node_allocator &operator=(forward_list_node_allocator &&rhs) noexcept {
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
        auto result {this->shared_list->free_list};
        if(n <= this->shared_list->node_size) {
            auto cursor {result};
            while(n not_eq 1) {
                cursor = cursor->next->node();
                --n;
            }
            this->shared_list->node_size -= n;
            this->shared_list->free_list = cursor->next->node();
            cursor->next = link_to;
            return result;
        }
        const auto nodes {this->NodeAllocator::template allocate<NoThrow>(n -= this->shared_list->node_size)};
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
        for(auto i {0uz}; i < last_position; ++i) {
            nodes[i].next = nodes + (i + 1);
        }
        nodes[last_position].next = link_to;
        if(auto cursor {result}; cursor) {
            for(; cursor->next; cursor = cursor->next->node());
            cursor->next = nodes;
        }else {
            result = nodes;
        }
        this->shared_list->free_list = nullptr;
        this->shared_list->node_size = 0;
        return result;
    }
    template <typename ...Args>
    [[nodiscard]]
    constexpr NodeTemplate<T> *allocate_with_value(size_t n, NodeTemplate<T> *link_to, Args &&...args) {
        if(n == 0) {
            return nullptr;
        }
        auto result {this->shared_list->free_list};
        if(n <= this->shared_list->node_size) {
            auto trans {transaction {free_list_exception_handler {result, result}}};
            auto &cursor {trans.get_rollback().end};
            while(n not_eq 1) {
                ds::construct(ds::address_of(cursor->value), ds::forward<Args>(args)...);
                cursor = cursor->next->node();
                --n;
            }
            ds::construct(ds::address_of(cursor->value), ds::forward<Args>(args)...);
            trans.complete();
            this->shared_list->node_size -= n;
            this->shared_list->free_list = cursor->next->node();
            cursor->next = link_to;
            return result;
        }
        if(result) {
            auto trans {transaction {free_list_exception_handler {result, result}}};
            auto &cursor {trans.get_rollback().end};
            for(; cursor->next; cursor = cursor->next->node()) {
                ds::construct(ds::address_of(cursor->value), ds::forward<Args>(args)...);
            }
            ds::construct(ds::address_of(cursor->value), ds::forward<Args>(args)...);
            cursor->next = link_to;
            trans.complete();
        }
        const auto nodes {this->NodeAllocator::template allocate<false>(n -= this->shared_list->node_size)};
        const auto last_position {n - 1};
        auto trans {transaction {allocation_exception_handler(nodes, n, *this)}};
        auto &i {trans.get_rollback().i};
        for(; i < last_position; ++i) {
            nodes[i].next = nodes + (i + 1);
            ds::construct(ds::address_of(nodes[i].value), ds::forward<Args>(args)...);
        }
        ds::construct(ds::address_of(nodes[i].value), ds::forward<Args>(args)...);
        ++i;
        this->shared_list->recorder = ::new shared_block::recorder_list {{nodes, n}, this->shared_list->recorder};
        trans.complete();
        nodes[last_position].next = link_to;
        this->shared_list->free_list = nullptr;
        this->shared_list->node_size = 0;
        return nodes;
    }
    template <IsInputIterator InputIterator>
    [[nodiscard]]
    constexpr NodeTemplate<T> *allocate_with_range(size_t n, NodeTemplate<T> *link_to, InputIterator begin) {
        if(n == 0) {
            return nullptr;
        }
        auto result {this->shared_list->free_list};
        if(n <= this->shared_list->node_size) {
            auto trans {transaction {free_list_exception_handler {result, result}}};
            auto &cursor {trans.get_rollback().end};
            while(n not_eq 1) {
                ds::construct(ds::address_of(cursor->value),
                        ds::move_if<not IsForwardIterator<InputIterator>>(*begin++));
                cursor = cursor->next->node();
                --n;
            }
            ds::construct(ds::address_of(cursor->value), ds::move_if<not IsForwardIterator<InputIterator>>(*begin++));
            trans.complete();
            this->shared_list->node_size -= n;
            this->shared_list->free_list = cursor->next->node();
            cursor->next = link_to;
            return result;
        }
        const auto nodes {this->NodeAllocator::template allocate<false>(n -= this->shared_list->node_size)};
        const auto last_position {n - 1};
        auto trans {transaction {allocation_exception_handler(nodes, n, *this)}};
        auto &i {trans.get_rollback().i};
        for(; i < last_position; ++i) {
            nodes[i].next = nodes + (i + 1);
            ds::construct(ds::address_of(nodes[i].value), ds::move_if<not IsForwardIterator<InputIterator>>(*begin++));
        }
        ds::construct(ds::address_of(nodes[i].value), ds::move_if<not IsForwardIterator<InputIterator>>(*begin++));
        ++i;
        this->shared_list->recorder = ::new shared_block::recorder_list {{nodes, n}, this->shared_list->recorder};
        if(result) {
            auto trans {transaction {free_list_exception_handler {result, result}}};
            auto &cursor {trans.get_rollback().end};
            for(; cursor->next; cursor = cursor->next->node()) {
                ds::construct(ds::address_of(cursor->value),
                        ds::move_if<not IsForwardIterator<InputIterator>>(*begin++));
            }
            ds::construct(ds::address_of(cursor->value), ds::move_if<not IsForwardIterator<InputIterator>>(*begin++));
            cursor->next = link_to;
            trans.complete();
        }
        trans.complete();
        nodes[last_position].next = link_to;
        this->shared_list->free_list = nullptr;
        this->shared_list->node_size = 0;
        return nodes;
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
            node->next = this->shared_list->free_list;
            this->shared_list->free_list = node;
            ++this->shared_list->node_size;
        }
    }
    constexpr void deallocate(NodeTemplate<T> *node, size_t n) noexcept {
        if(node) {
            auto it {node};
            this->shared_list->node_size += n;
            for(; n not_eq 1; it = it->next->node(), static_cast<void>(--n));
            it->next = this->shared_list->free_list;
            this->shared_list->free_list = node;
        }
    }
    constexpr void deallocate(NodeTemplate<T> *begin, NodeTemplate<T> *end) noexcept {
        if(begin) {
            auto n {1uz};
            end->next = this->shared_list->free_list;
            this->shared_list->free_list = begin;
            for(; begin not_eq end; begin = begin->next, static_cast<void>(++n));
            this->shared_list->node_size += n;
        }
    }
    constexpr void deallocate(NodeTemplate<T> *begin, NodeTemplate<T> *end, size_t n) noexcept {
        if(begin) {
            this->shared_list->node_size += n;
            end->next = this->shared_list->free_list;
            this->shared_list->free_list = begin;
        }
    }
};
__DATA_STRUCTURE_END(forward node node allocator)

}       // namespace data_structure::__data_structure_auxiliary
__DATA_STRUCTURE_START(inner tools for data structure library)

}       // namespace data_structure

#endif      // DATA_STRUCTURE_ALLOCATOR_HPP