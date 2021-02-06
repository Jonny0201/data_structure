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

#ifndef DATA_STRUCTURE_TYPE_TRAITS_HPP
#define DATA_STRUCTURE_TYPE_TRAITS_HPP

#include "__config.hpp"

__DATA_STRUCTURE_START(constant)
namespace data_structure {
    template <typename T, T Value>
    struct constant {
        using value_type = T;
        using type = constant;
        constexpr static auto value {Value};
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
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(meta)
namespace data_structure {
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
    struct make_true_type {
        using type = true_type;
    };
    template <typename ...Ts>
    using make_true_type_t = typename make_true_type<Ts...>::type;

    template <typename ...>
    struct make_false_type {
        using type = false_type;
    };
    template <typename ...Ts>
    using make_false_type_t = typename make_false_type<Ts...>::type;

    template <typename ...>
    constexpr inline auto make_true {true};

    template <typename ...>
    constexpr inline auto make_false {false};

    template <typename ...Args>
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
    template <typename T, typename ...Args>
    struct type_container<T, Args...> {
        using type = T;
        using remaining = type_container<Args...>;
    };

    template <void () = [] {}>
    struct unique_type {};
    using unique_type_t = unique_type<>;
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(detail)
#define __DATA_STRUCTURE_TEST_ADDITION(template_parameters, operation, disable_type, name) \
    template <template_parameters> \
    static constexpr operation test_##name(int) noexcept; \
    template <template_parameters> \
    static constexpr disable_type test_##name(...) noexcept
namespace data_structure::__data_structure_auxiliary {
    __DATA_STRUCTURE_TEST_ADDITION(typename T, T &, T, lvalue_reference);
    __DATA_STRUCTURE_TEST_ADDITION(typename T, T &&, T, rvalue_reference);
    __DATA_STRUCTURE_TEST_ADDITION(typename T, T *, T, pointer);
}
#define __DATA_STRUCTURE_REMOVE_CV_HELPER_MAIN(name) \
    template <typename> \
    struct name##_auxiliary : false_type {}
#define __DATA_STRUCTURE_REMOVE_CV_HELPER_SPECIALIZATION(name, type, ...) \
    template <__VA_ARGS__> \
    struct name##_auxiliary<type> : true_type {}
namespace data_structure {
    template <typename>
    struct is_function;
    namespace __data_structure_auxiliary {
        __DATA_STRUCTURE_REMOVE_CV_HELPER_MAIN(is_integral);
        __DATA_STRUCTURE_REMOVE_CV_HELPER_SPECIALIZATION(is_integral, bool);
        __DATA_STRUCTURE_REMOVE_CV_HELPER_SPECIALIZATION(is_integral, char);
        __DATA_STRUCTURE_REMOVE_CV_HELPER_SPECIALIZATION(is_integral, unsigned char);
        __DATA_STRUCTURE_REMOVE_CV_HELPER_SPECIALIZATION(is_integral, char8_t);
        __DATA_STRUCTURE_REMOVE_CV_HELPER_SPECIALIZATION(is_integral, char16_t);
        __DATA_STRUCTURE_REMOVE_CV_HELPER_SPECIALIZATION(is_integral, char32_t);
        __DATA_STRUCTURE_REMOVE_CV_HELPER_SPECIALIZATION(is_integral, wchar_t);
        __DATA_STRUCTURE_REMOVE_CV_HELPER_SPECIALIZATION(is_integral, short);
        __DATA_STRUCTURE_REMOVE_CV_HELPER_SPECIALIZATION(is_integral, unsigned short);
        __DATA_STRUCTURE_REMOVE_CV_HELPER_SPECIALIZATION(is_integral, int);
        __DATA_STRUCTURE_REMOVE_CV_HELPER_SPECIALIZATION(is_integral, unsigned int);
        __DATA_STRUCTURE_REMOVE_CV_HELPER_SPECIALIZATION(is_integral, long);
        __DATA_STRUCTURE_REMOVE_CV_HELPER_SPECIALIZATION(is_integral, unsigned long);
        __DATA_STRUCTURE_REMOVE_CV_HELPER_SPECIALIZATION(is_integral, long long);
        __DATA_STRUCTURE_REMOVE_CV_HELPER_SPECIALIZATION(is_integral, unsigned long long);
        __DATA_STRUCTURE_REMOVE_CV_HELPER_SPECIALIZATION(is_integral, __int128_t);
        __DATA_STRUCTURE_REMOVE_CV_HELPER_SPECIALIZATION(is_integral, __uint128_t);

        __DATA_STRUCTURE_REMOVE_CV_HELPER_MAIN(is_floating_point);
        __DATA_STRUCTURE_REMOVE_CV_HELPER_SPECIALIZATION(is_floating_point, float);
        __DATA_STRUCTURE_REMOVE_CV_HELPER_SPECIALIZATION(is_floating_point, double);
        __DATA_STRUCTURE_REMOVE_CV_HELPER_SPECIALIZATION(is_floating_point, long double);

        __DATA_STRUCTURE_REMOVE_CV_HELPER_MAIN(is_character);
        __DATA_STRUCTURE_REMOVE_CV_HELPER_SPECIALIZATION(is_character, char);
        __DATA_STRUCTURE_REMOVE_CV_HELPER_SPECIALIZATION(is_character, unsigned char);
        __DATA_STRUCTURE_REMOVE_CV_HELPER_SPECIALIZATION(is_character, char8_t);
        __DATA_STRUCTURE_REMOVE_CV_HELPER_SPECIALIZATION(is_character, char16_t);
        __DATA_STRUCTURE_REMOVE_CV_HELPER_SPECIALIZATION(is_character, char32_t);
        __DATA_STRUCTURE_REMOVE_CV_HELPER_SPECIALIZATION(is_character, wchar_t);

        template <typename T>
        struct is_signed_auxiliary : bool_constant<static_cast<T>(-1) < static_cast<T>(0)> {};

        template <typename T>
        struct is_unsigned_auxiliary : bool_constant<static_cast<T>(0) < static_cast<T>(-1)> {};

        __DATA_STRUCTURE_REMOVE_CV_HELPER_MAIN(is_pointer);
        __DATA_STRUCTURE_REMOVE_CV_HELPER_SPECIALIZATION(is_pointer, T *, typename T);

        template <typename>
        struct is_member_function_pointer_auxiliary : false_type {};
        template <typename F, typename Class>
        struct is_member_function_pointer_auxiliary<F Class::*> : is_function<F> {};

        template <typename T>
        static constexpr true_type test_convertible(T) noexcept;

        static constexpr false_type test_convertible(...) noexcept;

        template <typename T>
        static constexpr void test_noexcept(T) noexcept;

        template <typename T>
        static constexpr bool_constant<noexcept(test_noexcept<T>())> test_nothrow_convertible() noexcept;

        template <typename, typename = void>
        struct is_invocable_auxiliary : false_type {};
        template <typename Result>
        struct is_invocable_auxiliary<Result, void_t<typename Result::type>> : true_type {};

        template <bool, bool, typename ...>
        struct result_of_nothrow_auxiliary : false_type {};
    }
}
#define __DATA_STRUCTURE_TEST_OPERATION(name, expression, ...) \
    template <__VA_ARGS__> \
    static constexpr select_second_t<decltype(expression), true_type> test_##name(int) noexcept; \
    template <__VA_ARGS__> \
    static constexpr false_type test_##name(...) noexcept
#define __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(name, expression, ...) \
    template <__VA_ARGS__> \
    static constexpr bool_constant<noexcept(expression)> test_nothrow_##name(int) noexcept; \
    template <__VA_ARGS__> \
    static constexpr false_type test_##name_nothrow(...) noexcept
namespace data_structure {
    namespace __data_structure_auxiliary {
        template <typename, typename T>
        struct select_second {
            using type = T;
        };
        template <typename T, typename U>
        using select_second_t = typename select_second<T, U>::type;

        template <typename T>
        static constexpr T &&declval_auxiliary(int) noexcept;
        template <typename T>
        static constexpr T declval_auxiliary(...) noexcept;
    }

    template <typename T>
    constexpr decltype(__dsa::declval_auxiliary<T>(0)) declval() noexcept;

    template <typename> struct is_nothrow_move_constructible;
    template <typename> struct is_nothrow_move_assignable;
    template <typename T>
    void swap(T &lhs, T &rhs) noexcept(is_nothrow_move_constructible<T>::value and
            is_nothrow_move_assignable<T>::value);

