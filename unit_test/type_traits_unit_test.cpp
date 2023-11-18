#include "../source/type_traits.hpp"

using namespace ds;

__DATA_STRUCTURE_START(test macro)
#ifdef __DATA_STRUCTURE_REMOVE_CV_HELPER_MAIN
static_assert(false);
#endif
#ifdef __DATA_STRUCTURE_REMOVE_CV_HELPER_SPECIALIZATION
static_assert(false);
#endif
#ifdef __DATA_STRUCTURE_TEST_OPERATION
static_assert(false);
#endif
#ifdef __DATA_STRUCTURE_TEST_OPERATION_NOTHROW
static_assert(false);
#endif
__DATA_STRUCTURE_END

template <typename T>
constexpr T max_of {~static_cast<T>(static_cast<T>(1) << (sizeof(T) * 8 - 1))};
template <typename T>
constexpr T min_of {~max_of<T>};

class A {};

__DATA_STRUCTURE_START(unit test for ds::constant)
static_assert(constant<int, 0> {} == 0);
static_assert(constant<int, 0> {}() == 0);
static_assert(constant<int, 0>::value == 0);

static_assert(constant<int, 1> {} == 1);
static_assert(constant<int, 1> {}() == 1);
static_assert(constant<int, 1>::value == 1);

static_assert(constant<int, -1> {} == -1);
static_assert(constant<int, -1> {}() == -1);
static_assert(constant<int, -1>::value == -1);

static_assert(constant<int, 42> {} == 42);
static_assert(constant<int, 42> {}() == 42);
static_assert(constant<int, 42>::value == 42);

static_assert(constant<int, 1> {} == 1);
static_assert(constant<int, 1> {}() == 1);
static_assert(constant<int, 1>::value == 1);

// Apple Clang 15.0.0, todo : compatibility
static_assert(constant<int, max_of<int>> {} == 2147483647);
static_assert(constant<int, max_of<int>> {}() == 2147483647);
static_assert(constant<int, max_of<int>>::value == 2147483647);

// Apple Clang 15.0.0, todo : compatibility
static_assert(constant<int, min_of<int>> {} == -2147483648);
static_assert(constant<int, min_of<int>> {}() == -2147483648);
static_assert(constant<int, min_of<int>>::value == -2147483648);

static_assert(constant<char, 'A'>::value == 65);
static_assert(constant<signed char, 'A'>::value == 65);
static_assert(constant<unsigned char, 'A'>::value == 65);
static_assert(constant<wchar_t, L'A'>::value == 65);
static_assert(constant<char8_t, u8'A'>::value == 65);
static_assert(constant<char16_t, u'A'>::value == 65);
static_assert(constant<char32_t, U'A'>::value == 65);

static_assert(constant<bool, true>::value == true_type {});
static_assert(constant<bool, false>::value == false_type {});

static_assert(constant<unsigned short, static_cast<unsigned short>(~static_cast<unsigned short>(0))>::value ==
        static_cast<unsigned short>(max_of<short>) * 2 + 1);
static_assert(constant<unsigned, ~0u>::value == static_cast<unsigned>(max_of<int>) * 2 + 1);
static_assert(constant<unsigned long, ~0ul>::value == static_cast<unsigned long>(max_of<long>) * 2 + 1);
static_assert(constant<unsigned long long, ~0ull>::value ==
        static_cast<unsigned long long>(max_of<long long>) * 2 + 1);
static_assert(constant<__uint128_t, ~static_cast<__uint128_t>(0)>::value ==
        static_cast<__uint128_t>(max_of<__int128_t>) * 2 + 1);

static_assert(make_true_type<>::value == true);
static_assert(make_true_type<int>::value == true);
static_assert(make_true_type<double>::value == true);
static_assert(make_true_type<int []>::value == true);
static_assert(make_true_type<int &>::value == true);
static_assert(make_true_type<int *>::value == true);
static_assert(make_true_type<int (&)[]>::value == true);
static_assert(make_true_type<int [42][1]>::value == true);
static_assert(make_true_type<int (&)[42][42]>::value == true);
static_assert(make_true_type<A>::value == true);
static_assert(make_true_type<int A::*>::value == true);
static_assert(make_true_type<void ()>::value == true);
static_assert(make_true_type<void (*)()>::value == true);
static_assert(make_true_type<void (A::*)()>::value == true);
static_assert(make_true_type<void, int, void *, int **>::value == true);

