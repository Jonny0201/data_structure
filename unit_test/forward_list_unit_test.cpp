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
    // forward_list(size_type, const_reference)
    void test_constructor_3();
    // forward_list(InputIterator, InputIterator)
    void test_constructor_4();
    // forward_list(ForwardIterator, ForwardIterator)
    void test_constructor_5();
    // forward_list(initializer_list<T>)
    void test_constructor_6();
    void test_copy_constructor();
    void test_move_constructor();
    void test_copy_assignment();
    void test_move_assignment();
    // void assign(size_type, const_reference)
    void test_assign_1();
};

void forward_list_unit_test() {
    auto correctness {new forward_list_correctness {}};
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
void forward_list_correctness::test_constructor_5() {
    std::cout << "Start checking forward_list(ForwardIterator, ForwardIterator)!" << std::endl;

    // forward iterator
    {
        std::cout << "\tStart checking forward_iterator version!" << std::endl;

        // empty
        {
            forward_list<int> f(int_forward_iterator {}, {});
            assert(f.size() == 0);
            assert(f.empty());
            assert(f.begin() == f.end());
            assert(f.cbegin() == f.cend());
            std::cout << "\t\ttest_constructor_5/forward iterator/Empty forward_list checking done." << std::endl;
        }

        // random size
        {
            auto count {this->generate_count()};
            while(count == 0) {
                count = this->generate_count();
            }
            const auto numbers {this->generate_number(count)};
            auto l {this->to_forward_iterator(numbers)};
            forward_list<int> f(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
            assert(f.size() == count);
            assert(not f.empty());
            assert(f.begin() not_eq f.end());
            assert(advance(f.begin(), count) == f.end());
            assert(f.cbegin() not_eq f.cend());
            assert(advance(f.cbegin(), count) == f.cend());
            assert(f.cbegin() not_eq f.end());
            assert(advance(f.cbegin(), count) == f.end());
            assert(f.begin() not_eq f.cend());
            assert(advance(f.begin(), count) == f.cend());
            assert(*f.begin() == *numbers.begin());
            assert(f.front() == numbers.front());
            auto numbers_i {0uz};
            for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
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
            forward_list<int> f(int_bidirectional_iterator {}, {});
            assert(f.size() == 0);
            assert(f.empty());
            assert(f.begin() == f.end());
            assert(f.cbegin() == f.cend());
            std::cout << "\t\ttest_constructor_5/bidirectional iterator/Empty forward_list checking done." << std::endl;
        }

        // random size
        {
            auto count {this->generate_count()};
            while(count == 0) {
                count = this->generate_count();
            }
            const auto numbers {this->generate_number(count)};
            auto l {this->to_bidirectional_iterator(numbers)};
            forward_list<int> f(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
            assert(f.size() == count);
            assert(not f.empty());
            assert(f.begin() not_eq f.end());
            assert(advance(f.begin(), count) == f.end());
            assert(f.cbegin() not_eq f.cend());
            assert(advance(f.cbegin(), count) == f.cend());
            assert(f.cbegin() not_eq f.end());
            assert(advance(f.cbegin(), count) == f.end());
            assert(f.begin() not_eq f.cend());
            assert(advance(f.begin(), count) == f.cend());
            assert(*f.begin() == *numbers.begin());
            assert(f.front() == numbers.front());
            auto numbers_i {0uz};
            for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
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
            forward_list<int> f(int_random_access_iterator {}, {});
            assert(f.size() == 0);
            assert(f.empty());
            assert(f.begin() == f.end());
            assert(f.cbegin() == f.cend());
            std::cout << "\t\ttest_constructor_5/random access iterator/Empty forward_list checking done." << std::endl;
        }

        // random size
        {
            auto count {this->generate_count()};
            while(count == 0) {
                count = this->generate_count();
            }
            const auto numbers {this->generate_number(count)};
            auto d {this->to_random_access_iterator(numbers)};
            forward_list<int> f(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
            assert(f.size() == count);
            assert(not f.empty());
            assert(f.begin() not_eq f.end());
            assert(advance(f.begin(), count) == f.end());
            assert(f.cbegin() not_eq f.cend());
            assert(advance(f.cbegin(), count) == f.cend());
            assert(f.cbegin() not_eq f.end());
            assert(advance(f.cbegin(), count) == f.end());
            assert(f.begin() not_eq f.cend());
            assert(advance(f.begin(), count) == f.cend());
            assert(*f.begin() == *numbers.begin());
            assert(f.front() == numbers.front());
            auto numbers_i {0uz};
            for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            std::cout << "\t\ttest_constructor_5/Random access iterator/Random count done." << std::endl;
        }
        std::cout << "\tChecking bidirectional iterator version finished!" << std::endl;
    }

    std::cout << "Checking forward_list(ForwardIterator, ForwardIterator) finished!" << std::endl;
}
void forward_list_correctness::test_constructor_6() {
    std::cout << "Start checking forward_list(initializer_list<T>)!" << std::endl;

    const std::initializer_list<int> empty_list = {};
    const auto single_list = {42};
    const auto list = {-5, -2, 0, 1, 4, 6, 8, 111};

    // empty from initializer_list
    {
        forward_list<int> f1(empty_list);
        assert(f1.size() == 0);
        assert(f1.empty());
        assert(f1.begin() == f1.end());
        assert(f1.cbegin() == f1.cend());

        forward_list<int> f2({});
        assert(f2.size() == 0);
        assert(f2.empty());
        assert(f2.begin() == f2.end());
        assert(f2.cbegin() == f2.cend());
        std::cout << "\ttest_constructor_6/Empty forward_list from initializer_list checking done." << std::endl;
    }

    // single element
    {
        forward_list<int> f1 {42};
        assert(f1.size() == 1);
        assert(not f1.empty());
        assert(f1.begin() not_eq f1.end());
        assert(advance(f1.begin(), 1) == f1.end());
        assert(*f1.begin() == 42);
        assert(*f1.cbegin()== 42);
        assert(f1.front() == 42);

        forward_list<int> f2(single_list);
        assert(f2.size() == 1);
        assert(not f2.empty());
        assert(f2.begin() not_eq f2.end());
        assert(advance(f2.begin(), 1) == f2.end());
        assert(*f2.begin() == 42);
        assert(*f2.cbegin() == 42);
        assert(f2.front() == 42);
        std::cout << "\ttest_constructor_6/Single element forward_list checking done." << std::endl;
    }

    // other test
    {
        forward_list<int> f(list);
        assert(f.size() == 8);
        assert(not f.empty());
        assert(advance(f.begin(), 8) == f.end());
        assert(advance(f.cbegin(), 8) == f.cend());
        assert(*f.begin() == -5);
        assert(*f.cbegin() == -5);
        assert(f.front() == -5);
        for(auto i {0}; i < list.size(); ++i) {
            assert(*advance(f.begin(), i) == *(list.begin() + i));
        }
        std::cout << "\ttest_constructor_6/forward_list other test checking done." << std::endl;
    }

    std::cout << "Checking forward_list(initializer_list<T>) finished!" << std::endl;
}
void forward_list_correctness::test_copy_constructor() {
    std::cout << "Start checking copy constructor!" << std::endl;

    // empty
    {
        forward_list<int> f0(0);
        auto f {f0};
        assert(f.size() == 0);
        assert(f.empty());
        assert(f.begin() == f.end());
        assert(f.cbegin() == f.cend());
        std::cout << "\ttest_default_copy_constructor/Empty forward_list checking done." << std::endl;
    }

    // random size
    {
        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
        forward_list<int> f0(count);
        auto f {f0};
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
        std::cout << "\ttest_copy_constructor/Random count done." << std::endl;
    }

    std::cout << "Checking copy constructor finished!" << std::endl;
}
void forward_list_correctness::test_move_constructor() {
    std::cout << "Start checking move constructor!" << std::endl;

    // empty
    {
        forward_list<int> f0(0);
        auto f {move(f0)};
        assert(f0.size() == 0);
        assert(f0.empty());
        assert(f0.begin() == f0.end());
        assert(f0.cbegin() == f0.cend());
        assert(f.size() == 0);
        assert(f.empty());
        assert(f.begin() == f.end());
        assert(f.cbegin() == f.cend());
        std::cout << "\ttest_default_move_constructor/Empty forward_list checking done." << std::endl;
    }

    // random size
    {
        auto size {this->generate_count()};
        while(size == 0) {
            size = this->generate_count();
        }
        forward_list<int> f0(size);
        auto f {move(f0)};
        assert(f0.size() == 0);
        assert(f0.empty());
        assert(f0.begin() == f0.end());
        assert(f0.cbegin() == f0.cend());
        assert(f.size() == size);
        assert(not f.empty());
        assert(advance(f.begin(), size) == f.end());
        assert(advance(f.cbegin(), size) == f.cend());
        assert(f.front() == 0);
        for(auto it {f.begin()}; it not_eq f.end(); ++it) {
            assert(*it == 0);
        }
        for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
            assert(*it == 0);
        }
        std::cout << "\ttest_move_constructor/Random size done." << std::endl;
    }

    std::cout << "Checking move constructor finished!" << std::endl;
}
void forward_list_correctness::test_copy_assignment() {
    std::cout << "Start checking copy assignment for ds::forward_list!" << std::endl;

    // empty
    {
        forward_list<int> f0(0);
        forward_list<int> f {};
        f = f0;
        bool rechecked {};
        RECHECK_EMPTY : assert(f.size() == 0);
        assert(f.empty());
        assert(f.begin() == f.end());
        assert(f.cbegin() == f.cend());
        if(not rechecked) {
            f = f;
            rechecked = true;
            goto RECHECK_EMPTY;
        }
        std::cout << "\ttest_default_copy_assignment/Empty forward_list checking done." << std::endl;
    }

    // random size
    {
        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
        forward_list<int> f0(count);
        forward_list<int> f {};
        f = f0;
        bool rechecked {};
        RECHECK_RANDOM : assert(f.size() == count);
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
        if(not rechecked) {
            f = f;
            rechecked = true;
            goto RECHECK_RANDOM;
        }
        std::cout << "\ttest_copy_assignment/Random sized elements done." << std::endl;
    }

    std::cout << "Checking copy assignment for ds::forward_list finished!" << std::endl;
}
void forward_list_correctness::test_move_assignment() {
    std::cout << "Start checking move assignment for ds::forward_list!" << std::endl;

    // empty
    {
        forward_list<int> f0(0);
        forward_list<int> f {};
        f = move(f0);
        bool rechecked {};
        assert(f0.size() == 0);
        assert(f0.empty());
        assert(f0.begin() == f0.end());
        assert(f0.cbegin() == f0.cend());
        RECHECK_EMPTY : assert(f.size() == 0);
        assert(f.empty());
        assert(f.begin() == f.end());
        assert(f.cbegin() == f.cend());
        if(not rechecked) {
            f = move(f);
            rechecked = true;
            goto RECHECK_EMPTY;
        }
        std::cout << "\tChecking test_move_assignment/Empty forward_list checking done." << std::endl;
    }

    // random size
    {
        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
        forward_list<int> f0(count);
        forward_list<int> f {};
        f = move(f0);
        bool rechecked {};
        assert(f0.size() == 0);
        assert(f0.empty());
        assert(f0.begin() == f0.end());
        assert(f0.cbegin() == f0.cend());
        RECHECK_RANDOM : assert(f.size() == count);
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
        if(not rechecked) {
            f = move(f);
            rechecked = true;
            goto RECHECK_RANDOM;
        }
        std::cout << "\tChecking test_move_assignment/Random count done." << std::endl;
    }

    std::cout << "Checking move assignment for ds::forward_list finished!" << std::endl;
}
void forward_list_correctness::test_assign_1() {
    std::cout << "Start checking void assign(size_type, const_reference) for forward_list!" << std::endl;

    // empty forward_list to non-empty forward_list
    {
        forward_list<int> f {};
        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
        const auto number {this->generate_a_random_number()};
        f.assign(count, number);
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
        std::cout << "\ttest_assign_1/Empty forward_list to non-empty forward_list done." << std::endl;
    }

    // non-empty forward_list to empty forward_list
    {
        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
        forward_list<int> f(count);
        f.assign(0);
        assert(f.size() == 0);
        assert(f.empty());
        assert(f.begin() == f.end());
        assert(f.cbegin() == f.cend());
        std::cout << "\ttest_assign_1/Non-empty forward_list to forward_list done." << std::endl;
    }

    // non-empty forward_list with assigning size greater than capacity
    {
        auto count {this->generate_count()};
        while(count <= 5) {
            count = this->generate_count();
        }
        const auto number {this->generate_a_random_number()};
        forward_list<int> f(5);
        f.assign(count, number);
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
        std::cout << "\ttest_assign_1/Non-empty forward_list with assigning size greater than capacity done." << std::endl;
    }

    // non-empty forward_list with assigning size less than capacity
    {
        std::cout << "\tStart checking test_assign_1/Non-empty forward_list with assigning size less than capacity!" << std::endl;

        // greater than size
        {
            auto count {this->generate_count()};
            while(count <= 1) {
                count = this->generate_count();
            }
            count = 7;
            const auto offset {count / 2};
            const auto real_size {count - offset};
            forward_list<int> f(count);
            auto erasion {&f.head};
            for(auto i {real_size};; erasion = erasion->next) {
                if(i-- == 0) {
                    auto backup {erasion->next};
                    erasion->next = nullptr;
                    f.node_size.allocator().deallocate(backup->node(), offset);
                    f.node_size() = real_size;
                    break;
                }
            }
            auto new_size {this->generate_a_random_number(real_size + 1, count)};
            const auto number {this->generate_a_random_number()};
            new_size = 5;
            f.assign(new_size, number);
            assert(f.size() == new_size);
            assert(not f.empty());
            assert(advance(f.begin(), new_size) == f.end());
            assert(advance(f.cbegin(), new_size) == f.cend());
            assert(f.front() == number);
            for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                assert(*it == number);
            }
            for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                assert(*it == number);
            }
            std::cout << "\t\ttest_assign_1/Non-empty forward_list with assigning size less than capacity/Greater than size done." << std::endl;
        }

        // less than size
        {
            auto count {this->generate_count()};
            while(count <= 1) {
                count = this->generate_count();
            }
            forward_list<int> f(count);
            auto new_size {this->generate_a_random_number(1, count - 1)};
            auto erasion {&f.head};
            for(auto i {new_size};; erasion = erasion->next) {
                if(i-- == 0) {
                    auto backup {erasion->next};
                    erasion->next = nullptr;
                    f.node_size.allocator().deallocate(backup->node(), count - new_size);
                    f.node_size() = new_size;
                    break;
                }
            }
            const auto number {this->generate_a_random_number()};
            f.assign(new_size, number);
            assert(f.size() == new_size);
            assert(not f.empty());
            assert(advance(f.begin(), new_size) == f.end());
            assert(advance(f.cbegin(), new_size) == f.cend());
            assert(f.front() == number);
            for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                assert(*it == number);
            }
            for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                assert(*it == number);
            }
            std::cout << "\t\ttest_assign_1/Non-empty forward_list with assigning size less than capacity/Less than size done." << std::endl;
        }

        // equal to size
        {
            auto count {this->generate_count()};
            while(count == 0) {
                count = this->generate_count();
            }
            forward_list<int> f(count);
            const auto number {this->generate_a_random_number()};
            f.assign(count, number);
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
            std::cout << "\t\ttest_assign_1/Non-empty forward_list with assigning size less than capacity/Equal to size done." << std::endl;
        }

        std::cout << "\tChecking test_assign_1/Non-empty forward_list with assigning size less than capacity finished!" << std::endl;
    }

    std::cout << "Checking void assign(size_type, const_reference) for forward_list finished!" << std::endl;
}