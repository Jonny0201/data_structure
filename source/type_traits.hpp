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

#ifndef DATA_STRUCTURE_TYPE_TRAITS_HPP
#define DATA_STRUCTURE_TYPE_TRAITS_HPP

#include "__config.hpp"

namespace data_structure {

__DATA_STRUCTURE_START(constant)
template <typename T, T Value>
struct constant {
    using value_type = T;
    using type = constant;
    static constexpr auto value {Value};
    constexpr value_type operator()() const noexcept {
        return this->value;
    }
    constexpr operator value_type() const noexcept {
        return this->value;
    }
};

template <bool Value>
using bool_constant = constant<bool, Value>;
using true_type = bool_constant<true>;
using false_type = bool_constant<false>;
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(conditional and SFINAE)
template <bool, typename If, typename>
struct conditional {
    using type = If;
};
template <typename If, typename Then>
struct conditional<false, If, Then> {
    using type = Then;
};
template <bool Value, typename If, typename Then>
using conditional_t = typename conditional<Value, If, Then>::type;

template <bool, typename = void>
struct enable_if;
template <typename T>
struct enable_if<true, T> {
    using type = T;
};
template <bool Value, typename T = void>
using enable_if_t = typename enable_if<Value, T>::type;

template <typename ...>
struct make_void {
    using type = void;
};
template <typename ...Ts>
using make_void_t = typename make_void<Ts...>::type;
template <typename ...>
using void_t = void;

template <typename T>
struct type_identity {
    using type = T;
};
template <typename T>
using type_identity_t = typename type_identity<T>::type;
template <typename T>
using type_holder = type_identity<T>;
template <typename T>
using type_holder_t = typename type_holder<T>::type;

template <typename ...>
struct make_true_type : true_type {};
template <typename ...Ts>
using make_true_type_t = typename make_true_type<Ts...>::type;

template <typename ...>
struct make_false_type : false_type {};
template <typename ...Ts>
using make_false_type_t = typename make_false_type<Ts...>::type;

template <typename ...>
inline constexpr auto make_true {true};

template <typename ...>
inline constexpr auto make_false {false};

template <typename ...Args>
struct type_container;
template <>
struct type_container<> {
    using type = type_container<>;
    using next = type_container<>;
};
template <typename T>
struct type_container<T> {
    using type = T;
    using next = type_container<>;
};
template <typename T, typename ...Args>
struct type_container<T, Args...> {
    using type = T;
    using next = type_container<Args...>;
};

template <void () = [] {}>
struct unique_type {};
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(functions)
namespace __data_structure_auxiliary {
template <typename T>
static constexpr T &&declval_auxiliary(int) noexcept;
template <typename T>
static constexpr T declval_auxiliary(...) noexcept;
}
template <typename T>
consteval decltype(__dsa::declval_auxiliary<T>(0)) declval() noexcept;

template <typename S, typename M>
consteval bool is_pointer_interconvertible_with_class(M S::*) noexcept;

template <typename S1, typename S2, typename M1, typename M2>
consteval bool is_corresponding_member(M1 S1::*, M2 S2::*) noexcept;

constexpr bool is_constant_evaluated() noexcept {
    if consteval {
        return true;
    }
    return false;
}

template <typename T>
consteval bool is_within_lifetime(const T *) noexcept;
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(add something)
namespace __data_structure_auxiliary {
template <typename, typename T>
struct select_second {
    using type = T;
};
template <typename T, typename U>
using select_second_t = typename select_second<T, U>::type;

template <typename T>
static constexpr select_second_t<T &, true_type> test_lvalue_reference(int) noexcept;
template <typename T>
static constexpr false_type test_lvalue_reference(...) noexcept;
template <typename T, bool = decltype(test_lvalue_reference<T>(0))::value>
struct add_lvalue_reference_auxiliary {
    using type = T &;
};
template <typename T>
struct add_lvalue_reference_auxiliary<T, false> {
    using type = T;
};
template <typename T, bool = decltype(test_lvalue_reference<T>(0))::value>
struct add_rvalue_reference_auxiliary {
    using type = T &&;
};
template <typename T>
struct add_rvalue_reference_auxiliary<T, false> {
    using type = T;
};
}
template <typename T>
struct add_lvalue_reference : __dsa::add_lvalue_reference_auxiliary<T> {};
template <typename T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;
template <typename T>
struct add_rvalue_reference : __dsa::add_rvalue_reference_auxiliary<T> {};
template <typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

template <typename> struct is_void;
template <typename> struct remove_reference;
namespace __data_structure_auxiliary {
template <typename T, bool = decltype(__dsa::test_lvalue_reference<T>(0))::value or is_void<T>::value>
struct add_pointer_auxiliary {
    using type = typename remove_reference<T>::type *;
};
template <typename T>
struct add_pointer_auxiliary<T, false> {
    using type = T;
};
}
template <typename T>
struct add_pointer : __dsa::add_pointer_auxiliary<T> {};
template <typename T>
using add_pointer_t = typename add_pointer<T>::type;

template <typename T>
struct add_const {
    using type = const T;
};
template <typename T>
using add_const_t = typename add_const<T>::type;
template <typename T>
struct add_volatile {
    using type = volatile T;
};
template <typename T>
using add_volatile_t = typename add_volatile<T>::type;
template <typename T>
struct add_cv : add_const<add_volatile_t<T>> {};
template <typename T>
using add_cv_t = typename add_cv<T>::type;

template <typename T>
struct add_const_reference : add_lvalue_reference<add_const_t<
        typename remove_reference<T>::type>> {};
template <typename T>
using add_const_reference_t = typename add_const_reference<T>::type;
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(remove something)
template <typename T>
struct remove_lvalue_reference {
    using type = T;
};
template <typename T>
struct remove_lvalue_reference<T &> {
    using type = T;
};
template <typename T>
using remove_lvalue_reference_t = typename remove_lvalue_reference<T>::type;
template <typename T>
struct remove_rvalue_reference {
    using type = T;
};
template <typename T>
struct remove_rvalue_reference<T &&> {
    using type = T;
};
template <typename T>
using remove_rvalue_reference_t = typename remove_rvalue_reference<T>::type;
template <typename T>
struct remove_reference {
    using type = T;
};
template <typename T>
struct remove_reference<T &> {
    using type = T;
};
template <typename T>
struct remove_reference<T &&> {
    using type = T;
};
template <typename T>
using remove_reference_t = typename remove_reference<T>::type;

template <typename T>
struct remove_pointer {
    using type = T;
};
template <typename T>
struct remove_pointer<T *> {
    using type = T;
};
template <typename T>
struct remove_pointer<T *const> {
    using type = T;
};
template <typename T>
struct remove_pointer<T *volatile> {
    using type = T;
};
template <typename T>
struct remove_pointer<T *const volatile> {
    using type = T;
};
template <typename T>
using remove_pointer_t = typename remove_pointer<T>::type;

template <typename T>
struct remove_const {
    using type = T;
};
template <typename T>
struct remove_const<const T> {
    using type = T;
};
template <typename T>
using remove_const_t = typename remove_const<T>::type;
template <typename T>
struct remove_volatile {
    using type = T;
};
template <typename T>
struct remove_volatile<volatile T> {
    using type = T;
};
template <typename T>
using remove_volatile_t = typename remove_volatile<T>::type;

template <typename T>
struct remove_cv : remove_const<remove_volatile_t<T>> {};
template <typename T>
using remove_cv_t = typename remove_cv<T>::type;

template <typename> struct is_reference;
template <typename> struct is_const;
template <typename T>
struct remove_const_reference : conditional_t<
        is_reference<T>::value,
        type_identity<conditional_t<
                is_const<remove_reference_t<T>>::value,
                remove_const_t<remove_reference_t<T>>,
                T>>,
        type_identity<T>> {};
template <typename T>
using remove_const_reference_t = typename remove_const_reference<T>::type;

template <typename T>
struct remove_cvref : remove_cv<remove_reference_t<T>> {};
template <typename T>
using remove_cvref_t = typename remove_cvref<T>::type;

template <typename T>
struct remove_extent {
    using type = T;
};
template <typename T>
struct remove_extent<T []> {
    using type = T;
};
template <typename T, size_t N>
struct remove_extent<T [N]> {
    using type = T;
};
template <typename T>
using remove_extent_t = typename remove_extent<T>::type;

template <typename T>
struct remove_extents {
    using type = T;
};
template <typename T>
using remove_extents_t = typename remove_extents<T>::type;
template <typename T>
struct remove_extents<T []> {
    using type = remove_extents_t<T>;
};
template <typename T, size_t N>
struct remove_extents<T [N]> {
    using type = remove_extents_t<T>;
};
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(is something)
template <typename, typename>
struct is_same : false_type {};
template <typename T>
struct is_same<T, T> : true_type {};
template <typename T, typename U>
inline constexpr auto is_same_v = is_same<T, U>::value;

template <typename T>
struct is_void : is_same<void, remove_cv_t<T>> {};
template <typename T>
inline constexpr auto is_void_v {is_void<T>::value};

template <typename T>
struct is_null_pointer : is_same<decltype(nullptr), remove_cv_t<T>> {};
template <typename T>
inline constexpr auto is_null_pointer_v {is_null_pointer<T>::value};

template <typename T>
struct is_const : false_type {};
template <typename T>
struct is_const<const T> : true_type {};
template <typename T>
inline constexpr auto is_const_v {is_const<T>::value};

template <typename T>
struct is_volatile : false_type {};
template <typename T>
struct is_volatile<volatile T> : true_type {};
template <typename T>
inline constexpr auto is_volatile_v {is_volatile<T>::value};

template <typename T>
struct is_cv : false_type {};
template <typename T>
struct is_cv<const volatile T> : true_type {};
template <typename T>
inline constexpr auto is_cv_v {is_cv<T>::value};

namespace __data_structure_auxiliary {
template <typename>
struct is_integral_auxiliary : false_type {};
template <>
struct is_integral_auxiliary<bool> : true_type {};
template <>
struct is_integral_auxiliary<char> : true_type {};
template <>
struct is_integral_auxiliary<signed char> : true_type {};
template <>
struct is_integral_auxiliary<unsigned char> : true_type {};
template <>
struct is_integral_auxiliary<char8_t> : true_type {};
template <>
struct is_integral_auxiliary<char16_t> : true_type {};
template <>
struct is_integral_auxiliary<char32_t> : true_type {};
template <>
struct is_integral_auxiliary<wchar_t> : true_type {};
template <>
struct is_integral_auxiliary<short> : true_type {};
template <>
struct is_integral_auxiliary<unsigned short> : true_type {};
template <>
struct is_integral_auxiliary<int> : true_type {};
template <>
struct is_integral_auxiliary<unsigned int> : true_type {};
template <>
struct is_integral_auxiliary<long> : true_type {};
template <>
struct is_integral_auxiliary<unsigned long> : true_type {};
template <>
struct is_integral_auxiliary<long long> : true_type {};
template <>
struct is_integral_auxiliary<unsigned long long> : true_type {};
template <>
struct is_integral_auxiliary<__int128_t> : true_type {};
template <>
struct is_integral_auxiliary<__uint128_t> : true_type {};
}
template <typename T>
struct is_integral : __dsa::is_integral_auxiliary<remove_cv_t<T>> {};
template <typename T>
inline constexpr auto is_integral_v {is_integral<T>::value};

namespace __data_structure_auxiliary {
template <typename>
struct is_floating_point_auxiliary : false_type {};
template <>
struct is_floating_point_auxiliary<float> : true_type {};
template <>
struct is_floating_point_auxiliary<double> : true_type {};
template <>
struct is_floating_point_auxiliary<long double> : true_type {};
}
template <typename T>
struct is_floating_point : __dsa::is_floating_point_auxiliary<remove_cv_t<T>> {};
template <typename T>
inline constexpr auto is_floating_point_v {is_floating_point<T>::value};

namespace __data_structure_auxiliary {
template <typename T, typename = void>
struct is_signed_auxiliary : false_type {};
template <typename T>
struct is_signed_auxiliary<T, make_void_t<decltype(static_cast<T>(-1) < static_cast<T>(0))>> :
        conditional_t<static_cast<T>(-1) < static_cast<T>(0), true_type, false_type> {};
}
template <typename T>
struct is_signed : __dsa::is_signed_auxiliary<remove_cv_t<T>> {};
template <typename T>
inline constexpr auto is_signed_v {is_signed<T>::value};

namespace __data_structure_auxiliary {
template <typename T, typename = void>
struct is_unsigned_auxiliary : false_type {};
template <typename T>
struct is_unsigned_auxiliary<T, make_void_t<decltype(static_cast<T>(0) < static_cast<T>(-1))>> :
        conditional_t<static_cast<T>(0) < static_cast<T>(-1), true_type, false_type> {};
}
template <typename T>
struct is_unsigned : __dsa::is_unsigned_auxiliary<remove_cv_t<T>> {};
template <typename T>
inline constexpr auto is_unsigned_v {is_unsigned<T>::value};

namespace __data_structure_auxiliary {
template <typename>
struct is_character_auxiliary : false_type {};
template <>
struct is_character_auxiliary<char> : true_type {};
template <>
struct is_character_auxiliary<signed char> : true_type {};
template <>
struct is_character_auxiliary<unsigned char> : true_type {};
template <>
struct is_character_auxiliary<char8_t> : true_type {};
template <>
struct is_character_auxiliary<char16_t> : true_type {};
template <>
struct is_character_auxiliary<char32_t> : true_type {};
template <>
struct is_character_auxiliary<wchar_t> : true_type {};
}
template <typename T>
struct is_character : __dsa::is_character_auxiliary<remove_cv_t<T>> {};
template <typename T>
inline constexpr auto is_character_v {is_character<T>::value};

template <typename>
struct is_array : false_type {};
template <typename T>
struct is_array<T []> : true_type {};
template <typename T, size_t N>
struct is_array<T [N]> : true_type {};
template <typename T>
inline constexpr auto is_array_v {is_array<T>::value};

template <typename>
struct is_unbounded_array : false_type {};
template <typename T>
struct is_unbounded_array<T []> : true_type {};
template <typename T>
inline constexpr auto is_unbounded_array_v {is_unbounded_array<T>::value};

template <typename>
struct is_bounded_array : false_type {};
template <typename T, size_t N>
struct is_bounded_array<T [N]> : true_type {};
template <typename T>
inline constexpr auto is_bounded_array_v {is_bounded_array<T>::value};

template <typename T>
struct is_enum : bool_constant<__is_enum(T)> {};
template <typename T>
inline constexpr auto is_enum_v {is_enum<T>::value};

template <typename T>
struct is_union : bool_constant<__is_union(T)> {};
template <typename T>
inline constexpr auto is_union_v {is_union<T>::value};

template <typename T>
struct is_class : bool_constant<__is_class(T)> {};
template <typename T>
inline constexpr auto is_class_v {is_class<T>::value};

template <typename>
struct is_function : false_type {};
template <typename R, typename ...Args>
struct is_function<R (Args...)> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args..., ...)> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args...) const> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args...) volatile> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args...) const volatile> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args..., ...) const> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args..., ...) volatile> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args..., ...) const volatile> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args...) &> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args...) const &> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args...) volatile &> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args...) const volatile &> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args..., ...) &> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args..., ...) const &> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args..., ...) volatile &> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args..., ...) const volatile &> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args...) &&> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args...) const &&> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args...) volatile &&> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args...) const volatile &&> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args..., ...) &&> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args..., ...) const &&> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args..., ...) volatile &&> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args..., ...) const volatile &&> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args...) noexcept> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args..., ...) noexcept> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args...) const noexcept> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args...) volatile noexcept> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args...) const volatile noexcept> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args..., ...) const noexcept> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args..., ...) volatile noexcept> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args..., ...) const volatile noexcept> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args...) & noexcept> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args...) const & noexcept> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args...) volatile & noexcept> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args...) const volatile & noexcept> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args..., ...) & noexcept> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args..., ...) const & noexcept> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args..., ...) volatile & noexcept> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args..., ...) const volatile & noexcept> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args...) && noexcept> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args...) const && noexcept> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args...) volatile && noexcept> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args...) const volatile && noexcept> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args..., ...) && noexcept> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args..., ...) const && noexcept> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args..., ...) volatile && noexcept> : true_type {};
template <typename R, typename ...Args>
struct is_function<R (Args..., ...) const volatile && noexcept> : true_type {};
template <typename T>
inline constexpr auto is_function_v {is_function<T>::value};

