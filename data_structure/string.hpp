/*
    * Copyright © [2019 - 2022] [Jonny Charlotte]
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

#ifndef DATA_STRUCTURE_STRING_HPP
#define DATA_STRUCTURE_STRING_HPP

#include "iterator.hpp"
#include "allocator.hpp"

namespace data_structure {
    template <typename RandomAccessIterator>
    iterator_traits_t(RandomAccessIterator, size_type) string_length(RandomAccessIterator str) {
        auto end {str};
        while(*end++ not_eq '\0');
        return static_cast<iterator_traits_t(RandomAccessIterator, size_type)>(end - str);
    }
    template <typename T>
    inline bool is_upper(T ch) noexcept {
        return ch >= 'A' and ch <= 'Z';
    }
    template <typename T>
    inline bool is_lower(T ch) noexcept {
        return ch >= 'a' and ch <= 'z';
    }
    template <typename T>
    inline T to_upper(T ch) noexcept {
        return ds::is_lower(ch) ? ch - 32 : ch;
    }
    template <typename T>
    inline T to_lower(T ch) noexcept {
        return ds::is_upper(ch) ? ch + 32 : ch;
    }
}

#endif //DATA_STRUCTURE_STRING_HPP
