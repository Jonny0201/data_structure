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

#ifndef DATA_STRUCTURE_ARRAY_HPP
#define DATA_STRUCTURE_ARRAY_HPP

#include "iterator.hpp"
#include "algorithm.hpp"

namespace data_structure {
    template <typename T, size_t Size>
    struct array {
    public:
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using value_type = T;
        using reference = add_lvalue_reference_t<value_type>;
        using const_reference = add_const_reference_t<value_type>;
        using rvalue_reference = add_rvalue_reference_t<value_type>;
        using pointer = add_pointer_t<value_type>;
        using const_pointer = add_const_pointer_t<value_type>;
        using iterator = pointer;
        using const_iterator = const_pointer;
        using reverse_iterator = reverse_iterator<iterator>;
        using const_reverse_iterator = ds::reverse_iterator<const_iterator>;
    public:
        value_type elements[Size];
    public:
        [[nodiscard]]
        constexpr reference operator[](difference_type n) noexcept {
            return this->elements[n];
        }
        [[nodiscard]]
        constexpr const_reference operator[](difference_type n) const noexcept {
            return this->elements[n];
        }
    public:
        constexpr void fill(const_reference value) noexcept(is_nothrow_copy_assignable_v<value_type>) {
            ds::fill_n(elements, Size, value);
        }
        constexpr void swap(array &rhs) noexcept(is_nothrow_swappable_v<value_type>) {
            ds::swap_ranges(this->elements, this->elements + Size, rhs);
        }
        [[nodiscard]]
        constexpr iterator begin() noexcept {
            return this->elements;
        }
        [[nodiscard]]
        constexpr const_iterator begin() const noexcept {
            return this->elements;
        }
        [[nodiscard]]
        constexpr iterator end() noexcept {
            return this->elements + Size;
        }
        [[nodiscard]]
        constexpr const_iterator end() const noexcept {
            return this->elements + Size;
        }
        [[nodiscard]]
        constexpr const_iterator cbegin() const noexcept {
            return this->elements;
        }
        [[nodiscard]]
        constexpr const_iterator cend() const noexcept {
            return this->elements;
        }
        [[nodiscard]]
        constexpr reverse_iterator rbegin() noexcept {
            return reverse_iterator(this->elements + (Size - 1));
        }
        [[nodiscard]]
        constexpr const_reverse_iterator rbegin() const noexcept {
            return const_reverse_iterator(this->elements + (Size - 1));
        }
        [[nodiscard]]
        constexpr reverse_iterator rend() noexcept {
            return reverse_iterator(this->elements - 1);
        }
        [[nodiscard]]
        constexpr const_reverse_iterator rend() const noexcept {
            return const_reverse_iterator(this->elements - 1);
        }
        [[nodiscard]]
        constexpr const_reverse_iterator rcbegin() const noexcept {
            return const_reverse_iterator(this->elements + (Size - 1));
        }
        [[nodiscard]]
        constexpr const_reverse_iterator rcend() const noexcept {
            return const_reverse_iterator(this->elements - 1);
        }
        [[nodiscard]]
        consteval size_type size() const noexcept {
            return Size;
        }
        [[nodiscard]]
        consteval size_type max_size() const noexcept {
            return Size;
        }
        [[nodiscard]]
        constexpr bool empty() const noexcept {
            return false;
        }
        [[nodiscard]]
        constexpr reference at(difference_type n) noexcept {
            return (*this)[n];
        }
        [[nodiscard]]
        constexpr const_reference at(difference_type n) const noexcept {
            return (*this)[n];
        }
        [[nodiscard]]
        constexpr reference front() noexcept {
            return *this->elements;
        }
        [[nodiscard]]
        constexpr const_reference front() const noexcept {
            return *this->elements;
        }
        [[nodiscard]]
        constexpr reference back() noexcept {
            return *(this->elements + (Size - 1));
        }
        [[nodiscard]]
        constexpr const_reference back() const noexcept {
            return *(this->elements + (Size - 1));
        }
        [[nodiscard]]
        constexpr pointer data() noexcept {
            return this->elements;
        }
        [[nodiscard]]
        constexpr const_pointer data() const noexcept {
            return this->elements;
        }
    };
    
