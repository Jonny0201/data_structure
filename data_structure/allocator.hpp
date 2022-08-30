/*
    * Copyright © [2019 - 2022] [Jonny Charlotte]
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
#include "memory.hpp"

__DATA_STRUCTURE_START(allocator for C++ standard)
namespace data_structure {
    template <typename T>
    class allocator {
    public:
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using value_type = T;
        using reference = add_lvalue_reference_t<value_type>;
        using const_reference = add_const_reference_t<value_type>;
        using rvalue_reference = add_rvalue_reference_t<value_type>;
        using pointer = add_pointer_t<value_type>;
        using const_pointer = add_const_pointer_t<value_type>;
    public:
        constexpr allocator() noexcept = default;
        constexpr allocator(const allocator &) noexcept = default;
        constexpr allocator(allocator &&) noexcept = default;
        constexpr ~allocator() noexcept = default;
    public:
        constexpr allocator &operator=(const allocator &) noexcept = default;
        constexpr allocator &operator=(allocator &&) noexcept = default;
    public:
        [[nodiscard]]
        static pointer allocate(size_type n) {
            return static_cast<pointer>(::operator new(n * sizeof(value_type)));
        }
        [[nodiscard]]
        static pointer allocate(size_type n, meta::dynamic) noexcept {
            return static_cast<pointer>(::operator new(n * sizeof(value_type), std::nothrow));
        }
        static void deallocate(pointer p, size_type) noexcept {
            ::operator delete(p);
        }
        static void deallocate(pointer p, size_type, meta::dynamic) noexcept {
            ::operator delete(p);
        }
        template <typename ...Args>
        [[deprecated("This member function is removed in C++ 20!")]]
        static pointer construct(pointer p, Args &&...args)
                noexcept(is_nothrow_constructible_v<value_type, Args...>) {
            return ::new (p) value_type(ds::forward<Args>(args)...);
        }
        [[deprecated("This member function is removed in C++ 20!")]]
        static constexpr void destroy(pointer p) noexcept(is_nothrow_destructible_v<value_type>) {
            if constexpr(not is_trivially_destructible_v<value_type>) {
                p->~value_type();
            }
        }
    };
    template <typename T, typename U>
    [[nodiscard]]
    inline constexpr bool operator==(const allocator<T> &, const allocator<U> &) noexcept {
        return true;
    }
    template <typename T, typename U>
    [[nodiscard]]
    inline constexpr bool operator!=(const allocator<T> &, const allocator<U> &) noexcept {
        return false;
    }
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(stateless allocator of data structure library)
namespace data_structure {
    template <>
    class allocator<void> final : private memory_pool<> {
    private:
        using pool = memory_pool;
    public:
        using size_type = size_t;
        using difference_type = ptrdiff_t;
    public:
        constexpr allocator() noexcept = default;
        constexpr allocator(const allocator &) noexcept = default;
        constexpr allocator(allocator &&) noexcept = default;
        constexpr ~allocator() noexcept = default;
    public:
        constexpr allocator &operator=(const allocator &) noexcept = default;
        constexpr allocator &operator=(allocator &&) noexcept = default;
        using pool::operator new;
        using pool::operator delete;
    public:
        template <bool NoThrow = false>
        [[nodiscard]]
        static void *allocate(size_type n) noexcept(NoThrow) {
            return pool::allocate<NoThrow>(n);
        }
        static void deallocate(void *p, size_type n) noexcept {
            pool::deallocate(p, n);
        }
    };
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(construction function and destroy functions)
namespace data_structure {
    template <typename T, typename ...Args>
    inline constexpr T *construct(T *p, Args &&...args) noexcept(is_nothrow_constructible_v<T, Args...>) {
        return new (p) T(ds::forward<Args>(args)...);
    }
    template <typename T>
    inline constexpr void destroy(T *p) noexcept {
        if constexpr(not is_trivially_destructible_v<T>) {
            p->~T();
        }
    }
    template <typename T>
    inline constexpr void destroy(T *begin, T *end) noexcept {
        if constexpr(not is_trivially_destructible_v<T>) {
            while(begin not_eq end) {
                begin++->~T();
            }
        }
    }
}
__DATA_STRUCTURE_END

#endif //DATA_STRUCTURE_ALLOCATOR_HPP
