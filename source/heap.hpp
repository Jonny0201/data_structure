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

#ifndef DATA_STRUCTURE_HEAP_HPP
#define DATA_STRUCTURE_HEAP_HPP

#include "iterator.hpp"

namespace data_structure {

__DATA_STRUCTURE_START(heap algorithms)
template <IsRandomAccessIterator RandomAccessIterator, typename Compare>
inline constexpr void make_heap(RandomAccessIterator begin, RandomAccessIterator end, Compare compare) {
    const auto distance {end - begin};
    if(distance < 2) {
        return;
    }
    const auto boundary {distance / 2 - 1};
    for(auto i {boundary};;) {
        auto value {ds::move(begin[i])};
        for(auto parent {i};;) {
            const auto left_child {2 * parent + 1};
            auto target {left_child};
            if(const auto right_child {left_child + 1}; right_child < distance and compare(begin[right_child], begin[left_child])) {
                ++target;
            }
            if(compare(value, begin[target])) {
                begin[parent] = ds::move(value);
                break;
            }
            begin[parent] = ds::move(begin[target]);
            if(target > boundary) {
                begin[target] = ds::move(value);
                break;
            }
            parent = target;
        }
        if(--i == 0) {
            break;
        }
    }
}
template <IsRandomAccessIterator RandomAccessIterator, typename Compare>
inline constexpr void push_heap(RandomAccessIterator begin, RandomAccessIterator end, Compare compare) {
    const auto distance {end - begin};
    if(distance < 2) {
        return;
    }
    auto child {distance - 1}, parent {(distance - 2) / 2};
    if(compare(begin[child], begin[parent])) {
        return;
    }
    auto value {ds::move(begin[child])};
    do {
        begin[child] = ds::move(begin[parent]);
        if(parent == 0) {
            break;
        }
        child = parent;
        --parent /= 2;
    }while(not compare(begin[child], begin[parent]));
    begin[parent] = ds::move(value);
}
template <IsRandomAccessIterator RandomAccessIterator>
inline constexpr void push_heap(RandomAccessIterator begin, RandomAccessIterator end) {
    ds::push_heap(begin, end, std::less {});
}
template <IsRandomAccessIterator RandomAccessIterator, typename Compare>
inline constexpr void pop_heap(RandomAccessIterator begin, RandomAccessIterator end, Compare compare) {
    const auto distance {--end - begin};
    if(distance < 1) {
        return;
    }
    auto value {ds::move(*end)};
    auto parent {0}, child {1};
    while(true) {
        if(const auto right_child {child + 1}; right_child < distance and compare(begin[right_child], begin[child])) {
            ++child;
        }
        if(const auto &child_value {begin[child]}; compare(value, child_value)) {
            begin[parent] = ds::move(value);
            break;
        }else {
            begin[parent] = ds::move(child_value);
            parent = child;
            if(++(child *= 2) > distance) {
                break;
            }
        }
    }
    begin[parent] = ds::move(value);
}
template <IsRandomAccessIterator RandomAccessIterator>
inline constexpr void pop_heap(RandomAccessIterator begin, RandomAccessIterator end) {
    ds::pop_heap(begin, end, std::less {});
}
__DATA_STRUCTURE_END(heap algorithms)

}       // namespace data_structure

#endif      //DATA_STRUCTURE_HEAP_HPP
