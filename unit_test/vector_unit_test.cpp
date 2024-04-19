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

void vector_unit_test() {
    auto correctness {new vector_correctness {}};
    correctness->test_default_constructor();
    correctness->test_constructor_1();
    delete correctness;
}

void vector_correctness::test_default_constructor() {
    std::cout << "Start checking default constructor for ds::vector!" << std::endl;

    // the members which should be nothrow
    {
        static_assert(noexcept(vector<int> {}));
        static_assert(noexcept(vector<int> {allocator<int> {}}));
        static_assert(noexcept(vector<int> {vector<int> {}}));
        static_assert(noexcept(vector<int> {vector<int> {}, allocator<int> {}}));
        static_assert(noexcept(vector<int> {} = vector<int> {}));
        static_assert(noexcept(vector<int> {}[0]));
        static_assert(noexcept((const vector<int>) {}[0]));
        static_assert(noexcept(vector<int> {}.begin()));
        static_assert(noexcept((const vector<int>) {}.begin()));
        static_assert(noexcept(vector<int> {}.end()));
        static_assert(noexcept((const vector<int>) {}.end()));
        static_assert(noexcept(vector<int> {}.rbegin()));
        static_assert(noexcept((const vector<int>) {}.rbegin()));
        static_assert(noexcept(vector<int> {}.rend()));
        static_assert(noexcept((const vector<int>) {}.rend()));
        static_assert(noexcept(vector<int> {}.cbegin()));
        static_assert(noexcept(vector<int> {}.cend()));
        static_assert(noexcept(vector<int> {}.crbegin()));
        static_assert(noexcept(vector<int> {}.crend()));
        static_assert(noexcept(vector<int> {}.size()));
        static_assert(noexcept(vector<int> {}.empty()));
        static_assert(noexcept(vector<int> {}.capacity()));
        static_assert(noexcept(vector<int> {}.spare()));
        static_assert(noexcept(vector<int> {}.front()));
        static_assert(noexcept((const vector<int>) {}.front()));
        static_assert(noexcept(vector<int> {}.back()));
        static_assert(noexcept((const vector<int>) {}.back()));
        static_assert(noexcept(vector<int> {}.data()));
        static_assert(noexcept((const vector<int>) {}.data()));
        static_assert(noexcept(vector<int> {}.allocator()));
        static_assert(noexcept(vector<int> {}.pop_back()));
        static_assert(noexcept(vector<int> {}.clear()));
        static_assert(noexcept(vector<int> {}.swap(declval<vector<int> &>())));
        std::cout << "\ttest_default_constructor/Member functions nothrow checking done." << std::endl;
    }

    // empty
    {
        vector<int> v {};
        assert(v.size() == 0);
        assert(v.empty());
        assert(v.capacity() == 0);
        assert(v.spare() == 0);
        assert(v.begin() == v.end());
        assert(v.cbegin() == v.cend());
        assert(v.rbegin() == v.rend());
        assert(v.crbegin() == v.crend());
        assert(v.data() == nullptr);
        std::cout << "\ttest_default_constructor/Empty vector checking done." << std::endl;
    }

    std::cout << "Checking default constructor for ds::vector finished!" << std::endl;
}

void vector_correctness::test_constructor_1() {
    std::cout << "Start checking vector(const Allocator &)!" << std::endl;

    // ds::allocator<int>
    {
        vector<int> v {allocator<int> {}};
        assert(v.size() == 0);
        assert(v.empty());
        assert(v.capacity() == 0);
        assert(v.spare() == 0);
        assert(v.begin() == v.end());
        assert(v.cbegin() == v.cend());
        assert(v.rbegin() == v.rend());
        assert(v.crbegin() == v.crend());
        assert(v.data() == nullptr);
        std::cout << "\ttest_default_constructor/Empty vector with ds::allocator<int> checking done." << std::endl;
    }

    // std::allocator<int>
    {
        vector<int, std::allocator<int>> v {std::allocator<int> {}};
        assert(v.size() == 0);
        assert(v.empty());
        assert(v.capacity() == 0);
        assert(v.spare() == 0);
        assert(v.begin() == v.end());
        assert(v.cbegin() == v.cend());
        assert(v.rbegin() == v.rend());
        assert(v.crbegin() == v.crend());
        assert(v.data() == nullptr);
        std::cout << "\ttest_default_constructor/Empty vector with std::allocator<int> checking done." << std::endl;
    }

    std::cout << "Checking vector(const Allocator &) finished!" << std::endl;
}

