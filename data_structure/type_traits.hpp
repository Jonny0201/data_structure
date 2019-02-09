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

#ifndef DATA_STRUCTURE_TYPE_TRAITS_HPP
#define DATA_STRUCTURE_TYPE_TRAITS_HPP

/* template parameters
 *
 * O for object
 * F for function
 * T for type, Ts for Types
 * Arg for argument, Args for arguments
 * R for returning type
 *
 */

namespace data_structure {
    inline namespace __data_structure_helper {
        struct __true_type final {
            using value_type = bool;
            constexpr static inline auto value {true};
            constexpr value_type operator()() const noexcept {
                return true;
            }
            constexpr explicit operator value_type() const noexcept {
                return true;
            }
            constexpr __true_type() noexcept = default;
            constexpr __true_type(const __true_type &) noexcept = default;
            constexpr __true_type(__true_type &&) noexcept = default;
            __true_type &operator=(const __true_type &) noexcept = default;
            __true_type &operator=(__true_type &&) noexcept = default;
            ~__true_type() noexcept = default;
        };
        struct __false_type final {
            using value_type = bool;
            constexpr static inline auto value {false};
            constexpr value_type operator()() const noexcept {
                return false;
            }
            constexpr explicit operator value_type() const noexcept {
                return false;
            }
            constexpr __false_type() noexcept = default;
            constexpr __false_type(const __false_type &) noexcept = default;
            constexpr __false_type(__false_type &&) noexcept = default;
            __false_type &operator=(const __false_type &) noexcept = default;
            __false_type &operator=(__false_type &&) noexcept = default;
            ~__false_type() noexcept = default;
        };
    }
    namespace __data_structure_auxiliary {}
    namespace __dsa = __data_structure_auxiliary;
}

namespace data_structure {
    template <typename T>
    struct remove_reference final {
        using result = T;
        using type = T;
    };
    template <typename T>
    struct remove_reference<T &> final {
        using result = T;
        using type = T;
    };
    template <typename T>
    struct remove_reference<T &&> final {
        using result = T;
        using type = T;
    };
    template <typename T>
    struct remove_pointer final {
        using result = T;
        using type = T;
    };
    template <typename T>
    struct remove_pointer<T *> final {
        using result = T;
        using type = T;
    };
    template <typename T>
    struct remove_pointer<T *const> final {
        using result = T;
        using type = T;
    };
    template <typename T>
    struct remove_pointer<T *volatile> final {
        using result = T;
        using type = T;
    };
    template <typename T>
    struct remove_pointer<T *const volatile> final {
        using result = T;
        using type = T;
    };
    template <typename T>
    struct remove_const final {
        using result = T;
        using type = T;
    };
    template <typename T>
    struct remove_const<const T> final {
        using result = T;
        using type = T;
    };
    template <typename T>
    struct remove_volatile final {
        using result = T;
        using type = T;
    };
    template <typename T>
    struct remove_volatile<volatile T> final {
        using result = T;
        using type = T;
    };
    template <typename T>
    struct remove_cv final {
        using result = typename remove_const<typename remove_volatile<T>::result>::result;
        using type = typename remove_const<typename remove_volatile<T>::type>::type;
    };
    template <typename T>
    struct remove_extent final {
        using result = T;
        using type = T;
    };
    template <typename T>
    struct remove_extent<T []> final {
        using result = T;
        using type = T;
    };
    template <typename T, decltype(sizeof 0) N>
    struct remove_extent<T [N]> final {
        using result = T;
        using type = T;
    };
    template <typename T>
    struct remove_all_extents final {
        using result = T;
        using type = T;
    };
    template <typename T>
    struct remove_all_extents<T []> final {
        using result = typename remove_all_extents<T>::result;
        using type = typename remove_all_extents<T>::type;
    };
    template <typename T, decltype(sizeof 0) N>
    struct remove_all_extents<T [N]> final {
        using result = typename remove_all_extents<T>::result;
        using type = typename remove_all_extents<T>::type;
    };
    template <typename T>
    struct remove_const_reference final {
        using result = typename remove_const<typename remove_reference<T>::result>::result;
        using type = typename remove_const<typename remove_reference<T>::type>::type;
    };
    template <typename T>
    struct remove_volatile_reference final {
        using result = typename remove_volatile<typename remove_reference<T>::result>::result;
        using type = typename remove_volatile<typename remove_reference<T>::type>::type;
    };
    template <typename T>
    struct remove_cvreference final {
        using result = typename remove_cv<typename remove_reference<T>::result>::result;
        using type = typename remove_cv<typename remove_reference<T>::type>::type;
    };
    template <typename T>
    struct remove_const_pointer final {
        using result = typename remove_const<typename remove_pointer<T>::result>::result;
        using type = typename remove_const<typename remove_pointer<T>::type>::type;
    };
    template <typename T>
    struct remove_volatile_pointer final {
        using result = typename remove_volatile<typename remove_pointer<T>::result>::result;
        using type = typename remove_volatile<typename remove_pointer<T>::type>::type;
    };
    template <typename T>
    struct remove_cvpointer final {
        using result = typename remove_cv<typename remove_pointer<T>::result>::result;
        using type = typename remove_cv<typename remove_pointer<T>::type>::type;
    };
}

namespace data_structure {
    namespace __data_structure_auxiliary {
        template <typename, typename> struct select_second_type;
        template <typename> struct is_type;
        template <typename T>
        constexpr inline typename select_second_type<T &, __true_type>::result
        test_is_referenceable(int) noexcept {
            static_assert(is_type<T>::value,
                    "The function test_is_referenceable() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename select_second_type<T, __false_type>::result
        test_is_referenceable(...) noexcept {
            static_assert(is_type<T>::value,
                    "The function test_is_referenceable() cannot be called!");
            return {};
        }
        template <typename T>
        struct is_referenceable {
            using value_type = bool;
            using result = decltype(test_is_referenceable<T>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_referenceable<T>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_referenceable<T>::value;
            }
        };
        template <typename T, bool IsReferenceable = is_referenceable<T>::value>
        struct add_lvalue_reference_auxiliary final {
            using result = T &;
            using type = T &;
        };
        template <typename T>
        struct add_lvalue_reference_auxiliary<T, false> final {
            using result = T;
            using type = T;
        };
        template <typename T, bool IsReferenceable = is_referenceable<T>::value>
        struct add_rvalue_reference_auxiliary final {
            using result = T &&;
            using type = T &&;
        };
        template <typename T>
        struct add_rvalue_reference_auxiliary<T, false> final {
            using result = T;
            using type = T;
        };
    }
    template <typename T>
    struct add_lvalue_reference final {
        using result = typename __dsa::add_lvalue_reference_auxiliary<T>::result;
        using type = typename __dsa::add_lvalue_reference_auxiliary<T>::type;
    };
    template <typename T>
    struct add_rvalue_reference final {
        using result = typename __dsa::add_rvalue_reference_auxiliary<T>::result;
        using type = typename __dsa::add_rvalue_reference_auxiliary<T>::type;
    };
    template <typename T>
    struct add_const final {
        using result = const T;
        using type = const T;
    };
    template <typename T>
    struct add_volatile final {
        using result = volatile T;
        using type = volatile T;
    };
    template <typename T>
    struct add_cv final {
        using result = const volatile T;
        using type = const volatile T;
    };
    template <typename T>
    struct add_const_reference final {
        using result = typename add_lvalue_reference<typename add_const<T>::result>::result;
        using type = typename add_lvalue_reference<typename add_const<T>::type>::type;
    };
    template <typename T>
    struct add_volatile_reference final {
        using result = typename add_lvalue_reference<typename add_volatile<T>::result>::result;
        using type = typename add_lvalue_reference<typename add_volatile<T>::type>::type;
    };
    template <typename T>
    struct add_cvreference final {
        using result = typename add_lvalue_reference<typename add_cv<T>::result>::result;
        using type = typename add_lvalue_reference<typename add_cv<T>::type>::type;
    };
    template <typename> struct add_pointer;
    template <typename T>
    struct add_const_pointer final {
        using result = typename add_pointer<typename add_const<T>::result>::result;
        using type = typename add_pointer<typename add_const<T>::type>::type;
    };
    template <typename T>
    struct add_volatile_pointer final {
        using result = typename add_pointer<typename add_volatile<T>::result>::result;
        using type = typename add_pointer<typename add_volatile<T>::type>::type;
    };
    template <typename T>
    struct add_cvpointer final {
        using result = typename add_pointer<typename add_cv<T>::result>::result;
        using type = typename add_pointer<typename add_cv<T>::type>::type;
    };
}

namespace data_structure {
    template <typename T>
    constexpr inline typename remove_reference<T>::type &&move(T &&value) noexcept {
        return static_cast<typename remove_reference<T>::type &&>(value);
    }
    template <typename T>
    constexpr inline T &&forward(typename remove_reference<T>::type &value) noexcept {
        return static_cast<typename remove_reference<T>::type &&>(value);
    }
    template <typename> struct is_lvalue_reference;
    template <typename T>
    constexpr inline T &&forward(typename remove_reference<T>::type &&value) noexcept {
        static_assert(is_lvalue_reference<T>::value, "Cannot forward an rvalue as an lvalue!");
        return static_cast<typename remove_reference<T>::type &&>(value);
    }
}

namespace data_structure {
    template <bool, typename If, typename Then>
    struct conditional final {
        using result = If;
        using type = If;
    };
    template <typename If, typename Then>
    struct conditional<false, If, Then> final {
        using result = Then;
        using type = Then;
    };
    template <bool, typename T = void>
    struct enable_if final {
        using result = T;
        using type = T;
    };
    template <typename T>
    struct enable_if<false, T> final {};
    template <typename ...>
    using void_t = void;
    template <typename ...>
    struct conjunction final {
        using result = __true_type;
        using type = result;
    };
    template <typename BooleanExpression>
    struct conjunction<BooleanExpression> final {
        using result = typename BooleanExpression::result;
        using type = result;
    };
    template <typename BooleanExpression_1, typename ...BooleanExpression_N>
    struct conjunction<BooleanExpression_1, BooleanExpression_N...> final {
        using result = typename conditional<
                static_cast<bool>(typename BooleanExpression_1::result()),
                typename conjunction<BooleanExpression_N...>::result,
                typename BooleanExpression_1::result>::result;
        using type = result;
    };
    template <typename ...>
    struct disjunction final {
        using result = __false_type;
        using type = result;
    };
    template <typename BooleanExpression>
    struct disjunction<BooleanExpression> final {
        using result = typename BooleanExpression::result;
        using type = result;
    };
    template <typename BooleanExpression_1, typename ...BooleanExpression_N>
    struct disjunction<BooleanExpression_1, BooleanExpression_N...> final {
        using result = typename conditional<
                static_cast<bool>(typename BooleanExpression_1::result()),
                typename BooleanExpression_1::result,
                typename disjunction<BooleanExpression_N...>::result>::result;
        using type = result;
    };
    template <typename BooleanExpression>
    struct negation final {
        using result = typename conditional<
                static_cast<bool>(typename BooleanExpression::result()),
                __false_type, __true_type>::result;
        using type = result;
    };
}

namespace data_structure {
    template <typename Type_1, typename Type_2>
    struct is_same {
        using value_type = bool;
        using result = __false_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_same<Type_1, Type_2>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_same<Type_1, Type_2>::value;
        }
    };
    template <typename T>
    struct is_same<T, T> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_same<T, T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_same<T, T>::value;
        }
    };
    template <typename T>
    struct is_integral {
        using value_type = bool;
        using result = __false_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<T>::value;
        }
    };
    template <>
    struct is_integral<bool> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<bool>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<bool>::value;
        }
    };
    template <>
    struct is_integral<const bool> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<const bool>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<const bool>::value;
        }
    };
    template <>
    struct is_integral<volatile bool> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<volatile bool>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<volatile bool>::value;
        }
    };
    template <>
    struct is_integral<const volatile bool> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<const volatile bool>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<const volatile bool>::value;
        }
    };
    template <>
    struct is_integral<short int> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<short int>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<short int>::value;
        }
    };
    template <>
    struct is_integral<const short int> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<const short int>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<const short int>::value;
        }
    };
    template <>
    struct is_integral<volatile short int> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<volatile short int>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<volatile short int>::value;
        }
    };
    template <>
    struct is_integral<const volatile short int> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<const volatile short int>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<const volatile short int>::value;
        }
    };
    template <>
    struct is_integral<unsigned short int> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<unsigned short int>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<unsigned short int>::value;
        }
    };
    template <>
    struct is_integral<const unsigned short int> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<const unsigned short int>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<const unsigned short int>::value;
        }
    };
    template <>
    struct is_integral<volatile unsigned short int> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<volatile unsigned short int>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<volatile unsigned short int>::value;
        }
    };
    template <>
    struct is_integral<const volatile unsigned short int> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<const volatile unsigned short int>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<const volatile unsigned short int>::value;
        }
    };
    template <>
    struct is_integral<int> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<int>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<int>::value;
        }
    };
    template <>
    struct is_integral<const int> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<const int>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<const int>::value;
        }
    };
    template <>
    struct is_integral<volatile int> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<volatile int>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<volatile int>::value;
        }
    };
    template <>
    struct is_integral<const volatile int> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<const volatile int>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<const volatile int>::value;
        }
    };
    template <>
    struct is_integral<unsigned int> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<unsigned int>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<unsigned int>::value;
        }
    };
    template <>
    struct is_integral<const unsigned int> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<const unsigned int>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<const unsigned int>::value;
        }
    };
    template <>
    struct is_integral<volatile unsigned int> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<volatile unsigned int>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<volatile unsigned int>::value;
        }
    };
    template <>
    struct is_integral<const volatile unsigned int> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<const volatile unsigned int>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<const volatile unsigned int>::value;
        }
    };
    template <>
    struct is_integral<long int> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<long int>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<long int>::value;
        }
    };
    template <>
    struct is_integral<const long int> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<const long int>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<const long int>::value;
        }
    };
    template <>
    struct is_integral<volatile long int> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<volatile long int>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<volatile long int>::value;
        }
    };
    template <>
    struct is_integral<const volatile long int> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<const volatile long int>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<const volatile long int>::value;
        }
    };
    template <>
    struct is_integral<unsigned long int> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<unsigned long int>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<unsigned long int>::value;
        }
    };
    template <>
    struct is_integral<const unsigned long int> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<const unsigned long int>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<const unsigned long int>::value;
        }
    };
    template <>
    struct is_integral<volatile unsigned long int> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<volatile unsigned long int>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<volatile unsigned long int>::value;
        }
    };
    template <>
    struct is_integral<const volatile unsigned long int> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<const volatile unsigned long int>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<const volatile unsigned long int>::value;
        }
    };
    template <>
    struct is_integral<long long int> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<long long int>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<long long int>::value;
        }
    };
    template <>
    struct is_integral<const long long int> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<const long long int>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<const long long int>::value;
        }
    };
    template <>
    struct is_integral<volatile long long int> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<volatile long long int>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<volatile long long int>::value;
        }
    };
    template <>
    struct is_integral<const volatile long long int> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<const volatile long long int>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<const volatile long long int>::value;
        }
    };
    template <>
    struct is_integral<unsigned long long int> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<unsigned long long int>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<unsigned long long int>::value;
        }
    };
    template <>
    struct is_integral<const unsigned long long int> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<const unsigned long long int>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<const unsigned long long int>::value;
        }
    };
    template <>
    struct is_integral<volatile unsigned long long int> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<volatile unsigned long long int>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<volatile unsigned long long int>::value;
        }
    };
    template <>
    struct is_integral<const volatile unsigned long long int> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<const volatile unsigned long long int>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<const volatile unsigned long long int>::value;
        }
    };
    template <>
    struct is_integral<char> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<char>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<char>::value;
        }
    };
    template <>
    struct is_integral<const char> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<const char>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<const char>::value;
        }
    };
    template <>
    struct is_integral<volatile char> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<volatile char>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<volatile char>::value;
        }
    };
    template <>
    struct is_integral<const volatile char> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<const volatile char>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<const volatile char>::value;
        }
    };
    template <>
    struct is_integral<unsigned char> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<unsigned char>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<unsigned char>::value;
        }
    };
    template <>
    struct is_integral<const unsigned char> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<const unsigned char>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<const unsigned char>::value;
        }
    };
    template <>
    struct is_integral<volatile unsigned char> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<volatile unsigned char>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<volatile unsigned char>::value;
        }
    };
    template <>
    struct is_integral<const volatile unsigned char> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<const volatile unsigned char>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<const volatile unsigned char>::value;
        }
    };
    template <>
    struct is_integral<wchar_t> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<wchar_t>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<wchar_t>::value;
        }
    };
    template <>
    struct is_integral<const wchar_t> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<const wchar_t>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<const wchar_t>::value;
        }
    };
    template <>
    struct is_integral<volatile wchar_t> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<volatile wchar_t>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<volatile wchar_t>::value;
        }
    };
    template <>
    struct is_integral<const volatile wchar_t> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<const volatile wchar_t>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<const volatile wchar_t>::value;
        }
    };
    template <>
    struct is_integral<char16_t> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<char16_t>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<char16_t>::value;
        }
    };
    template <>
    struct is_integral<const char16_t> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<const char16_t>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<const char16_t>::value;
        }
    };
    template <>
    struct is_integral<volatile char16_t> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<volatile char16_t>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<volatile char16_t>::value;
        }
    };
    template <>
    struct is_integral<const volatile char16_t> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<const volatile char16_t>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<const volatile char16_t>::value;
        }
    };
    template <>
    struct is_integral<char32_t> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<char32_t>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<char32_t>::value;
        }
    };
    template <>
    struct is_integral<const char32_t> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<const char32_t>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<const char32_t>::value;
        }
    };
    template <>
    struct is_integral<volatile char32_t> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<volatile char32_t>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<volatile char32_t>::value;
        }
    };
    template <>
    struct is_integral<const volatile char32_t> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<const volatile char32_t>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<const volatile char32_t>::value;
        }
    };
    template <>
    struct is_integral<__int128 /* __int128_t */> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<__int128>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<__int128>::value;
        }
    };
    template <>
    struct is_integral<const __int128 /* const __int128_t */> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<const __int128>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<const __int128>::value;
        }
    };
    template <>
    struct is_integral<volatile __int128 /* volatile __int128_t */> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<volatile __int128>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<volatile __int128>::value;
        }
    };
    template <>
    struct is_integral<const volatile __int128 /* const volatile __int128_t */> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<const volatile __int128>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<const volatile __int128>::value;
        }
    };
    template <>
    struct is_integral<__uint128_t> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<__uint128_t>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<__uint128_t>::value;
        }
    };
    template <>
    struct is_integral<const __uint128_t> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<const __uint128_t>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<const __uint128_t>::value;
        }
    };
    template <>
    struct is_integral<volatile __uint128_t> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<volatile __uint128_t>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<volatile __uint128_t>::value;
        }
    };
    template <>
    struct is_integral<const volatile __uint128_t> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_integral<const volatile __uint128_t>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_integral<const volatile __uint128_t>::value;
        }
    };
    template <typename T>
    struct is_floating_point {
        using value_type = bool;
        using result = __false_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_floating_point<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_floating_point<T>::value;
        }
    };
    template <>
    struct is_floating_point<float> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_floating_point<float>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_floating_point<float>::value;
        }
    };
    template <>
    struct is_floating_point<const float> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_floating_point<const float>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_floating_point<const float>::value;
        }
    };
    template <>
    struct is_floating_point<volatile float> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_floating_point<volatile float>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_floating_point<volatile float>::value;
        }
    };
    template <>
    struct is_floating_point<const volatile float> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_floating_point<const volatile float>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_floating_point<const volatile float>::value;
        }
    };
    template <>
    struct is_floating_point<double> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_floating_point<double>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_floating_point<double>::value;
        }
    };
    template <>
    struct is_floating_point<const double> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_floating_point<const double>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_floating_point<const double>::value;
        }
    };
    template <>
    struct is_floating_point<volatile double> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_floating_point<volatile double>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_floating_point<volatile double>::value;
        }
    };
    template <>
    struct is_floating_point<const volatile double> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_floating_point<const volatile double>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_floating_point<const volatile double>::value;
        }
    };
    template <>
    struct is_floating_point<long double> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_floating_point<long double>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_floating_point<long double>::value;
        }
    };
    template <>
    struct is_floating_point<const long double> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_floating_point<const long double>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_floating_point<const long double>::value;
        }
    };
    template <>
    struct is_floating_point<volatile long double> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_floating_point<volatile long double>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_floating_point<volatile long double>::value;
        }
    };
    template <>
    struct is_floating_point<const volatile long double> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_floating_point<const volatile long double>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_floating_point<const volatile long double>::value;
        }
    };
    template <typename T>
    struct is_array {
        using value_type = bool;
        using result = __false_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_array<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_array<T>::value;
        }
    };
    template <typename T>
    struct is_array<T []> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_array<T []>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_array<T []>::value;
        }
    };
    template <typename T, decltype(sizeof 0) N>
    struct is_array<T [N]> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_array<T [N]>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_array<T [N]>::value;
        }
    };
    template <typename T>
    struct is_enum {
        using value_type = bool;
        using result = typename conditional<__is_enum(T), __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_enum<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_enum<T>::value;
        }
    };
    template <typename T>
    struct is_union {
        using value_type = bool;
        using result = typename conditional<__is_union(T), __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_union<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_union<T>::value;
        }
    };
    template <typename T>
    struct is_class {
        using value_type = bool;
        using result = typename conditional<__is_class(T), __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_class<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_class<T>::value;
        }
    };
    template <typename T>
    struct is_function {
        using value_type = bool;
        using result = __false_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<T>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args...)> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args...)>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args...)>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args..., ...)> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args..., ...)>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args..., ...)>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args...) const> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args...) const>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args...) const>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args...) volatile> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args...) volatile>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args...) volatile>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args...) const volatile> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args...) const volatile>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args...) const volatile>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args..., ...) const> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args..., ...) const>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args..., ...) const>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args..., ...) volatile> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args..., ...) volatile>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args..., ...) volatile>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args..., ...) const volatile> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args..., ...) const volatile>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args..., ...) const volatile>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args...) &> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args...) &>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args...) &>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args...) const &> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args...) const &>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args...) const &>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args...) volatile &> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args...) volatile &>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args...) volatile &>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args...) const volatile &> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args...) const volatile &>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args...) const volatile &>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args..., ...) &> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args..., ...) &>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args..., ...) &>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args..., ...) const &> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args..., ...) const &>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args..., ...) const &>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args..., ...) volatile &> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args..., ...) volatile &>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args..., ...) volatile &>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args..., ...) const volatile &> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args..., ...) const volatile &>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args..., ...) const volatile &>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args...) &&> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args...) &&>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args...) &&>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args...) const &&> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args...) const &&>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args...) const &&>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args...) volatile &&> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args...) volatile &&>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args...) volatile &&>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args...) const volatile &&> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args...) const volatile &&>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args...) const volatile &&>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args..., ...) &&> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args..., ...) &&>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args..., ...) &&>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args..., ...) const &&> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args..., ...) const &&>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args..., ...) const &&>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args..., ...) volatile &&> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args..., ...) volatile &&>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args..., ...) volatile &&>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args..., ...) const volatile &&> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args..., ...) const volatile &&>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args..., ...) const volatile &&>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args...) noexcept> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args...) noexcept>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args...) noexcept>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args..., ...) noexcept> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args..., ...) noexcept>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args..., ...) noexcept>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args...) const noexcept> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args...) const noexcept>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args...) const noexcept>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args...) volatile noexcept> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args...) volatile noexcept>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args...) volatile noexcept>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args...) const volatile noexcept> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args...) const volatile noexcept>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args...) const volatile noexcept>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args..., ...) const noexcept> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args..., ...) const noexcept>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args..., ...) const noexcept>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args..., ...) volatile noexcept> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args..., ...) volatile noexcept>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args..., ...) volatile noexcept>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args..., ...) const volatile noexcept> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args..., ...) const volatile noexcept>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args..., ...) const volatile noexcept>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args...) & noexcept> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args...) & noexcept>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args...) & noexcept>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args...) const & noexcept> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args...) const & noexcept>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args...) const & noexcept>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args...) volatile & noexcept> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args...) volatile & noexcept>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args...) volatile & noexcept>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args...) const volatile & noexcept> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args...) const volatile & noexcept>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args...) const volatile & noexcept>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args..., ...) & noexcept> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args..., ...) & noexcept>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args..., ...) & noexcept>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args..., ...) const & noexcept> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args..., ...) const & noexcept>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args..., ...) const & noexcept>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args..., ...) volatile & noexcept> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args..., ...) volatile & noexcept>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args..., ...) volatile & noexcept>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args..., ...) const volatile & noexcept> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args..., ...) const volatile & noexcept>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args..., ...) const volatile & noexcept>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args...) && noexcept> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args...) && noexcept>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args...) && noexcept>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args...) const && noexcept> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args...) const && noexcept>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args...) const && noexcept>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args...) volatile && noexcept> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args...) volatile && noexcept>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args...) volatile && noexcept>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args...) const volatile && noexcept> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args...) const volatile && noexcept>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args...) const volatile && noexcept>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args..., ...) && noexcept> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args..., ...) && noexcept>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args..., ...) && noexcept>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args..., ...) const && noexcept> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args..., ...) const && noexcept>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args..., ...) const && noexcept>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args..., ...) volatile && noexcept> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args..., ...) volatile && noexcept>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args..., ...) volatile && noexcept>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_function<F(Args..., ...) const volatile && noexcept> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_function<F(Args..., ...) const volatile && noexcept>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_function<F(Args..., ...) const volatile && noexcept>::value;
        }
    };
    template <typename T>
    struct is_pointer {
        using value_type = bool;
        using result = __false_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_pointer<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_pointer<T>::value;
        }
    };
    template <typename T>
    struct is_pointer<T *> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_pointer<T *>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_pointer<T *>::value;
        }
    };
    template <typename T>
    struct is_pointer<T *const> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_pointer<T *const>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_pointer<T *const>::value;
        }
    };
    template <typename T>
    struct is_pointer<T *volatile> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_pointer<T *volatile>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_pointer<T *volatile>::value;
        }
    };
    template <typename T>
    struct is_pointer<T *const volatile> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_pointer<T *const volatile>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_pointer<T *const volatile>::value;
        }
    };
    template <typename T>
    struct is_lvalue_reference {
        using value_type = bool;
        using result = __false_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_lvalue_reference<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_lvalue_reference<T>::value;
        }
    };
    template <typename T>
    struct is_lvalue_reference<T &> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_lvalue_reference<T &>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_lvalue_reference<T &>::value;
        }
    };
    template <typename T>
    struct is_rvalue_reference {
        using value_type = bool;
        using result = __false_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_rvalue_reference<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_rvalue_reference<T>::value;
        }
    };
    template <typename T>
    struct is_rvalue_reference<T &&> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_rvalue_reference<T &&>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_rvalue_reference<T &&>::value;
        }
    };
    template <typename T>
    struct is_reference {
        using value_type = bool;
        using result = typename conditional<is_lvalue_reference<T>::value or is_rvalue_reference<T>::value,
                __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_reference<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_reference<T>::value;
        }
    };
    template <typename T>
    struct is_member_pointer {
        using value_type = bool;
        using result = __false_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_member_pointer<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_member_pointer<T>::value;
        }
    };
    template <typename T, typename Class>
    struct is_member_pointer<T Class::*> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_member_pointer<T Class::*>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_member_pointer<T Class::*>::value;
        }
    };
    template <typename T, typename Class>
    struct is_member_pointer<T Class::*const> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_member_pointer<T Class::*const>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_member_pointer<T Class::*const>::value;
        }
    };
    template <typename T, typename Class>
    struct is_member_pointer<T Class::*volatile> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_member_pointer<T Class::*volatile>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_member_pointer<T Class::*volatile>::value;
        }
    };
    template <typename T, typename Class>
    struct is_member_pointer<T Class::*const volatile> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_member_pointer<T Class::*const volatile>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_member_pointer<T Class::*const volatile>::value;
        }
    };
    template <typename T>
    struct is_member_function_pointer {
        using value_type = bool;
        using result = __false_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_member_function_pointer<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_member_function_pointer<T>::value;
        }
    };
    template <typename T, typename Class>
    struct is_member_function_pointer<T Class::*> {
        using value_type = bool;
        using result = typename conditional<is_function<T>::value, __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_member_function_pointer<T Class::*>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_member_function_pointer<T Class::*>::value;
        }
    };
    template <typename T, typename Class>
    struct is_member_function_pointer<T Class::*const> {
        using value_type = bool;
        using result = typename conditional<is_function<T>::value, __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_member_function_pointer<T Class::*const>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_member_function_pointer<T Class::*const>::value;
        }
    };
    template <typename T, typename Class>
    struct is_member_function_pointer<T Class::*volatile> {
        using value_type = bool;
        using result = typename conditional<is_function<T>::value, __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_member_function_pointer<T Class::*volatile>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_member_function_pointer<T Class::*volatile>::value;
        }
    };
    template <typename T, typename Class>
    struct is_member_function_pointer<T Class::*const volatile> {
        using value_type = bool;
        using result = typename conditional<is_function<T>::value, __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_member_function_pointer<T Class::*const volatile>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_member_function_pointer<T Class::*const volatile>::value;
        }
    };
    template <typename T>
    struct is_member_object_pointer {
        using value_type = bool;
        using result = typename conditional<
                is_member_pointer<T>::value and not is_member_function_pointer<T>::value,
                __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_member_object_pointer<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_member_object_pointer<T>::value;
        }
    };
    template <typename T>
    struct is_null_pointer {
        using value_type = bool;
        using result = __false_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_null_pointer<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_null_pointer<T>::value;
        }
    };
    template <>
    struct is_null_pointer<decltype(nullptr)> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_null_pointer<decltype(nullptr)>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_null_pointer<decltype(nullptr)>::value;
        }
    };
    template <>
    struct is_null_pointer<const decltype(nullptr)> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_null_pointer<const decltype(nullptr)>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_null_pointer<const decltype(nullptr)>::value;
        }
    };
    template <>
    struct is_null_pointer<volatile decltype(nullptr)> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_null_pointer<volatile decltype(nullptr)>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_null_pointer<volatile decltype(nullptr)>::value;
        }
    };
    template <>
    struct is_null_pointer<const volatile decltype(nullptr)> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_null_pointer<const volatile decltype(nullptr)>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_null_pointer<const volatile decltype(nullptr)>::value;
        }
    };
    template <typename T>
    struct is_void {
        using value_type = bool;
        using result = __false_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_void<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_void<T>::value;
        }
    };
    template <>
    struct is_void<void> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_void<void>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_void<void>::value;
        }
    };
    template <>
    struct is_void<const void> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_void<const void>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_void<const void>::value;
        }
    };
    template <>
    struct is_void<volatile void> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_void<volatile void>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_void<volatile void>::value;
        }
    };
    template <>
    struct is_void<const volatile void> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_void<const volatile void>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_void<const volatile void>::value;
        }
    };
    template <typename T>
    struct is_arithmetic {
        using value_type = bool;
        using result = typename conditional<is_integral<T>::value or is_floating_point<T>::value,
                __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_arithmetic<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_arithmetic<T>::value;
        }
    };
    template <typename T>
    struct is_fundamental {
        using value_type = bool;
        using result = typename conditional<
                is_arithmetic<T>::value or is_null_pointer<T>::value or is_void<T>::value,
                __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<bool>(result())};
        constexpr value_type operator()() const noexcept {
            return is_fundamental<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_fundamental<T>::value;
        }
    };
    template <typename T>
    struct is_scalar {
        using value_type = bool;
        using result = typename conditional<
                is_arithmetic<T>::value or is_enum<T>::value or is_pointer<T>::value or
                is_member_pointer<T>::value or is_null_pointer<T>::value,
                __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<bool>(result())};
        constexpr value_type operator()() const noexcept {
            return is_scalar<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_scalar<T>::value;
        }
    };
    template <typename T>
    struct is_object {
        using value_type = bool;
        using result = typename conditional<is_scalar<T>::value or is_array<T>::value or
                is_union<T>::value or is_class<T>::value, __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<bool>(result())};
        constexpr value_type operator()() const noexcept {
            return is_object<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_scalar<T>::value;
        }
    };
    template <typename T>
    struct is_compound {
        using value_type = bool;
        using result = typename conditional<not is_fundamental<T>::value, __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<bool>(result())};
        constexpr value_type operator()() const noexcept {
            return is_compound<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_compound<T>::value;
        }
    };
    template <typename T>
    struct is_const {
        using value_type = bool;
        using result = __false_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_const<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_const<T>::value;
        }
    };
    template <typename T>
    struct is_const<const T> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_const<const T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_const<const T>::value;
        }
    };
    template <typename T>
    struct is_volatile {
        using value_type = bool;
        using result = __false_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_volatile<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_volatile<T>::value;
        }
    };
    template <typename T>
    struct is_volatile<volatile T> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_volatile<volatile T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_volatile<volatile T>::value;
        }
    };
    template <typename T>
    struct is_standard_layout {
        using value_type = bool;
        using result = typename conditional<__is_standard_layout(T), __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_standard_layout<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_standard_layout<T>::value;
        }
    };
    template <typename T>
    struct is_pod {
        using value_type = bool;
        using result = typename conditional<__is_pod(T), __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_pod<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_pod<T>::value;
        }
    };
    template <typename T>
    struct is_literal {
        using value_type = bool;
        using result = typename conditional<
#if defined(__GNUC__) && not defined(__clang__)
                __is_literal_type(T),
#else
                __is_literal(T),
#endif
                __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_literal<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_literal<T>::value;
        }
    };
    template <typename T>
    struct is_empty {
        using value_type = bool;
        using result = typename conditional<__is_empty(T), __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_empty<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_empty<T>::value;
        }
    };
