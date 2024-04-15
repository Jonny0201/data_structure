#include <iostream>
#include "unit_test.hpp"
#include "../source/vector.hpp"

using namespace ds;
class vector_correctness : public unit_test_correctness {
public:
    ~vector_correctness() noexcept override = default;
public:
    void test_default_constructor();
    // vector(const Allocator &)
    void test_constructor_1();
    // vector(size_type, const Allocator &), size, empty, capacity, spare, front, back, data, index and iterator
    void test_constructor_2();
    // vector(size_type, const T &, const Allocator &), size, empty, capacity, spare, front, back, data, index and iterator
    void test_constructor_3();
    // vector(InputIterator, InputIterator, const Allocator &), size, empty, capacity, spare, front, back, data, index and iterator
    void test_constructor_4();
    // vector(ForwardIterator, ForwardIterator, const Allocator &), size, empty, capacity, spare, front, back, data, index and iterator
    void test_constructor_5();
    // vector(initializer_list<T>, const Allocator &), size, empty, capacity, spare, front, back, data, index and iterator
    void test_constructor_6();
    // vector(const vector &), size, empty, capacity, spare, front, back, data, index and iterator
    void test_copy_constructor();
    // vector(vector &&), size, empty, capacity, spare, front, back, data, index and iterator
    void test_move_constructor();
    void test_copy_assignment();
    void test_move_assignment();
    // void assign(size_type, const_reference)
    void test_assign_1();
    // void assign(InputIterator, InputIterator)
    void test_assign_2();
    // void assign(ForwardIterator, ForwardIterator)
    void test_assign_3();
    void test_reserve();
    void test_push_back();
    void test_pop_back();
    void test_clear();
    void test_swap();
    // iterator insert(difference_type, difference_type, size_type)
    void test_insert_1();
    // iterator insert(difference_type, rvalue_reference) and iterator emplace(difference_type, Args &&...)
    void test_insert_2();
    // iterator insert(InputIterator, InputIterator)
    void test_insert_3();
    // iterator insert(ForwardIterator, ForwardIterator)
    void test_insert_4();
    // iterator erase(difference_type, size_type)
    void test_erase();
    void test_allocator();
    void test_non_trivial();
};