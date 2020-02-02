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
        void ranking_sort(RandomAccessIterator begin, RandomAccessIterator end) {
            const auto size {distance(begin, end)};
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
                        swap(begin[save], begin[i]);
                        swap(rank[save], save);
                    }
                }
            }catch(...) {
                ::delete[] rank;
            }
            ::delete[] rank;
        }
        template <typename BidirectionalIterator>
        BidirectionalIterator __selection_sort_index_max_element(BidirectionalIterator begin,
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
        void selection_sort(BidirectionalIterator begin, BidirectionalIterator end) {
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
        void insertion_sort(RandomAccessIterator begin, RandomAccessIterator end) {
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
        template <typename ForwardIterator, typename Arg>
        ForwardIterator binary_search(ForwardIterator begin, typename enable_if<
                is_forward_iterator<ForwardIterator>::value and
                        not is_random_access_iterator<ForwardIterator>::value, ForwardIterator>::type end,
                const Arg &value);
        template <typename RandomAccessIterator, typename Arg>
        RandomAccessIterator binary_search(RandomAccessIterator begin, typename enable_if<
                is_random_access_iterator<RandomAccessIterator>::value, RandomAccessIterator>::type end,
                const Arg &value) {
            const auto return_iterator {end};
            while(begin < end) {
                auto middle {begin + distance(begin, end) / 2};
                if(*middle == value) {
                    return middle;
                }else if(*middle < value) {
                    begin = middle + 1;
                }else {
                    end = middle;
                }
            }
            return return_iterator;
        }
        template <typename ForwardList, typename ForwardIterator>
        void bucket_sort(ForwardIterator begin, ForwardIterator end, ForwardList &forward_list,
                typename iterator_traits<ForwardIterator>::size_type range,
                int (*index_function)(typename iterator_traits<ForwardIterator>::const_reference)) {
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
                        forward_list = std::move(bucket[0]);
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
}

#endif //DATA_STRUCTURE_ALGORITHM_HPP