    template <typename T, size_t Size>
    void swap(const array<T, Size> &, const array<T, Size> &) noexcept(is_nothrow_swappable_v<T>);
    template <typename T, size_t Size>
    [[nodiscard]]
    bool operator==(const array<T, Size> &, const array<T, Size> &) noexcept(has_nothrow_equal_to_operator_v<T>);
    template <typename T, size_t Size>
    [[nodiscard]]
    bool operator!=(const array<T, Size> &, const array<T, Size> &) noexcept(has_nothrow_equal_to_operator_v<T>);
    template <typename T, size_t Size>
    [[nodiscard]]
    bool operator<(const array<T, Size> &, const array<T, Size> &) noexcept(has_nothrow_less_operator_v<T>);
    template <typename T, size_t Size>
    [[nodiscard]]
    bool operator<=(const array<T, Size> &, const array<T, Size> &) noexcept(has_nothrow_less_operator_v<T>);
    template <typename T, size_t Size>
    [[nodiscard]]
    bool operator>(const array<T, Size> &, const array<T, Size> &) noexcept(has_nothrow_less_operator_v<T>);
    template <typename T, size_t Size>
    [[nodiscard]]
    bool operator>=(const array<T, Size> &, const array<T, Size> &) noexcept(has_nothrow_less_operator_v<T>);
}

namespace data_structure {
    template <typename T>
    struct array<T, 0> {
    private:
        using char_type = conditional_t<is_const_v<T>, const char, char>;
    private:
        struct array_t {
            T data[1];
        };
    public:
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using value_type = T;
        using reference = add_lvalue_reference_t<value_type>;
        using const_reference = add_const_reference_t<value_type>;
        using rvalue_reference = add_rvalue_reference_t<value_type>;
        using pointer = add_pointer_t<value_type>;
        using const_pointer = add_const_pointer_t<value_type>;
        using iterator = pointer;
        using const_iterator = const_pointer;
        using reverse_iterator = data_structure::reverse_iterator<iterator>;
        using const_reverse_iterator = data_structure::reverse_iterator<const_iterator>;
    public:
        alignas(array_t) char_type elements[sizeof(array_t)];
    public:
        consteval void operator[](difference_type n) noexcept {
            static_assert(not is_complete_v<T>,
                    "Cannot call array<value_type, 0>::operator[] on a zero-sized array!");
        }
        consteval void operator[](difference_type n) const noexcept {
            static_assert(not is_complete_v<T>,
                    "Cannot call array<value_type, 0>::operator[] on a zero-sized array!");
        }
    public:
        consteval void fill(const_reference value) noexcept {
            static_assert(not is_const_v<value_type>,
                    "Cannot fill array<value_type, 0> held constant value_type!");
        }
        consteval void swap(array &rhs) noexcept(is_nothrow_swappable<value_type>::value) {
            static_assert(not is_const_v<value_type>,
                    "Cannot swap array<value_type, 0> held constant value_type!");
        }
        [[nodiscard]]
        constexpr iterator begin() noexcept {
            return this->elements;
        }
        [[nodiscard]]
        constexpr const_iterator begin() const noexcept {
            return this->elements;
        }
        [[nodiscard]]
        constexpr iterator end() noexcept {
            return this->elements;
        }
        [[nodiscard]]
        constexpr const_iterator end() const noexcept {
            return this->elements;
        }
        [[nodiscard]]
        constexpr const_iterator cbegin() const noexcept {
            return this->elements;
        }
        [[nodiscard]]
        constexpr const_iterator cend() const noexcept {
            return this->elements;
        }
        [[nodiscard]]
        constexpr reverse_iterator rbegin() noexcept {
            return reverse_iterator(this->elements);
        }
        [[nodiscard]]
        constexpr const_reverse_iterator rbegin() const noexcept {
            return const_reverse_iterator(this->elements);
        }
        [[nodiscard]]
        constexpr reverse_iterator rend() noexcept {
            return reverse_iterator(this->elements);
        }
        [[nodiscard]]
        constexpr const_reverse_iterator rend() const noexcept {
            return const_reverse_iterator(this->elements);
        }
        [[nodiscard]]
        constexpr const_reverse_iterator rcbegin() const noexcept {
            return const_reverse_iterator(this->elements);
        }
        [[nodiscard]]
        constexpr const_reverse_iterator rcend() const noexcept {
            return const_reverse_iterator(this->elements);
        }
        [[nodiscard]]
        consteval size_type size() const noexcept {
            return 0;
        }
        [[nodiscard]]
        consteval size_type max_size() const noexcept {
            return 0;
        }
        [[nodiscard]]
        consteval bool empty() const noexcept {
            return true;
        }
        consteval void at(difference_type n) noexcept {
            (*this)[n];
        }
        consteval void at(difference_type n) const noexcept {
            (*this)[n];
        }
        consteval void front() noexcept {
            static_assert(not is_complete_v<value_type>, "Trying to get elements from a zero-sized array!");
        }
        consteval void front() const noexcept {
            static_assert(not is_complete_v<value_type>, "Trying to get elements from a zero-sized array!");
        }
        consteval void back() noexcept {
            static_assert(not is_complete_v<value_type>, "Trying to get elements from a zero-sized array!");
        }
        consteval void back() const noexcept {
            static_assert(not is_complete_v<value_type>, "Trying to get elements from a zero-sized array!");
        }
        [[nodiscard]]
        constexpr pointer data() noexcept {
            return this->elements;
        }
        [[nodiscard]]
        constexpr const_pointer data() const noexcept {
            return this->elements;
        }
    };
}

