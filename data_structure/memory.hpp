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

#ifndef DATA_STRUCTURE_MEMORY_HPP
#define DATA_STRUCTURE_MEMORY_HPP

namespace data_structure {
    template <typename T>
    constexpr inline T *address_of(T &arg) noexcept {
        return reinterpret_cast<T *>(
                &const_cast<char &>(reinterpret_cast<const volatile char &>(arg)));
    }
    template <typename T>
    constexpr inline T *addressof(T &arg) noexcept {
        return address_of(arg);
    }
}

#endif //DATA_STRUCTURE_MEMORY_HPP