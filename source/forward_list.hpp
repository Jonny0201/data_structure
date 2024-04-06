/*
    * Copyright © [2019 - 2024] [Jonny Charlotte]
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

#ifndef DATA_STRUCTURE_FORWARD_LIST_HPP
#define DATA_STRUCTURE_FORWARD_LIST_HPP

#include "iterator.hpp"
#include "allocator.hpp"

namespace data_structure {

__DATA_STRUCTURE_START(forward_list declaration)
// Todo : enable memory pool
template <typename T, typename Allocator = allocator<T>>
class forward_list {
private:
    using begin_node_value_type = __dsa::forward_list_base_node<__dsa::forward_list_node<T>>;
    using begin_node_type = begin_node_value_type *;
    using node_value_type = __dsa::forward_list_node<T>;
    using node_type = node_value_type *;
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
    using iterator = __dsa::forward_list_iterator<T>;
    using const_iterator = __dsa::forward_list_iterator<T, true>;
    static_assert(is_same_v<T, typename Allocator::value_type>,
            "The value type of forward_list should same as the allocator's value_type!");
private:
    begin_node_value_type head {};
    __dsa::allocator_compressor<size_type, Allocator> node_size {};
public:
    constexpr forward_list() noexcept(is_nothrow_default_constructible_v<Allocator>) = default;
    explicit constexpr forward_list(const Allocator &) noexcept;
    explicit constexpr forward_list(size_type, const Allocator & = {});
    constexpr forward_list(size_type, const_reference, const Allocator & = {});
    template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
    constexpr forward_list(InputIterator, InputIterator, const Allocator & = {}, size_type = 64);
    template <IsForwardIterator ForwardIterator>
    constexpr forward_list(ForwardIterator, ForwardIterator, const Allocator & = {});
    constexpr forward_list(initializer_list<T>, const Allocator & = {});
    constexpr forward_list(const forward_list &);
    constexpr forward_list(const forward_list &, const Allocator &);
    constexpr forward_list(forward_list &&) noexcept;
    constexpr forward_list(forward_list &&, const Allocator &) noexcept;
    constexpr ~forward_list() noexcept;
public:
    constexpr forward_list &operator=(const forward_list &);
    constexpr forward_list &operator=(forward_list &&) noexcept;
    constexpr forward_list &operator=(initializer_list<T>);
public:
    constexpr void assign(size_type, const_reference = {});
    template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
    constexpr void assign(InputIterator, InputIterator, size_type = 64);
    template <IsForwardIterator ForwardIterator>
    constexpr void assign(ForwardIterator, ForwardIterator);
    constexpr void assign(initializer_list<T>);
    [[nodiscard]]
    constexpr iterator before_begin() noexcept;
    [[nodiscard]]
    constexpr const_iterator before_begin() const noexcept;
    [[nodiscard]]
    constexpr const_iterator cbefore_begin() const noexcept;
    [[nodiscard]]
    constexpr iterator begin() noexcept;
    [[nodiscard]]
    constexpr const_iterator begin() const noexcept;
    [[nodiscard]]
    constexpr const_iterator cbegin() const noexcept;
    [[nodiscard]]
    consteval iterator end() noexcept;
    [[nodiscard]]
    consteval const_iterator end() const noexcept;
    [[nodiscard]]
    consteval const_iterator cend() const noexcept;
    [[nodiscard]]
    constexpr size_type size() const noexcept;
    [[nodiscard]]
    constexpr bool empty() const noexcept;
    constexpr void resize(size_type);
    constexpr void resize(size_type, const_reference);
    [[nodiscard]]
    constexpr reference front() noexcept;
    [[nodiscard]]
    constexpr const_reference front() const noexcept;
    [[nodiscard]]
    constexpr Allocator allocator() const noexcept;
    constexpr void push_front(const_reference);
    constexpr void push_front(rvalue_reference);
    template <typename ...Args>
    constexpr void emplace_front(Args &&...);
    constexpr void pop_front() noexcept;
    constexpr void clear() noexcept;
    constexpr void swap(forward_list &) noexcept;
    constexpr iterator insert(difference_type, const_reference, size_type = 1);
    constexpr iterator insert_after(const_iterator, const_reference, size_type = 1);
    template <typename ...Args>
    constexpr iterator emplace(difference_type, Args &&...);
    template <typename ...Args>
    constexpr iterator emplace_after(const_iterator, Args &&...);
    constexpr iterator insert(difference_type, rvalue_reference);
    constexpr iterator insert_after(const_iterator, rvalue_reference);
    template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
    constexpr iterator insert(difference_type, InputIterator, InputIterator);
    template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
    constexpr iterator insert_after(const_iterator, InputIterator, InputIterator);
    template <IsForwardIterator ForwardIterator>
    constexpr iterator insert(difference_type, ForwardIterator, ForwardIterator);
    template <IsForwardIterator ForwardIterator>
    constexpr iterator insert_after(const_iterator, ForwardIterator, ForwardIterator);
    constexpr iterator insert(difference_type, initializer_list<T>);
    constexpr iterator insert_after(const_iterator, initializer_list<T>);
    constexpr iterator erase(difference_type, size_type = 1);
    constexpr iterator erase_after(const_iterator, size_type);
    constexpr iterator erase_after(const_iterator);
    constexpr iterator erase_after(const_iterator, const_iterator);
};
template <typename T, typename Allocator>
inline constexpr void swap(forward_list<T, Allocator> &, forward_list<T, Allocator> &) noexcept;
// Todo : wait for header "compare.hpp"?
/*template <typename T, typename Allocator>
inline constexpr some_ordering operator<=>(forward_list<T, Allocator> &, forward_list<T, Allocator> &)
        noexcept(is_nothrow_three_way_comparable_v<T>);*/
__DATA_STRUCTURE_END

}

#endif      // DATA_STRUCTURE_FORWARD_LIST_HPP