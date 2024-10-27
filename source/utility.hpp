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
move_if(T &&value) noexcept {
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
    void restart() noexcept {
        this->done = false;
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

__DATA_STRUCTURE_START(allocator
    compressor for container)
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
    constexpr allocator_compressor(allocator_compressor &&rhs) noexcept :
            first(rhs.first), alloc {ds::move(rhs.alloc)} {}
public:
    constexpr allocator_compressor &operator=(const allocator_compressor &rhs) noexcept {
        this->alloc = rhs.alloc;
        this->first = rhs.first;
        return *this;
    }
    constexpr allocator_compressor &operator=(allocator_compressor &&rhs) noexcept {
        this->alloc = ds::move(rhs.alloc);
        this->first = rhs.first;
        return *this;
    }
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
template <typename T, typename Allocator> requires is_trivial_v<T> and is_class_v<Allocator>
struct allocator_compressor<T, Allocator, true> : Allocator {
    T first {};
public:
    constexpr allocator_compressor() noexcept(is_nothrow_default_constructible_v<Allocator>) = default;
    explicit constexpr allocator_compressor(T first) noexcept(is_nothrow_default_constructible_v<Allocator>) :
            Allocator(), first {first} {}
    explicit constexpr allocator_compressor(const Allocator &allocator) noexcept :
            Allocator(allocator), first {} {}
    constexpr allocator_compressor(T first, const Allocator &allocator) noexcept :
            Allocator(allocator), first {first} {}
    constexpr allocator_compressor(const allocator_compressor &rhs) noexcept :
            Allocator(rhs.allocator()), first {rhs.first} {}
    constexpr allocator_compressor(allocator_compressor &&rhs) noexcept :
            Allocator(ds::move(rhs.allocator())), first {rhs.first} {}
public:
    constexpr allocator_compressor &operator=(const allocator_compressor &rhs) noexcept {
        static_cast<Allocator &>(*this) = rhs;
        this->first = rhs.first;
        return *this;
    }
    constexpr allocator_compressor &operator=(allocator_compressor &&rhs) noexcept {
        static_cast<Allocator &>(*this) = ds::move(rhs);
        this->first = rhs.first;
        return *this;
    }
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
__DATA_STRUCTURE_END(allocator compressor for container)

__DATA_STRUCTURE_START(partial compressor for container)
template <typename T, typename U, bool = is_empty_v<U> and not is_final_v<U>>
        requires (is_class_v<U> and not is_same_v<T, U>)
struct partial_compressor {
    T t {};
    U u {};
public:
    constexpr partial_compressor() = default;
    explicit partial_compressor(const T &t) noexcept(is_nothrow_copy_constructible_v<T> and
            is_nothrow_default_constructible_v<U>) : t {t}, u {} {}
    explicit partial_compressor(T &&t) noexcept(is_nothrow_move_constructible_v<T> and
            is_nothrow_default_constructible_v<U>) : t {ds::move(t)}, u {} {}
    explicit partial_compressor(const U &u) noexcept(is_nothrow_default_constructible_v<T> and
            is_nothrow_copy_constructible_v<U>) : t {}, u {u} {}
    explicit partial_compressor(U &&u) noexcept(is_nothrow_default_constructible_v<T> and
            is_nothrow_move_constructible_v<U>) : t {}, u {ds::move(u)} {}
    template <typename ConvertibleToT, typename ConvertibleToU>
    constexpr partial_compressor(ConvertibleToT &&t, ConvertibleToU &&u) noexcept(
            is_nothrow_constructible_v<T, ConvertibleToT &&> and is_nothrow_constructible_v<U, ConvertibleToU &&>) :
            t {ds::forward<ConvertibleToT>(t)}, u {ds::forward<ConvertibleToU>(u)} {}
public:
    T &first() noexcept {
        return this->t;
    }
    const T &first() const noexcept {
        return this->t;
    }
    U &second() noexcept {
        return this->u;
    }
    const U &second() const noexcept {
        return this->u;
    }
};
template <typename T, typename U> requires is_class_v<U>
struct partial_compressor<T, U, true> : U {
    T t;
public:
    constexpr partial_compressor() = default;
    explicit partial_compressor(const T &t) noexcept(is_nothrow_copy_constructible_v<T> and
            is_nothrow_default_constructible_v<U>) : U {}, t {t} {}
    explicit partial_compressor(T &&t) noexcept(is_nothrow_move_constructible_v<T> and
            is_nothrow_default_constructible_v<U>) : U {}, t {ds::move(t)} {}
    explicit partial_compressor(const U &u) noexcept(is_nothrow_default_constructible_v<T> and
            is_nothrow_copy_constructible_v<U>) : U {u}, t {} {}
    explicit partial_compressor(U &&u) noexcept(is_nothrow_default_constructible_v<T> and
            is_nothrow_move_constructible_v<U>) : U {ds::move(u)}, t {} {}
    template <typename ConvertibleToT, typename ConvertibleToU>
    constexpr partial_compressor(ConvertibleToT &&t, ConvertibleToU &&u) noexcept(
            is_nothrow_constructible_v<T, ConvertibleToT &&> and is_nothrow_constructible_v<U, ConvertibleToU &&>) :
            U {ds::forward<ConvertibleToU>(u)}, t {ds::forward<ConvertibleToT>(t)} {}
public:
    T &first() noexcept {
        return this->t;
    }
    const T &first() const noexcept {
        return this->t;
    }
    U &second() noexcept {
        return *this;
    }
    const U &second() const noexcept {
        return *this;
    }
};
__DATA_STRUCTURE_END(partial compressor for container)

__DATA_STRUCTURE_START(compressor for container)
template <typename T, typename U, bool = is_class_v<T> and not is_final_v<T>,
        bool = is_class_v<U> and not is_final_v<U>> requires (not is_same_v<T, U>)
struct compressor {
    T t;
    U u;
public:
    constexpr compressor() = default;
    explicit constexpr compressor(const T &t) noexcept(is_nothrow_copy_constructible_v<T> and
            is_nothrow_default_constructible_v<U>) : t {t}, u {} {}
    explicit constexpr compressor(T &&t) noexcept(is_nothrow_move_constructible_v<T> and
            is_nothrow_default_constructible_v<U>) : t {ds::move(t)}, u {} {}
    explicit constexpr compressor(const U &u) noexcept(is_nothrow_default_constructible_v<T> and
            is_nothrow_copy_constructible_v<U>) : t {}, u {u} {}
    explicit constexpr compressor(U &&u) noexcept(is_nothrow_default_constructible_v<T> and
            is_nothrow_move_constructible_v<U>) : t {}, u {ds::move(u)} {}
    template <typename ConvertibleToT, typename ConvertibleToU>
    constexpr compressor(ConvertibleToT &&t, ConvertibleToU &&u) noexcept(
            is_nothrow_constructible_v<T, ConvertibleToT &&> and is_nothrow_constructible_v<U, ConvertibleToU &&>) :
            t {ds::forward<ConvertibleToT>(t)}, u {ds::forward<ConvertibleToU>(u)} {}
public:
    constexpr T &first() noexcept {
        return this->t;
    }
    constexpr const T &first() const noexcept {
        return this->t;
    }
    constexpr U &second() noexcept {
        return this->u;
    }
    constexpr const U &second() const noexcept {
        return this->u;
    }
};
template <typename T, typename U> requires (not is_same_v<T, U>)
struct compressor<T, U, true, false> : T {
    U u;
public:
    constexpr compressor() = default;
    explicit constexpr compressor(const T &t) noexcept(is_nothrow_copy_constructible_v<T> and
            is_nothrow_default_constructible_v<U>) : T {t}, u {} {}
    explicit constexpr compressor(T &&t) noexcept(is_nothrow_move_constructible_v<T> and
            is_nothrow_default_constructible_v<U>) : T {ds::move(t)}, u {} {}
    explicit constexpr compressor(const U &u) noexcept(is_nothrow_default_constructible_v<T> and
            is_nothrow_copy_constructible_v<U>) : T {}, u {u} {}
    explicit constexpr compressor(U &&u) noexcept(is_nothrow_default_constructible_v<T> and
            is_nothrow_move_constructible_v<U>) : T {}, u {ds::move(u)} {}
    template <typename ConvertibleToT, typename ConvertibleToU>
    constexpr compressor(ConvertibleToT &&t, ConvertibleToU &&u) noexcept(
            is_nothrow_constructible_v<T, ConvertibleToT &&> and is_nothrow_constructible_v<U, ConvertibleToU &&>) :
            T {ds::forward<ConvertibleToT>(t)}, u {ds::forward<ConvertibleToU>(u)} {}
public:
    constexpr T &first() noexcept {
        return *this;
    }
    constexpr const T &first() const noexcept {
        return *this;
    }
    constexpr U &second() noexcept {
        return this->u;
    }
    constexpr const U &second() const noexcept {
        return this->u;
    }
};
template <typename T, typename U> requires (not is_same_v<T, U>)
struct compressor<T, U, false, true> : U {
    T t;
public:
    constexpr compressor() = default;
    explicit constexpr compressor(const T &t) noexcept(is_nothrow_copy_constructible_v<T> and
            is_nothrow_default_constructible_v<U>) : U {}, T {t} {}
    explicit constexpr compressor(T &&t) noexcept(is_nothrow_move_constructible_v<T> and
            is_nothrow_default_constructible_v<U>) : U {}, T {ds::move(t)} {}
    explicit constexpr compressor(const U &u) noexcept(is_nothrow_default_constructible_v<T> and
            is_nothrow_copy_constructible_v<U>) : U {u}, T {} {}
    explicit constexpr compressor(U &&u) noexcept(is_nothrow_default_constructible_v<T> and
            is_nothrow_move_constructible_v<U>) : U {ds::move(u)}, T {} {}
    template <typename ConvertibleToT, typename ConvertibleToU>
    constexpr compressor(ConvertibleToT &&t, ConvertibleToU &&u) noexcept(
            is_nothrow_constructible_v<T, ConvertibleToT &&> and is_nothrow_constructible_v<U, ConvertibleToU &&>) :
            U {ds::forward<ConvertibleToU>(u)}, T {ds::forward<ConvertibleToT>(t)} {}
public:
    constexpr T &first() noexcept {
        return this->t;
    }
    constexpr const T &first() const noexcept {
        return this->t;
    }
    constexpr U &second() noexcept {
        return *this;
    }
    constexpr const U &second() const noexcept {
        return *this;
    }
};
template <typename T, typename U> requires (not is_same_v<T, U>)
struct compressor<T, U, true, true> : T, U {
public:
    constexpr compressor() = default;
    explicit constexpr compressor(const T &t) noexcept(is_nothrow_copy_constructible_v<T> and
            is_nothrow_default_constructible_v<U>) : T {t}, U {} {}
    explicit constexpr compressor(T &&t) noexcept(is_nothrow_move_constructible_v<T> and
            is_nothrow_default_constructible_v<U>) : T {ds::move(t)}, U {} {}
    explicit constexpr compressor(const U &u) noexcept(is_nothrow_default_constructible_v<T> and
            is_nothrow_copy_constructible_v<U>) : T {}, U {u} {}
    explicit constexpr compressor(U &&u) noexcept(is_nothrow_default_constructible_v<T> and
            is_nothrow_move_constructible_v<U>) : T {}, U {ds::move(u)} {}
    template <typename ConvertibleToT, typename ConvertibleToU>
    constexpr compressor(ConvertibleToT &&t, ConvertibleToU &&u) noexcept(
            is_nothrow_constructible_v<T, ConvertibleToT &&> and is_nothrow_constructible_v<U, ConvertibleToU &&>) :
            T {ds::forward<ConvertibleToT>(t)}, U {ds::forward<ConvertibleToU>(u)} {}
public:
    constexpr T &first() noexcept {
        return *this;
    }
    constexpr const T &first() const noexcept {
        return *this;
    }
    constexpr U &second() noexcept {
        return *this;
    }
    constexpr const U &second() const noexcept {
        return *this;
    }
};
__DATA_STRUCTURE_END(compressor for container)

__DATA_STRUCTURE_START(tools for skip list)
struct skip_list_default_probability {
    consteval float operator()() const noexcept {
        return 0.5f;
    }
};
struct skip_list_default_random_engine {
    float operator()() const noexcept {
        static std::random_device d {};
        static std::default_random_engine e {d()};
        static std::uniform_real_distribution u(0.0f, 1.0f);
        return u(e);
    }
};
__DATA_STRUCTURE_END(tools for skip list)

}       // namespace data_structure::__data_structure_auxiliary
__DATA_STRUCTURE_END(inner tools for data structure library)

#endif //DATA_STRUCTURE_UTILITY_HPP