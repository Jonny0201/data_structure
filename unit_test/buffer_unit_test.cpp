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
    void test_release();
    void test_move_iterator();
    void test_allocator();
    void test_non_trivial();
};

void buffer_unit_test() {
    auto correctness {new buffer_correctness {}};
    //correctness->test_constructor_1();
    //correctness->test_constructor_2();
    //correctness->test_constructor_3();
    //correctness->test_constructor_4();
    //correctness->test_constructor_5();
    //correctness->test_release();
    //correctness->test_move_iterator();
    //correctness->test_allocator();
    correctness->test_non_trivial();
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
        std::cout << "\ttest_constructor_1/Buffer member functions nothrow checking done." << std::endl;
    }
    // empty
    {
        buffer<int> b(0);
        assert(b.size() == 0);
        assert(b.empty());
        assert(b.begin() == b.end());
        std::cout << "\ttest_constructor_1/Empty buffer checking done." << std::endl;
    }

    // single element
    {
        buffer<int> b(1);
        assert(b.size() == 1);
        assert(not b.empty());
        assert(b.begin() not_eq b.end());
        assert(b.begin() + 1 == b.end());
        assert(*b.begin() == 0);
        std::cout << "\ttest_constructor_1/Single element buffer checking done." << std::endl;
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
        std::cout << "\ttest_constructor_1/10 elements buffer checking done." << std::endl;
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
        std::cout << "\ttest_constructor_1/42 elements buffer checking done." << std::endl;
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
        std::cout << "\ttest_constructor_1/64 elements buffer checking done." << std::endl;
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
        std::cout << "\ttest_constructor_1/128 elements buffer checking done." << std::endl;
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
        std::cout << "\ttest_constructor_1/1024 elements buffer checking done." << std::endl;
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
        std::cout << "\ttest_constructor_1/10000 elements buffer checking next = " << next + 1 << " done." << std::endl;
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
        std::cout << "\ttest_constructor_1/100000 elements buffer checking next = " << next + 1 << " done." << std::endl;
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
        std::cout << "\ttest_constructor_1/1000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
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
        std::cout << "\ttest_constructor_1/10000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
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
        std::cout << "\ttest_constructor_1/100000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
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
        std::cout << "\ttest_constructor_1/Random sized elements " << size << " buffer checking next = " << next + 1 << " done." << std::endl;
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
        std::cout << "\ttest_constructor_2/Empty buffer checking done." << std::endl;
    }

    // single element
    {
        buffer<int> b(1);
        assert(b.size() == 1);
        assert(not b.empty());
        assert(b.begin() not_eq b.end());
        assert(b.begin() + 1 == b.end());
        assert(*b.begin() == 0);
        std::cout << "\ttest_constructor_2/Single element buffer checking done." << std::endl;
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
        std::cout << "\ttest_constructor_2/10 elements buffer checking done." << std::endl;
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
        std::cout << "\ttest_constructor_2/42 elements buffer checking done." << std::endl;
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
        std::cout << "\ttest_constructor_2/64 elements buffer checking done." << std::endl;
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
        std::cout << "\ttest_constructor_2/128 elements buffer checking done." << std::endl;
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
        std::cout << "\ttest_constructor_2/1024 elements buffer checking done." << std::endl;
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
        std::cout << "\ttest_constructor_2/10000 elements buffer checking next = " << next + 1 << " done." << std::endl;
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
        std::cout << "\ttest_constructor_2/100000 elements buffer checking next = " << next + 1 << " done." << std::endl;
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
        std::cout << "\ttest_constructor_2/1000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
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
        std::cout << "\ttest_constructor_2/10000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
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
        std::cout << "\ttest_constructor_2/100000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
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
        std::cout << "\ttest_constructor_2/Random sized elements " << size << " buffer checking next = " << next + 1 << " done." << std::endl;
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
        std::cout << "\ttest_constructor_3/Empty buffer checking done." << std::endl;
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
        std::cout << "\ttest_constructor_3/Single element buffer checking done." << std::endl;
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
        std::cout << "\ttest_constructor_3/10 elements buffer checking done." << std::endl;
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
        std::cout << "\ttest_constructor_3/42 elements buffer checking done." << std::endl;
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
        std::cout << "\ttest_constructor_3/64 elements buffer checking done." << std::endl;
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
        std::cout << "\ttest_constructor_3/128 elements buffer checking done." << std::endl;
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
        std::cout << "\ttest_constructor_3/1024 elements buffer checking done." << std::endl;
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
        std::cout << "\ttest_constructor_3/10000 elements buffer checking next = " << next + 1 << " done." << std::endl;
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
        std::cout << "\ttest_constructor_3/100000 elements buffer checking next = " << next + 1 << " done." << std::endl;
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
        std::cout << "\ttest_constructor_3/1000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
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
        std::cout << "\ttest_constructor_3/10000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
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
        std::cout << "\ttest_constructor_3/100000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
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
        std::cout << "\ttest_constructor_3/Random sized elements " << size << " buffer checking next = " << next + 1 << " done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/forward iterator/Empty buffer checking done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/forward iterator/Single element buffer checking done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/forward iterator/10 elements buffer checking done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/forward iterator/42 elements buffer checking done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/forward iterator/64 elements buffer checking done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/forward iterator/128 elements buffer checking done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/forward iterator/1024 elements buffer checking done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/forward iterator/10000 elements buffer checking next = " << next + 1 << " done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/forward iterator/100000 elements buffer checking next = " << next + 1 << " done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/forward iterator/1000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/forward iterator/10000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/forward iterator/100000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/forward iterator/Random sized elements " << size << " buffer checking next = " << next + 1 << " done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/bidirectional iterator/Empty buffer checking done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/bidirectional iterator/Single element buffer checking done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/bidirectional iterator/10 elements buffer checking done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/bidirectional iterator/42 elements buffer checking done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/bidirectional iterator/64 elements buffer checking done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/bidirectional iterator/128 elements buffer checking done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/bidirectional iterator/1024 elements buffer checking done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/bidirectional iterator/10000 elements buffer checking next = " << next + 1 << " done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/bidirectional iterator/100000 elements buffer checking next = " << next + 1 << " done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/bidirectional iterator/1000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/bidirectional iterator/10000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/bidirectional iterator/100000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/bidirectional iterator/Random sized elements " << size << " buffer checking next = " << next + 1 << " done." << std::endl;
            if(++next < 3) {
                goto RESTART_BIDIRECTIONAL_RANDOM;
            }
        }
        std::cout << "\tChecking bidirectional iterator version finished!" << std::endl;
    }

    // random access iterator
    {
        std::cout << "\tStart checking bidirectional iterator version!" << std::endl;
        // empty
        {
            buffer<int> b(int_random_access_iterator {}, {});
            assert(b.size() == 0);
            assert(b.empty());
            assert(b.begin() == b.end());
            std::cout << "\t\ttest_constructor_4/random access iterator/Empty buffer checking done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/random access iterator/Single element buffer checking done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/random access iterator/10 elements buffer checking done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/random access iterator/42 elements buffer checking done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/random access iterator/64 elements buffer checking done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/random access iterator/128 elements buffer checking done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/random access iterator/1024 elements buffer checking done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/random access iterator/10000 elements buffer checking next = " << next + 1 << " done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/random access iterator/100000 elements buffer checking next = " << next + 1 << " done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/random access iterator/1000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/random access iterator/10000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/random access iterator/100000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
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
            std::cout << "\t\ttest_constructor_4/random access iterator/Random sized elements " << size << " buffer checking next = " << next + 1 << " done." << std::endl;
            if(++next < 3) {
                goto RESTART_RANDOM_ACCESS_RANDOM;
            }
        }
        std::cout << "\tChecking bidirectional iterator version finished!" << std::endl;
    }

    std::cout << "Checking buffer(ForwardIterator, ForwardIterator, const Allocator &), size, empty and iterator finished!" << std::endl;
}
void buffer_correctness::test_constructor_5() {
    std::cout << "Start checking buffer(initializer_list<T>), size, empty and iterator!" << std::endl;
    const std::initializer_list<int> empty_list = {};
    const auto single_list = {42};
    const auto list = {-5, -2, 0, 1, 4, 6, 8, 111};

    // empty from initializer_list
    {
        buffer<int> b1(empty_list);
        assert(b1.size() == 0);
        assert(b1.empty());
        assert(b1.begin() == b1.end());

        buffer<int> b2({});
        assert(b2.size() == 0);
        assert(b2.empty());
        assert(b2.begin() == b2.end());
        std::cout << "\ttest_constructor_5/Empty buffer from initializer_list checking done." << std::endl;
    }

    // single element
    {
        buffer<int> b1 {42};
        assert(b1.size() == 1);
        assert(not b1.empty());
        assert(b1.begin() not_eq b1.end());
        assert(b1.begin() + 1 == b1.end());
        assert(*b1.begin() == 42);

        buffer<int> b2(single_list);
        assert(b2.size() == 1);
        assert(not b2.empty());
        assert(b2.begin() not_eq b2.end());
        assert(b2.begin() + 1 == b2.end());
        assert(*b2.begin() == 42);
        std::cout << "\ttest_constructor_5/Single element buffer checking done." << std::endl;
    }

    // other test
    {
        buffer<int> b(list);
        assert(b.size() == 8);
        assert(not b.empty());
        assert(b.begin() + 8 == b.end());
        for(auto i {0}; i < list.size(); ++i) {
            assert(*(b.begin() + i) == *(list.begin() + i));
        }
        std::cout << "\ttest_constructor_5/Buffer other test checking done." << std::endl;
    }

    std::cout << "Checking buffer(initializer_list<T>), size, empty and iterator finished!" << std::endl;
}
void buffer_correctness::test_release() {
    std::cout << "Start checking buffer::release!" << std::endl;

    // empty
    {
        buffer<int> b(int_input_iterator {}, {});
        auto p {b.release()};
        assert(b.empty());
        assert(b.size() == 0);
        std::cout << "\ttest_release/Empty buffer checking done." << std::endl;
    }

    // single element
    {
        buffer<int> b(1);
        auto p {b.release()};
        assert(b.empty());
        assert(b.size() == 1);
        assert(*p == 0);
        b.allocator().deallocate(p, b.size());
        std::cout << "\ttest_release/Single element buffer checking done." << std::endl;
    }

    // size == 10
    {
        buffer<int> b(10);
        auto p {b.release()};
        assert(b.empty());
        assert(b.size() == 10);
        for(auto i {0}; i < b.size(); ++i) {
            assert(p[i] == 0);
        }
        b.allocator().deallocate(p, b.size());
        std::cout << "\ttest_release/10 elements buffer checking done." << std::endl;
    }

    // size == 42
    {
        buffer<int> b(42);
        auto p {b.release()};
        assert(b.empty());
        assert(b.size() == 42);
        for(auto i {0}; i < b.size(); ++i) {
            assert(p[i] == 0);
        }
        b.allocator().deallocate(p, b.size());
        std::cout << "\ttest_release/42 elements buffer checking done." << std::endl;
    }

    // size == 64
    {
        buffer<int> b(64);
        auto p {b.release()};
        assert(b.empty());
        assert(b.size() == 64);
        for(auto i {0}; i < b.size(); ++i) {
            assert(p[i] == 0);
        }
        b.allocator().deallocate(p, b.size());
        std::cout << "\ttest_release/64 elements buffer checking done." << std::endl;
    }

    // size == 128
    {
        buffer<int> b(128);
        auto p {b.release()};
        assert(b.empty());
        assert(b.size() == 128);
        for(auto i {0}; i < b.size(); ++i) {
            assert(p[i] == 0);
        }
        b.allocator().deallocate(p, b.size());
        std::cout << "\ttest_release/128 elements buffer checking done." << std::endl;
    }

    // size == 1024
    {
        buffer<int> b(1024);
        auto p {b.release()};
        assert(b.empty());
        assert(b.size() == 1024);
        for(auto i {0}; i < b.size(); ++i) {
            assert(p[i] == 0);
        }
        b.allocator().deallocate(p, b.size());
        std::cout << "\ttest_release/1024 elements buffer checking done." << std::endl;
    }

    // size == 10000
    {
        int next {};
        RESTART_10000:
        buffer<int> b(10000);
        auto p {b.release()};
        assert(b.empty());
        assert(b.size() == 10000);
        for(auto i {0}; i < b.size(); ++i) {
            assert(p[i] == 0);
        }
        b.allocator().deallocate(p, b.size());
        std::cout << "\ttest_release/10000 elements buffer checking next = " << next + 1 << " done." << std::endl;
        if(++next < 100) {
            goto RESTART_10000;
        }
    }

    // size == 100000
    {
        int next {};
        RESTART_100000:
        buffer<int> b(100000);
        auto p {b.release()};
        assert(b.empty());
        assert(b.size() == 100000);
        for(auto i {0}; i < b.size(); ++i) {
            assert(p[i] == 0);
        }
        b.allocator().deallocate(p, b.size());
        std::cout << "\ttest_release/100000 elements buffer checking next = " << next + 1 << " done." << std::endl;
        if(++next < 50) {
            goto RESTART_100000;
        }
    }

    // size == 1000000
    {
        int next {};
        RESTART_1000000:
        buffer<int> b(1000000);
        auto p {b.release()};
        assert(b.empty());
        assert(b.size() == 1000000);
        for(auto i {0}; i < b.size(); ++i) {
            assert(p[i] == 0);
        }
        b.allocator().deallocate(p, b.size());
        std::cout << "\ttest_release/1000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
        if(++next < 10) {
            goto RESTART_1000000;
        }
    }

    // size == 10000000
    {
        int next {};
        RESTART_10000000:
        buffer<int> b(10000000);
        auto p {b.release()};
        assert(b.empty());
        assert(b.size() == 10000000);
        for(auto i {0}; i < b.size(); ++i) {
            assert(p[i] == 0);
        }
        b.allocator().deallocate(p, b.size());
        std::cout << "\ttest_release/10000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
        if(++next < 5) {
            goto RESTART_10000000;
        }
    }

    // size == 100000000
    {
        int next {};
        RESTART_100000000:
        buffer<int> b(100000000);
        auto p {b.release()};
        assert(b.empty());
        assert(b.size() == 100000000);
        for(auto i {0}; i < b.size(); ++i) {
            assert(p[i] == 0);
        }
        b.allocator().deallocate(p, b.size());
        std::cout << "\ttest_release/100000000 elements buffer checking next = " << next + 1 << " done." << std::endl;
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
        auto p {b.release()};
        assert(b.empty());
        assert(b.size() == size);
        for(auto i {0}; i < b.size(); ++i) {
            assert(p[i] == 0);
        }
        b.allocator().deallocate(p, b.size());
        std::cout << "\ttest_release/Random sized elements " << size << " buffer checking next = " << next + 1 << " done." << std::endl;
        if(++next < 3) {
            goto RESTART_RANDOM;
        }
    }

    std::cout << "Checking buffer::release finished!" << std::endl;
}
void buffer_correctness::test_move_iterator() {
    std::cout << "Start checking buffer's move iterator!" << std::endl;

    struct moveable {
        bool copy {};
        bool move {};
        moveable() noexcept = default;
        moveable(moveable &rhs) noexcept : copy {}, move {} {
            rhs.copy = true;
        }
        moveable(moveable &&rhs) noexcept : copy {}, move {} {
            rhs.move = true;
        }
        moveable &operator=(moveable &rhs) noexcept {
            rhs.copy = true;
            return *this;
        }
        moveable &operator=(moveable &&rhs) noexcept {
            rhs.move = true;
            return *this;
        }
    };

    buffer<moveable> b(this->generate_count());
    const auto end {b.mend()};
    for(auto it {b.mbegin()}; it not_eq end; ++it) {
        auto p {*it};
        const auto it_base {it.base()};
        assert(it_base->move and not it_base->copy);
    }

    std::cout << "Checking buffer's move iterator finished!" << std::endl;
}
void buffer_correctness::test_allocator() {
    std::cout << "Start checking buffer::allocator!" << std::endl;

    buffer<int> b {1, 2, 3};
    auto allocator {b.allocator()};
    static_assert(allocator == typename buffer<int>::allocator_type {});
    static_assert(allocator == typename buffer<char>::allocator_type {});

    std::cout << "Checking buffer::allocator finished!" << std::endl;
}
void buffer_correctness::test_non_trivial() {
    std::cout << "Start checking non trivial type std::string!" << std::endl;

    // buffer(size_type, const Allocator &)
    {
        int next {};
        RESTART_1:
        const auto size {this->generate_count(1000000)};
        buffer<std::string> b(size);
        assert(size == 0 ? b.empty() : not b.empty());
        assert(b.size() == size);
        assert(b.begin() + size == b.end());
        const auto end {b.end()};
        for(auto it {b.begin()}; it not_eq end; ++it) {
            assert(it->empty());
        }
        const auto mend {b.mend()};
        for(auto it {b.mbegin()}; it not_eq mend; ++it) {
            auto p {*it};
            const auto it_base {it.base()};
            assert(it_base->empty());
        }
        std::cout << "\ttest_non_trivial/buffer<std::string>(size_type, const Allocator &) next = " << next + 1 << " done." << std::endl;
        if(++next < 3) {
            goto RESTART_1;
        }
    }

    // buffer(size_type, const T &, const Allocator &)
    {
        int next {};
        RESTART_2:
        const auto size {this->generate_count(1000000)};
        std::string s {};
        for(auto i {0}; i < 1000; ++i) {
            s += "hello     ";
        }
        buffer<std::string> b(size, s);
        assert(size == 0 ? b.empty() : not b.empty());
        assert(b.size() == size);
        assert(b.begin() + size == b.end());
        const auto end {b.end()};
        for(auto it {b.begin()}; it not_eq end; ++it) {
            assert(*it == s);
        }
        const auto mend {b.mend()};
        for(auto it {b.mbegin()}; it not_eq mend; ++it) {
            auto p {*it};
            const auto it_base {it.base()};
            assert(it_base->empty());
        }
        std::cout << "\ttest_non_trivial/buffer<std::string>(size_type, const T &, const Allocator &) next = " << next + 1 << " done." << std::endl;
        if(++next < 3) {
            goto RESTART_2;
        }
    }

    // buffer(InputIterator, InputIterator, const Allocator &)
    {
        int next {};
        RESTART_3:
        const auto size {this->generate_count(1000000)};
        std::string s {};
        for(auto i {0}; i < 1000; ++i) {
            s += "hello";      // avoid SSO
        }
        auto stream {this->to_input_iterator(std::vector(size, s))};
        buffer<std::string> b(std_string_input_iterator {stream}, {});
        assert(size == 0 ? b.empty() : not b.empty());
        assert(b.size() == size);
        assert(b.begin() + size == b.end());
        const auto end {b.end()};
        for(auto it {b.begin()}; it not_eq end; ++it) {
            assert(*it == s);
        }
        const auto mend {b.mend()};
        for(auto it {b.mbegin()}; it not_eq mend; ++it) {
            auto p {*it};
            const auto it_base {it.base()};
            assert(it_base->empty());
        }
        std::cout << "\ttest_non_trivial/buffer<std::string>(InputIterator, InputIterator, const Allocator &) next = " << next + 1 << " done." << std::endl;
        if(++next < 3) {
            goto RESTART_3;
        }
    }

    // buffer(ForwardIterator, ForwardIterator, const Allocator &)
    {
        int next {};
        RESTART_4:
        const auto size {this->generate_count(1000000)};
        std::string s {};
        for(auto i {0}; i < 1000; ++i) {
            s += "hello";       // avoid SSO
        }
        auto d {this->to_random_access_iterator(std::vector(size, s))};
        buffer<std::string> b(std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()});
        assert(size == 0 ? b.empty() : not b.empty());
        assert(b.size() == size);
        assert(b.begin() + size == b.end());
        const auto end {b.end()};
        for(auto it {b.begin()}; it not_eq end; ++it) {
            assert(*it == s);
        }
        const auto mend {b.mend()};
        for(auto it {b.mbegin()}; it not_eq mend; ++it) {
            auto p {*it};
            const auto it_base {it.base()};
            assert(it_base->empty());
        }
        std::cout << "\ttest_non_trivial/buffer<std::string>(ForwardIterator, ForwardIterator, const Allocator &) next = " << next + 1 << " done." << std::endl;
        if(++next < 3) {
            goto RESTART_4;
        }
    }

    std::cout << "Checking non trivial type std::string finished!" << std::endl;
}