namespace data_structure {
    template <typename T, size_t Size>
    inline void swap(const array<T, Size> &lhs, const array<T, Size> &rhs)
            noexcept(is_nothrow_swappable_v<T>) {
        lhs.swap(rhs);
    }
    template <typename T, size_t Size>
    bool operator==(const array<T, Size> &lhs, const array<T, Size> &rhs)
            noexcept(has_nothrow_equal_to_operator_v<T>) {
        for(auto i {0}; i < Size; ++i) {
            if(not(lhs[i] == rhs[i])) {
                return false;
            }
        }
        return true;
    }
    template <typename T, size_t Size>
    inline bool operator!=(const array<T, Size> &lhs, const array<T, Size> &rhs)
            noexcept(has_nothrow_equal_to_operator_v<T>) {
        return not(lhs == rhs);
    }
    template <typename T, size_t Size>
    bool operator<(const array<T, Size> &lhs, const array<T, Size> &rhs)
            noexcept(has_nothrow_less_operator_v<T>) {
        for(auto i {0}; i < Size; ++i) {
            if(not(lhs[i] < rhs[i])) {
                return false;
            }
        }
        return true;
    }
    template <typename T, size_t Size>
    bool operator<=(const array<T, Size> &lhs, const array<T, Size> &rhs)
            noexcept(has_nothrow_less_operator_v<T>) {
        return not(rhs < lhs);
    }
    template <typename T, size_t Size>
    bool operator>(const array<T, Size> &lhs, const array<T, Size> &rhs)
            noexcept(has_nothrow_less_operator_v<T>) {
        return rhs < lhs;
    }
    template <typename T, size_t Size>
    bool operator>=(const array<T, Size> &lhs, const array<T, Size> &rhs)
            noexcept(has_nothrow_less_operator_v<T>) {
        return not(lhs < rhs);
    }
}

#endif //DATA_STRUCTURE_ARRAY_HPP