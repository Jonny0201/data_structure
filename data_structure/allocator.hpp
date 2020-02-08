/*
    * Copyright © [2019] [Jonny Charlotte]
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
#include "memory.hpp"
#include "meta.hpp"

namespace data_structure {
    template <typename T>
    class allocator final {
    public:
        using size_type = decltype(sizeof 0);
        using difference_type = decltype(static_cast<int *>(nullptr) - static_cast<int *>(nullptr));
        using value_type = T;
        using reference = typename add_lvalue_reference<value_type>::type;
        using const_reference = typename add_const_reference<value_type>::type;
        using rvalue_reference = typename add_rvalue_reference<value_type>::type;
        using pointer = typename add_pointer<value_type>::type;
        using const_pointer = typename add_const_pointer<value_type>::type;
        using void_pointer = void *;
        using const_void_pointer = const void *;
    private:
        constexpr void destroy(pointer, true_type) noexcept {}
        void destroy(pointer p, false_type) noexcept(is_nothrow_destructible<value_type>::value) {
            p->~value_type();
        }
        constexpr void destroy(pointer, pointer, true_type) noexcept {}
        void destroy(pointer begin, pointer end, false_type)
        noexcept(is_nothrow_destructible<value_type>::value) {
            for(auto cursor {begin}; cursor not_eq end; ++cursor) {
                cursor->~value_type();
            }
        }
    public:
        constexpr allocator() noexcept = default;
        constexpr allocator(const allocator &) noexcept = default;
        template <typename U>
        constexpr allocator(const allocator<U> &) noexcept {}
        constexpr allocator(allocator &&) noexcept = default;
        template <typename U>
        constexpr allocator(allocator<U> &&) noexcept {}
        ~allocator() noexcept = default;
    public:
        allocator &operator=(const allocator &) noexcept = default;
        template <typename U>
        allocator &operator=(const allocator<U> &) const noexcept {
            return *this;
        }
        allocator &operator=(allocator &&) noexcept = default;
        template <typename U>
        allocator &operator=(allocator<U> &&) const noexcept {
            return *this;
        }
    public:
        void *operator new (decltype(sizeof 0) n) {
            return ::operator new (n);
        }
        void *operator new (decltype(sizeof 0) n, dynamic) {
            return ::operator new (n, std::nothrow);
        }
        void operator delete (void *p) noexcept {
            ::operator delete (p);
        }
    public:
        static pointer allocate(size_type n) {
            return reinterpret_cast<pointer>(allocator::operator new (n));
        }
        static pointer allocate(size_type n, dynamic) noexcept {
            return reinterpret_cast<pointer>(allocator::operator new (n, dynamic()));
        }
        static void deallocate(pointer p, size_type n) noexcept {
            allocator::operator delete (p);
        }
        template <typename ...Args>
        static pointer construct(pointer p, Args &&...args)
                noexcept(is_nothrow_constructible<value_type, Args...>::value) {
            return new (p) value_type(data_structure::forward<Args>(args)...);
        }
        //DO NOT USE THIS FUNCTION!
        template <typename ...Args>
        static pointer construct(pointer begin, const_pointer end, Args &&...args)
                noexcept(is_nothrow_constructible<value_type, Args...>::value) {
            auto cursor {begin};
            while(cursor not_eq end) {
                new (cursor++) value_type(forward<Args>(args)...);        //origin of causing undefined behavior
            }
            return begin;
        }
        constexpr static void destroy(pointer p) noexcept(is_nothrow_destructible<value_type>::value) {
            allocator::destroy(p, typename conditional<
                    is_trivially_destructible<value_type>::value, true_type, false_type>::result());
        }
        constexpr static void destroy(pointer begin, const_pointer end)
                noexcept(is_nothrow_destructible<value_type>::value) {
            allocator::destroy(begin, end, typename conditional<
                    is_trivially_destructible<value_type>::value, true_type, false_type>::result());
        }
    };
}

namespace data_structure {
    template <typename T>
    class allocator<type_holder<T>> final : private __memory_pool<> {
    private:
        using __base = __memory_pool;
    public:
        using size_type = typename __base::size_type;
        using difference_type = typename __base::difference_type;
        using value_type = T;
        using reference = typename add_lvalue_reference<value_type>::type;
        using const_reference = typename add_const_reference<value_type>::type;
        using rvalue_reference = typename add_rvalue_reference<value_type>::type;
        using pointer = typename add_pointer<value_type>::type;
        using const_pointer = typename add_const_pointer<value_type>::type;
        using void_pointer = void *;
        using const_void_pointer = const void *;
    public:
        constexpr allocator() noexcept = default;
        constexpr allocator(const allocator &) noexcept = default;
        template <typename U>
        constexpr allocator(const allocator<U> &) noexcept {}
        constexpr allocator(allocator &&) noexcept = default;
        template <typename U>
        constexpr allocator(allocator<U> &&) noexcept {}
        ~allocator() noexcept = default;
    public:
        allocator &operator=(const allocator &) noexcept = default;
        template <typename U>
        allocator &operator=(const allocator<U> &) const noexcept {
            return *this;
        }
        allocator &operator=(allocator &&) noexcept = default;
        template <typename U>
        allocator &operator=(allocator<U> &&) const noexcept {
            return *this;
        }
    public:
        void *operator new (size_type size) {
            return __base::operator new (size);
        }
        void *operator new (size_type size, dynamic) noexcept {
            return __base::operator new (size, std::nothrow);
        }
        void operator delete (void *p) noexcept {
            __base::operator delete (p);
        }
        void operator delete (void *p, dynamic) noexcept {
            __base::operator delete (p, std::nothrow);
        }
        void operator delete (void *p, size_type) noexcept {
            __base::operator delete (p);
        }
        void operator delete(void *p, size_type, dynamic) noexcept {
            __base::operator delete (p, std::nothrow);
        }
    public:
        static pointer allocate(size_type n) {
            return reinterpret_cast<pointer>(__base::allocate(n));
        }
        static pointer allocate(size_type n, dynamic) noexcept {
            return reinterpret_cast<pointer>(__base::allocate(n, dynamic()));
        }
        static void deallocate(pointer p, size_type n) noexcept {
            __base::deallocate(p, n);
        }
        template <typename ...Args>
        static pointer construct(pointer p, Args &&...args)
                noexcept(is_nothrow_constructible<value_type, Args...>::value) {
            return new (p) value_type(data_structure::forward<Args>(args)...);
        }
        //DO NOT USE THIS FUNCTION!
        template <typename ...Args>
        static pointer construct(pointer begin, const_pointer end, Args &&...args)
                noexcept(is_nothrow_constructible<value_type, Args...>::value) {
            auto cursor {begin};
            while(cursor not_eq end) {
                new (cursor++) value_type(forward<Args>(args)...);        //origin of causing undefined behavior
            }
            return begin;
        }
        static constexpr void destroy(pointer p) noexcept(is_nothrow_destructible<value_type>::value) {
            if constexpr(not is_trivially_destructible<value_type>::value) {
                p->~value_type();
            }
        }
        static constexpr void destroy(pointer begin, const_pointer end)
                noexcept(is_nothrow_destructible<value_type>::value) {
            if constexpr(not is_trivially_destructible<value_type>::value) {
                while(begin not_eq end) {
                    begin++->~value_type();
                }
            }
        }
    };
}

#endif //DATA_STRUCTURE_ALLOCATOR_HPP
