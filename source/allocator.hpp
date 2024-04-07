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
 * (4) The copy and move operations of allocator, size_type, difference_type, pointer and
 *     const_pointer should be nothrow;
 * (5) If the allocation size is zero, no memory should be allocated and nullptr is the
 *     returning value. Especially note that if the reallocation size is zero, the source
 *     memory should be deallocated.
*/
__DATA_STRUCTURE_START(universal allocator)
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
    static constexpr T *allocate(size_type n) noexcept(NoThrow) {
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
    static constexpr T *reallocate(void *source, size_type n) noexcept(NoThrow) requires is_trivially_copyable_v<T> {
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
    static constexpr void deallocate(void *p, size_type) noexcept {
        if constexpr(is_trivially_copyable_v<T>) {
            return ds::memory_free(p);
        }
        ::operator delete(p, ds::nothrow);
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
template <typename T, template <typename> typename NodeTemplate, typename Allocator = allocator<NodeTemplate<T>>>
class node_allocator : public Allocator {
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
    constexpr static bool linked_after_allocation {true};
private:
    constexpr void release_this() noexcept;
public:
    constexpr node_allocator() : shared_list {new shared_block {.strong_count {1}}} {}
    constexpr node_allocator(const node_allocator &rhs) noexcept : shared_list {rhs.shared_list} {
        ++this->shared_list->strong_count;
    }
    constexpr node_allocator(node_allocator &&rhs) noexcept : shared_list {rhs.shared_list} {
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
        }
        return *this;
    }
    constexpr node_allocator &operator=(node_allocator &&rhs) noexcept {
        if(this not_eq &rhs) {
            this->release_this();
            this->shared_list = rhs.shared_list;
            rhs.shared_list = nullptr;
        }
        return *this;
    }
public:
    template <bool NoThrow = false>
    [[nodiscard]]
    constexpr NodeTemplate<T> *allocate(size_type n, NodeTemplate<T> *link_to = {}) noexcept(NoThrow);
    template <bool = false>
    [[nodiscard]]
    constexpr void *reallocate(void *source, size_type n) noexcept {
        if(n == 0) {
            ds::memory_free(source);
        }
        return nullptr;
    }
    constexpr void deallocate(void *p, size_type) noexcept;
};
__DATA_STRUCTURE_END(inner tools for data structure library)

}       // namespace data_structure::__data_structure_auxiliary
__DATA_STRUCTURE_START(inner tools for data structure library)

}       // namespace data_structure

#endif      // DATA_STRUCTURE_ALLOCATOR_HPP