#if false
    namespace __data_structure_0 {
        template <typename T>
        struct is_empty_auxiliary0 : public T {
            double var;
        };
        struct is_empty_auxiliary1 {
            double var;
        };
        template <typename T>
        struct is_empty {
            using value_type = bool;
            using result = typename conditional<
                    sizeof(is_empty_auxiliary0<T>) == sizeof(is_empty_auxiliary1),
                    __true_type, __false_type>::result;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_empty<T>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_empty<T>::value;
            }
        };
    }
#endif
    template <typename T>
    struct is_polymorphic {
        using value_type = bool;
        using result = typename conditional<__is_polymorphic(T), __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_polymorphic<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_polymorphic<T>::value;
        }
    };
    template <typename T>
    struct is_abstract {
        using value_type = bool;
        using result = typename conditional<__is_abstract(T), __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_abstract<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_abstract<T>::value;
        }
    };
    template <typename T>
    struct is_final {
        using value_type = bool;
        using result = typename conditional<__is_final(T), __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_final<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_final<T>::value;
        }
    };
    template <typename T>
    struct is_aggregate {
        using value_type = bool;
        using result = typename conditional<__is_aggregate(T), __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_aggregate<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_aggregate<T>::value;
        }
    };
    template <typename T>
    struct is_trivially_copyable {
        using value_type = bool;
        using result = typename conditional<__is_trivially_copyable(T), __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_trivially_copyable<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_trivially_copyable<T>::value;
        }
    };
    template <typename T, typename ...Args>
    struct is_constructible {
        using value_type = bool;
        using result = typename conditional<__is_constructible(T, Args...), __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_constructible<T, Args...>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_constructible<T, Args...>::value;
        }
    };
    template <typename T, typename ...Args>
    struct is_trivially_constructible {
        using value_type = bool;
        using result = __false_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_trivially_constructible<T, Args...>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_trivially_constructible<T, Args...>::value;
        }
    };
    template <typename T>
    struct is_trivially_constructible<T> {
        using value_type = bool;
        using result = typename conditional<__has_trivial_constructor(T), __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_trivially_constructible<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_trivially_constructible<T>::value;
        }
    };
    template <typename T>
    struct is_trivially_constructible<T, T &> {
        using value_type = bool;
        using result = typename conditional<
                __is_trivially_constructible(T, T &), __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_trivially_constructible<T, T &>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_trivially_constructible<T, T &>::value;
        }
    };
    template <typename T>
    struct is_trivially_constructible<T, const T &> {
        using value_type = bool;
        using result = typename conditional<
                __is_trivially_constructible(T, const T &), __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_trivially_constructible<T, const T &>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_trivially_constructible<T, const T &>::value;
        }
    };
    template <typename T>
    struct is_trivially_constructible<T, T &&> {
        using value_type = bool;
        using result = typename conditional<
                __is_trivially_constructible(T, T &&), __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_trivially_constructible<T, T &&>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_trivially_constructible<T, T &&>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename T>
        struct is_type {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_type<T>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_type<T>::value;
            }
        };
        template <typename T>
        constexpr inline typename add_rvalue_reference<T>::type declval() noexcept {
            static_assert(not is_type<T>::value, "The function declval() cannot be called!");
            return {};
        }
        template <bool IsConstructible, bool IsReference, typename T, typename ...Args>
        struct is_nothrow_constructible_auxiliary {
            static_assert(not is_type<T>::value, "Invalid template arguments!");
        };
        template <typename T, typename ...Args>
        struct is_nothrow_constructible_auxiliary<true, false, T, Args...> {
            using value_type = bool;
            using result = typename conditional<
                    noexcept(T(declval<Args>()...)),
                    __true_type, __false_type>::result;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_nothrow_constructible_auxiliary<true, false, T, Args...>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_nothrow_constructible_auxiliary<true, false, T, Args...>::value;
            }
        };
        template <typename T, typename Arg>
        struct is_nothrow_constructible_auxiliary<true, true, T, Arg> {
            using value_type = bool;
            using result = typename conditional<
                    noexcept(T(declval<Arg>())),
                    __true_type, __false_type>::result;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_nothrow_constructible_auxiliary<true, true, T, Arg>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_nothrow_constructible_auxiliary<true, true, T, Arg>::value;
            }
        };
        template <bool IsReference, typename T, typename ...Args>
        struct is_nothrow_constructible_auxiliary<false, IsReference, T, Args...> {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_nothrow_constructible_auxiliary<false, IsReference, T, Args...>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_nothrow_constructible_auxiliary<false, IsReference, T, Args...>::value;
            }
        };
    }
    template <typename T, typename ...Args>
    struct is_nothrow_constructible {
        using value_type = bool;
        using result = typename conditional<__dsa::is_nothrow_constructible_auxiliary<
                    is_constructible<T, Args...>::value, is_reference<T>::value, T, Args...>::value,
                __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_nothrow_constructible<T, Args...>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_nothrow_constructible<T, Args...>::value;
        }
    };
    template <typename T>
    struct is_default_constructible {
        using value_type = bool;
        using result = typename is_constructible<T>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_default_constructible<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_default_constructible<T>::value;
        }
    };
    template <typename T>
    struct is_trivially_default_constructible {
        using value_type = bool;
        using result = typename is_trivially_constructible<T>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_trivially_default_constructible<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_trivially_default_constructible<T>::value;
        }
    };
    template <typename T>
    struct is_nothrow_default_constructible {
        using value_type = bool;
        using result = typename is_nothrow_constructible<T>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_nothrow_default_constructible<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_nothrow_default_constructible<T>::value;
        }
    };
    template <typename T>
    struct is_copy_constructible {
        using value_type = bool;
        using result = typename is_constructible<T, const T &>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_copy_constructible<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_copy_constructible<T>::value;
        }
    };
    template <typename T>
    struct is_trivially_copy_constructible {
        using value_type = bool;
        using result = typename is_trivially_constructible<T, const T &>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_trivially_copy_constructible<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_trivially_copy_constructible<T>::value;
        }
    };
    template <typename T>
    struct is_nothrow_copy_constructible {
        using value_type = bool;
        using result = typename is_nothrow_constructible<T, const T &>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_nothrow_copy_constructible<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_nothrow_copy_constructible<T>::value;
        }
    };
    template <typename T>
    struct is_move_constructible {
        using value_type = bool;
        using result = typename is_constructible<T, T &&>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_move_constructible<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_move_constructible<T>::value;
        }
    };
    template <typename T>
    struct is_trivially_move_constructible {
        using value_type = bool;
        using result = typename is_trivially_constructible<T, T &&>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_trivially_move_constructible<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_trivially_move_constructible<T>::value;
        }
    };
    template <typename T>
    struct is_nothrow_move_constructible {
        using value_type = bool;
        using result = typename is_nothrow_constructible<T, T &&>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_nothrow_move_constructible<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_nothrow_move_constructible<T>::value;
        }
    };
    template <typename T>
    struct is_trivial {
        using value_type = bool;
        using result = typename conditional<
                is_trivially_copyable<T>::value and is_trivially_default_constructible<T>::value,
                __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_trivial<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_trivial<T>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename, typename T>
        struct select_second_type {
            using type = T;
            using result = T;
        };
        template <typename T, typename Arg>
        inline constexpr
        typename select_second_type<decltype((declval<T>() = declval<Arg>())), __true_type>::type
        is_assignable_test(int) noexcept {
            static_assert(not is_type<T>::value, "The function is_assignable_test() cannot be called!");
        }
        template <typename, typename Arg>
        inline constexpr
        typename select_second_type<Arg, __false_type>::type
        is_assignable_test(...) noexcept {
            static_assert(not is_type<Arg>::value, "The function is_assignable_test() cannot be called!");
        }
        template <typename T, typename Arg, bool IsVoidType = is_void<T>::value or is_void<Arg>::value>
        struct is_assignable_auxiliary {
            using value_type = bool;
            using result = decltype(is_assignable_test<T, Arg>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_assignable_auxiliary<T, Arg, IsVoidType>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_assignable_auxiliary<T, Arg, IsVoidType>::value;
            }
        };
        template <typename T, typename Arg>
        struct is_assignable_auxiliary<T, Arg, true> {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_assignable_auxiliary<T, Arg, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_assignable_auxiliary<T, Arg, true>::value;
            }
        };
    }
    template <typename T, typename Arg>
    struct is_assignable {
        using value_type = bool;
        using result = typename __dsa::is_assignable_auxiliary<T, Arg>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_assignable<T, Arg>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_assignable<T, Arg>::value;
        }
    };
    template <typename T, typename Arg>
    struct is_trivially_assignable {
        using value_type = bool;
        using result = typename conditional<__is_trivially_assignable(T, Arg), __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_trivially_assignable<T, Arg>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_trivially_assignable<T, Arg>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename T, typename Arg, bool IsAssignable = is_assignable<T, Arg>::value>
        struct is_nothrow_assignable_auxiliary {
            using value_type = bool;
            using result = typename conditional<
                    noexcept(declval<T>() = declval<Arg>()),
                    __true_type, __false_type>::result;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_nothrow_assignable_auxiliary<T, Arg, IsAssignable>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_nothrow_assignable_auxiliary<T, Arg, IsAssignable>::value;
            }
        };
        template <typename T, typename Arg>
        struct is_nothrow_assignable_auxiliary<T, Arg, false> {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_nothrow_assignable_auxiliary<T, Arg, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_nothrow_assignable_auxiliary<T, Arg, false>::value;
            }
        };
    }
    template <typename T, typename Arg>
    struct is_nothrow_assignable {
        using value_type = bool;
        using result = typename __dsa::is_nothrow_assignable_auxiliary<T, Arg>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_nothrow_assignable<T, Arg>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_nothrow_assignable<T, Arg>::value;
        }
    };
    template <typename T>
    struct is_copy_assignable {
        using value_type = bool;
        using result = typename is_assignable<
                typename add_lvalue_reference<T>::type,
                typename add_lvalue_reference<T>::type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_copy_assignable<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_copy_assignable<T>::value;
        }
    };
    template <typename T>
    struct is_trivially_copy_assignable {
        using value_type = bool;
        using result = typename is_trivially_assignable<
                typename add_lvalue_reference<T>::type,
                typename add_lvalue_reference<T>::type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_trivially_copy_assignable<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_trivially_copy_assignable<T>::value;
        }
    };
    template <typename T>
    struct is_nothrow_copy_assignable {
        using value_type = bool;
        using result = typename is_nothrow_assignable<
                typename add_lvalue_reference<T>::type,
                typename add_lvalue_reference<T>::type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_nothrow_copy_assignable<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_nothrow_copy_assignable<T>::value;
        }
    };
    template <typename T>
    struct is_move_assignable {
        using value_type = bool;
        using result = typename is_assignable<
                typename add_lvalue_reference<T>::type,
                typename add_rvalue_reference<T>::type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_move_assignable<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_move_assignable<T>::value;
        }
    };
    template <typename T>
    struct is_trivially_move_assignable {
        using value_type = bool;
        using result = typename is_trivially_assignable<
                typename add_lvalue_reference<T>::type,
                typename add_rvalue_reference<T>::type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_trivially_move_assignable<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_trivially_move_assignable<T>::value;
        }
    };
    template <typename T>
    struct is_nothrow_move_assignable {
        using value_type = bool;
        using result = typename is_nothrow_assignable<
                typename add_lvalue_reference<T>::type,
                typename add_rvalue_reference<T>::type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_nothrow_move_assignable<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_nothrow_move_assignable<T>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename T,
                  bool IsReference = is_reference<T>::value,
                  bool IsFunction = is_function<T>::value>
        struct is_destructible_auxiliary {
            static_assert(not is_type<T>::value, "Invalid template arguments!");
        };
        template <typename T>
        struct is_destructible_auxiliary<T, true, false> {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_destructible_auxiliary<T, true, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_destructible_auxiliary<T, true, false>::value;
            }
        };
        template <typename T>
        struct is_destructible_auxiliary<T, false, true> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_destructible_auxiliary<T, false, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_destructible_auxiliary<T, false, true>::value;
            }
        };
        template <typename T>
        constexpr inline
        typename select_second_type<decltype(declval<T &>().~T()), __true_type>::type
        test_destructor_apply(int) noexcept {
            static_assert(not is_type<T>::value, "The function test_destructor_apply() cannot be called!");
        }
        template <typename T>
        constexpr inline
        typename select_second_type<T, __false_type>::result
        test_destructor_apply(...) noexcept {
            static_assert(not is_type<T>::value, "The function test_destructor_apply() cannot be called!");
        }
        template <typename T>
        struct is_destructible_auxiliary<T, false, false> {
            using value_type = bool;
            using result = decltype(test_destructor_apply<typename remove_all_extents<T>::type>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_destructible_auxiliary<T, false, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_destructible_auxiliary<T, false, false>::value;
            }
        };
    }
    template <typename T>
    struct is_destructible {
        using value_type = bool;
        using result = typename __dsa::is_destructible_auxiliary<T>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_destructible<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_destructible<T>::value;
        }
    };
    template <>
    struct is_destructible<void> {
        using value_type = bool;
        using result = __false_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_destructible<void>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_destructible<void>::value;
        }
    };
    template <typename T>
    struct is_destructible<T []> {
        using value_type = bool;
        using result = __false_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_destructible<T []>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_destructible<T []>::value;
        }
    };
    template <typename T>
    struct is_trivially_destructible {
        using value_type = bool;
        using result = typename conditional<is_destructible<T>::value and __has_trivial_destructor(T),
                __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_trivially_destructible<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_trivially_destructible<T>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename T, bool IsDestructible = is_destructible<T>::value>
        struct is_nothrow_destructible_auxiliary {
            using value_type = bool;
            using result = typename conditional<noexcept(declval<T>().~T()), __true_type, __false_type>::result;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_nothrow_destructible_auxiliary<T, IsDestructible>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_nothrow_destructible_auxiliary<T, IsDestructible>::value;
            }
        };
        template <typename T>
        struct is_nothrow_destructible_auxiliary<T, false> {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_nothrow_destructible_auxiliary<T, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_nothrow_destructible_auxiliary<T, false>::value;
            }
        };
    }
    template <typename T>
    struct is_nothrow_destructible {
        using value_type = bool;
        using result = typename __dsa::is_nothrow_destructible_auxiliary<T>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_nothrow_destructible<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_nothrow_destructible<T>::value;
        }
    };
    template <typename T>
    struct is_nothrow_destructible<T &> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_nothrow_destructible<T &>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_nothrow_destructible<T &>::value;
        }
    };
    template <typename T>
    struct is_nothrow_destructible<T &&> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_nothrow_destructible<T &&>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_nothrow_destructible<T &&>::value;
        }
    };
    template <typename T, decltype(sizeof 0) N>
    struct is_nothrow_destructible<T [N]> {
        using value_type = bool;
        using result = typename is_nothrow_destructible<T>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_nothrow_destructible<T [N]>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_nothrow_destructible<T [N]>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename LHS, typename RHS>
        constexpr inline
        typename select_second_type<decltype(swap(declval<LHS>(), declval<RHS>())), __true_type>::type
        test_swapping_with(int) noexcept {
            static_assert(not is_type<LHS>::value, "The function test_swapping_with() cannot be called!");
        }
        template <typename LHS, typename RHS>
        constexpr inline
        typename select_second_type<LHS, __false_type>::result
        test_swapping_with(...) noexcept {
            static_assert(not is_type<LHS>::value, "The function test_swapping_with() cannot be called!");
        }
        template <typename LHS, typename RHS = LHS>
        struct is_swappable_with_auxiliary {
            using value_type = bool;
            using result = typename conditional<
                    is_same<decltype(test_swapping_with<LHS, RHS>(0)),
                            decltype(test_swapping_with<RHS, LHS>(0))>::value and
                            not is_void<LHS>::value and not is_void<RHS>::value,
                    decltype(test_swapping_with<LHS, RHS>(0)),
                    __false_type
                    >::result;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_swappable_with_auxiliary<LHS, RHS>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_swappable_with_auxiliary<LHS, RHS>::value;
            }
        };
    }
    template <typename LHS, typename RHS>
    struct is_swappable_with {
        using value_type = bool;
        using result = typename __dsa::is_swappable_with_auxiliary<LHS, RHS>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_swappable_with<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_swappable_with<LHS, RHS>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename LHS, typename RHS = LHS, bool IsSwappable = is_swappable_with<LHS, RHS>::value>
        struct is_nothrow_swappable_with_auxiliary {
            using value_type = bool;
            using result = typename conditional<
                    noexcept(swap(declval<LHS>(), declval<RHS>())) and
                    noexcept(swap(declval<RHS>(), declval<LHS>())), __true_type, __false_type>::result;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_nothrow_swappable_with_auxiliary<LHS, RHS, IsSwappable>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_nothrow_swappable_with_auxiliary<LHS, RHS, IsSwappable>::value;
            }
        };
        template <typename LHS, typename RHS>
        struct is_nothrow_swappable_with_auxiliary<LHS, RHS, false> {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_nothrow_swappable_with_auxiliary<LHS, RHS, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_nothrow_swappable_with_auxiliary<LHS, RHS, false>::value;
            }
        };
    }
    template <typename LHS, typename RHS>
    struct is_nothrow_swappable_with {
        using value_type = bool;
        using result = typename __dsa::is_nothrow_swappable_with_auxiliary<LHS, RHS>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_nothrow_swappable_with<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_nothrow_swappable_with<LHS, RHS>::value;
        }
    };
    template <typename T>
    struct is_swappable {
        using value_type = bool;
        using result = typename conditional<is_reference<T>::value,
                typename is_swappable_with<typename add_lvalue_reference<T>::result,
                    typename add_lvalue_reference<T>::result>::result,
                __false_type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_swappable<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_swappable<T>::value;
        }
    };
    template <typename T>
    struct is_nothrow_swappable {
        using value_type = bool;
        using result = typename conditional<is_reference<T>::value,
                typename is_nothrow_swappable_with<typename add_lvalue_reference<T>::result,
                    typename add_lvalue_reference<T>::result>::result,
                __false_type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_nothrow_swappable<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_nothrow_swappable<T>::value;
        }
    };
    template <typename Base, typename Derived>
    struct is_base_of {
        using value_type = bool;
        using result = typename conditional<__is_base_of(Base, Derived), __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_base_of<Base, Derived>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_base_of<Base, Derived>::value;
        }
    };
#if false
    namespace __data_structure_0 {
        using namespace data_structure::__data_structure_auxiliary;
        template <typename Base, typename Derived>
        constexpr inline
        typename select_second_type<
                decltype(dynamic_cast<const Base &>(declval<const Derived &>())),
                __true_type>::type
        test_is_base_of(int) noexcept {
            static_assert(not is_type<Derived>::value, "The function test_is_base_of() cannot be called!");
        }
        template <typename Base, typename Derived>
        constexpr inline typename select_second_type<Derived, __false_type>::type
        test_is_base_of(...) noexcept {
            static_assert(not is_type<Base>::value, "The function test_is_base_of() cannot be called!");
        }
        template <typename Base, typename Derived>
        struct is_base_of {
            using value_type = bool;
            using result = decltype(test_is_base_of<Base, Derived>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_base_of<Base, Derived>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_base_of<Base, Derived>::value;
            }
        };
    }
#endif
    namespace __data_structure_auxiliary {
        template <typename Base, typename Derived>
        constexpr inline
        typename select_second_type<
                decltype(static_cast<Base *>(declval<Derived *>())), __true_type>::type
        test_derived_converts_to_virtual_base(int) noexcept {
            static_assert(not is_type<Base>::value,
                    "The function test_derived_converts_to_virtual_base() cannot be called!");
        }
        template <typename Base, typename Derived>
        constexpr inline typename select_second_type<Base, __false_type>::result
        test_derived_converts_to_virtual_base(...) noexcept {
            static_assert(not is_type<Derived>::value,
                    "The function test_derived_converts_to_virtual_base() cannot be called!");
        }
    }
    template <typename Base, typename Derived>
    struct is_virtual_base_of {
        using value_type = bool;
        using result = decltype(__dsa::test_derived_converts_to_virtual_base<Base, Derived>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_virtual_base_of<Base, Derived>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_virtual_base_of<Base, Derived>::value;
        }
    };
    template <typename From, typename To>
    struct is_convertible {
        using value_type = bool;
        using result = typename conditional<
                __is_convertible(From, To) and not is_abstract<To>::value,
                __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_convertible<From, To>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_convertible<From, To>::value;
        }
    };