void vector_correctness::test_constructor_2() {
    std::cout << "Start checking vector(size_type, const Allocator &)!" << std::endl;

    // single element
    {
        vector<int> v(1);
        assert(v.size() == 1);
        assert(not v.empty());
        assert(v.begin() not_eq v.end());
        assert(v.begin() + 1 == v.end());
        assert(v.cbegin() not_eq v.cend());
        assert(v.cbegin() + 1 == v.cend());
        assert(v.cbegin() not_eq v.end());
        assert(v.cbegin() + 1 == v.end());
        assert(v.begin() not_eq v.cend());
        assert(v.begin() + 1 == v.cend());
        assert(*v.begin() == 0);
        std::cout << "\ttest_constructor_1/Single element vector checking done." << std::endl;
    }

    // size == 10
    {
        vector<int> v(10);
        assert(v.size() == 10);
        assert(not v.empty());
        assert(v.begin() + 10 == v.end());
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\ttest_constructor_1/10 elements vector checking done." << std::endl;
    }

    // size == 42
    {
        vector<int> v(42);
        assert(v.size() == 42);
        assert(not v.empty());
        assert(v.begin() + 42 == v.end());
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\ttest_constructor_1/42 elements vector checking done." << std::endl;
    }

    // size == 64
    {
        vector<int> v(64);
        assert(v.size() == 64);
        assert(not v.empty());
        assert(v.begin() + 64 == v.end());
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\ttest_constructor_1/64 elements vector checking done." << std::endl;
    }

    // size == 128
    {
        vector<int> v(128);
        assert(v.size() == 128);
        assert(not v.empty());
        assert(v.begin() + 128 == v.end());
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\ttest_constructor_1/128 elements vector checking done." << std::endl;
    }

    // size == 1024
    {
        vector<int> v(1024);
        assert(v.size() == 1024);
        assert(not v.empty());
        assert(v.begin() + 1024 == v.end());
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\ttest_constructor_1/1024 elements vector checking done." << std::endl;
    }

    // random size, size <= 10000
    {
        int next {};
        RESTART_10000:
        const auto size {this->generate_count(10000)};
        vector<int> v(size);
        assert(v.size() == size);
        assert(size == 0 ? v.empty() : not v.empty());
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\ttest_constructor_1/10000 elements vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 100) {
            goto RESTART_10000;
        }
    }

    // random size, size <= 100000
    {
        int next {};
        RESTART_100000:
        const auto size {this->generate_count(100000)};
        vector<int> v(size);
        assert(v.size() == size);
        assert(size == 0 ? v.empty() : not v.empty());
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\ttest_constructor_1/100000 elements vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 50) {
            goto RESTART_100000;
        }
    }

    // random size, size <= 1000000
    {
        int next {};
        RESTART_1000000:
        const auto size {this->generate_count(1000000)};
        vector<int> v(size);
        assert(v.size() == size);
        assert(size == 0 ? v.empty() : not v.empty());
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\ttest_constructor_1/1000000 elements vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 10) {
            goto RESTART_1000000;
        }
    }

    // random size, size <= 10000000
    {
        int next {};
        RESTART_10000000:
        const auto size {this->generate_count(10000000)};
        vector<int> v(size);
        assert(v.size() == size);
        assert(size == 0 ? v.empty() : not v.empty());
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\ttest_constructor_1/10000000 elements vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 5) {
            goto RESTART_10000000;
        }
    }

    // random size, size <= 100000000
    {
        int next {};
        RESTART_100000000:
        const auto size {this->generate_count(100000000)};
        vector<int> v(size);
        assert(v.size() == size);
        assert(size == 0 ? v.empty() : not v.empty());
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\ttest_constructor_1/100000000 elements vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 3) {
            goto RESTART_100000000;
        }
    }

    // random size
    {
        int next {};
        RESTART_RANDOM:
        const auto size {this->generate_count()};
        vector<int> v(size);
        assert(v.size() == size);
        assert(size == 0 ? v.empty() : not v.empty());
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\ttest_constructor_1/Random sized elements " << size << " vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 3) {
            goto RESTART_RANDOM;
        }
    }

    std::cout << "Checking vector(size_type, const Allocator &) finished!" << std::endl;
}