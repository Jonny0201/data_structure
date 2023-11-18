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

__DATA_STRUCTURE_START(unit test for ds::remove_const)
static_assert(is_same_v<remove_const_t<const int>, int>);
static_assert(is_same_v<remove_const_t<int>, int>);
static_assert(is_same_v<remove_const_t<volatile int>, volatile int>);
static_assert(is_same_v<remove_const_t<const volatile int>, volatile int>);
static_assert(is_same_v<remove_const_t<const int *>, const int *>);
static_assert(is_same_v<remove_const_t<int *const>, int *>);
static_assert(is_same_v<remove_const_t<const int &>, const int &>);
static_assert(is_same_v<remove_const_t<const void ()>, const void ()>);
static_assert(is_same_v<remove_const_t<const int []>, int []>);
static_assert(is_same_v<remove_const_t<const int (&)[]>, const int (&)[]>);
static_assert(is_same_v<remove_const_t<int (A::*const)()>, int (A::*)()>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::remove_volatile)
static_assert(is_same_v<remove_volatile_t<volatile int>, int>);
static_assert(is_same_v<remove_volatile_t<int>, int>);
static_assert(is_same_v<remove_volatile_t<const int>, const int>);
static_assert(is_same_v<remove_volatile_t<const volatile int>, const int>);
static_assert(is_same_v<remove_volatile_t<volatile int *>, volatile int *>);
static_assert(is_same_v<remove_volatile_t<int *volatile>, int *>);
static_assert(is_same_v<remove_volatile_t<volatile int &>, volatile int &>);
static_assert(is_same_v<remove_volatile_t<volatile void ()>, volatile void ()>);
static_assert(is_same_v<remove_volatile_t<volatile int []>, int []>);
static_assert(is_same_v<remove_volatile_t<volatile int (&)[]>, volatile int (&)[]>);
static_assert(is_same_v<remove_volatile_t<int (A::*volatile)()>, int (A::*)()>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::remove_cv)
static_assert(is_same_v<remove_cv_t<const int>, int>);
static_assert(is_same_v<remove_cv_t<int>, int>);
static_assert(is_same_v<remove_cv_t<volatile int>, int>);
static_assert(is_same_v<remove_cv_t<const volatile int>, int>);
static_assert(is_same_v<remove_cv_t<const int *>, const int *>);
static_assert(is_same_v<remove_cv_t<int *const>, int *>);
static_assert(is_same_v<remove_cv_t<int *const volatile>, int *>);
static_assert(is_same_v<remove_cv_t<const int &>, const int &>);
static_assert(is_same_v<remove_cv_t<const void ()>, const void ()>);
static_assert(is_same_v<remove_cv_t<const volatile void ()>, const volatile void ()>);
static_assert(is_same_v<remove_cv_t<const int []>, int []>);
static_assert(is_same_v<remove_cv_t<const volatile int []>, int []>);
static_assert(is_same_v<remove_cv_t<const int (&)[]>, const int (&)[]>);
static_assert(is_same_v<remove_cv_t<const volatile int (&)[]>, const volatile int (&)[]>);
static_assert(is_same_v<remove_cv_t<int (A::*const)()>, int (A::*)()>);
static_assert(is_same_v<remove_cv_t<int (A::*const volatile)()>, int (A::*)()>);
static_assert(is_same_v<remove_cv_t<volatile int>, int>);
static_assert(is_same_v<remove_cv_t<volatile int *>, volatile int *>);
static_assert(is_same_v<remove_cv_t<int *volatile>, int *>);
static_assert(is_same_v<remove_cv_t<volatile int &>, volatile int &>);
static_assert(is_same_v<remove_cv_t<volatile void ()>, volatile void ()>);
static_assert(is_same_v<remove_cv_t<volatile int []>, int []>);
static_assert(is_same_v<remove_cv_t<volatile int (&)[]>, volatile int (&)[]>);
static_assert(is_same_v<remove_cv_t<int (A::*volatile)()>, int (A::*)()>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::remove_const_reference)
static_assert(is_same_v<remove_const_reference_t<const int &>, int>);
static_assert(is_same_v<remove_const_reference_t<int &>, int &>);
static_assert(is_same_v<remove_const_reference_t<const int>, const int>);
static_assert(is_same_v<remove_const_reference_t<volatile int &>, volatile int &>);
static_assert(is_same_v<remove_const_reference_t<volatile int>, volatile int>);
static_assert(is_same_v<remove_const_reference_t<const volatile int &>, volatile int>);
static_assert(is_same_v<remove_const_reference_t<const int *&>, const int *&>);
static_assert(is_same_v<remove_const_reference_t<int *const &>, int *>);
static_assert(is_same_v<remove_const_reference_t<const int (&)[]>, int []>);
static_assert(is_same_v<remove_const_reference_t<const int (*&)[]>, const int (*&)[]>);
static_assert(is_same_v<remove_const_reference_t<const int (*const &)[]>, const int (*)[]>);
static_assert(is_same_v<remove_const_reference_t<const int (A::*)()>, const int (A::*)()>);
static_assert(is_same_v<remove_const_reference_t<const int (A::*const &)()>, const int (A::*)()>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::remove_extent)
static_assert(is_same_v<remove_extent_t<int []>, int>);
static_assert(is_same_v<remove_extent_t<const int []>, const int>);
static_assert(is_same_v<remove_extent_t<int [42]>, int>);
static_assert(is_same_v<remove_extent_t<const int [42]>, const int>);
static_assert(is_same_v<remove_extent_t<int [][42]>, int [42]>);        // multidimensional array type's first dimension will be removed
static_assert(is_same_v<remove_extent_t<int [42][1]>, int [1]>);
static_assert(is_same_v<remove_extent_t<int (&)[]>, int (&)[]>);        // the reference to array is not an array type
static_assert(is_same_v<remove_extent_t<int (*)[]>, int (*)[]>);        // a pointer to array is not an array type
static_assert(is_same_v<remove_extent_t<int *[]>, int *>);
static_assert(is_same_v<remove_extent_t<void (*[])()>, void (*)()>);
static_assert(is_same_v<remove_extent_t<void (A::*[])()>, void (A::*)()>);
// only for Clang and GCC, todo : compatibility
static_assert(is_same_v<remove_extent_t<int [0]>, int [0]>);
static_assert(is_same_v<remove_extent_t<const int [0]>, const int [0]>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::remove_extents)
static_assert(is_same_v<remove_extents_t<int []>, int>);
static_assert(is_same_v<remove_extents_t<const int []>, const int>);
static_assert(is_same_v<remove_extents_t<int [42]>, int>);
static_assert(is_same_v<remove_extents_t<const int [42]>, const int>);
static_assert(is_same_v<remove_extents_t<int [][42][1][2][3]>, int>);
static_assert(is_same_v<remove_extents_t<const int [][1]>, const int>);
static_assert(is_same_v<remove_extents_t<int *[][1][2][3]>, int *>);
static_assert(is_same_v<remove_extents_t<void (*[][1][2][3][4])()>, void (*)()>);
static_assert(is_same_v<remove_extents_t<void (A::*[1][2][3][4][5][6][7])()>, void (A::*)()>);
// only for Clang and GCC, todo : compatibility
static_assert(is_same_v<remove_extents_t<int [0][0][0][0]>, int [0][0][0][0]>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_void)
static_assert(is_void_v<void>);
static_assert(is_void_v<const void>);
static_assert(is_void_v<volatile void>);
static_assert(is_void_v<const volatile void>);
static_assert(is_void_v<make_void_t<int, char, long [], A &, A *[]>>);
static_assert(is_void_v<void_t<>>);
static_assert(not is_void_v<void ()>);
static_assert(not is_void_v<void (A::*)()>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_null_pointer)
static_assert(is_null_pointer_v<decltype(nullptr)>);
static_assert(is_null_pointer_v<const decltype(nullptr)>);
static_assert(is_null_pointer_v<volatile decltype(nullptr)>);
static_assert(is_null_pointer_v<const volatile decltype(nullptr)>);
static_assert(not is_null_pointer_v<decltype(NULL)>);
static_assert(not is_null_pointer_v<decltype(0)>);
static_assert(not is_null_pointer_v<decltype(static_cast<void *>(NULL))>);
static_assert(not is_null_pointer_v<decltype(static_cast<void *>(0))>);
static_assert(is_null_pointer_v<decltype(static_cast<decltype(nullptr)>(NULL))>);
static_assert(is_null_pointer_v<decltype(static_cast<decltype(nullptr)>(0))>);
static_assert(is_null_pointer_v<std::nullptr_t>);
static_assert(is_null_pointer_v<const std::nullptr_t>);
static_assert(is_null_pointer_v<volatile std::nullptr_t>);
static_assert(is_null_pointer_v<const volatile std::nullptr_t>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_const)
static_assert(is_const_v<const int>);
static_assert(not is_const_v<int>);
static_assert(not is_const_v<volatile int>);
static_assert(is_const_v<const volatile int>);
static_assert(is_const_v<const void>);
static_assert(not is_const_v<void>);
static_assert(not is_const_v<volatile void>);
static_assert(is_const_v<const volatile void>);
static_assert(not is_const_v<const int &>);
static_assert(not is_const_v<const int *>);
static_assert(is_const_v<int *const>);
static_assert(is_const_v<const int *const>);
static_assert(not is_const_v<const int *const &>);
static_assert(is_const_v<const int []>);
static_assert(not is_const_v<const int (&)[]>);
static_assert(is_const_v<const int [42]>);
static_assert(not is_const_v<const int (&)[42]>);
static_assert(is_const_v<int (*const)[]>);
static_assert(not is_const_v<const int *[]>);
static_assert(is_const_v<const int *const []>);
static_assert(not is_const_v<const void ()>);
static_assert(is_const_v<void (A::*const)()>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_volatile)
static_assert(is_volatile_v<volatile int>);
static_assert(not is_volatile_v<int>);
static_assert(not is_volatile_v<const int>);
static_assert(is_volatile_v<const volatile int>);
static_assert(is_volatile_v<volatile void>);
static_assert(not is_volatile_v<void>);
static_assert(not is_volatile_v<const void>);
static_assert(is_volatile_v<const volatile void>);
static_assert(not is_volatile_v<volatile int &>);
static_assert(not is_volatile_v<volatile int *>);
static_assert(is_volatile_v<int *volatile>);
static_assert(is_volatile_v<volatile int *volatile>);
static_assert(not is_volatile_v<volatile int *volatile &>);
static_assert(is_volatile_v<volatile int []>);
static_assert(not is_volatile_v<volatile int (&)[]>);
static_assert(is_volatile_v<volatile int [42]>);
static_assert(not is_volatile_v<volatile int (&)[42]>);
static_assert(is_volatile_v<int (*volatile)[]>);
static_assert(not is_volatile_v<volatile int *[]>);
static_assert(is_volatile_v<volatile int *volatile []>);
static_assert(not is_volatile_v<volatile void ()>);
static_assert(is_volatile_v<void (A::*volatile)()>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_cv)
static_assert(not is_cv_v<volatile int>);
static_assert(not is_cv_v<int>);
static_assert(not is_cv_v<const int>);
static_assert(is_cv_v<const volatile int>);
static_assert(not is_cv_v<volatile void>);
static_assert(not is_cv_v<void>);
static_assert(not is_cv_v<const void>);
static_assert(is_cv_v<const volatile void>);
static_assert(not is_cv_v<const volatile int &>);
static_assert(not is_cv_v<const volatile int *>);
static_assert(is_cv_v<int *const volatile>);
static_assert(is_cv_v<const volatile int *const volatile>);
static_assert(not is_cv_v<const volatile int *const volatile &>);
static_assert(is_cv_v<const volatile int []>);
static_assert(not is_cv_v<const volatile int (&)[]>);
static_assert(is_cv_v<const volatile int [42]>);
static_assert(not is_cv_v<const volatile int (&)[42]>);
static_assert(is_cv_v<int (*const volatile)[]>);
static_assert(not is_cv_v<const volatile int *[]>);
static_assert(is_cv_v<const volatile int *const volatile []>);
static_assert(not is_cv_v<const volatile void ()>);
static_assert(is_cv_v<void (A::*const volatile)()>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_integral)
static_assert(is_integral_v<bool>);
static_assert(is_integral_v<const bool>);
static_assert(is_integral_v<volatile bool>);
static_assert(is_integral_v<const volatile bool>);
static_assert(not is_integral_v<bool *>);
static_assert(not is_integral_v<bool &>);
static_assert(not is_integral_v<bool []>);
static_assert(not is_integral_v<bool [42]>);
static_assert(not is_integral_v<bool ()>);
static_assert(not is_integral_v<A>);
static_assert(is_integral_v<char>);
static_assert(is_integral_v<signed char>);
static_assert(is_integral_v<unsigned char>);
static_assert(is_integral_v<char8_t>);
static_assert(is_integral_v<char16_t>);
static_assert(is_integral_v<char32_t>);
static_assert(is_integral_v<wchar_t>);
static_assert(is_integral_v<short>);
static_assert(is_integral_v<signed short>);
static_assert(is_integral_v<unsigned short>);
static_assert(is_integral_v<int>);
static_assert(is_integral_v<signed>);
static_assert(is_integral_v<signed int>);
static_assert(is_integral_v<unsigned>);
static_assert(is_integral_v<unsigned int>);
static_assert(is_integral_v<long>);
static_assert(is_integral_v<unsigned long>);
static_assert(is_integral_v<long long>);
static_assert(is_integral_v<unsigned long long>);
static_assert(is_integral_v<__int128_t>);
static_assert(is_integral_v<__uint128_t>);
static_assert(not is_integral_v<float>);
static_assert(not is_integral_v<double>);
static_assert(not is_integral_v<long double>);
static_assert(not is_integral_v<void>);
static_assert(not is_integral_v<decltype(nullptr)>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_floating_point)
static_assert(is_floating_point_v<float>);
static_assert(is_floating_point_v<const float>);
static_assert(is_floating_point_v<volatile float>);
static_assert(is_floating_point_v<const volatile float>);
static_assert(not is_floating_point_v<float *>);
static_assert(not is_floating_point_v<float &>);
static_assert(not is_floating_point_v<float []>);
static_assert(not is_floating_point_v<float [42]>);
static_assert(not is_floating_point_v<float ()>);
static_assert(is_floating_point_v<double>);
static_assert(is_floating_point_v<long double>);
static_assert(not is_floating_point_v<bool>);
static_assert(not is_floating_point_v<A>);
static_assert(not is_floating_point_v<char>);
static_assert(not is_floating_point_v<signed char>);
static_assert(not is_floating_point_v<unsigned char>);
static_assert(not is_floating_point_v<char8_t>);
static_assert(not is_floating_point_v<char16_t>);
static_assert(not is_floating_point_v<char32_t>);
static_assert(not is_floating_point_v<wchar_t>);
static_assert(not is_floating_point_v<short>);
static_assert(not is_floating_point_v<signed short>);
static_assert(not is_floating_point_v<unsigned short>);
static_assert(not is_floating_point_v<int>);
static_assert(not is_floating_point_v<signed>);
static_assert(not is_floating_point_v<signed int>);
static_assert(not is_floating_point_v<unsigned>);
static_assert(not is_floating_point_v<unsigned int>);
static_assert(not is_floating_point_v<long>);
static_assert(not is_floating_point_v<unsigned long>);
static_assert(not is_floating_point_v<long long>);
static_assert(not is_floating_point_v<unsigned long long>);
static_assert(not is_floating_point_v<__int128_t>);
static_assert(not is_floating_point_v<__uint128_t>);
static_assert(not is_floating_point_v<void>);
static_assert(not is_floating_point_v<decltype(nullptr)>);
__DATA_STRUCTURE_END