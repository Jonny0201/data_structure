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
#ifndef DATA_STRUCTURE_ALLOCATOR_HPP
#define DATA_STRUCTURE_ALLOCATOR_HPP

#include "type_traits.hpp"
#include "meta.hpp"

namespace data_structure {

__DATA_STRUCTURE_START(allocator)
template <typename T>
class allocator {
public:
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using value_type = T;
public:
    consteval allocator() noexcept = default;
    consteval allocator(const allocator &) noexcept = default;
    consteval allocator(allocator &&) noexcept = default;
    constexpr ~allocator() noexcept = default;
public:
    consteval allocator &operator=(const allocator &) noexcept = default;
    consteval allocator &operator=(allocator &&) noexcept = default;
public:
    [[nodiscard]]
    static constexpr T *allocate(size_type n) {
        if constexpr(is_trivially_copyable_v<T>) {
            auto memory {static_cast<T *>(memory_allocation(n * sizeof(T)))};
            if(not memory) {
                throw std::bad_alloc {};
            }
            return memory;
        }
        return static_cast<T *>(::operator new(n * sizeof(T)));
    }
    [[nodiscard]]
    static constexpr T *allocate(size_type n, meta::dynamic) noexcept {
        if constexpr(is_trivially_copyable_v<T>) {
            return static_cast<T *>(memory_allocation(n * sizeof(T)));
        }
        return static_cast<T *>(::operator new(n * sizeof(T), std::nothrow));
    }
    [[nodiscard]]
    static constexpr T *reallocate(void *source, size_type n) requires is_trivially_copyable_v<T> {
        return static_cast<T *>(memory_reallocation(source, n * sizeof(T)));
    }
    static constexpr void deallocate(void *p, size_type) noexcept {
        if constexpr(is_trivially_copyable_v<T>) {
            return free(p);
        }
        ::operator delete(p);
    }
    static constexpr void deallocate(void *p, size_type, meta::dynamic) noexcept {
        if constexpr(is_trivially_copyable_v<T>) {
            return free(p);
        }
        ::operator delete(p, std::nothrow);
    }
};
template <typename T, typename U>
[[nodiscard]]
inline consteval bool operator==(const allocator<T> &, const allocator<U> &) noexcept {
    return true;
}
template <typename T, typename U>
[[nodiscard]]
inline consteval bool operator!=(const allocator<T> &, const allocator<U> &) noexcept {
    return false;
}
__DATA_STRUCTURE_END

}       // namespace data_structure

#endif //DATA_STRUCTURE_ALLOCATOR_HPP