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

#ifndef DATA_STRUCTURE_ITERATOR_HPP
#define DATA_STRUCTURE_ITERATOR_HPP

#include "memory.hpp"

namespace data_structure {

__DATA_STRUCTURE_START(iterator tag)
struct iterator_tag {};
struct output_iterator_tag : iterator_tag {};
struct input_iterator_tag : iterator_tag {};
struct forward_iterator_tag : input_iterator_tag {};
struct bidirectional_iterator_tag : forward_iterator_tag {};
struct random_access_iterator_tag : bidirectional_iterator_tag {};
struct contiguous_iterator_tag : random_access_iterator_tag {};
__DATA_STRUCTURE_END(iterator tag)

__DATA_STRUCTURE_START(iterator traits)
template <typename Iterator>
struct iterator_traits {
    using size_type = typename Iterator::size_type;
    using difference_type = typename Iterator::difference_type;
    using value_type = typename Iterator::value_type;
    using reference = typename __dsa::traits_reference<Iterator, value_type &>::type;
    using const_reference = typename __dsa::traits_const_reference<Iterator, const value_type &>::type;
    using rvalue_reference = typename __dsa::traits_rvalue_reference<Iterator, value_type &&>::type;
    using pointer = typename __dsa::traits_pointer<Iterator, value_type *>::type;
    using const_pointer = typename __dsa::traits_const_pointer<Iterator, const value_type *>::type;
    using iterator_category = typename Iterator::iterator_category;
};
template <typename T>
struct iterator_traits<T *> {
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using rvalue_reference = T &&;
    using pointer = T *;
    using const_pointer = const T *;
    using iterator_category = contiguous_iterator_tag;
};

namespace __data_structure_auxiliary {
template <typename T, bool = is_pointer_v<T>, typename = void>
struct has_iterator_category_auxiliary : false_type {
    using is_iterator = false_type;
    using is_input_iterator = false_type;
    using is_output_iterator = false_type;
    using is_forward_iterator = false_type;
    using is_bidirectional_iterator = false_type;
    using is_random_access_iterator = false_type;
    using is_contiguous_iterator = false_type;
};
template <typename T>
struct has_iterator_category_auxiliary<T, false, void_t<typename T::iterator_category>> : true_type {
    using is_iterator = is_base_of<iterator_tag, typename T::iterator_category>;
    using is_input_iterator = is_base_of<input_iterator_tag, typename T::iterator_category>;
    using is_output_iterator = is_same<output_iterator_tag, typename T::iterator_category>;
    using is_forward_iterator = is_base_of<forward_iterator_tag, typename T::iterator_category>;
    using is_bidirectional_iterator = is_base_of<bidirectional_iterator_tag, typename T::iterator_category>;
    using is_random_access_iterator = is_base_of<random_access_iterator_tag, typename T::iterator_category>;
    using is_contiguous_iterator = is_same<contiguous_iterator_tag, typename T::iterator_category>;
};
template <typename T>
struct has_iterator_category_auxiliary<T, true, void> : true_type {
    using is_iterator = true_type;
    using is_input_iterator = true_type;
    using is_output_iterator = true_type;
    using is_forward_iterator = true_type;
    using is_bidirectional_iterator = true_type;
    using is_random_access_iterator = true_type;
    using is_contiguous_iterator = true_type;
};
}
template <typename T>
struct has_iterator_category : __dsa::has_iterator_category_auxiliary<T> {};
template <typename T>
inline constexpr auto has_iterator_category_v {has_iterator_category<T>::value};
template <typename T>
concept HasIteratorCategory = has_iterator_category_v<T>;

template <typename Iterator>
struct is_iterator : __dsa::has_iterator_category_auxiliary<Iterator>::is_iterator {};
template <typename Iterator>
inline constexpr auto is_iterator_v {is_iterator<Iterator>::value};
template <typename Iterator>
concept IsIterator = is_iterator_v<Iterator>;

template <typename Iterator>
struct is_input_iterator : __dsa::has_iterator_category_auxiliary<Iterator>::is_input_iterator {};
template <typename Iterator>
inline constexpr auto is_input_iterator_v {is_input_iterator<Iterator>::value};
template <typename Iterator>
concept IsInputIterator = is_input_iterator_v<Iterator>;

template <typename Iterator>
struct is_output_iterator : __dsa::has_iterator_category_auxiliary<Iterator>::is_output_iterator {};
template <typename Iterator>
inline constexpr auto is_output_iterator_v {is_output_iterator<Iterator>::value};
template <typename Iterator>
concept IsOutputIterator = is_output_iterator_v<Iterator>;

template <typename Iterator>
struct is_forward_iterator : __dsa::has_iterator_category_auxiliary<Iterator>::is_forward_iterator {};
template <typename Iterator>
inline constexpr auto is_forward_iterator_v {is_forward_iterator<Iterator>::value};
template <typename Iterator>
concept IsForwardIterator = is_forward_iterator_v<Iterator>;

template <typename Iterator>
struct is_bidirectional_iterator : __dsa::has_iterator_category_auxiliary<Iterator>::is_bidirectional_iterator {};
template <typename Iterator>
inline constexpr auto is_bidirectional_iterator_v {is_bidirectional_iterator<Iterator>::value};
template <typename Iterator>
concept IsBidirectionalIterator = is_bidirectional_iterator_v<Iterator>;

template <typename Iterator>
struct is_random_access_iterator : __dsa::has_iterator_category_auxiliary<Iterator>::is_random_access_iterator {};
template <typename Iterator>
inline constexpr auto is_random_access_iterator_v {is_random_access_iterator<Iterator>::value};
template <typename Iterator>
concept IsRandomAccessIterator = is_random_access_iterator_v<Iterator>;

template <typename Iterator>
struct is_contiguous_iterator : __dsa::has_iterator_category_auxiliary<Iterator>::is_contiguous_iterator {};
template <typename Iterator>
inline constexpr auto is_contiguous_iterator_v {is_contiguous_iterator<Iterator>::value};
template <typename Iterator>
concept IsContiguousIterator = is_contiguous_iterator_v<Iterator>;
__DATA_STRUCTURE_END(iterator traits)

__DATA_STRUCTURE_START(iterator functions)
template <IsRandomAccessIterator RandomAccessIterator>
inline constexpr typename iterator_traits<RandomAccessIterator>::difference_type distance(RandomAccessIterator begin,
        RandomAccessIterator end) noexcept(is_nothrow_subtractable_v<RandomAccessIterator>) {
    return end - begin;
}
template <typename InputIterator>
inline constexpr typename iterator_traits<InputIterator>::difference_type distance(InputIterator begin,
        InputIterator end) noexcept(is_nothrow_prefix_increasable_v<InputIterator> and
                is_nothrow_constructible_v<typename iterator_traits<InputIterator>::difference_type, int> and
                is_nothrow_prefix_increasable_v<typename iterator_traits<InputIterator>::difference_type>) {
    typename iterator_traits<InputIterator>::difference_type difference {0};
    while(begin not_eq end) {
        ++begin;
        ++difference;
    }
    return difference;
}
inline constexpr ptrdiff_t distance(void *begin, void *end) noexcept {
    return static_cast<char *>(end) - static_cast<char *>(begin);
}

template <IsRandomAccessIterator RandomAccessIterator>
inline constexpr RandomAccessIterator advance(RandomAccessIterator begin,
        typename iterator_traits<RandomAccessIterator>::difference_type n) noexcept(is_nothrow_addable_v<
                RandomAccessIterator, typename iterator_traits<RandomAccessIterator>::difference_type>) {
    return begin + n;
}
template <typename InputIterator>
inline constexpr InputIterator advance(InputIterator begin, typename iterator_traits<InputIterator>::difference_type n)
        noexcept(is_nothrow_prefix_increasable_v<InputIterator>) {
    for(; n not_eq 0; --n, static_cast<void>(++begin));
    return begin;
}
__DATA_STRUCTURE_END(iterator functions)

__DATA_STRUCTURE_START(wrap iterator)
template <typename Iterator> requires is_pointer_v<Iterator>
class wrap_iterator {
public:
    using iterator_type = Iterator;
    using size_type = typename iterator_traits<Iterator>::size_type;
    using difference_type = typename iterator_traits<Iterator>::difference_type;
    using value_type = typename iterator_traits<Iterator>::value_type;
    using iterator_category = typename iterator_traits<Iterator>::iterator_category;
private:
    Iterator iterator {};
public:
    constexpr wrap_iterator() noexcept = default;
    explicit constexpr wrap_iterator(Iterator iterator) noexcept : iterator {iterator} {}
    constexpr wrap_iterator(const wrap_iterator &) noexcept = default;
    constexpr wrap_iterator(wrap_iterator &&) noexcept = default;
    constexpr ~wrap_iterator() noexcept = default;
public:
    constexpr wrap_iterator &operator=(const wrap_iterator &) noexcept = default;
    constexpr wrap_iterator &operator=(wrap_iterator &&) noexcept = default;
    [[nodiscard]]
    constexpr decltype(auto) operator*() noexcept {
        return *this->iterator;
    }
    [[nodiscard]]
    constexpr decltype(auto) operator*() const noexcept {
        return *this->iterator;
    }
    [[nodiscard]]
    constexpr auto operator->() noexcept {
        return ds::address_of(**this);
    }
    [[nodiscard]]
    constexpr auto operator->() const noexcept {
        return ds::address_of(**this);
    }
    [[nodiscard]]
    constexpr decltype(auto) operator[](difference_type n) noexcept {
        return this->iterator[n];
    };
    constexpr wrap_iterator &operator++() & noexcept {
        ++this->iterator;
        return *this;
    }
    constexpr wrap_iterator operator++(int) & noexcept {
        auto backup {*this};
        ++*this;
        return backup;
    }
    constexpr wrap_iterator &operator--() & noexcept {
        --this->iterator;
        return *this;
    }
    constexpr wrap_iterator operator--(int) & noexcept {
        auto backup {*this};
        --*this;
        return backup;
    }
    constexpr wrap_iterator &operator+=(difference_type n) & noexcept {
        this->iterator += n;
        return *this;
    }
    constexpr wrap_iterator &operator-=(difference_type n) & noexcept {
        this->iterator += -n;
        return *this;
    }
    constexpr wrap_iterator operator+(difference_type n) noexcept {
        auto backup {*this};
        return backup += n;
    }
    constexpr wrap_iterator operator-(difference_type n) noexcept {
        auto backup {*this};
        return backup += -n;
    }
    [[nodiscard]]
    explicit constexpr operator bool() const noexcept {
        return static_cast<bool>(this->iterator);
    }
public:
    [[nodiscard]]
    constexpr Iterator base() const noexcept {
        return this->iterator;
    }
};
template <typename IteratorLHS, typename IteratorRHS>
[[nodiscard]]
inline constexpr bool operator==(const wrap_iterator<IteratorLHS> &lhs,
        const wrap_iterator<IteratorRHS> &rhs) noexcept {
    return lhs.base() == rhs.base();
}
template <typename IteratorLHS, typename IteratorRHS>
[[nodiscard]]
inline constexpr bool operator!=(const wrap_iterator<IteratorLHS> &lhs,
        const wrap_iterator<IteratorRHS> &rhs) noexcept {
    return not(lhs == rhs);
}
template <typename IteratorLHS, typename IteratorRHS>
[[nodiscard]]
inline constexpr bool operator<(const wrap_iterator<IteratorLHS> &lhs,
        const wrap_iterator<IteratorRHS> &rhs) noexcept {
    return lhs.base() - rhs.base() < 0;
}
template <typename IteratorLHS, typename IteratorRHS>
[[nodiscard]]
inline constexpr bool operator>(const wrap_iterator<IteratorLHS> &lhs,
        const wrap_iterator<IteratorRHS> &rhs) noexcept {
    return rhs < lhs;
}
template <typename IteratorLHS, typename IteratorRHS>
[[nodiscard]]
inline constexpr bool operator<=(const wrap_iterator<IteratorLHS> &lhs,
        const wrap_iterator<IteratorRHS> &rhs) noexcept {
    return not(lhs > rhs);
}
template <typename IteratorLHS, typename IteratorRHS>
[[nodiscard]]
inline constexpr bool operator>=(const wrap_iterator<IteratorLHS> &lhs,
        const wrap_iterator<IteratorRHS> &rhs) noexcept {
    return not(lhs < rhs);
}
template <typename IteratorLHS, typename IteratorRHS>
[[nodiscard]]
inline constexpr ptrdiff_t operator-(const wrap_iterator<IteratorLHS> &lhs,
        const wrap_iterator<IteratorRHS> &rhs) noexcept {
    return lhs.base() - rhs.base();
}
__DATA_STRUCTURE_END(wrap iterator)

__DATA_STRUCTURE_START(reverse iterator)
template <IsIterator Iterator>
class reverse_iterator {
public:
    using iterator_type = Iterator;
    using size_type = typename iterator_traits<Iterator>::size_type;
    using difference_type = typename iterator_traits<Iterator>::difference_type;
    using value_type = typename iterator_traits<Iterator>::value_type;
    using iterator_category = typename iterator_traits<Iterator>::iterator_category;
private:
    Iterator iterator {};
public:
    constexpr reverse_iterator() = default;
    explicit constexpr reverse_iterator(Iterator iterator)
            noexcept(is_nothrow_copy_constructible_v<Iterator>) : iterator {iterator} {}
    constexpr reverse_iterator(const reverse_iterator &) = default;
    constexpr reverse_iterator(reverse_iterator &&) = default;
    constexpr ~reverse_iterator() noexcept = default;
public:
    constexpr reverse_iterator &operator=(const reverse_iterator &) = default;
    constexpr reverse_iterator &operator=(reverse_iterator &&) = default;
public:
    [[nodiscard]]
    constexpr decltype(auto) operator*() noexcept(is_nothrow_dereferenceable_v<Iterator>) {
        return *this->iterator;
    }
    [[nodiscard]]
    constexpr decltype(auto) operator*() const noexcept(is_nothrow_dereferenceable_v<Iterator>) {
        return *this->iterator;
    }
    [[nodiscard]]
    constexpr auto operator->() noexcept(is_nothrow_dereferenceable_v<Iterator>) {
        return ds::address_of(**this);
    }
    [[nodiscard]]
    constexpr auto operator->() const noexcept(is_nothrow_dereferenceable_v<Iterator>) {
        return ds::address_of(**this);
    }
    [[nodiscard]]
    constexpr decltype(auto) operator[](difference_type n) noexcept(is_nothrow_indexable_v<Iterator, difference_type>) {
        return this->iterator[n];
    }
    constexpr reverse_iterator &operator++() & noexcept(is_nothrow_prefix_decreasable_v<Iterator>) {
        --this->iterator;
        return *this;
    }
    constexpr reverse_iterator operator++(int) & noexcept(is_nothrow_prefix_decreasable_v<Iterator> and
            is_nothrow_copy_constructible_v<Iterator>) {
        auto backup {*this};
        --this->iterator;
        return backup;
    }
    constexpr reverse_iterator &operator--() & noexcept(is_nothrow_prefix_increasable_v<Iterator>)
            requires is_bidirectional_iterator_v<Iterator> {
        ++this->iterator;
        return *this;
    }
    constexpr reverse_iterator operator--(int) & noexcept(is_nothrow_prefix_increasable_v<Iterator> and
            is_nothrow_copy_constructible_v<Iterator>) requires is_bidirectional_iterator_v<Iterator> {
        auto backup {*this};
        ++this->iterator;
        return backup;
    }
    constexpr reverse_iterator &operator+=(difference_type n) & noexcept(is_nothrow_addition_assignable_v<Iterator,
            difference_type>) requires is_random_access_iterator_v<Iterator> {
        this->iterator += -n;
        return *this;
    }
    constexpr reverse_iterator &operator-=(difference_type n) & noexcept(is_nothrow_addition_assignable_v<Iterator,
            difference_type>) requires is_random_access_iterator_v<Iterator> {
        this->iterator += n;
        return *this;
    }
    [[nodiscard]]
    constexpr reverse_iterator operator+(difference_type n) noexcept(is_nothrow_addition_assignable_v<Iterator,
            difference_type> and is_nothrow_copy_constructible_v<Iterator>)
            requires is_random_access_iterator_v<Iterator> {
        auto backup {*this};
        backup += n;
        return backup;
    }
    [[nodiscard]]
    constexpr reverse_iterator operator-(difference_type n) noexcept(is_nothrow_addition_assignable_v<Iterator,
            difference_type> and is_nothrow_copy_constructible_v<Iterator>)
            requires is_random_access_iterator_v<Iterator> {
        auto backup {*this};
        backup -= n;
        return backup;
    }
    [[nodiscard]]
    constexpr operator Iterator() noexcept {
        return this->iterator;
    }
    [[nodiscard]]
    constexpr operator Iterator() const noexcept {
        return this->iterator;
    }
    [[nodiscard]]
    explicit constexpr operator bool() const noexcept(is_nothrow_static_castable_v<Iterator, bool>) {
        return static_cast<bool>(this->iterator);
    }
public:
    [[nodiscard]]
    constexpr Iterator base() const noexcept {
        return this->iterator;
    }
};
template <typename Iterator>
[[nodiscard]]
inline constexpr auto operator==(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
        noexcept(is_nothrow_equal_to_comparable_v<Iterator>)  {
    return rhs.base() == lhs.base();
}
template <typename Iterator>
[[nodiscard]]
inline constexpr bool operator!=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
        noexcept(is_nothrow_not_equal_to_comparable_v<Iterator>) {
    return lhs.base() not_eq rhs.base();
}
template <typename Iterator>
[[nodiscard]]
inline constexpr auto operator<(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
        noexcept(is_nothrow_less_comparable_v<Iterator>) {
    return lhs.base() > rhs.base();
}
template <typename Iterator>
[[nodiscard]]
inline constexpr auto operator<=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
        noexcept(is_nothrow_less_equal_to_comparable_v<Iterator>) {
    return lhs.base() >= rhs.base();
}
template <typename Iterator>
[[nodiscard]]
inline constexpr auto operator>(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
        noexcept(is_nothrow_greater_comparable_v<Iterator>) {
    return lhs.base() < rhs.base();
}
template <typename Iterator>
[[nodiscard]]
inline constexpr auto operator>=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
        noexcept(is_nothrow_greater_equal_to_comparable_v<Iterator>) {
    return lhs.base() <= rhs.base();
}
template <typename Iterator>
[[nodiscard]]
inline constexpr auto operator-(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
        noexcept(is_nothrow_subtractable_v<Iterator>) {
    return rhs.base() - lhs.base();
}
__DATA_STRUCTURE_END(reverse iterator)

__DATA_STRUCTURE_START(move iterator)
template <IsInputIterator Iterator>
class move_iterator {
public:
    using iterator_type = Iterator;
    using size_type = typename iterator_traits<Iterator>::size_type;
    using difference_type = typename iterator_traits<Iterator>::difference_type;
    using value_type = typename iterator_traits<Iterator>::value_type;
    using iterator_category = typename iterator_traits<Iterator>::iterator_category;
private:
    Iterator iterator {};
public:
    constexpr move_iterator() = default;
    explicit constexpr move_iterator(Iterator iterator) noexcept(is_nothrow_copy_constructible_v<Iterator>) :
            iterator {iterator} {}
    constexpr move_iterator(const move_iterator &) = default;
    constexpr move_iterator(move_iterator &&) = default;
    constexpr ~move_iterator() noexcept = default;
public:
    constexpr move_iterator &operator=(const move_iterator &) = default;
    constexpr move_iterator &operator=(move_iterator &&) = default;
public:
    [[nodiscard]]
    constexpr decltype(auto) operator*() const noexcept(is_nothrow_dereferenceable_v<Iterator>) {
        return ds::move(*this->iterator);
    }
    [[nodiscard]]
    constexpr decltype(auto) operator[](difference_type n) noexcept(is_nothrow_indexable_v<Iterator, difference_type>)
            requires is_random_access_iterator_v<Iterator> {
        return ds::move(this->iterator[n]);
    }
    constexpr move_iterator &operator++() & noexcept(is_nothrow_prefix_increasable_v<Iterator>) {
        ++this->iterator;
        return *this;
    }
    constexpr move_iterator operator++(int) & noexcept(is_nothrow_prefix_increasable_v<Iterator>) {
        auto backup {*this};
        ++this->iterator;
        return backup;
    }
    constexpr move_iterator &operator--() & noexcept(is_nothrow_prefix_decreasable_v<Iterator>)
            requires is_bidirectional_iterator_v<Iterator> {
        --this->iterator;
        return *this;
    }
    constexpr move_iterator operator--(int) & noexcept(is_nothrow_prefix_decreasable_v<Iterator>)
            requires is_bidirectional_iterator_v<Iterator> {
        auto backup {*this};
        --this->iterator;
        return backup;
    }
    constexpr move_iterator &operator+=(difference_type n) & noexcept(is_nothrow_addition_assignable_v<Iterator,
            difference_type>) requires is_random_access_iterator_v<Iterator> {
        this->iterator += n;
        return *this;
    }
    constexpr move_iterator &operator-=(difference_type n) & noexcept(is_nothrow_addition_assignable_v<Iterator,
            difference_type>) requires is_random_access_iterator_v<Iterator> {
        this->iterator += -n;
        return *this;
    }
    constexpr move_iterator operator+(difference_type n) & noexcept(is_nothrow_addition_assignable_v<Iterator,
            difference_type> and is_nothrow_copy_constructible_v<Iterator>)
            requires is_random_access_iterator_v<Iterator> {
        auto backup {*this};
        backup += n;
        return backup;
    }
    constexpr move_iterator operator-(difference_type n) & noexcept(is_nothrow_addition_assignable_v<Iterator,
            difference_type> and is_nothrow_copy_constructible_v<Iterator>)
            requires is_random_access_iterator_v<Iterator> {
        auto backup {*this};
        backup += -n;
        return backup;
    }
    [[nodiscard]]
    constexpr operator Iterator() const noexcept {
        return this->iterator;
    }
    [[nodiscard]]
    explicit constexpr operator bool() const noexcept(is_nothrow_static_castable_v<Iterator, bool>)
            requires is_static_castable_v<Iterator, bool> {
        return static_cast<bool>(this->iterator);
    }
public:
    [[nodiscard]]
    constexpr Iterator base() const noexcept {
        return this->iterator;
    }
};
template <typename Iterator>
[[nodiscard]]
inline constexpr auto operator==(const move_iterator<Iterator> &lhs, const move_iterator<Iterator> &rhs)
        noexcept(is_nothrow_equal_to_comparable_v<Iterator>)  {
    return rhs.base() == lhs.base();
}
template <typename Iterator>
[[nodiscard]]
inline constexpr bool operator!=(const move_iterator<Iterator> &lhs, const move_iterator<Iterator> &rhs)
        noexcept(is_nothrow_not_equal_to_comparable_v<Iterator>) {
    return lhs.base() not_eq rhs.base();
}
template <typename Iterator>
[[nodiscard]]
inline constexpr auto operator<(const move_iterator<Iterator> &lhs, const move_iterator<Iterator> &rhs)
        noexcept(is_nothrow_less_comparable_v<Iterator>) {
    return lhs.base() < rhs.base();
}
template <typename Iterator>
[[nodiscard]]
inline constexpr auto operator<=(const move_iterator<Iterator> &lhs, const move_iterator<Iterator> &rhs)
        noexcept(is_nothrow_less_equal_to_comparable_v<Iterator>) {
    return lhs.base() <= rhs.base();
}
template <typename Iterator>
[[nodiscard]]
inline constexpr auto operator>(const move_iterator<Iterator> &lhs, const move_iterator<Iterator> &rhs)
        noexcept(is_nothrow_greater_comparable_v<Iterator>) {
    return lhs.base() > rhs.base();
}
template <typename Iterator>
[[nodiscard]]
inline constexpr auto operator>=(const move_iterator<Iterator> &lhs, const move_iterator<Iterator> &rhs)
        noexcept(is_nothrow_greater_equal_to_comparable_v<Iterator>) {
    return lhs.base() >= rhs.base();
}
template <typename Iterator>
[[nodiscard]]
inline constexpr auto operator-(const move_iterator<Iterator> &lhs, const move_iterator<Iterator> &rhs)
        noexcept(is_nothrow_greater_equal_to_comparable_v<Iterator>) {
    return lhs.base() - rhs.base();
}
__DATA_STRUCTURE_END(move iterator)

__DATA_STRUCTURE_START(inner tools for data structure)

__DATA_STRUCTURE_START(container forward declaration)
template <typename, typename> class forward_list;
template <typename, typename, typename> class list;
__DATA_STRUCTURE_END(container forward declaration)

namespace __data_structure_auxiliary {
__DATA_STRUCTURE_START(forward list node)
template <typename ValueNode>
struct forward_list_base_node {
    forward_list_base_node *next;
    constexpr auto &value() noexcept {
        return static_cast<ValueNode *>(this)->value;
    }
    constexpr ValueNode *node() noexcept {
        return static_cast<ValueNode *>(this);
    }
};
template <typename T>
struct forward_list_node : forward_list_base_node<forward_list_node<T>> {
    T value;
};
__DATA_STRUCTURE_END(forward list node)

__DATA_STRUCTURE_START(data structure special iterator, forward list iterator)
template <typename T, bool IsConst = false>
class forward_list_iterator {
    friend class forward_list_iterator<T, false>;
    template <typename ValueType, bool IsConstLHS, bool IsConstRHS>
    friend constexpr bool operator==(const forward_list_iterator<ValueType, IsConstLHS> &,
            const forward_list_iterator<ValueType, IsConstRHS> &) noexcept;
    template <typename, typename> friend class forward_list;
private:
    using node_type = forward_list_base_node<forward_list_node<T>> *;
public:
    using iterator_type = forward_list_iterator;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using value_type = T;
    using iterator_category = forward_iterator_tag;
private:
    node_type node {};
public:
    constexpr forward_list_iterator() noexcept = default;
    explicit constexpr forward_list_iterator(forward_list_base_node<forward_list_node<T>> *node) noexcept :
            node {node} {}
    template <typename U> requires is_same_v<U, forward_list_iterator<T, false>>
    constexpr forward_list_iterator(enable_if_t<IsConst, const U &> non_const_iterator) :
            node {non_const_iterator.node} {}
    constexpr forward_list_iterator(const forward_list_iterator &) noexcept = default;
    constexpr forward_list_iterator(forward_list_iterator &&) noexcept = default;
    constexpr ~forward_list_iterator() noexcept = default;
public:
    constexpr forward_list_iterator &operator=(const forward_list_iterator &) noexcept = default;
    constexpr forward_list_iterator &operator=(forward_list_iterator &&) noexcept = default;
    constexpr conditional_t<IsConst, const T &, T &> operator*() noexcept {
        return this->node->value();
    }
    constexpr const T &operator*() const noexcept {
        return this->node->value();
    }
    constexpr conditional_t<IsConst, const T *, T *> operator->() noexcept {
        return ds::address_of(**this);
    }
    constexpr const T *operator->() const noexcept {
        return ds::address_of(**this);
    }
    constexpr forward_list_iterator &operator++() & noexcept {
        this->node = this->node->next;
        return *this;
    }
    constexpr forward_list_iterator operator++(int) & noexcept {
        auto backup {*this};
        ++*this;
        return backup;
    }
    explicit operator bool() const noexcept {
        return this->node;
    }
    operator forward_list_iterator<T, true>() const noexcept {
        return forward_list_iterator<T, true>(this->node);
    }
};
template <typename T, bool IsConstLHS, bool IsConstRHS>
inline constexpr bool operator==(const forward_list_iterator<T, IsConstLHS> &lhs,
        const forward_list_iterator<T, IsConstRHS> &rhs) noexcept {
    return lhs.node == rhs.node;
}
template <typename T, bool IsConstLHS, bool IsConstRHS>
inline constexpr bool operator!=(const forward_list_iterator<T, IsConstLHS> &lhs,
        const forward_list_iterator<T, IsConstRHS> &rhs) noexcept {
    return not(lhs == rhs);
}
__DATA_STRUCTURE_END(data structure special iterator, forward list iterator)

__DATA_STRUCTURE_START(list node)
template <typename ValueNode>
struct list_base_node {
    list_base_node *next;
    list_base_node *previous;
    constexpr auto &value() noexcept {
        return static_cast<ValueNode *>(this)->value;
    }
    constexpr ValueNode *node() noexcept {
        return static_cast<ValueNode *>(this);
    }
};
template <typename T>
struct list_node : list_base_node<list_node<T>> {
    T value;
};
__DATA_STRUCTURE_END(list node)

__DATA_STRUCTURE_START(data structure special iterator, list iterator)
template <typename T, bool IsConst = false>
class list_iterator {
    friend class list_iterator<T, false>;
    template <typename ValueType, bool IsConstLHS, bool IsConstRHS>
    friend constexpr bool operator==(const list_iterator<ValueType, IsConstLHS> &,
            const list_iterator<ValueType, IsConstRHS> &) noexcept;
    template <typename, typename> friend class list;
private:
    using node_type = list_base_node<list_node<T>> *;
public:
    using iterator_type = list_iterator;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using value_type = T;
    using iterator_category = bidirectional_iterator_tag;
private:
    node_type node {};
public:
    constexpr list_iterator() noexcept = default;
    explicit constexpr list_iterator(list_base_node<list_node<T>> *node) noexcept : node {node} {}
    template <typename U> requires is_same_v<U, list_iterator<T, false>>
    constexpr list_iterator(enable_if_t<IsConst, const U &> non_const_iterator) : node {non_const_iterator.node} {}
    constexpr list_iterator(const list_iterator &) noexcept = default;
    constexpr list_iterator(list_iterator &&) noexcept = default;
    constexpr ~list_iterator() noexcept = default;
public:
    constexpr list_iterator &operator=(const list_iterator &) noexcept = default;
    constexpr list_iterator &operator=(list_iterator &&) noexcept = default;
    constexpr conditional_t<IsConst, const T &, T &> operator*() noexcept {
        return this->node->value();
    }
    constexpr const T &operator*() const noexcept {
        return this->node->value();
    }
    constexpr conditional_t<IsConst, const T *, T *> operator->() noexcept {
        return ds::address_of(**this);
    }
    constexpr const T *operator->() const noexcept {
        return ds::address_of(**this);
    }
    constexpr list_iterator &operator++() & noexcept {
        this->node = this->node->next;
        return *this;
    }
    constexpr list_iterator operator++(int) & noexcept {
        auto backup {*this};
        ++*this;
        return backup;
    }
    constexpr list_iterator &operator--() & noexcept {
        this->node = this->node->previous;
        return *this;
    }
    constexpr list_iterator operator--(int) & noexcept {
        auto backup {*this};
        --*this;
        return backup;
    }
    explicit operator bool() const noexcept {
        return this->node;
    }
    operator list_iterator<T, true>() const noexcept {
        return list_iterator<T, true>(this->node);
    }
};
template <typename T, bool IsConstLHS, bool IsConstRHS>
inline constexpr bool operator==(const list_iterator<T, IsConstLHS> &lhs,
        const list_iterator<T, IsConstRHS> &rhs) noexcept {
    return lhs.node == rhs.node;
}
template <typename T, bool IsConstLHS, bool IsConstRHS>
inline constexpr bool operator!=(const list_iterator<T, IsConstLHS> &lhs,
        const list_iterator<T, IsConstRHS> &rhs) noexcept {
    return not(lhs == rhs);
}
__DATA_STRUCTURE_END(data structure special iterator, list iterator)

}       // namespace data_structure::__data_structure_auxiliary
__DATA_STRUCTURE_END(inner tools for data structure)

}       // namespace data_structure

#endif      //DATA_STRUCTURE_ITERATOR_HPP