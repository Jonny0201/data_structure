/*
    * Copyright © [2019] [Jonny Charlotte]
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

namespace data_structure {
    template <typename Iterator>
    inline typename iterator_traits<Iterator>::difference_type distance(typename enable_if<
                    is_input_iterator<Iterator>::value and not is_random_access_iterator<Iterator>::value,
            Iterator>::type begin, Iterator end) {
        typename iterator_traits<Iterator>::difference_type difference {0};
        while(begin not_eq end) {
            ++begin;
            ++difference;
        }
        return difference;
    }
    template <typename Iterator>
    inline typename iterator_traits<Iterator>::difference_type distance(
            typename enable_if<is_random_access_iterator<Iterator>::value, Iterator>::type begin,
            Iterator end) {
        return end - begin;
    }
    inline decltype(static_cast<char *>(nullptr) - static_cast<char *>(nullptr)) distance(
            void *begin, void *end) noexcept {
        return reinterpret_cast<char *>(end) - reinterpret_cast<char *>(begin);
    }

    template <typename T>
    inline typename enable_if<has_swap_function<T>::value, void>::type swap(T &lhs, T &rhs) noexcept {
        lhs.swap(rhs);
    }
    template <typename T>
    inline typename enable_if<not has_swap_function<T>::value, void>::type swap(T &lhs, T &rhs) noexcept {
        auto tmp {move(lhs)};
        lhs = move(rhs);
        rhs = move(tmp);
    }

    namespace __data_structure_testing {
        template <typename RandomAccessIterator>
        void ranking_sort(typename enable_if<
                is_random_access_iterator<RandomAccessIterator>::value, RandomAccessIterator>::type begin,
                RandomAccessIterator end) {
            const auto size {distance(begin, end)};
            auto rank {::new int[size] {}};
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
                    swap(begin[save], begin[i]);
                    swap(rank[save], save);
                }
            }
            ::delete[] rank;
        }
        template <typename BidirectionalIterator>
        BidirectionalIterator __selection_sort_index_max_element(typename enable_if<
                is_bidirectional_iterator<BidirectionalIterator>::value, BidirectionalIterator>::type begin,
                BidirectionalIterator end) {
            auto it {move(begin++)};
            while(begin not_eq end) {
                if(*begin > *it) {
                    it = begin;
                }
                ++begin;
            }
            return move(it);
        }
        template <typename BidirectionalIterator>
        void selection_sort(typename enable_if<
                is_bidirectional_iterator<BidirectionalIterator>::value, BidirectionalIterator>::type begin,
                BidirectionalIterator end) {
            auto max_iter {__data_structure_testing::__selection_sort_index_max_element(begin, end)};
            for(--end; end not_eq begin; --end) {
                if(max_iter not_eq end) {
                    swap(*max_iter, *end);
                }
                max_iter = __data_structure_testing::__selection_sort_index_max_element(begin, end);
            }
        }
        template <typename BidirectionalIterator>
        void bubble_sort(typename enable_if<
                is_bidirectional_iterator<BidirectionalIterator>::value, BidirectionalIterator>::type begin,
                BidirectionalIterator end) {
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
        void insertion_sort(typename enable_if<
                is_random_access_iterator<RandomAccessIterator>::value, RandomAccessIterator>::type begin,
                RandomAccessIterator end) {
            const auto size {distance(begin, end)};
            for(auto i {1}; i < size; ++i) {
                auto j {i - 1};
                auto save {move(begin[i])};
                for(; j >= 0 and save < begin[j]; --j) {
                    begin[j + 1] = begin[j];
                }
                begin[j + 1] = move(save);
            }
        }
    }
}

#endif //DATA_STRUCTURE_ALGORITHM_HPP
