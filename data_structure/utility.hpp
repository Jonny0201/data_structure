/*
    * Copyright © [2019 - 2020] [Jonny Charlotte]
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

#ifndef DATA_STRUCTURE_UTILITY_HPP
#define DATA_STRUCTURE_UTILITY_HPP

#include "type_traits.hpp"

namespace data_structure {
    template <typename T>
    constexpr inline typename remove_reference<T>::type &&move(T &&value) noexcept {
        return static_cast<typename remove_reference<T>::type &&>(value);
    }
    template <typename T>
    constexpr inline T &&forward(typename remove_reference<T>::type &value) noexcept {
        return static_cast<T &&>(value);
    }
    template <typename T>
    constexpr inline T &&forward(typename remove_reference<T>::type &&value) noexcept {
        static_assert(is_lvalue_reference<T>::value, "Cannot forward an rvalue as an lvalue!");
        return static_cast<T &&>(value);
    }
}

#endif //DATA_STRUCTURE_UTILITY_HPP