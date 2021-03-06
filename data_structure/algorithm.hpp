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

#ifndef DATA_STRUCTURE_ALGORITHM_HPP
#define DATA_STRUCTURE_ALGORITHM_HPP

#include "type_traits.hpp"
#include "iterator.hpp"
#include "heap.hpp"

__DATA_STRUCTURE_START(iterator)
namespace data_structure {
    template <typename Iterator>
    inline iterator_traits_t(Iterator, difference_type)
    distance(enable_if_t<not is_random_access_iterator_v<Iterator>, Iterator> begin, Iterator end) {
        iterator_traits_t(Iterator, difference_type) difference {0};
        while(begin not_eq end) {
            ++begin, static_cast<void>(++difference);
        }
        return difference;
    }
    template <typename Iterator>
    inline iterator_traits_t(Iterator, difference_type)
    distance(enable_if_t<is_random_access_iterator_v<Iterator>, Iterator> begin, Iterator end)
            noexcept(has_nothrow_minus_operator_v<Iterator>) {
        return end - begin;
    }
    inline ptrdiff_t distance(void *begin, void *end) noexcept {
        return reinterpret_cast<char *>(end) - reinterpret_cast<char *>(begin);
    }
    template <typename Iterator>
    inline enable_if_t<not is_random_access_iterator_v<Iterator>, Iterator>
    advance(Iterator begin, iterator_traits_t(Iterator, difference_type) step = 1) {
        if(step > 0) {
            while(step > 0) {
                ++begin, static_cast<void>(--step);
            }
        }else if(step < 0) {
            while(step < 0) {
                --begin, static_cast<void>(++step);
            }
        }
        return begin;
    }
    template <typename RandomAccessIterator>
    inline enable_if_t<is_random_access_iterator_v<RandomAccessIterator>, RandomAccessIterator>
    advance(RandomAccessIterator begin, iterator_traits_t(RandomAccessIterator, difference_type) step = 1)
            noexcept(has_nothrow_plus_operator_v<iterator_traits_t(RandomAccessIterator, difference_type)>) {
        return begin + step;
    }
    inline void *advance(void *ptr, ptrdiff_t step = 1) noexcept {
        return reinterpret_cast<char *>(ptr) + step;
    }
    template <typename Iterator>
    inline Iterator next(Iterator it) noexcept(has_nothrow_pre_increment_operator_v<Iterator>) {
        return ++it;
    }
    inline void *next(void *ptr) noexcept {
        return reinterpret_cast<char *>(ptr) + 1;
    }
    template <typename Iterator>
    inline Iterator previous(Iterator it) noexcept(has_nothrow_pre_decrement_operator_v<Iterator>) {
        return --it;
    }
    inline void *previous(void *ptr) noexcept {
        return reinterpret_cast<char *>(ptr) - 1;
    }
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(numeric)
namespace data_structure {
    template <typename T>
    inline T max(const T &a, const T &b) noexcept(has_nothrow_less_operator_v<T>) {
        return a < b ? b : a;
    }
    template <typename T>
    inline T min(const T &a, const T &b) noexcept(has_nothrow_less_operator_v<T>) {
        return a < b ? a : b;
    }
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(copy)
namespace data_structure {
    template <typename OutputIterator, typename InputIterator>
    OutputIterator copy(InputIterator begin, InputIterator end, OutputIterator result) {
        for(; begin not_eq end; ++begin, static_cast<void>(++result)) {
            *result = *begin;
        }
        return result;
    }
    template <bool Overlapping = false, typename T, typename U>
    inline enable_if_t<is_trivially_copy_assignable_v<U> and is_same_v<remove_reference_t<T>, U>, U *>
    copy(T *begin, T *end, U *result) noexcept {
        const auto size {static_cast<size_t>(end - begin)};
        if(size > 0) {
            if constexpr(Overlapping) {
                ds::memory_move(result, begin, size * sizeof(U));
            }else {
                ds::memory_copy(result, begin, size * sizeof(U));
            }
        }
        return result + size;
    }
    template <bool Overlapping = false, typename T, typename U>
    inline enable_if_t<is_trivially_copy_assignable_v<U> and is_same_v<remove_reference_t<T>, U>,
            wrap_iterator<U *>>
    copy(wrap_iterator<T *> begin, wrap_iterator<T *> end, wrap_iterator<U *> result) noexcept {
        return wrap_iterator<U *>(copy<Overlapping>(begin.base(), end.base(), result.base()));
    }
    template <bool Exception = false, typename ForwardIterator, typename InputIterator>
    ForwardIterator uninitialized_copy(InputIterator begin, InputIterator end, ForwardIterator result) {
        using value_type = iterator_traits_t(decay_t<ForwardIterator>, value_type);
        auto backup {result};
        if constexpr(Exception) {
            try {
                for(; begin not_eq end; ++result) {
                    ::new (ds::address_of(*result)) value_type(*begin++);
                }
            }catch(...) {
                if constexpr(not is_trivially_destructible_v<value_type>) {
                    for(; backup not_eq result; ++backup) {
                        backup->~value_type();
                    }
                }
                throw;
            }
        }else {
            while(begin not_eq end) {
                ::new (ds::address_of(*result++)) value_type(*begin++);
            }
        }
        return result;
    }
    template <typename T, typename U>
    inline enable_if_t<is_trivially_copy_assignable_v<U> and is_same_v<remove_reference_t<T>, U>, U *>
    uninitialized_copy(T *begin, T *end, U *result) noexcept {
        return ds::copy(begin, end, result);
    }
    template <typename T, typename U>
    inline enable_if_t<is_trivially_copy_assignable_v<U> and is_same_v<remove_reference_t<T>, U>, U *>
    uninitialized_copy(wrap_iterator<T *> begin, wrap_iterator<T *> end, wrap_iterator<U *> result) noexcept {
        return ds::copy(begin, end, result);
    }
    template <typename T, typename ForwardIterator>
    void fill(enable_if_t<is_forward_iterator_v<ForwardIterator> and
            not is_random_access_iterator_v<ForwardIterator>, ForwardIterator> first,
            ForwardIterator last, const T &value) {
        while(first not_eq last) {
            *first++ = value;
        }
    }
    template <typename T, typename OutputIterator, typename SizeType> OutputIterator fill_n(OutputIterator, SizeType, const T &);
    template <typename T, typename RandomAccessIterator>
    inline void fill(enable_if_t<is_random_access_iterator_v<RandomAccessIterator>, RandomAccessIterator> first,
            RandomAccessIterator last, const T &value) {
        ds::fill_n(first, last - first, value);
    }
    template <typename T, typename OutputIterator, typename SizeType>
    OutputIterator fill_n(OutputIterator first, SizeType size, const T &value) {
        while(size > 0) {
            *first++ = value;
            --size;
        }
        return first;
    }
    template <bool Exception = false, typename ForwardIterator, typename T>
    void uninitialized_fill(ForwardIterator begin, ForwardIterator end, const T &value) {
        using value_type = iterator_traits_t(decay_t<ForwardIterator>, value_type);
        if constexpr(Exception) {
            auto backup {begin};
            try {
                for(; begin not_eq end; ++begin) {
                    ::new (ds::address_of(*begin)) value_type(value);
                }
            }catch(...) {
                while(backup not_eq begin) {
                    backup->~value_type();
                }
            }
        }else {
            while(begin not_eq end) {
                ::new (ds::address_of(*begin++)) value_type(value);
            }
        }
    }
    template <bool Exception = false, typename ForwardIterator, typename SizeType, typename T>
    ForwardIterator uninitialized_fill_n(ForwardIterator begin, SizeType size, const T &value) {
        using value_type = iterator_traits_t(decay_t<ForwardIterator>, value_type);
        if constexpr(Exception) {
            auto backup {begin};
            try {
                for(; size-- > 0; ++begin) {
                    ::new (ds::address_of(*begin)) value_type(value);
                }
            }catch(...) {
                while(backup not_eq begin) {
                    backup->~value_type();
                }
            }
        }else {
            while(size-- > 0) {
                ::new (ds::address_of(*begin++)) value_type(value);
            }
        }
        return begin;
    }
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(swap)
namespace data_structure {
    template <typename T>
    inline void swap(T &lhs, T &rhs) noexcept(is_nothrow_move_constructible<T>::value and
            is_nothrow_move_assignable<T>::value) {
        auto tmp {ds::move(lhs)};
        lhs = ds::move(rhs);
        rhs = ds::move(tmp);
    }
    template <typename ForwardIteratorLHS, typename ForwardIteratorRHS = ForwardIteratorLHS>
    ForwardIteratorRHS swap_ranges(ForwardIteratorLHS first_lhs, ForwardIteratorLHS last_lhs,
            ForwardIteratorRHS first_rhs)  {
        while(first_lhs not_eq last_lhs) {
            ds::swap(*first_lhs++, *first_rhs);
        }
        return first_rhs;
    }
    template <typename T, size_t N>
    inline void swap_ranges(T (&array_lhs)[N], T (&array_rhs)[N]) noexcept(is_nothrow_swappable<T>::value) {
        ds::swap_ranges(array_lhs, array_lhs + N, array_rhs);
    }
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(search)
namespace data_structure {
    template <typename Equal = equal_to<>, typename Less = less<>, typename ForwardIterator, typename T>
    ForwardIterator binary_search(ForwardIterator begin, ForwardIterator end,
            const T &value, Equal equal = {}, Less less = {}) {
        auto size {ds::distance(begin, end)};
        const auto backup {end};
        while(size > 0) {
            auto middle {ds::advance(begin, size /= 2)};
            if(equal(*middle, value)) {
                return middle;
            }else if(less(*middle, value)) {
                begin = ++middle;
            }else {
                end = middle;
            }
        }
        return backup;
    }
    template <typename Compare = less<>, typename ForwardIterator, typename T>
    ForwardIterator lower_bound(ForwardIterator begin, ForwardIterator end, const T &value, Compare cmp = {}) {
        auto size {ds::distance(begin, end)};
        while(size > 0) {
            auto step {size / 2};
            auto middle {ds::advance(begin, step)};
            if(cmp(*middle, value)) {
                begin = ++middle;
                size -= ++step;
            }else {
                size = step;
            }
        }
        return begin;
    }
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(move)
namespace data_structure {
    template <typename InputIterator, typename OutputIterator>
    OutputIterator move(InputIterator begin, InputIterator end, OutputIterator first) {
        while(begin not_eq end) {
            *first++ = ds::move(*begin++);
        }
        return first;
    }
    template <typename BidirectionalIterator, typename BidirectionalIteratorReturningType>
    BidirectionalIteratorReturningType move_backward(BidirectionalIterator begin, BidirectionalIterator end,
            BidirectionalIteratorReturningType last) {
        while(begin not_eq end) {
            *(--last) = ds::move(*(--end));
        }
        return last;
    }
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(rotate)
namespace data_structure {
    namespace __data_structure_auxiliary {
        template <typename ForwardIterator>
        inline ForwardIterator rotate_left(ForwardIterator begin, ForwardIterator end) {
            iterator_traits_t(ForwardIterator, value_type) tmp {ds::move(*begin)};
            auto result {ds::move(ds::next(begin), end, begin)};
            *result = ds::move(tmp);
            return result;
        }
        template <typename BidirectionalIterator>
        inline BidirectionalIterator rotate_right(BidirectionalIterator begin, BidirectionalIterator end) {
            auto before_end {ds::previous(end)};
            iterator_traits_t(BidirectionalIterator, value_type) tmp {ds::move(*before_end)};
            auto result {ds::move_backward(begin, before_end, end)};
            *result = ds::move(*tmp);
            return result;
        }
        template <typename ForwardIterator>
        ForwardIterator rotate_forward(ForwardIterator begin, ForwardIterator middle, ForwardIterator end) {
            for(auto i {middle};;) {
                ds::swap(*begin++, *i++);
                if(i == end) {
                    break;
                }
                if(begin == middle) {
                    middle = i;
                }
            }
            auto result {begin};
            if(begin not_eq middle) {
                for(auto i {middle};;) {
                    ds::swap(*begin++, *i++);
                    if(i == end) {
                        if(begin == middle) {
                            break;
                        }
                        i = middle;
                    }else if(begin == middle) {
                        middle = i;
                    }
                }
            }
            return result;
        }
        template <typename Integral>
        inline Integral gcd(Integral x, Integral y) {
            do {
                auto t {x % y};
                x = y;
                y = t;
            }while(y);
            return x;
        }
        template <typename RandomAccessIterator>
        RandomAccessIterator rotate_gcd(RandomAccessIterator begin,
                RandomAccessIterator middle, RandomAccessIterator end) {
            const auto left {ds::distance(begin, middle)}, right {ds::distance(middle, end)};
            if(left == right) {
                ds::swap_ranges(begin, middle, end);
                return middle;
            }
            auto gcd {ds::__dsa::gcd(left, right)};
            for(auto i {begin + gcd}; i not_eq begin;) {
                auto tmp {ds::move(*--i)};
                auto p1 {i}, p2 {p1 + left};
                do {
                    *p1 = ds::move(*p2);
                    p1 = p2;
                    const auto distance {ds::distance(p2, end)};
                    if (left < distance) {
                        p2 += left;
                    }else {
                        p2 = begin + (left - distance);
                    }
                }while(p2 != i);
                *p1 = ds::move(tmp);
            }
            return begin + right;
        }
        template <typename ForwardIterator>
        inline ForwardIterator rotate_auxiliary(ForwardIterator begin, ForwardIterator middle,
                enable_if_t<is_forward_iterator_v<ForwardIterator> and
                        not is_bidirectional_iterator_v<ForwardIterator>, ForwardIterator> end) {
            if constexpr(is_trivially_move_assignable_v<iterator_traits_t(ForwardIterator, value_type)>) {
                if(ds::next(begin) == middle) {
                    return ds::__dsa::rotate_left(begin, end);
                }
            }
            return ds::__dsa::rotate_forward(begin, middle, end);
        }
        template <typename BidirectionalIterator>
        inline BidirectionalIterator rotate_auxiliary(BidirectionalIterator begin, BidirectionalIterator middle,
                enable_if_t<is_bidirectional_iterator_v<BidirectionalIterator> and
                        not is_random_access_iterator_v<BidirectionalIterator>, BidirectionalIterator> end) {
            if constexpr(is_trivially_move_assignable_v<iterator_traits_t(BidirectionalIterator, value_type)>) {
                if(ds::next(begin) == middle) {
                    return ds::__dsa::rotate_left(begin, end);
                }
                if (ds::next(middle) == end) {
                    return ds::__dsa::rotate_right(begin, end);
                }
            }
            return ds::__dsa::rotate_forward(begin, middle, end);
        }
        template <typename RandomAccessIterator>
        inline RandomAccessIterator rotate_auxiliary(RandomAccessIterator begin, RandomAccessIterator middle,
                enable_if_t<is_random_access_iterator_v<RandomAccessIterator>, RandomAccessIterator> end) {
            if constexpr(is_trivially_move_assignable_v<iterator_traits_t(RandomAccessIterator, value_type)>)
            {
                if (ds::next(begin) == middle) {
                    return ds::__dsa::rotate_left(begin, end);
                }else if(ds::next(middle) == end) {
                    return ds::__dsa::rotate_right(begin, end);
                }
                return ds::__dsa::rotate_gcd(begin, middle, end);
            }
            return ds::__dsa::rotate_forward(begin, middle, end);
        }
    }
    template <typename ForwardIterator>
    ForwardIterator rotate(ForwardIterator begin, ForwardIterator middle, ForwardIterator end) {
        if(begin == middle) {
            return end;
        }else if(middle == end) {
            return begin;
        }
        return ds::__dsa::rotate_auxiliary(begin, middle, end);
    }
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(sort)
namespace data_structure {
    namespace __data_structure_auxiliary {
        struct quick_sort_selector {
            constexpr void operator()(dynamic, dynamic, dynamic) const noexcept {}
        };
        template <typename Compare, typename Selector, typename RandomAccessIterator>
        void quick_sort_auxiliary(RandomAccessIterator begin, RandomAccessIterator end,
                iterator_traits_t(RandomAccessIterator, difference_type) left,
                iterator_traits_t(RandomAccessIterator, difference_type) right,
                Compare &compare, Selector &selector) {
            if(left >= right) {
                return;
            }
            auto left_cursor {left}, right_cursor {right};
            selector(begin, end, compare);
            auto pivot {ds::move(begin[right])};
            auto move_flag {true};
            while(true) {
                if(move_flag) {
                    while(compare(begin[left_cursor], pivot) and left_cursor < right_cursor) {
                        ++left_cursor;
                    }
                    if(left_cursor < right_cursor) {
                        begin[right_cursor--] = ds::move(begin[left_cursor]);
                        move_flag = false;
                        continue;
                    }
                }else {
                    while(compare(pivot, begin[right_cursor]) and left_cursor < right_cursor) {
                        --right_cursor;
                    }
                    if(left_cursor < right_cursor) {
                        begin[left_cursor++] = ds::move(begin[right_cursor]);
                        move_flag = true;
                        continue;
                    }
                }
                begin[left_cursor] = ds::move(pivot);
                quick_sort_auxiliary(begin, end, left, left_cursor - 1, compare, selector);
                quick_sort_auxiliary(begin, end, right_cursor + 1, right, compare, selector);
                return;
            }
        }
    }
    template <typename Compare = less<>, typename Selector = __dsa::quick_sort_selector,
            typename RandomAccessIterator>
    inline void quick_sort(RandomAccessIterator begin, RandomAccessIterator end,
            Compare compare = {}, Selector selector = {}) {
        auto size {ds::distance(begin, end)};
        if(size <= 1) {
            return;
        }
        __dsa::quick_sort_auxiliary<add_lvalue_reference_t<Compare>, add_lvalue_reference_t<Selector>>(
                begin, end, 0, size - 1, compare, selector);
    }

