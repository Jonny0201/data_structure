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

#ifndef DATA_STRUCTURE_META_HPP
#define DATA_STRUCTURE_META_HPP

#include "type_traits.hpp"

namespace data_structure {
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

    struct nil final {};
    struct null_type final {};

    template <typename T = nil, typename Pair = nil>
    struct type_list {
        using type = T;
        using next = Pair;
    };
    template <typename First, typename Second>
    struct type_pair {
        using first_type = First;
        using second_type = Second;
    };
}

namespace data_structure {
    template <typename BooleanExpression>
    struct negation : conditional_t<BooleanExpression::value, false_type, true_type> {};
    template <typename BooleanExpression>
    constexpr inline auto negation_v {negation<BooleanExpression>::value};

    template <typename, typename ...>
    struct conjunction : false_type {};
    template <typename BooleanExpression>
    struct conjunction<BooleanExpression> : BooleanExpression {};
    template <typename BooleanExpressionLHS, typename BooleanExpressionRHS>
    struct conjunction<BooleanExpressionLHS, BooleanExpressionRHS> :
            conditional_t<BooleanExpressionLHS::value and BooleanExpressionRHS::value, true_type, false_type> {};
    template <typename BooleanExpressionLHS, typename BooleanExpressionRHS, typename ...BooleanExpressions>
    struct conjunction<BooleanExpressionLHS, BooleanExpressionRHS, BooleanExpressions...> :
            conjunction<conjunction<BooleanExpressionLHS, BooleanExpressionRHS>, BooleanExpressions...> {};
    template <typename BooleanExpression, typename ...Expressions>
    constexpr inline auto conjunction_v {conjunction<BooleanExpression, Expressions...>::value};

    template <typename, typename ...>
    struct disjunction : false_type {};
    template <typename BooleanExpression>
    struct disjunction<BooleanExpression> : BooleanExpression {};
    template <typename BooleanExpressionLHS, typename BooleanExpressionRHS>
    struct disjunction<BooleanExpressionLHS, BooleanExpressionRHS> :
            conditional_t<BooleanExpressionLHS::value or BooleanExpressionRHS::value, true_type, false_type> {};
    template <typename BooleanExpressionLHS, typename BooleanExpressionRHS, typename ...BooleanExpressions>
    struct disjunction<BooleanExpressionLHS, BooleanExpressionRHS, BooleanExpressions...> :
            disjunction<disjunction<BooleanExpressionLHS, BooleanExpressionRHS>, BooleanExpressions...> {};
    template <typename BooleanExpression, typename ...Expressions>
    constexpr inline auto disjunction_v {disjunction<BooleanExpression, Expressions...>::value};
}

namespace data_structure {
    template <typename T, size_t N = 0>
    struct choose_argument;
    template <size_t N, typename ...Args>
    struct choose_argument<type_container<Args...>, N> {
        using type = typename choose_argument<typename type_container<Args...>::remaining, N - 1>::type;
    };
    template <typename ...Args>
    struct choose_argument<type_container<Args...>, 0> {
        using type = typename type_container<Args...>::type;
    };
    template <size_t N, typename T, typename Pair>
    struct choose_argument<type_list<T, Pair>, N> {
        using type = typename choose_argument<Pair, N - 1>::type;
    };
    template <typename T, typename Pair>
    struct choose_argument<type_list<T, Pair>, 0> {
        using type = T;
    };
    template <size_t N, typename T>
    struct choose_argument<type_list<T>, N> {
        using type = T;
    };
    template <size_t N>
    struct choose_argument<type_list<>, N> {
        using type = nil;
    };
    template <typename T, size_t N = 0>
    using choose_argument_t = typename choose_argument<T, N>::type;

    template <typename, typename ...>
    struct find_max;
    template <typename T, typename ...Args>
    using find_max_t = typename find_max<T, Args...>::type;
    template <typename T>
    struct find_max<T> {
        using type = T;
    };
    template <typename T, typename U>
    struct find_max<T, U> {
        using type = conditional_t<T::value < U::value, U, T>;
    };
    template <typename T, typename U, typename ...Args>
    struct find_max<T, U, Args...> : find_max<find_max_t<T, U>, Args...> {};

    template <typename, typename ...>
    struct find_min;
    template <typename T, typename ...Args>
    using find_min_t = typename find_min<T, Args...>::type;
    template <typename T>
    struct find_min<T> {
        using type = T;
    };
    template <typename T, typename U>
    struct find_min<T, U> {
        using type = conditional_t<T::value < U::value, T, U>;
    };
    template <typename T, typename U, typename ...Args>
    struct find_min<T, U, Args...> : find_min<find_min_t<T, U>, Args...> {};
}

#endif //DATA_STRUCTURE_META_HPP
