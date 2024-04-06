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

#ifndef DATA_STRUCTURE_UTILITY_HPP
#define DATA_STRUCTURE_UTILITY_HPP

#include "type_traits.hpp"

namespace data_structure {

__DATA_STRUCTURE_START(move and forward)
template <typename T>
inline constexpr remove_reference_t<T> &&move(T &&value) noexcept {
    return static_cast<remove_reference_t<T> &&>(value);
}
template <bool Conditional, typename T>
inline constexpr conditional_t<Conditional, remove_reference_t<T> &&, const T &>
move_if(T &value) noexcept {
    return ds::move(value);
}
template <typename T>
inline constexpr T &&forward(remove_reference_t<T> &value) noexcept {
    return static_cast<T &&>(value);
}
template <typename T>
inline constexpr T &&forward(remove_reference_t<T> &&value) noexcept {
    static_assert(is_lvalue_reference_v<T>, "Cannot forward an rvalue as an lvalue!");
    return static_cast<T &&>(value);
}
__DATA_STRUCTURE_END(move and forward)

__DATA_STRUCTURE_START(swap)
template <typename T>
inline constexpr enable_if_t<(is_move_constructible_v<T> and is_move_assignable_v<T>) or
        (is_copy_constructible_v<T> and is_copy_assignable_v<T>)>
swap(T &lhs, T &rhs) noexcept((is_nothrow_move_constructible<T>::value and is_nothrow_move_assignable<T>::value) or
        (is_nothrow_copy_constructible<T>::value and is_nothrow_copy_assignable<T>::value)) {
    T tmp {ds::move_if<is_nothrow_move_constructible_v<T>>(lhs)};
    lhs = ds::move_if<is_nothrow_move_assignable_v<T>>(rhs);
    rhs = ds::move_if<is_nothrow_move_assignable_v<T>>(tmp);
}
template <typename T, size_t N>
inline constexpr enable_if_t<(is_move_constructible_v<T> and is_move_assignable_v<T>) or
        (is_copy_constructible_v<T> and is_copy_assignable_v<T>)>
swap(T (&lhs)[N], T (&rhs)[N]) noexcept((is_move_constructible_v<T> and is_move_assignable_v<T>) or
        (is_copy_constructible_v<T> and is_copy_assignable_v<T>)) {
    for(auto i {0}; i < N; ++i) {
        ds::swap(lhs[i], rhs[i]);
    }
}
__DATA_STRUCTURE_END(swap)

__DATA_STRUCTURE_START(transaction tool)
template <typename Rollback>
class transaction {
private:
    Rollback rollback_block;
    bool done;
public:
    explicit transaction(Rollback rollback_block) noexcept(is_nothrow_move_constructible_v<Rollback>) :
            rollback_block {ds::move(rollback_block)}, done {} {}
    transaction(const transaction &) = delete;
    transaction(transaction &&rhs) noexcept(is_nothrow_move_constructible_v<Rollback>) :
            rollback_block {ds::move(rhs.rollback_block)}, done {} {
        rhs.done = true;
    }
    ~transaction() noexcept {
        if(not this->done) {
            this->rollback_block();
        }
    }
public:
    transaction &operator=(const transaction &) = delete;
    transaction &operator=(transaction &&) = delete;
public:
    void complete() noexcept {
        this->done = true;
    }
    void rollback() noexcept {
        this->rollback_block();
        this->done = true;
    }
    Rollback &get_rollback() & noexcept {
        return this->rollback_block;
    }
};
__DATA_STRUCTURE_END(transaction tool)

}       // namespace data_structure

__DATA_STRUCTURE_START(inner tools for data structure library)
namespace data_structure::__data_structure_auxiliary {

__DATA_STRUCTURE_START(allocator_compressor for container)
template <typename T, typename Allocator, bool = is_empty_v<Allocator> and not is_final_v<Allocator>>
        requires is_trivial_v<T> and is_class_v<Allocator>
struct allocator_compressor {
    T first {};
    Allocator alloc {};
public:
    constexpr allocator_compressor() noexcept(is_nothrow_default_constructible_v<Allocator>) = default;
    explicit constexpr allocator_compressor(T first) noexcept(is_nothrow_default_constructible_v<Allocator>) :
            first {first}, alloc {} {}
    explicit constexpr allocator_compressor(const Allocator &allocator)
            noexcept(is_nothrow_copy_constructible_v<Allocator>) : first {}, alloc {allocator} {}
    constexpr allocator_compressor(T first, const Allocator &allocator)
            noexcept(is_nothrow_copy_constructible_v<Allocator>) : first {first}, alloc {allocator} {}
    constexpr allocator_compressor(const allocator_compressor &rhs)
            noexcept(is_nothrow_copy_constructible_v<Allocator>) : first(rhs.first), alloc {rhs.alloc} {}
    constexpr allocator_compressor(allocator_compressor &&rhs) noexcept(is_nothrow_move_constructible_v<Allocator>) :
            first(rhs.first), alloc {ds::move(rhs.alloc)} {}
public:
    constexpr T &operator()() noexcept {
        return this->first;
    }
    constexpr const T &operator()() const noexcept {
        return this->first;
    }
    constexpr Allocator &allocator() noexcept {
        return this->alloc;
    }
    constexpr const Allocator &allocator() const noexcept {
        return this->alloc;
    }
};
template <typename T, typename Allocator>
struct allocator_compressor<T, Allocator, true> : Allocator {
    T first {};
public:
    constexpr allocator_compressor() noexcept(is_nothrow_default_constructible_v<Allocator>) = default;
    explicit constexpr allocator_compressor(T first) noexcept(is_nothrow_default_constructible_v<Allocator>) :
            Allocator(), first {first} {}
    explicit constexpr allocator_compressor(const Allocator &allocator)
            noexcept(is_nothrow_copy_constructible_v<Allocator>) : Allocator(allocator), first {} {}
    constexpr allocator_compressor(T first, const Allocator &allocator)
            noexcept(is_nothrow_copy_constructible_v<Allocator>) : Allocator(allocator), first {first} {}
    constexpr allocator_compressor(const allocator_compressor &rhs)
            noexcept(is_nothrow_copy_constructible_v<Allocator>) : Allocator(rhs.allocator()), first {rhs.first} {}
    constexpr allocator_compressor(allocator_compressor &&rhs) noexcept :
            Allocator(ds::move(rhs.allocator())), first {rhs.first} {}
public:
    constexpr T &operator()() noexcept {
        return this->first;
    }
    constexpr const T &operator()() const noexcept {
        return this->first;
    }
    constexpr Allocator &allocator() noexcept {
        return static_cast<Allocator &>(*this);
    }
    constexpr const Allocator &allocator() const noexcept {
        return static_cast<const Allocator &>(*this);
    }
};
__DATA_STRUCTURE_END(allocator_compressor for container)

}       // namespace data_structure::__data_structure_auxiliary
__DATA_STRUCTURE_END(inner tools for data structure library)

#endif //DATA_STRUCTURE_UTILITY_HPP