    namespace __data_structure_auxiliary {
        __DATA_STRUCTURE_TEST_OPERATION(destructible, declval<T >().~T(), typename T);
        __DATA_STRUCTURE_TEST_OPERATION(swappable, ds::swap(declval<LHS>(), declval<RHS>()),
                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION(complete, sizeof(T) > 0, typename T);
        __DATA_STRUCTURE_TEST_OPERATION(list_constructible, T {declval<Args>()...},
                typename T, typename ...Args);
        __DATA_STRUCTURE_TEST_OPERATION(static_castable, static_cast<To>(declval<From>()),
                typename From, typename To);
        __DATA_STRUCTURE_TEST_OPERATION(dynamic_castable, dynamic_cast<To>(declval<From>()),
                typename From, typename To);
        __DATA_STRUCTURE_TEST_OPERATION(const_castable, const_cast<To>(declval<From>()),
                typename From, typename To);
        __DATA_STRUCTURE_TEST_OPERATION(reinterpret_castable, reinterpret_cast<To>(declval<From>()),
                typename From, typename To);
        __DATA_STRUCTURE_TEST_OPERATION(castable, (To)declval<From>(), typename From, typename To);
        __DATA_STRUCTURE_TEST_OPERATION(swap_memfun, declval<T &>().swap(declval<T &>()), typename T);
        __DATA_STRUCTURE_TEST_OPERATION(address_of, &declval<T>(), typename T);
        __DATA_STRUCTURE_TEST_OPERATION(bit_and, declval<LHS>() bitand declval<RHS>(),
                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION(bit_and_assignment, declval<LHS>() and_eq declval<RHS>(),
                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION(bit_or, declval<LHS>() | declval<RHS>(),
                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION(bit_or_assignment, declval<LHS>() or_eq declval<RHS>(),
                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION(bit_xor, declval<LHS>() xor declval<RHS>(),
                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION(bit_xor_assignment, declval<LHS>() xor_eq declval<RHS>(),
                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION(complement, compl declval<T>(), typename T);
        __DATA_STRUCTURE_TEST_OPERATION(dereference, *declval<T>(), typename T);
        __DATA_STRUCTURE_TEST_OPERATION(divide, declval<LHS>() / declval<RHS>(),
                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION(divide_assignment, declval<LHS>() /= declval<RHS>(),
                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION(equal_to, declval<LHS>() == declval<RHS>(),
                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION(greater, declval<LHS>() > declval<RHS>(),
                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION(greater_equal_to, declval<LHS>() >= declval<RHS>(),
                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION(left_shift, declval<LHS>() << declval<RHS>(),
                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION(left_shift_assignment, declval<LHS>() <<= declval<RHS>(),
                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION(right_shift, declval<LHS>() >> declval<RHS>(),
                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION(right_shift_assignment, declval<LHS>() >>= declval<RHS>(),
                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION(less, declval<LHS>() < declval<RHS>(),
                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION(less_equal_to, declval<LHS>() <= declval<RHS>(),
                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION(logical_and, declval<LHS>() and declval<RHS>(),
                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION(logical_or, declval<LHS>() or declval<RHS>(),
                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION(logical_not, not declval<T>(), typename T);
        __DATA_STRUCTURE_TEST_OPERATION(unary_minus, -declval<T>(), typename T);
        __DATA_STRUCTURE_TEST_OPERATION(minus, declval<LHS>() - declval<RHS>(),
                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION(minus_assignment, declval<LHS>() -= declval<RHS>(),
                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION(modules, declval<LHS>() % declval<RHS>(),
                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION(modules_assignment, declval<LHS>() %= declval<RHS>(),
                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION(multiply, declval<LHS>() * declval<RHS>(),
                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION(multiply_assignment, declval<LHS>() *= declval<RHS>(),
                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION(three_way, declval<LHS>() <=> declval<RHS>(),
                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION(not_equal_to, declval<LHS>() not_eq declval<RHS>(),
                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION(plus, declval<LHS>() + declval<RHS>(),
                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION(unary_plus, +declval<T>(), typename T);
        __DATA_STRUCTURE_TEST_OPERATION(plus_assignment, declval<LHS>() += declval<RHS>(),
                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION(subscript, declval<LHS>()[declval<RHS>()],
                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION(pre_increment, ++declval<T>(), typename T);
        __DATA_STRUCTURE_TEST_OPERATION(post_increment, declval<T>()++, typename T);
        __DATA_STRUCTURE_TEST_OPERATION(pre_decrement, --declval<T>(), typename T);
        __DATA_STRUCTURE_TEST_OPERATION(post_decrement, declval<T>()--, typename T);
        __DATA_STRUCTURE_TEST_OPERATION(member_access_by_pointer, declval<T>().operator->(), typename T);
        __DATA_STRUCTURE_TEST_OPERATION(member_access_by_pointer_dereference,
                declval<T>().operator->*(), typename T);
        __DATA_STRUCTURE_TEST_OPERATION(new_operator, T::operator new(declval<Args>()...),
                typename T, typename ...Args);
        __DATA_STRUCTURE_TEST_OPERATION(new_array_operator, T::operator new[](declval<Args>()...),
                typename T, typename ...Args);
        __DATA_STRUCTURE_TEST_OPERATION(delete_operator, T::operator delete(declval<Args>()...),
                typename T, typename ...Args);
        __DATA_STRUCTURE_TEST_OPERATION(delete_array_operator, T::operator delete[](declval<Args>()...),
                typename T, typename ...Args);
        __DATA_STRUCTURE_TEST_OPERATION(function_call, declval<T>()(declval<Args>()...),
                typename T, typename ...Args);
        __DATA_STRUCTURE_TEST_OPERATION(comma, (declval<T>(), declval<Arg>()), typename T, typename Arg);

        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(destructible, declval<T &>().~T(), typename T);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(swappable, ds::swap(declval<LHS>(), declval<RHS>()),
                                                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(list_constructible, T {declval<Args>()...},
                                                typename T, typename ...Args);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(static_castable, static_cast<To>(declval<From>()),
                                                typename From, typename To);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(dynamic_castable, dynamic_cast<To>(declval<From>()),
                                                typename From, typename To);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(const_castable, const_cast<To>(declval<From>()),
                                                typename From, typename To);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(reinterpret_castable, reinterpret_cast<To>(declval<From>()),
                                                typename From, typename To);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(castable, (To)declval<From>(), typename From, typename To);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(swap_memfun, declval<T &>().swap(declval<T &>()), typename T);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(address_of, &declval<T>(), typename T);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(bit_and, declval<LHS>() bitand declval<RHS>(),
                                                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(bit_and_assignment, declval<LHS>() and_eq declval<RHS>(),
                                                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(bit_or, declval<LHS>() | declval<RHS>(),
                                                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(bit_or_assignment, declval<LHS>() or_eq declval<RHS>(),
                                                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(bit_xor, declval<LHS>() xor declval<RHS>(),
                                                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(bit_xor_assignment, declval<LHS>() xor_eq declval<RHS>(),
                                                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(complement, compl declval<T>(), typename T);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(dereference, *declval<T>(), typename T);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(divide, declval<LHS>() / declval<RHS>(),
                                                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(divide_assignment, declval<LHS>() /= declval<RHS>(),
                                                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(equal_to, declval<LHS>() == declval<RHS>(),
                                                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(greater, declval<LHS>() > declval<RHS>(),
                                                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(greater_equal_to, declval<LHS>() >= declval<RHS>(),
                                                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(left_shift, declval<LHS>() << declval<RHS>(),
                                                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(left_shift_assignment, declval<LHS>() <<= declval<RHS>(),
                                                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(right_shift, declval<LHS>() >> declval<RHS>(),
                                                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(right_shift_assignment, declval<LHS>() >>= declval<RHS>(),
                                                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(less, declval<LHS>() < declval<RHS>(),
                                                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(less_equal_to, declval<LHS>() <= declval<RHS>(),
                                                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(logical_and, declval<LHS>() and declval<RHS>(),
                                                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(logical_or, declval<LHS>() or declval<RHS>(),
                                                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(logical_not, not declval<T>(), typename T);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(unary_minus, -declval<T>(), typename T);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(minus, declval<LHS>() - declval<RHS>(),
                                                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(minus_assignment, declval<LHS>() -= declval<RHS>(),
                                                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(modules, declval<LHS>() % declval<RHS>(),
                                                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(modules_assignment, declval<LHS>() %= declval<RHS>(),
                                                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(multiply, declval<LHS>() * declval<RHS>(),
                                                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(multiply_assignment, declval<LHS>() *= declval<RHS>(),
                                                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(three_way, declval<LHS>() <=> declval<RHS>(),
                                                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(not_equal_to, declval<LHS>() not_eq declval<RHS>(),
                                                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(plus, declval<LHS>() + declval<RHS>(),
                                                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(unary_plus, +declval<T>(), typename T);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(plus_assignment, declval<LHS>() += declval<RHS>(),
                                                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(subscript, declval<LHS>()[declval<RHS>()],
                                                typename LHS, typename RHS);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(pre_increment, ++declval<T>(), typename T);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(post_increment, declval<T>()++, typename T);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(pre_decrement, --declval<T>(), typename T);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(post_decrement, declval<T>()--, typename T);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(member_access_by_pointer, declval<T>().operator->(), typename T);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(member_access_by_pointer_dereference,
                                                declval<T>().operator->*(), typename T);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(new_operator, T::operator new(declval<Args>()...),
                                                typename T, typename ...Args);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(new_array_operator, T::operator new[](declval<Args>()...),
                                                typename T, typename ...Args);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(delete_operator, T::operator delete(declval<Args>()...),
                                                typename T, typename ...Args);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(delete_array_operator, T::operator delete[](declval<Args>()...),
                                                typename T, typename ...Args);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(function_call, declval<T>()(declval<Args>()...),
                                                typename T, typename ...Args);
        __DATA_STRUCTURE_TEST_OPERATION_NOTHROW(comma, (declval<T>(), declval<Arg>()), typename T, typename Arg);
    }
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(add something)
namespace data_structure {
    template <typename T>
    struct add_lvalue_reference {
        using type = decltype(__dsa::test_lvalue_reference<T>(0));
    };
    template <typename T>
    using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;
    template <typename T>
    struct add_rvalue_reference {
        using type = decltype(__dsa::test_rvalue_reference<T>(0));
    };
    template <typename T>
    using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

    template <typename T>
    struct add_pointer {
        using type = decltype(__dsa::test_pointer<T>(0));
    };
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
    struct add_const_reference : add_lvalue_reference<add_const_t<T>> {};
    template <typename T>
    using add_const_reference_t = typename add_const_reference<T>::type;
    template <typename T>
    struct add_const_pointer : add_pointer<add_const_t<T>> {};
    template <typename T>
    using add_const_pointer_t = typename add_const_pointer<T>::type;
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(remove something)
namespace data_structure {
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

    template <typename T>
    struct remove_const_reference : remove_const<remove_reference_t<T>> {};
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
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(is something)
namespace data_structure {
    template <typename, typename>
    struct is_same : false_type {};
    template <typename T>
    struct is_same<T, T> : true_type {};
    template <typename T, typename U>
    constexpr inline auto is_same_v = is_same<T, U>::value;

    template <typename T>
    struct is_void : is_same<void, remove_cv_t<T>> {};
    template <typename T>
    constexpr inline auto is_void_v {is_void<T>::value};

    template <typename T>
    struct is_null_pointer : is_same<decltype(nullptr), remove_cv_t<T>> {};
    template <typename T>
    constexpr inline auto is_null_pointer_v {is_null_pointer<T>::value};

    template <typename T>
    struct is_const : false_type {};
    template <typename T>
    struct is_const<const T> : true_type {};
    template <typename T>
    constexpr inline auto is_const_v {is_const<T>::value};

    template <typename T>
    struct is_volatile : false_type {};
    template <typename T>
    struct is_volatile<volatile T> : true_type {};
    template <typename T>
    constexpr inline auto is_volatile_v {is_volatile<T>::value};

    template <typename T>
    struct is_cv : false_type {};
    template <typename T>
    struct is_cv<const volatile T> : true_type {};
    template <typename T>
    constexpr inline auto is_cv_v {is_cv<T>::value};

    template <typename T>
    struct is_integral : __dsa::is_integral_auxiliary<remove_cv_t<T>> {};
    template <typename T>
    constexpr inline auto is_integral_v {is_integral<T>::value};

    template <typename T>
    struct is_floating_point : __dsa::is_floating_point_auxiliary<remove_cv_t<T>> {};
    template <typename T>
    constexpr inline auto is_floating_point_v {is_floating_point<T>::value};

    template <typename T>
    struct is_signed : __dsa::is_signed_auxiliary<remove_cv_t<T>> {};
    template <typename T>
    constexpr inline auto is_signed_v {is_signed<T>::value};

    template <typename T>
    struct is_unsigned : __dsa::is_unsigned_auxiliary<remove_cv_t<T>> {};
    template <typename T>
    constexpr inline auto is_unsigned_v {is_unsigned<T>::value};

    template <typename T>
    struct is_character : __dsa::is_character_auxiliary<remove_cv_t<T>> {};
    template <typename T>
    constexpr inline auto is_character_v {is_character<T>::value};

    template <typename>
    struct is_array : false_type {};
    template <typename T>
    struct is_array<T []> : true_type {};
    template <typename T, size_t N>
    struct is_array<T [N]> : true_type {};
    template <typename T>
    constexpr inline auto is_array_v {is_array<T>::value};

    template <typename>
    struct is_unbounded_array : false_type {};
    template <typename T>
    struct is_unbounded_array<T []> : true_type {};
    template <typename T>
    constexpr inline auto is_unbounded_array_v {is_unbounded_array<T>::value};

    template <typename>
    struct is_bounded_array : false_type {};
    template <typename T, size_t N>
    struct is_bounded_array<T [N]> : true_type {};
    template <typename T>
    constexpr inline auto is_bounded_array_v {is_bounded_array<T>::value};

    template <typename T>
    struct is_enum : bool_constant<__is_enum(T)> {};
    template <typename T>
    constexpr inline auto is_enum_v {is_enum<T>::value};

    template <typename T>
    struct is_union : bool_constant<__is_union(T)> {};
    template <typename T>
    constexpr inline auto is_union_v {is_union<T>::value};

    template <typename T>
    struct is_class : bool_constant<__is_class(T)> {};
    template <typename T>
    constexpr inline auto is_class_v {is_class<T>::value};

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
    constexpr inline auto is_function_v {is_function<T>::value};

    template <typename T>
    struct is_pointer : __dsa::is_pointer_auxiliary<remove_cv_t<T>> {};
    template <typename T>
    constexpr inline auto is_pointer_v {is_pointer<T>::value};

    template <typename T>
    struct is_member_pointer : false_type {};
    template <typename T, typename Class>
    struct is_member_pointer<T Class::*> : true_type {};
    template <typename T>
    constexpr inline auto is_member_pointer_v {is_member_pointer<T>::value};

    template <typename T>
    struct is_member_function_pointer : __dsa::is_member_function_pointer_auxiliary<remove_cv_t<T>> {};
    template <typename T>
    constexpr inline auto is_member_function_pointer_v {is_member_function_pointer<T>::value};

    template <typename T>
    struct is_member_object_pointer : bool_constant<is_member_pointer_v<T> and not is_member_function_pointer_v<T>> {};
    template <typename T>
    constexpr inline auto is_member_object_pointer_v {is_member_object_pointer<T>::value};

    template <typename T>
    struct is_function_pointer : bool_constant<is_pointer_v<T> and
            (is_function_v<remove_pointer_t<T>> or is_void_v<remove_pointer_t<T>> or
                    is_null_pointer_v<remove_pointer_t<T>>)> {};
    template <typename T>
    constexpr inline auto is_function_pointer_v {is_function_pointer<T>::value};

    template <typename T>
    struct is_lvalue_reference : false_type {};
    template <typename T>
    struct is_lvalue_reference<T &> : false_type {};
    template <typename T>
    constexpr inline auto is_lvalue_reference_v {is_lvalue_reference<T>::value};

    template <typename T>
    struct is_rvalue_reference : false_type {};
    template <typename T>
    struct is_rvalue_reference<T &&> : false_type {};
    template <typename T>
    constexpr inline auto is_rvalue_reference_v {is_rvalue_reference<T>::value};

    template <typename T>
    struct is_reference : false_type {};
    template <typename T>
    struct is_reference<T &> : true_type {};
    template <typename T>
    struct is_reference<T &&> : true_type {};
    template <typename T>
    constexpr inline auto is_reference_v {is_reference<T>::value};

    template <typename T>
    struct is_const_reference : bool_constant<is_lvalue_reference_v<T> and
            is_const_v<remove_lvalue_reference_t<T>>> {};
    template <typename T>
    constexpr inline auto is_const_reference_v {is_const_reference<T>::value};

    template <typename T>
    struct is_type : true_type {};
    template <typename T>
    constexpr inline auto is_type_v {is_type<T>::value};

    template <typename T>
    struct is_complete : decltype(__dsa::test_complete<T>(0)) {};
    template <typename T>
    constexpr inline auto is_complete_v {is_complete<T>::value};

    template <typename T>
    struct is_pod : bool_constant<__is_pod(T)> {};
    template <typename T>
    constexpr inline auto is_pod_v {is_pod<T>::value};

    template <typename T>
    struct is_empty : bool_constant<__is_empty(T)> {};
    template <typename T>
    constexpr inline auto is_empty_v {is_empty<T>::value};

    template <typename T>
    struct is_literal_type : bool_constant<__is_literal_type(T)> {};
    template <typename T>
    constexpr inline auto is_literal_type_v {is_literal_type<T>::value};

    template <typename T>
    struct is_standard_layout : bool_constant<__is_standard_layout(T)> {};
    template <typename T>
    constexpr inline auto is_standard_layout_v {is_standard_layout<T>::value};

    template <typename T>
    struct is_polymorphic : bool_constant<__is_polymorphic(T)> {};
    template <typename T>
    constexpr inline auto is_polymorphic_v {is_polymorphic<T>::value};

    template <typename T>
    struct is_abstract : bool_constant<__is_abstract(T)> {};
    template <typename T>
    constexpr inline auto is_abstract_v {is_abstract<T>::value};

    template <typename Base, typename Derived>
    struct is_base_of : bool_constant<__is_base_of(Base, Derived)> {};
    template <typename Base, typename Derived>
    constexpr inline auto is_base_of_v {is_base_of<Base, Derived>::value};

    template <typename T>
    struct is_final : bool_constant<__is_final(T)> {};
    template <typename T>
    constexpr inline auto is_final_v {is_final<T>::value};

    template <typename T>
    struct is_aggregate : bool_constant<__is_aggregate(T)> {};
    template <typename T>
    constexpr inline auto is_aggregate_v {is_aggregate<T>::value};

    template <typename T>
    struct is_arithmetic : bool_constant<is_integral_v<T> or is_floating_point_v<T>> {};
    template <typename T>
    constexpr inline auto is_arithmetic_v {is_arithmetic<T>::value};

    template <typename T>
    struct is_fundamental : bool_constant<is_arithmetic_v<T> or is_void_v<T> or
            is_null_pointer_v<remove_cv_t<T>>> {};
    template <typename T>
    constexpr inline auto is_fundamental_v {is_fundamental<T>::value};

    template <typename T>
    struct is_scalar : bool_constant<is_arithmetic_v<T> or is_enum_v<T> or is_pointer_v<T> or
            is_member_pointer_v<T> or is_null_pointer_v<T>> {};
    template <typename T>
    constexpr inline auto is_scalar_v {is_scalar<T>::value};

    template <typename T>
    struct is_compound : bool_constant<not is_fundamental_v<T>> {};
    template <typename T>
    constexpr inline auto is_compound_v {is_compound<T>::value};

    template <typename T>
    struct is_object : bool_constant<is_scalar_v<T> or is_array_v<T> or is_union_v<T> or is_class_v<T>> {};
    template <typename T>
    constexpr inline auto is_object_v {is_object<T>::value};

    template <typename T>
    struct is_trivial : bool_constant<__is_trivial(T)> {};
    template <typename T>
    constexpr inline auto is_trivial_v {is_trivial<T>::value};

    template <typename T>
    struct is_trivially_copyable : bool_constant<__is_trivially_copyable(T)> {};
    template <typename T>
    constexpr inline auto is_trivially_copyable_v {is_trivially_copyable<T>::value};

    template <typename T, typename ...Args>
    struct is_trivially_constructible : bool_constant<__is_trivially_constructible(T, Args...)> {};
    template <typename T, typename ...Args>
    constexpr inline auto is_trivially_constructible_v {is_trivially_constructible<T, Args...>::value};

    template <typename T>
    struct is_trivially_default_constructible : is_trivially_constructible<T> {};
    template <typename T>
    constexpr inline auto is_trivially_default_constructible_v {is_trivially_default_constructible<T>::value};

    template <typename T>
    struct is_trivially_copy_constructible : is_trivially_constructible<T, add_const_reference_t<T>> {};
    template <typename T>
    constexpr inline auto is_trivially_copy_constructible_v {is_trivially_copy_constructible<T>::value};

    template <typename T>
    struct is_trivially_move_constructible : is_trivially_constructible<T, add_rvalue_reference_t<T>> {};
    template <typename T>
    constexpr inline auto is_trivially_move_constructible_v {is_trivially_move_constructible<T>::value};

    template <typename LHS, typename RHS = LHS>
    struct is_trivially_assignable : bool_constant<__is_trivially_assignable(LHS, RHS)> {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto is_trivially_assignable_v {is_trivially_assignable<LHS, RHS>::value};

    template <typename T>
    struct is_trivially_copy_assignable : is_trivially_assignable<T, add_const_reference_t<T>> {};
    template <typename T>
    constexpr inline auto is_trivially_copy_assignable_v {is_trivially_copy_assignable<T>::value};

    template <typename T>
    struct is_trivially_move_assignable : is_trivially_assignable<T, add_rvalue_reference_t<T>> {};
    template <typename T>
    constexpr inline auto is_trivially_move_assignable_v {is_trivially_move_assignable<T>::value};

    template <typename From, typename To>
    struct is_convertible : bool_constant<__is_convertible_to(From, To) and not is_abstract_v<To>> {};
    template <typename From, typename To>
    constexpr inline auto is_convertible_v {is_convertible<From, To>::value};

    template <typename T>
    struct is_trivially_destructible : bool_constant<__is_trivially_destructible(T)> {};
    template <typename T>
    constexpr inline auto is_trivially_destructible_v {is_trivially_destructible<T>::value};

    template <typename T, typename ...Args>
    struct is_constructible : bool_constant<__is_constructible(T, Args...)> {};
    template <typename T>
    constexpr inline auto is_constructible_v {is_constructible<T>::value};

    template <typename T>
    struct is_default_constructible : is_constructible<T> {};
    template <typename T>
    constexpr inline auto is_default_constructible_v {is_default_constructible<T>::value};

    template <typename T>
    struct is_copy_constructible : is_constructible<T, add_const_reference_t<T>> {};
    template <typename T>
    constexpr inline auto is_copy_constructible_v {is_copy_constructible<T>::value};

    template <typename T>
    struct is_move_constructible : is_constructible<T, add_rvalue_reference_t<T>> {};
    template <typename T>
    constexpr inline auto is_move_constructible_v {is_move_constructible<T>::value};

    template <typename T, typename ...Args>
    struct is_list_constructible : decltype(__dsa::test_list_constructible<T, Args...>(0)) {};
    template <typename T, typename ...Args>
    constexpr inline auto is_list_constructible_v {is_list_constructible<T, Args...>::value};

    template <typename LHS, typename RHS = LHS>
    struct is_assignable : bool_constant<__is_assignable(LHS, RHS)> {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto is_assignable_v {is_assignable<LHS, RHS>::value};

    template <typename T>
    struct is_copy_assignable : is_assignable<T, add_const_reference_t<T>> {};
    template <typename T>
    constexpr inline auto is_copy_assignable_v {is_copy_assignable<T>::value};

    template <typename T>
    struct is_move_assignable : is_assignable<T, add_rvalue_reference_t<T>> {};
    template <typename T>
    constexpr inline auto is_move_assignable_v {is_move_assignable<T>::value};

    template <typename T>
    struct is_destructible : conditional_t<
            not is_function_v<T> and not is_unbounded_array_v<T> and not is_same_v<void, T>,
            conditional_t<is_reference_v<T>, true_type, conditional_t<
                    is_complete_v<T>, decltype(__dsa::test_destructible<remove_extents_t<T>>(0)), false_type>
            >, false_type> {};
    template <typename T>
    constexpr inline auto is_destructible_v {is_destructible<T>::value};

    template <typename LHS, typename RHS = LHS>
    struct is_swappable_with : conditional_t<is_void_v<LHS> or is_void_v<RHS>, false_type,
            conditional_t<is_same_v<decltype(__dsa::test_swappable<LHS, RHS>(0)),
                    decltype(__dsa::test_swappable<RHS, LHS>(0))>,
            decltype(__dsa::test_swappable<LHS, RHS>(0)), false_type>> {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto is_swappable_with_v {is_swappable_with<LHS, RHS>::value};

    template <typename T>
    struct is_swappable : is_swappable_with<T, T> {};
    template <typename T>
    constexpr inline auto is_swappable_v {is_swappable<T>::value};

    template <typename, typename ...> struct invoke_result;
    template <typename F, typename ...Args>
    struct is_invocable : __dsa::is_invocable_auxiliary<invoke_result<F, Args...>> {};
    template <typename F, typename ...Args>
    constexpr inline auto is_invocable_v {is_invocable<F, Args...>::value};

    template <typename R, typename F, typename ...Args>
    struct is_invocable_r : conditional_t<is_invocable_v<F, Args...>,
            conditional_t<is_convertible_v<typename invoke_result<F, Args...>::type, R>, true_type, false_type>,
            false_type> {};
    template <typename R, typename F, typename ...Args>
    constexpr inline auto is_invocable_r_v {is_invocable_r<R, F, Args...>::value};

    template <typename From, typename To>
    struct is_static_castable : decltype(__dsa::test_static_castable<From, To>(0)) {};
    template <typename From, typename To>
    constexpr inline auto is_static_castable_v {is_static_castable<From, To>::value};

    template <typename From, typename To>
    struct is_dynamic_castable : decltype(__dsa::test_dynamic_castable<From, To>(0)) {};
    template <typename From, typename To>
    constexpr inline auto is_dynamic_castable_v {is_dynamic_castable<From, To>::value};

    template <typename From, typename To>
    struct is_const_castable : decltype(__dsa::test_const_castable<From, To>(0)) {};
    template <typename From, typename To>
    constexpr inline auto is_const_castable_v {is_const_castable<From, To>::value};

    template <typename From, typename To>
    struct is_reinterpret_castable : decltype(__dsa::test_reinterpret_castable<From, To>(0)) {};
    template <typename From, typename To>
    constexpr inline auto is_reinterpret_castable_v {is_reinterpret_castable<From, To>::value};

    template <typename From, typename To>
    struct is_castable : decltype(__dsa::test_castable<From, To>(0)) {};
    template <typename From, typename To>
    constexpr inline auto is_castable_v {is_castable<From, To>::value};

    template <typename T, typename ...Args>
    struct is_nothrow_constructible : bool_constant<__is_nothrow_constructible(T, Args...)> {};
    template <typename T, typename ...Args>
    constexpr inline auto is_nothrow_constructible_v {is_nothrow_constructible<T, Args...>::value};

    template <typename T>
    struct is_nothrow_default_constructible : is_nothrow_constructible<T> {};
    template <typename T>
    constexpr inline auto is_nothrow_default_constructible_v {is_nothrow_default_constructible<T>::value};

    template <typename T>
    struct is_nothrow_copy_constructible : is_nothrow_constructible<T, add_const_reference_t<T>> {};
    template <typename T>
    constexpr inline auto is_nothrow_copy_constructible_v {is_nothrow_copy_constructible<T>::value};

    template <typename T>
    struct is_nothrow_move_constructible : is_nothrow_constructible<T, add_rvalue_reference_t<T>> {};
    template <typename T>
    constexpr inline auto is_nothrow_move_constructible_v {is_nothrow_move_constructible<T>::value};

    template <typename T, typename ...Args>
    struct is_nothrow_list_constructible :
            decltype(__dsa::test_nothrow_list_constructible<T, Args...>()) {};
    template <typename T, typename ...Args>
    constexpr inline auto is_nothrow_list_constructible_v {is_nothrow_list_constructible<T, Args...>::value};

    template <typename LHS, typename RHS = LHS>
    struct is_nothrow_assignable : bool_constant<__is_nothrow_assignable(LHS, RHS)> {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto is_nothrow_assignable_v {is_nothrow_assignable<LHS, RHS>::value};

    template <typename T>
    struct is_nothrow_copy_assignable : is_nothrow_assignable<T, add_const_reference_t<T>> {};
    template <typename T>
    constexpr inline auto is_nothrow_copy_assignable_v {is_nothrow_copy_assignable<T>::value};

    template <typename T>
    struct is_nothrow_move_assignable : is_nothrow_assignable<T, add_rvalue_reference_t<T>> {};
    template <typename T>
    constexpr inline auto is_nothrow_move_assignable_v {is_nothrow_move_assignable<T>::value};

    template <typename T>
    struct is_nothrow_destructible : decltype(__dsa::test_nothrow_destructible<T>(0)) {};
    template <typename T>
    constexpr inline auto is_nothrow_destructible_v {is_nothrow_destructible<T>::value};

    template <typename LHS, typename RHS = LHS>
    struct is_nothrow_swappable_with : conditional_t<is_swappable_with_v<LHS, RHS>,
            decltype(__dsa::test_nothrow_swappable<LHS, RHS>(0)), false_type> {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto is_nothrow_swappable_with_v {is_nothrow_swappable_with<LHS, RHS>::value};

    template <typename T>
    struct is_nothrow_swappable : is_nothrow_swappable_with<T, T> {};
    template <typename T>
    constexpr inline auto is_nothrow_swappable_v {is_nothrow_swappable<T>::value};

    template <typename Ptr, typename ...Args>
    struct is_nothrow_invocable :
            __dsa::result_of_nothrow_auxiliary<is_member_object_pointer_v<remove_reference_t<Ptr>>,
            is_member_function_pointer_v<remove_reference_t<Ptr>>, Ptr, Args...> {};
    template <typename Ptr, typename ...Args>
    constexpr inline auto is_nothrow_invocable_v {is_nothrow_invocable<Ptr, Args...>::value};

    template <typename From, typename To>
    struct is_nothrow_convertible : conditional_t<is_void_v<From> and is_void_v<To>, true_type,
            conditional_t<is_convertible_v<From, To>,
                    decltype(__dsa::test_nothrow_convertible<To>(declval<From>())), false_type>> {};
    template <typename From, typename To>
    constexpr inline auto is_nothrow_convertible_v {is_nothrow_convertible<From, To>::value};

    template <typename R, typename Ptr, typename ...Args>
    struct is_nothrow_invocable_r : bool_constant<is_nothrow_invocable_v<Ptr, Args...> and
            is_nothrow_convertible_v<typename invoke_result<Ptr, Args...>::type, R>> {};

    template <typename From, typename To>
    struct is_nothrow_static_castable : decltype(__dsa::test_nothrow_static_castable<From, To>(0)) {};
    template <typename From, typename To>
    constexpr inline auto is_nothrow_static_castable_v {is_nothrow_static_castable<From, To>::value};

    template <typename From, typename To>
    struct is_nothrow_dynamic_castable : decltype(__dsa::test_nothrow_dynamic_castable<From, To>(0)) {};
    template <typename From, typename To>
    constexpr inline auto is_nothrow_dynamic_castable_v {is_nothrow_dynamic_castable<From, To>::value};

    template <typename From, typename To>
    struct is_nothrow_const_castable : decltype(__dsa::test_nothrow_const_castable<From, To>(0)) {};
    template <typename From, typename To>
    constexpr inline auto is_nothrow_const_castable_v {is_nothrow_const_castable<From, To>::value};

    template <typename From, typename To>
    struct is_nothrow_reinterpret_castable :
            decltype(__dsa::test_nothrow_reinterpret_castable<From, To>(0)) {};
    template <typename From, typename To>
    constexpr inline auto is_nothrow_reinterpret_castable_v {is_nothrow_reinterpret_castable<From, To>::value};

    template <typename From, typename To>
    struct is_nothrow_castable : decltype(__dsa::test_nothrow_castable<From, To>(0)) {};
    template <typename From, typename To>
    constexpr inline auto is_nothrow_castable_v {is_nothrow_castable<From, To>::value};

    template <typename T>
    struct is_stateless : conditional_t<is_trivially_default_constructible_v<T> and
            is_trivially_copy_constructible_v<T> and is_trivially_assignable_v<T> and
            is_trivially_destructible_v<T> and is_empty_v<T>, true_type, false_type> {};
    template <typename T>
    constexpr inline auto is_stateless_v {is_stateless<T>::value};

    template <typename Base, typename Derived>
    struct is_virtual_base_of : bool_constant<is_base_of_v<Base, Derived> and
            is_castable_v<Derived,  Base> and not is_castable_v<Base, Derived>> {};
    template <typename Base, typename Derived>
    constexpr inline auto is_virtual_base_of_v {is_virtual_base_of<Base, Derived>::value};
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(has something)
namespace data_structure {
    template <typename T>
    struct has_virtual_destructor : conditional_t<__has_virtual_destructor(T), true_type, false_type> {};
    template <typename T>
    constexpr inline auto has_virtual_destructor_v {has_virtual_destructor<T>::value};

    template <typename T>
    struct has_unique_object_representations :
            conditional_t<__has_unique_object_representations(T), true_type, false_type> {};
    template <typename T>
    constexpr inline auto has_unique_object_representations_v {has_unique_object_representations<T>::value};

    template <typename T>
    struct has_swap_member_function : decltype(__dsa::test_swap_memfun<T>(0)) {};
    template <typename T>
    constexpr inline auto has_swap_member_function_v {has_swap_member_function<T>::value};

    template <typename T>
    struct has_nothrow_swap_member_function : decltype(__dsa::test_nothrow_swap_memfun<T>(0)) {};
    template <typename T>
    constexpr inline auto has_nothrow_swap_member_function_v {has_nothrow_swap_member_function<T>::value};

    template <typename T>
    struct has_address_of_operator : decltype(__dsa::test_address_of<T>(0)) {};
    template <typename T>
    constexpr inline auto has_address_of_operator_v {has_address_of_operator<T>::value};

    template <typename T>
    struct has_nothrow_address_of_operator : decltype(__dsa::test_nothrow_address_of<T>(0)) {};
    template <typename T>
    constexpr inline auto has_nothrow_address_of_operator_v {has_nothrow_address_of_operator<T>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_bit_and_operator : decltype(__dsa::test_bit_and<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_bit_and_operator_v {has_bit_and_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_bit_and_operator : decltype(__dsa::test_nothrow_bit_and<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_nothrow_bit_and_operator_v {has_nothrow_bit_and_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_bit_and_assignment_operator : decltype(__dsa::test_bit_and_assignment<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_bit_and_assignment_operator_v {has_bit_and_assignment_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_bit_and_assignment_operator :
            decltype(__dsa::test_nothrow_bit_and_assignment<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_nothrow_bit_and_assignment_operator_v {
        has_nothrow_bit_and_assignment_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_bit_or_operator : decltype(__dsa::test_bit_or<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_bit_or_operator_v {has_bit_or_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_bit_or_operator : decltype(__dsa::test_nothrow_bit_or<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_nothrow_bit_or_operator_v {has_nothrow_bit_or_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_bit_or_assignment_operator : decltype(__dsa::test_bit_or_assignment<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_bit_or_assignment_operator_v {has_bit_or_assignment_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_bit_or_assignment_operator :
            decltype(__dsa::test_nothrow_bit_or_assignment<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_nothrow_bit_or_assignment_operator_v {
        has_nothrow_bit_or_assignment_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_bit_xor_operator : decltype(__dsa::test_bit_xor<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_bit_xor_operator_v {has_bit_xor_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_bit_xor_operator : decltype(__dsa::test_nothrow_bit_xor<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_nothrow_bit_xor_operator_v {has_nothrow_bit_xor_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_bit_xor_assignment_operator : decltype(__dsa::test_bit_xor_assignment<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_bit_xor_assignment_operator_v {has_bit_xor_assignment_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_bit_xor_assignment_operator :
            decltype(__dsa::test_nothrow_bit_xor_assignment<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_nothrow_bit_xor_assignment_operator_v {
        has_nothrow_bit_xor_assignment_operator<LHS, RHS>::value};

    template <typename T>
    struct has_complement_operator : decltype(__dsa::test_complement<T>(0)) {};
    template <typename T>
    constexpr inline auto has_complement_operator_v {has_complement_operator<T>::value};

    template <typename T>
    struct has_nothrow_complement_operator : decltype(__dsa::test_nothrow_complement<T>(0)) {};
    template <typename T>
    constexpr inline auto has_nothrow_complement_operator_v {has_nothrow_complement_operator<T>::value};

    template <typename T>
    struct has_dereference_operator : decltype(__dsa::test_dereference<T>(0)) {};
    template <typename T>
    constexpr inline auto has_dereference_operator_v {has_dereference_operator<T>::value};

    template <typename T>
    struct has_nothrow_dereference_operator : decltype(__dsa::test_nothrow_dereference<T>(0)) {};
    template <typename T>
    constexpr inline auto has_nothrow_dereference_operator_v {has_nothrow_dereference_operator<T>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_divide_operator : decltype(__dsa::test_divide<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_divide_operator_v {has_divide_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_divide_operator : decltype(__dsa::test_nothrow_divide<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_nothrow_divide_operator_v {has_nothrow_divide_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_divide_assignment_operator : decltype(__dsa::test_divide_assignment<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_divide_assignment_operator_v {has_divide_assignment_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_divide_assignment_operator :
            decltype(__dsa::test_nothrow_divide_assignment<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_nothrow_divide_assignment_operator_v {
        has_nothrow_divide_assignment_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_equal_to_operator : decltype(__dsa::test_equal_to<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_equal_to_operator_v {has_equal_to_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_equal_to_operator : decltype(__dsa::test_nothrow_equal_to<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_nothrow_equal_to_operator_v {has_nothrow_equal_to_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_greater_operator : decltype(__dsa::test_greater<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_greater_operator_v {has_greater_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_greater_operator : decltype(__dsa::test_nothrow_greater<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_nothrow_greater_operator_v {has_nothrow_greater_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_greater_equal_to_operator : decltype(__dsa::test_greater_equal_to<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_greater_equal_to_operator_v {has_greater_equal_to_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_greater_equal_to_operator :
            decltype(__dsa::test_nothrow_greater_equal_to<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_nothrow_greater_equal_to_operator_v {
        has_nothrow_greater_equal_to_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_left_shift_operator : decltype(__dsa::test_left_shift<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_left_shift_operator_v {has_left_shift_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_left_shift_operator : decltype(__dsa::test_nothrow_left_shift<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_nothrow_left_shift_operator_v {has_nothrow_left_shift_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_left_shift_assignment_operator : decltype(__dsa::test_left_shift_assignment<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_left_shift_assignment_operator_v {
        has_left_shift_assignment_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_left_shift_assignment_operator :
            decltype(__dsa::test_nothrow_left_shift_assignment<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_nothrow_left_shift_assignment_operator_v {
        has_nothrow_left_shift_assignment_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_right_shift_operator : decltype(__dsa::test_right_shift<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_right_shift_operator_v {has_right_shift_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_right_shift_operator : decltype(__dsa::test_nothrow_right_shift<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_nothrow_right_shift_operator_v {
        has_nothrow_right_shift_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_right_shift_assignment_operator :
            decltype(__dsa::test_right_shift_assignment<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_right_shift_assignment_operator_v {
        has_right_shift_assignment_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_right_shift_assignment_operator :
            decltype(__dsa::test_nothrow_right_shift_assignment<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_nothrow_right_shift_assignment_operator_v {
        has_nothrow_right_shift_assignment_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_less_operator : decltype(__dsa::test_less<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_less_operator_v {has_less_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_less_operator : decltype(__dsa::test_nothrow_less<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_nothrow_less_operator_v {has_nothrow_less_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_less_equal_to_operator : decltype(__dsa::test_less_equal_to<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_less_equal_to_operator_v {has_less_equal_to_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_less_equal_to_operator :
            decltype(__dsa::test_nothrow_less_equal_to<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_nothrow_less_equal_to_operator_v {
        has_nothrow_less_equal_to_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_logical_and_operator : decltype(__dsa::test_logical_and<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_logical_and_operator_v {has_logical_and_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_logical_and_operator : decltype(__dsa::test_nothrow_logical_and<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_nothrow_logical_and_operator_v {
        has_nothrow_logical_and_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_logical_or_operator : decltype(__dsa::test_logical_or<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_logical_or_operator_v {has_logical_or_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_logical_or_operator : decltype(__dsa::test_nothrow_logical_or<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_nothrow_logical_or_operator_v {
        has_nothrow_logical_or_operator<LHS, RHS>::value};

    template <typename T>
    struct has_logical_not_operator : decltype(__dsa::test_logical_not<T>(0)) {};
    template <typename T>
    constexpr inline auto has_logical_not_operator_v {has_logical_not_operator<T>::value};

    template <typename T>
    struct has_nothrow_logical_not_operator : decltype(__dsa::test_nothrow_logical_not<T>(0)) {};
    template <typename T>
    constexpr inline auto has_nothrow_logical_not_operator_v {has_nothrow_logical_not_operator<T>::value};

    template <typename T>
    struct has_unary_minus_operator : decltype(__dsa::test_unary_minus<T>(0)) {};
    template <typename T>
    constexpr inline auto has_unary_minus_operator_v {has_unary_minus_operator<T>::value};

    template <typename T>
    struct has_nothrow_unary_minus_operator : decltype(__dsa::test_nothrow_unary_minus<T>(0)) {};
    template <typename T>
    constexpr inline auto has_nothrow_unary_minus_operator_v {has_nothrow_unary_minus_operator<T>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_minus_operator : decltype(__dsa::test_minus<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_minus_operator_v {has_minus_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_minus_operator :
            decltype(__dsa::test_nothrow_minus<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_nothrow_minus_operator_v {
        has_nothrow_minus_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_minus_assignment_operator : decltype(__dsa::test_minus_assignment<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_minus_assignment_operator_v {has_minus_assignment_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_minus_assignment_operator :
            decltype(__dsa::test_nothrow_minus_assignment<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_nothrow_minus_assignment_operator_v {
        has_nothrow_minus_assignment_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_modules_operator : decltype(__dsa::test_modules<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_modules_operator_v {has_modules_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_modules_operator : decltype(__dsa::test_nothrow_modules<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_nothrow_modules_operator_v {has_nothrow_modules_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_modules_assignment_operator : decltype(__dsa::test_modules_assignment<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_modules_assignment_operator_v {
        has_modules_assignment_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_modules_assignment_operator :
            decltype(__dsa::test_nothrow_modules_assignment<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_nothrow_modules_assignment_operator_v {
        has_nothrow_modules_assignment_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_multiply_operator : decltype(__dsa::test_multiply<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_multiply_operator_v {has_multiply_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_multiply_operator : decltype(__dsa::test_nothrow_multiply<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_nothrow_multiply_operator_v {has_nothrow_multiply_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_multiply_assignment_operator : decltype(__dsa::test_multiply_assignment<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_multiply_assignment_operator_v {
        has_multiply_assignment_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_multiply_assignment_operator :
            decltype(__dsa::test_nothrow_multiply_assignment<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_nothrow_multiply_assignment_operator_v {
        has_nothrow_multiply_assignment_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_three_way_operator : decltype(__dsa::test_three_way<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_three_way_operator_v {has_three_way_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_three_way_operator : decltype(__dsa::test_nothrow_three_way<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_nothrow_three_way_operator_v {has_nothrow_three_way_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_not_equal_to_operator : decltype(__dsa::test_not_equal_to<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_not_equal_to_operator_v {has_not_equal_to_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_not_equal_to_operator : decltype(__dsa::test_nothrow_not_equal_to<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_nothrow_not_equal_to_operator_v {
        has_nothrow_not_equal_to_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_plus_operator : decltype(__dsa::test_plus<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_plus_operator_v {has_plus_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_plus_operator : decltype(__dsa::test_nothrow_plus<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_nothrow_plus_operator_v {has_nothrow_plus_operator<LHS, RHS>::value};

    template <typename T>
    struct has_unary_plus_operator : decltype(__dsa::test_unary_plus<T>(0)) {};
    template <typename T>
    constexpr inline auto has_unary_plus_operator_v {has_unary_plus_operator<T>::value};

    template <typename T>
    struct has_nothrow_unary_plus_operator : decltype(__dsa::test_nothrow_unary_plus<T>(0)) {};
    template <typename T>
    constexpr inline auto has_nothrow_unary_plus_operator_v {has_nothrow_unary_plus_operator<T>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_plus_assignment_operator : decltype(__dsa::test_plus_assignment<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_plus_assignment_operator_v {has_plus_assignment_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_plus_assignment_operator :
            decltype(__dsa::test_nothrow_plus_assignment<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_nothrow_plus_assignment_operator_v {
        has_nothrow_plus_assignment_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_subscript_operator : decltype(__dsa::test_subscript<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_subscript_operator_v {has_subscript_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_subscript_operator : decltype(__dsa::test_nothrow_subscript<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_nothrow_subscript_operator_v {has_nothrow_subscript_operator<LHS, RHS>::value};

    template <typename T>
    struct has_pre_increment_operator : decltype(__dsa::test_pre_increment<T>(0)) {};
    template <typename T>
    constexpr inline auto has_pre_increment_operator_v {has_pre_increment_operator<T>::value};

    template <typename T>
    struct has_nothrow_pre_increment_operator : decltype(__dsa::test_nothrow_pre_increment<T>(0)) {};
    template <typename T>
    constexpr inline auto has_nothrow_pre_increment_operator_v {has_nothrow_pre_increment_operator<T>::value};

    template <typename T>
    struct has_post_increment_operator : decltype(__dsa::test_post_increment<T>(0)) {};
    template <typename T>
    constexpr inline auto has_post_increment_operator_v {has_post_increment_operator<T>::value};

    template <typename T>
    struct has_nothrow_post_increment_operator : decltype(__dsa::test_nothrow_post_increment<T>(0)) {};
    template <typename T>
    constexpr inline auto has_nothrow_post_increment_operator_v {has_nothrow_post_increment_operator<T>::value};

    template <typename T>
    struct has_pre_decrement_operator : decltype(__dsa::test_pre_decrement<T>(0)) {};
    template <typename T>
    constexpr inline auto has_pre_decrement_operator_v {has_pre_decrement_operator<T>::value};

    template <typename T>
    struct has_nothrow_pre_decrement_operator : decltype(__dsa::test_nothrow_pre_decrement<T>(0)) {};
    template <typename T>
    constexpr inline auto has_nothrow_pre_decrement_operator_v {has_nothrow_pre_decrement_operator<T>::value};

    template <typename T>
    struct has_post_decrement_operator : decltype(__dsa::test_post_decrement<T>(0)) {};
    template <typename T>
    constexpr inline auto has_post_decrement_operator_v {has_post_decrement_operator<T>::value};

    template <typename T>
    struct has_nothrow_post_decrement_operator : decltype(__dsa::test_nothrow_post_decrement<T>(0)) {};
    template <typename T>
    constexpr inline auto has_nothrow_post_decrement_operator_v {has_nothrow_post_decrement_operator<T>::value};

    template <typename T>
    struct has_member_access_by_pointer_operator :
            decltype(__dsa::test_member_access_by_pointer<T>(0)) {};
    template <typename T>
    constexpr inline auto has_member_access_by_pointer_operator_v {
        has_member_access_by_pointer_operator<T>::value};

    template <typename T>
    struct has_nothrow_member_access_by_pointer_operator :
            decltype(__dsa::test_nothrow_member_access_by_pointer<T>(0)) {};
    template <typename T>
    constexpr inline auto has_nothrow_member_access_by_pointer_operator_v {
        has_nothrow_member_access_by_pointer_operator<T>::value};

    template <typename T>
    struct has_member_access_by_pointer_dereference_operator :
            decltype(__dsa::test_member_access_by_pointer_dereference<T>(0)) {};
    template <typename T>
    constexpr inline auto has_member_access_by_pointer_dereference_operator_v {
        has_member_access_by_pointer_dereference_operator<T>::value};

    template <typename T>
    struct has_nothrow_member_access_by_pointer_dereference_operator :
            decltype(__dsa::test_nothrow_member_access_by_pointer_dereference<T>(0)) {};
    template <typename T>
    constexpr inline auto has_nothrow_member_access_by_pointer_dereference_operator_v {
        has_nothrow_member_access_by_pointer_dereference_operator<T>::value};

    template <typename T, typename ...Args>
    struct has_new_operator : decltype(__dsa::test_new_operator<T, Args...>(0)) {};
    template <typename T, typename ...Args>
    constexpr inline auto has_new_operator_v {has_new_operator<T, Args...>::value};

    template <typename T, typename ...Args>
    struct has_nothrow_new_operator : decltype(__dsa::test_nothrow_new_operator<T, Args...>(0)) {};
    template <typename T, typename ...Args>
    constexpr inline auto has_nothrow_new_operator_v {has_nothrow_new_operator<T, Args...>::value};

    template <typename T, typename ...Args>
    struct has_new_array_operator : decltype(__dsa::test_new_array_operator<T, Args...>(0)) {};
    template <typename T, typename ...Args>
    constexpr inline auto has_new_array_operator_v {has_new_array_operator<T, Args...>::value};

    template <typename T, typename ...Args>
    struct has_nothrow_new_array_operator : decltype(__dsa::test_nothrow_new_array_operator<T, Args...>(0)) {};
    template <typename T, typename ...Args>
    constexpr inline auto has_nothrow_new_array_operator_v {has_nothrow_new_array_operator<T, Args...>::value};

    template <typename T, typename ...Args>
    struct has_delete_operator : decltype(__dsa::test_delete_operator<T, Args...>(0)) {};
    template <typename T, typename ...Args>
    constexpr inline auto has_delete_operator_v {has_delete_operator<T, Args...>::value};

    template <typename T, typename ...Args>
    struct has_nothrow_delete_operator : decltype(__dsa::test_nothrow_delete_operator<T, Args...>(0)) {};
    template <typename T, typename ...Args>
    constexpr inline auto has_nothrow_delete_operator_v {has_nothrow_delete_operator<T, Args...>::value};

    template <typename T, typename ...Args>
    struct has_delete_array_operator : decltype(__dsa::test_delete_array_operator<T, Args...>(0)) {};
    template <typename T, typename ...Args>
    constexpr inline auto has_delete_array_operator_v {has_delete_array_operator<T, Args...>::value};

    template <typename T, typename ...Args>
    struct has_nothrow_delete_array_operator :
            decltype(__dsa::test_nothrow_delete_array_operator<T, Args...>(0)) {};
    template <typename T, typename ...Args>
    constexpr inline auto has_nothrow_delete_array_operator_v {
        has_nothrow_delete_array_operator<T, Args...>::value};

    template <typename T, typename ...Args>
    struct has_function_call_operator : decltype(__dsa::test_function_call<T, Args...>(0)) {};
    template <typename T, typename ...Args>
    constexpr inline auto has_function_call_operator_v {has_function_call_operator<T, Args...>::value};

    template <typename T, typename ...Args>
    struct has_nothrow_function_call_operator :
            decltype(__dsa::test_nothrow_function_call<T, Args...>(0)) {};
    template <typename T, typename ...Args>
    constexpr inline auto has_nothrow_function_call_operator_v {
        has_nothrow_function_call_operator<T, Args...>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_comma_operator : decltype(__dsa::test_comma<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_comma_operator_v {has_comma_operator<LHS, RHS>::value};

    template <typename LHS, typename RHS = LHS>
    struct has_nothrow_comma_operator : decltype(__dsa::test_nothrow_comma<LHS, RHS>(0)) {};
    template <typename LHS, typename RHS = LHS>
    constexpr inline auto has_nothrow_comma_operator_v {has_nothrow_comma_operator<LHS, RHS>::value};
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(copy something)
namespace data_structure {
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
        using type = conditional_t<is_rvalue_reference_v<Original>, add_rvalue_reference_t<To>, To>;
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

    template <typename Original, typename To>
    struct copy_const_reference {
        using type = conditional_t<is_const_reference_v<Original>, add_const_reference_t<To>, To>;
    };
    template <typename Original, typename To>
    using copy_const_reference_t = typename copy_const_reference<Original, To>::type;

    template <typename Original, typename To>
    struct copy_cvref {
        using type = copy_cv_t<Original, copy_reference_t<Original, To>>;
    };
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(other auxliary)
namespace data_structure {
    template <typename> struct decay;
    template <typename ...> struct common_type;
    template <typename> struct alignment_of;
    namespace __data_structure_auxiliary {
        using signed_integral = type_container<signed char, signed short, signed int, signed long,
        signed long long, __int128_t>;
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
            using next_type = typename Container::remaining;
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
                    __int128_t, typename promotion_index<T, signed_integral>::type::remaining::type>;
        };
        template <typename T>
        struct integral_promotion_auxiliary<T, enable_if_t<is_unsigned_v<T>>> {
            using type = conditional_t<
                    is_same_v<typename promotion_index<T, unsigned_integral>::type::type, __uint128_t>,
                    __uint128_t, typename promotion_index<T, unsigned_integral>::type::remaining::type>;
        };

        template <typename T, typename = void>
        struct floating_point_promotion_auxiliary {
            static_assert(is_floating_point_v<T>, "The trait requires a floating point type!");
        };
        template <typename T>
        struct floating_point_promotion_auxiliary<T, enable_if_t<is_floating_point_v<T>>> {
            using type = conditional_t<
                    is_same_v<typename promotion_index<T, floating_point>::type::type, long double>,
                    long double, typename promotion_index<T, floating_point>::type::remaining::type>;
        };

        template <typename T, typename = void>
        struct character_promotion_auxiliary {
            static_assert(is_character_v<T>, "The trait requires a character type!");
        };
        template <typename T>
        struct character_promotion_auxiliary<T, enable_if_t<is_character_v<T>>> {
            using type = conditional_t<
                    is_same_v<typename promotion_index<T, character>::type::type, char32_t>,
                    char32_t, typename promotion_index<T, character>::type::remaining::type>;
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
            constexpr static auto min {Align1 < Align2 ? Align1 : Align2};
            constexpr static auto max {Align1 < Align2 ? Align2 : Align1};
        public:
            constexpr static auto value {Length < max ? min : max};
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
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(other)
namespace data_structure {
    template <typename T>
    struct size_of : constant<size_t, sizeof(T)> {};
    template <typename T>
    constexpr inline auto size_of_v {sizeof(T)};

    template <typename T>
    struct alignment_of : constant<size_t, alignof(T)> {};
    template <typename T>
    constexpr inline auto alignment_of_v {alignof(T)};

    template <typename T>
    struct rank : constant<size_t, 0> {};
    template <typename T>
    constexpr inline auto rank_v {rank<T>::value};
    template <typename T>
    struct rank<T []> : constant<size_t, rank_v<T> + 1> {};
    template <typename T, size_t N>
    struct rank<T [N]> : constant<size_t, rank_v<T> + 1> {};

    template <typename T, size_t = 0>
    struct extent : constant<size_t, 0> {};
    template <typename T>
    struct extent<T [], 0> : constant<size_t, 0> {};
    template <typename T, size_t N>
    struct extent<T [], N> : extent<T, N - 1> {};
    template <typename T, size_t Size>
    struct extent<T [Size], 0> : constant<size_t, Size> {};
    template <typename T, size_t Size, size_t N>
    struct extent<T [Size], N> : extent<T, N - 1> {};
    template <typename T, size_t N>
    constexpr inline auto extent_v {extent<T, N>::value};

    template <typename T>
    struct decay {
        using type = conditional_t<is_array_v<remove_reference_t<T>>,
                add_pointer_t<remove_extent_t<remove_reference_t<T>>>,
                conditional_t<is_function_v<remove_reference_t<T>>, add_pointer_t<remove_reference_t<T>>,
                        remove_cv_t<remove_reference_t<T>>>>;
    };
    template <typename T>
    using decay_t = typename decay<T>::type;

    template <typename T>
    struct underlying_type {
        using type = __underlying_type(T);
    };
    template <typename T>
    using underlying_type_t = typename underlying_type<T>::type;

    template <typename ...>
    struct common_type {};
    template <typename ...Ts>
    using common_type_t = typename common_type<Ts...>::type;
    template <typename T>
    struct common_type<T> {
        using type = common_type_t<T, T>;
    };
    template <typename T, typename U>
    struct common_type<T, U> {
        using type = decltype(make_true<T, U> ? declval<decay_t<T>>() : declval<decay_t<U>>());
    };
    template <typename T, typename U, typename V, typename ...Ts>
    struct common_type<T, U, V, Ts...> : common_type<common_type_t<T, U>, V, Ts...> {};

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
                signed char, typename __dsa::signed_integral::remaining>::type>;
    };
    template <typename T>
    using make_signed_t = typename make_signed<T>::type;
    template <typename T>
    struct make_unsigned {
        using type = copy_cv_t<T, typename __dsa::make_signed_or_unsigned_auxiliary<remove_cv_t<T>,
                unsigned char, typename __dsa::unsigned_integral::remaining>::type>;
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
    /* TODO : refactor it by modules in C++ 20 */
    #define class_template_traits_t(type, trait_name) typename ds::class_template_traits<type>::trait_name

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
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(undefine useless macros)
#undef __DATA_STRUCTURE_TEST_ADDITION
#undef __DATA_STRUCTURE_REMOVE_CV_HELPER_MAIN
#undef __DATA_STRUCTURE_REMOVE_CV_HELPER_SPECIALIZATION
#undef __DATA_STRUCTURE_TEST_OPERATION
#undef __DATA_STRUCTURE_HAS_NESTED_TYPE_IMPL
#undef __DATA_STRUCTURE_TEST_OPERATION_NOTHROW
__DATA_STRUCTURE_END

#endif //DATA_STRUCTURE_TYPE_TRAITS_HPP
