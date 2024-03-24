#include <iostream>
#include "unit_test.hpp"
#include "../source/buffer.hpp"

using namespace ds;
class buffer_correctness : public unit_test_correctness {
public:
    ~buffer_correctness() noexcept override = default;
public:
    // buffer(size_type, const Allocator &), size, empty and iterator
    void test_constructor_1();
    // buffer(size_type, const T &, const Allocator &), size, empty and iterator
    void test_constructor_2();
    // buffer(InputIterator, InputIterator, const Allocator &), size, empty and iterator
    void test_constructor_3();
    // buffer(ForwardIterator, ForwardIterator, const Allocator &), size, empty and iterator
    void test_constructor_4();
    // buffer(initializer_list<T>, const Allocator &), size, empty and iterator
    void test_constructor_5();
    void test_destructor();
    void test_release();
    void test_move_iterator();
    void test_allocator();
};

void buffer_unit_test() {
    auto correctness {new buffer_correctness {}};
    //correctness->test_constructor_1();
    //correctness->test_constructor_2();
    //correctness->test_constructor_3();
    correctness->test_constructor_4();
    delete correctness;
}

void buffer_correctness::test_constructor_1() {
    std::cout << "Start checking buffer(size_type, const Allocator &), size, empty and iterator!" << std::endl;

    // all member should be nothrow
    {
        buffer<int> b(1);
        static_assert(noexcept(b.begin()));
        static_assert(noexcept(b.end()));
        static_assert(noexcept(b.release()));
        static_assert(noexcept(b.mbegin()));
        static_assert(noexcept(b.mend()));
        static_assert(noexcept(b.size()));
        static_assert(noexcept(b.empty()));
        static_assert(noexcept(b.allocator()));
        static_assert(noexcept(b.~buffer()));
        std::cout << "\tBuffer member functions nothrow checking done." << std::endl;
    }
    // empty
    {
        buffer<int> b(0);
        assert(b.size() == 0);
        assert(b.empty());
        assert(b.begin() == b.end());
        std::cout << "\tEmpty buffer checking done." << std::endl;
    }

    // single element
    {
        buffer<int> b(1);
        assert(b.size() == 1);
        assert(not b.empty());
        assert(b.begin() not_eq b.end());
        assert(b.begin() + 1 == b.end());
        assert(*b.begin() == 0);
        std::cout << "\tSingle element buffer checking done." << std::endl;
    }

    // size == 10
    {
        buffer<int> b(10);
        assert(b.size() == 10);
        assert(not b.empty());
        assert(b.begin() + 10 == b.end());
        for(auto it {b.begin()}; it not_eq b.end(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\t10 elements buffer checking done." << std::endl;
    }

    // size == 42
    {
        buffer<int> b(42);
        assert(b.size() == 42);
        assert(not b.empty());
        assert(b.begin() + 42 == b.end());
        for(auto it {b.begin()}; it not_eq b.end(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\t42 elements buffer checking done." << std::endl;
    }

    // size == 64
    {
        buffer<int> b(64);
        assert(b.size() == 64);
        assert(not b.empty());
        assert(b.begin() + 64 == b.end());
        for(auto it {b.begin()}; it not_eq b.end(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\t64 elements buffer checking done." << std::endl;
    }

    // size == 128
    {
        buffer<int> b(128);
        assert(b.size() == 128);
        assert(not b.empty());
        assert(b.begin() + 128 == b.end());
        for(auto it {b.begin()}; it not_eq b.end(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\t128 elements buffer checking done." << std::endl;
    }

    // size == 1024
    {
        buffer<int> b(1024);
        assert(b.size() == 1024);
        assert(not b.empty());
        assert(b.begin() + 1024 == b.end());
        for(auto it {b.begin()}; it not_eq b.end(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\t1024 elements buffer checking done." << std::endl;
    }

    // random size, size <= 10000
    {
        int next {};
        RESTART_10000:
        const auto size {this->generate_count(10000)};
        buffer<int> b(size);
        assert(b.size() == size);
        assert(size == 0 ? b.empty() : not b.empty());
        for(auto it {b.begin()}; it not_eq b.end(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\t10000 elements buffer checking next = " << next + 1 << " done." << std::endl;
        if(++next < 100) {
            goto RESTART_10000;
        }
    }

    // random size, size <= 100000
    {
        int next {};
        RESTART_100000:
        const auto size {this->generate_count(100000)};
        buffer<int> b(size);
        assert(b.size() == size);
        assert(size == 0 ? b.empty() : not b.empty());
        for(auto it {b.begin()}; it not_eq b.end(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\t100000 elements buffer checking next = " << next + 1 << " done." << std::endl;
        if(++next < 50) {
            goto RESTART_100000;
        }
    }

    // random size, size <= 1000000
    {
        int next {};
        RESTART_1000000:
        const auto size {this->generate_count(1000000)};
        buffer<int> b(size);
        assert(b.size() == size);
        assert(size == 0 ? b.empty() : not b.empty());
        for(auto it {b.begin()}; it not_eq b.end(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\t1000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
        if(++next < 10) {
            goto RESTART_1000000;
        }
    }

    // random size, size <= 10000000
    {
        int next {};
        RESTART_10000000:
        const auto size {this->generate_count(10000000)};
        buffer<int> b(size);
        assert(b.size() == size);
        assert(size == 0 ? b.empty() : not b.empty());
        for(auto it {b.begin()}; it not_eq b.end(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\t10000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
        if(++next < 5) {
            goto RESTART_10000000;
        }
    }

    // random size, size <= 100000000
    {
        int next {};
        RESTART_100000000:
        const auto size {this->generate_count(100000000)};
        buffer<int> b(size);
        assert(b.size() == size);
        assert(size == 0 ? b.empty() : not b.empty());
        for(auto it {b.begin()}; it not_eq b.end(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\t100000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
        if(++next < 3) {
            goto RESTART_100000000;
        }
    }

    // random size
    {
        int next {};
        RESTART_RANDOM:
        const auto size {this->generate_count()};
        buffer<int> b(size);
        assert(b.size() == size);
        assert(size == 0 ? b.empty() : not b.empty());
        for(auto it {b.begin()}; it not_eq b.end(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\tRandom sized elements " << size << " buffer checking next = " << next + 1 << " done." << std::endl;
        if(++next < 3) {
            goto RESTART_RANDOM;
        }
    }

    std::cout << "Checking buffer(size_type, const Allocator &), size, empty and iterator finished!" << std::endl;
}
void buffer_correctness::test_constructor_2() {
    std::cout << "Start checking buffer(size_type, const T &, const Allocator &), size, empty and iterator!" << std::endl;

    // empty
    {
        buffer<int> b(0, this->generate_a_random_number());
        assert(b.size() == 0);
        assert(b.empty());
        assert(b.begin() == b.end());
        std::cout << "\tEmpty buffer checking done." << std::endl;
    }

    // single element
    {
        buffer<int> b(1);
        assert(b.size() == 1);
        assert(not b.empty());
        assert(b.begin() not_eq b.end());
        assert(b.begin() + 1 == b.end());
        assert(*b.begin() == 0);
        std::cout << "\tSingle element buffer checking done." << std::endl;
    }

    // size == 10
    {
        buffer<int> b(10);
        assert(b.size() == 10);
        assert(not b.empty());
        assert(b.begin() + 10 == b.end());
        for(auto it {b.begin()}; it not_eq b.end(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\t10 elements buffer checking done." << std::endl;
    }

    // size == 42
    {
        buffer<int> b(42);
        assert(b.size() == 42);
        assert(not b.empty());
        assert(b.begin() + 42 == b.end());
        for(auto it {b.begin()}; it not_eq b.end(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\t42 elements buffer checking done." << std::endl;
    }

    // size == 64
    {
        buffer<int> b(64);
        assert(b.size() == 64);
        assert(not b.empty());
        assert(b.begin() + 64 == b.end());
        for(auto it {b.begin()}; it not_eq b.end(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\t64 elements buffer checking done." << std::endl;
    }

    // size == 128
    {
        buffer<int> b(128);
        assert(b.size() == 128);
        assert(not b.empty());
        assert(b.begin() + 128 == b.end());
        for(auto it {b.begin()}; it not_eq b.end(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\t128 elements buffer checking done." << std::endl;
    }

    // size == 1024
    {
        buffer<int> b(1024);
        assert(b.size() == 1024);
        assert(not b.empty());
        assert(b.begin() + 1024 == b.end());
        for(auto it {b.begin()}; it not_eq b.end(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\t1024 elements buffer checking done." << std::endl;
    }

    // random size, size <= 10000
    {
        int next {};
        RESTART_10000:
        const auto size {this->generate_count(10000)};
        buffer<int> b(size);
        assert(b.size() == size);
        assert(size == 0 ? b.empty() : not b.empty());
        for(auto it {b.begin()}; it not_eq b.end(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\t10000 elements buffer checking next = " << next + 1 << " done." << std::endl;
        if(++next < 100) {
            goto RESTART_10000;
        }
    }

    // random size, size <= 100000
    {
        int next {};
        RESTART_100000:
        const auto size {this->generate_count(100000)};
        buffer<int> b(size);
        assert(b.size() == size);
        assert(size == 0 ? b.empty() : not b.empty());
        for(auto it {b.begin()}; it not_eq b.end(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\t100000 elements buffer checking next = " << next + 1 << " done." << std::endl;
        if(++next < 50) {
            goto RESTART_100000;
        }
    }

    // random size, size <= 1000000
    {
        int next {};
        RESTART_1000000:
        const auto size {this->generate_count(1000000)};
        buffer<int> b(size);
        assert(b.size() == size);
        assert(size == 0 ? b.empty() : not b.empty());
        for(auto it {b.begin()}; it not_eq b.end(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\t1000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
        if(++next < 10) {
            goto RESTART_1000000;
        }
    }

    // random size, size <= 10000000
    {
        int next {};
        RESTART_10000000:
        const auto size {this->generate_count(10000000)};
        buffer<int> b(size);
        assert(b.size() == size);
        assert(size == 0 ? b.empty() : not b.empty());
        for(auto it {b.begin()}; it not_eq b.end(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\t10000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
        if(++next < 5) {
            goto RESTART_10000000;
        }
    }

    // random size, size <= 100000000
    {
        int next {};
        RESTART_100000000:
        const auto size {this->generate_count(100000000)};
        buffer<int> b(size);
        assert(b.size() == size);
        assert(size == 0 ? b.empty() : not b.empty());
        for(auto it {b.begin()}; it not_eq b.end(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\t100000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
        if(++next < 3) {
            goto RESTART_100000000;
        }
    }

    // random size
    {
        int next {};
        RESTART_RANDOM:
        const auto size {this->generate_count()};
        buffer<int> b(size);
        assert(b.size() == size);
        assert(size == 0 ? b.empty() : not b.empty());
        for(auto it {b.begin()}; it not_eq b.end(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\tRandom sized elements " << size << " buffer checking next = " << next + 1 << " done." << std::endl;
        if(++next < 3) {
            goto RESTART_RANDOM;
        }
    }

    std::cout << "Checking buffer(size_type, const T &, const Allocator &), size, empty and iterator finished!" << std::endl;
}
void buffer_correctness::test_constructor_3() {
    std::cout << "Start checking buffer(InputIterator, InputIterator, const Allocator &), size, empty and iterator!" << std::endl;

    // empty
    {
        buffer<int> b(int_input_iterator {}, {});
        assert(b.size() == 0);
        assert(b.empty());
        assert(b.begin() == b.end());
        std::cout << "\tEmpty buffer checking done." << std::endl;
    }

    // single element
    {
        std::stringstream stream("42");
        buffer<int> b(int_input_iterator {stream}, {});
        assert(b.size() == 1);
        assert(not b.empty());
        assert(b.begin() not_eq b.end());
        assert(b.begin() + 1 == b.end());
        assert(*b.begin() == 42);
        std::cout << "\tSingle element buffer checking done." << std::endl;
    }

    // size == 10
    {
        const auto numbers {this->generate_number(10)};
        auto stream {this->to_input_iterator(numbers)};
        buffer<int> b(int_input_iterator {stream}, {});
        assert(b.size() == 10);
        assert(not b.empty());
        assert(b.begin() + 10 == b.end());
        const auto begin {b.begin()};
        for(auto i {0}; i < numbers.size(); ++i) {
            assert(begin[i] == numbers[i]);
        }
        std::cout << "\t10 elements buffer checking done." << std::endl;
    }

    // size == 42
    {
        const auto numbers {this->generate_number(42)};
        auto stream {this->to_input_iterator(numbers)};
        buffer<int> b(int_input_iterator {stream}, {});
        assert(b.size() == 42);
        assert(not b.empty());
        assert(b.begin() + 42 == b.end());
        const auto begin {b.begin()};
        for(auto i {0}; i < numbers.size(); ++i) {
            assert(begin[i] == numbers[i]);
        }
        std::cout << "\t42 elements buffer checking done." << std::endl;
    }

    // size == 64
    {
        const auto numbers {this->generate_number(64)};
        auto stream {this->to_input_iterator(numbers)};
        buffer<int> b(int_input_iterator {stream}, {});
        assert(b.size() == 64);
        assert(not b.empty());
        assert(b.begin() + 64 == b.end());
        const auto begin {b.begin()};
        for(auto i {0}; i < numbers.size(); ++i) {
            assert(begin[i] == numbers[i]);
        }
        std::cout << "\t64 elements buffer checking done." << std::endl;
    }

    // size == 128
    {
        const auto numbers {this->generate_number(128)};
        auto stream {this->to_input_iterator(numbers)};
        buffer<int> b(int_input_iterator {stream}, {});
        assert(b.size() == 128);
        assert(not b.empty());
        assert(b.begin() + 128 == b.end());
        const auto begin {b.begin()};
        for(auto i {0}; i < numbers.size(); ++i) {
            assert(begin[i] == numbers[i]);
        }
        std::cout << "\t128 elements buffer checking done." << std::endl;
    }

    // size == 1024
    {
        const auto numbers {this->generate_number(1024)};
        auto stream {this->to_input_iterator(numbers)};
        buffer<int> b(int_input_iterator {stream}, {});
        assert(b.size() == 1024);
        assert(not b.empty());
        assert(b.begin() + 1024 == b.end());
        const auto begin {b.begin()};
        for(auto i {0}; i < numbers.size(); ++i) {
            assert(begin[i] == numbers[i]);
        }
        std::cout << "\t1024 elements buffer checking done." << std::endl;
    }

    // size == 10000
    {
        int next {};
        RESTART_10000:
        const auto numbers {this->generate_number(10000)};
        auto stream {this->to_input_iterator(numbers)};
        buffer<int> b(int_input_iterator {stream}, {});
        assert(b.size() == 10000);
        assert(not b.empty());
        assert(b.begin() + 10000 == b.end());
        const auto begin {b.begin()};
        for(auto i {0}; i < numbers.size(); ++i) {
            assert(begin[i] == numbers[i]);
        }
        std::cout << "\t10000 elements buffer checking next = " << next + 1 << " done." << std::endl;
        if(++next < 100) {
            goto RESTART_10000;
        }
    }

    // size == 100000
    {
        int next {};
        RESTART_100000:
        const auto numbers {this->generate_number(100000)};
        auto stream {this->to_input_iterator(numbers)};
        buffer<int> b(int_input_iterator {stream}, {});
        assert(b.size() == 100000);
        assert(not b.empty());
        assert(b.begin() + 100000 == b.end());
        const auto begin {b.begin()};
        for(auto i {0}; i < numbers.size(); ++i) {
            assert(begin[i] == numbers[i]);
        }
        std::cout << "\t100000 elements buffer checking next = " << next + 1 << " done." << std::endl;
        if(++next < 50) {
            goto RESTART_100000;
        }
    }

    // size == 1000000
    {
        int next {};
        RESTART_1000000:
        const auto numbers {this->generate_number(1000000)};
        auto stream {this->to_input_iterator(numbers)};
        buffer<int> b(int_input_iterator {stream}, {});
        assert(b.size() == 1000000);
        assert(not b.empty());
        assert(b.begin() + 1000000 == b.end());
        const auto begin {b.begin()};
        for(auto i {0}; i < numbers.size(); ++i) {
            assert(begin[i] == numbers[i]);
        }
        std::cout << "\t1000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
        if(++next < 10) {
            goto RESTART_1000000;
        }
    }

    // size == 10000000
    {
        int next {};
        RESTART_10000000:
        const auto numbers {this->generate_number(10000000)};
        auto stream {this->to_input_iterator(numbers)};
        buffer<int> b(int_input_iterator {stream}, {});
        assert(b.size() == 10000000);
        assert(not b.empty());
        assert(b.begin() + 10000000 == b.end());
        const auto begin {b.begin()};
        for(auto i {0}; i < numbers.size(); ++i) {
            assert(begin[i] == numbers[i]);
        }
        std::cout << "\t10000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
        if(++next < 5) {
            goto RESTART_10000000;
        }
    }

    // size == 100000000
    {
        int next {};
        RESTART_100000000:
        const auto numbers {this->generate_number(100000000)};
        auto stream {this->to_input_iterator(numbers)};
        buffer<int> b(int_input_iterator {stream}, {});
        assert(b.size() == 100000000);
        assert(not b.empty());
        assert(b.begin() + 100000000 == b.end());
        const auto begin {b.begin()};
        for(auto i {0}; i < numbers.size(); ++i) {
            assert(begin[i] == numbers[i]);
        }
        std::cout << "\t100000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
        if(++next < 3) {
            goto RESTART_100000000;
        }
    }

    // random size
    {
        int next {};
        RESTART_RANDOM:
        const auto size {this->generate_count()};
        const auto numbers {this->generate_number(size)};
        auto stream {this->to_input_iterator(numbers)};
        buffer<int> b(int_input_iterator {stream}, {});
        assert(b.size() == size);
        assert(not b.empty());
        assert(b.begin() + size == b.end());
        const auto begin {b.begin()};
        for(auto i {0}; i < numbers.size(); ++i) {
            assert(begin[i] == numbers[i]);
        }
        std::cout << "\tRandom sized elements " << size << " buffer checking next = " << next + 1 << " done." << std::endl;
        if(++next < 3) {
            goto RESTART_RANDOM;
        }
    }

    std::cout << "Checking buffer(InputIterator, InputIterator, const Allocator &), size, empty and iterator finished!" << std::endl;
}

void buffer_correctness::test_constructor_4() {
    std::cout << "Start checking buffer(ForwardIterator, ForwardIterator, const Allocator &), size, empty and iterator!" << std::endl;

    // forward iterator
    {
        std::cout << "\tStart checking forward_iterator version!" << std::endl;
        // empty
        {
            buffer<int> b(int_forward_iterator {}, {});
            assert(b.size() == 0);
            assert(b.empty());
            assert(b.begin() == b.end());
            std::cout << "\t\tEmpty buffer checking done." << std::endl;
        }

        // single element
        {
            std::forward_list<int> l {42};
            buffer<int> b(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
            assert(b.size() == 1);
            assert(not b.empty());
            assert(b.begin() not_eq b.end());
            assert(b.begin() + 1 == b.end());
            assert(*b.begin() == 42);
            std::cout << "\t\tSingle element buffer checking done." << std::endl;
        }

        // size == 10
        {
            const auto numbers {this->generate_number(10)};
            auto l {this->to_forward_iterator(numbers)};
            buffer<int> b(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
            assert(b.size() == 10);
            assert(not b.empty());
            assert(b.begin() + 10 == b.end());
            const auto begin {b.begin()};
            for(auto i {0}; i < numbers.size(); ++i) {
                assert(begin[i] == numbers[i]);
            }
            std::cout << "\t\t10 elements buffer checking done." << std::endl;
        }

        // size == 42
        {
            const auto numbers {this->generate_number(42)};
            auto l {this->to_forward_iterator(numbers)};
            buffer<int> b(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
            assert(b.size() == 42);
            assert(not b.empty());
            assert(b.begin() + 42 == b.end());
            const auto begin {b.begin()};
            for(auto i {0}; i < numbers.size(); ++i) {
                assert(begin[i] == numbers[i]);
            }
            std::cout << "\t\t42 elements buffer checking done." << std::endl;
        }

        // size == 64
        {
            const auto numbers {this->generate_number(64)};
            auto l {this->to_forward_iterator(numbers)};
            buffer<int> b(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
            assert(b.size() == 64);
            assert(not b.empty());
            assert(b.begin() + 64 == b.end());
            const auto begin {b.begin()};
            for(auto i {0}; i < numbers.size(); ++i) {
                assert(begin[i] == numbers[i]);
            }
            std::cout << "\t\t64 elements buffer checking done." << std::endl;
        }

        // size == 128
        {
            const auto numbers {this->generate_number(128)};
            auto l {this->to_forward_iterator(numbers)};
            buffer<int> b(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
            assert(b.size() == 128);
            assert(not b.empty());
            assert(b.begin() + 128 == b.end());
            const auto begin {b.begin()};
            for(auto i {0}; i < numbers.size(); ++i) {
                assert(begin[i] == numbers[i]);
            }
            std::cout << "\t\t128 elements buffer checking done." << std::endl;
        }

        // size == 1024
        {
            const auto numbers {this->generate_number(1024)};
            auto l {this->to_forward_iterator(numbers)};
            buffer<int> b(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
            assert(b.size() == 1024);
            assert(not b.empty());
            assert(b.begin() + 1024 == b.end());
            const auto begin {b.begin()};
            for(auto i {0}; i < numbers.size(); ++i) {
                assert(begin[i] == numbers[i]);
            }
            std::cout << "\t\t1024 elements buffer checking done." << std::endl;
        }

        // size == 10000
        {
            int next {};
            RESTART_FORWARD_10000:
            const auto numbers {this->generate_number(10000)};
            auto l {this->to_forward_iterator(numbers)};
            buffer<int> b(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
            assert(b.size() == 10000);
            assert(not b.empty());
            assert(b.begin() + 10000 == b.end());
            const auto begin {b.begin()};
            for(auto i {0}; i < numbers.size(); ++i) {
                assert(begin[i] == numbers[i]);
            }
            std::cout << "\t\t10000 elements buffer checking next = " << next + 1 << " done." << std::endl;
            if(++next < 100) {
                goto RESTART_FORWARD_10000;
            }
        }

        // size == 100000
        {
            int next {};
            RESTART_FORWARD_100000:
            const auto numbers {this->generate_number(100000)};
            auto l {this->to_forward_iterator(numbers)};
            buffer<int> b(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
            assert(b.size() == 100000);
            assert(not b.empty());
            assert(b.begin() + 100000 == b.end());
            const auto begin {b.begin()};
            for(auto i {0}; i < numbers.size(); ++i) {
                assert(begin[i] == numbers[i]);
            }
            std::cout << "\t\t100000 elements buffer checking next = " << next + 1 << " done." << std::endl;
            if(++next < 50) {
                goto RESTART_FORWARD_100000;
            }
        }

        // size == 1000000
        {
            int next {};
            RESTART_FORWARD_1000000:
            const auto numbers {this->generate_number(1000000)};
            auto l {this->to_forward_iterator(numbers)};
            buffer<int> b(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
            assert(b.size() == 1000000);
            assert(not b.empty());
            assert(b.begin() + 1000000 == b.end());
            const auto begin {b.begin()};
            for(auto i {0}; i < numbers.size(); ++i) {
                assert(begin[i] == numbers[i]);
            }
            std::cout << "\t\t1000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
            if(++next < 10) {
                goto RESTART_FORWARD_1000000;
            }
        }

        // size == 10000000
        {
            int next {};
            RESTART_FORWARD_10000000:
            const auto numbers {this->generate_number(10000000)};
            auto l {this->to_forward_iterator(numbers)};
            buffer<int> b(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
            assert(b.size() == 10000000);
            assert(not b.empty());
            assert(b.begin() + 10000000 == b.end());
            const auto begin {b.begin()};
            for(auto i {0}; i < numbers.size(); ++i) {
                assert(begin[i] == numbers[i]);
            }
            std::cout << "\t\t10000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
            if(++next < 5) {
                goto RESTART_FORWARD_10000000;
            }
        }

        // size == 100000000
        {
            int next {};
            RESTART_FORWARD_100000000:
            const auto numbers {this->generate_number(100000000)};
            auto l {this->to_forward_iterator(numbers)};
            buffer<int> b(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
            assert(b.size() == 100000000);
            assert(not b.empty());
            assert(b.begin() + 100000000 == b.end());
            const auto begin {b.begin()};
            for(auto i {0}; i < numbers.size(); ++i) {
                assert(begin[i] == numbers[i]);
            }
            std::cout << "\t\t100000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
            if(++next < 3) {
                goto RESTART_FORWARD_100000000;
            }
        }

        // random size
        {
            int next {};
            RESTART_FORWARD_RANDOM:
            const auto size {this->generate_count()};
            const auto numbers {this->generate_number(size)};
            auto l {this->to_forward_iterator(numbers)};
            buffer<int> b(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
            assert(b.size() == size);
            assert(not b.empty());
            assert(b.begin() + size == b.end());
            const auto begin {b.begin()};
            for(auto i {0}; i < numbers.size(); ++i) {
                assert(begin[i] == numbers[i]);
            }
            std::cout << "\t\tRandom sized elements " << size << " buffer checking next = " << next + 1 << " done." << std::endl;
            if(++next < 3) {
                goto RESTART_FORWARD_RANDOM;
            }
        }
        std::cout << "\tChecking forward iterator version finished!" << std::endl;
    }

    // bidirectional iterator
    {
        std::cout << "\tStart checking bidirectional iterator version!" << std::endl;
        // empty
        {
            buffer<int> b(int_bidirectional_iterator {}, {});
            assert(b.size() == 0);
            assert(b.empty());
            assert(b.begin() == b.end());
            std::cout << "\t\tEmpty buffer checking done." << std::endl;
        }

        // single element
        {
            std::list<int> l {42};
            buffer<int> b(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
            assert(b.size() == 1);
            assert(not b.empty());
            assert(b.begin() not_eq b.end());
            assert(b.begin() + 1 == b.end());
            assert(*b.begin() == 42);
            std::cout << "\t\tSingle element buffer checking done." << std::endl;
        }

        // size == 10
        {
            const auto numbers {this->generate_number(10)};
            auto l {this->to_bidirectional_iterator(numbers)};
            buffer<int> b(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
            assert(b.size() == 10);
            assert(not b.empty());
            assert(b.begin() + 10 == b.end());
            const auto begin {b.begin()};
            for(auto i {0}; i < numbers.size(); ++i) {
                assert(begin[i] == numbers[i]);
            }
            std::cout << "\t\t10 elements buffer checking done." << std::endl;
        }

        // size == 42
        {
            const auto numbers {this->generate_number(42)};
            auto l {this->to_bidirectional_iterator(numbers)};
            buffer<int> b(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
            assert(b.size() == 42);
            assert(not b.empty());
            assert(b.begin() + 42 == b.end());
            const auto begin {b.begin()};
            for(auto i {0}; i < numbers.size(); ++i) {
                assert(begin[i] == numbers[i]);
            }
            std::cout << "\t\t42 elements buffer checking done." << std::endl;
        }

        // size == 64
        {
            const auto numbers {this->generate_number(64)};
            auto l {this->to_bidirectional_iterator(numbers)};
            buffer<int> b(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
            assert(b.size() == 64);
            assert(not b.empty());
            assert(b.begin() + 64 == b.end());
            const auto begin {b.begin()};
            for(auto i {0}; i < numbers.size(); ++i) {
                assert(begin[i] == numbers[i]);
            }
            std::cout << "\t\t64 elements buffer checking done." << std::endl;
        }

        // size == 128
        {
            const auto numbers {this->generate_number(128)};
            auto l {this->to_bidirectional_iterator(numbers)};
            buffer<int> b(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
            assert(b.size() == 128);
            assert(not b.empty());
            assert(b.begin() + 128 == b.end());
            const auto begin {b.begin()};
            for(auto i {0}; i < numbers.size(); ++i) {
                assert(begin[i] == numbers[i]);
            }
            std::cout << "\t\t128 elements buffer checking done." << std::endl;
        }

        // size == 1024
        {
            const auto numbers {this->generate_number(1024)};
            auto l {this->to_bidirectional_iterator(numbers)};
            buffer<int> b(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
            assert(b.size() == 1024);
            assert(not b.empty());
            assert(b.begin() + 1024 == b.end());
            const auto begin {b.begin()};
            for(auto i {0}; i < numbers.size(); ++i) {
                assert(begin[i] == numbers[i]);
            }
            std::cout << "\t\t1024 elements buffer checking done." << std::endl;
        }

        // size == 10000
        {
            int next {};
            RESTART_BIDIRECTIONAL_10000:
            const auto numbers {this->generate_number(10000)};
            auto l {this->to_bidirectional_iterator(numbers)};
            buffer<int> b(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
            assert(b.size() == 10000);
            assert(not b.empty());
            assert(b.begin() + 10000 == b.end());
            const auto begin {b.begin()};
            for(auto i {0}; i < numbers.size(); ++i) {
                assert(begin[i] == numbers[i]);
            }
            std::cout << "\t\t10000 elements buffer checking next = " << next + 1 << " done." << std::endl;
            if(++next < 100) {
                goto RESTART_BIDIRECTIONAL_10000;
            }
        }

        // size == 100000
        {
            int next {};
            RESTART_BIDIRECTIONAL_100000:
            const auto numbers {this->generate_number(100000)};
            auto l {this->to_bidirectional_iterator(numbers)};
            buffer<int> b(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
            assert(b.size() == 100000);
            assert(not b.empty());
            assert(b.begin() + 100000 == b.end());
            const auto begin {b.begin()};
            for(auto i {0}; i < numbers.size(); ++i) {
                assert(begin[i] == numbers[i]);
            }
            std::cout << "\t\t100000 elements buffer checking next = " << next + 1 << " done." << std::endl;
            if(++next < 50) {
                goto RESTART_BIDIRECTIONAL_100000;
            }
        }

        // size == 1000000
        {
            int next {};
            RESTART_BIDIRECTIONAL_1000000:
            const auto numbers {this->generate_number(1000000)};
            auto l {this->to_bidirectional_iterator(numbers)};
            buffer<int> b(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
            assert(b.size() == 1000000);
            assert(not b.empty());
            assert(b.begin() + 1000000 == b.end());
            const auto begin {b.begin()};
            for(auto i {0}; i < numbers.size(); ++i) {
                assert(begin[i] == numbers[i]);
            }
            std::cout << "\t\t1000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
            if(++next < 10) {
                goto RESTART_BIDIRECTIONAL_1000000;
            }
        }

        // size == 10000000
        {
            int next {};
            RESTART_BIDIRECTIONAL_10000000:
            const auto numbers {this->generate_number(10000000)};
            auto l {this->to_bidirectional_iterator(numbers)};
            buffer<int> b(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
            assert(b.size() == 10000000);
            assert(not b.empty());
            assert(b.begin() + 10000000 == b.end());
            const auto begin {b.begin()};
            for(auto i {0}; i < numbers.size(); ++i) {
                assert(begin[i] == numbers[i]);
            }
            std::cout << "\t\t10000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
            if(++next < 5) {
                goto RESTART_BIDIRECTIONAL_10000000;
            }
        }

        // size == 100000000
        {
            int next {};
            RESTART_BIDIRECTIONAL_100000000:
            const auto numbers {this->generate_number(100000000)};
            auto l {this->to_bidirectional_iterator(numbers)};
            buffer<int> b(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
            assert(b.size() == 100000000);
            assert(not b.empty());
            assert(b.begin() + 100000000 == b.end());
            const auto begin {b.begin()};
            for(auto i {0}; i < numbers.size(); ++i) {
                assert(begin[i] == numbers[i]);
            }
            std::cout << "\t\t100000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
            if(++next < 3) {
                goto RESTART_BIDIRECTIONAL_100000000;
            }
        }

        // random size
        {
            int next {};
            RESTART_BIDIRECTIONAL_RANDOM:
            const auto size {this->generate_count()};
            const auto numbers {this->generate_number(size)};
            auto l {this->to_bidirectional_iterator(numbers)};
            buffer<int> b(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
            assert(b.size() == size);
            assert(not b.empty());
            assert(b.begin() + size == b.end());
            const auto begin {b.begin()};
            for(auto i {0}; i < numbers.size(); ++i) {
                assert(begin[i] == numbers[i]);
            }
            std::cout << "\t\tRandom sized elements " << size << " buffer checking next = " << next + 1 << " done." << std::endl;
            if(++next < 3) {
                goto RESTART_BIDIRECTIONAL_RANDOM;
            }
        }
        std::cout << "\tChecking bidirectional iterator version finished!" << std::endl;
    }

    // bidirectional iterator
    {
        std::cout << "\tStart checking bidirectional iterator version!" << std::endl;
        // empty
        {
            buffer<int> b(int_random_access_iterator {}, {});
            assert(b.size() == 0);
            assert(b.empty());
            assert(b.begin() == b.end());
            std::cout << "\t\tEmpty buffer checking done." << std::endl;
        }

        // single element
        {
            std::deque<int> d {42};
            buffer<int> b(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
            assert(b.size() == 1);
            assert(not b.empty());
            assert(b.begin() not_eq b.end());
            assert(b.begin() + 1 == b.end());
            assert(*b.begin() == 42);
            std::cout << "\t\tSingle element buffer checking done." << std::endl;
        }

        // size == 10
        {
            const auto numbers {this->generate_number(10)};
            auto d {this->to_random_access_iterator(numbers)};
            buffer<int> b(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
            assert(b.size() == 10);
            assert(not b.empty());
            assert(b.begin() + 10 == b.end());
            const auto begin {b.begin()};
            for(auto i {0}; i < numbers.size(); ++i) {
                assert(begin[i] == numbers[i]);
            }
            std::cout << "\t\t10 elements buffer checking done." << std::endl;
        }

        // size == 42
        {
            const auto numbers {this->generate_number(42)};
            auto d {this->to_random_access_iterator(numbers)};
            buffer<int> b(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
            assert(b.size() == 42);
            assert(not b.empty());
            assert(b.begin() + 42 == b.end());
            const auto begin {b.begin()};
            for(auto i {0}; i < numbers.size(); ++i) {
                assert(begin[i] == numbers[i]);
            }
            std::cout << "\t\t42 elements buffer checking done." << std::endl;
        }

        // size == 64
        {
            const auto numbers {this->generate_number(64)};
            auto d {this->to_random_access_iterator(numbers)};
            buffer<int> b(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
            assert(b.size() == 64);
            assert(not b.empty());
            assert(b.begin() + 64 == b.end());
            const auto begin {b.begin()};
            for(auto i {0}; i < numbers.size(); ++i) {
                assert(begin[i] == numbers[i]);
            }
            std::cout << "\t\t64 elements buffer checking done." << std::endl;
        }

        // size == 128
        {
            const auto numbers {this->generate_number(128)};
            auto d {this->to_random_access_iterator(numbers)};
            buffer<int> b(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
            assert(b.size() == 128);
            assert(not b.empty());
            assert(b.begin() + 128 == b.end());
            const auto begin {b.begin()};
            for(auto i {0}; i < numbers.size(); ++i) {
                assert(begin[i] == numbers[i]);
            }
            std::cout << "\t\t128 elements buffer checking done." << std::endl;
        }

        // size == 1024
        {
            const auto numbers {this->generate_number(1024)};
            auto d {this->to_random_access_iterator(numbers)};
            buffer<int> b(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
            assert(b.size() == 1024);
            assert(not b.empty());
            assert(b.begin() + 1024 == b.end());
            const auto begin {b.begin()};
            for(auto i {0}; i < numbers.size(); ++i) {
                assert(begin[i] == numbers[i]);
            }
            std::cout << "\t\t1024 elements buffer checking done." << std::endl;
        }

        // size == 10000
        {
            int next {};
            RESTART_RANDOM_ACCESS_10000:
            const auto numbers {this->generate_number(10000)};
            auto d {this->to_random_access_iterator(numbers)};
            buffer<int> b(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
            assert(b.size() == 10000);
            assert(not b.empty());
            assert(b.begin() + 10000 == b.end());
            const auto begin {b.begin()};
            for(auto i {0}; i < numbers.size(); ++i) {
                assert(begin[i] == numbers[i]);
            }
            std::cout << "\t\t10000 elements buffer checking next = " << next + 1 << " done." << std::endl;
            if(++next < 100) {
                goto RESTART_RANDOM_ACCESS_10000;
            }
        }

        // size == 100000
        {
            int next {};
            RESTART_RANDOM_ACCESS_100000:
            const auto numbers {this->generate_number(100000)};
            auto d {this->to_random_access_iterator(numbers)};
            buffer<int> b(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
            assert(b.size() == 100000);
            assert(not b.empty());
            assert(b.begin() + 100000 == b.end());
            const auto begin {b.begin()};
            for(auto i {0}; i < numbers.size(); ++i) {
                assert(begin[i] == numbers[i]);
            }
            std::cout << "\t\t100000 elements buffer checking next = " << next + 1 << " done." << std::endl;
            if(++next < 50) {
                goto RESTART_RANDOM_ACCESS_100000;
            }
        }

        // size == 1000000
        {
            int next {};
            RESTART_RANDOM_ACCESS_1000000:
            const auto numbers {this->generate_number(1000000)};
            auto d {this->to_random_access_iterator(numbers)};
            buffer<int> b(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
            assert(b.size() == 1000000);
            assert(not b.empty());
            assert(b.begin() + 1000000 == b.end());
            const auto begin {b.begin()};
            for(auto i {0}; i < numbers.size(); ++i) {
                assert(begin[i] == numbers[i]);
            }
            std::cout << "\t\t1000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
            if(++next < 10) {
                goto RESTART_RANDOM_ACCESS_1000000;
            }
        }

        // size == 10000000
        {
            int next {};
            RESTART_RANDOM_ACCESS_10000000:
            const auto numbers {this->generate_number(10000000)};
            auto d {this->to_random_access_iterator(numbers)};
            buffer<int> b(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
            assert(b.size() == 10000000);
            assert(not b.empty());
            assert(b.begin() + 10000000 == b.end());
            const auto begin {b.begin()};
            for(auto i {0}; i < numbers.size(); ++i) {
                assert(begin[i] == numbers[i]);
            }
            std::cout << "\t\t10000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
            if(++next < 5) {
                goto RESTART_RANDOM_ACCESS_10000000;
            }
        }

        // size == 100000000
        {
            int next {};
            RESTART_RANDOM_ACCESS_100000000:
            const auto numbers {this->generate_number(100000000)};
            auto d {this->to_random_access_iterator(numbers)};
            buffer<int> b(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
            assert(b.size() == 100000000);
            assert(not b.empty());
            assert(b.begin() + 100000000 == b.end());
            const auto begin {b.begin()};
            for(auto i {0}; i < numbers.size(); ++i) {
                assert(begin[i] == numbers[i]);
            }
            std::cout << "\t\t100000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
            if(++next < 3) {
                goto RESTART_RANDOM_ACCESS_100000000;
            }
        }

        // random size
        {
            int next {};
            RESTART_RANDOM_ACCESS_RANDOM:
            const auto size {this->generate_count()};
            const auto numbers {this->generate_number(size)};
            auto d {this->to_random_access_iterator(numbers)};
            buffer<int> b(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
            assert(b.size() == size);
            assert(not b.empty());
            assert(b.begin() + size == b.end());
            const auto begin {b.begin()};
            for(auto i {0}; i < numbers.size(); ++i) {
                assert(begin[i] == numbers[i]);
            }
            std::cout << "\t\tRandom sized elements " << size << " buffer checking next = " << next + 1 << " done." << std::endl;
            if(++next < 3) {
                goto RESTART_RANDOM_ACCESS_RANDOM;
            }
        }
        std::cout << "\tChecking bidirectional iterator version finished!" << std::endl;
    }

    std::cout << "Checking buffer(ForwardIterator, ForwardIterator, const Allocator &), size, empty and iterator finished!" << std::endl;
}