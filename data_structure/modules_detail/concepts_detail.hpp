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

export module ds:concepts_detail;

import :algorithm;

export {
    template <typename LHS, typename RHS>
    concept is_variable_swappable_with = requires(LHS lhs, RHS rhs) {
        LHS tmp = lhs;
        lhs = rhs;
        rhs = tmp;
        RHS tmp = rhs;
        rhs = lhs;
        lhs = tmp;
    };
    template <typename LHS, typename RHS>
    concept is_function_swappable_with = requires(LHS &lhs, RHS &rhs) {
        ds::swap(lhs, rhs);
    };
    template <typename LHS, typename RHS>
    concept is_nothrow_variable_swappable_with = requires(LHS lhs, RHS rhs) {
        LHS tmp = lhs noexcept;
        lhs = rhs noexcept;
        rhs = tmp noexcept;
        RHS tmp = rhs noexcept;
        rhs = lhs noexcept;
        lhs = tmp noexcept;
    };
    template <typename LHS, typename RHS>
    concept is_nothrow_function_swappable_with = requires(LHS &lhs, RHS &rhs) {
        ds::swap(lhs, rhs) noexcept;
    };
    template <typename From, typename To>
    concept is_nothrow_function_call_convertible = requires(void (*p)(To) noexcept, From from) {
        p(from) noexcept;
    };
}
