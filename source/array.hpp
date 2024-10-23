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

#ifndef DATA_STRUCTURE_ARRAY_HPP
#define DATA_STRUCTURE_ARRAY_HPP

#include "utility.hpp"
#include "iterator.hpp"

namespace data_structure {

__DATA_STRUCTURE_START(array with non-zero size)
template <typename T, size_t N>
class array {
public:
    using allocator_type = void;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using rvalue_reference = T &&;
    using pointer = T *;
    using const_pointer = const T *;
    using iterator = T *;
    using const_iterator = const T *;
    using reverse_iterator = reverse_iterator<T *>;
    using const_reverse_iterator = ds::reverse_iterator<const T *>;
private:
    T elements[N];
public:
    [[nodiscard]]
    constexpr T &operator[](ptrdiff_t i) noexcept {
        return this->elements[i];
    }
    [[nodiscard]]
    constexpr const T &operator[](ptrdiff_t i) const noexcept {
        return this->elements[i];
    }
public:
    constexpr void fill(const T &value) noexcept(is_nothrow_copy_assignable_v<T>) {
        for(auto &element : this->elements) {
            element = value;
        }
    }
    template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
    constexpr void assign(InputIterator begin, InputIterator end) noexcept(
            is_nothrow_prefix_increasable_v<InputIterator> and is_nothrow_dereferenceable_v<InputIterator> and
            is_nothrow_assignable_v<T, decltype(ds::move(*ds::declval<InputIterator>()))>) {
        for(auto &element : this->elements) {
            element = ds::move(*begin++);
        }
    }
    template <IsForwardIterator ForwardIterator>
    constexpr void assign(ForwardIterator begin, ForwardIterator end) noexcept(
            is_nothrow_prefix_increasable_v<ForwardIterator> and is_nothrow_dereferenceable_v<ForwardIterator> and
            is_nothrow_assignable_v<T, decltype(*ds::declval<ForwardIterator>())>) {
        for(auto &element : this->elements) {
            element = *begin++;
        }
    }
    constexpr void assign(initializer_list<T> init_list) noexcept(is_nothrow_copy_assignable_v<T>) {
        const T *list {init_list.begin()};
        for(auto i {0uz}; i < N; ++i) {
            this->elements[i] = ds::move(list[i]);
        }
    }
    [[nodiscard]]
    constexpr T *begin() noexcept {
        return this->elements;
    }
    [[nodiscard]]
    constexpr const T *begin() const noexcept {
        return this->elements;
    }
    [[nodiscard]]
    constexpr const T *cbegin() const noexcept {
        return this->elements;
    }
    [[nodiscard]]
    constexpr T *end() noexcept {
        return this->elements + N;
    }
    [[nodiscard]]
    constexpr const T *end() const noexcept {
        return this->elements + N;
    }
    [[nodiscard]]
    constexpr const T *cend() const noexcept {
        return this->elements + N;
    }
    [[nodiscard]]
    constexpr reverse_iterator rbegin() noexcept {
        return reverse_iterator {this->elements + (N - 1)};
    }
    [[nodiscard]]
    constexpr const_reverse_iterator rbegin() const noexcept {
        return const_reverse_iterator {this->elements + (N - 1)};
    }
    [[nodiscard]]
    constexpr const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator {this->elements + (N - 1)};
    }
    [[nodiscard]]
    constexpr reverse_iterator rend() noexcept {
        return reverse_iterator {this->elements - 1};
    }
    [[nodiscard]]
    constexpr const_reverse_iterator rend() const noexcept {
        return const_reverse_iterator {this->elements - 1};
    }
    [[nodiscard]]
    constexpr const_reverse_iterator crend() const noexcept {
        return const_reverse_iterator {this->elements - 1};
    }
    [[nodiscard]]
    consteval size_t size() const noexcept {
        return N;
    }
    [[nodiscard]]
    consteval bool empty() const noexcept {
        return false;
    }
    [[nodiscard]]
    constexpr T &front() noexcept {
        return *this->elements;
    }
    [[nodiscard]]
    constexpr const T &front() const noexcept {
        return *this->elements;
    }
    [[nodiscard]]
    constexpr T &back() noexcept {
        return this->elements[N - 1];
    }
    [[nodiscard]]
    constexpr const T &back() const noexcept {
        return this->elements[N - 1];
    }
    [[nodiscard]]
    constexpr pointer data() noexcept {
        return this->elements;
    }
    [[nodiscard]]
    constexpr const_pointer data() const noexcept {
        return this->elements;
    }
    constexpr void swap(array &rhs) noexcept {
        using ds::swap;
        for(auto i {0uz}; i < N; ++i) {
            swap(this->elements[i], rhs.elements[i]);
        }
    }
};
template <typename T, size_t N>
void swap(array<T, N> &lhs, array<T, N> &rhs) noexcept {
    lhs.swap(rhs);
}
// Todo : wait for header "compare.hpp"?
/*template <typename T, size_t N>
inline constexpr some_ordering operator<=>(array<T, N> &, array<T, N> &)
        noexcept(is_nothrow_three_way_comparable_v<T>);*/
