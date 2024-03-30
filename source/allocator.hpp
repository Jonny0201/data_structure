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

namespace data_structure {

/*
 * The allocator in data structure project is different from std::allocator. If you want
 * to customize your own allocator, it's essential to follow the detailed specifications :
 * (1) The nothrow attribution of member function `allocate` is determined by the first
 *     non-type template parameter `NoThrow`, the default value of `NoThrow` is false;
 * (2) The allocator should support reallocation by providing member function `reallocate`;
 * (3) The member function `deallocate` should be marked as noexcept, and if there exists
 *     deallocating memory in other member functions, the operation should also be nothrow;
 * (4) The copy and move operations of allocator, size_type, difference_type, pointer and
 *     const_pointer should be nothrow;
 * (5) If the allocation size is zero, no memory should be allocated and nullptr is the
 *     returning value. Especially note that if the reallocation size is zero, the source
 *     memory should be deallocated.
*/
__DATA_STRUCTURE_START(allocator)
template <typename T>
class allocator {
public:
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using value_type = T;
    using pointer = T *;
    using const_pointer = const T *;
public:
    constexpr allocator() noexcept = default;
    constexpr allocator(const allocator &) noexcept = default;
    constexpr allocator(allocator &&) noexcept = default;
    constexpr ~allocator() noexcept = default;
public:
    constexpr allocator &operator=(const allocator &) noexcept = default;
    constexpr allocator &operator=(allocator &&) noexcept = default;
public:
    template <bool NoThrow = false>
    [[nodiscard]]
    static constexpr T *allocate(size_type n) noexcept(NoThrow) {
        if(n == 0) {
            return nullptr;
        }
        if constexpr(is_trivially_copyable_v<T>) {
            auto memory {static_cast<T *>(memory_allocation(n * sizeof(T)))};
            if constexpr(not NoThrow) {
                if(not memory) {
                    throw std::bad_alloc {};
                }
            }
            return memory;
        }
        if constexpr(NoThrow) {
            return static_cast<T *>(::operator new(n * sizeof(T), ds::nothrow));
        }
        return static_cast<T *>(::operator new(n * sizeof(T)));
    }
    template <bool NoThrow = false>
    [[nodiscard]]
    static constexpr T *reallocate(void *source, size_type n) noexcept(NoThrow) requires is_trivially_copyable_v<T> {
        if(n == 0) {
            free(source);
            return nullptr;
        }
        auto memory {static_cast<T *>(memory_reallocation(source, n * sizeof(T)))};
        if constexpr(not NoThrow) {
            if(not memory) {
                throw std::bad_alloc {};
            }
        }
        return memory;
    }
    static constexpr void deallocate(void *p, size_type) noexcept {
        if constexpr(is_trivially_copyable_v<T>) {
            return free(p);
        }
        ::operator delete(p, ds::nothrow);
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