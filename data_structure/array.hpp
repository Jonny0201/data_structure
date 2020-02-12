/*
    * Copyright © [2019 - 2020] [Jonny Charlotte]
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

#ifndef DATA_STRUCTURE_ARRAY_HPP
#define DATA_STRUCTURE_ARRAY_HPP

#include "type_traits.hpp"
#include "iterator.hpp"
#include "algorithm.hpp"

namespace data_structure {
    template <typename T, decltype(sizeof 0) Size>
    struct array final {
    public:
        using size_type = decltype(Size);
        using difference_type = decltype(static_cast<char *>(nullptr) - static_cast<char *>(nullptr));
        using value_type = T;
        using reference = typename add_lvalue_reference<value_type>::type;
        using const_reference = typename add_const_reference<value_type>::type;
        using rvalue_reference = typename add_rvalue_reference<value_type>::type;
        using pointer = typename add_pointer<value_type>::type;
        using const_pointer = typename add_const_pointer<value_type>::type;
        using iterator = pointer;
        using const_iterator = const_pointer;
        using reverse_iterator = data_structure::reverse_iterator<iterator>;
        using const_reverse_iterator = data_structure::reverse_iterator<const_iterator>;
    public:
        value_type elements[Size];
    public:
        constexpr reference operator[](difference_type n) noexcept {
            return this->elements[n];
        }
        constexpr const_reference operator[](difference_type n) const noexcept {
            return this->elements[n];
        }
    public:
        constexpr void fill(const_reference value) noexcept(is_nothrow_copy_assignable<value_type>::value) {
            ds::fill_n(elements, Size, value);
        }
        constexpr void swap(array &rhs) noexcept(is_nothrow_swappable<value_type>::value) {
            ds::swap_ranges(this->elements, this->elements + Size, rhs);
        }
        constexpr iterator begin() noexcept {
            return this->elements;
        }
        constexpr const_iterator begin() const noexcept {
            return this->elements;
        }
        constexpr iterator end() noexcept {
            return this->elements + Size;
        }
        constexpr const_iterator end() const noexcept {
            return this->elements + Size;
        }
        constexpr const_iterator cbegin() const noexcept {
            return this->elements;
        }
        constexpr const_iterator cend() const noexcept {
            return this->elements;
        }
        constexpr reverse_iterator rbegin() noexcept {
            return reverse_iterator(this->elements + (Size - 1));
        }
        constexpr const_reverse_iterator rbegin() const noexcept {
            return const_reverse_iterator(this->elements + (Size - 1));
        }
        constexpr reverse_iterator rend() noexcept {
            return reverse_iterator(this->elements - 1);
        }
        constexpr const_reverse_iterator rend() const noexcept {
            return const_reverse_iterator(this->elements - 1);
        }
        constexpr const_reverse_iterator rcbegin() const noexcept {
            return const_reverse_iterator(this->elements + (Size - 1));
        }
        constexpr const_reverse_iterator rcend() const noexcept {
            return const_reverse_iterator(this->elements - 1);
        }
        constexpr size_type size() const noexcept {
            return Size;
        }
        constexpr size_type max_size() const noexcept {
            return Size;
        }
        constexpr bool empty() const noexcept {
            return false;
        }
        constexpr reference at(difference_type n) noexcept {
            return (*this)[n];
        }
        constexpr const_reference at(difference_type n) const noexcept {
            return (*this)[n];
        }
        constexpr reference front() noexcept {
            return *this->elements;
        }
        constexpr const_reference front() const noexcept {
            return *this->elements;
        }
        constexpr reference back() noexcept {
            return *(this->elements + (Size - 1));
        }
        constexpr const_reference back() const noexcept {
            return *(this->elements + (Size - 1));
        }
        constexpr pointer data() noexcept {
            return this->elements;
        }
        constexpr const_pointer data() const noexcept {
            return this->elements;
        }
    };

    template <typename T, decltype(sizeof 0) Size>
    bool operator==(const array<T, Size> &lhs, const array<T, Size> &rhs)
            noexcept(has_nothrow_equal_to_operator<T>::value);
    template <typename T, decltype(sizeof 0) Size>
    bool operator!=(const array<T, Size> &lhs, const array<T, Size> &rhs)
            noexcept(has_nothrow_equal_to_operator<T>::value);
    template <typename T, decltype(sizeof 0) Size>
    bool operator<(const array<T, Size> &lhs, const array<T, Size> &rhs)
            noexcept(has_nothrow_less_operator<T>::value);
    template <typename T, decltype(sizeof 0) Size>
    bool operator<=(const array<T, Size> &lhs, const array<T, Size> &rhs)
            noexcept(has_nothrow_less_operator<T>::value);
    template <typename T, decltype(sizeof 0) Size>
    bool operator>(const array<T, Size> &lhs, const array<T, Size> &rhs)
            noexcept(has_nothrow_less_operator<T>::value);
    template <typename T, decltype(sizeof 0) Size>
    bool operator>=(const array<T, Size> &lhs, const array<T, Size> &rhs)
            noexcept(has_nothrow_less_operator<T>::value);
}

namespace data_structure {
    template <typename T>
    struct array<T, 0> final {
    private:
        using char_type = typename conditional<is_const<T>::value, const char, char>::type;
    private:
        struct array_t {
            T data[1];
        };
    public:
        using size_type = decltype(sizeof 0);
        using difference_type = decltype(static_cast<char *>(nullptr) - static_cast<char *>(nullptr));
        using value_type = T;
        using reference = typename add_lvalue_reference<value_type>::type;
        using const_reference = typename add_const_reference<value_type>::type;
        using rvalue_reference = typename add_rvalue_reference<value_type>::type;
        using pointer = typename add_pointer<value_type>::type;
        using const_pointer = typename add_const_pointer<value_type>::type;
        using iterator = pointer;
        using const_iterator = const_pointer;
        using reverse_iterator = data_structure::reverse_iterator<iterator>;
        using const_reverse_iterator = data_structure::reverse_iterator<const_iterator>;
    public:
        alignas(array_t) char_type elements[sizeof(array_t)];
    public:
    public:
        constexpr void operator[](difference_type n) noexcept {
            static_assert(not __dsa::is_type<T>::value,
                    "Cannot call array<T, 0>::operator[] on a zero-sized array!");
        }
        constexpr void operator[](difference_type n) const noexcept {
            static_assert(not __dsa::is_type<T>::value,
                    "Cannot call array<T, 0>::operator[] on a zero-sized array!");
        }
    public:
        constexpr void fill(const_reference value) noexcept {
            static_assert(is_const<value_type>::value,
                    "Cannot fill array<T, 0> held constant value_type!");
        }
        constexpr void swap(array &rhs) noexcept(is_nothrow_swappable<value_type>::value) {
            static_assert(is_const<value_type>::value,
                    "Cannot swap array<T, 0> held constant value_type!");
        }
        constexpr iterator begin() noexcept {
            return this->elements;
        }
        constexpr const_iterator begin() const noexcept {
            return this->elements;
        }
        constexpr iterator end() noexcept {
            return this->elements;
        }
        constexpr const_iterator end() const noexcept {
            return this->elements;
        }
        constexpr const_iterator cbegin() const noexcept {
            return this->elements;
        }
        constexpr const_iterator cend() const noexcept {
            return this->elements;
        }
        constexpr reverse_iterator rbegin() noexcept {
            return reverse_iterator(this->elements);
        }
        constexpr const_reverse_iterator rbegin() const noexcept {
            return const_reverse_iterator(this->elements);
        }
        constexpr reverse_iterator rend() noexcept {
            return reverse_iterator(this->elements);
        }
        constexpr const_reverse_iterator rend() const noexcept {
            return const_reverse_iterator(this->elements);
        }
        constexpr const_reverse_iterator rcbegin() const noexcept {
            return const_reverse_iterator(this->elements);
        }
        constexpr const_reverse_iterator rcend() const noexcept {
            return const_reverse_iterator(this->elements);
        }
        constexpr size_type size() const noexcept {
            return 0;
        }
        constexpr size_type max_size() const noexcept {
            return 0;
        }
        constexpr bool empty() const noexcept {
            return true;
        }
        constexpr void at(difference_type n) noexcept {
            (*this)[n];
        }
        constexpr void at(difference_type n) const noexcept {
            (*this)[n];
        }
        constexpr void front() noexcept {
            static_assert(not __dsa::is_type<value_type>::value,
                    "Trying to get elements from a zero-sized array!");
        }
        constexpr void front() const noexcept {
            static_assert(not __dsa::is_type<value_type>::value,
                    "Trying to get elements from a zero-sized array!");
        }
        constexpr void back() noexcept {
            static_assert(not __dsa::is_type<value_type>::value,
                    "Trying to get elements from a zero-sized array!");
        }
        constexpr void back() const noexcept {
            static_assert(not __dsa::is_type<value_type>::value,
                    "Trying to get elements from a zero-sized array!");
        }
        constexpr pointer data() noexcept {
            return this->elements;
        }
        constexpr const_pointer data() const noexcept {
            return this->elements;
        }
    };
}

namespace data_structure {
    template <typename T, decltype(sizeof 0) Size>
    bool operator==(const array<T, Size> &lhs, const array<T, Size> &rhs)
            noexcept(has_nothrow_equal_to_operator<T>::value) {
        for(auto i {0}; i < Size; ++i) {
            if(not(lhs[i] == rhs[i])) {
                return false;
            }
        }
        return true;
    }
    template <typename T, decltype(sizeof 0) Size>
    inline bool operator!=(const array<T, Size> &lhs, const array<T, Size> &rhs)
            noexcept(has_nothrow_equal_to_operator<T>::value) {
        return not(lhs == rhs);
    }
    template <typename T, decltype(sizeof 0) Size>
    bool operator<(const array<T, Size> &lhs, const array<T, Size> &rhs)
            noexcept(has_nothrow_less_operator<T>::value) {
        for(auto i {0}; i < Size; ++i) {
            if(not(lhs[i] < rhs[i])) {
                return false;
            }
        }
        return true;
    }
    template <typename T, decltype(sizeof 0) Size>
    bool operator<=(const array<T, Size> &lhs, const array<T, Size> &rhs)
            noexcept(has_nothrow_less_operator<T>::value) {
        return lhs < rhs or lhs == rhs;
    }
    template <typename T, decltype(sizeof 0) Size>
    bool operator>(const array<T, Size> &lhs, const array<T, Size> &rhs)
            noexcept(has_nothrow_less_operator<T>::value) {
        return rhs < lhs;
    }
    template <typename T, decltype(sizeof 0) Size>
    bool operator>=(const array<T, Size> &lhs, const array<T, Size> &rhs)
            noexcept(has_nothrow_less_operator<T>::value) {
        return not(lhs < rhs);
    }
}

#endif //DATA_STRUCTURE_ARRAY_HPP