__DATA_STRUCTURE_END(array with non-zero size)

__DATA_STRUCTURE_START(array with zero size)
template <typename T>
class array<T, 0> {
public:
    using allocator_type = void;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using rvalue_reference = T &&;
    using pointer = T *;
    using const_pointer = const T *;
    using iterator = T *;
    using const_iterator = const T *;
    using reverse_iterator = reverse_iterator<T *>;
    using const_reverse_iterator = ds::reverse_iterator<const T *>;
public:
    consteval void operator[](ptrdiff_t) const noexcept {
        static_assert(is_type_v<T>, "The size of array is zero!");
    }
public:
    consteval void fill(const T &) noexcept {}
    template <typename Iterator>
    consteval void assign(Iterator, Iterator) noexcept {}
    consteval void assign(initializer_list<T>) noexcept {}
    [[nodiscard]]
    consteval T *begin() noexcept {
        return {};
    }
    [[nodiscard]]
    consteval const T *begin() const noexcept {
        return {};
    }
    [[nodiscard]]
    consteval const T *cbegin() const noexcept {
        return {};
    }
    [[nodiscard]]
    consteval T *end() noexcept {
        return{};
    }
    [[nodiscard]]
    consteval const T *end() const noexcept {
        return {};
    }
    [[nodiscard]]
    consteval const T *cend() const noexcept {
        return {};
    }
    [[nodiscard]]
    consteval reverse_iterator rbegin() noexcept {
        return {};
    }
    [[nodiscard]]
    consteval const_reverse_iterator rbegin() const noexcept {
        return {};
    }
    [[nodiscard]]
    consteval const_reverse_iterator crbegin() const noexcept {
        return {};
    }
    [[nodiscard]]
    consteval reverse_iterator rend() noexcept {
        return {};
    }
    [[nodiscard]]
    consteval const_reverse_iterator rend() const noexcept {
        return {};
    }
    [[nodiscard]]
    consteval const_reverse_iterator crend() const noexcept {
        return {};
    }
    [[nodiscard]]
    consteval size_t size() const noexcept {
        return 0;
    }
    [[nodiscard]]
    consteval bool empty() const noexcept {
        return true;
    }
    consteval void front() const noexcept {
        static_assert(is_type_v<T>, "The size of array is zero!");
    }
    consteval void back() const noexcept {
        static_assert(is_type_v<T>, "The size of array is zero!");
    }
    [[nodiscard]]
    consteval T *data() noexcept {
        return {};
    }
    [[nodiscard]]
    consteval const T *data() const noexcept {
        return {};
    }
    consteval void swap(array &rhs) noexcept {}
};
template <typename T>
inline consteval void swap(array<T, 0> &, array<T, 0> &) noexcept {}
template <typename T>
inline consteval strong_ordering operator<=>(array<T, 0> &, array<T, 0> &) noexcept {
    return strong_ordering::equal;
}
__DATA_STRUCTURE_END(array with zero size)

}

#endif      // DATA_STRUCTURE_ARRAY_HPP