    template <typename Compare = less<>, typename ForwardIterator>
    void merge_sort(ForwardIterator begin, ForwardIterator end, Compare cmp = {}) {
        const auto size {ds::distance(begin, end)};
        switch(size) {
            case 2:
                if(auto next {ds::next(begin)}; not cmp(*begin, *next)) {
                    ds::swap(*begin, *next);
                }
                [[fallthrough]];
            case 0:
                [[fallthrough]];
            case 1:
                return;
            default:
                break;
        }
        auto mid {ds::advance(begin, size / 2)};
        merge_sort<add_lvalue_reference_t<Compare>>(begin, mid, cmp);
        merge_sort<add_lvalue_reference_t<Compare>>(mid, end, cmp);
        /* O(1) space complexity */
        for(auto i {begin}, j {mid}; j not_eq end;) {
            do {
                if(cmp(*j, *i)) {
                    break;
                }
            }while(++i not_eq j);
            auto middle {j};
            do {
                if(cmp(*i, *j)) {
                    break;
                }
            }while(++j not_eq end);
            ds::rotate(i, middle, j);
        }
    }
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(forward_list)
namespace data_structure {
    template <typename ForwardIterator>
    [[nodiscard]]
    bool is_loop_list(ForwardIterator begin, ForwardIterator end) {
        auto quick {begin};
        while(begin not_eq quick) {
            ++begin;
            ++++quick;
            if(quick == end) {
                return false;
            }
        }
        return true;
    }
    template <typename ForwardIterator>
    [[nodiscard]]
    ForwardIterator loop_list_entry(ForwardIterator begin, ForwardIterator end) {
        auto slow {begin};
        auto quick {begin};
        while(slow not_eq quick) {
            ++slow;
            ++++quick;
            if(quick == end) {
                return end;
            }
        }
        while(slow not_eq begin) {
            ++slow;
            ++begin;
        }
        return slow;
    }
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(auxiliary)
namespace data_structure::__data_structure_auxiliary {
    template <typename AllocTraits, typename ValueType, typename PointerRef,
            bool Bidirectional = false, bool CircularQueue = false, typename Pointer>
    static void construct_ranges(Pointer first, Pointer end_front, PointerRef cursor,
            Pointer rhs_begin, Pointer rhs_end) {
        static_assert(is_same_v<remove_reference_t<PointerRef>, Pointer>,
                "The template argument Pointer is different from pointer");
        if constexpr(is_trivially_copy_assignable_v<ValueType>) {
            ds::copy<Pointer>(rhs_begin, rhs_end, cursor);
        }else {
            if constexpr(is_nothrow_move_constructible_v<ValueType> or (
                    is_nothrow_copy_constructible_v<ValueType> and not is_move_constructible_v<ValueType>)) {
                for(auto rhs_cursor {rhs_begin}; rhs_cursor not_eq rhs_end;) {
                    AllocTraits::construct(cursor++, ds::move(*rhs_cursor++));
                }
            }else {
                const auto backup {cursor};
                try {
                    for(; rhs_begin not_eq rhs_end; ++cursor) {
                        AllocTraits::construct(cursor, *rhs_begin++);
                    }
                }catch(...) {
                    if constexpr(Bidirectional) {
                        AllocTraits::destroy(first, end_front);
                        AllocTraits::destroy(backup, cursor);
                    }else {
                        AllocTraits::destroy(first, cursor);
                    }
                    if constexpr(CircularQueue) {
                        AllocTraits::operator delete(first - 1);
                    }else {
                        AllocTraits::operator delete(first);
                    }
                    throw;
                }
            }
        }
    }
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(testing)
namespace data_structure::__data_structure_testing {
    template <typename RandomAccessIterator>
    void ranking_sort(RandomAccessIterator begin, RandomAccessIterator end) {
        const auto size {ds::distance(begin, end)};
        auto rank {::new int[size] {}};
        try {
            for(auto i {1}; i < size; ++i) {
                for(auto j {0}; j < i; ++j) {
                    if(begin[j] < begin[i] or begin[j] == begin[i]) {
                        ++rank[i];
                    }else {
                        ++rank[j];
                    }
                }
            }
            for(auto i {0}; i < size; ++i) {
                auto &save {rank[i]};
                while(save not_eq i) {
                    ds::swap(begin[save], begin[i]);
                    ds::swap(rank[save], save);
                }
            }
        }catch(...) {
            ::delete[] rank;
        }
        ::delete[] rank;
    }
    template <typename BidirectionalIterator>
    inline BidirectionalIterator
    __selection_sort_index_max_element(BidirectionalIterator begin, BidirectionalIterator end) {
        auto it {ds::move(begin++)};
        while(begin not_eq end) {
            if(*begin > *it) {
                it = begin;
            }
            ++begin;
        }
        return ds::move(it);
    }
    template <typename BidirectionalIterator>
    void selection_sort(BidirectionalIterator begin, BidirectionalIterator end) {
        auto max_iter {__dst::__selection_sort_index_max_element(begin, end)};
        for(--end; end not_eq begin; --end) {
            if(max_iter not_eq end) {
                ds::swap(*max_iter, *end);
            }
            max_iter = __dst::__selection_sort_index_max_element(begin, end);
        }
    }
    template <typename BidirectionalIterator>
    void bubble_sort(BidirectionalIterator begin, BidirectionalIterator end) {
        auto last {end};
        --last;
        for(auto i {begin}; i not_eq end; ++i) {
            for(auto j {last}; i not_eq j; --j) {
                if(*j < *i) {
                    swap(*i, *j);
                }
            }
        }
    }
    template <typename RandomAccessIterator>
    void insertion_sort(RandomAccessIterator begin, RandomAccessIterator end) {
        const auto size {ds::distance(begin, end)};
        for(auto i {1}; i < size; ++i) {
            auto j {i - 1};
            auto save {ds::move(begin[i])};
            for(; j >= 0 and save < begin[j]; --j) {
                begin[j + 1] = begin[j];
            }
            begin[j + 1] = ds::move(save);
        }
    }
    template <typename ForwardList, typename ForwardIterator>
    void bucket_sort(ForwardIterator begin, ForwardIterator end, ForwardList &forward_list,
            iterator_traits_t(ForwardIterator, size_type) range,
            int (*index_function)(iterator_traits_t(ForwardIterator, const_reference))) {
        auto bucket {::new ForwardList[range] {}};
        try {
            while(begin not_eq end) {
                auto &value {*begin};
                bucket[index_function(value)].push_back(value);
                ++begin;
            }
            for(auto i {0}; i < range; ++i) {
                forward_list.merge(bucket[i]);
            }
        }catch(...) {
            ::delete[] bucket;
            throw;
        }
        ::delete[] bucket;
    }
    template <typename T>
    T __radix_sort_power_auxiliary(T base, unsigned exponent) {
        if(not exponent) {
            return 1;
        }
        T result {1};
        while(true) {
            if(exponent % 2) {
                result *= base;
            }
            exponent /= 2;
            if(not exponent) {
                break;
            }
            base *= base;
        }
        return result;
    }
    template <typename ForwardList>
    typename ForwardList::const_iterator __radix_sort_before_end(const ForwardList &forward_list) noexcept {
        auto before_end {forward_list.cbefore_begin()};
        const auto the_end {forward_list.cend()};
        while(true) {
            auto next {before_end};
            ++next;
            if(next == the_end) {
                break;
            }
            ++before_end;
        }
        return before_end;
    }
    template <typename ForwardList, typename ForwardIterator>
    void radix_sort(ForwardIterator begin, ForwardIterator end, ForwardList &forward_list, int radix = 10) {
        auto bucket {::new ForwardList[radix] {}};
        try {
            ForwardList list {};
            auto exponent {1};
            while(true) {
                auto flag {true};
                while(begin not_eq end) {
                    auto &value {*begin++};
                    auto digit {static_cast<int>(value % __radix_sort_power_auxiliary(radix, exponent) /
                            __radix_sort_power_auxiliary(radix, exponent - 1))};
                    if(flag and digit) {
                        flag = false;
                    }
                    if(bucket[digit].empty()) {
                        bucket[digit].push_front(value);
                        continue;
                    }
                    bucket[digit].insert_after(__radix_sort_before_end(bucket[digit]), value);
                }
                ++exponent;
                list.clear();
                if(flag) {
                    forward_list = ds::move(bucket[0]);
                    break;
                }
                for(auto i {0}; i < radix; ++i) {
                    list.insert_after(__radix_sort_before_end(list), bucket[i].cbegin(), bucket[i].cend());
                    bucket[i].clear();
                }
                begin = list.begin();
                end = list.end();
            }
        }catch(...) {
            ::delete[] bucket;
            throw;
        }
        ::delete[] bucket;
    }
}
__DATA_STRUCTURE_END

#endif //DATA_STRUCTURE_ALGORITHM_HPP