namespace __data_structure_auxiliary {
template <typename T>
struct is_pointer_auxiliary : false_type {};
template <typename T>
struct is_pointer_auxiliary<T *> : true_type {};
}
template <typename T>
struct is_pointer : __dsa::is_pointer_auxiliary<remove_cv_t<T>> {};
template <typename T>
inline constexpr auto is_pointer_v {is_pointer<T>::value};

namespace __data_structure_auxiliary {
template <typename T>
struct is_member_pointer_auxiliary : false_type {};
template <typename T, typename Class>
struct is_member_pointer_auxiliary<T Class::*> : true_type {};
}
template <typename T>
struct is_member_pointer : __dsa::is_member_pointer_auxiliary<remove_cv_t<T>> {};
template <typename T>
inline constexpr auto is_member_pointer_v {is_member_pointer<T>::value};

namespace __data_structure_auxiliary {
template <typename T>
struct is_member_function_pointer_auxiliary : false_type {};
template <typename F, typename Class>
struct is_member_function_pointer_auxiliary<F Class::*> : is_function<F> {};
}
template <typename T>
struct is_member_function_pointer : __dsa::is_member_function_pointer_auxiliary<remove_cv_t<T>> {};
template <typename T>
inline constexpr auto is_member_function_pointer_v {is_member_function_pointer<T>::value};

template <typename T>
struct is_member_object_pointer : bool_constant<is_member_pointer_v<T> and not is_member_function_pointer_v<T>> {};
template <typename T>
inline constexpr auto is_member_object_pointer_v {is_member_object_pointer<T>::value};

template <typename T>
struct is_function_pointer : bool_constant<is_pointer_v<T> and
        (is_function_v<remove_pointer_t<T>> or is_void_v<remove_pointer_t<T>>)> {};
template <typename T>
inline constexpr auto is_function_pointer_v {is_function_pointer<T>::value};

template <typename T>
struct is_lvalue_reference : false_type {};
template <typename T>
struct is_lvalue_reference<T &> : true_type {};
template <typename T>
inline constexpr auto is_lvalue_reference_v {is_lvalue_reference<T>::value};

template <typename T>
struct is_rvalue_reference : false_type {};
template <typename T>
struct is_rvalue_reference<T &&> : true_type {};
template <typename T>
inline constexpr auto is_rvalue_reference_v {is_rvalue_reference<T>::value};

template <typename T>
struct is_reference : false_type {};
template <typename T>
struct is_reference<T &> : true_type {};
template <typename T>
struct is_reference<T &&> : true_type {};
template <typename T>
inline constexpr auto is_reference_v {is_reference<T>::value};

template <typename T>
struct is_const_reference : bool_constant<is_lvalue_reference_v<T> and
        is_const_v<remove_lvalue_reference_t<T>>> {};
template <typename T>
inline constexpr auto is_const_reference_v {is_const_reference<T>::value};

template <typename>
struct is_type : true_type {};
template <typename T>
inline constexpr auto is_type_v {is_type<T>::value};

namespace __data_structure_auxiliary {
template <typename T, typename = void>
struct is_complete_auxiliary : false_type {};
template <typename T>
struct is_complete_auxiliary<T, void_t<decltype(sizeof(T))>> :
        conditional_t<(sizeof(T) > 0), true_type, false_type> {};
}
template <typename T>
struct is_complete : __dsa::is_complete_auxiliary<T> {};
template <typename T>
inline constexpr auto is_complete_v {is_complete<T>::value};

template <typename T>
struct [[deprecated]] is_pod : bool_constant<__is_pod(T)> {};
template <typename T>
[[deprecated]] inline constexpr auto is_pod_v {is_pod<T>::value};

template <typename T>
struct is_empty : bool_constant<__is_empty(T)> {};
template <typename T>
inline constexpr auto is_empty_v {is_empty<T>::value};

template <typename T>
struct [[deprecated]] is_literal_type : bool_constant<__is_literal_type(T)> {};
template <typename T>
[[deprecated]] inline constexpr auto is_literal_type_v {is_literal_type<T>::value};

template <typename T>
struct is_standard_layout : bool_constant<__is_standard_layout(T)> {};
template <typename T>
inline constexpr auto is_standard_layout_v {is_standard_layout<T>::value};

template <typename T>
struct is_polymorphic : bool_constant<__is_polymorphic(T)> {};
template <typename T>
inline constexpr auto is_polymorphic_v {is_polymorphic<T>::value};

template <typename T>
struct is_abstract : bool_constant<__is_abstract(T)> {};
template <typename T>
inline constexpr auto is_abstract_v {is_abstract<T>::value};

template <typename Base, typename Derived>
struct is_base_of : bool_constant<__is_base_of(Base, Derived)> {};
template <typename Base, typename Derived>
inline constexpr auto is_base_of_v {is_base_of<Base, Derived>::value};

template <typename T>
struct is_final : bool_constant<__is_final(T)> {};
template <typename T>
inline constexpr auto is_final_v {is_final<T>::value};

template <typename T>
struct is_aggregate : bool_constant<__is_aggregate(T)> {};
template <typename T>
inline constexpr auto is_aggregate_v {is_aggregate<T>::value};

template <typename T>
struct is_arithmetic : bool_constant<is_integral_v<T> or is_floating_point_v<T>> {};
template <typename T>
inline constexpr auto is_arithmetic_v {is_arithmetic<T>::value};

template <typename T>
struct is_fundamental : bool_constant<is_arithmetic_v<T> or is_void_v<T> or
        is_null_pointer_v<remove_cv_t<T>>> {};
template <typename T>
inline constexpr auto is_fundamental_v {is_fundamental<T>::value};

template <typename T>
struct is_scalar : bool_constant<is_arithmetic_v<T> or is_enum_v<T> or is_pointer_v<T> or
        is_member_pointer_v<T> or is_null_pointer_v<T>> {};
template <typename T>
inline constexpr auto is_scalar_v {is_scalar<T>::value};

template <typename T>
struct is_compound : bool_constant<not is_fundamental_v<T>> {};
template <typename T>
inline constexpr auto is_compound_v {is_compound<T>::value};

template <typename T>
struct is_object : bool_constant<is_scalar_v<T> or is_array_v<T> or is_union_v<T> or is_class_v<T>> {};
template <typename T>
inline constexpr auto is_object_v {is_object<T>::value};

template <typename T>
struct is_trivial : bool_constant<__is_trivial(T)> {};
template <typename T>
inline constexpr auto is_trivial_v {is_trivial<T>::value};

template <typename T>
struct is_trivially_copyable : bool_constant<__is_trivially_copyable(T)> {};
template <typename T>
inline constexpr auto is_trivially_copyable_v {is_trivially_copyable<T>::value};

template <typename T, typename ...Args>
struct is_trivially_constructible : bool_constant<__is_trivially_constructible(T, Args...)> {};
template <typename T, typename ...Args>
inline constexpr auto is_trivially_constructible_v {is_trivially_constructible<T, Args...>::value};

template <typename T>
struct is_trivially_default_constructible : is_trivially_constructible<T> {};
template <typename T>
inline constexpr auto is_trivially_default_constructible_v {is_trivially_default_constructible<T>::value};

template <typename T>
struct is_trivially_copy_constructible : is_trivially_constructible<T, add_lvalue_reference_t<const T>> {};
template <typename T>
inline constexpr auto is_trivially_copy_constructible_v {is_trivially_copy_constructible<T>::value};

template <typename T>
struct is_trivially_move_constructible : is_trivially_constructible<T, add_rvalue_reference_t<T>> {};
template <typename T>
inline constexpr auto is_trivially_move_constructible_v {is_trivially_move_constructible<T>::value};

