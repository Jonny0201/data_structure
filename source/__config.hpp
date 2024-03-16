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

#ifndef DATA_STRUCTURE___CONFIG_HPP
#define DATA_STRUCTURE___CONFIG_HPP

#include <memory>
#include <initializer_list>
#include <compare>
#include <exception>

#define __DATA_STRUCTURE_START(x, ...)
#define __DATA_STRUCTURE_END

namespace data_structure {      // data_structure namespace creation

__DATA_STRUCTURE_START(basic type definition)
using size_t = decltype(sizeof 0);
using ptrdiff_t = decltype(static_cast<int *>(nullptr) - static_cast<int *>(nullptr));
using align_val_t = std::align_val_t;
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(exception type definition)
using exception = std::exception;
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(initializer_list)
template <typename T>
using initializer_list = std::initializer_list<T>;
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(three way comparison)
using strong_ordering = std::strong_ordering;
using weak_ordering = std::weak_ordering;
using partial_ordering = std::partial_ordering;
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(reserved helper namespace for data_structure)
namespace __data_structure_helper {}
namespace __data_structure_auxiliary {}
namespace __data_structure_implement {}
namespace __data_structure_testing {}
namespace __data_structure_detail {}

namespace __dsh = __data_structure_helper;
namespace __dsa = __data_structure_auxiliary;
namespace __dsi = __data_structure_implement;
namespace __dst = __data_structure_testing;
namespace __dsd = __data_structure_detail;
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(memory functions)
inline void *memory_set(void *start, int value, size_t size) noexcept {
    return __builtin_memset(start, value, size);
}
inline constexpr void *memory_copy(void *start, const void *first, size_t size) noexcept {
    return __builtin_memcpy(start, first, size);
}
inline constexpr void *memory_move(void *start, const void *first, size_t size) noexcept {
    return __builtin_memmove(start, first, size);
}
[[nodiscard]]
inline constexpr void *memory_character_search(const void *start, int ch, size_t size) noexcept {
    return __builtin_memchr(start, ch, size);
}
[[nodiscard]]
inline constexpr int memory_comparison(const void *start, const void *first, size_t size) noexcept {
    return __builtin_memcmp(start, first, size);
}
[[nodiscard]]
inline constexpr void *memory_allocation(size_t size) noexcept {
    return std::malloc(size);
}
inline constexpr void memory_free(void *ptr) noexcept {
    std::free(ptr);
}
[[nodiscard]]
inline constexpr void *memory_contiguous_allocation(size_t num, size_t size) noexcept {
    return std::calloc(num, size);
}
[[nodiscard]]
inline constexpr void *memory_reallocation(void *ptr, size_t size) noexcept {
    return std::realloc(ptr, size);
}
template <typename T = char>
inline constexpr void *memory_default_initialization(void *start, size_t size) noexcept {
    return __builtin_memset(start, 0, size * sizeof(T));
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(exceptional functions)
[[noreturn]]
inline void abort() noexcept {
    std::abort();
}
[[noreturn]]
inline void terminate() noexcept {
    std::terminate();
}
[[noreturn]]
inline void exit(int code) {
    std::exit(code);
}
__DATA_STRUCTURE_END

}       // namespace data_structure

namespace ds = data_structure;      // ds namespace alias definition

#endif // DATA_STRUCTURE___CONFIG_HPP