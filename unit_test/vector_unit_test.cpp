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
    // vector(size_type), size, empty, capacity, spare, front, back, data, index and iterator
    void test_constructor_2();
    // vector(size_type, const T &), size, empty, capacity, spare, front, back, data, index and iterator
    void test_constructor_3();
    // vector(InputIterator, InputIterator), size, empty, capacity, spare, front, back, data, index and iterator
    void test_constructor_4();
    // vector(ForwardIterator, ForwardIterator), size, empty, capacity, spare, front, back, data, index and iterator
    void test_constructor_5();
    // vector(initializer_list<T>), size, empty, capacity, spare, front, back, data, index and iterator
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
    void test_shrink_to_fit();
    // void resize(size_type)
    void test_resize_1();
    // void resize(size_type, const_reference)
    void test_resize_2();
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
    //correctness->test_default_constructor();
    //correctness->test_constructor_1();
    //correctness->test_constructor_2();
    //correctness->test_constructor_3();
    //correctness->test_constructor_4();
    //correctness->test_constructor_5();
    //correctness->test_constructor_6();
    //correctness->test_copy_constructor();
    //correctness->test_move_constructor();
    //correctness->test_copy_assignment();
    //correctness->test_move_assignment();
    //correctness->test_assign_1();
    //correctness->test_assign_2();
    //correctness->test_assign_3();
    //correctness->test_reserve();
    //correctness->test_shrink_to_fit();
    correctness->test_resize_1();
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
        assert(v.data() == nullptr);
        assert(v.begin() == v.end());
        assert(v.cbegin() == v.cend());
        assert(v.rbegin() == v.rend());
        assert(v.crbegin() == v.crend());
        std::cout << "\ttest_constructor_1/Empty vector with ds::allocator<int> checking done." << std::endl;
    }

    // std::allocator<int>
    {
        vector<int, std::allocator<int>> v {std::allocator<int> {}};
        assert(v.size() == 0);
        assert(v.empty());
        assert(v.capacity() == 0);
        assert(v.spare() == 0);
        assert(v.data() == nullptr);
        assert(v.begin() == v.end());
        assert(v.cbegin() == v.cend());
        assert(v.rbegin() == v.rend());
        assert(v.crbegin() == v.crend());
        std::cout << "\ttest_constructor_1/Empty vector with std::allocator<int> checking done." << std::endl;
    }

    std::cout << "Checking vector(const Allocator &) finished!" << std::endl;
}

