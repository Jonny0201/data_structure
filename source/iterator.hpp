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

#include "type_traits.hpp"

namespace data_structure {

__DATA_STRUCTURE_START(iterator tag)
struct iterator_tag {};
struct output_iterator_tag : iterator_tag {};
struct input_iterator_tag : iterator_tag {};
struct forward_iterator_tag : input_iterator_tag {};
struct bidirectional_iterator_tag : forward_iterator_tag {};
struct random_access_iterator_tag : bidirectional_iterator_tag {};
struct contiguous_iterator_tag : random_access_iterator_tag {};
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(iterator traits)
template <typename Iterator>
struct iterator_traits {
    using size_type = typename Iterator::size_type;
    using difference_type = typename Iterator::difference_type;
    using iterator_category = typename Iterator::iterator_category;
};
template <typename T>
struct iterator_traits<T *> {
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using iterator_category = contiguous_iterator_tag;
};

template <typename T>
concept HasIteratorCategory = requires {
    typename iterator_traits<T>::iterator_category;
};
template <typename Iterator>
struct has_iterator_category : bool_constant<HasIteratorCategory<Iterator>> {};
template <typename Iterator>
inline constexpr auto has_iterator_category_v {HasIteratorCategory<Iterator>};

template <typename Iterator>
concept IsIterator = requires {
    is_base_of_v<iterator_tag, typename iterator_traits<Iterator>::iterator_category>;
};
template <typename Iterator>
struct is_iterator : bool_constant<IsIterator<Iterator>> {};
template <typename Iterator>
inline constexpr auto is_iterator_v {IsIterator<Iterator>};

template <typename Iterator>
concept IsInputIterator = requires {
    is_base_of_v<input_iterator_tag, typename iterator_traits<Iterator>::iterator_category>;
};
template <typename Iterator>
struct is_input_iterator : bool_constant<IsInputIterator<Iterator>> {};
template <typename Iterator>
inline constexpr auto is_input_iterator_v {IsInputIterator<Iterator>};

template <typename Iterator>
concept IsOutputIterator = requires {
    is_base_of_v<output_iterator_tag, typename iterator_traits<Iterator>::iterator_category>;
};
template <typename Iterator>
struct is_output_iterator : bool_constant<IsOutputIterator<Iterator>> {};
template <typename Iterator>
inline constexpr auto is_output_iterator_v {IsOutputIterator<Iterator>};

template <typename Iterator>
concept IsForwardIterator = requires {
    is_base_of_v<forward_iterator_tag, typename iterator_traits<Iterator>::iterator_category>;
};
template <typename Iterator>
struct is_forward_iterator : bool_constant<IsForwardIterator<Iterator>> {};
template <typename Iterator>
inline constexpr auto is_forward_iterator_v {IsForwardIterator<Iterator>};

template <typename Iterator>
concept IsBidirectionalIterator = requires {
    is_base_of_v<bidirectional_iterator_tag, typename iterator_traits<Iterator>::iterator_category>;
};
template <typename Iterator>
struct is_bidirectional_iterator : bool_constant<IsBidirectionalIterator<Iterator>> {};
template <typename Iterator>
inline constexpr auto is_bidirectional_iterator_v {IsBidirectionalIterator<Iterator>};

template <typename Iterator>
concept IsRandomAccessIterator = requires {
    is_base_of_v<random_access_iterator_tag, typename iterator_traits<Iterator>::iterator_category>;
};
template <typename Iterator>
struct is_random_access_iterator : bool_constant<IsRandomAccessIterator<Iterator>> {};
template <typename Iterator>
inline constexpr auto is_random_access_iterator_v {IsRandomAccessIterator<Iterator>};

template <typename Iterator>
concept IsContiguousIterator = requires {
    is_same_v<contiguous_iterator_tag, typename iterator_traits<Iterator>::iterator_category>;
};
template <typename Iterator>
struct is_contiguous_iterator : bool_constant<IsContiguousIterator<Iterator>> {};
template <typename Iterator>
inline constexpr auto is_contiguous_iterator_v {IsContiguousIterator<Iterator>};
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(iterator functions)
template <IsRandomAccessIterator RandomAccessIterator>
inline typename iterator_traits<RandomAccessIterator>::difference_type distance(RandomAccessIterator begin,
        RandomAccessIterator end) noexcept(is_nothrow_subtractable_v<RandomAccessIterator>) {
    return end - begin;
}
template <typename InputIterator>
inline typename iterator_traits<InputIterator>::difference_type distance(InputIterator begin, InputIterator end)
        noexcept(is_nothrow_prefix_increasable_v<InputIterator> and
                is_nothrow_constructible_v<typename iterator_traits<InputIterator>::difference_type, int> and
                is_nothrow_prefix_increasable_v<typename iterator_traits<InputIterator>::difference_type>) {
    typename iterator_traits<InputIterator>::difference_type difference {0};
    while(begin not_eq end) {
        ++begin;
        ++difference;
    }
    return difference;
}
inline ptrdiff_t distance(void *begin, void *end) noexcept {
    return static_cast<char *>(end) - static_cast<char *>(begin);
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(move_iterator)
template <IsInputIterator Iterator>
class move_iterator {
public:
    using iterator_type = Iterator;
    using size_type = typename iterator_traits<Iterator>::size_type;
    using difference_type = typename iterator_traits<Iterator>::difference_type;
    using value_type = typename iterator_traits<Iterator>::value_type;
    using iterator_category = typename iterator_traits<Iterator>::iterator_category;
private:
    Iterator iterator;
public:
    constexpr move_iterator() = default;
    explicit constexpr move_iterator(Iterator iterator) noexcept(is_nothrow_copy_constructible_v<Iterator>) :
            iterator {iterator} {}
    template <typename IteratorRHS>
    explicit constexpr move_iterator(const move_iterator<IteratorRHS> &rhs)
            noexcept(is_nothrow_constructible_v<Iterator, IteratorRHS>) : move_iterator(rhs.base()) {}
    constexpr move_iterator(const move_iterator &) = default;
    constexpr move_iterator(move_iterator &&) = default;
    constexpr ~move_iterator() noexcept = default;
public:
    constexpr move_iterator &operator=(const move_iterator &) = default;
    constexpr move_iterator &operator=(move_iterator &&) = default;
    template <typename IteratorRHS>
    constexpr move_iterator &operator=(const move_iterator<IteratorRHS> &rhs)
            noexcept(is_nothrow_assignable_v<Iterator, IteratorRHS>) {
        this->iterator = rhs.base();
        return *this;
    }
public:
    decltype(auto) operator*() const noexcept(is_nothrow_dereferenceable_v<Iterator>) {
        return move(*this->iterator);
    }
    decltype(auto) operator[](difference_type n) noexcept(is_nothrow_indexable_v<Iterator, difference_type>)
            requires is_random_access_iterator_v<Iterator> {
        return move(this->iterator[n]);
    }
    move_iterator &operator++() & noexcept(is_nothrow_prefix_increasable_v<Iterator>) {
        ++this->iterator;
        return *this;
    }
    move_iterator operator++(int) & noexcept(is_nothrow_prefix_increasable_v<Iterator>) {
        auto backup {*this};
        ++this->iterator;
        return backup;
    }
    move_iterator &operator--() & noexcept(is_nothrow_prefix_decreasable_v<Iterator>)
            requires is_bidirectional_iterator_v<Iterator> {
        --this->iterator;
        return *this;
    }
    move_iterator operator--(int) & noexcept(is_nothrow_prefix_decreasable_v<Iterator>)
            requires is_bidirectional_iterator_v<Iterator> {
        auto backup {*this};
        --this->iterator;
        return backup;
    }
    move_iterator &operator+=(difference_type n) & noexcept(is_nothrow_addition_assignable_v<iterator_type,
            difference_type>) requires is_random_access_iterator_v<Iterator> {
        this->iterator += n;
        return *this;
    }
    move_iterator &operator-=(difference_type n) & noexcept(is_nothrow_addition_assignable_v<iterator_type,
            difference_type>) requires is_random_access_iterator_v<Iterator> {
        this->iterator += -n;
        return *this;
    }
    move_iterator operator+(difference_type n) & noexcept(is_nothrow_addition_assignable_v<iterator_type,
            difference_type>) requires is_random_access_iterator_v<Iterator> {
        auto backup {*this};
        backup += n;
        return backup;
    }
    move_iterator operator-(difference_type n) & noexcept(is_nothrow_addition_assignable_v<iterator_type,
            difference_type>) requires is_random_access_iterator_v<Iterator> {
        auto backup {*this};
        backup += -n;
        return backup;
    }
    operator Iterator() const noexcept {
        return this->iterator;
    }
    explicit operator bool() const noexcept(is_nothrow_static_castable_v<Iterator, bool>)
            requires is_static_castable_v<Iterator, bool> {
        return static_cast<bool>(this->iterator);
    }
public:
    Iterator base() const noexcept {
        return this->iterator;
    }
};
template <typename IteratorLHS, typename IteratorRHS = IteratorLHS>
auto operator-(const move_iterator<IteratorLHS> &lhs, const move_iterator<IteratorRHS> &rhs)
        noexcept(is_nothrow_subtractable_v<IteratorLHS, IteratorRHS>) {
    return rhs.base() - lhs.base();
}
template <typename IteratorLHS, typename IteratorRHS = IteratorLHS>
auto operator==(const move_iterator<IteratorLHS> &lhs, const move_iterator<IteratorRHS> &rhs)
        noexcept(is_nothrow_equal_to_comparable_v<IteratorLHS, IteratorRHS>) {
    return rhs.base() == lhs.base();
}
template <typename IteratorLHS, typename IteratorRHS = IteratorLHS>
auto operator!=(const move_iterator<IteratorLHS> &lhs, const move_iterator<IteratorRHS> &rhs)
        noexcept(is_nothrow_not_equal_to_comparable_v<IteratorLHS, IteratorRHS>) {
    return lhs.base() not_eq rhs.base();
}
template <typename IteratorLHS, typename IteratorRHS = IteratorLHS>
auto operator<(const move_iterator<IteratorLHS> &lhs, const move_iterator<IteratorRHS> &rhs)
        noexcept(is_nothrow_less_comparable_v<IteratorLHS, IteratorRHS>) {
    return lhs.base() < rhs.base();
}
template <typename IteratorLHS, typename IteratorRHS = IteratorLHS>
auto operator<=(const move_iterator<IteratorLHS> &lhs, const move_iterator<IteratorRHS> &rhs)
        noexcept(is_nothrow_less_equal_to_comparable_v<IteratorLHS, IteratorRHS>) {
    return lhs.base() <= rhs.base();
}
template <typename IteratorLHS, typename IteratorRHS = IteratorLHS>
auto operator>(const move_iterator<IteratorLHS> &lhs, const move_iterator<IteratorRHS> &rhs)
        noexcept(is_nothrow_greater_comparable_v<IteratorLHS, IteratorRHS>) {
    return lhs.base() > rhs.base();
}
template <typename IteratorLHS, typename IteratorRHS = IteratorLHS>
auto operator>=(const move_iterator<IteratorLHS> &lhs, const move_iterator<IteratorRHS> &rhs)
        noexcept(is_nothrow_greater_equal_to_comparable_v<IteratorLHS, IteratorRHS>) {
    return lhs.base() >= rhs.base();
}
__DATA_STRUCTURE_END

}

#endif //DATA_STRUCTURE_ITERATOR_HPP