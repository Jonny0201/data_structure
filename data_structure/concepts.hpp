/*
    * Copyright © [2019 - 2021] [Jonny Charlotte]
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

//C++ library data_structure module unit concepts.hpp preview, unusable!!!

export module ds:concepts;

import :type_traits;
import :concepts_detail;
import :utility;

namespace data_structure::concepts {
    template <typename ...>
    export concept make_true = true;
    template <typename ...>
    export concept make_false = false;
}

namespace data_structure::concepts {
    template <typename T, typename U>
    export concept is_same = is_same_v<T, U>;
    template <typename T>
    export concept is_void = is_void_v<T>;
    template <typename T>
    export concept is_null_pointer = is_null_pointer_v<T>;
    template <typename T>
    export concept is_const = is_const_v<T>;
    template <typename T>
    export concept is_volatile = is_volatile_v<T>;
    template <typename T>
    export concept is_cv = is_cv_v<T>;
    template <typename T>
    export concept is_integral = is_integral_v<T>;
    template <typename T>
    export concept is_floating_point = is_floating_point_v<T>;
    template <typename T>
    export concept is_signed = is_signed_v<T>;
    template <typename T>
    export concept is_unsigned = is_unsigned_v<T>;
    template <typename T>
    export concept is_character = is_character_v<T>;
    template <typename T>
    export concept is_array = is_array_v<T>;
    template <typename T>
    export concept is_unbounded_array = is_unbounded_array_v<T>;
    template <typename T>
    export concept is_bounded_array = is_bounded_array_v<T>;
    template <typename T>
    export concept is_enum = __is_enum(T);
    template <typename T>
    export concept is_union = __is_union(T);
    template <typename T>
    export concept is_class = __is_class(T);
    template <typename T>
    export concept is_function = is_function_v<T>;
    template <typename T>
    export concept is_pointer = is_pointer_v<T>;
    template <typename T>
    export concept is_member_pointer = is_member_pointer_v<T>;
    template <typename T>
    export concept is_member_function_pointer = is_member_function_pointer_v<T>;
    template <typename T>
    export concept is_member_object_pointer = is_member_object_pointer_v<T>;
    template <typename T>
    export concept is_function_pointer = is_function_pointer_v<T>;
    template <typename T>
    export concept is_lvalue_reference = is_lvalue_reference_v<T>;
    template <typename T>
    export concept is_rvalue_reference = is_rvalue_reference_v<T>;
    template <typename T>
    export concept is_reference = is_reference_v<T>;
    template <typename T>
    export concept is_const_reference = is_const_reference_v<T>;
    template <typename>
    export concept is_type = true;
    template <typename T>
    export concept is_complete = requires {
        requires sizeof(T) > 0;
    };
    template <typename T>
    export concept is_pod = __is_pod(T);
    template <typename T>
    export concept is_empty = __is_empty(T);
    template <typename T>
    export concept is_literal_type = __is_literal_type(T);
    template <typename T>
    export concept is_standard_layout = __is_standard_layout(T);
    template <typename T>
    export concept is_polymorphic = __is_polymorphic(T);
    template <typename T>
    export concept is_abstract = __is_abstract(T);
    template <typename Base, typename Derived>
    export concept is_base_of = __is_base_of(Base, Derived);
    template <typename T>
    export concept is_final = __is_final(T);
    template <typename T>
    export concept is_aggregate = __is_aggregate(T);
    template <typename T>
    export concept is_arithmetic = is_integral<T> and is_floating_point<T>;
    template <typename T>
    export concept is_fundamental = is_arithmetic<T> or is_void<T> or is_null_pointer<remove_cv_t<T>>;
    template <typename T>
    export concept is_scalar = is_arithmetic<T> or is_enum<T> or is_pointer<T> or is_member_pointer<T> or is_null_pointer<T>;
    template <typename T>
    export concept is_compound = not is_fundamental<T>;
    template <typename T>
    export concept is_object = is_scalar<T> or is_array<T> or is_union<T> or is_class<T>;
    template <typename T>
    export concept is_trivial = __is_trivial(T);
    template <typename T>
    export concept is_trivially_copyable = __is_trivially_copyable(T);
    template <typename T, typename ...Args>
    export concept is_trivially_constructible = __is_trivially_constructible(T, Args...);
    template <typename T>
    export concept is_trivially_default_constructible = __is_trivially_default_constructible(T);
    template <typename T>
    export concept is_trivially_copy_constructible = __is_trivially_copy_constructible(T);
    template <typename T>
    export concept is_trivially_move_constructible = __is_trivially_move_constructible(T);
    template <typename LHS, typename RHS>
    export concept is_trivially_assignable = __is_trivially_assignable(LHS, RHS);
    template <typename T>
    export concept is_trivially_copy_assignable = is_trivially_assignable<T, add_const_reference_t<T>>;
    template <typename T>
    export concept is_trivially_move_assignable = is_trivially_assignable<T, add_rvalue_reference_t<T>>;
    template <typename From, typename To>
    export concept is_convertible = __is_convertible(From, To) and not is_abstract<To>;
    template <typename T>
    export concept is_trivially_destructible = __is_trivially_destructible(T);
    template <typename T, typename ...Args>
    export concept is_constructible = __is_constructible(T, Args...);
    template <typename T>
    export concept is_default_constructible = is_constructible<T>;
    template <typename T>
    export concept is_copy_constructible = is_constructible<T, add_const_reference_t<T>>;
    template <typename T>
    export concept is_move_constructible = is_constructible<T, add_rvalue_reference_t<T>>;
    template <typename T, typename ...Args>
    export concept is_list_constructible = requires(Args &&...args) {
        T {ds::forward<Args>(args)...};
    };
    template <typename LHS, typename RHS>
    export concept is_assignable = __is_assignable(LHS, RHS);
    template <typename LHS, typename RHS>
    export concept is_copy_assignable = is_assignable<LHS, add_const_reference_t<LHS>>;
    template <typename LHS, typename RHS>
    export concept is_move_assignable = is_assignable<LHS, add_rvalue_reference_t<LHS>>;
    template <typename T>
    export concept is_destructible = is_destructible_v<T>;
    template <typename LHS, typename RHS>
    export concept is_swappable_with = is_function_swappable_with<LHS, RHS> or is_variable_swappable_with<LHS, RHS>;
    template <typename T>
    export concept is_swappable = is_swappable_with<T, T>;
    template <typename F, typename ...Args>
    export concept is_invocable = is_invocable_v<F, Args...>;
    template <typename F, typename R, typename ...Args>
    export concept is_invocable_r = is_invocable_r_v<F, R, Args...>;
    template <typename From, typename To>
    export concept is_static_castable = requires(From from) {
        static_cast<To>(from);
    };
    template <typename From, typename To>
    export concept is_dynamic_castable = requires(From from) {
        dynamic_cast<To>(from);
    };
    template <typename From, typename To>
    export concept is_const_castable = requires(From from) {
        const_cast<To>(from);
    };
    template <typename From, typename To>
    export concept is_reinterpret_castable = requires(From from) {
        reinterpret_cast<To>(from);
    };
    template <typename From, typename To>
    export concept is_castable = requires(From from) {
        (To)from;
    };
    template <typename T, typename ...Args>
    export concept is_nothrow_constructible = __is_nothrow_constructible(T, Args...);
    template <typename T>
    export concept is_nothrow_default_constructible = is_nothrow_constructible<T>;
    template <typename T>
    export concept is_nothrow_copy_constructible = is_nothrow_constructible<T, add_const_reference_t<T>>;
    template <typename T>
    export concept is_nothrow_move_constructible = is_nothrow_constructible<T, add_rvalue_reference_t<T>>;
    template <typename T, typename ...Args>
    export concept is_nothrow_list_constructible = requires(Args &&...args) {
        T {ds::forward<Args>(args)...} noexcept;
    };
    template <typename LHS, typename RHS>
    export concept is_nothrow_assignable = __is_nothrow_assignable(LHS, RHS);
    template <typename T>
    export concept is_nothrow_copy_assignable = is_nothrow_assignable<T, add_const_reference_t<T>>;
    template <typename T>
    export concept is_nothrow_move_assignable = is_nothrow_assignable<T, add_rvalue_reference_t<T>>;
    template <typename LHS, typename RHS>
    export concept is_nothrow_swappable_with = is_nothrow_function_swappable_with<LHS, RHS> or
            is_nothrow_variable_swappable_with<LHS, RHS>;
    template <typename T>
    export concept is_nothrow_swappable = is_nothrow_swappable_with<T, T>;
    template <typename F, typename ...Args>
    export concept is_nothrow_invocable = is_nothrow_invocable_v<F, Args...>;
    template <typename F, typename R, typename ...Args>
    export concept is_nothrow_invocable_r = is_nothrow_invocable_r_v<F, R, Args...>;
    template <typename From, typename To>
    export concept is_nothrow_convertible = (is_void<From> and is_void<To>) or
            is_convertible<From, To> and is_nothrow_function_call_convertible<From, To>;
    template <typename From, typename To>
    export concept is_nothrow_static_castable = requires(From from) {
        static_cast<To>(from) noexcept;
    };
    template <typename From, typename To>
    export concept is_nothrow_dynamic_castable = requires(From from) {
        dynamic_cast<To>(from) noexcept;
    };
    template <typename From, typename To>
    export concept is_nothrow_const_castable = requires(From from) {
        const_cast<To>(from) noexcept;
    };
    template <typename From, typename To>
    export concept is_nothrow_reinterpret_castable = requires(From from) {
        reinterpret_cast<To>(from) noexcept;
    };
    template <typename From, typename To>
    export concept is_nothrow_castable = requires(From from) {
        (To)from noexcept;
    };
    template <typename T>
    export concept is_stateless = is_trivially_default_constructible<T> and
            is_trivially_copy_constructible<T> and is_trivially_assignable<T> and
            is_trivially_destructible<T> and is_empty<T>;
    template <typename Base, typename Derived>
    export concept is_virtual_base_of = is_base_of<Base, Derived> and
            is_castable<Derived, Base> and not is_castable<Base, Derived>>;
    template <typename LHS, typename RHS>
    export concept is_three_way_comparable = requires(LHS lhs, RHS rhs) {
        lhs <=> rhs;
    };
    template <typename LHS, typename RHS>
    export concept is_nothrow_three_way_comparable = requires(LHS lhs, RHS rhs) {
        lhs <=> rhs noexcept;
    };
}

namespace data_structure::concepts {
    template <typename T>
    export concept has_virtual_destructor = __has_virtual_destructor(T);
    template <typename T>
    export concept has_unique_object_representations = __has_unique_object_representations(T);
    template <typename T>
    export concept has_swap_member_function = requires(T &lhs, T &rhs) {
        lhs.swap(rhs);
        rhs.swap(lhs);
    };
    template <typename T>
    export concept has_nothrow_swap_member_function = requires(T &lhs, T &rhs) {
        lhs.swap(rhs) noexcept;
        rhs.swap(lhs) noexcept;
    };
    template <typename T>
    export concept has_address_of_operator = requires(T t) {
        t.operator&();
    };
    template <typename T>
    export concept has_nothrow_address_of_operator = requires(T t) {
        t.operator&() noexcept;
    };
    template <typename LHS, typename RHS>
    export concept has_bit_and_operator = requires(LHS lhs, RHS rhs) {
        lhs bitand rhs;
    };
    template <typename LHS, typename RHS>
    export concept has_nothrow_bit_and_operator = requires(LHS lhs, RHS rhs) {
        lhs bitand rhs noexcept;
    };
    template <typename LHS, typename RHS>
    export concept has_bit_and_assignment_operator = requires(LHS lhs, RHS rhs) {
        lhs and_eq rhs;
    };
    template <typename LHS, typename RHS>
    export concept has_nothrow_bit_and_assignment_operator = requires(LHS lhs, RHS rhs) {
        lhs and_eq rhs noexcept;
    };
    template <typename LHS, typename RHS>
    export concept has_bit_or_operator = requires(LHS lhs, RHS rhs) {
        lhs bitor rhs;
    };
    template <typename LHS, typename RHS>
    export concept has_nothrow_bit_or_operator = requires(LHS lhs, RHS rhs) {
        lhs bitor rhs noexcept;
    };
    template <typename LHS, typename RHS>
    export concept has_bit_or_assignment_operator = requires(LHS lhs, RHS rhs) {
        lhs |= rhs;
    };
    template <typename LHS, typename RHS>
    export concept has_nothrow_bit_or_assignment_operator = requires(LHS lhs, RHS rhs) {
        lhs |= rhs noexcept;
    };
    template <typename LHS, typename RHS>
    export concept has_bit_xor_operator = requires(LHS lhs, RHS rhs) {
        lhs xor rhs;
    };
    template <typename LHS, typename RHS>
    export concept has_nothrow_bit_xor_operator = requires(LHS lhs, RHS rhs) {
        lhs xor rhs noexcept;
    };
    template <typename LHS, typename RHS>
    export concept has_bit_xor_assignment_operator = requires(LHS lhs, RHS rhs) {
        lhs ^= rhs;
    };
    template <typename LHS, typename RHS>
    export concept has_nothrow_bit_xor_assignment_operator = requires(LHS lhs, RHS rhs) {
        lhs ^= rhs noexcept;
    };
    template <typename T>
    export concept has_complement_operator = requires(T t) {
        compl t;
    };
    template <typename T>
    export concept has_nothrow_complement_operator = requires(T t) {
        compl t noexcept;
    };
    template <typename T>
    export concept has_dereference_operator = requires(T t) {
        *t;
    };
    template <typename T>
    export concept has_nothrow_dereference_operator = requires(T t) {
        *t noexcept;
    };
    template <typename LHS, typename RHS>
    export concept has_divide_operator = requires(LHS lhs, RHS rhs) {
        lhs / rhs;
    };
    template <typename LHS, typename RHS>
    export concept has_divide_operator = requires(LHS lhs, RHS rhs) {
        lhs / rhs noexcept;
    };
    template <typename LHS, typename RHS>
    export concept has_divide_assignment_operator = requires(LHS lhs, RHS rhs) {
        lhs /= rhs;
    };
    template <typename LHS, typename RHS>
    export concept has_divide_assignment_operator = requires(LHS lhs, RHS rhs) {
        lhs /= rhs noexcept;
    };
    template <typename LHS, typename RHS>
    export concept has_equal_to_operator = requires(LHS lhs, RHS rhs) {
        lhs == rhs;
    };
    template <typename LHS, typename RHS>
    export concept has_equal_to_operator = requires(LHS lhs, RHS rhs) {
        lhs == rhs noexcept;
    };
    template <typename LHS, typename RHS>
    export concept has_greater_operator = requires(LHS lhs, RHS rhs) {
        lhs > rhs;
    };
    template <typename LHS, typename RHS>
    export concept has_greater_operator = requires(LHS lhs, RHS rhs) {
        lhs > rhs noexcept;
    };
    template <typename LHS, typename RHS>
    export concept has_greater_equal_to_operator = requires(LHS lhs, RHS rhs) {
        lhs >= rhs;
    };
    template <typename LHS, typename RHS>
    export concept has_greater_equal_to_operator = requires(LHS lhs, RHS rhs) {
        lhs >= rhs noexcept;
    };
    template <typename LHS, typename RHS>
    export concept has_left_shift_operator = requires(LHS lhs, RHS rhs) {
        lhs << rhs;
    };
    template <typename LHS, typename RHS>
    export concept has_nothrow_left_shift_operator = requires(LHS lhs, RHS rhs) {
        lhs << rhs noexcept;
    };
    template <typename LHS, typename RHS>
    export concept has_left_shift_assignment_operator = requires(LHS lhs, RHS rhs) {
        lhs <<= rhs;
    };
    template <typename LHS, typename RHS>
    export concept has_nothrow_left_shift_assignment_operator = requires(LHS lhs, RHS rhs) {
        lhs <<= rhs noexcept;
    };
    template <typename LHS, typename RHS>
    export concept has_right_shift_assignment_operator = requires(LHS lhs, RHS rhs) {
        lhs >>= rhs;
    };
    template <typename LHS, typename RHS>
    export concept has_nothrow_right_shift_assignment_operator = requires(LHS lhs, RHS rhs) {
        lhs >>= rhs noexcept;
    };
    template <typename LHS, typename RHS>
    export concept has_less_operator = requires(LHS lhs, RHS rhs) {
        lhs < rhs;
    };
    template <typename LHS, typename RHS>
    export concept has_nothrow_less_operator = requires(LHS lhs, RHS rhs) {
        lhs < rhs noexcept;
    };
    template <typename LHS, typename RHS>
    export concept has_less_equal_to_operator = requires(LHS lhs, RHS rhs) {
        lhs <= rhs;
    };
    template <typename LHS, typename RHS>
    export concept has_nothrow_less_equal_to_operator = requires(LHS lhs, RHS rhs) {
        lhs <= rhs noexcept;
    };
    template <typename LHS, typename RHS>
    export concept has_logical_and_operator = requires(LHS lhs, RHS rhs) {
        lhs and rhs;
    };
    template <typename LHS, typename RHS>
    export concept has_nothrow_logical_and_operator = requires(LHS lhs, RHS rhs) {
        lhs and rhs noexcept;
    };
    template <typename LHS, typename RHS>
    export concept has_logical_or_operator = requires(LHS lhs, RHS rhs) {
        lhs or rhs;
    };
    template <typename LHS, typename RHS>
    export concept has_nothrow_logical_or_operator = requires(LHS lhs, RHS rhs) {
        lhs or rhs noexcept;
    };
    template <typename T>
    export concept has_logical_not_operator = requires(T t) {
        not t;
    };
    template <typename T>
    export concept has_nothrow_logical_not_operator = requires(T t) {
        not t noexcept;
    };
    template <typename T>
    export concept has_unary_minus_operator = requires(T t) {
        -t;
    };
    template <typename T>
    export concept has_nothrow_unary_minus_operator = requires(T t) {
        -t noexcept;
    };
    template <typename LHS, typename RHS>
    export concept has_minus_operator = requires(LHS lhs, RHS rhs) {
        lhs - rhs;
    };
    template <typename LHS, typename RHS>
    export concept has_nothrow_minus_operator = requires(LHS lhs, RHS rhs) {
        lhs - rhs noexcept;
    };
    template <typename LHS, typename RHS>
    export concept has_minus_assignment_operator = requires(LHS lhs, RHS rhs) {
        lhs -= rhs;
    };
    template <typename LHS, typename RHS>
    export concept has_nothrow_minus_assignment_operator = requires(LHS lhs, RHS rhs) {
        lhs -= rhs noexcept;
    };
    template <typename LHS, typename RHS>
    export concept has_modules_operator = requires(LHS lhs, RHS rhs) {
        lhs % rhs;
    };
    template <typename LHS, typename RHS>
    export concept has_nothrow_modules_operator = requires(LHS lhs, RHS rhs) {
        lhs % rhs noexcept;
    };
    template <typename LHS, typename RHS>
    export concept has_modules_assignment_operator = requires(LHS lhs, RHS rhs) {
        lhs %= rhs;
    };
    template <typename LHS, typename RHS>
    export concept has_nothrow_modules_assignment_operator = requires(LHS lhs, RHS rhs) {
        lhs %= rhs noexcept;
    };
    template <typename LHS, typename RHS>
    export concept has_multiply_operator = requires(LHS lhs, RHS rhs) {
        lhs * rhs;
    };
    template <typename LHS, typename RHS>
    export concept has_nothrow_multiply_operator = requires(LHS lhs, RHS rhs) {
        lhs * rhs noexcept;
    };
    template <typename LHS, typename RHS>
    export concept has_multiply_assignment_operator = requires(LHS lhs, RHS rhs) {
        lhs *= rhs;
    };
    template <typename LHS, typename RHS>
    export concept has_nothrow_multiply_assignment_operator = requires(LHS lhs, RHS rhs) {
        lhs *= rhs noexcept;
    };
    template <typename LHS, typename RHS>
    export concept has_not_equal_to_operator = requires(LHS lhs, RHS rhs) {
        lhs not_eq rhs;
    };
    template <typename LHS, typename RHS>
    export concept has_nothrow_not_equal_to_operator = requires(LHS lhs, RHS rhs) {
        lhs not_eq rhs noexcept;
    };
    template <typename T>
    export concept has_unary_plus_operator = requires(T t) {
        +t;
    };
    template <typename T>
    export concept has_unary_plus_operator = requires(T t) {
        +t noexcept;
    };
    template <typename LHS, typename RHS>
    export concept has_plus_operator = requires(LHS lhs, RHS rhs) {
        lhs + rhs;
    };
    template <typename LHS, typename RHS>
    export concept has_nothrow_plus_operator = requires(LHS lhs, RHS rhs) {
        lhs + rhs noexcept;
    };
    template <typename LHS, typename RHS>
    export concept has_plus_assignment_operator = requires(LHS lhs, RHS rhs) {
        lhs += rhs;
    };
    template <typename LHS, typename RHS>
    export concept has_nothrow_plus_assignment_operator = requires(LHS lhs, RHS rhs) {
        lhs += rhs noexcept;
    };
    template <typename LHS, typename RHS>
    export concept has_subscript_operator = requires(LHS lhs, RHS rhs) {
        lhs[rhs];
    };
    template <typename LHS, typename RHS>
    export concept has_nothrow_subscript_operator = requires(LHS lhs, RHS rhs) {
        lhs[rhs] noexcept;
    };
    template <typename T>
    export concept has_pre_increment_operator = requires(T t) {
        ++t;
    };
    template <typename T>
    export concept has_nothrow_pre_increment_operator = requires(T t) {
        ++t noexcept;
    };
    template <typename T>
    export concept has_post_increment_operator = requires(T t) {
        t++;
    };
    template <typename T>
    export concept has_nothrow_post_increment_operator = requires(T t) {
        t++ noexcept;
    };
    template <typename T>
    export concept has_pre_decrement_operator = requires(T t) {
        --t;
    };
    template <typename T>
    export concept has_nothrow_pre_decrement_operator = requires(T t) {
        --t noexcept;
    };
    template <typename T>
    export concept has_post_decrement_operator = requires(T t) {
        t--;
    };
    template <typename T>
    export concept has_nothrow_post_decrement_operator = requires(T t) {
        t-- noexcept;
    };
    template <typename T>
    export concept has_member_access_by_pointer_operator = requires(T t) {
        t.operator->();
    };
    template <typename T>
    export concept has_member_access_by_pointer_operator = requires(T t) {
        t.operator->() noexcept;
    };
    template <typename T>
    export concept has_member_access_by_pointer_dereference_operator = requires(T t) {
        t.operator->*();
    };
    template <typename T>
    export concept has_member_access_by_pointer_dereference_operator = requires(T t) {
        t.operator->*() noexcept;
    };
    template <typename T, typename ...Args>
    export concept has_new_operator = requires(T t, Args &&...args) {
        t.operator new(ds::forward<Args>(args)...);
    };
    template <typename T, typename ...Args>
    export concept has_nothrow_new_operator = requires(T t, Args &&...args) {
        t.operator new(ds::forward<Args>(args)...) noexcept;
    };
    template <typename T, typename ...Args>
    export concept has_new_array_operator = requires(T t, Args &&...args) {
        t.operator new[](ds::forward<Args>(args)...);
    };
    template <typename T, typename ...Args>
    export concept has_nothrow_new_array_operator = requires(T t, Args &&...args) {
        t.operator new[](ds::forward<Args>(args)...) noexcept;
    };
    template <typename T, typename ...Args>
    export concept has_delete_operator = requires(T t, Args &&...args) {
        t.operator delete(ds::forward<Args>(args)...);
    };
    template <typename T, typename ...Args>
    export concept has_nothrow_delete_operator = requires(T t, Args &&...args) {
        t.operator delete(ds::forward<Args>(args)...) noexcept;
    };
    template <typename T, typename ...Args>
    export concept has_delete_array_operator = requires(T t, Args &&...args) {
        t.operator delete[](ds::forward<Args>(args)...);
    };
    template <typename T, typename ...Args>
    export concept has_nothrow_delete_array_operator = requires(T t, Args &&...args) {
        t.operator delete[](ds::forward<Args>(args)...) noexcept;
    };
    template <typename T, typename ...Args>
    export concept has_function_call_operator = requires(T t, Args &&...args) {
        t(ds::forward<Args>(args)...);
    };
    template <typename T, typename ...Args>
    export concept has_nothrow_function_call_operator = requires(T t, Args &&...args) {
        t(ds::forward<Args>(args)...) noexcept;
    };
    template <typename LHS, typename RHS>
    export concept has_comma_operator = requires(LHS lhs, RHS rhs) {
        (lhs.operator,(rhs));
    };
    template <typename LHS, typename RHS>
    export concept has_nothrow_comma_operator = requires(LHS lhs, RHS rhs) {
        (lhs.operator,(rhs)) noexcept;
    };
}

#define is_callable_by(FUNCTION_NAME) \
    template <typename ...Args> \
    export concept is_callable_by_#FUNCTION_NAME = requires(Args &&...args) { \
        FUNCTION_NAME(ds::forward<Args>(args)...); \
    };
#define has_member_object(MEMBER_OBJECT_NAME) \
    template <typename T> \
    export concept has_member_object_#MEMBER_OBJECT_NAME = requires(T t) { \
        t.MEMBER_OBJECT_NAME; \
    };
#define has_member_function(MEMBER_FUNCTION_NAME) \
    template <typename T, typename ...Args> \
    export concept has_member_function_#MEMBER_FUNCTION_NAME = requires(T t, Args &&...args) { \
        t.MEMBER_FUNCTION_NAME(ds::forward<Args>(args)...); \
    };