void vector_correctness::test_constructor_2() {
    std::cout << "Start checking vector(size_type)!" << std::endl;

    // empty
    {
        vector<int> v(0);
        assert(v.size() == 0);
        assert(v.empty());
        assert(v.capacity() == 0);
        assert(v.spare() == 0);
        assert(v.begin() == v.end());
        assert(v.cbegin() == v.cend());
        assert(v.rbegin() == v.rend());
        assert(v.crbegin() == v.crend());
        assert(v.data() == nullptr);
        std::cout << "\ttest_default_constructor_2/Empty vector checking done." << std::endl;
    }

    // single element
    {
        vector<int> v(1);
        assert(v.size() == 1);
        assert(not v.empty());
        assert(v.capacity() == 1);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() not_eq v.end());
        assert(v.begin() + 1 == v.end());
        assert(v.cbegin() not_eq v.cend());
        assert(v.cbegin() + 1 == v.cend());
        assert(v.cbegin() not_eq v.end());
        assert(v.cbegin() + 1 == v.end());
        assert(v.begin() not_eq v.cend());
        assert(v.begin() + 1 == v.cend());
        assert(*v.begin() == 0);
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_constructor_2/Single element vector checking done." << std::endl;
    }

    // size == 10
    {
        vector<int> v(10);
        assert(v.size() == 10);
        assert(not v.empty());
        assert(v.capacity() == 10);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + 10 == v.end());
        assert(v.cbegin() + 10 == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_constructor_2/10 elements vector checking done." << std::endl;
    }

    // size == 42
    {
        vector<int> v(42);
        assert(v.size() == 42);
        assert(not v.empty());
        assert(v.capacity() == 42);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + 42 == v.end());
        assert(v.cbegin() + 42 == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_constructor_2/42 elements vector checking done." << std::endl;
    }

    // size == 64
    {
        vector<int> v(64);
        assert(v.size() == 64);
        assert(not v.empty());
        assert(v.capacity() == 64);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + 64 == v.end());
        assert(v.cbegin() + 64 == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_constructor_2/64 elements vector checking done." << std::endl;
    }

    // size == 128
    {
        vector<int> v(128);
        assert(v.size() == 128);
        assert(not v.empty());
        assert(v.capacity() == 128);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + 128 == v.end());
        assert(v.cbegin() + 128 == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_constructor_2/128 elements vector checking done." << std::endl;
    }

    // size == 1024
    {
        vector<int> v(1024);
        assert(v.size() == 1024);
        assert(not v.empty());
        assert(v.capacity() == 1024);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + 1024 == v.end());
        assert(v.cbegin() + 1024 == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_constructor_2/1024 elements vector checking done." << std::endl;
    }

    // random size, size <= 10000
    {
        int next {};
        RESTART_10000:
        const auto size {this->generate_count(10000)};
        vector<int> v(size);
        assert(v.size() == size);
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_constructor_2/10000 elements vector checking next = " << next + 1 << " done." << std::endl;
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
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_constructor_2/100000 elements vector checking next = " << next + 1 << " done." << std::endl;
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
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_constructor_2/1000000 elements vector checking next = " << next + 1 << " done." << std::endl;
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
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_constructor_2/10000000 elements vector checking next = " << next + 1 << " done." << std::endl;
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
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_constructor_2/100000000 elements vector checking next = " << next + 1 << " done." << std::endl;
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
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_constructor_2/Random sized elements " << size << " vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 3) {
            goto RESTART_RANDOM;
        }
    }

    std::cout << "Checking vector(size_type) finished!" << std::endl;
}
void vector_correctness::test_constructor_3() {
    std::cout << "Start checking vector(size_type, const T &)!" << std::endl;

    // empty
    {
        vector<int> v(0, this->generate_a_random_number());
        assert(v.size() == 0);
        assert(v.empty());
        assert(v.capacity() == 0);
        assert(v.spare() == 0);
        assert(v.begin() == v.end());
        assert(v.cbegin() == v.cend());
        assert(v.rbegin() == v.rend());
        assert(v.crbegin() == v.crend());
        assert(v.data() == nullptr);
        std::cout << "\ttest_constructor_3/Empty vector checking done." << std::endl;
    }

    // single element
    {
        auto e {this->generate_a_random_number()};
        vector<int> v(1, e);
        assert(v.size() == 1);
        assert(not v.empty());
        assert(v.capacity() == 1);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() not_eq v.end());
        assert(v.begin() + 1 == v.end());
        assert(v.cbegin() not_eq v.cend());
        assert(v.cbegin() + 1 == v.cend());
        assert(v.cbegin() not_eq v.end());
        assert(v.cbegin() + 1 == v.end());
        assert(v.begin() not_eq v.cend());
        assert(v.begin() + 1 == v.cend());
        assert(*v.begin() == e);
        assert(v.front() == e);
        assert(v.back() == e);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == e);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == e);
        }
        std::cout << "\ttest_constructor_3/Single element vector checking done." << std::endl;
    }

    // size == 10
    {
        auto e {this->generate_a_random_number()};
        vector<int> v(10, e);
        assert(v.size() == 10);
        assert(not v.empty());
        assert(v.capacity() == 10);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + 10 == v.end());
        assert(v.cbegin() + 10 == v.cend());
        assert(v.front() == e);
        assert(v.back() == e);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == e);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == e);
        }
        std::cout << "\ttest_constructor_3/10 elements vector checking done." << std::endl;
    }

    // size == 42
    {
        auto e {this->generate_a_random_number()};
        vector<int> v(42, e);
        assert(v.size() == 42);
        assert(not v.empty());
        assert(v.capacity() == 42);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + 42 == v.end());
        assert(v.cbegin() + 42 == v.cend());
        assert(v.front() == e);
        assert(v.back() == e);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == e);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == e);
        }
        std::cout << "\ttest_constructor_3/42 elements vector checking done." << std::endl;
    }

    // size == 64
    {
        auto e {this->generate_a_random_number()};
        vector<int> v(64, e);
        assert(v.size() == 64);
        assert(not v.empty());
        assert(v.capacity() == 64);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + 64 == v.end());
        assert(v.cbegin() + 64 == v.cend());
        assert(v.front() == e);
        assert(v.back() == e);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == e);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == e);
        }
        std::cout << "\ttest_constructor_3/64 elements vector checking done." << std::endl;
    }

    // size == 128
    {
        auto e {this->generate_a_random_number()};
        vector<int> v(128, e);
        assert(v.size() == 128);
        assert(not v.empty());
        assert(v.capacity() == 128);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + 128 == v.end());
        assert(v.cbegin() + 128 == v.cend());
        assert(v.front() == e);
        assert(v.back() == e);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == e);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == e);
        }
        std::cout << "\ttest_constructor_3/128 elements vector checking done." << std::endl;
    }

    // size == 1024
    {
        auto e {this->generate_a_random_number()};
        vector<int> v(1024, e);
        assert(v.size() == 1024);
        assert(not v.empty());
        assert(v.capacity() == 1024);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + 1024 == v.end());
        assert(v.cbegin() + 1024 == v.cend());
        assert(v.front() == e);
        assert(v.back() == e);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == e);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == e);
        }
        std::cout << "\ttest_constructor_3/1024 elements vector checking done." << std::endl;
    }

    // random size, size <= 10000
    {
        int next {};
        RESTART_10000:
        auto e {this->generate_a_random_number()};
        const auto size {this->generate_count(10000)};
        vector<int> v(size, e);
        assert(v.size() == size);
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == e);
        assert(v.back() == e);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == e);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == e);
        }
        std::cout << "\ttest_constructor_3/10000 elements vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 100) {
            goto RESTART_10000;
        }
    }

    // random size, size <= 100000
    {
        int next {};
        RESTART_100000:
        auto e {this->generate_a_random_number()};
        const auto size {this->generate_count(100000)};
        vector<int> v(size, e);
        assert(v.size() == size);
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == e);
        assert(v.back() == e);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == e);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == e);
        }
        std::cout << "\ttest_constructor_3/100000 elements vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 50) {
            goto RESTART_100000;
        }
    }

    // random size, size <= 1000000
    {
        int next {};
        RESTART_1000000:
        auto e {this->generate_a_random_number()};
        const auto size {this->generate_count(1000000)};
        vector<int> v(size, e);
        assert(v.size() == size);
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == e);
        assert(v.back() == e);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == e);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == e);
        }
        std::cout << "\ttest_constructor_3/1000000 elements vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 10) {
            goto RESTART_1000000;
        }
    }

    // random size, size <= 10000000
    {
        int next {};
        RESTART_10000000:
        auto e {this->generate_a_random_number()};
        const auto size {this->generate_count(10000000)};
        vector<int> v(size, e);
        assert(v.size() == size);
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == e);
        assert(v.back() == e);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == e);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == e);
        }
        std::cout << "\ttest_constructor_3/10000000 elements vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 5) {
            goto RESTART_10000000;
        }
    }

    // random size, size <= 100000000
    {
        int next {};
        RESTART_100000000:
        auto e {this->generate_a_random_number()};
        const auto size {this->generate_count(100000000)};
        vector<int> v(size, e);
        assert(v.size() == size);
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == e);
        assert(v.back() == e);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == e);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == e);
        }
        std::cout << "\ttest_constructor_3/100000000 elements vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 3) {
            goto RESTART_100000000;
        }
    }

    // random size
    {
        int next {};
        RESTART_RANDOM:
        auto e {this->generate_a_random_number()};
        const auto size {this->generate_count()};
        vector<int> v(size, e);
        assert(v.size() == size);
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == e);
        assert(v.back() == e);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == e);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == e);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == e);
        }
        std::cout << "\ttest_constructor_3/Random sized elements " << size << " vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 3) {
            goto RESTART_RANDOM;
        }
    }

    std::cout << "Checking vector(size_type, const T &) finished!" << std::endl;
}
void vector_correctness::test_constructor_4() {
    std::cout << "Start checking vector(InputIterator, InputIterator)!" << std::endl;

    // empty
    {
        vector<int> v(int_input_iterator {}, int_input_iterator {});
        assert(v.size() == 0);
        assert(v.empty());
        assert(v.capacity() == 0);
        assert(v.spare() == 0);
        assert(v.begin() == v.end());
        assert(v.cbegin() == v.cend());
        assert(v.rbegin() == v.rend());
        assert(v.crbegin() == v.crend());
        assert(v.data() == nullptr);
        std::cout << "\ttest_constructor_4/Empty buffer checking done." << std::endl;
    }

    // single element
    {
        std::stringstream stream("42");
        vector<int> v(int_input_iterator {stream}, {});
        assert(v.size() == 1);
        assert(not v.empty());
        assert(v.capacity() == 1);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() not_eq v.end());
        assert(v.begin() + 1 == v.end());
        assert(v.cbegin() not_eq v.cend());
        assert(v.cbegin() + 1 == v.cend());
        assert(v.cbegin() not_eq v.end());
        assert(v.cbegin() + 1 == v.end());
        assert(v.begin() not_eq v.cend());
        assert(v.begin() + 1 == v.cend());
        assert(*v.begin() == 42);
        assert(v.front() == 42);
        assert(v.back() == 42);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 42);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 42);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 42);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 42);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 42);
        }
        std::cout << "\ttest_constructor_4/Single element vector checking done." << std::endl;
    }

    // size == 10
    {
        const auto numbers {this->generate_number(10)};
        auto stream {this->to_input_iterator(numbers)};
        vector<int> v(int_input_iterator {stream}, {});
        assert(v.size() == 10);
        assert(not v.empty());
        assert(v.capacity() == 10);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() not_eq v.end());
        assert(v.begin() + 10 == v.end());
        assert(v.cbegin() not_eq v.cend());
        assert(v.cbegin() + 10 == v.cend());
        assert(v.cbegin() not_eq v.end());
        assert(v.cbegin() + 10 == v.end());
        assert(v.begin() not_eq v.cend());
        assert(v.begin() + 10 == v.cend());
        assert(*v.begin() == *numbers.begin());
        assert(v.front() == numbers.front());
        assert(v.back() == numbers.back());
        auto numbers_i {0uz};
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        numbers_i = 0;
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        numbers_i = numbers.size() - 1;
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == numbers[numbers_i--]);
        }
        numbers_i = numbers.size() - 1;
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == numbers[numbers_i--]);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == numbers[i]);
        }
        std::cout << "\ttest_constructor_4/10 elements vector checking done." << std::endl;
    }

    // size == 42
    {
        const auto numbers {this->generate_number(42)};
        auto stream {this->to_input_iterator(numbers)};
        vector<int> v(int_input_iterator {stream}, {});
        assert(v.size() == 42);
        assert(not v.empty());
        assert(v.capacity() == 42);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() not_eq v.end());
        assert(v.begin() + 42 == v.end());
        assert(v.cbegin() not_eq v.cend());
        assert(v.cbegin() + 42 == v.cend());
        assert(v.cbegin() not_eq v.end());
        assert(v.cbegin() + 42 == v.end());
        assert(v.begin() not_eq v.cend());
        assert(v.begin() + 42 == v.cend());
        assert(*v.begin() == *numbers.begin());
        assert(v.front() == numbers.front());
        assert(v.back() == numbers.back());
        auto numbers_i {0uz};
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        numbers_i = 0;
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        numbers_i = numbers.size() - 1;
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == numbers[numbers_i--]);
        }
        numbers_i = numbers.size() - 1;
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == numbers[numbers_i--]);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == numbers[i]);
        }
        std::cout << "\ttest_constructor_4/42 elements vector checking done." << std::endl;
    }

    // size == 64
    {
        const auto numbers {this->generate_number(64)};
        auto stream {this->to_input_iterator(numbers)};
        vector<int> v(int_input_iterator {stream}, {});
        assert(v.size() == 64);
        assert(not v.empty());
        assert(v.capacity() == 64);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() not_eq v.end());
        assert(v.begin() + 64 == v.end());
        assert(v.cbegin() not_eq v.cend());
        assert(v.cbegin() + 64 == v.cend());
        assert(v.cbegin() not_eq v.end());
        assert(v.cbegin() + 64 == v.end());
        assert(v.begin() not_eq v.cend());
        assert(v.begin() + 64 == v.cend());
        assert(*v.begin() == *numbers.begin());
        assert(v.front() == numbers.front());
        assert(v.back() == numbers.back());
        auto numbers_i {0uz};
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        numbers_i = 0;
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        numbers_i = numbers.size() - 1;
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == numbers[numbers_i--]);
        }
        numbers_i = numbers.size() - 1;
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == numbers[numbers_i--]);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == numbers[i]);
        }
        std::cout << "\ttest_constructor_4/64 elements vector checking done." << std::endl;
    }

    // size == 128
    {
        const auto numbers {this->generate_number(128)};
        auto stream {this->to_input_iterator(numbers)};
        vector<int> v(int_input_iterator {stream}, {});
        assert(v.size() == 128);
        assert(not v.empty());
        assert(v.capacity() == 128);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() not_eq v.end());
        assert(v.begin() + 128 == v.end());
        assert(v.cbegin() not_eq v.cend());
        assert(v.cbegin() + 128 == v.cend());
        assert(v.cbegin() not_eq v.end());
        assert(v.cbegin() + 128 == v.end());
        assert(v.begin() not_eq v.cend());
        assert(v.begin() + 128 == v.cend());
        assert(*v.begin() == *numbers.begin());
        assert(v.front() == numbers.front());
        assert(v.back() == numbers.back());
        auto numbers_i {0uz};
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        numbers_i = 0;
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        numbers_i = numbers.size() - 1;
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == numbers[numbers_i--]);
        }
        numbers_i = numbers.size() - 1;
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == numbers[numbers_i--]);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == numbers[i]);
        }
        std::cout << "\ttest_constructor_4/128 elements vector checking done." << std::endl;
    }

    // size == 1024
    {
        const auto numbers {this->generate_number(1024)};
        auto stream {this->to_input_iterator(numbers)};
        vector<int> v(int_input_iterator {stream}, {});
        assert(v.size() == 1024);
        assert(not v.empty());
        assert(v.capacity() == 1024);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() not_eq v.end());
        assert(v.begin() + 1024 == v.end());
        assert(v.cbegin() not_eq v.cend());
        assert(v.cbegin() + 1024 == v.cend());
        assert(v.cbegin() not_eq v.end());
        assert(v.cbegin() + 1024 == v.end());
        assert(v.begin() not_eq v.cend());
        assert(v.begin() + 1024 == v.cend());
        assert(*v.begin() == *numbers.begin());
        assert(v.front() == numbers.front());
        assert(v.back() == numbers.back());
        auto numbers_i {0uz};
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        numbers_i = 0;
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        numbers_i = numbers.size() - 1;
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == numbers[numbers_i--]);
        }
        numbers_i = numbers.size() - 1;
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == numbers[numbers_i--]);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == numbers[i]);
        }
        std::cout << "\ttest_constructor_4/1024 elements vector checking done." << std::endl;
    }

    // size == 10000
    {
        int next {};
        RESTART_10000:
        const auto numbers {this->generate_number(10000)};
        auto stream {this->to_input_iterator(numbers)};
        vector<int> v(int_input_iterator {stream}, {});
        assert(v.size() == 10000);
        assert(not v.empty());
        assert(v.capacity() == 10000);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() not_eq v.end());
        assert(v.begin() + 10000 == v.end());
        assert(v.cbegin() not_eq v.cend());
        assert(v.cbegin() + 10000 == v.cend());
        assert(v.cbegin() not_eq v.end());
        assert(v.cbegin() + 10000 == v.end());
        assert(v.begin() not_eq v.cend());
        assert(v.begin() + 10000 == v.cend());
        assert(*v.begin() == *numbers.begin());
        assert(v.front() == numbers.front());
        assert(v.back() == numbers.back());
        auto numbers_i {0uz};
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        numbers_i = 0;
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        numbers_i = numbers.size() - 1;
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == numbers[numbers_i--]);
        }
        numbers_i = numbers.size() - 1;
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == numbers[numbers_i--]);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == numbers[i]);
        }
        std::cout << "\ttest_constructor_4/10000 elements vector checking next = " << next + 1 << " done." << std::endl;
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
        vector<int> v(int_input_iterator {stream}, {});
        assert(v.size() == 100000);
        assert(not v.empty());
        assert(v.capacity() == 100000);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() not_eq v.end());
        assert(v.begin() + 100000 == v.end());
        assert(v.cbegin() not_eq v.cend());
        assert(v.cbegin() + 100000 == v.cend());
        assert(v.cbegin() not_eq v.end());
        assert(v.cbegin() + 100000 == v.end());
        assert(v.begin() not_eq v.cend());
        assert(v.begin() + 100000 == v.cend());
        assert(*v.begin() == *numbers.begin());
        assert(v.front() == numbers.front());
        assert(v.back() == numbers.back());
        auto numbers_i {0uz};
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        numbers_i = 0;
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        numbers_i = numbers.size() - 1;
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == numbers[numbers_i--]);
        }
        numbers_i = numbers.size() - 1;
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == numbers[numbers_i--]);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == numbers[i]);
        }
        std::cout << "\ttest_constructor_4/100000 elements vector checking next = " << next + 1 << " done." << std::endl;
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
        vector<int> v(int_input_iterator {stream}, {});
        assert(v.size() == 1000000);
        assert(not v.empty());
        assert(v.capacity() == 1000000);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() not_eq v.end());
        assert(v.begin() + 1000000 == v.end());
        assert(v.cbegin() not_eq v.cend());
        assert(v.cbegin() + 1000000 == v.cend());
        assert(v.cbegin() not_eq v.end());
        assert(v.cbegin() + 1000000 == v.end());
        assert(v.begin() not_eq v.cend());
        assert(v.begin() + 1000000 == v.cend());
        assert(*v.begin() == *numbers.begin());
        assert(v.front() == numbers.front());
        assert(v.back() == numbers.back());
        auto numbers_i {0uz};
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        numbers_i = 0;
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        numbers_i = numbers.size() - 1;
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == numbers[numbers_i--]);
        }
        numbers_i = numbers.size() - 1;
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == numbers[numbers_i--]);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == numbers[i]);
        }
        std::cout << "\ttest_constructor_4/1000000 elements vector checking next = " << next + 1 << " done." << std::endl;
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
        vector<int> v(int_input_iterator {stream}, {});
        assert(v.size() == 10000000);
        assert(not v.empty());
        assert(v.capacity() == 10000000);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() not_eq v.end());
        assert(v.begin() + 10000000 == v.end());
        assert(v.cbegin() not_eq v.cend());
        assert(v.cbegin() + 10000000 == v.cend());
        assert(v.cbegin() not_eq v.end());
        assert(v.cbegin() + 10000000 == v.end());
        assert(v.begin() not_eq v.cend());
        assert(v.begin() + 10000000 == v.cend());
        assert(*v.begin() == *numbers.begin());
        assert(v.front() == numbers.front());
        assert(v.back() == numbers.back());
        auto numbers_i {0uz};
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        numbers_i = 0;
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        numbers_i = numbers.size() - 1;
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == numbers[numbers_i--]);
        }
        numbers_i = numbers.size() - 1;
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == numbers[numbers_i--]);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == numbers[i]);
        }
        std::cout << "\ttest_constructor_4/10000000 elements vector checking next = " << next + 1 << " done." << std::endl;
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
        vector<int> v(int_input_iterator {stream}, {});
        assert(v.size() == 100000000);
        assert(not v.empty());
        assert(v.capacity() == 100000000);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() not_eq v.end());
        assert(v.begin() + 100000000 == v.end());
        assert(v.cbegin() not_eq v.cend());
        assert(v.cbegin() + 100000000 == v.cend());
        assert(v.cbegin() not_eq v.end());
        assert(v.cbegin() + 100000000 == v.end());
        assert(v.begin() not_eq v.cend());
        assert(v.begin() + 100000000 == v.cend());
        assert(*v.begin() == *numbers.begin());
        assert(v.front() == numbers.front());
        assert(v.back() == numbers.back());
        auto numbers_i {0uz};
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        numbers_i = 0;
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        numbers_i = numbers.size() - 1;
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == numbers[numbers_i--]);
        }
        numbers_i = numbers.size() - 1;
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == numbers[numbers_i--]);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == numbers[i]);
        }
        std::cout << "\ttest_constructor_4/100000000 elements vector checking next = " << next + 1 << " done." << std::endl;
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
        vector<int> v(int_input_iterator {stream}, {});
        assert(v.size() == size);
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() not_eq v.end());
        assert(v.begin() + size == v.end());
        assert(v.cbegin() not_eq v.cend());
        assert(v.cbegin() + size == v.cend());
        assert(v.cbegin() not_eq v.end());
        assert(v.cbegin() + size == v.end());
        assert(v.begin() not_eq v.cend());
        assert(v.begin() + size == v.cend());
        assert(*v.begin() == *numbers.begin());
        assert(v.front() == numbers.front());
        assert(v.back() == numbers.back());
        auto numbers_i {0uz};
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        numbers_i = 0;
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        numbers_i = numbers.size() - 1;
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == numbers[numbers_i--]);
        }
        numbers_i = numbers.size() - 1;
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == numbers[numbers_i--]);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == numbers[i]);
        }
        std::cout << "\ttest_constructor_4/Random sized elements " << size << " vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 3) {
            goto RESTART_RANDOM;
        }
    }

    std::cout << "Checking buffer(InputIterator, InputIterator), size, empty and iterator finished!" << std::endl;
}
void vector_correctness::test_constructor_5() {
    std::cout << "Start checking vector(ForwardIterator, ForwardIterator)!" << std::endl;

    // forward iterator
    {
        std::cout << "\tStart checking forward_iterator version!" << std::endl;
        // empty
        {
            vector<int> v(int_forward_iterator {}, {});
            assert(v.size() == 0);
            assert(v.empty());
            assert(v.capacity() == 0);
            assert(v.spare() == 0);
            assert(v.begin() == v.end());
            assert(v.cbegin() == v.cend());
            assert(v.rbegin() == v.rend());
            assert(v.crbegin() == v.crend());
            assert(v.data() == nullptr);
            std::cout << "\t\ttest_constructor_5/forward iterator/Empty vector checking done." << std::endl;
        }

        // single element
        {
            std::forward_list<int> l {42};
            vector<int> v(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
            assert(v.size() == 1);
            assert(not v.empty());
            assert(v.capacity() == 1);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + 1 == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + 1 == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + 1 == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + 1 == v.cend());
            assert(*v.begin() == 42);
            assert(v.front() == 42);
            assert(v.back() == 42);
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == 42);
            }
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == 42);
            }
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == 42);
            }
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == 42);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == 42);
            }
            std::cout << "\t\ttest_constructor_5/forward iterator/Single element vector checking done." << std::endl;
        }

        // size == 10
        {
            const auto numbers {this->generate_number(10)};
            auto l {this->to_forward_iterator(numbers)};
            vector<int> v(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
            assert(v.size() == 10);
            assert(not v.empty());
            assert(v.capacity() == 10);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + 10 == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + 10 == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + 10 == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + 10 == v.cend());
            assert(*v.begin() == *numbers.begin());
            assert(v.front() == numbers.front());
            assert(v.back() == numbers.back());
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[i]);
            }
            std::cout << "\t\ttest_constructor_5/forward iterator/10 elements vector checking done." << std::endl;
        }

        // size == 42
        {
            const auto numbers {this->generate_number(42)};
            auto l {this->to_forward_iterator(numbers)};
            vector<int> v(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
            assert(v.size() == 42);
            assert(not v.empty());
            assert(v.capacity() == 42);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + 42 == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + 42 == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + 42 == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + 42 == v.cend());
            assert(*v.begin() == *numbers.begin());
            assert(v.front() == numbers.front());
            assert(v.back() == numbers.back());
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[i]);
            }
            std::cout << "\t\ttest_constructor_5/forward iterator/42 elements vector checking done." << std::endl;
        }

        // size == 64
        {
            const auto numbers {this->generate_number(64)};
            auto l {this->to_forward_iterator(numbers)};
            vector<int> v(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
            assert(v.size() == 64);
            assert(not v.empty());
            assert(v.capacity() == 64);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + 64 == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + 64 == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + 64 == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + 64 == v.cend());
            assert(*v.begin() == *numbers.begin());
            assert(v.front() == numbers.front());
            assert(v.back() == numbers.back());
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[i]);
            }
            std::cout << "\t\ttest_constructor_5/forward iterator/64 elements vector checking done." << std::endl;
        }

        // size == 128
        {
            const auto numbers {this->generate_number(128)};
            auto l {this->to_forward_iterator(numbers)};
            vector<int> v(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
            assert(v.size() == 128);
            assert(not v.empty());
            assert(v.capacity() == 128);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + 128 == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + 128 == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + 128 == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + 128 == v.cend());
            assert(*v.begin() == *numbers.begin());
            assert(v.front() == numbers.front());
            assert(v.back() == numbers.back());
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[i]);
            }
            std::cout << "\t\ttest_constructor_5/forward iterator/128 elements vector checking done." << std::endl;
        }

        // size == 1024
        {
            const auto numbers {this->generate_number(1024)};
            auto l {this->to_forward_iterator(numbers)};
            vector<int> v(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
            assert(v.size() == 1024);
            assert(not v.empty());
            assert(v.capacity() == 1024);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + 1024 == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + 1024 == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + 1024 == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + 1024 == v.cend());
            assert(*v.begin() == *numbers.begin());
            assert(v.front() == numbers.front());
            assert(v.back() == numbers.back());
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[i]);
            }
            std::cout << "\t\ttest_constructor_5/forward iterator/1024 elements vector checking done." << std::endl;
        }

        // size == 10000
        {
            int next {};
            RESTART_FORWARD_10000:
            const auto numbers {this->generate_number(10000)};
            auto l {this->to_forward_iterator(numbers)};
            vector<int> v(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
            assert(v.size() == 10000);
            assert(not v.empty());
            assert(v.capacity() == 10000);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + 10000 == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + 10000 == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + 10000 == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + 10000 == v.cend());
            assert(*v.begin() == *numbers.begin());
            assert(v.front() == numbers.front());
            assert(v.back() == numbers.back());
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[i]);
            }
            std::cout << "\t\ttest_constructor_5/forward iterator/10000 elements vector checking next = " << next + 1 << " done." << std::endl;
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
            vector<int> v(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
            assert(v.size() == 100000);
            assert(not v.empty());
            assert(v.capacity() == 100000);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + 100000 == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + 100000 == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + 100000 == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + 100000 == v.cend());
            assert(*v.begin() == *numbers.begin());
            assert(v.front() == numbers.front());
            assert(v.back() == numbers.back());
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[i]);
            }
            std::cout << "\t\ttest_constructor_5/forward iterator/100000 elements vector checking next = " << next + 1 << " done." << std::endl;
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
            vector<int> v(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
            assert(v.size() == 1000000);
            assert(not v.empty());
            assert(v.capacity() == 1000000);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + 1000000 == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + 1000000 == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + 1000000 == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + 1000000 == v.cend());
            assert(*v.begin() == *numbers.begin());
            assert(v.front() == numbers.front());
            assert(v.back() == numbers.back());
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[i]);
            }
            std::cout << "\t\ttest_constructor_5/forward iterator/1000000 elements vector checking next = " << next + 1 << " done." << std::endl;
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
            vector<int> v(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
            assert(v.size() == 10000000);
            assert(not v.empty());
            assert(v.capacity() == 10000000);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + 10000000 == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + 10000000 == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + 10000000 == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + 10000000 == v.cend());
            assert(*v.begin() == *numbers.begin());
            assert(v.front() == numbers.front());
            assert(v.back() == numbers.back());
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[i]);
            }
            std::cout << "\t\ttest_constructor_5/forward iterator/10000000 elements vector checking next = " << next + 1 << " done." << std::endl;
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
            vector<int> v(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
            assert(v.size() == 100000000);
            assert(not v.empty());
            assert(v.capacity() == 100000000);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + 100000000 == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + 100000000 == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + 100000000 == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + 100000000 == v.cend());
            assert(*v.begin() == *numbers.begin());
            assert(v.front() == numbers.front());
            assert(v.back() == numbers.back());
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[i]);
            }
            std::cout << "\t\ttest_constructor_5/forward iterator/100000000 elements vector checking next = " << next + 1 << " done." << std::endl;
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
            vector<int> v(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
            assert(v.size() == size);
            assert(not v.empty());
            assert(v.capacity() == size);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + size == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + size == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + size == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + size == v.cend());
            assert(*v.begin() == *numbers.begin());
            assert(v.front() == numbers.front());
            assert(v.back() == numbers.back());
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[i]);
            }
            std::cout << "\t\ttest_constructor_5/forward iterator/Random sized elements " << size << " vector checking next = " << next + 1 << " done." << std::endl;
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
            vector<int> v(int_bidirectional_iterator {}, {});
            assert(v.size() == 0);
            assert(v.empty());
            assert(v.capacity() == 0);
            assert(v.spare() == 0);
            assert(v.begin() == v.end());
            assert(v.cbegin() == v.cend());
            assert(v.rbegin() == v.rend());
            assert(v.crbegin() == v.crend());
            assert(v.data() == nullptr);
            std::cout << "\t\ttest_constructor_5/bidirectional iterator/Empty vector checking done." << std::endl;
        }

        // single element
        {
            std::list<int> l {42};
            vector<int> v(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
            assert(v.size() == 1);
            assert(not v.empty());
            assert(v.capacity() == 1);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + 1 == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + 1 == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + 1 == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + 1 == v.cend());
            assert(*v.begin() == 42);
            assert(v.front() == 42);
            assert(v.back() == 42);
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == 42);
            }
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == 42);
            }
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == 42);
            }
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == 42);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == 42);
            }
            std::cout << "\t\ttest_constructor_5/bidirectional iterator/Single element vector checking done." << std::endl;
        }

        // size == 10
        {
            const auto numbers {this->generate_number(10)};
            auto l {this->to_bidirectional_iterator(numbers)};
            vector<int> v(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
            assert(v.size() == 10);
            assert(not v.empty());
            assert(v.capacity() == 10);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + 10 == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + 10 == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + 10 == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + 10 == v.cend());
            assert(*v.begin() == *numbers.begin());
            assert(v.front() == numbers.front());
            assert(v.back() == numbers.back());
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[i]);
            }
            std::cout << "\t\ttest_constructor_5/bidirectional iterator/10 elements vector checking done." << std::endl;
        }

        // size == 42
        {
            const auto numbers {this->generate_number(42)};
            auto l {this->to_bidirectional_iterator(numbers)};
            vector<int> v(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
            assert(v.size() == 42);
            assert(not v.empty());
            assert(v.capacity() == 42);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + 42 == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + 42 == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + 42 == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + 42 == v.cend());
            assert(*v.begin() == *numbers.begin());
            assert(v.front() == numbers.front());
            assert(v.back() == numbers.back());
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[i]);
            }
            std::cout << "\t\ttest_constructor_5/bidirectional iterator/42 elements vector checking done." << std::endl;
        }

        // size == 64
        {
            const auto numbers {this->generate_number(64)};
            auto l {this->to_bidirectional_iterator(numbers)};
            vector<int> v(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
            assert(v.size() == 64);
            assert(not v.empty());
            assert(v.capacity() == 64);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + 64 == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + 64 == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + 64 == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + 64 == v.cend());
            assert(*v.begin() == *numbers.begin());
            assert(v.front() == numbers.front());
            assert(v.back() == numbers.back());
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[i]);
            }
            std::cout << "\t\ttest_constructor_5/bidirectional iterator/64 elements vector checking done." << std::endl;
        }

        // size == 128
        {
            const auto numbers {this->generate_number(128)};
            auto l {this->to_bidirectional_iterator(numbers)};
            vector<int> v(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
            assert(v.size() == 128);
            assert(not v.empty());
            assert(v.capacity() == 128);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + 128 == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + 128 == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + 128 == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + 128 == v.cend());
            assert(*v.begin() == *numbers.begin());
            assert(v.front() == numbers.front());
            assert(v.back() == numbers.back());
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[i]);
            }
            std::cout << "\t\ttest_constructor_5/bidirectional iterator/128 elements vector checking done." << std::endl;
        }

        // size == 1024
        {
            const auto numbers {this->generate_number(1024)};
            auto l {this->to_bidirectional_iterator(numbers)};
            vector<int> v(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
            assert(v.size() == 1024);
            assert(not v.empty());
            assert(v.capacity() == 1024);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + 1024 == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + 1024 == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + 1024 == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + 1024 == v.cend());
            assert(*v.begin() == *numbers.begin());
            assert(v.front() == numbers.front());
            assert(v.back() == numbers.back());
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[i]);
            }
            std::cout << "\t\ttest_constructor_5/bidirectional iterator/1024 elements vector checking done." << std::endl;
        }

        // size == 10000
        {
            int next {};
            RESTART_BIDIRECTIONAL_10000:
            const auto numbers {this->generate_number(10000)};
            auto l {this->to_bidirectional_iterator(numbers)};
            vector<int> v(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
            assert(v.size() == 10000);
            assert(not v.empty());
            assert(v.capacity() == 10000);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + 10000 == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + 10000 == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + 10000 == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + 10000 == v.cend());
            assert(*v.begin() == *numbers.begin());
            assert(v.front() == numbers.front());
            assert(v.back() == numbers.back());
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[i]);
            }
            std::cout << "\t\ttest_constructor_5/bidirectional iterator/10000 elements vector checking next = " << next + 1 << " done." << std::endl;
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
            vector<int> v(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
            assert(v.size() == 100000);
            assert(not v.empty());
            assert(v.capacity() == 100000);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + 100000 == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + 100000 == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + 100000 == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + 100000 == v.cend());
            assert(*v.begin() == *numbers.begin());
            assert(v.front() == numbers.front());
            assert(v.back() == numbers.back());
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[i]);
            }
            std::cout << "\t\ttest_constructor_5/bidirectional iterator/100000 elements vector checking next = " << next + 1 << " done." << std::endl;
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
            vector<int> v(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
            assert(v.size() == 1000000);
            assert(not v.empty());
            assert(v.capacity() == 1000000);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + 1000000 == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + 1000000 == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + 1000000 == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + 1000000 == v.cend());
            assert(*v.begin() == *numbers.begin());
            assert(v.front() == numbers.front());
            assert(v.back() == numbers.back());
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[i]);
            }
            std::cout << "\t\ttest_constructor_5/bidirectional iterator/1000000 elements vector checking next = " << next + 1 << " done." << std::endl;
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
            vector<int> v(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
            assert(v.size() == 10000000);
            assert(not v.empty());
            assert(v.capacity() == 10000000);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + 10000000 == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + 10000000 == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + 10000000 == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + 10000000 == v.cend());
            assert(*v.begin() == *numbers.begin());
            assert(v.front() == numbers.front());
            assert(v.back() == numbers.back());
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[i]);
            }
            std::cout << "\t\ttest_constructor_5/bidirectional iterator/10000000 elements vector checking next = " << next + 1 << " done." << std::endl;
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
            vector<int> v(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
            assert(v.size() == 100000000);
            assert(not v.empty());
            assert(v.capacity() == 100000000);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + 100000000 == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + 100000000 == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + 100000000 == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + 100000000 == v.cend());
            assert(*v.begin() == *numbers.begin());
            assert(v.front() == numbers.front());
            assert(v.back() == numbers.back());
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[i]);
            }
            std::cout << "\t\ttest_constructor_5/bidirectional iterator/100000000 elements vector checking next = " << next + 1 << " done." << std::endl;
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
            vector<int> v(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
            assert(v.size() == size);
            assert(not v.empty());
            assert(v.capacity() == size);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + size == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + size == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + size == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + size == v.cend());
            assert(*v.begin() == *numbers.begin());
            assert(v.front() == numbers.front());
            assert(v.back() == numbers.back());
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[i]);
            }
            std::cout << "\t\ttest_constructor_5/bidirectional iterator/Random sized elements " << size << " vector checking next = " << next + 1 << " done." << std::endl;
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
            vector<int> v(int_random_access_iterator {}, {});
            assert(v.size() == 0);
            assert(v.empty());
            assert(v.capacity() == 0);
            assert(v.spare() == 0);
            assert(v.begin() == v.end());
            assert(v.cbegin() == v.cend());
            assert(v.rbegin() == v.rend());
            assert(v.crbegin() == v.crend());
            assert(v.data() == nullptr);
            std::cout << "\t\ttest_constructor_5/random access iterator/Empty vector checking done." << std::endl;
        }

        // single element
        {
            std::deque<int> d {42};
            vector<int> v(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
            assert(v.size() == 1);
            assert(not v.empty());
            assert(v.capacity() == 1);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + 1 == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + 1 == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + 1 == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + 1 == v.cend());
            assert(*v.begin() == 42);
            assert(v.front() == 42);
            assert(v.back() == 42);
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == 42);
            }
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == 42);
            }
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == 42);
            }
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == 42);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == 42);
            }
            std::cout << "\t\ttest_constructor_5/random access iterator/Single element vector checking done." << std::endl;
        }

        // size == 10
        {
            const auto numbers {this->generate_number(10)};
            auto d {this->to_random_access_iterator(numbers)};
            vector<int> v(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
            assert(v.size() == 10);
            assert(not v.empty());
            assert(v.capacity() == 10);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + 10 == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + 10 == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + 10 == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + 10 == v.cend());
            assert(*v.begin() == *numbers.begin());
            assert(v.front() == numbers.front());
            assert(v.back() == numbers.back());
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[i]);
            }
            std::cout << "\t\ttest_constructor_5/random access iterator/10 elements vector checking done." << std::endl;
        }

        // size == 42
        {
            const auto numbers {this->generate_number(42)};
            auto d {this->to_random_access_iterator(numbers)};
            vector<int> v(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
            assert(v.size() == 42);
            assert(not v.empty());
            assert(v.capacity() == 42);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + 42 == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + 42 == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + 42 == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + 42 == v.cend());
            assert(*v.begin() == *numbers.begin());
            assert(v.front() == numbers.front());
            assert(v.back() == numbers.back());
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[i]);
            }
            std::cout << "\t\ttest_constructor_5/random access iterator/42 elements vector checking done." << std::endl;
        }

        // size == 64
        {
            const auto numbers {this->generate_number(64)};
            auto d {this->to_random_access_iterator(numbers)};
            vector<int> v(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
            assert(v.size() == 64);
            assert(not v.empty());
            assert(v.capacity() == 64);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + 64 == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + 64 == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + 64 == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + 64 == v.cend());
            assert(*v.begin() == *numbers.begin());
            assert(v.front() == numbers.front());
            assert(v.back() == numbers.back());
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[i]);
            }
            std::cout << "\t\ttest_constructor_5/random access iterator/64 elements vector checking done." << std::endl;
        }

        // size == 128
        {
            const auto numbers {this->generate_number(128)};
            auto d {this->to_random_access_iterator(numbers)};
            vector<int> v(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
            assert(v.size() == 128);
            assert(not v.empty());
            assert(v.capacity() == 128);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + 128 == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + 128 == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + 128 == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + 128 == v.cend());
            assert(*v.begin() == *numbers.begin());
            assert(v.front() == numbers.front());
            assert(v.back() == numbers.back());
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[i]);
            }
            std::cout << "\t\ttest_constructor_5/random access iterator/128 elements vector checking done." << std::endl;
        }

        // size == 1024
        {
            const auto numbers {this->generate_number(1024)};
            auto d {this->to_random_access_iterator(numbers)};
            vector<int> v(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
            assert(v.size() == 1024);
            assert(not v.empty());
            assert(v.capacity() == 1024);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + 1024 == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + 1024 == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + 1024 == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + 1024 == v.cend());
            assert(*v.begin() == *numbers.begin());
            assert(v.front() == numbers.front());
            assert(v.back() == numbers.back());
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[i]);
            }
            std::cout << "\t\ttest_constructor_5/random access iterator/1024 elements vector checking done." << std::endl;
        }

        // size == 10000
        {
            int next {};
            RESTART_RANDOM_ACCESS_10000:
            const auto numbers {this->generate_number(10000)};
            auto d {this->to_random_access_iterator(numbers)};
            vector<int> v(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
            assert(v.size() == 10000);
            assert(not v.empty());
            assert(v.capacity() == 10000);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + 10000 == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + 10000 == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + 10000 == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + 10000 == v.cend());
            assert(*v.begin() == *numbers.begin());
            assert(v.front() == numbers.front());
            assert(v.back() == numbers.back());
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[i]);
            }
            std::cout << "\t\ttest_constructor_5/random access iterator/10000 elements vector checking next = " << next + 1 << " done." << std::endl;
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
            vector<int> v(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
            assert(v.size() == 100000);
            assert(not v.empty());
            assert(v.capacity() == 100000);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + 100000 == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + 100000 == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + 100000 == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + 100000 == v.cend());
            assert(*v.begin() == *numbers.begin());
            assert(v.front() == numbers.front());
            assert(v.back() == numbers.back());
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[i]);
            }
            std::cout << "\t\ttest_constructor_5/random access iterator/100000 elements vector checking next = " << next + 1 << " done." << std::endl;
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
            vector<int> v(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
            assert(v.size() == 1000000);
            assert(not v.empty());
            assert(v.capacity() == 1000000);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + 1000000 == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + 1000000 == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + 1000000 == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + 1000000 == v.cend());
            assert(*v.begin() == *numbers.begin());
            assert(v.front() == numbers.front());
            assert(v.back() == numbers.back());
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[i]);
            }
            std::cout << "\t\ttest_constructor_5/random access iterator/1000000 elements vector checking next = " << next + 1 << " done." << std::endl;
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
            vector<int> v(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
            assert(v.size() == 10000000);
            assert(not v.empty());
            assert(v.capacity() == 10000000);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + 10000000 == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + 10000000 == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + 10000000 == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + 10000000 == v.cend());
            assert(*v.begin() == *numbers.begin());
            assert(v.front() == numbers.front());
            assert(v.back() == numbers.back());
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[i]);
            }
            std::cout << "\t\ttest_constructor_5/random access iterator/10000000 elements vector checking next = " << next + 1 << " done." << std::endl;
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
            vector<int> v(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
            assert(v.size() == 100000000);
            assert(not v.empty());
            assert(v.capacity() == 100000000);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + 100000000 == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + 100000000 == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + 100000000 == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + 100000000 == v.cend());
            assert(*v.begin() == *numbers.begin());
            assert(v.front() == numbers.front());
            assert(v.back() == numbers.back());
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[i]);
            }
            std::cout << "\t\ttest_constructor_5/random access iterator/100000000 elements vector checking next = " << next + 1 << " done." << std::endl;
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
            vector<int> v(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
            assert(v.size() == size);
            assert(not v.empty());
            assert(v.capacity() == size);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + size == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + size == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + size == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + size == v.cend());
            assert(*v.begin() == *numbers.begin());
            assert(v.front() == numbers.front());
            assert(v.back() == numbers.back());
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            numbers_i = numbers.size() - 1;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i--]);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[i]);
            }
            std::cout << "\t\ttest_constructor_5/random access iterator/Random sized elements " << size << " vector checking next = " << next + 1 << " done." << std::endl;
            if(++next < 3) {
                goto RESTART_RANDOM_ACCESS_RANDOM;
            }
        }
        std::cout << "\tChecking bidirectional iterator version finished!" << std::endl;
    }

    std::cout << "Checking vector(ForwardIterator, ForwardIterator) finished!" << std::endl;
}
void vector_correctness::test_constructor_6() {
    std::cout << "Start checking vector(initializer_list<T>,)!" << std::endl;
    const std::initializer_list<int> empty_list = {};
    const auto single_list = {42};
    const auto list = {-5, -2, 0, 1, 4, 6, 8, 111};

    // empty from initializer_list
    {
        vector<int> v1(empty_list);
        assert(v1.size() == 0);
        assert(v1.empty());
        assert(v1.begin() == v1.end());

        vector<int> v2({});
        assert(v2.size() == 0);
        assert(v2.empty());
        assert(v2.begin() == v2.end());
        std::cout << "\ttest_constructor_6/Empty vector from initializer_list checking done." << std::endl;
    }

    // single element
    {
        vector<int> v1 {42};
        assert(v1.size() == 1);
        assert(not v1.empty());
        assert(v1.begin() not_eq v1.end());
        assert(v1.begin() + 1 == v1.end());
        assert(*v1.begin() == 42);

        vector<int> v2(single_list);
        assert(v2.size() == 1);
        assert(not v2.empty());
        assert(v2.begin() not_eq v2.end());
        assert(v2.begin() + 1 == v2.end());
        assert(*v2.begin() == 42);
        std::cout << "\ttest_constructor_6/Single element vector checking done." << std::endl;
    }

    // other test
    {
        vector<int> v(list);
        assert(v.size() == 8);
        assert(not v.empty());
        assert(v.begin() + 8 == v.end());
        for(auto i {0}; i < list.size(); ++i) {
            assert(*(v.begin() + i) == *(list.begin() + i));
        }
        std::cout << "\ttest_constructor_6/vector other test checking done." << std::endl;
    }

    std::cout << "Checking vector(initializer_list<T>) finished!" << std::endl;
}
void vector_correctness::test_copy_constructor() {
    std::cout << "Start checking copy constructor!" << std::endl;

    // empty
    {
        vector<int> v0(0);
        auto v {v0};
        assert(v.size() == 0);
        assert(v.empty());
        assert(v.capacity() == 0);
        assert(v.spare() == 0);
        assert(v.begin() == v.end());
        assert(v.cbegin() == v.cend());
        assert(v.rbegin() == v.rend());
        assert(v.crbegin() == v.crend());
        assert(v.data() == nullptr);
        std::cout << "\ttest_default_copy_constructor/Empty vector checking done." << std::endl;
    }

    // single element
    {
        vector<int> v0(1);
        auto v {v0};
        assert(v.size() == 1);
        assert(not v.empty());
        assert(v.capacity() == 1);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() not_eq v.end());
        assert(v.begin() + 1 == v.end());
        assert(v.cbegin() not_eq v.cend());
        assert(v.cbegin() + 1 == v.cend());
        assert(v.cbegin() not_eq v.end());
        assert(v.cbegin() + 1 == v.end());
        assert(v.begin() not_eq v.cend());
        assert(v.begin() + 1 == v.cend());
        assert(*v.begin() == 0);
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_copy_constructor/Single element vector checking done." << std::endl;
    }

    // size == 10
    {
        vector<int> v0(10);
        auto v {v0};
        assert(v.size() == 10);
        assert(not v.empty());
        assert(v.capacity() == 10);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + 10 == v.end());
        assert(v.cbegin() + 10 == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_copy_constructor/10 elements vector checking done." << std::endl;
    }

    // size == 42
    {
        vector<int> v0(42);
        auto v {v0};
        assert(v.size() == 42);
        assert(not v.empty());
        assert(v.capacity() == 42);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + 42 == v.end());
        assert(v.cbegin() + 42 == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_copy_constructor/42 elements vector checking done." << std::endl;
    }

    // size == 64
    {
        vector<int> v0(64);
        auto v {v0};
        assert(v.size() == 64);
        assert(not v.empty());
        assert(v.capacity() == 64);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + 64 == v.end());
        assert(v.cbegin() + 64 == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_copy_constructor/64 elements vector checking done." << std::endl;
    }

    // size == 128
    {
        vector<int> v0(128);
        auto v {v0};
        assert(v.size() == 128);
        assert(not v.empty());
        assert(v.capacity() == 128);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + 128 == v.end());
        assert(v.cbegin() + 128 == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_copy_constructor/128 elements vector checking done." << std::endl;
    }

    // size == 1024
    {
        vector<int> v0(1024);
        auto v {v0};
        assert(v.size() == 1024);
        assert(not v.empty());
        assert(v.capacity() == 1024);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + 1024 == v.end());
        assert(v.cbegin() + 1024 == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_copy_constructor/1024 elements vector checking done." << std::endl;
    }

    // random size, size <= 10000
    {
        int next {};
        RESTART_10000:
        const auto size {this->generate_count(10000)};
        vector<int> v0(size);
        auto v {v0};
        assert(v.size() == size);
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_copy_constructor/10000 elements vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 100) {
            goto RESTART_10000;
        }
    }

    // random size, size <= 100000
    {
        int next {};
        RESTART_100000:
        const auto size {this->generate_count(100000)};
        vector<int> v0(size);
        auto v {v0};
        assert(v.size() == size);
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_copy_constructor/100000 elements vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 50) {
            goto RESTART_100000;
        }
    }

    // random size, size <= 1000000
    {
        int next {};
        RESTART_1000000:
        const auto size {this->generate_count(1000000)};
        vector<int> v0(size);
        auto v {v0};
        assert(v.size() == size);
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_copy_constructor/1000000 elements vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 10) {
            goto RESTART_1000000;
        }
    }

    // random size, size <= 10000000
    {
        int next {};
        RESTART_10000000:
        const auto size {this->generate_count(10000000)};
        vector<int> v0(size);
        auto v {v0};
        assert(v.size() == size);
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_copy_constructor/10000000 elements vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 5) {
            goto RESTART_10000000;
        }
    }

    // random size, size <= 100000000
    {
        int next {};
        RESTART_100000000:
        const auto size {this->generate_count(100000000)};
        vector<int> v0(size);
        auto v {v0};
        assert(v.size() == size);
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_copy_constructor/100000000 elements vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 3) {
            goto RESTART_100000000;
        }
    }

    // random size
    {
        int next {};
        RESTART_RANDOM:
        const auto size {this->generate_count()};
        vector<int> v0(size);
        auto v {v0};
        assert(v.size() == size);
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_copy_constructor/Random sized elements " << size << " vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 3) {
            goto RESTART_RANDOM;
        }
    }

    std::cout << "Checking copy constructor finished!" << std::endl;
}
void vector_correctness::test_move_constructor() {
    std::cout << "Start checking move constructor!" << std::endl;

    // empty
    {
        vector<int> v0(0);
        auto v {move(v0)};
        assert(v0.size() == 0);
        assert(v0.empty());
        assert(v0.capacity() == 0);
        assert(v0.spare() == 0);
        assert(v0.begin() == v0.end());
        assert(v0.cbegin() == v0.cend());
        assert(v0.rbegin() == v0.rend());
        assert(v0.crbegin() == v0.crend());
        assert(v0.data() == nullptr);
        assert(v.size() == 0);
        assert(v.empty());
        assert(v.capacity() == 0);
        assert(v.spare() == 0);
        assert(v.begin() == v.end());
        assert(v.cbegin() == v.cend());
        assert(v.rbegin() == v.rend());
        assert(v.crbegin() == v.crend());
        assert(v.data() == nullptr);
        std::cout << "\ttest_default_move_constructor/Empty vector checking done." << std::endl;
    }

    // single element
    {
        vector<int> v0(1);
        auto v {move(v0)};
        assert(v0.size() == 0);
        assert(v0.empty());
        assert(v0.capacity() == 0);
        assert(v0.spare() == 0);
        assert(v0.begin() == v0.end());
        assert(v0.cbegin() == v0.cend());
        assert(v0.rbegin() == v0.rend());
        assert(v0.crbegin() == v0.crend());
        assert(v0.data() == nullptr);
        assert(v.size() == 1);
        assert(not v.empty());
        assert(v.capacity() == 1);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() not_eq v.end());
        assert(v.begin() + 1 == v.end());
        assert(v.cbegin() not_eq v.cend());
        assert(v.cbegin() + 1 == v.cend());
        assert(v.cbegin() not_eq v.end());
        assert(v.cbegin() + 1 == v.end());
        assert(v.begin() not_eq v.cend());
        assert(v.begin() + 1 == v.cend());
        assert(*v.begin() == 0);
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_move_constructor/Single element vector checking done." << std::endl;
    }

    // size == 10
    {
        vector<int> v0(10);
        auto v {move(v0)};
        assert(v0.size() == 0);
        assert(v0.empty());
        assert(v0.capacity() == 0);
        assert(v0.spare() == 0);
        assert(v0.begin() == v0.end());
        assert(v0.cbegin() == v0.cend());
        assert(v0.rbegin() == v0.rend());
        assert(v0.crbegin() == v0.crend());
        assert(v0.data() == nullptr);
        assert(v.size() == 10);
        assert(not v.empty());
        assert(v.capacity() == 10);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + 10 == v.end());
        assert(v.cbegin() + 10 == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_move_constructor/10 elements vector checking done." << std::endl;
    }

    // size == 42
    {
        vector<int> v0(42);
        auto v {move(v0)};
        assert(v0.size() == 0);
        assert(v0.empty());
        assert(v0.capacity() == 0);
        assert(v0.spare() == 0);
        assert(v0.begin() == v0.end());
        assert(v0.cbegin() == v0.cend());
        assert(v0.rbegin() == v0.rend());
        assert(v0.crbegin() == v0.crend());
        assert(v0.data() == nullptr);
        assert(v.size() == 42);
        assert(not v.empty());
        assert(v.capacity() == 42);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + 42 == v.end());
        assert(v.cbegin() + 42 == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_move_constructor/42 elements vector checking done." << std::endl;
    }

    // size == 64
    {
        vector<int> v0(64);
        auto v {move(v0)};
        assert(v0.size() == 0);
        assert(v0.empty());
        assert(v0.capacity() == 0);
        assert(v0.spare() == 0);
        assert(v0.begin() == v0.end());
        assert(v0.cbegin() == v0.cend());
        assert(v0.rbegin() == v0.rend());
        assert(v0.crbegin() == v0.crend());
        assert(v0.data() == nullptr);
        assert(v.size() == 64);
        assert(not v.empty());
        assert(v.capacity() == 64);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + 64 == v.end());
        assert(v.cbegin() + 64 == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_move_constructor/64 elements vector checking done." << std::endl;
    }

    // size == 128
    {
        vector<int> v0(128);
        auto v {move(v0)};
        assert(v0.size() == 0);
        assert(v0.empty());
        assert(v0.capacity() == 0);
        assert(v0.spare() == 0);
        assert(v0.begin() == v0.end());
        assert(v0.cbegin() == v0.cend());
        assert(v0.rbegin() == v0.rend());
        assert(v0.crbegin() == v0.crend());
        assert(v0.data() == nullptr);
        assert(v.size() == 128);
        assert(not v.empty());
        assert(v.capacity() == 128);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + 128 == v.end());
        assert(v.cbegin() + 128 == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_move_constructor/128 elements vector checking done." << std::endl;
    }

    // size == 1024
    {
        vector<int> v0(1024);
        auto v {move(v0)};
        assert(v0.size() == 0);
        assert(v0.empty());
        assert(v0.capacity() == 0);
        assert(v0.spare() == 0);
        assert(v0.begin() == v0.end());
        assert(v0.cbegin() == v0.cend());
        assert(v0.rbegin() == v0.rend());
        assert(v0.crbegin() == v0.crend());
        assert(v0.data() == nullptr);
        assert(v.size() == 1024);
        assert(not v.empty());
        assert(v.capacity() == 1024);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + 1024 == v.end());
        assert(v.cbegin() + 1024 == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_move_constructor/1024 elements vector checking done." << std::endl;
    }

    // random size, size <= 10000
    {
        int next {};
        RESTART_10000:
        const auto size {this->generate_count(10000)};
        vector<int> v0(size);
        auto v {move(v0)};
        assert(v0.size() == 0);
        assert(v0.empty());
        assert(v0.capacity() == 0);
        assert(v0.spare() == 0);
        assert(v0.begin() == v0.end());
        assert(v0.cbegin() == v0.cend());
        assert(v0.rbegin() == v0.rend());
        assert(v0.crbegin() == v0.crend());
        assert(v0.data() == nullptr);
        assert(v.size() == size);
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_move_constructor/10000 elements vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 100) {
            goto RESTART_10000;
        }
    }

    // random size, size <= 100000
    {
        int next {};
        RESTART_100000:
        const auto size {this->generate_count(100000)};
        vector<int> v0(size);
        auto v {move(v0)};
        assert(v0.size() == 0);
        assert(v0.empty());
        assert(v0.capacity() == 0);
        assert(v0.spare() == 0);
        assert(v0.begin() == v0.end());
        assert(v0.cbegin() == v0.cend());
        assert(v0.rbegin() == v0.rend());
        assert(v0.crbegin() == v0.crend());
        assert(v0.data() == nullptr);
        assert(v.size() == size);
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_move_constructor/100000 elements vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 50) {
            goto RESTART_100000;
        }
    }

    // random size, size <= 1000000
    {
        int next {};
        RESTART_1000000:
        const auto size {this->generate_count(1000000)};
        vector<int> v0(size);
        auto v {move(v0)};
        assert(v0.size() == 0);
        assert(v0.empty());
        assert(v0.capacity() == 0);
        assert(v0.spare() == 0);
        assert(v0.begin() == v0.end());
        assert(v0.cbegin() == v0.cend());
        assert(v0.rbegin() == v0.rend());
        assert(v0.crbegin() == v0.crend());
        assert(v0.data() == nullptr);
        assert(v.size() == size);
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_move_constructor/1000000 elements vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 10) {
            goto RESTART_1000000;
        }
    }

    // random size, size <= 10000000
    {
        int next {};
        RESTART_10000000:
        const auto size {this->generate_count(10000000)};
        vector<int> v0(size);
        auto v {move(v0)};
        assert(v0.size() == 0);
        assert(v0.empty());
        assert(v0.capacity() == 0);
        assert(v0.spare() == 0);
        assert(v0.begin() == v0.end());
        assert(v0.cbegin() == v0.cend());
        assert(v0.rbegin() == v0.rend());
        assert(v0.crbegin() == v0.crend());
        assert(v0.data() == nullptr);
        assert(v.size() == size);
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_move_constructor/10000000 elements vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 5) {
            goto RESTART_10000000;
        }
    }

    // random size, size <= 100000000
    {
        int next {};
        RESTART_100000000:
        const auto size {this->generate_count(100000000)};
        vector<int> v0(size);
        auto v {move(v0)};
        assert(v0.size() == 0);
        assert(v0.empty());
        assert(v0.capacity() == 0);
        assert(v0.spare() == 0);
        assert(v0.begin() == v0.end());
        assert(v0.cbegin() == v0.cend());
        assert(v0.rbegin() == v0.rend());
        assert(v0.crbegin() == v0.crend());
        assert(v0.data() == nullptr);
        assert(v.size() == size);
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_move_constructor/100000000 elements vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 3) {
            goto RESTART_100000000;
        }
    }

    // random size
    {
        int next {};
        RESTART_RANDOM:
        const auto size {this->generate_count()};
        vector<int> v0(size);
        auto v {move(v0)};
        assert(v0.size() == 0);
        assert(v0.empty());
        assert(v0.capacity() == 0);
        assert(v0.spare() == 0);
        assert(v0.begin() == v0.end());
        assert(v0.cbegin() == v0.cend());
        assert(v0.rbegin() == v0.rend());
        assert(v0.crbegin() == v0.crend());
        assert(v0.data() == nullptr);
        assert(v.size() == size);
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\ttest_move_constructor/Random sized elements " << size << " vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 3) {
            goto RESTART_RANDOM;
        }
    }

    std::cout << "Checking move constructor finished!" << std::endl;
}
void vector_correctness::test_copy_assignment() {
    std::cout << "Start checking copy assignment!" << std::endl;

    // empty
    {
        vector<int> v0(0);
        vector<int> v {};
        v = v0;
        bool rechecked {};
        RECHECK_EMPTY : assert(v.size() == 0);
        assert(v.empty());
        assert(v.capacity() == 0);
        assert(v.spare() == 0);
        assert(v.begin() == v.end());
        assert(v.cbegin() == v.cend());
        assert(v.rbegin() == v.rend());
        assert(v.crbegin() == v.crend());
        assert(v.data() == nullptr);
        if(not rechecked) {
            v = v;
            rechecked = true;
            goto RECHECK_EMPTY;
        }
        std::cout << "\ttest_default_copy_assignment/Empty vector checking done." << std::endl;
    }

    // single element
    {
        vector<int> v0(1);
        vector<int> v {};
        v = v0;
        bool rechecked {};
        RECHECK_1 : assert(v.size() == 1);
        assert(not v.empty());
        assert(v.capacity() == 1);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() not_eq v.end());
        assert(v.begin() + 1 == v.end());
        assert(v.cbegin() not_eq v.cend());
        assert(v.cbegin() + 1 == v.cend());
        assert(v.cbegin() not_eq v.end());
        assert(v.cbegin() + 1 == v.end());
        assert(v.begin() not_eq v.cend());
        assert(v.begin() + 1 == v.cend());
        assert(*v.begin() == 0);
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        if(not rechecked) {
            v = v;
            rechecked = true;
            goto RECHECK_1;
        }
        std::cout << "\ttest_copy_assignment/Single element vector checking done." << std::endl;
    }

    // size == 10
    {
        vector<int> v0(10);
        vector<int> v {};
        v = v0;
        bool rechecked {};
        RECHECK_10 : assert(v.size() == 10);
        assert(not v.empty());
        assert(v.capacity() == 10);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + 10 == v.end());
        assert(v.cbegin() + 10 == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        if(not rechecked) {
            v = v;
            rechecked = true;
            goto RECHECK_10;
        }
        std::cout << "\ttest_copy_assignment/10 elements vector checking done." << std::endl;
    }

    // size == 42
    {
        vector<int> v0(42);
        vector<int> v {};
        v = v0;
        bool rechecked {};
        RECHECK_42 : assert(v.size() == 42);
        assert(not v.empty());
        assert(v.capacity() == 42);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + 42 == v.end());
        assert(v.cbegin() + 42 == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        if(not rechecked) {
            v = v;
            rechecked = true;
            goto RECHECK_42;
        }
        std::cout << "\ttest_copy_assignment/42 elements vector checking done." << std::endl;
    }

    // size == 64
    {
        vector<int> v0(64);
        vector<int> v {};
        v = v0;
        bool rechecked {};
        RECHECK_64 : assert(v.size() == 64);
        assert(not v.empty());
        assert(v.capacity() == 64);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + 64 == v.end());
        assert(v.cbegin() + 64 == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        if(not rechecked) {
            v = v;
            rechecked = true;
            goto RECHECK_64;
        }
        std::cout << "\ttest_copy_assignment/64 elements vector checking done." << std::endl;
    }

    // size == 128
    {
        vector<int> v0(128);
        vector<int> v {};
        v = v0;
        bool rechecked {};
        RECHECK_128 : assert(v.size() == 128);
        assert(not v.empty());
        assert(v.capacity() == 128);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + 128 == v.end());
        assert(v.cbegin() + 128 == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        if(not rechecked) {
            v = v;
            rechecked = true;
            goto RECHECK_128;
        }
        std::cout << "\ttest_copy_assignment/128 elements vector checking done." << std::endl;
    }

    // size == 1024
    {
        vector<int> v0(1024);
        vector<int> v {};
        v = v0;
        bool rechecked {};
        RECHECK_1024 : assert(v.size() == 1024);
        assert(not v.empty());
        assert(v.capacity() == 1024);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + 1024 == v.end());
        assert(v.cbegin() + 1024 == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        if(not rechecked) {
            v = v;
            rechecked = true;
            goto RECHECK_1024;
        }
        std::cout << "\ttest_copy_assignment/1024 elements vector checking done." << std::endl;
    }

    // random size, size <= 10000
    {
        int next {};
        RESTART_10000:
        const auto size {this->generate_count(10000)};
        vector<int> v0(size);
        vector<int> v {};
        v = v0;
        bool rechecked {};
        RECHECK_10000 : assert(v.size() == size);
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        if(not rechecked) {
            v = v;
            rechecked = true;
            goto RECHECK_10000;
        }
        std::cout << "\ttest_copy_assignment/10000 elements vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 100) {
            goto RESTART_10000;
        }
    }

    // random size, size <= 100000
    {
        int next {};
        RESTART_100000:
        const auto size {this->generate_count(100000)};
        vector<int> v0(size);
        vector<int> v {};
        v = v0;
        bool rechecked {};
        RECHECK_100000 : assert(v.size() == size);
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        if(not rechecked) {
            v = v;
            rechecked = true;
            goto RECHECK_100000;
        }
        std::cout << "\ttest_copy_assignment/100000 elements vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 50) {
            goto RESTART_100000;
        }
    }

    // random size, size <= 1000000
    {
        int next {};
        RESTART_1000000:
        const auto size {this->generate_count(1000000)};
        vector<int> v0(size);
        vector<int> v {};
        v = v0;
        bool rechecked {};
        RECHECK_1000000 : assert(v.size() == size);
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        if(not rechecked) {
            v = v;
            rechecked = true;
            goto RECHECK_1000000;
        }
        std::cout << "\ttest_copy_assignment/1000000 elements vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 10) {
            goto RESTART_1000000;
        }
    }

    // random size, size <= 10000000
    {
        int next {};
        RESTART_10000000:
        const auto size {this->generate_count(10000000)};
        vector<int> v0(size);
        vector<int> v {};
        v = v0;
        bool rechecked {};
        RECHECK_10000000 : assert(v.size() == size);
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        if(not rechecked) {
            v = v;
            rechecked = true;
            goto RECHECK_10000000;
        }
        std::cout << "\ttest_copy_assignment/10000000 elements vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 5) {
            goto RESTART_10000000;
        }
    }

    // random size, size <= 100000000
    {
        int next {};
        RESTART_100000000:
        const auto size {this->generate_count(100000000)};
        vector<int> v0(size);
        vector<int> v {};
        v = v0;
        bool rechecked {};
        RECHECK_100000000 : assert(v.size() == size);
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        if(not rechecked) {
            v = v;
            rechecked = true;
            goto RECHECK_100000000;
        }
        std::cout << "\ttest_copy_assignment/100000000 elements vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 3) {
            goto RESTART_100000000;
        }
    }

    // random size
    {
        int next {};
        RESTART_RANDOM:
        const auto size {this->generate_count()};
        vector<int> v0(size);
        vector<int> v {};
        v = v0;
        bool rechecked {};
        RECHECK_RANDOM : assert(v.size() == size);
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        if(not rechecked) {
            v = v;
            rechecked = true;
            goto RECHECK_RANDOM;
        }
        std::cout << "\ttest_copy_assignment/Random sized elements " << size << " vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 3) {
            goto RESTART_RANDOM;
        }
    }

    std::cout << "Checking copy assignment finished!" << std::endl;
}
void vector_correctness::test_move_assignment() {
    std::cout << "Start checking move assignment!" << std::endl;

    // empty
    {
        vector<int> v0(0);
        vector<int> v {};
        v = move(v0);
        bool rechecked {};
        assert(v0.size() == 0);
        assert(v0.empty());
        assert(v0.capacity() == 0);
        assert(v0.spare() == 0);
        assert(v0.begin() == v0.end());
        assert(v0.cbegin() == v0.cend());
        assert(v0.rbegin() == v0.rend());
        assert(v0.crbegin() == v0.crend());
        assert(v0.data() == nullptr);
        RECHECK_EMPTY : assert(v.size() == 0);
        assert(v.empty());
        assert(v.capacity() == 0);
        assert(v.spare() == 0);
        assert(v.begin() == v.end());
        assert(v.cbegin() == v.cend());
        assert(v.rbegin() == v.rend());
        assert(v.crbegin() == v.crend());
        assert(v.data() == nullptr);
        if(not rechecked) {
            v = move(v);
            rechecked = true;
            goto RECHECK_EMPTY;
        }
        std::cout << "\ttest_default_move_assignment/Empty vector checking done." << std::endl;
    }

    // single element
    {
        vector<int> v0(1);
        vector<int> v {};
        v = move(v0);
        bool rechecked {};
        assert(v0.size() == 0);
        assert(v0.empty());
        assert(v0.capacity() == 0);
        assert(v0.spare() == 0);
        assert(v0.begin() == v0.end());
        assert(v0.cbegin() == v0.cend());
        assert(v0.rbegin() == v0.rend());
        assert(v0.crbegin() == v0.crend());
        assert(v0.data() == nullptr);
        RECHECK_1 : assert(v.size() == 1);
        assert(not v.empty());
        assert(v.capacity() == 1);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() not_eq v.end());
        assert(v.begin() + 1 == v.end());
        assert(v.cbegin() not_eq v.cend());
        assert(v.cbegin() + 1 == v.cend());
        assert(v.cbegin() not_eq v.end());
        assert(v.cbegin() + 1 == v.end());
        assert(v.begin() not_eq v.cend());
        assert(v.begin() + 1 == v.cend());
        assert(*v.begin() == 0);
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        if(not rechecked) {
            v = move(v);
            rechecked = true;
            goto RECHECK_1;
        }
        std::cout << "\ttest_move_assignment/Single element vector checking done." << std::endl;
    }

    // size == 10
    {
        vector<int> v0(10);
        vector<int> v {};
        v = move(v0);
        bool rechecked {};
        assert(v0.size() == 0);
        assert(v0.empty());
        assert(v0.capacity() == 0);
        assert(v0.spare() == 0);
        assert(v0.begin() == v0.end());
        assert(v0.cbegin() == v0.cend());
        assert(v0.rbegin() == v0.rend());
        assert(v0.crbegin() == v0.crend());
        assert(v0.data() == nullptr);
        RECHECK_10 : assert(v.size() == 10);
        assert(not v.empty());
        assert(v.capacity() == 10);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + 10 == v.end());
        assert(v.cbegin() + 10 == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        if(not rechecked) {
            v = move(v);
            rechecked = true;
            goto RECHECK_10;
        }
        std::cout << "\ttest_move_assignment/10 elements vector checking done." << std::endl;
    }

    // size == 42
    {
        vector<int> v0(42);
        vector<int> v {};
        v = move(v0);
        bool rechecked {};
        assert(v0.size() == 0);
        assert(v0.empty());
        assert(v0.capacity() == 0);
        assert(v0.spare() == 0);
        assert(v0.begin() == v0.end());
        assert(v0.cbegin() == v0.cend());
        assert(v0.rbegin() == v0.rend());
        assert(v0.crbegin() == v0.crend());
        assert(v0.data() == nullptr);
        RECHECK_42 : assert(v.size() == 42);
        assert(not v.empty());
        assert(v.capacity() == 42);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + 42 == v.end());
        assert(v.cbegin() + 42 == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        if(not rechecked) {
            v = move(v);
            rechecked = true;
            goto RECHECK_42;
        }
        std::cout << "\ttest_move_assignment/42 elements vector checking done." << std::endl;
    }

    // size == 64
    {
        vector<int> v0(64);
        vector<int> v {};
        v = move(v0);
        bool rechecked {};
        assert(v0.size() == 0);
        assert(v0.empty());
        assert(v0.capacity() == 0);
        assert(v0.spare() == 0);
        assert(v0.begin() == v0.end());
        assert(v0.cbegin() == v0.cend());
        assert(v0.rbegin() == v0.rend());
        assert(v0.crbegin() == v0.crend());
        assert(v0.data() == nullptr);
        RECHECK_64 : assert(v.size() == 64);
        assert(not v.empty());
        assert(v.capacity() == 64);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + 64 == v.end());
        assert(v.cbegin() + 64 == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        if(not rechecked) {
            v = move(v);
            rechecked = true;
            goto RECHECK_64;
        }
        std::cout << "\ttest_move_assignment/64 elements vector checking done." << std::endl;
    }

    // size == 128
    {
        vector<int> v0(128);
        vector<int> v {};
        v = move(v0);
        bool rechecked {};
        assert(v0.size() == 0);
        assert(v0.empty());
        assert(v0.capacity() == 0);
        assert(v0.spare() == 0);
        assert(v0.begin() == v0.end());
        assert(v0.cbegin() == v0.cend());
        assert(v0.rbegin() == v0.rend());
        assert(v0.crbegin() == v0.crend());
        assert(v0.data() == nullptr);
        RECHECK_128 : assert(v.size() == 128);
        assert(not v.empty());
        assert(v.capacity() == 128);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + 128 == v.end());
        assert(v.cbegin() + 128 == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        if(not rechecked) {
            v = move(v);
            rechecked = true;
            goto RECHECK_128;
        }
        std::cout << "\ttest_move_assignment/128 elements vector checking done." << std::endl;
    }

    // size == 1024
    {
        vector<int> v0(1024);
        vector<int> v {};
        v = move(v0);
        bool rechecked {};
        assert(v0.size() == 0);
        assert(v0.empty());
        assert(v0.capacity() == 0);
        assert(v0.spare() == 0);
        assert(v0.begin() == v0.end());
        assert(v0.cbegin() == v0.cend());
        assert(v0.rbegin() == v0.rend());
        assert(v0.crbegin() == v0.crend());
        assert(v0.data() == nullptr);
        RECHECK_1024 : assert(v.size() == 1024);
        assert(not v.empty());
        assert(v.capacity() == 1024);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + 1024 == v.end());
        assert(v.cbegin() + 1024 == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        if(not rechecked) {
            v = move(v);
            rechecked = true;
            goto RECHECK_1024;
        }
        std::cout << "\ttest_move_assignment/1024 elements vector checking done." << std::endl;
    }

    // random size, size <= 10000
    {
        int next {};
        RESTART_10000:
        const auto size {this->generate_count(10000)};
        vector<int> v0(size);
        vector<int> v {};
        v = move(v0);
        bool rechecked {};
        assert(v0.size() == 0);
        assert(v0.empty());
        assert(v0.capacity() == 0);
        assert(v0.spare() == 0);
        assert(v0.begin() == v0.end());
        assert(v0.cbegin() == v0.cend());
        assert(v0.rbegin() == v0.rend());
        assert(v0.crbegin() == v0.crend());
        assert(v0.data() == nullptr);
        RECHECK_10000 : assert(v.size() == size);
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        if(not rechecked) {
            v = move(v);
            rechecked = true;
            goto RECHECK_10000;
        }
        std::cout << "\ttest_move_assignment/10000 elements vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 100) {
            goto RESTART_10000;
        }
    }

    // random size, size <= 100000
    {
        int next {};
        RESTART_100000:
        const auto size {this->generate_count(100000)};
        vector<int> v0(size);
        vector<int> v {};
        v = move(v0);
        bool rechecked {};
        assert(v0.size() == 0);
        assert(v0.empty());
        assert(v0.capacity() == 0);
        assert(v0.spare() == 0);
        assert(v0.begin() == v0.end());
        assert(v0.cbegin() == v0.cend());
        assert(v0.rbegin() == v0.rend());
        assert(v0.crbegin() == v0.crend());
        assert(v0.data() == nullptr);
        RECHECK_100000 : assert(v.size() == size);
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        if(not rechecked) {
            v = move(v);
            rechecked = true;
            goto RECHECK_100000;
        }
        std::cout << "\ttest_move_assignment/100000 elements vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 50) {
            goto RESTART_100000;
        }
    }

    // random size, size <= 1000000
    {
        int next {};
        RESTART_1000000:
        const auto size {this->generate_count(1000000)};
        vector<int> v0(size);
        vector<int> v {};
        v = move(v0);
        bool rechecked {};
        assert(v0.size() == 0);
        assert(v0.empty());
        assert(v0.capacity() == 0);
        assert(v0.spare() == 0);
        assert(v0.begin() == v0.end());
        assert(v0.cbegin() == v0.cend());
        assert(v0.rbegin() == v0.rend());
        assert(v0.crbegin() == v0.crend());
        assert(v0.data() == nullptr);
        RECHECK_1000000 : assert(v.size() == size);
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        if(not rechecked) {
            v = move(v);
            rechecked = true;
            goto RECHECK_1000000;
        }
        std::cout << "\ttest_move_assignment/1000000 elements vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 10) {
            goto RESTART_1000000;
        }
    }

    // random size, size <= 10000000
    {
        int next {};
        RESTART_10000000:
        const auto size {this->generate_count(10000000)};
        vector<int> v0(size);
        vector<int> v {};
        v = move(v0);
        bool rechecked {};
        assert(v0.size() == 0);
        assert(v0.empty());
        assert(v0.capacity() == 0);
        assert(v0.spare() == 0);
        assert(v0.begin() == v0.end());
        assert(v0.cbegin() == v0.cend());
        assert(v0.rbegin() == v0.rend());
        assert(v0.crbegin() == v0.crend());
        assert(v0.data() == nullptr);
        RECHECK_10000000 : assert(v.size() == size);
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        if(not rechecked) {
            v = move(v);
            rechecked = true;
            goto RECHECK_10000000;
        }
        std::cout << "\ttest_move_assignment/10000000 elements vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 5) {
            goto RESTART_10000000;
        }
    }

    // random size, size <= 100000000
    {
        int next {};
        RESTART_100000000:
        const auto size {this->generate_count(100000000)};
        vector<int> v0(size);
        vector<int> v {};
        v = move(v0);
        bool rechecked {};
        assert(v0.size() == 0);
        assert(v0.empty());
        assert(v0.capacity() == 0);
        assert(v0.spare() == 0);
        assert(v0.begin() == v0.end());
        assert(v0.cbegin() == v0.cend());
        assert(v0.rbegin() == v0.rend());
        assert(v0.crbegin() == v0.crend());
        assert(v0.data() == nullptr);
        RECHECK_100000000 : assert(v.size() == size);
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        if(not rechecked) {
            v = move(v);
            rechecked = true;
            goto RECHECK_100000000;
        }
        std::cout << "\ttest_move_assignment/100000000 elements vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 3) {
            goto RESTART_100000000;
        }
    }

    // random size
    {
        int next {};
        RESTART_RANDOM:
        const auto size {this->generate_count()};
        vector<int> v0(size);
        vector<int> v {};
        v = move(v0);
        bool rechecked {};
        assert(v0.size() == 0);
        assert(v0.empty());
        assert(v0.capacity() == 0);
        assert(v0.spare() == 0);
        assert(v0.begin() == v0.end());
        assert(v0.cbegin() == v0.cend());
        assert(v0.rbegin() == v0.rend());
        assert(v0.crbegin() == v0.crend());
        assert(v0.data() == nullptr);
        RECHECK_RANDOM : assert(v.size() == size);
        assert(not v.empty());
        assert(v.capacity() == size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + size == v.end());
        assert(v.cbegin() + size == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        if(not rechecked) {
            v = move(v);
            rechecked = true;
            goto RECHECK_RANDOM;
        }
        std::cout << "\ttest_move_assignment/Random sized elements " << size << " vector checking next = " << next + 1 << " done." << std::endl;
        if(++next < 3) {
            goto RESTART_RANDOM;
        }
    }

    std::cout << "Checking move assignment finished!" << std::endl;
}
void vector_correctness::test_assign_1() {
    std::cout << "Start checking void assign(size_type, const_reference) for vector!" << std::endl;

    // empty vector to non-empty vector
    {
        vector<int> v {};
        const auto count {this->generate_count()};
        const auto number {this->generate_a_random_number()};
        v.assign(count, number);
        assert(v.size() == count);
        assert(not v.empty());
        assert(v.capacity() == count);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + count == v.end());
        assert(v.cbegin() + count == v.cend());
        assert(v.front() == number);
        assert(v.back() == number);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == number);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == number);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == number);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == number);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == number);
        }
        std::cout << "\ttest_assign_1/Empty vector to non-empty vector done." << std::endl;
    }

    // non-empty vector to empty vector
    {
        const auto count {this->generate_count()};
        vector<int> v(count);
        v.assign(0);
        assert(v.size() == 0);
        assert(v.empty());
        assert(v.capacity() == count);
        assert(v.spare() == count);
        assert(v.begin() == v.end());
        assert(v.cbegin() == v.cend());
        assert(v.rbegin() == v.rend());
        assert(v.crbegin() == v.crend());
        assert(v.data() not_eq nullptr);
        std::cout << "\ttest_assign_1/Non-empty vector to vector done." << std::endl;
    }

    // non-empty vector with assigning size greater than capacity
    {
        auto count {this->generate_count()};
        while(count <= 42) {
            count = this->generate_count();
        }
        const auto number {this->generate_a_random_number()};
        vector<int> v(42);
        v.assign(count, number);
        assert(v.size() == count);
        assert(not v.empty());
        assert(v.capacity() == count);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + count == v.end());
        assert(v.cbegin() + count == v.cend());
        assert(v.front() == number);
        assert(v.back() == number);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == number);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == number);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == number);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == number);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == number);
        }
        std::cout << "\ttest_assign_1/Non-empty vector with assigning size greater than capacity done." << std::endl;
    }

    // non-empty vector with assigning size less than capacity
    {
        std::cout << "\tStart checking test_assign_1/Non-empty vector with assigning size less than capacity!" << std::endl;

        // greater than size
        {
            auto count {this->generate_count()};
            while(count <= 1) {
                count = this->generate_count();
            }
            const auto offset {count / 2};
            const auto real_size {count - offset};
            vector<int> v(count);
            v.cursor -= offset;
            const auto new_size {this->generate_a_random_number(real_size + 1, count)};
            const auto number {this->generate_a_random_number()};
            v.assign(new_size, number);
            assert(v.size() == new_size);
            assert(not v.empty());
            assert(v.capacity() == count);
            assert(v.spare() == count - new_size);
            assert(v.data() not_eq nullptr);
            assert(v.begin() + new_size == v.end());
            assert(v.cbegin() + new_size == v.cend());
            assert(v.front() == number);
            assert(v.back() == number);
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == number);
            }
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == number);
            }
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == number);
            }
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == number);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == number);
            }
            std::cout << "\t\ttest_assign_1/Non-empty vector with assigning size less than capacity/Greater than size done." << std::endl;
        }

        // less than size
        {
            auto count {this->generate_count()};
            while(count <= 1) {
                count = this->generate_count();
            }
            vector<int> v(count);
            auto new_size {this->generate_a_random_number(1, count - 1)};
            v.cursor -= count - new_size;
            const auto number {this->generate_a_random_number()};
            v.assign(new_size, number);
            assert(v.size() == new_size);
            assert(not v.empty());
            assert(v.capacity() == count);
            assert(v.spare() == count - new_size);
            assert(v.data() not_eq nullptr);
            assert(v.begin() + new_size == v.end());
            assert(v.cbegin() + new_size == v.cend());
            assert(v.front() == number);
            assert(v.back() == number);
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == number);
            }
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == number);
            }
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == number);
            }
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == number);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == number);
            }
            std::cout << "\t\ttest_assign_1/Non-empty vector with assigning size less than capacity/Less than size done." << std::endl;
        }

        // equal to size
        {
            auto count {this->generate_count()};
            vector<int> v(count);
            const auto number {this->generate_a_random_number()};
            v.assign(count, number);
            assert(v.size() == count);
            assert(not v.empty());
            assert(v.capacity() == count);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() + count == v.end());
            assert(v.cbegin() + count == v.cend());
            assert(v.front() == number);
            assert(v.back() == number);
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == number);
            }
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == number);
            }
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == number);
            }
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == number);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == number);
            }
            std::cout << "\t\ttest_assign_1/Non-empty vector with assigning size less than capacity/Equal to size done." << std::endl;
        }

        std::cout << "\tChecking test_assign_1/Non-empty vector with assigning size less than capacity finished!" << std::endl;
    }

    std::cout << "Checking void assign(size_type, const_reference) for vector finished!" << std::endl;
}
void vector_correctness::test_assign_2() {
    std::cout << "Start checking void assign(InputIterator, InputIterator) for vector!" << std::endl;

    // empty vector to non-empty vector
    {
        vector<int> v {};
        const auto count {this->generate_count()};
        const auto numbers {this->generate_number(count)};
        auto stream {this->to_input_iterator(numbers)};
        v.assign(int_input_iterator {stream}, int_input_iterator {});
        assert(v.size() == count);
        assert(not v.empty());
        assert(v.capacity() == count);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + count == v.end());
        assert(v.cbegin() + count == v.cend());
        assert(v.front() == numbers[0]);
        assert(v.back() == numbers[count - 1]);
        auto numbers_i {0uz};
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        numbers_i = 0;
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        numbers_i = 0;
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        numbers_i = 0;
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        numbers_i = 0;
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == numbers[numbers_i++]);
        }
        std::cout << "\ttest_assign_2/Empty vector to non-empty vector done." << std::endl;
    }

    // non-empty vector to empty vector
    {
        const auto count {this->generate_count()};
        vector<int> v(count);
        v.assign(int_input_iterator {}, int_input_iterator {});
        assert(v.size() == 0);
        assert(v.empty());
        assert(v.capacity() == 0);
        assert(v.spare() == 0);
        assert(v.begin() == v.end());
        assert(v.cbegin() == v.cend());
        assert(v.rbegin() == v.rend());
        assert(v.crbegin() == v.crend());
        assert(v.data() == nullptr);
        std::cout << "\ttest_assign_2/Non-empty vector to vector done." << std::endl;
    }

    // non-empty vector with assigning size greater than capacity
    {
        auto count {this->generate_count()};
        while(count <= 42) {
            count = this->generate_count();
        }
        const auto numbers {this->generate_number(count)};
        auto stream {this->to_input_iterator(numbers)};
        vector<int> v(42);
        v.assign(int_input_iterator {stream}, int_input_iterator {});
        assert(v.size() == count);
        assert(not v.empty());
        assert(v.capacity() == count);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + count == v.end());
        assert(v.cbegin() + count == v.cend());
        assert(v.front() == numbers[0]);
        assert(v.back() == numbers[count - 1]);
        auto numbers_i {0uz};
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        numbers_i = 0;
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        numbers_i = 0;
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        numbers_i = 0;
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        numbers_i = 0;
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == numbers[numbers_i++]);
        }
        std::cout << "\ttest_assign_2/Non-empty vector with assigning size greater than capacity done." << std::endl;
    }

    // non-empty vector with assigning size less than capacity
    {
        std::cout << "\tStart checking test_assign_2/Non-empty vector with assigning size less than capacity!" << std::endl;

        // greater than size
        {
            auto count {this->generate_count()};
            while(count <= 1) {
                count = this->generate_count();
            }
            const auto offset {count / 2};
            const auto real_size {count - offset};
            vector<int> v(count);
            v.cursor -= offset;
            const auto new_size {this->generate_a_random_number(real_size + 1, count)};
            const auto numbers {this->generate_number(new_size)};
            auto stream {this->to_input_iterator(numbers)};
            v.assign(int_input_iterator {stream}, int_input_iterator {});
            assert(v.size() == new_size);
            assert(not v.empty());
            assert(v.capacity() == new_size);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() + new_size == v.end());
            assert(v.cbegin() + new_size == v.cend());
            assert(v.front() == numbers[0]);
            assert(v.back() == numbers[new_size - 1]);
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[numbers_i++]);
            }
            std::cout << "\t\ttest_assign_2/Non-empty vector with assigning size less than capacity/Greater than size done." << std::endl;
        }

        // less than size
        {
            auto count {this->generate_count()};
            while(count <= 1) {
                count = this->generate_count();
            }
            vector<int> v(count);
            auto new_size {this->generate_a_random_number(1, count - 1)};
            v.cursor -= count - new_size;
            const auto numbers {this->generate_number(new_size)};
            auto stream {this->to_input_iterator(numbers)};
            v.assign(int_input_iterator {stream}, int_input_iterator {});
            assert(v.size() == new_size);
            assert(v.size() == new_size);
            assert(not v.empty());
            assert(v.capacity() == new_size);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() + new_size == v.end());
            assert(v.cbegin() + new_size == v.cend());
            assert(v.front() == numbers[0]);
            assert(v.back() == numbers[new_size - 1]);
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[numbers_i++]);
            }
            std::cout << "\t\ttest_assign_2/Non-empty vector with assigning size less than capacity/Less than size done." << std::endl;
        }

        // equal to size
        {
            auto count {this->generate_count()};
            vector<int> v(count);
            const auto numbers {this->generate_number(count)};
            auto stream {this->to_input_iterator(numbers)};
            v.assign(int_input_iterator {stream}, int_input_iterator {});
            assert(v.size() == count);
            assert(not v.empty());
            assert(v.capacity() == count);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() + count == v.end());
            assert(v.cbegin() + count == v.cend());
            assert(v.front() == numbers[0]);
            assert(v.back() == numbers[count - 1]);
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[numbers_i++]);
            }
            std::cout << "\t\ttest_assign_2/Non-empty vector with assigning size less than capacity/Equal to size done." << std::endl;
        }

        std::cout << "\tChecking test_assign_2/Non-empty vector with assigning size less than capacity finished!" << std::endl;
    }

    std::cout << "Checking void assign(InputIterator, InputIterator) for vector finished!" << std::endl;
}
void vector_correctness::test_assign_3() {
    std::cout << "Start checking void assign(ForwardIterator, ForwardIterator) for vector!" << std::endl;

    // forward iterator
    {
        std::cout << "\tStart checking test_assign_3/Forward iterator for vector!" << std::endl;

        // empty vector to non-empty vector
        {
            vector<int> v {};
            const auto count {this->generate_count()};
            const auto numbers {this->generate_number(count)};
            auto l {this->to_forward_iterator(numbers)};
            v.assign(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
            assert(v.size() == count);
            assert(not v.empty());
            assert(v.capacity() == count);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() + count == v.end());
            assert(v.cbegin() + count == v.cend());
            assert(v.front() == numbers[0]);
            assert(v.back() == numbers[count - 1]);
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[numbers_i++]);
            }
            std::cout << "\t\ttest_assign_3/Empty vector to non-empty vector done." << std::endl;
        }

        // non-empty vector to empty vector
        {
            const auto count {this->generate_count()};
            vector<int> v(count);
            v.assign(int_forward_iterator {}, int_forward_iterator {});
            assert(v.size() == 0);
            assert(v.empty());
            assert(v.capacity() == count);
            assert(v.spare() == count);
            assert(v.begin() == v.end());
            assert(v.cbegin() == v.cend());
            assert(v.rbegin() == v.rend());
            assert(v.crbegin() == v.crend());
            assert(v.data() not_eq nullptr);
            std::cout << "\t\ttest_assign_3/Non-empty vector to vector done." << std::endl;
        }

        // non-empty vector with assigning size greater than capacity
        {
            auto count {this->generate_count()};
            while(count <= 42) {
                count = this->generate_count();
            }
            const auto numbers {this->generate_number(count)};
            auto l {this->to_forward_iterator(numbers)};
            vector<int> v(42);
            v.assign(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
            assert(v.size() == count);
            assert(not v.empty());
            assert(v.capacity() == count);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() + count == v.end());
            assert(v.cbegin() + count == v.cend());
            assert(v.front() == numbers[0]);
            assert(v.back() == numbers[count - 1]);
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[numbers_i++]);
            }
            std::cout << "\t\ttest_assign_3/Non-empty vector with assigning size greater than capacity done." << std::endl;
        }

        // non-empty vector with assigning size less than capacity
        {
            std::cout << "\t\tStart checking test_assign_3/Non-empty vector with assigning size less than capacity!" << std::endl;

            // greater than size
            {
                auto count {this->generate_count()};
                while(count <= 1) {
                    count = this->generate_count();
                }
                const auto offset {count / 2};
                const auto real_size {count - offset};
                vector<int> v(count);
                v.cursor -= offset;
                const auto new_size {this->generate_a_random_number(real_size + 1, count)};
                const auto numbers {this->generate_number(new_size)};
                auto l {this->to_forward_iterator(numbers)};
                v.assign(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
                assert(v.size() == new_size);
                assert(not v.empty());
                assert(v.capacity() == count);
                assert(v.spare() == count - new_size);
                assert(v.data() not_eq nullptr);
                assert(v.begin() + new_size == v.end());
                assert(v.cbegin() + new_size == v.cend());
                assert(v.front() == numbers[0]);
                assert(v.back() == numbers[new_size - 1]);
                auto numbers_i {0uz};
                for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto i {0}; i < v.size(); ++i) {
                    assert(v[i] == numbers[numbers_i++]);
                }
                std::cout << "\t\t\ttest_assign_3/Non-empty vector with assigning size less than capacity/Greater than size done." << std::endl;
            }

            // less than size
            {
                auto count {this->generate_count()};
                while(count <= 1) {
                    count = this->generate_count();
                }
                vector<int> v(count);
                auto new_size {this->generate_a_random_number(1, count - 1)};
                v.cursor -= count - new_size;
                const auto numbers {this->generate_number(new_size)};
                auto l {this->to_forward_iterator(numbers)};
                v.assign(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
                assert(v.size() == new_size);
                assert(v.size() == new_size);
                assert(not v.empty());
                assert(v.capacity() == count);
                assert(v.spare() == count - new_size);
                assert(v.data() not_eq nullptr);
                assert(v.begin() + new_size == v.end());
                assert(v.cbegin() + new_size == v.cend());
                assert(v.front() == numbers[0]);
                assert(v.back() == numbers[new_size - 1]);
                auto numbers_i {0uz};
                for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto i {0}; i < v.size(); ++i) {
                    assert(v[i] == numbers[numbers_i++]);
                }
                std::cout << "\t\t\ttest_assign_3/Non-empty vector with assigning size less than capacity/Less than size done." << std::endl;
            }

            // equal to size
            {
                auto count {this->generate_count()};
                vector<int> v(count);
                const auto numbers {this->generate_number(count)};
                auto l {this->to_forward_iterator(numbers)};
                v.assign(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
                assert(v.size() == count);
                assert(not v.empty());
                assert(v.capacity() == count);
                assert(v.spare() == 0);
                assert(v.data() not_eq nullptr);
                assert(v.begin() + count == v.end());
                assert(v.cbegin() + count == v.cend());
                assert(v.front() == numbers[0]);
                assert(v.back() == numbers[count - 1]);
                auto numbers_i {0uz};
                for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto i {0}; i < v.size(); ++i) {
                    assert(v[i] == numbers[numbers_i++]);
                }
                std::cout << "\t\t\ttest_assign_3/Non-empty vector with assigning size less than capacity/Equal to size done." << std::endl;
            }

            std::cout << "\t\tChecking test_assign_3/Non-empty vector with assigning size less than capacity finished!" << std::endl;
        }

        std::cout << "\tChecking test_assign3/Forward iterator for vector finished!" << std::endl;
    }

    // bidirectional iterator
    {
        std::cout << "\tStart checking test_assign_3/Bidirectional iterator for vector!" << std::endl;

        // empty vector to non-empty vector
        {
            vector<int> v {};
            const auto count {this->generate_count()};
            const auto numbers {this->generate_number(count)};
            auto l {this->to_bidirectional_iterator(numbers)};
            v.assign(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
            assert(v.size() == count);
            assert(not v.empty());
            assert(v.capacity() == count);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() + count == v.end());
            assert(v.cbegin() + count == v.cend());
            assert(v.front() == numbers[0]);
            assert(v.back() == numbers[count - 1]);
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[numbers_i++]);
            }
            std::cout << "\t\ttest_assign_3/Empty vector to non-empty vector done." << std::endl;
        }

        // non-empty vector to empty vector
        {
            const auto count {this->generate_count()};
            vector<int> v(count);
            v.assign(int_bidirectional_iterator {}, int_bidirectional_iterator {});
            assert(v.size() == 0);
            assert(v.empty());
            assert(v.capacity() == count);
            assert(v.spare() == count);
            assert(v.begin() == v.end());
            assert(v.cbegin() == v.cend());
            assert(v.rbegin() == v.rend());
            assert(v.crbegin() == v.crend());
            assert(v.data() not_eq nullptr);
            std::cout << "\t\ttest_assign_3/Non-empty vector to vector done." << std::endl;
        }

        // non-empty vector with assigning size greater than capacity
        {
            auto count {this->generate_count()};
            while(count <= 42) {
                count = this->generate_count();
            }
            const auto numbers {this->generate_number(count)};
            auto l {this->to_bidirectional_iterator(numbers)};
            vector<int> v(42);
            v.assign(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
            assert(v.size() == count);
            assert(not v.empty());
            assert(v.capacity() == count);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() + count == v.end());
            assert(v.cbegin() + count == v.cend());
            assert(v.front() == numbers[0]);
            assert(v.back() == numbers[count - 1]);
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[numbers_i++]);
            }
            std::cout << "\t\ttest_assign_3/Non-empty vector with assigning size greater than capacity done." << std::endl;
        }

        // non-empty vector with assigning size less than capacity
        {
            std::cout << "\t\tStart checking test_assign_3/Non-empty vector with assigning size less than capacity!" << std::endl;

            // greater than size
            {
                auto count {this->generate_count()};
                while(count <= 1) {
                    count = this->generate_count();
                }
                const auto offset {count / 2};
                const auto real_size {count - offset};
                vector<int> v(count);
                v.cursor -= offset;
                const auto new_size {this->generate_a_random_number(real_size + 1, count)};
                const auto numbers {this->generate_number(new_size)};
                auto l {this->to_bidirectional_iterator(numbers)};
                v.assign(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
                assert(v.size() == new_size);
                assert(not v.empty());
                assert(v.capacity() == count);
                assert(v.spare() == count - new_size);
                assert(v.data() not_eq nullptr);
                assert(v.begin() + new_size == v.end());
                assert(v.cbegin() + new_size == v.cend());
                assert(v.front() == numbers[0]);
                assert(v.back() == numbers[new_size - 1]);
                auto numbers_i {0uz};
                for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto i {0}; i < v.size(); ++i) {
                    assert(v[i] == numbers[numbers_i++]);
                }
                std::cout << "\t\t\ttest_assign_3/Non-empty vector with assigning size less than capacity/Greater than size done." << std::endl;
            }

            // less than size
            {
                auto count {this->generate_count()};
                while(count <= 1) {
                    count = this->generate_count();
                }
                vector<int> v(count);
                auto new_size {this->generate_a_random_number(1, count - 1)};
                v.cursor -= count - new_size;
                const auto numbers {this->generate_number(new_size)};
                auto l {this->to_bidirectional_iterator(numbers)};
                v.assign(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
                assert(v.size() == new_size);
                assert(v.size() == new_size);
                assert(not v.empty());
                assert(v.capacity() == count);
                assert(v.spare() == count - new_size);
                assert(v.data() not_eq nullptr);
                assert(v.begin() + new_size == v.end());
                assert(v.cbegin() + new_size == v.cend());
                assert(v.front() == numbers[0]);
                assert(v.back() == numbers[new_size - 1]);
                auto numbers_i {0uz};
                for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto i {0}; i < v.size(); ++i) {
                    assert(v[i] == numbers[numbers_i++]);
                }
                std::cout << "\t\t\ttest_assign_3/Non-empty vector with assigning size less than capacity/Less than size done." << std::endl;
            }

            // equal to size
            {
                auto count {this->generate_count()};
                vector<int> v(count);
                const auto numbers {this->generate_number(count)};
                auto l {this->to_bidirectional_iterator(numbers)};
                v.assign(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
                assert(v.size() == count);
                assert(not v.empty());
                assert(v.capacity() == count);
                assert(v.spare() == 0);
                assert(v.data() not_eq nullptr);
                assert(v.begin() + count == v.end());
                assert(v.cbegin() + count == v.cend());
                assert(v.front() == numbers[0]);
                assert(v.back() == numbers[count - 1]);
                auto numbers_i {0uz};
                for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto i {0}; i < v.size(); ++i) {
                    assert(v[i] == numbers[numbers_i++]);
                }
                std::cout << "\t\t\ttest_assign_3/Non-empty vector with assigning size less than capacity/Equal to size done." << std::endl;
            }

            std::cout << "\t\tChecking test_assign_3/Non-empty vector with assigning size less than capacity finished!" << std::endl;
        }

        std::cout << "\tChecking test_assign3/Bidirectional iterator for vector finished!" << std::endl;
    }

    // random access iterator
    {
        std::cout << "\tStart checking test_assign_3/Random access iterator for vector!" << std::endl;

        // empty vector to non-empty vector
        {
            vector<int> v {};
            const auto count {this->generate_count()};
            const auto numbers {this->generate_number(count)};
            auto d {this->to_random_access_iterator(numbers)};
            v.assign(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
            assert(v.size() == count);
            assert(not v.empty());
            assert(v.capacity() == count);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() + count == v.end());
            assert(v.cbegin() + count == v.cend());
            assert(v.front() == numbers[0]);
            assert(v.back() == numbers[count - 1]);
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[numbers_i++]);
            }
            std::cout << "\t\ttest_assign_3/Empty vector to non-empty vector done." << std::endl;
        }

        // non-empty vector to empty vector
        {
            const auto count {this->generate_count()};
            vector<int> v(count);
            v.assign(int_random_access_iterator {}, int_random_access_iterator {});
            assert(v.size() == 0);
            assert(v.empty());
            assert(v.capacity() == count);
            assert(v.spare() == count);
            assert(v.begin() == v.end());
            assert(v.cbegin() == v.cend());
            assert(v.rbegin() == v.rend());
            assert(v.crbegin() == v.crend());
            assert(v.data() not_eq nullptr);
            std::cout << "\t\ttest_assign_3/Non-empty vector to vector done." << std::endl;
        }

        // non-empty vector with assigning size greater than capacity
        {
            auto count {this->generate_count()};
            while(count <= 42) {
                count = this->generate_count();
            }
            const auto numbers {this->generate_number(count)};
            auto d {this->to_random_access_iterator(numbers)};
            vector<int> v(42);
            v.assign(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
            assert(v.size() == count);
            assert(not v.empty());
            assert(v.capacity() == count);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() + count == v.end());
            assert(v.cbegin() + count == v.cend());
            assert(v.front() == numbers[0]);
            assert(v.back() == numbers[count - 1]);
            auto numbers_i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[numbers_i++]);
            }
            std::cout << "\t\ttest_assign_3/Non-empty vector with assigning size greater than capacity done." << std::endl;
        }

        // non-empty vector with assigning size less than capacity
        {
            std::cout << "\t\tStart checking test_assign_3/Non-empty vector with assigning size less than capacity!" << std::endl;

            // greater than size
            {
                auto count {this->generate_count()};
                while(count <= 1) {
                    count = this->generate_count();
                }
                const auto offset {count / 2};
                const auto real_size {count - offset};
                vector<int> v(count);
                v.cursor -= offset;
                const auto new_size {this->generate_a_random_number(real_size + 1, count)};
                const auto numbers {this->generate_number(new_size)};
                auto d {this->to_random_access_iterator(numbers)};
                v.assign(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
                assert(v.size() == new_size);
                assert(not v.empty());
                assert(v.capacity() == count);
                assert(v.spare() == count - new_size);
                assert(v.data() not_eq nullptr);
                assert(v.begin() + new_size == v.end());
                assert(v.cbegin() + new_size == v.cend());
                assert(v.front() == numbers[0]);
                assert(v.back() == numbers[new_size - 1]);
                auto numbers_i {0uz};
                for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto i {0}; i < v.size(); ++i) {
                    assert(v[i] == numbers[numbers_i++]);
                }
                std::cout << "\t\t\ttest_assign_3/Non-empty vector with assigning size less than capacity/Greater than size done." << std::endl;
            }

            // less than size
            {
                auto count {this->generate_count()};
                while(count <= 1) {
                    count = this->generate_count();
                }
                vector<int> v(count);
                auto new_size {this->generate_a_random_number(1, count - 1)};
                v.cursor -= count - new_size;
                const auto numbers {this->generate_number(new_size)};
                auto d {this->to_random_access_iterator(numbers)};
                v.assign(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
                assert(v.size() == new_size);
                assert(v.size() == new_size);
                assert(not v.empty());
                assert(v.capacity() == count);
                assert(v.spare() == count - new_size);
                assert(v.data() not_eq nullptr);
                assert(v.begin() + new_size == v.end());
                assert(v.cbegin() + new_size == v.cend());
                assert(v.front() == numbers[0]);
                assert(v.back() == numbers[new_size - 1]);
                auto numbers_i {0uz};
                for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto i {0}; i < v.size(); ++i) {
                    assert(v[i] == numbers[numbers_i++]);
                }
                std::cout << "\t\t\ttest_assign_3/Non-empty vector with assigning size less than capacity/Less than size done." << std::endl;
            }

            // equal to size
            {
                auto count {this->generate_count()};
                vector<int> v(count);
                const auto numbers {this->generate_number(count)};
                auto d {this->to_random_access_iterator(numbers)};
                v.assign(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
                assert(v.size() == count);
                assert(not v.empty());
                assert(v.capacity() == count);
                assert(v.spare() == 0);
                assert(v.data() not_eq nullptr);
                assert(v.begin() + count == v.end());
                assert(v.cbegin() + count == v.cend());
                assert(v.front() == numbers[0]);
                assert(v.back() == numbers[count - 1]);
                auto numbers_i {0uz};
                for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto i {0}; i < v.size(); ++i) {
                    assert(v[i] == numbers[numbers_i++]);
                }
                std::cout << "\t\t\ttest_assign_3/Non-empty vector with assigning size less than capacity/Equal to size done." << std::endl;
            }

            std::cout << "\t\tChecking test_assign_3/Non-empty vector with assigning size less than capacity finished!" << std::endl;
        }

        std::cout << "\tChecking test_assign3/Random access  iterator for vector finished!" << std::endl;
    }

    std::cout << "Checking void assign(ForwardIterator, ForwardIterator) for vector finished!" << std::endl;
}
void vector_correctness::test_reserve() {
    std::cout << "Start checking reserve for ds::vector!" << std::endl;

    // empty vector
    {
        vector<int> v {};
        v.reserve(0);
        assert(v.size() == 0);
        assert(v.empty());
        assert(v.capacity() == 0);
        assert(v.spare() == 0);
        assert(v.begin() == v.end());
        assert(v.cbegin() == v.cend());
        assert(v.rbegin() == v.rend());
        assert(v.crbegin() == v.crend());
        assert(v.data() == nullptr);

        const auto count {this->generate_count()};
        v.reserve(count);
        assert(v.size() == 0);
        assert(v.empty());
        assert(v.capacity() == count);
        assert(v.spare() == count);
        assert(v.begin() == v.end());
        assert(v.cbegin() == v.cend());
        assert(v.rbegin() == v.rend());
        assert(v.crbegin() == v.crend());
        assert(v.data() not_eq nullptr);

        auto count_2 {this->generate_count(count - 1)};
        v.reserve(count_2);
        assert(v.size() == 0);
        assert(v.empty());
        assert(v.capacity() == count);
        assert(v.spare() == count);
        assert(v.begin() == v.end());
        assert(v.cbegin() == v.cend());
        assert(v.rbegin() == v.rend());
        assert(v.crbegin() == v.crend());
        assert(v.data() not_eq nullptr);

        std::cout << "\tChecking test_reserve/Reserve for empty vector done." << std::endl;
    }

    // non-empty vector
    {
        std::cout << "\tStart checking test_reserve/Reserve for non-empty vector!" << std::endl;

        // greater than capacity
        {
            auto count_1 {this->generate_count()}, count_2 {this->generate_count()};
            while(count_1 == 0) {
                count_1 = this->generate_count();
            }
            while(count_2 == 0 or count_1 == count_2) {
                count_2 = this->generate_count();
            }
            const auto initialization_size {count_1 > count_2 ? count_2 : count_1};
            const auto reserved_size {count_1 > count_2 ? count_1 : count_2};
            const auto number {this->generate_a_random_number()};
            vector<int> v(initialization_size, number);
            v.reserve(reserved_size);
            assert(v.size() == initialization_size);
            assert(not v.empty());
            assert(v.capacity() == reserved_size);
            assert(v.spare() == reserved_size - initialization_size);
            assert(v.data() not_eq nullptr);
            assert(v.begin() + initialization_size == v.end());
            assert(v.cbegin() + initialization_size == v.cend());
            assert(v.front() == number);
            assert(v.back() == number);
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == number);
            }
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == number);
            }
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == number);
            }
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == number);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == number);
            }
            std::cout << "\t\ttest_reserve/Non-empty vector with reserved size greater than capacity done." << std::endl;
        }

        // less equal to capacity
        {
            auto capacity {this->generate_count()};
            while(capacity <= 1) {
                capacity = this->generate_count();
            }
            const auto size {this->generate_a_random_number(1, capacity - 1)};
            const auto number {this->generate_a_random_number()};
            vector<int> v(capacity, number);
            v.cursor = v.first + size;

            // less equal to size
            v.reserve(this->generate_a_random_number(1, size));
            assert(v.size() == size);
            assert(not v.empty());
            assert(v.capacity() == capacity);
            assert(v.spare() == capacity - size);
            assert(v.data() not_eq nullptr);
            assert(v.begin() + size == v.end());
            assert(v.cbegin() + size == v.cend());
            assert(v.front() == number);
            assert(v.back() == number);
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == number);
            }
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == number);
            }
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == number);
            }
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == number);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == number);
            }

            // greater than size but less equal to capacity
            v.reserve(this->generate_a_random_number(size + 1, capacity));
            assert(v.size() == size);
            assert(not v.empty());
            assert(v.capacity() == capacity);
            assert(v.spare() == capacity - size);
            assert(v.data() not_eq nullptr);
            assert(v.begin() + size == v.end());
            assert(v.cbegin() + size == v.cend());
            assert(v.front() == number);
            assert(v.back() == number);
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == number);
            }
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == number);
            }
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == number);
            }
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == number);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == number);
            }
            std::cout << "\t\ttest_reserve/Non-empty vector with reserved size less equal to capacity done." << std::endl;
        }

        std::cout << "\tChecking test_reserve/Reserve for non-empty vector finished!" << std::endl;
    }

    std::cout << "Checking reserve for ds::vector finished!" << std::endl;
}
void vector_correctness::test_shrink_to_fit() {
    std::cout << "Start checking shrink_to_fit for ds::vector!" << std::endl;

    // empty
    {
        vector<int> v {};
        v.shrink_to_fit();
        assert(v.size() == 0);
        assert(v.empty());
        assert(v.capacity() == 0);
        assert(v.spare() == 0);
        assert(v.begin() == v.end());
        assert(v.cbegin() == v.cend());
        assert(v.rbegin() == v.rend());
        assert(v.crbegin() == v.crend());
        assert(v.data() == nullptr);

        v = vector<int>(this->generate_count(), this->generate_a_random_number());
        v.cursor = v.first;
        v.shrink_to_fit();
        assert(v.size() == 0);
        assert(v.empty());
        assert(v.capacity() == 0);
        assert(v.spare() == 0);
        assert(v.begin() == v.end());
        assert(v.cbegin() == v.cend());
        assert(v.rbegin() == v.rend());
        assert(v.crbegin() == v.crend());
        assert(v.data() == nullptr);

        std::cout << "\tChecking test_shrink_to_fit/Empty vector done." << std::endl;
    }

    // non-empty
    {
        auto count {this->generate_count()};
        while(count <= 1) {
            count = this->generate_count();
        }
        const auto number {this->generate_a_random_number()};
        vector<int> v(count, number);
        v.shrink_to_fit();
        assert(v.size() == count);
        assert(not v.empty());
        assert(v.capacity() == count);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + count == v.end());
        assert(v.cbegin() + count == v.cend());
        assert(v.front() == number);
        assert(v.back() == number);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == number);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == number);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == number);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == number);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == number);
        }

        const auto real_size {count / 2};
        v.cursor = v.first + real_size;
        v.shrink_to_fit();
        assert(v.size() == real_size);
        assert(not v.empty());
        assert(v.capacity() == real_size);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + real_size == v.end());
        assert(v.cbegin() + real_size == v.cend());
        assert(v.front() == number);
        assert(v.back() == number);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == number);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == number);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == number);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == number);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == number);
        }

        std::cout << "\tChecking test_shrink_to_fit/Non-empty vector done." << std::endl;
    }

    std::cout << "Checking shrink_to_fit for ds::vector finished!" << std::endl;
}
void vector_correctness::test_resize_1() {
    std::cout << "Start checking void resize(size_type) for ds::vector!" << std::endl;

    // empty to empty
    {
        vector<int> v {};
        v.resize(0);
        assert(v.size() == 0);
        assert(v.empty());
        assert(v.capacity() == 0);
        assert(v.spare() == 0);
        assert(v.begin() == v.end());
        assert(v.cbegin() == v.cend());
        assert(v.rbegin() == v.rend());
        assert(v.crbegin() == v.crend());
        assert(v.data() == nullptr);
        std::cout << "\tChecking test_resize_1/Empty to empty done." << std::endl;
    }

    // empty to non-empty
    {
        vector<int> v {};
        const auto count {this->generate_count()};
        v.resize(count);
        assert(v.size() == count);
        assert(not v.empty());
        assert(v.capacity() == count);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + count == v.end());
        assert(v.cbegin() + count == v.cend());
        assert(v.front() == 0);
        assert(v.back() == 0);
        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
            assert(*it == 0);
        }
        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
            assert(*it == 0);
        }
        for(auto i {0}; i < v.size(); ++i) {
            assert(v[i] == 0);
        }
        std::cout << "\tChecking test_resize_1/Empty to non-empty done." << std::endl;
    }

    // non-empty to empty
    {
        const auto count {this->generate_count()};
        vector<int> v(count);
        v.resize(0);
        assert(v.size() == 0);
        assert(v.empty());
        assert(v.capacity() == 0);
        assert(v.spare() == 0);
        assert(v.begin() == v.end());
        assert(v.cbegin() == v.cend());
        assert(v.rbegin() == v.rend());
        assert(v.crbegin() == v.crend());
        assert(v.data() == nullptr);
        std::cout << "\tChecking test_resize_1/Non-empty to empty done." << std::endl;
    }

    // non-empty to non-empty
    {
        std::cout << "\tStart checking test_resize_1/Non-empty to non-empty for ds::vector!" << std::endl;

        // less than size
        {
            //const auto count {this->generate_count()};
            const auto count {42};
            const auto new_size {this->generate_count(count - 1)};
            const auto number {this->generate_a_random_number()};
            vector<int> v(count, number);
            v.resize(new_size);
            assert(v.size() == new_size);
            assert(not v.empty());
            assert(v.capacity() == new_size);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() + new_size == v.end());
            assert(v.cbegin() + new_size == v.cend());
            assert(v.front() == number);
            assert(v.back() == number);
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == number);
            }
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == number);
            }
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == number);
            }
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == number);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == number);
            }
            std::cout << "\t\tChecking test_resize_1/Non-empty to non-empty/Less than size done." << std::endl;
        }

        // equal to size
        {
            const auto count {this->generate_count()};
            const auto number {this->generate_a_random_number()};
            vector<int> v(count, number);
            v.resize(count);
            assert(v.size() == count);
            assert(not v.empty());
            assert(v.capacity() == count);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() + count == v.end());
            assert(v.cbegin() + count == v.cend());
            assert(v.front() == number);
            assert(v.back() == number);
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == number);
            }
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == number);
            }
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == number);
            }
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == number);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == number);
            }
            std::cout << "\t\tChecking test_resize_1/Non-empty to non-empty/Equal to size done." << std::endl;
        }

        // greater than size
        {
            const auto count {this->generate_count()};
            const auto new_size {this->generate_a_random_number(count + 1)};
            const auto number {this->generate_a_random_number()};
            vector<int> v(count, number);
            v.resize(new_size);
            assert(v.size() == new_size);
            assert(not v.empty());
            assert(v.capacity() == new_size);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() + new_size == v.end());
            assert(v.cbegin() + new_size == v.cend());
            assert(v.front() == number);
            assert(v.back() == 0);
            const auto offset {new_size - count};
            for(auto it {v.begin()}; it not_eq v.end() - offset; ++it) {
                assert(*it == number);
            }
            for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                assert(*it == 0);
            }
            for(auto it {v.cbegin()}; it not_eq v.cend() - offset; ++it) {
                assert(*it == number);
            }
            for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                assert(*it == 0);
            }
            for(auto it {v.rbegin()}; it not_eq v.rend() - count; ++it) {
                assert(*it == 0);
            }
            for(auto it {v.rbegin() + offset}; it not_eq v.rend(); ++it) {
                assert(*it == number);
            }
            for(auto it {v.crbegin()}; it not_eq v.crend() - count; ++it) {
                assert(*it == 0);
            }
            for(auto it {v.rbegin() + offset}; it not_eq v.rend(); ++it) {
                assert(*it == number);
            }
            for(auto i {0}; i < v.size() - offset; ++i) {
                assert(v[i] == number);
            }
            for(auto i {count}; i < v.size(); ++i) {
                assert(v[i] == 0);
            }
            std::cout << "\t\tChecking test_resize_1/Non-empty to non-empty/Greater than size done." << std::endl;
        }

        std::cout << "\tChecking test_resize_1/Non-empty to non-empty for ds::vector finished!" << std::endl;
    }

    std::cout << "Checking void resize(size_type) for ds::vector finished!" << std::endl;
}