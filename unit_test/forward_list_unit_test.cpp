#include <iostream>
#include "unit_test.hpp"
#include "../source/forward_list.hpp"

using namespace ds;
class forward_list_correctness : public unit_test_correctness {
public:
    ~forward_list_correctness() noexcept override = default;
public:
    void test_default_constructor();
    // forward_list(const Allocator &)
    void test_constructor_1();
    // forward_list(size_type)
    void test_constructor_2();
    // forward_list(size_type, const T &)
    void test_constructor_3();
    // forward_list(InputIterator, InputIterator)
    void test_constructor_4();
};

void forward_list_unit_test() {
    auto correctness {new forward_list_correctness {}};
    correctness->test_default_constructor();
    correctness->test_constructor_1();
    correctness->test_constructor_2();
    correctness->test_constructor_3();
    correctness->test_constructor_4();
    delete correctness;
}

void forward_list_correctness::test_default_constructor() {
    std::cout << "Start checking default constructor for ds::forward_list!" << std::endl;

    // the members which should be nothrow
    {
        forward_list<int> l {};
        const forward_list<int> cl {};
        static_assert(noexcept(forward_list<int> {move(l)}));
        static_assert(noexcept(l = move(l)));
        static_assert(noexcept(l.before_begin()));
        static_assert(noexcept(cl.before_begin()));
        static_assert(noexcept(l.begin()));
        static_assert(noexcept(cl.begin()));
        static_assert(noexcept(l.end()));
        static_assert(noexcept(cl.end()));
        static_assert(noexcept(l.cbefore_begin()));
        static_assert(noexcept(cl.cbefore_begin()));
        static_assert(noexcept(l.cbegin()));
        static_assert(noexcept(l.cend()));
        static_assert(noexcept(l.size()));
        static_assert(noexcept(l.empty()));
        static_assert(noexcept(l.front()));
        static_assert(noexcept(cl.front()));
        static_assert(noexcept(l.allocator()));
        static_assert(noexcept(l.pop_front()));
        static_assert(noexcept(l.clear()));
        static_assert(noexcept(l.swap(declval<forward_list<int> &>())));
        std::cout << "\ttest_default_constructor/Member functions nothrow checking done." << std::endl;
    }

    // empty
    {
        forward_list<int> l {};
        assert(l.size() == 0);
        assert(l.empty());
        assert(l.begin() == l.end());
        assert(l.cbegin() == l.cend());
        std::cout << "\ttest_default_constructor/Empty forward_list checking done." << std::endl;
    }

    std::cout << "Checking default constructor for ds::forward_list finished!" << std::endl;
}
void forward_list_correctness::test_constructor_1() {
    std::cout << "Start checking forward_list(const Allocator &)!" << std::endl;

    // ds::allocator<int>
    {
        forward_list<int> f {allocator<int> {}};
        assert(f.size() == 0);
        assert(f.empty());
        assert(f.begin() == f.end());
        assert(f.cbegin() == f.cend());
        std::cout << "\ttest_constructor_1/Empty forward_list with ds::allocator<int> checking done." << std::endl;
    }

    // std::allocator<int>
    {
        forward_list<int, std::allocator<int>> f {std::allocator<int> {}};
        assert(f.size() == 0);
        assert(f.empty());
        assert(f.begin() == f.end());
        assert(f.cbegin() == f.cend());
        std::cout << "\ttest_constructor_1/Empty forward_list with std::allocator<int> checking done." << std::endl;
    }

    std::cout << "Checking forward_list(const Allocator &) finished!" << std::endl;
}
void forward_list_correctness::test_constructor_2() {
    std::cout << "Start checking forward_list(size_type)!" << std::endl;

    // empty
    {
        forward_list<int> f(0);
        assert(f.size() == 0);
        assert(f.empty());
        assert(f.begin() == f.end());
        assert(f.cbegin() == f.cend());
        std::cout << "\ttest_default_constructor_2/Empty forward_list checking done." << std::endl;
    }

    // random size
    {
        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
        forward_list<int> f(count);
        assert(f.size() == count);
        assert(not f.empty());
        assert(advance(f.begin(), count) == f.end());
        assert(advance(f.cbegin(), count) == f.cend());
        assert(f.front() == 0);
        for(auto it {f.begin()}; it not_eq f.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\ttest_constructor_2/Random count done." << std::endl;
    }

    std::cout << "Checking forward_list(size_type) finished!" << std::endl;
}
void forward_list_correctness::test_constructor_3() {
    std::cout << "Start checking forward_list(size_type, const T &)!" << std::endl;

    // empty
    {
        forward_list<int> f(0, this->generate_a_random_number());
        assert(f.size() == 0);
        assert(f.empty());
        assert(f.begin() == f.end());
        assert(f.cbegin() == f.cend());
        std::cout << "\ttest_default_constructor_3/Empty forward_list checking done." << std::endl;
    }

    // random size
    {
        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
        const auto number {this->generate_a_random_number()};
        forward_list<int> f(count, number);
        assert(f.size() == count);
        assert(not f.empty());
        assert(advance(f.begin(), count) == f.end());
        assert(advance(f.cbegin(), count) == f.cend());
        assert(f.front() == number);
        for(auto it {f.begin()}; it not_eq f.end(); ++it) {
            assert(*it == number);
        }
        for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
            assert(*it == number);
        }
        std::cout << "\ttest_constructor_3/Random count done." << std::endl;
    }

    std::cout << "Checking forward_list(size_type, const T &) finished!" << std::endl;
}
void forward_list_correctness::test_constructor_4() {
    std::cout << "Start checking forward_list(InputIterator, InputIterator)!" << std::endl;

    // empty
    {
        forward_list<int> f(int_input_iterator {}, int_input_iterator {});
        assert(f.size() == 0);
        assert(f.empty());
        assert(f.begin() == f.end());
        assert(f.cbegin() == f.cend());
        std::cout << "\ttest_constructor_4/Empty buffer checking done." << std::endl;
    }

    // random size
    {
        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
        const auto numbers {this->generate_number(count)};
        auto stream {this->to_input_iterator(numbers)};
        forward_list<int> f(int_input_iterator {stream}, {});
        assert(f.size() == count);
        assert(not f.empty());
        assert(f.begin() not_eq f.end());
        assert(advance(f.begin(), count) == f.end());
        assert(f.cbegin() not_eq f.cend());
        assert(advance(f.cbegin(), count) == f.end());
        assert(f.front() == numbers.front());
        auto numbers_i {0uz};
        for(auto it {f.begin()}; it not_eq f.end(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        numbers_i = 0;
        for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        std::cout << "\ttest_constructor_4/Random count done." << std::endl;
    }

    std::cout << "Checking forward_list(InputIterator, InputIterator), size, empty and iterator finished!" << std::endl;
}