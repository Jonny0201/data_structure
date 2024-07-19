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
    // vector(size_type)
    void test_constructor_2();
    // vector(size_type, const T &)
    void test_constructor_3();
    // vector(InputIterator, InputIterator)
    void test_constructor_4();
    // vector(ForwardIterator, ForwardIterator)
    void test_constructor_5();
    // vector(initializer_list<T>)
    void test_constructor_6();
    // vector(const vector &)
    void test_copy_constructor();
    // vector(vector &&)
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
    void test_emplace_back();
    void test_pop_back();
    void test_clear();
    void test_swap();
    void test_emplace();
    // iterator insert(difference_type, const_reference, size_type)
    void test_insert_1();
    // iterator insert(InputIterator, InputIterator)
    void test_insert_2();
    // iterator insert(ForwardIterator, ForwardIterator)
    void test_insert_3();
    // iterator erase(difference_type, size_type)
    void test_erase();
    void test_allocator();
    void test_non_trivial();
};

void vector_unit_test() {
    auto correctness {new vector_correctness {}};
    correctness->test_default_constructor();
    correctness->test_constructor_1();
    correctness->test_constructor_2();
    correctness->test_constructor_3();
    correctness->test_constructor_4();
    correctness->test_constructor_5();
    correctness->test_constructor_6();
    correctness->test_copy_constructor();
    correctness->test_move_constructor();
    correctness->test_copy_assignment();
    correctness->test_move_assignment();
    correctness->test_assign_1();
    correctness->test_assign_2();
    correctness->test_assign_3();
    correctness->test_reserve();
    correctness->test_shrink_to_fit();
    correctness->test_resize_1();
    correctness->test_resize_2();
    correctness->test_emplace_back();
    correctness->test_pop_back();
    correctness->test_clear();
    correctness->test_swap();
    correctness->test_emplace();
    correctness->test_insert_1();
    correctness->test_insert_2();
    correctness->test_insert_3();
    correctness->test_erase();
    correctness->test_allocator();
    correctness->test_non_trivial();
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
        assert(v.crbegin() == v.crend());
        assert(v.data() == nullptr);
        std::cout << "\ttest_default_constructor_2/Empty vector checking done." << std::endl;
    }

    // random size
    {
        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
        vector<int> v(count);
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
        std::cout << "\ttest_constructor_2/Random count done." << std::endl;
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
        assert(v.crbegin() == v.crend());
        assert(v.data() == nullptr);
        std::cout << "\ttest_constructor_3/Empty vector checking done." << std::endl;
    }

    // random size
    {
        auto e {this->generate_a_random_number()};
        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
        vector<int> v(count, e);
        assert(v.size() == count);
        assert(not v.empty());
        assert(v.capacity() == count);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + count == v.end());
        assert(v.cbegin() + count == v.cend());
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
        std::cout << "\ttest_constructor_3/Random count done." << std::endl;
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
        assert(v.crbegin() == v.crend());
        assert(v.data() == nullptr);
        std::cout << "\ttest_constructor_4/Empty vector checking done." << std::endl;
    }

    // random size
    {
        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
        const auto numbers {this->generate_number(count)};
        auto stream {this->to_input_iterator(numbers)};
        vector<int> v(int_input_iterator {stream}, {});
        assert(v.size() == count);
        assert(not v.empty());
        assert(v.capacity() == count);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() not_eq v.end());
        assert(v.begin() + count == v.end());
        assert(v.cbegin() not_eq v.cend());
        assert(v.cbegin() + count == v.cend());
        assert(v.cbegin() not_eq v.end());
        assert(v.cbegin() + count == v.end());
        assert(v.begin() not_eq v.cend());
        assert(v.begin() + count == v.cend());
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
        std::cout << "\ttest_constructor_4/Random count done." << std::endl;
    }

    std::cout << "Checking vector(InputIterator, InputIterator), size, empty and iterator finished!" << std::endl;
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

        // random size
        {
            auto count {this->generate_count()};
            while(count == 0) {
                count = this->generate_count();
            }
            const auto numbers {this->generate_number(count)};
            auto l {this->to_forward_iterator(numbers)};
            vector<int> v(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
            assert(v.size() == count);
            assert(not v.empty());
            assert(v.capacity() == count);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + count == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + count == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + count == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + count == v.cend());
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
            std::cout << "\t\ttest_constructor_5/Forward iterator/Random count done." << std::endl;
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

        // random size
        {
            auto count {this->generate_count()};
            while(count == 0) {
                count = this->generate_count();
            }
            const auto numbers {this->generate_number(count)};
            auto l {this->to_bidirectional_iterator(numbers)};
            vector<int> v(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
            assert(v.size() == count);
            assert(not v.empty());
            assert(v.capacity() == count);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + count == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + count == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + count == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + count == v.cend());
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
            std::cout << "\t\ttest_constructor_5/Bidirectional iterator/Random count done." << std::endl;
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

        // random size
        {
            auto count {this->generate_count()};
            while(count == 0) {
                count = this->generate_count();
            }
            const auto numbers {this->generate_number(count)};
            auto d {this->to_random_access_iterator(numbers)};
            vector<int> v(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
            assert(v.size() == count);
            assert(not v.empty());
            assert(v.capacity() == count);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() not_eq v.end());
            assert(v.begin() + count == v.end());
            assert(v.cbegin() not_eq v.cend());
            assert(v.cbegin() + count == v.cend());
            assert(v.cbegin() not_eq v.end());
            assert(v.cbegin() + count == v.end());
            assert(v.begin() not_eq v.cend());
            assert(v.begin() + count == v.cend());
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
            std::cout << "\t\ttest_constructor_5/Random access iterator/Random count done." << std::endl;
        }
        std::cout << "\tChecking bidirectional iterator version finished!" << std::endl;
    }

    std::cout << "Checking vector(ForwardIterator, ForwardIterator) finished!" << std::endl;
}
void vector_correctness::test_constructor_6() {
    std::cout << "Start checking vector(initializer_list<T>)!" << std::endl;

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
        assert(v.crbegin() == v.crend());
        assert(v.data() == nullptr);
        std::cout << "\ttest_default_copy_constructor/Empty vector checking done." << std::endl;
    }

    // random size
    {
        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
        vector<int> v0(count);
        auto v {v0};
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
        std::cout << "\ttest_copy_constructor/Random count done." << std::endl;
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
        assert(v.crbegin() == v.crend());
        assert(v.data() == nullptr);
        std::cout << "\ttest_default_move_constructor/Empty vector checking done." << std::endl;
    }

    // random size
    {
        auto size {this->generate_count()};
        while(size == 0) {
            size = this->generate_count();
        }
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
        std::cout << "\ttest_move_constructor/Random size done." << std::endl;
    }

    std::cout << "Checking move constructor finished!" << std::endl;
}
void vector_correctness::test_copy_assignment() {
    std::cout << "Start checking copy assignment for ds::vector!" << std::endl;

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
        assert(v.crbegin() == v.crend());
        assert(v.data() == nullptr);
        if(not rechecked) {
            v = v;
            rechecked = true;
            goto RECHECK_EMPTY;
        }
        std::cout << "\ttest_default_copy_assignment/Empty vector checking done." << std::endl;
    }

    // random size
    {
        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
        vector<int> v0(count);
        vector<int> v {};
        v = v0;
        bool rechecked {};
        RECHECK_RANDOM : assert(v.size() == count);
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
        if(not rechecked) {
            v = v;
            rechecked = true;
            goto RECHECK_RANDOM;
        }
        std::cout << "\ttest_copy_assignment/Random sized elements done." << std::endl;
    }

    std::cout << "Checking copy assignment for ds::vector finished!" << std::endl;
}
void vector_correctness::test_move_assignment() {
    std::cout << "Start checking move assignment for ds::vector!" << std::endl;

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
        assert(v.crbegin() == v.crend());
        assert(v.data() == nullptr);
        if(not rechecked) {
            v = move(v);
            rechecked = true;
            goto RECHECK_EMPTY;
        }
        std::cout << "\tChecking test_move_assignment/Empty vector checking done." << std::endl;
    }

    // random size
    {
        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
        vector<int> v0(count);
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
        RECHECK_RANDOM : assert(v.size() == count);
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
        if(not rechecked) {
            v = move(v);
            rechecked = true;
            goto RECHECK_RANDOM;
        }
        std::cout << "\tChecking test_move_assignment/Random count done." << std::endl;
    }

    std::cout << "Checking move assignment for ds::vector finished!" << std::endl;
}
void vector_correctness::test_assign_1() {
    std::cout << "Start checking void assign(size_type, const_reference) for vector!" << std::endl;

    // empty vector to non-empty vector
    {
        vector<int> v {};
        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
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
        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
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
            while(count == 0) {
                count = this->generate_count();
            }
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
        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
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
            while(count == 0) {
                count = this->generate_count();
            }
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
            auto count {this->generate_count()};
            while(count == 0) {
                count = this->generate_count();
            }
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
            auto count {this->generate_count()};
            while(count == 0) {
                count = this->generate_count();
            }
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
                while(count == 0) {
                    count = this->generate_count();
                }
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
            auto count {this->generate_count()};
            while(count == 0) {
                count = this->generate_count();
            }
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
            auto count {this->generate_count()};
            while(count == 0) {
                count = this->generate_count();
            }
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
                while(count == 0) {
                    count = this->generate_count();
                }
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
            auto count {this->generate_count()};
            while(count == 0) {
                count = this->generate_count();
            }
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
            auto count {this->generate_count()};
            while(count == 0) {
                count = this->generate_count();
            }
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
                while(count == 0) {
                    count = this->generate_count();
                }
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
        assert(v.crbegin() == v.crend());
        assert(v.data() == nullptr);

        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
        v.reserve(count);
        assert(v.size() == 0);
        assert(v.empty());
        assert(v.capacity() == count);
        assert(v.spare() == count);
        assert(v.begin() == v.end());
        assert(v.cbegin() == v.cend());
        assert(v.rbegin() == v.rend());
        assert(v.crbegin() == v.crend());
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
        assert(v.crbegin() == v.crend());
        assert(v.data() == nullptr);
        std::cout << "\tChecking test_resize_1/Empty to empty done." << std::endl;
    }

    // empty to non-empty
    {
        vector<int> v {};
        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
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
        assert(v.crbegin() == v.crend());
        assert(v.data() == nullptr);
        std::cout << "\tChecking test_resize_1/Non-empty to empty done." << std::endl;
    }

    // non-empty to non-empty
    {
        std::cout << "\tStart checking test_resize_1/Non-empty to non-empty for ds::vector!" << std::endl;

        // less than size
        {
            auto count {this->generate_count()};
            while(count <= 1) {
                count = this->generate_count();
            }
            auto new_size {this->generate_count(count - 1)};
            while(new_size == 0) {
                new_size = this->generate_count(count - 1);
            }
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
            auto count {this->generate_count()};
            while(count == 0) {
                count = this->generate_count();
            }
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
            auto count {this->generate_count(std::numeric_limits<int>::max() - 1)};
            while(count == 0) {
                count = this->generate_count(std::numeric_limits<int>::max() - 1);
            }
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
void vector_correctness::test_resize_2() {
    std::cout << "Start checking void resize(size_type, const_reference) for ds::vector!" << std::endl;

    // empty to empty
    {
        vector<int> v {};
        v.resize(0, this->generate_a_random_number());
        assert(v.size() == 0);
        assert(v.empty());
        assert(v.capacity() == 0);
        assert(v.spare() == 0);
        assert(v.begin() == v.end());
        assert(v.cbegin() == v.cend());
        assert(v.rbegin() == v.rend());
        assert(v.crbegin() == v.crend());
        assert(v.crbegin() == v.crend());
        assert(v.data() == nullptr);
        std::cout << "\tChecking test_resize_1/Empty to empty done." << std::endl;
    }

    // empty to non-empty
    {
        vector<int> v {};
        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
        const auto number {this->generate_a_random_number()};
        v.resize(count, number);
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
        std::cout << "\tChecking test_resize_1/Empty to non-empty done." << std::endl;
    }

    // non-empty to empty
    {
        const auto count {this->generate_count()};
        vector<int> v(count, this->generate_a_random_number());
        v.resize(0);
        assert(v.size() == 0);
        assert(v.empty());
        assert(v.capacity() == 0);
        assert(v.spare() == 0);
        assert(v.begin() == v.end());
        assert(v.cbegin() == v.cend());
        assert(v.rbegin() == v.rend());
        assert(v.crbegin() == v.crend());
        assert(v.crbegin() == v.crend());
        assert(v.data() == nullptr);
        std::cout << "\tChecking test_resize_1/Non-empty to empty done." << std::endl;
    }

    // non-empty to non-empty
    {
        std::cout << "\tStart checking test_resize_1/Non-empty to non-empty for ds::vector!" << std::endl;

        // less than size
        {
            auto count {this->generate_count()};
            while(count <= 1) {
                count = this->generate_count();
            }
            auto new_size {this->generate_count(count - 1)};
            while(new_size == 0) {
                new_size = this->generate_count(count - 1);
            }
            const auto number {this->generate_a_random_number()};
            vector<int> v(count, number);
            auto number_2 {this->generate_a_random_number()};
            while(number == number_2) {
                number_2 = this->generate_a_random_number();
            }
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
            auto count {this->generate_count()};
            while(count == 0) {
                count = this->generate_count();
            }
            const auto number {this->generate_a_random_number()};
            vector<int> v(count, number);
            auto number_2 {this->generate_a_random_number()};
            while(number == number_2) {
                number_2 = this->generate_a_random_number();
            }
            v.resize(count, number_2);
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
            auto count {this->generate_count(std::numeric_limits<int>::max() - 1)};
            while(count == 0) {
                count = this->generate_count(std::numeric_limits<int>::max() - 1);
            }
            const auto new_size {this->generate_a_random_number(count + 1)};
            const auto number {this->generate_a_random_number()};
            vector<int> v(count, number);
            auto number_2 {this->generate_a_random_number()};
            while(number == number_2) {
                number_2 = this->generate_a_random_number();
            }
            v.resize(new_size, number_2);
            assert(v.size() == new_size);
            assert(not v.empty());
            assert(v.capacity() == new_size);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() + new_size == v.end());
            assert(v.cbegin() + new_size == v.cend());
            assert(v.front() == number);
            assert(v.back() == number_2);
            const auto offset {new_size - count};
            for(auto it {v.begin()}; it not_eq v.end() - offset; ++it) {
                assert(*it == number);
            }
            for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                assert(*it == number_2);
            }
            for(auto it {v.cbegin()}; it not_eq v.cend() - offset; ++it) {
                assert(*it == number);
            }
            for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                assert(*it == number_2);
            }
            for(auto it {v.rbegin()}; it not_eq v.rend() - count; ++it) {
                assert(*it == number_2);
            }
            for(auto it {v.rbegin() + offset}; it not_eq v.rend(); ++it) {
                assert(*it == number);
            }
            for(auto it {v.crbegin()}; it not_eq v.crend() - count; ++it) {
                assert(*it == number_2);
            }
            for(auto it {v.rbegin() + offset}; it not_eq v.rend(); ++it) {
                assert(*it == number);
            }
            for(auto i {0}; i < v.size() - offset; ++i) {
                assert(v[i] == number);
            }
            for(auto i {count}; i < v.size(); ++i) {
                assert(v[i] == number_2);
            }
            std::cout << "\t\tChecking test_resize_1/Non-empty to non-empty/Greater than size done." << std::endl;
        }

        std::cout << "\tChecking test_resize_1/Non-empty to non-empty for ds::vector finished!" << std::endl;
    }

    std::cout << "Checking void resize(size_type) for ds::vector finished!" << std::endl;
}
void vector_correctness::test_emplace_back() {
    std::cout << "Start checking void emplace_back(Args &&...) for ds::vector!" << std::endl;

    // empty
    {
        vector<int> v {};
        const auto number {this->generate_a_random_number()};
        v.emplace_back(number);
        assert(v.size() == 1);
        assert(not v.empty());
        assert(v.capacity() == 1);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + 1 == v.end());
        assert(v.cbegin() + 1 == v.cend());
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

        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
        v = vector<int>(count);
        v.cursor = v.first;
        v.emplace_back(number);
        assert(v.size() == 1);
        assert(not v.empty());
        assert(v.capacity() == count);
        assert(v.spare() == count - 1);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + 1 == v.end());
        assert(v.cbegin() + 1 == v.cend());
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

        std::cout << "\tChecking test_emplace_back/Empty done." << std::endl;
    }

    // non-empty
    {
        std::cout << "\tStart checking test_emplace_back/Non-empty for ds::vector!" << std::endl;

        // not full
        {
            auto count {this->generate_count()};
            while(count <= 1) {
                count = this->generate_count();
            }
            const auto number {this->generate_a_random_number()};
            vector<int> v(count, number);
            auto number_2 {this->generate_a_random_number()};
            while(number == number_2) {
                number_2 = this->generate_a_random_number();
            }
            auto new_size {this->generate_a_random_number(0, count - 1)};
            while(new_size == 0) {
                new_size = this->generate_a_random_number(0, count - 1);
            }
            v.cursor = v.first + new_size;
            v.emplace_back(number_2);
            assert(v.size() == new_size + 1);
            assert(not v.empty());
            assert(v.capacity() == count);
            assert(v.spare() == count - new_size - 1);
            assert(v.data() not_eq nullptr);
            assert(v.begin() + (new_size + 1) == v.end());
            assert(v.cbegin() + (new_size + 1) == v.cend());
            assert(v.front() == number);
            assert(v.back() == number_2);
            for(auto it {v.begin()}; it not_eq v.end() - 1; ++it) {
                assert(*it == number);
            }
            assert(*(v.end() - 1) == number_2);
            for(auto it {v.cbegin()}; it not_eq v.cend() - 1; ++it) {
                assert(*it == number);
            }
            assert(*(v.cend() - 1) == number_2);
            for(auto it {v.rbegin() + 1}; it not_eq v.rend(); ++it) {
                assert(*it == number);
            }
            assert(*v.rbegin() == number_2);
            for(auto it {v.crbegin() + 1}; it not_eq v.crend(); ++it) {
                assert(*it == number);
            }
            assert(*v.crbegin() == number_2);
            for(auto i {0}; i < v.size() - 1; ++i) {
                assert(v[i] == number);
            }
            assert(v[v.size() - 1] == number_2);
            std::cout << "\t\tChecking test_emplace_back/Non-empty vector/Not full done." << std::endl;
        }

        // full
        {
            auto count {this->generate_count(std::numeric_limits<int>::max() - 1)};
            while(count == 0) {
                count = this->generate_count(std::numeric_limits<int>::max() - 1);
            }
            const auto number {this->generate_a_random_number()};
            vector<int> v(count, number);
            auto number_2 {this->generate_a_random_number()};
            while(number == number_2) {
                number_2 = this->generate_a_random_number();
            }
            v.emplace_back(number_2);
            assert(v.size() == count + 1);
            assert(not v.empty());
            assert(v.capacity() == static_cast<size_t>(count) * 2);
            assert(v.spare() == count - 1);
            assert(v.data() not_eq nullptr);
            assert(v.begin() + (count + 1) == v.end());
            assert(v.cbegin() + (count + 1) == v.cend());
            assert(v.front() == number);
            assert(v.back() == number_2);
            for(auto it {v.begin()}; it not_eq v.end() - 1; ++it) {
                assert(*it == number);
            }
            assert(*(v.end() - 1) == number_2);
            for(auto it {v.cbegin()}; it not_eq v.cend() - 1; ++it) {
                assert(*it == number);
            }
            assert(*(v.cend() - 1) == number_2);
            for(auto it {v.rbegin() + 1}; it not_eq v.rend(); ++it) {
                assert(*it == number);
            }
            assert(*v.rbegin() == number_2);
            for(auto it {v.crbegin() + 1}; it not_eq v.crend(); ++it) {
                assert(*it == number);
            }
            assert(*v.crbegin() == number_2);
            for(auto i {0}; i < v.size() - 1; ++i) {
                assert(v[i] == number);
            }
            assert(v[v.size() - 1] == number_2);
            std::cout << "\t\tChecking test_emplace_back/Non-empty vector/Not full done." << std::endl;
        }

        std::cout << "\tChecking test_emplace_back/Non-empty for ds::vector finished!" << std::endl;
    }

    // type implicit conversion
    {
        vector<int> v {};
        v.emplace_back(42.2);
        assert(v.size() == 1);
        assert(not v.empty());
        assert(v.capacity() == 1);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + 1 == v.end());
        assert(v.cbegin() + 1 == v.cend());
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
    }

    std::cout << "Checking void emplace_back(Args &&...) for ds::vector finished!" << std::endl;
}
void vector_correctness::test_pop_back() {
    std::cout << "Start checking void pop_back() for ds::vector!" << std::endl;

    // size == 1
    {
        vector<int> v(1);
        v.pop_back();
        assert(v.size() == 0);
        assert(v.empty());
        assert(v.capacity() == 1);
        assert(v.spare() == 1);
        assert(v.data() not_eq nullptr);
        assert(v.begin() == v.end());
        assert(v.cbegin() == v.cend());
        assert(v.rbegin() == v.rend());
        assert(v.crbegin() == v.crend());
        std::cout << "\tChecking test_pop_back/Size equal to 1 done." << std::endl;
    }

    // random size
    {
        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
        const auto pop_count {this->generate_count(count - 1)};
        const auto number {this->generate_a_random_number()};
        vector<int> v(count, number);
        for(auto i {0}; i < pop_count; ++i) {
            v.pop_back();
        }
        assert(v.size() == count - pop_count);
        assert(not v.empty());
        assert(v.capacity() == count);
        assert(v.spare() == pop_count);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + (count - pop_count) == v.end());
        assert(v.cbegin() + (count - pop_count) == v.cend());
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
        std::cout << "\tChecking test_pop_back/Random size done." << std::endl;
    }

    std::cout << "Checking void pop_back() for ds::vector finished!" << std::endl;
}
void vector_correctness::test_clear() {
    std::cout << "Start checking void clear() for ds::vector!" << std::endl;

    // empty
    {
        vector<int> v {};
        v.clear();
        assert(v.size() == 0);
        assert(v.empty());
        assert(v.capacity() == 0);
        assert(v.spare() == 0);
        assert(v.data() == nullptr);
        assert(v.begin() == v.end());
        assert(v.cbegin() == v.cend());
        assert(v.rbegin() == v.rend());
        assert(v.crbegin() == v.crend());

        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
        v = vector<int>(count);
        v.cursor = v.first;
        v.clear();
        assert(v.size() == 0);
        assert(v.empty());
        assert(v.capacity() == count);
        assert(v.spare() == count);
        assert(v.data() not_eq nullptr);
        assert(v.begin() == v.end());
        assert(v.cbegin() == v.cend());
        assert(v.rbegin() == v.rend());
        assert(v.crbegin() == v.crend());

        std::cout << "\tChecking test_clear/Empty vector done." << std::endl;
    }

    // non-empty
    {
        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
        vector<int> v(count, this->generate_a_random_number());
        v.clear();
        assert(v.size() == 0);
        assert(v.empty());
        assert(v.capacity() == count);
        assert(v.spare() == count);
        assert(v.data() not_eq nullptr);
        assert(v.begin() == v.end());
        assert(v.cbegin() == v.cend());
        assert(v.rbegin() == v.rend());
        assert(v.crbegin() == v.crend());
        std::cout << "\tChecking test_clear/Non-empty vector done." << std::endl;
    }

    std::cout << "Checking void clear() for ds::vector finished!" << std::endl;
}
void vector_correctness::test_swap() {
    std::cout << "Start checking void swap() for ds::vector!" << std::endl;

    // swap empty capacity with empty capacity
    {
        vector<int> v1 {}, v2 {};
        v1.swap(v2);
        assert(v1.size() == 0);
        assert(v1.empty());
        assert(v1.capacity() == 0);
        assert(v1.spare() == 0);
        assert(v1.data() == nullptr);
        assert(v1.begin() == v1.end());
        assert(v1.cbegin() == v1.cend());
        assert(v1.rbegin() == v1.rend());
        assert(v1.crbegin() == v1.crend());
        assert(v2.size() == 0);
        assert(v2.empty());
        assert(v2.capacity() == 0);
        assert(v2.spare() == 0);
        assert(v2.data() == nullptr);
        assert(v2.begin() == v2.end());
        assert(v2.cbegin() == v2.cend());
        assert(v2.rbegin() == v2.rend());
        assert(v2.crbegin() == v2.crend());

        v1.swap(v2);        // revert
        assert(v1.size() == 0);
        assert(v1.empty());
        assert(v1.capacity() == 0);
        assert(v1.spare() == 0);
        assert(v1.data() == nullptr);
        assert(v1.begin() == v1.end());
        assert(v1.cbegin() == v1.cend());
        assert(v1.rbegin() == v1.rend());
        assert(v1.crbegin() == v1.crend());
        assert(v2.size() == 0);
        assert(v2.empty());
        assert(v2.capacity() == 0);
        assert(v2.spare() == 0);
        assert(v2.data() == nullptr);
        assert(v2.begin() == v2.end());
        assert(v2.cbegin() == v2.cend());
        assert(v2.rbegin() == v2.rend());
        assert(v2.crbegin() == v2.crend());

        std::cout << "\tChecking test_swap/Swap empty capacity with empty capacity done." << std::endl;
    }

    // swap empty capacity with non-zero capacity empty
    {
        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
        vector<int> v1 {}, v2(count, this->generate_a_random_number());
        v2.cursor = v2.first;
        v1.swap(v2);
        assert(v1.size() == 0);
        assert(v1.empty());
        assert(v1.capacity() == count);
        assert(v1.spare() == count);
        assert(v1.data() not_eq nullptr);
        assert(v1.begin() == v1.end());
        assert(v1.cbegin() == v1.cend());
        assert(v1.rbegin() == v1.rend());
        assert(v1.crbegin() == v1.crend());
        assert(v2.size() == 0);
        assert(v2.empty());
        assert(v2.capacity() == 0);
        assert(v2.spare() == 0);
        assert(v2.data() == nullptr);
        assert(v2.begin() == v2.end());
        assert(v2.cbegin() == v2.cend());
        assert(v2.rbegin() == v2.rend());
        assert(v2.crbegin() == v2.crend());

        v1.swap(v2);        // revert
        assert(v1.size() == 0);
        assert(v1.empty());
        assert(v1.capacity() == 0);
        assert(v1.spare() == 0);
        assert(v1.data() == nullptr);
        assert(v1.begin() == v1.end());
        assert(v1.cbegin() == v1.cend());
        assert(v1.rbegin() == v1.rend());
        assert(v1.crbegin() == v1.crend());
        assert(v2.size() == 0);
        assert(v2.empty());
        assert(v2.capacity() == count);
        assert(v2.spare() == count);
        assert(v2.data() not_eq nullptr);
        assert(v2.begin() == v2.end());
        assert(v2.cbegin() == v2.cend());
        assert(v2.rbegin() == v2.rend());
        assert(v2.crbegin() == v2.crend());

        std::cout << "\tChecking test_swap/Swap empty capacity with non-zero capacity empty done." << std::endl;
    }

    // swap non-zero capacity empty with non-zero capacity empty
    {
        auto count_1 {this->generate_count()}, count_2 {this->generate_count()};
        while(count_1 == 0) {
            count_1 = this->generate_count();
        }
        while(count_2 == 0) {
            count_2 = this->generate_count();
        }
        vector<int> v1(count_1, this->generate_a_random_number()), v2(count_2, this->generate_a_random_number());
        v1.cursor = v1.first;
        v2.cursor = v2.first;
        v1.swap(v2);
        assert(v1.size() == 0);
        assert(v1.empty());
        assert(v1.capacity() == count_2);
        assert(v1.spare() == count_2);
        assert(v1.data() not_eq nullptr);
        assert(v1.begin() == v1.end());
        assert(v1.cbegin() == v1.cend());
        assert(v1.rbegin() == v1.rend());
        assert(v1.crbegin() == v1.crend());
        assert(v2.size() == 0);
        assert(v2.empty());
        assert(v2.capacity() == count_1);
        assert(v2.spare() == count_1);
        assert(v2.data() not_eq nullptr);
        assert(v2.begin() == v2.end());
        assert(v2.cbegin() == v2.cend());
        assert(v2.rbegin() == v2.rend());
        assert(v2.crbegin() == v2.crend());
        assert(v1.data() not_eq v2.data());

        v1.swap(v2);        // revert
        assert(v1.size() == 0);
        assert(v1.empty());
        assert(v1.capacity() == count_1);
        assert(v1.spare() == count_1);
        assert(v1.data() not_eq nullptr);
        assert(v1.begin() == v1.end());
        assert(v1.cbegin() == v1.cend());
        assert(v1.rbegin() == v1.rend());
        assert(v1.crbegin() == v1.crend());
        assert(v2.size() == 0);
        assert(v2.empty());
        assert(v2.capacity() == count_2);
        assert(v2.spare() == count_2);
        assert(v2.data() not_eq nullptr);
        assert(v2.begin() == v2.end());
        assert(v2.cbegin() == v2.cend());
        assert(v2.rbegin() == v2.rend());
        assert(v2.crbegin() == v2.crend());
        assert(v1.data() not_eq v2.data());

        std::cout << "\tChecking test_swap/Swap empty capacity with non-zero capacity empty done." << std::endl;
    }

    // swap empty with non-empty
    {
        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
        const auto number {this->generate_a_random_number()};
        vector<int> v1 {}, v2(count, number);
        v1.swap(v2);
        assert(v1.size() == count);
        assert(not v1.empty());
        assert(v1.capacity() == count);
        assert(v1.spare() == 0);
        assert(v1.data() not_eq nullptr);
        assert(v1.begin() + count == v1.end());
        assert(v1.cbegin() + count == v1.cend());
        assert(v1.front() == number);
        assert(v1.back() == number);
        for(auto it {v1.begin()}; it not_eq v1.end(); ++it) {
            assert(*it == number);
        }
        for(auto it {v1.cbegin()}; it not_eq v1.cend(); ++it) {
            assert(*it == number);
        }
        for(auto it {v1.rbegin()}; it not_eq v1.rend(); ++it) {
            assert(*it == number);
        }
        for(auto it {v1.crbegin()}; it not_eq v1.crend(); ++it) {
            assert(*it == number);
        }
        for(auto i {0}; i < v1.size(); ++i) {
            assert(v1[i] == number);
        }
        assert(v2.size() == 0);
        assert(v2.empty());
        assert(v2.capacity() == 0);
        assert(v2.spare() == 0);
        assert(v2.data() == nullptr);
        assert(v2.begin() == v2.end());
        assert(v2.cbegin() == v2.cend());
        assert(v2.rbegin() == v2.rend());
        assert(v2.crbegin() == v2.crend());

        v1.swap(v2);        // revert
        assert(v1.size() == 0);
        assert(v1.empty());
        assert(v1.capacity() == 0);
        assert(v1.spare() == 0);
        assert(v1.data() == nullptr);
        assert(v1.begin() == v1.end());
        assert(v1.cbegin() == v1.cend());
        assert(v1.rbegin() == v1.rend());
        assert(v1.crbegin() == v1.crend());
        assert(v2.size() == count);
        assert(not v2.empty());
        assert(v2.capacity() == count);
        assert(v2.spare() == 0);
        assert(v2.data() not_eq nullptr);
        assert(v2.begin() + count == v2.end());
        assert(v2.cbegin() + count == v2.cend());
        assert(v2.front() == number);
        assert(v2.back() == number);
        for(auto it {v2.begin()}; it not_eq v2.end(); ++it) {
            assert(*it == number);
        }
        for(auto it {v2.cbegin()}; it not_eq v2.cend(); ++it) {
            assert(*it == number);
        }
        for(auto it {v2.rbegin()}; it not_eq v2.rend(); ++it) {
            assert(*it == number);
        }
        for(auto it {v2.crbegin()}; it not_eq v2.crend(); ++it) {
            assert(*it == number);
        }
        for(auto i {0}; i < v2.size(); ++i) {
            assert(v2[i] == number);
        }

        std::cout << "\tChecking test_swap/Swap empty with non-empty done." << std::endl;
    }

    // swap non-zero capacity empty with non-empty
    {
        auto count_1 {this->generate_count()}, count_2 {this->generate_count()};
        while(count_1 == 0) {
            count_1 = this->generate_count();
        }
        while(count_2 == 0) {
            count_2 = this->generate_count();
        }
        const auto number {this->generate_a_random_number()};
        vector<int> v1(count_1), v2(count_2, number);
        v1.cursor = v1.first;
        v1.swap(v2);
        assert(v1.size() == count_2);
        assert(not v1.empty());
        assert(v1.capacity() == count_2);
        assert(v1.spare() == 0);
        assert(v1.data() not_eq nullptr);
        assert(v1.begin() + count_2 == v1.end());
        assert(v1.cbegin() + count_2 == v1.cend());
        assert(v1.front() == number);
        assert(v1.back() == number);
        for(auto it {v1.begin()}; it not_eq v1.end(); ++it) {
            assert(*it == number);
        }
        for(auto it {v1.cbegin()}; it not_eq v1.cend(); ++it) {
            assert(*it == number);
        }
        for(auto it {v1.rbegin()}; it not_eq v1.rend(); ++it) {
            assert(*it == number);
        }
        for(auto it {v1.crbegin()}; it not_eq v1.crend(); ++it) {
            assert(*it == number);
        }
        for(auto i {0}; i < v1.size(); ++i) {
            assert(v1[i] == number);
        }
        assert(v2.size() == 0);
        assert(v2.empty());
        assert(v2.capacity() == count_1);
        assert(v2.spare() == count_1);
        assert(v2.data() not_eq nullptr);
        assert(v2.begin() == v2.end());
        assert(v2.cbegin() == v2.cend());
        assert(v2.rbegin() == v2.rend());
        assert(v2.crbegin() == v2.crend());
        assert(v1.data() not_eq v2.data());

        v1.swap(v2);        // revert
        assert(v1.size() == 0);
        assert(v1.empty());
        assert(v1.capacity() == count_1);
        assert(v1.spare() == count_1);
        assert(v1.data() not_eq nullptr);
        assert(v1.begin() == v1.end());
        assert(v1.cbegin() == v1.cend());
        assert(v1.rbegin() == v1.rend());
        assert(v1.crbegin() == v1.crend());
        assert(v2.size() == count_2);
        assert(not v2.empty());
        assert(v2.capacity() == count_2);
        assert(v2.spare() == 0);
        assert(v2.data() not_eq nullptr);
        assert(v2.begin() + count_2 == v2.end());
        assert(v2.cbegin() + count_2 == v2.cend());
        assert(v2.front() == number);
        assert(v2.back() == number);
        for(auto it {v2.begin()}; it not_eq v2.end(); ++it) {
            assert(*it == number);
        }
        for(auto it {v2.cbegin()}; it not_eq v2.cend(); ++it) {
            assert(*it == number);
        }
        for(auto it {v2.rbegin()}; it not_eq v2.rend(); ++it) {
            assert(*it == number);
        }
        for(auto it {v2.crbegin()}; it not_eq v2.crend(); ++it) {
            assert(*it == number);
        }
        for(auto i {0}; i < v2.size(); ++i) {
            assert(v2[i] == number);
        }
        assert(v1.data() not_eq v2.data());

        std::cout << "\tChecking test_swap/Swap non-zero capacity empty with non-empty done." << std::endl;
    }

    // Swap non-empty with non-empty
    {
        auto count_1 {this->generate_count()}, count_2 {this->generate_count()};
        while(count_1 == 0) {
            count_1 = this->generate_count();
        }
        while(count_2 == 0) {
            count_2 = this->generate_count();
        }
        const auto number_1 {this->generate_a_random_number()};
        auto number_2 {this->generate_a_random_number()};
        while(number_1 == number_2) {
            number_2 = this->generate_a_random_number();
        }
        vector<int> v1(count_1, number_1), v2(count_2, number_2);
        v1.swap(v2);
        assert(v1.size() == count_2);
        assert(not v1.empty());
        assert(v1.capacity() == count_2);
        assert(v1.spare() == 0);
        assert(v1.data() not_eq nullptr);
        assert(v1.begin() + count_2 == v1.end());
        assert(v1.cbegin() + count_2 == v1.cend());
        assert(v1.front() == number_2);
        assert(v1.back() == number_2);
        for(auto it {v1.begin()}; it not_eq v1.end(); ++it) {
            assert(*it == number_2);
        }
        for(auto it {v1.cbegin()}; it not_eq v1.cend(); ++it) {
            assert(*it == number_2);
        }
        for(auto it {v1.rbegin()}; it not_eq v1.rend(); ++it) {
            assert(*it == number_2);
        }
        for(auto it {v1.crbegin()}; it not_eq v1.crend(); ++it) {
            assert(*it == number_2);
        }
        for(auto i {0}; i < v1.size(); ++i) {
            assert(v1[i] == number_2);
        }
        assert(v2.size() == count_1);
        assert(not v2.empty());
        assert(v2.capacity() == count_1);
        assert(v2.spare() == 0);
        assert(v2.data() not_eq nullptr);
        assert(v2.begin() + count_1 == v2.end());
        assert(v2.cbegin() + count_1 == v2.cend());
        assert(v2.front() == number_1);
        assert(v2.back() == number_1);
        for(auto it {v2.begin()}; it not_eq v2.end(); ++it) {
            assert(*it == number_1);
        }
        for(auto it {v2.cbegin()}; it not_eq v2.cend(); ++it) {
            assert(*it == number_1);
        }
        for(auto it {v2.rbegin()}; it not_eq v2.rend(); ++it) {
            assert(*it == number_1);
        }
        for(auto it {v2.crbegin()}; it not_eq v2.crend(); ++it) {
            assert(*it == number_1);
        }
        for(auto i {0}; i < v2.size(); ++i) {
            assert(v2[i] == number_1);
        }
        assert(v1.data() not_eq v2.data());

        v1.swap(v2);        // revert
        assert(v1.size() == count_1);
        assert(not v1.empty());
        assert(v1.capacity() == count_1);
        assert(v1.spare() == 0);
        assert(v1.data() not_eq nullptr);
        assert(v1.begin() + count_1 == v1.end());
        assert(v1.cbegin() + count_1 == v1.cend());
        assert(v1.front() == number_1);
        assert(v1.back() == number_1);
        for(auto it {v1.begin()}; it not_eq v1.end(); ++it) {
            assert(*it == number_1);
        }
        for(auto it {v1.cbegin()}; it not_eq v1.cend(); ++it) {
            assert(*it == number_1);
        }
        for(auto it {v1.rbegin()}; it not_eq v1.rend(); ++it) {
            assert(*it == number_1);
        }
        for(auto it {v1.crbegin()}; it not_eq v1.crend(); ++it) {
            assert(*it == number_1);
        }
        for(auto i {0}; i < v1.size(); ++i) {
            assert(v1[i] == number_1);
        }
        assert(v2.size() == count_2);
        assert(not v2.empty());
        assert(v2.capacity() == count_2);
        assert(v2.spare() == 0);
        assert(v2.data() not_eq nullptr);
        assert(v2.begin() + count_2 == v2.end());
        assert(v2.cbegin() + count_2 == v2.cend());
        assert(v2.front() == number_2);
        assert(v2.back() == number_2);
        for(auto it {v2.begin()}; it not_eq v2.end(); ++it) {
            assert(*it == number_2);
        }
        for(auto it {v2.cbegin()}; it not_eq v2.cend(); ++it) {
            assert(*it == number_2);
        }
        for(auto it {v2.rbegin()}; it not_eq v2.rend(); ++it) {
            assert(*it == number_2);
        }
        for(auto it {v2.crbegin()}; it not_eq v2.crend(); ++it) {
            assert(*it == number_2);
        }
        for(auto i {0}; i < v2.size(); ++i) {
            assert(v2[i] == number_2);
        }
        assert(v1.data() not_eq v2.data());

        std::cout << "\tChecking test_swap/Swap non-empty with non-empty done." << std::endl;
    }

    std::cout << "Checking void swap() for ds::vector finished!" << std::endl;
}
void vector_correctness::test_emplace() {
    std::cout << "Start checking iterator emplace(difference_type, Args &&...) for ds::vector!" << std::endl;

    // emplace to empty vector
    {
        vector<int> v {};
        const auto result {v.emplace(0, 42.2)};
        assert(v.size() == 1);
        assert(not v.empty());
        assert(v.capacity() == 1);
        assert(v.spare() == 0);
        assert(v.data() not_eq nullptr);
        assert(v.begin() + 1 == v.end());
        assert(v.cbegin() + 1 == v.cend());
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
        assert(result == v.begin());
        assert(result == v.cbegin());
        std::cout << "\tChecking test_emplace/Emplace to empty vector done." << std::endl;
    }

    // emplace to non-empty vector
    {
        std::cout << "\tStart checking test_emplace/Emplace to non-empty vector!" << std::endl;

        // emplace to head
        {
            std::cout << "\t\tStart checking test_emplace/Emplace to non-empty vector/Emplace to head!" << std::endl;

            // without reallocation
            {
                auto count {this->generate_count()};
                while(count <= 1) {
                    count = this->generate_count();
                }
                const auto new_size {this->generate_a_random_number(1, count - 1)};
                const auto number {this->generate_a_random_number()};
                vector<int> v(count, number);
                v.cursor = v.first + new_size;
                auto number_2 {this->generate_a_random_number()};
                while(number == number_2) {
                    number_2 = this->generate_a_random_number();
                }
                const auto result {v.emplace(0, number_2)};
                assert(v.size() == new_size + 1);
                assert(not v.empty());
                assert(v.capacity() == count);
                assert(v.spare() == count - new_size - 1);
                assert(v.data() not_eq nullptr);
                assert(v.begin() + (new_size + 1) == v.end());
                assert(v.cbegin() + (new_size + 1) == v.cend());
                assert(v.front() == number_2);
                assert(v.back() == number);
                assert(*v.begin() == number_2);
                assert(*v.cbegin() == number_2);
                assert(*(v.rend() - 1) == number_2);
                assert(*(v.crend() - 1) == number_2);
                assert(v[0] == number_2);
                for(auto it {v.begin() + 1}; it not_eq v.end(); ++it) {
                    assert(*it == number);
                }
                for(auto it {v.cbegin() + 1}; it not_eq v.cend(); ++it) {
                    assert(*it == number);
                }
                for(auto it {v.rbegin()}; it not_eq v.rend() - 1; ++it) {
                    assert(*it == number);
                }
                for(auto it {v.crbegin()}; it not_eq v.crend() - 1; ++it) {
                    assert(*it == number);
                }
                for(auto i {1}; i < v.size(); ++i) {
                    assert(v[i] == number);
                }
                assert(result == v.begin());
                assert(result == v.cbegin());
                std::cout << "\t\t\tChecking test_emplace/Emplace to non-empty vector/Emplace to head/Without reallocation done." << std::endl;
            }

            // with reallocation
            {
                auto count {this->generate_count(std::numeric_limits<int>::max() - 1)};
                while(count == 0) {
                    count = this->generate_count(std::numeric_limits<int>::max() - 1);
                }
                const auto number {this->generate_a_random_number()};
                auto number_2 {this->generate_a_random_number()};
                while(number == number_2) {
                    number_2 = this->generate_a_random_number(std::numeric_limits<int>::max() - 1);
                }
                vector<int> v(count, number);
                const auto result {v.emplace(0, number_2)};
                assert(v.size() == count + 1);
                assert(not v.empty());
                assert(v.capacity() == static_cast<size_t>(count) * 2);
                assert(v.spare() == count - 1);
                assert(v.data() not_eq nullptr);
                assert(v.begin() + (count + 1) == v.end());
                assert(v.cbegin() + (count + 1) == v.cend());
                assert(v.front() == number_2);
                assert(v.back() == number);
                assert(*v.begin() == number_2);
                assert(*v.cbegin() == number_2);
                assert(*(v.rend() - 1) == number_2);
                assert(*(v.crend() - 1) == number_2);
                assert(v[0] == number_2);
                for(auto it {v.begin() + 1}; it not_eq v.end(); ++it) {
                    assert(*it == number);
                }
                for(auto it {v.cbegin() + 1}; it not_eq v.cend(); ++it) {
                    assert(*it == number);
                }
                for(auto it {v.rbegin()}; it not_eq v.rend() - 1; ++it) {
                    assert(*it == number);
                }
                for(auto it {v.crbegin()}; it not_eq v.crend() - 1; ++it) {
                    assert(*it == number);
                }
                for(auto i {1}; i < v.size(); ++i) {
                    assert(v[i] == number);
                }
                assert(result == v.begin());
                assert(result == v.cbegin());
                std::cout << "\t\t\tChecking test_emplace/Emplace to non-empty vector/Emplace to head/With reallocation done." << std::endl;
            }

            std::cout << "\t\tChecking test_emplace/Emplace to non-empty vector/Emplace to head finished!" << std::endl;
        }

        // emplace to random position
        {
            std::cout << "\t\tStart checking test_emplace/Emplace to non-empty vector/Emplace to random position!" << std::endl;

            // without reallocation
            {
                auto count {this->generate_count()};
                while(count <= 2) {
                    count = this->generate_count();
                }
                auto new_size {this->generate_a_random_number(1, count - 1)};
                while(new_size <= 1) {
                    new_size = this->generate_a_random_number(1, count - 1);
                }
                const auto number {this->generate_a_random_number()};
                vector<int> v(count, number);
                v.cursor = v.first + new_size;
                auto number_2 {this->generate_a_random_number()};
                while(number == number_2) {
                    number_2 = this->generate_a_random_number();
                }
                const auto insertion_position {this->generate_a_random_number(1, new_size - 1)};
                const auto result {v.emplace(insertion_position, number_2)};
                assert(v.size() == new_size + 1);
                assert(not v.empty());
                assert(v.capacity() == count);
                assert(v.spare() == count - new_size - 1);
                assert(v.data() not_eq nullptr);
                assert(v.begin() + (new_size + 1) == v.end());
                assert(v.cbegin() + (new_size + 1) == v.cend());
                assert(v.front() == number);
                assert(v.back() == number);
                for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                    assert(*it == number);
                }
                assert(*(v.begin() + insertion_position) == number_2);
                for(auto it {v.begin() + (insertion_position + 1)}; it not_eq v.end(); ++it) {
                    assert(*it == number);
                }
                for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                    assert(*it == number);
                }
                assert(*(v.cbegin() + insertion_position) == number_2);
                for(auto it {v.cbegin() + (insertion_position + 1)}; it not_eq v.cend(); ++it) {
                    assert(*it == number);
                }
                for(auto it {v.rbegin()}; it not_eq v.rend() - (insertion_position + 1); ++it) {
                    assert(*it == number);
                }
                assert(*(v.rend() - (insertion_position + 1)) == number_2);
                for(auto it {v.rend() - insertion_position}; it not_eq v.rend(); ++it) {
                    assert(*it == number);
                }
                for(auto it {v.crbegin()}; it not_eq v.crend() - (insertion_position + 1); ++it) {
                    assert(*it == number);
                }
                assert(*(v.crend() - (insertion_position + 1)) == number_2);
                for(auto it {v.crend() - insertion_position}; it not_eq v.crend(); ++it) {
                    assert(*it == number);
                }
                for(auto i {0}; i < insertion_position; ++i) {
                    assert(v[i] == number);
                }
                assert(v[insertion_position] == number_2);
                for(auto i {insertion_position + 1}; i < v.size(); ++i) {
                    assert(v[i] == number);
                }
                assert(result == v.begin() + insertion_position);
                assert(result == v.cbegin() + insertion_position);
                std::cout << "\t\t\tChecking test_emplace/Emplace to non-empty vector/Emplace to random position/Without reallocation done." << std::endl;
            }

            // with reallocation
            {
                auto count {this->generate_count()};
                while(count <= 2) {
                    count = this->generate_count();
                }
                const auto number {this->generate_a_random_number()};
                auto number_2 {this->generate_a_random_number()};
                while(number == number_2) {
                    number_2 = this->generate_a_random_number();
                }
                vector<int> v(count, number);
                const auto insertion_position {this->generate_a_random_number(1, count - 1)};
                const auto result {v.emplace(insertion_position, number_2)};
                assert(v.size() == count + 1);
                assert(not v.empty());
                assert(v.capacity() == static_cast<size_t>(count) * 2);
                assert(v.spare() == count - 1);
                assert(v.data() not_eq nullptr);
                assert(v.begin() + (count + 1) == v.end());
                assert(v.cbegin() + (count + 1) == v.cend());
                assert(v.front() == number);
                assert(v.back() == number);
                for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                    assert(*it == number);
                }
                assert(*(v.begin() + insertion_position) == number_2);
                for(auto it {v.begin() + (insertion_position + 1)}; it not_eq v.end(); ++it) {
                    assert(*it == number);
                }
                for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                    assert(*it == number);
                }
                assert(*(v.cbegin() + insertion_position) == number_2);
                for(auto it {v.cbegin() + (insertion_position + 1)}; it not_eq v.cend(); ++it) {
                    assert(*it == number);
                }
                for(auto it {v.rbegin()}; it not_eq v.rend() - (insertion_position + 1); ++it) {
                    assert(*it == number);
                }
                assert(*(v.rend() - (insertion_position + 1)) == number_2);
                for(auto it {v.rend() - insertion_position}; it not_eq v.rend(); ++it) {
                    assert(*it == number);
                }
                for(auto it {v.crbegin()}; it not_eq v.crend() - (insertion_position + 1); ++it) {
                    assert(*it == number);
                }
                assert(*(v.crend() - (insertion_position + 1)) == number_2);
                for(auto it {v.crend() - insertion_position}; it not_eq v.crend(); ++it) {
                    assert(*it == number);
                }
                for(auto i {0}; i < insertion_position; ++i) {
                    assert(v[i] == number);
                }
                assert(v[insertion_position] == number_2);
                for(auto i {insertion_position + 1}; i < v.size(); ++i) {
                    assert(v[i] == number);
                }
            }

            std::cout << "\t\tChecking test_emplace/Emplace to non-empty vector/Emplace to random position/With reallocation finished!" << std::endl;
        }

        // emplace to tail
        {
            std::cout << "\t\tStart checking test_emplace/Emplace to non-empty vector/Emplace to tail!" << std::endl;

            // without reallocation
            {
                auto count {this->generate_count()};
                while(count <= 1) {
                    count = this->generate_count();
                }
                const auto new_size {this->generate_a_random_number(1, count - 1)};
                const auto number {this->generate_a_random_number()};
                vector<int> v(count, number);
                v.cursor = v.first + new_size;
                auto number_2 {this->generate_a_random_number()};
                while(number == number_2) {
                    number_2 = this->generate_a_random_number();
                }
                const auto result {v.emplace(new_size, number_2)};
                assert(v.size() == new_size + 1);
                assert(not v.empty());
                assert(v.capacity() == count);
                assert(v.spare() == count - new_size - 1);
                assert(v.data() not_eq nullptr);
                assert(v.begin() + (new_size + 1) == v.end());
                assert(v.cbegin() + (new_size + 1) == v.cend());
                assert(v.front() == number);
                assert(v.back() == number_2);
                for(auto it {v.begin()}; it not_eq v.end() - 1; ++it) {
                    assert(*it == number);
                }
                assert(*(v.end() - 1) == number_2);
                for(auto it {v.cbegin()}; it not_eq v.cend() - 1; ++it) {
                    assert(*it == number);
                }
                assert(*(v.cend() - 1) == number_2);
                for(auto it {v.rbegin() + 1}; it not_eq v.rend(); ++it) {
                    assert(*it == number);
                }
                assert(*v.rbegin() == number_2);
                for(auto it {v.crbegin() + 1}; it not_eq v.crend(); ++it) {
                    assert(*it == number);
                }
                assert(*v.crbegin() == number_2);
                for(auto i {0}; i < v.size() - 1; ++i) {
                    assert(v[i] == number);
                }
                assert(v[new_size] == number_2);
                assert(result == v.end() - 1);
                assert(result == v.cend() - 1);
                std::cout << "\t\t\tChecking test_emplace/Emplace to non-empty vector/Emplace to tail/Without reallocation done." << std::endl;
            }

            // with reallocation
            {
                auto count {this->generate_count()};
                while(count == 0) {
                    count = this->generate_count();
                }
                const auto number {this->generate_a_random_number()};
                auto number_2 {this->generate_a_random_number()};
                while(number == number_2) {
                    number_2 = this->generate_a_random_number();
                }
                vector<int> v(count, number);
                const auto result {v.emplace(count, number_2)};
                assert(v.size() == count + 1);
                assert(not v.empty());
                assert(v.capacity() == static_cast<size_t>(count) * 2);
                assert(v.spare() == count - 1);
                assert(v.data() not_eq nullptr);
                assert(v.begin() + (count + 1) == v.end());
                assert(v.cbegin() + (count + 1) == v.cend());
                assert(v.front() == number);
                assert(v.back() == number_2);
                for(auto it {v.begin()}; it not_eq v.end() - 1; ++it) {
                    assert(*it == number);
                }
                assert(*(v.end() - 1) == number_2);
                for(auto it {v.cbegin()}; it not_eq v.cend() - 1; ++it) {
                    assert(*it == number);
                }
                assert(*(v.cend() - 1) == number_2);
                for(auto it {v.rbegin() + 1}; it not_eq v.rend(); ++it) {
                    assert(*it == number);
                }
                assert(*v.rbegin() == number_2);
                for(auto it {v.crbegin() + 1}; it not_eq v.crend(); ++it) {
                    assert(*it == number);
                }
                assert(*v.crbegin() == number_2);
                for(auto i {0}; i < v.size() - 1; ++i) {
                    assert(v[i] == number);
                }
                assert(v[count] == number_2);
                assert(result == v.end() - 1);
                assert(result == v.cend() - 1);
                std::cout << "\t\t\tChecking test_emplace/Emplace to non-empty vector/Emplace to tail/With reallocation done." << std::endl;
            }

            std::cout << "\t\tChecking test_emplace/Emplace to non-empty vector/Emplace to tail finished!" << std::endl;
        }

        std::cout << "\tChecking test_emplace/Emplace to non-empty vector finished!" << std::endl;
    }

    std::cout << "Checking iterator emplace(difference_type, Args &&...) for ds::vector finished!" << std::endl;
}
void vector_correctness::test_insert_1() {
    std::cout << "Start checking iterator insert(size_type, const_reference, size_type) for ds::vector!" << std::endl;

    // insert to empty vector
    {
        std::cout << "\tStart checking test_insert_1/Insert to empty vector for ds::vector!" << std::endl;

        // insertion size equal to zero
        {
            vector<int> v {};
            const auto result {v.insert(0, this->generate_a_random_number(), 0)};
            assert(v.size() == 0);
            assert(v.empty());
            assert(v.capacity() == 0);
            assert(v.spare() == 0);
            assert(v.data() == nullptr);
            assert(v.begin() == v.end());
            assert(v.cbegin() == v.cend());
            assert(result == v.begin());
            assert(result == v.cbegin());
            std::cout << "\t\tChecking test_insert_1/Insert to empty vector/Insertion size not equal to zero done." << std::endl;
        }

        // insertion size not equal to zero
        {
            vector<int> v {};
            auto insertion_size {this->generate_count()};
            while(insertion_size == 0) {
                insertion_size = this->generate_count();
            }
            const auto insertion_number {this->generate_a_random_number()};
            const auto result {v.insert(0, insertion_number, insertion_size)};
            assert(v.size() == insertion_size);
            assert(not v.empty());
            assert(v.capacity() == insertion_size);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() + insertion_size == v.end());
            assert(v.cbegin() + insertion_size == v.cend());
            assert(v.front() == insertion_number);
            assert(v.back() == insertion_number);
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == insertion_number);
            }
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == insertion_number);
            }
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == insertion_number);
            }
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == insertion_number);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == insertion_number);
            }
            assert(result == v.begin());
            assert(result == v.cbegin());
            std::cout << "\t\tChecking test_insert_1/Insert to empty vector/Insertion size not equal to zero done." << std::endl;
        }

        std::cout << "\tChecking test_insert_1/Insert to empty vector for ds::vector finished!" << std::endl;
    }

    // insert to non-empty vector
    {
        std::cout << "\tStart checking test_insert_1/Insert to non-empty vector!" << std::endl;

        // insert to head
        {
            std::cout << "\t\tStart checking test_insert_1/Insert to non-empty vector/Insert to head!" << std::endl;

            // without reallocation
            {
                std::cout << "\t\t\tStart checking test_insert_1/Insert to non-empty vector/Insert to head/Without reallocation!" << std::endl;

                // insertion size is zero
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    const auto new_size {this->generate_a_random_number(1, count - 1)};
                    const auto number {this->generate_a_random_number()};
                    vector<int> v(count, number);
                    v.cursor = v.first + new_size;
                    const auto result {v.insert(0, this->generate_a_random_number(), 0)};
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
                    for(auto i {1}; i < v.size(); ++i) {
                        assert(v[i] == number);
                    }
                    assert(result == v.begin());
                    assert(result == v.cbegin());
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty vector/Insert to head/Without reallocation/Insertion size is zero done." << std::endl;
                }

                // insertion size less equal to tail size
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    auto insertion_size {this->generate_a_random_number(1, count)};
                    const auto number {this->generate_a_random_number()};
                    const auto spare {this->generate_count(count)};
                    vector<int> v(count + static_cast<size_t>(insertion_size) + spare, number);
                    v.cursor -= insertion_size + spare;
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    const auto result {v.insert(0, number_2, insertion_size)};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                    assert(v.spare() == spare);
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number_2);
                    assert(v.back() == number);
                    for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto i {0}; i < insertion_size; ++i) {
                        assert(v[i] == number_2);
                    }
                    for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                        assert(v[i] == number);
                    }
                    assert(result == v.begin());
                    assert(result == v.cbegin());
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty vector/Insert to head/Without reallocation/Insertion size less equal to tail size done." << std::endl;
                }

                // insertion size greater than tail size
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    const auto insertion_size {this->generate_a_random_number(count + 1)};
                    const auto number {this->generate_a_random_number()};
                    const auto spare {this->generate_count(count)};
                    vector<int> v(count + static_cast<size_t>(insertion_size) + spare, number);
                    v.cursor -= static_cast<size_t>(insertion_size) + spare;
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    const auto result {v.insert(0, number_2, insertion_size)};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                    assert(v.spare() == spare);
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number_2);
                    assert(v.back() == number);
                    for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto i {0}; i < insertion_size; ++i) {
                        assert(v[i] == number_2);
                    }
                    for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                        assert(v[i] == number);
                    }
                    assert(result == v.begin());
                    assert(result == v.cbegin());
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty vector/Insert to head/Without reallocation/Insertion size greater than tail size done." << std::endl;
                }

                // the value is from self
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    auto insertion_size {this->generate_count()};
                    while(insertion_size == 0) {
                        insertion_size = this->generate_count();
                    }
                    const auto number {this->generate_a_random_number()};
                    vector<int> v(count + static_cast<size_t>(insertion_size), number);
                    v.cursor -= insertion_size;
                    ++v[0];
                    auto result {v.insert(0, v[0], insertion_size)};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    assert(v.capacity() == static_cast<size_t>(count) + insertion_size);
                    assert(v.spare() == 0);
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number + 1);
                    assert(v.back() == number);
                    for(auto it {v.begin()}; it not_eq v.begin() + (insertion_size + 1); ++it) {
                        assert(*it == number + 1);
                    }
                    for(auto it {v.begin() + (insertion_size + 1)}; it not_eq v.end(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + (insertion_size + 1); ++it) {
                        assert(*it == number + 1);
                    }
                    for(auto it {v.cbegin() + (insertion_size + 1)}; it not_eq v.cend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + (count - 1); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.rbegin() + (count - 1)}; it not_eq v.rend(); ++it) {
                        assert(*it == number + 1);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + (count - 1); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin() + (count - 1)}; it not_eq v.crend(); ++it) {
                        assert(*it == number + 1);
                    }
                    for(auto i {0}; i < insertion_size + 1; ++i) {
                        assert(v[i] == number + 1);
                    }
                    for(auto i {insertion_size + 1}; i < count + insertion_size; ++i) {
                        assert(v[i] == number);
                    }
                    assert(result == v.begin());
                    assert(result == v.cbegin());
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty vector/Insert to head/Without reallocation/The value is from self done." << std::endl;
                }

                std::cout << "\t\t\tStart checking test_insert_1/Insert to non-empty vector/Insert to head/Without reallocation finished!" << std::endl;
            }

            // with reallocation
            {
                std::cout << "\t\t\tStart checking test_insert_1/Insert to non-empty vector/Insert to head/With reallocation!" << std::endl;

                // insertion size less equal to tail size
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    auto insertion_size {this->generate_a_random_number(1, count)};
                    const auto number {this->generate_a_random_number()};
                    vector<int> v(count, number);
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    const auto result {v.insert(0, number_2, insertion_size)};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                        assert(v.spare() == 0);
                    }else {
                        assert(v.capacity() == static_cast<size_t>(count) * 2);
                        assert(v.spare() == count - insertion_size);
                    }
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number_2);
                    assert(v.back() == number);
                    for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto i {0}; i < insertion_size; ++i) {
                        assert(v[i] == number_2);
                    }
                    for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                        assert(v[i] == number);
                    }
                    assert(result == v.begin());
                    assert(result == v.cbegin());
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty vector/Insert to head/With reallocation/Insertion size less equal to tail size done." << std::endl;
                }

                // insertion size greater than tail size
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    const auto insertion_size {this->generate_a_random_number(count + 1)};
                    const auto number {this->generate_a_random_number()};
                    vector<int> v(count, number);
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    const auto result {v.insert(0, number_2, insertion_size)};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                        assert(v.spare() == 0);
                    }else {
                        assert(v.capacity() == static_cast<size_t>(count) * 2);
                        assert(v.spare() == count - insertion_size);
                    }
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number_2);
                    assert(v.back() == number);
                    for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto i {0}; i < insertion_size; ++i) {
                        assert(v[i] == number_2);
                    }
                    for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                        assert(v[i] == number);
                    }
                    assert(result == v.begin());
                    assert(result == v.cbegin());
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty vector/Insert to head/With reallocation/Insertion size greater than tail size done." << std::endl;
                }

                // insertion size less equal to double capacity
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    auto insertion_size {this->generate_a_random_number(1, count)};
                    const auto number {this->generate_a_random_number()};
                    vector<int> v(count, number);
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    auto result {v.insert(0, number_2, insertion_size)};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    assert(v.capacity() == static_cast<size_t>(count) * 2);
                    assert(v.spare() == count - insertion_size);
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number_2);
                    assert(v.back() == number);
                    for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto i {0}; i < insertion_size; ++i) {
                        assert(v[i] == number_2);
                    }
                    for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                        assert(v[i] == number);
                    }
                    assert(result == v.begin());
                    assert(result == v.cbegin());
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty vector/Insert to head/With reallocation/Insertion size less equal to double capacity done." << std::endl;
                }

                // insertion size greater than double capacity
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    auto insertion_size {this->generate_a_random_number(2 * count + 1)};
                    const auto number {this->generate_a_random_number()};
                    vector<int> v(count, number);
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    auto result {v.insert(0, number_2, insertion_size)};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    assert(v.capacity() == static_cast<size_t>(count) + insertion_size);
                    assert(v.spare() == 0);
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number_2);
                    assert(v.back() == number);
                    for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto i {0}; i < insertion_size; ++i) {
                        assert(v[i] == number_2);
                    }
                    for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                        assert(v[i] == number);
                    }
                    assert(result == v.begin());
                    assert(result == v.cbegin());
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty vector/Insert to head/With reallocation/Insertion size greater than double capacity done." << std::endl;
                }

                // the value is from self
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    auto insertion_size {this->generate_count()};
                    while(insertion_size == 0) {
                        insertion_size = this->generate_count();
                    }
                    const auto number {this->generate_a_random_number()};
                    vector<int> v(count, number);
                    ++v[0];
                    auto result {v.insert(0, v[0], insertion_size)};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                        assert(v.spare() == 0);
                    }else {
                        assert(v.capacity() == static_cast<size_t>(count) * 2);
                        assert(v.spare() == count - insertion_size);
                    }
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number + 1);
                    assert(v.back() == number);
                    for(auto it {v.begin()}; it not_eq v.begin() + (insertion_size + 1); ++it) {
                        assert(*it == number + 1);
                    }
                    for(auto it {v.begin() + (insertion_size + 1)}; it not_eq v.end(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + (insertion_size + 1); ++it) {
                        assert(*it == number + 1);
                    }
                    for(auto it {v.cbegin() + (insertion_size + 1)}; it not_eq v.cend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + (count - 1); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.rbegin() + (count - 1)}; it not_eq v.rend(); ++it) {
                        assert(*it == number + 1);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + (count - 1); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin() + (count - 1)}; it not_eq v.crend(); ++it) {
                        assert(*it == number + 1);
                    }
                    for(auto i {0}; i < insertion_size + 1; ++i) {
                        assert(v[i] == number + 1);
                    }
                    for(auto i {insertion_size + 1}; i < count + insertion_size; ++i) {
                        assert(v[i] == number);
                    }
                    assert(result == v.begin());
                    assert(result == v.cbegin());
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty vector/Insert to head/With reallocation/The value is from self done." << std::endl;
                }

                std::cout << "\t\t\tStart checking test_insert_1/Insert to non-empty vector/Insert to head/With reallocation finished!" << std::endl;
            }

            std::cout << "\t\tChecking test_insert_1/Insert to non-empty vector/Insert to head finished!" << std::endl;
        }

        // insert to random position
        {
            std::cout << "\t\tStart checking test_insert_1/Insert to non-empty vector/Insert to random position!" << std::endl;

            // without reallocation
            {
                std::cout << "\t\t\tStart checking test_insert_1/Insert to non-empty vector/Insert to random position/Without reallocation!" << std::endl;

                // insertion size is zero
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    const auto new_size {this->generate_a_random_number(1, count - 1)};
                    const auto number {this->generate_a_random_number()};
                    const auto insertion_position {this->generate_a_random_number(1, new_size - 1)};
                    vector<int> v(count, number);
                    v.cursor = v.first + new_size;
                    const auto result {v.insert(insertion_position, this->generate_a_random_number(), 0)};
                    assert(v.size() == new_size);
                    assert(not v.empty());
                    assert(v.capacity() == count);
                    assert(v.spare() == count - new_size);
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + new_size == v.end());
                    assert(v.cbegin() + new_size == v.cend());
                    assert(v.front() == number);
                    assert(v.back() == number);
                    for(auto it {v.begin() + 1}; it not_eq v.end(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin() + 1}; it not_eq v.cend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.rbegin()}; it not_eq v.rend() - 1; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crend() - 1; ++it) {
                        assert(*it == number);
                    }
                    for(auto i {1}; i < v.size(); ++i) {
                        assert(v[i] == number);
                    }
                    assert(result == v.begin() + insertion_position);
                    assert(result == v.cbegin() + insertion_position);
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty vector/Insert to random position/Without reallocation/Insertion size is zero done." << std::endl;
                }

                // insertion size less equal to tail size
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    const auto insertion_position {this->generate_a_random_number(1, count - 1)};
                    auto insertion_size {this->generate_a_random_number(1, count - insertion_position)};
                    const auto number {this->generate_a_random_number()};
                    const auto spare {this->generate_count(count)};
                    vector<int> v(count + static_cast<size_t>(insertion_size) + spare, number);
                    v.cursor -= insertion_size + spare;
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    const auto result {v.insert(insertion_position, number_2, insertion_size)};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                    assert(v.spare() == spare);
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number);
                    assert(v.back() == number);
                    for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                        assert(*it == number);
                    }
                    const auto tail_size {count - insertion_position};
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto i {0}; i < insertion_position; ++i) {
                        assert(v[i] == number);
                    }
                    for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                        assert(v[i] == number_2);
                    }
                    for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                        assert(v[i] == number);
                    }
                    assert(result == v.begin() + insertion_position);
                    assert(result == v.cbegin() + insertion_position);
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty vector/Insert to random position/Without reallocation/Insertion size less equal to tail size done." << std::endl;
                }

                // insertion size greater than tail size
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    const auto insertion_position {this->generate_a_random_number(1, count - 1)};
                    const auto insertion_size {this->generate_a_random_number(count - insertion_position + 1)};
                    const auto number {this->generate_a_random_number()};
                    const auto spare {this->generate_count(count)};
                    vector<int> v(count + static_cast<size_t>(insertion_size) + spare, number);
                    v.cursor -= static_cast<size_t>(insertion_size) + spare;
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    const auto result {v.insert(insertion_position, number_2, insertion_size)};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                    assert(v.spare() == spare);
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number);
                    assert(v.back() == number);
                    for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                        assert(*it == number);
                    }
                    const auto tail_size {count - insertion_position};
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto i {0}; i < insertion_position; ++i) {
                        assert(v[i] == number);
                    }
                    for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                        assert(v[i] == number_2);
                    }
                    for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                        assert(v[i] == number);
                    }
                    assert(result == v.begin() + insertion_position);
                    assert(result == v.cbegin() + insertion_position);
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty vector/Insert to random position/Without reallocation/Insertion size greater than tail size done." << std::endl;
                }

                // the value is from self
                {
                    auto count {this->generate_count()};
                    while(count <= 2) {
                        count = this->generate_count();
                    }
                    const auto insertion_position {this->generate_a_random_number(1, count - 2)};
                    auto insertion_size {this->generate_count()};
                    while(insertion_size == 0) {
                        insertion_size = this->generate_count();
                    }
                    const auto number {this->generate_a_random_number()};
                    vector<int> v(count + static_cast<size_t>(insertion_size), number);
                    v.cursor -= insertion_size;
                    ++v[insertion_position];
                    auto result {v.insert(insertion_position, v[insertion_position], insertion_size)};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    assert(v.capacity() == static_cast<size_t>(count) + insertion_size);
                    assert(v.spare() == 0);
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number);
                    assert(v.back() == number);
                    for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size + 1); ++it) {
                        assert(*it == number + 1);
                    }
                    for(auto it {v.begin() + (insertion_position + insertion_size + 1)}; it not_eq v.end(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size + 1); ++it) {
                        assert(*it == number + 1);
                    }
                    for(auto it {v.cbegin() + (insertion_position + insertion_size + 1)}; it not_eq v.cend(); ++it) {
                        assert(*it == number);
                    }
                    const auto tail_size {count - insertion_position};
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + (tail_size - 1); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.rbegin() + (tail_size - 1)}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                        assert(*it == number + 1);
                    }
                    for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + (tail_size - 1); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin() + (tail_size - 1)}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                        assert(*it == number + 1);
                    }
                    for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto i {0}; i < insertion_position; ++i) {
                        assert(v[i] == number);
                    }
                    for(auto i {insertion_position}; i < insertion_position + insertion_size + 1; ++i) {
                        assert(v[i] == number + 1);
                    }
                    for(auto i {insertion_position + insertion_size + 1}; i < v.size(); ++i) {
                        assert(v[i] == number);
                    }
                    assert(result == v.begin() + insertion_position);
                    assert(result == v.cbegin() + insertion_position);
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty vector/Insert to random position/Without reallocation/The value is from self done." << std::endl;
                }

                std::cout << "\t\t\tStart checking test_insert_1/Insert to non-empty vector/Insert to random position/Without reallocation finished!" << std::endl;
            }

            // with reallocation
            {
                std::cout << "\t\t\tStart checking test_insert_1/Insert to non-empty vector/Insert to random position/With reallocation!" << std::endl;

                // insertion size less equal to tail size
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    const auto insertion_position {this->generate_a_random_number(1, count - 1)};
                    auto insertion_size {this->generate_a_random_number(1, count - insertion_position)};
                    const auto number {this->generate_a_random_number()};
                    vector<int> v(count, number);
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    const auto result {v.insert(insertion_position, number_2, insertion_size)};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                        assert(v.spare() == 0);
                    }else {
                        assert(v.capacity() == static_cast<size_t>(count) * 2);
                        assert(v.spare() == count - insertion_size);
                    }
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number);
                    assert(v.back() == number);
                    for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                        assert(*it == number);
                    }
                    const auto tail_size {count - insertion_position};
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto i {0}; i < insertion_position; ++i) {
                        assert(v[i] == number);
                    }
                    for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                        assert(v[i] == number_2);
                    }
                    for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                        assert(v[i] == number);
                    }
                    assert(result == v.begin() + insertion_position);
                    assert(result == v.cbegin() + insertion_position);
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty vector/Insert to random position/With reallocation/Insertion size less equal to tail size done." << std::endl;
                }

                // insertion size greater than tail size
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    const auto insertion_position {this->generate_a_random_number(1, count - 1)};
                    const auto insertion_size {this->generate_a_random_number(count - insertion_position + 1)};
                    const auto number {this->generate_a_random_number()};
                    vector<int> v(count, number);
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    const auto result {v.insert(insertion_position, number_2, insertion_size)};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                        assert(v.spare() == 0);
                    }else {
                        assert(v.capacity() == static_cast<size_t>(count) * 2);
                        assert(v.spare() == count - insertion_size);
                    }
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number);
                    assert(v.back() == number);
                    for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                        assert(*it == number);
                    }
                    const auto tail_size {count - insertion_position};
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto i {0}; i < insertion_position; ++i) {
                        assert(v[i] == number);
                    }
                    for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                        assert(v[i] == number_2);
                    }
                    for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                        assert(v[i] == number);
                    }
                    assert(result == v.begin() + insertion_position);
                    assert(result == v.cbegin() + insertion_position);
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty vector/Insert to random position/With reallocation/Insertion size greater than tail size done." << std::endl;
                }

                // insertion size less equal to double capacity
                {
                    auto count {this->generate_count()};
                    while(count <= 2) {
                        count = this->generate_count();
                    }
                    const auto insertion_position {this->generate_a_random_number(1, count - 2)};
                    auto insertion_size {this->generate_a_random_number(1, count)};
                    const auto number {this->generate_a_random_number()};
                    vector<int> v(count, number);
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    auto result {v.insert(insertion_position, number_2, insertion_size)};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    assert(v.capacity() == static_cast<size_t>(count) * 2);
                    assert(v.spare() == count - insertion_size);
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number);
                    assert(v.back() == number);
                    for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                        assert(*it == number);
                    }
                    const auto tail_size {count - insertion_position};
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto i {0}; i < insertion_position; ++i) {
                        assert(v[i] == number);
                    }
                    for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                        assert(v[i] == number_2);
                    }
                    for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                        assert(v[i] == number);
                    }
                    assert(result == v.begin() + insertion_position);
                    assert(result == v.cbegin() + insertion_position);
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty vector/Insert to random position/With reallocation/Insertion size less equal to double capacity done." << std::endl;
                }

                // insertion size greater than double capacity
                {
                    auto count {this->generate_count()};
                    while(count <= 2) {
                        count = this->generate_count();
                    }
                    const auto insertion_position {this->generate_a_random_number(1, count - 2)};
                    auto insertion_size {this->generate_a_random_number(2 * count + 1)};
                    const auto number {this->generate_a_random_number()};
                    vector<int> v(count, number);
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    auto result {v.insert(insertion_position, number_2, insertion_size)};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    assert(v.capacity() == static_cast<size_t>(count) + insertion_size);
                    assert(v.spare() == 0);
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number);
                    assert(v.back() == number);
                    for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                        assert(*it == number);
                    }
                    const auto tail_size {count - insertion_position};
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto i {0}; i < insertion_position; ++i) {
                        assert(v[i] == number);
                    }
                    for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                        assert(v[i] == number_2);
                    }
                    for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                        assert(v[i] == number);
                    }
                    assert(result == v.begin() + insertion_position);
                    assert(result == v.cbegin() + insertion_position);
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty vector/Insert to random position/With reallocation/Insertion size greater than double capacity done." << std::endl;
                }

                // the value is from self
                {
                    auto count {this->generate_count()};
                    while(count <= 2) {
                        count = this->generate_count();
                    }
                    const auto insertion_position {this->generate_a_random_number(1, count - 2)};
                    auto insertion_size {this->generate_count()};
                    while(insertion_size == 0) {
                        insertion_size = this->generate_count();
                    }
                    const auto number {this->generate_a_random_number()};
                    vector<int> v(count, number);
                    ++v[insertion_position];
                    auto result {v.insert(insertion_position, v[insertion_position], insertion_size)};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                        assert(v.spare() == 0);
                    }else {
                        assert(v.capacity() == static_cast<size_t>(count) * 2);
                        assert(v.spare() == count - insertion_size);
                    }
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number);
                    assert(v.back() == number);
                    for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size + 1); ++it) {
                        assert(*it == number + 1);
                    }
                    for(auto it {v.begin() + (insertion_position + insertion_size + 1)}; it not_eq v.end(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size + 1); ++it) {
                        assert(*it == number + 1);
                    }
                    for(auto it {v.cbegin() + (insertion_position + insertion_size + 1)}; it not_eq v.cend(); ++it) {
                        assert(*it == number);
                    }
                    const auto tail_size {count - insertion_position};
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + (tail_size - 1); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.rbegin() + (tail_size - 1)}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                        assert(*it == number + 1);
                    }
                    for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + (tail_size - 1); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin() + (tail_size - 1)}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                        assert(*it == number + 1);
                    }
                    for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto i {0}; i < insertion_position; ++i) {
                        assert(v[i] == number);
                    }
                    for(auto i {insertion_position}; i < insertion_position + insertion_size + 1; ++i) {
                        assert(v[i] == number + 1);
                    }
                    for(auto i {insertion_position + insertion_size + 1}; i < v.size(); ++i) {
                        assert(v[i] == number);
                    }
                    assert(result == v.begin() + insertion_position);
                    assert(result == v.cbegin() + insertion_position);
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty vector/Insert to random position/With reallocation/The value is from self done." << std::endl;
                }

                std::cout << "\t\t\tStart checking test_insert_1/Insert to non-empty vector/Insert to random position/With reallocation finished!" << std::endl;
            }

            std::cout << "\t\tChecking test_insert_1/Insert to non-empty vector/Insert to random position finished!" << std::endl;
        }

        // insert to tail
        {
            std::cout << "\t\tStart checking test_insert_1/Insert to non-empty vector/Insert to tail!" << std::endl;

            // without reallocation
            {
                std::cout << "\t\t\tStart checking test_insert_1/Insert to non-empty vector/Insert to tail/Without reallocation!" << std::endl;

                // insertion size is zero
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    const auto new_size {this->generate_a_random_number(1, count - 1)};
                    const auto number {this->generate_a_random_number()};
                    vector<int> v(count, number);
                    v.cursor = v.first + new_size;
                    const auto result {v.insert(new_size, this->generate_a_random_number(), 0)};
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
                    for(auto i {1}; i < v.size(); ++i) {
                        assert(v[i] == number);
                    }
                    assert(result == v.end());
                    assert(result == v.cend());
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty vector/Insert to tail/Without reallocation/Insertion size is zero done." << std::endl;
                }

                // insertion size less equal to tail size
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    auto insertion_size {this->generate_a_random_number(1, count)};
                    const auto number {this->generate_a_random_number()};
                    const auto spare {this->generate_count(count)};
                    vector<int> v(count + static_cast<size_t>(insertion_size) + spare, number);
                    v.cursor -= insertion_size + spare;
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    const auto result {v.insert(count, number_2, insertion_size)};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                    assert(v.spare() == spare);
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number);
                    assert(v.back() == number_2);
                    for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto i {0}; i < count; ++i) {
                        assert(v[i] == number);
                    }
                    for(auto i {count}; i < count + insertion_size; ++i) {
                        assert(v[i] == number_2);
                    }
                    assert(result == v.begin() + count);
                    assert(result == v.cbegin() + count);
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty vector/Insert to tail/Without reallocation/Insertion size less equal to tail size done." << std::endl;
                }

                // insertion size greater than tail size
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    const auto insertion_size {this->generate_a_random_number(count + 1)};
                    const auto number {this->generate_a_random_number()};
                    const auto spare {this->generate_count(count)};
                    vector<int> v(count + static_cast<size_t>(insertion_size) + spare, number);
                    v.cursor -= static_cast<size_t>(insertion_size) + spare;
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    const auto result {v.insert(count, number_2, insertion_size)};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                    assert(v.spare() == spare);
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number);
                    assert(v.back() == number_2);
                    for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto i {0}; i < count; ++i) {
                        assert(v[i] == number);
                    }
                    for(auto i {count}; i < count + insertion_size; ++i) {
                        assert(v[i] == number_2);
                    }
                    assert(result == v.begin() + count);
                    assert(result == v.cbegin() + count);
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty vector/Insert to tail/Without reallocation/Insertion size greater than tail size done." << std::endl;
                }

                // the value is from self
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    auto insertion_size {this->generate_count()};
                    while(insertion_size == 0) {
                        insertion_size = this->generate_count();
                    }
                    const auto number {this->generate_a_random_number()};
                    vector<int> v(count + static_cast<size_t>(insertion_size), number);
                    v.cursor -= insertion_size;
                    ++v[count - 1];
                    auto result {v.insert(count, v[count - 1], insertion_size)};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    assert(v.capacity() == static_cast<size_t>(count) + insertion_size);
                    assert(v.spare() == 0);
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number);
                    assert(v.back() == number + 1);
                    for(auto it {v.begin()}; it not_eq v.begin() + (count - 1); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.begin() + (count - 1)}; it not_eq v.end(); ++it) {
                        assert(*it == number + 1);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + (count - 1); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin() + (count - 1)}; it not_eq v.cend(); ++it) {
                        assert(*it == number + 1);
                    }
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + (insertion_size + 1); ++it) {
                        assert(*it == number + 1);
                    }
                    for(auto it {v.rbegin() + (insertion_size + 1)}; it not_eq v.rend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + (insertion_size + 1); ++it) {
                        assert(*it == number + 1);
                    }
                    for(auto it {v.crbegin() + (insertion_size + 1)}; it not_eq v.crend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto i {0}; i < count - 1; ++i) {
                        assert(v[i] == number);
                    }
                    for(auto i {count - 1}; i < count + insertion_size; ++i) {
                        assert(v[i] == number + 1);
                    }
                    assert(result == v.begin() + count);
                    assert(result == v.cbegin() + count);
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty vector/Insert to tail/Without reallocation/The value is from self done." << std::endl;
                }

                std::cout << "\t\t\tStart checking test_insert_1/Insert to non-empty vector/Insert to tail/Without reallocation finished!" << std::endl;
            }

            // with reallocation
            {
                std::cout << "\t\t\tStart checking test_insert_1/Insert to non-empty vector/Insert to tail/With reallocation!" << std::endl;

                // insertion size less equal to tail size
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    auto insertion_size {this->generate_a_random_number(1, count)};
                    const auto number {this->generate_a_random_number()};
                    vector<int> v(count, number);
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    const auto result {v.insert(count, number_2, insertion_size)};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                        assert(v.spare() == 0);
                    }else {
                        assert(v.capacity() == static_cast<size_t>(count) * 2);
                        assert(v.spare() == count - insertion_size);
                    }
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number);
                    assert(v.back() == number_2);
                    for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto i {0}; i < count; ++i) {
                        assert(v[i] == number);
                    }
                    for(auto i {count}; i < count + insertion_size; ++i) {
                        assert(v[i] == number_2);
                    }
                    assert(result == v.begin() + count);
                    assert(result == v.cbegin() + count);
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty vector/Insert to tail/With reallocation/Insertion size less equal to tail size done." << std::endl;
                }

                // insertion size greater than tail size
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    const auto insertion_size {this->generate_a_random_number(count + 1)};
                    const auto number {this->generate_a_random_number()};
                    vector<int> v(count, number);
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    const auto result {v.insert(count, number_2, insertion_size)};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                        assert(v.spare() == 0);
                    }else {
                        assert(v.capacity() == static_cast<size_t>(count) * 2);
                        assert(v.spare() == count - insertion_size);
                    }
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number);
                    assert(v.back() == number_2);
                    for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto i {0}; i < count; ++i) {
                        assert(v[i] == number);
                    }
                    for(auto i {count}; i < count + insertion_size; ++i) {
                        assert(v[i] == number_2);
                    }
                    assert(result == v.begin() + count);
                    assert(result == v.cbegin() + count);
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty vector/Insert to tail/With reallocation/Insertion size greater than tail size done." << std::endl;
                }

                // insertion size less equal to double capacity
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    auto insertion_size {this->generate_a_random_number(1, count)};
                    const auto number {this->generate_a_random_number()};
                    vector<int> v(count, number);
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    auto result {v.insert(count, number_2, insertion_size)};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    assert(v.capacity() == static_cast<size_t>(count) * 2);
                    assert(v.spare() == count - insertion_size);
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number);
                    assert(v.back() == number_2);
                    for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto i {0}; i < count; ++i) {
                        assert(v[i] == number);
                    }
                    for(auto i {count}; i < count + insertion_size; ++i) {
                        assert(v[i] == number_2);
                    }
                    assert(result == v.begin() + count);
                    assert(result == v.cbegin() + count);
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty vector/Insert to tail/With reallocation/Insertion size less equal to double capacity done." << std::endl;
                }

                // insertion size greater than double capacity
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    auto insertion_size {this->generate_a_random_number(2 * count + 1)};
                    const auto number {this->generate_a_random_number()};
                    vector<int> v(count, number);
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    auto result {v.insert(count, number_2, insertion_size)};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    assert(v.capacity() == static_cast<size_t>(count) + insertion_size);
                    assert(v.spare() == 0);
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number);
                    assert(v.back() == number_2);
                    for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto i {0}; i < count; ++i) {
                        assert(v[i] == number);
                    }
                    for(auto i {count}; i < count + insertion_size; ++i) {
                        assert(v[i] == number_2);
                    }
                    assert(result == v.begin() + count);
                    assert(result == v.cbegin() + count);
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty vector/Insert to tail/With reallocation/Insertion size greater than double capacity done." << std::endl;
                }

                // the value is from self
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    auto insertion_size {this->generate_count()};
                    while(insertion_size == 0) {
                        insertion_size = this->generate_count();
                    }
                    const auto number {this->generate_a_random_number()};
                    vector<int> v(count, number);
                    ++v[count - 1];
                    auto result {v.insert(count, v[count - 1], insertion_size)};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                        assert(v.spare() == 0);
                    }else {
                        assert(v.capacity() == static_cast<size_t>(count) * 2);
                        assert(v.spare() == count - insertion_size);
                    }
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number);
                    assert(v.back() == number + 1);
                    for(auto it {v.begin()}; it not_eq v.begin() + (count - 1); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.begin() + (count - 1)}; it not_eq v.end(); ++it) {
                        assert(*it == number + 1);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + (count - 1); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin() + (count - 1)}; it not_eq v.cend(); ++it) {
                        assert(*it == number + 1);
                    }
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + (insertion_size + 1); ++it) {
                        assert(*it == number + 1);
                    }
                    for(auto it {v.rbegin() + (insertion_size + 1)}; it not_eq v.rend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + (insertion_size + 1); ++it) {
                        assert(*it == number + 1);
                    }
                    for(auto it {v.crbegin() + (insertion_size + 1)}; it not_eq v.crend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto i {0}; i < count - 1; ++i) {
                        assert(v[i] == number);
                    }
                    for(auto i {count - 1}; i < count + insertion_size; ++i) {
                        assert(v[i] == number + 1);
                    }
                    assert(result == v.begin() + count);
                    assert(result == v.cbegin() + count);
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty vector/Insert to tail/With reallocation/The value is from self done." << std::endl;
                }

                std::cout << "\t\t\tStart checking test_insert_1/Insert to non-empty vector/Insert to tail/With reallocation finished!" << std::endl;
            }

            std::cout << "\t\tChecking test_insert_1/Insert to non-empty vector/Insert to tail finished!" << std::endl;
        }

        std::cout << "\tChecking test_insert_1/Insert to non-empty vector finished!" << std::endl;
    }

    std::cout << "Checking iterator insert(size_type, const_reference, size_type) for ds::vector finished!" << std::endl;
}
void vector_correctness::test_insert_2() {
    std::cout << "Start checking iterator insert(size_type, InputIterator, InputIterator) for ds::vector!" << std::endl;

    // insert to empty vector
    {
        std::cout << "\tStart checking test_insert_2/Insert to empty vector for ds::vector!" << std::endl;

        // insertion size equal to zero
        {
            vector<int> v {};
            const auto result {v.insert(0, int_input_iterator {}, int_input_iterator {})};
            assert(v.size() == 0);
            assert(v.empty());
            assert(v.capacity() == 0);
            assert(v.spare() == 0);
            assert(v.data() == nullptr);
            assert(v.begin() == v.end());
            assert(v.cbegin() == v.cend());
            assert(result == v.begin());
            assert(result == v.cbegin());
            std::cout << "\t\tChecking test_insert_2/Insert to empty vector/Insertion size not equal to zero done." << std::endl;
        }

        // insertion size not equal to zero
        {
            vector<int> v {};
            auto insertion_size {this->generate_count()};
            while(insertion_size == 0) {
                insertion_size = this->generate_count();
            }
            const auto numbers {this->generate_random_sequence(insertion_size)};
            auto stream {this->to_input_iterator(numbers)};
            const auto result {v.insert(0, int_input_iterator {stream}, int_input_iterator {})};
            assert(v.size() == insertion_size);
            assert(not v.empty());
            assert(v.capacity() == insertion_size);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() + insertion_size == v.end());
            assert(v.cbegin() + insertion_size == v.cend());
            assert(v.front() == numbers.front());
            assert(v.back() == numbers.back());
            auto i {0uz};
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == numbers[i++]);
            }
            i = 0;
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == numbers[i++]);
            }
            i = insertion_size - 1;
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == numbers[i--]);
            }
            i = insertion_size - 1;
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == numbers[i--]);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == numbers[i]);
            }
            assert(result == v.begin());
            assert(result == v.cbegin());
            std::cout << "\t\tChecking test_insert_2/Insert to empty vector/Insertion size not equal to zero done." << std::endl;
        }

        std::cout << "\tChecking test_insert_2/Insert to empty vector for ds::vector finished!" << std::endl;
    }

    // insert to non-empty vector
    {
        std::cout << "\tStart checking test_insert_2/Insert to non-empty vector!" << std::endl;

        // insert to head
        {
            std::cout << "\t\tStart checking test_insert_2/Insert to non-empty vector/Insert to head!" << std::endl;

            // without reallocation
            {
                std::cout << "\t\t\tStart checking test_insert_2/Insert to non-empty vector/Insert to head/Without reallocation!" << std::endl;

                // insertion size is zero
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    const auto new_size {this->generate_a_random_number(1, count - 1)};
                    const auto number {this->generate_a_random_number()};
                    vector<int> v(count, number);
                    v.cursor = v.first + new_size;
                    const auto result {v.insert(0, int_input_iterator {}, int_input_iterator {})};
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
                    for(auto i {1}; i < v.size(); ++i) {
                        assert(v[i] == number);
                    }
                    assert(result == v.begin());
                    assert(result == v.cbegin());
                    std::cout << "\t\t\t\tChecking test_insert_2/Insert to non-empty vector/Insert to head/Without reallocation/Insertion size is zero done." << std::endl;
                }

                // insertion size less equal to tail size
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    auto insertion_size {this->generate_a_random_number(1, count)};
                    const auto numbers {this->generate_random_sequence(insertion_size)};
                    auto stream {this->to_input_iterator(numbers)};
                    const auto number {this->generate_a_random_number()};
                    const auto spare {this->generate_count(count)};
                    vector<int> v(count + static_cast<size_t>(insertion_size) + spare, number);
                    v.cursor -= insertion_size + spare;
                    const auto result {v.insert(0, int_input_iterator {stream}, int_input_iterator {})};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                    assert(v.spare() == spare);
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == numbers.front());
                    assert(v.back() == number);
                    auto number_i {0uz};
                    for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                        assert(*it == numbers[number_i++]);
                    }
                    for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                        assert(*it == number);
                    }
                    number_i = 0;
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                        assert(*it == numbers[number_i++]);
                    }
                    for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    number_i = insertion_size - 1;
                    for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                        assert(*it == numbers[number_i--]);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    number_i = insertion_size - 1;
                    for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                        assert(*it == numbers[number_i--]);
                    }
                    number_i = 0;
                    for(auto i {0}; i < insertion_size; ++i) {
                        assert(v[i] == numbers[number_i++]);
                    }
                    for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                        assert(v[i] == number);
                    }
                    assert(result == v.begin());
                    assert(result == v.cbegin());
                    std::cout << "\t\t\t\tChecking test_insert_2/Insert to non-empty vector/Insert to head/Without reallocation/Insertion size less equal to tail size done." << std::endl;
                }

                // insertion size greater than tail size
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    const auto insertion_size {this->generate_a_random_number(count + 1)};
                    const auto numbers {this->generate_random_sequence(insertion_size)};
                    auto stream {this->to_input_iterator(numbers)};
                    const auto number {this->generate_a_random_number()};
                    const auto spare {this->generate_count(count)};
                    vector<int> v(count + static_cast<size_t>(insertion_size) + spare, number);
                    v.cursor -= static_cast<size_t>(insertion_size) + spare;
                    const auto result {v.insert(0, int_input_iterator {stream}, int_input_iterator {})};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                    assert(v.spare() == spare);
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == numbers.front());
                    assert(v.back() == number);
                    auto number_i {0uz};
                    for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                        assert(*it == numbers[number_i++]);
                    }
                    for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                        assert(*it == number);
                    }
                    number_i = 0;
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                        assert(*it == numbers[number_i++]);
                    }
                    for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    number_i = insertion_size - 1;
                    for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                        assert(*it == numbers[number_i--]);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    number_i = insertion_size - 1;
                    for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                        assert(*it == numbers[number_i--]);
                    }
                    number_i = 0;
                    for(auto i {0}; i < insertion_size; ++i) {
                        assert(v[i] == numbers[number_i++]);
                    }
                    for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                        assert(v[i] == number);
                    }
                    assert(result == v.begin());
                    assert(result == v.cbegin());
                    std::cout << "\t\t\t\tChecking test_insert_2/Insert to non-empty vector/Insert to head/Without reallocation/Insertion size greater than tail size done." << std::endl;
                }

                std::cout << "\t\t\tStart checking test_insert_2/Insert to non-empty vector/Insert to head/Without reallocation finished!" << std::endl;
            }

            // with reallocation
            {
                std::cout << "\t\t\tStart checking test_insert_2/Insert to non-empty vector/Insert to head/With reallocation!" << std::endl;

                // insertion size less equal to tail size
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    auto insertion_size {this->generate_a_random_number(1, count)};
                    const auto numbers {this->generate_random_sequence(insertion_size)};
                    auto stream {this->to_input_iterator(numbers)};
                    const auto number {this->generate_a_random_number()};
                    vector<int> v(count, number);
                    const auto result {v.insert(0, int_input_iterator {stream}, int_input_iterator {})};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                        assert(v.spare() == 0);
                    }else {
                        assert(v.capacity() == static_cast<size_t>(count) * 2);
                        assert(v.spare() == count - insertion_size);
                    }
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == numbers.front());
                    assert(v.back() == number);
                    auto number_i {0uz};
                    for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                        assert(*it == numbers[number_i++]);
                    }
                    for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                        assert(*it == number);
                    }
                    number_i = 0;
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                        assert(*it == numbers[number_i++]);
                    }
                    for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    number_i = insertion_size - 1;
                    for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                        assert(*it == numbers[number_i--]);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    number_i = insertion_size - 1;
                    for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                        assert(*it == numbers[number_i--]);
                    }
                    number_i = 0;
                    for(auto i {0}; i < insertion_size; ++i) {
                        assert(v[i] == numbers[number_i++]);
                    }
                    for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                        assert(v[i] == number);
                    }
                    assert(result == v.begin());
                    assert(result == v.cbegin());
                    std::cout << "\t\t\t\tChecking test_insert_2/Insert to non-empty vector/Insert to head/With reallocation/Insertion size less equal to tail size done." << std::endl;
                }

                // insertion size greater than tail size
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    const auto insertion_size {this->generate_a_random_number(count + 1)};
                    const auto numbers {this->generate_random_sequence(insertion_size)};
                    auto stream {this->to_input_iterator(numbers)};
                    const auto number {this->generate_a_random_number()};
                    vector<int> v(count, number);
                    const auto result {v.insert(0, int_input_iterator {stream}, int_input_iterator {})};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                        assert(v.spare() == 0);
                    }else {
                        assert(v.capacity() == static_cast<size_t>(count) * 2);
                        assert(v.spare() == count - insertion_size);
                    }
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == numbers.front());
                    assert(v.back() == number);
                    auto number_i {0uz};
                    for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                        assert(*it == numbers[number_i++]);
                    }
                    for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                        assert(*it == number);
                    }
                    number_i = 0;
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                        assert(*it == numbers[number_i++]);
                    }
                    for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    number_i = insertion_size - 1;
                    for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                        assert(*it == numbers[number_i--]);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    number_i = insertion_size - 1;
                    for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                        assert(*it == numbers[number_i--]);
                    }
                    number_i = 0;
                    for(auto i {0}; i < insertion_size; ++i) {
                        assert(v[i] == numbers[number_i++]);
                    }
                    for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                        assert(v[i] == number);
                    }
                    assert(result == v.begin());
                    assert(result == v.cbegin());
                    std::cout << "\t\t\t\tChecking test_insert_2/Insert to non-empty vector/Insert to head/With reallocation/Insertion size greater than tail size done." << std::endl;
                }

                // insertion size less equal to double capacity
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    const auto insertion_size {this->generate_a_random_number(1, count)};
                    const auto numbers {this->generate_random_sequence(insertion_size)};
                    auto stream {this->to_input_iterator(numbers)};
                    const auto number {this->generate_a_random_number()};
                    vector<int> v(count, number);
                    auto result {v.insert(0, int_input_iterator {stream}, int_input_iterator {})};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    assert(v.capacity() == static_cast<size_t>(count) * 2);
                    assert(v.spare() == count - insertion_size);
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == numbers.front());
                    assert(v.back() == number);
                    auto number_i {0uz};
                    for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                        assert(*it == numbers[number_i++]);
                    }
                    for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                        assert(*it == number);
                    }
                    number_i = 0;
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                        assert(*it == numbers[number_i++]);
                    }
                    for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    number_i = insertion_size - 1;
                    for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                        assert(*it == numbers[number_i--]);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    number_i = insertion_size - 1;
                    for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                        assert(*it == numbers[number_i--]);
                    }
                    number_i = 0;
                    for(auto i {0}; i < insertion_size; ++i) {
                        assert(v[i] == numbers[number_i++]);
                    }
                    for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                        assert(v[i] == number);
                    }
                    assert(result == v.begin());
                    assert(result == v.cbegin());
                    std::cout << "\t\t\t\tChecking test_insert_2/Insert to non-empty vector/Insert to head/With reallocation/Insertion size less equal to double capacity done." << std::endl;
                }

                // insertion size greater than double capacity
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    const auto insertion_size {this->generate_a_random_number(2 * count + 1)};
                    const auto numbers {this->generate_random_sequence(insertion_size)};
                    auto stream {this->to_input_iterator(numbers)};
                    const auto number {this->generate_a_random_number()};
                    vector<int> v(count, number);
                    auto result {v.insert(0, int_input_iterator {stream}, int_input_iterator {})};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    assert(v.capacity() == static_cast<size_t>(count) + insertion_size);
                    assert(v.spare() == 0);
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == numbers.front());
                    assert(v.back() == number);
                    auto number_i {0uz};
                    for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                        assert(*it == numbers[number_i++]);
                    }
                    for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                        assert(*it == number);
                    }
                    number_i = 0;
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                        assert(*it == numbers[number_i++]);
                    }
                    for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    number_i = insertion_size - 1;
                    for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                        assert(*it == numbers[number_i--]);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    number_i = insertion_size - 1;
                    for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                        assert(*it == numbers[number_i--]);
                    }
                    number_i = 0;
                    for(auto i {0}; i < insertion_size; ++i) {
                        assert(v[i] == numbers[number_i++]);
                    }
                    for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                        assert(v[i] == number);
                    }
                    assert(result == v.begin());
                    assert(result == v.cbegin());
                    std::cout << "\t\t\t\tChecking test_insert_2/Insert to non-empty vector/Insert to head/With reallocation/Insertion size greater than double capacity done." << std::endl;
                }

                std::cout << "\t\t\tStart checking test_insert_2/Insert to non-empty vector/Insert to head/With reallocation finished!" << std::endl;
            }

            std::cout << "\t\tChecking test_insert_2/Insert to non-empty vector/Insert to head finished!" << std::endl;
        }

        // insert to random position
        {
            std::cout << "\t\tStart checking test_insert_2/Insert to non-empty vector/Insert to random position!" << std::endl;

            // without reallocation
            {
                std::cout << "\t\t\tStart checking test_insert_2/Insert to non-empty vector/Insert to random position/Without reallocation!" << std::endl;

                // insertion size is zero
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    const auto new_size {this->generate_a_random_number(1, count - 1)};
                    const auto number {this->generate_a_random_number()};
                    const auto insertion_position {this->generate_a_random_number(1, new_size - 1)};
                    vector<int> v(count, number);
                    v.cursor = v.first + new_size;
                    const auto result {v.insert(insertion_position, int_input_iterator {}, int_input_iterator {})};
                    assert(v.size() == new_size);
                    assert(not v.empty());
                    assert(v.capacity() == count);
                    assert(v.spare() == count - new_size);
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + new_size == v.end());
                    assert(v.cbegin() + new_size == v.cend());
                    assert(v.front() == number);
                    assert(v.back() == number);
                    for(auto it {v.begin() + 1}; it not_eq v.end(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin() + 1}; it not_eq v.cend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.rbegin()}; it not_eq v.rend() - 1; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crend() - 1; ++it) {
                        assert(*it == number);
                    }
                    for(auto i {1}; i < v.size(); ++i) {
                        assert(v[i] == number);
                    }
                    assert(result == v.begin() + insertion_position);
                    assert(result == v.cbegin() + insertion_position);
                    std::cout << "\t\t\t\tChecking test_insert_2/Insert to non-empty vector/Insert to random position/Without reallocation/Insertion size is zero done." << std::endl;
                }

                // insertion size less equal to tail size
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    const auto insertion_position {this->generate_a_random_number(1, count - 1)};
                    auto insertion_size {this->generate_a_random_number(1, count - insertion_position)};
                    const auto numbers {this->generate_random_sequence(insertion_size)};
                    auto stream {this->to_input_iterator(numbers)};
                    const auto number {this->generate_a_random_number()};
                    const auto spare {this->generate_count(count)};
                    vector<int> v(count + static_cast<size_t>(insertion_size) + spare, number);
                    v.cursor -= insertion_size + spare;
                    const auto result {v.insert(insertion_position, int_input_iterator {stream}, int_input_iterator {})};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                    assert(v.spare() == spare);
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number);
                    assert(v.back() == number);
                    auto numbers_i {0uz};
                    for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = 0;
                    for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                        assert(*it == number);
                    }
                    const auto tail_size {count - insertion_position};
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = insertion_size - 1;
                    for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                        assert(*it == numbers[numbers_i--]);
                    }
                    for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = insertion_size - 1;
                    for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                        assert(*it == numbers[numbers_i--]);
                    }
                    for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto i {0}; i < insertion_position; ++i) {
                        assert(v[i] == number);
                    }
                    numbers_i = 0;
                    for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                        assert(v[i] == numbers[numbers_i++]);
                    }
                    for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                        assert(v[i] == number);
                    }
                    assert(result == v.begin() + insertion_position);
                    assert(result == v.cbegin() + insertion_position);
                    std::cout << "\t\t\tChecking test_insert_2/Insert to non-empty vector/Insert to random position/Without reallocation/Insertion size less equal to tail size done." << std::endl;
                }

                // insertion size greater than tail size
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    const auto insertion_position {this->generate_a_random_number(1, count - 1)};
                    const auto insertion_size {this->generate_a_random_number(count - insertion_position + 1)};
                    const auto numbers {this->generate_random_sequence(insertion_size)};
                    auto stream {this->to_input_iterator(numbers)};
                    const auto number {this->generate_a_random_number()};
                    const auto spare {this->generate_count(count)};
                    vector<int> v(count + static_cast<size_t>(insertion_size) + spare, number);
                    v.cursor -= static_cast<size_t>(insertion_size) + spare;
                    const auto result {v.insert(insertion_position, int_input_iterator {stream}, int_input_iterator {})};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                    assert(v.spare() == spare);
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number);
                    assert(v.back() == number);
                    auto numbers_i {0uz};
                    for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = 0;
                    for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                        assert(*it == number);
                    }
                    const auto tail_size {count - insertion_position};
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = insertion_size - 1;
                    for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                        assert(*it == numbers[numbers_i--]);
                    }
                    for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = insertion_size - 1;
                    for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                        assert(*it == numbers[numbers_i--]);
                    }
                    for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto i {0}; i < insertion_position; ++i) {
                        assert(v[i] == number);
                    }
                    numbers_i = 0;
                    for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                        assert(v[i] == numbers[numbers_i++]);
                    }
                    for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                        assert(v[i] == number);
                    }
                    assert(result == v.begin() + insertion_position);
                    assert(result == v.cbegin() + insertion_position);
                    std::cout << "\t\t\tChecking test_insert_2/Insert to non-empty vector/Insert to random position/Without reallocation/Insertion size greater than tail size done." << std::endl;
                }

                std::cout << "\t\t\tStart checking test_insert_2/Insert to non-empty vector/Insert to random position/Without reallocation finished!" << std::endl;
            }

            // with reallocation
            {
                std::cout << "\t\t\tStart checking test_insert_2/Insert to non-empty vector/Insert to random position/With reallocation!" << std::endl;

                // insertion size less equal to tail size
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    const auto insertion_position {this->generate_a_random_number(1, count - 1)};
                    auto insertion_size {this->generate_a_random_number(1, count - insertion_position)};
                    const auto numbers {this->generate_random_sequence(insertion_size)};
                    auto stream {this->to_input_iterator(numbers)};
                    const auto number {this->generate_a_random_number()};
                    vector<int> v(count, number);
                    const auto result {v.insert(insertion_position, int_input_iterator {stream}, int_input_iterator {})};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                        assert(v.spare() == 0);
                    }else {
                        assert(v.capacity() == static_cast<size_t>(count) * 2);
                        assert(v.spare() == count - insertion_size);
                    }
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number);
                    assert(v.back() == number);
                    auto numbers_i {0uz};
                    for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = 0;
                    for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                        assert(*it == number);
                    }
                    const auto tail_size {count - insertion_position};
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = insertion_size - 1;
                    for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                        assert(*it == numbers[numbers_i--]);
                    }
                    for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = insertion_size - 1;
                    for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                        assert(*it == numbers[numbers_i--]);
                    }
                    for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto i {0}; i < insertion_position; ++i) {
                        assert(v[i] == number);
                    }
                    numbers_i = 0;
                    for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                        assert(v[i] == numbers[numbers_i++]);
                    }
                    for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                        assert(v[i] == number);
                    }
                    assert(result == v.begin() + insertion_position);
                    assert(result == v.cbegin() + insertion_position);
                    std::cout << "\t\t\tChecking test_insert_2/Insert to non-empty vector/Insert to random position/With reallocation/Insertion size less equal to tail size done." << std::endl;
                }

                // insertion size greater than tail size
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    const auto insertion_position {this->generate_a_random_number(1, count - 1)};
                    const auto insertion_size {this->generate_a_random_number(count - insertion_position + 1)};
                    const auto numbers {this->generate_random_sequence(insertion_size)};
                    auto stream {this->to_input_iterator(numbers)};
                    const auto number {this->generate_a_random_number()};
                    vector<int> v(count, number);
                    const auto result {v.insert(insertion_position, int_input_iterator {stream}, int_input_iterator {})};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                        assert(v.spare() == 0);
                    }else {
                        assert(v.capacity() == static_cast<size_t>(count) * 2);
                        assert(v.spare() == count - insertion_size);
                    }
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number);
                    assert(v.back() == number);
                    auto numbers_i {0uz};
                    for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = 0;
                    for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                        assert(*it == number);
                    }
                    const auto tail_size {count - insertion_position};
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = insertion_size - 1;
                    for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                        assert(*it == numbers[numbers_i--]);
                    }
                    for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = insertion_size - 1;
                    for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                        assert(*it == numbers[numbers_i--]);
                    }
                    for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto i {0}; i < insertion_position; ++i) {
                        assert(v[i] == number);
                    }
                    numbers_i = 0;
                    for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                        assert(v[i] == numbers[numbers_i++]);
                    }
                    for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                        assert(v[i] == number);
                    }
                    assert(result == v.begin() + insertion_position);
                    assert(result == v.cbegin() + insertion_position);
                    std::cout << "\t\t\tChecking test_insert_2/Insert to non-empty vector/Insert to random position/With reallocation/Insertion size greater than tail size done." << std::endl;
                }

                // insertion size less equal to double capacity
                {
                    auto count {this->generate_count()};
                    while(count <= 2) {
                        count = this->generate_count();
                    }
                    const auto insertion_position {this->generate_a_random_number(1, count - 2)};
                    auto insertion_size {this->generate_a_random_number(1, count)};
                    const auto numbers {this->generate_random_sequence(insertion_size)};
                    auto stream {this->to_input_iterator(numbers)};
                    const auto number {this->generate_a_random_number()};
                    vector<int> v(count, number);
                    auto result {v.insert(insertion_position, int_input_iterator {stream}, int_input_iterator {})};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    assert(v.capacity() == static_cast<size_t>(count) * 2);
                    assert(v.spare() == count - insertion_size);
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number);
                    assert(v.back() == number);
                    auto numbers_i {0uz};
                    for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = 0;
                    for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                        assert(*it == number);
                    }
                    const auto tail_size {count - insertion_position};
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = insertion_size - 1;
                    for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                        assert(*it == numbers[numbers_i--]);
                    }
                    for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = insertion_size - 1;
                    for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                        assert(*it == numbers[numbers_i--]);
                    }
                    for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto i {0}; i < insertion_position; ++i) {
                        assert(v[i] == number);
                    }
                    numbers_i = 0;
                    for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                        assert(v[i] == numbers[numbers_i++]);
                    }
                    for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                        assert(v[i] == number);
                    }
                    assert(result == v.begin() + insertion_position);
                    assert(result == v.cbegin() + insertion_position);
                    std::cout << "\t\t\tChecking test_insert_2/Insert to non-empty vector/Insert to random position/With reallocation/Insertion size less equal to double capacity done." << std::endl;
                }

                // insertion size greater than double capacity
                {
                    auto count {this->generate_count()};
                    while(count <= 2) {
                        count = this->generate_count();
                    }
                    const auto insertion_position {this->generate_a_random_number(1, count - 2)};
                    auto insertion_size {this->generate_a_random_number(2 * count + 1)};
                    const auto numbers {this->generate_random_sequence(insertion_size)};
                    auto stream {this->to_input_iterator(numbers)};
                    const auto number {this->generate_a_random_number()};
                    vector<int> v(count, number);
                    auto result {v.insert(insertion_position, int_input_iterator {stream}, int_input_iterator {})};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    assert(v.capacity() == static_cast<size_t>(count) + insertion_size);
                    assert(v.spare() == 0);
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number);
                    assert(v.back() == number);
                    auto numbers_i {0uz};
                    for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = 0;
                    for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                        assert(*it == number);
                    }
                    const auto tail_size {count - insertion_position};
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = insertion_size - 1;
                    for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                        assert(*it == numbers[numbers_i--]);
                    }
                    for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = insertion_size - 1;
                    for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                        assert(*it == numbers[numbers_i--]);
                    }
                    for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto i {0}; i < insertion_position; ++i) {
                        assert(v[i] == number);
                    }
                    numbers_i = 0;
                    for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                        assert(v[i] == numbers[numbers_i++]);
                    }
                    for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                        assert(v[i] == number);
                    }
                    assert(result == v.begin() + insertion_position);
                    assert(result == v.cbegin() + insertion_position);
                    std::cout << "\t\t\tChecking test_insert_2/Insert to non-empty vector/Insert to random position/With reallocation/Insertion size greater than double capacity done." << std::endl;
                }

                std::cout << "\t\t\tStart checking test_insert_2/Insert to non-empty vector/Insert to random position/With reallocation finished!" << std::endl;
            }

            std::cout << "\t\tChecking test_insert_2/Insert to non-empty vector/Insert to random position finished!" << std::endl;
        }

        // insert to tail
        {
            std::cout << "\t\tStart checking test_insert_2/Insert to non-empty vector/Insert to tail!" << std::endl;

            // without reallocation
            {
                std::cout << "\t\t\tStart checking test_insert_2/Insert to non-empty vector/Insert to tail/Without reallocation!" << std::endl;

                // insertion size is zero
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    const auto new_size {this->generate_a_random_number(1, count - 1)};
                    const auto number {this->generate_a_random_number()};
                    vector<int> v(count, number);
                    v.cursor = v.first + new_size;
                    const auto result {v.insert(new_size, int_input_iterator {}, int_input_iterator {})};
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
                    for(auto i {1}; i < v.size(); ++i) {
                        assert(v[i] == number);
                    }
                    assert(result == v.end());
                    assert(result == v.cend());
                    std::cout << "\t\t\t\tChecking test_insert_2/Insert to non-empty vector/Insert to tail/Without reallocation/Insertion size is zero done." << std::endl;
                }

                // insertion size less equal to tail size
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    auto insertion_size {this->generate_a_random_number(1, count)};
                    const auto numbers {this->generate_random_sequence(insertion_size)};
                    auto stream {this->to_input_iterator(numbers)};
                    const auto number {this->generate_a_random_number()};
                    const auto spare {this->generate_count(count)};
                    vector<int> v(count + static_cast<size_t>(insertion_size) + spare, number);
                    v.cursor -= insertion_size + spare;
                    const auto result {v.insert(count, int_input_iterator {stream}, int_input_iterator {})};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                    assert(v.spare() == spare);
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number);
                    assert(v.back() == numbers.back());
                    auto numbers_i {0uz};
                    for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = 0;
                    for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    numbers_i = insertion_size - 1;
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                        assert(*it == numbers[numbers_i--]);
                    }
                    for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                        assert(*it == number);
                    }
                    numbers_i = insertion_size - 1;
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                        assert(*it == numbers[numbers_i--]);
                    }
                    for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto i {0}; i < count; ++i) {
                        assert(v[i] == number);
                    }
                    numbers_i = 0;
                    for(auto i {count}; i < count + insertion_size; ++i) {
                        assert(v[i] == numbers[numbers_i++]);
                    }
                    assert(result == v.begin() + count);
                    assert(result == v.cbegin() + count);
                    std::cout << "\t\t\t\tChecking test_insert_2/Insert to non-empty vector/Insert to tail/Without reallocation/Insertion size less equal to tail size done." << std::endl;
                }

                // insertion size greater than tail size
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    const auto insertion_size {this->generate_a_random_number(count + 1)};
                    const auto numbers {this->generate_random_sequence(insertion_size)};
                    auto stream {this->to_input_iterator(numbers)};
                    const auto number {this->generate_a_random_number()};
                    const auto spare {this->generate_count(count)};
                    vector<int> v(count + static_cast<size_t>(insertion_size) + spare, number);
                    v.cursor -= static_cast<size_t>(insertion_size) + spare;
                    const auto result {v.insert(count, int_input_iterator {stream}, int_input_iterator {})};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                    assert(v.spare() == spare);
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number);
                    assert(v.back() == numbers.back());
                    auto numbers_i {0uz};
                    for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = 0;
                    for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    numbers_i = insertion_size - 1;
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                        assert(*it == numbers[numbers_i--]);
                    }
                    for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                        assert(*it == number);
                    }
                    numbers_i = insertion_size - 1;
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                        assert(*it == numbers[numbers_i--]);
                    }
                    for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto i {0}; i < count; ++i) {
                        assert(v[i] == number);
                    }
                    numbers_i = 0;
                    for(auto i {count}; i < count + insertion_size; ++i) {
                        assert(v[i] == numbers[numbers_i++]);
                    }
                    assert(result == v.begin() + count);
                    assert(result == v.cbegin() + count);
                    std::cout << "\t\t\t\tChecking test_insert_2/Insert to non-empty vector/Insert to tail/Without reallocation/Insertion size greater than tail size done." << std::endl;
                }

                std::cout << "\t\t\tStart checking test_insert_2/Insert to non-empty vector/Insert to tail/Without reallocation finished!" << std::endl;
            }

            // with reallocation
            {
                std::cout << "\t\t\tStart checking test_insert_2/Insert to non-empty vector/Insert to tail/With reallocation!" << std::endl;

                // insertion size less equal to tail size
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    auto insertion_size {this->generate_a_random_number(1, count)};
                    const auto numbers {this->generate_random_sequence(insertion_size)};
                    auto stream {this->to_input_iterator(numbers)};
                    const auto number {this->generate_a_random_number()};
                    vector<int> v(count, number);
                    const auto result {v.insert(count, int_input_iterator {stream}, int_input_iterator {})};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                        assert(v.spare() == 0);
                    }else {
                        assert(v.capacity() == static_cast<size_t>(count) * 2);
                        assert(v.spare() == count - insertion_size);
                    }
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number);
                    assert(v.back() == numbers.back());
                    auto numbers_i {0uz};
                    for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = 0;
                    for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    numbers_i = insertion_size - 1;
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                        assert(*it == numbers[numbers_i--]);
                    }
                    for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                        assert(*it == number);
                    }
                    numbers_i = insertion_size - 1;
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                        assert(*it == numbers[numbers_i--]);
                    }
                    for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto i {0}; i < count; ++i) {
                        assert(v[i] == number);
                    }
                    numbers_i = 0;
                    for(auto i {count}; i < count + insertion_size; ++i) {
                        assert(v[i] == numbers[numbers_i++]);
                    }
                    assert(result == v.begin() + count);
                    assert(result == v.cbegin() + count);
                    std::cout << "\t\t\t\tChecking test_insert_2/Insert to non-empty vector/Insert to tail/With reallocation/Insertion size less equal to tail size done." << std::endl;
                }

                // insertion size greater than tail size
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    const auto insertion_size {this->generate_a_random_number(count + 1)};
                    const auto numbers {this->generate_random_sequence(insertion_size)};
                    auto stream {this->to_input_iterator(numbers)};
                    const auto number {this->generate_a_random_number()};
                    vector<int> v(count, number);
                    const auto result {v.insert(count, int_input_iterator {stream}, int_input_iterator {})};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                        assert(v.spare() == 0);
                    }else {
                        assert(v.capacity() == static_cast<size_t>(count) * 2);
                        assert(v.spare() == count - insertion_size);
                    }
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number);
                    assert(v.back() == numbers.back());
                    auto numbers_i {0uz};
                    for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = 0;
                    for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    numbers_i = insertion_size - 1;
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                        assert(*it == numbers[numbers_i--]);
                    }
                    for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                        assert(*it == number);
                    }
                    numbers_i = insertion_size - 1;
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                        assert(*it == numbers[numbers_i--]);
                    }
                    for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto i {0}; i < count; ++i) {
                        assert(v[i] == number);
                    }
                    numbers_i = 0;
                    for(auto i {count}; i < count + insertion_size; ++i) {
                        assert(v[i] == numbers[numbers_i++]);
                    }
                    assert(result == v.begin() + count);
                    assert(result == v.cbegin() + count);
                    std::cout << "\t\t\t\tChecking test_insert_2/Insert to non-empty vector/Insert to tail/With reallocation/Insertion size greater than tail size done." << std::endl;
                }

                // insertion size less equal to double capacity
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    auto insertion_size {this->generate_a_random_number(1, count)};
                    const auto numbers {this->generate_random_sequence(insertion_size)};
                    auto stream {this->to_input_iterator(numbers)};
                    const auto number {this->generate_a_random_number()};
                    vector<int> v(count, number);
                    auto result {v.insert(count, int_input_iterator {stream}, int_input_iterator {})};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    assert(v.capacity() == static_cast<size_t>(count) * 2);
                    assert(v.spare() == count - insertion_size);
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number);
                    assert(v.back() == numbers.back());
                    auto numbers_i {0uz};
                    for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = 0;
                    for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    numbers_i = insertion_size - 1;
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                        assert(*it == numbers[numbers_i--]);
                    }
                    for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                        assert(*it == number);
                    }
                    numbers_i = insertion_size - 1;
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                        assert(*it == numbers[numbers_i--]);
                    }
                    for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto i {0}; i < count; ++i) {
                        assert(v[i] == number);
                    }
                    numbers_i = 0;
                    for(auto i {count}; i < count + insertion_size; ++i) {
                        assert(v[i] == numbers[numbers_i++]);
                    }
                    assert(result == v.begin() + count);
                    assert(result == v.cbegin() + count);
                    std::cout << "\t\t\t\tChecking test_insert_2/Insert to non-empty vector/Insert to tail/With reallocation/Insertion size less equal to double capacity done." << std::endl;
                }

                // insertion size greater than double capacity
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    auto insertion_size {this->generate_a_random_number(2 * count + 1)};
                    const auto numbers {this->generate_random_sequence(insertion_size)};
                    auto stream {this->to_input_iterator(numbers)};
                    const auto number {this->generate_a_random_number()};
                    vector<int> v(count, number);
                    auto result {v.insert(count, int_input_iterator {stream}, int_input_iterator {})};
                    assert(v.size() == count + static_cast<size_t>(insertion_size));
                    assert(not v.empty());
                    assert(v.capacity() == static_cast<size_t>(count) + insertion_size);
                    assert(v.spare() == 0);
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                    assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                    assert(v.front() == number);
                    assert(v.back() == numbers.back());
                    auto numbers_i {0uz};
                    for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = 0;
                    for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    numbers_i = insertion_size - 1;
                    for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                        assert(*it == numbers[numbers_i--]);
                    }
                    for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                        assert(*it == number);
                    }
                    numbers_i = insertion_size - 1;
                    for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                        assert(*it == numbers[numbers_i--]);
                    }
                    for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                        assert(*it == number);
                    }
                    for(auto i {0}; i < count; ++i) {
                        assert(v[i] == number);
                    }
                    numbers_i = 0;
                    for(auto i {count}; i < count + insertion_size; ++i) {
                        assert(v[i] == numbers[numbers_i++]);
                    }
                    assert(result == v.begin() + count);
                    assert(result == v.cbegin() + count);
                    std::cout << "\t\t\t\tChecking test_insert_2/Insert to non-empty vector/Insert to tail/With reallocation/Insertion size greater than double capacity done." << std::endl;
                }

                std::cout << "\t\t\tStart checking test_insert_2/Insert to non-empty vector/Insert to tail/With reallocation finished!" << std::endl;
            }

            std::cout << "\t\tChecking test_insert_2/Insert to non-empty vector/Insert to tail finished!" << std::endl;
        }

        std::cout << "\tChecking test_insert_2/Insert to non-empty vector finished!" << std::endl;
    }

    std::cout << "Checking iterator insert(size_type, InputIterator, InputIterator) for ds::vector finished!" << std::endl;
}
void vector_correctness::test_insert_3() {
    std::cout << "Start checking iterator insert(size_type, ForwardIterator, ForwardIterator) for ds::vector!" << std::endl;

    // forward iterator
    {
        std::cout << "\tStart checking test_insert_3/Forward iterator for ds::vector!" << std::endl;

        // insert to empty vector
        {
            std::cout << "\t\tStart checking test_insert_3/Forward iteratorInsert to empty vector for ds::vector!" << std::endl;

            // insertion size equal to zero
            {
                vector<int> v {};
                const auto result {v.insert(0, int_forward_iterator {}, int_forward_iterator {})};
                assert(v.size() == 0);
                assert(v.empty());
                assert(v.capacity() == 0);
                assert(v.spare() == 0);
                assert(v.data() == nullptr);
                assert(v.begin() == v.end());
                assert(v.cbegin() == v.cend());
                assert(result == v.begin());
                assert(result == v.cbegin());
                std::cout << "\t\t\tChecking test_insert_3/Forward iteratorInsert to empty vector/Insertion size not equal to zero done." << std::endl;
            }

            // insertion size not equal to zero
            {
                vector<int> v {};
                auto insertion_size {this->generate_count()};
                while(insertion_size == 0) {
                    insertion_size = this->generate_count();
                }
                const auto numbers {this->generate_random_sequence(insertion_size)};
                auto l {this->to_forward_iterator(numbers)};
                const auto result {v.insert(0, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                assert(v.size() == insertion_size);
                assert(not v.empty());
                assert(v.capacity() == insertion_size);
                assert(v.spare() == 0);
                assert(v.data() not_eq nullptr);
                assert(v.begin() + insertion_size == v.end());
                assert(v.cbegin() + insertion_size == v.cend());
                assert(v.front() == numbers.front());
                assert(v.back() == numbers.back());
                auto i {0uz};
                for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                    assert(*it == numbers[i++]);
                }
                i = 0;
                for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                    assert(*it == numbers[i++]);
                }
                i = insertion_size - 1;
                for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                    assert(*it == numbers[i--]);
                }
                i = insertion_size - 1;
                for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                    assert(*it == numbers[i--]);
                }
                for(auto i {0}; i < v.size(); ++i) {
                    assert(v[i] == numbers[i]);
                }
                assert(result == v.begin());
                assert(result == v.cbegin());
                std::cout << "\t\t\tChecking test_insert_3/Forward iteratorInsert to empty vector/Insertion size not equal to zero done." << std::endl;
            }

            std::cout << "\t\tChecking test_insert_3/Forward iteratorInsert to empty vector for ds::vector finished!" << std::endl;
        }

        // insert to non-empty vector
        {
            std::cout << "\t\tStart checking test_insert_3/Forward iteratorInsert to non-empty vector!" << std::endl;

            // insert to head
            {
                std::cout << "\t\t\tStart checking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to head!" << std::endl;

                // without reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to head/Without reallocation!" << std::endl;

                    // insertion size is zero
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto new_size {this->generate_a_random_number(1, count - 1)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        v.cursor = v.first + new_size;
                        const auto result {v.insert(0, int_forward_iterator {}, int_forward_iterator {})};
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
                        for(auto i {1}; i < v.size(); ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin());
                        assert(result == v.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to head/Without reallocation/Insertion size is zero done." << std::endl;
                    }

                    // insertion size less equal to tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        auto insertion_size {this->generate_a_random_number(1, count)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_forward_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        const auto spare {this->generate_count(count)};
                        vector<int> v(count + static_cast<size_t>(insertion_size) + spare, number);
                        v.cursor -= insertion_size + spare;
                        const auto result {v.insert(0, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                        assert(v.spare() == spare);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == numbers.front());
                        assert(v.back() == number);
                        auto number_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        number_i = 0;
                        for(auto i {0}; i < insertion_size; ++i) {
                            assert(v[i] == numbers[number_i++]);
                        }
                        for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin());
                        assert(result == v.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to head/Without reallocation/Insertion size less equal to tail size done." << std::endl;
                    }

                    // insertion size greater than tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_size {this->generate_a_random_number(count + 1)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_forward_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        const auto spare {this->generate_count(count)};
                        vector<int> v(count + static_cast<size_t>(insertion_size) + spare, number);
                        v.cursor -= static_cast<size_t>(insertion_size) + spare;
                        const auto result {v.insert(0, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                        assert(v.spare() == spare);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == numbers.front());
                        assert(v.back() == number);
                        auto number_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        number_i = 0;
                        for(auto i {0}; i < insertion_size; ++i) {
                            assert(v[i] == numbers[number_i++]);
                        }
                        for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin());
                        assert(result == v.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to head/Without reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to head/Without reallocation finished!" << std::endl;
                }

                // with reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to head/With reallocation!" << std::endl;

                    // insertion size less equal to tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        auto insertion_size {this->generate_a_random_number(1, count)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_forward_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        const auto result {v.insert(0, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                            assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                            assert(v.spare() == 0);
                        }else {
                            assert(v.capacity() == static_cast<size_t>(count) * 2);
                            assert(v.spare() == count - insertion_size);
                        }
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == numbers.front());
                        assert(v.back() == number);
                        auto number_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        number_i = 0;
                        for(auto i {0}; i < insertion_size; ++i) {
                            assert(v[i] == numbers[number_i++]);
                        }
                        for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin());
                        assert(result == v.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to head/With reallocation/Insertion size less equal to tail size done." << std::endl;
                    }

                    // insertion size greater than tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_size {this->generate_a_random_number(count + 1)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_forward_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        const auto result {v.insert(0, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                            assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                            assert(v.spare() == 0);
                        }else {
                            assert(v.capacity() == static_cast<size_t>(count) * 2);
                            assert(v.spare() == count - insertion_size);
                        }
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == numbers.front());
                        assert(v.back() == number);
                        auto number_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        number_i = 0;
                        for(auto i {0}; i < insertion_size; ++i) {
                            assert(v[i] == numbers[number_i++]);
                        }
                        for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin());
                        assert(result == v.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to head/With reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    // insertion size less equal to double capacity
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_size {this->generate_a_random_number(1, count)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_forward_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        auto result {v.insert(0, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == static_cast<size_t>(count) * 2);
                        assert(v.spare() == count - insertion_size);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == numbers.front());
                        assert(v.back() == number);
                        auto number_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        number_i = 0;
                        for(auto i {0}; i < insertion_size; ++i) {
                            assert(v[i] == numbers[number_i++]);
                        }
                        for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin());
                        assert(result == v.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to head/With reallocation/Insertion size less equal to double capacity done." << std::endl;
                    }

                    // insertion size greater than double capacity
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_size {this->generate_a_random_number(2 * count + 1)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_forward_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        auto result {v.insert(0, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == static_cast<size_t>(count) + insertion_size);
                        assert(v.spare() == 0);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == numbers.front());
                        assert(v.back() == number);
                        auto number_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        number_i = 0;
                        for(auto i {0}; i < insertion_size; ++i) {
                            assert(v[i] == numbers[number_i++]);
                        }
                        for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin());
                        assert(result == v.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to head/With reallocation/Insertion size greater than double capacity done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to head/With reallocation finished!" << std::endl;
                }

                std::cout << "\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to head finished!" << std::endl;
            }

            // insert to random position
            {
                std::cout << "\t\t\tStart checking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to random position!" << std::endl;

                // without reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to random position/Without reallocation!" << std::endl;

                    // insertion size is zero
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto new_size {this->generate_a_random_number(1, count - 1)};
                        const auto number {this->generate_a_random_number()};
                        const auto insertion_position {this->generate_a_random_number(1, new_size - 1)};
                        vector<int> v(count, number);
                        v.cursor = v.first + new_size;
                        const auto result {v.insert(insertion_position, int_forward_iterator {}, int_forward_iterator {})};
                        assert(v.size() == new_size);
                        assert(not v.empty());
                        assert(v.capacity() == count);
                        assert(v.spare() == count - new_size);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + new_size == v.end());
                        assert(v.cbegin() + new_size == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == number);
                        for(auto it {v.begin() + 1}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.cbegin() + 1}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.rbegin()}; it not_eq v.rend() - 1; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crend() - 1; ++it) {
                            assert(*it == number);
                        }
                        for(auto i {1}; i < v.size(); ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin() + insertion_position);
                        assert(result == v.cbegin() + insertion_position);
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to random position/Without reallocation/Insertion size is zero done." << std::endl;
                    }

                    // insertion size less equal to tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_position {this->generate_a_random_number(1, count - 1)};
                        auto insertion_size {this->generate_a_random_number(1, count - insertion_position)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_forward_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        const auto spare {this->generate_count(count)};
                        vector<int> v(count + static_cast<size_t>(insertion_size) + spare, number);
                        v.cursor -= insertion_size + spare;
                        const auto result {v.insert(insertion_position, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                        assert(v.spare() == spare);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == number);
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        const auto tail_size {count - insertion_position};
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < insertion_position; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin() + insertion_position);
                        assert(result == v.cbegin() + insertion_position);
                        std::cout << "\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to random position/Without reallocation/Insertion size less equal to tail size done." << std::endl;
                    }

                    // insertion size greater than tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_position {this->generate_a_random_number(1, count - 1)};
                        const auto insertion_size {this->generate_a_random_number(count - insertion_position + 1)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_forward_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        const auto spare {this->generate_count(count)};
                        vector<int> v(count + static_cast<size_t>(insertion_size) + spare, number);
                        v.cursor -= static_cast<size_t>(insertion_size) + spare;
                        const auto result {v.insert(insertion_position, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                        assert(v.spare() == spare);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == number);
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        const auto tail_size {count - insertion_position};
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < insertion_position; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin() + insertion_position);
                        assert(result == v.cbegin() + insertion_position);
                        std::cout << "\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to random position/Without reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to random position/Without reallocation finished!" << std::endl;
                }

                // with reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to random position/With reallocation!" << std::endl;

                    // insertion size less equal to tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_position {this->generate_a_random_number(1, count - 1)};
                        auto insertion_size {this->generate_a_random_number(1, count - insertion_position)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_forward_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        const auto result {v.insert(insertion_position, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                            assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                            assert(v.spare() == 0);
                        }else {
                            assert(v.capacity() == static_cast<size_t>(count) * 2);
                            assert(v.spare() == count - insertion_size);
                        }
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == number);
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        const auto tail_size {count - insertion_position};
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < insertion_position; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin() + insertion_position);
                        assert(result == v.cbegin() + insertion_position);
                        std::cout << "\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to random position/With reallocation/Insertion size less equal to tail size done." << std::endl;
                    }

                    // insertion size greater than tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_position {this->generate_a_random_number(1, count - 1)};
                        const auto insertion_size {this->generate_a_random_number(count - insertion_position + 1)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_forward_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        const auto result {v.insert(insertion_position, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                            assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                            assert(v.spare() == 0);
                        }else {
                            assert(v.capacity() == static_cast<size_t>(count) * 2);
                            assert(v.spare() == count - insertion_size);
                        }
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == number);
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        const auto tail_size {count - insertion_position};
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < insertion_position; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin() + insertion_position);
                        assert(result == v.cbegin() + insertion_position);
                        std::cout << "\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to random position/With reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    // insertion size less equal to double capacity
                    {
                        auto count {this->generate_count()};
                        while(count <= 2) {
                            count = this->generate_count();
                        }
                        const auto insertion_position {this->generate_a_random_number(1, count - 2)};
                        auto insertion_size {this->generate_a_random_number(1, count)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_forward_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        auto result {v.insert(insertion_position, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == static_cast<size_t>(count) * 2);
                        assert(v.spare() == count - insertion_size);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == number);
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        const auto tail_size {count - insertion_position};
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < insertion_position; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin() + insertion_position);
                        assert(result == v.cbegin() + insertion_position);
                        std::cout << "\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to random position/With reallocation/Insertion size less equal to double capacity done." << std::endl;
                    }

                    // insertion size greater than double capacity
                    {
                        auto count {this->generate_count()};
                        while(count <= 2) {
                            count = this->generate_count();
                        }
                        const auto insertion_position {this->generate_a_random_number(1, count - 2)};
                        auto insertion_size {this->generate_a_random_number(2 * count + 1)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_forward_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        auto result {v.insert(insertion_position, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == static_cast<size_t>(count) + insertion_size);
                        assert(v.spare() == 0);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == number);
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        const auto tail_size {count - insertion_position};
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < insertion_position; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin() + insertion_position);
                        assert(result == v.cbegin() + insertion_position);
                        std::cout << "\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to random position/With reallocation/Insertion size greater than double capacity done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to random position/With reallocation finished!" << std::endl;
                }

                std::cout << "\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to random position finished!" << std::endl;
            }

            // insert to tail
            {
                std::cout << "\t\t\tStart checking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to tail!" << std::endl;

                // without reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to tail/Without reallocation!" << std::endl;

                    // insertion size is zero
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto new_size {this->generate_a_random_number(1, count - 1)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        v.cursor = v.first + new_size;
                        const auto result {v.insert(new_size, int_forward_iterator {}, int_forward_iterator {})};
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
                        for(auto i {1}; i < v.size(); ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.end());
                        assert(result == v.cend());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to tail/Without reallocation/Insertion size is zero done." << std::endl;
                    }

                    // insertion size less equal to tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        auto insertion_size {this->generate_a_random_number(1, count)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_forward_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        const auto spare {this->generate_count(count)};
                        vector<int> v(count + static_cast<size_t>(insertion_size) + spare, number);
                        v.cursor -= insertion_size + spare;
                        const auto result {v.insert(count, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                        assert(v.spare() == spare);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == numbers.back());
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < count; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {count}; i < count + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        assert(result == v.begin() + count);
                        assert(result == v.cbegin() + count);
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to tail/Without reallocation/Insertion size less equal to tail size done." << std::endl;
                    }

                    // insertion size greater than tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_size {this->generate_a_random_number(count + 1)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_forward_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        const auto spare {this->generate_count(count)};
                        vector<int> v(count + static_cast<size_t>(insertion_size) + spare, number);
                        v.cursor -= static_cast<size_t>(insertion_size) + spare;
                        const auto result {v.insert(count, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                        assert(v.spare() == spare);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == numbers.back());
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < count; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {count}; i < count + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        assert(result == v.begin() + count);
                        assert(result == v.cbegin() + count);
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to tail/Without reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to tail/Without reallocation finished!" << std::endl;
                }

                // with reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to tail/With reallocation!" << std::endl;

                    // insertion size less equal to tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        auto insertion_size {this->generate_a_random_number(1, count)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_forward_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        const auto result {v.insert(count, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                            assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                            assert(v.spare() == 0);
                        }else {
                            assert(v.capacity() == static_cast<size_t>(count) * 2);
                            assert(v.spare() == count - insertion_size);
                        }
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == numbers.back());
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < count; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {count}; i < count + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        assert(result == v.begin() + count);
                        assert(result == v.cbegin() + count);
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to tail/With reallocation/Insertion size less equal to tail size done." << std::endl;
                    }

                    // insertion size greater than tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_size {this->generate_a_random_number(count + 1)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_forward_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        const auto result {v.insert(count, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                            assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                            assert(v.spare() == 0);
                        }else {
                            assert(v.capacity() == static_cast<size_t>(count) * 2);
                            assert(v.spare() == count - insertion_size);
                        }
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == numbers.back());
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < count; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {count}; i < count + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        assert(result == v.begin() + count);
                        assert(result == v.cbegin() + count);
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to tail/With reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    // insertion size less equal to double capacity
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        auto insertion_size {this->generate_a_random_number(1, count)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_forward_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        auto result {v.insert(count, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == static_cast<size_t>(count) * 2);
                        assert(v.spare() == count - insertion_size);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == numbers.back());
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < count; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {count}; i < count + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        assert(result == v.begin() + count);
                        assert(result == v.cbegin() + count);
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to tail/With reallocation/Insertion size less equal to double capacity done." << std::endl;
                    }

                    // insertion size greater than double capacity
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        auto insertion_size {this->generate_a_random_number(2 * count + 1)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_forward_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        auto result {v.insert(count, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == static_cast<size_t>(count) + insertion_size);
                        assert(v.spare() == 0);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == numbers.back());
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < count; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {count}; i < count + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        assert(result == v.begin() + count);
                        assert(result == v.cbegin() + count);
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to tail/With reallocation/Insertion size greater than double capacity done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to tail/With reallocation finished!" << std::endl;
                }

                std::cout << "\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty vector/Insert to tail finished!" << std::endl;
            }

            std::cout << "\t\tChecking test_insert_3/Forward iteratorInsert to non-empty vector finished!" << std::endl;
        }

        std::cout << "\tChecking test_insert3/Forward iterator for ds::vector finished!" << std::endl;
    }

    // bidirectional iterator
    {
        std::cout << "\tStart checking test_insert_3/Bidirectional iterator for ds::vector!" << std::endl;

        // insert to empty vector
        {
            std::cout << "\t\tStart checking test_insert_3/Bidirectional iteratorInsert to empty vector for ds::vector!" << std::endl;

            // insertion size equal to zero
            {
                vector<int> v {};
                const auto result {v.insert(0, int_bidirectional_iterator {}, int_bidirectional_iterator {})};
                assert(v.size() == 0);
                assert(v.empty());
                assert(v.capacity() == 0);
                assert(v.spare() == 0);
                assert(v.data() == nullptr);
                assert(v.begin() == v.end());
                assert(v.cbegin() == v.cend());
                assert(result == v.begin());
                assert(result == v.cbegin());
                std::cout << "\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to empty vector/Insertion size not equal to zero done." << std::endl;
            }

            // insertion size not equal to zero
            {
                vector<int> v {};
                auto insertion_size {this->generate_count()};
                while(insertion_size == 0) {
                    insertion_size = this->generate_count();
                }
                const auto numbers {this->generate_random_sequence(insertion_size)};
                auto l {this->to_bidirectional_iterator(numbers)};
                const auto result {v.insert(0, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                assert(v.size() == insertion_size);
                assert(not v.empty());
                assert(v.capacity() == insertion_size);
                assert(v.spare() == 0);
                assert(v.data() not_eq nullptr);
                assert(v.begin() + insertion_size == v.end());
                assert(v.cbegin() + insertion_size == v.cend());
                assert(v.front() == numbers.front());
                assert(v.back() == numbers.back());
                auto i {0uz};
                for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                    assert(*it == numbers[i++]);
                }
                i = 0;
                for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                    assert(*it == numbers[i++]);
                }
                i = insertion_size - 1;
                for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                    assert(*it == numbers[i--]);
                }
                i = insertion_size - 1;
                for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                    assert(*it == numbers[i--]);
                }
                for(auto i {0}; i < v.size(); ++i) {
                    assert(v[i] == numbers[i]);
                }
                assert(result == v.begin());
                assert(result == v.cbegin());
                std::cout << "\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to empty vector/Insertion size not equal to zero done." << std::endl;
            }

            std::cout << "\t\tChecking test_insert_3/Bidirectional iteratorInsert to empty vector for ds::vector finished!" << std::endl;
        }

        // insert to non-empty vector
        {
            std::cout << "\t\tStart checking test_insert_3/Bidirectional iteratorInsert to non-empty vector!" << std::endl;

            // insert to head
            {
                std::cout << "\t\t\tStart checking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to head!" << std::endl;

                // without reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to head/Without reallocation!" << std::endl;

                    // insertion size is zero
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto new_size {this->generate_a_random_number(1, count - 1)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        v.cursor = v.first + new_size;
                        const auto result {v.insert(0, int_bidirectional_iterator {}, int_bidirectional_iterator {})};
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
                        for(auto i {1}; i < v.size(); ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin());
                        assert(result == v.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to head/Without reallocation/Insertion size is zero done." << std::endl;
                    }

                    // insertion size less equal to tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        auto insertion_size {this->generate_a_random_number(1, count)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_bidirectional_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        const auto spare {this->generate_count(count)};
                        vector<int> v(count + static_cast<size_t>(insertion_size) + spare, number);
                        v.cursor -= insertion_size + spare;
                        const auto result {v.insert(0, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                        assert(v.spare() == spare);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == numbers.front());
                        assert(v.back() == number);
                        auto number_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        number_i = 0;
                        for(auto i {0}; i < insertion_size; ++i) {
                            assert(v[i] == numbers[number_i++]);
                        }
                        for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin());
                        assert(result == v.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to head/Without reallocation/Insertion size less equal to tail size done." << std::endl;
                    }

                    // insertion size greater than tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_size {this->generate_a_random_number(count + 1)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_bidirectional_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        const auto spare {this->generate_count(count)};
                        vector<int> v(count + static_cast<size_t>(insertion_size) + spare, number);
                        v.cursor -= static_cast<size_t>(insertion_size) + spare;
                        const auto result {v.insert(0, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                        assert(v.spare() == spare);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == numbers.front());
                        assert(v.back() == number);
                        auto number_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        number_i = 0;
                        for(auto i {0}; i < insertion_size; ++i) {
                            assert(v[i] == numbers[number_i++]);
                        }
                        for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin());
                        assert(result == v.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to head/Without reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to head/Without reallocation finished!" << std::endl;
                }

                // with reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to head/With reallocation!" << std::endl;

                    // insertion size less equal to tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        auto insertion_size {this->generate_a_random_number(1, count)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_bidirectional_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        const auto result {v.insert(0, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                            assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                            assert(v.spare() == 0);
                        }else {
                            assert(v.capacity() == static_cast<size_t>(count) * 2);
                            assert(v.spare() == count - insertion_size);
                        }
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == numbers.front());
                        assert(v.back() == number);
                        auto number_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        number_i = 0;
                        for(auto i {0}; i < insertion_size; ++i) {
                            assert(v[i] == numbers[number_i++]);
                        }
                        for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin());
                        assert(result == v.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to head/With reallocation/Insertion size less equal to tail size done." << std::endl;
                    }

                    // insertion size greater than tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_size {this->generate_a_random_number(count + 1)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_bidirectional_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        const auto result {v.insert(0, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                            assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                            assert(v.spare() == 0);
                        }else {
                            assert(v.capacity() == static_cast<size_t>(count) * 2);
                            assert(v.spare() == count - insertion_size);
                        }
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == numbers.front());
                        assert(v.back() == number);
                        auto number_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        number_i = 0;
                        for(auto i {0}; i < insertion_size; ++i) {
                            assert(v[i] == numbers[number_i++]);
                        }
                        for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin());
                        assert(result == v.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to head/With reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    // insertion size less equal to double capacity
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_size {this->generate_a_random_number(1, count)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_bidirectional_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        auto result {v.insert(0, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == static_cast<size_t>(count) * 2);
                        assert(v.spare() == count - insertion_size);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == numbers.front());
                        assert(v.back() == number);
                        auto number_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        number_i = 0;
                        for(auto i {0}; i < insertion_size; ++i) {
                            assert(v[i] == numbers[number_i++]);
                        }
                        for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin());
                        assert(result == v.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to head/With reallocation/Insertion size less equal to double capacity done." << std::endl;
                    }

                    // insertion size greater than double capacity
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_size {this->generate_a_random_number(2 * count + 1)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_bidirectional_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        auto result {v.insert(0, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == static_cast<size_t>(count) + insertion_size);
                        assert(v.spare() == 0);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == numbers.front());
                        assert(v.back() == number);
                        auto number_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        number_i = 0;
                        for(auto i {0}; i < insertion_size; ++i) {
                            assert(v[i] == numbers[number_i++]);
                        }
                        for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin());
                        assert(result == v.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to head/With reallocation/Insertion size greater than double capacity done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to head/With reallocation finished!" << std::endl;
                }

                std::cout << "\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to head finished!" << std::endl;
            }

            // insert to random position
            {
                std::cout << "\t\t\tStart checking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to random position!" << std::endl;

                // without reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to random position/Without reallocation!" << std::endl;

                    // insertion size is zero
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto new_size {this->generate_a_random_number(1, count - 1)};
                        const auto number {this->generate_a_random_number()};
                        const auto insertion_position {this->generate_a_random_number(1, new_size - 1)};
                        vector<int> v(count, number);
                        v.cursor = v.first + new_size;
                        const auto result {v.insert(insertion_position, int_bidirectional_iterator {}, int_bidirectional_iterator {})};
                        assert(v.size() == new_size);
                        assert(not v.empty());
                        assert(v.capacity() == count);
                        assert(v.spare() == count - new_size);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + new_size == v.end());
                        assert(v.cbegin() + new_size == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == number);
                        for(auto it {v.begin() + 1}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.cbegin() + 1}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.rbegin()}; it not_eq v.rend() - 1; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crend() - 1; ++it) {
                            assert(*it == number);
                        }
                        for(auto i {1}; i < v.size(); ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin() + insertion_position);
                        assert(result == v.cbegin() + insertion_position);
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to random position/Without reallocation/Insertion size is zero done." << std::endl;
                    }

                    // insertion size less equal to tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_position {this->generate_a_random_number(1, count - 1)};
                        auto insertion_size {this->generate_a_random_number(1, count - insertion_position)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_bidirectional_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        const auto spare {this->generate_count(count)};
                        vector<int> v(count + static_cast<size_t>(insertion_size) + spare, number);
                        v.cursor -= insertion_size + spare;
                        const auto result {v.insert(insertion_position, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                        assert(v.spare() == spare);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == number);
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        const auto tail_size {count - insertion_position};
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < insertion_position; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin() + insertion_position);
                        assert(result == v.cbegin() + insertion_position);
                        std::cout << "\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to random position/Without reallocation/Insertion size less equal to tail size done." << std::endl;
                    }

                    // insertion size greater than tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_position {this->generate_a_random_number(1, count - 1)};
                        const auto insertion_size {this->generate_a_random_number(count - insertion_position + 1)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_bidirectional_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        const auto spare {this->generate_count(count)};
                        vector<int> v(count + static_cast<size_t>(insertion_size) + spare, number);
                        v.cursor -= static_cast<size_t>(insertion_size) + spare;
                        const auto result {v.insert(insertion_position, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                        assert(v.spare() == spare);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == number);
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        const auto tail_size {count - insertion_position};
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < insertion_position; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin() + insertion_position);
                        assert(result == v.cbegin() + insertion_position);
                        std::cout << "\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to random position/Without reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to random position/Without reallocation finished!" << std::endl;
                }

                // with reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to random position/With reallocation!" << std::endl;

                    // insertion size less equal to tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_position {this->generate_a_random_number(1, count - 1)};
                        auto insertion_size {this->generate_a_random_number(1, count - insertion_position)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_bidirectional_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        const auto result {v.insert(insertion_position, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                            assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                            assert(v.spare() == 0);
                        }else {
                            assert(v.capacity() == static_cast<size_t>(count) * 2);
                            assert(v.spare() == count - insertion_size);
                        }
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == number);
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        const auto tail_size {count - insertion_position};
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < insertion_position; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin() + insertion_position);
                        assert(result == v.cbegin() + insertion_position);
                        std::cout << "\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to random position/With reallocation/Insertion size less equal to tail size done." << std::endl;
                    }

                    // insertion size greater than tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_position {this->generate_a_random_number(1, count - 1)};
                        const auto insertion_size {this->generate_a_random_number(count - insertion_position + 1)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_bidirectional_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        const auto result {v.insert(insertion_position, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                            assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                            assert(v.spare() == 0);
                        }else {
                            assert(v.capacity() == static_cast<size_t>(count) * 2);
                            assert(v.spare() == count - insertion_size);
                        }
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == number);
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        const auto tail_size {count - insertion_position};
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < insertion_position; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin() + insertion_position);
                        assert(result == v.cbegin() + insertion_position);
                        std::cout << "\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to random position/With reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    // insertion size less equal to double capacity
                    {
                        auto count {this->generate_count()};
                        while(count <= 2) {
                            count = this->generate_count();
                        }
                        const auto insertion_position {this->generate_a_random_number(1, count - 2)};
                        auto insertion_size {this->generate_a_random_number(1, count)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_bidirectional_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        auto result {v.insert(insertion_position, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == static_cast<size_t>(count) * 2);
                        assert(v.spare() == count - insertion_size);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == number);
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        const auto tail_size {count - insertion_position};
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < insertion_position; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin() + insertion_position);
                        assert(result == v.cbegin() + insertion_position);
                        std::cout << "\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to random position/With reallocation/Insertion size less equal to double capacity done." << std::endl;
                    }

                    // insertion size greater than double capacity
                    {
                        auto count {this->generate_count()};
                        while(count <= 2) {
                            count = this->generate_count();
                        }
                        const auto insertion_position {this->generate_a_random_number(1, count - 2)};
                        auto insertion_size {this->generate_a_random_number(2 * count + 1)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_bidirectional_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        auto result {v.insert(insertion_position, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == static_cast<size_t>(count) + insertion_size);
                        assert(v.spare() == 0);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == number);
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        const auto tail_size {count - insertion_position};
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < insertion_position; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin() + insertion_position);
                        assert(result == v.cbegin() + insertion_position);
                        std::cout << "\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to random position/With reallocation/Insertion size greater than double capacity done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to random position/With reallocation finished!" << std::endl;
                }

                std::cout << "\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to random position finished!" << std::endl;
            }

            // insert to tail
            {
                std::cout << "\t\t\tStart checking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to tail!" << std::endl;

                // without reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to tail/Without reallocation!" << std::endl;

                    // insertion size is zero
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto new_size {this->generate_a_random_number(1, count - 1)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        v.cursor = v.first + new_size;
                        const auto result {v.insert(new_size, int_bidirectional_iterator {}, int_bidirectional_iterator {})};
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
                        for(auto i {1}; i < v.size(); ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.end());
                        assert(result == v.cend());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to tail/Without reallocation/Insertion size is zero done." << std::endl;
                    }

                    // insertion size less equal to tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        auto insertion_size {this->generate_a_random_number(1, count)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_bidirectional_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        const auto spare {this->generate_count(count)};
                        vector<int> v(count + static_cast<size_t>(insertion_size) + spare, number);
                        v.cursor -= insertion_size + spare;
                        const auto result {v.insert(count, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                        assert(v.spare() == spare);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == numbers.back());
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < count; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {count}; i < count + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        assert(result == v.begin() + count);
                        assert(result == v.cbegin() + count);
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to tail/Without reallocation/Insertion size less equal to tail size done." << std::endl;
                    }

                    // insertion size greater than tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_size {this->generate_a_random_number(count + 1)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_bidirectional_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        const auto spare {this->generate_count(count)};
                        vector<int> v(count + static_cast<size_t>(insertion_size) + spare, number);
                        v.cursor -= static_cast<size_t>(insertion_size) + spare;
                        const auto result {v.insert(count, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                        assert(v.spare() == spare);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == numbers.back());
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < count; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {count}; i < count + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        assert(result == v.begin() + count);
                        assert(result == v.cbegin() + count);
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to tail/Without reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to tail/Without reallocation finished!" << std::endl;
                }

                // with reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to tail/With reallocation!" << std::endl;

                    // insertion size less equal to tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        auto insertion_size {this->generate_a_random_number(1, count)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_bidirectional_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        const auto result {v.insert(count, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                            assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                            assert(v.spare() == 0);
                        }else {
                            assert(v.capacity() == static_cast<size_t>(count) * 2);
                            assert(v.spare() == count - insertion_size);
                        }
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == numbers.back());
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < count; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {count}; i < count + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        assert(result == v.begin() + count);
                        assert(result == v.cbegin() + count);
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to tail/With reallocation/Insertion size less equal to tail size done." << std::endl;
                    }

                    // insertion size greater than tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_size {this->generate_a_random_number(count + 1)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_bidirectional_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        const auto result {v.insert(count, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                            assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                            assert(v.spare() == 0);
                        }else {
                            assert(v.capacity() == static_cast<size_t>(count) * 2);
                            assert(v.spare() == count - insertion_size);
                        }
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == numbers.back());
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < count; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {count}; i < count + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        assert(result == v.begin() + count);
                        assert(result == v.cbegin() + count);
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to tail/With reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    // insertion size less equal to double capacity
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        auto insertion_size {this->generate_a_random_number(1, count)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_bidirectional_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        auto result {v.insert(count, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == static_cast<size_t>(count) * 2);
                        assert(v.spare() == count - insertion_size);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == numbers.back());
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < count; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {count}; i < count + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        assert(result == v.begin() + count);
                        assert(result == v.cbegin() + count);
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to tail/With reallocation/Insertion size less equal to double capacity done." << std::endl;
                    }

                    // insertion size greater than double capacity
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        auto insertion_size {this->generate_a_random_number(2 * count + 1)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_bidirectional_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        auto result {v.insert(count, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == static_cast<size_t>(count) + insertion_size);
                        assert(v.spare() == 0);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == numbers.back());
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < count; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {count}; i < count + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        assert(result == v.begin() + count);
                        assert(result == v.cbegin() + count);
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to tail/With reallocation/Insertion size greater than double capacity done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to tail/With reallocation finished!" << std::endl;
                }

                std::cout << "\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty vector/Insert to tail finished!" << std::endl;
            }

            std::cout << "\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty vector finished!" << std::endl;
        }

        std::cout << "\tChecking test_insert3/Bidirectional iterator for ds::vector finished!" << std::endl;
    }

    // random access iterator
    {
        std::cout << "\tStart checking test_insert_3/Random access iterator for ds::vector!" << std::endl;

        // insert to empty vector
        {
            std::cout << "\t\tStart checking test_insert_3/Random access iteratorInsert to empty vector for ds::vector!" << std::endl;

            // insertion size equal to zero
            {
                vector<int> v {};
                const auto result {v.insert(0, int_random_access_iterator {}, int_random_access_iterator {})};
                assert(v.size() == 0);
                assert(v.empty());
                assert(v.capacity() == 0);
                assert(v.spare() == 0);
                assert(v.data() == nullptr);
                assert(v.begin() == v.end());
                assert(v.cbegin() == v.cend());
                assert(result == v.begin());
                assert(result == v.cbegin());
                std::cout << "\t\t\tChecking test_insert_3/Random access iteratorInsert to empty vector/Insertion size not equal to zero done." << std::endl;
            }

            // insertion size not equal to zero
            {
                vector<int> v {};
                auto insertion_size {this->generate_count()};
                while(insertion_size == 0) {
                    insertion_size = this->generate_count();
                }
                const auto numbers {this->generate_random_sequence(insertion_size)};
                auto d {this->to_random_access_iterator(numbers)};
                const auto result {v.insert(0, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                assert(v.size() == insertion_size);
                assert(not v.empty());
                assert(v.capacity() == insertion_size);
                assert(v.spare() == 0);
                assert(v.data() not_eq nullptr);
                assert(v.begin() + insertion_size == v.end());
                assert(v.cbegin() + insertion_size == v.cend());
                assert(v.front() == numbers.front());
                assert(v.back() == numbers.back());
                auto i {0uz};
                for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                    assert(*it == numbers[i++]);
                }
                i = 0;
                for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                    assert(*it == numbers[i++]);
                }
                i = insertion_size - 1;
                for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                    assert(*it == numbers[i--]);
                }
                i = insertion_size - 1;
                for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                    assert(*it == numbers[i--]);
                }
                for(auto i {0}; i < v.size(); ++i) {
                    assert(v[i] == numbers[i]);
                }
                assert(result == v.begin());
                assert(result == v.cbegin());
                std::cout << "\t\t\tChecking test_insert_3/Random access iteratorInsert to empty vector/Insertion size not equal to zero done." << std::endl;
            }

            std::cout << "\t\tChecking test_insert_3/Random access iteratorInsert to empty vector for ds::vector finished!" << std::endl;
        }

        // insert to non-empty vector
        {
            std::cout << "\t\tStart checking test_insert_3/Random access iteratorInsert to non-empty vector!" << std::endl;

            // insert to head
            {
                std::cout << "\t\t\tStart checking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to head!" << std::endl;

                // without reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to head/Without reallocation!" << std::endl;

                    // insertion size is zero
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto new_size {this->generate_a_random_number(1, count - 1)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        v.cursor = v.first + new_size;
                        const auto result {v.insert(0, int_random_access_iterator {}, int_random_access_iterator {})};
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
                        for(auto i {1}; i < v.size(); ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin());
                        assert(result == v.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to head/Without reallocation/Insertion size is zero done." << std::endl;
                    }

                    // insertion size less equal to tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        auto insertion_size {this->generate_a_random_number(1, count)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto d {this->to_random_access_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        const auto spare {this->generate_count(count)};
                        vector<int> v(count + static_cast<size_t>(insertion_size) + spare, number);
                        v.cursor -= insertion_size + spare;
                        const auto result {v.insert(0, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                        assert(v.spare() == spare);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == numbers.front());
                        assert(v.back() == number);
                        auto number_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        number_i = 0;
                        for(auto i {0}; i < insertion_size; ++i) {
                            assert(v[i] == numbers[number_i++]);
                        }
                        for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin());
                        assert(result == v.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to head/Without reallocation/Insertion size less equal to tail size done." << std::endl;
                    }

                    // insertion size greater than tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_size {this->generate_a_random_number(count + 1)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto d {this->to_random_access_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        const auto spare {this->generate_count(count)};
                        vector<int> v(count + static_cast<size_t>(insertion_size) + spare, number);
                        v.cursor -= static_cast<size_t>(insertion_size) + spare;
                        const auto result {v.insert(0, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                        assert(v.spare() == spare);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == numbers.front());
                        assert(v.back() == number);
                        auto number_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        number_i = 0;
                        for(auto i {0}; i < insertion_size; ++i) {
                            assert(v[i] == numbers[number_i++]);
                        }
                        for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin());
                        assert(result == v.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to head/Without reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to head/Without reallocation finished!" << std::endl;
                }

                // with reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to head/With reallocation!" << std::endl;

                    // insertion size less equal to tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        auto insertion_size {this->generate_a_random_number(1, count)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto d {this->to_random_access_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        const auto result {v.insert(0, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                            assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                            assert(v.spare() == 0);
                        }else {
                            assert(v.capacity() == static_cast<size_t>(count) * 2);
                            assert(v.spare() == count - insertion_size);
                        }
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == numbers.front());
                        assert(v.back() == number);
                        auto number_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        number_i = 0;
                        for(auto i {0}; i < insertion_size; ++i) {
                            assert(v[i] == numbers[number_i++]);
                        }
                        for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin());
                        assert(result == v.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to head/With reallocation/Insertion size less equal to tail size done." << std::endl;
                    }

                    // insertion size greater than tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_size {this->generate_a_random_number(count + 1)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto d {this->to_random_access_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        const auto result {v.insert(0, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                            assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                            assert(v.spare() == 0);
                        }else {
                            assert(v.capacity() == static_cast<size_t>(count) * 2);
                            assert(v.spare() == count - insertion_size);
                        }
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == numbers.front());
                        assert(v.back() == number);
                        auto number_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        number_i = 0;
                        for(auto i {0}; i < insertion_size; ++i) {
                            assert(v[i] == numbers[number_i++]);
                        }
                        for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin());
                        assert(result == v.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to head/With reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    // insertion size less equal to double capacity
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_size {this->generate_a_random_number(1, count)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto d {this->to_random_access_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        auto result {v.insert(0, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == static_cast<size_t>(count) * 2);
                        assert(v.spare() == count - insertion_size);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == numbers.front());
                        assert(v.back() == number);
                        auto number_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        number_i = 0;
                        for(auto i {0}; i < insertion_size; ++i) {
                            assert(v[i] == numbers[number_i++]);
                        }
                        for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin());
                        assert(result == v.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to head/With reallocation/Insertion size less equal to double capacity done." << std::endl;
                    }

                    // insertion size greater than double capacity
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_size {this->generate_a_random_number(2 * count + 1)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto d {this->to_random_access_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        auto result {v.insert(0, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == static_cast<size_t>(count) + insertion_size);
                        assert(v.spare() == 0);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == numbers.front());
                        assert(v.back() == number);
                        auto number_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        number_i = insertion_size - 1;
                        for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                            assert(*it == numbers[number_i--]);
                        }
                        number_i = 0;
                        for(auto i {0}; i < insertion_size; ++i) {
                            assert(v[i] == numbers[number_i++]);
                        }
                        for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin());
                        assert(result == v.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to head/With reallocation/Insertion size greater than double capacity done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to head/With reallocation finished!" << std::endl;
                }

                std::cout << "\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to head finished!" << std::endl;
            }

            // insert to random position
            {
                std::cout << "\t\t\tStart checking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to random position!" << std::endl;

                // without reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to random position/Without reallocation!" << std::endl;

                    // insertion size is zero
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto new_size {this->generate_a_random_number(1, count - 1)};
                        const auto number {this->generate_a_random_number()};
                        const auto insertion_position {this->generate_a_random_number(1, new_size - 1)};
                        vector<int> v(count, number);
                        v.cursor = v.first + new_size;
                        const auto result {v.insert(insertion_position, int_random_access_iterator {}, int_random_access_iterator {})};
                        assert(v.size() == new_size);
                        assert(not v.empty());
                        assert(v.capacity() == count);
                        assert(v.spare() == count - new_size);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + new_size == v.end());
                        assert(v.cbegin() + new_size == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == number);
                        for(auto it {v.begin() + 1}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.cbegin() + 1}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.rbegin()}; it not_eq v.rend() - 1; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crend() - 1; ++it) {
                            assert(*it == number);
                        }
                        for(auto i {1}; i < v.size(); ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin() + insertion_position);
                        assert(result == v.cbegin() + insertion_position);
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to random position/Without reallocation/Insertion size is zero done." << std::endl;
                    }

                    // insertion size less equal to tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_position {this->generate_a_random_number(1, count - 1)};
                        auto insertion_size {this->generate_a_random_number(1, count - insertion_position)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto d {this->to_random_access_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        const auto spare {this->generate_count(count)};
                        vector<int> v(count + static_cast<size_t>(insertion_size) + spare, number);
                        v.cursor -= insertion_size + spare;
                        const auto result {v.insert(insertion_position, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                        assert(v.spare() == spare);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == number);
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        const auto tail_size {count - insertion_position};
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < insertion_position; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin() + insertion_position);
                        assert(result == v.cbegin() + insertion_position);
                        std::cout << "\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to random position/Without reallocation/Insertion size less equal to tail size done." << std::endl;
                    }

                    // insertion size greater than tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_position {this->generate_a_random_number(1, count - 1)};
                        const auto insertion_size {this->generate_a_random_number(count - insertion_position + 1)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto d {this->to_random_access_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        const auto spare {this->generate_count(count)};
                        vector<int> v(count + static_cast<size_t>(insertion_size) + spare, number);
                        v.cursor -= static_cast<size_t>(insertion_size) + spare;
                        const auto result {v.insert(insertion_position, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                        assert(v.spare() == spare);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == number);
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        const auto tail_size {count - insertion_position};
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < insertion_position; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin() + insertion_position);
                        assert(result == v.cbegin() + insertion_position);
                        std::cout << "\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to random position/Without reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to random position/Without reallocation finished!" << std::endl;
                }

                // with reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to random position/With reallocation!" << std::endl;

                    // insertion size less equal to tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_position {this->generate_a_random_number(1, count - 1)};
                        auto insertion_size {this->generate_a_random_number(1, count - insertion_position)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto d {this->to_random_access_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        const auto result {v.insert(insertion_position, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                            assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                            assert(v.spare() == 0);
                        }else {
                            assert(v.capacity() == static_cast<size_t>(count) * 2);
                            assert(v.spare() == count - insertion_size);
                        }
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == number);
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        const auto tail_size {count - insertion_position};
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < insertion_position; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin() + insertion_position);
                        assert(result == v.cbegin() + insertion_position);
                        std::cout << "\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to random position/With reallocation/Insertion size less equal to tail size done." << std::endl;
                    }

                    // insertion size greater than tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_position {this->generate_a_random_number(1, count - 1)};
                        const auto insertion_size {this->generate_a_random_number(count - insertion_position + 1)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto d {this->to_random_access_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        const auto result {v.insert(insertion_position, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                            assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                            assert(v.spare() == 0);
                        }else {
                            assert(v.capacity() == static_cast<size_t>(count) * 2);
                            assert(v.spare() == count - insertion_size);
                        }
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == number);
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        const auto tail_size {count - insertion_position};
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < insertion_position; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin() + insertion_position);
                        assert(result == v.cbegin() + insertion_position);
                        std::cout << "\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to random position/With reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    // insertion size less equal to double capacity
                    {
                        auto count {this->generate_count()};
                        while(count <= 2) {
                            count = this->generate_count();
                        }
                        const auto insertion_position {this->generate_a_random_number(1, count - 2)};
                        auto insertion_size {this->generate_a_random_number(1, count)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto d {this->to_random_access_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        auto result {v.insert(insertion_position, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == static_cast<size_t>(count) * 2);
                        assert(v.spare() == count - insertion_size);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == number);
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        const auto tail_size {count - insertion_position};
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < insertion_position; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin() + insertion_position);
                        assert(result == v.cbegin() + insertion_position);
                        std::cout << "\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to random position/With reallocation/Insertion size less equal to double capacity done." << std::endl;
                    }

                    // insertion size greater than double capacity
                    {
                        auto count {this->generate_count()};
                        while(count <= 2) {
                            count = this->generate_count();
                        }
                        const auto insertion_position {this->generate_a_random_number(1, count - 2)};
                        auto insertion_size {this->generate_a_random_number(2 * count + 1)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto d {this->to_random_access_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        auto result {v.insert(insertion_position, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == static_cast<size_t>(count) + insertion_size);
                        assert(v.spare() == 0);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == number);
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                            assert(*it == number);
                        }
                        const auto tail_size {count - insertion_position};
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < insertion_position; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.begin() + insertion_position);
                        assert(result == v.cbegin() + insertion_position);
                        std::cout << "\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to random position/With reallocation/Insertion size greater than double capacity done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to random position/With reallocation finished!" << std::endl;
                }

                std::cout << "\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to random position finished!" << std::endl;
            }

            // insert to tail
            {
                std::cout << "\t\t\tStart checking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to tail!" << std::endl;

                // without reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to tail/Without reallocation!" << std::endl;

                    // insertion size is zero
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto new_size {this->generate_a_random_number(1, count - 1)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        v.cursor = v.first + new_size;
                        const auto result {v.insert(new_size, int_random_access_iterator {}, int_random_access_iterator {})};
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
                        for(auto i {1}; i < v.size(); ++i) {
                            assert(v[i] == number);
                        }
                        assert(result == v.end());
                        assert(result == v.cend());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to tail/Without reallocation/Insertion size is zero done." << std::endl;
                    }

                    // insertion size less equal to tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        auto insertion_size {this->generate_a_random_number(1, count)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto d {this->to_random_access_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        const auto spare {this->generate_count(count)};
                        vector<int> v(count + static_cast<size_t>(insertion_size) + spare, number);
                        v.cursor -= insertion_size + spare;
                        const auto result {v.insert(count, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                        assert(v.spare() == spare);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == numbers.back());
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < count; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {count}; i < count + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        assert(result == v.begin() + count);
                        assert(result == v.cbegin() + count);
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to tail/Without reallocation/Insertion size less equal to tail size done." << std::endl;
                    }

                    // insertion size greater than tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_size {this->generate_a_random_number(count + 1)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto d {this->to_random_access_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        const auto spare {this->generate_count(count)};
                        vector<int> v(count + static_cast<size_t>(insertion_size) + spare, number);
                        v.cursor -= static_cast<size_t>(insertion_size) + spare;
                        const auto result {v.insert(count, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                        assert(v.spare() == spare);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == numbers.back());
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < count; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {count}; i < count + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        assert(result == v.begin() + count);
                        assert(result == v.cbegin() + count);
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to tail/Without reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to tail/Without reallocation finished!" << std::endl;
                }

                // with reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to tail/With reallocation!" << std::endl;

                    // insertion size less equal to tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        auto insertion_size {this->generate_a_random_number(1, count)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto d {this->to_random_access_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        const auto result {v.insert(count, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                            assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                            assert(v.spare() == 0);
                        }else {
                            assert(v.capacity() == static_cast<size_t>(count) * 2);
                            assert(v.spare() == count - insertion_size);
                        }
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == numbers.back());
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < count; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {count}; i < count + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        assert(result == v.begin() + count);
                        assert(result == v.cbegin() + count);
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to tail/With reallocation/Insertion size less equal to tail size done." << std::endl;
                    }

                    // insertion size greater than tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_size {this->generate_a_random_number(count + 1)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto d {this->to_random_access_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        const auto result {v.insert(count, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                            assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                            assert(v.spare() == 0);
                        }else {
                            assert(v.capacity() == static_cast<size_t>(count) * 2);
                            assert(v.spare() == count - insertion_size);
                        }
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == numbers.back());
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < count; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {count}; i < count + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        assert(result == v.begin() + count);
                        assert(result == v.cbegin() + count);
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to tail/With reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    // insertion size less equal to double capacity
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        auto insertion_size {this->generate_a_random_number(1, count)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto d {this->to_random_access_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        auto result {v.insert(count, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == static_cast<size_t>(count) * 2);
                        assert(v.spare() == count - insertion_size);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == numbers.back());
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < count; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {count}; i < count + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        assert(result == v.begin() + count);
                        assert(result == v.cbegin() + count);
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to tail/With reallocation/Insertion size less equal to double capacity done." << std::endl;
                    }

                    // insertion size greater than double capacity
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        auto insertion_size {this->generate_a_random_number(2 * count + 1)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto d {this->to_random_access_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        vector<int> v(count, number);
                        auto result {v.insert(count, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == static_cast<size_t>(count) + insertion_size);
                        assert(v.spare() == 0);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == number);
                        assert(v.back() == numbers.back());
                        auto numbers_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                            assert(*it == number);
                        }
                        numbers_i = insertion_size - 1;
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                            assert(*it == numbers[numbers_i--]);
                        }
                        for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                            assert(*it == number);
                        }
                        for(auto i {0}; i < count; ++i) {
                            assert(v[i] == number);
                        }
                        numbers_i = 0;
                        for(auto i {count}; i < count + insertion_size; ++i) {
                            assert(v[i] == numbers[numbers_i++]);
                        }
                        assert(result == v.begin() + count);
                        assert(result == v.cbegin() + count);
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to tail/With reallocation/Insertion size greater than double capacity done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to tail/With reallocation finished!" << std::endl;
                }

                std::cout << "\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty vector/Insert to tail finished!" << std::endl;
            }

            std::cout << "\t\tChecking test_insert_3/Random access iteratorInsert to non-empty vector finished!" << std::endl;
        }

        std::cout << "\tChecking test_insert3/Random access iterator for ds::vector finished!" << std::endl;
    }

    // Todo : contiguous iterator (pointer)

    std::cout << "Checking iterator insert(size_type, ForwardIterator, ForwardIterator) for ds::vector finished!" << std::endl;
}
void vector_correctness::test_erase() {
    std::cout << "Start checking iterator erase(size_type, size_type) for ds::vector!" << std::endl;

    // erase from head
    {
        std::cout << "\tStart checking test_erase/Erase from head for ds::vector!" << std::endl;

        // erasion size is zero
        {
            std::cout << "\t\tStart checking test_erase/Erase from head/Erasion size is zero for ds::vector!" << std::endl;

            // empty
            {
                vector<int> v {};
                auto result {v.erase(0, 0)};
                assert(v.size() == 0);
                assert(v.empty());
                assert(v.capacity() == 0);
                assert(v.spare() == 0);
                assert(v.begin() == v.end());
                assert(v.cbegin() == v.cend());
                assert(v.rbegin() == v.rend());
                assert(v.crbegin() == v.crend());
                assert(v.crbegin() == v.crend());
                assert(v.data() == nullptr);
                assert(result == v.begin());
                assert(result == v.cbegin());
                assert(result == v.end());
                assert(result == v.cend());
                std::cout << "\t\t\tChecking test_erase/Erase from head/Erasion size is zero/Empty done." << std::endl;
            }

            // non-empty
            {
                auto count {this->generate_count()};
                while(count <= 1) {
                    count = this->generate_count();
                }
                const auto number {this->generate_a_random_number()};
                vector<int> v(count, number);
                auto result {v.erase(0, 0)};
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
                assert(result == v.begin());
                assert(result == v.cbegin());
                std::cout << "\t\t\tChecking test_erase/Erase from head/Erasion size is zero/Non-empty done." << std::endl;
            }

            std::cout << "\t\tChecking test_erase/Erase from head/Erasion size is zero for ds::vector finished!" << std::endl;
        }

        // erasion size is random
        {
            auto count {this->generate_count()};
            while(count <= 1) {
                count = this->generate_count();
            }
            const auto number {this->generate_a_random_number()};
            vector<int> v(count, number);
            const auto erasion_size {this->generate_a_random_number(1, count - 1)};
            auto result {v.erase(0, erasion_size)};
            assert(v.size() == count - erasion_size);
            assert(not v.empty());
            assert(v.capacity() == count);
            assert(v.spare() == erasion_size);
            assert(v.data() not_eq nullptr);
            assert(v.begin() + (count - erasion_size) == v.end());
            assert(v.cbegin() + (count - erasion_size) == v.cend());
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
            for(auto i {0}; i < count - erasion_size; ++i) {
                assert(v[i] == number);
            }
            assert(result == v.begin());
            assert(result == v.cbegin());
            std::cout << "\t\tChecking test_erase/Erase from head/Erasion size is random done." << std::endl;
        }

        // erase all
        {
            auto count {this->generate_count()};
            while(count <= 1) {
                count = this->generate_count();
            }
            const auto number {this->generate_a_random_number()};
            vector<int> v(count, number);
            auto result {v.erase(0, count)};
            assert(v.size() == 0);
            assert(v.empty());
            assert(v.capacity() == count);
            assert(v.spare() == count);
            assert(v.data() not_eq nullptr);
            assert(v.begin() == v.end());
            assert(v.cbegin() == v.cend());
            assert(result == v.begin());
            assert(result == v.cbegin());
            assert(result == v.end());
            assert(result == v.cend());
            std::cout << "\t\tChecking test_erase/Erase from head/Erasion all done." << std::endl;
        }

        std::cout << "\tChecking test_erase/Erase from head for ds::vector finished!" << std::endl;
    }

    // erase from any position
    {
        std::cout << "\tStart checking test_erase/Erase from any position for ds::vector!" << std::endl;

        // erasion size is zero
        {
            auto count {this->generate_count()};
            while(count <= 1) {
                count = this->generate_count();
            }
            const auto number {this->generate_a_random_number()};
            vector<int> v(count, number);
            const auto erasion_position {this->generate_a_random_number(1, count - 1)};
            auto result {v.erase(erasion_position, 0)};
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
            assert(result == v.begin() + erasion_position);
            assert(result == v.cbegin() + erasion_position);
            std::cout << "\t\t\tChecking test_erase/Erase from head/Erase from any position/Erasion size is zero done." << std::endl;
        }

        // erasion size is not zero
        {
            auto count {this->generate_count()};
            while(count <= 1) {
                count = this->generate_count();
            }
            const auto number {this->generate_a_random_number()};
            vector<int> v(count, number);
            const auto erasion_position {this->generate_a_random_number(1, count - 1)};
            const auto erasion_size {this->generate_a_random_number(1, count - erasion_position)};
            auto result {v.erase(erasion_position, erasion_size)};
            assert(v.size() == count - erasion_size);
            assert(not v.empty());
            assert(v.capacity() == count);
            assert(v.spare() == erasion_size);
            assert(v.data() not_eq nullptr);
            assert(v.begin() + (count - erasion_size) == v.end());
            assert(v.cbegin() + (count - erasion_size) == v.cend());
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
            for(auto i {0}; i < count - erasion_size; ++i) {
                assert(v[i] == number);
            }
            assert(result == v.begin() + erasion_position);
            assert(result == v.cbegin() + erasion_position);
            std::cout << "\t\t\tChecking test_erase/Erase from head/Erase from any position/Erasion size is not zero done." << std::endl;
        }

        // erase to tail
        {
            auto count {this->generate_count()};
            while(count <= 1) {
                count = this->generate_count();
            }
            const auto number {this->generate_a_random_number()};
            vector<int> v(count, number);
            const auto erasion_position {this->generate_a_random_number(1, count - 1)};
            auto result {v.erase(erasion_position, count - erasion_position)};
            assert(v.size() == erasion_position);
            assert(not v.empty());
            assert(v.capacity() == count);
            assert(v.spare() == count - erasion_position);
            assert(v.data() not_eq nullptr);
            assert(v.begin() + erasion_position == v.end());
            assert(v.cbegin() + erasion_position == v.cend());
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
            for(auto i {0}; i < erasion_position; ++i) {
                assert(v[i] == number);
            }
            assert(result == v.begin() + erasion_position);
            assert(result == v.cbegin() + erasion_position);
            std::cout << "\t\t\tChecking test_erase/Erase from head/Erase from any position/Erase to tail done." << std::endl;
        }

        std::cout << "\tChecking test_erase/Erase from any position for ds::vector finished!" << std::endl;
    }

    std::cout << "Checking iterator erase(size_type, size_type) for ds::vector finished!" << std::endl;
}
void vector_correctness::test_allocator() {
    std::cout << "Start checking allocator for ds::vector!" << std::endl;

    vector<int> v {1, 2, 3};
    auto allocator {v.allocator()};
    static_assert(allocator == typename vector<int>::allocator_type {});
    static_assert(allocator == typename vector<char>::allocator_type {});

    std::cout << "Checking allocator for ds::vector finished!" << std::endl;
}
void vector_correctness::test_non_trivial() {
    goto A;
    std::cout << "Start checking non-trivial type for ds::vector!" << std::endl;

    // default constructor
    {
        vector<std::string> v {};
        assert(v.size() == 0);
        assert(v.empty());
        assert(v.capacity() == 0);
        assert(v.spare() == 0);
        assert(v.begin() == v.end());
        assert(v.cbegin() == v.cend());
        assert(v.rbegin() == v.rend());
        assert(v.crbegin() == v.crend());
        assert(v.crbegin() == v.crend());
        assert(v.data() == nullptr);
        std::cout << "\tChecking test_non_trivial/Default constructor done." << std::endl;
    }

    // vector(size_type)
    {
        std::cout << "\tStart checking test_non_trivial/vector(size_type)!" << std::endl;

        // empty
        {
            vector<std::string> v {};
            assert(v.size() == 0);
            assert(v.empty());
            assert(v.capacity() == 0);
            assert(v.spare() == 0);
            assert(v.begin() == v.end());
            assert(v.cbegin() == v.cend());
            assert(v.rbegin() == v.rend());
            assert(v.crbegin() == v.crend());
            assert(v.crbegin() == v.crend());
            assert(v.data() == nullptr);
            std::cout << "\t\tChecking test_non_trivial/vector(size_type)/Empty done." << std::endl;
        }

        // not empty
        {
            const auto count {this->generate_count()};
            std::string s {};
            for(auto i {0}; i < this->generate_a_random_number(1, 100); ++i) {
                s += "hello";
            }
            vector<std::string> v(count, s);
            assert(v.size() == count);
            assert(not v.empty());
            assert(v.capacity() == count);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() + count == v.end());
            assert(v.cbegin() + count == v.cend());
            assert(v.front() == s);
            assert(v.back() == s);
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == s);
            }
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == s);
            }
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == s);
            }
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == s);
            }
            for(auto i {0}; i < count; ++i) {
                assert(v[i] == s);
            }
            std::cout << "\t\tChecking test_non_trivial/vector(size_type)/Not empty done." << std::endl;
        }

        std::cout << "\tChecking test_non_trivial/vector(size_type) finished!" << std::endl;
    }

    // vector(size_type, const_reference)
    {
        std::cout << "\tStart checking test_non_trivial/vector(size_type, const_reference)!" << std::endl;

        // empty
        {
            vector<std::string> v {};
            assert(v.size() == 0);
            assert(v.empty());
            assert(v.capacity() == 0);
            assert(v.spare() == 0);
            assert(v.begin() == v.end());
            assert(v.cbegin() == v.cend());
            assert(v.rbegin() == v.rend());
            assert(v.crbegin() == v.crend());
            assert(v.crbegin() == v.crend());
            assert(v.data() == nullptr);
            std::cout << "\t\tChecking test_non_trivial/vector(size_type, const_reference)/Empty done." << std::endl;
        }

        // not empty
        {
            auto count {this->generate_count()};
            while(count == 0) {
                count = this->generate_count();
            }
            std::string s {};
            for(auto i {0}; i < this->generate_a_random_number(1, 100); ++i) {
                s += "hello";
            }
            vector<std::string> v(count, s);
            assert(v.size() == count);
            assert(not v.empty());
            assert(v.capacity() == count);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() + count == v.end());
            assert(v.cbegin() + count == v.cend());
            assert(v.front() == s);
            assert(v.back() == s);
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == s);
            }
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == s);
            }
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == s);
            }
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == s);
            }
            for(auto i {0}; i < count; ++i) {
                assert(v[i] == s);
            }
            std::cout << "\t\tChecking test_non_trivial/vector(size_type, const_reference)/Empty done." << std::endl;
        }

        std::cout << "\tChecking test_non_trivial/vector(size_type, const_reference) finished!" << std::endl;
    }

    // vector(InputIterator, InputIterator)
    {
        std::cout << "\tStart checking test_non_trivial/vector(InputIterator, InputIterator)!" << std::endl;

        // empty
        {
            vector<std::string> v(std_string_input_iterator {}, std_string_input_iterator {});
            assert(v.size() == 0);
            assert(v.empty());
            assert(v.capacity() == 0);
            assert(v.spare() == 0);
            assert(v.begin() == v.end());
            assert(v.cbegin() == v.cend());
            assert(v.rbegin() == v.rend());
            assert(v.crbegin() == v.crend());
            assert(v.crbegin() == v.crend());
            assert(v.data() == nullptr);
            std::cout << "\t\tChecking test_non_trivial/vector(InputIterator, InputIterator)/Empty done." << std::endl;
        }

        // not empty
        {
            auto count {this->generate_count()};
            while(count == 0) {
                count = this->generate_count();
            }
            std::string s {};
            for(auto i {0}; i < this->generate_a_random_number(1, 100); ++i) {
                s += "hello";
            }
            auto stream {this->to_input_iterator(std::vector(count, s))};
            vector<std::string> v(std_string_input_iterator {stream}, {});
            assert(v.size() == count);
            assert(not v.empty());
            assert(v.capacity() == count);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() + count == v.end());
            assert(v.cbegin() + count == v.cend());
            assert(v.front() == s);
            assert(v.back() == s);
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == s);
            }
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == s);
            }
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == s);
            }
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == s);
            }
            for(auto i {0}; i < count; ++i) {
                assert(v[i] == s);
            }
            std::cout << "\t\tChecking test_non_trivial/vector(InputIterator, InputIterator)/Not Empty done." << std::endl;
        }

        std::cout << "\tChecking test_non_trivial/vector(InputIterator, InputIterator)!" << std::endl;
    }

    // vector(ForwardIterator, ForwardIterator)
    {
        std::cout << "\tStart checking test_non_trivial/vector(ForwardIterator, ForwardIterator)!" << std::endl;

        // empty
        {
            vector<std::string> v(std_string_random_access_iterator {}, std_string_random_access_iterator {});
            assert(v.size() == 0);
            assert(v.empty());
            assert(v.capacity() == 0);
            assert(v.spare() == 0);
            assert(v.begin() == v.end());
            assert(v.cbegin() == v.cend());
            assert(v.rbegin() == v.rend());
            assert(v.crbegin() == v.crend());
            assert(v.crbegin() == v.crend());
            assert(v.data() == nullptr);
            std::cout << "\t\tChecking test_non_trivial/vector(ForwardIterator, ForwardIterator)/Empty done." << std::endl;
        }

        // not empty
        {
            auto count {this->generate_count()};
            while(count == 0) {
                count = this->generate_count();
            }
            std::string s {};
            for(auto i {0}; i < this->generate_a_random_number(1, 100); ++i) {
                s += "hello";
            }
            auto d {this->to_random_access_iterator(std::vector(count, s))};
            vector<std::string> v(std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()});
            assert(v.size() == count);
            assert(not v.empty());
            assert(v.capacity() == count);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() + count == v.end());
            assert(v.cbegin() + count == v.cend());
            assert(v.front() == s);
            assert(v.back() == s);
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == s);
            }
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == s);
            }
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == s);
            }
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == s);
            }
            for(auto i {0}; i < count; ++i) {
                assert(v[i] == s);
            }
            std::cout << "\t\tChecking test_non_trivial/vector(ForwardIterator, ForwardIterator)/Not Empty done." << std::endl;
        }

        std::cout << "\tChecking test_non_trivial/vector(ForwardIterator, ForwardIterator)!" << std::endl;
    }

    // reserve
    {
        std::cout << "\tStart checking test_non_trivial/Reserve for ds::vector!" << std::endl;

        // empty
        {
            vector<std::string> v {};
            v.reserve(0);
            assert(v.size() == 0);
            assert(v.empty());
            assert(v.capacity() == 0);
            assert(v.spare() == 0);
            assert(v.begin() == v.end());
            assert(v.cbegin() == v.cend());
            assert(v.rbegin() == v.rend());
            assert(v.crbegin() == v.crend());
            assert(v.crbegin() == v.crend());
            assert(v.data() == nullptr);

            auto count {this->generate_count()};
            while(count == 0) {
                count = this->generate_count();
            }
            v.reserve(count);
            assert(v.size() == 0);
            assert(v.empty());
            assert(v.capacity() == count);
            assert(v.spare() == count);
            assert(v.begin() == v.end());
            assert(v.cbegin() == v.cend());
            assert(v.rbegin() == v.rend());
            assert(v.crbegin() == v.crend());
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
            assert(v.crbegin() == v.crend());
            assert(v.data() not_eq nullptr);

            std::cout << "\t\tChecking test_non_trivial/Reserve/Empty done." << std::endl;
        }

        // not empty
        {
            std::cout << "\t\tStart checking test_non_trivial/Reserve/Not empty for ds::vector!" << std::endl;

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
                std::string s {};
                for(auto i {0}; i < this->generate_a_random_number(1, 100); ++i) {
                    s += "hello";
                }
                vector<std::string> v(initialization_size, s);
                v.reserve(reserved_size);
                assert(v.size() == initialization_size);
                assert(not v.empty());
                assert(v.capacity() == reserved_size);
                assert(v.spare() == reserved_size - initialization_size);
                assert(v.data() not_eq nullptr);
                assert(v.begin() + initialization_size == v.end());
                assert(v.cbegin() + initialization_size == v.cend());
                assert(v.front() == s);
                assert(v.back() == s);
                for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                    assert(*it == s);
                }
                for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                    assert(*it == s);
                }
                for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                    assert(*it == s);
                }
                for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                    assert(*it == s);
                }
                for(auto i {0}; i < v.size(); ++i) {
                    assert(v[i] == s);
                }
                std::cout << "\t\t\tChecking test_non_trivial/Reserve/Not empty/Greater than capacity done." << std::endl;
            }

            // less equal to capacity
            {
                auto capacity {this->generate_count()};
                while(capacity <= 1) {
                    capacity = this->generate_count();
                }
                const auto size {this->generate_a_random_number(1, capacity - 1)};
                std::string s {};
                for(auto i {0}; i < this->generate_a_random_number(1, 100); ++i) {
                    s += "hello";
                }
                vector<std::string> v(capacity, s);
                destroy(v.first + size, v.cursor);
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
                assert(v.front() == s);
                assert(v.back() == s);
                for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                    assert(*it == s);
                }
                for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                    assert(*it == s);
                }
                for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                    assert(*it == s);
                }
                for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                    assert(*it == s);
                }
                for(auto i {0}; i < v.size(); ++i) {
                    assert(v[i] == s);
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
                assert(v.front() == s);
                assert(v.back() == s);
                for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                    assert(*it == s);
                }
                for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                    assert(*it == s);
                }
                for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                    assert(*it == s);
                }
                for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                    assert(*it == s);
                }
                for(auto i {0}; i < v.size(); ++i) {
                    assert(v[i] == s);
                }
                std::cout << "\t\t\tChecking test_non_trivial/Reserve/Not empty/Less equal to capacity done." << std::endl;
            }

            std::cout << "\t\tChecking test_non_trivial/Reserve/Not empty for ds::vector finished!" << std::endl;
        }

        std::cout << "\tChecking test_non_trivial/Reserve for ds::vector finished!" << std::endl;
    }

    // shrink to fit
    {
        std::cout << "\tStart checking test_non_trivial/Shrink to fit for ds::vector!" << std::endl;

        // empty
        {
            vector<std::string> v {};
            v.shrink_to_fit();
            assert(v.size() == 0);
            assert(v.empty());
            assert(v.capacity() == 0);
            assert(v.spare() == 0);
            assert(v.begin() == v.end());
            assert(v.cbegin() == v.cend());
            assert(v.rbegin() == v.rend());
            assert(v.crbegin() == v.crend());
            assert(v.crbegin() == v.crend());
            assert(v.data() == nullptr);

            v = vector<std::string>(this->generate_count(), "hello");
            destroy(v.first, v.cursor);
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
            assert(v.crbegin() == v.crend());
            assert(v.data() == nullptr);

            std::cout << "\t\tChecking test_non_trivial/Shrink to fit/Empty vector done." << std::endl;
        }

        // non-empty
        {
            auto count {this->generate_count()};
            while(count <= 1) {
                count = this->generate_count();
            }
            const std::string s {"hel lo"};
            vector<std::string> v(count, s);
            v.shrink_to_fit();
            assert(v.size() == count);
            assert(not v.empty());
            assert(v.capacity() == count);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() + count == v.end());
            assert(v.cbegin() + count == v.cend());
            assert(v.front() == s);
            assert(v.back() == s);
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == s);
            }
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == s);
            }
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == s);
            }
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == s);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == s);
            }

            const auto real_size {count / 2};
            destroy(v.first + real_size, v.cursor);
            v.cursor = v.first + real_size;
            v.shrink_to_fit();
            assert(v.size() == real_size);
            assert(not v.empty());
            assert(v.capacity() == real_size);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() + real_size == v.end());
            assert(v.cbegin() + real_size == v.cend());
            assert(v.front() == s);
            assert(v.back() == s);
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == s);
            }
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == s);
            }
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == s);
            }
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == s);
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == s);
            }

            std::cout << "\tChecking test_non_trivial/Shrink to fit/Non-empty vector done." << std::endl;
        }

        std::cout << "\tChecking test_non_trivial/Shrink to fit for ds::vector finished!" << std::endl;
    }

    // resize
    {
        std::cout << "\tStart checking void resize(size_type) for ds::vector!" << std::endl;

        // empty to empty
        {
            vector<std::string> v {};
            v.resize(0);
            assert(v.size() == 0);
            assert(v.empty());
            assert(v.capacity() == 0);
            assert(v.spare() == 0);
            assert(v.begin() == v.end());
            assert(v.cbegin() == v.cend());
            assert(v.rbegin() == v.rend());
            assert(v.crbegin() == v.crend());
            assert(v.crbegin() == v.crend());
            assert(v.data() == nullptr);
            std::cout << "\t\tChecking test_non_trivial/Resize/Empty to empty done." << std::endl;
        }

        // empty to non-empty
        {
            vector<std::string> v {};
            const auto count {this->generate_count()};
            v.resize(count);
            assert(v.size() == count);
            assert(not v.empty());
            assert(v.capacity() == count);
            assert(v.spare() == 0);
            assert(v.data() not_eq nullptr);
            assert(v.begin() + count == v.end());
            assert(v.cbegin() + count == v.cend());
            assert(v.front() == "");
            assert(v.back() == "");
            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                assert(*it == "");
            }
            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                assert(*it == "");
            }
            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                assert(*it == "");
            }
            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                assert(*it == "");
            }
            for(auto i {0}; i < v.size(); ++i) {
                assert(v[i] == "");
            }
            std::cout << "\t\tChecking test_non_trivial/Resize/Empty to non-empty done." << std::endl;
        }

        // non-empty to empty
        {
            const auto count {this->generate_count()};
            vector<std::string> v(count, "hello");
            v.resize(0);
            assert(v.size() == 0);
            assert(v.empty());
            assert(v.capacity() == 0);
            assert(v.spare() == 0);
            assert(v.begin() == v.end());
            assert(v.cbegin() == v.cend());
            assert(v.rbegin() == v.rend());
            assert(v.crbegin() == v.crend());
            assert(v.crbegin() == v.crend());
            assert(v.data() == nullptr);
            std::cout << "\t\tChecking test_non_trivial/Resize/Non-empty to empty done." << std::endl;
        }

        // non-empty to non-empty
        {
            std::cout << "\t\tStart checking test_non_trivial/Resize/Non-empty to non-empty for ds::vector!" << std::endl;

            // less than size
            {
                const auto count {this->generate_count()};
                const auto new_size {this->generate_count(count - 1)};
                const std::string s {"hello"};
                vector<std::string> v(count, s);
                v.resize(new_size);
                assert(v.size() == new_size);
                assert(not v.empty());
                assert(v.capacity() == new_size);
                assert(v.spare() == 0);
                assert(v.data() not_eq nullptr);
                assert(v.begin() + new_size == v.end());
                assert(v.cbegin() + new_size == v.cend());
                assert(v.front() == s);
                assert(v.back() == s);
                for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                    assert(*it == s);
                }
                for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                    assert(*it == s);
                }
                for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                    assert(*it == s);
                }
                for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                    assert(*it == s);
                }
                for(auto i {0}; i < v.size(); ++i) {
                    assert(v[i] == s);
                }
                std::cout << "\t\t\tChecking test_non_trivial/Resize/Non-empty to non-empty/Less than size done." << std::endl;
            }

            // equal to size
            {
                const auto count {this->generate_count()};
                const auto number {this->generate_a_random_number()};
                const std::string s {"hello"};
                vector<std::string> v(count, s);
                v.resize(count);
                assert(v.size() == count);
                assert(not v.empty());
                assert(v.capacity() == count);
                assert(v.spare() == 0);
                assert(v.data() not_eq nullptr);
                assert(v.begin() + count == v.end());
                assert(v.cbegin() + count == v.cend());
                assert(v.front() == s);
                assert(v.back() == s);
                for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                    assert(*it == s);
                }
                for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                    assert(*it == s);
                }
                for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                    assert(*it == s);
                }
                for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                    assert(*it == s);
                }
                for(auto i {0}; i < v.size(); ++i) {
                    assert(v[i] == s);
                }
                std::cout << "\t\t\tChecking test_non_trivial/Resize/Non-empty to non-empty/Equal to size done." << std::endl;
            }

            // greater than size
            {
                auto count {this->generate_count(std::numeric_limits<int>::max() - 1)};
                const auto new_size {this->generate_a_random_number(count + 1)};
                const auto number {this->generate_a_random_number()};
                const std::string s {"hello"};
                vector<std::string> v(count, s);
                v.resize(new_size);
                assert(v.size() == new_size);
                assert(not v.empty());
                assert(v.capacity() == new_size);
                assert(v.spare() == 0);
                assert(v.data() not_eq nullptr);
                assert(v.begin() + new_size == v.end());
                assert(v.cbegin() + new_size == v.cend());
                assert(v.front() == s);
                assert(v.back() == "");
                const auto offset {new_size - count};
                for(auto it {v.begin()}; it not_eq v.end() - offset; ++it) {
                    assert(*it == s);
                }
                for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                    assert(*it == "");
                }
                for(auto it {v.cbegin()}; it not_eq v.cend() - offset; ++it) {
                    assert(*it == s);
                }
                for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                    assert(*it == "");
                }
                for(auto it {v.rbegin()}; it not_eq v.rend() - count; ++it) {
                    assert(*it == "");
                }
                for(auto it {v.rbegin() + offset}; it not_eq v.rend(); ++it) {
                    assert(*it == s);
                }
                for(auto it {v.crbegin()}; it not_eq v.crend() - count; ++it) {
                    assert(*it == "");
                }
                for(auto it {v.rbegin() + offset}; it not_eq v.rend(); ++it) {
                    assert(*it == s);
                }
                for(auto i {0}; i < v.size() - offset; ++i) {
                    assert(v[i] == s);
                }
                for(auto i {count}; i < v.size(); ++i) {
                    assert(v[i] == "");
                }
                std::cout << "\t\t\tChecking test_non_trivial/Resize/Non-empty to non-empty/Greater than size done." << std::endl;
            }

            std::cout << "\t\tChecking test_resize_1/Non-empty to non-empty for ds::vector finished!" << std::endl;
        }

        std::cout << "\tChecking void resize(size_type) for ds::vector finished!" << std::endl;
    }

    // iterator insert(size_type, const_reference, size_type)
    {
        std::cout << "\tStart checking test_non_trivial/iterator insert(size_type, const_reference, size_type) for ds::vector!" << std::endl;

        {
            // insert to empty vector
            {
                std::cout << "\t\tStart checking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to empty vector for ds::vector!" << std::endl;

                // insertion size equal to zero
                {
                    vector<std::string> v {};
                    const auto result {v.insert(0, "hello", 0)};
                    assert(v.size() == 0);
                    assert(v.empty());
                    assert(v.capacity() == 0);
                    assert(v.spare() == 0);
                    assert(v.data() == nullptr);
                    assert(v.begin() == v.end());
                    assert(v.cbegin() == v.cend());
                    assert(result == v.begin());
                    assert(result == v.cbegin());
                    std::cout << "\t\t\tChecking test_insert_1/Insert to empty vector/Insertion size not equal to zero done." << std::endl;
                }

                // insertion size not equal to zero
                {
                    vector<std::string> v {};
                    auto insertion_size {this->generate_count()};
                    while(insertion_size == 0) {
                        insertion_size = this->generate_count();
                    }
                    const std::string s {"insertion"};
                    const auto result {v.insert(0, s, insertion_size)};
                    assert(v.size() == insertion_size);
                    assert(not v.empty());
                    assert(v.capacity() == insertion_size);
                    assert(v.spare() == 0);
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + insertion_size == v.end());
                    assert(v.cbegin() + insertion_size == v.cend());
                    assert(v.front() == s);
                    assert(v.back() == s);
                    for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                        assert(*it == s);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                        assert(*it == s);
                    }
                    for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                        assert(*it == s);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                        assert(*it == s);
                    }
                    for(auto i {0}; i < v.size(); ++i) {
                        assert(v[i] == s);
                    }
                    assert(result == v.begin());
                    assert(result == v.cbegin());
                    std::cout << "\t\t\tChecking test_non_trivial/test_insert_1/Insert to empty vector/Insertion size not equal to zero done." << std::endl;
                }

                std::cout << "\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to empty vector for ds::vector finished!" << std::endl;
            }

            // insert to non-empty vector
            {
                std::cout << "\t\tStart checking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector!" << std::endl;

                // insert to head
                {
                    std::cout << "\t\t\tStart checking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to head!" << std::endl;

                    // without reallocation
                    {
                        std::cout << "\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, const_reference, size_type)/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to head/Without reallocation!" << std::endl;

                        // insertion size is zero
                        {
                            auto count {this->generate_count()};
                            while(count <= 1) {
                                count = this->generate_count();
                            }
                            const auto new_size {this->generate_a_random_number(1, count - 1)};
                            const std::string s {"init"};
                            vector<std::string> v(count, s);
                            destroy(v.first + new_size, v.cursor);
                            v.cursor = v.first + new_size;
                            const auto result {v.insert(0, "hello", 0)};
                            assert(v.size() == new_size);
                            assert(not v.empty());
                            assert(v.capacity() == count);
                            assert(v.spare() == count - new_size);
                            assert(v.data() not_eq nullptr);
                            assert(v.begin() + new_size == v.end());
                            assert(v.cbegin() + new_size == v.cend());
                            assert(v.front() == s);
                            assert(v.back() == s);
                            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto i {1}; i < v.size(); ++i) {
                                assert(v[i] == s);
                            }
                            assert(result == v.begin());
                            assert(result == v.cbegin());
                            std::cout << "\t\t\t\t\tChecking test_insert_1/Insert to non-empty vector/Insert to head/Without reallocation/Insertion size is zero done." << std::endl;
                        }

                        // insertion size less equal to tail size
                        {
                            auto count {this->generate_count()};
                            while(count <= 1) {
                                count = this->generate_count();
                            }
                            const auto insertion_size {this->generate_a_random_number(1, count)};
                            const auto s {"init"};
                            const auto spare {this->generate_count(count)};
                            vector<std::string> v(count + static_cast<size_t>(insertion_size) + spare, s);
                            destroy(v.cursor - (insertion_size + spare), v.cursor);
                            v.cursor -= insertion_size + spare;
                            auto s2 {"insert"};
                            const auto result {v.insert(0, s2, insertion_size)};
                            assert(v.size() == count + static_cast<size_t>(insertion_size));
                            assert(not v.empty());
                            assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                            assert(v.spare() == spare);
                            assert(v.data() not_eq nullptr);
                            assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                            assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                            assert(v.front() == s2);
                            assert(v.back() == s);
                            for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                                assert(*it == s2);
                            }
                            for(auto i {0}; i < insertion_size; ++i) {
                                assert(v[i] == s2);
                            }
                            for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                                assert(v[i] == s);
                            }
                            assert(result == v.begin());
                            assert(result == v.cbegin());
                            std::cout << "\t\t\t\t\tChecking test_insert_1/Insert to non-empty vector/Insert to head/Without reallocation/Insertion size less equal to tail size done." << std::endl;
                        }

                        // insertion size greater than tail size
                        {
                            auto count {this->generate_count()};
                            while(count <= 1) {
                                count = this->generate_count();
                            }
                            const auto insertion_size {this->generate_a_random_number(count + 1)};
                            const std::string s {"init"};
                            const auto spare {this->generate_count(count)};
                            vector<std::string> v(count + static_cast<size_t>(insertion_size) + spare, s);
                            destroy(v.cursor - (static_cast<size_t>(insertion_size) + spare), v.cursor);
                            v.cursor -= static_cast<size_t>(insertion_size) + spare;
                            const std::string s2 {"insert"};
                            const auto result {v.insert(0, s2, insertion_size)};
                            assert(v.size() == count + static_cast<size_t>(insertion_size));
                            assert(not v.empty());
                            assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                            assert(v.spare() == spare);
                            assert(v.data() not_eq nullptr);
                            assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                            assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                            assert(v.front() == s2);
                            assert(v.back() == s);
                            for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                                assert(*it == s2);
                            }
                            for(auto i {0}; i < insertion_size; ++i) {
                                assert(v[i] == s2);
                            }
                            for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                                assert(v[i] == s);
                            }
                            assert(result == v.begin());
                            assert(result == v.cbegin());
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to head/Without reallocation/Insertion size greater than tail size done." << std::endl;
                        }

                        // the value is from self
                        A:{
                            auto count {this->generate_count()};
                            while(count <= 1) {
                                count = this->generate_count();
                            }
                            auto insertion_size {this->generate_count()};
                            while(insertion_size == 0) {
                                insertion_size = this->generate_count();
                            }
                            const std::string s {"init"};
                            vector<std::string> v(count + static_cast<size_t>(insertion_size), s);
                            destroy(v.cursor - insertion_size, v.cursor);
                            v.cursor -= insertion_size;
                            const std::string s2 {"insert"};
                            v[0] = s2;
                            auto result {v.insert(0, v[0], insertion_size)};
                            assert(v.size() == count + static_cast<size_t>(insertion_size));
                            assert(not v.empty());
                            assert(v.capacity() == static_cast<size_t>(count) + insertion_size);
                            assert(v.spare() == 0);
                            assert(v.data() not_eq nullptr);
                            assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                            assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                            assert(v.front() == s2);
                            assert(v.back() == s);
                            for(auto it {v.begin()}; it not_eq v.begin() + (insertion_size + 1); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.begin() + (insertion_size + 1)}; it not_eq v.end(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin()}; it not_eq v.cbegin() + (insertion_size + 1); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.cbegin() + (insertion_size + 1)}; it not_eq v.cend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.rbegin()}; it not_eq v.rbegin() + (count - 1); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.rbegin() + (count - 1)}; it not_eq v.rend(); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.crbegin()}; it not_eq v.crbegin() + (count - 1); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin() + (count - 1)}; it not_eq v.crend(); ++it) {
                                assert(*it == s2);
                            }
                            for(auto i {0}; i < insertion_size + 1; ++i) {
                                assert(v[i] == s2);
                            }
                            for(auto i {insertion_size + 1}; i < count + insertion_size; ++i) {
                                assert(v[i] == s);
                            }
                            assert(result == v.begin());
                            assert(result == v.cbegin());
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to head/Without reallocation/The value is from self done." << std::endl;
                        }

                        std::cout << "\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to head/Without reallocation finished!" << std::endl;
                    }

                    // with reallocation
                    {
                        std::cout << "\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to head/With reallocation!" << std::endl;

                        // insertion size less equal to tail size
                        {
                            auto count {this->generate_count()};
                            while(count <= 1) {
                                count = this->generate_count();
                            }
                            auto insertion_size {this->generate_a_random_number(1, count)};
                            const std::string s {"init"};
                            vector<std::string> v(count, s);
                            const std::string s2 {"insert"};
                            const auto result {v.insert(0, s2, insertion_size)};
                            assert(v.size() == count + static_cast<size_t>(insertion_size));
                            assert(not v.empty());
                            if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                                assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                                assert(v.spare() == 0);
                            }else {
                                assert(v.capacity() == static_cast<size_t>(count) * 2);
                                assert(v.spare() == count - insertion_size);
                            }
                            assert(v.data() not_eq nullptr);
                            assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                            assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                            assert(v.front() == s2);
                            assert(v.back() == s);
                            for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                                assert(*it == s2);
                            }
                            for(auto i {0}; i < insertion_size; ++i) {
                                assert(v[i] == s2);
                            }
                            for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                                assert(v[i] == s);
                            }
                            assert(result == v.begin());
                            assert(result == v.cbegin());
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to head/With reallocation/Insertion size less equal to tail size done." << std::endl;
                        }

                        // insertion size greater than tail size
                        {
                            auto count {this->generate_count()};
                            while(count <= 1) {
                                count = this->generate_count();
                            }
                            const auto insertion_size {this->generate_a_random_number(count + 1)};
                            const std::string s {"init"};
                            vector<std::string> v(count, s);
                            const std::string s2 {"insert"};
                            const auto result {v.insert(0, s2, insertion_size)};
                            assert(v.size() == count + static_cast<size_t>(insertion_size));
                            assert(not v.empty());
                            if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                                assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                                assert(v.spare() == 0);
                            }else {
                                assert(v.capacity() == static_cast<size_t>(count) * 2);
                                assert(v.spare() == count - insertion_size);
                            }
                            assert(v.data() not_eq nullptr);
                            assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                            assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                            assert(v.front() == s2);
                            assert(v.back() == s);
                            for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                                assert(*it == s2);
                            }
                            for(auto i {0}; i < insertion_size; ++i) {
                                assert(v[i] == s2);
                            }
                            for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                                assert(v[i] == s);
                            }
                            assert(result == v.begin());
                            assert(result == v.cbegin());
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to head/With reallocation/Insertion size greater than tail size done." << std::endl;
                        }

                        // insertion size less equal to double capacity
                        {
                            auto count {this->generate_count()};
                            while(count <= 1) {
                                count = this->generate_count();
                            }
                            auto insertion_size {this->generate_a_random_number(1, count)};
                            const std::string s {"init"};
                            vector<std::string> v(count, s);
                            const std::string s2 {"insert"};
                            auto result {v.insert(0, s2, insertion_size)};
                            assert(v.size() == count + static_cast<size_t>(insertion_size));
                            assert(not v.empty());
                            assert(v.capacity() == static_cast<size_t>(count) * 2);
                            assert(v.spare() == count - insertion_size);
                            assert(v.data() not_eq nullptr);
                            assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                            assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                            assert(v.front() == s2);
                            assert(v.back() == s);
                            for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                                assert(*it == s2);
                            }
                            for(auto i {0}; i < insertion_size; ++i) {
                                assert(v[i] == s2);
                            }
                            for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                                assert(v[i] == s);
                            }
                            assert(result == v.begin());
                            assert(result == v.cbegin());
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to head/With reallocation/Insertion size less equal to double capacity done." << std::endl;
                        }

                        // insertion size greater than double capacity
                        {
                            auto count {this->generate_count()};
                            while(count <= 1) {
                                count = this->generate_count();
                            }
                            const auto insertion_size {this->generate_a_random_number(2 * count + 1)};
                            const std::string s {"init"};
                            vector<std::string> v(count, s);
                            const auto s2 {"insert"};
                            auto result {v.insert(0, s2, insertion_size)};
                            assert(v.size() == count + static_cast<size_t>(insertion_size));
                            assert(not v.empty());
                            assert(v.capacity() == static_cast<size_t>(count) + insertion_size);
                            assert(v.spare() == 0);
                            assert(v.data() not_eq nullptr);
                            assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                            assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                            assert(v.front() == s2);
                            assert(v.back() == s);
                            for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                                assert(*it == s2);
                            }
                            for(auto i {0}; i < insertion_size; ++i) {
                                assert(v[i] == s2);
                            }
                            for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                                assert(v[i] == s);
                            }
                            assert(result == v.begin());
                            assert(result == v.cbegin());
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to head/With reallocation/Insertion size greater than double capacity done." << std::endl;
                        }

                        // the value is from self
                        {
                            auto count {this->generate_count()};
                            while(count <= 1) {
                                count = this->generate_count();
                            }
                            auto insertion_size {this->generate_count()};
                            while(insertion_size == 0) {
                                insertion_size = this->generate_count();
                            }
                            const std::string s {"init"};
                            vector<std::string> v(count, s);
                            const std::string s2 {"insert"};
                            v[0] = s2;
                            auto result {v.insert(0, v[0], insertion_size)};
                            assert(v.size() == count + static_cast<size_t>(insertion_size));
                            assert(not v.empty());
                            if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                                assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                                assert(v.spare() == 0);
                            }else {
                                assert(v.capacity() == static_cast<size_t>(count) * 2);
                                assert(v.spare() == count - insertion_size);
                            }
                            assert(v.data() not_eq nullptr);
                            assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                            assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                            assert(v.front() == s2);
                            assert(v.back() == s);
                            for(auto it {v.begin()}; it not_eq v.begin() + (insertion_size + 1); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.begin() + (insertion_size + 1)}; it not_eq v.end(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin()}; it not_eq v.cbegin() + (insertion_size + 1); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.cbegin() + (insertion_size + 1)}; it not_eq v.cend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.rbegin()}; it not_eq v.rbegin() + (count - 1); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.rbegin() + (count - 1)}; it not_eq v.rend(); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.crbegin()}; it not_eq v.crbegin() + (count - 1); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin() + (count - 1)}; it not_eq v.crend(); ++it) {
                                assert(*it == s2);
                            }
                            for(auto i {0}; i < insertion_size + 1; ++i) {
                                assert(v[i] == s2);
                            }
                            for(auto i {insertion_size + 1}; i < count + insertion_size; ++i) {
                                assert(v[i] == s);
                            }
                            assert(result == v.begin());
                            assert(result == v.cbegin());
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to head/With reallocation/The value is from self done." << std::endl;
                        }

                        std::cout << "\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to head/With reallocation finished!" << std::endl;
                    }

                    std::cout << "\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to head finished!" << std::endl;
                }

                // insert to random position
                {
                    std::cout << "\t\t\tStart checking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to random position!" << std::endl;

                    // without reallocation
                    {
                        std::cout << "\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to random position/Without reallocation!" << std::endl;

                        // insertion size is zero
                        {
                            auto count {this->generate_count()};
                            while(count <= 1) {
                                count = this->generate_count();
                            }
                            const auto new_size {this->generate_a_random_number(1, count - 1)};
                            const std::string s {"insert"};
                            const auto insertion_position {this->generate_a_random_number(1, new_size - 1)};
                            vector<std::string> v(count, s);
                            destroy(v.first + new_size, v.cursor);
                            v.cursor = v.first + new_size;
                            const auto result {v.insert(insertion_position, "hello", 0)};
                            assert(v.size() == new_size);
                            assert(not v.empty());
                            assert(v.capacity() == count);
                            assert(v.spare() == count - new_size);
                            assert(v.data() not_eq nullptr);
                            assert(v.begin() + new_size == v.end());
                            assert(v.cbegin() + new_size == v.cend());
                            assert(v.front() == s);
                            assert(v.back() == s);
                            for(auto it {v.begin() + 1}; it not_eq v.end(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin() + 1}; it not_eq v.cend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.rbegin()}; it not_eq v.rend() - 1; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin()}; it not_eq v.crend() - 1; ++it) {
                                assert(*it == s);
                            }
                            for(auto i {1}; i < v.size(); ++i) {
                                assert(v[i] == s);
                            }
                            assert(result == v.begin() + insertion_position);
                            assert(result == v.cbegin() + insertion_position);
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to random position/Without reallocation/Insertion size is zero done." << std::endl;
                        }

                        // insertion size less equal to tail size
                        {
                            auto count {this->generate_count()};
                            while(count <= 1) {
                                count = this->generate_count();
                            }
                            const auto insertion_position {this->generate_a_random_number(1, count - 1)};
                            const auto insertion_size {this->generate_a_random_number(1, count - insertion_position)};
                            const auto s {"init"};
                            const auto spare {this->generate_count(count)};
                            vector<std::string> v(count + static_cast<size_t>(insertion_size) + spare, s);
                            destroy(v.cursor - (insertion_size + spare), v.cursor);
                            v.cursor -= insertion_size + spare;
                            auto s2 {"insert"};
                            const auto result {v.insert(insertion_position, s2, insertion_size)};
                            assert(v.size() == count + static_cast<size_t>(insertion_size));
                            assert(not v.empty());
                            assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                            assert(v.spare() == spare);
                            assert(v.data() not_eq nullptr);
                            assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                            assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                            assert(v.front() == s);
                            assert(v.back() == s);
                            for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                                assert(*it == s);
                            }
                            const auto tail_size {count - insertion_position};
                            for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto i {0}; i < insertion_position; ++i) {
                                assert(v[i] == s);
                            }
                            for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                                assert(v[i] == s2);
                            }
                            for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                                assert(v[i] == s);
                            }
                            assert(result == v.begin() + insertion_position);
                            assert(result == v.cbegin() + insertion_position);
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to random position/Without reallocation/Insertion size less equal to tail size done." << std::endl;
                        }

                        // insertion size greater than tail size
                        {
                            auto count {this->generate_count()};
                            while(count <= 1) {
                                count = this->generate_count();
                            }
                            const auto insertion_position {this->generate_a_random_number(1, count - 1)};
                            const auto insertion_size {this->generate_a_random_number(count - insertion_position + 1)};
                            const std::string s {"init"};
                            const auto spare {this->generate_count(count)};
                            vector<std::string> v(count + static_cast<size_t>(insertion_size) + spare, s);
                            destroy(v.cursor - (static_cast<size_t>(insertion_size) + spare), v.cursor);
                            v.cursor -= static_cast<size_t>(insertion_size) + spare;
                            const std::string s2 {"insert"};
                            const auto result {v.insert(insertion_position, s2, insertion_size)};
                            assert(v.size() == count + static_cast<size_t>(insertion_size));
                            assert(not v.empty());
                            assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                            assert(v.spare() == spare);
                            assert(v.data() not_eq nullptr);
                            assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                            assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                            assert(v.front() == s);
                            assert(v.back() == s);
                            for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                                assert(*it == s);
                            }
                            const auto tail_size {count - insertion_position};
                            for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto i {0}; i < insertion_position; ++i) {
                                assert(v[i] == s);
                            }
                            for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                                assert(v[i] == s2);
                            }
                            for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                                assert(v[i] == s);
                            }
                            assert(result == v.begin() + insertion_position);
                            assert(result == v.cbegin() + insertion_position);
                            std::cout << "\t\t\t\t\tChecking test_test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to random position/Without reallocation/Insertion size greater than tail size done." << std::endl;
                        }

                        // the value is from self
                        {
                            auto count {this->generate_count()};
                            while(count <= 2) {
                                count = this->generate_count();
                            }
                            const auto insertion_position {this->generate_a_random_number(1, count - 2)};
                            auto insertion_size {this->generate_count()};
                            while(insertion_size == 0) {
                                insertion_size = this->generate_count();
                            }
                            const std::string s {"init"};
                            vector<std::string> v(count + static_cast<size_t>(insertion_size), s);
                            destroy(v.cursor - insertion_size, v.cursor);
                            v.cursor -= insertion_size;
                            const std::string s2 {"insert"};
                            v[insertion_position] = s2;
                            auto result {v.insert(insertion_position, v[insertion_position], insertion_size)};
                            assert(v.size() == count + static_cast<size_t>(insertion_size));
                            assert(not v.empty());
                            assert(v.capacity() == static_cast<size_t>(count) + insertion_size);
                            assert(v.spare() == 0);
                            assert(v.data() not_eq nullptr);
                            assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                            assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                            assert(v.front() == s);
                            assert(v.back() == s);
                            for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size + 1); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.begin() + (insertion_position + insertion_size + 1)}; it not_eq v.end(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size + 1); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.cbegin() + (insertion_position + insertion_size + 1)}; it not_eq v.cend(); ++it) {
                                assert(*it == s);
                            }
                            const auto tail_size {count - insertion_position};
                            for(auto it {v.rbegin()}; it not_eq v.rbegin() + (tail_size - 1); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.rbegin() + (tail_size - 1)}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin()}; it not_eq v.crbegin() + (tail_size - 1); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin() + (tail_size - 1)}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto i {0}; i < insertion_position; ++i) {
                                assert(v[i] == s);
                            }
                            for(auto i {insertion_position}; i < insertion_position + insertion_size + 1; ++i) {
                                assert(v[i] == s2);
                            }
                            for(auto i {insertion_position + insertion_size + 1}; i < v.size(); ++i) {
                                assert(v[i] == s);
                            }
                            assert(result == v.begin() + insertion_position);
                            assert(result == v.cbegin() + insertion_position);
                            std::cout << "\t\t\t\t\tChecking test_test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to random position/Without reallocation/The value is from self done." << std::endl;
                        }

                        std::cout << "\t\t\t\tStart checking test_test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to random position/Without reallocation finished!" << std::endl;
                    }

                    // with reallocation
                    {
                        std::cout << "\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to random position/With reallocation!" << std::endl;

                        // insertion size less equal to tail size
                        {
                            auto count {this->generate_count()};
                            while(count <= 1) {
                                count = this->generate_count();
                            }
                            const auto insertion_position {this->generate_a_random_number(1, count - 1)};
                            auto insertion_size {this->generate_a_random_number(1, count - insertion_position)};
                            const std::string s {"init"};
                            vector<std::string> v(count, s);
                            const std::string s2 {"insert"};
                            const auto result {v.insert(insertion_position, s2, insertion_size)};
                            assert(v.size() == count + static_cast<size_t>(insertion_size));
                            assert(not v.empty());
                            if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                                assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                                assert(v.spare() == 0);
                            }else {
                                assert(v.capacity() == static_cast<size_t>(count) * 2);
                                assert(v.spare() == count - insertion_size);
                            }
                            assert(v.data() not_eq nullptr);
                            assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                            assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                            assert(v.front() == s);
                            assert(v.back() == s);
                            for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                                assert(*it == s);
                            }
                            const auto tail_size {count - insertion_position};
                            for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto i {0}; i < insertion_position; ++i) {
                                assert(v[i] == s);
                            }
                            for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                                assert(v[i] == s2);
                            }
                            for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                                assert(v[i] == s);
                            }
                            assert(result == v.begin() + insertion_position);
                            assert(result == v.cbegin() + insertion_position);
                            std::cout << "\t\t\t\t\tChecking test_insert_1/Insert to non-empty vector/Insert to random position/With reallocation/Insertion size less equal to tail size done." << std::endl;
                        }

                        // insertion size greater than tail size
                        {
                            auto count {this->generate_count()};
                            while(count <= 1) {
                                count = this->generate_count();
                            }
                            const auto insertion_position {this->generate_a_random_number(1, count - 1)};
                            const auto insertion_size {this->generate_a_random_number(count - insertion_position + 1)};
                            const std::string s {"init"};
                            vector<std::string> v(count, s);
                            const std::string s2 {"insert"};
                            const auto result {v.insert(insertion_position, s2, insertion_size)};
                            assert(v.size() == count + static_cast<size_t>(insertion_size));
                            assert(not v.empty());
                            if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                                assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                                assert(v.spare() == 0);
                            }else {
                                assert(v.capacity() == static_cast<size_t>(count) * 2);
                                assert(v.spare() == count - insertion_size);
                            }
                            assert(v.data() not_eq nullptr);
                            assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                            assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                            assert(v.front() == s);
                            assert(v.back() == s);
                            for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                                assert(*it == s);
                            }
                            const auto tail_size {count - insertion_position};
                            for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto i {0}; i < insertion_position; ++i) {
                                assert(v[i] == s);
                            }
                            for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                                assert(v[i] == s2);
                            }
                            for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                                assert(v[i] == s);
                            }
                            assert(result == v.begin() + insertion_position);
                            assert(result == v.cbegin() + insertion_position);
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to random position/With reallocation/Insertion size greater than tail size done." << std::endl;
                        }

                        // insertion size less equal to double capacity
                        {
                            auto count {this->generate_count()};
                            while(count <= 2) {
                                count = this->generate_count();
                            }
                            const auto insertion_position {this->generate_a_random_number(1, count - 2)};
                            auto insertion_size {this->generate_a_random_number(1, count)};
                            const std::string s {"init"};
                            vector<std::string> v(count, s);
                            const std::string s2 {"insert"};
                            auto result {v.insert(insertion_position, s2, insertion_size)};
                            assert(v.size() == count + static_cast<size_t>(insertion_size));
                            assert(not v.empty());
                            assert(v.capacity() == static_cast<size_t>(count) * 2);
                            assert(v.spare() == count - insertion_size);
                            assert(v.data() not_eq nullptr);
                            assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                            assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                            assert(v.front() == s);
                            assert(v.back() == s);
                            for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                                assert(*it == s);
                            }
                            const auto tail_size {count - insertion_position};
                            for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto i {0}; i < insertion_position; ++i) {
                                assert(v[i] == s);
                            }
                            for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                                assert(v[i] == s2);
                            }
                            for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                                assert(v[i] == s);
                            }
                            assert(result == v.begin() + insertion_position);
                            assert(result == v.cbegin() + insertion_position);
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to random position/With reallocation/Insertion size less equal to double capacity done." << std::endl;
                        }

                        // insertion size greater than double capacity
                        {
                            auto count {this->generate_count()};
                            while(count <= 2) {
                                count = this->generate_count();
                            }
                            const auto insertion_position {this->generate_a_random_number(1, count - 2)};
                            auto insertion_size {this->generate_a_random_number(2 * count + 1)};
                            const std::string s {"init"};
                            vector<std::string> v(count, s);
                            const std::string s2 {"insert"};
                            auto result {v.insert(insertion_position, s2, insertion_size)};
                            assert(v.size() == count + static_cast<size_t>(insertion_size));
                            assert(not v.empty());
                            assert(v.capacity() == static_cast<size_t>(count) + insertion_size);
                            assert(v.spare() == 0);
                            assert(v.data() not_eq nullptr);
                            assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                            assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                            assert(v.front() == s);
                            assert(v.back() == s);
                            for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                                assert(*it == s);
                            }
                            const auto tail_size {count - insertion_position};
                            for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto i {0}; i < insertion_position; ++i) {
                                assert(v[i] == s);
                            }
                            for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                                assert(v[i] == s2);
                            }
                            for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                                assert(v[i] == s);
                            }
                            assert(result == v.begin() + insertion_position);
                            assert(result == v.cbegin() + insertion_position);
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to random position/With reallocation/Insertion size greater than double capacity done." << std::endl;
                        }

                        // the value is from self
                        {
                            auto count {this->generate_count()};
                            while(count <= 2) {
                                count = this->generate_count();
                            }
                            const auto insertion_position {this->generate_a_random_number(1, count - 2)};
                            auto insertion_size {this->generate_count()};
                            while(insertion_size == 0) {
                                insertion_size = this->generate_count();
                            }
                            const std::string s {"init"};
                            vector<std::string> v(count, s);
                            const std::string s2 {"insert"};
                            v[insertion_position] = s2;
                            auto result {v.insert(insertion_position, v[insertion_position], insertion_size)};
                            assert(v.size() == count + static_cast<size_t>(insertion_size));
                            assert(not v.empty());
                            if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                                assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                                assert(v.spare() == 0);
                            }else {
                                assert(v.capacity() == static_cast<size_t>(count) * 2);
                                assert(v.spare() == count - insertion_size);
                            }
                            assert(v.data() not_eq nullptr);
                            assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                            assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                            assert(v.front() == s);
                            assert(v.back() == s);
                            for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size + 1); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.begin() + (insertion_position + insertion_size + 1)}; it not_eq v.end(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size + 1); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.cbegin() + (insertion_position + insertion_size + 1)}; it not_eq v.cend(); ++it) {
                                assert(*it == s);
                            }
                            const auto tail_size {count - insertion_position};
                            for(auto it {v.rbegin()}; it not_eq v.rbegin() + (tail_size - 1); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.rbegin() + (tail_size - 1)}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin()}; it not_eq v.crbegin() + (tail_size - 1); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin() + (tail_size - 1)}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto i {0}; i < insertion_position; ++i) {
                                assert(v[i] == s);
                            }
                            for(auto i {insertion_position}; i < insertion_position + insertion_size + 1; ++i) {
                                assert(v[i] == s2);
                            }
                            for(auto i {insertion_position + insertion_size + 1}; i < v.size(); ++i) {
                                assert(v[i] == s);
                            }
                            assert(result == v.begin() + insertion_position);
                            assert(result == v.cbegin() + insertion_position);
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to random position/With reallocation/The value is from self done." << std::endl;
                        }

                        std::cout << "\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to random position/With reallocation finished!" << std::endl;
                    }

                    std::cout << "\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to random position finished!" << std::endl;
                }

                // insert to tail
                {
                    std::cout << "\t\t\tStart checking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to tail!" << std::endl;

                    // without reallocation
                    {
                        std::cout << "\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to tail/Without reallocation!" << std::endl;

                        // insertion size is zero
                        {
                            auto count {this->generate_count()};
                            while(count <= 1) {
                                count = this->generate_count();
                            }
                            const auto new_size {this->generate_a_random_number(1, count - 1)};
                            const std::string s {"init"};
                            vector<std::string> v(count, s);
                            destroy(v.first + new_size, v.cursor);
                            v.cursor = v.first + new_size;
                            const auto result {v.insert(new_size, "hello", 0)};
                            assert(v.size() == new_size);
                            assert(not v.empty());
                            assert(v.capacity() == count);
                            assert(v.spare() == count - new_size);
                            assert(v.data() not_eq nullptr);
                            assert(v.begin() + new_size == v.end());
                            assert(v.cbegin() + new_size == v.cend());
                            assert(v.front() == s);
                            assert(v.back() == s);
                            for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto i {1}; i < v.size(); ++i) {
                                assert(v[i] == s);
                            }
                            assert(result == v.end());
                            assert(result == v.cend());
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to tail/Without reallocation/Insertion size is zero done." << std::endl;
                        }

                        // insertion size less equal to tail size
                        {
                            auto count {this->generate_count()};
                            while(count <= 1) {
                                count = this->generate_count();
                            }
                            auto insertion_size {this->generate_a_random_number(1, count)};
                            const std::string s {"init"};
                            const auto spare {this->generate_count(count)};
                            vector<std::string> v(count + static_cast<size_t>(insertion_size) + spare, s);
                            v.cursor -= insertion_size + spare;
                            const std::string s2 {"insert"};
                            const auto result {v.insert(count, s2, insertion_size)};
                            assert(v.size() == count + static_cast<size_t>(insertion_size));
                            assert(not v.empty());
                            assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                            assert(v.spare() == spare);
                            assert(v.data() not_eq nullptr);
                            assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                            assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                            assert(v.front() == s);
                            assert(v.back() == s2);
                            for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto i {0}; i < count; ++i) {
                                assert(v[i] == s);
                            }
                            for(auto i {count}; i < count + insertion_size; ++i) {
                                assert(v[i] == s2);
                            }
                            assert(result == v.begin() + count);
                            assert(result == v.cbegin() + count);
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to tail/Without reallocation/Insertion size less equal to tail size done." << std::endl;
                        }

                        // insertion size greater than tail size
                        {
                            auto count {this->generate_count()};
                            while(count <= 1) {
                                count = this->generate_count();
                            }
                            const auto insertion_size {this->generate_a_random_number(count + 1)};
                            const std::string s {"init"};
                            const auto spare {this->generate_count(count)};
                            vector<std::string> v(count + static_cast<size_t>(insertion_size) + spare, s);
                            destroy(v.cursor - (static_cast<size_t>(insertion_size + spare)), v.cursor);
                            v.cursor -= static_cast<size_t>(insertion_size) + spare;
                            const std::string s2 {"insert"};
                            const auto result {v.insert(count, s2, insertion_size)};
                            assert(v.size() == count + static_cast<size_t>(insertion_size));
                            assert(not v.empty());
                            assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                            assert(v.spare() == spare);
                            assert(v.data() not_eq nullptr);
                            assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                            assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                            assert(v.front() == s);
                            assert(v.back() == s2);
                            for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto i {0}; i < count; ++i) {
                                assert(v[i] == s);
                            }
                            for(auto i {count}; i < count + insertion_size; ++i) {
                                assert(v[i] == s2);
                            }
                            assert(result == v.begin() + count);
                            assert(result == v.cbegin() + count);
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to tail/Without reallocation/Insertion size greater than tail size done." << std::endl;
                        }

                        // the value is from self
                        {
                            auto count {this->generate_count()};
                            while(count <= 1) {
                                count = this->generate_count();
                            }
                            auto insertion_size {this->generate_count()};
                            while(insertion_size == 0) {
                                insertion_size = this->generate_count();
                            }
                            const std::string s {"init"};
                            vector<std::string> v(count + static_cast<size_t>(insertion_size), s);
                            destroy(v.cursor - insertion_size, v.cursor);
                            v.cursor -= insertion_size;
                            const std::string s2 {"insert"};
                            v[count - 1] = s2;
                            const auto result {v.insert(count, v[count - 1], insertion_size)};
                            assert(v.size() == count + static_cast<size_t>(insertion_size));
                            assert(not v.empty());
                            assert(v.capacity() == static_cast<size_t>(count) + insertion_size);
                            assert(v.spare() == 0);
                            assert(v.data() not_eq nullptr);
                            assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                            assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                            assert(v.front() == s);
                            assert(v.back() == s2);
                            for(auto it {v.begin()}; it not_eq v.begin() + (count - 1); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.begin() + (count - 1)}; it not_eq v.end(); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.cbegin()}; it not_eq v.cbegin() + (count - 1); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin() + (count - 1)}; it not_eq v.cend(); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.rbegin()}; it not_eq v.rbegin() + (insertion_size + 1); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.rbegin() + (insertion_size + 1)}; it not_eq v.rend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin()}; it not_eq v.crbegin() + (insertion_size + 1); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.crbegin() + (insertion_size + 1)}; it not_eq v.crend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto i {0}; i < count - 1; ++i) {
                                assert(v[i] == s);
                            }
                            for(auto i {count - 1}; i < count + insertion_size; ++i) {
                                assert(v[i] == s2);
                            }
                            assert(result == v.begin() + count);
                            assert(result == v.cbegin() + count);
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to tail/Without reallocation/The value is from self done." << std::endl;
                        }

                        std::cout << "\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to tail/Without reallocation finished!" << std::endl;
                    }

                    // with reallocation
                    {
                        std::cout << "\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to tail/With reallocation!" << std::endl;

                        // insertion size less equal to tail size
                        {
                            auto count {this->generate_count()};
                            while(count <= 1) {
                                count = this->generate_count();
                            }
                            auto insertion_size {this->generate_a_random_number(1, count)};
                            const std::string s {"init"};
                            vector<std::string> v(count, s);
                            const auto s2 {"insert"};
                            const auto result {v.insert(count, s2, insertion_size)};
                            assert(v.size() == count + static_cast<size_t>(insertion_size));
                            assert(not v.empty());
                            if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                                assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                                assert(v.spare() == 0);
                            }else {
                                assert(v.capacity() == static_cast<size_t>(count) * 2);
                                assert(v.spare() == count - insertion_size);
                            }
                            assert(v.data() not_eq nullptr);
                            assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                            assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                            assert(v.front() == s);
                            assert(v.back() == s2);
                            for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto i {0}; i < count; ++i) {
                                assert(v[i] == s);
                            }
                            for(auto i {count}; i < count + insertion_size; ++i) {
                                assert(v[i] == s2);
                            }
                            assert(result == v.begin() + count);
                            assert(result == v.cbegin() + count);
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to tail/With reallocation/Insertion size less equal to tail size done." << std::endl;
                        }

                        // insertion size greater than tail size
                        {
                            auto count {this->generate_count()};
                            while(count <= 1) {
                                count = this->generate_count();
                            }
                            const auto insertion_size {this->generate_a_random_number(count + 1)};
                            const std::string s {"init"};
                            vector<std::string> v(count, s);
                            const std::string s2 {"insert"};
                            const auto result {v.insert(count, s2, insertion_size)};
                            assert(v.size() == count + static_cast<size_t>(insertion_size));
                            assert(not v.empty());
                            if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                                assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                                assert(v.spare() == 0);
                            }else {
                                assert(v.capacity() == static_cast<size_t>(count) * 2);
                                assert(v.spare() == count - insertion_size);
                            }
                            assert(v.data() not_eq nullptr);
                            assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                            assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                            assert(v.front() == s);
                            assert(v.back() == s2);
                            for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto i {0}; i < count; ++i) {
                                assert(v[i] == s);
                            }
                            for(auto i {count}; i < count + insertion_size; ++i) {
                                assert(v[i] == s2);
                            }
                            assert(result == v.begin() + count);
                            assert(result == v.cbegin() + count);
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to tail/With reallocation/Insertion size greater than tail size done." << std::endl;
                        }

                        // insertion size less equal to double capacity
                        {
                            auto count {this->generate_count()};
                            while(count <= 1) {
                                count = this->generate_count();
                            }
                            auto insertion_size {this->generate_a_random_number(1, count)};
                            const std::string s {"init"};
                            vector<std::string> v(count, s);
                            const std::string s2 {"insert"};
                            auto result {v.insert(count, s2, insertion_size)};
                            assert(v.size() == count + static_cast<size_t>(insertion_size));
                            assert(not v.empty());
                            assert(v.capacity() == static_cast<size_t>(count) * 2);
                            assert(v.spare() == count - insertion_size);
                            assert(v.data() not_eq nullptr);
                            assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                            assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                            assert(v.front() == s);
                            assert(v.back() == s2);
                            for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto i {0}; i < count; ++i) {
                                assert(v[i] == s);
                            }
                            for(auto i {count}; i < count + insertion_size; ++i) {
                                assert(v[i] == s2);
                            }
                            assert(result == v.begin() + count);
                            assert(result == v.cbegin() + count);
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to tail/With reallocation/Insertion size less equal to double capacity done." << std::endl;
                        }

                        // insertion size greater than double capacity
                        {
                            auto count {this->generate_count()};
                            while(count <= 1) {
                                count = this->generate_count();
                            }
                            auto insertion_size {this->generate_a_random_number(2 * count + 1)};
                            const std::string s {"init"};
                            vector<std::string> v(count, s);
                            const std::string s2 {"insert"};
                            auto result {v.insert(count, s2, insertion_size)};
                            assert(v.size() == count + static_cast<size_t>(insertion_size));
                            assert(not v.empty());
                            assert(v.capacity() == static_cast<size_t>(count) + insertion_size);
                            assert(v.spare() == 0);
                            assert(v.data() not_eq nullptr);
                            assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                            assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                            assert(v.front() == s);
                            assert(v.back() == s2);
                            for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto i {0}; i < count; ++i) {
                                assert(v[i] == s);
                            }
                            for(auto i {count}; i < count + insertion_size; ++i) {
                                assert(v[i] == s2);
                            }
                            assert(result == v.begin() + count);
                            assert(result == v.cbegin() + count);
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to tail/With reallocation/Insertion size greater than double capacity done." << std::endl;
                        }

                        // the value is from self
                        {
                            auto count {this->generate_count()};
                            while(count <= 1) {
                                count = this->generate_count();
                            }
                            auto insertion_size {this->generate_count()};
                            while(insertion_size == 0) {
                                insertion_size = this->generate_count();
                            }
                            const std::string s {"init"};
                            vector<std::string> v(count, s);
                            const std::string s2 {"insert"};
                            v[count - 1] = s2;
                            auto result {v.insert(count, v[count - 1], insertion_size)};
                            assert(v.size() == count + static_cast<size_t>(insertion_size));
                            assert(not v.empty());
                            if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                                assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                                assert(v.spare() == 0);
                            }else {
                                assert(v.capacity() == static_cast<size_t>(count) * 2);
                                assert(v.spare() == count - insertion_size);
                            }
                            assert(v.data() not_eq nullptr);
                            assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                            assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                            assert(v.front() == s);
                            assert(v.back() == s2);
                            for(auto it {v.begin()}; it not_eq v.begin() + (count - 1); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.begin() + (count - 1)}; it not_eq v.end(); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.cbegin()}; it not_eq v.cbegin() + (count - 1); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.cbegin() + (count - 1)}; it not_eq v.cend(); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.rbegin()}; it not_eq v.rbegin() + (insertion_size + 1); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.rbegin() + (insertion_size + 1)}; it not_eq v.rend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {v.crbegin()}; it not_eq v.crbegin() + (insertion_size + 1); ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {v.crbegin() + (insertion_size + 1)}; it not_eq v.crend(); ++it) {
                                assert(*it == s);
                            }
                            for(auto i {0}; i < count - 1; ++i) {
                                assert(v[i] == s);
                            }
                            for(auto i {count - 1}; i < count + insertion_size; ++i) {
                                assert(v[i] == s2);
                            }
                            assert(result == v.begin() + count);
                            assert(result == v.cbegin() + count);
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to tail/With reallocation/The value is from self done." << std::endl;
                        }

                        std::cout << "\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to tail/With reallocation finished!" << std::endl;
                    }

                    std::cout << "\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector/Insert to tail finished!" << std::endl;
                }

                std::cout << "\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty vector finished!" << std::endl;
            }
        }

        std::cout << "\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type) for ds::vector finished!" << std::endl;
    }

    // iterator insert(size_type, ForwardIterator, ForwardIterator)
    {
        std::cout << "\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/ for ds::vector!" << std::endl;

        // insert to empty vector
        {
            std::cout << "\t\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to empty vector for ds::vector!" << std::endl;

            // insertion size equal to zero
            {
                vector<std::string> v {};
                const auto result {v.insert(0, std_string_random_access_iterator {}, std_string_random_access_iterator {})};
                assert(v.size() == 0);
                assert(v.empty());
                assert(v.capacity() == 0);
                assert(v.spare() == 0);
                assert(v.data() == nullptr);
                assert(v.begin() == v.end());
                assert(v.cbegin() == v.cend());
                assert(result == v.begin());
                assert(result == v.cbegin());
                std::cout << "\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to empty vector/Insertion size not equal to zero done." << std::endl;
            }

            // insertion size not equal to zero
            {
                vector<std::string> v {};
                auto insertion_size {this->generate_count()};
                while(insertion_size == 0) {
                    insertion_size = this->generate_count();
                }
                const std::vector<std::string> strings(insertion_size, "init");
                auto d {this->to_random_access_iterator(strings)};
                const auto result {v.insert(0, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                assert(v.size() == insertion_size);
                assert(not v.empty());
                assert(v.capacity() == insertion_size);
                assert(v.spare() == 0);
                assert(v.data() not_eq nullptr);
                assert(v.begin() + insertion_size == v.end());
                assert(v.cbegin() + insertion_size == v.cend());
                assert(v.front() == strings.front());
                assert(v.back() == strings.back());
                auto i {0uz};
                for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                    assert(*it == strings[i++]);
                }
                i = 0;
                for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                    assert(*it == strings[i++]);
                }
                i = insertion_size - 1;
                for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                    assert(*it == strings[i--]);
                }
                i = insertion_size - 1;
                for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                    assert(*it == strings[i--]);
                }
                for(auto i {0}; i < v.size(); ++i) {
                    assert(v[i] == strings[i]);
                }
                assert(result == v.begin());
                assert(result == v.cbegin());
                std::cout << "\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to empty vector/Insertion size not equal to zero done." << std::endl;
            }

            std::cout << "\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to empty vector for ds::vector finished!" << std::endl;
        }

        // insert to non-empty vector
        {
            std::cout << "\t\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector!" << std::endl;

            // insert to head
            {
                std::cout << "\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to head!" << std::endl;

                // without reallocation
                {
                    std::cout << "\t\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to head/Without reallocation!" << std::endl;

                    // insertion size is zero
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto new_size {this->generate_a_random_number(1, count - 1)};
                        const std::string s {"init"};
                        vector<std::string> v(count, s);
                        v.cursor = v.first + new_size;
                        const auto result {v.insert(0, std_string_random_access_iterator {}, std_string_random_access_iterator {})};
                        assert(v.size() == new_size);
                        assert(not v.empty());
                        assert(v.capacity() == count);
                        assert(v.spare() == count - new_size);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + new_size == v.end());
                        assert(v.cbegin() + new_size == v.cend());
                        assert(v.front() == s);
                        assert(v.back() == s);
                        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                            assert(*it == s);
                        }
                        for(auto i {1}; i < v.size(); ++i) {
                            assert(v[i] == s);
                        }
                        assert(result == v.begin());
                        assert(result == v.cbegin());
                        std::cout << "\t\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to head/Without reallocation/Insertion size is zero done." << std::endl;
                    }

                    // insertion size less equal to tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        auto insertion_size {this->generate_a_random_number(1, count)};
                        const std::vector<std::string> strings(insertion_size, "init");
                        auto d {this->to_random_access_iterator(strings)};
                        const std::string s {"init"};
                        const auto spare {this->generate_count(count)};
                        vector<std::string> v(count + static_cast<size_t>(insertion_size) + spare, s);
                        destroy(v.cursor - (insertion_size + spare), v.cursor);
                        v.cursor -= insertion_size + spare;
                        const auto result {v.insert(0, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                        assert(v.spare() == spare);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == strings.front());
                        assert(v.back() == s);
                        auto string_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                            assert(*it == s);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                            assert(*it == s);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        string_i = 0;
                        for(auto i {0}; i < insertion_size; ++i) {
                            assert(v[i] == strings[string_i++]);
                        }
                        for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                            assert(v[i] == s);
                        }
                        assert(result == v.begin());
                        assert(result == v.cbegin());
                        std::cout << "\t\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to head/Without reallocation/Insertion size less equal to tail size done." << std::endl;
                    }

                    // insertion size greater than tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_size {this->generate_a_random_number(count + 1)};
                        const std::vector<std::string> strings(insertion_size, "init");
                        auto d {this->to_random_access_iterator(strings)};
                        const std::string s {"init"};
                        const auto spare {this->generate_count(count)};
                        vector<std::string> v(count + static_cast<size_t>(insertion_size) + spare, s);
                        destroy(v.cursor - (static_cast<size_t>(insertion_size) + spare), v.cursor);
                        v.cursor -= static_cast<size_t>(insertion_size) + spare;
                        const auto result {v.insert(0, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                        assert(v.spare() == spare);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == strings.front());
                        assert(v.back() == s);
                        auto string_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                            assert(*it == s);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                            assert(*it == s);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        string_i = 0;
                        for(auto i {0}; i < insertion_size; ++i) {
                            assert(v[i] == strings[string_i++]);
                        }
                        for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                            assert(v[i] == s);
                        }
                        assert(result == v.begin());
                        assert(result == v.cbegin());
                        std::cout << "\t\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to head/Without reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    std::cout << "\t\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to head/Without reallocation finished!" << std::endl;
                }

                // with reallocation
                {
                    std::cout << "\t\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to head/With reallocation!" << std::endl;

                    // insertion size less equal to tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        auto insertion_size {this->generate_a_random_number(1, count)};
                        const std::vector<std::string> strings(insertion_size, "init");
                        auto d {this->to_random_access_iterator(strings)};
                        const std::string s {"init"};
                        vector<std::string> v(count, s);
                        const auto result {v.insert(0, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                            assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                            assert(v.spare() == 0);
                        }else {
                            assert(v.capacity() == static_cast<size_t>(count) * 2);
                            assert(v.spare() == count - insertion_size);
                        }
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == strings.front());
                        assert(v.back() == s);
                        auto string_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                            assert(*it == s);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                            assert(*it == s);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        string_i = 0;
                        for(auto i {0}; i < insertion_size; ++i) {
                            assert(v[i] == strings[string_i++]);
                        }
                        for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                            assert(v[i] == s);
                        }
                        assert(result == v.begin());
                        assert(result == v.cbegin());
                        std::cout << "\t\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to head/With reallocation/Insertion size less equal to tail size done." << std::endl;
                    }

                    // insertion size greater than tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_size {this->generate_a_random_number(count + 1)};
                        const std::vector<std::string> strings(insertion_size, "init");
                        auto d {this->to_random_access_iterator(strings)};
                        const std::string s {"init"};
                        vector<std::string> v(count, s);
                        const auto result {v.insert(0, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                            assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                            assert(v.spare() == 0);
                        }else {
                            assert(v.capacity() == static_cast<size_t>(count) * 2);
                            assert(v.spare() == count - insertion_size);
                        }
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == strings.front());
                        assert(v.back() == s);
                        auto string_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                            assert(*it == s);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                            assert(*it == s);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        string_i = 0;
                        for(auto i {0}; i < insertion_size; ++i) {
                            assert(v[i] == strings[string_i++]);
                        }
                        for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                            assert(v[i] == s);
                        }
                        assert(result == v.begin());
                        assert(result == v.cbegin());
                        std::cout << "\t\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to head/With reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    // insertion size less equal to double capacity
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_size {this->generate_a_random_number(1, count)};
                        const std::vector<std::string> strings(insertion_size, "init");
                        auto d {this->to_random_access_iterator(strings)};
                        const std::string s {"init"};
                        vector<std::string> v(count, s);
                        auto result {v.insert(0, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == static_cast<size_t>(count) * 2);
                        assert(v.spare() == count - insertion_size);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == strings.front());
                        assert(v.back() == s);
                        auto string_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                            assert(*it == s);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                            assert(*it == s);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        string_i = 0;
                        for(auto i {0}; i < insertion_size; ++i) {
                            assert(v[i] == strings[string_i++]);
                        }
                        for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                            assert(v[i] == s);
                        }
                        assert(result == v.begin());
                        assert(result == v.cbegin());
                        std::cout << "\t\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to head/With reallocation/Insertion size less equal to double capacity done." << std::endl;
                    }

                    // insertion size greater than double capacity
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_size {this->generate_a_random_number(2 * count + 1)};
                        const std::vector<std::string> strings(insertion_size, "init");
                        auto d {this->to_random_access_iterator(strings)};
                        const std::string s {"init"};
                        vector<std::string> v(count, s);
                        auto result {v.insert(0, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == static_cast<size_t>(count) + insertion_size);
                        assert(v.spare() == 0);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == strings.front());
                        assert(v.back() == s);
                        auto string_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_size; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {v.begin() + insertion_size}; it not_eq v.end(); ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_size; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {v.cbegin() + insertion_size}; it not_eq v.cend(); ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + count; ++it) {
                            assert(*it == s);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.rbegin() + count}; it not_eq v.rend(); ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + count; ++it) {
                            assert(*it == s);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.crbegin() + count}; it not_eq v.crend(); ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        string_i = 0;
                        for(auto i {0}; i < insertion_size; ++i) {
                            assert(v[i] == strings[string_i++]);
                        }
                        for(auto i {insertion_size}; i < count + insertion_size; ++i) {
                            assert(v[i] == s);
                        }
                        assert(result == v.begin());
                        assert(result == v.cbegin());
                        std::cout << "\t\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to head/With reallocation/Insertion size greater than double capacity done." << std::endl;
                    }

                    std::cout << "\t\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to head/With reallocation finished!" << std::endl;
                }

                std::cout << "\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to head finished!" << std::endl;
            }

            // insert to random position
            {
                std::cout << "\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to random position!" << std::endl;

                // without reallocation
                {
                    std::cout << "\t\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to random position/Without reallocation!" << std::endl;

                    // insertion size is zero
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto new_size {this->generate_a_random_number(1, count - 1)};
                        const std::string s {"init"};
                        const auto insertion_position {this->generate_a_random_number(1, new_size - 1)};
                        vector<std::string> v(count, s);\
                        destroy(v.first + new_size, v.cursor);
                        v.cursor = v.first + new_size;
                        const auto result {v.insert(insertion_position, std_string_random_access_iterator {}, std_string_random_access_iterator {})};
                        assert(v.size() == new_size);
                        assert(not v.empty());
                        assert(v.capacity() == count);
                        assert(v.spare() == count - new_size);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + new_size == v.end());
                        assert(v.cbegin() + new_size == v.cend());
                        assert(v.front() == s);
                        assert(v.back() == s);
                        for(auto it {v.begin() + 1}; it not_eq v.end(); ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.cbegin() + 1}; it not_eq v.cend(); ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.rbegin()}; it not_eq v.rend() - 1; ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crend() - 1; ++it) {
                            assert(*it == s);
                        }
                        for(auto i {1}; i < v.size(); ++i) {
                            assert(v[i] == s);
                        }
                        assert(result == v.begin() + insertion_position);
                        assert(result == v.cbegin() + insertion_position);
                        std::cout << "\t\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to random position/Without reallocation/Insertion size is zero done." << std::endl;
                    }

                    // insertion size less equal to tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_position {this->generate_a_random_number(1, count - 1)};
                        auto insertion_size {this->generate_a_random_number(1, count - insertion_position)};
                        const std::vector<std::string> strings(insertion_size, "init");
                        auto d {this->to_random_access_iterator(strings)};
                        const std::string s {"init"};
                        const auto spare {this->generate_count(count)};
                        vector<std::string> v(count + static_cast<size_t>(insertion_size) + spare, s);
                        v.cursor -= insertion_size + spare;
                        const auto result {v.insert(insertion_position, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                        assert(v.spare() == spare);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == s);
                        assert(v.back() == s);
                        auto string_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                            assert(*it == s);
                        }
                        const auto tail_size {count - insertion_position};
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                            assert(*it == s);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                            assert(*it == s);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                            assert(*it == s);
                        }
                        for(auto i {0}; i < insertion_position; ++i) {
                            assert(v[i] == s);
                        }
                        string_i = 0;
                        for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                            assert(v[i] == strings[string_i++]);
                        }
                        for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                            assert(v[i] == s);
                        }
                        assert(result == v.begin() + insertion_position);
                        assert(result == v.cbegin() + insertion_position);
                        std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to random position/Without reallocation/Insertion size less equal to tail size done." << std::endl;
                    }

                    // insertion size greater than tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_position {this->generate_a_random_number(1, count - 1)};
                        const auto insertion_size {this->generate_a_random_number(count - insertion_position + 1)};
                        const std::vector<std::string> strings(insertion_size, "init");
                        auto d {this->to_random_access_iterator(strings)};
                        const std::string s {"init"};
                        const auto spare {this->generate_count(count)};
                        vector<std::string> v(count + static_cast<size_t>(insertion_size) + spare, s);
                        v.cursor -= static_cast<size_t>(insertion_size) + spare;
                        const auto result {v.insert(insertion_position, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                        assert(v.spare() == spare);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == s);
                        assert(v.back() == s);
                        auto string_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                            assert(*it == s);
                        }
                        const auto tail_size {count - insertion_position};
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                            assert(*it == s);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                            assert(*it == s);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                            assert(*it == s);
                        }
                        for(auto i {0}; i < insertion_position; ++i) {
                            assert(v[i] == s);
                        }
                        string_i = 0;
                        for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                            assert(v[i] == strings[string_i++]);
                        }
                        for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                            assert(v[i] == s);
                        }
                        assert(result == v.begin() + insertion_position);
                        assert(result == v.cbegin() + insertion_position);
                        std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to random position/Without reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    std::cout << "\t\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to random position/Without reallocation finished!" << std::endl;
                }

                // with reallocation
                {
                    std::cout << "\t\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to random position/With reallocation!" << std::endl;

                    // insertion size less equal to tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_position {this->generate_a_random_number(1, count - 1)};
                        auto insertion_size {this->generate_a_random_number(1, count - insertion_position)};
                        const std::vector<std::string> strings(insertion_size, "init");
                        auto d {this->to_random_access_iterator(strings)};
                        const std::string s {"init"};
                        vector<std::string> v(count, s);
                        const auto result {v.insert(insertion_position, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                            assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                            assert(v.spare() == 0);
                        }else {
                            assert(v.capacity() == static_cast<size_t>(count) * 2);
                            assert(v.spare() == count - insertion_size);
                        }
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == s);
                        assert(v.back() == s);
                        auto string_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                            assert(*it == s);
                        }
                        const auto tail_size {count - insertion_position};
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                            assert(*it == s);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                            assert(*it == s);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                            assert(*it == s);
                        }
                        for(auto i {0}; i < insertion_position; ++i) {
                            assert(v[i] == s);
                        }
                        string_i = 0;
                        for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                            assert(v[i] == strings[string_i++]);
                        }
                        for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                            assert(v[i] == s);
                        }
                        assert(result == v.begin() + insertion_position);
                        assert(result == v.cbegin() + insertion_position);
                        std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to random position/With reallocation/Insertion size less equal to tail size done." << std::endl;
                    }

                    // insertion size greater than tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_position {this->generate_a_random_number(1, count - 1)};
                        const auto insertion_size {this->generate_a_random_number(count - insertion_position + 1)};
                        const std::vector<std::string> strings(insertion_size, "init");
                        auto d {this->to_random_access_iterator(strings)};
                        const std::string s {"init"};
                        vector<std::string> v(count, s);
                        const auto result {v.insert(insertion_position, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                            assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                            assert(v.spare() == 0);
                        }else {
                            assert(v.capacity() == static_cast<size_t>(count) * 2);
                            assert(v.spare() == count - insertion_size);
                        }
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == s);
                        assert(v.back() == s);
                        auto string_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                            assert(*it == s);
                        }
                        const auto tail_size {count - insertion_position};
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                            assert(*it == s);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                            assert(*it == s);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                            assert(*it == s);
                        }
                        for(auto i {0}; i < insertion_position; ++i) {
                            assert(v[i] == s);
                        }
                        string_i = 0;
                        for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                            assert(v[i] == strings[string_i++]);
                        }
                        for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                            assert(v[i] == s);
                        }
                        assert(result == v.begin() + insertion_position);
                        assert(result == v.cbegin() + insertion_position);
                        std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to random position/With reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    // insertion size less equal to double capacity
                    {
                        auto count {this->generate_count()};
                        while(count <= 2) {
                            count = this->generate_count();
                        }
                        const auto insertion_position {this->generate_a_random_number(1, count - 2)};
                        auto insertion_size {this->generate_a_random_number(1, count)};
                        const std::vector<std::string> strings(insertion_size, "init");
                        auto d {this->to_random_access_iterator(strings)};
                        const std::string s {"init"};
                        vector<std::string> v(count, s);
                        auto result {v.insert(insertion_position, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == static_cast<size_t>(count) * 2);
                        assert(v.spare() == count - insertion_size);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == s);
                        assert(v.back() == s);
                        auto string_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                            assert(*it == s);
                        }
                        const auto tail_size {count - insertion_position};
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                            assert(*it == s);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                            assert(*it == s);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                            assert(*it == s);
                        }
                        for(auto i {0}; i < insertion_position; ++i) {
                            assert(v[i] == s);
                        }
                        string_i = 0;
                        for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                            assert(v[i] == strings[string_i++]);
                        }
                        for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                            assert(v[i] == s);
                        }
                        assert(result == v.begin() + insertion_position);
                        assert(result == v.cbegin() + insertion_position);
                        std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to random position/With reallocation/Insertion size less equal to double capacity done." << std::endl;
                    }

                    // insertion size greater than double capacity
                    {
                        auto count {this->generate_count()};
                        while(count <= 2) {
                            count = this->generate_count();
                        }
                        const auto insertion_position {this->generate_a_random_number(1, count - 2)};
                        auto insertion_size {this->generate_a_random_number(2 * count + 1)};
                        const std::vector<std::string> strings(insertion_size, "init");
                        auto d {this->to_random_access_iterator(strings)};
                        const std::string s {"init"};
                        vector<std::string> v(count, s);
                        auto result {v.insert(insertion_position, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == static_cast<size_t>(count) + insertion_size);
                        assert(v.spare() == 0);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == s);
                        assert(v.back() == s);
                        auto string_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + insertion_position; ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.begin() + insertion_position}; it not_eq v.begin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {v.begin() + (insertion_position + insertion_size)}; it not_eq v.end(); ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + insertion_position; ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        for(auto it {v.cbegin() + insertion_position}; it not_eq v.cbegin() + (insertion_position + insertion_size); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {v.cbegin() + (insertion_position + insertion_size)}; it not_eq v.cend(); ++it) {
                            assert(*it == s);
                        }
                        const auto tail_size {count - insertion_position};
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + tail_size; ++it) {
                            assert(*it == s);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.rbegin() + tail_size}; it not_eq v.rbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        for(auto it {v.rbegin() + (tail_size + insertion_size)}; it not_eq v.rend(); ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + tail_size; ++it) {
                            assert(*it == s);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.crbegin() + tail_size}; it not_eq v.crbegin() + (tail_size + insertion_size); ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        for(auto it {v.crbegin() + (tail_size + insertion_size)}; it not_eq v.crend(); ++it) {
                            assert(*it == s);
                        }
                        for(auto i {0}; i < insertion_position; ++i) {
                            assert(v[i] == s);
                        }
                        string_i = 0;
                        for(auto i {insertion_position}; i < insertion_position + insertion_size; ++i) {
                            assert(v[i] == strings[string_i++]);
                        }
                        for(auto i {insertion_position + insertion_size}; i < v.size(); ++i) {
                            assert(v[i] == s);
                        }
                        assert(result == v.begin() + insertion_position);
                        assert(result == v.cbegin() + insertion_position);
                        std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to random position/With reallocation/Insertion size greater than double capacity done." << std::endl;
                    }

                    std::cout << "\t\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to random position/With reallocation finished!" << std::endl;
                }

                std::cout << "\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to random position finished!" << std::endl;
            }

            // insert to tail
            {
                std::cout << "\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to tail!" << std::endl;

                // without reallocation
                {
                    std::cout << "\t\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to tail/Without reallocation!" << std::endl;

                    // insertion size is zero
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto new_size {this->generate_a_random_number(1, count - 1)};
                        const std::string s {"init"};
                        vector<std::string> v(count, s);
                        destroy(v.first + new_size, v.cursor);
                        v.cursor = v.first + new_size;
                        const auto result {v.insert(new_size, std_string_random_access_iterator {}, std_string_random_access_iterator {})};
                        assert(v.size() == new_size);
                        assert(not v.empty());
                        assert(v.capacity() == count);
                        assert(v.spare() == count - new_size);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + new_size == v.end());
                        assert(v.cbegin() + new_size == v.cend());
                        assert(v.front() == s);
                        assert(v.back() == s);
                        for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                            assert(*it == s);
                        }
                        for(auto i {1}; i < v.size(); ++i) {
                            assert(v[i] == s);
                        }
                        assert(result == v.end());
                        assert(result == v.cend());
                        std::cout << "\t\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to tail/Without reallocation/Insertion size is zero done." << std::endl;
                    }

                    // insertion size less equal to tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        auto insertion_size {this->generate_a_random_number(1, count)};
                        const std::vector<std::string> strings(insertion_size, "init");
                        auto d {this->to_random_access_iterator(strings)};
                        const std::string s {"init"};
                        const auto spare {this->generate_count(count)};
                        vector<std::string> v(count + static_cast<size_t>(insertion_size) + spare, s);
                        destroy(v.cursor - (insertion_size + spare), v.cursor);
                        v.cursor -= insertion_size + spare;
                        const auto result {v.insert(count, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                        assert(v.spare() == spare);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == s);
                        assert(v.back() == strings.back());
                        auto string_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                            assert(*it == s);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                            assert(*it == s);
                        }
                        for(auto i {0}; i < count; ++i) {
                            assert(v[i] == s);
                        }
                        string_i = 0;
                        for(auto i {count}; i < count + insertion_size; ++i) {
                            assert(v[i] == strings[string_i++]);
                        }
                        assert(result == v.begin() + count);
                        assert(result == v.cbegin() + count);
                        std::cout << "\t\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to tail/Without reallocation/Insertion size less equal to tail size done." << std::endl;
                    }

                    // insertion size greater than tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_size {this->generate_a_random_number(count + 1)};
                        const std::vector<std::string> strings(insertion_size, "init");
                        auto d {this->to_random_access_iterator(strings)};
                        const std::string s {"init"};
                        const auto spare {this->generate_count(count)};
                        vector<std::string> v(count + static_cast<size_t>(insertion_size) + spare, s);
                        destroy(v.cursor - (static_cast<size_t>(insertion_size) + spare), v.cursor);
                        v.cursor -= static_cast<size_t>(insertion_size) + spare;
                        const auto result {v.insert(count, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == count + static_cast<size_t>(insertion_size) + spare);
                        assert(v.spare() == spare);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == s);
                        assert(v.back() == strings.back());
                        auto string_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                            assert(*it == s);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                            assert(*it == s);
                        }
                        for(auto i {0}; i < count; ++i) {
                            assert(v[i] == s);
                        }
                        string_i = 0;
                        for(auto i {count}; i < count + insertion_size; ++i) {
                            assert(v[i] == strings[string_i++]);
                        }
                        assert(result == v.begin() + count);
                        assert(result == v.cbegin() + count);
                        std::cout << "\t\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to tail/Without reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    std::cout << "\t\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to tail/Without reallocation finished!" << std::endl;
                }

                // with reallocation
                {
                    std::cout << "\t\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to tail/With reallocation!" << std::endl;

                    // insertion size less equal to tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        auto insertion_size {this->generate_a_random_number(1, count)};
                        const std::vector<std::string> strings(insertion_size, "init");
                        auto d {this->to_random_access_iterator(strings)};
                        const std::string s {"init"};
                        vector<std::string> v(count, s);
                        const auto result {v.insert(count, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                            assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                            assert(v.spare() == 0);
                        }else {
                            assert(v.capacity() == static_cast<size_t>(count) * 2);
                            assert(v.spare() == count - insertion_size);
                        }
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == s);
                        assert(v.back() == strings.back());
                        auto string_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                            assert(*it == s);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                            assert(*it == s);
                        }
                        for(auto i {0}; i < count; ++i) {
                            assert(v[i] == s);
                        }
                        string_i = 0;
                        for(auto i {count}; i < count + insertion_size; ++i) {
                            assert(v[i] == strings[string_i++]);
                        }
                        assert(result == v.begin() + count);
                        assert(result == v.cbegin() + count);
                        std::cout << "\t\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to tail/With reallocation/Insertion size less equal to tail size done." << std::endl;
                    }

                    // insertion size greater than tail size
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto insertion_size {this->generate_a_random_number(count + 1)};
                        const std::vector<std::string> strings(insertion_size, "init");
                        auto d {this->to_random_access_iterator(strings)};
                        const std::string s {"init"};
                        vector<std::string> v(count, s);
                        const auto result {v.insert(count, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        if(static_cast<size_t>(insertion_size) + count > static_cast<size_t>(count) * 2) {
                            assert(v.capacity() == count + static_cast<size_t>(insertion_size));
                            assert(v.spare() == 0);
                        }else {
                            assert(v.capacity() == static_cast<size_t>(count) * 2);
                            assert(v.spare() == count - insertion_size);
                        }
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == s);
                        assert(v.back() == strings.back());
                        auto string_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                            assert(*it == s);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                            assert(*it == s);
                        }
                        for(auto i {0}; i < count; ++i) {
                            assert(v[i] == s);
                        }
                        string_i = 0;
                        for(auto i {count}; i < count + insertion_size; ++i) {
                            assert(v[i] == strings[string_i++]);
                        }
                        assert(result == v.begin() + count);
                        assert(result == v.cbegin() + count);
                        std::cout << "\t\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to tail/With reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    // insertion size less equal to double capacity
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        auto insertion_size {this->generate_a_random_number(1, count)};
                        const std::vector<std::string> strings(insertion_size, "init");
                        auto d {this->to_random_access_iterator(strings)};
                        const std::string s {"init"};
                        vector<std::string> v(count, s);
                        auto result {v.insert(count, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == static_cast<size_t>(count) * 2);
                        assert(v.spare() == count - insertion_size);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == s);
                        assert(v.back() == strings.back());
                        auto string_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                            assert(*it == s);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                            assert(*it == s);
                        }
                        for(auto i {0}; i < count; ++i) {
                            assert(v[i] == s);
                        }
                        string_i = 0;
                        for(auto i {count}; i < count + insertion_size; ++i) {
                            assert(v[i] == strings[string_i++]);
                        }
                        assert(result == v.begin() + count);
                        assert(result == v.cbegin() + count);
                        std::cout << "\t\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to tail/With reallocation/Insertion size less equal to double capacity done." << std::endl;
                    }

                    // insertion size greater than double capacity
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        auto insertion_size {this->generate_a_random_number(2 * count + 1)};
                        const std::vector<std::string> strings(insertion_size, "init");
                        auto d {this->to_random_access_iterator(strings)};
                        const std::string s {"init"};
                        vector<std::string> v(count, s);
                        auto result {v.insert(count, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(v.size() == count + static_cast<size_t>(insertion_size));
                        assert(not v.empty());
                        assert(v.capacity() == static_cast<size_t>(count) + insertion_size);
                        assert(v.spare() == 0);
                        assert(v.data() not_eq nullptr);
                        assert(v.begin() + (count + static_cast<size_t>(insertion_size)) == v.end());
                        assert(v.cbegin() + (count + static_cast<size_t>(insertion_size)) == v.cend());
                        assert(v.front() == s);
                        assert(v.back() == strings.back());
                        auto string_i {0uz};
                        for(auto it {v.begin()}; it not_eq v.begin() + count; ++it) {
                            assert(*it == s);
                        }
                        for(auto it {v.begin() + count}; it not_eq v.end(); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {v.cbegin()}; it not_eq v.cbegin() + count; ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        for(auto it {v.cbegin() + count}; it not_eq v.cend(); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.rbegin()}; it not_eq v.rbegin() + insertion_size; ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        for(auto it {v.rbegin() + insertion_size}; it not_eq v.rend(); ++it) {
                            assert(*it == s);
                        }
                        string_i = insertion_size - 1;
                        for(auto it {v.crbegin()}; it not_eq v.crbegin() + insertion_size; ++it) {
                            assert(*it == strings[string_i--]);
                        }
                        for(auto it {v.crbegin() + insertion_size}; it not_eq v.crend(); ++it) {
                            assert(*it == s);
                        }
                        for(auto i {0}; i < count; ++i) {
                            assert(v[i] == s);
                        }
                        string_i = 0;
                        for(auto i {count}; i < count + insertion_size; ++i) {
                            assert(v[i] == strings[string_i++]);
                        }
                        assert(result == v.begin() + count);
                        assert(result == v.cbegin() + count);
                        std::cout << "\t\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to tail/With reallocation/Insertion size greater than double capacity done." << std::endl;
                    }

                    std::cout << "\t\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to tail/With reallocation finished!" << std::endl;
                }

                std::cout << "\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector/Insert to tail finished!" << std::endl;
            }

            std::cout << "\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty vector finished!" << std::endl;
        }

        std::cout << "\t\tChecking test_insert3/Random access iterator for ds::vector finished!" << std::endl;
    }

    // iterator erase(size_type, size_type)
    {
        std::cout << "\tStart checking test_non_trivial/iterator erase(size_type, size_type) for ds::vector!" << std::endl;

        // erase from head
        {
            std::cout << "\t\tStart checking test_non_trivial/iterator erase(size_type, size_type)/Erase from head for ds::vector!" << std::endl;

            // erasion size is zero
            {
                std::cout << "\t\t\tStart checking test_non_trivial/iterator erase(size_type, size_type)/Erase from head/Erasion size is zero for ds::vector!" << std::endl;

                // empty
                {
                    vector<std::string> v {};
                    auto result {v.erase(0, 0)};
                    assert(v.size() == 0);
                    assert(v.empty());
                    assert(v.capacity() == 0);
                    assert(v.spare() == 0);
                    assert(v.begin() == v.end());
                    assert(v.cbegin() == v.cend());
                    assert(v.rbegin() == v.rend());
                    assert(v.crbegin() == v.crend());
                    assert(v.crbegin() == v.crend());
                    assert(v.data() == nullptr);
                    assert(result == v.begin());
                    assert(result == v.cbegin());
                    assert(result == v.end());
                    assert(result == v.cend());
                    std::cout << "\t\t\t\tChecking test_non_trivial/iterator erase(size_type, size_type)/Erase from head/Erasion size is zero/Empty done." << std::endl;
                }

                // non-empty
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    const std::string s {"init"};
                    vector<std::string> v(count, s);
                    auto result {v.erase(0, 0)};
                    assert(v.size() == count);
                    assert(not v.empty());
                    assert(v.capacity() == count);
                    assert(v.spare() == 0);
                    assert(v.data() not_eq nullptr);
                    assert(v.begin() + count == v.end());
                    assert(v.cbegin() + count == v.cend());
                    assert(v.front() == s);
                    assert(v.back() == s);
                    for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                        assert(*it == s);
                    }
                    for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                        assert(*it == s);
                    }
                    for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                        assert(*it == s);
                    }
                    for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                        assert(*it == s);
                    }
                    for(auto i {0}; i < v.size(); ++i) {
                        assert(v[i] == s);
                    }
                    assert(result == v.begin());
                    assert(result == v.cbegin());
                    std::cout << "\t\t\t\tChecking test_non_trivial/iterator erase(size_type, size_type)/Erase from head/Erasion size is zero/Non-empty done." << std::endl;
                }

                std::cout << "\t\t\tChecking test_non_trivial/iterator erase(size_type, size_type)/Erase from head/Erasion size is zero for ds::vector finished!" << std::endl;
            }

            // erasion size is random
            {
                auto count {this->generate_count()};
                while(count <= 1) {
                    count = this->generate_count();
                }
                const std::string s {"init"};
                vector<std::string> v(count, s);
                const auto erasion_size {this->generate_a_random_number(1, count - 1)};
                auto result {v.erase(0, erasion_size)};
                assert(v.size() == count - erasion_size);
                assert(not v.empty());
                assert(v.capacity() == count);
                assert(v.spare() == erasion_size);
                assert(v.data() not_eq nullptr);
                assert(v.begin() + (count - erasion_size) == v.end());
                assert(v.cbegin() + (count - erasion_size) == v.cend());
                assert(v.front() == s);
                assert(v.back() == s);
                for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                    assert(*it == s);
                }
                for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                    assert(*it == s);
                }
                for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                    assert(*it == s);
                }
                for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                    assert(*it == s);
                }
                for(auto i {0}; i < count - erasion_size; ++i) {
                    assert(v[i] == s);
                }
                assert(result == v.begin());
                assert(result == v.cbegin());
                std::cout << "\t\t\tChecking test_non_trivial/iterator erase(size_type, size_type)/Erase from head/Erasion size is random done." << std::endl;
            }

            // erase all
            {
                auto count {this->generate_count()};
                while(count <= 1) {
                    count = this->generate_count();
                }
                const std::string s {"init"};
                vector<std::string> v(count, s);
                auto result {v.erase(0, count)};
                assert(v.size() == 0);
                assert(v.empty());
                assert(v.capacity() == count);
                assert(v.spare() == count);
                assert(v.data() not_eq nullptr);
                assert(v.begin() == v.end());
                assert(v.cbegin() == v.cend());
                assert(result == v.begin());
                assert(result == v.cbegin());
                assert(result == v.end());
                assert(result == v.cend());
                std::cout << "\t\t\tChecking test_non_trivial/iterator erase(size_type, size_type)/Erase from head/Erasion all done." << std::endl;
            }

            std::cout << "\t\tChecking test_non_trivial/iterator erase(size_type, size_type)/Erase from head for ds::vector finished!" << std::endl;
        }

        // erase from any position
        {
            std::cout << "\t\tStart checking test_non_trivial/iterator erase(size_type, size_type)/Erase from any position for ds::vector!" << std::endl;

            // erasion size is zero
            {
                auto count {this->generate_count()};
                while(count <= 1) {
                    count = this->generate_count();
                }
                const std::string s {"init"};
                vector<std::string> v(count, s);
                const auto erasion_position {this->generate_a_random_number(1, count - 1)};
                auto result {v.erase(erasion_position, 0)};
                assert(v.size() == count);
                assert(not v.empty());
                assert(v.capacity() == count);
                assert(v.spare() == 0);
                assert(v.data() not_eq nullptr);
                assert(v.begin() + count == v.end());
                assert(v.cbegin() + count == v.cend());
                assert(v.front() == s);
                assert(v.back() == s);
                for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                    assert(*it == s);
                }
                for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                    assert(*it == s);
                }
                for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                    assert(*it == s);
                }
                for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                    assert(*it == s);
                }
                for(auto i {0}; i < v.size(); ++i) {
                    assert(v[i] == s);
                }
                assert(result == v.begin() + erasion_position);
                assert(result == v.cbegin() + erasion_position);
                std::cout << "\t\t\t\tChecking test_non_trivial/iterator erase(size_type, size_type)/Erase from head/Erase from any position/Erasion size is zero done." << std::endl;
            }

            // erasion size is not zero
            {
                auto count {this->generate_count()};
                while(count <= 1) {
                    count = this->generate_count();
                }
                const std::string s {"init"};
                vector<std::string> v(count, s);
                const auto erasion_position {this->generate_a_random_number(1, count - 1)};
                const auto erasion_size {this->generate_a_random_number(1, count - erasion_position)};
                auto result {v.erase(erasion_position, erasion_size)};
                assert(v.size() == count - erasion_size);
                assert(not v.empty());
                assert(v.capacity() == count);
                assert(v.spare() == erasion_size);
                assert(v.data() not_eq nullptr);
                assert(v.begin() + (count - erasion_size) == v.end());
                assert(v.cbegin() + (count - erasion_size) == v.cend());
                assert(v.front() == s);
                assert(v.back() == s);
                for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                    assert(*it == s);
                }
                for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                    assert(*it == s);
                }
                for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                    assert(*it == s);
                }
                for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                    assert(*it == s);
                }
                for(auto i {0}; i < count - erasion_size; ++i) {
                    assert(v[i] == s);
                }
                assert(result == v.begin() + erasion_position);
                assert(result == v.cbegin() + erasion_position);
                std::cout << "\t\t\t\tChecking test_non_trivial/iterator erase(size_type, size_type)/Erase from head/Erase from any position/Erasion size is not zero done." << std::endl;
            }

            // erase to tail
            {
                auto count {this->generate_count()};
                while(count <= 1) {
                    count = this->generate_count();
                }
                const std::string s {"init"};
                vector<std::string> v(count, s);
                const auto erasion_position {this->generate_a_random_number(1, count - 1)};
                auto result {v.erase(erasion_position, count - erasion_position)};
                assert(v.size() == erasion_position);
                assert(not v.empty());
                assert(v.capacity() == count);
                assert(v.spare() == count - erasion_position);
                assert(v.data() not_eq nullptr);
                assert(v.begin() + erasion_position == v.end());
                assert(v.cbegin() + erasion_position == v.cend());
                assert(v.front() == s);
                assert(v.back() == s);
                for(auto it {v.begin()}; it not_eq v.end(); ++it) {
                    assert(*it == s);
                }
                for(auto it {v.cbegin()}; it not_eq v.cend(); ++it) {
                    assert(*it == s);
                }
                for(auto it {v.rbegin()}; it not_eq v.rend(); ++it) {
                    assert(*it == s);
                }
                for(auto it {v.crbegin()}; it not_eq v.crend(); ++it) {
                    assert(*it == s);
                }
                for(auto i {0}; i < erasion_position; ++i) {
                    assert(v[i] == s);
                }
                assert(result == v.begin() + erasion_position);
                assert(result == v.cbegin() + erasion_position);
                std::cout << "\t\t\t\tChecking test_non_trivial/iterator erase(size_type, size_type)/Erase from head/Erase from any position/Erase to tail done." << std::endl;
            }

            std::cout << "\t\tChecking test_non_trivial/iterator erase(size_type, size_type)/Erase from any position for ds::vector finished!" << std::endl;
        }

        std::cout << "\tChecking test_non_trivial/iterator erase(size_type, size_type) for ds::vector finished!" << std::endl;
    }

    std::cout << "Checking non-trivial type for ds::vector finished!" << std::endl;
}