template <typename LHS, typename RHS = LHS>
struct is_trivially_assignable : bool_constant<__is_trivially_assignable(LHS, RHS)> {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_trivially_assignable_v {is_trivially_assignable<LHS, RHS>::value};

template <typename T>
struct is_trivially_copy_assignable :
        is_trivially_assignable<add_lvalue_reference_t<T>, add_lvalue_reference_t<const T>> {};
template <typename T>
inline constexpr auto is_trivially_copy_assignable_v {is_trivially_copy_assignable<T>::value};

template <typename T>
struct is_trivially_move_assignable : is_trivially_assignable<add_lvalue_reference_t<T>, add_rvalue_reference_t<T>> {};
template <typename T>
inline constexpr auto is_trivially_move_assignable_v {is_trivially_move_assignable<T>::value};

template <typename T>
struct is_trivially_destructible : bool_constant<__is_trivially_destructible(T)> {};
template <typename T>
inline constexpr auto is_trivially_destructible_v {is_trivially_destructible<T>::value};

template <typename T, typename ...Args>
struct is_constructible : bool_constant<__is_constructible(T, Args...)> {};
template <typename T, typename ...Args>
inline constexpr auto is_constructible_v {is_constructible<T, Args...>::value};

template <typename T>
struct is_default_constructible : is_constructible<T> {};
template <typename T>
inline constexpr auto is_default_constructible_v {is_default_constructible<T>::value};

template <typename T>
struct is_copy_constructible : is_constructible<T, add_const_reference_t<T>> {};
template <typename T>
inline constexpr auto is_copy_constructible_v {is_copy_constructible<T>::value};

template <typename T>
struct is_move_constructible : is_constructible<T, add_rvalue_reference_t<T>> {};
template <typename T>
inline constexpr auto is_move_constructible_v {is_move_constructible<T>::value};

namespace __data_structure_auxiliary {
template <typename T, typename ...Args>
select_second_t<decltype(T {declval<Args>()...}), true_type> test_list_constructible(int) noexcept;
template <typename ...>
false_type test_list_constructible(...) noexcept;
}
template <typename T, typename ...Args>
struct is_list_constructible : decltype(__dsa::test_list_constructible<T, Args...>(0)) {};
template <typename T, typename ...Args>
inline constexpr auto is_list_constructible_v {is_list_constructible<T, Args...>::value};

template <typename LHS, typename RHS = LHS>
struct is_assignable : bool_constant<__is_assignable(LHS, RHS)> {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_assignable_v {is_assignable<LHS, RHS>::value};

template <typename T>
struct is_copy_assignable : is_assignable<add_lvalue_reference_t<T>, add_lvalue_reference_t<const T>> {};
template <typename T>
inline constexpr auto is_copy_assignable_v {is_copy_assignable<T>::value};

template <typename T>
struct is_move_assignable : is_assignable<add_lvalue_reference_t<T>, add_rvalue_reference_t<T>> {};
template <typename T>
inline constexpr auto is_move_assignable_v {is_move_assignable<T>::value};

namespace __data_structure_auxiliary {
template <typename T>
select_second_t<decltype(declval<T>().~T()), true_type> test_destructible(int) noexcept;
template <typename>
false_type test_destructible(...) noexcept;
}
template <typename T>
struct is_destructible : conditional_t<
        not is_function_v<T> and not is_unbounded_array_v<T> and not is_same_v<void, T>,
        conditional_t<is_reference_v<T>, true_type, conditional_t<
                is_complete_v<T>, decltype(__dsa::test_destructible<remove_extents_t<T>>(0)), false_type>
        >, false_type> {};
template <typename T>
inline constexpr auto is_destructible_v {is_destructible<T>::value};

template <typename From, typename To>
struct is_convertible : bool_constant<__is_convertible_to(From, To) and not is_abstract_v<To>> {};
template <typename From, typename To>
inline constexpr auto is_convertible_v {is_convertible<From, To>::value};

__DATA_STRUCTURE_START(forward declaration for ds::swap)
template <typename> struct is_nothrow_copy_constructible;
template <typename> struct is_nothrow_copy_assignable;
template <typename> struct is_nothrow_move_constructible;
template <typename> struct is_nothrow_move_assignable;
template <typename T>
constexpr enable_if_t<(is_move_constructible_v<T> and is_move_assignable_v<T>) or
        (is_copy_constructible_v<T> and is_copy_assignable_v<T>)>
swap(T &lhs, T &rhs) noexcept((is_nothrow_move_constructible<T>::value and is_nothrow_move_assignable<T>::value) or
        (is_nothrow_copy_constructible<T>::value and is_nothrow_copy_assignable<T>::value));
template <typename T, size_t N>
constexpr enable_if_t<(is_move_constructible_v<T> and is_move_assignable_v<T>) or
        (is_copy_constructible_v<T> and is_copy_assignable_v<T>)>
swap(T (&lhs)[N], T (&rhs)[N]) noexcept((is_move_constructible_v<T> and is_move_assignable_v<T>) or
        (is_copy_constructible_v<T> and is_copy_assignable_v<T>));
__DATA_STRUCTURE_END
namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(swap(declval<LHS>(), declval<RHS>())), true_type> test_swappable(int) noexcept;
template <typename, typename>
false_type test_swappable(...) noexcept;
}
template <typename LHS, typename RHS>
struct is_swappable_with : conditional_t<is_void_v<LHS> or is_void_v<RHS>, false_type,
        conditional_t<is_same_v<decltype(__dsa::test_swappable<LHS, RHS>(0)),
                decltype(__dsa::test_swappable<RHS, LHS>(0))>,
        decltype(__dsa::test_swappable<LHS, RHS>(0)), false_type>> {};
template <typename LHS, typename RHS>
inline constexpr auto is_swappable_with_v {is_swappable_with<LHS, RHS>::value};

template <typename T>
struct is_swappable : conditional_t<decltype(__dsa::test_lvalue_reference<T>(0))::value,
        is_swappable_with<add_lvalue_reference_t<T>, add_lvalue_reference_t<T>>, false_type> {};
template <typename T>
inline constexpr auto is_swappable_v {is_swappable<T>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>().swap(declval<RHS>())), true_type> test_member_function_swap(int) noexcept;
template <typename, typename>
false_type test_member_function_swap(...) noexcept;
}
template <typename LHS, typename RHS>
struct is_swappable_by_member_function_with : conditional_t<
        is_class_v<remove_reference_t<LHS>> and is_class_v<remove_reference_t<RHS>>,
        conditional_t<is_same_v<decltype(__dsa::test_member_function_swap<LHS, RHS>(0)),
                decltype(__dsa::test_member_function_swap<RHS, LHS>(0))>,
                decltype(__dsa::test_member_function_swap<LHS, RHS>(0)), false_type>, false_type> {};
template <typename LHS, typename RHS>
inline constexpr auto is_swappable_by_member_function_with_v {is_swappable_by_member_function_with<LHS, RHS>::value};

template <typename T>
struct is_swappable_by_member_function : conditional_t<decltype(__dsa::test_lvalue_reference<T>(0))::value,
        is_swappable_by_member_function_with<add_lvalue_reference_t<T>, add_lvalue_reference_t<T>>, false_type> {};
template<typename T>
inline constexpr auto is_swappable_by_member_function_v {is_swappable_by_member_function<T>::value};

namespace __data_structure_auxiliary {
template <typename From, typename To>
select_second_t<decltype(static_cast<To>(declval<From>())), true_type> test_static_cast(int) noexcept;
template <typename, typename>
false_type test_static_cast(...) noexcept;
}
template <typename From, typename To>
struct is_static_castable : decltype(__dsa::test_static_cast<From, To>(0)) {};
template <typename From, typename To>
inline constexpr auto is_static_castable_v {is_static_castable<From, To>::value};

namespace __data_structure_auxiliary {
template <typename From, typename To>
select_second_t<decltype(dynamic_cast<To>(declval<From>())), true_type> test_dynamic_cast(int) noexcept;
template <typename, typename>
false_type test_dynamic_cast(...) noexcept;
}
template <typename From, typename To>
struct is_dynamic_castable : decltype(__dsa::test_dynamic_cast<From, To>(0)) {};
template <typename From, typename To>
inline constexpr auto is_dynamic_castable_v {is_dynamic_castable<From, To>::value};

namespace __data_structure_auxiliary {
template <typename From, typename To>
select_second_t<decltype(const_cast<To>(declval<From>())), true_type> test_const_cast(int) noexcept;
template <typename, typename>
false_type test_const_cast(...) noexcept;
}
template <typename From, typename To>
struct is_const_castable : decltype(__dsa::test_const_cast<From, To>(0)) {};
template <typename From, typename To>
inline constexpr auto is_const_castable_v {is_const_castable<From, To>::value};

namespace __data_structure_auxiliary {
template <typename From, typename To>
select_second_t<decltype(reinterpret_cast<To>(declval<From>())), true_type> test_reinterpret_cast(int) noexcept;
template <typename, typename>
false_type test_reinterpret_cast(...) noexcept;
}
template <typename From, typename To>
struct is_reinterpret_castable : decltype(__dsa::test_reinterpret_cast<From, To>(0)) {};
template <typename From, typename To>
inline constexpr auto is_reinterpret_castable_v {is_reinterpret_castable<From, To>::value};

namespace __data_structure_auxiliary {
template <typename From, typename To>
select_second_t<decltype((To)declval<From>()), true_type> test_c_style_cast(int) noexcept;
template <typename, typename>
false_type test_c_style_cast(...) noexcept;
}
template <typename From, typename To>
struct is_castable : decltype(__dsa::test_c_style_cast<From, To>(0)) {};
template <typename From, typename To>
inline constexpr auto is_castable_v {is_castable<From, To>::value};

template <typename, typename ...> struct invoke_result;
template <typename> struct decay;
namespace __data_structure_auxiliary {
template <typename, typename = void>
struct is_invocable_auxiliary : false_type {};
template <typename Result>
struct is_invocable_auxiliary<Result, void_t<typename Result::type>> : true_type {};
}
template <typename F, typename ...Args>
struct is_invocable : conditional_t<is_function_v<F>,
        __dsa::is_invocable_auxiliary<invoke_result<typename decay<F>::type, Args...>>,
        conditional_t<is_complete_v<F>, __dsa::is_invocable_auxiliary<invoke_result<remove_reference_t<F>, Args...>>,
                false_type>> {};
template <typename F, typename ...Args>
inline constexpr auto is_invocable_v {is_invocable<F, Args...>::value};

template <typename R, typename F, typename ...Args>
struct is_invocable_r : bool_constant<is_invocable_v<F, Args...> and
        is_convertible_v<typename invoke_result<F, Args...>::type, R>> {};
template <typename R, typename F, typename ...Args>
inline constexpr auto is_invocable_r_v {is_invocable_r<R, F, Args...>::value};

template <typename T, typename ...Args>
struct is_nothrow_constructible : bool_constant<__is_nothrow_constructible(T, Args...)> {};
template <typename T, typename ...Args>
inline constexpr auto is_nothrow_constructible_v {is_nothrow_constructible<T, Args...>::value};

template <typename T>
struct is_nothrow_default_constructible : is_nothrow_constructible<T> {};
template <typename T>
inline constexpr auto is_nothrow_default_constructible_v {is_nothrow_default_constructible<T>::value};

template <typename T>
struct is_nothrow_copy_constructible : is_nothrow_constructible<T, add_const_reference_t<T>> {};
template <typename T>
inline constexpr auto is_nothrow_copy_constructible_v {is_nothrow_copy_constructible<T>::value};

template <typename T>
struct is_nothrow_move_constructible : is_nothrow_constructible<T, add_rvalue_reference_t<T>> {};
template <typename T>
inline constexpr auto is_nothrow_move_constructible_v {is_nothrow_move_constructible<T>::value};

namespace __data_structure_auxiliary {
template <typename T, typename ...Args>
select_second_t<decltype(T {declval<Args>()...}), bool_constant<noexcept(T {declval<Args>()...})>>
test_nothrow_list_constructible(int) noexcept;
template <typename, typename ...>
false_type test_nothrow_list_constructible(...) noexcept;
}
template <typename T, typename ...Args>
struct is_nothrow_list_constructible : decltype(__dsa::test_nothrow_list_constructible<T, Args...>(0)) {};
template <typename T, typename ...Args>
inline constexpr auto is_nothrow_list_constructible_v {is_nothrow_list_constructible<T, Args...>::value};

