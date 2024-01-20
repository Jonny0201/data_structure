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
struct B;
enum class C;
enum D : int;
union E;

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
static_assert(not is_same_v<void (&)(), void (&&)()>);
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
// update : Clang has built-in __remove_extent, which is able to remove zero-dimensional array type
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
// update : Clang has built-in __remove_extents, which is able to remove zero-dimensional array type
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
static_assert(not is_const_v<void () const>);
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
static_assert(not is_volatile_v<void () volatile>);
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
static_assert(not is_cv_v<void () const volatile>);
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

__DATA_STRUCTURE_START(unit test for ds::is_signed)
static_assert(is_signed_v<int>);
static_assert(is_signed_v<const int>);
static_assert(is_signed_v<volatile int>);
static_assert(is_signed_v<const volatile int>);
static_assert(not is_signed_v<int *>);
static_assert(not is_signed_v<int &>);
static_assert(not is_signed_v<int []>);
static_assert(not is_signed_v<int [42]>);
static_assert(not is_signed_v<int ()>);
static_assert(not is_signed_v<bool>);
static_assert(not is_signed_v<A>);
static_assert(is_signed_v<char>);
static_assert(is_signed_v<signed char>);
static_assert(not is_signed_v<unsigned char>);
static_assert(not is_signed_v<char8_t>);
static_assert(not is_signed_v<char16_t>);
static_assert(not is_signed_v<char32_t>);
// todo : compatibility
static_assert(is_signed_v<wchar_t>);
static_assert(is_signed_v<short>);
static_assert(is_signed_v<signed short>);
static_assert(not is_signed_v<unsigned short>);
static_assert(is_signed_v<signed>);
static_assert(is_signed_v<signed int>);
static_assert(not is_signed_v<unsigned>);
static_assert(not is_signed_v<unsigned int>);
static_assert(is_signed_v<long>);
static_assert(not is_signed_v<unsigned long>);
static_assert(is_signed_v<long long>);
static_assert(not is_signed_v<unsigned long long>);
static_assert(is_signed_v<__int128_t>);
static_assert(not is_signed_v<__uint128_t>);
static_assert(is_signed_v<float>);
static_assert(is_signed_v<double>);
static_assert(is_signed_v<long double>);
static_assert(not is_signed_v<void>);
static_assert(not is_signed_v<decltype(nullptr)>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_unsigned)
static_assert(is_unsigned_v<unsigned>);
static_assert(is_unsigned_v<const unsigned>);
static_assert(is_unsigned_v<volatile unsigned>);
static_assert(is_unsigned_v<const volatile unsigned>);
static_assert(not is_unsigned_v<unsigned *>);
static_assert(not is_unsigned_v<unsigned &>);
static_assert(not is_unsigned_v<unsigned []>);
static_assert(not is_unsigned_v<unsigned [42]>);
static_assert(not is_unsigned_v<unsigned ()>);
static_assert(is_unsigned_v<bool>);
static_assert(not is_unsigned_v<A>);
static_assert(not is_unsigned_v<char>);
static_assert(not is_unsigned_v<signed char>);
static_assert(is_unsigned_v<unsigned char>);
static_assert(is_unsigned_v<char8_t>);
static_assert(is_unsigned_v<char16_t>);
static_assert(is_unsigned_v<char32_t>);
// todo : compatibility
static_assert(not is_unsigned_v<wchar_t>);
static_assert(not is_unsigned_v<short>);
static_assert(not is_unsigned_v<signed short>);
static_assert(is_unsigned_v<unsigned short>);
static_assert(not is_unsigned_v<signed>);
static_assert(not is_unsigned_v<signed int>);
static_assert(is_unsigned_v<unsigned int>);
static_assert(not is_unsigned_v<long>);
static_assert(is_unsigned_v<unsigned long>);
static_assert(not is_unsigned_v<long long>);
static_assert(is_unsigned_v<unsigned long long>);
static_assert(not is_unsigned_v<__int128_t>);
static_assert(is_unsigned_v<__uint128_t>);
static_assert(not is_unsigned_v<float>);
static_assert(not is_unsigned_v<double>);
static_assert(not is_unsigned_v<long double>);
static_assert(not is_unsigned_v<void>);
static_assert(not is_unsigned_v<decltype(nullptr)>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_character)
static_assert(is_character_v<char>);
static_assert(is_character_v<const char>);
static_assert(is_character_v<volatile char>);
static_assert(is_character_v<const volatile char>);
static_assert(not is_character_v<char *>);
static_assert(not is_character_v<char &>);
static_assert(not is_character_v<char []>);
static_assert(not is_character_v<char [42]>);
static_assert(not is_character_v<char ()>);
static_assert(not is_character_v<bool>);
static_assert(not is_character_v<A>);
static_assert(is_character_v<signed char>);
static_assert(is_character_v<unsigned char>);
static_assert(is_character_v<char8_t>);
static_assert(is_character_v<char16_t>);
static_assert(is_character_v<char32_t>);
static_assert(is_character_v<wchar_t>);
static_assert(not is_character_v<short>);
static_assert(not is_character_v<signed short>);
static_assert(not is_character_v<unsigned short>);
static_assert(not is_character_v<signed>);
static_assert(not is_character_v<signed int>);
static_assert(not is_character_v<unsigned int>);
static_assert(not is_character_v<long>);
static_assert(not is_character_v<unsigned long>);
static_assert(not is_character_v<long long>);
static_assert(not is_character_v<unsigned long long>);
static_assert(not is_character_v<__int128_t>);
static_assert(not is_character_v<__uint128_t>);
static_assert(not is_character_v<float>);
static_assert(not is_character_v<double>);
static_assert(not is_character_v<long double>);
static_assert(not is_character_v<void>);
static_assert(not is_character_v<decltype(nullptr)>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_array)
static_assert(is_array_v<int []>);
static_assert(is_array_v<const int []>);
static_assert(is_array_v<volatile int []>);
static_assert(is_array_v<const volatile int []>);
static_assert(is_array_v<int [42]>);
static_assert(is_array_v<int [][42]>);
static_assert(is_array_v<int [][42][1][2][3][4]>);
static_assert(not is_array_v<int>);
static_assert(is_array_v<int *[]>);
static_assert(not is_array_v<int (*)[]>);
static_assert(not is_array_v<int (&)[]>);
static_assert(is_array_v<void (*[])()>);
static_assert(not is_array_v<void (*(&)[])()>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_unbounded_array)
static_assert(is_unbounded_array_v<int []>);
static_assert(is_unbounded_array_v<const int []>);
static_assert(is_unbounded_array_v<volatile int []>);
static_assert(is_unbounded_array_v<const volatile int []>);
static_assert(not is_unbounded_array_v<int [42]>);
static_assert(is_unbounded_array_v<int [][42]>);
static_assert(is_unbounded_array_v<int [][42][1][2][3][4]>);
static_assert(not is_unbounded_array_v<int>);
static_assert(is_unbounded_array_v<int *[]>);
static_assert(not is_unbounded_array_v<int (*)[]>);
static_assert(not is_unbounded_array_v<int (&)[]>);
static_assert(is_unbounded_array_v<void (*[])()>);
static_assert(not is_unbounded_array_v<void (*(&)[])()>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_bounded_array)
static_assert(is_bounded_array_v<int [42]>);
static_assert(is_bounded_array_v<const int [42]>);
static_assert(is_bounded_array_v<volatile int [42]>);
static_assert(is_bounded_array_v<const volatile int [42]>);
static_assert(not is_bounded_array_v<int []>);
static_assert(not is_bounded_array_v<int [][42]>);
static_assert(not is_bounded_array_v<int [][42][1][2][3][4]>);
static_assert(not is_bounded_array_v<int>);
static_assert(is_bounded_array_v<int *[42]>);
static_assert(not is_bounded_array_v<int (*)[42]>);
static_assert(not is_bounded_array_v<int (&)[42]>);
static_assert(is_bounded_array_v<void (*[42])()>);
static_assert(not is_bounded_array_v<void (*(&)[42])()>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_enum)
static_assert(is_enum_v<C>);
static_assert(is_enum_v<D>);
static_assert(is_enum_v<const C>);
static_assert(is_enum_v<volatile C>);
static_assert(is_enum_v<const volatile C>);
static_assert(not is_enum_v<int>);
static_assert(not is_enum_v<C []>);
static_assert(not is_enum_v<C [42]>);
static_assert(not is_enum_v<C &>);
static_assert(not is_enum_v<C *>);
static_assert(not is_enum_v<C ()>);
static_assert(not is_enum_v<C (A::*)(D)>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_union)
static_assert(is_union_v<E>);
static_assert(is_union_v<const E>);
static_assert(is_union_v<volatile E>);
static_assert(is_union_v<const volatile E>);
static_assert(not is_union_v<int>);
static_assert(not is_union_v<E []>);
static_assert(not is_union_v<E [42]>);
static_assert(not is_union_v<E &>);
static_assert(not is_union_v<E *>);
static_assert(not is_union_v<E ()>);
static_assert(not is_union_v<E (E::*)(E)>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_class)
static_assert(is_class_v<A>);
static_assert(is_class_v<B>);
static_assert(is_class_v<const A>);
static_assert(is_class_v<volatile A>);
static_assert(is_class_v<const volatile A>);
static_assert(not is_class_v<int>);
static_assert(not is_class_v<A []>);
static_assert(not is_class_v<A [42]>);
static_assert(not is_class_v<A &>);
static_assert(not is_class_v<A *>);
static_assert(not is_class_v<A ()>);
static_assert(not is_class_v<A (B::*)(A)>);
static_assert(not is_class_v<decltype(nullptr)>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_function)
static_assert(is_function_v<void ()>);
static_assert(not is_function_v<void (*)()>);
static_assert(not is_function_v<void (&)()>);
static_assert(not is_function_v<void (&&)()>);
static_assert(not is_function_v<void (A::*)()>);
static_assert(not is_function_v<void (A::*&)()>);
static_assert(not is_function_v<void (A::*&&)()>);
static_assert(is_function_v<void (int)>);
static_assert(is_function_v<void (int) const>);
static_assert(is_function_v<void (int) volatile>);
static_assert(is_function_v<void (int) const noexcept>);
static_assert(is_function_v<void (int) volatile noexcept>);
static_assert(is_function_v<void (int) const volatile noexcept>);
static_assert(is_function_v<void (int) &>);
static_assert(is_function_v<void (int) const &>);
static_assert(is_function_v<void (int) volatile &>);
static_assert(is_function_v<void (int) const & noexcept>);
static_assert(is_function_v<void (int) volatile & noexcept>);
static_assert(is_function_v<void (int) const volatile & noexcept>);
static_assert(is_function_v<void (int) &&>);
static_assert(is_function_v<void (int) const &&>);
static_assert(is_function_v<void (int) volatile &&>);
static_assert(is_function_v<void (int) const && noexcept>);
static_assert(is_function_v<void (int) volatile && noexcept>);
static_assert(is_function_v<void (int) const volatile && noexcept>);
static_assert(is_function_v<void (int, ...)>);
static_assert(is_function_v<void (int, ...) const>);
static_assert(is_function_v<void (int, ...) volatile>);
static_assert(is_function_v<void (int, ...) const noexcept>);
static_assert(is_function_v<void (int, ...) volatile noexcept>);
static_assert(is_function_v<void (int, ...) const volatile noexcept>);
static_assert(is_function_v<void (int, ...) &>);
static_assert(is_function_v<void (int, ...) const &>);
static_assert(is_function_v<void (int, ...) volatile &>);
static_assert(is_function_v<void (int, ...) const & noexcept>);
static_assert(is_function_v<void (int, ...) volatile & noexcept>);
static_assert(is_function_v<void (int, ...) const volatile & noexcept>);
static_assert(is_function_v<void (int, ...) &&>);
static_assert(is_function_v<void (int, ...) const &&>);
static_assert(is_function_v<void (int, ...) volatile &&>);
static_assert(is_function_v<void (int, ...) const && noexcept>);
static_assert(is_function_v<void (int, ...) volatile && noexcept>);
static_assert(is_function_v<void (int, ...) const volatile && noexcept>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_pointer)
static_assert(is_pointer_v<void *>);
static_assert(is_pointer_v<void *const>);
static_assert(is_pointer_v<void *volatile>);
static_assert(is_pointer_v<void *const volatile>);
static_assert(is_pointer_v<const void *>);
static_assert(is_pointer_v<volatile void *>);
static_assert(is_pointer_v<const volatile void *>);
static_assert(is_pointer_v<const void *const>);
static_assert(is_pointer_v<const void *volatile>);
static_assert(is_pointer_v<volatile void *const>);
static_assert(is_pointer_v<volatile void *volatile>);
static_assert(is_pointer_v<const volatile void *>);
static_assert(is_pointer_v<const volatile void *const>);
static_assert(is_pointer_v<const volatile void *volatile>);
static_assert(is_pointer_v<const volatile void *const volatile>);
static_assert(not is_pointer_v<decltype(nullptr)>);
static_assert(is_pointer_v<void (*)()>);
static_assert(is_pointer_v<void (*const)()>);
static_assert(is_pointer_v<void (*volatile)()>);
static_assert(is_pointer_v<void (*const volatile)()>);
static_assert(is_pointer_v<int (*)[]>);
static_assert(not is_pointer_v<int *[]>);
static_assert(not is_pointer_v<void (A::*)()>);
static_assert(not is_pointer_v<int A::*>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_member_pointer)
static_assert(is_member_pointer_v<void (A::*)()>);
static_assert(is_member_pointer_v<void (A::*const)()>);
static_assert(is_member_pointer_v<void (A::*volatile)()>);
static_assert(is_member_pointer_v<void (A::*const volatile)()>);
static_assert(is_member_pointer_v<int A::*>);
static_assert(is_member_pointer_v<int A::*const>);
static_assert(is_member_pointer_v<int A::*volatile>);
static_assert(is_member_pointer_v<int A::*const volatile>);
static_assert(not is_member_pointer_v<void *>);
static_assert(not is_member_pointer_v<void *[]>);
static_assert(not is_member_pointer_v<int (*)[]>);
static_assert(not is_member_pointer_v<void (*)()>);
static_assert(not is_member_pointer_v<void (...) const & noexcept>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_member_function_pointer)
static_assert(is_member_function_pointer_v<void (A::*)()>);
static_assert(is_member_function_pointer_v<void (A::*const)()>);
static_assert(is_member_function_pointer_v<void (A::*volatile)()>);
static_assert(is_member_function_pointer_v<void (A::*const volatile)()>);
static_assert(not is_member_function_pointer_v<int A::*>);
static_assert(not is_member_function_pointer_v<int A::*const>);
static_assert(not is_member_function_pointer_v<int A::*volatile>);
static_assert(not is_member_function_pointer_v<int A::*const volatile>);
static_assert(not is_member_function_pointer_v<void *>);
static_assert(not is_member_function_pointer_v<void *[]>);
static_assert(not is_member_function_pointer_v<int (*)[]>);
static_assert(not is_member_function_pointer_v<void (*)()>);
static_assert(not is_member_function_pointer_v<void (...) const & noexcept>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_member_object_pointer)
static_assert(not is_member_object_pointer_v<void (A::*)()>);
static_assert(not is_member_object_pointer_v<void (A::*const)()>);
static_assert(not is_member_object_pointer_v<void (A::*volatile)()>);
static_assert(not is_member_object_pointer_v<void (A::*const volatile)()>);
static_assert(is_member_object_pointer_v<int A::*>);
static_assert(is_member_object_pointer_v<int A::*const>);
static_assert(is_member_object_pointer_v<int A::*volatile>);
static_assert(is_member_object_pointer_v<int A::*const volatile>);
static_assert(not is_member_object_pointer_v<void *>);
static_assert(not is_member_object_pointer_v<void *[]>);
static_assert(not is_member_object_pointer_v<int (*)[]>);
static_assert(not is_member_object_pointer_v<void (*)()>);
static_assert(not is_member_object_pointer_v<void (...) const & noexcept>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_function_pointer)
static_assert(is_function_pointer_v<void (*)()>);
static_assert(is_function_pointer_v<void (*const)()>);
static_assert(is_function_pointer_v<void (*volatile)()>);
static_assert(is_function_pointer_v<void (*const volatile)()>);
static_assert(not is_function_pointer_v<void ()>);
static_assert(not is_function_pointer_v<void (*[])()>);
static_assert(not is_function_pointer_v<void (&)()>);
static_assert(is_function_pointer_v<void *>);       // void * maybe point to a function
static_assert(is_function_pointer_v<void *const>);
static_assert(is_function_pointer_v<void *volatile>);
static_assert(is_function_pointer_v<void *const volatile>);
static_assert(is_function_pointer_v<const void *>);
static_assert(is_function_pointer_v<const void *const>);
static_assert(is_function_pointer_v<const void *volatile>);
static_assert(is_function_pointer_v<const void *const volatile>);
static_assert(is_function_pointer_v<volatile void *>);
static_assert(is_function_pointer_v<volatile void *const>);
static_assert(is_function_pointer_v<volatile void *volatile>);
static_assert(is_function_pointer_v<volatile void *const volatile>);
static_assert(is_function_pointer_v<const volatile void *>);
static_assert(is_function_pointer_v<const volatile void *const>);
static_assert(is_function_pointer_v<const volatile void *volatile>);
static_assert(is_function_pointer_v<const volatile void *const volatile>);
static_assert(not is_function_pointer_v<decltype(nullptr)>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_lvalue_reference_v)
static_assert(is_lvalue_reference_v<int &>);
static_assert(is_lvalue_reference_v<const int &>);
static_assert(is_lvalue_reference_v<volatile int &>);
static_assert(is_lvalue_reference_v<const volatile int &>);
static_assert(is_lvalue_reference_v<int (&)()>);
static_assert(is_lvalue_reference_v<int (A::*&)()>);
static_assert(is_lvalue_reference_v<int A::*&>);
static_assert(is_lvalue_reference_v<int (&)[]>);
static_assert(is_lvalue_reference_v<int (&)[42]>);
static_assert(is_lvalue_reference_v<int (*&)[]>);
static_assert(is_lvalue_reference_v<int *(&)[]>);
static_assert(not is_lvalue_reference_v<int *>);
static_assert(not is_lvalue_reference_v<int &&>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_rvalue_reference_v)
static_assert(is_rvalue_reference_v<int &&>);
static_assert(is_rvalue_reference_v<const int &&>);
static_assert(is_rvalue_reference_v<volatile int &&>);
static_assert(is_rvalue_reference_v<const volatile int &&>);
static_assert(is_rvalue_reference_v<int (&&)()>);
static_assert(is_rvalue_reference_v<int (A::*&&)()>);
static_assert(is_rvalue_reference_v<int A::*&&>);
static_assert(is_rvalue_reference_v<int (&&)[]>);
static_assert(is_rvalue_reference_v<int (&&)[42]>);
static_assert(is_rvalue_reference_v<int (*&&)[]>);
static_assert(is_rvalue_reference_v<int *(&&)[]>);
static_assert(not is_rvalue_reference_v<int *>);
static_assert(not is_rvalue_reference_v<int &>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_reference_v)
static_assert(is_reference_v<int &>);
static_assert(is_reference_v<const int &>);
static_assert(is_reference_v<volatile int &>);
static_assert(is_reference_v<const volatile int &>);
static_assert(is_reference_v<int (&)()>);
static_assert(is_reference_v<int (A::*&)()>);
static_assert(is_reference_v<int A::*&>);
static_assert(is_reference_v<int (&)[]>);
static_assert(is_reference_v<int (&)[42]>);
static_assert(is_reference_v<int (*&)[]>);
static_assert(is_reference_v<int *(&)[]>);
static_assert(is_reference_v<int &&>);
static_assert(is_reference_v<const int &&>);
static_assert(is_reference_v<volatile int &&>);
static_assert(is_reference_v<const volatile int &&>);
static_assert(is_reference_v<int (&&)()>);
static_assert(is_reference_v<int (A::*&&)()>);
static_assert(is_reference_v<int A::*&&>);
static_assert(is_reference_v<int (&&)[]>);
static_assert(is_reference_v<int (&&)[42]>);
static_assert(is_reference_v<int (*&&)[]>);
static_assert(is_reference_v<int *(&&)[]>);
static_assert(not is_reference_v<int *>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_const_reference_v)
static_assert(is_const_reference_v<const int &>);
static_assert(is_const_reference_v<const volatile int &>);
static_assert(not is_const_reference_v<int &>);
static_assert(not is_const_reference_v<volatile int &>);
static_assert(not is_const_reference_v<int &&>);
static_assert(not is_const_reference_v<const int &&>);
static_assert(not is_const_reference_v<volatile int &&>);
static_assert(not is_const_reference_v<const volatile int &&>);
static_assert(is_const_reference_v<void (A::*const &)()>);
static_assert(is_const_reference_v<int A::*const &>);
static_assert(is_const_reference_v<const int (&)[]>);
static_assert(is_const_reference_v<int (*const &)[]>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_type)
static_assert(is_type_v<void>);
static_assert(is_type_v<int>);
static_assert(is_type_v<void ()>);
static_assert(is_type_v<A>);
static_assert(is_type_v<B>);
static_assert(is_type_v<C>);
static_assert(is_type_v<D>);
static_assert(is_type_v<E>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_complete)
static_assert(is_complete_v<int>);
static_assert(is_complete_v<int *>);
static_assert(is_complete_v<int &>);
static_assert(is_complete_v<void (*)()>);
static_assert(is_complete_v<int [42]>);
static_assert(not is_complete_v<int []>);
static_assert(is_complete_v<int A::*>);
static_assert(is_complete_v<int (A::*)()>);
static_assert(not is_complete_v<void>);
static_assert(not is_complete_v<void ()>);
static_assert(is_complete_v<A>);
static_assert(not is_complete_v<B>);
static_assert(is_complete_v<C>);
static_assert(is_complete_v<D>);
static_assert(not is_complete_v<E>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test helper classes)
struct unit_test_stateless {};
struct unit_test_standard_layout {
    int a;
    char b;
    void *c;
    double d[42];
    void f();
    int g(int);
};
struct unit_test_non_standard_layout {
    virtual ~unit_test_non_standard_layout();
};
struct unit_test_pure_virtual {
    void *p;
    virtual ~unit_test_pure_virtual() = 0;
};
struct unit_test_derived_from_stateless : unit_test_stateless {};
struct unit_test_derived_from_standard_layout : unit_test_standard_layout {};
struct unit_test_derived_from_non_standard_layout : unit_test_non_standard_layout {};
struct unit_test_derived_from_pure_virtual : unit_test_pure_virtual {};
struct unit_test_derived_from_stateless_standard_layout : unit_test_stateless, unit_test_standard_layout {};
struct unit_test_derived_from_stateless_non_standard_layout : unit_test_stateless, unit_test_non_standard_layout {};
struct unit_test_derived_from_stateless_pure_virtual : unit_test_stateless, unit_test_pure_virtual {};
struct unit_test_derived_from_standard_layout_non_standard_layout : unit_test_standard_layout, unit_test_non_standard_layout {};
struct unit_test_derived_from_standard_layout_pure_virtual : unit_test_standard_layout, unit_test_pure_virtual {};
struct unit_test_derived_from_non_standard_layout_pure_virtual : unit_test_non_standard_layout, unit_test_pure_virtual {};
struct unit_test_derived_from_stateless_standard_layout_non_standard_layout : unit_test_stateless, unit_test_standard_layout, unit_test_non_standard_layout {};
struct unit_test_derived_from_stateless_standard_layout_pure_virtual : unit_test_stateless, unit_test_standard_layout, unit_test_pure_virtual {};
struct unit_test_derived_from_standard_layout_non_standard_layout_pure_virtual : unit_test_standard_layout, unit_test_non_standard_layout, unit_test_pure_virtual {};
struct unit_test_derived_from_all : unit_test_stateless, unit_test_standard_layout, unit_test_non_standard_layout, unit_test_pure_virtual {};
struct unit_test_virtual_derived_from_stateless : virtual unit_test_stateless {};
struct unit_test_virtual_derived_from_standard_layout : virtual unit_test_standard_layout {};
struct unit_test_virtual_derived_from_non_standard_layout : virtual unit_test_non_standard_layout {};
struct unit_test_virtual_derived_from_pure_virtual : virtual unit_test_pure_virtual {};
struct unit_test_virtual_derived_from_stateless_standard_layout : unit_test_virtual_derived_from_stateless, unit_test_virtual_derived_from_standard_layout {};
struct unit_test_virtual_derived_from_stateless_non_standard_layout : unit_test_virtual_derived_from_stateless, unit_test_virtual_derived_from_non_standard_layout {};
struct unit_test_virtual_derived_from_stateless_pure_virtual : unit_test_virtual_derived_from_stateless, unit_test_virtual_derived_from_pure_virtual {};
struct unit_test_virtual_derived_from_standard_layout_non_standard_layout : unit_test_virtual_derived_from_standard_layout, unit_test_virtual_derived_from_non_standard_layout {};
struct unit_test_virtual_derived_from_standard_layout_pure_virtual : unit_test_virtual_derived_from_standard_layout, unit_test_virtual_derived_from_pure_virtual {};
struct unit_test_virtual_derived_from_non_standard_layout_pure_virtual : unit_test_virtual_derived_from_non_standard_layout, unit_test_virtual_derived_from_pure_virtual {};
struct unit_test_virtual_derived_from_stateless_standard_layout_non_standard_layout : unit_test_virtual_derived_from_stateless, unit_test_virtual_derived_from_standard_layout, unit_test_virtual_derived_from_non_standard_layout {};
struct unit_test_virtual_derived_from_stateless_standard_layout_pure_virtual : unit_test_virtual_derived_from_stateless, unit_test_virtual_derived_from_standard_layout, unit_test_virtual_derived_from_pure_virtual {};
struct unit_test_virtual_derived_from_standard_layout_non_standard_layout_pure_virtual : unit_test_virtual_derived_from_standard_layout, unit_test_virtual_derived_from_non_standard_layout, unit_test_virtual_derived_from_pure_virtual {};
struct unit_test_virtual_derived_from_all : unit_test_virtual_derived_from_stateless, unit_test_virtual_derived_from_standard_layout, unit_test_virtual_derived_from_non_standard_layout, unit_test_virtual_derived_from_pure_virtual {};
struct unit_test_stateless_finally final {};
struct unit_test_standard_layout_finally final {
    int a;
    char b;
    void *c;
    double d[42];
    void f();
    int g(int);
};
struct unit_test_non_standard_layout_finally final {
    virtual ~unit_test_non_standard_layout_finally();
};
struct unit_test_pure_virtual_finally final {
    virtual ~unit_test_pure_virtual_finally() = 0;
};
struct unit_test_derived_from_stateless_finally final : unit_test_stateless {};
struct unit_test_derived_from_standard_layout_finally final : unit_test_standard_layout {};
struct unit_test_derived_from_non_standard_layout_finally final : unit_test_non_standard_layout {};
struct unit_test_derived_from_pure_virtual_finally final : unit_test_pure_virtual {};
struct unit_test_derived_from_stateless_standard_layout_finally final : unit_test_stateless, unit_test_standard_layout {};
struct unit_test_derived_from_stateless_non_standard_layout_finally final : unit_test_stateless, unit_test_non_standard_layout {};
struct unit_test_derived_from_stateless_pure_virtual_finally final : unit_test_stateless, unit_test_pure_virtual {};
struct unit_test_derived_from_standard_layout_non_standard_layout_finally final : unit_test_standard_layout, unit_test_non_standard_layout {};
struct unit_test_derived_from_standard_layout_pure_virtual_finally final : unit_test_standard_layout, unit_test_pure_virtual {};
struct unit_test_derived_from_non_standard_layout_pure_virtual_finally final : unit_test_non_standard_layout, unit_test_pure_virtual {};
struct unit_test_derived_from_stateless_standard_layout_non_standard_layout_finally final : unit_test_stateless, unit_test_standard_layout, unit_test_non_standard_layout {};
struct unit_test_derived_from_stateless_standard_layout_pure_virtual_finally final : unit_test_stateless, unit_test_standard_layout, unit_test_pure_virtual {};
struct unit_test_derived_from_standard_layout_non_standard_layout_pure_virtual_finally final : unit_test_standard_layout, unit_test_non_standard_layout, unit_test_pure_virtual {};
struct unit_test_derived_from_all_finally final : unit_test_stateless, unit_test_standard_layout, unit_test_non_standard_layout, unit_test_pure_virtual {};
struct unit_test_virtual_derived_from_stateless_finally final : virtual unit_test_stateless {};
struct unit_test_virtual_derived_from_standard_layout_finally final : virtual unit_test_standard_layout {};
struct unit_test_virtual_derived_from_non_standard_layout_finally final : virtual unit_test_non_standard_layout {};
struct unit_test_virtual_derived_from_pure_virtual_finally final : virtual unit_test_pure_virtual {};
struct unit_test_virtual_derived_from_stateless_standard_layout_finally final : unit_test_virtual_derived_from_stateless, unit_test_virtual_derived_from_standard_layout {};
struct unit_test_virtual_derived_from_stateless_non_standard_layout_finally final : unit_test_virtual_derived_from_stateless, unit_test_virtual_derived_from_non_standard_layout {};
struct unit_test_virtual_derived_from_stateless_pure_virtual_finally final : unit_test_virtual_derived_from_stateless, unit_test_virtual_derived_from_pure_virtual {};
struct unit_test_virtual_derived_from_standard_layout_non_standard_layout_finally final : unit_test_virtual_derived_from_standard_layout, unit_test_virtual_derived_from_non_standard_layout {};
struct unit_test_virtual_derived_from_standard_layout_pure_virtual_finally final : unit_test_virtual_derived_from_standard_layout, unit_test_virtual_derived_from_pure_virtual {};
struct unit_test_virtual_derived_from_non_standard_layout_pure_virtual_finally final : unit_test_virtual_derived_from_non_standard_layout, unit_test_virtual_derived_from_pure_virtual {};
struct unit_test_virtual_derived_from_stateless_standard_layout_non_standard_layout_finally final : unit_test_virtual_derived_from_stateless, unit_test_virtual_derived_from_standard_layout, unit_test_virtual_derived_from_non_standard_layout {};
struct unit_test_virtual_derived_from_stateless_standard_layout_pure_virtual_finally final : unit_test_virtual_derived_from_stateless, unit_test_virtual_derived_from_standard_layout, unit_test_virtual_derived_from_pure_virtual {};
struct unit_test_virtual_derived_from_standard_layout_non_standard_layout_pure_virtual_finally final : unit_test_virtual_derived_from_standard_layout, unit_test_virtual_derived_from_non_standard_layout, unit_test_virtual_derived_from_pure_virtual {};
struct unit_test_virtual_derived_from_all_finally final : unit_test_virtual_derived_from_stateless, unit_test_virtual_derived_from_standard_layout, unit_test_virtual_derived_from_non_standard_layout, unit_test_virtual_derived_from_pure_virtual {};
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_pod)
static_assert(is_pod_v<int>);
static_assert(is_pod_v<const int>);
static_assert(is_pod_v<volatile int>);
static_assert(is_pod_v<const volatile int>);
static_assert(not is_pod_v<void>);
static_assert(not is_pod_v<const void>);
static_assert(not is_pod_v<volatile void>);
static_assert(not is_pod_v<const volatile void>);
static_assert(is_pod_v<void *>);
static_assert(is_pod_v<int [42]>);
static_assert(is_pod_v<int []>);
static_assert(not is_pod_v<int &>);
static_assert(not is_pod_v<const int &>);
static_assert(not is_pod_v<volatile int &>);
static_assert(not is_pod_v<const volatile int &>);
static_assert(not is_pod_v<int ()>);
static_assert(is_pod_v<void (*)()>);
static_assert(not is_pod_v<void (&)()>);
static_assert(not is_pod_v<void (&&)()>);
static_assert(is_pod_v<int (A::*)()>);
static_assert(not is_pod_v<int (A::*&)()>);
static_assert(is_pod_v<A>);
//static_assert(not is_pod_v<B>);     // undefined behavior
static_assert(is_pod_v<C>);
static_assert(is_pod_v<D>);
//static_assert(is_pod_v<E>);     // undefined behavior
static_assert(is_pod_v<unit_test_stateless>);
static_assert(is_pod_v<unit_test_standard_layout>);
static_assert(not is_pod_v<unit_test_non_standard_layout>);
static_assert(not is_pod_v<unit_test_pure_virtual>);
static_assert(is_pod_v<unit_test_derived_from_stateless>);
static_assert(is_pod_v<unit_test_derived_from_standard_layout>);
static_assert(not is_pod_v<unit_test_derived_from_non_standard_layout>);
static_assert(not is_pod_v<unit_test_derived_from_pure_virtual>);
static_assert(is_pod_v<unit_test_derived_from_stateless_standard_layout>);
static_assert(not is_pod_v<unit_test_derived_from_stateless_non_standard_layout>);
static_assert(not is_pod_v<unit_test_derived_from_stateless_pure_virtual>);
static_assert(not is_pod_v<unit_test_derived_from_standard_layout_non_standard_layout>);
static_assert(not is_pod_v<unit_test_derived_from_standard_layout_pure_virtual>);
static_assert(not is_pod_v<unit_test_derived_from_non_standard_layout_pure_virtual>);
static_assert(not is_pod_v<unit_test_derived_from_stateless_standard_layout_non_standard_layout>);
static_assert(not is_pod_v<unit_test_derived_from_stateless_standard_layout_pure_virtual>);
static_assert(not is_pod_v<unit_test_derived_from_standard_layout_non_standard_layout_pure_virtual>);
static_assert(not is_pod_v<unit_test_derived_from_all>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_stateless>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_standard_layout>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_non_standard_layout>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_pure_virtual>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_stateless>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_standard_layout>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_non_standard_layout>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_pure_virtual>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_stateless_standard_layout>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_stateless_non_standard_layout>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_stateless_pure_virtual>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_standard_layout_non_standard_layout>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_standard_layout_pure_virtual>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_non_standard_layout_pure_virtual>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_stateless_standard_layout_non_standard_layout>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_stateless_standard_layout_pure_virtual>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_standard_layout_non_standard_layout_pure_virtual>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_all>);
static_assert(is_pod_v<unit_test_stateless_finally>);
static_assert(is_pod_v<unit_test_standard_layout_finally>);
static_assert(not is_pod_v<unit_test_non_standard_layout_finally>);
static_assert(not is_pod_v<unit_test_pure_virtual_finally>);
static_assert(is_pod_v<unit_test_derived_from_stateless_finally>);
static_assert(is_pod_v<unit_test_derived_from_standard_layout_finally>);
static_assert(not is_pod_v<unit_test_derived_from_non_standard_layout_finally>);
static_assert(not is_pod_v<unit_test_derived_from_pure_virtual_finally>);
static_assert(is_pod_v<unit_test_derived_from_stateless_standard_layout_finally>);
static_assert(not is_pod_v<unit_test_derived_from_stateless_non_standard_layout_finally>);
static_assert(not is_pod_v<unit_test_derived_from_stateless_pure_virtual_finally>);
static_assert(not is_pod_v<unit_test_derived_from_standard_layout_non_standard_layout_finally>);
static_assert(not is_pod_v<unit_test_derived_from_standard_layout_pure_virtual_finally>);
static_assert(not is_pod_v<unit_test_derived_from_non_standard_layout_pure_virtual_finally>);
static_assert(not is_pod_v<unit_test_derived_from_stateless_standard_layout_non_standard_layout_finally>);
static_assert(not is_pod_v<unit_test_derived_from_stateless_standard_layout_pure_virtual_finally>);
static_assert(not is_pod_v<unit_test_derived_from_standard_layout_non_standard_layout_pure_virtual_finally>);
static_assert(not is_pod_v<unit_test_derived_from_all_finally>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_stateless_finally>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_standard_layout_finally>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_non_standard_layout_finally>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_pure_virtual_finally>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_stateless_finally>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_standard_layout_finally>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_non_standard_layout_finally>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_pure_virtual_finally>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_stateless_standard_layout_finally>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_stateless_non_standard_layout_finally>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_stateless_pure_virtual_finally>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_standard_layout_non_standard_layout_finally>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_standard_layout_pure_virtual_finally>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_non_standard_layout_pure_virtual_finally>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_stateless_standard_layout_non_standard_layout_finally>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_stateless_standard_layout_pure_virtual_finally>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_standard_layout_non_standard_layout_pure_virtual_finally>);
static_assert(not is_pod_v<unit_test_virtual_derived_from_all_finally>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_empty)
static_assert(is_empty_v<A>);
//static_assert(is_empty_v<B>);     // undefined behavior
static_assert(not is_empty_v<C>);
static_assert(not is_empty_v<D>);
static_assert(not is_empty_v<E>);
static_assert(not is_empty_v<int>);
static_assert(not is_empty_v<void>);
static_assert(not is_empty_v<void ()>);
static_assert(is_empty_v<unit_test_stateless>);
static_assert(not is_empty_v<unit_test_standard_layout>);
static_assert(not is_empty_v<unit_test_non_standard_layout>);
static_assert(not is_empty_v<unit_test_pure_virtual>);
static_assert(is_empty_v<unit_test_derived_from_stateless>);
static_assert(not is_empty_v<unit_test_derived_from_standard_layout>);
static_assert(not is_empty_v<unit_test_derived_from_non_standard_layout>);
static_assert(not is_empty_v<unit_test_derived_from_pure_virtual>);
static_assert(not is_empty_v<unit_test_derived_from_stateless_standard_layout>);
static_assert(not is_empty_v<unit_test_derived_from_stateless_non_standard_layout>);
static_assert(not is_empty_v<unit_test_derived_from_stateless_pure_virtual>);
static_assert(not is_empty_v<unit_test_derived_from_standard_layout_non_standard_layout>);
static_assert(not is_empty_v<unit_test_derived_from_standard_layout_pure_virtual>);
static_assert(not is_empty_v<unit_test_derived_from_non_standard_layout_pure_virtual>);
static_assert(not is_empty_v<unit_test_derived_from_stateless_standard_layout_non_standard_layout>);
static_assert(not is_empty_v<unit_test_derived_from_stateless_standard_layout_pure_virtual>);
static_assert(not is_empty_v<unit_test_derived_from_standard_layout_non_standard_layout_pure_virtual>);
static_assert(not is_empty_v<unit_test_derived_from_all>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_stateless>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_standard_layout>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_non_standard_layout>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_pure_virtual>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_stateless>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_standard_layout>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_non_standard_layout>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_pure_virtual>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_stateless_standard_layout>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_stateless_non_standard_layout>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_stateless_pure_virtual>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_standard_layout_non_standard_layout>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_standard_layout_pure_virtual>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_non_standard_layout_pure_virtual>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_stateless_standard_layout_non_standard_layout>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_stateless_standard_layout_pure_virtual>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_standard_layout_non_standard_layout_pure_virtual>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_all>);
static_assert(is_empty_v<unit_test_stateless_finally>);
static_assert(not is_empty_v<unit_test_standard_layout_finally>);
static_assert(not is_empty_v<unit_test_non_standard_layout_finally>);
static_assert(not is_empty_v<unit_test_pure_virtual_finally>);
static_assert(is_empty_v<unit_test_derived_from_stateless_finally>);
static_assert(not is_empty_v<unit_test_derived_from_standard_layout_finally>);
static_assert(not is_empty_v<unit_test_derived_from_non_standard_layout_finally>);
static_assert(not is_empty_v<unit_test_derived_from_pure_virtual_finally>);
static_assert(not is_empty_v<unit_test_derived_from_stateless_standard_layout_finally>);
static_assert(not is_empty_v<unit_test_derived_from_stateless_non_standard_layout_finally>);
static_assert(not is_empty_v<unit_test_derived_from_stateless_pure_virtual_finally>);
static_assert(not is_empty_v<unit_test_derived_from_standard_layout_non_standard_layout_finally>);
static_assert(not is_empty_v<unit_test_derived_from_standard_layout_pure_virtual_finally>);
static_assert(not is_empty_v<unit_test_derived_from_non_standard_layout_pure_virtual_finally>);
static_assert(not is_empty_v<unit_test_derived_from_stateless_standard_layout_non_standard_layout_finally>);
static_assert(not is_empty_v<unit_test_derived_from_stateless_standard_layout_pure_virtual_finally>);
static_assert(not is_empty_v<unit_test_derived_from_standard_layout_non_standard_layout_pure_virtual_finally>);
static_assert(not is_empty_v<unit_test_derived_from_all_finally>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_stateless_finally>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_standard_layout_finally>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_non_standard_layout_finally>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_pure_virtual_finally>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_stateless_finally>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_standard_layout_finally>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_non_standard_layout_finally>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_pure_virtual_finally>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_stateless_standard_layout_finally>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_stateless_non_standard_layout_finally>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_stateless_pure_virtual_finally>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_standard_layout_non_standard_layout_finally>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_standard_layout_pure_virtual_finally>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_non_standard_layout_pure_virtual_finally>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_stateless_standard_layout_non_standard_layout_finally>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_stateless_standard_layout_pure_virtual_finally>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_standard_layout_non_standard_layout_pure_virtual_finally>);
static_assert(not is_empty_v<unit_test_virtual_derived_from_all_finally>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_literal_type)
static_assert(is_literal_type_v<int>);
static_assert(is_literal_type_v<const int>);
static_assert(is_literal_type_v<volatile int>);
static_assert(is_literal_type_v<const volatile int>);
static_assert(is_literal_type_v<void>);
static_assert(is_literal_type_v<const void>);
static_assert(is_literal_type_v<volatile void>);
static_assert(is_literal_type_v<const volatile void>);
static_assert(is_literal_type_v<void *>);
static_assert(is_literal_type_v<int [42]>);
static_assert(is_literal_type_v<int []>);
static_assert(is_literal_type_v<int &>);
static_assert(is_literal_type_v<const int &>);
static_assert(is_literal_type_v<volatile int &>);
static_assert(is_literal_type_v<const volatile int &>);
static_assert(not is_literal_type_v<int ()>);
static_assert(is_literal_type_v<void (*)()>);
static_assert(is_literal_type_v<void (&)()>);
static_assert(is_literal_type_v<void (&&)()>);
static_assert(is_literal_type_v<int (A::*)()>);
static_assert(is_literal_type_v<int (A::*&)()>);
static_assert(is_literal_type_v<A>);
//static_assert(not is_literal_type_v<B>);     // undefined behavior
static_assert(is_literal_type_v<C>);
static_assert(is_literal_type_v<D>);
//static_assert(is_literal_type_v<E>);     // undefined behavior
static_assert(is_literal_type_v<unit_test_stateless>);
static_assert(is_literal_type_v<unit_test_standard_layout>);
static_assert(not is_literal_type_v<unit_test_non_standard_layout>);
static_assert(not is_literal_type_v<unit_test_pure_virtual>);
static_assert(is_literal_type_v<unit_test_derived_from_stateless>);
static_assert(is_literal_type_v<unit_test_derived_from_standard_layout>);
static_assert(not is_literal_type_v<unit_test_derived_from_non_standard_layout>);
static_assert(not is_literal_type_v<unit_test_derived_from_pure_virtual>);
static_assert(is_literal_type_v<unit_test_derived_from_stateless_standard_layout>);
static_assert(not is_literal_type_v<unit_test_derived_from_stateless_non_standard_layout>);
static_assert(not is_literal_type_v<unit_test_derived_from_stateless_pure_virtual>);
static_assert(not is_literal_type_v<unit_test_derived_from_standard_layout_non_standard_layout>);
static_assert(not is_literal_type_v<unit_test_derived_from_standard_layout_pure_virtual>);
static_assert(not is_literal_type_v<unit_test_derived_from_non_standard_layout_pure_virtual>);
static_assert(not is_literal_type_v<unit_test_derived_from_stateless_standard_layout_non_standard_layout>);
static_assert(not is_literal_type_v<unit_test_derived_from_stateless_standard_layout_pure_virtual>);
static_assert(not is_literal_type_v<unit_test_derived_from_standard_layout_non_standard_layout_pure_virtual>);
static_assert(not is_literal_type_v<unit_test_derived_from_all>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_stateless>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_standard_layout>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_non_standard_layout>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_pure_virtual>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_stateless>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_standard_layout>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_non_standard_layout>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_pure_virtual>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_stateless_standard_layout>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_stateless_non_standard_layout>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_stateless_pure_virtual>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_standard_layout_non_standard_layout>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_standard_layout_pure_virtual>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_non_standard_layout_pure_virtual>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_stateless_standard_layout_non_standard_layout>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_stateless_standard_layout_pure_virtual>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_standard_layout_non_standard_layout_pure_virtual>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_all>);
static_assert(is_literal_type_v<unit_test_stateless_finally>);
static_assert(is_literal_type_v<unit_test_standard_layout_finally>);
static_assert(not is_literal_type_v<unit_test_non_standard_layout_finally>);
static_assert(not is_literal_type_v<unit_test_pure_virtual_finally>);
static_assert(is_literal_type_v<unit_test_derived_from_stateless_finally>);
static_assert(is_literal_type_v<unit_test_derived_from_standard_layout_finally>);
static_assert(not is_literal_type_v<unit_test_derived_from_non_standard_layout_finally>);
static_assert(not is_literal_type_v<unit_test_derived_from_pure_virtual_finally>);
static_assert(is_literal_type_v<unit_test_derived_from_stateless_standard_layout_finally>);
static_assert(not is_literal_type_v<unit_test_derived_from_stateless_non_standard_layout_finally>);
static_assert(not is_literal_type_v<unit_test_derived_from_stateless_pure_virtual_finally>);
static_assert(not is_literal_type_v<unit_test_derived_from_standard_layout_non_standard_layout_finally>);
static_assert(not is_literal_type_v<unit_test_derived_from_standard_layout_pure_virtual_finally>);
static_assert(not is_literal_type_v<unit_test_derived_from_non_standard_layout_pure_virtual_finally>);
static_assert(not is_literal_type_v<unit_test_derived_from_stateless_standard_layout_non_standard_layout_finally>);
static_assert(not is_literal_type_v<unit_test_derived_from_stateless_standard_layout_pure_virtual_finally>);
static_assert(not is_literal_type_v<unit_test_derived_from_standard_layout_non_standard_layout_pure_virtual_finally>);
static_assert(not is_literal_type_v<unit_test_derived_from_all_finally>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_stateless_finally>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_standard_layout_finally>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_non_standard_layout_finally>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_pure_virtual_finally>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_stateless_finally>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_standard_layout_finally>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_non_standard_layout_finally>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_pure_virtual_finally>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_stateless_standard_layout_finally>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_stateless_non_standard_layout_finally>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_stateless_pure_virtual_finally>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_standard_layout_non_standard_layout_finally>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_standard_layout_pure_virtual_finally>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_non_standard_layout_pure_virtual_finally>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_stateless_standard_layout_non_standard_layout_finally>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_stateless_standard_layout_pure_virtual_finally>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_standard_layout_non_standard_layout_pure_virtual_finally>);
static_assert(not is_literal_type_v<unit_test_virtual_derived_from_all_finally>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds:is_standard_layout)
static_assert(is_standard_layout_v<int>);
static_assert(is_standard_layout_v<const int>);
static_assert(is_standard_layout_v<volatile int>);
static_assert(is_standard_layout_v<const volatile int>);
static_assert(not is_standard_layout_v<void>);
static_assert(not is_standard_layout_v<const void>);
static_assert(not is_standard_layout_v<volatile void>);
static_assert(not is_standard_layout_v<const volatile void>);
static_assert(is_standard_layout_v<void *>);
static_assert(is_standard_layout_v<int [42]>);
static_assert(is_standard_layout_v<int []>);
static_assert(not is_standard_layout_v<int &>);
static_assert(not is_standard_layout_v<const int &>);
static_assert(not is_standard_layout_v<volatile int &>);
static_assert(not is_standard_layout_v<const volatile int &>);
static_assert(not is_standard_layout_v<int ()>);
static_assert(is_standard_layout_v<void (*)()>);
static_assert(not is_standard_layout_v<void (&)()>);
static_assert(not is_standard_layout_v<void (&&)()>);
static_assert(is_standard_layout_v<int (A::*)()>);
static_assert(not is_standard_layout_v<int (A::*&)()>);
static_assert(is_standard_layout_v<A>);
//static_assert(not is_standard_layout_v<B>);     // undefined behavior
static_assert(is_standard_layout_v<C>);
static_assert(is_standard_layout_v<D>);
//static_assert(is_standard_layout_v<E>);     // undefined behavior
static_assert(is_standard_layout_v<unit_test_stateless>);
static_assert(is_standard_layout_v<unit_test_standard_layout>);
static_assert(not is_standard_layout_v<unit_test_non_standard_layout>);
static_assert(not is_standard_layout_v<unit_test_pure_virtual>);
static_assert(is_standard_layout_v<unit_test_derived_from_stateless>);
static_assert(is_standard_layout_v<unit_test_derived_from_standard_layout>);
static_assert(not is_standard_layout_v<unit_test_derived_from_non_standard_layout>);
static_assert(not is_standard_layout_v<unit_test_derived_from_pure_virtual>);
static_assert(is_standard_layout_v<unit_test_derived_from_stateless_standard_layout>);
static_assert(not is_standard_layout_v<unit_test_derived_from_stateless_non_standard_layout>);
static_assert(not is_standard_layout_v<unit_test_derived_from_stateless_pure_virtual>);
static_assert(not is_standard_layout_v<unit_test_derived_from_standard_layout_non_standard_layout>);
static_assert(not is_standard_layout_v<unit_test_derived_from_standard_layout_pure_virtual>);
static_assert(not is_standard_layout_v<unit_test_derived_from_non_standard_layout_pure_virtual>);
static_assert(not is_standard_layout_v<unit_test_derived_from_stateless_standard_layout_non_standard_layout>);
static_assert(not is_standard_layout_v<unit_test_derived_from_stateless_standard_layout_pure_virtual>);
static_assert(not is_standard_layout_v<unit_test_derived_from_standard_layout_non_standard_layout_pure_virtual>);
static_assert(not is_standard_layout_v<unit_test_derived_from_all>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_stateless>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_standard_layout>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_non_standard_layout>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_pure_virtual>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_stateless>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_standard_layout>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_non_standard_layout>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_pure_virtual>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_stateless_standard_layout>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_stateless_non_standard_layout>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_stateless_pure_virtual>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_standard_layout_non_standard_layout>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_standard_layout_pure_virtual>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_non_standard_layout_pure_virtual>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_stateless_standard_layout_non_standard_layout>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_stateless_standard_layout_pure_virtual>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_standard_layout_non_standard_layout_pure_virtual>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_all>);
static_assert(is_standard_layout_v<unit_test_stateless_finally>);
static_assert(is_standard_layout_v<unit_test_standard_layout_finally>);
static_assert(not is_standard_layout_v<unit_test_non_standard_layout_finally>);
static_assert(not is_standard_layout_v<unit_test_pure_virtual_finally>);
static_assert(is_standard_layout_v<unit_test_derived_from_stateless_finally>);
static_assert(is_standard_layout_v<unit_test_derived_from_standard_layout_finally>);
static_assert(not is_standard_layout_v<unit_test_derived_from_non_standard_layout_finally>);
static_assert(not is_standard_layout_v<unit_test_derived_from_pure_virtual_finally>);
static_assert(is_standard_layout_v<unit_test_derived_from_stateless_standard_layout_finally>);
static_assert(not is_standard_layout_v<unit_test_derived_from_stateless_non_standard_layout_finally>);
static_assert(not is_standard_layout_v<unit_test_derived_from_stateless_pure_virtual_finally>);
static_assert(not is_standard_layout_v<unit_test_derived_from_standard_layout_non_standard_layout_finally>);
static_assert(not is_standard_layout_v<unit_test_derived_from_standard_layout_pure_virtual_finally>);
static_assert(not is_standard_layout_v<unit_test_derived_from_non_standard_layout_pure_virtual_finally>);
static_assert(not is_standard_layout_v<unit_test_derived_from_stateless_standard_layout_non_standard_layout_finally>);
static_assert(not is_standard_layout_v<unit_test_derived_from_stateless_standard_layout_pure_virtual_finally>);
static_assert(not is_standard_layout_v<unit_test_derived_from_standard_layout_non_standard_layout_pure_virtual_finally>);
static_assert(not is_standard_layout_v<unit_test_derived_from_all_finally>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_stateless_finally>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_standard_layout_finally>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_non_standard_layout_finally>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_pure_virtual_finally>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_stateless_finally>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_standard_layout_finally>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_non_standard_layout_finally>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_pure_virtual_finally>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_stateless_standard_layout_finally>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_stateless_non_standard_layout_finally>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_stateless_pure_virtual_finally>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_standard_layout_non_standard_layout_finally>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_standard_layout_pure_virtual_finally>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_non_standard_layout_pure_virtual_finally>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_stateless_standard_layout_non_standard_layout_finally>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_stateless_standard_layout_pure_virtual_finally>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_standard_layout_non_standard_layout_pure_virtual_finally>);
static_assert(not is_standard_layout_v<unit_test_virtual_derived_from_all_finally>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_polymorphic)
static_assert(not is_polymorphic_v<unit_test_stateless>);
static_assert(not is_polymorphic_v<unit_test_standard_layout>);
static_assert(is_polymorphic_v<unit_test_non_standard_layout>);
static_assert(is_polymorphic_v<unit_test_pure_virtual>);
static_assert(not is_polymorphic_v<unit_test_derived_from_stateless>);
static_assert(not is_polymorphic_v<unit_test_derived_from_standard_layout>);
static_assert(is_polymorphic_v<unit_test_derived_from_non_standard_layout>);
static_assert(is_polymorphic_v<unit_test_derived_from_pure_virtual>);
static_assert(not is_polymorphic_v<unit_test_derived_from_stateless_standard_layout>);
static_assert(is_polymorphic_v<unit_test_derived_from_stateless_non_standard_layout>);
static_assert(is_polymorphic_v<unit_test_derived_from_stateless_pure_virtual>);
static_assert(is_polymorphic_v<unit_test_derived_from_standard_layout_non_standard_layout>);
static_assert(is_polymorphic_v<unit_test_derived_from_standard_layout_pure_virtual>);
static_assert(is_polymorphic_v<unit_test_derived_from_non_standard_layout_pure_virtual>);
static_assert(is_polymorphic_v<unit_test_derived_from_stateless_standard_layout_non_standard_layout>);
static_assert(is_polymorphic_v<unit_test_derived_from_stateless_standard_layout_pure_virtual>);
static_assert(is_polymorphic_v<unit_test_derived_from_standard_layout_non_standard_layout_pure_virtual>);
static_assert(is_polymorphic_v<unit_test_derived_from_all>);
static_assert(not is_polymorphic_v<unit_test_virtual_derived_from_stateless>);
static_assert(not is_polymorphic_v<unit_test_virtual_derived_from_standard_layout>);
static_assert(is_polymorphic_v<unit_test_virtual_derived_from_non_standard_layout>);
static_assert(is_polymorphic_v<unit_test_virtual_derived_from_pure_virtual>);
static_assert(not is_polymorphic_v<unit_test_virtual_derived_from_stateless>);
static_assert(not is_polymorphic_v<unit_test_virtual_derived_from_standard_layout>);
static_assert(is_polymorphic_v<unit_test_virtual_derived_from_non_standard_layout>);
static_assert(is_polymorphic_v<unit_test_virtual_derived_from_pure_virtual>);
static_assert(not is_polymorphic_v<unit_test_virtual_derived_from_stateless_standard_layout>);
static_assert(is_polymorphic_v<unit_test_virtual_derived_from_stateless_non_standard_layout>);
static_assert(is_polymorphic_v<unit_test_virtual_derived_from_stateless_pure_virtual>);
static_assert(is_polymorphic_v<unit_test_virtual_derived_from_standard_layout_non_standard_layout>);
static_assert(is_polymorphic_v<unit_test_virtual_derived_from_standard_layout_pure_virtual>);
static_assert(is_polymorphic_v<unit_test_virtual_derived_from_non_standard_layout_pure_virtual>);
static_assert(is_polymorphic_v<unit_test_virtual_derived_from_stateless_standard_layout_non_standard_layout>);
static_assert(is_polymorphic_v<unit_test_virtual_derived_from_stateless_standard_layout_pure_virtual>);
static_assert(is_polymorphic_v<unit_test_virtual_derived_from_standard_layout_non_standard_layout_pure_virtual>);
static_assert(is_polymorphic_v<unit_test_virtual_derived_from_all>);
static_assert(not is_polymorphic_v<unit_test_stateless_finally>);
static_assert(not is_polymorphic_v<unit_test_standard_layout_finally>);
static_assert(is_polymorphic_v<unit_test_non_standard_layout_finally>);
static_assert(is_polymorphic_v<unit_test_pure_virtual_finally>);
static_assert(not is_polymorphic_v<unit_test_derived_from_stateless_finally>);
static_assert(not is_polymorphic_v<unit_test_derived_from_standard_layout_finally>);
static_assert(is_polymorphic_v<unit_test_derived_from_non_standard_layout_finally>);
static_assert(is_polymorphic_v<unit_test_derived_from_pure_virtual_finally>);
static_assert(not is_polymorphic_v<unit_test_derived_from_stateless_standard_layout_finally>);
static_assert(is_polymorphic_v<unit_test_derived_from_stateless_non_standard_layout_finally>);
static_assert(is_polymorphic_v<unit_test_derived_from_stateless_pure_virtual_finally>);
static_assert(is_polymorphic_v<unit_test_derived_from_standard_layout_non_standard_layout_finally>);
static_assert(is_polymorphic_v<unit_test_derived_from_standard_layout_pure_virtual_finally>);
static_assert(is_polymorphic_v<unit_test_derived_from_non_standard_layout_pure_virtual_finally>);
static_assert(is_polymorphic_v<unit_test_derived_from_stateless_standard_layout_non_standard_layout_finally>);
static_assert(is_polymorphic_v<unit_test_derived_from_stateless_standard_layout_pure_virtual_finally>);
static_assert(is_polymorphic_v<unit_test_derived_from_standard_layout_non_standard_layout_pure_virtual_finally>);
static_assert(is_polymorphic_v<unit_test_derived_from_all_finally>);
static_assert(not is_polymorphic_v<unit_test_virtual_derived_from_stateless_finally>);
static_assert(not is_polymorphic_v<unit_test_virtual_derived_from_standard_layout_finally>);
static_assert(is_polymorphic_v<unit_test_virtual_derived_from_non_standard_layout_finally>);
static_assert(is_polymorphic_v<unit_test_virtual_derived_from_pure_virtual_finally>);
static_assert(not is_polymorphic_v<unit_test_virtual_derived_from_stateless_finally>);
static_assert(not is_polymorphic_v<unit_test_virtual_derived_from_standard_layout_finally>);
static_assert(is_polymorphic_v<unit_test_virtual_derived_from_non_standard_layout_finally>);
static_assert(is_polymorphic_v<unit_test_virtual_derived_from_pure_virtual_finally>);
static_assert(not is_polymorphic_v<unit_test_virtual_derived_from_stateless_standard_layout_finally>);
static_assert(is_polymorphic_v<unit_test_virtual_derived_from_stateless_non_standard_layout_finally>);
static_assert(is_polymorphic_v<unit_test_virtual_derived_from_stateless_pure_virtual_finally>);
static_assert(is_polymorphic_v<unit_test_virtual_derived_from_standard_layout_non_standard_layout_finally>);
static_assert(is_polymorphic_v<unit_test_virtual_derived_from_standard_layout_pure_virtual_finally>);
static_assert(is_polymorphic_v<unit_test_virtual_derived_from_non_standard_layout_pure_virtual_finally>);
static_assert(is_polymorphic_v<unit_test_virtual_derived_from_stateless_standard_layout_non_standard_layout_finally>);
static_assert(is_polymorphic_v<unit_test_virtual_derived_from_stateless_standard_layout_pure_virtual_finally>);
static_assert(is_polymorphic_v<unit_test_virtual_derived_from_standard_layout_non_standard_layout_pure_virtual_finally>);
static_assert(is_polymorphic_v<unit_test_virtual_derived_from_all_finally>);
static_assert(not is_polymorphic_v<int>);
static_assert(not is_polymorphic_v<const int>);
static_assert(not is_polymorphic_v<volatile int>);
static_assert(not is_polymorphic_v<const volatile int>);
static_assert(not is_polymorphic_v<void>);
static_assert(not is_polymorphic_v<const void>);
static_assert(not is_polymorphic_v<volatile void>);
static_assert(not is_polymorphic_v<const volatile void>);
static_assert(not is_polymorphic_v<void *>);
static_assert(not is_polymorphic_v<int [42]>);
static_assert(not is_polymorphic_v<int []>);
static_assert(not is_polymorphic_v<int &>);
static_assert(not is_polymorphic_v<const int &>);
static_assert(not is_polymorphic_v<volatile int &>);
static_assert(not is_polymorphic_v<const volatile int &>);
static_assert(not is_polymorphic_v<int ()>);
static_assert(not is_polymorphic_v<void (*)()>);
static_assert(not is_polymorphic_v<void (&)()>);
static_assert(not is_polymorphic_v<void (&&)()>);
static_assert(not is_polymorphic_v<int (A::*)()>);
static_assert(not is_polymorphic_v<int (A::*&)()>);
static_assert(not is_polymorphic_v<A>);
//static_assert(not is_polymorphic_v<B>);     // undefined behavior
static_assert(not is_polymorphic_v<C>);
static_assert(not is_polymorphic_v<D>);
//static_assert(not is_polymorphic_v<E>);     // undefined behavior
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_abstract)
static_assert(not is_abstract_v<unit_test_stateless>);
static_assert(not is_abstract_v<unit_test_standard_layout>);
static_assert(not is_abstract_v<unit_test_non_standard_layout>);
static_assert(is_abstract_v<unit_test_pure_virtual>);
static_assert(not is_abstract_v<unit_test_derived_from_stateless>);
static_assert(not is_abstract_v<unit_test_derived_from_standard_layout>);
static_assert(not is_abstract_v<unit_test_derived_from_non_standard_layout>);
static_assert(not is_abstract_v<unit_test_derived_from_pure_virtual>);
static_assert(not is_abstract_v<unit_test_derived_from_stateless_standard_layout>);
static_assert(not is_abstract_v<unit_test_derived_from_stateless_non_standard_layout>);
static_assert(not is_abstract_v<unit_test_derived_from_stateless_pure_virtual>);
static_assert(not is_abstract_v<unit_test_derived_from_standard_layout_non_standard_layout>);
static_assert(not is_abstract_v<unit_test_derived_from_standard_layout_pure_virtual>);
static_assert(not is_abstract_v<unit_test_derived_from_stateless_standard_layout_non_standard_layout>);
static_assert(not is_abstract_v<unit_test_derived_from_stateless_standard_layout_pure_virtual>);
static_assert(not is_abstract_v<unit_test_derived_from_standard_layout_non_standard_layout_pure_virtual>);
static_assert(not is_abstract_v<unit_test_derived_from_all>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_stateless>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_standard_layout>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_non_standard_layout>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_pure_virtual>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_stateless>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_standard_layout>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_non_standard_layout>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_pure_virtual>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_stateless_standard_layout>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_stateless_non_standard_layout>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_stateless_pure_virtual>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_standard_layout_non_standard_layout>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_standard_layout_pure_virtual>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_non_standard_layout_pure_virtual>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_stateless_standard_layout_non_standard_layout>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_stateless_standard_layout_pure_virtual>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_standard_layout_non_standard_layout_pure_virtual>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_all>);
static_assert(not is_abstract_v<unit_test_stateless_finally>);
static_assert(not is_abstract_v<unit_test_standard_layout_finally>);
static_assert(not is_abstract_v<unit_test_non_standard_layout_finally>);
static_assert(is_abstract_v<unit_test_pure_virtual_finally>);
static_assert(not is_abstract_v<unit_test_derived_from_stateless_finally>);
static_assert(not is_abstract_v<unit_test_derived_from_standard_layout_finally>);
static_assert(not is_abstract_v<unit_test_derived_from_non_standard_layout_finally>);
static_assert(not is_abstract_v<unit_test_derived_from_pure_virtual_finally>);
static_assert(not is_abstract_v<unit_test_derived_from_stateless_standard_layout_finally>);
static_assert(not is_abstract_v<unit_test_derived_from_stateless_non_standard_layout_finally>);
static_assert(not is_abstract_v<unit_test_derived_from_stateless_pure_virtual_finally>);
static_assert(not is_abstract_v<unit_test_derived_from_standard_layout_non_standard_layout_finally>);
static_assert(not is_abstract_v<unit_test_derived_from_standard_layout_pure_virtual_finally>);
static_assert(not is_abstract_v<unit_test_derived_from_non_standard_layout_pure_virtual_finally>);
static_assert(not is_abstract_v<unit_test_derived_from_stateless_standard_layout_non_standard_layout_finally>);
static_assert(not is_abstract_v<unit_test_derived_from_stateless_standard_layout_pure_virtual_finally>);
static_assert(not is_abstract_v<unit_test_derived_from_standard_layout_non_standard_layout_pure_virtual_finally>);
static_assert(not is_abstract_v<unit_test_derived_from_all_finally>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_stateless_finally>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_standard_layout_finally>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_non_standard_layout_finally>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_pure_virtual_finally>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_stateless_finally>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_standard_layout_finally>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_non_standard_layout_finally>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_pure_virtual_finally>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_stateless_standard_layout_finally>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_stateless_non_standard_layout_finally>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_stateless_pure_virtual_finally>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_standard_layout_non_standard_layout_finally>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_standard_layout_pure_virtual_finally>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_non_standard_layout_pure_virtual_finally>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_stateless_standard_layout_non_standard_layout_finally>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_stateless_standard_layout_pure_virtual_finally>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_standard_layout_non_standard_layout_pure_virtual_finally>);
static_assert(not is_abstract_v<unit_test_virtual_derived_from_all_finally>);
static_assert(not is_abstract_v<int>);
static_assert(not is_abstract_v<const int>);
static_assert(not is_abstract_v<volatile int>);
static_assert(not is_abstract_v<const volatile int>);
static_assert(not is_abstract_v<void>);
static_assert(not is_abstract_v<const void>);
static_assert(not is_abstract_v<volatile void>);
static_assert(not is_abstract_v<const volatile void>);
static_assert(not is_abstract_v<void *>);
static_assert(not is_abstract_v<int [42]>);
static_assert(not is_abstract_v<int []>);
static_assert(not is_abstract_v<int &>);
static_assert(not is_abstract_v<const int &>);
static_assert(not is_abstract_v<volatile int &>);
static_assert(not is_abstract_v<const volatile int &>);
static_assert(not is_abstract_v<int ()>);
static_assert(not is_abstract_v<void (*)()>);
static_assert(not is_abstract_v<void (&)()>);
static_assert(not is_abstract_v<void (&&)()>);
static_assert(not is_abstract_v<int (A::*)()>);
static_assert(not is_abstract_v<int (A::*&)()>);
static_assert(not is_abstract_v<A>);
//static_assert(not is_abstract_v<B>);     // undefined behavior
static_assert(not is_abstract_v<C>);
static_assert(not is_abstract_v<D>);
//static_assert(not is_abstract_v<E>);      // undefined behavior
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_base_of)
static_assert(not is_base_of_v<int, int>);      // the type must be build-in type
static_assert(not is_base_of_v<int, char>);
static_assert(not is_base_of_v<int &, int *>);
static_assert(not is_base_of_v<int [], int [42]>);
static_assert(not is_base_of_v<int [42], int []>);
static_assert(not is_base_of_v<void, void>);
static_assert(is_base_of_v<unit_test_stateless, unit_test_stateless>);
static_assert(is_base_of_v<const unit_test_stateless, unit_test_stateless>);
static_assert(is_base_of_v<volatile unit_test_stateless, unit_test_stateless>);
static_assert(is_base_of_v<const volatile unit_test_stateless, unit_test_stateless>);
static_assert(is_base_of_v<unit_test_stateless, unit_test_derived_from_stateless>);
static_assert(is_base_of_v<unit_test_stateless, unit_test_derived_from_all>);
static_assert(is_base_of_v<unit_test_stateless, unit_test_virtual_derived_from_stateless>);
static_assert(is_base_of_v<unit_test_stateless, unit_test_virtual_derived_from_all>);
static_assert(is_base_of_v<unit_test_stateless_finally, unit_test_stateless_finally>);      // still be true
static_assert(is_base_of_v<unit_test_stateless, unit_test_derived_from_stateless_finally>);
static_assert(is_base_of_v<unit_test_stateless, unit_test_derived_from_all_finally>);
static_assert(is_base_of_v<unit_test_stateless, unit_test_virtual_derived_from_stateless_finally>);
static_assert(is_base_of_v<unit_test_stateless, unit_test_virtual_derived_from_all_finally>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_final)
static_assert(not is_final_v<unit_test_stateless>);
static_assert(not is_final_v<unit_test_standard_layout>);
static_assert(not is_final_v<unit_test_non_standard_layout>);
static_assert(not is_final_v<unit_test_pure_virtual>);
static_assert(not is_final_v<unit_test_derived_from_stateless>);
static_assert(not is_final_v<unit_test_derived_from_standard_layout>);
static_assert(not is_final_v<unit_test_derived_from_non_standard_layout>);
static_assert(not is_final_v<unit_test_derived_from_pure_virtual>);
static_assert(not is_final_v<unit_test_derived_from_stateless_standard_layout>);
static_assert(not is_final_v<unit_test_derived_from_stateless_non_standard_layout>);
static_assert(not is_final_v<unit_test_derived_from_stateless_pure_virtual>);
static_assert(not is_final_v<unit_test_derived_from_standard_layout_non_standard_layout>);
static_assert(not is_final_v<unit_test_derived_from_standard_layout_pure_virtual>);
static_assert(not is_final_v<unit_test_derived_from_non_standard_layout_pure_virtual>);
static_assert(not is_final_v<unit_test_derived_from_stateless_standard_layout_non_standard_layout>);
static_assert(not is_final_v<unit_test_derived_from_stateless_standard_layout_pure_virtual>);
static_assert(not is_final_v<unit_test_derived_from_standard_layout_non_standard_layout_pure_virtual>);
static_assert(not is_final_v<unit_test_derived_from_all>);
static_assert(not is_final_v<unit_test_virtual_derived_from_stateless>);
static_assert(not is_final_v<unit_test_virtual_derived_from_standard_layout>);
static_assert(not is_final_v<unit_test_virtual_derived_from_non_standard_layout>);
static_assert(not is_final_v<unit_test_virtual_derived_from_pure_virtual>);
static_assert(not is_final_v<unit_test_virtual_derived_from_stateless>);
static_assert(not is_final_v<unit_test_virtual_derived_from_standard_layout>);
static_assert(not is_final_v<unit_test_virtual_derived_from_non_standard_layout>);
static_assert(not is_final_v<unit_test_virtual_derived_from_pure_virtual>);
static_assert(not is_final_v<unit_test_virtual_derived_from_stateless_standard_layout>);
static_assert(not is_final_v<unit_test_virtual_derived_from_stateless_non_standard_layout>);
static_assert(not is_final_v<unit_test_virtual_derived_from_stateless_pure_virtual>);
static_assert(not is_final_v<unit_test_virtual_derived_from_standard_layout_non_standard_layout>);
static_assert(not is_final_v<unit_test_virtual_derived_from_standard_layout_pure_virtual>);
static_assert(not is_final_v<unit_test_virtual_derived_from_non_standard_layout_pure_virtual>);
static_assert(not is_final_v<unit_test_virtual_derived_from_stateless_standard_layout_non_standard_layout>);
static_assert(not is_final_v<unit_test_virtual_derived_from_stateless_standard_layout_pure_virtual>);
static_assert(not is_final_v<unit_test_virtual_derived_from_standard_layout_non_standard_layout_pure_virtual>);
static_assert(not is_final_v<unit_test_virtual_derived_from_all>);
static_assert(is_final_v<unit_test_stateless_finally>);
static_assert(is_final_v<unit_test_standard_layout_finally>);
static_assert(is_final_v<unit_test_non_standard_layout_finally>);
static_assert(is_final_v<unit_test_pure_virtual_finally>);
static_assert(is_final_v<unit_test_derived_from_stateless_finally>);
static_assert(is_final_v<unit_test_derived_from_standard_layout_finally>);
static_assert(is_final_v<unit_test_derived_from_non_standard_layout_finally>);
static_assert(is_final_v<unit_test_derived_from_pure_virtual_finally>);
static_assert(is_final_v<unit_test_derived_from_stateless_standard_layout_finally>);
static_assert(is_final_v<unit_test_derived_from_stateless_non_standard_layout_finally>);
static_assert(is_final_v<unit_test_derived_from_stateless_pure_virtual_finally>);
static_assert(is_final_v<unit_test_derived_from_standard_layout_non_standard_layout_finally>);
static_assert(is_final_v<unit_test_derived_from_standard_layout_pure_virtual_finally>);
static_assert(is_final_v<unit_test_derived_from_non_standard_layout_pure_virtual_finally>);
static_assert(is_final_v<unit_test_derived_from_stateless_standard_layout_non_standard_layout_finally>);
static_assert(is_final_v<unit_test_derived_from_stateless_standard_layout_pure_virtual_finally>);
static_assert(is_final_v<unit_test_derived_from_standard_layout_non_standard_layout_pure_virtual_finally>);
static_assert(is_final_v<unit_test_derived_from_all_finally>);
static_assert(is_final_v<unit_test_virtual_derived_from_stateless_finally>);
static_assert(is_final_v<unit_test_virtual_derived_from_standard_layout_finally>);
static_assert(is_final_v<unit_test_virtual_derived_from_non_standard_layout_finally>);
static_assert(is_final_v<unit_test_virtual_derived_from_pure_virtual_finally>);
static_assert(is_final_v<unit_test_virtual_derived_from_stateless_finally>);
static_assert(is_final_v<unit_test_virtual_derived_from_standard_layout_finally>);
static_assert(is_final_v<unit_test_virtual_derived_from_non_standard_layout_finally>);
static_assert(is_final_v<unit_test_virtual_derived_from_pure_virtual_finally>);
static_assert(is_final_v<unit_test_virtual_derived_from_stateless_standard_layout_finally>);
static_assert(is_final_v<unit_test_virtual_derived_from_stateless_non_standard_layout_finally>);
static_assert(is_final_v<unit_test_virtual_derived_from_stateless_pure_virtual_finally>);
static_assert(is_final_v<unit_test_virtual_derived_from_standard_layout_non_standard_layout_finally>);
static_assert(is_final_v<unit_test_virtual_derived_from_standard_layout_pure_virtual_finally>);
static_assert(is_final_v<unit_test_virtual_derived_from_non_standard_layout_pure_virtual_finally>);
static_assert(is_final_v<unit_test_virtual_derived_from_stateless_standard_layout_non_standard_layout_finally>);
static_assert(is_final_v<unit_test_virtual_derived_from_stateless_standard_layout_pure_virtual_finally>);
static_assert(is_final_v<unit_test_virtual_derived_from_standard_layout_non_standard_layout_pure_virtual_finally>);
static_assert(is_final_v<unit_test_virtual_derived_from_all_finally>);
static_assert(not is_final_v<int>);
static_assert(not is_final_v<const int>);
static_assert(not is_final_v<volatile int>);
static_assert(not is_final_v<const volatile int>);
static_assert(not is_final_v<void>);
static_assert(not is_final_v<const void>);
static_assert(not is_final_v<volatile void>);
static_assert(not is_final_v<const volatile void>);
static_assert(not is_final_v<void *>);
static_assert(not is_final_v<int [42]>);
static_assert(not is_final_v<int []>);
static_assert(not is_final_v<int &>);
static_assert(not is_final_v<const int &>);
static_assert(not is_final_v<volatile int &>);
static_assert(not is_final_v<const volatile int &>);
static_assert(not is_final_v<int ()>);
static_assert(not is_final_v<void (*)()>);
static_assert(not is_final_v<void (&)()>);
static_assert(not is_final_v<void (&&)()>);
static_assert(not is_final_v<int (A::*)()>);
static_assert(not is_final_v<int (A::*&)()>);
static_assert(not is_final_v<A>);
//static_assert(not is_final_v<B>);     // undefined behavior
static_assert(not is_final_v<C>);
static_assert(not is_final_v<D>);
//static_assert(not is_final_v<E>);     // undefined behavior
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_aggregate)
static_assert(is_aggregate_v<int [42]>);
static_assert(is_aggregate_v<int []>);
static_assert(is_aggregate_v<unit_test_stateless>);
static_assert(is_aggregate_v<unit_test_standard_layout>);
static_assert(not is_aggregate_v<unit_test_non_standard_layout>);
static_assert(not is_aggregate_v<unit_test_pure_virtual>);
static_assert(is_aggregate_v<unit_test_derived_from_stateless>);
static_assert(is_aggregate_v<unit_test_derived_from_standard_layout>);
static_assert(not is_aggregate_v<unit_test_derived_from_non_standard_layout>);
static_assert(not is_aggregate_v<unit_test_derived_from_pure_virtual>);
static_assert(is_aggregate_v<unit_test_derived_from_stateless_standard_layout>);
static_assert(not is_aggregate_v<unit_test_derived_from_stateless_non_standard_layout>);
static_assert(not is_aggregate_v<unit_test_derived_from_stateless_pure_virtual>);
static_assert(not is_aggregate_v<unit_test_derived_from_standard_layout_non_standard_layout>);
static_assert(not is_aggregate_v<unit_test_derived_from_standard_layout_pure_virtual>);
static_assert(not is_aggregate_v<unit_test_derived_from_non_standard_layout_pure_virtual>);
static_assert(not is_aggregate_v<unit_test_derived_from_stateless_standard_layout_non_standard_layout>);
static_assert(not is_aggregate_v<unit_test_derived_from_stateless_standard_layout_pure_virtual>);
static_assert(not is_aggregate_v<unit_test_derived_from_standard_layout_non_standard_layout_pure_virtual>);
static_assert(not is_aggregate_v<unit_test_derived_from_all>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_stateless>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_standard_layout>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_non_standard_layout>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_pure_virtual>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_stateless>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_standard_layout>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_non_standard_layout>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_pure_virtual>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_stateless_standard_layout>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_stateless_non_standard_layout>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_stateless_pure_virtual>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_standard_layout_non_standard_layout>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_standard_layout_pure_virtual>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_non_standard_layout_pure_virtual>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_stateless_standard_layout_non_standard_layout>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_stateless_standard_layout_pure_virtual>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_standard_layout_non_standard_layout_pure_virtual>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_all>);
static_assert(is_aggregate_v<unit_test_stateless_finally>);
static_assert(is_aggregate_v<unit_test_standard_layout_finally>);
static_assert(not is_aggregate_v<unit_test_non_standard_layout_finally>);
static_assert(not is_aggregate_v<unit_test_pure_virtual_finally>);
static_assert(is_aggregate_v<unit_test_derived_from_stateless_finally>);
static_assert(is_aggregate_v<unit_test_derived_from_standard_layout_finally>);
static_assert(not is_aggregate_v<unit_test_derived_from_non_standard_layout_finally>);
static_assert(not is_aggregate_v<unit_test_derived_from_pure_virtual_finally>);
static_assert(is_aggregate_v<unit_test_derived_from_stateless_standard_layout_finally>);
static_assert(not is_aggregate_v<unit_test_derived_from_stateless_non_standard_layout_finally>);
static_assert(not is_aggregate_v<unit_test_derived_from_stateless_pure_virtual_finally>);
static_assert(not is_aggregate_v<unit_test_derived_from_standard_layout_non_standard_layout_finally>);
static_assert(not is_aggregate_v<unit_test_derived_from_standard_layout_pure_virtual_finally>);
static_assert(not is_aggregate_v<unit_test_derived_from_non_standard_layout_pure_virtual_finally>);
static_assert(not is_aggregate_v<unit_test_derived_from_stateless_standard_layout_non_standard_layout_finally>);
static_assert(not is_aggregate_v<unit_test_derived_from_stateless_standard_layout_pure_virtual_finally>);
static_assert(not is_aggregate_v<unit_test_derived_from_standard_layout_non_standard_layout_pure_virtual_finally>);
static_assert(not is_aggregate_v<unit_test_derived_from_all_finally>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_stateless_finally>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_standard_layout_finally>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_non_standard_layout_finally>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_pure_virtual_finally>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_stateless_finally>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_standard_layout_finally>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_non_standard_layout_finally>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_pure_virtual_finally>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_stateless_standard_layout_finally>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_stateless_non_standard_layout_finally>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_stateless_pure_virtual_finally>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_standard_layout_non_standard_layout_finally>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_standard_layout_pure_virtual_finally>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_non_standard_layout_pure_virtual_finally>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_stateless_standard_layout_non_standard_layout_finally>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_stateless_standard_layout_pure_virtual_finally>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_standard_layout_non_standard_layout_pure_virtual_finally>);
static_assert(not is_aggregate_v<unit_test_virtual_derived_from_all_finally>);
static_assert(not is_aggregate_v<int>);
static_assert(not is_aggregate_v<const int>);
static_assert(not is_aggregate_v<volatile int>);
static_assert(not is_aggregate_v<const volatile int>);
static_assert(not is_aggregate_v<void>);
static_assert(not is_aggregate_v<const void>);
static_assert(not is_aggregate_v<volatile void>);
static_assert(not is_aggregate_v<const volatile void>);
static_assert(not is_aggregate_v<void *>);
static_assert(not is_aggregate_v<int &>);
static_assert(not is_aggregate_v<const int &>);
static_assert(not is_aggregate_v<volatile int &>);
static_assert(not is_aggregate_v<const volatile int &>);
static_assert(not is_aggregate_v<int ()>);
static_assert(not is_aggregate_v<void (*)()>);
static_assert(not is_aggregate_v<void (&)()>);
static_assert(not is_aggregate_v<void (&&)()>);
static_assert(not is_aggregate_v<int (A::*)()>);
static_assert(not is_aggregate_v<int (A::*&)()>);
static_assert(is_aggregate_v<A>);
//static_assert(not is_aggregate_v<B>);     // undefined behavior
static_assert(not is_aggregate_v<C>);
static_assert(not is_aggregate_v<D>);
//static_assert(not is_aggregate_v<E>);     // undefined behavior
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_arithmetic)
static_assert(is_arithmetic_v<int>);
static_assert(is_arithmetic_v<const int>);
static_assert(is_arithmetic_v<volatile int>);
static_assert(is_arithmetic_v<const volatile int>);
static_assert(not is_arithmetic_v<int *>);
static_assert(not is_arithmetic_v<int &>);
static_assert(not is_arithmetic_v<int []>);
static_assert(not is_arithmetic_v<int [42]>);
static_assert(not is_arithmetic_v<int ()>);
static_assert(not is_arithmetic_v<A>);
static_assert(not is_arithmetic_v<C>);
static_assert(not is_arithmetic_v<D>);
static_assert(not is_arithmetic_v<E>);
static_assert(is_arithmetic_v<bool>);
static_assert(is_arithmetic_v<char>);
static_assert(is_arithmetic_v<signed char>);
static_assert(is_arithmetic_v<unsigned char>);
static_assert(is_arithmetic_v<char8_t>);
static_assert(is_arithmetic_v<char16_t>);
static_assert(is_arithmetic_v<char32_t>);
static_assert(is_arithmetic_v<wchar_t>);
static_assert(is_arithmetic_v<short>);
static_assert(is_arithmetic_v<signed short>);
static_assert(is_arithmetic_v<unsigned short>);
static_assert(is_arithmetic_v<signed>);
static_assert(is_arithmetic_v<signed int>);
static_assert(is_arithmetic_v<unsigned>);
static_assert(is_arithmetic_v<unsigned int>);
static_assert(is_arithmetic_v<long>);
static_assert(is_arithmetic_v<unsigned long>);
static_assert(is_arithmetic_v<long long>);
static_assert(is_arithmetic_v<unsigned long long>);
static_assert(is_arithmetic_v<__int128_t>);
static_assert(is_arithmetic_v<__uint128_t>);
static_assert(is_arithmetic_v<float>);
static_assert(is_arithmetic_v<double>);
static_assert(is_arithmetic_v<long double>);
static_assert(not is_arithmetic_v<void>);
static_assert(not is_arithmetic_v<decltype(nullptr)>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_fundamental)
static_assert(is_fundamental_v<int>);
static_assert(is_fundamental_v<const int>);
static_assert(is_fundamental_v<volatile int>);
static_assert(is_fundamental_v<const volatile int>);
static_assert(not is_fundamental_v<int *>);
static_assert(not is_fundamental_v<int &>);
static_assert(not is_fundamental_v<int []>);
static_assert(not is_fundamental_v<int [42]>);
static_assert(not is_fundamental_v<int ()>);
static_assert(not is_fundamental_v<A>);
static_assert(not is_fundamental_v<C>);
static_assert(not is_fundamental_v<D>);
static_assert(not is_fundamental_v<E>);
static_assert(is_fundamental_v<bool>);
static_assert(is_fundamental_v<char>);
static_assert(is_fundamental_v<signed char>);
static_assert(is_fundamental_v<unsigned char>);
static_assert(is_fundamental_v<char8_t>);
static_assert(is_fundamental_v<char16_t>);
static_assert(is_fundamental_v<char32_t>);
static_assert(is_fundamental_v<wchar_t>);
static_assert(is_fundamental_v<short>);
static_assert(is_fundamental_v<signed short>);
static_assert(is_fundamental_v<unsigned short>);
static_assert(is_fundamental_v<signed>);
static_assert(is_fundamental_v<signed int>);
static_assert(is_fundamental_v<unsigned>);
static_assert(is_fundamental_v<unsigned int>);
static_assert(is_fundamental_v<long>);
static_assert(is_fundamental_v<unsigned long>);
static_assert(is_fundamental_v<long long>);
static_assert(is_fundamental_v<unsigned long long>);
static_assert(is_fundamental_v<__int128_t>);
static_assert(is_fundamental_v<__uint128_t>);
static_assert(is_fundamental_v<float>);
static_assert(is_fundamental_v<double>);
static_assert(is_fundamental_v<long double>);
static_assert(is_fundamental_v<void>);
static_assert(is_fundamental_v<decltype(nullptr)>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_scalar)
static_assert(is_scalar_v<int>);
static_assert(is_scalar_v<const int>);
static_assert(is_scalar_v<volatile int>);
static_assert(is_scalar_v<const volatile int>);
static_assert(is_scalar_v<int *>);
static_assert(is_scalar_v<int A::*>);
static_assert(is_scalar_v<void (A::*)()>);
static_assert(not is_scalar_v<int &>);
static_assert(not is_scalar_v<int []>);
static_assert(not is_scalar_v<int [42]>);
static_assert(not is_scalar_v<int ()>);
static_assert(not is_scalar_v<A>);
static_assert(is_scalar_v<C>);
static_assert(is_scalar_v<D>);
static_assert(not is_scalar_v<E>);
static_assert(is_scalar_v<bool>);
static_assert(is_scalar_v<char>);
static_assert(is_scalar_v<signed char>);
static_assert(is_scalar_v<unsigned char>);
static_assert(is_scalar_v<char8_t>);
static_assert(is_scalar_v<char16_t>);
static_assert(is_scalar_v<char32_t>);
static_assert(is_scalar_v<wchar_t>);
static_assert(is_scalar_v<short>);
static_assert(is_scalar_v<signed short>);
static_assert(is_scalar_v<unsigned short>);
static_assert(is_scalar_v<signed>);
static_assert(is_scalar_v<signed int>);
static_assert(is_scalar_v<unsigned>);
static_assert(is_scalar_v<unsigned int>);
static_assert(is_scalar_v<long>);
static_assert(is_scalar_v<unsigned long>);
static_assert(is_scalar_v<long long>);
static_assert(is_scalar_v<unsigned long long>);
static_assert(is_scalar_v<__int128_t>);
static_assert(is_scalar_v<__uint128_t>);
static_assert(is_scalar_v<float>);
static_assert(is_scalar_v<double>);
static_assert(is_scalar_v<long double>);
static_assert(not is_scalar_v<void>);
static_assert(is_scalar_v<decltype(nullptr)>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_compound)
struct unit_test_is_compound_virtual {
    virtual ~unit_test_is_compound_virtual() = default;
};
struct unit_test_is_compound_derived_from_A {};
struct unit_test_is_compound_virtual_derived_from_A : virtual A {};

