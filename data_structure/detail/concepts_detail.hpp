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