template <typename LHS, typename RHS = LHS>
struct is_nothrow_assignable : bool_constant<__is_nothrow_assignable(LHS, RHS)> {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_nothrow_assignable_v {is_nothrow_assignable<LHS, RHS>::value};

template <typename T>
struct is_nothrow_copy_assignable :
        is_nothrow_assignable<add_lvalue_reference_t<T>, add_const_reference_t<T>> {};
template <typename T>
inline constexpr auto is_nothrow_copy_assignable_v {is_nothrow_copy_assignable<T>::value};

template <typename T>
struct is_nothrow_move_assignable :
        is_nothrow_assignable<add_lvalue_reference_t<T>, add_rvalue_reference_t<T>> {};
template <typename T>
inline constexpr auto is_nothrow_move_assignable_v {is_nothrow_move_assignable<T>::value};

namespace __data_structure_auxiliary {
template <typename T>
select_second_t<decltype(declval<T>().~T()), bool_constant<noexcept(declval<T>().~T())>>
test_nothrow_destructible(int) noexcept;
template <typename>
false_type test_nothrow_destructible(...) noexcept;
}
template <typename T>
struct is_nothrow_destructible : decltype(__dsa::test_nothrow_destructible<T>(0)) {};
template <typename T>
inline constexpr auto is_nothrow_destructible_v {is_nothrow_destructible<T>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS, bool = is_swappable_with_v<LHS, RHS>>
struct is_nothrow_swappable_with_auxiliary : bool_constant<noexcept(swap(declval<LHS>(), declval<RHS>())) and
        noexcept(swap(declval<RHS>(), declval<LHS>()))> {};
template <typename LHS, typename RHS>
struct is_nothrow_swappable_with_auxiliary<LHS, RHS, false> : false_type {};
}
template <typename LHS, typename RHS>
struct is_nothrow_swappable_with : __dsa::is_nothrow_swappable_with_auxiliary<LHS, RHS> {};
template <typename LHS, typename RHS>
inline constexpr auto is_nothrow_swappable_with_v {is_nothrow_swappable_with<LHS, RHS>::value};

template <typename T>
struct is_nothrow_swappable : conditional_t<decltype(__dsa::test_lvalue_reference<T>(0))::value,
        is_nothrow_swappable_with<add_lvalue_reference_t<T>, add_lvalue_reference_t<T>>, false_type> {};
template <typename T>
inline constexpr auto is_nothrow_swappable_v {is_nothrow_swappable<T>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS, bool = is_swappable_by_member_function_with_v<LHS, RHS>>
struct is_nothrow_swappable_by_member_function_with_auxiliary : bool_constant<
        noexcept(declval<LHS>().swap(declval<RHS>())) and noexcept(declval<RHS>().swap(declval<LHS>()))> {};
template <typename LHS, typename RHS>
struct is_nothrow_swappable_by_member_function_with_auxiliary<LHS, RHS, false> : false_type {};
}
template <typename LHS, typename RHS>
struct is_nothrow_swappable_by_member_function_with :
        __dsa::is_nothrow_swappable_by_member_function_with_auxiliary<LHS, RHS> {};
template <typename LHS, typename RHS>
inline constexpr auto is_nothrow_swappable_by_member_function_with_v {
    is_nothrow_swappable_by_member_function_with<LHS, RHS>::value
};

template <typename T>
struct is_nothrow_swappable_by_member_function : conditional_t<decltype(__dsa::test_lvalue_reference<T>(0))::value,
        is_nothrow_swappable_by_member_function_with<add_lvalue_reference_t<T>, add_lvalue_reference_t<T>>,
        false_type> {};
template <typename T>
inline constexpr auto is_nothrow_swappable_by_member_function_v {is_nothrow_swappable_by_member_function<T>::value};

namespace __data_structure_auxiliary {
template <bool, bool, typename ...>
struct result_of_nothrow_auxiliary : false_type {};
}
template <typename Ptr, typename ...Args>
struct is_nothrow_invocable :
        __dsa::result_of_nothrow_auxiliary<is_member_object_pointer_v<remove_reference_t<Ptr>>,
                is_member_function_pointer_v<remove_reference_t<Ptr>>, Ptr, Args...> {};
template <typename Ptr, typename ...Args>
inline constexpr auto is_nothrow_invocable_v {is_nothrow_invocable<Ptr, Args...>::value};

namespace __data_structure_auxiliary {
template <typename T>
void test_convertible(T) noexcept;
template <typename From, typename To>
select_second_t<decltype(test_convertible<To>(declval<From>())),
        bool_constant<noexcept(test_convertible<To>(declval<From>()))>> test_nothrow_convertible(int) noexcept;
template <typename, typename>
false_type test_nothrow_convertible(...) noexcept;
}
template <typename From, typename To>
struct is_nothrow_convertible : conditional_t<is_void_v<From> and is_void_v<To>, true_type,
        bool_constant<is_convertible_v<From, To> and decltype(__dsa::test_nothrow_convertible<From, To>(0))::value>> {};
template <typename From, typename To>
inline constexpr auto is_nothrow_convertible_v {is_nothrow_convertible<From, To>::value};

template <typename R, typename Ptr, typename ...Args>
struct is_nothrow_invocable_r : bool_constant<is_nothrow_invocable_v<Ptr, Args...> and
        is_nothrow_convertible_v<typename invoke_result<Ptr, Args...>::type, R>> {};

namespace __data_structure_auxiliary {
template <typename From, typename To>
select_second_t<decltype(static_cast<To>(declval<From>())), bool_constant<noexcept(static_cast<To>(declval<From>()))>>
test_nothrow_static_castable(int) noexcept;
template <typename, typename>
false_type test_nothrow_static_castable(...) noexcept;
}
template <typename From, typename To>
struct is_nothrow_static_castable : decltype(__dsa::test_nothrow_static_castable<From, To>(0)) {};
template <typename From, typename To>
inline constexpr auto is_nothrow_static_castable_v {is_nothrow_static_castable<From, To>::value};

namespace __data_structure_auxiliary {
template <typename From, typename To>
select_second_t<decltype(dynamic_cast<To>(declval<From>())),
        bool_constant<noexcept(dynamic_cast<To>(declval<From>()))>> test_nothrow_dynamic_castable(int) noexcept;
template <typename, typename>
false_type test_nothrow_dynamic_castable(...) noexcept;
}
template <typename From, typename To>
struct is_nothrow_dynamic_castable : decltype(__dsa::test_nothrow_dynamic_castable<From, To>(0)) {};
template <typename From, typename To>
inline constexpr auto is_nothrow_dynamic_castable_v {is_nothrow_dynamic_castable<From, To>::value};

namespace __data_structure_auxiliary {
template <typename From, typename To>
select_second_t<decltype(const_cast<To>(declval<From>())),
        bool_constant<noexcept(const_cast<To>(declval<From>()))>> test_nothrow_const_castable(int) noexcept;
template <typename, typename>
false_type test_nothrow_const_castable(...) noexcept;
}
template <typename From, typename To>
struct is_nothrow_const_castable : decltype(__dsa::test_nothrow_const_castable<From, To>(0)) {};
template <typename From, typename To>
inline constexpr auto is_nothrow_const_castable_v {is_nothrow_const_castable<From, To>::value};

namespace __data_structure_auxiliary {
template <typename From, typename To>
select_second_t<decltype(reinterpret_cast<To>(declval<From>())),
        bool_constant<noexcept(reinterpret_cast<To>(declval<From>()))>> test_nothrow_reinterpret_castable(int) noexcept;
template <typename, typename>
false_type test_nothrow_reinterpret_castable(...) noexcept;
}
template <typename From, typename To>
struct is_nothrow_reinterpret_castable :
        decltype(__dsa::test_nothrow_reinterpret_castable<From, To>(0)) {};
template <typename From, typename To>
inline constexpr auto is_nothrow_reinterpret_castable_v {is_nothrow_reinterpret_castable<From, To>::value};

namespace __data_structure_auxiliary {
template <typename From, typename To>
select_second_t<decltype((To)declval<From>()), bool_constant<noexcept((To)declval<From>())>>
test_nothrow_castable(int) noexcept;
template <typename, typename>
false_type test_nothrow_castable(...) noexcept;
}
template <typename From, typename To>
struct is_nothrow_castable : decltype(__dsa::test_nothrow_castable<From, To>(0)) {};
template <typename From, typename To>
inline constexpr auto is_nothrow_castable_v {is_nothrow_castable<From, To>::value};

template <typename T>
struct is_stateless : bool_constant<is_trivially_default_constructible_v<T> and
        is_trivially_copy_constructible_v<T> and is_trivially_copy_assignable_v<T> and
        is_trivially_destructible_v<T> and is_empty_v<T>> {};
template <typename T>
inline constexpr auto is_stateless_v {is_stateless<T>::value};

template <typename Base, typename Derived>
struct is_virtual_base_of : bool_constant<is_base_of_v<Base, Derived> and
        is_castable_v<Derived *, Base *> and not is_castable_v<Base *, Derived *>> {};
template <typename Base, typename Derived>
inline constexpr auto is_virtual_base_of_v {is_virtual_base_of<Base, Derived>::value};

namespace __data_structure_auxiliary {
template <typename E, bool = is_enum_v<E>>
struct is_scoped_enum_auxiliary : is_convertible<E, __underlying_type(E)> {};
template <typename T>
struct is_scoped_enum_auxiliary<T, false> : true_type {};
}
template <typename E>
struct is_scoped_enum : bool_constant<not __dsa::is_scoped_enum_auxiliary<E>::value> {};
template <typename E>
inline constexpr auto is_scoped_enum_v {is_scoped_enum<E>::value};

template <typename T>
struct is_implicit_lifetime : bool_constant<is_scalar_v<T> or is_array_v<T> or
        (is_aggregate_v<T> and is_trivially_destructible_v<T>) or ((is_trivially_default_constructible_v<T> or
                        is_trivially_copy_constructible_v<T> or is_trivially_move_constructible_v<T>) and
                is_trivially_destructible_v<T>)> {};
template <typename T>
inline constexpr auto is_implicit_lifetime_v {is_implicit_lifetime<T>::value};

template <typename T>
struct is_layout_compatible;

template <typename Base, typename Derived>
struct is_pointer_interconvertible_base_of;

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() + declval<RHS>()), true_type> test_addable(int) noexcept;
template <typename, typename>
false_type test_addable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_addable : decltype(__dsa::test_addable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_addable_v {is_addable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() + declval<RHS>()), bool_constant<noexcept(declval<LHS>() + declval<RHS>())>>
test_nothrow_addable(int) noexcept;
template <typename, typename>
false_type test_nothrow_addable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_nothrow_addable : decltype(__dsa::test_nothrow_addable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_nothrow_addable_v {is_nothrow_addable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename T>
select_second_t<decltype(+declval<T>()), true_type> test_positivible(int) noexcept;
template <typename>
false_type test_positivible(...) noexcept;
}
template <typename T>
struct is_positivible : decltype(__dsa::test_positivible<T>(0)) {};
template <typename T>
inline constexpr auto is_positivible_v {is_positivible<T>::value};

namespace __data_structure_auxiliary {
template <typename T>
select_second_t<decltype(+declval<T>()), bool_constant<noexcept(+declval<T>())>> test_nothrow_positivible(int) noexcept;
template <typename>
false_type test_nothrow_positivible(...) noexcept;
}
template <typename T>
struct is_nothrow_positivible : decltype(__dsa::test_nothrow_positivible<T>(0)) {};
template <typename T>
inline constexpr auto is_nothrow_positivible_v {is_nothrow_positivible<T>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() - declval<RHS>()), true_type> test_subtractable(int) noexcept;
template <typename, typename>
false_type test_subtractable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_subtractable : decltype(__dsa::test_subtractable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_subtractable_v {is_subtractable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() - declval<RHS>()), bool_constant<noexcept(declval<LHS>() - declval<RHS>())>>
test_nothrow_subtractable(int) noexcept;
template <typename, typename>
false_type test_nothrow_subtractable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_nothrow_subtractable : decltype(__dsa::test_nothrow_subtractable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_nothrow_subtractable_v {is_nothrow_subtractable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename T>
select_second_t<decltype(-declval<T>()), true_type> test_negtivible(int) noexcept;
template <typename>
false_type test_negtivible(...) noexcept;
}
template <typename T>
struct is_negtivible : decltype(__dsa::test_negtivible<T>(0)) {};
template <typename T>
inline constexpr auto is_negtivible_v {is_negtivible<T>::value};

namespace __data_structure_auxiliary {
template <typename T>
select_second_t<decltype(-declval<T>()), bool_constant<noexcept(-declval<T>())>> test_nothrow_negtivible(int) noexcept;
template <typename>
false_type test_nothrow_negtivible(...) noexcept;
}
template <typename T>
struct is_nothrow_negtivible : decltype(__dsa::test_nothrow_negtivible<T>(0)) {};
template <typename T>
inline constexpr auto is_nothrow_negtivible_v {is_nothrow_negtivible<T>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() * declval<RHS>()), true_type> test_multipliable(int) noexcept;
template <typename, typename>
false_type test_multipliable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_multipliable : decltype(__dsa::test_multipliable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_multipliable_v {is_multipliable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() * declval<RHS>()), bool_constant<noexcept(declval<LHS>() * declval<RHS>())>>
test_nothrow_multipliable(int) noexcept;
template <typename, typename>
false_type test_nothrow_multipliable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_nothrow_multipliable : decltype(__dsa::test_nothrow_multipliable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_nothrow_multipliable_v {is_nothrow_multipliable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename T>
select_second_t<decltype(*declval<T>()), true_type> test_dereferenceable(int) noexcept;
template <typename>
false_type test_dereferenceable(...) noexcept;
}
template <typename T>
struct is_dereferenceable : decltype(__dsa::test_dereferenceable<T>(0)) {};
template <typename T>
inline constexpr auto is_dereferenceable_v {is_dereferenceable<T>::value};

namespace __data_structure_auxiliary {
template <typename T>
select_second_t<decltype(*declval<T>()), bool_constant<noexcept(*declval<T>())>>
test_nothrow_dereferenceable(int) noexcept;
template <typename>
false_type test_nothrow_dereferenceable(...) noexcept;
}
template <typename T>
struct is_nothrow_dereferenceable : decltype(__dsa::test_nothrow_dereferenceable<T>(0)) {};
template <typename T>
inline constexpr auto is_nothrow_dereferenceable_v {is_nothrow_dereferenceable<T>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() / declval<RHS>()), true_type> test_divisible(int) noexcept;
template <typename, typename>
false_type test_divisible(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_divisible : decltype(__dsa::test_divisible<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_divisible_v {is_divisible<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() / declval<RHS>()), bool_constant<noexcept(declval<LHS>() / declval<RHS>())>>
test_nothrow_divisible(int) noexcept;
template <typename, typename>
false_type test_nothrow_divisible(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_nothrow_divisible : decltype(__dsa::test_nothrow_divisible<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_nothrow_divisible_v {is_nothrow_divisible<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() % declval<RHS>()), true_type> test_muldable(int) noexcept;
template <typename, typename>
false_type test_muldable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_muldable : decltype(__dsa::test_muldable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_muldable_v {is_muldable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() % declval<RHS>()), bool_constant<noexcept(declval<LHS>() % declval<RHS>())>>
test_nothrow_muldable(int) noexcept;
template <typename, typename>
false_type test_nothrow_muldable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_nothrow_muldable : decltype(__dsa::test_nothrow_muldable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_nothrow_muldable_v {is_nothrow_muldable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() ^ declval<RHS>()), true_type> test_bitwise_xorable(int) noexcept;
template <typename, typename>
false_type test_bitwise_xorable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_bitwise_xorable : decltype(__dsa::test_bitwise_xorable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_bitwise_xorable_v {is_bitwise_xorable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() ^ declval<RHS>()), bool_constant<noexcept(declval<LHS>() ^ declval<RHS>())>>
test_nothrow_bitwise_xorable(int) noexcept;
template <typename, typename>
false_type test_nothrow_bitwise_xorable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_nothrow_bitwise_xorable : decltype(__dsa::test_nothrow_bitwise_xorable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_nothrow_bitwise_xorable_v {is_nothrow_bitwise_xorable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() | declval<RHS>()), true_type> test_bitwise_orable(int) noexcept;
template <typename, typename>
false_type test_bitwise_orable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_bitwise_orable : decltype(__dsa::test_bitwise_orable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_bitwise_orable_v {is_bitwise_orable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() | declval<RHS>()), bool_constant<noexcept(declval<LHS>() | declval<RHS>())>>
test_nothrow_bitwise_orable(int) noexcept;
template <typename, typename>
false_type test_nothrow_bitwise_orable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_nothrow_bitwise_orable : decltype(__dsa::test_nothrow_bitwise_orable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_nothrow_bitwise_orable_v {is_nothrow_bitwise_orable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename T>
select_second_t<decltype(~declval<T>()), true_type> test_bitwise_notable(int) noexcept;
template <typename>
false_type test_bitwise_notable(...) noexcept;
}
template <typename T>
struct is_bitwise_notable : decltype(__dsa::test_bitwise_notable<T>(0)) {};
template <typename T>
inline constexpr auto is_bitwise_notable_v {is_bitwise_notable<T>::value};

namespace __data_structure_auxiliary {
template <typename T>
select_second_t<decltype(~declval<T>()), bool_constant<noexcept(~declval<T>())>>
test_nothrow_bitwise_notable(int) noexcept;
template <typename>
false_type test_nothrow_bitwise_notable(...) noexcept;
}
template <typename T>
struct is_nothrow_bitwise_notable : decltype(__dsa::test_nothrow_bitwise_notable<T>(0)) {};
template <typename T>
inline constexpr auto is_nothrow_bitwise_notable_v {is_nothrow_bitwise_notable<T>::value};

namespace __data_structure_auxiliary {
template <typename T>
select_second_t<decltype(!declval<T>()), true_type> test_logical_notable(int) noexcept;
template <typename>
false_type test_logical_notable(...) noexcept;
}
template <typename T>
struct is_logical_notable : decltype(__dsa::test_logical_notable<T>(0)) {};
template <typename T>
inline constexpr auto is_logical_notable_v {is_logical_notable<T>::value};

namespace __data_structure_auxiliary {
template <typename T>
select_second_t<decltype(!declval<T>()), bool_constant<noexcept(!declval<T>())>>
test_nothrow_logical_notable(int) noexcept;
template <typename>
false_type test_nothrow_logical_notable(...) noexcept;
}
template <typename T>
struct is_nothrow_logical_notable : decltype(__dsa::test_nothrow_logical_notable<T>(0)) {};
template <typename T>
inline constexpr auto is_nothrow_logical_notable_v {is_nothrow_logical_notable<T>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() < declval<RHS>()), true_type> test_less_comparable(int) noexcept;
template <typename, typename>
false_type test_less_comparable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_less_comparable : decltype(__dsa::test_less_comparable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_less_comparable_v {is_less_comparable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() < declval<RHS>()), bool_constant<noexcept(declval<LHS>() < declval<RHS>())>>
test_nothrow_less_comparable(int) noexcept;
template <typename, typename>
false_type test_nothrow_less_comparable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_nothrow_less_comparable : decltype(__dsa::test_nothrow_less_comparable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_nothrow_less_comparable_v {is_nothrow_less_comparable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() > declval<RHS>()), true_type> test_greater_comparable(int) noexcept;
template <typename, typename>
false_type test_greater_comparable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_greater_comparable : decltype(__dsa::test_greater_comparable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_greater_comparable_v {is_greater_comparable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() > declval<RHS>()), bool_constant<noexcept(declval<LHS>() > declval<RHS>())>>
test_nothrow_greater_comparable(int) noexcept;
template <typename, typename>
false_type test_nothrow_greater_comparable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_nothrow_greater_comparable : decltype(__dsa::test_nothrow_greater_comparable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_nothrow_greater_comparable_v {is_nothrow_greater_comparable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() += declval<RHS>()), true_type> test_addition_assignable(int) noexcept;
template <typename, typename>
false_type test_addition_assignable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_addition_assignable : decltype(__dsa::test_addition_assignable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_addition_assignable_v {is_addition_assignable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() += declval<RHS>()), bool_constant<noexcept(declval<LHS>() += declval<RHS>())>>
test_nothrow_addition_assignable(int) noexcept;
template <typename, typename>
false_type test_nothrow_addition_assignable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_nothrow_addition_assignable : decltype(__dsa::test_nothrow_addition_assignable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_nothrow_addition_assignable_v {is_nothrow_addition_assignable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() -= declval<RHS>()), true_type> test_subtraction_assignable(int) noexcept;
template <typename, typename>
false_type test_subtraction_assignable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_subtraction_assignable : decltype(__dsa::test_subtraction_assignable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_subtraction_assignable_v {is_subtraction_assignable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() -= declval<RHS>()), bool_constant<noexcept(declval<LHS>() -= declval<RHS>())>>
test_nothrow_subtraction_assignable(int) noexcept;
template <typename, typename>
false_type test_nothrow_subtraction_assignable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_nothrow_subtraction_assignable : decltype(__dsa::test_nothrow_subtraction_assignable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_nothrow_subtraction_assignable_v {is_nothrow_subtraction_assignable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() *= declval<RHS>()), true_type> test_multiple_assignable(int) noexcept;
template <typename, typename>
false_type test_multiple_assignable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_multiple_assignable : decltype(__dsa::test_multiple_assignable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_multiple_assignable_v {is_multiple_assignable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() *= declval<RHS>()), bool_constant<noexcept(declval<LHS>() *= declval<RHS>())>>
test_nothrow_multiple_assignable(int) noexcept;
template <typename, typename>
false_type test_nothrow_multiple_assignable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_nothrow_multiple_assignable : decltype(__dsa::test_nothrow_multiple_assignable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_nothrow_multiple_assignable_v {is_nothrow_multiple_assignable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() /= declval<RHS>()), true_type> test_division_assignable(int) noexcept;
template <typename, typename>
false_type test_division_assignable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_division_assignable : decltype(__dsa::test_division_assignable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_division_assignable_v {is_division_assignable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() /= declval<RHS>()), bool_constant<noexcept(declval<LHS>() /= declval<RHS>())>>
test_nothrow_division_assignable(int) noexcept;
template <typename, typename>
false_type test_nothrow_division_assignable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_nothrow_division_assignable : decltype(__dsa::test_nothrow_division_assignable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_nothrow_division_assignable_v {is_nothrow_division_assignable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() %= declval<RHS>()), true_type> test_modulus_assignable(int) noexcept;
template <typename, typename>
false_type test_modulus_assignable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_modulus_assignable : decltype(__dsa::test_modulus_assignable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_modulus_assignable_v {is_modulus_assignable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() %= declval<RHS>()), bool_constant<noexcept(declval<LHS>() %= declval<RHS>())>>
test_nothrow_modulus_assignable(int) noexcept;
template <typename, typename>
false_type test_nothrow_modulus_assignable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_nothrow_modulus_assignable : decltype(__dsa::test_nothrow_modulus_assignable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_nothrow_modulus_assignable_v {is_nothrow_modulus_assignable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() ^= declval<RHS>()), true_type> test_bitwise_xor_assignable(int) noexcept;
template <typename, typename>
false_type test_bitwise_xor_assignable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_bitwise_xor_assignable : decltype(__dsa::test_bitwise_xor_assignable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_bitwise_xor_assignable_v {is_bitwise_xor_assignable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() ^= declval<RHS>()), bool_constant<noexcept(declval<LHS>() ^= declval<RHS>())>>
test_nothrow_bitwise_xor_assignable(int) noexcept;
template <typename, typename>
false_type test_nothrow_bitwise_xor_assignable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_nothrow_bitwise_xor_assignable : decltype(__dsa::test_nothrow_bitwise_xor_assignable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_nothrow_bitwise_xor_assignable_v {is_nothrow_bitwise_xor_assignable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() &= declval<RHS>()), true_type> test_bitwise_and_assignable(int) noexcept;
template <typename, typename>
false_type test_bitwise_and_assignable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_bitwise_and_assignable : decltype(__dsa::test_bitwise_and_assignable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_bitwise_and_assignable_v {is_bitwise_and_assignable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() &= declval<RHS>()), bool_constant<noexcept(declval<LHS>() &= declval<RHS>())>>
test_nothrow_bitwise_and_assignable(int) noexcept;
template <typename, typename>
false_type test_nothrow_bitwise_and_assignable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_nothrow_bitwise_and_assignable : decltype(__dsa::test_nothrow_bitwise_and_assignable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_nothrow_bitwise_and_assignable_v {is_nothrow_bitwise_and_assignable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() |= declval<RHS>()), true_type> test_bitwise_or_assignable(int) noexcept;
template <typename, typename>
false_type test_bitwise_or_assignable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_bitwise_or_assignable : decltype(__dsa::test_bitwise_or_assignable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_bitwise_or_assignable_v {is_bitwise_or_assignable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() |= declval<RHS>()), bool_constant<noexcept(declval<LHS>() |= declval<RHS>())>>
test_nothrow_bitwise_or_assignable(int) noexcept;
template <typename, typename>
false_type test_nothrow_bitwise_or_assignable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_nothrow_bitwise_or_assignable : decltype(__dsa::test_nothrow_bitwise_or_assignable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_nothrow_bitwise_or_assignable_v {is_nothrow_bitwise_or_assignable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() << declval<RHS>()), true_type> test_left_shiftable(int) noexcept;
template <typename, typename>
false_type test_left_shiftable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_left_shiftable : decltype(__dsa::test_left_shiftable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_left_shiftable_v {is_left_shiftable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() << declval<RHS>()), bool_constant<noexcept(declval<LHS>() << declval<RHS>())>>
test_nothrow_left_shiftable(int) noexcept;
template <typename, typename>
false_type test_nothrow_left_shiftable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_nothrow_left_shiftable : decltype(__dsa::test_nothrow_left_shiftable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_nothrow_left_shiftable_v {is_nothrow_left_shiftable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() >> declval<RHS>()), true_type> test_right_shiftable(int) noexcept;
template <typename, typename>
false_type test_right_shiftable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_right_shiftable : decltype(__dsa::test_right_shiftable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_right_shiftable_v {is_right_shiftable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() >> declval<RHS>()), bool_constant<noexcept(declval<LHS>() >> declval<RHS>())>>
test_nothrow_right_shiftable(int) noexcept;
template <typename, typename>
false_type test_nothrow_right_shiftable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_nothrow_right_shiftable : decltype(__dsa::test_nothrow_right_shiftable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_nothrow_right_shiftable_v {is_nothrow_right_shiftable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() >>= declval<RHS>()), true_type>
test_right_shift_assignable(int) noexcept;
template <typename, typename>
false_type test_right_shift_assignable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_right_shift_assignable : decltype(__dsa::test_right_shift_assignable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_right_shift_assignable_v {is_right_shift_assignable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() >>= declval<RHS>()), bool_constant<noexcept(declval<LHS>() >>= declval<RHS>())>>
test_nothrow_right_shift_assignable(int) noexcept;
template <typename, typename>
false_type test_nothrow_right_shift_assignable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_nothrow_right_shift_assignable : decltype(__dsa::test_nothrow_right_shift_assignable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_nothrow_right_shift_assignable_v {
    is_nothrow_right_shift_assignable<LHS, RHS>::value
};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() <<= declval<RHS>()), true_type> test_left_shift_assignable(int) noexcept;
template <typename, typename>
false_type test_left_shift_assignable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_left_shift_assignable : decltype(__dsa::test_left_shift_assignable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_left_shift_assignable_v {is_left_shift_assignable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() <<= declval<RHS>()), bool_constant<noexcept(declval<LHS>() <<= declval<RHS>())>>
test_nothrow_left_shift_assignable(int) noexcept;
template <typename, typename>
false_type test_nothrow_left_shift_assignable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_nothrow_left_shift_assignable : decltype(__dsa::test_nothrow_left_shift_assignable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_nothrow_left_shift_assignable_v {is_nothrow_left_shift_assignable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() == declval<RHS>()), true_type> test_equal_to_comparable(int) noexcept;
template <typename, typename>
false_type test_equal_to_comparable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_equal_to_comparable : decltype(__dsa::test_equal_to_comparable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_equal_to_comparable_v {is_equal_to_comparable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() == declval<RHS>()), bool_constant<noexcept(declval<LHS>() == declval<RHS>())>>
test_nothrow_equal_to_comparable(int) noexcept;
template <typename, typename>
false_type test_nothrow_equal_to_comparable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_nothrow_equal_to_comparable : decltype(__dsa::test_nothrow_equal_to_comparable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_nothrow_equal_to_comparable_v {is_nothrow_equal_to_comparable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() != declval<RHS>()), true_type> test_not_equal_to_comparable(int) noexcept;
template <typename, typename>
false_type test_not_equal_to_comparable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_not_equal_to_comparable : decltype(__dsa::test_not_equal_to_comparable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_not_equal_to_comparable_v {is_not_equal_to_comparable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() != declval<RHS>()), bool_constant<noexcept(declval<LHS>() != declval<RHS>())>>
test_nothrow_not_equal_to_comparable(int) noexcept;
template <typename, typename>
false_type test_nothrow_not_equal_to_comparable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_nothrow_not_equal_to_comparable : decltype(__dsa::test_nothrow_not_equal_to_comparable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_nothrow_not_equal_to_comparable_v {is_nothrow_not_equal_to_comparable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() <= declval<RHS>()), true_type> test_less_equal_to_comparable(int) noexcept;
template <typename, typename>
false_type test_less_equal_to_comparable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_less_equal_to_comparable : decltype(__dsa::test_less_equal_to_comparable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_less_equal_to_comparable_v {is_less_equal_to_comparable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() <= declval<RHS>()), bool_constant<noexcept(declval<LHS>() <= declval<RHS>())>>
test_nothrow_less_equal_to_comparable(int) noexcept;
template <typename, typename>
false_type test_nothrow_less_equal_to_comparable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_nothrow_less_equal_to_comparable : decltype(__dsa::test_nothrow_less_equal_to_comparable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_nothrow_less_equal_to_comparable_v {is_nothrow_less_equal_to_comparable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() >= declval<RHS>()), true_type> test_greater_equal_to_comparable(int) noexcept;
template <typename, typename>
false_type test_greater_equal_to_comparable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_greater_equal_to_comparable : decltype(__dsa::test_greater_equal_to_comparable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_greater_equal_to_comparable_v {is_greater_equal_to_comparable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() >= declval<RHS>()), bool_constant<noexcept(declval<LHS>() >= declval<RHS>())>>
test_nothrow_greater_equal_to_comparable(int) noexcept;
template <typename, typename>
false_type test_nothrow_greater_equal_to_comparable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_nothrow_greater_equal_to_comparable :
        decltype(__dsa::test_nothrow_greater_equal_to_comparable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_nothrow_greater_equal_to_comparable_v {
    is_nothrow_greater_equal_to_comparable<LHS, RHS>::value
};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() <=> declval<RHS>()), true_type> test_three_way_comparable(int) noexcept;
template <typename, typename>
false_type test_three_way_comparable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_three_way_comparable : decltype(__dsa::test_three_way_comparable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_three_way_comparable_v {is_three_way_comparable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() <=> declval<RHS>()), bool_constant<noexcept(declval<LHS>() <=> declval<RHS>())>>
test_nothrow_three_way_comparable(int) noexcept;
template <typename, typename>
false_type test_nothrow_three_way_comparable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_nothrow_three_way_comparable : decltype(__dsa::test_nothrow_three_way_comparable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_nothrow_three_way_comparable_v {is_nothrow_three_way_comparable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() && declval<RHS>()), true_type> test_logical_andable(int) noexcept;
template <typename, typename>
false_type test_logical_andable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_logical_andable : decltype(__dsa::test_logical_andable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_logical_andable_v {is_logical_andable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() && declval<RHS>()), bool_constant<noexcept(declval<LHS>() && declval<RHS>())>>
test_nothrow_logical_andable(int) noexcept;
template <typename, typename>
false_type test_nothrow_logical_andable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_nothrow_logical_andable : decltype(__dsa::test_nothrow_logical_andable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_nothrow_logical_andable_v {is_nothrow_logical_andable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() || declval<RHS>()), true_type> test_logical_orable(int) noexcept;
template <typename, typename>
false_type test_logical_orable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_logical_orable : decltype(__dsa::test_logical_orable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_logical_orable_v {is_logical_orable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>() || declval<RHS>()), bool_constant<noexcept(declval<LHS>() || declval<RHS>())>>
test_nothrow_logical_orable(int) noexcept;
template <typename, typename>
false_type test_nothrow_logical_orable(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_nothrow_logical_orable : decltype(__dsa::test_nothrow_logical_orable<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_nothrow_logical_orable_v {is_nothrow_logical_orable<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename T>
select_second_t<decltype(++declval<T>()), true_type> test_prefix_increasable(int) noexcept;
template <typename>
false_type test_prefix_increasable(...) noexcept;
}
template <typename T>
struct is_prefix_increasable : decltype(__dsa::test_prefix_increasable<T>(0)) {};
template <typename T>
inline constexpr auto is_prefix_increasable_v {is_prefix_increasable<T>::value};

namespace __data_structure_auxiliary {
template <typename T>
select_second_t<decltype(++declval<T>()), bool_constant<noexcept(++declval<T>())>>
test_nothrow_prefix_increasable(int) noexcept;
template <typename>
false_type test_nothrow_prefix_increasable(...) noexcept;
}
template <typename T>
struct is_nothrow_prefix_increasable : decltype(__dsa::test_nothrow_prefix_increasable<T>(0)) {};
template <typename T>
inline constexpr auto is_nothrow_prefix_increasable_v {is_nothrow_prefix_increasable<T>::value};

namespace __data_structure_auxiliary {
template <typename T>
select_second_t<decltype(declval<T>()++), true_type> test_postfix_increasable(int) noexcept;
template <typename>
false_type test_postfix_increasable(...) noexcept;
}
template <typename T>
struct is_postfix_increasable : decltype(__dsa::test_postfix_increasable<T>(0)) {};
template <typename T>
inline constexpr auto is_postfix_increasable_v {is_postfix_increasable<T>::value};

namespace __data_structure_auxiliary {
template <typename T>
select_second_t<decltype(declval<T>()++), bool_constant<noexcept(declval<T>()++)>>
test_nothrow_postfix_increasable(int) noexcept;
template <typename>
false_type test_nothrow_postfix_increasable(...) noexcept;
}
template <typename T>
struct is_nothrow_postfix_increasable : decltype(__dsa::test_nothrow_postfix_increasable<T>(0)) {};
template <typename T>
inline constexpr auto is_nothrow_postfix_increasable_v {is_nothrow_postfix_increasable<T>::value};

namespace __data_structure_auxiliary {
template <typename T>
select_second_t<decltype(--declval<T>()), true_type> test_prefix_decreasable(int) noexcept;
template <typename>
false_type test_prefix_decreasable(...) noexcept;
}
template <typename T>
struct is_prefix_decreasable : decltype(__dsa::test_prefix_decreasable<T>(0)) {};
template <typename T>
inline constexpr auto is_prefix_decreasable_v {is_prefix_decreasable<T>::value};

namespace __data_structure_auxiliary {
template <typename T>
select_second_t<decltype(--declval<T>()), bool_constant<noexcept(--declval<T>())>>
test_nothrow_prefix_decreasable(int) noexcept;
template <typename>
false_type test_nothrow_prefix_decreasable(...) noexcept;
}
template <typename T>
struct is_nothrow_prefix_decreasable : decltype(__dsa::test_nothrow_prefix_decreasable<T>(0)) {};
template <typename T>
inline constexpr auto is_nothrow_prefix_decreasable_v {is_nothrow_prefix_decreasable<T>::value};

namespace __data_structure_auxiliary {
template <typename T>
select_second_t<decltype(declval<T>()--), true_type> test_postfix_decreasable(int) noexcept;
template <typename>
false_type test_postfix_decreasable(...) noexcept;
}
template <typename T>
struct is_postfix_decreasable : decltype(__dsa::test_postfix_decreasable<T>(0)) {};
template <typename T>
inline constexpr auto is_postfix_decreasable_v {is_postfix_decreasable<T>::value};

namespace __data_structure_auxiliary {
template <typename T>
select_second_t<decltype(declval<T>()--), bool_constant<noexcept(declval<T>()--)>>
test_nothrow_postfix_decreasable(int) noexcept;
template <typename>
false_type test_nothrow_postfix_decreasable(...) noexcept;
}
template <typename T>
struct is_nothrow_postfix_decreasable : decltype(__dsa::test_nothrow_postfix_decreasable<T>(0)) {};
template <typename T>
inline constexpr auto is_nothrow_postfix_decreasable_v {is_nothrow_postfix_decreasable<T>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>().operator,(declval<RHS>())), true_type> test_comma(int) noexcept;
template <typename LHS, typename RHS>
select_second_t<decltype(operator,(declval<LHS>(), declval<RHS>())), true_type> test_comma(long) noexcept;
template <typename, typename>
false_type test_comma(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_comma_overloaded : decltype(__dsa::test_comma<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_comma_overloaded_v {is_comma_overloaded<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename LHS, typename RHS>
select_second_t<decltype(declval<LHS>().operator,(declval<RHS>())),
        bool_constant<noexcept(declval<LHS>().operator,(declval<RHS>()))>> test_nothrow_comma(int) noexcept;
template <typename LHS, typename RHS>
select_second_t<decltype(operator,(declval<LHS>(), declval<RHS>())),
        bool_constant<noexcept(operator,(declval<LHS>(), declval<RHS>()))>> test_nothrow_comma(long) noexcept;
template <typename, typename>
false_type test_nothrow_comma(...) noexcept;
}
template <typename LHS, typename RHS = LHS>
struct is_nothrow_comma_overloaded : decltype(__dsa::test_nothrow_comma<LHS, RHS>(0)) {};
template <typename LHS, typename RHS = LHS>
inline constexpr auto is_nothrow_comma_overloaded_v {is_nothrow_comma_overloaded<LHS, RHS>::value};

namespace __data_structure_auxiliary {
template <typename T, typename O>
select_second_t<decltype(declval<T>()->*declval<O>()), true_type> test_pointer_to_member_accessible(int) noexcept;
template <typename, typename>
false_type test_pointer_to_member_accessible(...) noexcept;
}
template <typename T, typename O>
struct is_pointer_to_member_accessible : decltype(__dsa::test_pointer_to_member_accessible<T, O>(0)) {};
template <typename T, typename O>
inline constexpr auto is_pointer_to_member_accessible_v {is_pointer_to_member_accessible<T, O>::value};

namespace __data_structure_auxiliary {
template <typename T, typename O>
select_second_t<decltype(declval<T>()->*declval<O>()), bool_constant<noexcept(declval<T>()->*declval<O>())>>
test_nothrow_pointer_to_member_accessible(int) noexcept;
template <typename, typename>
false_type test_nothrow_pointer_to_member_accessible(...) noexcept;
}
template <typename T, typename O>
struct is_nothrow_pointer_to_member_accessible : decltype(__dsa::test_nothrow_pointer_to_member_accessible<T, O>(0)) {};
template <typename T, typename O>
inline constexpr auto is_nothrow_pointer_to_member_accessible_v {is_nothrow_pointer_to_member_accessible<T, O>::value};

namespace __data_structure_auxiliary {
template <typename T>
select_second_t<decltype(declval<T>().operator->()), true_type> test_member_accessible_by_pointer(int) noexcept;
template <typename>
false_type test_member_accessible_by_pointer(...) noexcept;
}
template <typename T>
struct is_member_accessible_by_pointer : conditional_t<is_pointer_v<remove_reference_t<T>>,
        bool_constant<is_class_v<remove_pointer_t<typename decay<T>::type>>>,
        decltype(__dsa::test_member_accessible_by_pointer<T>(0))> {};
template <typename T>
inline constexpr auto is_member_accessible_by_pointer_v {is_member_accessible_by_pointer<T>::value};

namespace __data_structure_auxiliary {
template <typename T>
select_second_t<decltype(declval<T>().operator->()), bool_constant<noexcept(declval<T>().operator->())>>
test_nothrow_member_accessible_by_pointer(int) noexcept;
template <typename>
false_type test_nothrow_member_accessible_by_pointer(...) noexcept;
}
template <typename T>
struct is_nothrow_member_accessible_by_pointer : conditional_t<is_pointer_v<remove_reference_t<T>>,
        bool_constant<is_class_v<remove_pointer_t<typename decay<T>::type>>>,
        decltype(__dsa::test_nothrow_member_accessible_by_pointer<T>(0))> {};
template <typename T>
inline constexpr auto is_nothrow_member_accessible_by_pointer_v {is_nothrow_member_accessible_by_pointer<T>::value};

namespace __data_structure_auxiliary {
template <typename T, typename I>
select_second_t<decltype(declval<T>()[declval<I>()]), true_type> test_indexable(int) noexcept;
template <typename, typename>
false_type test_indexable(...) noexcept;
}
template <typename T, typename I>
struct is_indexable : decltype(__dsa::test_indexable<T, I>(0)) {};
template <typename T, typename I>
inline constexpr auto is_indexable_v {is_indexable<T, I>::value};

namespace __data_structure_auxiliary {
template <typename T, typename I>
select_second_t<decltype(declval<T>()[declval<I>()]), bool_constant<noexcept(declval<T>()[declval<I>()])>>
test_nothrow_indexable(int) noexcept;
template <typename, typename>
false_type test_nothrow_indexable(...) noexcept;
}
template <typename T, typename I>
struct is_nothrow_indexable : decltype(__dsa::test_nothrow_indexable<T, I>(0)) {};
template <typename T, typename I>
inline constexpr auto is_nothrow_indexable_v {is_nothrow_indexable<T, I>::value};

namespace __data_structure_auxiliary {
template <typename T>
select_second_t<decltype(declval<T>().operator co_await()), true_type> test_coroutine_awaitable(int) noexcept;
template <typename>
false_type test_coroutine_awaitable(...) noexcept;
}
template <typename T>
struct is_coroutine_awaitable : decltype(__dsa::test_coroutine_awaitable<T>(0)) {};
template <typename T>
inline constexpr auto is_coroutine_awaitable_v {is_coroutine_awaitable<T>::value};

namespace __data_structure_auxiliary {
template <typename T>
select_second_t<decltype(declval<T>().operator co_await()), bool_constant<noexcept(declval<T>().operator co_await())>>
test_nothrow_coroutine_awaitable(int) noexcept;
template <typename>
false_type test_nothrow_coroutine_awaitable(...) noexcept;
}
template <typename T>
struct is_nothrow_coroutine_awaitable : decltype(__dsa::test_nothrow_coroutine_awaitable<T>(0)) {};
template <typename T>
inline constexpr auto is_nothrow_coroutine_awaitable_v {is_nothrow_coroutine_awaitable<T>::value};
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(has something)
template <typename T>
struct has_virtual_destructor : conditional_t<__has_virtual_destructor(T), true_type, false_type> {};
template <typename T>
inline constexpr auto has_virtual_destructor_v {has_virtual_destructor<T>::value};

template <typename T>
struct has_unique_object_representations :
        conditional_t<__has_unique_object_representations(T), true_type, false_type> {};
template <typename T>
inline constexpr auto has_unique_object_representations_v {has_unique_object_representations<T>::value};
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(copy something)
template <typename Original, typename To>
struct copy_const {
    using type = conditional_t<is_const_v<Original>, add_const_t<To>, To>;
};
template <typename Original, typename To>
using copy_const_t = typename copy_const<Original, To>::type;

template <typename Original, typename To>
struct copy_volatile {
    using type = conditional_t<is_volatile_v<Original>, add_volatile_t<To>, To>;
};
template <typename Original, typename To>
using copy_volatile_t = typename copy_volatile<Original, To>::type;

template <typename Original, typename To>
struct copy_cv {
    using type = copy_const_t<Original, copy_volatile_t<Original, To>>;
};
template <typename Original, typename To>
using copy_cv_t = typename copy_cv<Original, To>::type;

template <typename Original, typename To>
struct copy_lvalue_reference {
    using type = conditional_t<is_lvalue_reference_v<Original>, add_lvalue_reference_t<To>, To>;
};
template <typename Original, typename To>
using copy_lvalue_reference_t = typename copy_lvalue_reference<Original, To>::type;

template <typename Original, typename To>
struct copy_rvalue_reference {
    using type = conditional_t<is_rvalue_reference_v<Original>, add_rvalue_reference_t<remove_reference_t<To>>, To>;
};
template <typename Original, typename To>
using copy_rvalue_reference_t = typename copy_rvalue_reference<Original, To>::type;

template <typename Original, typename To>
struct copy_reference {
    using type = conditional_t<is_lvalue_reference_v<Original>, add_lvalue_reference_t<To>,
            conditional_t<is_rvalue_reference_v<Original>, add_rvalue_reference_t<To>, To>>;
};
template <typename Original, typename To>
using copy_reference_t = typename copy_reference<Original, To>::type;
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(other auxliary)
template <typename> struct decay;
template <typename ...> struct common_type;
template <typename> struct alignment_of;
namespace __data_structure_auxiliary {
using signed_integral = type_container<signed char, signed short, signed int,
        signed long, signed long long, __int128_t>;
using unsigned_integral = type_container<unsigned char, unsigned short, unsigned int,
        unsigned long, unsigned long long, __uint128_t>;
using floating_point = type_container<float, double, long double>;
using character = type_container<char8_t, char16_t, char32_t>;

template <typename T, typename Result, typename Container>
struct make_signed_or_unsigned_auxiliary {
private:
    using next_type = typename Container::type;
    using remaining_type = typename Container::remaining;
public:
    using type = conditional_t<sizeof(T) == sizeof(Result), Result,
            conditional_t<(sizeof(T) > sizeof(Result)) and sizeof(T) <= sizeof(next_type), next_type,
                    typename make_signed_or_unsigned_auxiliary<T, next_type, remaining_type>::type>>;
};
template <typename T, typename Result>
struct make_signed_or_unsigned_auxiliary<T, Result, type_container<>> {
    using type = Result;
};

template <typename, typename>
struct promotion_index;
template <typename T, typename Container>
using promotion_index_t = typename promotion_index<T, Container>::type;
template <typename T, typename Container>
struct promotion_index {
private:
    using next_type = typename Container::next;
    using this_type = typename Container::type;
public:
    using type = conditional_t<is_same_v<T, this_type>, Container, promotion_index_t<T, next_type>>;
};
template <typename T>
struct promotion_index<T, type_container<>> {
    using type = type_container<>;
};

template <typename T, typename = void>
struct integral_promotion_auxiliary {
    static_assert(is_integral_v<T>, "This trait requires an integral type!");
};
template <typename T>
struct integral_promotion_auxiliary<T, enable_if_t<is_signed_v<T>>> {
    using type = conditional_t<
            is_same_v<typename promotion_index<T, signed_integral>::type::type, __int128_t>,
            __int128_t, typename promotion_index<T, signed_integral>::type::next::type>;
};
template <typename T>
struct integral_promotion_auxiliary<T, enable_if_t<is_unsigned_v<T>>> {
    using type = conditional_t<
            is_same_v<typename promotion_index<T, unsigned_integral>::type::type, __uint128_t>,
            __uint128_t, typename promotion_index<T, unsigned_integral>::type::next::type>;
};

template <typename T, typename = void>
struct floating_point_promotion_auxiliary {
    static_assert(is_floating_point_v<T>, "The trait requires a floating point type!");
};
template <typename T>
struct floating_point_promotion_auxiliary<T, enable_if_t<is_floating_point_v<T>>> {
    using type = conditional_t<
            is_same_v<typename promotion_index<T, floating_point>::type::type, long double>,
            long double, typename promotion_index<T, floating_point>::type::next::type>;
};

template <typename T, typename = void>
struct character_promotion_auxiliary {
    static_assert(is_character_v<T>, "The trait requires a character type!");
};
template <typename T>
struct character_promotion_auxiliary<T, enable_if_t<is_character_v<T>>> {
    using type = conditional_t<
            is_same_v<typename promotion_index<T, character>::type::type, char32_t>,
            char32_t, typename promotion_index<T, character>::type::next::type>;
};

template <typename T, typename = void>
struct arithmetic_promotion_auxiliary {
    static_assert(is_integral_v<T> or is_floating_point_v<T>,
                  "The trait requires a character type or an integral type!");
};
template <typename T>
struct arithmetic_promotion_auxiliary<T, enable_if_t<is_integral_v<T>>> :
        copy_cv<T, typename __dsa::integral_promotion_auxiliary<remove_cv_t<T>>::type> {};
template <typename T>
struct arithmetic_promotion_auxiliary<T, enable_if_t<is_floating_point_v<T>>> :
        copy_cv<T, typename __dsa::floating_point_promotion_auxiliary<remove_cv_t<T>>::type> {};

template <typename T>
using decay_t = typename decay<T>::type;
template <typename> struct reference_wrapper;
struct invoke_failure_tag {};
template <typename T, typename = decay_t<T>>
struct unwrap : type_identity<T> {};
template <typename T, typename U>
struct unwrap<T, reference_wrapper<U>> : type_identity<reference_wrapper<U>> {};
template <typename Fp, typename T, typename ...Args>
static constexpr decltype((declval<T>().*declval<Fp>())(declval<Args>()...))
test_member_function(int) noexcept;
template <typename ...>
static constexpr invoke_failure_tag test_member_function(...) noexcept;
template <typename Fp, typename T, typename ...Args>
static consteval inline bool is_nothrow_member_function() noexcept {
    return noexcept((declval<T>().*declval<Fp>())(declval<Args>()...));
}
template <typename Fp, typename Ptr, typename ...Args>
static constexpr decltype((declval<Ptr>()->*declval<Fp>())(declval<Args>()...))
test_member_function_deref(int) noexcept;
template <typename ...>
static constexpr invoke_failure_tag test_member_function_deref(...) noexcept;
template <typename Fp, typename Ptr, typename ...Args>
static consteval inline bool is_nothrow_member_function_deref() noexcept {
    return noexcept((declval<Ptr>()->*declval<Fp>())(declval<Args>()...));
}
template <typename Op, typename T>
static constexpr decltype(declval<T>().*declval<Op>()) test_member_object(int) noexcept;
template <typename, typename>
static constexpr invoke_failure_tag test_member_object(...) noexcept;
template <typename Op, typename T>
static consteval inline bool is_nothrow_member_object() noexcept {
    return noexcept(declval<T>().*declval<Op>());
}
template <typename Op, typename T>
static constexpr decltype(declval<T>()->*declval<Op>()) test_member_object_deref(int) noexcept;
template <typename, typename>
static constexpr invoke_failure_tag test_member_object_deref(...) noexcept;
template <typename Op, typename T>
static consteval inline bool is_nothrow_member_object_deref() noexcept {
    return noexcept(declval<T>()->*declval<Op>());
}
template <typename F, typename ...Args>
static constexpr decltype(declval<F>()(declval<Args>()...)) test_function(int) noexcept;
template <typename ...>
static constexpr invoke_failure_tag test_function(...) noexcept;
template <typename F, typename ...Args>
static consteval inline bool is_nothrow_function() noexcept {
    return noexcept(declval<F>()(declval<Args>()...));
}
template <typename, typename>
struct result_of_member_object;
template <typename PreT, typename Class, typename T>
struct result_of_member_object<PreT Class::*, T> {
    using type = conditional_t<
            is_same_v<remove_cvref_t<T>, Class> or is_base_of_v<Class, remove_cvref_t<T>>,
            decltype(test_member_object<PreT Class::*, T>(0)),
            decltype(test_member_object_deref<PreT Class::*, T>(0))>;
};
template <typename, typename>
struct result_of_nothrow_member_object;
template <typename PreT, typename Class, typename T>
struct result_of_nothrow_member_object<PreT Class::*, T> :
        conditional_t<is_same_v<remove_cvref_t<T>, Class> or is_base_of_v<Class, remove_cvref_t<T>>,
                bool_constant<is_nothrow_member_object<PreT Class::*, T>()>,
                bool_constant<is_nothrow_member_object_deref<PreT Class::*, T>()>> {};
template <typename ...>
struct result_of_member_function;
template <typename PreT, typename Class, typename Fp, typename ...Args>
struct result_of_member_function<PreT Class::*, Fp, Args...> {
    using type = conditional_t<
            is_same_v<remove_cvref_t<Fp>, Class> or is_base_of_v<Class, remove_cvref_t<Fp>>,
            decltype(test_member_function<PreT Class::*, Fp, Args...>(0)),
            decltype(test_member_function_deref<PreT Class::*, Fp, Args...>(0))>;
};
template <typename ...>
struct result_of_nothrow_member_function;
template <typename PreT, typename Class, typename Fp, typename ...Args>
struct result_of_nothrow_member_function<PreT Class::*, Fp, Args...> :
        conditional_t<is_same_v<remove_cvref_t<Fp>, Class> or is_base_of_v<Class, remove_cvref_t<Fp>>,
                bool_constant<is_nothrow_member_function<PreT Class::*, Fp, Args...>()>,
                bool_constant<is_nothrow_member_function_deref<PreT Class::*, Fp, Args...>()>> {};
template <bool, bool, typename, typename ...>
struct result_of_auxiliary : invoke_failure_tag {};
template <typename MenPtr, typename T>
struct result_of_auxiliary<true, false, MenPtr, T> : conditional_t<is_same_v<invoke_failure_tag,
        typename result_of_member_object<decay_t<MenPtr>, typename unwrap<T>::type>::type>,
        invoke_failure_tag, result_of_member_object<decay_t<MenPtr>, typename unwrap<T>::type>> {};
template <typename MenPtr, typename T, typename ...Args>
struct result_of_auxiliary<false, true, MenPtr, T, Args...> :
        conditional_t<is_same_v<invoke_failure_tag, typename result_of_member_function<
                decay_t<MenPtr>, typename unwrap<T>::type, Args...>::type>,
                invoke_failure_tag,
                result_of_member_function<decay_t<MenPtr>, typename unwrap<T>::type, Args...>> {};
template <typename F, typename ...Args>
struct result_of_auxiliary<false, false, F, Args...> : conditional_t<is_same_v<invoke_failure_tag,
        decltype(test_function<F, Args...>(0))>, invoke_failure_tag,
        type_identity<decltype(test_function<F, Args...>(0))>> {};
template <typename MemPtr, typename T>
struct result_of_nothrow_auxiliary<true, false, MemPtr, T> :
        result_of_nothrow_member_object<decay_t<MemPtr>, typename unwrap<T>::type> {};
template <typename MemPtr, typename T, typename ...Args>
struct result_of_nothrow_auxiliary<false, true, MemPtr, T, Args...> :
        result_of_nothrow_member_function<decay_t<MemPtr>, typename unwrap<T>::type> {};
template <typename F, typename ...Args>
struct result_of_nothrow_auxiliary<false, false, F, Args...> :
        bool_constant<is_nothrow_function<F, Args...>()> {};

struct aligned_storage_double_helper {
    long double _1;
};
struct aligned_storage_double4_helper {
    double _1[4];
};
using aligned_storage_helper_types = type_container<unsigned char, unsigned short, unsigned int,
        unsigned long, unsigned long long, double, long double, aligned_storage_double_helper,
        aligned_storage_double4_helper, int *>;
template <size_t Align>
struct alignas(Align) overaligned {};
template <typename, size_t>
struct aligned_storage_find_suitable_type;
template <size_t Align, typename T, typename ...Args>
struct aligned_storage_find_suitable_type<type_container<T, Args...>, Align> {
    using type = conditional_t<Align == alignof(T), T,
            typename aligned_storage_find_suitable_type<type_container<Args...>, Align>::type>;
};
template <size_t Align>
struct aligned_storage_find_suitable_type<type_container<>, Align> {
    using type = overaligned<Align>;
};
template <size_t Length, size_t Align1, size_t Align2>
struct aligned_storage_selector {
private:
    static constexpr auto min {Align1 < Align2 ? Align1 : Align2};
    static constexpr auto max {Align1 < Align2 ? Align2 : Align1};
public:
    static constexpr auto value {Length < max ? min : max};
};
template <typename, size_t>
struct aligned_storage_find_max_align;
template <size_t Length, typename T>
struct aligned_storage_find_max_align<type_container<T>, Length> : alignment_of<T> {};
template <size_t Length, typename T, typename ...Args>
struct aligned_storage_find_max_align<type_container<T, Args...>, Length> : constant<size_t,
        aligned_storage_selector<Length, alignof(T),
                aligned_storage_find_max_align<type_container<Args...>, Length>::value>::value> {};

template <typename, typename ...>
struct aligned_union_find_max_align;
template <typename T>
struct aligned_union_find_max_align<T> : alignment_of<T> {};
template <typename T, typename U>
struct aligned_union_find_max_align<T, U> :
        conditional<alignof(T) < alignof(U), alignment_of<U>, alignment_of<T>> {};
template <typename T, typename U, typename ...Args>
struct aligned_union_find_max_align<T, U, Args...> : conditional_t<alignof(T) < alignof(U),
        aligned_union_find_max_align<U, Args...>, aligned_union_find_max_align<T, Args...>> {};
template <size_t, size_t ...>
struct aligned_union_find_max_number;
template <size_t N>
struct aligned_union_find_max_number<N> : constant<size_t, N> {};
template <size_t N, size_t M>
struct aligned_union_find_max_number<N, M> :
        conditional_t<N < M, constant<size_t, M>, constant<size_t, M>> {};
template <size_t N, size_t M, size_t ...Numbers>
struct aligned_union_find_max_number<N, M, Numbers...> :
        aligned_union_find_max_number<aligned_union_find_max_number<N, M>::value, Numbers...> {};

union type_with_alignment_max_alignment {
    char _1;
    short _2;
    int _3;
    long _4;
    long long _5;
    __int128_t _6;
    float _7;
    double _8;
    long double _9;
};
using type_with_alignment_helper_types = type_container<
        char, short, int, long, long long, double, long double>;
template <typename, size_t>
struct type_with_alignment_find_suitable_type;
template <size_t Align>
struct type_with_alignment_find_suitable_type<type_container<>, Align> {
    using type = type_with_alignment_max_alignment;
};
template <size_t Align, typename T, typename ...Args>
struct type_with_alignment_find_suitable_type<type_container<T, Args...>, Align> {
    using type = conditional_t<Align < alignof(T), T,
            typename type_with_alignment_find_suitable_type<type_container<Args...>, Align>::type>;
};

template <typename T, typename U>
using common_ref_auxiliary = decltype(make_true<T, U> ? declval<T (&)()>()() : declval<U (&)()>()());
template <typename T, typename U, typename = void>
struct common_ref_impl {};
template <typename T, typename U>
using common_ref = typename common_ref_impl<T, U>::type;
template <typename T, typename U>
struct common_ref_impl<T &, U &, void_t<common_ref_auxiliary<
        add_lvalue_reference_t<copy_cv_t<T, U>>, add_lvalue_reference_t<copy_cv_t<U, T>>>>> {
    using type = common_ref_auxiliary<
            add_lvalue_reference_t<copy_cv_t<T, U>>, add_lvalue_reference_t<copy_cv_t<U, T>>>;
};
template <typename T, typename U>
using common_ref_make_rvalue_ref = add_rvalue_reference_t<remove_reference_t<common_ref<T &, U &>>>;
template <typename T, typename U>
struct common_ref_impl<T &&, U &&, enable_if_t<is_convertible_v<T &&, common_ref_make_rvalue_ref<T, U>>
        and is_convertible_v<U &&, common_ref_make_rvalue_ref<T, U>>>> {
    using type = common_ref_make_rvalue_ref<T, U>;
};
template <typename T, typename U>
using common_ref_for_const_ref = common_ref<const T &, U &>;
template <typename T, typename U>
struct common_ref_impl<T &&, U &, enable_if_t<is_convertible_v<T &&, common_ref_for_const_ref<T, U>>>> {
    using type = common_ref_for_const_ref<T, U>;
};
template <typename T, typename U>
struct common_ref_impl<T &, U &&> : common_ref_impl<U &&, T &> {};
template <typename T, typename U, template <typename> typename TQual, template <typename> typename UQual>
struct basic_common_reference {};
template <typename T>
struct copy_ref_for_class_template {
    template <typename U>
    using type = copy_cv_t<T, U>;
};
template <typename T>
struct copy_ref_for_class_template<T &> {
    template <typename U>
    using type = add_lvalue_reference_t<copy_cv_t<T, U>>;
};
template <typename T>
struct copy_ref_for_class_template<T &&> {
    template <typename U>
    using type = add_rvalue_reference_t<copy_cv_t<T, U>>;
};
template <typename T, typename U>
using basic_common_ref = typename basic_common_reference<remove_cvref_t<T>, remove_cvref_t<U>,
        copy_ref_for_class_template<T>::template type, copy_ref_for_class_template<U>::template type>::type;
template <typename T, typename U, int Bullet = 1, typename = void>
struct common_reference_auxiliary : common_reference_auxiliary<T, U, Bullet + 1> {};
template <typename T, typename U>
struct common_reference_auxiliary<T &, U &, 1, void_t<common_ref<T &, U &>>> {
    using type = common_ref<T &, U &>;
};
template <typename T, typename U>
struct common_reference_auxiliary<T &&, U &&, 1, void_t<common_ref<T &, U &>>> {
    using type = common_ref<T &&, U &&>;
};
template <typename T, typename U>
struct common_reference_auxiliary<T &, U &&, 1, void_t<common_ref<T &, U &&>>> {
    using type = common_ref<T &, U &&>;
};
template <typename T, typename U>
struct common_reference_auxiliary<T &&, U &, 1, void_t<common_ref<T &&, U &>>> {
    using type = common_ref<T &&, U &>;
};
template <typename T, typename U>
struct common_reference_auxiliary<T, U, 2, void_t<basic_common_ref<T, U>>> {
    using type = basic_common_ref<T, U>;
};
template <typename T, typename U>
struct common_reference_auxiliary<T, U, 3, void_t<common_ref_auxiliary<T, U>>> {
    using type = common_ref_auxiliary<T, U>;
};
template <typename T, typename U>
struct common_reference_auxiliary<T, U, 4, void_t<typename common_type<T, U>::type>> {
    using type = typename common_type<T, U>::type;
};
template <typename T, typename U>
struct common_reference_auxiliary<T, U, 5, void> {};
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(other)
namespace __data_structure_auxiliary {
template <typename T, bool = is_complete_v<T>>
struct size_of_auxiliary : constant<size_t, sizeof(T)> {};
template <typename T>
struct size_of_auxiliary<T, false> : constant<size_t, 0> {};
}
template <typename T>
struct size_of : __dsa::size_of_auxiliary<T> {};
template <typename T>
inline constexpr auto size_of_v {size_of<T>::value};

namespace __data_structure_auxiliary {
template <typename T, bool = is_complete_v<T> or is_unbounded_array_v<T>>
struct alignment_of_auxiliary : constant<size_t, alignof(T)> {};
template <typename T>
struct alignment_of_auxiliary<T, false> : constant<size_t, 0> {};
}
template <typename T>
struct alignment_of : __dsa::alignment_of_auxiliary<T> {};
template <typename T>
inline constexpr auto alignment_of_v {alignment_of<T>::value};

template <typename T>
struct rank : constant<size_t, 0> {};
template <typename T>
inline constexpr auto rank_v {rank<T>::value};
template <typename T>
struct rank<T []> : constant<size_t, rank_v<T> + 1> {};
template <typename T, size_t N>
struct rank<T [N]> : constant<size_t, rank_v<T> + 1> {};

template <typename T, size_t Index = 0>
struct extent : constant<size_t, 0> {};
template <typename T>
struct extent<T [], 0> : constant<size_t, 0> {};
template <typename T, size_t Index>
struct extent<T [], Index> : extent<T, Index - 1> {};
template <typename T, size_t Size>
struct extent<T [Size], 0> : constant<size_t, Size> {};
template <typename T, size_t Size, size_t Index>
struct extent<T [Size], Index> : extent<T, Index - 1> {};
template <typename T, size_t Index = 0>
inline constexpr auto extent_v {extent<T, Index>::value};

template <typename T>
struct decay {
private:
    using real_type = remove_reference_t<T>;
public:
    using type = conditional_t<is_array_v<real_type>, add_pointer_t<remove_extent_t<real_type>>,
            conditional_t<is_function_v<real_type>, add_pointer_t<real_type>, remove_cv_t<real_type>>>;
};
template <typename T>
using decay_t = typename decay<T>::type;

namespace __data_structure_auxiliary {
template <typename E, bool = is_enum_v<E>>
struct underlying_type_auxiliary {
    using type = __underlying_type(E);
};
template <typename T>
struct underlying_type_auxiliary<T, false> {
    using type = T;
};
}
template <typename E>
struct underlying_type : __dsa::underlying_type_auxiliary<E> {};
template <typename E>
using underlying_type_t = typename underlying_type<E>::type;

template <typename ...>
struct common_type {};
template <typename ...Ts>
using common_type_t = typename common_type<Ts...>::type;
namespace __data_structure_auxiliary {
template <typename T, typename U, typename = void>
struct common_type_const_reference {};
template <typename T, typename U>
struct common_type_const_reference<T, U,
        void_t<decay_t<decltype(true ? declval<const T &>() : declval<const U &>())>>> {
    using type = decay_t<decltype(true ? declval<const T &>() : declval<const U &>())>;
};
template <typename T, typename U, typename = void>
struct common_type_two_types : common_type_const_reference<T, U> {};
template <typename T, typename U>
struct common_type_two_types<T, U, void_t<decay_t<decltype(true ? declval<T>() : declval<U>())>>> {
    using type = decay_t<decltype(true ? declval<T>() : declval<U>())>;
};
template <typename T, typename U, typename = void_t<common_type_t<T, U>>>
struct common_type_auxiliary : false_type {};
template <typename T, typename U>
struct common_type_auxiliary<T, U, void> : true_type {};
}
template <typename T>
struct common_type<T> : common_type<T, T> {};
template <typename T, typename U>
struct common_type<T, U> : conditional_t<is_same_v<decay_t<T>, T> and is_same_v<decay_t<U>, U>,
        __dsa::common_type_two_types<T, U>, common_type<decay_t<T>, decay_t<U>>> {};
template <typename T, typename U, typename V, typename ...Ts>
struct common_type<T, U, V, Ts...> : conditional_t<__dsa::common_type_auxiliary<T, U>::value,
        common_type<common_type_t<T, U>, V, Ts...>, common_type<>> {};

template <typename ...>
struct common_reference {};
template <typename ...Ts>
using common_reference_t = typename common_reference<Ts...>::type;
template <typename T>
struct common_reference<T> {
    using type = T;
};
template <typename T, typename U>
struct common_reference<T, U> : __dsa::common_reference_auxiliary<T, U> {};
template <typename T, typename U, typename ...Ts>
struct common_reference<T, U, Ts...> : common_reference<common_reference_t<T, U>, Ts...> {};

template <typename T>
struct make_signed {
    using type = copy_cv_t<T, typename __dsa::make_signed_or_unsigned_auxiliary<remove_cv_t<T>,
            signed char, typename __dsa::signed_integral::next>::type>;
};
template <typename T>
using make_signed_t = typename make_signed<T>::type;
template <typename T>
struct make_unsigned {
    using type = copy_cv_t<T, typename __dsa::make_signed_or_unsigned_auxiliary<remove_cv_t<T>,
            unsigned char, typename __dsa::unsigned_integral::next>::type>;
};
template <typename T>
using make_unsigned_t = typename make_unsigned<T>::type;

template <typename T>
struct integral_promotion {
    using type = copy_cv_t<T, typename __dsa::integral_promotion_auxiliary<remove_cv_t<T>>::type>;
};
template <typename T>
using integral_promotion_t = typename integral_promotion<T>::type;

template <typename T>
struct floating_point_promotion {
    using type = copy_cv_t<T, typename __dsa::floating_point_promotion_auxiliary<remove_cv_t<T>>::type>;
};
template <typename T>
using floating_point_promotion_t = typename floating_point_promotion<T>::type;

template <typename T>
struct character_promotion {
    using type = copy_cv_t<T, typename __dsa::character_promotion_auxiliary<remove_cv_t<T>>::type>;
};
template <typename T>
using character_promotion_t = typename character_promotion<T>::type;

template <typename T>
struct arithmetic_promotion : __dsa::arithmetic_promotion_auxiliary<T> {};
template <typename T>
using arithmetic_promotion_t = typename arithmetic_promotion<T>::type;

template <typename ...>
struct class_template_traits;
template <template <typename ...> typename T, typename ...Args>
struct class_template_traits<T<Args...>> {
    using type = T<Args...>;
    template <typename ...Ts>
    using rebind = T<Ts...>;
    using arguments = type_container<Args...>;
};

template <typename Ptr, typename ...Args>
struct invoke_result : __dsa::result_of_auxiliary<is_member_object_pointer_v<remove_reference_t<Ptr>>,
        is_member_function_pointer_v<remove_reference_t<Ptr>>, Ptr, Args...> {
    static_assert(is_complete_v<Ptr>, "The first template argument must be a complete type!");
};
template <typename Ptr, typename ...Args>
using invoke_result_t = typename invoke_result<Ptr, Args...>::type;

template <typename ...>
struct result_of;
template <typename F, typename ...Args>
struct result_of<F (Args...)> : invoke_result<F, Args...> {};
template <typename F, typename ...Args>
using result_of_t = typename result_of<F, Args...>::type;

template <size_t Length, size_t Align =
__dsa::aligned_storage_find_max_align<__dsa::aligned_storage_helper_types, Length>::value>
struct aligned_storage {
private:
    using aligner = typename __dsa::aligned_storage_find_suitable_type<
            __dsa::aligned_storage_helper_types, Align>::type;
public:
    union type {
        aligner align;
        unsigned char data[(Length + Align - 1) / Align * Align];
    };
};
template <size_t Length, size_t Align =
__dsa::aligned_storage_find_max_align<__dsa::aligned_storage_helper_types, Length>::value>
using aligned_storage_t = typename aligned_storage<Length, Align>::type;

template <size_t Length, typename ...Ts>
struct aligned_union {
    struct type {
        alignas(__dsa::aligned_union_find_max_align<Ts...>::value)
        char data[__dsa::aligned_union_find_max_number<Length, sizeof...(Ts)>::value];
    };
};
template <size_t Length, typename ...Ts>
using aligned_union_t = typename aligned_union<Length, Ts...>::type;

template <size_t Align>
struct type_with_alignment :
        __dsa::type_with_alignment_find_suitable_type<__dsa::type_with_alignment_helper_types, Align> {};
template <size_t Align>
using type_with_alignment_t = typename type_with_alignment<Align>::type;
__DATA_STRUCTURE_END

}       // namespace data_structure

#endif //DATA_STRUCTURE_TYPE_TRAITS_HPP