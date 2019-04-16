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
    inline constexpr auto distance(typename enable_if<
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
    inline constexpr auto distance(
            typename enable_if<is_random_access_iterator<Iterator>::value, Iterator>::type begin,
            Iterator end) {
        return end - begin;
    }
    inline auto distance(void *begin, void *end) noexcept {
        return reinterpret_cast<char *>(end) - reinterpret_cast<char *>(begin);
    }
}

#endif //DATA_STRUCTURE_ALGORITHM_HPP