static_assert(make_false_type<>::value == make_false<>);
static_assert(make_false_type<int>::value == make_false<>);
static_assert(make_false_type<double>::value == make_false<>);
static_assert(make_false_type<int []>::value == make_false<>);
static_assert(make_false_type<int &>::value == make_false<>);
static_assert(make_false_type<int *>::value == make_false<>);
static_assert(make_false_type<int (&)[]>::value == make_false<>);
static_assert(make_false_type<int [42][1]>::value == make_false<>);
static_assert(make_false_type<int (&)[42][42]>::value == make_false<>);
static_assert(make_false_type<A>::value == make_false<>);
static_assert(make_false_type<int A::*>::value == make_false<>);
static_assert(make_false_type<void ()>::value == make_false<>);
static_assert(make_false_type<void (*)()>::value == make_false<>);
static_assert(make_false_type<void (A::*)()>::value == make_false<>);
static_assert(make_false_type<void, int, void *, int **>::value == make_false<>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_same)
static_assert(is_same_v<size_t, std::size_t>);
static_assert(is_same_v<std::size_t, size_t>);
static_assert(is_same_v<ptrdiff_t, std::ptrdiff_t>);
static_assert(is_same_v<std::ptrdiff_t, ptrdiff_t>);
static_assert(is_same_v<align_val_t, std::align_val_t>);
static_assert(is_same_v<std::align_val_t, align_val_t>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::unique_type)
using unique_type_1 = unique_type<>;
using unique_type_2 = unique_type<>;
using unique_type_3 = unique_type<>;
static_assert(not is_same_v<unique_type_1, unique_type_2>);
static_assert(not is_same_v<unique_type_1, unique_type_3>);
static_assert(not is_same_v<unique_type_2, unique_type_3>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::add_lvalue_reference)
static_assert(is_same_v<add_lvalue_reference_t<int>, int &>);
static_assert(is_same_v<add_lvalue_reference_t<int *>, int *&>);
static_assert(is_same_v<add_lvalue_reference_t<int &>, int &>);
static_assert(is_same_v<add_lvalue_reference_t<int &&>, int &>);
static_assert(is_same_v<add_lvalue_reference_t<const int>, const int &>);
static_assert(is_same_v<add_lvalue_reference_t<volatile int>, volatile int &>);
static_assert(is_same_v<add_lvalue_reference_t<const volatile int>, const volatile int &>);
static_assert(is_same_v<add_lvalue_reference_t<void>, void>);
static_assert(is_same_v<add_lvalue_reference_t<int []>, int (&)[]>);
static_assert(is_same_v<add_lvalue_reference_t<int [42]>, int (&)[42]>);
static_assert(is_same_v<add_lvalue_reference_t<A>, A &>);
static_assert(is_same_v<add_lvalue_reference_t<A *>, A *&>);
static_assert(is_same_v<add_lvalue_reference_t<const A>, const A &>);
static_assert(is_same_v<add_lvalue_reference_t<void ()>, void (&)()>);
static_assert(is_same_v<add_lvalue_reference_t<void (int) noexcept>, void (&)(int) noexcept>);
static_assert(is_same_v<add_lvalue_reference_t<__int128_t>, __int128_t &>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::add_rvalue_reference)
static_assert(is_same_v<add_rvalue_reference_t<int>, int &&>);
static_assert(is_same_v<add_rvalue_reference_t<int *>, int *&&>);
static_assert(is_same_v<add_rvalue_reference_t<int &>, int &>);
static_assert(is_same_v<add_rvalue_reference_t<int &&>, int &&>);
static_assert(is_same_v<add_rvalue_reference_t<const int>, const int &&>);
static_assert(is_same_v<add_rvalue_reference_t<volatile int>, volatile int &&>);
static_assert(is_same_v<add_rvalue_reference_t<const volatile int>, const volatile int &&>);
static_assert(is_same_v<add_rvalue_reference_t<void>, void>);
static_assert(is_same_v<add_rvalue_reference_t<int []>, int (&&)[]>);
static_assert(is_same_v<add_rvalue_reference_t<int [42]>, int (&&)[42]>);
static_assert(is_same_v<add_rvalue_reference_t<A>, A &&>);
static_assert(is_same_v<add_rvalue_reference_t<A *>, A *&&>);
static_assert(is_same_v<add_rvalue_reference_t<const A>, const A &&>);
static_assert(is_same_v<add_rvalue_reference_t<void ()>, void (&&)()>);
static_assert(is_same_v<add_rvalue_reference_t<void (int) noexcept>, void (&&)(int) noexcept>);
static_assert(is_same_v<add_rvalue_reference_t<__int128_t>, __int128_t &&>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::add_pointer)
static_assert(is_same_v<add_pointer_t<int>, int *>);
static_assert(is_same_v<add_pointer_t<int *>, int **>);
static_assert(is_same_v<add_pointer_t<int &>, int *>);
static_assert(is_same_v<add_pointer_t<int &&>, int *>);
static_assert(is_same_v<add_pointer_t<const int>, const int *>);
static_assert(is_same_v<add_pointer_t<volatile int>, volatile int *>);
static_assert(is_same_v<add_pointer_t<const volatile int>, const volatile int *>);
static_assert(is_same_v<add_pointer_t<void>, void *>);
static_assert(is_same_v<add_pointer_t<int []>, int (*)[]>);
static_assert(is_same_v<add_pointer_t<int [42]>, int (*)[42]>);
static_assert(is_same_v<add_pointer_t<A>, A *>);
static_assert(is_same_v<add_pointer_t<A *>, A **>);
static_assert(is_same_v<add_pointer_t<const A>, const A *>);
static_assert(is_same_v<add_pointer_t<void ()>, void (*)()>);
static_assert(is_same_v<add_pointer_t<void (int) noexcept>, void (*)(int) noexcept>);
static_assert(is_same_v<add_pointer_t<__int128_t>, __int128_t *>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::add_const)
static_assert(is_same_v<add_const_t<int>, const int>);
static_assert(is_same_v<add_const_t<const int>, const int>);
static_assert(is_same_v<add_const_t<volatile int>, const volatile int>);
static_assert(is_same_v<add_const_t<const volatile int>, const volatile int>);
static_assert(is_same_v<add_const_t<int &>, int &>);
static_assert(is_same_v<add_const_t<const int &>, const int &>);
static_assert(is_same_v<add_const_t<void>, const void>);
static_assert(is_same_v<add_const_t<const void>, const void>);
static_assert(is_same_v<add_const_t<volatile void>, const volatile void>);
static_assert(is_same_v<add_const_t<const volatile void>, const volatile void>);
static_assert(is_same_v<add_const_t<void ()>, void()>);
static_assert(is_same_v<add_const_t<void (*)()>, void (*const)()>);
static_assert(is_same_v<add_const_t<void (&)()>, void (&)()>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::add_volatile)
static_assert(is_same_v<add_volatile_t<int>, volatile int>);
static_assert(is_same_v<add_volatile_t<volatile int>, volatile int>);
static_assert(is_same_v<add_volatile_t<const int>, const volatile int>);
static_assert(is_same_v<add_volatile_t<const volatile int>, const volatile int>);
static_assert(is_same_v<add_volatile_t<int &>, int &>);
static_assert(is_same_v<add_volatile_t<const int &>, const int &>);
static_assert(is_same_v<add_volatile_t<void>, volatile void>);
static_assert(is_same_v<add_volatile_t<const void>, const volatile void>);
static_assert(is_same_v<add_volatile_t<volatile void>, volatile void>);
static_assert(is_same_v<add_volatile_t<const volatile void>, const volatile void>);
static_assert(is_same_v<add_volatile_t<void ()>, void()>);
static_assert(is_same_v<add_volatile_t<void (*)()>, void (*volatile)()>);
static_assert(is_same_v<add_volatile_t<void (&)()>, void (&)()>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::add_cv)
static_assert(is_same_v<add_cv_t<int>, const volatile int>);
static_assert(is_same_v<add_cv_t<volatile int>, const volatile int>);
static_assert(is_same_v<add_cv_t<const int>, const volatile int>);
static_assert(is_same_v<add_cv_t<const volatile int>, const volatile int>);
static_assert(is_same_v<add_cv_t<int &>, int &>);
static_assert(is_same_v<add_cv_t<const int &>, const int &>);
static_assert(is_same_v<add_cv_t<void>, const volatile void>);
static_assert(is_same_v<add_cv_t<const void>, const volatile void>);
static_assert(is_same_v<add_cv_t<volatile void>, const volatile void>);
static_assert(is_same_v<add_cv_t<const volatile void>, const volatile void>);
static_assert(is_same_v<add_cv_t<void ()>, void()>);
static_assert(is_same_v<add_cv_t<void (*)()>, void (*const volatile)()>);
static_assert(is_same_v<add_cv_t<void (&)()>, void (&)()>);
static_assert(is_same_v<add_cv_t<void (A::*)()>, void (A::*const volatile)()>);
static_assert(is_same_v<add_cv_t<void (A::*&)()>, void (A::*&)()>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::const_reference)
static_assert(is_same_v<add_const_reference_t<int>, const int &>);
static_assert(is_same_v<add_const_reference_t<const int>, const int &>);
static_assert(is_same_v<add_const_reference_t<volatile int>, const volatile int &>);
static_assert(is_same_v<add_const_reference_t<int &&>, const int &>);
static_assert(is_same_v<add_const_reference_t<const int &&>, const int &>);
static_assert(is_same_v<add_const_reference_t<int *>, int *const &>);
static_assert(is_same_v<add_const_reference_t<const int *>, const int *const &>);
static_assert(is_same_v<add_const_reference_t<const int *const *const>, const int *const *const &>);
static_assert(is_same_v<add_const_reference_t<int []>, const int (&)[]>);
static_assert(is_same_v<add_const_reference_t<int [42]>, const int (&)[42]>);
static_assert(is_same_v<add_const_reference_t<void ()>, void (&)()>);
static_assert(is_same_v<add_const_reference_t<void (A::*)()>, void (A::*const &)()>);
static_assert(is_same_v<add_const_reference_t<void (A::*&)()>, void (A::*const &)()>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::remove_lvalue_reference)
static_assert(is_same_v<remove_lvalue_reference_t<int>, int>);
static_assert(is_same_v<remove_lvalue_reference_t<int &>, int>);
static_assert(is_same_v<remove_lvalue_reference_t<const int &>, const int>);
static_assert(is_same_v<remove_lvalue_reference_t<volatile int &>, volatile int>);
static_assert(is_same_v<remove_lvalue_reference_t<const volatile int &>, const volatile int>);
static_assert(is_same_v<remove_lvalue_reference_t<int (&)[]>, int []>);
static_assert(is_same_v<remove_lvalue_reference_t<int (&)[42]>, int [42]>);
static_assert(is_same_v<remove_lvalue_reference_t<int (&)[][42]>, int [][42]>);
static_assert(is_same_v<remove_lvalue_reference_t<const int (&)[]>, const int []>);
static_assert(is_same_v<remove_lvalue_reference_t<int &&>, int &&>);
static_assert(is_same_v<remove_lvalue_reference_t<int *&>, int *>);
static_assert(is_same_v<remove_lvalue_reference_t<void (&)()>, void ()>);
static_assert(is_same_v<remove_lvalue_reference_t<void (*&)()>, void (*)()>);
static_assert(is_same_v<remove_lvalue_reference_t<void (A::*&)()>, void (A::*)()>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::remove_rvalue_reference)
static_assert(is_same_v<remove_rvalue_reference_t<int>, int>);
static_assert(is_same_v<remove_rvalue_reference_t<int &>, int &>);
static_assert(is_same_v<remove_rvalue_reference_t<int &&>, int>);
static_assert(is_same_v<remove_rvalue_reference_t<const int &>, const int &>);
static_assert(is_same_v<remove_rvalue_reference_t<const int &&>, const int>);
static_assert(is_same_v<remove_rvalue_reference_t<volatile int &&>, volatile int>);
static_assert(is_same_v<remove_rvalue_reference_t<const volatile int &&>, const volatile int>);
static_assert(is_same_v<remove_rvalue_reference_t<int (&&)[]>, int []>);
static_assert(is_same_v<remove_rvalue_reference_t<int (&&)[42]>, int [42]>);
static_assert(is_same_v<remove_rvalue_reference_t<int (&&)[][42]>, int [][42]>);
static_assert(is_same_v<remove_rvalue_reference_t<const int (&&)[]>, const int []>);
static_assert(is_same_v<remove_rvalue_reference_t<int *&&>, int *>);
static_assert(is_same_v<remove_rvalue_reference_t<void (&&)()>, void ()>);
static_assert(is_same_v<remove_rvalue_reference_t<void (*&&)()>, void (*)()>);
static_assert(is_same_v<remove_rvalue_reference_t<void (A::*&&)()>, void (A::*)()>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::remove_reference)
static_assert(is_same_v<remove_reference_t<int>, int>);
static_assert(is_same_v<remove_reference_t<int &>, int>);
static_assert(is_same_v<remove_reference_t<int &&>, int>);
static_assert(is_same_v<remove_reference_t<const int &>, const int>);
static_assert(is_same_v<remove_reference_t<const int &&>, const int>);
static_assert(is_same_v<remove_reference_t<volatile int &>, volatile int>);
static_assert(is_same_v<remove_reference_t<const volatile int &>, const volatile int>);
static_assert(is_same_v<remove_reference_t<int (&)[]>, int []>);
static_assert(is_same_v<remove_reference_t<int (&&)[42]>, int [42]>);
static_assert(is_same_v<remove_reference_t<int (&)[][42]>, int [][42]>);
static_assert(is_same_v<remove_reference_t<const int (&&)[]>, const int []>);
static_assert(is_same_v<remove_reference_t<int *&>, int *>);
static_assert(is_same_v<remove_reference_t<void (&&)()>, void ()>);
static_assert(is_same_v<remove_reference_t<void (*&)()>, void (*)()>);
static_assert(is_same_v<remove_reference_t<add_lvalue_reference_t<void (A::*&&)()>>, void (A::*)()>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::remove_pointer)
static_assert(is_same_v<remove_pointer_t<int *>, int>);
static_assert(is_same_v<remove_pointer_t<int>, int>);
static_assert(is_same_v<remove_pointer_t<int **>, int *>);
static_assert(is_same_v<remove_pointer_t<int &>, int &>);
static_assert(is_same_v<remove_pointer_t<int *&>, int *&>);
static_assert(is_same_v<remove_pointer_t<int *const *const>, int *const>);
static_assert(is_same_v<remove_pointer_t<int *volatile>, int>);
static_assert(is_same_v<remove_pointer_t<int *const volatile>, int>);
static_assert(is_same_v<remove_pointer_t<int []>, int []>);
static_assert(is_same_v<remove_pointer_t<int *[]>, int *[]>);
static_assert(is_same_v<remove_pointer_t<int [42]>, int [42]>);
static_assert(is_same_v<remove_pointer_t<void ()>, void ()>);
static_assert(is_same_v<remove_pointer_t<void (*)()>, void ()>);
static_assert(is_same_v<remove_pointer_t<void (A::*const &)()>, void (A::*const &)()>);
static_assert(is_same_v<remove_pointer_t<int A::*>, int A::*>);       // pointer-to-member type is not a pointer type
__DATA_STRUCTURE_END