#if false
    namespace __data_structure_0 {
        using namespace data_structure::__data_structure_auxiliary;
        template <typename T>
        constexpr inline void test_convert(T) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_converting() cannot be called!");
        }
        template <typename From, typename To>
        constexpr inline
        typename select_second_type<decltype(test_convert<To>(declval<From>())), __true_type>::type
        test_is_convertible(int) noexcept {
            static_assert(not is_type<To>::value,
                    "The function test_is_convertible() cannot be called!");
        }
        template <typename T, typename>
        constexpr inline typename select_second_type<T, __false_type>::type
        test_is_convertible(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_is_convertible() cannot be called!");
        }
        template <typename T, bool IsArray = is_array<T>::value,
                bool IsFunction = is_function<T>::value, bool IsVoid = is_void<T>::value>
        struct is_convertible_type_id final {
            static_assert(not is_type<T>::value, "Invalid template arguments!");
        };
        template <typename T>
        struct is_convertible_type_id<T, true, false, false> final {
            constexpr static inline auto value {1};
        };
        template <typename T>
        struct is_convertible_type_id<T, false, true, false> final {
            constexpr static inline auto value {2};
        };
        template <typename T>
        struct is_convertible_type_id<T, false, false, true> final {
            constexpr static inline auto value {3};
        };
        template <typename T>
        struct is_convertible_type_id<T, false, false, false> final {
            constexpr static inline auto value {0};
        };
        template <typename T, int = is_convertible_type_id<typename remove_reference<T>::type>::value>
        struct is_convertible_check final {
            constexpr static inline auto value {0};
        };
        template <typename T>
        struct is_convertible_check<T, 0> final {
            constexpr static inline auto value {sizeof(T)};
        };
        template <typename From, typename To, int FromTypeId = is_convertible_type_id<From>::value,
                int ToTypeId = is_convertible_type_id<To>::value>
        struct is_convertible_auxiliary {
        private:
            constexpr static inline auto from_type_check {is_convertible_check<From>::value};
            constexpr static inline auto to_type_check {is_convertible_check<To>::value};
        public:
            using value_type = bool;
            using result = decltype(test_is_convertible<From, To>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_convertible_auxiliary<From, To, FromTypeId, ToTypeId>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_convertible_auxiliary<From, To, FromTypeId, ToTypeId>::value;
            }
        };
        template <typename From, typename To>
        struct is_convertible_auxiliary<From, To, 0, 1> {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_convertible_auxiliary<From, To, 0, 1>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_convertible_auxiliary<From, To, 0, 1>::value;
            }
        };
        template <typename From, typename To>
        struct is_convertible_auxiliary<From, To, 1, 1> {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_convertible_auxiliary<From, To, 1, 1>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_convertible_auxiliary<From, To, 1, 1>::value;
            }
        };
        template <typename From, typename To>
        struct is_convertible_auxiliary<From, To, 2, 1> {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_convertible_auxiliary<From, To, 2, 1>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_convertible_auxiliary<From, To, 2, 1>::value;
            }
        };
        template <typename From, typename To>
        struct is_convertible_auxiliary<From, To, 3, 1> {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_convertible_auxiliary<From, To, 3, 1>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_convertible_auxiliary<From, To, 3, 1>::value;
            }
        };
        template <typename From, typename To>
        struct is_convertible_auxiliary<From, To, 0, 2> {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_convertible_auxiliary<From, To, 0, 2>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_convertible_auxiliary<From, To, 0, 2>::value;
            }
        };
        template <typename From, typename To>
        struct is_convertible_auxiliary<From, To, 1, 2> {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_convertible_auxiliary<From, To, 1, 2>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_convertible_auxiliary<From, To, 1, 2>::value;
            }
        };
        template <typename From, typename To>
        struct is_convertible_auxiliary<From, To, 2, 2> {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_convertible_auxiliary<From, To, 2, 2>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_convertible_auxiliary<From, To, 2, 2>::value;
            }
        };
        template <typename From, typename To>
        struct is_convertible_auxiliary<From, To, 3, 2> {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_convertible_auxiliary<From, To, 3, 2>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_convertible_auxiliary<From, To, 3, 2>::value;
            }
        };
        template <typename From, typename To>
        struct is_convertible_auxiliary<From, To, 0, 3> {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_convertible_auxiliary<From, To, 0, 3>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_convertible_auxiliary<From, To, 0, 3>::value;
            }
        };
        template <typename From, typename To>
        struct is_convertible_auxiliary<From, To, 1, 3> {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_convertible_auxiliary<From, To, 1, 3>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_convertible_auxiliary<From, To, 1, 3>::value;
            }
        };
        template <typename From, typename To>
        struct is_convertible_auxiliary<From, To, 2, 3> {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_convertible_auxiliary<From, To, 2, 3>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_convertible_auxiliary<From, To, 2, 3>::value;
            }
        };
        template <typename From, typename To>
        struct is_convertible_auxiliary<From, To, 3, 3> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_convertible_auxiliary<From, To, 3, 3>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_convertible_auxiliary<From, To, 3, 3>::value;
            }
        };
        template <typename From, typename To>
        struct is_convertible {
            using value_type = bool;
            using result = typename is_convertible_auxiliary<From, To>::result;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_convertible<From, To>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_convertible<From, To>::value;
            }
        };
    }
#endif
    namespace __data_structure_auxiliary {
        template <typename From, typename To>
        struct is_nothrow_convertible_auxiliary {
            using value_type = bool;
            using result = typename conditional<
                    noexcept(static_cast<To>(declval<From>())), __true_type, __false_type>::result;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_nothrow_convertible_auxiliary<From, To>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_nothrow_convertible_auxiliary<From, To>::value;
            }
        };
    }
    template <typename From, typename To>
    struct is_nothrow_convertible {
        using value_type = bool;
        using result = typename __dsa::is_nothrow_convertible_auxiliary<From, To>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_nothrow_convertible<From, To>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_nothrow_convertible<From, To>::value;
        }
    };
    template <>
    struct is_nothrow_convertible<void, void> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_nothrow_convertible<void, void>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_nothrow_convertible<void, void>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename T, bool IsEnum = is_enum<T>::value>
        struct is_signed_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_signed_auxiliary<T, IsEnum>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_signed_auxiliary<T, IsEnum>::value;
            }
        };
        template <typename T>
        struct is_signed_auxiliary<T, true> {
            using value_type = bool;
            using result = typename conditional<is_signed_auxiliary<__underlying_type(T)>::value,
                    __true_type, __false_type>::result;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_signed_auxiliary<T, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_signed_auxiliary<T, true>::value;
            }
        };
        template <>
        struct is_signed_auxiliary<signed char, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_signed_auxiliary<signed char, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_signed_auxiliary<signed char, false>::value;
            }
        };
        template <>
        struct is_signed_auxiliary<const signed char, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_signed_auxiliary<const signed char, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_signed_auxiliary<const signed char, false>::value;
            }
        };
        template <>
        struct is_signed_auxiliary<volatile signed char, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_signed_auxiliary<volatile signed char, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_signed_auxiliary<volatile signed char, false>::value;
            }
        };
        template <>
        struct is_signed_auxiliary<const volatile signed char, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_signed_auxiliary<const volatile signed char, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_signed_auxiliary<const volatile signed char, false>::value;
            }
        };
        template <>
        struct is_signed_auxiliary<signed wchar_t, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_signed_auxiliary<signed wchar_t, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_signed_auxiliary<signed wchar_t, false>::value;
            }
        };
        template <>
        struct is_signed_auxiliary<const signed wchar_t, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_signed_auxiliary<const signed wchar_t, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_signed_auxiliary<const signed wchar_t, false>::value;
            }
        };
        template <>
        struct is_signed_auxiliary<volatile signed wchar_t, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_signed_auxiliary<volatile signed wchar_t, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_signed_auxiliary<volatile signed wchar_t, false>::value;
            }
        };
        template <>
        struct is_signed_auxiliary<const volatile signed wchar_t, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_signed_auxiliary<const volatile signed wchar_t, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_signed_auxiliary<const volatile signed wchar_t, false>::value;
            }
        };
        template <>
        struct is_signed_auxiliary<signed short int, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_signed_auxiliary<signed short int, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_signed_auxiliary<signed short int, false>::value;
            }
        };
        template <>
        struct is_signed_auxiliary<const signed short int, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_signed_auxiliary<const signed short int, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_signed_auxiliary<const signed short int, false>::value;
            }
        };
        template <>
        struct is_signed_auxiliary<volatile signed short int, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_signed_auxiliary<volatile signed short int, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_signed_auxiliary<volatile signed short int, false>::value;
            }
        };
        template <>
        struct is_signed_auxiliary<const volatile signed short int, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_signed_auxiliary<const volatile signed short int, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_signed_auxiliary<const volatile signed short int, false>::value;
            }
        };
        template <>
        struct is_signed_auxiliary<signed int, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_signed_auxiliary<signed int, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_signed_auxiliary<signed int, false>::value;
            }
        };
        template <>
        struct is_signed_auxiliary<const signed int, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_signed_auxiliary<const signed int, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_signed_auxiliary<const signed int, false>::value;
            }
        };
        template <>
        struct is_signed_auxiliary<volatile signed int, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_signed_auxiliary<volatile signed int, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_signed_auxiliary<volatile signed int, false>::value;
            }
        };
        template <>
        struct is_signed_auxiliary<const volatile signed int, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_signed_auxiliary<const volatile signed int, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_signed_auxiliary<const volatile signed int, false>::value;
            }
        };
        template <>
        struct is_signed_auxiliary<signed long int, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_signed_auxiliary<signed long int, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_signed_auxiliary<signed long int, false>::value;
            }
        };
        template <>
        struct is_signed_auxiliary<const signed long int, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_signed_auxiliary<const signed long int, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_signed_auxiliary<const signed long int, false>::value;
            }
        };
        template <>
        struct is_signed_auxiliary<volatile signed long int, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_signed_auxiliary<volatile signed long int, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_signed_auxiliary<volatile signed long int, false>::value;
            }
        };
        template <>
        struct is_signed_auxiliary<const volatile signed long int, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_signed_auxiliary<const volatile signed long int, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_signed_auxiliary<const volatile signed long int, false>::value;
            }
        };
        template <>
        struct is_signed_auxiliary<signed long long int, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_signed_auxiliary<signed long long int, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_signed_auxiliary<signed long long int, false>::value;
            }
        };
        template <>
        struct is_signed_auxiliary<const signed long long int, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_signed_auxiliary<const signed long long int, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_signed_auxiliary<const signed long long int, false>::value;
            }
        };
        template <>
        struct is_signed_auxiliary<volatile signed long long int, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_signed_auxiliary<volatile signed long long int, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_signed_auxiliary<volatile signed long long int, false>::value;
            }
        };
        template <>
        struct is_signed_auxiliary<const volatile signed long long int, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_signed_auxiliary<const volatile signed long long int, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_signed_auxiliary<const volatile signed long long int, false>::value;
            }
        };
        template <>
        struct is_signed_auxiliary<__int128 /* __int128_t */ , false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_signed_auxiliary<__int128 /* __int128_t */ , false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_signed_auxiliary<__int128 /* __int128_t */ , false>::value;
            }
        };
        template <>
        struct is_signed_auxiliary<const __int128 /* __int128_t */ , false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_signed_auxiliary<const __int128 /* __int128_t */ , false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_signed_auxiliary<const __int128 /* __int128_t */ , false>::value;
            }
        };
        template <>
        struct is_signed_auxiliary<volatile __int128 /* __int128_t */ , false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_signed_auxiliary<volatile __int128 /* __int128_t */ , false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_signed_auxiliary<volatile __int128 /* __int128_t */ , false>::value;
            }
        };
        template <>
        struct is_signed_auxiliary<const volatile __int128 /* __int128_t */ , false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_signed_auxiliary<const volatile __int128 /* __int128_t */ , false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_signed_auxiliary<const volatile __int128 /* __int128_t */ , false>::value;
            }
        };
    }
    template <typename T>
    struct is_signed {
        using value_type = bool;
        using result = typename __dsa::is_signed_auxiliary<T>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_signed<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_signed<T>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename T, bool IsEnum = is_enum<T>::value>
        struct is_unsigned_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_unsigned_auxiliary<T, IsEnum>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_unsigned_auxiliary<T, IsEnum>::value;
            }
        };
        template <typename T>
        struct is_unsigned_auxiliary<T, true> {
            using value_type = bool;
            using result = typename is_unsigned_auxiliary<__underlying_type(T)>::result;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_unsigned_auxiliary<T, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_unsigned_auxiliary<T, true>::value;
            }
        };
        template <>
        struct is_unsigned_auxiliary<unsigned char, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_unsigned_auxiliary<unsigned char, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_unsigned_auxiliary<unsigned char, false>::value;
            }
        };
        template <>
        struct is_unsigned_auxiliary<const unsigned char, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_unsigned_auxiliary<const unsigned char, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_unsigned_auxiliary<const unsigned char, false>::value;
            }
        };
        template <>
        struct is_unsigned_auxiliary<volatile unsigned char, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_unsigned_auxiliary<volatile unsigned char, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_unsigned_auxiliary<volatile unsigned char, false>::value;
            }
        };
        template <>
        struct is_unsigned_auxiliary<const volatile unsigned char, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_unsigned_auxiliary<const volatile unsigned char, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_unsigned_auxiliary<const volatile unsigned char, false>::value;
            }
        };
        template <>
        struct is_unsigned_auxiliary<unsigned short int, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_unsigned_auxiliary<unsigned short int, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_unsigned_auxiliary<unsigned short int, false>::value;
            }
        };
        template <>
        struct is_unsigned_auxiliary<const unsigned short int, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_unsigned_auxiliary<const unsigned short int, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_unsigned_auxiliary<const unsigned short int, false>::value;
            }
        };
        template <>
        struct is_unsigned_auxiliary<volatile unsigned short int, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_unsigned_auxiliary<volatile unsigned short int, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_unsigned_auxiliary<volatile unsigned short int, false>::value;
            }
        };
        template <>
        struct is_unsigned_auxiliary<const volatile unsigned short int, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_unsigned_auxiliary<const volatile unsigned short int, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_unsigned_auxiliary<const volatile unsigned short int, false>::value;
            }
        };
        template <>
        struct is_unsigned_auxiliary<unsigned int, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_unsigned_auxiliary<unsigned int, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_unsigned_auxiliary<unsigned int, false>::value;
            }
        };
        template <>
        struct is_unsigned_auxiliary<const unsigned int, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_unsigned_auxiliary<const unsigned int, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_unsigned_auxiliary<const unsigned int, false>::value;
            }
        };
        template <>
        struct is_unsigned_auxiliary<volatile unsigned int, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_unsigned_auxiliary<volatile unsigned int, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_unsigned_auxiliary<volatile unsigned int, false>::value;
            }
        };
        template <>
        struct is_unsigned_auxiliary<const volatile unsigned int, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_unsigned_auxiliary<const volatile unsigned int, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_unsigned_auxiliary<const volatile unsigned int, false>::value;
            }
        };
        template <>
        struct is_unsigned_auxiliary<unsigned long int, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_unsigned_auxiliary<unsigned long int, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_unsigned_auxiliary<unsigned long int, false>::value;
            }
        };
        template <>
        struct is_unsigned_auxiliary<const unsigned long int, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_unsigned_auxiliary<const unsigned long int, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_unsigned_auxiliary<const unsigned long int, false>::value;
            }
        };
        template <>
        struct is_unsigned_auxiliary<volatile unsigned long int, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_unsigned_auxiliary<volatile unsigned long int, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_unsigned_auxiliary<volatile unsigned long int, false>::value;
            }
        };
        template <>
        struct is_unsigned_auxiliary<const volatile unsigned long int, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_unsigned_auxiliary<const volatile unsigned long int, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_unsigned_auxiliary<const volatile unsigned long int, false>::value;
            }
        };
        template <>
        struct is_unsigned_auxiliary<unsigned long long int, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_unsigned_auxiliary<unsigned long long int, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_unsigned_auxiliary<unsigned long long int, false>::value;
            }
        };
        template <>
        struct is_unsigned_auxiliary<const unsigned long long int, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_unsigned_auxiliary<const unsigned long long int, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_unsigned_auxiliary<const unsigned long long int, false>::value;
            }
        };
        template <>
        struct is_unsigned_auxiliary<volatile unsigned long long int, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_unsigned_auxiliary<volatile unsigned long long int, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_unsigned_auxiliary<volatile unsigned long long int, false>::value;
            }
        };
        template <>
        struct is_unsigned_auxiliary<const volatile unsigned long long int, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_unsigned_auxiliary<const volatile unsigned long long int, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_unsigned_auxiliary<const volatile unsigned long long int, false>::value;
            }
        };
        template <>
        struct is_unsigned_auxiliary<__uint128_t, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_unsigned_auxiliary<__uint128_t, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_unsigned_auxiliary<__uint128_t, false>::value;
            }
        };
        template <>
        struct is_unsigned_auxiliary<const __uint128_t, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_unsigned_auxiliary<const __uint128_t, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_unsigned_auxiliary<const __uint128_t, false>::value;
            }
        };
        template <>
        struct is_unsigned_auxiliary<volatile __uint128_t, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_unsigned_auxiliary<volatile __uint128_t, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_unsigned_auxiliary<volatile __uint128_t, false>::value;
            }
        };
        template <>
        struct is_unsigned_auxiliary<const volatile __uint128_t, false> {
            using value_type = bool;
            using result = __true_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_unsigned_auxiliary<const volatile __uint128_t, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_unsigned_auxiliary<const volatile __uint128_t, false>::value;
            }
        };
    }
    template <typename T>
    struct is_unsigned {
        using value_type = bool;
        using result = typename __dsa::is_unsigned_auxiliary<T>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_unsigned<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_unsigned<T>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename T>
        constexpr inline
        typename select_second_type<decltype(sizeof declval<T>()), __true_type>::type
        check_is_complete(int) noexcept {
            static_assert(is_type<T>::value, "The function check_is_complete() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline
        typename select_second_type<T, __false_type>::type
        check_is_complete(...) noexcept {
            static_assert(is_type<T>::value, "The function check_is_complete() cannot be called!");
            return {};
        }
    }
    template <typename T>
    struct is_complete {
        using value_type = bool;
        using result = decltype(__dsa::check_is_complete<T>(0));
        constexpr static inline auto value {static_cast<bool>(result())};
        constexpr value_type operator()() const noexcept {
            return is_complete<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_complete<T>::value;
        }
    };
    template <typename T>
    struct is_stateless {
        using value_type = bool;
        using result = typename conditional<is_trivially_default_constructible<T>::value and
                is_trivially_copy_constructible<T>:: value and
                is_trivially_destructible<T>::value and is_class<T>::value and is_empty<T>::value,
                __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<bool>(result())};
        constexpr value_type operator()() const noexcept {
            return is_stateless<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_stateless<T>::value;
        }
    };
    template <typename T>
    struct is_reference_wrapper {
        using value_type = bool;
        using result = __false_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_reference_wrapper<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_reference_wrapper<T>::value;
        }
    };
    template <typename> class reference_wrapper;        //from "functional.hpp"
    template <typename T>
    struct is_reference_wrapper<reference_wrapper<T>> {
        using value_type = bool;
        using result = __true_type;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_reference_wrapper<reference_wrapper<T>>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_reference_wrapper<reference_wrapper<T>>::value;
        }
    };
    template <typename, typename> struct type_list;
    template <typename> struct decay;
    namespace __data_structure_auxiliary {
        struct invoke_failure_tag final {
            constexpr invoke_failure_tag() noexcept = delete;
            constexpr invoke_failure_tag(const invoke_failure_tag &) noexcept = delete;
            constexpr invoke_failure_tag(invoke_failure_tag &&) noexcept = delete;
            ~invoke_failure_tag() noexcept = delete;
            invoke_failure_tag &operator=(const invoke_failure_tag &) noexcept = delete;
            invoke_failure_tag &operator=(invoke_failure_tag &&) noexcept = delete;
        };
        template <typename F, typename T, typename ...Args>
        constexpr inline decltype(declval<T>().*declval<F>()(declval<Args>()...)) *
        result_of_member_function_reference(int) noexcept {
            static_assert(not is_type<F>::value,
                          "The function result_of_member_function_reference() cannot be called!");
            return nullptr;
        }
        template <decltype(sizeof 0) N, typename ...Args>
        struct choose_argument;
        template <decltype(sizeof 0) N, typename ThisType, typename ...Args>
        struct choose_argument<N, ThisType, Args...>;
        template <typename ThisType, typename ...Args>
        struct choose_argument<0, ThisType, Args...>;
        template <typename ...Args>
        constexpr inline invoke_failure_tag *
        result_of_member_function_reference(...) noexcept {
            static_assert(not is_type<typename choose_argument<0, Args...>::type>::value,
                          "The function result_of_member_function_reference() cannot be called!");
            return nullptr;
        }
        template <typename F, typename T, typename ...Args>
        struct result_of_member_function_reference_auxiliary final {
            using result = typename remove_pointer<
                    decltype(result_of_member_function_reference<F, T, Args...>(0))>::result;
            using type = typename remove_pointer<
                    decltype(result_of_member_function_reference<F, T, Args...>(0))>::result;
        };
        template <typename F, typename T, typename ...Args>
        constexpr inline typename conditional<noexcept(declval<T>().*declval<F>()(declval<Args>()...)),
                __true_type, __false_type>::type
        test_member_function_reference_is_nothrow() noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_member_function_reference_is_nothrow() cannot be called!");
            return {};
        }
        template <typename F, typename T, typename ...Args>
        struct is_member_function_reference_nothrow {
            using value_type = bool;
            using result = decltype(test_member_function_reference_is_nothrow<F, T, Args...>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_member_function_reference_nothrow<F, T, Args...>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_member_function_reference_nothrow<F, T, Args...>::value;
            }
        };
        template <typename F, typename T, typename ...Args>
        constexpr inline decltype((*declval<T>()).*declval<F>()(declval<Args>()...)) *
        result_of_member_function_dereference(int) noexcept {
            static_assert(not is_type<F>::value,
                          "The function result_of_member_function_dereference() cannot be called!");
            return nullptr;
        }
        template <typename F, typename T, typename ...Args>
        constexpr inline decltype(declval<T>()->*declval<F>()(declval<Args>()...)) *
        result_of_member_function_dereference(long) noexcept {
            static_assert(not is_type<F>::value,
                          "The function result_of_member_function_dereference() cannot be called!");
            return nullptr;
        }
        template <typename ...Args>
        constexpr inline invoke_failure_tag *
        result_of_member_function_dereference(...) noexcept {
            static_assert(not is_type<typename choose_argument<0, Args...>::type>::value,
                          "The function result_of_member_function_dereference() cannot be called!");
            return nullptr;
        }
        template <typename F, typename T, typename ...Args>
        struct result_of_member_function_dereference_auxiliary final {
            using result = typename remove_pointer<
                    decltype(result_of_member_function_dereference<F, T, Args...>(0))>::result;
            using type = typename remove_pointer<
                    decltype(result_of_member_function_dereference<F, T, Args...>(0))>::result;
        };
        template <typename F, typename T, typename ...Args>
        constexpr inline typename conditional<noexcept((*declval<T>()).*declval<F>()(declval<Args>()...)),
                __true_type, __false_type>::type
        test_member_function_dereference_is_nothrow() noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_member_function_dereference_is_nothrow() cannot be called!");
            return {};
        }
        template <typename F, typename T, typename ...Args>
        constexpr inline typename conditional<noexcept(declval<T>()->*declval<F>()(declval<Args>()...)),
                __true_type, __false_type>::type
        test_member_function_dereference_is_nothrow() noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_member_function_dereference_is_nothrow() cannot be called!");
            return {};
        }
        template <typename F, typename T, typename ...Args>
        struct is_member_function_dereference_nothrow {
            using value_type = bool;
            using result = decltype(test_member_function_dereference_is_nothrow<F, T, Args...>());
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_member_function_dereference_nothrow<F, T, Args...>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_member_function_dereference_nothrow<F, T, Args...>::value;
            }
        };
        template <typename O, typename T>
        constexpr inline decltype(declval<T>().*declval<O>()) *
        result_of_member_object_reference(int) noexcept {
            static_assert(not is_type<O>::value,
                          "The function result_of_member_object_reference() cannot be called!");
            return nullptr;
        }
        template <typename T, typename>
        constexpr inline invoke_failure_tag *
        result_of_member_object_reference(...) noexcept {
            static_assert(not is_type<T>::value,
                          "The function result_of_member_object_reference() cannot be called!");
            return nullptr;
        }
        template <typename T, typename O>
        struct result_of_member_object_reference_auxiliary final {
            using result = typename remove_pointer<
                    decltype(result_of_member_object_reference<T, O>(0))>::result;
            using type = typename remove_pointer<
                    decltype(result_of_member_object_reference<T, O>(0))>::result;
        };
        template <typename O, typename T>
        constexpr inline typename conditional<noexcept(declval<T>().*declval<O>()),
                __true_type, __false_type>::type
        test_member_object_reference_is_nothrow() noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_member_object_reference_is_nothrow() cannot be called!");
            return {};
        }
        template <typename T, typename O>
        struct is_member_object_reference_nothrow {
            using value_type = bool;
            using result = decltype(test_member_object_reference_is_nothrow<T, O>());
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_member_object_reference_nothrow<T, O>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_member_object_reference_nothrow<T, O>::value;
            }
        };
        template <typename O, typename T>
        constexpr inline decltype((*declval<T>()).*declval<O>()) *
        result_of_member_object_dereference(int) noexcept {
            static_assert(not is_type<T>::value,
                          "The function result_of_member_object_dereference() cannot be called!");
            return nullptr;
        }
        template <typename O, typename T>
        constexpr inline decltype(declval<T>()->*declval<O>()) *
        result_of_member_object_dereference(long) noexcept {
            static_assert(not is_type<O>::value,
                          "The function result_of_member_object_dereference() cannot be called!");
            return nullptr;
        }
        template <typename T, typename>
        constexpr inline invoke_failure_tag *
        result_of_member_object_dereference(...) noexcept {
            static_assert(not is_type<T>::value,
                          "The function result_of_member_object_dereference() cannot be called!");
            return nullptr;
        }
        template <typename T, typename O>
        struct result_of_member_object_dereference_auxiliary {
            using result = typename remove_pointer<
                    decltype(result_of_member_object_dereference<T, O>(0))>::result;
            using type = typename remove_pointer<
                    decltype(result_of_member_object_dereference<T, O>(0))>::result;
        };
        template <typename O, typename T>
        constexpr inline typename conditional<noexcept((*declval<T>()).*declval<O>()),
                __true_type, __false_type>::type
        test_member_object_dereference_is_nothrow() noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_member_object_dereference_is_nothrow() cannot be called!");
            return {};
        }
        template <typename O, typename T>
        constexpr inline typename conditional<noexcept(declval<T>()->*declval<O>()),
                __true_type, __false_type>::type
        test_member_object_dereference_is_nothrow() noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_member_object_dereference_is_nothrow() cannot be called!");
            return {};
        }
        template <typename T, typename O>
        struct is_member_object_dereference_nothrow {
            using value_type = bool;
            using result = decltype(test_member_object_dereference_is_nothrow<T, O>());
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_member_object_dereference_nothrow<T, O>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_member_object_dereference_nothrow<T, O>::value;
            }
        };
        template <typename T, typename>
        struct result_of_member_object final {
            static_assert(not is_type<T>::value, "Invalid template arguments!");
        };
        template <typename T, typename Class, typename O>
        struct result_of_member_object<T Class::*, O> final {
            using result = typename conditional<static_cast<bool>(
                    typename disjunction<is_same<typename remove_cvreference<O>::result, Class>,
                            is_base_of<Class, typename remove_cvreference<O>::result>>::result()),
                    typename result_of_member_object_reference_auxiliary<T Class::*, O>::result,
                    typename result_of_member_object_dereference_auxiliary<T Class::*, O>::result
                    >::result;
            using type = typename conditional<static_cast<bool>(
                    typename disjunction<is_same<typename remove_cvreference<O>::type, Class>,
                            is_base_of<Class, typename remove_cvreference<O>::type>>::result()),
                    typename result_of_member_object_reference_auxiliary<T Class::*, O>::type,
                    typename result_of_member_object_dereference_auxiliary<T Class::*, O>::type
                    >::type;
        };
        template <typename T, typename O>
        struct is_member_object_nothrow {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_member_object_nothrow<T, O>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_member_object_nothrow<T, O>::value;
            }
        };
        template <typename T, typename Class, typename O>
        struct is_member_object_nothrow<T Class::*, O> {
            using value_type = bool;
            using result = typename conditional<static_cast<bool>(
                    typename disjunction<is_same<typename remove_cvreference<O>::result, Class>,
                            is_base_of<Class, typename remove_cvreference<O>::result>>::result()),
                    typename is_member_object_reference_nothrow<T Class::*, O>::result,
                    typename is_member_object_dereference_nothrow<T Class::*, O>::result
                    >::result;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_member_object_nothrow<T Class::*, O>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_member_object_nothrow<T Class::*, O>::value;
            }
        };
        template <typename T, typename, typename ...>
        struct result_of_member_function final {
            static_assert(not is_type<T>::value, "Invalid template arguments!");
        };
        template <typename T, typename Class, typename F, typename ...Args>
        struct result_of_member_function<T Class::*, F, Args...> final {
            using result = typename conditional<static_cast<bool>(
                    typename disjunction<is_same<typename remove_cvreference<F>::result, Class>,
                            is_base_of<Class, typename remove_cvreference<F>::result>>::result()),
                    typename result_of_member_function_reference_auxiliary<
                            T Class::*, F, Args...>::result,
                    typename result_of_member_function_dereference_auxiliary<
                            T Class::*, F, Args...>::result
                    >::result;
            using type = typename conditional<static_cast<bool>(
                    typename disjunction<is_same<typename remove_cvreference<F>::type, Class>,
                            is_base_of<Class, typename remove_cvreference<F>::type>>::result()),
                    typename result_of_member_function_reference_auxiliary<
                            T Class::*, F, Args...>::type,
                    typename result_of_member_function_dereference_auxiliary<
                            T Class::*, F, Args...>::type
                    >::type;
        };
        template <typename T, typename F, typename ...Args>
        struct is_member_function_nothrow {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_member_function_nothrow<T, F, Args...>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_member_function_nothrow<T, F, Args...>::value;
            }
        };
        template <typename T, typename Class, typename F, typename ...Args>
        struct is_member_function_nothrow<T Class::*, F, Args...> {
            using value_type = bool;
            using result = typename conditional<static_cast<bool>(
                    typename disjunction<is_same<typename remove_cvreference<F>::result, Class>,
                            is_base_of<Class, typename remove_cvreference<F>::result>>::result()),
                    typename is_member_function_reference_nothrow<T Class::*, F, Args...>::result,
                    typename is_member_function_dereference_nothrow<T Class::*, F, Args...>::result
                    >::result;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_member_function_nothrow<T Class::*, F, Args...>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_member_function_nothrow<T Class::*, F, Args...>::value;
            }
        };
        template <typename T, typename = typename decay<T>::type>
        struct unwrap final {
            using result = T;
            using type = T;
        };
        template <typename Type_1, typename Type_2>
        struct unwrap<Type_1, reference_wrapper<Type_2>> final {
            using result = Type_2 &;
            using type = Type_2 &;
        };
        template <bool, bool, typename, typename ...>
        struct result_of_auxiliary final {
            using result = invoke_failure_tag;
            using type = invoke_failure_tag;
        };
        template <typename T, typename O>
        struct result_of_auxiliary<true, false, T, O> final {
            using result = typename result_of_member_object<
                    typename decay<T>::result, typename unwrap<O>::result>::result;
            using type = typename result_of_member_object<
                    typename decay<T>::type, typename unwrap<O>::type>::type;
        };
        template <typename T, typename F, typename ...Args>
        struct result_of_auxiliary<false, true, T, F, Args...> final {
            using result = typename result_of_member_function<
                    typename decay<T>::result, typename unwrap<F>::result, Args...>::result;
            using type = typename result_of_member_function<
                    typename decay<T>::type, typename unwrap<F>::type, Args...>::type;
        };
        template <typename F, typename ...Args>
        constexpr inline decltype(declval<F>()(declval<Args>()...)) *
        result_of_function(int) noexcept {
            static_assert(not is_type<F>::value, "The function result_of_function() cannot be called!");
            return nullptr;
        }
        template <typename ...Args>
        constexpr inline invoke_failure_tag *
        result_of_function(...) noexcept {
            static_assert(not is_type<typename choose_argument<0, Args...>::type>::value,
                          "The function result_of_function() cannot be called!");
            return nullptr;
        }
        template <typename F, typename ...Args>
        constexpr inline typename conditional<noexcept(declval<F>()(declval<Args>()...)),
                __true_type, __false_type>::type
        is_function_nothrow() noexcept {
            static_assert(not is_type<F>::value,
                    "The function is_function_nothrow() cannot be called!");
            return {};
        }
        template <typename F, typename ...Args>
        struct result_of_auxiliary<false, false, F, Args...> final {
            using result = typename remove_pointer<
                    decltype(result_of_function<F, Args...>(0))>::result;
            using type = typename remove_pointer<
                    decltype(result_of_function<F, Args...>(0))>::type;
        };
        template <bool IsMemberObjectPointer, bool IsMemberFunctionPointer,
                typename F, typename ...Args>
        struct is_nothrow_reachable_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_nothrow_reachable_auxiliary<
                        IsMemberObjectPointer, IsMemberFunctionPointer, F, Args...>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_nothrow_reachable_auxiliary<
                        IsMemberObjectPointer, IsMemberFunctionPointer, F, Args...>::value;
            }
        };
        template <typename T, typename O>
        struct is_nothrow_reachable_auxiliary<true, false, T, O> {
            using value_type = bool;
            using result = typename is_member_object_nothrow<
                    typename decay<T>::result, typename unwrap<O>::result>::result;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_nothrow_reachable_auxiliary<true, false, T, O>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_nothrow_reachable_auxiliary<true, false, T, O>::value;
            }
        };
        template <typename T, typename F, typename ...Args>
        struct is_nothrow_reachable_auxiliary<false, true, T, F, Args...> {
            using value_type = bool;
            using result = typename is_member_function_nothrow<
                    typename decay<T>::result, typename unwrap<F>::result, Args...>::result;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_nothrow_reachable_auxiliary<false, true, T, F, Args...>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_nothrow_reachable_auxiliary<false, true, T, F, Args...>::value;
            }
        };
        template <typename F, typename ...Args>
        struct is_nothrow_reachable_auxiliary<false, false, F, Args...> {
            using value_type = bool;
            using result = decltype(is_function_nothrow<F, Args...>());
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_nothrow_reachable_auxiliary<false, false, F, Args...>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_nothrow_reachable_auxiliary<false, false, F, Args...>::value;
            }
        };
        template <typename Resource, typename R, typename SFINAE = void>
        struct is_invocable_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<bool>(result())};
            constexpr value_type operator()() const noexcept {
                return is_invocable_auxiliary<Resource, R, SFINAE>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_invocable_auxiliary<Resource, R, SFINAE>::value;
            }
        };
        template <typename Resource, typename R>
        struct is_invocable_auxiliary<Resource, R, void_t<typename Resource::type>> {
            using value_type = bool;
            using result = typename disjunction<
                    is_void<R>, is_convertible<typename Resource::result, R>>::result;
            constexpr static inline auto value {static_cast<bool>(result())};
            constexpr value_type operator()() const noexcept {
                return is_invocable_auxiliary<Resource, R, void_t<typename Resource::type>>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_invocable_auxiliary<Resource, R, void_t<typename Resource::type>>::value;
            }
        };
        template <typename T>
        struct check_type_is_complete {
            static_assert(sizeof(T) > 0, "Invalid template argument(s), the types(s) must be complete!");
        };
        template <typename F, typename ...Args>
        struct invoke_result final : private check_type_is_complete<F> {
            using result = typename __dsa::result_of_auxiliary<
                    is_member_object_pointer<typename remove_reference<F>::result>::value,
                    is_member_object_pointer<typename remove_reference<F>::result>::value,
                    F, Args...>::result;
            using type = typename __dsa::result_of_auxiliary<
                    is_member_object_pointer<typename remove_reference<F>::type>::value,
                    is_member_function_pointer<typename remove_reference<F>::type>::value,
                    F, Args...>::type;
        };
        template <typename T, typename ...>
        struct result_of final : private check_type_is_complete<T> {
            static_assert(not __dsa::is_type<T>::value, "Invalid template arguments!");
        };
        template <typename F, typename ...Args>
        struct result_of<F (Args...)> final : private check_type_is_complete<F> {
            using result = typename invoke_result<F, Args...>::result;
            using type = typename invoke_result<F, Args...>::type;
        };
    }
    template <typename F, typename ...Args>
    struct is_reachable {
        using value_type = bool;
        using result = typename conditional<
                is_same<typename __dsa::invoke_result<F, Args...>::result,
                        __dsa::invoke_failure_tag>::value,
                __false_type,
                typename __dsa::is_invocable_auxiliary<
                        __dsa::invoke_result<F, Args...>, void>::result
                >::result;
        constexpr static inline auto value {static_cast<bool>(result())};
        constexpr value_type operator()() const noexcept {
            return is_reachable<F, Args...>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_reachable<F, Args...>::value;
        }
    };
    template <typename F, typename ...Args>
    struct is_invocable {
        using value_type = bool;
        using result = typename conditional<
                is_same<typename __dsa::invoke_result<F, Args...>::result,
                        __dsa::invoke_failure_tag>::value,
                __false_type,
                typename __dsa::is_invocable_auxiliary<
                        __dsa::invoke_result<F, Args...>, void>::result
                >::result;
        constexpr static inline auto value {static_cast<bool>(result())};
        constexpr value_type operator()() const noexcept {
            return is_invocable<F, Args...>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_invocable<F, Args...>::value;
        }
    };
    template <typename R, typename F, typename ...Args>
    struct is_invocable_r {
        using value_type = bool;
        using result = typename conditional<
                is_same<typename __dsa::invoke_result<F, Args...>::result,
                        __dsa::invoke_failure_tag>::value,
                __false_type,
                typename __dsa::is_invocable_auxiliary<
                        __dsa::invoke_result<F, Args...>, R>::result
                >::result;
        constexpr static inline auto value {static_cast<bool>(result())};
        constexpr value_type operator()() const noexcept {
            return is_invocable_r<R, F, Args...>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_invocable_r<R, F, Args...>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <bool IsCallable, typename F, typename ...Args>
        struct is_nothrow_invocable_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_nothrow_invocable_auxiliary<IsCallable, F, Args...>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_nothrow_invocable_auxiliary<IsCallable, F, Args...>::value;
            }
        };
        template <typename F, typename ...Args>
        struct is_nothrow_invocable_auxiliary<true, F, Args...> {
            using value_type = bool;
            using result = typename is_nothrow_reachable_auxiliary<
                    is_member_object_pointer<typename remove_reference<F>::result>::value,
                    is_member_object_pointer<typename remove_reference<F>::result>::value,
                    F, Args...>::result;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_nothrow_invocable_auxiliary<true, F, Args...>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_nothrow_invocable_auxiliary<true, F, Args...>::value;
            }
        };
    }
    template <typename F, typename ...Args>
    struct is_nothrow_invocable {
        using value_type = bool;
        using result = typename __dsa::is_nothrow_invocable_auxiliary<
                is_invocable<F, Args...>::value, F, Args...>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_nothrow_invocable<F, Args...>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_nothrow_invocable<F, Args...>::value;
        }
    };
    template <typename R, typename F, typename ...Args>
    struct is_nothrow_invocable_r {
        using value_type = bool;
        using result = typename __dsa::is_nothrow_invocable_auxiliary<
                is_invocable_r<R, F, Args...>::value, F, Args...>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_nothrow_invocable_r<R, F, Args...>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_nothrow_invocable_r<R, F, Args...>::value;
        }
    };
}

