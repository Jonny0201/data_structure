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

#ifndef DATA_STRUCTURE_HEAP_HPP
#define DATA_STRUCTURE_HEAP_HPP

#include "iterator.hpp"
#include "functional.hpp"

namespace data_structure {
    template <typename Iterator>
    inline iterator_traits_t(Iterator, difference_type)
    distance(enable_if<not is_random_access_iterator_v<Iterator>, Iterator>, Iterator);
    template <typename Iterator>
    inline iterator_traits_t(Iterator, difference_type)
    distance(enable_if_t<is_random_access_iterator_v<Iterator>, Iterator>, Iterator)
            noexcept(has_nothrow_minus_operator_v<Iterator>);
    template <typename RandomAccessIterator>
    inline void make_heap(RandomAccessIterator begin, RandomAccessIterator end)
            noexcept(is_nothrow_swappable<typename iterator_traits<RandomAccessIterator>::value_type>::value){
        ds::make_heap(begin, end, ds::less<>());
    }
    template <typename RandomAccessIterator, typename Compare>
    void make_heap(RandomAccessIterator begin, RandomAccessIterator end, Compare cmp) {
        const auto distance {ds::distance(begin, end)};
        for(auto parent {(distance - 2) / 2}; parent >= 0; --parent) {
            auto child {parent * 2 + 1};
            if(const auto right_child {child + 1};
                    right_child < distance and cmp(begin[child], begin[right_child])) {
                ++child;
            }
            if(cmp(begin[child], begin[parent])) {
                continue;
            }
            auto value {ds::move(begin[parent])};
            do {
                begin[parent] = ds::move(begin[child]);
                parent = child;
                if(++(child *= 2); child >= distance) {
                    break;
                }
                if(const auto right_child {child + 1};
                        right_child < distance and cmp(begin[child], begin[right_child])) {
                    ++child;
                }
            }while(cmp(value, begin[child]));
            begin[parent] = ds::move(value);
        }
    }
    template <typename RandomAccessIterator>
    inline void push_heap(RandomAccessIterator begin, RandomAccessIterator end) {
        push_heap(begin, end, ds::less<>());
    }
    template <typename RandomAccessIterator, typename Compare>
    void push_heap(RandomAccessIterator begin, RandomAccessIterator end, Compare cmp) {
        const auto distance {ds::distance(begin, end)};
        if(distance < 2) {
            return;
        }
        auto child {distance - 1}, parent {(child - 1) / 2};
        if(cmp(begin[child], begin[parent])) {
            return;
        }
        auto value {ds::move(begin[child])};
        do {
            begin[child] = ds::move(begin[parent]);
            if(not parent) {
                break;
            }
            child = parent;
            --parent /= 2;
        }while(cmp(begin[parent], value));
        begin[parent] = ds::move(value);
    }
    template <typename RandomAccessIterator>
    inline void pop_heap(RandomAccessIterator begin, RandomAccessIterator end) {
        ds::pop_heap(begin, end, ds::less<>());
    }
    template <typename RandomAccessIterator, typename Compare>
    void pop_heap(RandomAccessIterator begin, RandomAccessIterator end, Compare cmp) {
        const auto distance {ds::distance(begin, end)};
        switch(distance) {
            case 0:
                [[fallthrough]];
            case 1:
                return;
            default:
                break;
        }
        --distance;
        auto value {ds::move(*--end)};
        typename iterator_traits<RandomAccessIterator>::difference_type parent {0}, child {1};
        if(const auto right_child {child + 1};
                right_child < distance and cmp(begin[child], begin[right_child])) {
            ++child;
        }
        while(true) {
            begin[parent] = ds::move(begin[child]);
            parent = child;
            ++(child *= 2);
            if(child >= distance) {
                break;
            }
        }
        begin[parent] = ds::move(value);
    }
}

#endif //DATA_STRUCTURE_HEAP_HPP