static_assert(is_compound_v<int *>);
static_assert(is_compound_v<int &>);
static_assert(is_compound_v<int []>);
static_assert(is_compound_v<int [42]>);
static_assert(is_compound_v<int ()>);
static_assert(is_compound_v<A>);
static_assert(is_compound_v<C>);
static_assert(is_compound_v<D>);
static_assert(is_compound_v<E>);
static_assert(is_compound_v<unit_test_is_compound_virtual>);
static_assert(is_compound_v<unit_test_is_compound_derived_from_A>);
static_assert(is_compound_v<unit_test_is_compound_virtual_derived_from_A>);
static_assert(is_compound_v<int A::*>);
static_assert(is_compound_v<void (A::*)()>);
static_assert(not is_compound_v<int>);
static_assert(not is_compound_v<const int>);
static_assert(not is_compound_v<volatile int>);
static_assert(not is_compound_v<const volatile int>);
static_assert(not is_compound_v<bool>);
static_assert(not is_compound_v<char>);
static_assert(not is_compound_v<signed char>);
static_assert(not is_compound_v<unsigned char>);
static_assert(not is_compound_v<char8_t>);
static_assert(not is_compound_v<char16_t>);
static_assert(not is_compound_v<char32_t>);
static_assert(not is_compound_v<wchar_t>);
static_assert(not is_compound_v<short>);
static_assert(not is_compound_v<signed short>);
static_assert(not is_compound_v<unsigned short>);
static_assert(not is_compound_v<signed>);
static_assert(not is_compound_v<signed int>);
static_assert(not is_compound_v<unsigned>);
static_assert(not is_compound_v<unsigned int>);
static_assert(not is_compound_v<long>);
static_assert(not is_compound_v<unsigned long>);
static_assert(not is_compound_v<long long>);
static_assert(not is_compound_v<unsigned long long>);
static_assert(not is_compound_v<__int128_t>);
static_assert(not is_compound_v<__uint128_t>);
static_assert(not is_compound_v<float>);
static_assert(not is_compound_v<double>);
static_assert(not is_compound_v<long double>);
static_assert(not is_compound_v<void>);
static_assert(not is_compound_v<decltype(nullptr)>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_object)
static_assert(is_object_v<int>);
static_assert(is_object_v<const int>);
static_assert(is_object_v<volatile int>);
static_assert(is_object_v<const volatile int>);
static_assert(is_object_v<double>);
static_assert(is_object_v<void *>);
static_assert(is_object_v<int []>);
static_assert(is_object_v<int [42]>);
static_assert(is_object_v<int (*)[]>);
static_assert(is_object_v<int *[]>);
static_assert(is_object_v<A>);
static_assert(is_object_v<B>);
static_assert(is_object_v<C>);
static_assert(is_object_v<D>);
static_assert(is_object_v<E>);
static_assert(is_object_v<int A::*>);
static_assert(is_object_v<int (A::*)(...)>);
static_assert(is_object_v<decltype(nullptr)>);
static_assert(not is_object_v<void>);
static_assert(not is_object_v<const void>);
static_assert(not is_object_v<volatile void>);
static_assert(not is_object_v<const volatile void>);
static_assert(not is_object_v<int &>);
static_assert(not is_object_v<int &&>);
static_assert(not is_object_v<void ()>);
static_assert(not is_object_v<int (&)[]>);
static_assert(not is_object_v<int (&)[42]>);
static_assert(not is_object_v<int (&&)[]>);
static_assert(not is_object_v<int (&&)[42]>);
static_assert(not is_object_v<void (&)()>);
static_assert(not is_object_v<void (&&)()>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test helper classes)
struct trivial_stateless {};
struct trivial {
    int a;
    char b;
    void *c;
    double d[42];
};
struct non_trivial_1 {
    non_trivial_1();
};
struct non_trivial_2 {
    non_trivial_2();
};
struct trivial_with_deleted_destructor {
    trivial_with_deleted_destructor() = default;
    ~trivial_with_deleted_destructor() = delete;
};
struct trivially_copy_constructible {
    trivially_copy_constructible() = delete;
    trivially_copy_constructible(const trivially_copy_constructible &) = default;
    trivially_copy_constructible(trivially_copy_constructible &&) = delete;
    trivially_copy_constructible &operator=(const trivially_copy_constructible &) = delete;
    trivially_copy_constructible &operator=(trivially_copy_constructible &&) = delete;
    ~trivially_copy_constructible() = default;
};
struct trivially_copy_constructible_non_destructible {
    trivially_copy_constructible_non_destructible() = delete;
    trivially_copy_constructible_non_destructible(const trivially_copy_constructible_non_destructible &) = default;
    trivially_copy_constructible_non_destructible(trivially_copy_constructible_non_destructible &&) = delete;
    trivially_copy_constructible_non_destructible &operator=(const trivially_copy_constructible_non_destructible &) = delete;
    trivially_copy_constructible_non_destructible &operator=(trivially_copy_constructible_non_destructible &&) = delete;
    ~trivially_copy_constructible_non_destructible() = delete;
};
struct trivially_move_constructible {
    trivially_move_constructible() = delete;
    trivially_move_constructible(const trivially_move_constructible &) = delete;
    trivially_move_constructible(trivially_move_constructible &&) = default;
    trivially_move_constructible &operator=(const trivially_move_constructible &) = delete;
    trivially_move_constructible &operator=(trivially_move_constructible &&) = delete;
    ~trivially_move_constructible() = default;
};
struct trivially_move_constructible_non_destructible {
    trivially_move_constructible_non_destructible() = delete;
    trivially_move_constructible_non_destructible(const trivially_move_constructible_non_destructible &) = delete;
    trivially_move_constructible_non_destructible(trivially_move_constructible_non_destructible &&) = default;
    trivially_move_constructible_non_destructible &operator=(const trivially_move_constructible_non_destructible &) = delete;
    trivially_move_constructible_non_destructible &operator=(trivially_move_constructible_non_destructible &&) = delete;
    ~trivially_move_constructible_non_destructible() = delete;
};
struct trivially_copy_assignable {
    trivially_copy_assignable() = delete;
    trivially_copy_assignable(const trivially_copy_assignable &) = delete;
    trivially_copy_assignable(trivially_copy_assignable &&) = delete;
    trivially_copy_assignable &operator=(const trivially_copy_assignable &) = default;
    trivially_copy_assignable &operator=(trivially_copy_assignable &&) = delete;
    ~trivially_copy_assignable() = default;
};
struct trivially_copy_assignable_non_destructible {
    trivially_copy_assignable_non_destructible() = delete;
    trivially_copy_assignable_non_destructible(const trivially_copy_assignable_non_destructible &) = delete;
    trivially_copy_assignable_non_destructible(trivially_copy_assignable_non_destructible &&) = delete;
    trivially_copy_assignable_non_destructible &operator=(const trivially_copy_assignable_non_destructible &) = default;
    trivially_copy_assignable_non_destructible &operator=(trivially_copy_assignable_non_destructible &&) = delete;
    ~trivially_copy_assignable_non_destructible() = delete;
};
struct trivially_move_assignable {
    trivially_move_assignable() = delete;
    trivially_move_assignable(const trivially_move_assignable &) = delete;
    trivially_move_assignable(trivially_move_assignable &&) = delete;
    trivially_move_assignable &operator=(const trivially_move_assignable &) = delete;
    trivially_move_assignable &operator=(trivially_move_assignable &&) = default;
    ~trivially_move_assignable() = default;
};
struct trivially_move_assignable_non_destructible {
    trivially_move_assignable_non_destructible() = delete;
    trivially_move_assignable_non_destructible(const trivially_move_assignable_non_destructible &) = delete;
    trivially_move_assignable_non_destructible(trivially_move_assignable_non_destructible &&) = delete;
    trivially_move_assignable_non_destructible &operator=(const trivially_move_assignable_non_destructible &) = delete;
    trivially_move_assignable_non_destructible &operator=(trivially_move_assignable_non_destructible &&) = default;
    ~trivially_move_assignable_non_destructible() = delete;
};
struct trivially_default_constructible_simulator {
    trivially_default_constructible_simulator() {
        using type = int;
        static_assert(true);
        ;;;;
    }
};
struct non_trivially_default_constructible {
    non_trivially_default_constructible() {
        int a {};
        ++a;
    }
};
struct trivially_constructible_simulator : trivial {
    trivially_constructible_simulator(int) {}
    trivially_constructible_simulator(char) {}
    trivially_constructible_simulator(void *) {}
    trivially_constructible_simulator(double *, std::size_t) {}
    template <typename T>
    trivially_constructible_simulator(T &&) {}
    template <std::size_t N>
    trivially_constructible_simulator(double (&arr)[N]) {}
};
struct non_trivially_constructible {
    non_trivially_constructible(int) {
        f();
    }
    template <typename T>
    non_trivially_constructible(T) {
        f();
    }
    template <typename ...Args>
    non_trivially_constructible(Args &&...) {
        f();
    }
    void f() {
        int a {};
        ++a;
    }
};
struct only_copy_constructor_implemented : trivial {
    only_copy_constructor_implemented(const only_copy_constructor_implemented &) {
        int a {};
        ++a;
    }
};
struct only_copy_assignment_operator_implemented : trivial {
    only_copy_assignment_operator_implemented(only_copy_assignment_operator_implemented &&) {
        int a {};
        ++a;
    }
};
struct only_move_constructor_implemented : trivial {
    only_move_constructor_implemented &operator=(const only_move_constructor_implemented &) {
        int a {};
        ++a;
        return *this;
    }
};
struct only_move_assignment_operator_implemented : trivial {
    only_move_assignment_operator_implemented &operator=(only_move_assignment_operator_implemented &&) {
        int a {};
        ++a;
        return *this;
    }
};
struct unit_test_is_constructible : trivial {
    unit_test_is_constructible(int);
    unit_test_is_constructible(char) = delete;
    template <typename T>
    unit_test_is_constructible(T);
    unit_test_is_constructible(const unit_test_is_constructible &) {
        int a {};
        ++a;
    }
    unit_test_is_constructible(unit_test_is_constructible &&) = delete;
    unit_test_is_constructible &operator=(const unit_test_is_constructible &) = delete;
    unit_test_is_constructible &operator=(unit_test_is_constructible &&) {
        int a {};
        ++a;
        return *this;
    }
    unit_test_is_constructible(int, char);
    template <std::size_t N>
    unit_test_is_constructible(double (&arr)[N]);
    template <typename T, typename U>
    unit_test_is_constructible(T, U) = delete;
    template <typename T, typename U, typename ...Args>
    unit_test_is_constructible(T, U, Args &&...);
};
struct unit_test_derived_from_is_constructible : unit_test_is_constructible {
    int f;
};
struct trivially_destructible {
    ~trivially_destructible() = default;
};
struct non_trivially_destructible {
    ~non_trivially_destructible() {
        int a {};
        ++a;
    }
};
struct exceptional_trivially_destructible {
    ~exceptional_trivially_destructible() noexcept(false) = default;
};
struct exceptional_non_trivially_destructible {
    ~exceptional_non_trivially_destructible() noexcept(false) {
        int a {};
        ++a;
    }
};
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_trivial)
static_assert(is_trivial_v<int>);
static_assert(is_trivial_v<const int>);
static_assert(is_trivial_v<volatile int>);
static_assert(is_trivial_v<const volatile int>);
static_assert(is_trivial_v<int *>);
static_assert(is_trivial_v<const int *>);
static_assert(is_trivial_v<volatile int *>);
static_assert(is_trivial_v<int *const>);
static_assert(is_trivial_v<int *volatile>);
static_assert(not is_trivial_v<int &>);
static_assert(not is_trivial_v<const int &>);
static_assert(not is_trivial_v<volatile int &>);
static_assert(not is_trivial_v<int &&>);
static_assert(not is_trivial_v<void>);
static_assert(is_trivial_v<int []>);
static_assert(is_trivial_v<int [42]>);
static_assert(not is_trivial_v<int (&)[42]>);
static_assert(not is_trivial_v<int (&&)[]>);
static_assert(not is_trivial_v<void ()>);
static_assert(is_trivial_v<void (*)()>);
static_assert(is_trivial_v<void (*const)()>);
static_assert(is_trivial_v<decltype(nullptr)>);
static_assert(not is_trivial_v<void (&)()>);
static_assert(not is_trivial_v<void (&&)()>);
static_assert(is_trivial_v<A>);
//static_assert(is_trivial_v<B>);     // undefined behavior
static_assert(is_trivial_v<C>);
static_assert(is_trivial_v<D>);
//static_assert(is_trivial_v<E>);     // undefined behavior
static_assert(is_trivial_v<trivial_stateless>);
static_assert(is_trivial_v<trivial>);
static_assert(not is_trivial_v<non_trivial_1>);
static_assert(not is_trivial_v<non_trivial_2>);
static_assert(is_trivial_v<trivial_with_deleted_destructor>);
static_assert(is_trivial_v<trivially_copy_constructible>);
static_assert(is_trivial_v<trivially_copy_constructible_non_destructible>);
static_assert(is_trivial_v<trivially_move_constructible>);
static_assert(is_trivial_v<trivially_move_constructible_non_destructible>);
static_assert(is_trivial_v<trivially_copy_assignable>);
static_assert(is_trivial_v<trivially_copy_assignable_non_destructible>);
static_assert(is_trivial_v<trivially_move_assignable>);
static_assert(is_trivial_v<trivially_move_assignable_non_destructible>);
static_assert(not is_trivial_v<trivially_default_constructible_simulator>);
static_assert(not is_trivial_v<trivially_constructible_simulator>);
static_assert(not is_trivial_v<non_trivially_constructible>);
static_assert(not is_trivial_v<only_copy_constructor_implemented>);
static_assert(not is_trivial_v<only_copy_assignment_operator_implemented>);
static_assert(not is_trivial_v<only_move_constructor_implemented>);
static_assert(not is_trivial_v<only_move_assignment_operator_implemented>);
static_assert(not is_trivial_v<unit_test_is_constructible>);
static_assert(not is_trivial_v<unit_test_derived_from_is_constructible>);
static_assert(is_trivial_v<trivially_destructible>);
static_assert(not is_trivial_v<non_trivially_destructible>);
static_assert(is_trivial_v<exceptional_trivially_destructible>);
static_assert(not is_trivial_v<exceptional_non_trivially_destructible>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_trivially_copyable)
static_assert(is_trivially_copyable_v<int>);
static_assert(is_trivially_copyable_v<const int>);
static_assert(is_trivially_copyable_v<volatile int>);
static_assert(is_trivially_copyable_v<const volatile int>);
static_assert(is_trivially_copyable_v<int *>);
static_assert(is_trivially_copyable_v<const int *>);
static_assert(is_trivially_copyable_v<volatile int *>);
static_assert(is_trivially_copyable_v<int *const>);
static_assert(is_trivially_copyable_v<int *volatile>);
static_assert(not is_trivially_copyable_v<int &>);
static_assert(not is_trivially_copyable_v<const int &>);
static_assert(not is_trivially_copyable_v<volatile int &>);
static_assert(not is_trivially_copyable_v<int &&>);
static_assert(not is_trivially_copyable_v<void>);
static_assert(is_trivially_copyable_v<int []>);
static_assert(is_trivially_copyable_v<int [42]>);
static_assert(not is_trivially_copyable_v<int (&)[42]>);
static_assert(not is_trivially_copyable_v<int (&&)[]>);
static_assert(not is_trivially_copyable_v<void ()>);
static_assert(is_trivially_copyable_v<void (*)()>);
static_assert(is_trivially_copyable_v<void (*const)()>);
static_assert(is_trivially_copyable_v<decltype(nullptr)>);
static_assert(not is_trivially_copyable_v<void (&)()>);
static_assert(not is_trivially_copyable_v<void (&&)()>);
static_assert(is_trivially_copyable_v<A>);
//static_assert(is_trivially_copyable_v<B>);     // undefined behavior
static_assert(is_trivially_copyable_v<C>);
static_assert(is_trivially_copyable_v<D>);
//static_assert(is_trivially_copyable_v<E>);     // undefined behavior
static_assert(is_trivially_copyable_v<trivial_stateless>);
static_assert(is_trivially_copyable_v<trivial>);
static_assert(is_trivially_copyable_v<non_trivial_1>);
static_assert(is_trivially_copyable_v<non_trivial_2>);
static_assert(is_trivially_copyable_v<trivial_with_deleted_destructor>);
static_assert(is_trivially_copyable_v<trivially_copy_constructible>);
static_assert(is_trivially_copyable_v<trivially_copy_constructible_non_destructible>);
static_assert(is_trivially_copyable_v<trivially_move_constructible>);
static_assert(is_trivially_copyable_v<trivially_move_constructible_non_destructible>);
static_assert(is_trivially_copyable_v<trivially_copy_assignable>);
static_assert(is_trivially_copyable_v<trivially_copy_assignable_non_destructible>);
static_assert(is_trivially_copyable_v<trivially_move_assignable>);
static_assert(is_trivially_copyable_v<trivially_move_assignable_non_destructible>);
static_assert(is_trivially_copyable_v<trivially_default_constructible_simulator>);
static_assert(is_trivially_copyable_v<trivially_constructible_simulator>);
static_assert(is_trivially_copyable_v<non_trivially_constructible>);
static_assert(not is_trivially_copyable_v<only_copy_constructor_implemented>);
static_assert(not is_trivially_copyable_v<only_copy_assignment_operator_implemented>);
static_assert(not is_trivially_copyable_v<only_move_constructor_implemented>);
static_assert(not is_trivially_copyable_v<only_move_assignment_operator_implemented>);
static_assert(not is_trivially_copyable_v<unit_test_is_constructible>);
static_assert(not is_trivially_copyable_v<unit_test_derived_from_is_constructible>);
static_assert(is_trivially_copyable_v<trivially_destructible>);
static_assert(not is_trivially_copyable_v<non_trivially_destructible>);
static_assert(is_trivially_copyable_v<exceptional_trivially_destructible>);
static_assert(not is_trivially_copyable_v<exceptional_non_trivially_destructible>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_trivially_constructible)
static_assert(is_trivially_constructible_v<int>);
static_assert(is_trivially_constructible_v<const int>);
static_assert(is_trivially_constructible_v<volatile int>);
static_assert(is_trivially_constructible_v<const volatile int>);
static_assert(is_trivially_constructible_v<int *>);
static_assert(is_trivially_constructible_v<const int *>);
static_assert(is_trivially_constructible_v<volatile int *>);
static_assert(is_trivially_constructible_v<int *const>);
static_assert(is_trivially_constructible_v<int *volatile>);
static_assert(not is_trivially_constructible_v<int &>);
static_assert(not is_trivially_constructible_v<const int &>);
static_assert(not is_trivially_constructible_v<volatile int &>);
static_assert(not is_trivially_constructible_v<int &&>);
static_assert(not is_trivially_constructible_v<void>);
static_assert(not is_trivially_constructible_v<int []>);
static_assert(is_trivially_constructible_v<int [42]>);
static_assert(not is_trivially_constructible_v<int (&)[42]>);
static_assert(not is_trivially_constructible_v<int (&&)[]>);
static_assert(not is_trivially_constructible_v<void ()>);
static_assert(is_trivially_constructible_v<void (*)()>);
static_assert(is_trivially_constructible_v<void (*const)()>);
static_assert(is_trivially_constructible_v<decltype(nullptr)>);
static_assert(not is_trivially_constructible_v<void (&)()>);
static_assert(not is_trivially_constructible_v<void (&&)()>);
static_assert(is_trivially_constructible_v<A>);
//static_assert(is_trivially_constructible_v<B>);       // undefined behavior
static_assert(is_trivially_constructible_v<C>);
static_assert(is_trivially_constructible_v<D>);
//static_assert(is_trivially_constructible_v<E>);       // undefined behavior
static_assert(is_trivially_constructible_v<trivial_stateless>);
static_assert(is_trivially_constructible_v<trivial>);
static_assert(not is_trivially_constructible_v<non_trivial_1>);
static_assert(not is_trivially_constructible_v<non_trivial_2>);
static_assert(not is_trivially_constructible_v<trivial_with_deleted_destructor>);
static_assert(not is_trivially_constructible_v<trivially_copy_constructible>);
static_assert(not is_trivially_constructible_v<trivially_copy_constructible_non_destructible>);
static_assert(not is_trivially_constructible_v<trivially_move_constructible>);
static_assert(not is_trivially_constructible_v<trivially_move_constructible_non_destructible>);
static_assert(not is_trivially_constructible_v<trivially_copy_assignable>);
static_assert(not is_trivially_constructible_v<trivially_copy_assignable_non_destructible>);
static_assert(not is_trivially_constructible_v<trivially_move_assignable>);
static_assert(not is_trivially_constructible_v<trivially_move_assignable_non_destructible>);
static_assert(not is_trivially_constructible_v<trivially_default_constructible_simulator>);
static_assert(not is_trivially_constructible_v<trivially_constructible_simulator>);
static_assert(not is_trivially_constructible_v<non_trivially_constructible>);
static_assert(not is_trivially_constructible_v<only_copy_constructor_implemented>);
static_assert(not is_trivially_constructible_v<only_copy_assignment_operator_implemented>);
static_assert(is_trivially_constructible_v<only_move_constructor_implemented>);
static_assert(is_trivially_constructible_v<only_move_assignment_operator_implemented>);
static_assert(not is_trivially_constructible_v<unit_test_is_constructible>);
static_assert(not is_trivially_constructible_v<unit_test_derived_from_is_constructible>);
static_assert(is_trivially_constructible_v<trivially_destructible>);
static_assert(not is_trivially_constructible_v<non_trivially_destructible>);
static_assert(is_trivially_constructible_v<exceptional_trivially_destructible>);
static_assert(not is_trivially_constructible_v<exceptional_non_trivially_destructible>);
static_assert(not is_trivially_constructible_v<trivially_constructible_simulator, int>);
static_assert(not is_trivially_constructible_v<trivially_constructible_simulator &, int>);
static_assert(not is_trivially_constructible_v<trivially_constructible_simulator &&, int>);
static_assert(not is_trivially_constructible_v<const trivially_constructible_simulator &, int>);
static_assert(not is_trivially_constructible_v<volatile trivially_constructible_simulator, int>);
static_assert(not is_trivially_constructible_v<trivially_constructible_simulator, int &>);
static_assert(not is_trivially_constructible_v<trivially_constructible_simulator &, int &>);
static_assert(not is_trivially_constructible_v<trivially_constructible_simulator &&, int &>);
static_assert(not is_trivially_constructible_v<const trivially_constructible_simulator &, int &>);
static_assert(not is_trivially_constructible_v<volatile trivially_constructible_simulator, int &>);
static_assert(not is_trivially_constructible_v<trivially_constructible_simulator, int &&>);
static_assert(not is_trivially_constructible_v<trivially_constructible_simulator &, int &&>);
static_assert(not is_trivially_constructible_v<trivially_constructible_simulator &&, int &&>);
static_assert(not is_trivially_constructible_v<const trivially_constructible_simulator &, int &&>);
static_assert(not is_trivially_constructible_v<volatile trivially_constructible_simulator, int &&>);
static_assert(not is_trivially_constructible_v<trivially_constructible_simulator, const int &>);
static_assert(not is_trivially_constructible_v<trivially_constructible_simulator &, const int &>);
static_assert(not is_trivially_constructible_v<trivially_constructible_simulator &&, const int &>);
static_assert(not is_trivially_constructible_v<const trivially_constructible_simulator &, const int &>);
static_assert(not is_trivially_constructible_v<volatile trivially_constructible_simulator, const int &>);
static_assert(not is_trivially_constructible_v<trivially_constructible_simulator, char>);
static_assert(not is_trivially_constructible_v<trivially_constructible_simulator &, char>);
static_assert(not is_trivially_constructible_v<trivially_constructible_simulator &&, char>);
static_assert(not is_trivially_constructible_v<const trivially_constructible_simulator &, char>);
static_assert(not is_trivially_constructible_v<volatile trivially_constructible_simulator, char>);
static_assert(not is_trivially_constructible_v<trivially_constructible_simulator, void *>);
static_assert(not is_trivially_constructible_v<trivially_constructible_simulator &, void *>);
static_assert(not is_trivially_constructible_v<trivially_constructible_simulator &&, void *>);
static_assert(not is_trivially_constructible_v<const trivially_constructible_simulator &, void *>);
static_assert(not is_trivially_constructible_v<volatile trivially_constructible_simulator, void *>);
static_assert(not is_trivially_constructible_v<trivially_constructible_simulator, double *, std::size_t>);
static_assert(not is_trivially_constructible_v<trivially_constructible_simulator &, double *, std::size_t>);
static_assert(not is_trivially_constructible_v<trivially_constructible_simulator &&, double *, std::size_t>);
static_assert(not is_trivially_constructible_v<const trivially_constructible_simulator &, double *, std::size_t>);
static_assert(not is_trivially_constructible_v<volatile trivially_constructible_simulator, double *, std::size_t>);
static_assert(not is_trivially_constructible_v<trivially_constructible_simulator, double (&)[42]>);
static_assert(not is_trivially_constructible_v<trivially_constructible_simulator &, double (&)[42]>);
static_assert(not is_trivially_constructible_v<trivially_constructible_simulator &&, double (&)[42]>);
static_assert(not is_trivially_constructible_v<const trivially_constructible_simulator &, double (&)[42]>);
static_assert(not is_trivially_constructible_v<volatile trivially_constructible_simulator, double (&)[42]>);
static_assert(not is_trivially_constructible_v<trivially_constructible_simulator, trivially_constructible_simulator *>);
static_assert(not is_trivially_constructible_v<trivially_constructible_simulator &, trivially_constructible_simulator *>);
static_assert(not is_trivially_constructible_v<trivially_constructible_simulator &&, trivially_constructible_simulator *>);
static_assert(not is_trivially_constructible_v<const trivially_constructible_simulator &, trivially_constructible_simulator *>);
static_assert(not is_trivially_constructible_v<volatile trivially_constructible_simulator, trivially_constructible_simulator *>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_trivially_default_constructible)
static_assert(is_trivially_default_constructible_v<int>);
static_assert(is_trivially_default_constructible_v<const int>);
static_assert(is_trivially_default_constructible_v<volatile int>);
static_assert(is_trivially_default_constructible_v<const volatile int>);
static_assert(is_trivially_default_constructible_v<int *>);
static_assert(is_trivially_default_constructible_v<const int *>);
static_assert(is_trivially_default_constructible_v<volatile int *>);
static_assert(is_trivially_default_constructible_v<int *const>);
static_assert(is_trivially_default_constructible_v<int *volatile>);
static_assert(not is_trivially_default_constructible_v<int &>);
static_assert(not is_trivially_default_constructible_v<const int &>);
static_assert(not is_trivially_default_constructible_v<volatile int &>);
static_assert(not is_trivially_default_constructible_v<int &&>);
static_assert(not is_trivially_default_constructible_v<void>);
static_assert(not is_trivially_default_constructible_v<int []>);
static_assert(is_trivially_default_constructible_v<int [42]>);
static_assert(not is_trivially_default_constructible_v<int (&)[42]>);
static_assert(not is_trivially_default_constructible_v<int (&&)[]>);
static_assert(not is_trivially_default_constructible_v<void ()>);
static_assert(is_trivially_default_constructible_v<void (*)()>);
static_assert(is_trivially_default_constructible_v<void (*const)()>);
static_assert(is_trivially_default_constructible_v<decltype(nullptr)>);
static_assert(not is_trivially_default_constructible_v<void (&)()>);
static_assert(not is_trivially_default_constructible_v<void (&&)()>);
static_assert(is_trivially_default_constructible_v<A>);
//static_assert(is_trivially_default_constructible_v<B>);     // undefined behavior
static_assert(is_trivially_default_constructible_v<C>);
static_assert(is_trivially_default_constructible_v<D>);
//static_assert(is_trivially_default_constructible_v<E>);     // undefined behavior
static_assert(is_trivially_default_constructible_v<trivial_stateless>);
static_assert(is_trivially_default_constructible_v<trivial>);
static_assert(not is_trivially_default_constructible_v<non_trivial_1>);
static_assert(not is_trivially_default_constructible_v<non_trivial_2>);
static_assert(not is_trivially_default_constructible_v<trivial_with_deleted_destructor>);
static_assert(not is_trivially_default_constructible_v<trivially_copy_constructible>);
static_assert(not is_trivially_default_constructible_v<trivially_copy_constructible_non_destructible>);
static_assert(not is_trivially_default_constructible_v<trivially_move_constructible>);
static_assert(not is_trivially_default_constructible_v<trivially_move_constructible_non_destructible>);
static_assert(not is_trivially_default_constructible_v<trivially_copy_assignable>);
static_assert(not is_trivially_default_constructible_v<trivially_copy_assignable_non_destructible>);
static_assert(not is_trivially_default_constructible_v<trivially_move_assignable>);
static_assert(not is_trivially_default_constructible_v<trivially_move_assignable_non_destructible>);
static_assert(not is_trivially_default_constructible_v<trivially_default_constructible_simulator>);
static_assert(not is_trivially_default_constructible_v<trivially_constructible_simulator>);
static_assert(not is_trivially_default_constructible_v<non_trivially_constructible>);
static_assert(not is_trivially_default_constructible_v<only_copy_constructor_implemented>);
static_assert(not is_trivially_default_constructible_v<only_copy_assignment_operator_implemented>);
static_assert(is_trivially_default_constructible_v<only_move_constructor_implemented>);
static_assert(is_trivially_default_constructible_v<only_move_assignment_operator_implemented>);
static_assert(not is_trivially_default_constructible_v<unit_test_is_constructible>);
static_assert(not is_trivially_default_constructible_v<unit_test_derived_from_is_constructible>);
static_assert(is_trivially_default_constructible_v<trivially_destructible>);
static_assert(not is_trivially_default_constructible_v<non_trivially_destructible>);
static_assert(is_trivially_default_constructible_v<exceptional_trivially_destructible>);
static_assert(not is_trivially_default_constructible_v<exceptional_non_trivially_destructible>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_trivially_copy_constructible)
static_assert(is_trivially_copy_constructible_v<int>);
static_assert(is_trivially_copy_constructible_v<const int>);
static_assert(is_trivially_copy_constructible_v<volatile int>);
static_assert(is_trivially_copy_constructible_v<const volatile int>);
static_assert(is_trivially_copy_constructible_v<int *>);
static_assert(is_trivially_copy_constructible_v<const int *>);
static_assert(is_trivially_copy_constructible_v<volatile int *>);
static_assert(is_trivially_copy_constructible_v<int *const>);
static_assert(is_trivially_copy_constructible_v<int *volatile>);
static_assert(is_trivially_copy_constructible_v<int &>);
static_assert(is_trivially_copy_constructible_v<const int &>);
static_assert(is_trivially_copy_constructible_v<volatile int &>);
static_assert(not is_trivially_copy_constructible_v<int &&>);
static_assert(not is_trivially_copy_constructible_v<void>);
static_assert(not is_trivially_copy_constructible_v<int []>);
static_assert(not is_trivially_copy_constructible_v<int [42]>);
static_assert(is_trivially_copy_constructible_v<int (&)[42]>);
static_assert(not is_trivially_copy_constructible_v<int (&&)[]>);
static_assert(not is_trivially_copy_constructible_v<void ()>);
static_assert(is_trivially_copy_constructible_v<void (*)()>);
static_assert(is_trivially_copy_constructible_v<void (*const)()>);
static_assert(is_trivially_copy_constructible_v<decltype(nullptr)>);
static_assert(is_trivially_copy_constructible_v<void (&)()>);
static_assert(is_trivially_copy_constructible_v<void (&&)()>);
static_assert(is_trivially_copy_constructible_v<A>);
//static_assert(is_trivially_copy_constructible_v<B>);     // undefined behavior
static_assert(is_trivially_copy_constructible_v<C>);
static_assert(is_trivially_copy_constructible_v<D>);
//static_assert(is_trivially_copy_constructible_v<E>);     // undefined behavior
static_assert(is_trivially_copy_constructible_v<trivial_stateless>);
static_assert(is_trivially_copy_constructible_v<trivial>);
static_assert(is_trivially_copy_constructible_v<non_trivial_1>);
static_assert(is_trivially_copy_constructible_v<non_trivial_2>);
static_assert(not is_trivially_copy_constructible_v<trivial_with_deleted_destructor>);
static_assert(is_trivially_copy_constructible_v<trivially_copy_constructible>);
static_assert(not is_trivially_copy_constructible_v<trivially_copy_constructible_non_destructible>);
static_assert(not is_trivially_copy_constructible_v<trivially_move_constructible>);
static_assert(not is_trivially_copy_constructible_v<trivially_move_constructible_non_destructible>);
static_assert(not is_trivially_copy_constructible_v<trivially_copy_assignable>);
static_assert(not is_trivially_copy_constructible_v<trivially_copy_assignable_non_destructible>);
static_assert(not is_trivially_copy_constructible_v<trivially_move_assignable>);
static_assert(not is_trivially_copy_constructible_v<trivially_move_assignable_non_destructible>);
static_assert(is_trivially_copy_constructible_v<trivially_default_constructible_simulator>);
static_assert(is_trivially_copy_constructible_v<trivially_constructible_simulator>);
static_assert(is_trivially_copy_constructible_v<non_trivially_constructible>);
static_assert(not is_trivially_copy_constructible_v<only_copy_constructor_implemented>);
static_assert(not is_trivially_copy_constructible_v<only_copy_assignment_operator_implemented>);
static_assert(is_trivially_copy_constructible_v<only_move_constructor_implemented>);
static_assert(not is_trivially_copy_constructible_v<only_move_assignment_operator_implemented>);
static_assert(not is_trivially_copy_constructible_v<unit_test_is_constructible>);
static_assert(not is_trivially_copy_constructible_v<unit_test_derived_from_is_constructible>);
static_assert(is_trivially_copy_constructible_v<trivially_destructible>);
static_assert(not is_trivially_copy_constructible_v<non_trivially_destructible>);
static_assert(is_trivially_copy_constructible_v<exceptional_trivially_destructible>);
static_assert(not is_trivially_copy_constructible_v<exceptional_non_trivially_destructible>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_trivially_move_constructible)
static_assert(is_trivially_move_constructible_v<int>);
static_assert(is_trivially_move_constructible_v<const int>);
static_assert(is_trivially_move_constructible_v<volatile int>);
static_assert(is_trivially_move_constructible_v<const volatile int>);
static_assert(is_trivially_move_constructible_v<int *>);
static_assert(is_trivially_move_constructible_v<const int *>);
static_assert(is_trivially_move_constructible_v<volatile int *>);
static_assert(is_trivially_move_constructible_v<int *const>);
static_assert(is_trivially_move_constructible_v<int *volatile>);
static_assert(is_trivially_move_constructible_v<int &>);
static_assert(is_trivially_move_constructible_v<const int &>);
static_assert(is_trivially_move_constructible_v<volatile int &>);
static_assert(is_trivially_move_constructible_v<int &&>);
static_assert(not is_trivially_move_constructible_v<void>);
static_assert(not is_trivially_move_constructible_v<int []>);
static_assert(not is_trivially_move_constructible_v<int [42]>);
static_assert(is_trivially_move_constructible_v<int (&)[42]>);
static_assert(is_trivially_move_constructible_v<int (&&)[]>);
static_assert(not is_trivially_move_constructible_v<void ()>);
static_assert(is_trivially_move_constructible_v<void (*)()>);
static_assert(is_trivially_move_constructible_v<void (*const)()>);
static_assert(is_trivially_move_constructible_v<decltype(nullptr)>);
static_assert(is_trivially_move_constructible_v<void (&)()>);
static_assert(is_trivially_move_constructible_v<void (&&)()>);
static_assert(is_trivially_move_constructible_v<A>);
//static_assert(is_trivially_move_constructible_v<B>);     // undefined behavior
static_assert(is_trivially_move_constructible_v<C>);
static_assert(is_trivially_move_constructible_v<D>);
//static_assert(is_trivially_move_constructible_v<E>);     // undefined behavior
static_assert(is_trivially_move_constructible_v<trivial_stateless>);
static_assert(is_trivially_move_constructible_v<trivial>);
static_assert(is_trivially_move_constructible_v<non_trivial_1>);
static_assert(is_trivially_move_constructible_v<non_trivial_2>);
static_assert(not is_trivially_move_constructible_v<trivial_with_deleted_destructor>);
static_assert(not is_trivially_move_constructible_v<trivially_copy_constructible>);
static_assert(not is_trivially_move_constructible_v<trivially_copy_constructible_non_destructible>);
static_assert(is_trivially_move_constructible_v<trivially_move_constructible>);
static_assert(not is_trivially_move_constructible_v<trivially_move_constructible_non_destructible>);
static_assert(not is_trivially_move_constructible_v<trivially_copy_assignable>);
static_assert(not is_trivially_move_constructible_v<trivially_copy_assignable_non_destructible>);
static_assert(not is_trivially_move_constructible_v<trivially_move_assignable>);
static_assert(not is_trivially_move_constructible_v<trivially_move_assignable_non_destructible>);
static_assert(is_trivially_move_constructible_v<trivially_default_constructible_simulator>);
static_assert(is_trivially_move_constructible_v<trivially_constructible_simulator>);
static_assert(is_trivially_move_constructible_v<non_trivially_constructible>);
static_assert(not is_trivially_move_constructible_v<only_copy_constructor_implemented>);
static_assert(not is_trivially_move_constructible_v<only_copy_assignment_operator_implemented>);
static_assert(is_trivially_move_constructible_v<only_move_constructor_implemented>);
static_assert(not is_trivially_move_constructible_v<only_move_assignment_operator_implemented>);
static_assert(not is_trivially_move_constructible_v<unit_test_is_constructible>);
static_assert(not is_trivially_move_constructible_v<unit_test_derived_from_is_constructible>);
static_assert(is_trivially_move_constructible_v<trivially_destructible>);
static_assert(not is_trivially_move_constructible_v<non_trivially_destructible>);
static_assert(is_trivially_move_constructible_v<exceptional_trivially_destructible>);
static_assert(not is_trivially_move_constructible_v<exceptional_non_trivially_destructible>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_trivially_assignable)
static_assert(not is_trivially_assignable_v<int>);      // int is an rvalue type, cannot be assigned
static_assert(not is_trivially_assignable_v<const int>);
static_assert(not is_trivially_assignable_v<volatile int>);
static_assert(not is_trivially_assignable_v<const volatile int>);
static_assert(not is_trivially_assignable_v<int *>);
static_assert(not is_trivially_assignable_v<const int *>);
static_assert(not is_trivially_assignable_v<volatile int *>);
static_assert(not is_trivially_assignable_v<int *const>);
static_assert(not is_trivially_assignable_v<int *volatile>);
static_assert(is_trivially_assignable_v<int &>);
static_assert(not is_trivially_assignable_v<const int &>);
static_assert(is_trivially_assignable_v<volatile int &>);
static_assert(not is_trivially_assignable_v<int &&>);
static_assert(not is_trivially_assignable_v<void>);
static_assert(not is_trivially_assignable_v<int []>);
static_assert(not is_trivially_assignable_v<int [42]>);
static_assert(not is_trivially_assignable_v<int (&)[42]>);
static_assert(not is_trivially_assignable_v<int (&&)[]>);
static_assert(not is_trivially_assignable_v<void ()>);
static_assert(not is_trivially_assignable_v<void (*)()>);
static_assert(not is_trivially_assignable_v<void (*const)()>);
static_assert(not is_trivially_assignable_v<decltype(nullptr)>);
static_assert(not is_trivially_assignable_v<void (&)()>);
static_assert(not is_trivially_assignable_v<void (&&)()>);
static_assert(is_trivially_assignable_v<A>);
//static_assert(is_trivially_assignable_v<B>);     // undefined behavior
static_assert(not is_trivially_assignable_v<C>);
static_assert(not is_trivially_assignable_v<D>);
//static_assert(is_trivially_assignable_v<E>);     // undefined behavior
static_assert(is_trivially_assignable_v<trivial_stateless>);
static_assert(is_trivially_assignable_v<trivial>);
static_assert(is_trivially_assignable_v<non_trivial_1>);
static_assert(is_trivially_assignable_v<non_trivial_2>);
static_assert(is_trivially_assignable_v<trivial_with_deleted_destructor>);
static_assert(not is_trivially_assignable_v<trivially_copy_constructible>);
static_assert(not is_trivially_assignable_v<trivially_copy_constructible_non_destructible>);
static_assert(not is_trivially_assignable_v<trivially_move_constructible>);
static_assert(not is_trivially_assignable_v<trivially_move_constructible_non_destructible>);
static_assert(not is_trivially_assignable_v<trivially_copy_assignable>);
static_assert(not is_trivially_assignable_v<trivially_copy_assignable_non_destructible>);
static_assert(is_trivially_assignable_v<trivially_move_assignable>);
static_assert(is_trivially_assignable_v<trivially_move_assignable_non_destructible>);
static_assert(is_trivially_assignable_v<trivially_default_constructible_simulator>);
static_assert(is_trivially_assignable_v<trivially_constructible_simulator>);
static_assert(is_trivially_assignable_v<non_trivially_constructible>);
static_assert(is_trivially_assignable_v<only_copy_constructor_implemented>);
static_assert(not is_trivially_assignable_v<only_copy_assignment_operator_implemented>);
static_assert(not is_trivially_assignable_v<only_move_constructor_implemented>);
static_assert(not is_trivially_assignable_v<only_move_assignment_operator_implemented>);
static_assert(not is_trivially_assignable_v<unit_test_is_constructible>);
static_assert(not is_trivially_assignable_v<unit_test_derived_from_is_constructible>);
static_assert(is_trivially_assignable_v<trivially_destructible>);
static_assert(is_trivially_assignable_v<non_trivially_destructible>);
static_assert(is_trivially_assignable_v<exceptional_trivially_destructible>);
static_assert(is_trivially_assignable_v<exceptional_non_trivially_destructible>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_trivially_copy_assignable)
static_assert(is_trivially_copy_assignable_v<int>);
static_assert(not is_trivially_copy_assignable_v<const int>);
static_assert(is_trivially_copy_assignable_v<volatile int>);
static_assert(not is_trivially_copy_assignable_v<const volatile int>);
static_assert(is_trivially_copy_assignable_v<int *>);
static_assert(is_trivially_copy_assignable_v<const int *>);
static_assert(is_trivially_copy_assignable_v<volatile int *>);
static_assert(not is_trivially_copy_assignable_v<int *const>);
static_assert(is_trivially_copy_assignable_v<int *volatile>);
static_assert(is_trivially_copy_assignable_v<int &>);
static_assert(not is_trivially_copy_assignable_v<const int &>);
static_assert(is_trivially_copy_assignable_v<volatile int &>);
static_assert(is_trivially_copy_assignable_v<int &&>);
static_assert(not is_trivially_copy_assignable_v<void>);
static_assert(not is_trivially_copy_assignable_v<int []>);
static_assert(not is_trivially_copy_assignable_v<int [42]>);
static_assert(not is_trivially_copy_assignable_v<int (&)[42]>);
static_assert(not is_trivially_copy_assignable_v<int (&&)[]>);
static_assert(not is_trivially_copy_assignable_v<void ()>);
static_assert(is_trivially_copy_assignable_v<void (*)()>);
static_assert(not is_trivially_copy_assignable_v<void (*const)()>);
static_assert(is_trivially_copy_assignable_v<decltype(nullptr)>);
static_assert(not is_trivially_copy_assignable_v<void (&)()>);
static_assert(not is_trivially_copy_assignable_v<void (&&)()>);
static_assert(is_trivially_copy_assignable_v<A>);
//static_assert(is_trivially_copy_assignable_v<B>);     // undefined behavior
static_assert(is_trivially_copy_assignable_v<C>);
static_assert(is_trivially_copy_assignable_v<D>);
//static_assert(is_trivially_copy_assignable_v<E>);     // undefined behavior
static_assert(is_trivially_copy_assignable_v<trivial_stateless>);
static_assert(is_trivially_copy_assignable_v<trivial>);
static_assert(is_trivially_copy_assignable_v<non_trivial_1>);
static_assert(is_trivially_copy_assignable_v<non_trivial_2>);
static_assert(is_trivially_copy_assignable_v<trivial_with_deleted_destructor>);
static_assert(not is_trivially_copy_assignable_v<trivially_copy_constructible>);
static_assert(not is_trivially_copy_assignable_v<trivially_copy_constructible_non_destructible>);
static_assert(not is_trivially_copy_assignable_v<trivially_move_constructible>);
static_assert(not is_trivially_copy_assignable_v<trivially_move_constructible_non_destructible>);
static_assert(is_trivially_copy_assignable_v<trivially_copy_assignable>);
static_assert(is_trivially_copy_assignable_v<trivially_copy_assignable_non_destructible>);
static_assert(not is_trivially_copy_assignable_v<trivially_move_assignable>);
static_assert(not is_trivially_copy_assignable_v<trivially_move_assignable_non_destructible>);
static_assert(is_trivially_copy_assignable_v<trivially_default_constructible_simulator>);
static_assert(is_trivially_copy_assignable_v<trivially_constructible_simulator>);
static_assert(is_trivially_copy_assignable_v<non_trivially_constructible>);
static_assert(is_trivially_copy_assignable_v<only_copy_constructor_implemented>);
static_assert(not is_trivially_copy_assignable_v<only_copy_assignment_operator_implemented>);
static_assert(not is_trivially_copy_assignable_v<only_move_constructor_implemented>);
static_assert(not is_trivially_copy_assignable_v<only_move_assignment_operator_implemented>);
static_assert(not is_trivially_copy_assignable_v<unit_test_is_constructible>);
static_assert(not is_trivially_copy_assignable_v<unit_test_derived_from_is_constructible>);
static_assert(is_trivially_copy_assignable_v<trivially_destructible>);
static_assert(is_trivially_copy_assignable_v<non_trivially_destructible>);
static_assert(is_trivially_copy_assignable_v<exceptional_trivially_destructible>);
static_assert(is_trivially_copy_assignable_v<exceptional_non_trivially_destructible>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_trivially_move_assignable)
static_assert(is_trivially_move_assignable_v<int>);
static_assert(not is_trivially_move_assignable_v<const int>);
static_assert(is_trivially_move_assignable_v<volatile int>);
static_assert(not is_trivially_move_assignable_v<const volatile int>);
static_assert(is_trivially_move_assignable_v<int *>);
static_assert(is_trivially_move_assignable_v<const int *>);
static_assert(is_trivially_move_assignable_v<volatile int *>);
static_assert(not is_trivially_move_assignable_v<int *const>);
static_assert(is_trivially_move_assignable_v<int *volatile>);
static_assert(is_trivially_move_assignable_v<int &>);
static_assert(not is_trivially_move_assignable_v<const int &>);
static_assert(is_trivially_move_assignable_v<volatile int &>);
static_assert(is_trivially_move_assignable_v<int &&>);
static_assert(not is_trivially_move_assignable_v<void>);
static_assert(not is_trivially_move_assignable_v<int []>);
static_assert(not is_trivially_move_assignable_v<int [42]>);
static_assert(not is_trivially_move_assignable_v<int (&)[42]>);
static_assert(not is_trivially_move_assignable_v<int (&&)[]>);
static_assert(not is_trivially_move_assignable_v<void ()>);
static_assert(is_trivially_move_assignable_v<void (*)()>);
static_assert(not is_trivially_move_assignable_v<void (*const)()>);
static_assert(is_trivially_move_assignable_v<decltype(nullptr)>);
static_assert(not is_trivially_move_assignable_v<void (&)()>);
static_assert(not is_trivially_move_assignable_v<void (&&)()>);
static_assert(is_trivially_move_assignable_v<A>);
//static_assert(is_trivially_move_assignable_v<B>);     // undefined behavior
static_assert(is_trivially_move_assignable_v<C>);
static_assert(is_trivially_move_assignable_v<D>);
//static_assert(is_trivially_move_assignable_v<E>);     // undefined behavior
static_assert(is_trivially_move_assignable_v<trivial_stateless>);
static_assert(is_trivially_move_assignable_v<trivial>);
static_assert(is_trivially_move_assignable_v<non_trivial_1>);
static_assert(is_trivially_move_assignable_v<non_trivial_2>);
static_assert(is_trivially_move_assignable_v<trivial_with_deleted_destructor>);
static_assert(not is_trivially_move_assignable_v<trivially_copy_constructible>);
static_assert(not is_trivially_move_assignable_v<trivially_copy_constructible_non_destructible>);
static_assert(not is_trivially_move_assignable_v<trivially_move_constructible>);
static_assert(not is_trivially_move_assignable_v<trivially_move_constructible_non_destructible>);
static_assert(not is_trivially_move_assignable_v<trivially_copy_assignable>);
static_assert(not is_trivially_move_assignable_v<trivially_copy_assignable_non_destructible>);
static_assert(is_trivially_move_assignable_v<trivially_move_assignable>);
static_assert(is_trivially_move_assignable_v<trivially_move_assignable_non_destructible>);
static_assert(is_trivially_move_assignable_v<trivially_default_constructible_simulator>);
static_assert(is_trivially_move_assignable_v<trivially_constructible_simulator>);
static_assert(is_trivially_move_assignable_v<non_trivially_constructible>);
static_assert(is_trivially_move_assignable_v<only_copy_constructor_implemented>);
static_assert(not is_trivially_move_assignable_v<only_copy_assignment_operator_implemented>);
static_assert(not is_trivially_move_assignable_v<only_move_constructor_implemented>);
static_assert(not is_trivially_move_assignable_v<only_move_assignment_operator_implemented>);
static_assert(not is_trivially_move_assignable_v<unit_test_is_constructible>);
static_assert(not is_trivially_move_assignable_v<unit_test_derived_from_is_constructible>);
static_assert(is_trivially_move_assignable_v<trivially_destructible>);
static_assert(is_trivially_move_assignable_v<non_trivially_destructible>);
static_assert(is_trivially_move_assignable_v<exceptional_trivially_destructible>);
static_assert(is_trivially_move_assignable_v<exceptional_non_trivially_destructible>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_convertible)

