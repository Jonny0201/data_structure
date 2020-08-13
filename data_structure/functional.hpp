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

#ifndef DATA_STRUCTURE_FUNCTIONAL_HPP
#define DATA_STRUCTURE_FUNCTIONAL_HPP

#include "utility.hpp"
#include "memory.hpp"

namespace data_structure {
    template <typename T>
    struct function_traits;
    template <typename R, typename ...Args>
    struct function_traits<R (Args...)> {
        using returning_type = R;
        using class_type = void;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = false_type;
        using is_nothrow = false_type;
        using has_const_qualifier = false_type;
        using has_volatile_qualifier = false_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = false_type;
        using has_rvalue_reference_qualifer = false_type;
        using has_reference_qualifier = false_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args..., ...)> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = true_type;
        using is_nothrow = false_type;
        using has_const_qualifier = false_type;
        using has_volatile_qualifier = false_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = false_type;
        using has_rvalue_reference_qualifer = false_type;
        using has_reference_qualifier = false_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args...) const> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = false_type;
        using is_nothrow = false_type;
        using has_const_qualifier = true_type;
        using has_volatile_qualifier = false_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = false_type;
        using has_rvalue_reference_qualifer = false_type;
        using has_reference_qualifier = false_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args...) volatile> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = false_type;
        using is_nothrow = false_type;
        using has_const_qualifier = false_type;
        using has_volatile_qualifier = true_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = false_type;
        using has_rvalue_reference_qualifer = false_type;
        using has_reference_qualifier = false_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args...) const volatile> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = false_type;
        using is_nothrow = false_type;
        using has_const_qualifier = true_type;
        using has_volatile_qualifier = true_type;
        using has_cv_qualifer = true_type;
        using has_lvalue_reference_qualifer = false_type;
        using has_rvalue_reference_qualifer = false_type;
        using has_reference_qualifier = false_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args..., ...) const> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = true_type;
        using is_nothrow = false_type;
        using has_const_qualifier = true_type;
        using has_volatile_qualifier = false_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = false_type;
        using has_rvalue_reference_qualifer = false_type;
        using has_reference_qualifier = false_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args..., ...) volatile> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = true_type;
        using is_nothrow = false_type;
        using has_const_qualifier = false_type;
        using has_volatile_qualifier = true_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = false_type;
        using has_rvalue_reference_qualifer = false_type;
        using has_reference_qualifier = false_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args..., ...) const volatile> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = true_type;
        using is_nothrow = false_type;
        using has_const_qualifier = true_type;
        using has_volatile_qualifier = true_type;
        using has_cv_qualifer = true_type;
        using has_lvalue_reference_qualifer = false_type;
        using has_rvalue_reference_qualifer = false_type;
        using has_reference_qualifier = false_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args...) &> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = false_type;
        using is_nothrow = false_type;
        using has_const_qualifier = false_type;
        using has_volatile_qualifier = false_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = true_type;
        using has_rvalue_reference_qualifer = false_type;
        using has_reference_qualifier = true_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args...) const &> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = false_type;
        using is_nothrow = false_type;
        using has_const_qualifier = true_type;
        using has_volatile_qualifier = false_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = true_type;
        using has_rvalue_reference_qualifer = false_type;
        using has_reference_qualifier = true_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args...) volatile &> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = false_type;
        using is_nothrow = false_type;
        using has_const_qualifier = false_type;
        using has_volatile_qualifier = true_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = false_type;
        using has_rvalue_reference_qualifer = true_type;
        using has_reference_qualifier = true_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args...) const volatile &> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = false_type;
        using is_nothrow = false_type;
        using has_const_qualifier = true_type;
        using has_volatile_qualifier = true_type;
        using has_cv_qualifer = true_type;
        using has_lvalue_reference_qualifer = true_type;
        using has_rvalue_reference_qualifer = false_type;
        using has_reference_qualifier = true_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args..., ...) &> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = true_type;
        using is_nothrow = false_type;
        using has_const_qualifier = false_type;
        using has_volatile_qualifier = false_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = true_type;
        using has_rvalue_reference_qualifer = false_type;
        using has_reference_qualifier = true_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args..., ...) const &> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = true_type;
        using is_nothrow = false_type;
        using has_const_qualifier = true_type;
        using has_volatile_qualifier = false_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = true_type;
        using has_rvalue_reference_qualifer = false_type;
        using has_reference_qualifier = true_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args..., ...) volatile &> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = true_type;
        using is_nothrow = false_type;
        using has_const_qualifier = false_type;
        using has_volatile_qualifier = true_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = true_type;
        using has_rvalue_reference_qualifer = false_type;
        using has_reference_qualifier = true_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args..., ...) const volatile &> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = true_type;
        using is_nothrow = false_type;
        using has_const_qualifier = true_type;
        using has_volatile_qualifier = true_type;
        using has_cv_qualifer = true_type;
        using has_lvalue_reference_qualifer = true_type;
        using has_rvalue_reference_qualifer = false_type;
        using has_reference_qualifier = true_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args...) &&> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = false_type;
        using is_nothrow = false_type;
        using has_const_qualifier = false_type;
        using has_volatile_qualifier = false_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = false_type;
        using has_rvalue_reference_qualifer = true_type;
        using has_reference_qualifier = true_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args...) const &&> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = false_type;
        using is_nothrow = false_type;
        using has_const_qualifier = true_type;
        using has_volatile_qualifier = false_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = false_type;
        using has_rvalue_reference_qualifer = true_type;
        using has_reference_qualifier = true_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args...) volatile &&> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = false_type;
        using is_nothrow = false_type;
        using has_const_qualifier = false_type;
        using has_volatile_qualifier = true_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = false_type;
        using has_rvalue_reference_qualifer = true_type;
        using has_reference_qualifier = true_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args...) const volatile &&> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = false_type;
        using is_nothrow = false_type;
        using has_const_qualifier = true_type;
        using has_volatile_qualifier = true_type;
        using has_cv_qualifer = true_type;
        using has_lvalue_reference_qualifer = false_type;
        using has_rvalue_reference_qualifer = true_type;
        using has_reference_qualifier = true_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args..., ...) &&> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = true_type;
        using is_nothrow = false_type;
        using has_const_qualifier = false_type;
        using has_volatile_qualifier = false_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = false_type;
        using has_rvalue_reference_qualifer = true_type;
        using has_reference_qualifier = true_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args..., ...) const &&> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = true_type;
        using is_nothrow = false_type;
        using has_const_qualifier = true_type;
        using has_volatile_qualifier = false_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = false_type;
        using has_rvalue_reference_qualifer = true_type;
        using has_reference_qualifier = true_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args..., ...) volatile &&> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = true_type;
        using is_nothrow = false_type;
        using has_const_qualifier = false_type;
        using has_volatile_qualifier = true_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = false_type;
        using has_rvalue_reference_qualifer = true_type;
        using has_reference_qualifier = true_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args..., ...) const volatile &&> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = true_type;
        using is_nothrow = false_type;
        using has_const_qualifier = true_type;
        using has_volatile_qualifier = true_type;
        using has_cv_qualifer = true_type;
        using has_lvalue_reference_qualifer = false_type;
        using has_rvalue_reference_qualifer = true_type;
        using has_reference_qualifier = true_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args...) noexcept> {
        using returning_type = R;
        using class_type = void;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = false_type;
        using is_nothrow = true_type;
        using has_const_qualifier = false_type;
        using has_volatile_qualifier = false_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = false_type;
        using has_rvalue_reference_qualifer = false_type;
        using has_reference_qualifier = false_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args..., ...) noexcept> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = true_type;
        using is_nothrow = true_type;
        using has_const_qualifier = false_type;
        using has_volatile_qualifier = false_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = false_type;
        using has_rvalue_reference_qualifer = false_type;
        using has_reference_qualifier = false_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args...) const noexcept> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = false_type;
        using is_nothrow = true_type;
        using has_const_qualifier = true_type;
        using has_volatile_qualifier = false_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = false_type;
        using has_rvalue_reference_qualifer = false_type;
        using has_reference_qualifier = false_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args...) volatile noexcept> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = false_type;
        using is_nothrow = true_type;
        using has_const_qualifier = false_type;
        using has_volatile_qualifier = true_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = false_type;
        using has_rvalue_reference_qualifer = false_type;
        using has_reference_qualifier = false_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args...) const volatile noexcept> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = false_type;
        using is_nothrow = true_type;
        using has_const_qualifier = true_type;
        using has_volatile_qualifier = true_type;
        using has_cv_qualifer = true_type;
        using has_lvalue_reference_qualifer = false_type;
        using has_rvalue_reference_qualifer = false_type;
        using has_reference_qualifier = false_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args..., ...) const noexcept> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = true_type;
        using is_nothrow = true_type;
        using has_const_qualifier = true_type;
        using has_volatile_qualifier = false_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = false_type;
        using has_rvalue_reference_qualifer = false_type;
        using has_reference_qualifier = false_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args..., ...) volatile noexcept> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = true_type;
        using is_nothrow = true_type;
        using has_const_qualifier = false_type;
        using has_volatile_qualifier = true_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = false_type;
        using has_rvalue_reference_qualifer = false_type;
        using has_reference_qualifier = false_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args..., ...) const volatile noexcept> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = true_type;
        using is_nothrow = true_type;
        using has_const_qualifier = true_type;
        using has_volatile_qualifier = true_type;
        using has_cv_qualifer = true_type;
        using has_lvalue_reference_qualifer = false_type;
        using has_rvalue_reference_qualifer = false_type;
        using has_reference_qualifier = false_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args...) & noexcept> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = false_type;
        using is_nothrow = true_type;
        using has_const_qualifier = false_type;
        using has_volatile_qualifier = false_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = true_type;
        using has_rvalue_reference_qualifer = false_type;
        using has_reference_qualifier = true_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args...) const & noexcept> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = false_type;
        using is_nothrow = true_type;
        using has_const_qualifier = true_type;
        using has_volatile_qualifier = false_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = true_type;
        using has_rvalue_reference_qualifer = false_type;
        using has_reference_qualifier = true_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args...) volatile & noexcept> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = false_type;
        using is_nothrow = true_type;
        using has_const_qualifier = false_type;
        using has_volatile_qualifier = true_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = false_type;
        using has_rvalue_reference_qualifer = true_type;
        using has_reference_qualifier = true_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args...) const volatile & noexcept> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = false_type;
        using is_nothrow = true_type;
        using has_const_qualifier = true_type;
        using has_volatile_qualifier = true_type;
        using has_cv_qualifer = true_type;
        using has_lvalue_reference_qualifer = true_type;
        using has_rvalue_reference_qualifer = false_type;
        using has_reference_qualifier = true_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args..., ...) & noexcept> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = true_type;
        using is_nothrow = true_type;
        using has_const_qualifier = false_type;
        using has_volatile_qualifier = false_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = true_type;
        using has_rvalue_reference_qualifer = false_type;
        using has_reference_qualifier = true_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args..., ...) const & noexcept> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = true_type;
        using is_nothrow = true_type;
        using has_const_qualifier = true_type;
        using has_volatile_qualifier = false_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = true_type;
        using has_rvalue_reference_qualifer = false_type;
        using has_reference_qualifier = true_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args..., ...) volatile & noexcept> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = true_type;
        using is_nothrow = true_type;
        using has_const_qualifier = false_type;
        using has_volatile_qualifier = true_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = true_type;
        using has_rvalue_reference_qualifer = false_type;
        using has_reference_qualifier = true_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args..., ...) const volatile & noexcept> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = true_type;
        using is_nothrow = true_type;
        using has_const_qualifier = true_type;
        using has_volatile_qualifier = true_type;
        using has_cv_qualifer = true_type;
        using has_lvalue_reference_qualifer = true_type;
        using has_rvalue_reference_qualifer = false_type;
        using has_reference_qualifier = true_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args...) && noexcept> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = false_type;
        using is_nothrow = true_type;
        using has_const_qualifier = false_type;
        using has_volatile_qualifier = false_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = false_type;
        using has_rvalue_reference_qualifer = true_type;
        using has_reference_qualifier = true_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args...) const && noexcept> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = false_type;
        using is_nothrow = true_type;
        using has_const_qualifier = true_type;
        using has_volatile_qualifier = false_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = false_type;
        using has_rvalue_reference_qualifer = true_type;
        using has_reference_qualifier = true_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args...) volatile && noexcept> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = false_type;
        using is_nothrow = true_type;
        using has_const_qualifier = false_type;
        using has_volatile_qualifier = true_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = false_type;
        using has_rvalue_reference_qualifer = true_type;
        using has_reference_qualifier = true_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args...) const volatile && noexcept> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = false_type;
        using is_nothrow = true_type;
        using has_const_qualifier = true_type;
        using has_volatile_qualifier = true_type;
        using has_cv_qualifer = true_type;
        using has_lvalue_reference_qualifer = false_type;
        using has_rvalue_reference_qualifer = true_type;
        using has_reference_qualifier = true_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args..., ...) && noexcept> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = true_type;
        using is_nothrow = true_type;
        using has_const_qualifier = false_type;
        using has_volatile_qualifier = false_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = false_type;
        using has_rvalue_reference_qualifer = true_type;
        using has_reference_qualifier = true_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args..., ...) const && noexcept> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = true_type;
        using is_nothrow = true_type;
        using has_const_qualifier = true_type;
        using has_volatile_qualifier = false_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = false_type;
        using has_rvalue_reference_qualifer = true_type;
        using has_reference_qualifier = true_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args..., ...) volatile && noexcept> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = true_type;
        using is_nothrow = true_type;
        using has_const_qualifier = false_type;
        using has_volatile_qualifier = true_type;
        using has_cv_qualifer = false_type;
        using has_lvalue_reference_qualifer = false_type;
        using has_rvalue_reference_qualifer = true_type;
        using has_reference_qualifier = true_type;
    };
    template <typename R, typename ...Args>
    struct function_traits<R (Args..., ...) const volatile && noexcept> {
        using returning_type = R;
        using parameter_list = type_container<Args...>;
        using is_c_style_variable_parameter = true_type;
        using is_nothrow = true_type;
        using has_const_qualifier = true_type;
        using has_volatile_qualifier = true_type;
        using has_cv_qualifer = true_type;
        using has_lvalue_reference_qualifer = false_type;
        using has_rvalue_reference_qualifer = true_type;
        using has_reference_qualifier = true_type;
    };
    template <typename T, typename Class>
    struct function_traits<T Class::*> : function_traits<T> {};
    template <typename R, typename ...Args>
    struct function_traits<R (*)(Args...)> : function_traits<R (Args...)> {};
    template <typename R, typename ...Args>
    struct function_traits<R (*)(Args..., ...)> : function_traits<R (Args..., ...)> {};
    template <typename R, typename ...Args>
    struct function_traits<R (*)(Args...) noexcept> : function_traits<R (Args...) noexcept> {};
    template <typename R, typename ...Args>
    struct function_traits<R (*)(Args..., ...) noexcept> : function_traits<R (Args..., ...) noexcept> {};

    /* TODO : refactor it by modules in C++ 20 */
    #define function_traits_t(type, trait_name) typename ds::function_traits<type>::trait_name
    #define function_traits_v(type, trait_name) ds::function_traits<type>::trait_name()()
}