namespace data_structure {
    namespace __data_structure_auxiliary {
        template <typename T, bool IsFunction = is_function<T>::value>
        struct add_pointer_auxiliary final {
            using result = typename remove_reference<T>::result *;
            using type = typename remove_reference<T>::type *;
        };
        template <typename F>
        struct add_pointer_auxiliary<F, true> final {
            using result = F;
            using type = F;
        };
        template <typename F, typename ...Args>
        struct add_pointer_auxiliary<F(Args...), true> final {
            using result = F (*)(Args...);
            using type = F (*)(Args...);
        };
        template <typename F, typename ...Args>
        struct add_pointer_auxiliary<F(Args..., ...), true> final {
            using result = F (*)(Args..., ...);
            using type = F (*)(Args..., ...);
        };
    }
    template <typename T>
    struct add_pointer final {
        using result = typename __dsa::add_pointer_auxiliary<T>::result;
        using type = typename __dsa::add_pointer_auxiliary<T>::type;
    };
}

namespace data_structure {
    template <typename T>
    struct size_of {
        using value_type = decltype(sizeof 0);
        constexpr static inline auto value {sizeof(T)};
        constexpr value_type operator()() const noexcept {
            return size_of<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return size_of<T>::value;
        }
    };
    template <typename T>
    struct alignment_of {
        using value_type = decltype(alignof(T));
        constexpr static inline auto value {alignof(T)};
        constexpr value_type operator()() const noexcept {
            return alignment_of<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return alignment_of<T>::value;
        }
    };
    template <typename T>
    struct rank {
        using value_type = decltype(sizeof 0);
        constexpr static inline value_type value {0};
        constexpr value_type operator()() const noexcept {
            return rank<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return rank<T>::value;
        }
    };
    template <typename T>
    struct rank<T []> {
        using value_type = decltype(sizeof 0);
        constexpr static inline value_type value {rank<T>::value + 1};
        constexpr value_type operator()() const noexcept {
            return rank<T []>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return rank<T []>::value;
        }
    };
    template <typename T, decltype(sizeof 0) N>
    struct rank<T [N]> {
        using value_type = decltype(sizeof 0);
        constexpr static inline value_type value {rank<T>::value + 1};
        constexpr value_type operator()() const noexcept {
            return rank<T [N]>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return rank<T [N]>::value;
        }
    };
    template <typename T, decltype(sizeof 0) N>
    struct extent {
        using value_type = decltype(sizeof 0);
        constexpr static inline value_type value {0};
        constexpr value_type operator()() const noexcept {
            return extent<T, N>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return extent<T, N>::value;
        }
    };
    template <typename T>
    struct extent<T, 0> {
        using value_type = decltype(sizeof 0);
        constexpr static inline value_type value {0};
        constexpr value_type operator()() const noexcept {
            return extent<T, 0>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return extent<T, 0>::value;
        }
    };
    template <typename T, decltype(sizeof 0) N>
    struct extent<T [], N> {
        using value_type = decltype(sizeof 0);
        constexpr static inline value_type value {extent<T, N - 1>::value};
        constexpr value_type operator()() const noexcept {
            return extent<T [], N>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return extent<T [], N>::value;
        }
    };
    template <typename T>
    struct extent<T [], 0> {
        using value_type = decltype(sizeof 0);
        constexpr static inline value_type value {0};
        constexpr value_type operator()() const noexcept {
            return extent<T [], 0>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return extent<T [], 0>::value;
        }
    };
    template <typename T, decltype(sizeof 0) N, decltype(sizeof 0) Size>
    struct extent<T [Size], N> {
        using value_type = decltype(sizeof 0);
        constexpr static inline value_type value {extent<T, N - 1>::value};
        constexpr value_type operator()() const noexcept {
            return extent<T [Size], N>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return extent<T [Size], N>::value;
        }
    };
    template <typename T, decltype(sizeof 0) Size>
    struct extent<T [Size], 0> {
        using value_type = decltype(sizeof 0);
        constexpr static inline value_type value {Size};
        constexpr value_type operator()() const noexcept {
            return extent<T [Size], 0>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return extent<T [Size], 0>::value;
        }
    };
    template <typename T, T ...Args>
    struct find_max;
    template <typename T, T Arg>
    struct find_max<T, Arg> final {
        using value_type = T;
        constexpr static inline value_type value {Arg};
        constexpr value_type operator()() const noexcept {
            return find_max<T, Arg>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return find_max<T, Arg>::value;
        }
    };
    template <typename T, T Arg_1, T Arg_2>
    struct find_max<T, Arg_1, Arg_2> final {
        using value_type = T;
        constexpr static inline value_type value {Arg_1 >= Arg_2 ? Arg_1 : Arg_2};
        constexpr value_type operator()() const noexcept {
            return find_max<T, Arg_1, Arg_2>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return find_max<T, Arg_1, Arg_2>::value;
        }
    };
    template <typename T, T Arg_1, T Arg_2, T ...Args>
    struct find_max<T, Arg_1, Arg_2, Args...> final {
        using value_type = T;
        constexpr static inline value_type value {
            find_max<value_type, Arg_1 >= Arg_2 ? Arg_1 : Arg_2, Args...>::value
        };
        constexpr value_type operator()() const noexcept {
            return find_max<T, Arg_1, Arg_2, Args...>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return find_max<T, Arg_1, Arg_2, Args...>::value;
        }
    };
    template <typename T, T ...Args>
    struct find_min;
    template <typename T, T Arg>
    struct find_min<T, Arg> final {
        using value_type = T;
        constexpr static inline value_type value {Arg};
        constexpr value_type operator()() const noexcept {
            return find_min<T, Arg>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return find_min<T, Arg>::value;
        }
    };
    template <typename T, T Arg_1, T Arg_2>
    struct find_min<T, Arg_1, Arg_2> final {
        using value_type = T;
        constexpr static inline value_type value {Arg_1 <= Arg_2 ? Arg_1 : Arg_2};
        constexpr value_type operator()() const noexcept {
            return find_min<T, Arg_1, Arg_2>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return find_min<T, Arg_1, Arg_2>::value;
        }
    };
    template <typename T, T Arg_1, T Arg_2, T ...Args>
    struct find_min<T, Arg_1, Arg_2, Args...> final {
        using value_type = T;
        constexpr static inline value_type value {
                find_min<value_type, Arg_1 <= Arg_2 ? Arg_1 : Arg_2, Args...>::value
        };
        constexpr value_type operator()() const noexcept {
            return find_min<T, Arg_1, Arg_2, Args...>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return find_min<T, Arg_1, Arg_2, Args...>::value;
        }
    };
    template <typename ...>
    struct make_void final {
        using result = void;
        using type = void;
    };
    template <decltype(sizeof 0) Len, decltype(alignof(void *)) Align>
    struct aligned_storage final {
        struct type {
            alignas(Align) unsigned char data[Len];
        };
        using result = type;
    };
    template <decltype(sizeof 0) Len, typename ...Ts>
    struct aligned_union final {
        using value_type = decltype(Len);
        constexpr static inline value_type alignment_value {
            find_max<decltype(alignof(void *)), alignof(Ts)...>::value
        };
        struct type {
            alignas(alignment_value) char data[find_max<value_type, Len, sizeof(Ts)...>::value];
        };
        using result = type;
        constexpr static inline value_type value {alignment_value};
        constexpr value_type operator()() const noexcept {
            return aligned_union<Len, Ts...>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return aligned_union<Len, Ts...>::value;
        }
    };
    template <typename Head, typename Tail>
    struct type_list final {
        using head = Head;
        using tail = Tail;
    };
    template <typename ...>
    struct type_container;
    template <typename Head, typename Next, typename ...Ts>
    struct type_container<Head, Next, Ts...> final {
        using this_type = Head;
        using next_type = typename type_container<Next, Ts...>::this_type;
        using subcontainer = type_container<Next, Ts...>;
    };
    template <typename T>
    struct type_container<T> final {
        using this_type = T;
        using subcontainer = void;
    };
    template <typename BaseType, typename WaitingType>
    struct copy_const final {
    private:
        using in_type = BaseType;
        using out_type = WaitingType;
    public:
        using result = typename conditional<is_const<BaseType>::value, const out_type, out_type>::result;
        using type = typename conditional<is_const<BaseType>::value, const out_type, out_type>::type;
    };
    template <typename BaseType, typename WaitingType>
    struct copy_volatile final {
    private:
        using in_type = BaseType;
        using out_type = WaitingType;
    public:
        using result = typename conditional<is_volatile<BaseType>::value, volatile out_type, out_type>::result;
        using type = typename conditional<is_volatile<BaseType>::value, volatile out_type, out_type>::result;
    };
    template <typename BaseType, typename WaitingType>
    struct copy_cv final {
        using result = typename copy_const<BaseType,
                typename copy_volatile<BaseType, WaitingType>::result>::result;
        using type = typename copy_const<BaseType, typename copy_volatile<BaseType, WaitingType>::type>::type;
    };
    template <typename BaseType, typename WaitingType>
    struct copy_lvalue_reference final {
    private:
        using in_type = BaseType;
        using out_type = WaitingType;
    public:
        using result = typename conditional<is_lvalue_reference<in_type>::value,
                typename add_lvalue_reference<typename remove_reference<out_type>::result>::result,
                out_type>::result;
        using type = typename conditional<is_lvalue_reference<in_type>::value,
                typename add_lvalue_reference<typename remove_reference<out_type>::type>::type,
                out_type>::result;
    };
    template <typename BaseType, typename WaitingType>
    struct copy_rvalue_reference final {
    private:
        using in_type = BaseType;
        using out_type = WaitingType;
    public:
        using result = typename conditional<is_rvalue_reference<in_type>::value,
                typename add_rvalue_reference<typename remove_reference<out_type>::result>::result,
                out_type>::result;
        using type = typename conditional<is_rvalue_reference<in_type>::value,
                typename add_rvalue_reference<typename remove_reference<out_type>::type>::type,
                out_type>::type;
    };
    template <typename BaseType, typename WaitingType>
    struct copy_reference final {
    private:
        using in_type = BaseType;
        using out_type = WaitingType;
    public:
        using result = typename conditional<is_lvalue_reference<in_type>::value,
                typename copy_lvalue_reference<in_type, out_type>::result,
                typename conditional<is_rvalue_reference<in_type>::value,
                        typename copy_rvalue_reference<in_type, out_type>::result,
                        out_type>::result>::result;
        using type = typename conditional<is_lvalue_reference<in_type>::value,
                typename copy_lvalue_reference<in_type, out_type>::type,
                typename conditional<is_rvalue_reference<in_type>::value,
                        typename copy_rvalue_reference<in_type, out_type>::result,
                        out_type>::type>::type;
    };
    namespace __data_structure_auxiliary {
        using signed_type_list = type_list<signed char,
                type_list<signed short int,
                        type_list<signed int,
                                type_list<signed long int,
                                        type_list<signed long long int,
                                                __int128 /* __int128_t */ >>>>>;
        using unsigned_type_list = type_list<unsigned char,
                type_list<unsigned short int,
                        type_list<unsigned int,
                                type_list<unsigned long int,
                                        type_list<unsigned long long int, __uint128_t>>>>>;
        using signed_type_container = type_container<signed char, signed short int,
                signed int, signed long int,
                signed long long int, __int128 /* __int128_t */ >;
        using unsigned_type_container = type_container<unsigned char, unsigned short int, unsigned int,
                unsigned long int, unsigned long long int, __uint128_t>;
        template <decltype(sizeof 0) Size, typename TypeContainer>
        struct find_first_type_that_is_suitable final {
            using result = typename conditional<Size <= sizeof(typename TypeContainer::this_type),
                    typename TypeContainer::this_type,
                    typename find_first_type_that_is_suitable<
                            Size, typename TypeContainer::subcontainer>::result
            >::result;
            using type = typename conditional<Size <= sizeof(typename TypeContainer::this_type),
                    typename TypeContainer::this_type,
                    typename find_first_type_that_is_suitable<
                            Size, typename TypeContainer::subcontainer>::type
            >::type;
        };
        template <decltype(sizeof 0) Size>
        struct find_first_type_that_is_suitable<Size, void> final {
            using result = void;
            using type = void;
        };
    }
    template <typename T>
    struct make_signed final {
        static_assert(is_integral<T>::value or is_enum<T>::value,
                      "The template argument must be an integral type (except bool)!");
        static_assert(not is_same<T, bool>::value, "The template argument cannot be a bool type!");
        using result = typename copy_cv<T,
                typename __dsa::find_first_type_that_is_suitable<
                        sizeof(T), __dsa::signed_type_container>::result
        >::result;
        using type = typename copy_cv<T,
                typename __dsa::find_first_type_that_is_suitable<
                        sizeof(T), __dsa::signed_type_container>::type>::type;
    };
    template <>
    struct make_signed<signed char> final {
        using result = signed char;
        using type = signed char;
    };
    template <>
    struct make_signed<const signed char> final {
        using result = const signed char;
        using type = const signed char;
    };
    template <>
    struct make_signed<volatile signed char> final {
        using result = volatile signed char;
        using type = volatile signed char;
    };
    template <>
    struct make_signed<const volatile signed char> final {
        using result = const volatile signed char;
        using type = const volatile signed char;
    };
    template <>
    struct make_signed<unsigned char> final {
        using result = signed char;
        using type = signed char;
    };
    template <>
    struct make_signed<const unsigned char> final {
        using result = const signed char;
        using type = const signed char;
    };
    template <>
    struct make_signed<volatile unsigned char> final {
        using result = volatile signed char;
        using type = volatile signed char;
    };
    template <>
    struct make_signed<const volatile unsigned char> final {
        using result = const volatile signed char;
        using type = const volatile signed char;
    };
    template <>
    struct make_signed<signed short int> final {
        using result = signed short int;
        using type = signed short int;
    };
    template <>
    struct make_signed<const signed short int> final {
        using result = const signed short int;
        using type = const signed short int;
    };
    template <>
    struct make_signed<volatile signed short int> final {
        using result = volatile signed short int;
        using type = volatile signed short int;
    };
    template <>
    struct make_signed<const volatile signed short int> final {
        using result = const volatile signed short int;
        using type = const volatile signed short int;
    };
    template <>
    struct make_signed<unsigned short int> final {
        using result = signed short int;
        using type = signed short int;
    };
    template <>
    struct make_signed<const unsigned short int> final {
        using result = const signed short int;
        using type = const signed short int;
    };
    template <>
    struct make_signed<volatile unsigned short int> final {
        using result = volatile signed short int;
        using type = volatile signed short int;
    };
    template <>
    struct make_signed<const volatile unsigned short int> final {
        using result = const volatile signed short int;
        using type = const volatile signed short int;
    };
    template <>
    struct make_signed<signed int> final {
        using result = signed int;
        using type = signed int;
    };
    template <>
    struct make_signed<const signed int> final {
        using result = const signed int;
        using type = const signed int;
    };
    template <>
    struct make_signed<volatile signed int> final {
        using result = volatile signed int;
        using type = volatile signed int;
    };
    template <>
    struct make_signed<const volatile signed int> final {
        using result = const volatile signed int;
        using type = const volatile signed int;
    };
    template <>
    struct make_signed<unsigned int> final {
        using result = signed int;
        using type = signed int;
    };
    template <>
    struct make_signed<const unsigned int> final {
        using result = const signed int;
        using type = const signed int;
    };
    template <>
    struct make_signed<volatile unsigned int> final {
        using result = volatile signed int;
        using type = volatile signed int;
    };
    template <>
    struct make_signed<const volatile unsigned int> final {
        using result = const volatile signed int;
        using type = const volatile signed int;
    };
    template <>
    struct make_signed<signed long int> final {
        using result = signed long int;
        using type = signed long int;
    };
    template <>
    struct make_signed<const signed long int> final {
        using result = const signed long int;
        using type = const signed long int;
    };
    template <>
    struct make_signed<volatile signed long int> final {
        using result = volatile signed long int;
        using type = volatile signed long int;
    };
    template <>
    struct make_signed<const volatile signed long int> final {
        using result = const volatile signed long int;
        using type = const volatile signed long int;
    };
    template <>
    struct make_signed<unsigned long int> final {
        using result = signed long int;
        using type = signed long int;
    };
    template <>
    struct make_signed<const unsigned long int> final {
        using result = const signed long int;
        using type = const signed long int;
    };
    template <>
    struct make_signed<volatile unsigned long int> final {
        using result = volatile signed long int;
        using type = volatile signed long int;
    };
    template <>
    struct make_signed<const volatile unsigned long int> final {
        using result = const volatile signed long int;
        using type = const volatile signed long int;
    };
    template <>
    struct make_signed<signed long long int> final {
        using result = signed long long int;
        using type = signed long long int;
    };
    template <>
    struct make_signed<const signed long long int> final {
        using result = const signed long long int;
        using type = const signed long long int;
    };
    template <>
    struct make_signed<volatile signed long long int> final {
        using result = volatile signed long long int;
        using type = volatile signed long long int;
    };
    template <>
    struct make_signed<const volatile signed long long int> final {
        using result = const volatile signed long long int;
        using type = const volatile signed long long int;
    };
    template <>
    struct make_signed<unsigned long long int> final {
        using result = signed long long int;
        using type = signed long long int;
    };
    template <>
    struct make_signed<const unsigned long long int> final {
        using result = const signed long long int;
        using type = const signed long long int;
    };
    template <>
    struct make_signed<volatile unsigned long long int> final {
        using result = volatile signed long long int;
        using type = volatile signed long long int;
    };
    template <>
    struct make_signed<const volatile unsigned long long int> final {
        using result = const volatile signed long long int;
        using type = const volatile signed long long int;
    };
    template <>
    struct make_signed<signed wchar_t> final {
        using result = signed wchar_t;
        using type = signed wchar_t;
    };
    template <>
    struct make_signed<const signed wchar_t> final {
        using result = const signed wchar_t;
        using type = const signed wchar_t;
    };
    template <>
    struct make_signed<volatile signed wchar_t> final {
        using result = volatile signed wchar_t;
        using type = volatile signed wchar_t;
    };
    template <>
    struct make_signed<const volatile signed wchar_t> final {
        using result = const volatile signed wchar_t;
        using type = const volatile signed wchar_t;
    };
    template <>
    struct make_signed<__int128 /* __int128_t */ > final {
        using result = __int128 /* __int128_t */ ;
        using type = __int128 /* __int128_t */ ;
    };
    template <>
    struct make_signed<const __int128 /* __int128_t */ > final {
        using result = const __int128 /* __int128_t */ ;
        using type = const __int128 /* __int128_t */ ;
    };
    template <>
    struct make_signed<volatile __int128 /* __int128_t */ > final {
        using result = volatile __int128 /* __int128_t */ ;
        using type = volatile __int128 /* __int128_t */ ;
    };
    template <>
    struct make_signed<const volatile __int128 /* __int128_t */ > final {
        using result = __int128 /* __int128_t */ ;
        using type = const volatile __int128 /* __int128_t */ ;
    };
    template <>
    struct make_signed<__uint128_t> final {
        using result = __int128 /* __int128_t */ ;
        using type = __int128 /* __int128_t */ ;
    };
    template <>
    struct make_signed<const __uint128_t> final {
        using result = const __int128 /* __int128_t */ ;
        using type = const __int128 /* __int128_t */ ;
    };
    template <>
    struct make_signed<volatile __uint128_t> final {
        using result = volatile __int128 /* __int128_t */ ;
        using type = volatile __int128 /* __int128_t */ ;
    };
    template <>
    struct make_signed<const volatile __uint128_t> final {
        using result = const volatile __int128 /* __int128_t */ ;
        using type = const volatile __int128 /* __int128_t */ ;
    };
    template <typename T>
    struct make_unsigned final {
        static_assert(is_integral<T>::value or is_enum<T>::value,
                      "The template argument must be an integral type (except bool)!");
        static_assert(not is_same<T, bool>::value, "The template argument cannot be a bool type!");
        using result = typename copy_cv<T,
                typename __dsa::find_first_type_that_is_suitable<
                        sizeof(T), __dsa::unsigned_type_container>::result
        >::result;
        using type = typename copy_cv<T,
                typename __dsa::find_first_type_that_is_suitable<
                        sizeof(T), __dsa::unsigned_type_container>::type>::type;
    };
    template <>
    struct make_unsigned<signed char> final {
        using result = unsigned char;
        using type = signed char;
    };
    template <>
    struct make_unsigned<const signed char> final {
        using result = const unsigned char;
        using type = const signed char;
    };
    template <>
    struct make_unsigned<volatile signed char> final {
        using result = volatile unsigned char;
        using type = volatile signed char;
    };
    template <>
    struct make_unsigned<const volatile signed char> final {
        using result = const volatile unsigned char;
        using type = const volatile signed char;
    };
    template <>
    struct make_unsigned<unsigned char> final {
        using result = unsigned char;
        using type = signed char;
    };
    template <>
    struct make_unsigned<const unsigned char> final {
        using result = const unsigned char;
        using type = const signed char;
    };
    template <>
    struct make_unsigned<volatile unsigned char> final {
        using result = volatile unsigned char;
        using type = volatile signed char;
    };
    template <>
    struct make_unsigned<const volatile unsigned char> final {
        using result = const volatile unsigned char;
        using type = const volatile signed char;
    };
    template <>
    struct make_unsigned<signed short int> final {
        using result = unsigned short int;
        using type = signed short int;
    };
    template <>
    struct make_unsigned<const signed short int> final {
        using result = const unsigned short int;
        using type = const signed short int;
    };
    template <>
    struct make_unsigned<volatile signed short int> final {
        using result = volatile unsigned short int;
        using type = volatile signed short int;
    };
    template <>
    struct make_unsigned<const volatile signed short int> final {
        using result = const volatile unsigned short int;
        using type = const volatile signed short int;
    };
    template <>
    struct make_unsigned<unsigned short int> final {
        using result = unsigned short int;
        using type = signed short int;
    };
    template <>
    struct make_unsigned<const unsigned short int> final {
        using result = const unsigned short int;
        using type = const signed short int;
    };
    template <>
    struct make_unsigned<volatile unsigned short int> final {
        using result = volatile unsigned short int;
        using type = volatile signed short int;
    };
    template <>
    struct make_unsigned<const volatile unsigned short int> final {
        using result = const volatile unsigned short int;
        using type = const volatile signed short int;
    };
    template <>
    struct make_unsigned<signed int> final {
        using result = unsigned int;
        using type = signed int;
    };
    template <>
    struct make_unsigned<const signed int> final {
        using result = const unsigned int;
        using type = const signed int;
    };
    template <>
    struct make_unsigned<volatile signed int> final {
        using result = volatile unsigned int;
        using type = volatile signed int;
    };
    template <>
    struct make_unsigned<const volatile signed int> final {
        using result = const volatile unsigned int;
        using type = const volatile signed int;
    };
    template <>
    struct make_unsigned<unsigned int> final {
        using result = unsigned int;
        using type = signed int;
    };
    template <>
    struct make_unsigned<const unsigned int> final {
        using result = const unsigned int;
        using type = const signed int;
    };
    template <>
    struct make_unsigned<volatile unsigned int> final {
        using result = volatile unsigned int;
        using type = volatile signed int;
    };
    template <>
    struct make_unsigned<const volatile unsigned int> final {
        using result = const volatile unsigned int;
        using type = const volatile signed int;
    };
    template <>
    struct make_unsigned<signed long int> final {
        using result = unsigned long int;
        using type = signed long int;
    };
    template <>
    struct make_unsigned<const signed long int> final {
        using result = const unsigned long int;
        using type = const signed long int;
    };
    template <>
    struct make_unsigned<volatile signed long int> final {
        using result = volatile unsigned long int;
        using type = volatile signed long int;
    };
    template <>
    struct make_unsigned<const volatile signed long int> final {
        using result = const volatile unsigned long int;
        using type = const volatile signed long int;
    };
    template <>
    struct make_unsigned<unsigned long int> final {
        using result = unsigned long int;
        using type = signed long int;
    };
    template <>
    struct make_unsigned<const unsigned long int> final {
        using result = const unsigned long int;
        using type = const signed long int;
    };
    template <>
    struct make_unsigned<volatile unsigned long int> final {
        using result = volatile unsigned long int;
        using type = volatile signed long int;
    };
    template <>
    struct make_unsigned<const volatile unsigned long int> final {
        using result = const volatile unsigned long int;
        using type = const volatile signed long int;
    };
    template <>
    struct make_unsigned<signed long long int> final {
        using result = unsigned long long int;
        using type = signed long long int;
    };
    template <>
    struct make_unsigned<const signed long long int> final {
        using result = const unsigned long long int;
        using type = const signed long long int;
    };
    template <>
    struct make_unsigned<volatile signed long long int> final {
        using result = volatile unsigned long long int;
        using type = volatile signed long long int;
    };
    template <>
    struct make_unsigned<const volatile signed long long int> final {
        using result = const volatile unsigned long long int;
        using type = const volatile signed long long int;
    };
    template <>
    struct make_unsigned<unsigned long long int> final {
        using result = unsigned long long int;
        using type = signed long long int;
    };
    template <>
    struct make_unsigned<const unsigned long long int> final {
        using result = const unsigned long long int;
        using type = const signed long long int;
    };
    template <>
    struct make_unsigned<volatile unsigned long long int> final {
        using result = volatile unsigned long long int;
        using type = volatile signed long long int;
    };
    template <>
    struct make_unsigned<const volatile unsigned long long int> final {
        using result = const volatile unsigned long long int;
        using type = const volatile signed long long int;
    };
    template <>
    struct make_unsigned<signed wchar_t> final {
        using result = unsigned wchar_t;
        using type = signed wchar_t;
    };
    template <>
    struct make_unsigned<const signed wchar_t> final {
        using result = const unsigned wchar_t;
        using type = const signed wchar_t;
    };
    template <>
    struct make_unsigned<volatile signed wchar_t> final {
        using result = volatile unsigned wchar_t;
        using type = volatile signed wchar_t;
    };
    template <>
    struct make_unsigned<const volatile signed wchar_t> final {
        using result = const volatile unsigned wchar_t;
        using type = const volatile signed wchar_t;
    };
    template <>
    struct make_unsigned<__int128 /* __int128_t */ > final {
        using result = __int128 /* __int128_t */ ;
        using type = __int128 /* __int128_t */;
    };
    template <>
    struct make_unsigned<const __int128 /* __int128_t */ > final {
        using result = const __int128 /* __int128_t */ ;
        using type = const __int128 /* __int128_t */;
    };
    template <>
    struct make_unsigned<volatile __int128 /* __int128_t */ > final {
        using result = volatile __int128 /* __int128_t */ ;
        using type = volatile __int128 /* __int128_t */;
    };
    template <>
    struct make_unsigned<const volatile __int128 /* __int128_t */ > final {
        using result = __int128 /* __int128_t */ ;
        using type = const volatile __int128 /* __int128_t */;
    };
    template <>
    struct make_unsigned<__uint128_t> final {
        using result = __int128 /* __int128_t */ ;
        using type = __int128 /* __int128_t */ ;
    };
    template <>
    struct make_unsigned<const __uint128_t> final {
        using result = const __int128 /* __int128_t */ ;
        using type = const __int128 /* __int128_t */ ;
    };
    template <>
    struct make_unsigned<volatile __uint128_t> final {
        using result = volatile __int128 /* __int128_t */ ;
        using type = volatile __int128 /* __int128_t */ ;
    };
    template <>
    struct make_unsigned<const volatile __uint128_t> final {
        using result = const volatile __int128 /* __int128_t */ ;
        using type = const volatile __int128 /* __int128_t */ ;
    };
    template <typename Integer, Integer Value>
    struct integral_constant {
        static_assert(is_integral<Integer>::value or is_enum<Integer>::value,
                "The first template argument is not a integral type!");
        using value_type = Integer;
        constexpr static inline auto value {Value};
        constexpr value_type operator()() const noexcept {
            return integral_constant<Integer, Value>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return integral_constant<Integer, Value>::value;
        }
    };
    template <bool Value>
    struct bool_constant {
        using value_type = bool;
        constexpr static inline auto value {Value};
        constexpr value_type operator()() const noexcept {
            return bool_constant<Value>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return bool_constant<Value>::value;
        }
    };
    template <typename FloatingPoint, FloatingPoint Value>
    struct floating_point_constant {
        static_assert(is_floating_point<FloatingPoint>::value,
                "The first template argument is not a floating-point type!");
        using value_type = FloatingPoint;
        constexpr static inline auto value {Value};
        constexpr value_type operator()() const noexcept {
            return floating_point_constant<FloatingPoint, Value>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return floating_point_constant<FloatingPoint, Value>::value;
        }
    };
    template <typename T>
    struct decay final {
        using result = typename conditional<
                is_array<typename remove_reference<T>::result>::value,
                typename remove_extent<typename remove_reference<T>::result>::result *,
                typename conditional<
                        is_function<typename remove_reference<T>::result>::value,
                        typename add_pointer<typename remove_reference<T>::result>::result,
                        typename remove_cv<typename remove_reference<T>::result>::result>::result>::result;
        using type = typename conditional<
                is_array<typename remove_reference<T>::type>::value,
                typename remove_extent<typename remove_reference<T>::type>::type *,
                typename conditional<
                        is_function<typename remove_reference<T>::type>::value,
                        typename add_pointer<typename remove_reference<T>::type>::type,
                        typename remove_cv<typename remove_reference<T>::type>::type>::type>::type;
    };
    template <typename ...>
    struct common_type final {};
    template <typename T>
    struct common_type<T> final {
        using result = typename common_type<T, T>::result;
        using type = typename common_type<T, T>::type;
    };
    namespace __data_structure_auxiliary {
        template <typename Type_1, typename Type_2, typename = void>
        struct common_type2_auxiliary final {};
        template <typename Type_1, typename Type_2>
        struct common_type2_auxiliary<Type_1, Type_2, typename make_void<
                decltype(is_type<Type_1>::value or is_type<Type_2>::value ?
                        declval<Type_1>() : declval<Type_2>())>::type> final {
            using result = typename decay<
                    decltype(is_type<Type_1>::value or is_type<Type_2>::value ?
                            declval<Type_1>() : declval<Type_2>())>::result;
            using type = typename decay<
                    decltype(is_type<Type_1>::value or is_type<Type_2>::value ?
                            declval<Type_1>() : declval<Type_2>())>::type;
        };
        template <typename Type_1, typename Type_2,
                typename DecayType_1 = typename decay<Type_1>::type,
                typename DecayType_2 = typename decay<Type_2>::type,
                bool IsSame = is_same<Type_1, DecayType_1>::value and
                        is_same<Type_2, DecayType_2>::value>
        struct common_type2 final {
            using result = typename common_type2_auxiliary<Type_1, Type_2>::result;
            using type = typename common_type2_auxiliary<Type_1, Type_2>::type;
        };
        template <typename Type_1, typename Type_2, typename DecayType_1, typename DecayType_2>
        struct common_type2<Type_1, Type_2, DecayType_1, DecayType_2, false> final {
            using result = typename common_type<DecayType_1, DecayType_2>::result;
            using type = typename common_type<DecayType_1, DecayType_2>::type;
        };
        template <typename, typename = void>
        struct common_type_auxiliary final {};
        template <typename Type_1, typename Type_2>
        struct common_type_auxiliary<type_container<Type_1, Type_2>,
                typename make_void<typename common_type<Type_1, Type_2>::type>::type> final {
            using result = typename common_type<Type_1, Type_2>::result;
            using type = typename common_type<Type_1, Type_2>::type;
        };
        template <typename Type_1, typename Type_2, typename ...Ts>
        struct common_type_auxiliary<type_container<Type_1, Type_2, Ts...>,
                typename make_void<typename common_type<Type_1, Type_2>::type>::type> final {
            using result = typename common_type_auxiliary<
                    type_container<typename common_type<Type_1, Type_2>::result, Ts...>>::result;
            using type = typename common_type_auxiliary<
                    type_container<typename common_type<Type_1, Type_2>::type, Ts...>>::type;
        };
    }
    template <typename Type_1, typename Type_2>
    struct common_type<Type_1, Type_2> final {
        using type = typename __dsa::common_type2<Type_1, Type_2>::type;
        using result = typename __dsa::common_type2<Type_1, Type_2>::result;
    };
    template <typename Type_1, typename Type_2, typename ...Ts>
    struct common_type<Type_1, Type_2, Ts...> final {
        using result = typename __dsa::common_type_auxiliary<
                type_container<Type_1, Type_2, Ts...>>::result;
        using type = typename __dsa::common_type_auxiliary<
                type_container<Type_1, Type_2, Ts...>>::type;
    };
    template <typename T>
    struct underlying_type final {
        static_assert(is_enum<T>::value, "The template argument must be an enumeration type!");
        using result = __underlying_type(T);
        using type = __underlying_type(T);
    };
    namespace __data_structure_auxiliary {
#if false
        template <typename T>
        struct floating_point_promotion_auxiliary final {
            static_assert(is_floating_point<T>::value,
                    "The template argument must be a floating point type!");
        };
        template <>
        struct floating_point_promotion_auxiliary<float> final {
            using result = double;
            using type = double;
        };
        template <>
        struct floating_point_promotion_auxiliary<double> final {
            using result = long double;
            using type = long double;
        };
        template <>
        struct floating_point_promotion_auxiliary<long double> final {
            using result = long double;
            using type = long double;
        };
#endif
        using floating_point_container = type_container<float, double, long double>;
        using floating_point_type_list = type_list<float, type_list<double, long double>>;
        template <decltype(sizeof 0) Size, typename TypeContainer>
        struct find_first_type_that_is_bigger final {
            using result = typename conditional<
                    (sizeof(typename TypeContainer::this_type) <= Size),
                    typename find_first_type_that_is_bigger<
                            Size, typename TypeContainer::subcontainer>::result,
                    typename TypeContainer::this_type>::result;
            using type = typename conditional<
                    (sizeof(typename TypeContainer::this_type) <= Size),
                    typename find_first_type_that_is_bigger<
                            Size, typename TypeContainer::subcontainer>::type,
                    typename TypeContainer::this_type>::type;
        };
        template <decltype(sizeof 0) Size>
        struct find_first_type_that_is_bigger<Size, void> final {
            using result = void;
            using type = void;
        };
        template <typename T>
        struct floating_point_promotion_auxiliary final {
            using result = typename find_first_type_that_is_bigger<
                    sizeof(T), floating_point_container>::result;
            using type = typename find_first_type_that_is_bigger<
                    sizeof(T), floating_point_container>::type;
        };
        template <>
        struct floating_point_promotion_auxiliary<long double> final {
            using result = long double;
            using type = long double;
        };
    }
    template <typename T>
    struct floating_point_promotion final {
        static_assert(is_floating_point<typename remove_reference<T>::result>::value,
                "The template argument must be a floating point type!");
        using result = typename copy_reference<T, typename copy_cv<typename remove_reference<T>::result,
                typename __dsa::floating_point_promotion_auxiliary<
                        typename remove_cv<typename remove_reference<T>::result>::result
                >::result>::result>::result;
        using type = typename copy_reference<T, typename copy_cv<typename remove_reference<T>::type,
                typename __dsa::floating_point_promotion_auxiliary<
                        typename remove_cv<typename remove_reference<T>::type>::type
                >::type>::type>::type;
    };
    namespace __data_structure_auxiliary {
        template <typename T, bool IsEnum = is_enum<T>::value>
        struct integral_promotion_auxiliary final {
            static_assert(is_integral<T>::value,
                    "The first template argument must be an integral type!");
            using result = typename conditional<is_signed<T>::value,
                    typename find_first_type_that_is_bigger<sizeof(T), signed_type_container>::result,
                    typename find_first_type_that_is_bigger<sizeof(T), unsigned_type_container>::result
            >::result;
            using type = typename conditional<is_signed<T>::value,
                    typename find_first_type_that_is_bigger<sizeof(T), signed_type_container>::type,
                    typename find_first_type_that_is_bigger<sizeof(T), unsigned_type_container>::type
            >::type;
        };
        template <>
        struct integral_promotion_auxiliary<__int128 /* __int128_t */ , false> final {
            using result = __int128 /* __int128_t */ ;
            using type = __int128 /* __int128_t */ ;
        };
        template <>
        struct integral_promotion_auxiliary<__uint128_t, false> final {
            using result = __uint128_t;
            using type = __uint128_t;
        };
        template <typename T>
        struct integral_promotion_auxiliary<T, true> final {
            using result = typename conditional<is_signed<__underlying_type(T)>::value,
                    typename find_first_type_that_is_bigger<
                            sizeof(typename make_signed<T>::result), signed_type_container>::result,
                    typename find_first_type_that_is_bigger<
                            sizeof(typename make_unsigned<T>::result), unsigned_type_container>::result
            >::result;
            using type = typename conditional<is_signed<__underlying_type(T)>::value,
                    typename find_first_type_that_is_bigger<
                            sizeof(typename make_signed<T>::type), signed_type_container>::type,
                    typename find_first_type_that_is_bigger<
                            sizeof(typename make_unsigned<T>::type), unsigned_type_container>::type
            >::type;
        };
    }
    template <typename T>
    struct integral_promotion final {
        static_assert(is_integral<typename remove_reference<T>::result>::value or
                is_enum<typename remove_reference<T>::result>::value,
                "The template argument must be a floating point type!");
        using result = typename copy_reference<T, typename copy_cv<typename remove_reference<T>::result,
                typename __dsa::integral_promotion_auxiliary<
                        typename remove_cv<typename remove_reference<T>::result>::result
                >::result>::result>::result;
        using type = typename copy_reference<T, typename copy_cv<typename remove_reference<T>::type,
                typename __dsa::integral_promotion_auxiliary<
                        typename remove_cv<typename remove_reference<T>::type>::type
                >::type>::type>::type;
    };
    namespace __data_structure_auxiliary {
        template <typename T, bool IsIntegral = is_integral<T>::value,
                bool IsEnumeration = is_enum<T>::value,
                bool IsFloatingPoint = is_floating_point<T>::value>
        struct promote_auxiliary final {
            static_assert(is_integral<T>::value or is_enum<T>::value or is_floating_point<T>::value,
                    "The first template argument must be a/an"
                    "integral type, enumeration type or floating point type");
            static_assert(is_type<T>::value, "Invalid template arguments!");
        };
        template <typename T>
        struct promote_auxiliary<T, true, false, false> final {
            using result = typename integral_promotion<T>::result;
            using type = typename integral_promotion<T>::type;
        };
        template <typename T>
        struct promote_auxiliary<T, false, true, false> final {
            using result = typename integral_promotion<T>::result;
            using type = typename integral_promotion<T>::type;
        };
        template <typename T>
        struct promote_auxiliary<T, false, false, true> final {
            using result = typename floating_point_promotion<T>::result;
            using type = typename floating_point_promotion<T>::type;
        };
    }
    template <typename T>
    struct promote final {
        using result = typename __dsa::promote_auxiliary<T>::result;
        using type = typename __dsa::promote_auxiliary<T>::type;
    };
    template <typename T>
    struct type_identify final {
        using type = T;
        using result = type;
    };
    template <typename F, typename ...Args>
    struct invoke_result final : private __dsa::check_type_is_complete<F> {
        using result = typename __dsa::result_of_auxiliary<
                is_member_object_pointer<typename remove_reference<F>::result>::value,
                is_member_object_pointer<typename remove_reference<F>::result>::value,
                F, Args...>::result;
        using type = typename __dsa::result_of_auxiliary<
                is_member_object_pointer<typename remove_reference<F>::type>::value,
                is_member_function_pointer<typename remove_reference<F>::type>::value,
                F, Args...>::type;
        static_assert(not is_same<result, __dsa::invoke_failure_tag>::value,
                "Invalid template arguments or the function or object isn't reachable!");
    };
    template <typename T, typename ...>
    struct result_of final : private __dsa::check_type_is_complete<T> {
        static_assert(not __dsa::is_type<T>::value, "Invalid template arguments!");
    };
    template <typename F, typename ...Args>
    struct result_of<F (Args...)> final : private __dsa::check_type_is_complete<F> {
        using result = typename invoke_result<F, Args...>::result;
        using type = typename invoke_result<F, Args...>::type;
        static_assert(not is_same<result, __dsa::invoke_failure_tag>::value,
                "The function isn't callable!");
    };
}