__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_trivially_destructible)
static_assert(is_trivially_destructible_v<int>);
static_assert(is_trivially_destructible_v<const int>);
static_assert(is_trivially_destructible_v<volatile int>);
static_assert(is_trivially_destructible_v<const volatile int>);
static_assert(is_trivially_destructible_v<int *>);
static_assert(is_trivially_destructible_v<const int *>);
static_assert(is_trivially_destructible_v<volatile int *>);
static_assert(is_trivially_destructible_v<int *const>);
static_assert(is_trivially_destructible_v<int *volatile>);
static_assert(is_trivially_destructible_v<int &>);
static_assert(is_trivially_destructible_v<const int &>);
static_assert(is_trivially_destructible_v<volatile int &>);
static_assert(is_trivially_destructible_v<int &&>);
static_assert(not is_trivially_destructible_v<void>);
static_assert(not is_trivially_destructible_v<int []>);
static_assert(is_trivially_destructible_v<int [42]>);
static_assert(is_trivially_destructible_v<int (&)[42]>);
static_assert(is_trivially_destructible_v<int (&&)[]>);
static_assert(not is_trivially_destructible_v<void ()>);
static_assert(is_trivially_destructible_v<void (*)()>);
static_assert(is_trivially_destructible_v<void (*const)()>);
static_assert(is_trivially_destructible_v<decltype(nullptr)>);
static_assert(is_trivially_destructible_v<void (&)()>);
static_assert(is_trivially_destructible_v<void (&&)()>);
static_assert(is_trivially_destructible_v<A>);
//static_assert(is_trivially_destructible_v<B>);     // undefined behavior
static_assert(is_trivially_destructible_v<C>);
static_assert(is_trivially_destructible_v<D>);
//static_assert(is_trivially_destructible_v<E>);     // undefined behavior
static_assert(is_trivially_destructible_v<trivial_stateless>);
static_assert(is_trivially_destructible_v<trivial>);
static_assert(is_trivially_destructible_v<non_trivial_1>);
static_assert(is_trivially_destructible_v<non_trivial_2>);
static_assert(not is_trivially_destructible_v<trivial_with_deleted_destructor>);
static_assert(is_trivially_destructible_v<trivially_copy_constructible>);
static_assert(not is_trivially_destructible_v<trivially_copy_constructible_non_destructible>);
static_assert(is_trivially_destructible_v<trivially_move_constructible>);
static_assert(not is_trivially_destructible_v<trivially_move_constructible_non_destructible>);
static_assert(is_trivially_destructible_v<trivially_copy_assignable>);
static_assert(not is_trivially_destructible_v<trivially_copy_assignable_non_destructible>);
static_assert(is_trivially_destructible_v<trivially_move_assignable>);
static_assert(not is_trivially_destructible_v<trivially_move_assignable_non_destructible>);
static_assert(is_trivially_destructible_v<trivially_default_constructible_simulator>);
static_assert(is_trivially_destructible_v<trivially_constructible_simulator>);
static_assert(is_trivially_destructible_v<non_trivially_constructible>);
static_assert(is_trivially_destructible_v<only_copy_constructor_implemented>);
static_assert(is_trivially_destructible_v<only_copy_assignment_operator_implemented>);
static_assert(is_trivially_destructible_v<only_move_constructor_implemented>);
static_assert(is_trivially_destructible_v<only_move_assignment_operator_implemented>);
static_assert(is_trivially_destructible_v<unit_test_is_constructible>);
static_assert(is_trivially_destructible_v<unit_test_derived_from_is_constructible>);
static_assert(is_trivially_destructible_v<trivially_destructible>);
static_assert(not is_trivially_destructible_v<non_trivially_destructible>);
static_assert(is_trivially_destructible_v<exceptional_trivially_destructible>);
static_assert(not is_trivially_destructible_v<exceptional_non_trivially_destructible>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_constructible)
static_assert(is_constructible_v<int>);
static_assert(is_constructible_v<const int>);
static_assert(is_constructible_v<volatile int>);
static_assert(is_constructible_v<const volatile int>);
static_assert(is_constructible_v<int *>);
static_assert(is_constructible_v<const int *>);
static_assert(is_constructible_v<volatile int *>);
static_assert(is_constructible_v<int *const>);
static_assert(is_constructible_v<int *volatile>);
static_assert(not is_constructible_v<int &>);
static_assert(not is_constructible_v<const int &>);
static_assert(not is_constructible_v<volatile int &>);
static_assert(not is_constructible_v<int &&>);
static_assert(not is_constructible_v<void>);
static_assert(not is_constructible_v<int []>);
static_assert(is_constructible_v<int [42]>);
static_assert(not is_constructible_v<int (&)[42]>);
static_assert(not is_constructible_v<int (&&)[]>);
static_assert(not is_constructible_v<void ()>);
static_assert(is_constructible_v<void (*)()>);
static_assert(is_constructible_v<void (*const)()>);
static_assert(is_constructible_v<decltype(nullptr)>);
static_assert(not is_constructible_v<void (&)()>);
static_assert(not is_constructible_v<void (&&)()>);
static_assert(is_constructible_v<A>);
//static_assert(is_constructible_v<B>);       // undefined behavior
static_assert(is_constructible_v<C>);
static_assert(is_constructible_v<D>);
//static_assert(is_constructible_v<E>);       // undefined behavior
static_assert(is_constructible_v<trivial_stateless>);
static_assert(is_constructible_v<trivial>);
static_assert(is_constructible_v<non_trivial_1>);
static_assert(is_constructible_v<non_trivial_2>);
static_assert(not is_constructible_v<trivial_with_deleted_destructor>);
static_assert(not is_constructible_v<trivially_copy_constructible>);
static_assert(not is_constructible_v<trivially_copy_constructible_non_destructible>);
static_assert(not is_constructible_v<trivially_move_constructible>);
static_assert(not is_constructible_v<trivially_move_constructible_non_destructible>);
static_assert(not is_constructible_v<trivially_copy_assignable>);
static_assert(not is_constructible_v<trivially_copy_assignable_non_destructible>);
static_assert(not is_constructible_v<trivially_move_assignable>);
static_assert(not is_constructible_v<trivially_move_assignable_non_destructible>);
static_assert(is_constructible_v<trivially_default_constructible_simulator>);
static_assert(not is_constructible_v<trivially_constructible_simulator>);
static_assert(is_constructible_v<non_trivially_constructible>);
static_assert(not is_constructible_v<only_copy_constructor_implemented>);
static_assert(not is_constructible_v<only_copy_assignment_operator_implemented>);
static_assert(is_constructible_v<only_move_constructor_implemented>);
static_assert(is_constructible_v<only_move_assignment_operator_implemented>);
static_assert(not is_constructible_v<unit_test_is_constructible>);
static_assert(not is_constructible_v<unit_test_derived_from_is_constructible>);
static_assert(is_constructible_v<trivially_destructible>);
static_assert(is_constructible_v<non_trivially_destructible>);
static_assert(is_constructible_v<exceptional_trivially_destructible>);
static_assert(is_constructible_v<exceptional_non_trivially_destructible>);
static_assert(is_constructible_v<trivially_constructible_simulator, int>);
static_assert(not is_constructible_v<trivially_constructible_simulator &, int>);
static_assert(is_constructible_v<trivially_constructible_simulator &&, int>);
static_assert(is_constructible_v<const trivially_constructible_simulator &, int>);
static_assert(is_constructible_v<volatile trivially_constructible_simulator, int>);
static_assert(is_constructible_v<trivially_constructible_simulator, int &>);
static_assert(not is_constructible_v<trivially_constructible_simulator &, int &>);
static_assert(is_constructible_v<trivially_constructible_simulator &&, int &>);
static_assert(is_constructible_v<const trivially_constructible_simulator &, int &>);
static_assert(is_constructible_v<volatile trivially_constructible_simulator, int &>);
static_assert(is_constructible_v<trivially_constructible_simulator, int &&>);
static_assert(not is_constructible_v<trivially_constructible_simulator &, int &&>);
static_assert(is_constructible_v<trivially_constructible_simulator &&, int &&>);
static_assert(is_constructible_v<const trivially_constructible_simulator &, int &&>);
static_assert(is_constructible_v<volatile trivially_constructible_simulator, int &&>);
static_assert(is_constructible_v<trivially_constructible_simulator, const int &>);
static_assert(not is_constructible_v<trivially_constructible_simulator &, const int &>);
static_assert(is_constructible_v<trivially_constructible_simulator &&, const int &>);
static_assert(is_constructible_v<const trivially_constructible_simulator &, const int &>);
static_assert(is_constructible_v<volatile trivially_constructible_simulator, const int &>);
static_assert(is_constructible_v<trivially_constructible_simulator, char>);
static_assert(not is_constructible_v<trivially_constructible_simulator &, char>);
static_assert(is_constructible_v<trivially_constructible_simulator &&, char>);
static_assert(is_constructible_v<const trivially_constructible_simulator &, char>);
static_assert(is_constructible_v<volatile trivially_constructible_simulator, char>);
static_assert(is_constructible_v<trivially_constructible_simulator, void *>);
static_assert(not is_constructible_v<trivially_constructible_simulator &, void *>);
static_assert(is_constructible_v<trivially_constructible_simulator &&, void *>);
static_assert(is_constructible_v<const trivially_constructible_simulator &, void *>);
static_assert(is_constructible_v<volatile trivially_constructible_simulator, void *>);
static_assert(is_constructible_v<trivially_constructible_simulator, double *, std::size_t>);
static_assert(not is_constructible_v<trivially_constructible_simulator &, double *, std::size_t>);
static_assert(not is_constructible_v<trivially_constructible_simulator &&, double *, std::size_t>);
static_assert(not is_constructible_v<const trivially_constructible_simulator &, double *, std::size_t>);
static_assert(is_constructible_v<volatile trivially_constructible_simulator, double *, std::size_t>);
static_assert(is_constructible_v<trivially_constructible_simulator, double (&)[42]>);
static_assert(not is_constructible_v<trivially_constructible_simulator &, double (&)[42]>);
static_assert(is_constructible_v<trivially_constructible_simulator &&, double (&)[42]>);
static_assert(is_constructible_v<const trivially_constructible_simulator &, double (&)[42]>);
static_assert(is_constructible_v<volatile trivially_constructible_simulator, double (&)[42]>);
static_assert(is_constructible_v<trivially_constructible_simulator, trivially_constructible_simulator *>);
static_assert(not is_constructible_v<trivially_constructible_simulator &, trivially_constructible_simulator *>);
static_assert(is_constructible_v<trivially_constructible_simulator &&, trivially_constructible_simulator *>);
static_assert(is_constructible_v<const trivially_constructible_simulator &, trivially_constructible_simulator *>);
static_assert(is_constructible_v<volatile trivially_constructible_simulator, trivially_constructible_simulator *>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_default_constructible)
static_assert(is_default_constructible_v<int>);
static_assert(is_default_constructible_v<const int>);
static_assert(is_default_constructible_v<volatile int>);
static_assert(is_default_constructible_v<const volatile int>);
static_assert(is_default_constructible_v<int *>);
static_assert(is_default_constructible_v<const int *>);
static_assert(is_default_constructible_v<volatile int *>);
static_assert(is_default_constructible_v<int *const>);
static_assert(is_default_constructible_v<int *volatile>);
static_assert(not is_default_constructible_v<int &>);
static_assert(not is_default_constructible_v<const int &>);
static_assert(not is_default_constructible_v<volatile int &>);
static_assert(not is_default_constructible_v<int &&>);
static_assert(not is_default_constructible_v<void>);
static_assert(not is_default_constructible_v<int []>);
static_assert(is_default_constructible_v<int [42]>);
static_assert(not is_default_constructible_v<int (&)[42]>);
static_assert(not is_default_constructible_v<int (&&)[]>);
static_assert(not is_default_constructible_v<void ()>);
static_assert(is_default_constructible_v<void (*)()>);
static_assert(is_default_constructible_v<void (*const)()>);
static_assert(is_default_constructible_v<decltype(nullptr)>);
static_assert(not is_default_constructible_v<void (&)()>);
static_assert(not is_default_constructible_v<void (&&)()>);
static_assert(is_default_constructible_v<A>);
//static_assert(is_default_constructible_v<B>);     // undefined behavior
static_assert(is_default_constructible_v<C>);
static_assert(is_default_constructible_v<D>);
//static_assert(is_default_constructible_v<E>);     // undefined behavior
static_assert(is_default_constructible_v<trivial_stateless>);
static_assert(is_default_constructible_v<trivial>);
static_assert(is_default_constructible_v<non_trivial_1>);
static_assert(is_default_constructible_v<non_trivial_2>);
static_assert(not is_default_constructible_v<trivial_with_deleted_destructor>);
static_assert(not is_default_constructible_v<trivially_copy_constructible>);
static_assert(not is_default_constructible_v<trivially_copy_constructible_non_destructible>);
static_assert(not is_default_constructible_v<trivially_move_constructible>);
static_assert(not is_default_constructible_v<trivially_move_constructible_non_destructible>);
static_assert(not is_default_constructible_v<trivially_copy_assignable>);
static_assert(not is_default_constructible_v<trivially_copy_assignable_non_destructible>);
static_assert(not is_default_constructible_v<trivially_move_assignable>);
static_assert(not is_default_constructible_v<trivially_move_assignable_non_destructible>);
static_assert(is_default_constructible_v<trivially_default_constructible_simulator>);
static_assert(not is_default_constructible_v<trivially_constructible_simulator>);
static_assert(is_default_constructible_v<non_trivially_constructible>);
static_assert(not is_default_constructible_v<only_copy_constructor_implemented>);
static_assert(not is_default_constructible_v<only_copy_assignment_operator_implemented>);
static_assert(is_default_constructible_v<only_move_constructor_implemented>);
static_assert(is_default_constructible_v<only_move_assignment_operator_implemented>);
static_assert(not is_default_constructible_v<unit_test_is_constructible>);
static_assert(not is_default_constructible_v<unit_test_derived_from_is_constructible>);
static_assert(is_default_constructible_v<trivially_destructible>);
static_assert(is_default_constructible_v<non_trivially_destructible>);
static_assert(is_default_constructible_v<exceptional_trivially_destructible>);
static_assert(is_default_constructible_v<exceptional_non_trivially_destructible>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for is_copy_constructible)
static_assert(is_copy_constructible_v<int>);
static_assert(is_copy_constructible_v<const int>);
static_assert(is_copy_constructible_v<volatile int>);
static_assert(is_copy_constructible_v<const volatile int>);
static_assert(is_copy_constructible_v<int *>);
static_assert(is_copy_constructible_v<const int *>);
static_assert(is_copy_constructible_v<volatile int *>);
static_assert(is_copy_constructible_v<int *const>);
static_assert(is_copy_constructible_v<int *volatile>);
static_assert(not is_copy_constructible_v<int &>);
static_assert(is_copy_constructible_v<const int &>);
static_assert(not is_copy_constructible_v<volatile int &>);
static_assert(not is_copy_constructible_v<int &&>);
static_assert(not is_copy_constructible_v<void>);
static_assert(not is_copy_constructible_v<int []>);
static_assert(not is_copy_constructible_v<int [42]>);
static_assert(not is_copy_constructible_v<int (&)[42]>);
static_assert(not is_copy_constructible_v<int (&&)[]>);
static_assert(not is_copy_constructible_v<void ()>);
static_assert(is_copy_constructible_v<void (*)()>);
static_assert(is_copy_constructible_v<void (*const)()>);
static_assert(is_copy_constructible_v<decltype(nullptr)>);
static_assert(is_copy_constructible_v<void (&)()>);
static_assert(is_copy_constructible_v<void (&&)()>);
static_assert(is_copy_constructible_v<A>);
//static_assert(is_copy_constructible_v<B>);     // undefined behavior
static_assert(is_copy_constructible_v<C>);
static_assert(is_copy_constructible_v<D>);
//static_assert(is_copy_constructible_v<E>);     // undefined behavior
static_assert(is_copy_constructible_v<trivial_stateless>);
static_assert(is_copy_constructible_v<trivial>);
static_assert(is_copy_constructible_v<non_trivial_1>);
static_assert(is_copy_constructible_v<non_trivial_2>);
static_assert(not is_copy_constructible_v<trivial_with_deleted_destructor>);
static_assert(is_copy_constructible_v<trivially_copy_constructible>);
static_assert(not is_copy_constructible_v<trivially_copy_constructible_non_destructible>);
static_assert(not is_copy_constructible_v<trivially_move_constructible>);
static_assert(not is_copy_constructible_v<trivially_move_constructible_non_destructible>);
static_assert(not is_copy_constructible_v<trivially_copy_assignable>);
static_assert(not is_copy_constructible_v<trivially_copy_assignable_non_destructible>);
static_assert(not is_copy_constructible_v<trivially_move_assignable>);
static_assert(not is_copy_constructible_v<trivially_move_assignable_non_destructible>);
static_assert(is_copy_constructible_v<trivially_default_constructible_simulator>);
static_assert(is_copy_constructible_v<trivially_constructible_simulator>);
static_assert(is_copy_constructible_v<non_trivially_constructible>);
static_assert(is_copy_constructible_v<only_copy_constructor_implemented>);
static_assert(not is_copy_constructible_v<only_copy_assignment_operator_implemented>);
static_assert(is_copy_constructible_v<only_move_constructor_implemented>);
static_assert(not is_copy_constructible_v<only_move_assignment_operator_implemented>);
static_assert(is_copy_constructible_v<unit_test_is_constructible>);
static_assert(is_copy_constructible_v<unit_test_derived_from_is_constructible>);
static_assert(is_copy_constructible_v<trivially_destructible>);
static_assert(is_copy_constructible_v<non_trivially_destructible>);
static_assert(is_copy_constructible_v<exceptional_trivially_destructible>);
static_assert(is_copy_constructible_v<exceptional_non_trivially_destructible>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_move_constructible)
static_assert(is_move_constructible_v<int>);
static_assert(is_move_constructible_v<const int>);
static_assert(is_move_constructible_v<volatile int>);
static_assert(is_move_constructible_v<const volatile int>);
static_assert(is_move_constructible_v<int *>);
static_assert(is_move_constructible_v<const int *>);
static_assert(is_move_constructible_v<volatile int *>);
static_assert(is_move_constructible_v<int *const>);
static_assert(is_move_constructible_v<int *volatile>);
static_assert(is_move_constructible_v<int &>);
static_assert(is_move_constructible_v<const int &>);
static_assert(is_move_constructible_v<volatile int &>);
static_assert(is_move_constructible_v<int &&>);
static_assert(not is_move_constructible_v<void>);
static_assert(not is_move_constructible_v<int []>);
static_assert(not is_move_constructible_v<int [42]>);
static_assert(is_move_constructible_v<int (&)[42]>);
static_assert(is_move_constructible_v<int (&&)[]>);
static_assert(not is_move_constructible_v<void ()>);
static_assert(is_move_constructible_v<void (*)()>);
static_assert(is_move_constructible_v<void (*const)()>);
static_assert(is_move_constructible_v<decltype(nullptr)>);
static_assert(is_move_constructible_v<void (&)()>);
static_assert(is_move_constructible_v<void (&&)()>);
static_assert(is_move_constructible_v<A>);
//static_assert(is_move_constructible_v<B>);     // undefined behavior
static_assert(is_move_constructible_v<C>);
static_assert(is_move_constructible_v<D>);
//static_assert(is_move_constructible_v<E>);     // undefined behavior
static_assert(is_move_constructible_v<trivial_stateless>);
static_assert(is_move_constructible_v<trivial>);
static_assert(is_move_constructible_v<non_trivial_1>);
static_assert(is_move_constructible_v<non_trivial_2>);
static_assert(not is_move_constructible_v<trivial_with_deleted_destructor>);
static_assert(not is_move_constructible_v<trivially_copy_constructible>);
static_assert(not is_move_constructible_v<trivially_copy_constructible_non_destructible>);
static_assert(is_move_constructible_v<trivially_move_constructible>);
static_assert(not is_move_constructible_v<trivially_move_constructible_non_destructible>);
static_assert(not is_move_constructible_v<trivially_copy_assignable>);
static_assert(not is_move_constructible_v<trivially_copy_assignable_non_destructible>);
static_assert(not is_move_constructible_v<trivially_move_assignable>);
static_assert(not is_move_constructible_v<trivially_move_assignable_non_destructible>);
static_assert(is_move_constructible_v<trivially_default_constructible_simulator>);
static_assert(is_move_constructible_v<trivially_constructible_simulator>);
static_assert(is_move_constructible_v<non_trivially_constructible>);
static_assert(is_move_constructible_v<only_copy_constructor_implemented>);
static_assert(is_move_constructible_v<only_copy_assignment_operator_implemented>);
static_assert(is_move_constructible_v<only_move_constructor_implemented>);
static_assert(not is_move_constructible_v<only_move_assignment_operator_implemented>);
static_assert(not is_move_constructible_v<unit_test_is_constructible>);
static_assert(is_move_constructible_v<unit_test_derived_from_is_constructible>);
static_assert(is_move_constructible_v<trivially_destructible>);
static_assert(is_move_constructible_v<non_trivially_destructible>);
static_assert(is_move_constructible_v<exceptional_trivially_destructible>);
static_assert(is_move_constructible_v<exceptional_non_trivially_destructible>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_list_constructible)
struct unit_test_is_list_constructible_base {
    int a;
};
struct unit_test_is_list_constructible_derived : unit_test_is_list_constructible_base {
    int b;
};
struct unit_test_is_list_constructible_polymorphic_base {
    int a;
    virtual ~unit_test_is_list_constructible_polymorphic_base();
};
struct unit_test_is_list_constructible_polymorphic_derived_1 : unit_test_is_list_constructible_polymorphic_base {
    int b;
    virtual ~unit_test_is_list_constructible_polymorphic_derived_1() override;
};
struct unit_test_is_list_constructible_polymorphic_derived_2 : unit_test_is_list_constructible_polymorphic_base {
    int c;
};
struct unit_test_is_list_constructible_polymorphic_derived_3 : unit_test_is_list_constructible_polymorphic_derived_1, unit_test_is_list_constructible_polymorphic_derived_2 {
    int d;
};
struct unit_test_is_list_constructible_polymorphic_virtual_derived_1 : virtual unit_test_is_list_constructible_polymorphic_derived_1 {
    int b;
};
struct unit_test_is_list_constructible_polymorphic_virtual_derived_2 : virtual unit_test_is_list_constructible_polymorphic_derived_1 {
    int c;
};
struct unit_test_is_list_constructible_polymorphic_virtual_derived_final : unit_test_is_list_constructible_polymorphic_virtual_derived_1, unit_test_is_list_constructible_polymorphic_virtual_derived_2 {
    int d;
};
struct unit_test_is_list_constructible {
    unit_test_is_list_constructible() = default;
    unit_test_is_list_constructible(int);
    explicit unit_test_is_list_constructible(char);
    unit_test_is_list_constructible(double) = delete;
    explicit unit_test_is_list_constructible(void *) = delete;
    unit_test_is_list_constructible(int, char);
    explicit unit_test_is_list_constructible(long, long);
    unit_test_is_list_constructible(initializer_list<int *>);
    explicit unit_test_is_list_constructible(initializer_list<char *>);
    unit_test_is_list_constructible(initializer_list<double *>, int, char, long);
    template <typename T, typename U, typename V>
    unit_test_is_list_constructible(T, U &&, V **);
    unit_test_is_list_constructible(void *, void *, void **) = delete;
    operator unsigned short &();
    operator unsigned &() = delete;
    operator const unsigned long &() const &;
    explicit operator float &();
    explicit operator double &() = delete;
    explicit operator const long double &() const &;
    operator int **();
    operator int **&() = delete;
    operator int **&&();
};
static_assert(is_list_constructible_v<int, int>);
static_assert(is_list_constructible_v<int, int &>);
static_assert(is_list_constructible_v<int, int &&>);
static_assert(is_list_constructible_v<int, const int>);
static_assert(is_list_constructible_v<int, volatile int>);
static_assert(is_list_constructible_v<int, const volatile int>);
static_assert(is_list_constructible_v<int, const int &>);
static_assert(is_list_constructible_v<int, volatile int &>);
static_assert(is_list_constructible_v<int, const volatile int &>);
static_assert(is_list_constructible_v<int, const int &&>);
static_assert(is_list_constructible_v<int, volatile int &&>);
static_assert(is_list_constructible_v<int, const volatile int &&>);
static_assert(not is_list_constructible_v<int &, int>);
static_assert(is_list_constructible_v<int &, int &>);
static_assert(not is_list_constructible_v<int &, int &&>);
static_assert(not is_list_constructible_v<int &, const int>);
static_assert(not is_list_constructible_v<int &, volatile int>);
static_assert(not is_list_constructible_v<int &, const volatile int>);
static_assert(not is_list_constructible_v<int &, const int &>);
static_assert(not is_list_constructible_v<int &, volatile int &>);
static_assert(not is_list_constructible_v<int &, const volatile int &>);
static_assert(not is_list_constructible_v<int &, const int &&>);
static_assert(not is_list_constructible_v<int &, volatile int &&>);
static_assert(not is_list_constructible_v<int &, const volatile int &&>);
static_assert(is_list_constructible_v<int &&, int>);
static_assert(not is_list_constructible_v<int &&, int &>);
static_assert(is_list_constructible_v<int &&, int &&>);
static_assert(not is_list_constructible_v<int &&, const int>);
static_assert(not is_list_constructible_v<int &&, volatile int>);
static_assert(not is_list_constructible_v<int &&, const volatile int>);
static_assert(not is_list_constructible_v<int &&, const int &>);
static_assert(not is_list_constructible_v<int &&, volatile int &>);
static_assert(not is_list_constructible_v<int &&, const volatile int &>);
static_assert(not is_list_constructible_v<int &&, const int &&>);
static_assert(not is_list_constructible_v<int &&, volatile int &&>);
static_assert(not is_list_constructible_v<int &&, const volatile int &&>);
static_assert(is_list_constructible_v<const int, int>);
static_assert(is_list_constructible_v<const int, int &>);
static_assert(is_list_constructible_v<const int, int &&>);
static_assert(is_list_constructible_v<const int, const int>);
static_assert(is_list_constructible_v<const int, volatile int>);
static_assert(is_list_constructible_v<const int, const volatile int>);
static_assert(is_list_constructible_v<const int, const int &>);
static_assert(is_list_constructible_v<const int, volatile int &>);
static_assert(is_list_constructible_v<const int, const volatile int &>);
static_assert(is_list_constructible_v<const int, const int &&>);
static_assert(is_list_constructible_v<const int, volatile int &&>);
static_assert(is_list_constructible_v<const int, const volatile int &&>);
static_assert(is_list_constructible_v<volatile int, int>);
static_assert(is_list_constructible_v<volatile int, int &>);
static_assert(is_list_constructible_v<volatile int, int &&>);
static_assert(is_list_constructible_v<volatile int, const int>);
static_assert(is_list_constructible_v<volatile int, volatile int>);
static_assert(is_list_constructible_v<volatile int, const volatile int>);
static_assert(is_list_constructible_v<volatile int, const int &>);
static_assert(is_list_constructible_v<volatile int, volatile int &>);
static_assert(is_list_constructible_v<volatile int, const volatile int &>);
static_assert(is_list_constructible_v<volatile int, const int &&>);
static_assert(is_list_constructible_v<volatile int, volatile int &&>);
static_assert(is_list_constructible_v<volatile int, const volatile int &&>);
static_assert(is_list_constructible_v<const volatile int, int>);
static_assert(is_list_constructible_v<const volatile int, int &>);
static_assert(is_list_constructible_v<const volatile int, int &&>);
static_assert(is_list_constructible_v<const volatile int, const int>);
static_assert(is_list_constructible_v<const volatile int, volatile int>);
static_assert(is_list_constructible_v<const volatile int, const volatile int>);
static_assert(is_list_constructible_v<const volatile int, const int &>);
static_assert(is_list_constructible_v<const volatile int, volatile int &>);
static_assert(is_list_constructible_v<const volatile int, const volatile int &>);
static_assert(is_list_constructible_v<const volatile int, const int &&>);
static_assert(is_list_constructible_v<const volatile int, volatile int &&>);
static_assert(is_list_constructible_v<const volatile int, const volatile int &&>);
static_assert(is_list_constructible_v<const int &, int>);
static_assert(is_list_constructible_v<const int &, int &>);
static_assert(is_list_constructible_v<const int &, int &&>);
static_assert(is_list_constructible_v<const int &, const int>);
static_assert(not is_list_constructible_v<const int &, volatile int>);
static_assert(not is_list_constructible_v<const int &, const volatile int>);
static_assert(is_list_constructible_v<const int &, const int &>);
static_assert(not is_list_constructible_v<const int &, volatile int &>);
static_assert(not is_list_constructible_v<const int &, const volatile int &>);
static_assert(is_list_constructible_v<const int &, const int &&>);
static_assert(not is_list_constructible_v<const int &, volatile int &&>);
static_assert(not is_list_constructible_v<const int &, const volatile int &&>);
static_assert(not is_list_constructible_v<volatile int &, int>);
static_assert(is_list_constructible_v<volatile int &, int &>);
static_assert(not is_list_constructible_v<volatile int &, int &&>);
static_assert(not is_list_constructible_v<volatile int &, const int>);
static_assert(not is_list_constructible_v<volatile int &, volatile int>);
static_assert(not is_list_constructible_v<volatile int &, const volatile int>);
static_assert(not is_list_constructible_v<volatile int &, const int &>);
static_assert(is_list_constructible_v<volatile int &, volatile int &>);
static_assert(not is_list_constructible_v<volatile int &, const volatile int &>);
static_assert(not is_list_constructible_v<volatile int &, const int &&>);
static_assert(not is_list_constructible_v<volatile int &, volatile int &&>);
static_assert(not is_list_constructible_v<volatile int &, const volatile int &&>);
static_assert(not is_list_constructible_v<const volatile int &, int>);
static_assert(is_list_constructible_v<const volatile int &, int &>);
static_assert(not is_list_constructible_v<const volatile int &, int &&>);
static_assert(not is_list_constructible_v<const volatile int &, const int>);
static_assert(not is_list_constructible_v<const volatile int &, volatile int>);
static_assert(not is_list_constructible_v<const volatile int &, const volatile int>);
static_assert(is_list_constructible_v<const volatile int &, const int &>);
static_assert(is_list_constructible_v<const volatile int &, volatile int &>);
static_assert(is_list_constructible_v<const volatile int &, const volatile int &>);
static_assert(not is_list_constructible_v<const volatile int &, const int &&>);
static_assert(not is_list_constructible_v<const volatile int &, volatile int &&>);
static_assert(not is_list_constructible_v<const volatile int &, const volatile int &&>);
static_assert(is_list_constructible_v<const int &&, int>);
static_assert(not is_list_constructible_v<const int &&, int &>);
static_assert(is_list_constructible_v<const int &&, int &&>);
static_assert(is_list_constructible_v<const int &&, const int>);
static_assert(not is_list_constructible_v<const int &&, volatile int>);
static_assert(not is_list_constructible_v<const int &&, const volatile int>);
static_assert(not is_list_constructible_v<const int &&, const int &>);
static_assert(not is_list_constructible_v<const int &&, volatile int &>);
static_assert(not is_list_constructible_v<const int &&, const volatile int &>);
static_assert(is_list_constructible_v<const int &&, const int &&>);
static_assert(not is_list_constructible_v<const int &&, volatile int &&>);
static_assert(not is_list_constructible_v<const int &&, const volatile int &&>);
static_assert(is_list_constructible_v<volatile int &&, int>);
static_assert(not is_list_constructible_v<volatile int &&, int &>);
static_assert(is_list_constructible_v<volatile int &&, int &&>);
static_assert(not is_list_constructible_v<volatile int &&, const int>);
static_assert(is_list_constructible_v<volatile int &&, volatile int>);
static_assert(not is_list_constructible_v<volatile int &&, const volatile int>);
static_assert(not is_list_constructible_v<volatile int &&, const int &>);
static_assert(not is_list_constructible_v<volatile int &&, volatile int &>);
static_assert(not is_list_constructible_v<volatile int &&, const volatile int &>);
static_assert(not is_list_constructible_v<volatile int &&, const int &&>);
static_assert(is_list_constructible_v<volatile int &&, volatile int &&>);
static_assert(not is_list_constructible_v<volatile int &&, const volatile int &&>);
static_assert(is_list_constructible_v<const volatile int &&, int>);
static_assert(not is_list_constructible_v<const volatile int &&, int &>);
static_assert(is_list_constructible_v<const volatile int &&, int &&>);
static_assert(is_list_constructible_v<const volatile int &&, const int>);
static_assert(is_list_constructible_v<const volatile int &&, volatile int>);
static_assert(is_list_constructible_v<const volatile int &&, const volatile int>);
static_assert(not is_list_constructible_v<const volatile int &&, const int &>);
static_assert(not is_list_constructible_v<const volatile int &&, volatile int &>);
static_assert(not is_list_constructible_v<const volatile int &&, const volatile int &>);
static_assert(is_list_constructible_v<const volatile int &&, const int &&>);
static_assert(is_list_constructible_v<const volatile int &&, volatile int &&>);
static_assert(is_list_constructible_v<const volatile int &&, const volatile int &&>);
static_assert(is_list_constructible_v<int, bool>);
static_assert(is_list_constructible_v<int, short>);
static_assert(is_list_constructible_v<int, unsigned short>);
static_assert(is_list_constructible_v<int, char>);
static_assert(is_list_constructible_v<int, unsigned char>);
static_assert(is_list_constructible_v<int, signed char>);
static_assert(not is_list_constructible_v<int, unsigned>);
static_assert(not is_list_constructible_v<int, long>);
static_assert(not is_list_constructible_v<int, unsigned long>);
static_assert(not is_list_constructible_v<int, const unsigned>);
static_assert(not is_list_constructible_v<int, const long>);
static_assert(not is_list_constructible_v<int, const unsigned long>);
static_assert(is_list_constructible_v<int, char8_t>);
static_assert(is_list_constructible_v<int, char16_t>);
static_assert(not is_list_constructible_v<int, char32_t>);
static_assert(is_list_constructible_v<int, wchar_t>);
static_assert(not is_list_constructible_v<int, float>);
static_assert(is_list_constructible_v<double, float>);
static_assert(not is_list_constructible_v<double, int>);
static_assert(not is_list_constructible_v<double, unsigned>);
static_assert(not is_list_constructible_v<double, long double>);
/* inconsistent cases */
//static_assert(is_list_constructible_v<double, const int>);
//static_assert(is_list_constructible_v<double, const unsigned>);
static_assert(is_list_constructible_v<int *, int []>);
static_assert(is_list_constructible_v<const int *, int []>);
static_assert(is_list_constructible_v<int *const, int []>);
static_assert(is_list_constructible_v<const int *const, int []>);
static_assert(is_list_constructible_v<int *, int [42]>);
static_assert(is_list_constructible_v<const int *, int [42]>);
static_assert(is_list_constructible_v<int *const, int [42]>);
static_assert(is_list_constructible_v<const int *const, int [42]>);
static_assert(not is_list_constructible_v<int [], initializer_list<int>>);
static_assert(not is_list_constructible_v<int [42], initializer_list<int>>);
static_assert(not is_list_constructible_v<int *, initializer_list<int>>);
static_assert(not is_list_constructible_v<int (&)[], int []>);
static_assert(is_list_constructible_v<int (&&)[], int []>);
static_assert(not is_list_constructible_v<int (&)[42], int [42]>);
static_assert(is_list_constructible_v<int (&&)[42], int [42]>);
static_assert(not is_list_constructible_v<int (&)[], initializer_list<int>>);
static_assert(not is_list_constructible_v<int (&)[42], initializer_list<int>>);
static_assert(is_list_constructible_v<int *, int (&)[]>);
static_assert(is_list_constructible_v<int *, int (&&)[]>);
static_assert(is_list_constructible_v<int *, int (&)[42]>);
static_assert(is_list_constructible_v<int *, int (&&)[42]>);
static_assert(is_list_constructible_v<const int *, int (&)[]>);
static_assert(is_list_constructible_v<const int *, int (&&)[]>);
static_assert(is_list_constructible_v<const int *, int (&)[42]>);
static_assert(is_list_constructible_v<const int *, int (&&)[42]>);
static_assert(is_list_constructible_v<int *const, int (&)[]>);
static_assert(is_list_constructible_v<int *const, int (&&)[]>);
static_assert(is_list_constructible_v<int *const, int (&)[42]>);
static_assert(is_list_constructible_v<int *const, int (&&)[42]>);
static_assert(is_list_constructible_v<const int *const, int (&)[]>);
static_assert(is_list_constructible_v<const int *const, int (&&)[]>);
static_assert(is_list_constructible_v<const int *const, int (&)[42]>);
static_assert(is_list_constructible_v<const int *const, int (&&)[42]>);
static_assert(is_list_constructible_v<void (*)(), void ()>);
static_assert(not is_list_constructible_v<void (), void ()>);
static_assert(is_list_constructible_v<void (&)(), void ()>);
static_assert(is_list_constructible_v<void (&&)(), void ()>);
static_assert(is_list_constructible_v<void (&)(), void (&&)()>);
static_assert(is_list_constructible_v<void (&&)(), void (&)()>);
static_assert(is_list_constructible_v<void (*)(), void (&)()>);
static_assert(is_list_constructible_v<void (*)(), void (&&)()>);
static_assert(is_list_constructible_v<void (*const)(), void ()>);
static_assert(is_list_constructible_v<void (*const)(), void (&)()>);
static_assert(is_list_constructible_v<void (*const)(), void (&&)()>);
static_assert(not is_list_constructible_v<int, C>);
static_assert(is_list_constructible_v<int, D>);
static_assert(is_list_constructible_v<C, int>);
static_assert(is_list_constructible_v<D, int>);
static_assert(is_list_constructible_v<D, short>);
static_assert(is_list_constructible_v<D, bool>);
static_assert(not is_list_constructible_v<D, unsigned>);
static_assert(not is_list_constructible_v<D, unit_test_is_list_constructible>);
static_assert(is_list_constructible_v<unit_test_is_list_constructible_base, unit_test_is_list_constructible_derived>);
static_assert(is_list_constructible_v<unit_test_is_list_constructible_derived, unit_test_is_list_constructible_base>);
static_assert(is_list_constructible_v<unit_test_is_list_constructible_base *, unit_test_is_list_constructible_derived *>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_derived *, unit_test_is_list_constructible_base *>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_base *, const unit_test_is_list_constructible_derived *>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_derived *, const unit_test_is_list_constructible_base *>);
static_assert(is_list_constructible_v<unit_test_is_list_constructible_base *, unit_test_is_list_constructible_derived *const>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_derived *, unit_test_is_list_constructible_base *const>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_base *, const unit_test_is_list_constructible_derived *const>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_derived *, const unit_test_is_list_constructible_base *const>);
static_assert(is_list_constructible_v<const unit_test_is_list_constructible_base *, unit_test_is_list_constructible_derived *>);
static_assert(not is_list_constructible_v<const unit_test_is_list_constructible_derived *, unit_test_is_list_constructible_base *>);
static_assert(is_list_constructible_v<const unit_test_is_list_constructible_base *, const unit_test_is_list_constructible_derived *>);
static_assert(not is_list_constructible_v<const unit_test_is_list_constructible_derived *, const unit_test_is_list_constructible_base *>);
static_assert(is_list_constructible_v<const unit_test_is_list_constructible_base *, unit_test_is_list_constructible_derived *const>);
static_assert(not is_list_constructible_v<const unit_test_is_list_constructible_derived *, unit_test_is_list_constructible_base *const>);
static_assert(is_list_constructible_v<const unit_test_is_list_constructible_base *, const unit_test_is_list_constructible_derived *const>);
static_assert(not is_list_constructible_v<const unit_test_is_list_constructible_derived *, const unit_test_is_list_constructible_base *const>);
static_assert(is_list_constructible_v<unit_test_is_list_constructible_base *const, unit_test_is_list_constructible_derived *>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_derived *const, unit_test_is_list_constructible_base *>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_base *const, const unit_test_is_list_constructible_derived *>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_derived *const, const unit_test_is_list_constructible_base *>);
static_assert(is_list_constructible_v<unit_test_is_list_constructible_base *const, unit_test_is_list_constructible_derived *const>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_derived *const, unit_test_is_list_constructible_base *const>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_base *const, const unit_test_is_list_constructible_derived *const>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_derived *const, const unit_test_is_list_constructible_base *const>);
static_assert(is_list_constructible_v<const unit_test_is_list_constructible_base *const, unit_test_is_list_constructible_derived *>);
static_assert(not is_list_constructible_v<const unit_test_is_list_constructible_derived *const, unit_test_is_list_constructible_base *>);
static_assert(is_list_constructible_v<const unit_test_is_list_constructible_base *const, const unit_test_is_list_constructible_derived *>);
static_assert(not is_list_constructible_v<const unit_test_is_list_constructible_derived *const, const unit_test_is_list_constructible_base *>);
static_assert(is_list_constructible_v<const unit_test_is_list_constructible_base *const, unit_test_is_list_constructible_derived *const>);
static_assert(not is_list_constructible_v<const unit_test_is_list_constructible_derived *const, unit_test_is_list_constructible_base *const>);
static_assert(is_list_constructible_v<const unit_test_is_list_constructible_base *const, const unit_test_is_list_constructible_derived *const>);
static_assert(not is_list_constructible_v<const unit_test_is_list_constructible_derived *const, const unit_test_is_list_constructible_base *const>);
static_assert(is_list_constructible_v<unit_test_is_list_constructible_base &, unit_test_is_list_constructible_derived &>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_base &, unit_test_is_list_constructible_derived &&>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_derived &, unit_test_is_list_constructible_base &>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_derived &, unit_test_is_list_constructible_base &&>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_base &, const unit_test_is_list_constructible_derived &>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_base &, const unit_test_is_list_constructible_derived &&>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_derived &, const unit_test_is_list_constructible_base &>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_derived &, const unit_test_is_list_constructible_base &&>);
static_assert(is_list_constructible_v<const unit_test_is_list_constructible_base &, unit_test_is_list_constructible_derived &>);
static_assert(is_list_constructible_v<const unit_test_is_list_constructible_base &, unit_test_is_list_constructible_derived &&>);
static_assert(is_list_constructible_v<const unit_test_is_list_constructible_derived &, unit_test_is_list_constructible_base &>);
static_assert(is_list_constructible_v<const unit_test_is_list_constructible_derived &, unit_test_is_list_constructible_base &&>);
static_assert(is_list_constructible_v<const unit_test_is_list_constructible_base &, const unit_test_is_list_constructible_derived &>);
static_assert(is_list_constructible_v<const unit_test_is_list_constructible_base &, const unit_test_is_list_constructible_derived &&>);
static_assert(is_list_constructible_v<const unit_test_is_list_constructible_derived &, const unit_test_is_list_constructible_base &>);
static_assert(is_list_constructible_v<const unit_test_is_list_constructible_derived &, const unit_test_is_list_constructible_base &&>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_base &&, unit_test_is_list_constructible_derived &>);
static_assert(is_list_constructible_v<unit_test_is_list_constructible_base &&, unit_test_is_list_constructible_derived &&>);
static_assert(is_list_constructible_v<unit_test_is_list_constructible_derived &&, unit_test_is_list_constructible_base &>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_derived &, unit_test_is_list_constructible_base &&>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_base &&, const unit_test_is_list_constructible_derived &>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_base &&, const unit_test_is_list_constructible_derived &&>);
static_assert(is_list_constructible_v<unit_test_is_list_constructible_derived &&, const unit_test_is_list_constructible_base &>);
static_assert(is_list_constructible_v<unit_test_is_list_constructible_derived &&, const unit_test_is_list_constructible_base &&>);
static_assert(not is_list_constructible_v<const unit_test_is_list_constructible_base &&, unit_test_is_list_constructible_derived &>);
static_assert(is_list_constructible_v<const unit_test_is_list_constructible_base &&, unit_test_is_list_constructible_derived &&>);
static_assert(is_list_constructible_v<const unit_test_is_list_constructible_derived &&, unit_test_is_list_constructible_base &>);
static_assert(is_list_constructible_v<const unit_test_is_list_constructible_derived &&, unit_test_is_list_constructible_base &&>);
static_assert(not is_list_constructible_v<const unit_test_is_list_constructible_base &&, const unit_test_is_list_constructible_derived &>);
static_assert(is_list_constructible_v<const unit_test_is_list_constructible_base &&, const unit_test_is_list_constructible_derived &&>);
static_assert(is_list_constructible_v<const unit_test_is_list_constructible_derived &&, const unit_test_is_list_constructible_base &>);
static_assert(is_list_constructible_v<const unit_test_is_list_constructible_derived &&, const unit_test_is_list_constructible_base &&>);
static_assert(is_list_constructible_v<unit_test_is_list_constructible_polymorphic_base, unit_test_is_list_constructible_polymorphic_derived_1>);
static_assert(is_list_constructible_v<unit_test_is_list_constructible_polymorphic_base, unit_test_is_list_constructible_polymorphic_derived_2>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_polymorphic_base, unit_test_is_list_constructible_polymorphic_derived_3>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_polymorphic_derived_1, unit_test_is_list_constructible_polymorphic_base>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_polymorphic_derived_2, unit_test_is_list_constructible_polymorphic_base>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_polymorphic_derived_3, unit_test_is_list_constructible_polymorphic_base>);
static_assert(is_list_constructible_v<unit_test_is_list_constructible_polymorphic_base *, unit_test_is_list_constructible_polymorphic_derived_1 *>);
static_assert(is_list_constructible_v<unit_test_is_list_constructible_polymorphic_base *, unit_test_is_list_constructible_polymorphic_derived_2 *>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_polymorphic_base *, unit_test_is_list_constructible_polymorphic_derived_3 *>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_polymorphic_derived_1 *, unit_test_is_list_constructible_polymorphic_base *>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_polymorphic_derived_2 *, unit_test_is_list_constructible_polymorphic_base *>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_polymorphic_derived_3 *, unit_test_is_list_constructible_polymorphic_base *>);
static_assert(is_list_constructible_v<unit_test_is_list_constructible_polymorphic_base &, unit_test_is_list_constructible_polymorphic_derived_1 &>);
static_assert(is_list_constructible_v<unit_test_is_list_constructible_polymorphic_base &, unit_test_is_list_constructible_polymorphic_derived_2 &>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_polymorphic_base &, unit_test_is_list_constructible_polymorphic_derived_3 &>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_polymorphic_derived_1 &, unit_test_is_list_constructible_polymorphic_base &>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_polymorphic_derived_2 &, unit_test_is_list_constructible_polymorphic_base &>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible_polymorphic_derived_3 &, unit_test_is_list_constructible_polymorphic_base &>);
static_assert(is_list_constructible_v<unit_test_is_list_constructible>);
static_assert(is_list_constructible_v<unit_test_is_list_constructible, int>);
static_assert(is_list_constructible_v<unit_test_is_list_constructible, char>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible, double>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible, void *>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible, long>);
static_assert(is_list_constructible_v<unit_test_is_list_constructible, int, char>);
static_assert(is_list_constructible_v<unit_test_is_list_constructible, long, long>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible, unsigned long, long>);
static_assert(is_list_constructible_v<unit_test_is_list_constructible, int *>);
static_assert(is_list_constructible_v<unit_test_is_list_constructible, int *, int *>);
static_assert(is_list_constructible_v<unit_test_is_list_constructible, int *, int *, int *const, int *&, int *&&>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible, double *, double *, double *, double *, int, char, long>);
static_assert(is_list_constructible_v<unit_test_is_list_constructible, int *, char *, long **>);
static_assert(not is_list_constructible_v<unit_test_is_list_constructible, int, char, void ()>);
static_assert(is_list_constructible_v<unsigned short, unit_test_is_list_constructible>);
static_assert(not is_list_constructible_v<unsigned short &, unit_test_is_list_constructible>);
static_assert(not is_list_constructible_v<unsigned, unit_test_is_list_constructible>);
static_assert(not is_list_constructible_v<unsigned long, unit_test_is_list_constructible>);
static_assert(not is_list_constructible_v<unsigned long, unit_test_is_list_constructible &>);
static_assert(is_list_constructible_v<unsigned long, const unit_test_is_list_constructible &>);
static_assert(is_list_constructible_v<float, unit_test_is_list_constructible>);
static_assert(not is_list_constructible_v<double, unit_test_is_list_constructible>);
static_assert(is_list_constructible_v<long double, const unit_test_is_list_constructible &>);
static_assert(not is_list_constructible_v<int **, unit_test_is_list_constructible>);        // prefer to operator int **&()
static_assert(not is_list_constructible_v<int **&&, unit_test_is_list_constructible>);      // still prefer to operator int **&()
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_assignable)
struct unit_test_is_assignable {
    void operator=(int *);
    unit_test_is_assignable &operator=(int);
    auto operator=(char) -> void (*)();
    template <std::size_t N>
    void operator=(unit_test_is_assignable (&)[N]);
    int operator=(double);
    void operator=(double *) &;
    void operator=(double **) const &;
    void operator=(double ***) volatile &;
    void operator=(double ****) const volatile &;
    void operator=(double *****) &&;
    void operator=(double ******) const &&;
    void operator=(double *******) volatile &&;
    void operator=(double ********) const volatile &&;
};
static_assert(not is_assignable_v<int>);
static_assert(not is_assignable_v<const int>);
static_assert(not is_assignable_v<volatile int>);
static_assert(not is_assignable_v<const volatile int>);
static_assert(not is_assignable_v<int *>);
static_assert(not is_assignable_v<const int *>);
static_assert(not is_assignable_v<volatile int *>);
static_assert(not is_assignable_v<int *const>);
static_assert(not is_assignable_v<int *volatile>);
static_assert(is_assignable_v<int &>);
static_assert(not is_assignable_v<const int &>);
static_assert(is_assignable_v<volatile int &>);
static_assert(not is_assignable_v<int &&>);
static_assert(not is_assignable_v<void>);
static_assert(not is_assignable_v<int []>);
static_assert(not is_assignable_v<int [42]>);
static_assert(not is_assignable_v<int (&)[42]>);
static_assert(not is_assignable_v<int (&&)[]>);
static_assert(not is_assignable_v<void ()>);
static_assert(not is_assignable_v<void (*)()>);
static_assert(not is_assignable_v<void (*const)()>);
static_assert(not is_assignable_v<decltype(nullptr)>);
static_assert(not is_assignable_v<void (&)()>);
static_assert(not is_assignable_v<void (&&)()>);
static_assert(is_assignable_v<A>);
//static_assert(is_assignable_v<B>);     // undefined behavior
static_assert(not is_assignable_v<C>);
static_assert(not is_assignable_v<D>);
//static_assert(is_assignable_v<E>);     // undefined behavior
static_assert(is_assignable_v<trivial_stateless>);
static_assert(is_assignable_v<trivial>);
static_assert(is_assignable_v<non_trivial_1>);
static_assert(is_assignable_v<non_trivial_2>);
static_assert(is_assignable_v<trivial_with_deleted_destructor>);
static_assert(not is_assignable_v<trivially_copy_constructible>);
static_assert(not is_assignable_v<trivially_copy_constructible_non_destructible>);
static_assert(not is_assignable_v<trivially_move_constructible>);
static_assert(not is_assignable_v<trivially_move_constructible_non_destructible>);
static_assert(not is_assignable_v<trivially_copy_assignable>);
static_assert(not is_assignable_v<trivially_copy_assignable_non_destructible>);
static_assert(is_assignable_v<trivially_move_assignable>);
static_assert(is_assignable_v<trivially_move_assignable_non_destructible>);
static_assert(is_assignable_v<trivially_default_constructible_simulator>);
static_assert(is_assignable_v<trivially_constructible_simulator>);
static_assert(is_assignable_v<non_trivially_constructible>);
static_assert(is_assignable_v<only_copy_constructor_implemented>);
static_assert(not is_assignable_v<only_copy_assignment_operator_implemented>);
static_assert(is_assignable_v<only_move_constructor_implemented>);
static_assert(is_assignable_v<only_move_assignment_operator_implemented>);
static_assert(is_assignable_v<unit_test_is_constructible>);
static_assert(is_assignable_v<unit_test_derived_from_is_constructible>);
static_assert(is_assignable_v<trivially_destructible>);
static_assert(is_assignable_v<non_trivially_destructible>);
static_assert(is_assignable_v<exceptional_trivially_destructible>);
static_assert(is_assignable_v<exceptional_non_trivially_destructible>);
static_assert(is_assignable_v<unit_test_is_assignable, int>);
static_assert(not is_assignable_v<unit_test_is_assignable, void *>);
static_assert(is_assignable_v<unit_test_is_assignable, const int &>);
static_assert(is_assignable_v<unit_test_is_assignable, char>);
static_assert(not is_assignable_v<unit_test_is_assignable, unit_test_is_assignable []>);
static_assert(not is_assignable_v<unit_test_is_assignable, unit_test_is_assignable [42]>);
static_assert(not is_assignable_v<unit_test_is_assignable, unit_test_is_assignable (&)[]>);
static_assert(is_assignable_v<unit_test_is_assignable, unit_test_is_assignable (&)[42]>);
static_assert(is_assignable_v<unit_test_is_assignable, unit_test_is_assignable>);
static_assert(is_assignable_v<unit_test_is_assignable, const unit_test_is_assignable>);
static_assert(not is_assignable_v<unit_test_is_assignable, volatile unit_test_is_assignable>);
static_assert(not is_assignable_v<unit_test_is_assignable, const volatile unit_test_is_assignable>);
static_assert(is_assignable_v<unit_test_is_assignable, unit_test_is_assignable &>);
static_assert(is_assignable_v<unit_test_is_assignable, unit_test_is_assignable &&>);
static_assert(is_assignable_v<unit_test_is_assignable, const unit_test_is_assignable &>);
static_assert(is_assignable_v<unit_test_is_assignable, const unit_test_is_assignable &&>);
static_assert(not is_assignable_v<unit_test_is_assignable, volatile unit_test_is_assignable &>);
static_assert(not is_assignable_v<unit_test_is_assignable, volatile unit_test_is_assignable &&>);
static_assert(not is_assignable_v<unit_test_is_assignable, double *>);
static_assert(is_assignable_v<unit_test_is_assignable &, double *>);
static_assert(not is_assignable_v<const unit_test_is_assignable &, double *>);
static_assert(not is_assignable_v<volatile unit_test_is_assignable &, double *>);
static_assert(not is_assignable_v<const volatile unit_test_is_assignable &, double *>);
static_assert(not is_assignable_v<unit_test_is_assignable &&, double *>);
static_assert(not is_assignable_v<const unit_test_is_assignable &&, double *>);
static_assert(not is_assignable_v<volatile unit_test_is_assignable &&, double *>);
static_assert(not is_assignable_v<const volatile unit_test_is_assignable &&, double *>);
static_assert(is_assignable_v<unit_test_is_assignable, double **>);
static_assert(is_assignable_v<unit_test_is_assignable &, double **>);
static_assert(is_assignable_v<const unit_test_is_assignable &, double **>);
static_assert(not is_assignable_v<volatile unit_test_is_assignable &, double **>);
static_assert(not is_assignable_v<const volatile unit_test_is_assignable &, double **>);
static_assert(is_assignable_v<unit_test_is_assignable &&, double **>);
static_assert(is_assignable_v<const unit_test_is_assignable &&, double **>);
static_assert(not is_assignable_v<volatile unit_test_is_assignable &&, double **>);
static_assert(not is_assignable_v<const volatile unit_test_is_assignable &&, double **>);
static_assert(not is_assignable_v<unit_test_is_assignable, double ***>);
static_assert(is_assignable_v<unit_test_is_assignable &, double ***>);
static_assert(not is_assignable_v<const unit_test_is_assignable &, double ***>);
static_assert(is_assignable_v<volatile unit_test_is_assignable &, double ***>);
static_assert(not is_assignable_v<const volatile unit_test_is_assignable &, double ***>);
static_assert(not is_assignable_v<unit_test_is_assignable &&, double ***>);
static_assert(not is_assignable_v<const unit_test_is_assignable &&, double ***>);
static_assert(not is_assignable_v<volatile unit_test_is_assignable &&, double ***>);
static_assert(not is_assignable_v<const volatile unit_test_is_assignable &&, double ***>);
static_assert(not is_assignable_v<unit_test_is_assignable, double ****>);
static_assert(is_assignable_v<unit_test_is_assignable &, double ****>);
static_assert(is_assignable_v<const unit_test_is_assignable &, double ****>);
static_assert(is_assignable_v<volatile unit_test_is_assignable &, double ****>);
static_assert(is_assignable_v<const volatile unit_test_is_assignable &, double ****>);
static_assert(not is_assignable_v<unit_test_is_assignable &&, double ****>);
static_assert(not is_assignable_v<const unit_test_is_assignable &&, double ****>);
static_assert(not is_assignable_v<volatile unit_test_is_assignable &&, double ****>);
static_assert(not is_assignable_v<const volatile unit_test_is_assignable &&, double ****>);
static_assert(is_assignable_v<unit_test_is_assignable, double *****>);
static_assert(not is_assignable_v<unit_test_is_assignable &, double *****>);
static_assert(not is_assignable_v<const unit_test_is_assignable &, double *****>);
static_assert(not is_assignable_v<volatile unit_test_is_assignable &, double *****>);
static_assert(not is_assignable_v<const volatile unit_test_is_assignable &, double *****>);
static_assert(is_assignable_v<unit_test_is_assignable &&, double *****>);
static_assert(not is_assignable_v<const unit_test_is_assignable &&, double *****>);
static_assert(not is_assignable_v<volatile unit_test_is_assignable &&, double *****>);
static_assert(not is_assignable_v<const volatile unit_test_is_assignable &&, double *****>);
static_assert(is_assignable_v<unit_test_is_assignable, double ******>);
static_assert(not is_assignable_v<unit_test_is_assignable &, double ******>);
static_assert(not is_assignable_v<const unit_test_is_assignable &, double ******>);
static_assert(not is_assignable_v<volatile unit_test_is_assignable &, double ******>);
static_assert(not is_assignable_v<const volatile unit_test_is_assignable &, double ******>);
static_assert(is_assignable_v<unit_test_is_assignable &&, double ******>);
static_assert(is_assignable_v<const unit_test_is_assignable &&, double ******>);
static_assert(not is_assignable_v<volatile unit_test_is_assignable &&, double ******>);
static_assert(not is_assignable_v<const volatile unit_test_is_assignable &&, double ******>);
static_assert(is_assignable_v<unit_test_is_assignable, double *******>);
static_assert(not is_assignable_v<unit_test_is_assignable &, double *******>);
static_assert(not is_assignable_v<const unit_test_is_assignable &, double *******>);
static_assert(not is_assignable_v<volatile unit_test_is_assignable &, double *******>);
static_assert(not is_assignable_v<const volatile unit_test_is_assignable &, double *******>);
static_assert(is_assignable_v<unit_test_is_assignable &&, double *******>);
static_assert(not is_assignable_v<const unit_test_is_assignable &&, double *******>);
static_assert(is_assignable_v<volatile unit_test_is_assignable &&, double *******>);
static_assert(not is_assignable_v<const volatile unit_test_is_assignable &&, double *******>);
static_assert(is_assignable_v<unit_test_is_assignable &&, double ******>);
static_assert(is_assignable_v<const unit_test_is_assignable &&, double ******>);
static_assert(not is_assignable_v<volatile unit_test_is_assignable &&, double ******>);
static_assert(not is_assignable_v<const volatile unit_test_is_assignable &&, double ******>);
static_assert(is_assignable_v<unit_test_is_assignable, double ********>);
static_assert(not is_assignable_v<unit_test_is_assignable &, double ********>);
static_assert(not is_assignable_v<const unit_test_is_assignable &, double ********>);
static_assert(not is_assignable_v<volatile unit_test_is_assignable &, double ********>);
static_assert(not is_assignable_v<const volatile unit_test_is_assignable &, double ********>);
static_assert(is_assignable_v<unit_test_is_assignable &&, double ********>);
static_assert(is_assignable_v<const unit_test_is_assignable &&, double ********>);
static_assert(is_assignable_v<volatile unit_test_is_assignable &&, double ********>);
static_assert(is_assignable_v<const volatile unit_test_is_assignable &&, double ********>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_copy_assignable)
static_assert(is_copy_assignable_v<int>);
static_assert(not is_copy_assignable_v<const int>);
static_assert(is_copy_assignable_v<volatile int>);
static_assert(not is_copy_assignable_v<const volatile int>);
static_assert(is_copy_assignable_v<int *>);
static_assert(is_copy_assignable_v<const int *>);
static_assert(is_copy_assignable_v<volatile int *>);
static_assert(not is_copy_assignable_v<int *const>);
static_assert(is_copy_assignable_v<int *volatile>);
static_assert(is_copy_assignable_v<int &>);
static_assert(not is_copy_assignable_v<const int &>);
static_assert(is_copy_assignable_v<volatile int &>);
static_assert(is_copy_assignable_v<int &&>);
static_assert(not is_copy_assignable_v<void>);
static_assert(not is_copy_assignable_v<int []>);
static_assert(not is_copy_assignable_v<int [42]>);
static_assert(not is_copy_assignable_v<int (&)[42]>);
static_assert(not is_copy_assignable_v<int (&&)[]>);
static_assert(not is_copy_assignable_v<void ()>);
static_assert(is_copy_assignable_v<void (*)()>);
static_assert(not is_copy_assignable_v<void (*const)()>);
static_assert(is_copy_assignable_v<decltype(nullptr)>);
static_assert(not is_copy_assignable_v<void (&)()>);
static_assert(not is_copy_assignable_v<void (&&)()>);
static_assert(is_copy_assignable_v<A>);
//static_assert(is_copy_assignable_v<B>);     // undefined behavior
static_assert(is_copy_assignable_v<C>);
static_assert(is_copy_assignable_v<D>);
//static_assert(is_copy_assignable_v<E>);     // undefined behavior
static_assert(is_copy_assignable_v<trivial_stateless>);
static_assert(is_copy_assignable_v<trivial>);
static_assert(is_copy_assignable_v<non_trivial_1>);
static_assert(is_copy_assignable_v<non_trivial_2>);
static_assert(is_copy_assignable_v<trivial_with_deleted_destructor>);
static_assert(not is_copy_assignable_v<trivially_copy_constructible>);
static_assert(not is_copy_assignable_v<trivially_copy_constructible_non_destructible>);
static_assert(not is_copy_assignable_v<trivially_move_constructible>);
static_assert(not is_copy_assignable_v<trivially_move_constructible_non_destructible>);
static_assert(is_copy_assignable_v<trivially_copy_assignable>);
static_assert(is_copy_assignable_v<trivially_copy_assignable_non_destructible>);
static_assert(not is_copy_assignable_v<trivially_move_assignable>);
static_assert(not is_copy_assignable_v<trivially_move_assignable_non_destructible>);
static_assert(is_copy_assignable_v<trivially_default_constructible_simulator>);
static_assert(is_copy_assignable_v<trivially_constructible_simulator>);
static_assert(is_copy_assignable_v<non_trivially_constructible>);
static_assert(is_copy_assignable_v<only_copy_constructor_implemented>);
static_assert(not is_copy_assignable_v<only_copy_assignment_operator_implemented>);
static_assert(is_copy_assignable_v<only_move_constructor_implemented>);
static_assert(not is_copy_assignable_v<only_move_assignment_operator_implemented>);
static_assert(not is_copy_assignable_v<unit_test_is_constructible>);
static_assert(not is_copy_assignable_v<unit_test_derived_from_is_constructible>);
static_assert(is_copy_assignable_v<trivially_destructible>);
static_assert(is_copy_assignable_v<non_trivially_destructible>);
static_assert(is_copy_assignable_v<exceptional_trivially_destructible>);
static_assert(is_copy_assignable_v<exceptional_non_trivially_destructible>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_move_assignable)
static_assert(is_move_assignable_v<int>);
static_assert(not is_move_assignable_v<const int>);
static_assert(is_move_assignable_v<volatile int>);
static_assert(not is_move_assignable_v<const volatile int>);
static_assert(is_move_assignable_v<int *>);
static_assert(is_move_assignable_v<const int *>);
static_assert(is_move_assignable_v<volatile int *>);
static_assert(not is_move_assignable_v<int *const>);
static_assert(is_move_assignable_v<int *volatile>);
static_assert(is_move_assignable_v<int &>);
static_assert(not is_move_assignable_v<const int &>);
static_assert(is_move_assignable_v<volatile int &>);
static_assert(is_move_assignable_v<int &&>);
static_assert(not is_move_assignable_v<void>);
static_assert(not is_move_assignable_v<int []>);
static_assert(not is_move_assignable_v<int [42]>);
static_assert(not is_move_assignable_v<int (&)[42]>);
static_assert(not is_move_assignable_v<int (&&)[]>);
static_assert(not is_move_assignable_v<void ()>);
static_assert(is_move_assignable_v<void (*)()>);
static_assert(not is_move_assignable_v<void (*const)()>);
static_assert(is_move_assignable_v<decltype(nullptr)>);
static_assert(not is_move_assignable_v<void (&)()>);
static_assert(not is_move_assignable_v<void (&&)()>);
static_assert(is_move_assignable_v<A>);
//static_assert(is_move_assignable_v<B>);     // undefined behavior
static_assert(is_move_assignable_v<C>);
static_assert(is_move_assignable_v<D>);
//static_assert(is_move_assignable_v<E>);     // undefined behavior
static_assert(is_move_assignable_v<trivial_stateless>);
static_assert(is_move_assignable_v<trivial>);
static_assert(is_move_assignable_v<non_trivial_1>);
static_assert(is_move_assignable_v<non_trivial_2>);
static_assert(is_move_assignable_v<trivial_with_deleted_destructor>);
static_assert(not is_move_assignable_v<trivially_copy_constructible>);
static_assert(not is_move_assignable_v<trivially_copy_constructible_non_destructible>);
static_assert(not is_move_assignable_v<trivially_move_constructible>);
static_assert(not is_move_assignable_v<trivially_move_constructible_non_destructible>);
static_assert(not is_move_assignable_v<trivially_copy_assignable>);
static_assert(not is_move_assignable_v<trivially_copy_assignable_non_destructible>);
static_assert(is_move_assignable_v<trivially_move_assignable>);
static_assert(is_move_assignable_v<trivially_move_assignable_non_destructible>);
static_assert(is_move_assignable_v<trivially_default_constructible_simulator>);
static_assert(is_move_assignable_v<trivially_constructible_simulator>);
static_assert(is_move_assignable_v<non_trivially_constructible>);
static_assert(is_move_assignable_v<only_copy_constructor_implemented>);
static_assert(not is_move_assignable_v<only_copy_assignment_operator_implemented>);
static_assert(is_move_assignable_v<only_move_constructor_implemented>);
static_assert(is_move_assignable_v<only_move_assignment_operator_implemented>);
static_assert(is_move_assignable_v<unit_test_is_constructible>);
static_assert(is_move_assignable_v<unit_test_derived_from_is_constructible>);
static_assert(is_move_assignable_v<trivially_destructible>);
static_assert(is_move_assignable_v<non_trivially_destructible>);
static_assert(is_move_assignable_v<exceptional_trivially_destructible>);
static_assert(is_move_assignable_v<exceptional_non_trivially_destructible>);
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(unit test for ds::is_destructible)
static_assert(is_destructible_v<int>);
static_assert(is_destructible_v<const int>);
static_assert(is_destructible_v<volatile int>);
static_assert(is_destructible_v<const volatile int>);
static_assert(is_destructible_v<int *>);
static_assert(is_destructible_v<const int *>);
static_assert(is_destructible_v<volatile int *>);
static_assert(is_destructible_v<int *const>);
static_assert(is_destructible_v<int *volatile>);
static_assert(is_destructible_v<int &>);
static_assert(is_destructible_v<const int &>);
static_assert(is_destructible_v<volatile int &>);
static_assert(is_destructible_v<int &&>);
static_assert(not is_destructible_v<void>);
static_assert(not is_destructible_v<int []>);
static_assert(is_destructible_v<int [42]>);
static_assert(is_destructible_v<int (&)[42]>);
static_assert(is_destructible_v<int (&&)[]>);
static_assert(not is_destructible_v<void ()>);
static_assert(is_destructible_v<void (*)()>);
static_assert(is_destructible_v<void (*const)()>);
static_assert(is_destructible_v<decltype(nullptr)>);
static_assert(is_destructible_v<void (&)()>);
static_assert(is_destructible_v<void (&&)()>);
static_assert(is_destructible_v<A>);
//static_assert(is_destructible_v<B>);     // undefined behavior
static_assert(is_destructible_v<C>);
static_assert(is_destructible_v<D>);
//static_assert(is_destructible_v<E>);     // undefined behavior
static_assert(is_destructible_v<trivial_stateless>);
static_assert(is_destructible_v<trivial>);
static_assert(is_destructible_v<non_trivial_1>);
static_assert(is_destructible_v<non_trivial_2>);
static_assert(not is_destructible_v<trivial_with_deleted_destructor>);
static_assert(is_destructible_v<trivially_copy_constructible>);
static_assert(not is_destructible_v<trivially_copy_constructible_non_destructible>);
static_assert(is_destructible_v<trivially_move_constructible>);
static_assert(not is_destructible_v<trivially_move_constructible_non_destructible>);
static_assert(is_destructible_v<trivially_copy_assignable>);
static_assert(not is_destructible_v<trivially_copy_assignable_non_destructible>);
static_assert(is_destructible_v<trivially_move_assignable>);
static_assert(not is_destructible_v<trivially_move_assignable_non_destructible>);
static_assert(is_destructible_v<trivially_default_constructible_simulator>);
static_assert(is_destructible_v<trivially_constructible_simulator>);
static_assert(is_destructible_v<non_trivially_constructible>);
static_assert(is_destructible_v<only_copy_constructor_implemented>);
static_assert(is_destructible_v<only_copy_assignment_operator_implemented>);
static_assert(is_destructible_v<only_move_constructor_implemented>);
static_assert(is_destructible_v<only_move_assignment_operator_implemented>);
static_assert(is_destructible_v<unit_test_is_constructible>);
static_assert(is_destructible_v<unit_test_derived_from_is_constructible>);
static_assert(is_destructible_v<trivially_destructible>);
static_assert(is_destructible_v<non_trivially_destructible>);
static_assert(is_destructible_v<exceptional_trivially_destructible>);
static_assert(is_destructible_v<exceptional_non_trivially_destructible>);
__DATA_STRUCTURE_END