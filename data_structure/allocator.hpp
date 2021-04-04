/*
    * Copyright © [2019 - 2021] [Jonny Charlotte]
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
#include "meta.hpp"

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
        using void_pointer = void *;
        using const_void_pointer = const void *;
    public:
        constexpr allocator() noexcept = default;
        constexpr allocator(const allocator &) noexcept = default;
        constexpr allocator(allocator &&) noexcept = default;
        template <typename U>
        constexpr explicit allocator(const allocator<U> &) noexcept {}
        template <typename U>
        constexpr explicit allocator(allocator<U> &&) noexcept {}
        ~allocator() noexcept = default;
    public:
        constexpr allocator &operator=(const allocator &) noexcept = default;
        constexpr allocator &operator=(allocator &&) noexcept = default;
        template <typename U>
        constexpr allocator &operator=(const allocator<U> &) const noexcept {
            return *this;
        }
        template <typename U>
        constexpr allocator &operator=(allocator<U> &&) const noexcept {
            return *this;
        }
    public:
        void *operator new(size_t n) {
            return ::operator new (n);
        }
        void *operator new(size_t n, dynamic) noexcept {
            return ::operator new(n, std::nothrow);
        }
        void operator delete(void *p) noexcept {
            ::operator delete(p, std::nothrow);
        }
    public:
        static pointer allocate(size_type n) {
            return reinterpret_cast<pointer>(allocator::operator new(n));
        }
        static pointer allocate(size_type n, dynamic) noexcept {
            return reinterpret_cast<pointer>(allocator::operator new(n, dynamic()));
        }
        static void deallocate(pointer p, size_type) noexcept {
            allocator::operator delete(p);
        }
        template <typename ...Args>
        static pointer construct(pointer p, Args &&...args)
                noexcept(is_nothrow_constructible_v<value_type, Args...>) {
            return ::new (p) value_type(ds::forward<Args>(args)...);
        }
        template <typename ...Args>
        [[deprecated]]
        static pointer construct(pointer begin, const_pointer end, Args &&...args)
                noexcept(is_nothrow_constructible_v<value_type, Args...>) {
            auto cursor {begin};
            while(cursor not_eq end) {
                ::new (cursor++) value_type(forward<Args>(args)...);
            }
            return begin;
        }
        static constexpr void destroy(pointer p) noexcept(is_nothrow_destructible_v<value_type>) {
            if constexpr(not is_trivially_destructible_v<value_type>) {
                p->~value_type();
            }
        }
        static constexpr void destroy(pointer begin, const_pointer end)
                noexcept(is_nothrow_destructible_v<value_type>) {
            if constexpr(not is_trivially_destructible_v<value_type>) {
                while(begin not_eq end) {
                    ++begin->~value_type();
                }
            }
        }
    };
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(stateless allocator of data structure library)
namespace data_structure {
    template <typename T>
    class allocator<type_holder<T>> final : private memory_pool<> {
    private:
        using base = memory_pool;
    public:
        using size_type = typename base::size_type;
        using difference_type = typename base::difference_type;
        using value_type = T;
        using reference = add_lvalue_reference_t<value_type>;
        using const_reference = add_const_reference_t<value_type>;
        using rvalue_reference = add_rvalue_reference_t<value_type>;
        using pointer = add_pointer_t<value_type>;
        using const_pointer = add_const_pointer_t<value_type>;
        using void_pointer = void *;
        using const_void_pointer = const void *;
    public:
        constexpr allocator() noexcept = default;
        constexpr allocator(const allocator &) noexcept = default;
        template <typename U>
        explicit constexpr allocator(const allocator<U> &) noexcept {}
        constexpr allocator(allocator &&) noexcept = default;
        template <typename U>
        explicit constexpr allocator(allocator<U> &&) noexcept {}
        ~allocator() noexcept = default;
    public:
        constexpr allocator &operator=(const allocator &) noexcept = default;
        template <typename U>
        constexpr allocator &operator=(const allocator<type_holder<U>> &) const noexcept {
            return *this;
        }
        constexpr allocator &operator=(allocator &&) noexcept = default;
        template <typename U>
        constexpr allocator &operator=(allocator<type_holder<U>> &&) const noexcept {
            return *this;
        }
        using base::operator new;
        using base::operator delete;
    public:
        static pointer allocate(size_type n) {
            return reinterpret_cast<pointer>(base::allocate(n));
        }
        static pointer allocate(size_type n, dynamic) noexcept {
            return reinterpret_cast<pointer>(base::allocate<true>(n));
        }
        static void deallocate(pointer p, size_type n) noexcept {
            base::deallocate(p, n);
        }
        template <typename ...Args>
        static pointer construct(pointer p, Args &&...args)
                noexcept(is_nothrow_constructible<value_type, Args...>::value) {
            return new (p) value_type(ds::forward<Args>(args)...);
        }
        template <typename ...Args>
        [[deprecated]]
        static pointer construct(pointer begin, const_pointer end, Args &&...args)
                noexcept(is_nothrow_constructible<value_type, Args...>::value) {
            auto cursor {begin};
            while(cursor not_eq end) {
                new (cursor++) value_type(forward<Args>(args)...);
            }
            return begin;
        }
        static constexpr void destroy(pointer p) noexcept {
            if constexpr(not is_trivially_destructible_v<value_type>) {
                p->~value_type();
            }
        }
        static constexpr void destroy(pointer begin, const_pointer end) noexcept {
            if constexpr(not is_trivially_destructible_v<value_type>) {
                while(begin not_eq end) {
                    begin++->~value_type();
                }
            }
        }
    };
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(allocator traits)
namespace data_structure {
    template <typename Allocator>
    struct allocator_traits {
    public:
        using allocator_type = Allocator;
        using size_type = typename allocator_type::size_type;
        using difference_type = typename allocator_type::difference_type;
        using value_type = typename allocator_type::value_type;
        using reference = typename allocator_type::reference;
        using const_reference = typename allocator_type::const_reference;
        using rvalue_reference = typename allocator_type::rvalue_reference;
        using pointer = typename allocator_type::pointer;
        using const_pointer = typename allocator_type::const_pointer;
        using void_pointer = typename allocator_type::void_pointer;
        using const_void_pointer = typename allocator_type::const_void_pointer;
    public:
        static void *operator new(size_t n) noexcept(has_nothrow_new_operator_v<allocator_type, size_t>) {
            return allocator_type::operator new(n);
        }
        static void operator delete(void *p) noexcept(has_nothrow_delete_operator_v<allocator_type, void *>) {
            return allocator_type::operator delete(p);
        }
        template <typename ...Args>
        static void *operator new(size_t n, Args &&...args)
                noexcept(noexcept(allocator_type::operator new (n, forward<Args>(args)...))) {
            return allocator_type::operator new(n, forward<Args>(args)...);
        }
        template <typename ...Args>
        static void operator delete(void *p, Args &&...args)
                noexcept(noexcept(allocator_type::operator delete(p, forward<Args>(args)...))) {
            return allocator_type::operator delete(p, forward<Args>(args)...);
        }
    public:
        static constexpr pointer allocate(allocator_type &allocator, size_type n)
                noexcept(noexcept(allocator.allocate(n))) {
            return allocator.allocate(n);
        }
        static constexpr pointer allocate(size_type n) noexcept(noexcept(allocator_type::allocate(n))) {
            return allocator_type::allocate(n);
        }
        static constexpr void deallocate(allocator_type &allocator, pointer begin, size_type n)
                noexcept(noexcept(allocator.deallocate(begin, n))) {
            allocator.deallocate(begin, n);
        }
        static constexpr void deallocate(pointer begin, size_type n)
                noexcept(noexcept(allocator_type::deallocate(begin, n))) {
            allocator_type::deallocate(begin, n);
        }
        static constexpr void construct(allocator_type &allocator, pointer obj, const_reference value)
                noexcept(noexcept(allocator.construct(obj, value))) {
            allocator.construct(obj, value);
        }
        static constexpr void construct(pointer obj, const_reference value)
                noexcept(noexcept(allocator_type::construct(obj, value))) {
            allocator_type::construct(obj, value);
        }
        static constexpr void construct(allocator_type &allocator, pointer obj, rvalue_reference value)
                noexcept(noexcept(allocator.construct(obj, ds::move(value)))) {
            allocator.construct(obj, ds::move(value));
        }
        static constexpr void construct(pointer obj, rvalue_reference value)
                noexcept(noexcept(allocator_type::construct(obj, ds::move(value)))) {
            allocator_type::construct(obj, ds::move(value));
        }
        static constexpr void construct(allocator_type &allocator, pointer obj)
                noexcept(noexcept(allocator.construct(obj))) {
            allocator.construct(obj);
        }
        static constexpr void construct(pointer obj) noexcept(noexcept(allocator_type::construct(obj))) {
            allocator_type::construct(obj);
        }
        static constexpr void destroy(allocator_type &allocator, pointer obj)
                noexcept(noexcept(allocator.destroy(obj))) {
            allocator.destroy(obj);
        }
        static constexpr void destroy(pointer obj) noexcept(noexcept(allocator_type::destroy(obj))) {
            allocator_type::destroy(obj);
        }
        static constexpr void destroy(allocator_type &allocator, pointer begin, pointer end)
                noexcept(noexcept(allocator.destroy(begin, end))) {
            allocator.destroy(begin, end);
        }
        static constexpr void destroy(pointer begin, pointer end)
                noexcept(noexcept(allocator_type::destroy(begin, end))) {
            allocator_type::destroy(begin, end);
        }
    };

    /* TODO : refactor it by modules in C++ 20 */
    #define allocator_traits_t(type, trait_name) typename ds::allocator_traits<type>::trait_name
}
__DATA_STRUCTURE_END

#endif //DATA_STRUCTURE_ALLOCATOR_HPP