namespace data_structure {
    template <typename T>
    struct function_traits {
        static_assert(is_function<T>::value, "The template argument is not a function type!");
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args...)> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args..., ...)> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args...) const> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args...) volatile> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args...) const volatile> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args..., ...) const> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args..., ...) volatile> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args..., ...) const volatile> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args...) &> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __true_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args...) const &> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __true_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args...) volatile &> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __true_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args...) const volatile &> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __true_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args..., ...) &> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __true_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args..., ...) const &> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __true_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args..., ...) volatile &> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __true_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args..., ...) const volatile &> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __true_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args...) &&> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __true_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args...) const &&> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __true_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args...) volatile &&> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __true_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args...) const volatile &&> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __true_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args..., ...) &&> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __true_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args..., ...) const &&> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __true_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args..., ...) volatile &&> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __true_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args..., ...) const volatile &&> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __true_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args...) noexcept> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args..., ...) noexcept> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args...) const noexcept> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args...) volatile noexcept> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args...) const volatile noexcept> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args..., ...) const noexcept> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args..., ...) volatile noexcept> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args..., ...) const volatile noexcept> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args...) & noexcept> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __true_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args...) const & noexcept> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __true_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args...) volatile & noexcept> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __true_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args...) const volatile & noexcept> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __true_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args..., ...) & noexcept> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __true_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args..., ...) const & noexcept> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __true_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args..., ...) volatile & noexcept> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __true_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args..., ...) const volatile & noexcept> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __true_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args...) && noexcept> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __true_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args...) const && noexcept> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __true_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args...) volatile && noexcept> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __true_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args...) const volatile && noexcept> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __true_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args..., ...) && noexcept> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __true_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args..., ...) const && noexcept> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __true_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args..., ...) volatile && noexcept> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __true_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F(Args..., ...) const volatile && noexcept> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __false_type;
        using is_member_function_pointer = __false_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __true_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename ...Args>
    struct function_traits<F (*)(Args...)> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __false_type;
    };
    template <typename F, typename ...Args>
    struct function_traits<F (*)(Args..., ...)> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __false_type;
    };
    template <typename F, typename ...Args>
    struct function_traits<F (*)(Args...) noexcept> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __false_type;
    };
    template <typename F, typename ...Args>
    struct function_traits<F (*)(Args..., ...) noexcept> {
        using returning_type = F;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __false_type;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args...)> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args..., ...)> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args...) const> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args...) volatile> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args...) const volatile> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args..., ...) const> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args..., ...) volatile> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args..., ...) const volatile> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args...) &> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __true_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args...) const &> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __true_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args...) volatile &> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __true_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args...) const volatile &> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __true_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args..., ...) &> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __true_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args..., ...) const &> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __true_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args..., ...) volatile &> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __true_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args..., ...) const volatile &> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __true_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args...) &&> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __true_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args...) const &&> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __true_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args...) volatile &&> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __true_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args...) const volatile &&> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __true_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args..., ...) &&> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __true_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args..., ...) const &&> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __true_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args..., ...) volatile &&> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __true_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args..., ...) const volatile &&> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __false_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __true_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args...) noexcept> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args..., ...) noexcept> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args...) const noexcept> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args...) volatile noexcept> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args...) const volatile noexcept> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args..., ...) const noexcept> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args..., ...) volatile noexcept> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args..., ...) const volatile noexcept> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args...) & noexcept> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __true_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args...) const & noexcept> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __true_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args...) volatile & noexcept> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __true_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args...) const volatile & noexcept> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __true_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args..., ...) & noexcept> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __true_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args..., ...) const & noexcept> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __true_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args..., ...) volatile & noexcept> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __true_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args..., ...) const volatile & noexcept> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __true_type;
        using has_rvalue_reference_qualifier = __false_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args...) && noexcept> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __true_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args...) const && noexcept> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __true_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args...) volatile && noexcept> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __true_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args...) const volatile && noexcept> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __false_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __true_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args..., ...) && noexcept> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __true_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args..., ...) const && noexcept> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __false_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __true_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args..., ...) volatile && noexcept> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __false_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __true_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename F, typename Class, typename ...Args>
    struct function_traits<F (Class::*)(Args..., ...) const volatile && noexcept> {
        using returning_type = F;
        using class_type = Class;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter_function = __true_type;
        using is_nothrow_function = __true_type;
        using is_function_pointer = __true_type;
        using is_member_function_pointer = __true_type;
        using has_const_qualifier = __true_type;
        using has_volatile_qualifier = __true_type;
        using has_cv_qualifier = typename conditional<
                static_cast<bool>(has_const_qualifier()) or static_cast<bool>(has_volatile_qualifier()),
                __true_type, __false_type>::result;
        using has_lvalue_reference_qualifier = __false_type;
        using has_rvalue_reference_qualifier = __true_type;
        using has_reference_qualifier = typename conditional<
                static_cast<bool>(has_lvalue_reference_qualifier()) or
                static_cast<bool>(has_rvalue_reference_qualifier()), __true_type, __false_type>::result;
    };
    template <typename T>
    struct template_argument_traits {
        using old_type = T;
        using new_type = T;
    };
    template <template <typename ...> typename T, typename ...TArgs>
    struct template_argument_traits<T<TArgs...>> {
        using old_type = T<TArgs...>;
        using old_arguments = type_container<TArgs...>;
        template <typename ...Args>
        using new_type = T<Args...>;
    };
    template <decltype(sizeof 0) N, typename ...Args>
    struct choose_argument;
    template <decltype(sizeof 0) N, typename ThisType, typename ...Args>
    struct choose_argument<N, ThisType, Args...> {
        using result = typename choose_argument<N - 1, Args...>::result;
        using type = typename choose_argument<N - 1, Args...>::type;
    };
    template <typename ThisType, typename ...Args>
    struct choose_argument<0, ThisType, Args...> {
        using result = ThisType;
        using type = ThisType;
    };
    template <typename Allocator>
    struct allocator_traits {
    public:
        using allocator_type = Allocator;
        using size_type = typename allocator_type::size_type;
        using difference_type = typename allocator_type::difference_type;
        using value_type = typename allocator_type::value_type;
        using reference = typename allocator_type::reference;
        using const_reference = typename allocator_type::const_reference;
        using volatile_reference = typename allocator_type::volatile_reference;
        using cv_reference = typename allocator_type::cv_reference;
        using rvalue_reference = typename allocator_type::rvalue_reference;
        using pointer = typename allocator_type::pointer;
        using const_pointer = typename allocator_type::const_pointer;
        using volatile_pointer = typename allocator_type::volatile_pointer;
        using cv_pointer = typename allocator_type::cv_pointer;
        using void_pointer = typename allocator_type::void_pointer;
        using const_void_pointer = typename allocator_type::const_void_pointer;
    public:
        static void *operator new (unsigned long n)
                noexcept(noexcept(allocator_type::operator new(n))) __attribute__((always_inline)) {
            return allocator_type::operator new(n);
        }
        static void operator delete (void *p)
                noexcept(noexcept(allocator_type::operator delete(p))) __attribute__((always_inline)) {
            return allocator_type::operator delete(p);
        }
    public:
        static pointer allocate(allocator_type &allocator, size_type n)
                noexcept(noexcept(allocator.allocate(n))) __attribute__((always_inline)) {
            return allocator.allocate(n);
        }
        static pointer allocate(size_type n)
                noexcept(noexcept(allocator_type::allocate(n))) __attribute__((always_inline)) {
            return allocator_type::allocate(n);
        }
        static void deallocate(allocator_type &allocator, pointer begin, size_type n)
                noexcept(noexcept(allocator.deallocate(begin, n))) __attribute__((always_inline)) {
            allocator.deallocate(begin, n);
        }
        static void deallocate(pointer begin, size_type n)
                noexcept(noexcept(allocator_type::deallocate(begin, n))) __attribute__((always_inline)) {
            allocator_type::deallocate(begin, n);
        }
        static void construct(allocator_type &allocator, pointer obj, const_reference value)
                noexcept(noexcept(allocator.construct(obj, value))) __attribute__((always_inline)) {
            allocator.construct(obj, value);
        }
        static void construct(pointer obj, const_reference value)
                noexcept(noexcept(allocator_type::construct(obj, value))) __attribute__((always_inline)) {
            allocator_type::construct(obj, value);
        }
        static void construct(allocator_type &allocator, pointer obj, rvalue_reference value)
                noexcept(noexcept(allocator.construct(obj, move(value)))) __attribute__((always_inline)) {
            allocator.construct(obj, move(value));
        }
        static void construct(pointer obj, rvalue_reference value)
                noexcept(noexcept(allocator_type::construct(obj, move(value)))) {
            allocator_type::construct(obj, move(value));
        }
        template <typename ...Args>
        static void construct(allocator_type &allocator, pointer obj, Args &&...args)
                noexcept(noexcept(allocator.construct(obj, forward<Args>(args)...))) {
            allocator.construct(obj, forward<Args>(args)...);
        }
        template <typename ...Args>
        static void construct(pointer obj, Args &&...args)
                noexcept(noexcept(allocator_type::construct(obj, forward<Args>(args)...))) {
            allocator_type::construct(obj, forward<Args>(args)...);
        }
        static void destroy(allocator_type &allocator, pointer obj)
                noexcept(noexcept(allocator.destroy(obj))) __attribute__((always_inline)) {
            allocator.destroy(obj);
        }
        static void destroy(pointer obj) noexcept(noexcept(allocator_type::destroy(obj))) {
            allocator_type::destroy(obj);
        }
    };
    template <typename Container>
    struct container_traits {
        using container_type = Container;
        using size_type = typename container_type::size_type;
        using difference_type = typename container_type::difference_type;
        using value_type = typename container_type::value_type;
        using reference = typename container_type::reference;
        using const_reference = typename container_type::const_reference;
        using volatile_reference = typename container_type::volatile_reference;
        using cv_reference = typename container_type::cv_reference;
        using rvalue_reference = typename container_type::rvalue_reference;
        using pointer = typename container_type::pointer;
        using const_pointer = typename container_type::const_pointer;
        using volatile_pointer = typename container_type::volatile_pointer;
        using cv_pointer = typename container_type::cv_pointer;
        using void_pointer = typename container_type::void_pointer;
        using const_void_pointer = typename container_type::const_void_pointer;
    public:
        static container_type empty_container() noexcept(is_nothrow_constructible<container_type>::value) {
            return container_type();
        }
        template <typename ...Args>
        static container_type filled_container(Args &&...args)
                noexcept(is_nothrow_constructible<container_type, Args...>::value) {
            return container_type(forward<Args>(args)...);
        }
    };
    template <typename Structure>
    struct structure_traits {
    public:
        using structure_type = Structure;
        using size_type = typename structure_type::size_type;
        using difference_type = typename structure_type::difference_type;
        using value_type = typename structure_type::value_type;
        using reference = typename structure_type::reference;
        using const_reference = typename structure_type::const_reference;
        using volatile_reference = typename structure_type::volatile_reference;
        using cv_reference = typename structure_type::cv_reference;
        using rvalue_reference = typename structure_type::rvalue_reference;
        using pointer = typename structure_type::pointer;
        using const_pointer = typename structure_type::const_pointer;
        using volatile_pointer = typename structure_type::volatile_pointer;
        using cv_pointer = typename structure_type::cv_pointer;
        using void_pointer = typename structure_type::void_pointer;
        using const_void_pointer = typename structure_type::const_void_pointer;
    public:
        static structure_type empty_structure() noexcept(is_nothrow_constructible<structure_type>::value) {
            return structure_type();
        }
        template <typename ...Args>
        static structure_type filled_structure(Args &&...args)
                noexcept(is_nothrow_constructible<structure_type, Args...>::value) {
            return structure_type(forward<Args>(args)...);
        }
    };
}

