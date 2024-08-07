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

#ifndef DATA_STRUCTURE_META_HPP
#define DATA_STRUCTURE_META_HPP

#include "type_traits.hpp"

__DATA_STRUCTURE_START(nested namespace creation)
namespace data_structure::meta {}
__DATA_STRUCTURE_END(nested namespace creation)

__DATA_STRUCTURE_START(meta namespace alias)
namespace dsmeta = data_structure::meta;
__DATA_STRUCTURE_END(meta namespace alias)

namespace data_structure::meta {

__DATA_STRUCTURE_START(dynamic)
struct dynamic {
    constexpr dynamic() noexcept = default;
    constexpr dynamic(const dynamic &) noexcept = default;
    constexpr dynamic(dynamic &&) noexcept = default;
    ~dynamic() noexcept = default;
    constexpr dynamic &operator=(const dynamic &) noexcept = default;
    constexpr dynamic &operator=(dynamic &&) noexcept = default;
    template <typename T>
    constexpr dynamic(T) noexcept {}
    template <typename T>
    constexpr operator T() noexcept(is_nothrow_default_constructible<T>::value) {
        return {};
    }
    template <typename T>
    constexpr operator T() const noexcept(is_nothrow_default_constructible<T>::value) {
        return {};
    }
};
template <typename ...>
struct multi_dynamic {
    constexpr multi_dynamic() noexcept = default;
    constexpr multi_dynamic(const multi_dynamic &) noexcept = default;
    constexpr multi_dynamic(multi_dynamic &&) noexcept = default;
    ~multi_dynamic() noexcept = default;
    constexpr multi_dynamic &operator=(const multi_dynamic &) noexcept = default;
    constexpr multi_dynamic &operator=(multi_dynamic &&) noexcept = default;
    template <typename ...Args>
    constexpr multi_dynamic(Args &&...) noexcept {}
    template <typename T>
    constexpr operator T() noexcept(is_nothrow_default_constructible<T>::value) {
        return {};
    }
    template <typename T>
    constexpr operator T() const noexcept(is_nothrow_default_constructible<T>::value) {
        return {};
    }
};
__DATA_STRUCTURE_END(dynamic)

__DATA_STRUCTURE_START(meta fundamentals)
struct nil final {};
struct null final {};

template <typename ...Ts>
struct type_container;
template <>
struct type_container<> {
    using type = type_container<>;
    using remaining = type_container<>;
};
template <typename T>
struct type_container<T> {
    using type = T;
    using remaining = type_container<>;
};
template <typename T, typename ...Ts>
struct type_container<T, Ts...> {
    using type = T;
    using remaining = type_container<Ts...>;
};

template <typename T = nil, typename Pair = nil>
struct type_list {
    using type = T;
    using next = Pair;
};

template <typename First, typename Second>
struct type_pair {
    using first = First;
    using second = Second;
};
__DATA_STRUCTURE_END(meta fundamentals)

__DATA_STRUCTURE_START(meta functions, type operator)
template <typename T, size_t N>
struct choose_argument;
template <size_t N, typename ...Args>
struct choose_argument<type_container<Args...>, N> {
    using type = typename choose_argument<typename type_container<Args...>::remaining, N - 1>::type;
};
template <typename T, typename ...Args>
struct choose_argument<type_container<T, Args...>, 0> {
    using type = T;
};
template <>
struct choose_argument<type_container<>, 0> {
    using type = nil;
};
template <size_t N, typename T, typename Pair>
struct choose_argument<type_list<T, Pair>, N> {
    using type = typename choose_argument<Pair, N - 1>::type;
};
template <typename T, typename Pair>
struct choose_argument<type_list<T, Pair>, 0> {
    using type = T;
};
template <size_t N>
struct choose_argument<type_list<>, N> {
    using type = nil;
};
template <typename First, typename Second>
struct choose_argument<type_pair<First, Second>, 0> {
    using type = First;
};
template <typename First, typename Second>
struct choose_argument<type_pair<First, Second>, 1> {
    using type = Second;
};
template <typename T, size_t N>
using choose_argument_t = typename choose_argument<T, N>::type;
__DATA_STRUCTURE_END(meta functions, type operator)

__DATA_STRUCTURE_START(meta functions, conditional operator)
template <typename BooleanExpression>
struct negation : bool_constant<not BooleanExpression::value> {};
template <typename BooleanExpression>
constexpr inline auto negation_v {negation<BooleanExpression>::value};

template <typename ...>
struct conjunction : true_type {};
template <typename BooleanExpression>
struct conjunction<BooleanExpression> : BooleanExpression {};
template <typename BooleanExpressionLHS, typename BooleanExpressionRHS>
struct conjunction<BooleanExpressionLHS, BooleanExpressionRHS> :
        bool_constant<BooleanExpressionLHS::value and BooleanExpressionRHS::value> {};
template <typename BooleanExpressionLHS, typename BooleanExpressionRHS, typename ...BooleanExpressions>
struct conjunction<BooleanExpressionLHS, BooleanExpressionRHS, BooleanExpressions...> :
        conjunction<conjunction<BooleanExpressionLHS, BooleanExpressionRHS>, BooleanExpressions...> {};
template <typename BooleanExpression, typename ...Expressions>
constexpr inline auto conjunction_v {conjunction<BooleanExpression, Expressions...>::value};

template <typename ...>
struct disjunction : false_type {};
template <typename BooleanExpression>
struct disjunction<BooleanExpression> : BooleanExpression {};
template <typename BooleanExpressionLHS, typename BooleanExpressionRHS>
struct disjunction<BooleanExpressionLHS, BooleanExpressionRHS> :
        bool_constant<BooleanExpressionLHS::value or BooleanExpressionRHS::value> {};
template <typename BooleanExpressionLHS, typename BooleanExpressionRHS, typename ...BooleanExpressions>
struct disjunction<BooleanExpressionLHS, BooleanExpressionRHS, BooleanExpressions...> :
        disjunction<disjunction<BooleanExpressionLHS, BooleanExpressionRHS>, BooleanExpressions...> {};
template <typename BooleanExpression, typename ...Expressions>
constexpr inline auto disjunction_v {disjunction<BooleanExpression, Expressions...>::value};
__DATA_STRUCTURE_END(meta functions, conditional operator)

__DATA_STRUCTURE_START(meta functions, max and min)
template <typename, typename ...>
struct max;
template <typename T, typename ...Args>
using max_t = typename max<T, Args...>::type;
template <typename T>
struct max<T> {
    using type = T;
};
template <typename T, typename U>
struct max<T, U> {
    using type = conditional_t<T::value < U::value, U, T>;
};
template <typename T, typename U, typename ...Args>
struct max<T, U, Args...> : max<max_t<T, U>, Args...> {};

template <typename, typename ...>
struct min;
template <typename T, typename ...Args>
using min_t = typename min<T, Args...>::type;
template <typename T>
struct min<T> {
    using type = T;
};
template <typename T, typename U>
struct min<T, U> {
    using type = conditional_t<T::value < U::value, T, U>;
};
template <typename T, typename U, typename ...Args>
struct min<T, U, Args...> : min<min_t<T, U>, Args...> {};
__DATA_STRUCTURE_END(meta functions, max and min)

}       // namespace data_structure::meta

#endif      // DATA_STRUCTURE_META_HPP