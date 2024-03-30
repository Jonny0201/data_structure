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

#ifndef DATA_STRUCTURE_VECTOR_HPP
#define DATA_STRUCTURE_VECTOR_HPP

#include "allocator.hpp"
#include "iterator.hpp"

namespace data_structure {

__DATA_STRUCTURE_START(vector declaration)
template <typename T, typename Allocator = allocator<T>>
class vector {
public:
    using allocator_type = Allocator;
    using size_type = typename Allocator::size_type;
    using difference_type = typename Allocator::difference_type;
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using rvalue_reference = T &&;
    using pointer = typename Allocator::pointer;
    using const_pointer = typename Allocator::const_pointer;
    using iterator = wrap_iterator<pointer>;
    using const_iterator = wrap_iterator<const_pointer>;
    using reverse_iterator = reverse_iterator<pointer>;
    using const_reverse_iterator = ds::reverse_iterator<const_pointer>;
    static_assert(is_same_v<T, typename Allocator::value_type>,
            "The value type of vector should same as the allocator's value_type!");
private:
    struct exception_handler;
    friend struct exception_handler;
private:
    pointer first {};
    pointer cursor {};
    __dsa::allocator_compressor<pointer, Allocator> last {};
private:
    template <bool = true>
    constexpr void initialize(const T &);
    template <typename InputIterator>
    constexpr void initialize(InputIterator, InputIterator, false_type);
    template <typename ForwardIterator>
    constexpr void initialize(ForwardIterator, ForwardIterator, true_type);
public:
    constexpr vector() noexcept(is_nothrow_default_constructible_v<Allocator>) = default;
    explicit constexpr vector(const Allocator &) noexcept;
    explicit constexpr vector(size_type, const Allocator & = {});
    constexpr vector(size_type, const T &, const Allocator & = {});
    template <size_type = 64, IsInputIterator InputIterator>
            requires (not is_forward_iterator_v<InputIterator>)
    constexpr vector(InputIterator, InputIterator, const Allocator & = {});
    template <IsForwardIterator ForwardIterator>
    constexpr vector(ForwardIterator, ForwardIterator, const Allocator & = {});
    constexpr vector(initializer_list<T>, const Allocator & = {});
    constexpr vector(const vector &);
    constexpr vector(const vector &, const Allocator &);
    constexpr vector(vector &&) noexcept;
    constexpr vector(vector &&, const Allocator &) noexcept;
    constexpr ~vector() noexcept;
public:
    constexpr vector &operator=(const vector &);
    constexpr vector &operator=(vector &&) noexcept;
    constexpr vector &operator=(initializer_list<T>);
    [[nodiscard]]
    constexpr T &operator[](difference_type) noexcept(is_nothrow_indexable_v<pointer, difference_type>);
    [[nodiscard]]
    constexpr const T &operator[](difference_type) const noexcept(is_nothrow_indexable_v<pointer, difference_type>);
public:
    constexpr void assign(size_type, const T & = {});
    template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
    constexpr void assign(InputIterator, InputIterator);
    template <IsForwardIterator ForwardIterator>
    constexpr void assign(ForwardIterator, ForwardIterator);
    constexpr void assign(initializer_list<T>);
    [[nodiscard]]
    constexpr iterator begin() noexcept;
    [[nodiscard]]
    constexpr const_iterator begin() const noexcept;
    [[nodiscard]]
    constexpr const_iterator cbegin() const noexcept;
    [[nodiscard]]
    constexpr iterator end() noexcept;
    [[nodiscard]]
    constexpr const_iterator end() const noexcept;
    [[nodiscard]]
    constexpr const_iterator cend() const noexcept;
    [[nodiscard]]
    constexpr reverse_iterator rbegin() noexcept;
    [[nodiscard]]
    constexpr const_reverse_iterator rbegin() const noexcept;
    [[nodiscard]]
    constexpr const_reverse_iterator crbegin() const noexcept;
    [[nodiscard]]
    constexpr reverse_iterator rend() noexcept;
    [[nodiscard]]
    constexpr const_reverse_iterator rend() const noexcept;
    [[nodiscard]]
    constexpr const_reverse_iterator crend() const noexcept;
    [[nodiscard]]
    constexpr size_type size() const noexcept;
    [[nodiscard]]
    constexpr bool empty() const noexcept;
    [[nodiscard]]
    constexpr size_type capacity() const noexcept;
    [[nodiscard]]
    constexpr size_type spare() const noexcept;
    constexpr void reverse(size_type);
    constexpr void shrink_to_fit();
    constexpr void resize(size_type, const T & = {});
    [[nodiscard]]
    constexpr T &front() noexcept;
    [[nodiscard]]
    constexpr const T &front() const noexcept;
    [[nodiscard]]
    constexpr T &back() noexcept;
    [[nodiscard]]
    constexpr const T &back() const noexcept;
    [[nodiscard]]
    constexpr pointer data() noexcept;
    [[nodiscard]]
    constexpr const_pointer data() const noexcept;
    constexpr void push_back(const T &);
    constexpr void push_back(T &&);
    template <typename ...Args>
    constexpr void emplace_back(Args &&...);
    constexpr void pop_back() noexcept;
    constexpr void clear() noexcept;
    constexpr void swap(vector &) noexcept;
    constexpr iterator insert(difference_type, const T &, size_type = 1);
    constexpr iterator insert(const_iterator, const T &, size_type = 1);
    template <typename ...Args>
    constexpr iterator emplace(difference_type, Args &&...);
    template <typename ...Args>
    constexpr iterator emplace(const_iterator, Args &&...);
    constexpr iterator insert(difference_type, T &&);
    constexpr iterator insert(const_iterator, T &&);
    template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
    constexpr iterator insert(difference_type, InputIterator, InputIterator);
    template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
    constexpr iterator insert(const_iterator, InputIterator, InputIterator);
    template <IsForwardIterator ForwardIterator>
    constexpr iterator insert(difference_type, ForwardIterator, ForwardIterator);
    template <IsForwardIterator ForwardIterator>
    constexpr iterator insert(const_iterator, ForwardIterator, ForwardIterator);
    constexpr iterator insert(difference_type, initializer_list<T>);
    constexpr iterator insert(const_iterator, initializer_list<T>);
    constexpr iterator erase(difference_type, size_type = 1);
    constexpr iterator erase(const_iterator, size_type);
    constexpr iterator erase(const_iterator);
    constexpr iterator erase(const_iterator, const_iterator);
};
__DATA_STRUCTURE_END

}       // namespace data_structure

#endif      //DATA_STRUCTURE_VECTOR_HPP