namespace data_structure {
    namespace __data_structure_auxiliary {
        template <typename LHS, typename RHS = LHS>
        struct lvalue_auxiliary {
            static inline LHS lhs {declval<LHS>()};
            static inline RHS rhs {declval<RHS>()};
        };
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(declval<LHS>() bitand declval<RHS>()), __true_type>::type
        test_bit_and_operator(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_bit_and_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(lvalue_auxiliary<LHS, RHS>::lhs bitand lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type>::type
        test_bit_and_operator(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_bit_and_operator() cannot be called!");
            return {};
        }
        template <typename T, typename>
        constexpr inline __false_type test_bit_and_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_bit_and_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<noexcept(declval<LHS>() bitand declval<RHS>()),
                __true_type, __false_type>::type
        is_bit_and_operator_nothrow(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_bit_and_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<
                noexcept(lvalue_auxiliary<LHS, RHS>::lhs bitand lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type, __false_type>::type
        is_bit_and_operator_nothrow(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_bit_and_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(declval<LHS>() and_eq declval<RHS>()), __true_type>::type
        test_bit_and_assignment_operator(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_bit_and_assignment_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(lvalue_auxiliary<LHS, RHS>::lhs and_eq lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type>::type
        test_bit_and_assignment_operator(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_bit_and_assignment_operator() cannot be called!");
            return {};
        }
        template <typename T, typename>
        constexpr inline __false_type test_bit_and_assignment_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_bit_and_assignment_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<noexcept(declval<LHS>() and_eq declval<RHS>()),
                __true_type, __false_type>::type
        is_bit_and_assignment_operator_nothrow(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_bit_and_assignment_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<
                noexcept(lvalue_auxiliary<LHS, RHS>::lhs and_eq lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type, __false_type>::type
        is_bit_and_assignment_operator_nothrow(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_bit_and_assignment_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(declval<LHS>() bitor declval<RHS>()), __true_type>::type
        test_bit_or_operator(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_bit_or_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(lvalue_auxiliary<LHS, RHS>::lhs bitor lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type>::type
        test_bit_or_operator(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_bit_or_operator() cannot be called!");
            return {};
        }
        template <typename T, typename>
        constexpr inline __false_type test_bit_or_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_bit_or_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<noexcept(declval<LHS>() bitor declval<RHS>()),
                __true_type, __false_type>::type
        is_bit_or_operator_nothrow(int) noexcept {
            static_assert(not is_type<RHS>::value,
                    "The function is_bit_or_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<
                noexcept(lvalue_auxiliary<LHS, RHS>::lhs bitor lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type, __false_type>::type
        is_bit_or_operator_nothrow(long) noexcept {
            static_assert(not is_type<RHS>::value,
                    "The function is_bit_or_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(declval<LHS>() or_eq declval<RHS>()), __true_type>::type
        test_bit_or_assignment_operator(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_bit_or_assignment_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(lvalue_auxiliary<LHS, RHS>::lhs or_eq lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type>::type
        test_bit_or_assignment_operator(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_bit_or_assignment_operator() cannot be called!");
            return {};
        }
        template <typename T, typename>
        constexpr inline __false_type test_bit_or_assignment_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_bit_or_assignment_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<noexcept(declval<LHS>() or_eq declval<RHS>()),
                __true_type, __false_type>::type
        is_bit_or_assignment_operator_nothrow(int) noexcept {
            static_assert(not is_type<RHS>::value,
                    "The function is_bit_or_assignment_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<
                noexcept(lvalue_auxiliary<LHS, RHS>::lhs or_eq lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type, __false_type>::type
        is_bit_or_assignment_operator_nothrow(long) noexcept {
            static_assert(not is_type<RHS>::value,
                    "The function is_bit_or_assignment_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(declval<LHS>() xor declval<RHS>()), __true_type>::type
        test_bit_xor_operator(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_bit_xor_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(lvalue_auxiliary<LHS, RHS>::lhs xor lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type>::type
        test_bit_xor_operator(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_bit_xor_operator() cannot be called!");
            return {};
        }
        template <typename T, typename>
        constexpr inline __false_type test_bit_xor_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_bit_xor_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<noexcept(declval<LHS>() xor declval<RHS>()),
                __true_type, __false_type>::type
        is_bit_xor_operator_nothrow(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_bit_xor_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<
                noexcept(lvalue_auxiliary<LHS, RHS>::lhs xor lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type, __false_type>::type
        is_bit_xor_operator_nothrow(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_bit_xor_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(declval<LHS>() xor_eq declval<RHS>()), __true_type>::type
        test_bit_xor_assignment_operator(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_bit_xor_assignment_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(lvalue_auxiliary<LHS, RHS>::lhs xor_eq lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type>::type
        test_bit_xor_assignment_operator(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_bit_xor_assignment_operator() cannot be called!");
            return {};
        }
        template <typename T, typename>
        constexpr inline __false_type test_bit_xor_assignment_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_bit_xor_assignment_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<noexcept(declval<LHS>() xor_eq declval<RHS>()),
                __true_type, __false_type>::type
        is_bit_xor_assignment_operator_nothrow(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_bit_xor_assignment_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<
                noexcept(lvalue_auxiliary<LHS, RHS>::lhs xor_eq lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type, __false_type>::type
        is_bit_xor_assignment_operator_nothrow(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_bit_xor_assignment_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename select_second_type<
                decltype(compl declval<T>()), __true_type>::type
        test_complement_operator(int) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_complement_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename select_second_type<
                decltype(compl lvalue_auxiliary<T, void *>::lhs), __true_type>::type
        test_complement_operator(long) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_complement_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline __false_type test_complement_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_complement_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename conditional<noexcept(compl declval<T>()),
                __true_type, __false_type>::type
        is_complement_operator_nothrow(int) noexcept {
            static_assert(not is_type<T>::value,
                    "The function is_complement_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename conditional<
                noexcept(compl lvalue_auxiliary<T, void *>::lhs),
                __true_type, __false_type>::type
        is_complement_operator_nothrow(long) noexcept {
            static_assert(not is_type<T>::value,
                    "The function is_complement_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename select_second_type<decltype(*declval<T>()), __true_type>::type
        test_dereference_operator(int) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_dereference_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename select_second_type<
                decltype(*lvalue_auxiliary<T, void *>::lhs), __true_type>::type
        test_dereference_operator(long) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_dereference_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline __false_type test_dereference_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_dereference_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename conditional<noexcept(*declval<T>()),
                __true_type, __false_type>::type
        is_dereference_operator_nothrow(int) noexcept {
            static_assert(not is_type<T>::value,
                    "The function is_dereference_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename conditional<
                noexcept(*lvalue_auxiliary<T, void *>::lhs),
                __true_type, __false_type>::type
        is_dereference_operator_nothrow(long) noexcept {
            static_assert(not is_type<T>::value,
                    "The function is_dereference_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(declval<LHS>() / declval<RHS>()), __true_type>::type
        test_divide_operator(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_divide_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(lvalue_auxiliary<LHS, RHS>::lhs / lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type>::type
        test_divide_operator(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_divide_operator() cannot be called!");
            return {};
        }
        template <typename T, typename>
        constexpr inline __false_type test_divide_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_divide_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<noexcept(declval<LHS>() / declval<RHS>()),
                __true_type, __false_type>::type
        is_divide_operator_nothrow(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_divide_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<
                noexcept(lvalue_auxiliary<LHS, RHS>::lhs / lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type, __false_type>::type
        is_divide_operator_nothrow(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_divide_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(declval<LHS>() /= declval<RHS>()), __true_type>::type
        test_divide_assignment_operator(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_divide_assignment_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(lvalue_auxiliary<LHS, RHS>::lhs /= lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type>::type
        test_divide_assignment_operator(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_divide_assignment_operator() cannot be called!");
            return {};
        }
        template <typename T, typename>
        constexpr inline __false_type test_divide_assignment_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_divide_assignment_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<noexcept(declval<LHS>() /= declval<RHS>()),
                __true_type, __false_type>::type
        is_divide_assignment_operator_nothrow(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_divide_assignment_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<
                noexcept(lvalue_auxiliary<LHS, RHS>::lhs /= lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type, __false_type>::type
        is_divide_assignment_operator_nothrow(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_divide_assignment_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(declval<LHS>() == declval<RHS>()), __true_type>::type
        test_equal_to_operator(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_equal_to_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(lvalue_auxiliary<LHS, RHS>::lhs == lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type>::type
        test_equal_to_operator(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_equal_to_operator() cannot be called!");
            return {};
        }
        template <typename T, typename>
        constexpr inline __false_type test_equal_to_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_equal_to_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<noexcept(declval<LHS>() == declval<RHS>()),
                __true_type, __false_type>::type
        is_equal_to_operator_nothrow(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_equal_to_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<
                noexcept(lvalue_auxiliary<LHS, RHS>::lhs == lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type, __false_type>::type
        is_equal_to_operator_nothrow(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_equal_to_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(declval<LHS>() > declval<RHS>()), __true_type>::type
        test_greater_operator(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_greater_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(lvalue_auxiliary<LHS, RHS>::lhs > lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type>::type
        test_greater_operator(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_greater_operator() cannot be called!");
            return {};
        }
        template <typename T, typename>
        constexpr inline __false_type test_greater_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_greater_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<noexcept(declval<LHS>() > declval<RHS>()),
                __true_type, __false_type>::type
        is_greater_operator_nothrow(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_greater_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<
                noexcept(lvalue_auxiliary<LHS, RHS>::lhs > lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type, __false_type>::type
        is_greater_operator_nothrow(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_greater_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(declval<LHS>() >= declval<RHS>()), __true_type>::type
        test_greater_equal_operator(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_greater_equal_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(lvalue_auxiliary<LHS, RHS>::lhs >= lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type>::type
        test_greater_equal_operator(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_greater_equal_operator() cannot be called!");
            return {};
        }
        template <typename T, typename>
        constexpr inline __false_type test_greater_equal_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_greater_equal_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<noexcept(declval<LHS>() >= declval<RHS>()),
                __true_type, __false_type>::type
        is_greater_equal_operator_nothrow(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_greater_equal_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<
                noexcept(lvalue_auxiliary<LHS, RHS>::lhs >= lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type, __false_type>::type
        is_greater_equal_operator_nothrow(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_greater_equal_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(declval<LHS>() << declval<RHS>()), __true_type>::type
        test_left_shift_operator(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_left_shift_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(lvalue_auxiliary<LHS, RHS>::lhs << lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type>::type
        test_left_shift_operator(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_left_shift_operator() cannot be called!");
            return {};
        }
        template <typename T, typename>
        constexpr inline __false_type test_left_shift_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_left_shift_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<noexcept(declval<LHS>() << declval<RHS>()),
                __true_type, __false_type>::type
        is_left_shift_operator_nothrow(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_left_shift_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<
                noexcept(lvalue_auxiliary<LHS, RHS>::lhs << lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type, __false_type>::type
        is_left_shift_operator_nothrow(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_left_shift_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(declval<LHS>() <<= declval<RHS>()), __true_type>::type
        test_left_shift_assignment_operator(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_left_shift_assignment_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(lvalue_auxiliary<LHS, RHS>::lhs <<= lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type>::type
        test_left_shift_assignment_operator(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_left_shift_assignment_operator() cannot be called!");
            return {};
        }
        template <typename T, typename>
        constexpr inline __false_type test_left_shift_assignment_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_left_shift_assignment_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<noexcept(declval<LHS>() <<= declval<RHS>()),
                __true_type, __false_type>::type
        is_left_shift_assignment_operator_nothrow(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_left_shift_assignment_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<
                noexcept(lvalue_auxiliary<LHS, RHS>::lhs <<= lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type, __false_type>::type
        is_left_shift_assignment_operator_nothrow(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_left_shift_assignment_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(declval<LHS>() < declval<RHS>()), __true_type>::type
        test_less_operator(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_less_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(lvalue_auxiliary<LHS, RHS>::lhs < lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type>::type
        test_less_operator(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_less_operator() cannot be called!");
        }
        template <typename T, typename>
        constexpr inline __false_type test_less_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_less_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<noexcept(declval<LHS>() < declval<RHS>()),
                __true_type, __false_type>::type
        is_less_operator_nothrow(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_less_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<
                noexcept(lvalue_auxiliary<LHS, RHS>::lhs < lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type, __false_type>::type
        is_less_operator_nothrow(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_less_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(declval<LHS>() <= declval<RHS>()), __true_type>::type
        test_less_equal_operator(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_less_equal_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(lvalue_auxiliary<LHS, RHS>::lhs <= lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type>::type
        test_less_equal_operator(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_less_equal_operator() cannot be called!");
            return {};
        }
        template <typename T, typename>
        constexpr inline __false_type test_less_equal_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_less_equal_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<noexcept(declval<LHS>() <= declval<RHS>()),
                __true_type, __false_type>::type
        is_less_equal_operator_nothrow(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_less_equal_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<
                noexcept(lvalue_auxiliary<LHS, RHS>::lhs <= lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type, __false_type>::type
        is_less_equal_operator_nothrow(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_less_equal_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(declval<LHS>() and declval<RHS>()), __true_type>::type
        test_logical_and_operator(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_logical_and_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(lvalue_auxiliary<LHS, RHS>::lhs and lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type>::type
        test_logical_and_operator(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_logical_and_operator() cannot be called!");
            return {};
        }
        template <typename T, typename>
        constexpr inline __false_type test_logical_and_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_logical_and_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<noexcept(declval<LHS>() and declval<RHS>()),
                __true_type, __false_type>::type
        is_logical_and_operator_nothrow(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_logical_and_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<
                noexcept(lvalue_auxiliary<LHS, RHS>::lhs and lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type, __false_type>::type
        is_logical_and_operator_nothrow(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_logical_and_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(declval<LHS>() or declval<RHS>()), __true_type>::type
        test_logical_or_operator(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_logical_or_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(lvalue_auxiliary<LHS, RHS>::lhs or lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type>::type
        test_logical_or_operator(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_logical_or_operator() cannot be called!");
            return {};
        }
        template <typename T, typename>
        constexpr inline __false_type test_logical_or_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_logical_or_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<noexcept(declval<LHS>() or declval<RHS>()),
                __true_type, __false_type>::type
        is_logical_or_operator_nothrow(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_logical_or_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<
                noexcept(lvalue_auxiliary<LHS, RHS>::lhs or lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type, __false_type>::type
        is_logical_or_operator_nothrow(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_logical_or_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename select_second_type<decltype(not declval<T>()), __true_type>::type
        test_logical_not_operator(int) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_logical_not_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename select_second_type<
                decltype(not lvalue_auxiliary<T, void *>::lhs), __true_type>::type
        test_logical_not_operator(long) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_logical_not_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline __false_type test_logical_not_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_logical_not_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename conditional<noexcept(not declval<T>()),
                __true_type, __false_type>::type
        is_logical_not_operator_nothrow(int) noexcept {
            static_assert(not is_type<T>::value,
                    "The function is_logical_not_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename conditional<
                noexcept(not lvalue_auxiliary<T, void *>::lhs),
                __true_type, __false_type>::type
        is_logical_not_operator_nothrow(long) noexcept {
            static_assert(not is_type<T>::value,
                    "The function is_logical_not_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(declval<LHS>() - declval<RHS>()), __true_type>::type
        test_minus_operator(int) noexcept {
            static_assert(not is_type<RHS>::value,
                    "The function test_minus_operator() cannot be called!");
            return {};
        };
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(lvalue_auxiliary<LHS, RHS>::lhs - lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type>::type
        test_minus_operator(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_minus_operator() cannot be called!");
            return {};
        }
        template <typename T, typename>
        constexpr inline __false_type test_minus_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_minus_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<noexcept(declval<LHS>() - declval<RHS>()),
                __true_type, __false_type>::type
        is_minus_operator_nothrow(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_minus_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<
                noexcept(lvalue_auxiliary<LHS, RHS>::lhs - lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type, __false_type>::type
        is_minus_operator_nothrow(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_minus_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(declval<LHS>() -= declval<RHS>()), __true_type>::type
        test_minus_assignment_operator(int) noexcept {
            static_assert(not is_type<RHS>::value,
                    "The function test_minus_assignment_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(lvalue_auxiliary<LHS, RHS>::lhs -= lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type>::type
        test_minus_assignment_operator(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_minus_assignment_operator() cannot be called!");
            return {};
        }
        template <typename T, typename>
        constexpr inline __false_type test_minus_assignment_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_minus_assignment_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<noexcept(declval<LHS>() -= declval<RHS>()),
                __true_type, __false_type>::type
        is_minus_assignment_operator_nothrow(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_minus_assignment_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<
                noexcept(lvalue_auxiliary<LHS, RHS>::lhs -= lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type, __false_type>::type
        is_minus_assignment_operator_nothrow(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_minus_assignment_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(declval<LHS>() % declval<RHS>()), __true_type>::type
        test_modulus_operator(int) noexcept {
            static_assert(not is_type<RHS>::value,
                    "The function test_modulus_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(lvalue_auxiliary<LHS, RHS>::lhs % lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type>::type
        test_modulus_operator(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_modulus_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline __false_type test_modulus_operator(...) noexcept {
            static_assert(not is_type<RHS>::value,
                    "The function test_modulus_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<noexcept(declval<LHS>() % declval<RHS>()),
                __true_type, __false_type>::type
        is_modulus_operator_nothrow(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_modulus_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<
                noexcept(lvalue_auxiliary<LHS, RHS>::lhs % lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type, __false_type>::type
        is_modulus_operator_nothrow(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_modulus_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(declval<LHS>() %= declval<RHS>()), __true_type>::type
        test_modulus_assignment_operator(int) noexcept {
            static_assert(not is_type<RHS>::value,
                    "The function test_modulus_assignment_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(lvalue_auxiliary<LHS, RHS>::lhs %= lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type>::type
        test_modulus_assignment_operator(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_modulus_assignment_operator() cannot be called!");
            return {};
        }
        template <typename T, typename>
        constexpr inline __false_type test_modulus_assignment_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_modulus_assignment_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<noexcept(declval<LHS>() %= declval<RHS>()),
                __true_type, __false_type>::type
        is_modulus_assignment_operator_nothrow(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_modulus_assignment_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<
                noexcept(lvalue_auxiliary<LHS, RHS>::lhs %= lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type, __false_type>::type
        is_modulus_assignment_operator_nothrow(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_modulus_assignment_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(declval<LHS>() * declval<RHS>()), __true_type>::type
        test_multiply_operator(int) noexcept {
            static_assert(not is_type<RHS>::value,
                    "The function test_multiply_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(lvalue_auxiliary<LHS, RHS>::lhs * lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type>::type
        test_multiply_operator(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_multiply_operator() cannot be called!");
            return {};
        }
        template <typename T, typename>
        constexpr inline __false_type test_multiply_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_multiply_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<noexcept(declval<LHS>() * declval<RHS>()),
                __true_type, __false_type>::type
        is_multiply_operator_nothrow(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_multiply_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<
                noexcept(lvalue_auxiliary<LHS, RHS>::lhs * lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type, __false_type>::type
        is_multiply_operator_nothrow(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_multiply_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(declval<LHS>() *= declval<RHS>()), __true_type>::type
        test_multiply_assignment_operator(int) noexcept {
            static_assert(not is_type<RHS>::value,
                    "The function test_multiply_assignment_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(lvalue_auxiliary<LHS, RHS>::lhs *= lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type>::type
        test_multiply_assignment_operator(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_multiply_assignment_operator() cannot be called!");
            return {};
        }
        template <typename T, typename>
        constexpr inline __false_type test_multiply_assignment_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_multiply_assignment_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<noexcept(declval<LHS>() *= declval<RHS>()),
                __true_type, __false_type>::type
        is_multiply_assignment_operator_nothrow(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_multiply_assignment_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<
                noexcept(lvalue_auxiliary<LHS, RHS>::lhs *= lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type, __false_type>::type
        is_multiply_assignment_operator_nothrow(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_multiply_assignment_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename select_second_type<
                decltype(T::operator new (0)), __true_type>::type
        test_new_operator(int) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_new_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename select_second_type<
                decltype(lvalue_auxiliary<T, void *>::lhs.operator new (0)), __true_type>::type
        test_new_operator(long) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_new_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline __false_type test_new_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_new_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename select_second_type<
                decltype(T::operator delete (nullptr)), __true_type>::type
        test_delete_operator(int) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_delete_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename select_second_type<
                decltype(lvalue_auxiliary<T, void *>::lhs.operator delete (nullptr)), __true_type>::type
        test_delete_operator(long) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_delete_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline __false_type test_delete_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_delete_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename select_second_type<
                decltype(T::operator new[] (0)), __true_type>::type
        test_new_array_operator(int) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_new_array_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename select_second_type<
                decltype(lvalue_auxiliary<T, void *>::lhs.operator new[] (0)), __true_type>::type
        test_new_array_operator(long) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_new_array_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline __false_type test_new_array_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_new_array_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename select_second_type<
                decltype(T::operator delete[] (nullptr)), __true_type>::type
        test_delete_array_operator(int) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_delete_array_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename select_second_type<
                decltype(lvalue_auxiliary<T, void *>::lhs.operator delete[] (nullptr)), __true_type>::type
        test_delete_array_operator(long) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_delete_array_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline __false_type test_delete_array_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_delete_array_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(declval<LHS>() not_eq declval<RHS>()), __true_type>::type
        test_not_equal_to_operator(int) noexcept {
            static_assert(not is_type<RHS>::value,
                    "The function test_not_equal_to_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(lvalue_auxiliary<LHS, RHS>::lhs not_eq lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type>::type
        test_not_equal_to_operator(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_not_equal_to_operator() cannot be called!");
            return {};
        }
        template <typename T, typename>
        constexpr inline __false_type test_not_equal_to_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_not_equal_to_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<noexcept(declval<LHS>() not_eq declval<RHS>()),
                __true_type, __false_type>::type
        is_not_equal_to_operator_nothrow(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_not_equal_to_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<
                noexcept(lvalue_auxiliary<LHS, RHS>::lhs not_eq lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type, __false_type>::type
        is_not_equal_to_operator_nothrow(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_not_equal_to_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(declval<LHS>() + declval<RHS>()), __true_type>::type
        test_plus_operator(int) noexcept {
            static_assert(not is_type<RHS>::value,
                    "The function test_plus_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(lvalue_auxiliary<LHS, RHS>::lhs + lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type>::type
        test_plus_operator(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_plus_operator() cannot be called!");
            return {};
        }
        template <typename T, typename>
        constexpr inline __false_type test_plus_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_plus_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<noexcept(declval<LHS>() + declval<RHS>()),
                __true_type, __false_type>::type
        is_plus_operator_nothrow(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_plus_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<
                noexcept(lvalue_auxiliary<LHS, RHS>::lhs + lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type, __false_type>::type
        is_plus_operator_nothrow(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_plus_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(declval<LHS>() += declval<RHS>()), __true_type>::type
        test_plus_assignment_operator(int) noexcept {
            static_assert(not is_type<RHS>::value,
                    "The function test_plus_assignment_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(lvalue_auxiliary<LHS, RHS>::lhs += lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type>::type
        test_plus_assignment_operator(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_plus_assignment_operator() cannot be called!");
            return {};
        }
        template <typename T, typename>
        constexpr inline __false_type test_plus_assignment_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_plus_assignment_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<noexcept(declval<LHS>() += declval<RHS>()),
                __true_type, __false_type>::type
        is_plus_assignment_operator_nothrow(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_plus_assignment_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<
                noexcept(lvalue_auxiliary<LHS, RHS>::lhs += lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type, __false_type>::type
        is_plus_assignment_operator_nothrow(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_plus_assignment_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename select_second_type<decltype(declval<T>()--), __true_type>::type
        test_post_decrement_operator(int) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_post_decrement_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename select_second_type<
                decltype(lvalue_auxiliary<T>::lhs--), __true_type>::type
        test_post_decrement_operator(long) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_post_decrement_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline __false_type test_post_decrement_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_post_decrement_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename conditional<noexcept(declval<T>()--),
                __true_type, __false_type>::type
        is_post_decrement_operator_nothrow(int) noexcept {
            static_assert(not is_type<T>::value,
                    "The function is_post_decrement_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename conditional<
                noexcept(lvalue_auxiliary<T, void *>::lhs--),
                __true_type, __false_type>::type
        is_post_decrement_operator_nothrow(long) noexcept {
            static_assert(not is_type<T>::value,
                    "The function is_post_decrement_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename select_second_type<decltype(declval<T>()++), __true_type>::type
        test_post_increment_operator(int) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_post_increment_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename select_second_type<
                decltype(lvalue_auxiliary<T>::lhs++), __true_type>::type
        test_post_increment_operator(long) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_post_increment_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline __false_type test_post_increment_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_post_increment_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename conditional<noexcept(declval<T>()++),
                __true_type, __false_type>::type
        is_post_increment_operator_nothrow(int) noexcept {
            static_assert(not is_type<T>::value,
                    "The function is_post_increment_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename conditional<
                noexcept(lvalue_auxiliary<T, void *>::lhs++),
                __true_type, __false_type>::type
        is_post_increment_operator_nothrow(long) noexcept {
            static_assert(not is_type<T>::value,
                    "The function is_post_increment_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename select_second_type<decltype(++declval<T>()), __true_type>::type
        test_pre_increment_operator(int) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_pre_increment_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename select_second_type<
                decltype(++lvalue_auxiliary<T>::lhs), __true_type>::type
        test_pre_increment_operator(long) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_post_increment_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline __false_type test_pre_increment_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_pre_increment_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename conditional<noexcept(++declval<T>()),
                __true_type, __false_type>::type
        is_pre_increment_operator_nothrow(int) noexcept {
            static_assert(not is_type<T>::value,
                    "The function is_pre_increment_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename conditional<
                noexcept(++lvalue_auxiliary<T, void *>::lhs),
                __true_type, __false_type>::type
        is_pre_increment_operator_nothrow(long) noexcept {
            static_assert(not is_type<T>::value,
                    "The function is_pre_increment_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename select_second_type<
                decltype(--declval<T>()), __true_type>::type
        test_pre_decrement_operator(int) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_pre_decrement_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename select_second_type<
                decltype(--lvalue_auxiliary<T>::lhs), __true_type>::type
        test_pre_decrement_operator(long) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_pre_decrement_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline __false_type test_pre_decrement_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_pre_decrement_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename conditional<noexcept(--declval<T>()),
                __true_type, __false_type>::type
        is_pre_decrement_operator_nothrow(int) noexcept {
            static_assert(not is_type<T>::value,
                    "The function is_pre_decrement_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename conditional<
                noexcept(--lvalue_auxiliary<T, void *>::lhs),
                __true_type, __false_type>::type
        is_pre_decrement_operator_nothrow(long) noexcept {
            static_assert(not is_type<T>::value,
                    "The function is_pre_decrement_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(declval<LHS>() >> declval<RHS>()), __true_type>::type
        test_right_shift_operator(int) noexcept {
            static_assert(not is_type<RHS>::value,
                    "The function test_right_shift_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(lvalue_auxiliary<LHS, RHS>::lhs >> lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type>::type
        test_right_shift_operator(long) noexcept {
            static_assert(not is_type<LHS>::value,
                          "The function test_right_shift_operator() cannot be called!");
            return {};
        }
        template <typename T, typename>
        constexpr inline __false_type test_right_shift_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_right_shift_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<noexcept(declval<LHS>() >> declval<RHS>()),
                __true_type, __false_type>::type
        is_right_shift_operator_nothrow(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_right_shift_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<
                noexcept(lvalue_auxiliary<LHS, RHS>::lhs >> lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type, __false_type>::type
        is_right_shift_operator_nothrow(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_right_shift_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(declval<LHS>() >>= declval<RHS>()), __true_type>::type
        test_right_shift_assignment_operator(int) noexcept {
            static_assert(not is_type<RHS>::value,
                    "The function test_right_shift_assignment_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename select_second_type<
                decltype(lvalue_auxiliary<LHS, RHS>::lhs >>= lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type>::type
        test_right_shift_assignment_operator(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function test_right_shift_assignment_operator() cannot be called!");
            return {};
        }
        template <typename T, typename>
        constexpr inline __false_type test_right_shift_assignment_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_right_shift_assignment_operator() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<noexcept(declval<LHS>() >>= declval<RHS>()),
                __true_type, __false_type>::type
        is_right_shift_assignment_operator_nothrow(int) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_right_shift_assignment_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename LHS, typename RHS>
        constexpr inline typename conditional<
                noexcept(lvalue_auxiliary<LHS, RHS>::lhs >>= lvalue_auxiliary<LHS, RHS>::rhs),
                __true_type, __false_type>::type
        is_right_shift_assignment_operator_nothrow(long) noexcept {
            static_assert(not is_type<LHS>::value,
                    "The function is_right_shift_assignment_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename select_second_type<decltype(-declval<T>()), __true_type>::type
        test_unary_minus_operator(int) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_unary_minus_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename select_second_type<
                decltype(-lvalue_auxiliary<T>::lhs), __true_type>::type
        test_unary_minus_operator(long) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_unary_minus_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline __false_type test_unary_minus_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_unary_minus_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename conditional<noexcept(-declval<T>()),
                __true_type, __false_type>::type
        is_unary_minus_operator_nothrow(int) noexcept {
            static_assert(not is_type<T>::value,
                    "The function is_unary_minus_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename conditional<
                noexcept(-lvalue_auxiliary<T, void *>::lhs),
                __true_type, __false_type>::type
        is_unary_minus_operator_nothrow(long) noexcept {
            static_assert(not is_type<T>::value,
                    "The function is_unary_minus_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename select_second_type<decltype(+declval<T>()), __true_type>::type
        test_unary_plus_operator(int) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_unary_plus_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename select_second_type<
                decltype(+lvalue_auxiliary<T>::lhs), __true_type>::type
        test_unary_plus_operator(long) noexcept {
            static_assert(not is_type<T>::value,
                          "The function test_unary_plus_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline __false_type test_unary_plus_operator(...) noexcept {
            static_assert(not is_type<T>::value,
                    "The function test_unary_plus_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename conditional<noexcept(+declval<T>()),
                __true_type, __false_type>::type
        is_unary_plus_operator_nothrow(int) noexcept {
            static_assert(not is_type<T>::value,
                    "The function is_unary_plus_operator_nothrow() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename conditional<
                noexcept(+lvalue_auxiliary<T, void *>::lhs),
                __true_type, __false_type>::type
        is_unary_plus_operator_nothrow(long) noexcept {
            static_assert(not is_type<T>::value,
                    "The function is_unary_plus_operator_nothrow() cannot be called!");
            return {};
        }
    }
    template <typename T>
    struct has_virtual_destructor {
        using value_type = bool;
        using result = typename conditional<__has_virtual_destructor(T), __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_virtual_destructor<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_virtual_destructor<T>::value;
        }
    };
    template <typename T>
    struct has_unique_object_representations {
        using value_type = bool;
        using result = typename conditional<__has_unique_object_representations(
                        typename remove_cv<typename remove_all_extents<T>::result>::result),
                __true_type, __false_type>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_unique_object_representations<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_unique_object_representations<T>::value;
        }
    };
    template <typename LHS, typename RHS = LHS>
    struct has_bit_and_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_bit_and_operator<LHS, RHS>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_bit_and_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_bit_and_operator<LHS, RHS>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename LHS, typename RHS = LHS,
                bool HasBitAndOperator = has_bit_and_operator<LHS, RHS>::value>
        struct has_nothrow_bit_and_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_bit_and_operator_auxiliary<
                        LHS, RHS, HasBitAndOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_bit_and_operator_auxiliary<
                        LHS, RHS, HasBitAndOperator>::value;
            }
        };
        template <typename LHS, typename RHS>
        struct has_nothrow_bit_and_operator_auxiliary<LHS, RHS, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_bit_and_operator_nothrow<LHS, RHS>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_bit_and_operator_auxiliary<LHS, RHS, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_bit_and_operator_auxiliary<LHS, RHS, true>::value;
            }
        };
    }
    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_bit_and_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_bit_and_operator_auxiliary<LHS, RHS>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_bit_and_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_bit_and_operator<LHS, RHS>::value;
        }
    };
    template <typename LHS, typename RHS = LHS>
    struct has_bit_and_assignment_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_bit_and_assignment_operator<LHS, RHS>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_bit_and_assignment_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_bit_and_assignment_operator<LHS, RHS>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename LHS, typename RHS = LHS,
                bool HasBitAndAssignmentOperator = has_bit_and_assignment_operator<LHS, RHS>::value>
        struct has_nothrow_bit_and_assignment_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_bit_and_assignment_operator_auxiliary<
                        LHS, RHS, HasBitAndAssignmentOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_bit_and_assignment_operator_auxiliary<
                        LHS, RHS, HasBitAndAssignmentOperator>::value;
            }
        };
        template <typename LHS, typename RHS>
        struct has_nothrow_bit_and_assignment_operator_auxiliary<LHS, RHS, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_bit_and_assignment_operator_nothrow<LHS, RHS>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_bit_and_assignment_operator_auxiliary<LHS, RHS, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_bit_and_assignment_operator_auxiliary<LHS, RHS, true>::value;
            }
        };
    }
    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_bit_and_assignment_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_bit_and_assignment_operator_auxiliary<
                LHS, RHS>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_bit_and_assignment_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_bit_and_assignment_operator<LHS, RHS>::value;
        }
    };
    template <typename LHS, typename RHS = LHS>
    struct has_bit_or_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_bit_or_operator<LHS, RHS>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_bit_or_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_bit_or_operator<LHS, RHS>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename LHS, typename RHS = LHS,
                bool HasBitOrOperator = has_bit_or_operator<LHS, RHS>::value>
        struct has_nothrow_bit_or_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_bit_or_operator_auxiliary<LHS, RHS, HasBitOrOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_bit_or_operator_auxiliary<LHS, RHS, HasBitOrOperator>::value;
            }
        };
        template <typename LHS, typename RHS>
        struct has_nothrow_bit_or_operator_auxiliary<LHS, RHS, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_bit_or_operator_nothrow<LHS, RHS>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_bit_or_operator_auxiliary<LHS, RHS, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_bit_or_operator_auxiliary<LHS, RHS, true>::value;
            }
        };
    }
    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_bit_or_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_bit_or_operator_auxiliary<LHS, RHS>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_bit_or_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_bit_or_operator<LHS, RHS>::value;
        }
    };
    template <typename LHS, typename RHS = LHS>
    struct has_bit_or_assignment_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_bit_or_assignment_operator<LHS, RHS>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_bit_or_assignment_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_bit_or_assignment_operator<LHS, RHS>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename LHS, typename RHS = LHS,
                bool HasBitOrAssignmentOperator = has_bit_or_assignment_operator<LHS, RHS>::value>
        struct has_nothrow_bit_or_assignment_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_bit_or_assignment_operator_auxiliary<
                        LHS, RHS, HasBitOrAssignmentOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_bit_or_assignment_operator_auxiliary<
                        LHS, RHS, HasBitOrAssignmentOperator>::value;
            }
        };
        template <typename LHS, typename RHS>
        struct has_nothrow_bit_or_assignment_operator_auxiliary<LHS, RHS, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_bit_or_assignment_operator_nothrow<LHS, RHS>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_bit_or_assignment_operator_auxiliary<LHS, RHS, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_bit_or_assignment_operator_auxiliary<LHS, RHS, true>::value;
            }
        };
    }
    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_bit_or_assignment_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_bit_or_assignment_operator_auxiliary<
                LHS, RHS>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_bit_or_assignment_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_bit_or_assignment_operator<LHS, RHS>::value;
        }
    };
    template <typename LHS, typename RHS = LHS>
    struct has_bit_xor_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_bit_xor_operator<LHS, RHS>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_bit_xor_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_bit_xor_operator<LHS, RHS>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename LHS, typename RHS = LHS,
                bool HasBitXorOperator = has_bit_xor_operator<LHS, RHS>::value>
        struct has_nothrow_bit_xor_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_bit_xor_operator_auxiliary<LHS, RHS, HasBitXorOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_bit_xor_operator_auxiliary<LHS, RHS, HasBitXorOperator>::value;
            }
        };
        template <typename LHS, typename RHS>
        struct has_nothrow_bit_xor_operator_auxiliary<LHS, RHS, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_bit_xor_operator_nothrow<LHS, RHS>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_bit_xor_operator_auxiliary<LHS, RHS, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_bit_xor_operator_auxiliary<LHS, RHS, true>::value;
            }
        };
    }
    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_bit_xor_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_bit_xor_operator_auxiliary<
                LHS, RHS, true>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_bit_xor_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_bit_xor_operator<LHS, RHS>::value;
        }
    };
    template <typename LHS, typename RHS = LHS>
    struct has_bit_xor_assignment_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_bit_xor_assignment_operator<LHS, RHS>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_bit_xor_assignment_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_bit_xor_assignment_operator<LHS, RHS>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename LHS, typename RHS = LHS,
                bool HasBitXorAssignmentOperator = has_bit_xor_assignment_operator<LHS, RHS>::value>
        struct has_nothrow_bit_xor_assignment_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_bit_xor_assignment_operator_auxiliary<
                        LHS, RHS, HasBitXorAssignmentOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_bit_xor_assignment_operator_auxiliary<
                        LHS, RHS, HasBitXorAssignmentOperator>::value;
            }
        };
        template <typename LHS, typename RHS>
        struct has_nothrow_bit_xor_assignment_operator_auxiliary<LHS, RHS, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_bit_xor_assignment_operator_nothrow<LHS, RHS>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_bit_xor_assignment_operator_auxiliary<LHS, RHS, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_bit_xor_assignment_operator_auxiliary<LHS, RHS, true>::value;
            }
        };
    }
    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_bit_xor_assignment_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_bit_xor_assignment_operator_auxiliary<
                LHS, RHS>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_bit_xor_assignment_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_bit_xor_assignment_operator<LHS, RHS>::value;
        }
    };
    template <typename T>
    struct has_complement_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_complement_operator<T>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_complement_operator<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_complement_operator<T>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename T, bool HasComplementOperator = has_complement_operator<T>::value>
        struct has_nothrow_complement_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_complement_operator_auxiliary<T, HasComplementOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_complement_operator_auxiliary<T, HasComplementOperator>::value;
            }
        };
        template <typename T>
        struct has_nothrow_complement_operator_auxiliary<T, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_complement_operator_nothrow<T>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_complement_operator_auxiliary<T, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_complement_operator_auxiliary<T, true>::value;
            }
        };
    }
    template <typename T>
    struct has_nothrow_complement_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_complement_operator_auxiliary<T>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_complement_operator<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_complement_operator<T>::value;
        }
    };
    template <typename T>
    struct has_dereference_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_dereference_operator<T>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_dereference_operator<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_dereference_operator<T>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename T, bool HasDereferenceOperator = has_dereference_operator<T>::value>
        struct has_nothrow_dereference_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_dereference_operator_auxiliary<T, HasDereferenceOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_dereference_operator_auxiliary<T, HasDereferenceOperator>::value;
            }
        };
        template <typename T>
        struct has_nothrow_dereference_operator_auxiliary<T, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_dereference_operator_nothrow<T>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_dereference_operator_auxiliary<T, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_dereference_operator_auxiliary<T, true>::value;
            }
        };
    }
    template <typename T>
    struct has_nothrow_dereference_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_dereference_operator_auxiliary<T>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_dereference_operator<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_dereference_operator<T>::value;
        }
    };
    template <typename LHS, typename RHS = LHS>
    struct has_divide_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_divide_operator<LHS, RHS>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_divide_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_divide_operator<LHS, RHS>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename LHS, typename RHS = LHS,
                bool HasDivideOperator = has_divide_operator<LHS, RHS>::value>
        struct has_nothrow_divide_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_divide_operator_auxiliary<LHS, RHS, HasDivideOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_divide_operator_auxiliary<LHS, RHS, HasDivideOperator>::value;
            }
        };
        template <typename LHS, typename RHS>
        struct has_nothrow_divide_operator_auxiliary<LHS, RHS, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_divide_operator_nothrow<LHS, RHS>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_divide_operator_auxiliary<LHS, RHS, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_divide_operator_auxiliary<LHS, RHS, true>::value;
            }
        };
    }
    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_divide_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_divide_operator_auxiliary<LHS, RHS>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_divide_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_divide_operator<LHS, RHS>::value;
        }
    };
    template <typename LHS, typename RHS = LHS>
    struct has_divide_assignment_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_divide_assignment_operator<LHS, RHS>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_divide_assignment_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_divide_assignment_operator<LHS, RHS>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename LHS, typename RHS = LHS,
                bool HasDivideAssignmentOperator = has_divide_assignment_operator<LHS, RHS>::value>
        struct has_nothrow_divide_assignment_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_divide_assignment_operator_auxiliary<
                        LHS, RHS, HasDivideAssignmentOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_divide_assignment_operator_auxiliary<
                        LHS, RHS, HasDivideAssignmentOperator>::value;
            }
        };
        template <typename LHS, typename RHS>
        struct has_nothrow_divide_assignment_operator_auxiliary<LHS, RHS, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_divide_assignment_operator_nothrow<LHS, RHS>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_divide_assignment_operator_auxiliary<LHS, RHS, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_divide_assignment_operator_auxiliary<LHS, RHS, true>::value;
            }
        };
    }
    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_divide_assignment_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_divide_assignment_operator_auxiliary<
                LHS, RHS>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_divide_assignment_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_divide_assignment_operator<LHS, RHS>::value;
        }
    };
    template <typename LHS, typename RHS = LHS>
    struct has_equal_to_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_equal_to_operator<LHS, RHS>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_equal_to_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_equal_to_operator<LHS, RHS>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename LHS, typename RHS = LHS,
                bool HasEqualToOperator = has_equal_to_operator<LHS, RHS>::value>
        struct has_nothrow_equal_to_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_equal_to_operator_auxiliary<
                        LHS, RHS, HasEqualToOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_equal_to_operator_auxiliary<
                        LHS, RHS, HasEqualToOperator>::value;
            }
        };
        template <typename LHS, typename RHS>
        struct has_nothrow_equal_to_operator_auxiliary<LHS, RHS, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_equal_to_operator_nothrow<LHS, RHS>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_equal_to_operator_auxiliary<LHS, RHS, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_equal_to_operator_auxiliary<LHS, RHS, true>::value;
            }
        };
    }
    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_equal_to_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_equal_to_operator_auxiliary<LHS, RHS>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_equal_to_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_equal_to_operator<LHS, RHS>::value;
        }
    };
    template <typename LHS, typename RHS = LHS>
    struct has_greater_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_greater_operator<LHS, RHS>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_greater_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_greater_operator<LHS, RHS>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename LHS, typename RHS = LHS,
                bool HasGreaterOperator = has_greater_operator<LHS, RHS>::value>
        struct has_nothrow_greater_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_greater_operator_auxiliary<
                        LHS, RHS, HasGreaterOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_greater_operator_auxiliary<
                        LHS, RHS, HasGreaterOperator>::value;
            }
        };
        template <typename LHS, typename RHS>
        struct has_nothrow_greater_operator_auxiliary<LHS, RHS, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_greater_operator_nothrow<LHS, RHS>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_greater_operator_auxiliary<LHS, RHS, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_greater_operator_auxiliary<LHS, RHS, true>::value;
            }
        };
    }
    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_greater_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_greater_operator_auxiliary<LHS, RHS>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_greater_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_greater_operator<LHS, RHS>::value;
        }
    };
    template <typename LHS, typename RHS = LHS>
    struct has_greater_equal_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_greater_equal_operator<LHS, RHS>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_greater_equal_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_greater_equal_operator<LHS, RHS>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename LHS, typename RHS = LHS,
                bool HasGreaterEqualOperator = has_greater_equal_operator<LHS, RHS>::value>
        struct has_nothrow_greater_equal_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_greater_equal_operator_auxiliary<
                        LHS, RHS, HasGreaterEqualOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_greater_equal_operator_auxiliary<
                        LHS, RHS, HasGreaterEqualOperator>::value;
            }
        };
        template <typename LHS, typename RHS>
        struct has_nothrow_greater_equal_operator_auxiliary<LHS, RHS, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_greater_equal_operator_nothrow<LHS, RHS>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_greater_equal_operator_auxiliary<LHS, RHS, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_greater_equal_operator_auxiliary<LHS, RHS, true>::value;
            }
        };
    }
    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_greater_equal_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_greater_operator_auxiliary<LHS, RHS>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_greater_equal_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_greater_equal_operator<LHS, RHS>::value;
        }
    };
    template <typename LHS, typename RHS = LHS>
    struct has_left_shift_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_left_shift_operator<LHS, RHS>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_left_shift_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_left_shift_operator<LHS, RHS>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename LHS, typename RHS = LHS,
                bool HasLeftShiftOperator = has_left_shift_operator<LHS, RHS>::value>
        struct has_nothrow_left_shift_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_left_shift_operator_auxiliary<
                        LHS, RHS, HasLeftShiftOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_left_shift_operator_auxiliary<
                        LHS, RHS, HasLeftShiftOperator>::value;
            }
        };
        template <typename LHS, typename RHS>
        struct has_nothrow_left_shift_operator_auxiliary<LHS, RHS, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_left_shift_operator_nothrow<LHS, RHS>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_left_shift_operator_auxiliary<LHS, RHS, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_left_shift_operator_auxiliary<LHS, RHS, true>::value;
            }
        };
    }
    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_left_shift_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_left_shift_operator_auxiliary<LHS, RHS>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_left_shift_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_left_shift_operator<LHS, RHS>::value;
        }
    };
    template <typename LHS, typename RHS = LHS>
    struct has_left_shift_assignment_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_left_shift_assignment_operator<LHS, RHS>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_left_shift_assignment_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_left_shift_assignment_operator<LHS, RHS>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename LHS, typename RHS,
                bool HasLeftShiftAssignmentOperator = has_left_shift_assignment_operator<LHS, RHS>::value>
        struct has_nothrow_left_shift_assignment_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_left_shift_assignment_operator_auxiliary<
                        LHS, RHS, HasLeftShiftAssignmentOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_left_shift_assignment_operator_auxiliary<
                        LHS, RHS, HasLeftShiftAssignmentOperator>::value;
            }
        };
        template <typename LHS, typename RHS>
        struct has_nothrow_left_shift_assignment_operator_auxiliary<LHS, RHS, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_left_shift_assignment_operator_nothrow<LHS, RHS>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_left_shift_assignment_operator_auxiliary<LHS, RHS, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_left_shift_assignment_operator_auxiliary<LHS, RHS, true>::value;
            }
        };
    }
    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_left_shift_assignment_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_left_shift_assignment_operator_auxiliary<
                LHS, RHS, true>::value;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_left_shift_assignment_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_left_shift_assignment_operator<LHS, RHS>::value;
        }
    };
    template <typename LHS, typename RHS = LHS>
    struct has_less_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_less_operator<LHS, RHS>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_less_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_less_operator<LHS, RHS>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename LHS, typename RHS = LHS,
                bool HasLessOperator = has_less_operator<LHS, RHS>::value>
        struct has_nothrow_less_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_less_operator_auxiliary<LHS, RHS, HasLessOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_less_operator_auxiliary<LHS, RHS, HasLessOperator>::value;
            }
        };
        template <typename LHS, typename RHS>
        struct has_nothrow_less_operator_auxiliary<LHS, RHS, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_less_operator_nothrow<LHS, RHS>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_less_operator_auxiliary<LHS, RHS, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_less_operator_auxiliary<LHS, RHS, true>::value;
            }
        };
    }
    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_less_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_less_operator_auxiliary<LHS, RHS>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_less_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_less_operator<LHS, RHS>::value;
        }
    };
    template <typename LHS, typename RHS = LHS>
    struct has_logical_and_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_logical_and_operator<LHS, RHS>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_logical_and_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_logical_and_operator<LHS, RHS>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename LHS, typename RHS = LHS,
                bool HasLogicalAndOperator = has_logical_and_operator<LHS, RHS>::value>
        struct has_nothrow_logical_and_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_logical_and_operator_auxiliary<
                        LHS, RHS, HasLogicalAndOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_logical_and_operator_auxiliary<
                        LHS, RHS, HasLogicalAndOperator>::value;
            }
        };
        template <typename LHS, typename RHS>
        struct has_nothrow_logical_and_operator_auxiliary<LHS, RHS, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_logical_and_operator_nothrow<LHS, RHS>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_logical_and_operator_auxiliary<LHS, RHS, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_logical_and_operator_auxiliary<LHS, RHS, true>::value;
            }
        };
    }
    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_logical_and_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_logical_and_operator_auxiliary<LHS, RHS>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_logical_and_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_logical_and_operator<LHS, RHS>::value;
        }
    };
    template <typename T>
    struct has_logical_not_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_logical_not_operator<T>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_logical_not_operator<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_logical_not_operator<T>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename T, bool HasLogicalNotOperator = has_logical_not_operator<T>::value>
        struct has_nothrow_logical_not_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_logical_not_operator_auxiliary<T, HasLogicalNotOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_logical_not_operator_auxiliary<T, HasLogicalNotOperator>::value;
            }
        };
        template <typename T>
        struct has_nothrow_logical_not_operator_auxiliary<T, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_logical_not_operator_nothrow<T>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_logical_not_operator_auxiliary<T, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_logical_not_operator_auxiliary<T, true>::value;
            }
        };
    }
    template <typename T>
    struct has_nothrow_logical_not_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_logical_not_operator_auxiliary<T>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_logical_not_operator<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_logical_not_operator<T>::value;
        }
    };
    template <typename LHS, typename RHS = LHS>
    struct has_logical_or_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_logical_or_operator<LHS, RHS>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_logical_or_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_logical_or_operator<LHS, RHS>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename LHS, typename RHS = LHS,
                bool HasLogicalOrOperator = has_logical_or_operator<LHS, RHS>::value>
        struct has_nothrow_logical_or_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_logical_or_operator_auxiliary<LHS, RHS, HasLogicalOrOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_logical_or_operator_auxiliary<LHS, RHS, HasLogicalOrOperator>::value;
            }
        };
        template <typename LHS, typename RHS>
        struct has_nothrow_logical_or_operator_auxiliary<LHS, RHS, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_logical_or_operator_nothrow<LHS, RHS>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_logical_or_operator_auxiliary<LHS, RHS, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_logical_or_operator_auxiliary<LHS, RHS, true>::value;
            }
        };
    }
    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_logical_or_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_logical_or_operator_auxiliary<LHS, RHS>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_logical_or_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_logical_or_operator<LHS, RHS>::value;
        }
    };
    template <typename LHS, typename RHS = LHS>
    struct has_minus_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_minus_operator<LHS, RHS>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_minus_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_minus_operator<LHS, RHS>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename LHS, typename RHS = LHS,
                bool HasMinusOperator = has_minus_operator<LHS, RHS>::value>
        struct has_nothrow_minus_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_minus_operator_auxiliary<LHS, RHS, HasMinusOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_minus_operator_auxiliary<LHS, RHS, HasMinusOperator>::value;
            }
        };
        template <typename LHS, typename RHS>
        struct has_nothrow_minus_operator_auxiliary<LHS, RHS, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_minus_operator_nothrow<LHS, RHS>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_minus_operator_auxiliary<LHS, RHS, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_minus_operator_auxiliary<LHS, RHS, true>::value;
            }
        };
    }
    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_minus_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_minus_operator_auxiliary<LHS, RHS>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_minus_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_minus_operator<LHS, RHS>::value;
        }
    };
    template <typename LHS, typename RHS = LHS>
    struct has_minus_assignment_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_minus_assignment_operator<LHS, RHS>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_minus_assignment_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_minus_assignment_operator<LHS, RHS>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename LHS, typename RHS = LHS,
                bool HasMinusAssignmentOperator = has_minus_assignment_operator<LHS, RHS>::value>
        struct has_nothrow_minus_assignment_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_minus_assignment_operator_auxiliary<
                        LHS, RHS, HasMinusAssignmentOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_minus_assignment_operator_auxiliary<
                        LHS, RHS, HasMinusAssignmentOperator>::value;
            }
        };
        template <typename LHS, typename RHS>
        struct has_nothrow_minus_assignment_operator_auxiliary<LHS, RHS, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_minus_assignment_operator_nothrow<LHS, RHS>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_minus_assignment_operator_auxiliary<LHS, RHS, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_minus_assignment_operator_auxiliary<LHS, RHS, true>::value;
            }
        };
    }
    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_minus_assignment_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_minus_assignment_operator_auxiliary<
                LHS, RHS>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_minus_assignment_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_minus_assignment_operator<LHS, RHS>::value;
        }
    };
    template <typename LHS, typename RHS = LHS>
    struct has_modulus_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_modulus_operator<LHS, RHS>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_modulus_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_modulus_operator<LHS, RHS>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename LHS, typename RHS = LHS,
                bool HasModulusOperator = has_modulus_operator<LHS, RHS>::value>
        struct has_nothrow_modulus_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_modulus_operator_auxiliary<LHS, RHS, HasModulusOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_modulus_operator_auxiliary<LHS, RHS, HasModulusOperator>::value;
            }
        };
        template <typename LHS, typename RHS>
        struct has_nothrow_modulus_operator_auxiliary<LHS, RHS, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_modulus_operator_nothrow<LHS, RHS>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_modulus_operator_auxiliary<LHS, RHS, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_modulus_operator_auxiliary<LHS, RHS, true>::value;
            }
        };
    }
    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_modulus_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_modulus_operator_auxiliary<LHS, RHS>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_modulus_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_modulus_operator<LHS, RHS>::value;
        }
    };
    template <typename LHS, typename RHS = LHS>
    struct has_modulus_assignment_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_modulus_assignment_operator<LHS, RHS>(0));
        constexpr static inline auto value{static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_modulus_assignment_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_modulus_assignment_operator<LHS, RHS>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename LHS, typename RHS = LHS,
                bool HasModulusAssignmentOperator = has_modulus_assignment_operator<LHS, RHS>::value>
        struct has_nothrow_modulus_assignment_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_modulus_assignment_operator_auxiliary<
                        LHS, RHS, HasModulusAssignmentOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_modulus_assignment_operator_auxiliary<
                        LHS, RHS, HasModulusAssignmentOperator>::value;
            }
        };
        template <typename LHS, typename RHS>
        struct has_nothrow_modulus_assignment_operator_auxiliary<LHS, RHS, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_modulus_assignment_operator_nothrow<LHS, RHS>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_modulus_assignment_operator_auxiliary<LHS, RHS, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_modulus_assignment_operator_auxiliary<LHS, RHS, true>::value;
            }
        };
    }
    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_modulus_assignment_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_modulus_assignment_operator_auxiliary<
                LHS, RHS>::result;
        constexpr static inline auto value{static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_modulus_assignment_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_modulus_assignment_operator<LHS, RHS>::value;
        }
    };
    template <typename LHS, typename RHS = LHS>
    struct has_multiply_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_multiply_operator<LHS, RHS>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_multiply_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_multiply_operator<LHS, RHS>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename LHS, typename RHS = LHS,
                bool HasMultiplyOperator = has_multiply_operator<LHS, RHS>::value>
        struct has_nothrow_multiply_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_multiply_operator_auxiliary<LHS, RHS, HasMultiplyOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_multiply_operator_auxiliary<LHS, RHS, HasMultiplyOperator>::value;
            }
        };
        template <typename LHS, typename RHS>
        struct has_nothrow_multiply_operator_auxiliary<LHS, RHS, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_multiply_operator_nothrow<LHS, RHS>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_multiply_operator_auxiliary<LHS, RHS, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_multiply_operator_auxiliary<LHS, RHS, true>::value;
            }
        };
    }
    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_multiply_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_multiply_operator_auxiliary<LHS, RHS>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_multiply_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_multiply_operator<LHS, RHS>::value;
        }
    };
    template <typename LHS, typename RHS = LHS>
    struct has_multiply_assignment_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_multiply_assignment_operator<LHS, RHS>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_multiply_assignment_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_multiply_assignment_operator<LHS, RHS>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename LHS, typename RHS = LHS,
                bool HasMultiplyAssignmentOperator = has_multiply_assignment_operator<LHS, RHS>::value>
        struct has_nothrow_multiply_assignment_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_multiply_assignment_operator_auxiliary<
                        LHS, RHS, HasMultiplyAssignmentOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_multiply_assignment_operator_auxiliary<
                        LHS, RHS, HasMultiplyAssignmentOperator>::value;
            }
        };
        template <typename LHS, typename RHS>
        struct has_nothrow_multiply_assignment_operator_auxiliary<LHS, RHS, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_multiply_assignment_operator_nothrow<LHS, RHS>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_multiply_assignment_operator_auxiliary<LHS, RHS, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_multiply_assignment_operator_auxiliary<LHS, RHS, true>::value;
            }
        };
    }
    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_multiply_assignment_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_multiply_assignment_operator_auxiliary<
                LHS, RHS>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_multiply_assignment_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_multiply_assignment_operator<LHS, RHS>::value;
        }
    };
    template <typename T>
    struct has_new_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_new_operator<T>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_new_operator<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_new_operator<T>::value;
        }
    };
    template <typename T>
    struct has_delete_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_delete_operator<T>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_delete_operator<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_delete_operator<T>::value;
        }
    };
    template <typename T>
    struct has_new_array_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_new_array_operator<T>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_new_array_operator<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_new_array_operator<T>::value;
        }
    };
    template <typename T>
    struct has_delete_array_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_delete_array_operator<T>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_delete_array_operator<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_delete_array_operator<T>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename T>
        constexpr inline typename conditional<
                noexcept(T::operator new (0)), __true_type, __false_type>::type
        test_nothrow_new_operator(int) noexcept {
            static_assert(is_type<T>::value,
                    "The function test_nothrow_new_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename conditional<
                noexcept(lvalue_auxiliary<T, void *>::lhs.operator new (0)),
                __true_type, __false_type>::type
        test_nothrow_new_operator(long) noexcept {
            static_assert(is_type<T>::value,
                    "The function test_nothrow_new_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename conditional<
                noexcept(T::operator new[] (0)), __true_type, __false_type>::type
        test_nothrow_new_array_operator(int) noexcept {
            static_assert(is_type<T>::value,
                    "The function test_nothrow_new_array_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename conditional<
                noexcept(lvalue_auxiliary<T, void *>::lhs.operator new[] (0)),
                __true_type, __false_type>::type
        test_nothrow_new_array_operator(long) noexcept {
            static_assert(is_type<T>::value,
                    "The function test_nothrow_new_array_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename conditional<
                noexcept(T::operator delete (nullptr)), __true_type, __false_type>::type
        test_nothrow_delete_operator(int) noexcept {
            static_assert(is_type<T>::value,
                          "The function test_nothrow_delete_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename conditional<
                noexcept(lvalue_auxiliary<T, void>::lhs.operator delete (nullptr)),
                __true_type, __false_type>::type
        test_nothrow_delete_operator(long) noexcept {
            static_assert(is_type<T>::value,
                          "The function test_nothrow_delete_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename conditional<
                noexcept(T::operator delete[] (nullptr)), __true_type, __false_type>::type
        test_nothrow_delete_array_operator(int) noexcept {
            static_assert(is_type<T>::value,
                          "The function test_nothrow_delete_array_operator() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline typename conditional<
                noexcept(lvalue_auxiliary<T, void>::lhs.operator delete[] (nullptr)),
                __true_type, __false_type>::type
        test_nothrow_delete_array_operator(long) noexcept {
            static_assert(is_type<T>::value,
                          "The function test_nothrow_delete_array_operator() cannot be called!");
            return {};
        }
        template <typename T, bool HasNewOperator = has_new_operator<T>::value>
        struct has_nothrow_new_operator_auxiliary {
            using value_type = bool;
            using result = decltype(test_nothrow_new_operator<T>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_new_operator_auxiliary<T, HasNewOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_new_operator_auxiliary<T, HasNewOperator>::value;
            }
        };
        template <typename T>
        struct has_nothrow_new_operator_auxiliary<T, false> {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_new_operator_auxiliary<T, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_new_operator_auxiliary<T, false>::value;
            }
        };
        template <typename T, bool HasNewArrayOperator = has_new_array_operator<T>::value>
        struct has_nothrow_new_array_operator_auxiliary {
            using value_type = bool;
            using result = decltype(test_nothrow_new_array_operator<T>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_new_array_operator_auxiliary<T, HasNewArrayOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_new_array_operator_auxiliary<T, HasNewArrayOperator>::value;
            }
        };
        template <typename T>
        struct has_nothrow_new_array_operator_auxiliary<T, false> {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_new_array_operator_auxiliary<T, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_new_array_operator_auxiliary<T, false>::value;
            }
        };
        template <typename T, bool HasDeleteOperator = has_delete_operator<T>::value>
        struct has_nothrow_delete_operator_auxiliary {
            using value_type = bool;
            using result = decltype(test_nothrow_delete_operator<T>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_delete_operator_auxiliary<T, HasDeleteOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_delete_operator_auxiliary<T, HasDeleteOperator>::value;
            }
        };
        template <typename T>
        struct has_nothrow_delete_operator_auxiliary<T, false> {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_delete_operator_auxiliary<T, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_delete_operator_auxiliary<T, false>::value;
            }
        };
        template <typename T, bool HasDeleteArrayOperator = has_delete_array_operator<T>::value>
        struct has_nothrow_delete_array_operator_auxiliary {
            using value_type = bool;
            using result = decltype(test_delete_array_operator<T>(0));
            constexpr static inline auto value {static_cast<bool>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_delete_array_operator_auxiliary<T, HasDeleteArrayOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_delete_array_operator_auxiliary<T, HasDeleteArrayOperator>::value;
            }
        };
    }
    template <typename T>
    struct has_nothrow_new_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_new_operator_auxiliary<T>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_new_operator<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_new_operator<T>::value;
        }
    };
    template <typename T>
    struct has_nothrow_new_array_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_new_array_operator_auxiliary<T>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_new_array_operator<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_new_array_operator<T>::value;
        }
    };
    template <typename T>
    struct has_nothrow_delete_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_delete_operator_auxiliary<T>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_delete_operator<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_delete_operator<T>::value;
        }
    };
    template <typename T>
    struct has_nothrow_delete_array_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_delete_array_operator_auxiliary<T>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_delete_array_operator<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_delete_array_operator<T>::value;
        }
    };
    template <typename LHS, typename RHS = LHS>
    struct has_not_equal_to_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_not_equal_to_operator<LHS, RHS>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_not_equal_to_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_not_equal_to_operator<LHS, RHS>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename LHS, typename RHS = LHS,
                bool HasNotEqualToOperator = has_not_equal_to_operator<LHS, RHS>::value>
        struct has_nothrow_not_equal_to_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_not_equal_to_operator_auxiliary<
                        LHS, RHS, HasNotEqualToOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_not_equal_to_operator_auxiliary<
                        LHS, RHS, HasNotEqualToOperator>::value;
            }
        };
        template <typename LHS, typename RHS>
        struct has_nothrow_not_equal_to_operator_auxiliary<LHS, RHS, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_not_equal_to_operator_nothrow<LHS, RHS>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_not_equal_to_operator_auxiliary<LHS, RHS, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_not_equal_to_operator_auxiliary<LHS, RHS, true>::value;
            }
        };
    }
    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_not_equal_to_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_not_equal_to_operator_auxiliary<
                LHS, RHS, true>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_not_equal_to_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_not_equal_to_operator<LHS, RHS>::value;
        }
    };
    template <typename LHS, typename RHS = LHS>
    struct has_plus_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_plus_operator<LHS, RHS>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_plus_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_plus_operator<LHS, RHS>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename LHS, typename RHS = LHS,
                bool HasPlusOperator = has_plus_operator<LHS, RHS>::value>
        struct has_nothrow_plus_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_plus_operator_auxiliary<LHS, RHS, HasPlusOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_plus_operator_auxiliary<LHS, RHS, HasPlusOperator>::value;
            }
        };
        template <typename LHS, typename RHS>
        struct has_nothrow_plus_operator_auxiliary<LHS, RHS, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_plus_operator_nothrow<LHS, RHS>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_plus_operator_auxiliary<LHS, RHS, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_plus_operator_auxiliary<LHS, RHS, true>::value;
            }
        };
    }
    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_plus_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_plus_operator_auxiliary<LHS, RHS>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_plus_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_plus_operator<LHS, RHS>::value;
        }
    };
    template <typename LHS, typename RHS = LHS>
    struct has_plus_assignment_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_plus_assignment_operator<LHS, RHS>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_plus_assignment_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_plus_assignment_operator<LHS, RHS>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename LHS, typename RHS = LHS,
                bool HasPlusAssignmentOperator = has_plus_assignment_operator<LHS, RHS>::value>
        struct has_nothrow_plus_assignment_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_plus_assignment_operator_auxiliary<
                        LHS, RHS, HasPlusAssignmentOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_plus_assignment_operator_auxiliary<
                        LHS, RHS, HasPlusAssignmentOperator>::value;
            }
        };
        template <typename LHS, typename RHS>
        struct has_nothrow_plus_assignment_operator_auxiliary<LHS, RHS, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_plus_assignment_operator_nothrow<LHS, RHS>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_plus_assignment_operator_auxiliary<LHS, RHS, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_plus_assignment_operator_auxiliary<LHS, RHS, true>::value;
            }
        };
    }
    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_plus_assignment_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_plus_assignment_operator_auxiliary<
                LHS, RHS>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_plus_assignment_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_plus_assignment_operator<LHS, RHS>::value;
        }
    };
    template <typename T>
    struct has_post_decrement_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_post_decrement_operator<T>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_post_decrement_operator<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_post_decrement_operator<T>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename T, bool HasPostDecrementOperator = has_post_decrement_operator<T>::value>
        struct has_nothrow_post_decrement_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_post_decrement_operator_auxiliary<
                        T, HasPostDecrementOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_post_decrement_operator_auxiliary<
                        T, HasPostDecrementOperator>::value;
            }
        };
        template <typename T>
        struct has_nothrow_post_decrement_operator_auxiliary<T, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_post_decrement_operator_nothrow<T>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_post_decrement_operator_auxiliary<T, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_post_decrement_operator_auxiliary<T, true>::value;
            }
        };
    }
    template <typename T>
    struct has_nothrow_post_decrement_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_post_decrement_operator_auxiliary<T>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_post_decrement_operator<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_post_decrement_operator<T>::value;
        }
    };
    template <typename T>
    struct has_post_increment_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_post_increment_operator<T>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_post_increment_operator<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_post_increment_operator<T>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename T, bool HasPostIncrementOperator = has_post_increment_operator<T>::value>
        struct has_nothrow_post_increment_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_post_increment_operator_auxiliary<
                        T, HasPostIncrementOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_post_increment_operator_auxiliary<
                        T, HasPostIncrementOperator>::value;
            }
        };
        template <typename T>
        struct has_nothrow_post_increment_operator_auxiliary<T, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_post_increment_operator_nothrow<T>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_post_increment_operator_auxiliary<T, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_post_increment_operator_auxiliary<T, true>::value;
            }
        };
    }
    template <typename T>
    struct has_nothrow_post_increment_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_post_increment_operator_auxiliary<T>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_post_increment_operator<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_post_increment_operator<T>::value;
        }
    };
    template <typename T>
    struct has_pre_decrement_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_pre_decrement_operator<T>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_pre_decrement_operator<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_pre_decrement_operator<T>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename T, bool HasPreDecrementOperator = has_pre_decrement_operator<T>::value>
        struct has_nothrow_pre_decrement_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_pre_decrement_operator_auxiliary<
                        T, HasPreDecrementOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_pre_decrement_operator_auxiliary<
                        T, HasPreDecrementOperator>::value;
            }
        };
        template <typename T>
        struct has_nothrow_pre_decrement_operator_auxiliary<T, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_pre_decrement_operator_nothrow<T>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_pre_decrement_operator_auxiliary<T, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_pre_decrement_operator_auxiliary<T, true>::value;
            }
        };
    }
    template <typename T>
    struct has_nothrow_pre_decrement_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_pre_decrement_operator_auxiliary<T>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_pre_decrement_operator<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_pre_decrement_operator<T>::value;
        }
    };
    template <typename T>
    struct has_pre_increment_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_pre_increment_operator<T>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_pre_increment_operator<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_pre_increment_operator<T>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename T, bool HasPreIncrementOperator = has_pre_increment_operator<T>::value>
        struct has_nothrow_pre_increment_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_pre_increment_operator_auxiliary<
                        T, HasPreIncrementOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_pre_increment_operator_auxiliary<
                        T, HasPreIncrementOperator>::value;
            }
        };
        template <typename T>
        struct has_nothrow_pre_increment_operator_auxiliary<T, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_pre_increment_operator_nothrow<T>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_pre_increment_operator_auxiliary<T, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_pre_increment_operator_auxiliary<T, true>::value;
            }
        };
    }
    template <typename T>
    struct has_nothrow_pre_increment_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_pre_increment_operator_auxiliary<T>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_pre_increment_operator<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_pre_increment_operator<T>::value;
        }
    };
    template <typename LHS, typename RHS = LHS>
    struct has_right_shift_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_right_shift_operator<LHS, RHS>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_right_shift_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_right_shift_operator<LHS, RHS>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename LHS, typename RHS = LHS,
                bool HasRightShiftOperator = has_right_shift_operator<LHS, RHS>::value>
        struct has_nothrow_right_shift_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_right_shift_operator_auxiliary<
                        LHS, RHS, HasRightShiftOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_right_shift_operator_auxiliary<
                        LHS, RHS, HasRightShiftOperator>::value;
            }
        };
        template <typename LHS, typename RHS>
        struct has_nothrow_right_shift_operator_auxiliary<LHS, RHS, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_right_shift_operator_nothrow<LHS, RHS>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_right_shift_operator_auxiliary<LHS, RHS, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_right_shift_operator_auxiliary<LHS, RHS, true>::value;
            }
        };
    }
    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_right_shift_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_right_shift_operator_auxiliary<LHS, RHS>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_right_shift_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_right_shift_operator<LHS, RHS>::value;
        }
    };
    template <typename LHS, typename RHS = LHS>
    struct has_right_shift_assignment_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_right_shift_assignment_operator<LHS, RHS>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_right_shift_assignment_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_right_shift_assignment_operator<LHS, RHS>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename LHS, typename RHS = LHS,
                bool HasRightShiftAssignmentOperator = has_right_shift_assignment_operator<
                        LHS, RHS>::value>
        struct has_nothrow_right_shift_assignment_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_right_shift_assignment_operator_auxiliary<
                        LHS, RHS, HasRightShiftAssignmentOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_right_shift_assignment_operator_auxiliary<
                        LHS, RHS, HasRightShiftAssignmentOperator>::value;
            }
        };
        template <typename LHS, typename RHS>
        struct has_nothrow_right_shift_assignment_operator_auxiliary<LHS, RHS, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_right_shift_assignment_operator_nothrow<LHS, RHS>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_right_shift_assignment_operator_auxiliary<LHS, RHS, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_right_shift_assignment_operator_auxiliary<LHS, RHS, true>::value;
            }
        };
    }
    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_right_shift_assignment_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_right_shift_assignment_operator_auxiliary<
                LHS, RHS>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_right_shift_assignment_operator<LHS, RHS>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_right_shift_assignment_operator<LHS, RHS>::value;
        }
    };
    template <typename T>
    struct has_unary_minus_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_unary_minus_operator<T>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_unary_minus_operator<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_unary_minus_operator<T>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename T, bool HasUnaryMinusOperator = has_unary_minus_operator<T>::value>
        struct has_nothrow_unary_minus_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_unary_minus_operator_auxiliary<T, HasUnaryMinusOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_unary_minus_operator_auxiliary<T, HasUnaryMinusOperator>::value;
            }
        };
        template <typename T>
        struct has_nothrow_unary_minus_operator_auxiliary<T, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_unary_minus_operator_nothrow<T>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_unary_minus_operator_auxiliary<T, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_unary_minus_operator_auxiliary<T, true>::value;
            }
        };
    }
    template <typename T>
    struct has_nothrow_unary_minus_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_unary_minus_operator_auxiliary<T>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_unary_minus_operator<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_unary_minus_operator<T>::value;
        }
    };
    template <typename T>
    struct has_unary_plus_operator {
        using value_type = bool;
        using result = decltype(__dsa::test_unary_plus_operator<T>(0));
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_unary_plus_operator<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_unary_plus_operator<T>::value;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename T, bool HasUnaryPlusOperator = has_unary_plus_operator<T>::value>
        struct has_nothrow_unary_plus_operator_auxiliary {
            using value_type = bool;
            using result = __false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_unary_plus_operator_auxiliary<T, HasUnaryPlusOperator>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_unary_plus_operator_auxiliary<T, HasUnaryPlusOperator>::value;
            }
        };
        template <typename T>
        struct has_nothrow_unary_plus_operator_auxiliary<T, true> {
            using value_type = bool;
            using result = decltype(__dsa::is_unary_plus_operator_nothrow<T>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_nothrow_unary_plus_operator_auxiliary<T, true>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_nothrow_unary_plus_operator_auxiliary<T, true>::value;
            }
        };
    }
    template <typename T>
    struct has_nothrow_unary_plus_operator {
        using value_type = bool;
        using result = typename __dsa::has_nothrow_unary_plus_operator_auxiliary<T>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return has_nothrow_unary_plus_operator<T>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return has_nothrow_unary_plus_operator<T>::value;
        }
    };
}

#if defined(__ORDER_LITTLE_ENDIAN__) and defined(__ORDER_BIG_ENDIAN__) and defined(__BYTE_ORDER__)
namespace data_structure {
    enum class endian {
        little = __ORDER_LITTLE_ENDIAN__,
        big = __ORDER_BIG_ENDIAN__,
        native = __BYTE_ORDER__
    };
}
#endif

#endif //DATA_STRUCTURE_TYPE_TRAITS_HPP
