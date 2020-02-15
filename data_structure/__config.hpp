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

#ifndef DATA_STRUCTURE_CONFIG_HPP
#define DATA_STRUCTURE_CONFIG_HPP

#include <memory>
#include <initializer_list>
#include <limits>

#define __DATA_STRUCTURE_START(x, ...)
#define __DATA_STRUCTURE_END

__DATA_STRUCTURE_START(data_structure macro)
#define __DS data_structure
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(configure for C++ 2a)
#if __has_keyword(consteval)
#define _DATA_STRUCTURE_HAS_CONSTEVAL
#endif

#if __has_keyword(constinit)
#define _DATA_STRUCTURE_HAS_CONSTINIT
#endif

#if __has_keyword(char8_t)
#define _DATA_STRUCTURE_HAS_CHAR8_T
#endif

#if __has_keyword(concept) && __has_keyword(requires)
#define _DATA_STRUCTURE_HAS_CONCEPT
#endif

#if __has_keyword(co_await) && __has_keyword(co_return) && __has_keyword(co_yield)
#define _DATA_STRUCTURE_HAS_COROUTINE
#endif

#if __has_keyword(reflexpr)
#define _DATA_STRUCTURE_HAS_REFLECTION
#endif

#if __has_keyword(module) && __has_keyword(import)
#define _DATA_STRUCTURE_HAS_MODULE
#endif
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(namespace creation)
namespace data_structure {
    template <typename T>
    using initializer_list = std::initializer_list<T>;
    using size_t = decltype(sizeof 0);
    using ptrdiff_t = decltype(static_cast<int *>(nullptr) - static_cast<int *>(nullptr));

    inline namespace __data_structure_helper {}
    namespace __data_structure_auxiliary {}
    namespace __data_structure_impl {}
    namespace __data_structure_testing {}

    namespace __dsh = __data_structure_helper;
    namespace __dsa = __data_structure_auxiliary;
    namespace __dsi = __data_structure_impl;
    namespace __dst = __data_structure_testing;
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(namespace alias)
namespace ds = data_structure;
__DATA_STRUCTURE_END

#endif //DATA_STRUCTURE_CONFIG_HPP