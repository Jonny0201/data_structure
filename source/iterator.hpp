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
    using value_type = typename Iterator::value_type;
    using iterator_category = typename Iterator::iterator_category;
};
template <typename T>
struct iterator_traits<T *> {
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using value_type = T;
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