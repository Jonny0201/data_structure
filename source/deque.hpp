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

#ifndef DATA_STRUCTURE_DEQUE_HPP
#define DATA_STRUCTURE_DEQUE_HPP

#include "allocator.hpp"

namespace data_structure {

__DATA_STRUCTURE_START(deque declaration)
template <typename T, typename Allocator = allocator<T>>
class deque {
public:
    using allocator_type = Allocator;
    using size_type = typename Allocator::size_type;
    using difference_type = typename Allocator::difference_type;
    using value_type = T;
    using reference = typename allocator_traits<Allocator>::reference;
    using const_reference = typename allocator_traits<Allocator>::const_reference;
    using rvalue_reference = typename allocator_traits<Allocator>::rvalue_reference;
    using pointer = typename allocator_traits<Allocator>::pointer;
    using const_pointer = typename allocator_traits<Allocator>::const_pointer;
    using iterator = __dsa::deque_iterator<T>;
    using const_iterator = __dsa::deque_iterator<T, true>;
    using reverse_iterator = reverse_iterator<iterator>;
    using const_reverse_iterator = ds::reverse_iterator<const_iterator>;
    static_assert(is_same_v<T, typename Allocator::value_type>,
            "The value type of deque should same as the allocator's value_type!");
private:
    using map_allocator = typename allocator_traits<Allocator>::template rebind<T *>;
public:
    static constexpr auto block_size {sizeof(T) < 256 ? 4096 / sizeof(T) : 16};
private:
    __dsa::allocator_compressor<T **, map_allocator> map;
    __dsa::allocator_compressor<size_type, Allocator> map_size;
    size_type first;
    size_type last;
public:
    constexpr deque() noexcept(is_nothrow_copy_constructible_v<Allocator> and
            is_nothrow_default_constructible_v<map_allocator>) = default;
    explicit constexpr deque(const Allocator &) noexcept(is_nothrow_copy_constructible_v<Allocator> and
            is_nothrow_default_constructible_v<map_allocator>);
    explicit constexpr deque(size_type, const Allocator & = {});
    constexpr deque(size_type, const_reference, const Allocator & = {});
    template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
    constexpr deque(InputIterator, InputIterator, const Allocator & = {});
    template <IsForwardIterator ForwardIterator>
    constexpr deque(ForwardIterator, ForwardIterator, const Allocator & = {});
    constexpr deque(initializer_list<T>);
    constexpr deque(const deque &);
    constexpr deque(const deque &, const Allocator &);
    constexpr deque(deque &&) noexcept;
    constexpr deque(deque &&, const Allocator &) noexcept(is_nothrow_copy_constructible_v<Allocator>);
    constexpr ~deque() noexcept;
public:
    constexpr deque &operator=(const deque &);
    constexpr deque &operator=(deque &&) noexcept;
    constexpr deque &operator=(initializer_list<T>);
    constexpr reference operator[](size_type) noexcept;
    constexpr const_reference operator[](size_type) const noexcept;
public:
    constexpr void assign(size_type, const_reference = {});
    template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
    constexpr void assign(InputIterator, InputIterator, size_type = 64);
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
    constexpr size_type front_spare() const noexcept;
    [[nodiscard]]
    constexpr size_type back_spare() const noexcept;
    [[nodiscard]]
    constexpr size_type spare() const noexcept;
    constexpr void reserve(size_type);
    constexpr void shrink_to_fit();
    constexpr void resize(size_type);
    constexpr void resize(size_type, const_reference);
    [[nodiscard]]
    constexpr reference front() noexcept;
    [[nodiscard]]
    constexpr const_reference front() const noexcept;
    [[nodiscard]]
    constexpr reference back() noexcept;
    [[nodiscard]]
    constexpr const_reference back() const noexcept;
    [[nodiscard]]
    constexpr Allocator allocator() const noexcept;
    constexpr void push_back(const_reference);
    constexpr void push_back(rvalue_reference);
    template <typename ...Args>
    constexpr void emplace_back(Args &&...);
    constexpr void pop_back() noexcept;
    constexpr void clear() noexcept;
    constexpr void swap(deque &) noexcept;
    constexpr iterator insert(size_type, const_reference, size_type = 1);
    constexpr iterator insert(const_iterator, const_reference, size_type = 1);
    template <typename ...Args>
    constexpr iterator emplace(size_type, Args &&...);
    template <typename ...Args>
    constexpr iterator emplace(const_iterator, Args &&...);
    constexpr iterator insert(size_type, rvalue_reference);
    constexpr iterator insert(const_iterator, rvalue_reference);
    template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
    constexpr iterator insert(size_type, InputIterator, InputIterator);
    template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
    constexpr iterator insert(const_iterator, InputIterator, InputIterator);
    template <IsForwardIterator ForwardIterator>
    constexpr iterator insert(size_type, ForwardIterator, ForwardIterator);
    template <IsForwardIterator ForwardIterator>
    constexpr iterator insert(const_iterator, ForwardIterator, ForwardIterator);
    constexpr iterator insert(size_type, initializer_list<T>);
    constexpr iterator insert(const_iterator, initializer_list<T>);
    constexpr iterator erase(size_type, size_type = 1);
    constexpr iterator erase(const_iterator, size_type);
    constexpr iterator erase(const_iterator);
    constexpr iterator erase(const_iterator, const_iterator);
};
__DATA_STRUCTURE_END(deque declaration)

}

#endif      //DATA_STRUCTURE_DEQUE_HPP
