#include "../source/buffer.hpp"
#include "unit_test.hpp"

class buffer_correctness : public unit_test_correctness {
public:
    // buffer(size_type, const Allocator &), size and empty
    void test_constructor_1();
    // buffer(size_type, const T &, const Allocator &), size and empty
    void test_constructor_2();
    // buffer(InputIterator, InputIterator, const Allocator &), size and empty
    void test_constructor_3();
    // buffer(ForwardIterator, ForwardIterator, const Allocator &), size and empty
    void test_constructor_4();
    // buffer(initializer_list<T>, const Allocator &), size and empty
    void test_constructor_5();
    void test_destructor();
    void test_iterator();
    void test_release();
    void test_move_iterator();
    void test_allocator();
};

void buffer_unit_test() {

}