namespace data_structure {
    template <typename T>
    class reference_wrapper {
    public:
        using type = T;
    private:
        type *pointer;
    public:
        constexpr reference_wrapper(type &ref) noexcept : pointer {ds::address_of(ref)} {}
        reference_wrapper(const reference_wrapper &rhs) noexcept = default;
        reference_wrapper(reference_wrapper &&) noexcept = delete;
    public:
        reference_wrapper &operator=(const reference_wrapper &) noexcept = default;
        reference_wrapper &operator=(reference_wrapper &&) noexcept = delete;
        operator type &() const noexcept {
            return *this->pointer;
        }
        template <typename ...Args>
        invoke_result_t<type &, Args...> operator()(Args &&...args) const {
            return this->get()(forward<Args>(args)...);
        }
    public:
        type &get() const noexcept {
            return *this->pointer;
        }
    };
}

namespace data_structure {
    template <typename Arg1, typename Arg2, typename Result>
    struct binary_function {
        using first_argument_type = Arg1;
        using second_argument_type = Arg2;
        using result_type = Result;
    };
}

namespace data_structure {
    template <typename LHS = void, typename RHS = LHS>
    struct less : binary_function<LHS, RHS, bool> {
        constexpr bool operator()(const LHS &lhs, const RHS &rhs) const noexcept(noexcept(lhs < rhs)) {
            return lhs < rhs;
        }
    };
    template <>
    struct less<void, void> {
        template <typename LHS, typename RHS = LHS>
        constexpr bool operator()(LHS &&lhs, RHS &&rhs) const
                noexcept(noexcept(ds::forward<LHS>(lhs) < ds::forward<RHS>(rhs))) {
            return ds::forward<LHS>(lhs) < ds::forward<RHS>(rhs);
        }
    };
    template <typename LHS = void, typename RHS = LHS>
    struct less_equal : binary_function<LHS, RHS, bool> {
        constexpr bool operator()(const LHS &lhs, const RHS &rhs) const noexcept(noexcept(lhs <= rhs)) {
            return lhs <= rhs;
        }
    };
    template <>
    struct less_equal<void, void> {
        template <typename LHS, typename RHS = LHS>
        constexpr bool operator()(LHS &&lhs, RHS &&rhs) const
                noexcept(noexcept(ds::forward<LHS>(lhs) <= ds::forward<RHS>(rhs))) {
            return ds::forward<LHS>(lhs) <= ds::forward<RHS>(rhs);
        }
    };
    template <typename LHS = void, typename RHS = LHS>
    struct greater : binary_function<LHS, RHS, bool> {
        constexpr bool operator()(const LHS &lhs, const RHS &rhs) const noexcept(noexcept(lhs > rhs)) {
            return lhs > rhs;
        }
    };
    template <>
    struct greater<void, void> {
        template <typename LHS, typename RHS = LHS>
        constexpr bool operator()(LHS &&lhs, RHS &&rhs) const
                noexcept(noexcept(ds::forward<LHS>(lhs) > ds::forward<RHS>(rhs))) {
            return ds::forward<LHS>(lhs) > ds::forward<RHS>(rhs);
        }
    };
    template <typename LHS = void, typename RHS = LHS>
    struct greater_equal : binary_function<LHS, RHS, bool> {
        constexpr bool operator()(const LHS &lhs, const RHS &rhs) const noexcept(noexcept(lhs >= rhs)) {
            return lhs >= rhs;
        }
    };
    template <>
    struct greater_equal<void, void> {
        template <typename LHS, typename RHS = LHS>
        constexpr bool operator()(LHS &&lhs, RHS &&rhs) const
                noexcept(noexcept(ds::forward<LHS>(lhs) >= ds::forward<RHS>(rhs))) {
            return ds::forward<LHS>(lhs) >= ds::forward<RHS>(rhs);
        }
    };
    template <typename LHS = void, typename RHS = LHS>
    struct equal_to : binary_function<LHS, RHS, bool> {
        constexpr bool operator()(const LHS &lhs, const RHS &rhs) const noexcept(noexcept(lhs == rhs)) {
            return lhs == rhs;
        }
    };
    template <>
    struct equal_to<void, void> {
        template <typename LHS, typename RHS = LHS>
        constexpr bool operator()(LHS &&lhs, RHS &&rhs) const
                noexcept(noexcept(ds::forward<LHS>(lhs) == ds::forward<RHS>(rhs))) {
            return ds::forward<LHS>(lhs) == ds::forward<RHS>(rhs);
        }
    };
    template <typename LHS = void, typename RHS = LHS>
    struct not_equal_to : binary_function<LHS, RHS, bool> {
        constexpr bool operator()(const LHS &lhs, const RHS &rhs) const noexcept(noexcept(lhs != rhs)) {
            return lhs != rhs;
        }
    };
    template <>
    struct not_equal_to<void, void> {
        template <typename LHS, typename RHS = LHS>
        constexpr bool operator()(LHS &&lhs, RHS &&rhs) const
                noexcept(noexcept(ds::forward<LHS>(lhs) != ds::forward<RHS>(rhs))) {
            return ds::forward<LHS>(lhs) != ds::forward<RHS>(rhs);
        }
    };
}

#endif //DATA_STRUCTURE_FUNCTIONAL_HPP
