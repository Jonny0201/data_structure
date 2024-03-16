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

#ifndef DATA_STRUCTURE_MEMORY_HPP
#define DATA_STRUCTURE_MEMORY_HPP

#include "utility.hpp"

namespace data_structure {

__DATA_STRUCTURE_START(object construction and destruction)
template <typename T, typename ...Args>
inline constexpr T *construct(T *p, Args &&...args) noexcept(is_nothrow_constructible_v<T, Args...>) {
    return new (static_cast<void *>(p)) T {forward<Args>(args)...};
}
template <typename T>
inline constexpr void destroy(T *p) noexcept(is_nothrow_destructible_v<T>) {
    if constexpr(not is_trivially_destructible_v<T>) {
        p->~T();
    }
}
template <typename T>
inline constexpr void destroy(T *begin, T *end) noexcept(is_nothrow_destructible_v<T>) {
    if constexpr(not is_trivially_destructible_v<T>) {
        while(begin not_eq end) {
            begin++->~T();
        }
    }
}
__DATA_STRUCTURE_END

}       // namespace data_structure

#endif //DATA_STRUCTURE_MEMORY_HPP