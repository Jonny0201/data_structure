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
    // void assign(InputIterator, InputIterator)
    void test_assign_2();
    // void assign(ForwardIterator, ForwardIterator)
    void test_assign_3();
    // void resize(size_type)
    void test_resize_1();
    // void resize(size_type, const_reference)
    void test_resize_2();
    void test_emplace_front();
    void test_pop_front();
    void test_clear();
    void test_swap();
    void test_emplace_after();
    // iterator insert_after(const_iterator, const_reference, size_type)
    void test_insert_after_1();
    // iterator insert_after(const_iterator, InputIterator, InputIterator)
    void test_insert_after_2();
    // iterator insert_after(const_iterator, ForwardIterator, ForwardIterator)
    void test_insert_after_3();
    void test_erase();
    void test_allocator();
    void test_non_trivial();
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
    correctness->test_assign_2();
    correctness->test_assign_3();
    correctness->test_emplace_front();
    correctness->test_pop_front();
    correctness->test_clear();
    correctness->test_emplace_after();
    correctness->test_insert_after_1();
    correctness->test_insert_after_2();
    correctness->test_insert_after_3();
    correctness->test_erase();
    correctness->test_allocator();
    correctness->test_non_trivial();
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
        while(count <= 42) {
            count = this->generate_count();
        }
        const auto number {this->generate_a_random_number()};
        forward_list<int> f(42);
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
void forward_list_correctness::test_assign_2() {
    std::cout << "Start checking void assign(InputIterator, InputIterator) for forward_list!" << std::endl;

    // empty forward_list to non-empty forward_list
    {
        forward_list<int> f {};
        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
        const auto numbers {this->generate_number(count)};
        auto stream {this->to_input_iterator(numbers)};
        f.assign(int_input_iterator {stream}, int_input_iterator {});
        assert(f.size() == count);
        assert(not f.empty());
        assert(advance(f.begin(), count) == f.end());
        assert(advance(f.cbegin(), count) == f.cend());
        assert(f.front() == numbers[0]);
        auto numbers_i {0uz};
        for(auto it {f.begin()}; it not_eq f.end(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        numbers_i = 0;
        for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        std::cout << "\ttest_assign_2/Empty forward_list to non-empty forward_list done." << std::endl;
    }

    // non-empty forward_list to empty forward_list
    {
        const auto count {this->generate_count()};
        forward_list<int> f(count);
        f.assign(int_input_iterator {}, int_input_iterator {});
        assert(f.size() == 0);
        assert(f.empty());
        assert(f.begin() == f.end());
        assert(f.cbegin() == f.cend());
        std::cout << "\ttest_assign_2/Non-empty forward_list to forward_list done." << std::endl;
    }

    // non-empty forward_list with assigning size greater than capacity
    {
        auto count {this->generate_count()};
        while(count <= 42) {
            count = this->generate_count();
        }
        const auto numbers {this->generate_number(count)};
        auto stream {this->to_input_iterator(numbers)};
        forward_list<int> f(42);
        f.assign(int_input_iterator {stream}, int_input_iterator {});
        assert(f.size() == count);
        assert(not f.empty());
        assert(advance(f.begin(), count) == f.end());
        assert(advance(f.cbegin(), count) == f.cend());
        assert(f.front() == numbers[0]);
        auto numbers_i {0uz};
        for(auto it {f.begin()}; it not_eq f.end(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        numbers_i = 0;
        for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
            assert(*it == numbers[numbers_i++]);
        }
        std::cout << "\ttest_assign_2/Non-empty forward_list with assigning size greater than capacity done." << std::endl;
    }

    // non-empty forward_list with assigning size less than capacity
    {
        std::cout << "\tStart checking test_assign_2/Non-empty forward_list with assigning size less than capacity!" << std::endl;

        // greater than size
        {
            auto count {this->generate_count()};
            while(count <= 1) {
                count = this->generate_count();
            }
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
            const auto new_size {this->generate_a_random_number(real_size + 1, count)};
            const auto numbers {this->generate_number(new_size)};
            auto stream {this->to_input_iterator(numbers)};
            f.assign(int_input_iterator {stream}, int_input_iterator {});
            assert(f.size() == new_size);
            assert(not f.empty());
            assert(advance(f.begin(), new_size) == f.end());
            assert(advance(f.cbegin(), new_size) == f.cend());
            assert(f.front() == numbers[0]);
            auto numbers_i {0uz};
            for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            std::cout << "\t\ttest_assign_2/Non-empty forward_list with assigning size less than capacity/Greater than size done." << std::endl;
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
            const auto numbers {this->generate_number(new_size)};
            auto stream {this->to_input_iterator(numbers)};
            f.assign(int_input_iterator {stream}, int_input_iterator {});
            assert(f.size() == new_size);
            assert(not f.empty());
            assert(advance(f.begin(), new_size) == f.end());
            assert(advance(f.cbegin(), new_size) == f.cend());
            assert(f.front() == numbers[0]);
            auto numbers_i {0uz};
            for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            std::cout << "\t\ttest_assign_2/Non-empty forward_list with assigning size less than capacity/Less than size done." << std::endl;
        }

        // equal to size
        {
            auto count {this->generate_count()};
            while(count == 0) {
                count = this->generate_count();
            }
            forward_list<int> f(count);
            const auto numbers {this->generate_number(count)};
            auto stream {this->to_input_iterator(numbers)};
            f.assign(int_input_iterator {stream}, int_input_iterator {});
            assert(f.size() == count);
            assert(not f.empty());
            assert(advance(f.begin(), count) == f.end());
            assert(advance(f.cbegin(), count) == f.cend());
            assert(f.front() == numbers[0]);
            auto numbers_i {0uz};
            for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            std::cout << "\t\ttest_assign_2/Non-empty forward_list with assigning size less than capacity/Equal to size done." << std::endl;
        }

        std::cout << "\tChecking test_assign_2/Non-empty forward_list with assigning size less than capacity finished!" << std::endl;
    }

    std::cout << "Checking void assign(InputIterator, InputIterator) for forward_list finished!" << std::endl;
}
void forward_list_correctness::test_assign_3() {
    std::cout << "Start checking void assign(ForwardIterator, ForwardIterator) for forward_list!" << std::endl;

    // forward iterator
    {
        std::cout << "\tStart checking test_assign_3/Forward iterator for forward_list!" << std::endl;

        // empty forward_list to non-empty forward_list
        {
            forward_list<int> f {};
            auto count {this->generate_count()};
            while(count == 0) {
                count = this->generate_count();
            }
            const auto numbers {this->generate_number(count)};
            auto l {this->to_forward_iterator(numbers)};
            f.assign(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
            assert(f.size() == count);
            assert(not f.empty());
            assert(advance(f.begin(), count) == f.end());
            assert(advance(f.cbegin(), count) == f.cend());
            assert(f.front() == numbers[0]);
            auto numbers_i {0uz};
            for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            std::cout << "\t\ttest_assign_3/Empty forward_list to non-empty forward_list done." << std::endl;
        }

        // non-empty forward_list to empty forward_list
        {
            auto count {this->generate_count()};
            while(count == 0) {
                count = this->generate_count();
            }
            forward_list<int> f(count);
            f.assign(int_forward_iterator {}, int_forward_iterator {});
            assert(f.size() == 0);
            assert(f.empty());
            assert(f.begin() == f.end());
            assert(f.cbegin() == f.cend());
            std::cout << "\t\ttest_assign_3/Non-empty forward_list to forward_list done." << std::endl;
        }

        // non-empty forward_list with assigning size greater than capacity
        {
            auto count {this->generate_count()};
            while(count <= 42) {
                count = this->generate_count();
            }
            const auto numbers {this->generate_number(count)};
            auto l {this->to_forward_iterator(numbers)};
            forward_list<int> f(42);
            f.assign(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
            assert(f.size() == count);
            assert(not f.empty());
            assert(advance(f.begin(), count) == f.end());
            assert(advance(f.cbegin(), count) == f.cend());
            assert(f.front() == numbers[0]);
            auto numbers_i {0uz};
            for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            std::cout << "\t\ttest_assign_3/Non-empty forward_list with assigning size greater than capacity done." << std::endl;
        }

        // non-empty forward_list with assigning size less than capacity
        {
            std::cout << "\t\tStart checking test_assign_3/Non-empty forward_list with assigning size less than capacity!" << std::endl;

            // greater than size
            {
                auto count {this->generate_count()};
                while(count <= 1) {
                    count = this->generate_count();
                }
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
                const auto new_size {this->generate_a_random_number(real_size + 1, count)};
                const auto numbers {this->generate_number(new_size)};
                auto l {this->to_forward_iterator(numbers)};
                f.assign(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
                assert(f.size() == new_size);
                assert(not f.empty());
                assert(advance(f.begin(), new_size) == f.end());
                assert(advance(f.cbegin(), new_size) == f.cend());
                assert(f.front() == numbers[0]);
                auto numbers_i {0uz};
                for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                std::cout << "\t\t\ttest_assign_3/Non-empty forward_list with assigning size less than capacity/Greater than size done." << std::endl;
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
                const auto numbers {this->generate_number(new_size)};
                auto l {this->to_forward_iterator(numbers)};
                f.assign(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
                assert(f.size() == new_size);
                assert(not f.empty());
                assert(advance(f.begin(), new_size) == f.end());
                assert(advance(f.cbegin(), new_size) == f.cend());
                assert(f.front() == numbers[0]);
                auto numbers_i {0uz};
                for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                std::cout << "\t\t\ttest_assign_3/Non-empty forward_list with assigning size less than capacity/Less than size done." << std::endl;
            }

            // equal to size
            {
                auto count {this->generate_count()};
                while(count == 0) {
                    count = this->generate_count();
                }
                forward_list<int> f(count);
                const auto numbers {this->generate_number(count)};
                auto l {this->to_forward_iterator(numbers)};
                f.assign(int_forward_iterator {l.begin()}, int_forward_iterator {l.end()});
                assert(f.size() == count);
                assert(not f.empty());
                assert(advance(f.begin(), count) == f.end());
                assert(advance(f.cbegin(), count) == f.cend());
                assert(f.front() == numbers[0]);
                auto numbers_i {0uz};
                for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                std::cout << "\t\t\ttest_assign_3/Non-empty forward_list with assigning size less than capacity/Equal to size done." << std::endl;
            }

            std::cout << "\t\tChecking test_assign_3/Non-empty forward_list with assigning size less than capacity finished!" << std::endl;
        }

        std::cout << "\tChecking test_assign3/Forward iterator for forward_list finished!" << std::endl;
    }

    // bidirectional iterator
    {
        std::cout << "\tStart checking test_assign_3/Bidirectional iterator for forward_list!" << std::endl;

        // empty forward_list to non-empty forward_list
        {
            forward_list<int> f {};
            auto count {this->generate_count()};
            while(count == 0) {
                count = this->generate_count();
            }
            const auto numbers {this->generate_number(count)};
            auto l {this->to_bidirectional_iterator(numbers)};
            f.assign(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
            assert(f.size() == count);
            assert(not f.empty());
            assert(advance(f.begin(), count) == f.end());
            assert(advance(f.cbegin(), count) == f.cend());
            assert(f.front() == numbers[0]);
            auto numbers_i {0uz};
            for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            std::cout << "\t\ttest_assign_3/Empty forward_list to non-empty forward_list done." << std::endl;
        }

        // non-empty forward_list to empty forward_list
        {
            auto count {this->generate_count()};
            while(count == 0) {
                count = this->generate_count();
            }
            forward_list<int> f(count);
            f.assign(int_bidirectional_iterator {}, int_bidirectional_iterator {});
            assert(f.size() == 0);
            assert(f.empty());
            assert(f.begin() == f.end());
            assert(f.cbegin() == f.cend());
            std::cout << "\t\ttest_assign_3/Non-empty forward_list to forward_list done." << std::endl;
        }

        // non-empty forward_list with assigning size greater than capacity
        {
            auto count {this->generate_count()};
            while(count <= 42) {
                count = this->generate_count();
            }
            const auto numbers {this->generate_number(count)};
            auto l {this->to_bidirectional_iterator(numbers)};
            forward_list<int> f(42);
            f.assign(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
            assert(f.size() == count);
            assert(not f.empty());
            assert(advance(f.begin(), count) == f.end());
            assert(advance(f.cbegin(), count) == f.cend());
            assert(f.front() == numbers[0]);
            auto numbers_i {0uz};
            for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            std::cout << "\t\ttest_assign_3/Non-empty forward_list with assigning size greater than capacity done." << std::endl;
        }

        // non-empty forward_list with assigning size less than capacity
        {
            std::cout << "\t\tStart checking test_assign_3/Non-empty forward_list with assigning size less than capacity!" << std::endl;

            // greater than size
            {
                auto count {this->generate_count()};
                while(count <= 1) {
                    count = this->generate_count();
                }
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
                const auto new_size {this->generate_a_random_number(real_size + 1, count)};
                const auto numbers {this->generate_number(new_size)};
                auto l {this->to_bidirectional_iterator(numbers)};
                f.assign(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
                assert(f.size() == new_size);
                assert(not f.empty());
                assert(advance(f.begin(), new_size) == f.end());
                assert(advance(f.cbegin(), new_size) == f.cend());
                assert(f.front() == numbers[0]);
                auto numbers_i {0uz};
                for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                std::cout << "\t\t\ttest_assign_3/Non-empty forward_list with assigning size less than capacity/Greater than size done." << std::endl;
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
                const auto numbers {this->generate_number(new_size)};
                auto l {this->to_bidirectional_iterator(numbers)};
                f.assign(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
                assert(f.size() == new_size);
                assert(not f.empty());
                assert(advance(f.begin(), new_size) == f.end());
                assert(advance(f.cbegin(), new_size) == f.cend());
                assert(f.front() == numbers[0]);
                auto numbers_i {0uz};
                for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                std::cout << "\t\t\ttest_assign_3/Non-empty forward_list with assigning size less than capacity/Less than size done." << std::endl;
            }

            // equal to size
            {
                auto count {this->generate_count()};
                while(count == 0) {
                    count = this->generate_count();
                }
                forward_list<int> f(count);
                const auto numbers {this->generate_number(count)};
                auto l {this->to_bidirectional_iterator(numbers)};
                f.assign(int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()});
                assert(f.size() == count);
                assert(not f.empty());
                assert(advance(f.begin(), count) == f.end());
                assert(advance(f.cbegin(), count) == f.cend());
                assert(f.front() == numbers[0]);
                auto numbers_i {0uz};
                for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                std::cout << "\t\t\ttest_assign_3/Non-empty forward_list with assigning size less than capacity/Equal to size done." << std::endl;
            }

            std::cout << "\t\tChecking test_assign_3/Non-empty forward_list with assigning size less than capacity finished!" << std::endl;
        }

        std::cout << "\tChecking test_assign3/Bidirectional iterator for forward_list finished!" << std::endl;
    }

    // random access iterator
    {
        std::cout << "\tStart checking test_assign_3/Random access iterator for forward_list!" << std::endl;

        // empty forward_list to non-empty forward_list
        {
            forward_list<int> f {};
            auto count {this->generate_count()};
            while(count == 0) {
                count = this->generate_count();
            }
            const auto numbers {this->generate_number(count)};
            auto d {this->to_random_access_iterator(numbers)};
            f.assign(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
            assert(f.size() == count);
            assert(not f.empty());
            assert(advance(f.begin(), count) == f.end());
            assert(advance(f.cbegin(), count) == f.cend());
            assert(f.front() == numbers[0]);
            auto numbers_i {0uz};
            for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            std::cout << "\t\ttest_assign_3/Empty forward_list to non-empty forward_list done." << std::endl;
        }

        // non-empty forward_list to empty forward_list
        {
            auto count {this->generate_count()};
            while(count == 0) {
                count = this->generate_count();
            }
            forward_list<int> f(count);
            f.assign(int_random_access_iterator {}, int_random_access_iterator {});
            assert(f.size() == 0);
            assert(f.empty());
            assert(f.begin() == f.end());
            assert(f.cbegin() == f.cend());
            std::cout << "\t\ttest_assign_3/Non-empty forward_list to forward_list done." << std::endl;
        }

        // non-empty forward_list with assigning size greater than capacity
        {
            auto count {this->generate_count()};
            while(count <= 42) {
                count = this->generate_count();
            }
            const auto numbers {this->generate_number(count)};
            auto d {this->to_random_access_iterator(numbers)};
            forward_list<int> f(42);
            f.assign(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
            assert(f.size() == count);
            assert(not f.empty());
            assert(advance(f.begin(), count) == f.end());
            assert(advance(f.cbegin(), count) == f.cend());
            assert(f.front() == numbers[0]);
            auto numbers_i {0uz};
            for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            numbers_i = 0;
            for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                assert(*it == numbers[numbers_i++]);
            }
            std::cout << "\t\ttest_assign_3/Non-empty forward_list with assigning size greater than capacity done." << std::endl;
        }

        // non-empty forward_list with assigning size less than capacity
        {
            std::cout << "\t\tStart checking test_assign_3/Non-empty forward_list with assigning size less than capacity!" << std::endl;

            // greater than size
            {
                auto count {this->generate_count()};
                while(count <= 1) {
                    count = this->generate_count();
                }
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
                const auto new_size {this->generate_a_random_number(real_size + 1, count)};
                const auto numbers {this->generate_number(new_size)};
                auto d {this->to_random_access_iterator(numbers)};
                f.assign(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
                assert(f.size() == new_size);
                assert(not f.empty());
                assert(advance(f.begin(), new_size) == f.end());
                assert(advance(f.cbegin(), new_size) == f.cend());
                assert(f.front() == numbers[0]);
                auto numbers_i {0uz};
                for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                std::cout << "\t\t\ttest_assign_3/Non-empty forward_list with assigning size less than capacity/Greater than size done." << std::endl;
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
                const auto numbers {this->generate_number(new_size)};
                auto d {this->to_random_access_iterator(numbers)};
                f.assign(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
                assert(f.size() == new_size);
                assert(not f.empty());
                assert(advance(f.begin(), new_size) == f.end());
                assert(advance(f.cbegin(), new_size) == f.cend());
                assert(f.front() == numbers[0]);
                auto numbers_i {0uz};
                for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                std::cout << "\t\t\ttest_assign_3/Non-empty forward_list with assigning size less than capacity/Less than size done." << std::endl;
            }

            // equal to size
            {
                auto count {this->generate_count()};
                while(count == 0) {
                    count = this->generate_count();
                }
                forward_list<int> f(count);
                const auto numbers {this->generate_number(count)};
                auto d {this->to_random_access_iterator(numbers)};
                f.assign(int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()});
                assert(f.size() == count);
                assert(not f.empty());
                assert(advance(f.begin(), count) == f.end());
                assert(advance(f.cbegin(), count) == f.cend());
                assert(f.front() == numbers[0]);
                auto numbers_i {0uz};
                for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                numbers_i = 0;
                for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                    assert(*it == numbers[numbers_i++]);
                }
                std::cout << "\t\t\ttest_assign_3/Non-empty forward_list with assigning size less than capacity/Equal to size done." << std::endl;
            }

            std::cout << "\t\tChecking test_assign_3/Non-empty forward_list with assigning size less than capacity finished!" << std::endl;
        }

        std::cout << "\tChecking test_assign3/Random access  iterator for forward_list finished!" << std::endl;
    }

    std::cout << "Checking void assign(ForwardIterator, ForwardIterator) for forward_list finished!" << std::endl;
}
void forward_list_correctness::test_resize_1() {
    std::cout << "Start checking void resize(size_type) for ds::forward_list!" << std::endl;

    // empty to empty
    {
        forward_list<int> f {};
        f.resize(0);
        assert(f.size() == 0);
        assert(f.empty());
        assert(f.begin() == f.end());
        assert(f.cbegin() == f.cend());
        std::cout << "\tChecking test_resize_1/Empty to empty done." << std::endl;
    }

    // empty to non-empty
    {
        forward_list<int> f {};
        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
        f.resize(count);
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
        std::cout << "\tChecking test_resize_1/Empty to non-empty done." << std::endl;
    }

    // non-empty to empty
    {
        const auto count {this->generate_count()};
        forward_list<int> f(count);
        f.resize(0);
        assert(f.size() == 0);
        assert(f.empty());
        assert(f.begin() == f.end());
        assert(f.cbegin() == f.cend());
        std::cout << "\tChecking test_resize_1/Non-empty to empty done." << std::endl;
    }

    // non-empty to non-empty
    {
        std::cout << "\tStart checking test_resize_1/Non-empty to non-empty for ds::forward_list!" << std::endl;

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
            forward_list<int> f(count, number);
            f.resize(new_size);
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
            std::cout << "\t\tChecking test_resize_1/Non-empty to non-empty/Less than size done." << std::endl;
        }

        // equal to size
        {
            auto count {this->generate_count()};
            while(count == 0) {
                count = this->generate_count();
            }
            const auto number {this->generate_a_random_number()};
            forward_list<int> f(count, number);
            f.resize(count);
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
            forward_list<int> f(count, number);
            f.resize(new_size);
            assert(f.size() == new_size);
            assert(not f.empty());
            assert(advance(f.begin(), new_size) == f.end());
            assert(advance(f.cbegin(), new_size) == f.cend());
            assert(f.front() == number);
            const auto end {advance(f.begin(), count)};
            for(auto it {f.begin()}; it not_eq end; ++it) {
                assert(*it == number);
            }
            for(auto it {end}; it not_eq f.end(); ++it) {
                assert(*it == 0);
            }
            const auto cend {advance(f.cbegin(), count)};
            for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                assert(*it == number);
            }
            for(auto it {cend}; it not_eq f.cend(); ++it) {
                assert(*it == 0);
            }
            std::cout << "\t\tChecking test_resize_1/Non-empty to non-empty/Greater than size done." << std::endl;
        }

        std::cout << "\tChecking test_resize_1/Non-empty to non-empty for ds::forward_list finished!" << std::endl;
    }

    std::cout << "Checking void resize(size_type) for ds::forward_list finished!" << std::endl;
}
void forward_list_correctness::test_resize_2() {
    std::cout << "Start checking void resize(size_type, const_reference) for ds::forward_list!" << std::endl;

    // empty to empty
    {
        forward_list<int> f {};
        f.resize(0, this->generate_a_random_number());
        assert(f.size() == 0);
        assert(f.empty());
        assert(f.begin() == f.end());
        assert(f.cbegin() == f.cend());
        std::cout << "\tChecking test_resize_1/Empty to empty done." << std::endl;
    }

    // empty to non-empty
    {
        forward_list<int> f {};
        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
        const auto number {this->generate_a_random_number()};
        f.resize(count, number);
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
        std::cout << "\tChecking test_resize_1/Empty to non-empty done." << std::endl;
    }

    // non-empty to empty
    {
        const auto count {this->generate_count()};
        forward_list<int> f(count, this->generate_a_random_number());
        f.resize(0);
        assert(f.size() == 0);
        assert(f.empty());
        assert(f.begin() == f.end());
        assert(f.cbegin() == f.cend());
        std::cout << "\tChecking test_resize_1/Non-empty to empty done." << std::endl;
    }

    // non-empty to non-empty
    {
        std::cout << "\tStart checking test_resize_1/Non-empty to non-empty for ds::forward_list!" << std::endl;

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
            forward_list<int> f(count, number);
            auto number_2 {this->generate_a_random_number()};
            while(number == number_2) {
                number_2 = this->generate_a_random_number();
            }
            f.resize(new_size);
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
            std::cout << "\t\tChecking test_resize_1/Non-empty to non-empty/Less than size done." << std::endl;
        }

        // equal to size
        {
            auto count {this->generate_count()};
            while(count == 0) {
                count = this->generate_count();
            }
            const auto number {this->generate_a_random_number()};
            forward_list<int> f(count, number);
            auto number_2 {this->generate_a_random_number()};
            while(number == number_2) {
                number_2 = this->generate_a_random_number();
            }
            f.resize(count, number_2);
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
            forward_list<int> f(count, number);
            auto number_2 {this->generate_a_random_number()};
            while(number == number_2) {
                number_2 = this->generate_a_random_number();
            }
            f.resize(new_size, number_2);
            assert(f.size() == new_size);
            assert(not f.empty());
            assert(advance(f.begin(), new_size) == f.end());
            assert(advance(f.cbegin(), new_size) == f.cend());
            assert(f.front() == number);
            const auto end {advance(f.begin(), count)};
            for(auto it {f.begin()}; it not_eq end; ++it) {
                assert(*it == number);
            }
            for(auto it {end}; it not_eq f.end(); ++it) {
                assert(*it == number_2);
            }
            const auto cend {advance(f.cbegin(), count)};
            for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                assert(*it == number);
            }
            for(auto it {cend}; it not_eq f.cend(); ++it) {
                assert(*it == number_2);
            }
            std::cout << "\t\tChecking test_resize_1/Non-empty to non-empty/Greater than size done." << std::endl;
        }

        std::cout << "\tChecking test_resize_1/Non-empty to non-empty for ds::forward_list finished!" << std::endl;
    }

    std::cout << "Checking void resize(size_type) for ds::forward_list finished!" << std::endl;
}
void forward_list_correctness::test_emplace_front() {
    std::cout << "Start checking void emplace_front(Args &&...) for ds::forward_list!" << std::endl;

    // empty
    {
        forward_list<int> f {};
        const auto number {this->generate_a_random_number()};
        f.emplace_front(number);
        assert(f.size() == 1);
        assert(not f.empty());
        assert(advance(f.begin(), 1) == f.end());
        assert(advance(f.cbegin(), 1) == f.cend());
        assert(f.front() == number);
        for(auto it {f.begin()}; it not_eq f.end(); ++it) {
            assert(*it == number);
        }
        for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
            assert(*it == number);
        }

        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
        f = forward_list<int>(count);
        f.deallocate_nodes(f.head.next->node(), f.node_size());
        f.head.next = nullptr;
        f.node_size() = 0;
        f.emplace_front(number);
        assert(f.size() == 1);
        assert(not f.empty());
        assert(advance(f.begin(), 1) == f.end());
        assert(advance(f.cbegin(), 1)  == f.cend());
        assert(f.front() == number);
        for(auto it {f.begin()}; it not_eq f.end(); ++it) {
            assert(*it == number);
        }
        for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
            assert(*it == number);
        }

        std::cout << "\tChecking test_emplace_front/Empty done." << std::endl;
    }

    // non-empty
    {
        std::cout << "\tStart checking test_emplace_front/Non-empty for ds::forward_list!" << std::endl;

        // not full
        {
            auto count {this->generate_count()};
            while(count <= 1) {
                count = this->generate_count();
            }
            const auto number {this->generate_a_random_number()};
            forward_list<int> f(count, number);
            auto number_2 {this->generate_a_random_number()};
            while(number == number_2) {
                number_2 = this->generate_a_random_number();
            }
            auto new_size {this->generate_a_random_number(0, count - 1)};
            while(new_size == 0) {
                new_size = this->generate_a_random_number(0, count - 1);
            }
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
            f.emplace_front(number_2);
            assert(f.size() == new_size + 1);
            assert(not f.empty());
            assert(advance(f.begin(), new_size + 1) == f.end());
            assert(advance(f.cbegin(), new_size + 1) == f.cend());
            assert(f.front() == number_2);
            assert(*f.begin() == number_2);
            for(auto it {advance(f.begin(), 1)}; it not_eq f.end(); ++it) {
                assert(*it == number);
            }
            assert(*f.cbegin() == number_2);
            for(auto it {advance(f.cbegin(), 1)}; it not_eq f.cend(); ++it) {
                assert(*it == number);
            }
            std::cout << "\t\tChecking test_emplace_front/Non-empty forward_list/Not full done." << std::endl;
        }

        // full
        {
            auto count {this->generate_count(std::numeric_limits<int>::max() - 1)};
            while(count == 0) {
                count = this->generate_count(std::numeric_limits<int>::max() - 1);
            }
            const auto number {this->generate_a_random_number()};
            forward_list<int> f(count, number);
            auto number_2 {this->generate_a_random_number()};
            while(number == number_2) {
                number_2 = this->generate_a_random_number();
            }
            f.emplace_front(number_2);
            assert(f.size() == count + 1);
            assert(not f.empty());
            assert(advance(f.begin(), count + 1) == f.end());
            assert(advance(f.cbegin(), count + 1) == f.cend());
            assert(f.front() == number_2);
            assert(*f.begin() == number_2);
            for(auto it {advance(f.begin(), 1)}; it not_eq f.end(); ++it) {
                assert(*it == number);
            }
            assert(*f.cbegin() == number_2);
            for(auto it {advance(f.cbegin(), 1)}; it not_eq f.cend(); ++it) {
                assert(*it == number);
            }
            std::cout << "\t\tChecking test_emplace_front/Non-empty forward_list/Not full done." << std::endl;
        }

        std::cout << "\tChecking test_emplace_front/Non-empty for ds::forward_list finished!" << std::endl;
    }

    // type implicit conversion
    {
        forward_list<int> f {};
        f.emplace_front(42.2);
        assert(f.size() == 1);
        assert(not f.empty());
        assert(advance(f.begin(), 1) == f.end());
        assert(advance(f.cbegin(), 1) == f.cend());
        assert(f.front() == 42);
        for(auto it {f.begin()}; it not_eq f.end(); ++it) {
            assert(*it == 42);
        }
        for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
            assert(*it == 42);
        }
    }

    std::cout << "Checking void emplace_front(Args &&...) for ds::forward_list finished!" << std::endl;
}
void forward_list_correctness::test_pop_front() {
    std::cout << "Start checking void pop_front() for ds::forward_list!" << std::endl;

    // size == 1
    {
        forward_list<int> f(1);
        f.pop_front();
        assert(f.size() == 0);
        assert(f.empty());
        assert(f.begin() == f.end());
        assert(f.cbegin() == f.cend());
        std::cout << "\tChecking test_pop_front/Size equal to 1 done." << std::endl;
    }

    // random size
    {
        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
        const auto pop_count {this->generate_a_random_number(0, count - 1)};
        const auto number {this->generate_a_random_number()};
        forward_list<int> f(count, number);
        for(auto i {0}; i < pop_count; ++i) {
            f.pop_front();
        }
        assert(f.size() == count - pop_count);
        assert(not f.empty());
        assert(advance(f.begin(), count - pop_count) == f.end());
        assert(advance(f.cbegin(), count - pop_count) == f.cend());
        assert(f.front() == number);
        for(auto it {f.begin()}; it not_eq f.end(); ++it) {
            assert(*it == number);
        }
        for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
            assert(*it == number);
        }
        std::cout << "\tChecking test_pop_front/Random size done." << std::endl;
    }

    std::cout << "Checking void pop_front() for ds::forward_list finished!" << std::endl;
}
void forward_list_correctness::test_clear() {
    std::cout << "Start checking void clear() for ds::forward_list!" << std::endl;

    // empty
    {
        forward_list<int> f {};
        f.clear();
        assert(f.size() == 0);
        assert(f.empty());
        assert(f.begin() == f.end());
        assert(f.cbegin() == f.cend());

        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
        f = forward_list<int>(count);
        f.deallocate_nodes(f.head.next->node(), f.node_size());
        f.head.next = nullptr;
        f.node_size() = 0;
        f.clear();
        assert(f.size() == 0);
        assert(f.empty());
        assert(f.begin() == f.end());
        assert(f.cbegin() == f.cend());

        std::cout << "\tChecking test_clear/Empty forward_list done." << std::endl;
    }

    // non-empty
    {
        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
        forward_list<int> f(count, this->generate_a_random_number());
        f.clear();
        assert(f.size() == 0);
        assert(f.empty());
        assert(f.begin() == f.end());
        assert(f.cbegin() == f.cend());
        std::cout << "\tChecking test_clear/Non-empty forward_list done." << std::endl;
    }

    std::cout << "Checking void clear() for ds::forward_list finished!" << std::endl;
}
void forward_list_correctness::test_swap() {
    std::cout << "Start checking void swap() for ds::forward_list!" << std::endl;

    // swap empty capacity with empty capacity
    {
        forward_list<int> f1 {}, f2 {};
        f1.swap(f2);
        assert(f1.size() == 0);
        assert(f1.empty());
        assert(f1.begin() == f1.end());
        assert(f1.cbegin() == f1.cend());
        assert(f2.size() == 0);
        assert(f2.empty());
        assert(f2.begin() == f2.end());
        assert(f2.cbegin() == f2.cend());

        f1.swap(f2);        // revert
        assert(f1.size() == 0);
        assert(f1.empty());
        assert(f1.begin() == f1.end());
        assert(f1.cbegin() == f1.cend());
        assert(f2.size() == 0);
        assert(f2.empty());
        assert(f2.begin() == f2.end());
        assert(f2.cbegin() == f2.cend());

        std::cout << "\tChecking test_swap/Swap empty capacity with empty capacity done." << std::endl;
    }

    // swap empty capacity with non-zero capacity empty
    {
        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
        forward_list<int> f1 {}, f2(count, this->generate_a_random_number());
        f2.deallocate_nodes(f2.head.next->node(), f2.node_size());
        f2.head.next = nullptr;
        f2.node_size() = 0;
        f1.swap(f2);
        assert(f1.size() == 0);
        assert(f1.empty());
        assert(f1.begin() == f1.end());
        assert(f1.cbegin() == f1.cend());
        assert(f2.size() == 0);
        assert(f2.empty());
        assert(f2.begin() == f2.end());
        assert(f2.cbegin() == f2.cend());

        f1.swap(f2);        // revert
        assert(f1.size() == 0);
        assert(f1.empty());
        assert(f1.begin() == f1.end());
        assert(f1.cbegin() == f1.cend());
        assert(f2.size() == 0);
        assert(f2.empty());
        assert(f2.begin() == f2.end());
        assert(f2.cbegin() == f2.cend());

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
        forward_list<int> f1(count_1, this->generate_a_random_number()), f2(count_2, this->generate_a_random_number());
        f1.deallocate_nodes(f1.head.next->node(), f1.node_size());
        f1.head.next = nullptr;
        f1.node_size() = 0;
        f2.deallocate_nodes(f2.head.next->node(), f2.node_size());
        f2.head.next = nullptr;
        f2.node_size() = 0;
        f1.swap(f2);
        assert(f1.size() == 0);
        assert(f1.empty());
        assert(f1.begin() == f1.end());
        assert(f1.cbegin() == f1.cend());
        assert(f2.size() == 0);
        assert(f2.empty());
        assert(f2.begin() == f2.end());
        assert(f2.cbegin() == f2.cend());

        f1.swap(f2);        // revert
        assert(f1.size() == 0);
        assert(f1.empty());
        assert(f1.begin() == f1.end());
        assert(f1.cbegin() == f1.cend());
        assert(f2.size() == 0);
        assert(f2.empty());
        assert(f2.begin() == f2.end());
        assert(f2.cbegin() == f2.cend());

        std::cout << "\tChecking test_swap/Swap empty capacity with non-zero capacity empty done." << std::endl;
    }

    // swap empty with non-empty
    {
        auto count {this->generate_count()};
        while(count == 0) {
            count = this->generate_count();
        }
        const auto number {this->generate_a_random_number()};
        forward_list<int> f1 {}, f2(count, number);
        f1.swap(f2);
        assert(f1.size() == count);
        assert(not f1.empty());
        assert(advance(f1.begin(), count) == f1.end());
        assert(advance(f1.cbegin(), count) == f1.cend());
        assert(f1.front() == number);
        for(auto it {f1.begin()}; it not_eq f1.end(); ++it) {
            assert(*it == number);
        }
        for(auto it {f1.cbegin()}; it not_eq f1.cend(); ++it) {
            assert(*it == number);
        }
        assert(f2.size() == 0);
        assert(f2.empty());
        assert(f2.begin() == f2.end());
        assert(f2.cbegin() == f2.cend());

        f1.swap(f2);        // revert
        assert(f1.size() == 0);
        assert(f1.empty());
        assert(f1.begin() == f1.end());
        assert(f1.cbegin() == f1.cend());
        assert(f2.size() == count);
        assert(not f2.empty());
        assert(advance(f2.begin(), count) == f1.end());
        assert(advance(f2.cbegin(), count) == f1.cend());
        assert(f2.front() == number);
        for(auto it {f2.begin()}; it not_eq f2.end(); ++it) {
            assert(*it == number);
        }
        for(auto it {f2.cbegin()}; it not_eq f2.cend(); ++it) {
            assert(*it == number);
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
        forward_list<int> f1(count_1), f2(count_2, number);
        f1.deallocate_nodes(f1.head.next->node(), f1.node_size());
        f1.head.next = nullptr;
        f1.node_size() = 0;
        f1.swap(f2);
        assert(f1.size() == count_2);
        assert(not f1.empty());
        assert(advance(f1.begin(), count_2) == f1.end());
        assert(advance(f1.cbegin(), count_2) == f1.cend());
        assert(f1.front() == number);
        for(auto it {f1.begin()}; it not_eq f1.end(); ++it) {
            assert(*it == number);
        }
        for(auto it {f1.cbegin()}; it not_eq f1.cend(); ++it) {
            assert(*it == number);
        }
        assert(f2.size() == 0);
        assert(f2.empty());
        assert(f2.begin() == f2.end());
        assert(f2.cbegin() == f2.cend());

        f1.swap(f2);        // revert
        assert(f1.size() == 0);
        assert(f1.empty());
        assert(f1.begin() == f1.end());
        assert(f1.cbegin() == f1.cend());
        assert(f2.size() == count_2);
        assert(not f2.empty());
        assert(advance(f2.begin(), count_2) == f1.end());
        assert(advance(f2.cbegin(), count_2) == f1.cend());
        assert(f2.front() == number);
        for(auto it {f2.begin()}; it not_eq f2.end(); ++it) {
            assert(*it == number);
        }
        for(auto it {f2.cbegin()}; it not_eq f2.cend(); ++it) {
            assert(*it == number);
        }

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
        forward_list<int> f1(count_1, number_1), f2(count_2, number_2);
        f1.swap(f2);
        assert(f1.size() == count_2);
        assert(not f1.empty());
        assert(advance(f1.begin(), count_2) == f1.end());
        assert(advance(f1.cbegin(), count_2) == f1.cend());
        assert(f1.front() == number_2);
        for(auto it {f1.begin()}; it not_eq f1.end(); ++it) {
            assert(*it == number_2);
        }
        for(auto it {f1.cbegin()}; it not_eq f1.cend(); ++it) {
            assert(*it == number_2);
        }
        assert(f2.size() == count_1);
        assert(not f2.empty());
        assert(advance(f2.begin(), count_2) == f1.end());
        assert(advance(f2.cbegin(), count_2) == f1.cend());
        assert(f2.front() == number_1);
        for(auto it {f2.begin()}; it not_eq f2.end(); ++it) {
            assert(*it == number_1);
        }
        for(auto it {f2.cbegin()}; it not_eq f2.cend(); ++it) {
            assert(*it == number_1);
        }

        f1.swap(f2);        // revert
        assert(f1.size() == count_1);
        assert(not f1.empty());
        assert(advance(f1.begin(), count_2) == f1.end());
        assert(advance(f1.cbegin(), count_2) == f1.cend());
        assert(f1.front() == number_1);
        for(auto it {f1.begin()}; it not_eq f1.end(); ++it) {
            assert(*it == number_1);
        }
        for(auto it {f1.cbegin()}; it not_eq f1.cend(); ++it) {
            assert(*it == number_1);
        }
        assert(f2.size() == count_2);
        assert(not f2.empty());
        assert(advance(f2.begin(), count_2) == f1.end());
        assert(advance(f2.cbegin(), count_2) == f1.cend());
        assert(f2.front() == number_2);
        for(auto it {f2.begin()}; it not_eq f2.end(); ++it) {
            assert(*it == number_2);
        }
        for(auto it {f2.cbegin()}; it not_eq f2.cend(); ++it) {
            assert(*it == number_2);
        }

        std::cout << "\tChecking test_swap/Swap non-empty with non-empty done." << std::endl;
    }

    std::cout << "Checking void swap() for ds::forward_list finished!" << std::endl;
}
void forward_list_correctness::test_emplace_after() {
    std::cout << "Start checking iterator emplace(difference_type, Args &&...) for ds::forward_list!" << std::endl;

    // emplace to empty forward_list
    {
        forward_list<int> f {};
        const auto result {f.emplace(0, 42.2)};
        assert(f.size() == 1);
        assert(not f.empty());
        assert(advance(f.begin(), 1) == f.end());
        assert(advance(f.cbegin(), 1) == f.cend());
        assert(f.front() == 42);
        for(auto it {f.begin()}; it not_eq f.end(); ++it) {
            assert(*it == 42);
        }
        for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
            assert(*it == 42);
        }
        assert(result == f.begin());
        assert(result == f.cbegin());
        std::cout << "\tChecking test_emplace/Emplace to empty forward_list done." << std::endl;
    }

    // emplace to non-empty forward_list
    {
        std::cout << "\tStart checking test_emplace/Emplace to non-empty forward_list!" << std::endl;

        // emplace to head
        {
            std::cout << "\t\tStart checking test_emplace/Emplace to non-empty forward_list/Emplace to head!" << std::endl;

            // without reallocation
            {
                auto count {this->generate_count()};
                while(count <= 1) {
                    count = this->generate_count();
                }
                const auto new_size {this->generate_a_random_number(1, count - 1)};
                const auto number {this->generate_a_random_number()};
                forward_list<int> f(count, number);
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
                auto number_2 {this->generate_a_random_number()};
                while(number == number_2) {
                    number_2 = this->generate_a_random_number();
                }
                const auto result {f.emplace(0, number_2)};
                assert(f.size() == new_size + 1);
                assert(not f.empty());
                assert(advance(f.begin(), new_size + 1) == f.end());
                assert(advance(f.cbegin(), new_size + 1) == f.cend());
                assert(f.front() == number_2);
                assert(*f.begin() == number_2);
                assert(*f.cbegin() == number_2);
                for(auto it {advance(f.begin(), 1)}; it not_eq f.end(); ++it) {
                    assert(*it == number);
                }
                for(auto it {advance(f.cbegin(), 1)}; it not_eq f.cend(); ++it) {
                    assert(*it == number);
                }
                assert(result == f.begin());
                assert(result == f.cbegin());
                std::cout << "\t\t\tChecking test_emplace/Emplace to non-empty forward_list/Emplace to head/Without reallocation done." << std::endl;
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
                forward_list<int> f(count, number);
                const auto result {f.emplace(0, number_2)};
                assert(f.size() == count + 1);
                assert(not f.empty());
                assert(advance(f.begin(), count + 1) == f.end());
                assert(advance(f.cbegin(), count + 1) == f.cend());
                assert(f.front() == number_2);
                assert(*f.begin() == number_2);
                assert(*f.cbegin() == number_2);
                for(auto it {advance(f.begin(), 1)}; it not_eq f.end(); ++it) {
                    assert(*it == number);
                }
                for(auto it {advance(f.cbegin(), 1)}; it not_eq f.cend(); ++it) {
                    assert(*it == number);
                }
                assert(result == f.begin());
                assert(result == f.cbegin());
                std::cout << "\t\t\tChecking test_emplace/Emplace to non-empty forward_list/Emplace to head/With reallocation done." << std::endl;
            }

            std::cout << "\t\tChecking test_emplace/Emplace to non-empty forward_list/Emplace to head finished!" << std::endl;
        }

        // emplace to random position
        {
            std::cout << "\t\tStart checking test_emplace/Emplace to non-empty forward_list/Emplace to random position!" << std::endl;

            // without reallocation
            {
                auto count {this->generate_count()};
                while(count <= 2) {
                    count = this->generate_count();
                }
                auto new_size {this->generate_a_random_number(2, count - 1)};
                const auto number {this->generate_a_random_number()};
                forward_list<int> f(count, number);
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
                auto number_2 {this->generate_a_random_number()};
                while(number == number_2) {
                    number_2 = this->generate_a_random_number();
                }
                const auto insertion_position {this->generate_a_random_number(1, new_size - 1)};
                const auto result {f.emplace(insertion_position, number_2)};
                assert(f.size() == new_size + 1);
                assert(not f.empty());
                assert(advance(f.begin(), new_size + 1) == f.end());
                assert(advance(f.cbegin(), new_size + 1) == f.cend());
                assert(f.front() == number);
                const auto end {advance(f.begin(), insertion_position)};
                for(auto it {f.begin()}; it not_eq end; ++it) {
                    assert(*it == number);
                }
                assert(*end == number_2);
                for(auto it {advance(f.begin(), insertion_position + 1)}; it not_eq f.end(); ++it) {
                    assert(*it == number);
                }
                const auto cend {advance(f.cbegin(), insertion_position)};
                for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                    assert(*it == number);
                }
                assert(*cend == number_2);
                for(auto it {advance(f.cbegin(), insertion_position + 1)}; it not_eq f.cend(); ++it) {
                    assert(*it == number);
                }
                assert(result == advance(f.begin(), insertion_position));
                assert(result == advance(f.cbegin(), insertion_position));
                std::cout << "\t\t\tChecking test_emplace/Emplace to non-empty forward_list/Emplace to random position/Without reallocation done." << std::endl;
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
                forward_list<int> f(count, number);
                const auto insertion_position {this->generate_a_random_number(1, count - 1)};
                const auto result {f.emplace(insertion_position, number_2)};
                assert(f.size() == count + 1);
                assert(not f.empty());
                assert(advance(f.begin(), count + 1) == f.end());
                assert(advance(f.cbegin(), count + 1) == f.cend());
                assert(f.front() == number);
                const auto end {advance(f.begin(), insertion_position)};
                for(auto it {f.begin()}; it not_eq end; ++it) {
                    assert(*it == number);
                }
                assert(*end == number_2);
                for(auto it {advance(f.begin(), insertion_position + 1)}; it not_eq f.end(); ++it) {
                    assert(*it == number);
                }
                const auto cend {advance(f.cbegin(), insertion_position)};
                for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                    assert(*it == number);
                }
                assert(*cend == number_2);
                for(auto it {advance(f.cbegin(), insertion_position + 1)}; it not_eq f.cend(); ++it) {
                    assert(*it == number);
                }
            }

            std::cout << "\t\tChecking test_emplace/Emplace to non-empty forward_list/Emplace to random position/With reallocation finished!" << std::endl;
        }

        // emplace to tail
        {
            std::cout << "\t\tStart checking test_emplace/Emplace to non-empty forward_list/Emplace to tail!" << std::endl;

            // without reallocation
            {
                auto count {this->generate_count()};
                while(count <= 1) {
                    count = this->generate_count();
                }
                const auto new_size {this->generate_a_random_number(1, count - 1)};
                const auto number {this->generate_a_random_number()};
                forward_list<int> f(count, number);
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
                auto number_2 {this->generate_a_random_number()};
                while(number == number_2) {
                    number_2 = this->generate_a_random_number();
                }
                const auto result {f.emplace(new_size, number_2)};
                assert(f.size() == new_size + 1);
                assert(not f.empty());
                assert(advance(f.begin(), new_size + 1) == f.end());
                assert(advance(f.cbegin(), new_size + 1) == f.cend());
                assert(f.front() == number);
                const auto end {advance(f.before_begin(), f.size())};
                for(auto it {f.begin()}; it not_eq end; ++it) {
                    assert(*it == number);
                }
                assert(*end == number_2);
                const auto cend {advance(f.cbefore_begin(), f.size())};
                for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                    assert(*it == number);
                }
                assert(*cend == number_2);
                assert(result == advance(f.begin(), f.size() - 1));
                assert(result == advance(f.cbegin(), f.size() - 1));
                std::cout << "\t\t\tChecking test_emplace/Emplace to non-empty forward_list/Emplace to tail/Without reallocation done." << std::endl;
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
                forward_list<int> f(count, number);
                const auto result {f.emplace(count, number_2)};
                assert(f.size() == count + 1);
                assert(not f.empty());
                assert(advance(f.begin(), count + 1) == f.end());
                assert(advance(f.cbegin(), count + 1) == f.cend());
                assert(f.front() == number);
                const auto end {advance(f.before_begin(), f.size())};
                for(auto it {f.begin()}; it not_eq end; ++it) {
                    assert(*it == number);
                }
                assert(*end == number_2);
                const auto cend {advance(f.cbefore_begin(), f.size())};
                for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                    assert(*it == number);
                }
                assert(*cend == number_2);
                assert(result == advance(f.begin(), f.size() - 1));
                assert(result == advance(f.cbegin(), f.size() - 1));
                std::cout << "\t\t\tChecking test_emplace/Emplace to non-empty forward_list/Emplace to tail/With reallocation done." << std::endl;
            }

            std::cout << "\t\tChecking test_emplace/Emplace to non-empty forward_list/Emplace to tail finished!" << std::endl;
        }

        std::cout << "\tChecking test_emplace/Emplace to non-empty forward_list finished!" << std::endl;
    }

    std::cout << "Checking iterator emplace(difference_type, Args &&...) for ds::forward_list finished!" << std::endl;
}
void forward_list_correctness::test_insert_after_1() {
    std::cout << "Start checking iterator insert(size_type, const_reference, size_type) for ds::forward_list!" << std::endl;

    // insert to empty forward_list
    {
        std::cout << "\tStart checking test_insert_1/Insert to empty forward_list for ds::forward_list!" << std::endl;

        // insertion size equal to zero
        {
            forward_list<int> f {};
            const auto result {f.insert(0, this->generate_a_random_number(), 0)};
            assert(f.size() == 0);
            assert(f.empty());
            assert(f.begin() == f.end());
            assert(f.cbegin() == f.cend());
            assert(result == f.begin());
            assert(result == f.cbegin());
            std::cout << "\t\tChecking test_insert_1/Insert to empty forward_list/Insertion size not equal to zero done." << std::endl;
        }

        // insertion size not equal to zero
        {
            forward_list<int> f {};
            auto insertion_size {this->generate_count()};
            while(insertion_size == 0) {
                insertion_size = this->generate_count();
            }
            const auto insertion_number {this->generate_a_random_number()};
            const auto result {f.insert(0, insertion_number, insertion_size)};
            assert(f.size() == insertion_size);
            assert(not f.empty());
            assert(advance(f.begin(), insertion_size) == f.end());
            assert(advance(f.cbegin(), insertion_size) == f.cend());
            assert(f.front() == insertion_number);
            for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                assert(*it == insertion_number);
            }
            for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                assert(*it == insertion_number);
            }
            assert(result == f.begin());
            assert(result == f.cbegin());
            std::cout << "\t\tChecking test_insert_1/Insert to empty forward_list/Insertion size not equal to zero done." << std::endl;
        }

        std::cout << "\tChecking test_insert_1/Insert to empty forward_list for ds::forward_list finished!" << std::endl;
    }

    // insert to non-empty forward_list
    {
        std::cout << "\tStart checking test_insert_1/Insert to non-empty forward_list!" << std::endl;

        // insert to head
        {
            std::cout << "\t\tStart checking test_insert_1/Insert to non-empty forward_list/Insert to head!" << std::endl;

            // without reallocation
            {
                std::cout << "\t\t\tStart checking test_insert_1/Insert to non-empty forward_list/Insert to head/Without reallocation!" << std::endl;

                // insertion size is zero
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    const auto new_size {this->generate_a_random_number(1, count - 1)};
                    const auto number {this->generate_a_random_number()};
                    forward_list<int> f(count, number);
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
                    const auto result {f.insert(0, this->generate_a_random_number(), 0)};
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
                    assert(result == f.begin());
                    assert(result == f.cbegin());
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty forward_list/Insert to head/Without reallocation/Insertion size is zero done." << std::endl;
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
                    forward_list<int> f(count + static_cast<size_t>(insertion_size) + spare, number);
                    auto erasion {&f.head};
                    for(auto i {count};; erasion = erasion->next) {
                        if(i-- == 0) {
                            auto backup {erasion->next};
                            erasion->next = nullptr;
                            f.node_size.allocator().deallocate(backup->node(), insertion_size + spare);
                            f.node_size() = count;
                            break;
                        }
                    }
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    const auto result {f.insert(0, number_2, insertion_size)};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number_2);
                    const auto end {advance(f.begin(), insertion_size)};
                    for(auto it {f.begin()}; it not_eq end; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {end}; it not_eq f.end(); ++it) {
                        assert(*it == number);
                    }
                    const auto cend {advance(f.cbegin(), insertion_size)};
                    for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {cend}; it not_eq f.cend(); ++it) {
                        assert(*it == number);
                    }
                    assert(result == f.begin());
                    assert(result == f.cbegin());
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty forward_list/Insert to head/Without reallocation/Insertion size less equal to tail size done." << std::endl;
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
                    forward_list<int> f(count + static_cast<size_t>(insertion_size) + spare, number);
                    auto erasion {&f.head};
                    for(auto i {count};; erasion = erasion->next) {
                        if(i-- == 0) {
                            auto backup {erasion->next};
                            erasion->next = nullptr;
                            f.node_size.allocator().deallocate(backup->node(), static_cast<size_t>(insertion_size) + spare);
                            f.node_size() = count;
                            break;
                        }
                    }
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    const auto result {f.insert(0, number_2, insertion_size)};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number_2);
                    const auto end {advance(f.begin(), insertion_size)};
                    for(auto it {f.begin()}; it not_eq end; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {end}; it not_eq f.end(); ++it) {
                        assert(*it == number);
                    }
                    const auto cend {advance(f.cbegin(), insertion_size)};
                    for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {cend}; it not_eq f.cend(); ++it) {
                        assert(*it == number);
                    }
                    assert(result == f.begin());
                    assert(result == f.cbegin());
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty forward_list/Insert to head/Without reallocation/Insertion size greater than tail size done." << std::endl;
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
                    forward_list<int> f(count + static_cast<size_t>(insertion_size), number);
                    auto erasion {&f.head};
                    for(auto i {count};; erasion = erasion->next) {
                        if(i-- == 0) {
                            auto backup {erasion->next};
                            erasion->next = nullptr;
                            f.node_size.allocator().deallocate(backup->node(), insertion_size);
                            f.node_size() = count;
                            break;
                        }
                    }
                    ++f.front();
                    auto result {f.insert(0, f.front(), insertion_size)};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number + 1);
                    const auto end {advance(f.begin(), insertion_size + 1)};
                    for(auto it {f.begin()}; it not_eq end; ++it) {
                        assert(*it == number + 1);
                    }
                    for(auto it {end}; it not_eq f.end(); ++it) {
                        assert(*it == number);
                    }
                    const auto cend {advance(f.cbegin(), insertion_size + 1)};
                    for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                        assert(*it == number + 1);
                    }
                    for(auto it {cend}; it not_eq f.cend(); ++it) {
                        assert(*it == number);
                    }
                    assert(result == f.begin());
                    assert(result == f.cbegin());
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty forward_list/Insert to head/Without reallocation/The value is from self done." << std::endl;
                }

                std::cout << "\t\t\tStart checking test_insert_1/Insert to non-empty forward_list/Insert to head/Without reallocation finished!" << std::endl;
            }

            // with reallocation
            {
                std::cout << "\t\t\tStart checking test_insert_1/Insert to non-empty forward_list/Insert to head/With reallocation!" << std::endl;

                // insertion size less equal to tail size
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    auto insertion_size {this->generate_a_random_number(1, count)};
                    const auto number {this->generate_a_random_number()};
                    forward_list<int> f(count, number);
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    const auto result {f.insert(0, number_2, insertion_size)};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number_2);
                    const auto end {advance(f.begin(), insertion_size)};
                    for(auto it {f.begin()}; it not_eq end; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {end}; it not_eq f.end(); ++it) {
                        assert(*it == number);
                    }
                    const auto cend {advance(f.cbegin(), insertion_size)};
                    for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {cend}; it not_eq f.cend(); ++it) {
                        assert(*it == number);
                    }
                    assert(result == f.begin());
                    assert(result == f.cbegin());
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty forward_list/Insert to head/With reallocation/Insertion size less equal to tail size done." << std::endl;
                }

                // insertion size greater than tail size
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    const auto insertion_size {this->generate_a_random_number(count + 1)};
                    const auto number {this->generate_a_random_number()};
                    forward_list<int> f(count, number);
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    const auto result {f.insert(0, number_2, insertion_size)};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number_2);
                    const auto end {advance(f.begin(), insertion_size)};
                    for(auto it {f.begin()}; it not_eq end; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {end}; it not_eq f.end(); ++it) {
                        assert(*it == number);
                    }
                    const auto cend {advance(f.cbegin(), insertion_size)};
                    for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {cend}; it not_eq f.cend(); ++it) {
                        assert(*it == number);
                    }
                    assert(result == f.begin());
                    assert(result == f.cbegin());
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty forward_list/Insert to head/With reallocation/Insertion size greater than tail size done." << std::endl;
                }

                // insertion size less equal to double capacity
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    auto insertion_size {this->generate_a_random_number(1, count)};
                    const auto number {this->generate_a_random_number()};
                    forward_list<int> f(count, number);
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    auto result {f.insert(0, number_2, insertion_size)};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number_2);
                    const auto end {advance(f.begin(), insertion_size)};
                    for(auto it {f.begin()}; it not_eq end; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {end}; it not_eq f.end(); ++it) {
                        assert(*it == number);
                    }
                    const auto cend {advance(f.cbegin(), insertion_size)};
                    for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {cend}; it not_eq f.cend(); ++it) {
                        assert(*it == number);
                    }
                    assert(result == f.begin());
                    assert(result == f.cbegin());
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty forward_list/Insert to head/With reallocation/Insertion size less equal to double capacity done." << std::endl;
                }

                // insertion size greater than double capacity
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    auto insertion_size {this->generate_a_random_number(2 * count + 1)};
                    const auto number {this->generate_a_random_number()};
                    forward_list<int> f(count, number);
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    auto result {f.insert(0, number_2, insertion_size)};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number_2);
                    const auto end {advance(f.begin(), insertion_size)};
                    for(auto it {f.begin()}; it not_eq end; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {end}; it not_eq f.end(); ++it) {
                        assert(*it == number);
                    }
                    const auto cend {advance(f.cbegin(), insertion_size)};
                    for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {cend}; it not_eq f.cend(); ++it) {
                        assert(*it == number);
                    }
                    assert(result == f.begin());
                    assert(result == f.cbegin());
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty forward_list/Insert to head/With reallocation/Insertion size greater than double capacity done." << std::endl;
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
                    forward_list<int> f(count, number);
                    ++f.front();
                    auto result {f.insert(0, f.front(), insertion_size)};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number + 1);
                    const auto end {advance(f.begin(), insertion_size + 1)};
                    for(auto it {f.begin()}; it not_eq end; ++it) {
                        assert(*it == number + 1);
                    }
                    for(auto it {end}; it not_eq f.end(); ++it) {
                        assert(*it == number);
                    }
                    const auto cend {advance(f.cbegin(), insertion_size + 1)};
                    for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                        assert(*it == number + 1);
                    }
                    for(auto it {cend}; it not_eq f.cend(); ++it) {
                        assert(*it == number);
                    }
                    assert(result == f.begin());
                    assert(result == f.cbegin());
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty forward_list/Insert to head/With reallocation/The value is from self done." << std::endl;
                }

                std::cout << "\t\t\tStart checking test_insert_1/Insert to non-empty forward_list/Insert to head/With reallocation finished!" << std::endl;
            }

            std::cout << "\t\tChecking test_insert_1/Insert to non-empty forward_list/Insert to head finished!" << std::endl;
        }

        // insert to random position
        {
            std::cout << "\t\tStart checking test_insert_1/Insert to non-empty forward_list/Insert to random position!" << std::endl;

            // without reallocation
            {
                std::cout << "\t\t\tStart checking test_insert_1/Insert to non-empty forward_list/Insert to random position/Without reallocation!" << std::endl;

                // insertion size is zero
                {
                    auto count {this->generate_count()};
                    while(count <= 2) {
                        count = this->generate_count();
                    }
                    const auto new_size {this->generate_a_random_number(2, count - 1)};
                    const auto number {this->generate_a_random_number()};
                    const auto insertion_position {this->generate_a_random_number(1, new_size - 1)};
                    forward_list<int> f(count, number);
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
                    const auto result {f.insert(insertion_position, this->generate_a_random_number(), 0)};
                    assert(f.size() == new_size);
                    assert(not f.empty());
                    assert(advance(f.begin(), new_size) == f.end());
                    assert(advance(f.cbegin(), new_size) == f.cend());
                    assert(f.front() == number);
                    for(auto it {advance(f.begin(), 1)}; it not_eq f.end(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {advance(f.cbegin(), 1)}; it not_eq f.cend(); ++it) {
                        assert(*it == number);
                    }
                    assert(result == advance(f.begin(), insertion_position));
                    assert(result == advance(f.cbegin(), insertion_position));
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty forward_list/Insert to random position/Without reallocation/Insertion size is zero done." << std::endl;
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
                    forward_list<int> f(count + static_cast<size_t>(insertion_size) + spare, number);
                    auto erasion {&f.head};
                    for(auto i {count};; erasion = erasion->next) {
                        if(i-- == 0) {
                            auto backup {erasion->next};
                            erasion->next = nullptr;
                            f.node_size.allocator().deallocate(backup->node(), insertion_size + spare);
                            f.node_size() = count;
                            break;
                        }
                    }
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    const auto result {f.insert(insertion_position, number_2, insertion_size)};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number);
                    const auto end1 {advance(f.begin(), insertion_position)};
                    for(auto it {f.begin()}; it not_eq end1; ++it) {
                        assert(*it == number);
                    }
                    const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                    for(auto it {end1}; it not_eq end2; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {end2}; it not_eq f.end(); ++it) {
                        assert(*it == number);
                    }
                    const auto cend1 {advance(f.cbegin(), insertion_position)};
                    for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                        assert(*it == number);
                    }
                    const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                    for(auto it {cend1}; it not_eq cend2; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {cend2}; it not_eq f.cend(); ++it) {
                        assert(*it == number);
                    }
                    assert(result == advance(f.begin(), insertion_position));
                    assert(result == advance(f.cbegin(), insertion_position));
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty forward_list/Insert to random position/Without reallocation/Insertion size less equal to tail size done." << std::endl;
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
                    forward_list<int> f(count + static_cast<size_t>(insertion_size) + spare, number);
                    auto erasion {&f.head};
                    for(auto i {count};; erasion = erasion->next) {
                        if(i-- == 0) {
                            auto backup {erasion->next};
                            erasion->next = nullptr;
                            f.node_size.allocator().deallocate(backup->node(), static_cast<size_t>(insertion_size) + spare);
                            f.node_size() = count;
                            break;
                        }
                    }
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    const auto result {f.insert(insertion_position, number_2, insertion_size)};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number);
                    const auto end1 {advance(f.begin(), insertion_position)};
                    for(auto it {f.begin()}; it not_eq end1; ++it) {
                        assert(*it == number);
                    }
                    const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                    for(auto it {end1}; it not_eq end2; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {end2}; it not_eq f.end(); ++it) {
                        assert(*it == number);
                    }
                    const auto cend1 {advance(f.cbegin(), insertion_position)};
                    for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                        assert(*it == number);
                    }
                    const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                    for(auto it {cend1}; it not_eq cend2; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {cend2}; it not_eq f.cend(); ++it) {
                        assert(*it == number);
                    }
                    assert(result == advance(f.begin(), insertion_position));
                    assert(result == advance(f.cbegin(), insertion_position));
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty forward_list/Insert to random position/Without reallocation/Insertion size greater than tail size done." << std::endl;
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
                    forward_list<int> f(count + static_cast<size_t>(insertion_size), number);
                    auto erasion {&f.head};
                    for(auto i {count};; erasion = erasion->next) {
                        if(i-- == 0) {
                            auto backup {erasion->next};
                            erasion->next = nullptr;
                            f.node_size.allocator().deallocate(backup->node(), insertion_size);
                            f.node_size() = count;
                            break;
                        }
                    }
                    auto cursor {f.before_begin()};
                    for(auto i {0}; i <= insertion_position; ++cursor, ++i);
                    ++*cursor;
                    auto result {f.insert(insertion_position, *cursor, insertion_size)};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number);
                    const auto end1 {advance(f.begin(), insertion_position)};
                    for(auto it {f.begin()}; it not_eq end1; ++it) {
                        assert(*it == number);
                    }
                    const auto end2 {advance(f.begin(), insertion_position + insertion_size + 1)};
                    for(auto it {end1}; it not_eq end2; ++it) {
                        assert(*it == number + 1);
                    }
                    for(auto it {end2}; it not_eq f.end(); ++it) {
                        assert(*it == number);
                    }
                    const auto cend1 {advance(f.cbegin(), insertion_position)};
                    for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                        assert(*it == number);
                    }
                    const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size + 1)};
                    for(auto it {cend1}; it not_eq cend2; ++it) {
                        assert(*it == number + 1);
                    }
                    for(auto it {cend2}; it not_eq f.cend(); ++it) {
                        assert(*it == number);
                    }
                    assert(result == advance(f.begin(), insertion_position));
                    assert(result == advance(f.cbegin(), insertion_position));
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty forward_list/Insert to random position/Without reallocation/The value is from self done." << std::endl;
                }

                std::cout << "\t\t\tStart checking test_insert_1/Insert to non-empty forward_list/Insert to random position/Without reallocation finished!" << std::endl;
            }

            // with reallocation
            {
                std::cout << "\t\t\tStart checking test_insert_1/Insert to non-empty forward_list/Insert to random position/With reallocation!" << std::endl;

                // insertion size less equal to tail size
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    const auto insertion_position {this->generate_a_random_number(1, count - 1)};
                    auto insertion_size {this->generate_a_random_number(1, count - insertion_position)};
                    const auto number {this->generate_a_random_number()};
                    forward_list<int> f(count, number);
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    const auto result {f.insert(insertion_position, number_2, insertion_size)};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number);
                    const auto end1 {advance(f.begin(), insertion_position)};
                    for(auto it {f.begin()}; it not_eq end1; ++it) {
                        assert(*it == number);
                    }
                    const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                    for(auto it {end1}; it not_eq end2; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {end2}; it not_eq f.end(); ++it) {
                        assert(*it == number);
                    }
                    const auto cend1 {advance(f.cbegin(), insertion_position)};
                    for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                        assert(*it == number);
                    }
                    const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                    for(auto it {cend1}; it not_eq cend2; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {cend2}; it not_eq f.cend(); ++it) {
                        assert(*it == number);
                    }
                    assert(result == advance(f.begin(), insertion_position));
                    assert(result == advance(f.cbegin(), insertion_position));
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty forward_list/Insert to random position/With reallocation/Insertion size less equal to tail size done." << std::endl;
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
                    forward_list<int> f(count, number);
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    const auto result {f.insert(insertion_position, number_2, insertion_size)};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number);
                    const auto end1 {advance(f.begin(), insertion_position)};
                    for(auto it {f.begin()}; it not_eq end1; ++it) {
                        assert(*it == number);
                    }
                    const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                    for(auto it {end1}; it not_eq end2; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {end2}; it not_eq f.end(); ++it) {
                        assert(*it == number);
                    }
                    const auto cend1 {advance(f.cbegin(), insertion_position)};
                    for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                        assert(*it == number);
                    }
                    const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                    for(auto it {cend1}; it not_eq cend2; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {cend2}; it not_eq f.cend(); ++it) {
                        assert(*it == number);
                    }
                    assert(result == advance(f.begin(), insertion_position));
                    assert(result == advance(f.cbegin(), insertion_position));
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty forward_list/Insert to random position/With reallocation/Insertion size greater than tail size done." << std::endl;
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
                    forward_list<int> f(count, number);
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    auto result {f.insert(insertion_position, number_2, insertion_size)};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number);
                    const auto end1 {advance(f.begin(), insertion_position)};
                    for(auto it {f.begin()}; it not_eq end1; ++it) {
                        assert(*it == number);
                    }
                    const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                    for(auto it {end1}; it not_eq end2; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {end2}; it not_eq f.end(); ++it) {
                        assert(*it == number);
                    }
                    const auto cend1 {advance(f.cbegin(), insertion_position)};
                    for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                        assert(*it == number);
                    }
                    const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                    for(auto it {cend1}; it not_eq cend2; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {cend2}; it not_eq f.cend(); ++it) {
                        assert(*it == number);
                    }
                    assert(result == advance(f.begin(), insertion_position));
                    assert(result == advance(f.cbegin(), insertion_position));
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty forward_list/Insert to random position/With reallocation/Insertion size less equal to double capacity done." << std::endl;
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
                    forward_list<int> f(count, number);
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    auto result {f.insert(insertion_position, number_2, insertion_size)};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number);
                    const auto end1 {advance(f.begin(), insertion_position)};
                    for(auto it {f.begin()}; it not_eq end1; ++it) {
                        assert(*it == number);
                    }
                    const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                    for(auto it {end1}; it not_eq end2; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {end2}; it not_eq f.end(); ++it) {
                        assert(*it == number);
                    }
                    const auto cend1 {advance(f.cbegin(), insertion_position)};
                    for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                        assert(*it == number);
                    }
                    const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                    for(auto it {cend1}; it not_eq cend2; ++it) {
                        assert(*it == number_2);
                    }
                    for(auto it {cend2}; it not_eq f.cend(); ++it) {
                        assert(*it == number);
                    }
                    assert(result == advance(f.begin(), insertion_position));
                    assert(result == advance(f.cbegin(), insertion_position));
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty forward_list/Insert to random position/With reallocation/Insertion size greater than double capacity done." << std::endl;
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
                    forward_list<int> f(count, number);
                    auto cursor {f.before_begin()};
                    for(auto i {0}; i <= insertion_position; ++cursor, ++i);
                    ++*cursor;
                    auto result {f.insert(insertion_position, *cursor, insertion_size)};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number);
                    const auto end1 {advance(f.begin(), insertion_position)};
                    for(auto it {f.begin()}; it not_eq end1; ++it) {
                        assert(*it == number);
                    }
                    const auto end2 {advance(f.begin(), insertion_position + insertion_size + 1)};
                    for(auto it {end1}; it not_eq end2; ++it) {
                        assert(*it == number + 1);
                    }
                    for(auto it {end2}; it not_eq f.end(); ++it) {
                        assert(*it == number);
                    }
                    const auto cend1 {advance(f.cbegin(), insertion_position)};
                    for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                        assert(*it == number);
                    }
                    const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size + 1)};
                    for(auto it {cend1}; it not_eq cend2; ++it) {
                        assert(*it == number + 1);
                    }
                    for(auto it {cend2}; it not_eq f.cend(); ++it) {
                        assert(*it == number);
                    }
                    assert(result == advance(f.begin(), insertion_position));
                    assert(result == advance(f.cbegin(), insertion_position));
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty forward_list/Insert to random position/With reallocation/The value is from self done." << std::endl;
                }

                std::cout << "\t\t\tStart checking test_insert_1/Insert to non-empty forward_list/Insert to random position/With reallocation finished!" << std::endl;
            }

            std::cout << "\t\tChecking test_insert_1/Insert to non-empty forward_list/Insert to random position finished!" << std::endl;
        }

        // insert to tail
        {
            std::cout << "\t\tStart checking test_insert_1/Insert to non-empty forward_list/Insert to tail!" << std::endl;

            // without reallocation
            {
                std::cout << "\t\t\tStart checking test_insert_1/Insert to non-empty forward_list/Insert to tail/Without reallocation!" << std::endl;

                // insertion size is zero
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    const auto new_size {this->generate_a_random_number(1, count - 1)};
                    const auto number {this->generate_a_random_number()};
                    forward_list<int> f(count, number);
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
                    const auto result {f.insert(new_size, this->generate_a_random_number(), 0)};
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
                    assert(result == f.end());
                    assert(result == f.cend());
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty forward_list/Insert to tail/Without reallocation/Insertion size is zero done." << std::endl;
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
                    forward_list<int> f(count + static_cast<size_t>(insertion_size) + spare, number);
                    auto erasion {&f.head};
                    for(auto i {count};; erasion = erasion->next) {
                        if(i-- == 0) {
                            auto backup {erasion->next};
                            erasion->next = nullptr;
                            f.node_size.allocator().deallocate(backup->node(), insertion_size + spare);
                            f.node_size() = count;
                            break;
                        }
                    }
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    const auto result {f.insert(count, number_2, insertion_size)};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number);
                    const auto end {advance(f.begin(), count)};
                    for(auto it {f.begin()}; it not_eq end; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {end}; it not_eq f.end(); ++it) {
                        assert(*it == number_2);
                    }
                    const auto cend {advance(f.cbegin(), count)};
                    for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {cend}; it not_eq f.cend(); ++it) {
                        assert(*it == number_2);
                    }
                    assert(result == advance(f.begin(), count));
                    assert(result == advance(f.cbegin(), count));
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty forward_list/Insert to tail/Without reallocation/Insertion size less equal to tail size done." << std::endl;
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
                    forward_list<int> f(count + static_cast<size_t>(insertion_size) + spare, number);
                    auto erasion {&f.head};
                    for(auto i {count};; erasion = erasion->next) {
                        if(i-- == 0) {
                            auto backup {erasion->next};
                            erasion->next = nullptr;
                            f.node_size.allocator().deallocate(backup->node(), static_cast<size_t>(insertion_size) + spare);
                            f.node_size() = count;
                            break;
                        }
                    }
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    const auto result {f.insert(count, number_2, insertion_size)};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number);
                    const auto end {advance(f.begin(), count)};
                    for(auto it {f.begin()}; it not_eq end; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {end}; it not_eq f.end(); ++it) {
                        assert(*it == number_2);
                    }
                    const auto cend {advance(f.cbegin(), count)};
                    for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {cend}; it not_eq f.cend(); ++it) {
                        assert(*it == number_2);
                    }
                    assert(result == advance(f.begin(), count));
                    assert(result == advance(f.cbegin(), count));
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty forward_list/Insert to tail/Without reallocation/Insertion size greater than tail size done." << std::endl;
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
                    forward_list<int> f(count + static_cast<size_t>(insertion_size), number);
                    auto erasion {&f.head};
                    for(auto i {count};; erasion = erasion->next) {
                        if(i-- == 0) {
                            auto backup {erasion->next};
                            erasion->next = nullptr;
                            f.node_size.allocator().deallocate(backup->node(), insertion_size);
                            f.node_size() = count;
                            break;
                        }
                    }
                    auto cursor {f.before_begin()};
                    for(auto i {0}; i < f.size(); ++i, ++cursor);
                    ++*cursor;
                    auto result {f.insert(count, *cursor, insertion_size)};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number);
                    const auto end {advance(f.begin(), count - 1)};
                    for(auto it {f.begin()}; it not_eq end; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {end}; it not_eq f.end(); ++it) {
                        assert(*it == number + 1);
                    }
                    const auto cend {advance(f.cbegin(), count - 1)};
                    for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {cend}; it not_eq f.cend(); ++it) {
                        assert(*it == number + 1);
                    }
                    assert(result == advance(f.begin(), count));
                    assert(result == advance(f.cbegin(), count));
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty forward_list/Insert to tail/Without reallocation/The value is from self done." << std::endl;
                }

                std::cout << "\t\t\tStart checking test_insert_1/Insert to non-empty forward_list/Insert to tail/Without reallocation finished!" << std::endl;
            }

            // with reallocation
            {
                std::cout << "\t\t\tStart checking test_insert_1/Insert to non-empty forward_list/Insert to tail/With reallocation!" << std::endl;

                // insertion size less equal to tail size
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    auto insertion_size {this->generate_a_random_number(1, count)};
                    const auto number {this->generate_a_random_number()};
                    forward_list<int> f(count, number);
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    const auto result {f.insert(count, number_2, insertion_size)};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number);
                    const auto end {advance(f.begin(), count)};
                    for(auto it {f.begin()}; it not_eq end; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {end}; it not_eq f.end(); ++it) {
                        assert(*it == number_2);
                    }
                    const auto cend {advance(f.cbegin(), count)};
                    for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {cend}; it not_eq f.cend(); ++it) {
                        assert(*it == number_2);
                    }
                    assert(result == advance(f.begin(), count));
                    assert(result == advance(f.cbegin(), count));
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty forward_list/Insert to tail/With reallocation/Insertion size less equal to tail size done." << std::endl;
                }

                // insertion size greater than tail size
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    const auto insertion_size {this->generate_a_random_number(count + 1)};
                    const auto number {this->generate_a_random_number()};
                    forward_list<int> f(count, number);
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    const auto result {f.insert(count, number_2, insertion_size)};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number);
                    const auto end {advance(f.begin(), count)};
                    for(auto it {f.begin()}; it not_eq end; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {end}; it not_eq f.end(); ++it) {
                        assert(*it == number_2);
                    }
                    const auto cend {advance(f.cbegin(), count)};
                    for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {cend}; it not_eq f.cend(); ++it) {
                        assert(*it == number_2);
                    }
                    assert(result == advance(f.begin(), count));
                    assert(result == advance(f.cbegin(), count));
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty forward_list/Insert to tail/With reallocation/Insertion size greater than tail size done." << std::endl;
                }

                // insertion size less equal to double capacity
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    auto insertion_size {this->generate_a_random_number(1, count)};
                    const auto number {this->generate_a_random_number()};
                    forward_list<int> f(count, number);
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    auto result {f.insert(count, number_2, insertion_size)};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number);
                    const auto end {advance(f.begin(), count)};
                    for(auto it {f.begin()}; it not_eq end; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {end}; it not_eq f.end(); ++it) {
                        assert(*it == number_2);
                    }
                    const auto cend {advance(f.cbegin(), count)};
                    for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {cend}; it not_eq f.cend(); ++it) {
                        assert(*it == number_2);
                    }
                    assert(result == advance(f.begin(), count));
                    assert(result == advance(f.cbegin(), count));
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty forward_list/Insert to tail/With reallocation/Insertion size less equal to double capacity done." << std::endl;
                }

                // insertion size greater than double capacity
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    auto insertion_size {this->generate_a_random_number(2 * count + 1)};
                    const auto number {this->generate_a_random_number()};
                    forward_list<int> f(count, number);
                    auto number_2 {this->generate_a_random_number()};
                    while(number == number_2) {
                        number_2 = this->generate_a_random_number();
                    }
                    auto result {f.insert(count, number_2, insertion_size)};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number);
                    const auto end {advance(f.begin(), count)};
                    for(auto it {f.begin()}; it not_eq end; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {end}; it not_eq f.end(); ++it) {
                        assert(*it == number_2);
                    }
                    const auto cend {advance(f.cbegin(), count)};
                    for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {cend}; it not_eq f.cend(); ++it) {
                        assert(*it == number_2);
                    }
                    assert(result == advance(f.begin(), count));
                    assert(result == advance(f.cbegin(), count));
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty forward_list/Insert to tail/With reallocation/Insertion size greater than double capacity done." << std::endl;
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
                    forward_list<int> f(count, number);
                    auto cursor {f.before_begin()};
                    for(auto i {0}; i < f.size(); ++i, ++cursor);
                    ++*cursor;
                    auto result {f.insert(count, *cursor, insertion_size)};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number);
                    const auto end {advance(f.begin(), count - 1)};
                    for(auto it {f.begin()}; it not_eq end; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {end}; it not_eq f.end(); ++it) {
                        assert(*it == number + 1);
                    }
                    const auto cend {advance(f.cbegin(), count - 1)};
                    for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {cend}; it not_eq f.cend(); ++it) {
                        assert(*it == number + 1);
                    }
                    assert(result == advance(f.begin(), count));
                    assert(result == advance(f.cbegin(), count));
                    std::cout << "\t\t\t\tChecking test_insert_1/Insert to non-empty forward_list/Insert to tail/With reallocation/The value is from self done." << std::endl;
                }

                std::cout << "\t\t\tStart checking test_insert_1/Insert to non-empty forward_list/Insert to tail/With reallocation finished!" << std::endl;
            }

            std::cout << "\t\tChecking test_insert_1/Insert to non-empty forward_list/Insert to tail finished!" << std::endl;
        }

        std::cout << "\tChecking test_insert_1/Insert to non-empty forward_list finished!" << std::endl;
    }

    std::cout << "Checking iterator insert(size_type, const_reference, size_type) for ds::forward_list finished!" << std::endl;
}
void forward_list_correctness::test_insert_after_2() {
    std::cout << "Start checking iterator insert(size_type, InputIterator, InputIterator) for ds::forward_list!" << std::endl;

    // insert to empty forward_list
    {
        std::cout << "\tStart checking test_insert_2/Insert to empty forward_list for ds::forward_list!" << std::endl;

        // insertion size equal to zero
        {
            forward_list<int> f {};
            const auto result {f.insert(0, int_input_iterator {}, int_input_iterator {})};
            assert(f.size() == 0);
            assert(f.empty());
            assert(f.begin() == f.end());
            assert(f.cbegin() == f.cend());
            assert(result == f.begin());
            assert(result == f.cbegin());
            std::cout << "\t\tChecking test_insert_2/Insert to empty forward_list/Insertion size not equal to zero done." << std::endl;
        }

        // insertion size not equal to zero
        {
            forward_list<int> f {};
            auto insertion_size {this->generate_count()};
            while(insertion_size == 0) {
                insertion_size = this->generate_count();
            }
            const auto numbers {this->generate_random_sequence(insertion_size)};
            auto stream {this->to_input_iterator(numbers)};
            const auto result {f.insert(0, int_input_iterator {stream}, int_input_iterator {})};
            assert(f.size() == insertion_size);
            assert(not f.empty());
            assert(advance(f.begin(), insertion_size) == f.end());
            assert(advance(f.cbegin(), insertion_size) == f.cend());
            assert(f.front() == numbers.front());
            auto i {0uz};
            for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                assert(*it == numbers[i++]);
            }
            i = 0;
            for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                assert(*it == numbers[i++]);
            }
            assert(result == f.begin());
            assert(result == f.cbegin());
            std::cout << "\t\tChecking test_insert_2/Insert to empty forward_list/Insertion size not equal to zero done." << std::endl;
        }

        std::cout << "\tChecking test_insert_2/Insert to empty forward_list for ds::forward_list finished!" << std::endl;
    }

    // insert to non-empty forward_list
    {
        std::cout << "\tStart checking test_insert_2/Insert to non-empty forward_list!" << std::endl;

        // insert to head
        {
            std::cout << "\t\tStart checking test_insert_2/Insert to non-empty forward_list/Insert to head!" << std::endl;

            // without reallocation
            {
                std::cout << "\t\t\tStart checking test_insert_2/Insert to non-empty forward_list/Insert to head/Without reallocation!" << std::endl;

                // insertion size is zero
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    const auto new_size {this->generate_a_random_number(1, count - 1)};
                    const auto number {this->generate_a_random_number()};
                    forward_list<int> f(count, number);
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
                    const auto result {f.insert(0, int_input_iterator {}, int_input_iterator {})};
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
                    assert(result == f.begin());
                    assert(result == f.cbegin());
                    std::cout << "\t\t\t\tChecking test_insert_2/Insert to non-empty forward_list/Insert to head/Without reallocation/Insertion size is zero done." << std::endl;
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
                    forward_list<int> f(count + static_cast<size_t>(insertion_size) + spare, number);
                    auto erasion {&f.head};
                    for(auto i {count};; erasion = erasion->next) {
                        if(i-- == 0) {
                            auto backup {erasion->next};
                            erasion->next = nullptr;
                            f.node_size.allocator().deallocate(backup->node(), insertion_size + spare);
                            f.node_size() = count;
                            break;
                        }
                    }
                    const auto result {f.insert(0, int_input_iterator {stream}, int_input_iterator {})};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == numbers.front());
                    auto number_i {0uz};
                    const auto end {advance(f.begin(), insertion_size)};
                    for(auto it {f.begin()}; it not_eq end; ++it) {
                        assert(*it == numbers[number_i++]);
                    }
                    for(auto it {end}; it not_eq f.end(); ++it) {
                        assert(*it == number);
                    }
                    number_i = 0;
                    const auto cend {advance(f.cbegin(), insertion_size)};
                    for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                        assert(*it == numbers[number_i++]);
                    }
                    for(auto it {cend}; it not_eq f.cend(); ++it) {
                        assert(*it == number);
                    }
                    assert(result == f.begin());
                    assert(result == f.cbegin());
                    std::cout << "\t\t\t\tChecking test_insert_2/Insert to non-empty forward_list/Insert to head/Without reallocation/Insertion size less equal to tail size done." << std::endl;
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
                    forward_list<int> f(count + static_cast<size_t>(insertion_size) + spare, number);
                    auto erasion {&f.head};
                    for(auto i {count};; erasion = erasion->next) {
                        if(i-- == 0) {
                            auto backup {erasion->next};
                            erasion->next = nullptr;
                            f.node_size.allocator().deallocate(backup->node(), static_cast<size_t>(insertion_size) + spare);
                            f.node_size() = count;
                            break;
                        }
                    }
                    const auto result {f.insert(0, int_input_iterator {stream}, int_input_iterator {})};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == numbers.front());
                    auto number_i {0uz};
                    const auto end {advance(f.begin(), insertion_size)};
                    for(auto it {f.begin()}; it not_eq end; ++it) {
                        assert(*it == numbers[number_i++]);
                    }
                    for(auto it {end}; it not_eq f.end(); ++it) {
                        assert(*it == number);
                    }
                    number_i = 0;
                    const auto cend {advance(f.cbegin(), insertion_size)};
                    for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                        assert(*it == numbers[number_i++]);
                    }
                    for(auto it {cend}; it not_eq f.cend(); ++it) {
                        assert(*it == number);
                    }
                    assert(result == f.begin());
                    assert(result == f.cbegin());
                    std::cout << "\t\t\t\tChecking test_insert_2/Insert to non-empty forward_list/Insert to head/Without reallocation/Insertion size greater than tail size done." << std::endl;
                }

                std::cout << "\t\t\tStart checking test_insert_2/Insert to non-empty forward_list/Insert to head/Without reallocation finished!" << std::endl;
            }

            // with reallocation
            {
                std::cout << "\t\t\tStart checking test_insert_2/Insert to non-empty forward_list/Insert to head/With reallocation!" << std::endl;

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
                    forward_list<int> f(count, number);
                    const auto result {f.insert(0, int_input_iterator {stream}, int_input_iterator {})};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == numbers.front());
                    auto number_i {0uz};
                    const auto end {advance(f.begin(), insertion_size)};
                    for(auto it {f.begin()}; it not_eq end; ++it) {
                        assert(*it == numbers[number_i++]);
                    }
                    for(auto it {end}; it not_eq f.end(); ++it) {
                        assert(*it == number);
                    }
                    number_i = 0;
                    const auto cend {advance(f.cbegin(), insertion_size)};
                    for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                        assert(*it == numbers[number_i++]);
                    }
                    for(auto it {cend}; it not_eq f.cend(); ++it) {
                        assert(*it == number);
                    }
                    assert(result == f.begin());
                    assert(result == f.cbegin());
                    std::cout << "\t\t\t\tChecking test_insert_2/Insert to non-empty forward_list/Insert to head/With reallocation/Insertion size less equal to tail size done." << std::endl;
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
                    forward_list<int> f(count, number);
                    const auto result {f.insert(0, int_input_iterator {stream}, int_input_iterator {})};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == numbers.front());
                    auto number_i {0uz};
                    const auto end {advance(f.begin(), insertion_size)};
                    for(auto it {f.begin()}; it not_eq end; ++it) {
                        assert(*it == numbers[number_i++]);
                    }
                    for(auto it {end}; it not_eq f.end(); ++it) {
                        assert(*it == number);
                    }
                    number_i = 0;
                    const auto cend {advance(f.cbegin(), insertion_size)};
                    for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                        assert(*it == numbers[number_i++]);
                    }
                    for(auto it {cend}; it not_eq f.cend(); ++it) {
                        assert(*it == number);
                    }
                    assert(result == f.begin());
                    assert(result == f.cbegin());
                    std::cout << "\t\t\t\tChecking test_insert_2/Insert to non-empty forward_list/Insert to head/With reallocation/Insertion size greater than tail size done." << std::endl;
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
                    forward_list<int> f(count, number);
                    auto result {f.insert(0, int_input_iterator {stream}, int_input_iterator {})};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == numbers.front());
                    auto number_i {0uz};
                    const auto end {advance(f.begin(), insertion_size)};
                    for(auto it {f.begin()}; it not_eq end; ++it) {
                        assert(*it == numbers[number_i++]);
                    }
                    for(auto it {end}; it not_eq f.end(); ++it) {
                        assert(*it == number);
                    }
                    number_i = 0;
                    const auto cend {advance(f.cbegin(), insertion_size)};
                    for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                        assert(*it == numbers[number_i++]);
                    }
                    for(auto it {cend}; it not_eq f.cend(); ++it) {
                        assert(*it == number);
                    }
                    assert(result == f.begin());
                    assert(result == f.cbegin());
                    std::cout << "\t\t\t\tChecking test_insert_2/Insert to non-empty forward_list/Insert to head/With reallocation/Insertion size less equal to double capacity done." << std::endl;
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
                    forward_list<int> f(count, number);
                    auto result {f.insert(0, int_input_iterator {stream}, int_input_iterator {})};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == numbers.front());
                    auto number_i {0uz};
                    const auto end {advance(f.begin(), insertion_size)};
                    for(auto it {f.begin()}; it not_eq end; ++it) {
                        assert(*it == numbers[number_i++]);
                    }
                    for(auto it {end}; it not_eq f.end(); ++it) {
                        assert(*it == number);
                    }
                    number_i = 0;
                    const auto cend {advance(f.cbegin(), insertion_size)};
                    for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                        assert(*it == numbers[number_i++]);
                    }
                    for(auto it {cend}; it not_eq f.cend(); ++it) {
                        assert(*it == number);
                    }
                    assert(result == f.begin());
                    assert(result == f.cbegin());
                    std::cout << "\t\t\t\tChecking test_insert_2/Insert to non-empty forward_list/Insert to head/With reallocation/Insertion size greater than double capacity done." << std::endl;
                }

                std::cout << "\t\t\tStart checking test_insert_2/Insert to non-empty forward_list/Insert to head/With reallocation finished!" << std::endl;
            }

            std::cout << "\t\tChecking test_insert_2/Insert to non-empty forward_list/Insert to head finished!" << std::endl;
        }

        // insert to random position
        {
            std::cout << "\t\tStart checking test_insert_2/Insert to non-empty forward_list/Insert to random position!" << std::endl;

            // without reallocation
            {
                std::cout << "\t\t\tStart checking test_insert_2/Insert to non-empty forward_list/Insert to random position/Without reallocation!" << std::endl;

                // insertion size is zero
                {
                    auto count {this->generate_count()};
                    while(count <= 2) {
                        count = this->generate_count();
                    }
                    const auto new_size {this->generate_a_random_number(2, count - 1)};
                    const auto number {this->generate_a_random_number()};
                    const auto insertion_position {this->generate_a_random_number(1, new_size - 1)};
                    forward_list<int> f(count, number);
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
                    const auto result {f.insert(insertion_position, int_input_iterator {}, int_input_iterator {})};
                    assert(f.size() == new_size);
                    assert(not f.empty());
                    assert(advance(f.begin(), new_size) == f.end());
                    assert(advance(f.cbegin(), new_size) == f.cend());
                    assert(f.front() == number);
                    for(auto it {advance(f.begin(), 1)}; it not_eq f.end(); ++it) {
                        assert(*it == number);
                    }
                    for(auto it {advance(f.cbegin(), 1)}; it not_eq f.cend(); ++it) {
                        assert(*it == number);
                    }
                    assert(result == advance(f.begin(), insertion_position));
                    assert(result == advance(f.cbegin(), insertion_position));
                    std::cout << "\t\t\t\tChecking test_insert_2/Insert to non-empty forward_list/Insert to random position/Without reallocation/Insertion size is zero done." << std::endl;
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
                    forward_list<int> f(count + static_cast<size_t>(insertion_size) + spare, number);
                    auto erasion {&f.head};
                    for(auto i {count};; erasion = erasion->next) {
                        if(i-- == 0) {
                            auto backup {erasion->next};
                            erasion->next = nullptr;
                            f.node_size.allocator().deallocate(backup->node(), insertion_size + spare);
                            f.node_size() = count;
                            break;
                        }
                    }
                    const auto result {f.insert(insertion_position, int_input_iterator {stream}, int_input_iterator {})};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number);
                    auto numbers_i {0uz};
                    const auto end1 {advance(f.begin(), insertion_position)};
                    for(auto it {f.begin()}; it not_eq end1; ++it) {
                        assert(*it == number);
                    }
                    const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                    for(auto it {end1}; it not_eq end2; ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    for(auto it {end2}; it not_eq f.end(); ++it) {
                        assert(*it == number);
                    }
                    const auto cend1 {advance(f.cbegin(), insertion_position)};
                    for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = 0;
                    const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                    for(auto it {cend1}; it not_eq cend2; ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    for(auto it {advance(f.cbegin(), insertion_position + insertion_size)}; it not_eq f.cend(); ++it) {
                        assert(*it == number);
                    }
                    assert(result == advance(f.begin(), insertion_position));
                    assert(result == advance(f.cbegin(), insertion_position));
                    std::cout << "\t\t\tChecking test_insert_2/Insert to non-empty forward_list/Insert to random position/Without reallocation/Insertion size less equal to tail size done." << std::endl;
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
                    forward_list<int> f(count + static_cast<size_t>(insertion_size) + spare, number);
                    auto erasion {&f.head};
                    for(auto i {count};; erasion = erasion->next) {
                        if(i-- == 0) {
                            auto backup {erasion->next};
                            erasion->next = nullptr;
                            f.node_size.allocator().deallocate(backup->node(), static_cast<size_t>(insertion_size) + spare);
                            f.node_size() = count;
                            break;
                        }
                    }
                    const auto result {f.insert(insertion_position, int_input_iterator {stream}, int_input_iterator {})};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number);
                    auto numbers_i {0uz};
                    const auto end1 {advance(f.begin(), insertion_position)};
                    for(auto it {f.begin()}; it not_eq end1; ++it) {
                        assert(*it == number);
                    }
                    const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                    for(auto it {end1}; it not_eq end2; ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    for(auto it {end2}; it not_eq f.end(); ++it) {
                        assert(*it == number);
                    }
                    const auto cend1 {advance(f.cbegin(), insertion_position)};
                    for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = 0;
                    const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                    for(auto it {cend1}; it not_eq cend2; ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    for(auto it {advance(f.cbegin(), insertion_position + insertion_size)}; it not_eq f.cend(); ++it) {
                        assert(*it == number);
                    }
                    assert(result == advance(f.begin(), insertion_position));
                    assert(result == advance(f.cbegin(), insertion_position));
                    std::cout << "\t\t\tChecking test_insert_2/Insert to non-empty forward_list/Insert to random position/Without reallocation/Insertion size greater than tail size done." << std::endl;
                }

                std::cout << "\t\t\tStart checking test_insert_2/Insert to non-empty forward_list/Insert to random position/Without reallocation finished!" << std::endl;
            }

            // with reallocation
            {
                std::cout << "\t\t\tStart checking test_insert_2/Insert to non-empty forward_list/Insert to random position/With reallocation!" << std::endl;

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
                    forward_list<int> f(count, number);
                    const auto result {f.insert(insertion_position, int_input_iterator {stream}, int_input_iterator {})};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number);
                    auto numbers_i {0uz};
                    const auto end1 {advance(f.begin(), insertion_position)};
                    for(auto it {f.begin()}; it not_eq end1; ++it) {
                        assert(*it == number);
                    }
                    const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                    for(auto it {end1}; it not_eq end2; ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    for(auto it {end2}; it not_eq f.end(); ++it) {
                        assert(*it == number);
                    }
                    const auto cend1 {advance(f.cbegin(), insertion_position)};
                    for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = 0;
                    const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                    for(auto it {cend1}; it not_eq cend2; ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    for(auto it {advance(f.cbegin(), insertion_position + insertion_size)}; it not_eq f.cend(); ++it) {
                        assert(*it == number);
                    }
                    assert(result == advance(f.begin(), insertion_position));
                    assert(result == advance(f.cbegin(), insertion_position));
                    std::cout << "\t\t\tChecking test_insert_2/Insert to non-empty forward_list/Insert to random position/With reallocation/Insertion size less equal to tail size done." << std::endl;
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
                    forward_list<int> f(count, number);
                    const auto result {f.insert(insertion_position, int_input_iterator {stream}, int_input_iterator {})};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number);
                    auto numbers_i {0uz};
                    const auto end1 {advance(f.begin(), insertion_position)};
                    for(auto it {f.begin()}; it not_eq end1; ++it) {
                        assert(*it == number);
                    }
                    const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                    for(auto it {end1}; it not_eq end2; ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    for(auto it {end2}; it not_eq f.end(); ++it) {
                        assert(*it == number);
                    }
                    const auto cend1 {advance(f.cbegin(), insertion_position)};
                    for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = 0;
                    const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                    for(auto it {cend1}; it not_eq cend2; ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    for(auto it {advance(f.cbegin(), insertion_position + insertion_size)}; it not_eq f.cend(); ++it) {
                        assert(*it == number);
                    }
                    assert(result == advance(f.begin(), insertion_position));
                    assert(result == advance(f.cbegin(), insertion_position));
                    std::cout << "\t\t\tChecking test_insert_2/Insert to non-empty forward_list/Insert to random position/With reallocation/Insertion size greater than tail size done." << std::endl;
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
                    forward_list<int> f(count, number);
                    auto result {f.insert(insertion_position, int_input_iterator {stream}, int_input_iterator {})};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number);
                    auto numbers_i {0uz};
                    const auto end1 {advance(f.begin(), insertion_position)};
                    for(auto it {f.begin()}; it not_eq end1; ++it) {
                        assert(*it == number);
                    }
                    const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                    for(auto it {end1}; it not_eq end2; ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    for(auto it {end2}; it not_eq f.end(); ++it) {
                        assert(*it == number);
                    }
                    const auto cend1 {advance(f.cbegin(), insertion_position)};
                    for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = 0;
                    const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                    for(auto it {cend1}; it not_eq cend2; ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    for(auto it {advance(f.cbegin(), insertion_position + insertion_size)}; it not_eq f.cend(); ++it) {
                        assert(*it == number);
                    }
                    assert(result == advance(f.begin(), insertion_position));
                    assert(result == advance(f.cbegin(), insertion_position));
                    std::cout << "\t\t\tChecking test_insert_2/Insert to non-empty forward_list/Insert to random position/With reallocation/Insertion size less equal to double capacity done." << std::endl;
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
                    forward_list<int> f(count, number);
                    auto result {f.insert(insertion_position, int_input_iterator {stream}, int_input_iterator {})};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number);
                    auto numbers_i {0uz};
                    const auto end1 {advance(f.begin(), insertion_position)};
                    for(auto it {f.begin()}; it not_eq end1; ++it) {
                        assert(*it == number);
                    }
                    const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                    for(auto it {end1}; it not_eq end2; ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    for(auto it {end2}; it not_eq f.end(); ++it) {
                        assert(*it == number);
                    }
                    const auto cend1 {advance(f.cbegin(), insertion_position)};
                    for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = 0;
                    const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                    for(auto it {cend1}; it not_eq cend2; ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    for(auto it {advance(f.cbegin(), insertion_position + insertion_size)}; it not_eq f.cend(); ++it) {
                        assert(*it == number);
                    }
                    assert(result == advance(f.begin(), insertion_position));
                    assert(result == advance(f.cbegin(), insertion_position));
                    std::cout << "\t\t\tChecking test_insert_2/Insert to non-empty forward_list/Insert to random position/With reallocation/Insertion size greater than double capacity done." << std::endl;
                }

                std::cout << "\t\t\tStart checking test_insert_2/Insert to non-empty forward_list/Insert to random position/With reallocation finished!" << std::endl;
            }

            std::cout << "\t\tChecking test_insert_2/Insert to non-empty forward_list/Insert to random position finished!" << std::endl;
        }

        // insert to tail
        {
            std::cout << "\t\tStart checking test_insert_2/Insert to non-empty forward_list/Insert to tail!" << std::endl;

            // without reallocation
            {
                std::cout << "\t\t\tStart checking test_insert_2/Insert to non-empty forward_list/Insert to tail/Without reallocation!" << std::endl;

                // insertion size is zero
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    const auto new_size {this->generate_a_random_number(1, count - 1)};
                    const auto number {this->generate_a_random_number()};
                    forward_list<int> f(count, number);
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
                    const auto result {f.insert(new_size, int_input_iterator {}, int_input_iterator {})};
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
                    assert(result == f.end());
                    assert(result == f.cend());
                    std::cout << "\t\t\t\tChecking test_insert_2/Insert to non-empty forward_list/Insert to tail/Without reallocation/Insertion size is zero done." << std::endl;
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
                    forward_list<int> f(count + static_cast<size_t>(insertion_size) + spare, number);
                    auto erasion {&f.head};
                    for(auto i {count};; erasion = erasion->next) {
                        if(i-- == 0) {
                            auto backup {erasion->next};
                            erasion->next = nullptr;
                            f.node_size.allocator().deallocate(backup->node(), insertion_size + spare);
                            f.node_size() = count;
                            break;
                        }
                    }
                    const auto result {f.insert(count, int_input_iterator {stream}, int_input_iterator {})};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number);
                    auto numbers_i {0uz};
                    const auto end {advance(f.begin(), count)};
                    for(auto it {f.begin()}; it not_eq end; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {end}; it not_eq f.end(); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    const auto cend {advance(f.cbegin(), count)};
                    for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = 0;
                    for(auto it {cend}; it not_eq f.cend(); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    assert(result == advance(f.begin(), count));
                    assert(result == advance(f.cbegin(), count));
                    std::cout << "\t\t\t\tChecking test_insert_2/Insert to non-empty forward_list/Insert to tail/Without reallocation/Insertion size less equal to tail size done." << std::endl;
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
                    forward_list<int> f(count + static_cast<size_t>(insertion_size) + spare, number);
                    auto erasion {&f.head};
                    for(auto i {count};; erasion = erasion->next) {
                        if(i-- == 0) {
                            auto backup {erasion->next};
                            erasion->next = nullptr;
                            f.node_size.allocator().deallocate(backup->node(), static_cast<size_t>(insertion_size) + spare);
                            f.node_size() = count;
                            break;
                        }
                    }
                    const auto result {f.insert(count, int_input_iterator {stream}, int_input_iterator {})};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number);
                    auto numbers_i {0uz};
                    const auto end {advance(f.begin(), count)};
                    for(auto it {f.begin()}; it not_eq end; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {end}; it not_eq f.end(); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    const auto cend {advance(f.cbegin(), count)};
                    for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = 0;
                    for(auto it {cend}; it not_eq f.cend(); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    assert(result == advance(f.begin(), count));
                    assert(result == advance(f.cbegin(), count));
                    std::cout << "\t\t\t\tChecking test_insert_2/Insert to non-empty forward_list/Insert to tail/Without reallocation/Insertion size greater than tail size done." << std::endl;
                }

                std::cout << "\t\t\tStart checking test_insert_2/Insert to non-empty forward_list/Insert to tail/Without reallocation finished!" << std::endl;
            }

            // with reallocation
            {
                std::cout << "\t\t\tStart checking test_insert_2/Insert to non-empty forward_list/Insert to tail/With reallocation!" << std::endl;

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
                    forward_list<int> f(count, number);
                    const auto result {f.insert(count, int_input_iterator {stream}, int_input_iterator {})};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number);
                    auto numbers_i {0uz};
                    const auto end {advance(f.begin(), count)};
                    for(auto it {f.begin()}; it not_eq end; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {end}; it not_eq f.end(); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    const auto cend {advance(f.cbegin(), count)};
                    for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = 0;
                    for(auto it {cend}; it not_eq f.cend(); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    assert(result == advance(f.begin(), count));
                    assert(result == advance(f.cbegin(), count));
                    std::cout << "\t\t\t\tChecking test_insert_2/Insert to non-empty forward_list/Insert to tail/With reallocation/Insertion size less equal to tail size done." << std::endl;
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
                    forward_list<int> f(count, number);
                    const auto result {f.insert(count, int_input_iterator {stream}, int_input_iterator {})};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number);
                    auto numbers_i {0uz};
                    const auto end {advance(f.begin(), count)};
                    for(auto it {f.begin()}; it not_eq end; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {end}; it not_eq f.end(); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    const auto cend {advance(f.cbegin(), count)};
                    for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = 0;
                    for(auto it {cend}; it not_eq f.cend(); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    assert(result == advance(f.begin(), count));
                    assert(result == advance(f.cbegin(), count));
                    std::cout << "\t\t\t\tChecking test_insert_2/Insert to non-empty forward_list/Insert to tail/With reallocation/Insertion size greater than tail size done." << std::endl;
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
                    forward_list<int> f(count, number);
                    auto result {f.insert(count, int_input_iterator {stream}, int_input_iterator {})};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number);
                    auto numbers_i {0uz};
                    const auto end {advance(f.begin(), count)};
                    for(auto it {f.begin()}; it not_eq end; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {end}; it not_eq f.end(); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    const auto cend {advance(f.cbegin(), count)};
                    for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = 0;
                    for(auto it {cend}; it not_eq f.cend(); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    assert(result == advance(f.begin(), count));
                    assert(result == advance(f.cbegin(), count));
                    std::cout << "\t\t\t\tChecking test_insert_2/Insert to non-empty forward_list/Insert to tail/With reallocation/Insertion size less equal to double capacity done." << std::endl;
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
                    forward_list<int> f(count, number);
                    auto result {f.insert(count, int_input_iterator {stream}, int_input_iterator {})};
                    assert(f.size() == count + static_cast<size_t>(insertion_size));
                    assert(not f.empty());
                    assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                    assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                    assert(f.front() == number);
                    auto numbers_i {0uz};
                    const auto end {advance(f.begin(), count)};
                    for(auto it {f.begin()}; it not_eq end; ++it) {
                        assert(*it == number);
                    }
                    for(auto it {end}; it not_eq f.end(); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    const auto cend {advance(f.cbegin(), count)};
                    for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                        assert(*it == number);
                    }
                    numbers_i = 0;
                    for(auto it {cend}; it not_eq f.cend(); ++it) {
                        assert(*it == numbers[numbers_i++]);
                    }
                    assert(result == advance(f.begin(), count));
                    assert(result == advance(f.cbegin(), count));
                    std::cout << "\t\t\t\tChecking test_insert_2/Insert to non-empty forward_list/Insert to tail/With reallocation/Insertion size greater than double capacity done." << std::endl;
                }

                std::cout << "\t\t\tStart checking test_insert_2/Insert to non-empty forward_list/Insert to tail/With reallocation finished!" << std::endl;
            }

            std::cout << "\t\tChecking test_insert_2/Insert to non-empty forward_list/Insert to tail finished!" << std::endl;
        }

        std::cout << "\tChecking test_insert_2/Insert to non-empty forward_list finished!" << std::endl;
    }

    std::cout << "Checking iterator insert(size_type, InputIterator, InputIterator) for ds::forward_list finished!" << std::endl;
}
void forward_list_correctness::test_insert_after_3() {
    std::cout << "Start checking iterator insert(size_type, ForwardIterator, ForwardIterator) for ds::forward_list!" << std::endl;

    // forward iterator
    {
        std::cout << "\tStart checking test_insert_3/Forward iterator for ds::forward_list!" << std::endl;

        // insert to empty forward_list
        {
            std::cout << "\t\tStart checking test_insert_3/Forward iteratorInsert to empty forward_list for ds::forward_list!" << std::endl;

            // insertion size equal to zero
            {
                forward_list<int> f {};
                const auto result {f.insert(0, int_forward_iterator {}, int_forward_iterator {})};
                assert(f.size() == 0);
                assert(f.empty());
                assert(f.begin() == f.end());
                assert(f.cbegin() == f.cend());
                assert(result == f.begin());
                assert(result == f.cbegin());
                std::cout << "\t\t\tChecking test_insert_3/Forward iteratorInsert to empty forward_list/Insertion size not equal to zero done." << std::endl;
            }

            // insertion size not equal to zero
            {
                forward_list<int> f {};
                auto insertion_size {this->generate_count()};
                while(insertion_size == 0) {
                    insertion_size = this->generate_count();
                }
                const auto numbers {this->generate_random_sequence(insertion_size)};
                auto l {this->to_forward_iterator(numbers)};
                const auto result {f.insert(0, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                assert(f.size() == insertion_size);
                assert(not f.empty());
                assert(advance(f.begin(), insertion_size) == f.end());
                assert(advance(f.cbegin(), insertion_size) == f.cend());
                assert(f.front() == numbers.front());
                auto i {0uz};
                for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                    assert(*it == numbers[i++]);
                }
                i = 0;
                for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                    assert(*it == numbers[i++]);
                }
                assert(result == f.begin());
                assert(result == f.cbegin());
                std::cout << "\t\t\tChecking test_insert_3/Forward iteratorInsert to empty forward_list/Insertion size not equal to zero done." << std::endl;
            }

            std::cout << "\t\tChecking test_insert_3/Forward iteratorInsert to empty forward_list for ds::forward_list finished!" << std::endl;
        }

        // insert to non-empty forward_list
        {
            std::cout << "\t\tStart checking test_insert_3/Forward iteratorInsert to non-empty forward_list!" << std::endl;

            // insert to head
            {
                std::cout << "\t\t\tStart checking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to head!" << std::endl;

                // without reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to head/Without reallocation!" << std::endl;

                    // insertion size is zero
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto new_size {this->generate_a_random_number(1, count - 1)};
                        const auto number {this->generate_a_random_number()};
                        forward_list<int> f(count, number);
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
                        const auto result {f.insert(0, int_forward_iterator {}, int_forward_iterator {})};
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
                        assert(result == f.begin());
                        assert(result == f.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to head/Without reallocation/Insertion size is zero done." << std::endl;
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
                        forward_list<int> f(count + static_cast<size_t>(insertion_size) + spare, number);
                        auto erasion {&f.head};
                        for(auto i {count};; erasion = erasion->next) {
                            if(i-- == 0) {
                                auto backup {erasion->next};
                                erasion->next = nullptr;
                                f.node_size.allocator().deallocate(backup->node(), insertion_size + spare);
                                f.node_size() = count;
                                break;
                            }
                        }
                        const auto result {f.insert(0, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == numbers.front());
                        auto number_i {0uz};
                        const auto end {advance(f.begin(), insertion_size)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        const auto cend {advance(f.cbegin(), insertion_size)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == f.begin());
                        assert(result == f.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to head/Without reallocation/Insertion size less equal to tail size done." << std::endl;
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
                        forward_list<int> f(count + static_cast<size_t>(insertion_size) + spare, number);
                        auto erasion {&f.head};
                        for(auto i {count};; erasion = erasion->next) {
                            if(i-- == 0) {
                                auto backup {erasion->next};
                                erasion->next = nullptr;
                                f.node_size.allocator().deallocate(backup->node(), static_cast<size_t>(insertion_size) + spare);
                                f.node_size() = count;
                                break;
                            }
                        }
                        const auto result {f.insert(0, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == numbers.front());
                        auto number_i {0uz};
                        const auto end {advance(f.begin(), insertion_size)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        const auto cend {advance(f.cbegin(), insertion_size)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == f.begin());
                        assert(result == f.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to head/Without reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to head/Without reallocation finished!" << std::endl;
                }

                // with reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to head/With reallocation!" << std::endl;

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
                        forward_list<int> f(count, number);
                        const auto result {f.insert(0, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == numbers.front());
                        auto number_i {0uz};
                        const auto end {advance(f.begin(), insertion_size)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        const auto cend {advance(f.cbegin(), insertion_size)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == f.begin());
                        assert(result == f.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to head/With reallocation/Insertion size less equal to tail size done." << std::endl;
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
                        forward_list<int> f(count, number);
                        const auto result {f.insert(0, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == numbers.front());
                        auto number_i {0uz};
                        const auto end {advance(f.begin(), insertion_size)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        const auto cend {advance(f.cbegin(), insertion_size)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == f.begin());
                        assert(result == f.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to head/With reallocation/Insertion size greater than tail size done." << std::endl;
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
                        forward_list<int> f(count, number);
                        auto result {f.insert(0, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == numbers.front());
                        auto number_i {0uz};
                        const auto end {advance(f.begin(), insertion_size)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        const auto cend {advance(f.cbegin(), insertion_size)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == f.begin());
                        assert(result == f.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to head/With reallocation/Insertion size less equal to double capacity done." << std::endl;
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
                        forward_list<int> f(count, number);
                        auto result {f.insert(0, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == numbers.front());
                        auto number_i {0uz};
                        const auto end {advance(f.begin(), insertion_size)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        const auto cend {advance(f.cbegin(), insertion_size)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == f.begin());
                        assert(result == f.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to head/With reallocation/Insertion size greater than double capacity done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to head/With reallocation finished!" << std::endl;
                }

                std::cout << "\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to head finished!" << std::endl;
            }

            // insert to random position
            {
                std::cout << "\t\t\tStart checking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to random position!" << std::endl;

                // without reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to random position/Without reallocation!" << std::endl;

                    // insertion size is zero
                    {
                        auto count {this->generate_count()};
                        while(count <= 2) {
                            count = this->generate_count();
                        }
                        const auto new_size {this->generate_a_random_number(2, count - 1)};
                        const auto number {this->generate_a_random_number()};
                        const auto insertion_position {this->generate_a_random_number(1, new_size - 1)};
                        forward_list<int> f(count, number);
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
                        const auto result {f.insert(insertion_position, int_forward_iterator {}, int_forward_iterator {})};
                        assert(f.size() == new_size);
                        assert(not f.empty());
                        assert(advance(f.begin(), new_size) == f.end());
                        assert(advance(f.cbegin(), new_size) == f.cend());
                        assert(f.front() == number);
                        for(auto it {advance(f.begin(), 1)}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {advance(f.cbegin(), 1)}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == advance(f.begin(), insertion_position));
                        assert(result == advance(f.cbegin(), insertion_position));
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to random position/Without reallocation/Insertion size is zero done." << std::endl;
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
                        forward_list<int> f(count + static_cast<size_t>(insertion_size) + spare, number);
                        auto erasion {&f.head};
                        for(auto i {count};; erasion = erasion->next) {
                            if(i-- == 0) {
                                auto backup {erasion->next};
                                erasion->next = nullptr;
                                f.node_size.allocator().deallocate(backup->node(), insertion_size + spare);
                                f.node_size() = count;
                                break;
                            }
                        }
                        const auto result {f.insert(insertion_position, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end1 {advance(f.begin(), insertion_position)};
                        for(auto it {f.begin()}; it not_eq end1; ++it) {
                            assert(*it == number);
                        }
                        const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                        for(auto it {end1}; it not_eq end2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {end2}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        const auto cend1 {advance(f.cbegin(), insertion_position)};
                        for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                        for(auto it {cend1}; it not_eq cend2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {cend2}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == advance(f.begin(), insertion_position));
                        assert(result == advance(f.cbegin(), insertion_position));
                        std::cout << "\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to random position/Without reallocation/Insertion size less equal to tail size done." << std::endl;
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
                        forward_list<int> f(count + static_cast<size_t>(insertion_size) + spare, number);
                        auto erasion {&f.head};
                        for(auto i {count};; erasion = erasion->next) {
                            if(i-- == 0) {
                                auto backup {erasion->next};
                                erasion->next = nullptr;
                                f.node_size.allocator().deallocate(backup->node(), static_cast<size_t>(insertion_size) + spare);
                                f.node_size() = count;
                                break;
                            }
                        }
                        const auto result {f.insert(insertion_position, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end1 {advance(f.begin(), insertion_position)};
                        for(auto it {f.begin()}; it not_eq end1; ++it) {
                            assert(*it == number);
                        }
                        const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                        for(auto it {end1}; it not_eq end2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {end2}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        const auto cend1 {advance(f.cbegin(), insertion_position)};
                        for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                        for(auto it {cend1}; it not_eq cend2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {cend2}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == advance(f.begin(), insertion_position));
                        assert(result == advance(f.cbegin(), insertion_position));
                        std::cout << "\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to random position/Without reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to random position/Without reallocation finished!" << std::endl;
                }

                // with reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to random position/With reallocation!" << std::endl;

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
                        forward_list<int> f(count, number);
                        const auto result {f.insert(insertion_position, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end1 {advance(f.begin(), insertion_position)};
                        for(auto it {f.begin()}; it not_eq end1; ++it) {
                            assert(*it == number);
                        }
                        const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                        for(auto it {end1}; it not_eq end2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {end2}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        const auto cend1 {advance(f.cbegin(), insertion_position)};
                        for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                        for(auto it {cend1}; it not_eq cend2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {cend2}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == advance(f.begin(), insertion_position));
                        assert(result == advance(f.cbegin(), insertion_position));
                        std::cout << "\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to random position/With reallocation/Insertion size less equal to tail size done." << std::endl;
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
                        forward_list<int> f(count, number);
                        const auto result {f.insert(insertion_position, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end1 {advance(f.begin(), insertion_position)};
                        for(auto it {f.begin()}; it not_eq end1; ++it) {
                            assert(*it == number);
                        }
                        const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                        for(auto it {end1}; it not_eq end2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {end2}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        const auto cend1 {advance(f.cbegin(), insertion_position)};
                        for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                        for(auto it {cend1}; it not_eq cend2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {cend2}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == advance(f.begin(), insertion_position));
                        assert(result == advance(f.cbegin(), insertion_position));
                        std::cout << "\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to random position/With reallocation/Insertion size greater than tail size done." << std::endl;
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
                        forward_list<int> f(count, number);
                        auto result {f.insert(insertion_position, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end1 {advance(f.begin(), insertion_position)};
                        for(auto it {f.begin()}; it not_eq end1; ++it) {
                            assert(*it == number);
                        }
                        const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                        for(auto it {end1}; it not_eq end2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {end2}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        const auto cend1 {advance(f.cbegin(), insertion_position)};
                        for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                        for(auto it {cend1}; it not_eq cend2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {cend2}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == advance(f.begin(), insertion_position));
                        assert(result == advance(f.cbegin(), insertion_position));
                        std::cout << "\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to random position/With reallocation/Insertion size less equal to double capacity done." << std::endl;
                    }

                    // insertion size greater than double capacity
                    {
                        auto count {this->generate_count()};
                        while(count <= 2) {
                            count = this->generate_count();
                        }
                        const auto insertion_position {this->generate_a_random_number(1, count - 2)};
                        const auto insertion_size {this->generate_a_random_number(2 * count + 1)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_forward_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        forward_list<int> f(count, number);
                        auto result {f.insert(insertion_position, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end1 {advance(f.begin(), insertion_position)};
                        for(auto it {f.begin()}; it not_eq end1; ++it) {
                            assert(*it == number);
                        }
                        const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                        for(auto it {end1}; it not_eq end2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {end2}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        const auto cend1 {advance(f.cbegin(), insertion_position)};
                        for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                        for(auto it {cend1}; it not_eq cend2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {cend2}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == advance(f.begin(), insertion_position));
                        assert(result == advance(f.cbegin(), insertion_position));
                        std::cout << "\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to random position/With reallocation/Insertion size greater than double capacity done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to random position/With reallocation finished!" << std::endl;
                }

                std::cout << "\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to random position finished!" << std::endl;
            }

            // insert to tail
            {
                std::cout << "\t\t\tStart checking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to tail!" << std::endl;

                // without reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to tail/Without reallocation!" << std::endl;

                    // insertion size is zero
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto new_size {this->generate_a_random_number(1, count - 1)};
                        const auto number {this->generate_a_random_number()};
                        forward_list<int> f(count, number);
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
                        const auto result {f.insert(new_size, int_forward_iterator {}, int_forward_iterator {})};
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
                        assert(result == f.end());
                        assert(result == f.cend());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to tail/Without reallocation/Insertion size is zero done." << std::endl;
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
                        forward_list<int> f(count + static_cast<size_t>(insertion_size) + spare, number);
                        auto erasion {&f.head};
                        for(auto i {count};; erasion = erasion->next) {
                            if(i-- == 0) {
                                auto backup {erasion->next};
                                erasion->next = nullptr;
                                f.node_size.allocator().deallocate(backup->node(), insertion_size + spare);
                                f.node_size() = count;
                                break;
                            }
                        }
                        const auto result {f.insert(count, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end {advance(f.begin(), count)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        const auto cend {advance(f.cbegin(), count)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        assert(result == advance(f.begin(), count));
                        assert(result == advance(f.cbegin(), count));
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to tail/Without reallocation/Insertion size less equal to tail size done." << std::endl;
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
                        forward_list<int> f(count + static_cast<size_t>(insertion_size) + spare, number);
                        auto erasion {&f.head};
                        for(auto i {count};; erasion = erasion->next) {
                            if(i-- == 0) {
                                auto backup {erasion->next};
                                erasion->next = nullptr;
                                f.node_size.allocator().deallocate(backup->node(), static_cast<size_t>(insertion_size) + spare);
                                f.node_size() = count;
                                break;
                            }
                        }
                        const auto result {f.insert(count, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end {advance(f.begin(), count)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        const auto cend {advance(f.cbegin(), count)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        assert(result == advance(f.begin(), count));
                        assert(result == advance(f.cbegin(), count));
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to tail/Without reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to tail/Without reallocation finished!" << std::endl;
                }

                // with reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to tail/With reallocation!" << std::endl;

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
                        forward_list<int> f(count, number);
                        const auto result {f.insert(count, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end {advance(f.begin(), count)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        const auto cend {advance(f.cbegin(), count)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        assert(result == advance(f.begin(), count));
                        assert(result == advance(f.cbegin(), count));
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to tail/With reallocation/Insertion size less equal to tail size done." << std::endl;
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
                        forward_list<int> f(count, number);
                        const auto result {f.insert(count, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end {advance(f.begin(), count)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        const auto cend {advance(f.cbegin(), count)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        assert(result == advance(f.begin(), count));
                        assert(result == advance(f.cbegin(), count));
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to tail/With reallocation/Insertion size greater than tail size done." << std::endl;
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
                        forward_list<int> f(count, number);
                        auto result {f.insert(count, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end {advance(f.begin(), count)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        const auto cend {advance(f.cbegin(), count)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        assert(result == advance(f.begin(), count));
                        assert(result == advance(f.cbegin(), count));
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to tail/With reallocation/Insertion size less equal to double capacity done." << std::endl;
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
                        forward_list<int> f(count, number);
                        auto result {f.insert(count, int_forward_iterator {l.begin()}, int_forward_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end {advance(f.begin(), count)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        const auto cend {advance(f.cbegin(), count)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        assert(result == advance(f.begin(), count));
                        assert(result == advance(f.cbegin(), count));
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to tail/With reallocation/Insertion size greater than double capacity done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to tail/With reallocation finished!" << std::endl;
                }

                std::cout << "\t\t\tChecking test_insert_3/Forward iteratorInsert to non-empty forward_list/Insert to tail finished!" << std::endl;
            }

            std::cout << "\t\tChecking test_insert_3/Forward iteratorInsert to non-empty forward_list finished!" << std::endl;
        }

        std::cout << "\tChecking test_insert3/Forward iterator for ds::forward_list finished!" << std::endl;
    }

    // bidirectional iterator
    {
        std::cout << "\tStart checking test_insert_3/Bidirectional iterator for ds::forward_list!" << std::endl;

        // insert to empty forward_list
        {
            std::cout << "\t\tStart checking test_insert_3/Bidirectional iteratorInsert to empty forward_list for ds::forward_list!" << std::endl;

            // insertion size equal to zero
            {
                forward_list<int> f {};
                const auto result {f.insert(0, int_bidirectional_iterator {}, int_bidirectional_iterator {})};
                assert(f.size() == 0);
                assert(f.empty());
                assert(f.begin() == f.end());
                assert(f.cbegin() == f.cend());
                assert(result == f.begin());
                assert(result == f.cbegin());
                std::cout << "\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to empty forward_list/Insertion size not equal to zero done." << std::endl;
            }

            // insertion size not equal to zero
            {
                forward_list<int> f {};
                auto insertion_size {this->generate_count()};
                while(insertion_size == 0) {
                    insertion_size = this->generate_count();
                }
                const auto numbers {this->generate_random_sequence(insertion_size)};
                auto l {this->to_bidirectional_iterator(numbers)};
                const auto result {f.insert(0, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                assert(f.size() == insertion_size);
                assert(not f.empty());
                assert(advance(f.begin(), insertion_size) == f.end());
                assert(advance(f.cbegin(), insertion_size) == f.cend());
                assert(f.front() == numbers.front());
                auto i {0uz};
                for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                    assert(*it == numbers[i++]);
                }
                i = 0;
                for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                    assert(*it == numbers[i++]);
                }
                assert(result == f.begin());
                assert(result == f.cbegin());
                std::cout << "\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to empty forward_list/Insertion size not equal to zero done." << std::endl;
            }

            std::cout << "\t\tChecking test_insert_3/Bidirectional iteratorInsert to empty forward_list for ds::forward_list finished!" << std::endl;
        }

        // insert to non-empty forward_list
        {
            std::cout << "\t\tStart checking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list!" << std::endl;

            // insert to head
            {
                std::cout << "\t\t\tStart checking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to head!" << std::endl;

                // without reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to head/Without reallocation!" << std::endl;

                    // insertion size is zero
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto new_size {this->generate_a_random_number(1, count - 1)};
                        const auto number {this->generate_a_random_number()};
                        forward_list<int> f(count, number);
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
                        const auto result {f.insert(0, int_bidirectional_iterator {}, int_bidirectional_iterator {})};
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
                        assert(result == f.begin());
                        assert(result == f.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to head/Without reallocation/Insertion size is zero done." << std::endl;
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
                        forward_list<int> f(count + static_cast<size_t>(insertion_size) + spare, number);
                        auto erasion {&f.head};
                        for(auto i {count};; erasion = erasion->next) {
                            if(i-- == 0) {
                                auto backup {erasion->next};
                                erasion->next = nullptr;
                                f.node_size.allocator().deallocate(backup->node(), insertion_size + spare);
                                f.node_size() = count;
                                break;
                            }
                        }
                        const auto result {f.insert(0, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == numbers.front());
                        auto number_i {0uz};
                        const auto end {advance(f.begin(), insertion_size)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        const auto cend {advance(f.cbegin(), insertion_size)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == f.begin());
                        assert(result == f.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to head/Without reallocation/Insertion size less equal to tail size done." << std::endl;
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
                        forward_list<int> f(count + static_cast<size_t>(insertion_size) + spare, number);
                        auto erasion {&f.head};
                        for(auto i {count};; erasion = erasion->next) {
                            if(i-- == 0) {
                                auto backup {erasion->next};
                                erasion->next = nullptr;
                                f.node_size.allocator().deallocate(backup->node(), static_cast<size_t>(insertion_size) + spare);
                                f.node_size() = count;
                                break;
                            }
                        }
                        const auto result {f.insert(0, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == numbers.front());
                        auto number_i {0uz};
                        const auto end {advance(f.begin(), insertion_size)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        const auto cend {advance(f.cbegin(), insertion_size)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == f.begin());
                        assert(result == f.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to head/Without reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to head/Without reallocation finished!" << std::endl;
                }

                // with reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to head/With reallocation!" << std::endl;

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
                        forward_list<int> f(count, number);
                        const auto result {f.insert(0, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == numbers.front());
                        auto number_i {0uz};
                        const auto end {advance(f.begin(), insertion_size)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        const auto cend {advance(f.cbegin(), insertion_size)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == f.begin());
                        assert(result == f.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to head/With reallocation/Insertion size less equal to tail size done." << std::endl;
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
                        forward_list<int> f(count, number);
                        const auto result {f.insert(0, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == numbers.front());
                        auto number_i {0uz};
                        const auto end {advance(f.begin(), insertion_size)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        const auto cend {advance(f.cbegin(), insertion_size)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == f.begin());
                        assert(result == f.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to head/With reallocation/Insertion size greater than tail size done." << std::endl;
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
                        forward_list<int> f(count, number);
                        auto result {f.insert(0, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == numbers.front());
                        auto number_i {0uz};
                        const auto end {advance(f.begin(), insertion_size)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        const auto cend {advance(f.cbegin(), insertion_size)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == f.begin());
                        assert(result == f.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to head/With reallocation/Insertion size less equal to double capacity done." << std::endl;
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
                        forward_list<int> f(count, number);
                        auto result {f.insert(0, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == numbers.front());
                        auto number_i {0uz};
                        const auto end {advance(f.begin(), insertion_size)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        const auto cend {advance(f.cbegin(), insertion_size)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == f.begin());
                        assert(result == f.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to head/With reallocation/Insertion size greater than double capacity done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to head/With reallocation finished!" << std::endl;
                }

                std::cout << "\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to head finished!" << std::endl;
            }

            // insert to random position
            {
                std::cout << "\t\t\tStart checking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to random position!" << std::endl;

                // without reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to random position/Without reallocation!" << std::endl;

                    // insertion size is zero
                    {
                        auto count {this->generate_count()};
                        while(count <= 2) {
                            count = this->generate_count();
                        }
                        const auto new_size {this->generate_a_random_number(2, count - 1)};
                        const auto number {this->generate_a_random_number()};
                        const auto insertion_position {this->generate_a_random_number(1, new_size - 1)};
                        forward_list<int> f(count, number);
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
                        const auto result {f.insert(insertion_position, int_bidirectional_iterator {}, int_bidirectional_iterator {})};
                        assert(f.size() == new_size);
                        assert(not f.empty());
                        assert(advance(f.begin(), new_size) == f.end());
                        assert(advance(f.cbegin(), new_size) == f.cend());
                        assert(f.front() == number);
                        for(auto it {advance(f.begin(), 1)}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {advance(f.cbegin(), 1)}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == advance(f.begin(), insertion_position));
                        assert(result == advance(f.cbegin(), insertion_position));
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to random position/Without reallocation/Insertion size is zero done." << std::endl;
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
                        forward_list<int> f(count + static_cast<size_t>(insertion_size) + spare, number);
                        auto erasion {&f.head};
                        for(auto i {count};; erasion = erasion->next) {
                            if(i-- == 0) {
                                auto backup {erasion->next};
                                erasion->next = nullptr;
                                f.node_size.allocator().deallocate(backup->node(), insertion_size + spare);
                                f.node_size() = count;
                                break;
                            }
                        }
                        const auto result {f.insert(insertion_position, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end1 {advance(f.begin(), insertion_position)};
                        for(auto it {f.begin()}; it not_eq end1; ++it) {
                            assert(*it == number);
                        }
                        const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                        for(auto it {end1}; it not_eq end2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {end2}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        const auto cend1 {advance(f.cbegin(), insertion_position)};
                        for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                        for(auto it {cend1}; it not_eq cend2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {cend2}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == advance(f.begin(), insertion_position));
                        assert(result == advance(f.cbegin(), insertion_position));
                        std::cout << "\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to random position/Without reallocation/Insertion size less equal to tail size done." << std::endl;
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
                        forward_list<int> f(count + static_cast<size_t>(insertion_size) + spare, number);
                        auto erasion {&f.head};
                        for(auto i {count};; erasion = erasion->next) {
                            if(i-- == 0) {
                                auto backup {erasion->next};
                                erasion->next = nullptr;
                                f.node_size.allocator().deallocate(backup->node(), static_cast<size_t>(insertion_size) + spare);
                                f.node_size() = count;
                                break;
                            }
                        }
                        const auto result {f.insert(insertion_position, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end1 {advance(f.begin(), insertion_position)};
                        for(auto it {f.begin()}; it not_eq end1; ++it) {
                            assert(*it == number);
                        }
                        const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                        for(auto it {end1}; it not_eq end2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {end2}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        const auto cend1 {advance(f.cbegin(), insertion_position)};
                        for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                        for(auto it {cend1}; it not_eq cend2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {cend2}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == advance(f.begin(), insertion_position));
                        assert(result == advance(f.cbegin(), insertion_position));
                        std::cout << "\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to random position/Without reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to random position/Without reallocation finished!" << std::endl;
                }

                // with reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to random position/With reallocation!" << std::endl;

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
                        forward_list<int> f(count, number);
                        const auto result {f.insert(insertion_position, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end1 {advance(f.begin(), insertion_position)};
                        for(auto it {f.begin()}; it not_eq end1; ++it) {
                            assert(*it == number);
                        }
                        const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                        for(auto it {end1}; it not_eq end2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {end2}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        const auto cend1 {advance(f.cbegin(), insertion_position)};
                        for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                        for(auto it {cend1}; it not_eq cend2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {cend2}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == advance(f.begin(), insertion_position));
                        assert(result == advance(f.cbegin(), insertion_position));
                        std::cout << "\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to random position/With reallocation/Insertion size less equal to tail size done." << std::endl;
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
                        forward_list<int> f(count, number);
                        const auto result {f.insert(insertion_position, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end1 {advance(f.begin(), insertion_position)};
                        for(auto it {f.begin()}; it not_eq end1; ++it) {
                            assert(*it == number);
                        }
                        const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                        for(auto it {end1}; it not_eq end2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {end2}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        const auto cend1 {advance(f.cbegin(), insertion_position)};
                        for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                        for(auto it {cend1}; it not_eq cend2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {cend2}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == advance(f.begin(), insertion_position));
                        assert(result == advance(f.cbegin(), insertion_position));
                        std::cout << "\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to random position/With reallocation/Insertion size greater than tail size done." << std::endl;
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
                        forward_list<int> f(count, number);
                        auto result {f.insert(insertion_position, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end1 {advance(f.begin(), insertion_position)};
                        for(auto it {f.begin()}; it not_eq end1; ++it) {
                            assert(*it == number);
                        }
                        const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                        for(auto it {end1}; it not_eq end2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {end2}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        const auto cend1 {advance(f.cbegin(), insertion_position)};
                        for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                        for(auto it {cend1}; it not_eq cend2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {cend2}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == advance(f.begin(), insertion_position));
                        assert(result == advance(f.cbegin(), insertion_position));
                        std::cout << "\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to random position/With reallocation/Insertion size less equal to double capacity done." << std::endl;
                    }

                    // insertion size greater than double capacity
                    {
                        auto count {this->generate_count()};
                        while(count <= 2) {
                            count = this->generate_count();
                        }
                        const auto insertion_position {this->generate_a_random_number(1, count - 2)};
                        const auto insertion_size {this->generate_a_random_number(2 * count + 1)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto l {this->to_bidirectional_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        forward_list<int> f(count, number);
                        auto result {f.insert(insertion_position, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end1 {advance(f.begin(), insertion_position)};
                        for(auto it {f.begin()}; it not_eq end1; ++it) {
                            assert(*it == number);
                        }
                        const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                        for(auto it {end1}; it not_eq end2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {end2}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        const auto cend1 {advance(f.cbegin(), insertion_position)};
                        for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                        for(auto it {cend1}; it not_eq cend2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {cend2}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == advance(f.begin(), insertion_position));
                        assert(result == advance(f.cbegin(), insertion_position));
                        std::cout << "\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to random position/With reallocation/Insertion size greater than double capacity done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to random position/With reallocation finished!" << std::endl;
                }

                std::cout << "\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to random position finished!" << std::endl;
            }

            // insert to tail
            {
                std::cout << "\t\t\tStart checking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to tail!" << std::endl;

                // without reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to tail/Without reallocation!" << std::endl;

                    // insertion size is zero
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto new_size {this->generate_a_random_number(1, count - 1)};
                        const auto number {this->generate_a_random_number()};
                        forward_list<int> f(count, number);
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
                        const auto result {f.insert(new_size, int_bidirectional_iterator {}, int_bidirectional_iterator {})};
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
                        assert(result == f.end());
                        assert(result == f.cend());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to tail/Without reallocation/Insertion size is zero done." << std::endl;
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
                        forward_list<int> f(count + static_cast<size_t>(insertion_size) + spare, number);
                        auto erasion {&f.head};
                        for(auto i {count};; erasion = erasion->next) {
                            if(i-- == 0) {
                                auto backup {erasion->next};
                                erasion->next = nullptr;
                                f.node_size.allocator().deallocate(backup->node(), insertion_size + spare);
                                f.node_size() = count;
                                break;
                            }
                        }
                        const auto result {f.insert(count, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end {advance(f.begin(), count)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        const auto cend {advance(f.cbegin(), count)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        assert(result == advance(f.begin(), count));
                        assert(result == advance(f.cbegin(), count));
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to tail/Without reallocation/Insertion size less equal to tail size done." << std::endl;
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
                        forward_list<int> f(count + static_cast<size_t>(insertion_size) + spare, number);
                        auto erasion {&f.head};
                        for(auto i {count};; erasion = erasion->next) {
                            if(i-- == 0) {
                                auto backup {erasion->next};
                                erasion->next = nullptr;
                                f.node_size.allocator().deallocate(backup->node(), static_cast<size_t>(insertion_size) + spare);
                                f.node_size() = count;
                                break;
                            }
                        }
                        const auto result {f.insert(count, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end {advance(f.begin(), count)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        const auto cend {advance(f.cbegin(), count)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        assert(result == advance(f.begin(), count));
                        assert(result == advance(f.cbegin(), count));
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to tail/Without reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to tail/Without reallocation finished!" << std::endl;
                }

                // with reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to tail/With reallocation!" << std::endl;

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
                        forward_list<int> f(count, number);
                        const auto result {f.insert(count, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end {advance(f.begin(), count)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        const auto cend {advance(f.cbegin(), count)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        assert(result == advance(f.begin(), count));
                        assert(result == advance(f.cbegin(), count));
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to tail/With reallocation/Insertion size less equal to tail size done." << std::endl;
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
                        forward_list<int> f(count, number);
                        const auto result {f.insert(count, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end {advance(f.begin(), count)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        const auto cend {advance(f.cbegin(), count)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        assert(result == advance(f.begin(), count));
                        assert(result == advance(f.cbegin(), count));
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to tail/With reallocation/Insertion size greater than tail size done." << std::endl;
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
                        forward_list<int> f(count, number);
                        auto result {f.insert(count, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end {advance(f.begin(), count)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        const auto cend {advance(f.cbegin(), count)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        assert(result == advance(f.begin(), count));
                        assert(result == advance(f.cbegin(), count));
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to tail/With reallocation/Insertion size less equal to double capacity done." << std::endl;
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
                        forward_list<int> f(count, number);
                        auto result {f.insert(count, int_bidirectional_iterator {l.begin()}, int_bidirectional_iterator {l.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end {advance(f.begin(), count)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        const auto cend {advance(f.cbegin(), count)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        assert(result == advance(f.begin(), count));
                        assert(result == advance(f.cbegin(), count));
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to tail/With reallocation/Insertion size greater than double capacity done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to tail/With reallocation finished!" << std::endl;
                }

                std::cout << "\t\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list/Insert to tail finished!" << std::endl;
            }

            std::cout << "\t\tChecking test_insert_3/Bidirectional iteratorInsert to non-empty forward_list finished!" << std::endl;
        }

        std::cout << "\tChecking test_insert3/Bidirectional iterator for ds::forward_list finished!" << std::endl;
    }

    // random access iterator
    {
        std::cout << "\tStart checking test_insert_3/Random access iterator for ds::forward_list!" << std::endl;

        // insert to empty forward_list
        {
            std::cout << "\t\tStart checking test_insert_3/Random access iteratorInsert to empty forward_list for ds::forward_list!" << std::endl;

            // insertion size equal to zero
            {
                forward_list<int> f {};
                const auto result {f.insert(0, int_random_access_iterator {}, int_random_access_iterator {})};
                assert(f.size() == 0);
                assert(f.empty());
                assert(f.begin() == f.end());
                assert(f.cbegin() == f.cend());
                assert(result == f.begin());
                assert(result == f.cbegin());
                std::cout << "\t\t\tChecking test_insert_3/Random access iteratorInsert to empty forward_list/Insertion size not equal to zero done." << std::endl;
            }

            // insertion size not equal to zero
            {
                forward_list<int> f {};
                auto insertion_size {this->generate_count()};
                while(insertion_size == 0) {
                    insertion_size = this->generate_count();
                }
                const auto numbers {this->generate_random_sequence(insertion_size)};
                auto d {this->to_random_access_iterator(numbers)};
                const auto result {f.insert(0, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                assert(f.size() == insertion_size);
                assert(not f.empty());
                assert(advance(f.begin(), insertion_size) == f.end());
                assert(advance(f.cbegin(), insertion_size) == f.cend());
                assert(f.front() == numbers.front());
                auto i {0uz};
                for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                    assert(*it == numbers[i++]);
                }
                i = 0;
                for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                    assert(*it == numbers[i++]);
                }
                assert(result == f.begin());
                assert(result == f.cbegin());
                std::cout << "\t\t\tChecking test_insert_3/Random access iteratorInsert to empty forward_list/Insertion size not equal to zero done." << std::endl;
            }

            std::cout << "\t\tChecking test_insert_3/Random access iteratorInsert to empty forward_list for ds::forward_list finished!" << std::endl;
        }

        // insert to non-empty forward_list
        {
            std::cout << "\t\tStart checking test_insert_3/Random access iteratorInsert to non-empty forward_list!" << std::endl;

            // insert to head
            {
                std::cout << "\t\t\tStart checking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to head!" << std::endl;

                // without reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to head/Without reallocation!" << std::endl;

                    // insertion size is zero
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto new_size {this->generate_a_random_number(1, count - 1)};
                        const auto number {this->generate_a_random_number()};
                        forward_list<int> f(count, number);
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
                        const auto result {f.insert(0, int_random_access_iterator {}, int_random_access_iterator {})};
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
                        assert(result == f.begin());
                        assert(result == f.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to head/Without reallocation/Insertion size is zero done." << std::endl;
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
                        forward_list<int> f(count + static_cast<size_t>(insertion_size) + spare, number);
                        auto erasion {&f.head};
                        for(auto i {count};; erasion = erasion->next) {
                            if(i-- == 0) {
                                auto backup {erasion->next};
                                erasion->next = nullptr;
                                f.node_size.allocator().deallocate(backup->node(), insertion_size + spare);
                                f.node_size() = count;
                                break;
                            }
                        }
                        const auto result {f.insert(0, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == numbers.front());
                        auto number_i {0uz};
                        const auto end {advance(f.begin(), insertion_size)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        const auto cend {advance(f.cbegin(), insertion_size)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == f.begin());
                        assert(result == f.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to head/Without reallocation/Insertion size less equal to tail size done." << std::endl;
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
                        forward_list<int> f(count + static_cast<size_t>(insertion_size) + spare, number);
                        auto erasion {&f.head};
                        for(auto i {count};; erasion = erasion->next) {
                            if(i-- == 0) {
                                auto backup {erasion->next};
                                erasion->next = nullptr;
                                f.node_size.allocator().deallocate(backup->node(), static_cast<size_t>(insertion_size) + spare);
                                f.node_size() = count;
                                break;
                            }
                        }
                        const auto result {f.insert(0, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == numbers.front());
                        auto number_i {0uz};
                        const auto end {advance(f.begin(), insertion_size)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        const auto cend {advance(f.cbegin(), insertion_size)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == f.begin());
                        assert(result == f.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to head/Without reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to head/Without reallocation finished!" << std::endl;
                }

                // with reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to head/With reallocation!" << std::endl;

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
                        forward_list<int> f(count, number);
                        const auto result {f.insert(0, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == numbers.front());
                        auto number_i {0uz};
                        const auto end {advance(f.begin(), insertion_size)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        const auto cend {advance(f.cbegin(), insertion_size)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == f.begin());
                        assert(result == f.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to head/With reallocation/Insertion size less equal to tail size done." << std::endl;
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
                        forward_list<int> f(count, number);
                        const auto result {f.insert(0, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == numbers.front());
                        auto number_i {0uz};
                        const auto end {advance(f.begin(), insertion_size)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        const auto cend {advance(f.cbegin(), insertion_size)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == f.begin());
                        assert(result == f.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to head/With reallocation/Insertion size greater than tail size done." << std::endl;
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
                        forward_list<int> f(count, number);
                        auto result {f.insert(0, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == numbers.front());
                        auto number_i {0uz};
                        const auto end {advance(f.begin(), insertion_size)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        const auto cend {advance(f.cbegin(), insertion_size)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == f.begin());
                        assert(result == f.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to head/With reallocation/Insertion size less equal to double capacity done." << std::endl;
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
                        forward_list<int> f(count, number);
                        auto result {f.insert(0, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == numbers.front());
                        auto number_i {0uz};
                        const auto end {advance(f.begin(), insertion_size)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        number_i = 0;
                        const auto cend {advance(f.cbegin(), insertion_size)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == numbers[number_i++]);
                        }
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == f.begin());
                        assert(result == f.cbegin());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to head/With reallocation/Insertion size greater than double capacity done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to head/With reallocation finished!" << std::endl;
                }

                std::cout << "\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to head finished!" << std::endl;
            }

            // insert to random position
            {
                std::cout << "\t\t\tStart checking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to random position!" << std::endl;

                // without reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to random position/Without reallocation!" << std::endl;

                    // insertion size is zero
                    {
                        auto count {this->generate_count()};
                        while(count <= 2) {
                            count = this->generate_count();
                        }
                        const auto new_size {this->generate_a_random_number(2, count - 1)};
                        const auto number {this->generate_a_random_number()};
                        const auto insertion_position {this->generate_a_random_number(1, new_size - 1)};
                        forward_list<int> f(count, number);
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
                        const auto result {f.insert(insertion_position, int_random_access_iterator {}, int_random_access_iterator {})};
                        assert(f.size() == new_size);
                        assert(not f.empty());
                        assert(advance(f.begin(), new_size) == f.end());
                        assert(advance(f.cbegin(), new_size) == f.cend());
                        assert(f.front() == number);
                        for(auto it {advance(f.begin(), 1)}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        for(auto it {advance(f.cbegin(), 1)}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == advance(f.begin(), insertion_position));
                        assert(result == advance(f.cbegin(), insertion_position));
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to random position/Without reallocation/Insertion size is zero done." << std::endl;
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
                        forward_list<int> f(count + static_cast<size_t>(insertion_size) + spare, number);
                        auto erasion {&f.head};
                        for(auto i {count};; erasion = erasion->next) {
                            if(i-- == 0) {
                                auto backup {erasion->next};
                                erasion->next = nullptr;
                                f.node_size.allocator().deallocate(backup->node(), insertion_size + spare);
                                f.node_size() = count;
                                break;
                            }
                        }
                        const auto result {f.insert(insertion_position, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end1 {advance(f.begin(), insertion_position)};
                        for(auto it {f.begin()}; it not_eq end1; ++it) {
                            assert(*it == number);
                        }
                        const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                        for(auto it {end1}; it not_eq end2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {end2}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        const auto cend1 {advance(f.cbegin(), insertion_position)};
                        for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                        for(auto it {cend1}; it not_eq cend2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {cend2}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == advance(f.begin(), insertion_position));
                        assert(result == advance(f.cbegin(), insertion_position));
                        std::cout << "\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to random position/Without reallocation/Insertion size less equal to tail size done." << std::endl;
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
                        forward_list<int> f(count + static_cast<size_t>(insertion_size) + spare, number);
                        auto erasion {&f.head};
                        for(auto i {count};; erasion = erasion->next) {
                            if(i-- == 0) {
                                auto backup {erasion->next};
                                erasion->next = nullptr;
                                f.node_size.allocator().deallocate(backup->node(), static_cast<size_t>(insertion_size) + spare);
                                f.node_size() = count;
                                break;
                            }
                        }
                        const auto result {f.insert(insertion_position, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end1 {advance(f.begin(), insertion_position)};
                        for(auto it {f.begin()}; it not_eq end1; ++it) {
                            assert(*it == number);
                        }
                        const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                        for(auto it {end1}; it not_eq end2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {end2}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        const auto cend1 {advance(f.cbegin(), insertion_position)};
                        for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                        for(auto it {cend1}; it not_eq cend2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {cend2}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == advance(f.begin(), insertion_position));
                        assert(result == advance(f.cbegin(), insertion_position));
                        std::cout << "\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to random position/Without reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to random position/Without reallocation finished!" << std::endl;
                }

                // with reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to random position/With reallocation!" << std::endl;

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
                        forward_list<int> f(count, number);
                        const auto result {f.insert(insertion_position, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end1 {advance(f.begin(), insertion_position)};
                        for(auto it {f.begin()}; it not_eq end1; ++it) {
                            assert(*it == number);
                        }
                        const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                        for(auto it {end1}; it not_eq end2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {end2}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        const auto cend1 {advance(f.cbegin(), insertion_position)};
                        for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                        for(auto it {cend1}; it not_eq cend2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {cend2}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == advance(f.begin(), insertion_position));
                        assert(result == advance(f.cbegin(), insertion_position));
                        std::cout << "\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to random position/With reallocation/Insertion size less equal to tail size done." << std::endl;
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
                        forward_list<int> f(count, number);
                        const auto result {f.insert(insertion_position, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end1 {advance(f.begin(), insertion_position)};
                        for(auto it {f.begin()}; it not_eq end1; ++it) {
                            assert(*it == number);
                        }
                        const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                        for(auto it {end1}; it not_eq end2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {end2}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        const auto cend1 {advance(f.cbegin(), insertion_position)};
                        for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                        for(auto it {cend1}; it not_eq cend2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {cend2}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == advance(f.begin(), insertion_position));
                        assert(result == advance(f.cbegin(), insertion_position));
                        std::cout << "\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to random position/With reallocation/Insertion size greater than tail size done." << std::endl;
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
                        forward_list<int> f(count, number);
                        auto result {f.insert(insertion_position, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end1 {advance(f.begin(), insertion_position)};
                        for(auto it {f.begin()}; it not_eq end1; ++it) {
                            assert(*it == number);
                        }
                        const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                        for(auto it {end1}; it not_eq end2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {end2}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        const auto cend1 {advance(f.cbegin(), insertion_position)};
                        for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                        for(auto it {cend1}; it not_eq cend2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {cend2}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == advance(f.begin(), insertion_position));
                        assert(result == advance(f.cbegin(), insertion_position));
                        std::cout << "\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to random position/With reallocation/Insertion size less equal to double capacity done." << std::endl;
                    }

                    // insertion size greater than double capacity
                    {
                        auto count {this->generate_count()};
                        while(count <= 2) {
                            count = this->generate_count();
                        }
                        const auto insertion_position {this->generate_a_random_number(1, count - 2)};
                        const auto insertion_size {this->generate_a_random_number(2 * count + 1)};
                        const auto numbers {this->generate_random_sequence(insertion_size)};
                        auto d {this->to_random_access_iterator(numbers)};
                        const auto number {this->generate_a_random_number()};
                        forward_list<int> f(count, number);
                        auto result {f.insert(insertion_position, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end1 {advance(f.begin(), insertion_position)};
                        for(auto it {f.begin()}; it not_eq end1; ++it) {
                            assert(*it == number);
                        }
                        const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                        for(auto it {end1}; it not_eq end2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {end2}; it not_eq f.end(); ++it) {
                            assert(*it == number);
                        }
                        const auto cend1 {advance(f.cbegin(), insertion_position)};
                        for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                        for(auto it {cend1}; it not_eq cend2; ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        for(auto it {cend2}; it not_eq f.cend(); ++it) {
                            assert(*it == number);
                        }
                        assert(result == advance(f.begin(), insertion_position));
                        assert(result == advance(f.cbegin(), insertion_position));
                        std::cout << "\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to random position/With reallocation/Insertion size greater than double capacity done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to random position/With reallocation finished!" << std::endl;
                }

                std::cout << "\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to random position finished!" << std::endl;
            }

            // insert to tail
            {
                std::cout << "\t\t\tStart checking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to tail!" << std::endl;

                // without reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to tail/Without reallocation!" << std::endl;

                    // insertion size is zero
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto new_size {this->generate_a_random_number(1, count - 1)};
                        const auto number {this->generate_a_random_number()};
                        forward_list<int> f(count, number);
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
                        const auto result {f.insert(new_size, int_random_access_iterator {}, int_random_access_iterator {})};
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
                        assert(result == f.end());
                        assert(result == f.cend());
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to tail/Without reallocation/Insertion size is zero done." << std::endl;
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
                        forward_list<int> f(count + static_cast<size_t>(insertion_size) + spare, number);
                        auto erasion {&f.head};
                        for(auto i {count};; erasion = erasion->next) {
                            if(i-- == 0) {
                                auto backup {erasion->next};
                                erasion->next = nullptr;
                                f.node_size.allocator().deallocate(backup->node(), insertion_size + spare);
                                f.node_size() = count;
                                break;
                            }
                        }
                        const auto result {f.insert(count, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end {advance(f.begin(), count)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        const auto cend {advance(f.cbegin(), count)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        assert(result == advance(f.begin(), count));
                        assert(result == advance(f.cbegin(), count));
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to tail/Without reallocation/Insertion size less equal to tail size done." << std::endl;
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
                        forward_list<int> f(count + static_cast<size_t>(insertion_size) + spare, number);
                        auto erasion {&f.head};
                        for(auto i {count};; erasion = erasion->next) {
                            if(i-- == 0) {
                                auto backup {erasion->next};
                                erasion->next = nullptr;
                                f.node_size.allocator().deallocate(backup->node(), static_cast<size_t>(insertion_size) + spare);
                                f.node_size() = count;
                                break;
                            }
                        }
                        const auto result {f.insert(count, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end {advance(f.begin(), count)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        const auto cend {advance(f.cbegin(), count)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        assert(result == advance(f.begin(), count));
                        assert(result == advance(f.cbegin(), count));
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to tail/Without reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to tail/Without reallocation finished!" << std::endl;
                }

                // with reallocation
                {
                    std::cout << "\t\t\t\tStart checking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to tail/With reallocation!" << std::endl;

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
                        forward_list<int> f(count, number);
                        const auto result {f.insert(count, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end {advance(f.begin(), count)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        const auto cend {advance(f.cbegin(), count)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        assert(result == advance(f.begin(), count));
                        assert(result == advance(f.cbegin(), count));
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to tail/With reallocation/Insertion size less equal to tail size done." << std::endl;
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
                        forward_list<int> f(count, number);
                        const auto result {f.insert(count, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end {advance(f.begin(), count)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        const auto cend {advance(f.cbegin(), count)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        assert(result == advance(f.begin(), count));
                        assert(result == advance(f.cbegin(), count));
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to tail/With reallocation/Insertion size greater than tail size done." << std::endl;
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
                        forward_list<int> f(count, number);
                        auto result {f.insert(count, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end {advance(f.begin(), count)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        const auto cend {advance(f.cbegin(), count)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        assert(result == advance(f.begin(), count));
                        assert(result == advance(f.cbegin(), count));
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to tail/With reallocation/Insertion size less equal to double capacity done." << std::endl;
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
                        forward_list<int> f(count, number);
                        auto result {f.insert(count, int_random_access_iterator {d.begin()}, int_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == number);
                        auto numbers_i {0uz};
                        const auto end {advance(f.begin(), count)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == number);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        const auto cend {advance(f.cbegin(), count)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == number);
                        }
                        numbers_i = 0;
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == numbers[numbers_i++]);
                        }
                        assert(result == advance(f.begin(), count));
                        assert(result == advance(f.cbegin(), count));
                        std::cout << "\t\t\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to tail/With reallocation/Insertion size greater than double capacity done." << std::endl;
                    }

                    std::cout << "\t\t\t\tStart checking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to tail/With reallocation finished!" << std::endl;
                }

                std::cout << "\t\t\tChecking test_insert_3/Random access iteratorInsert to non-empty forward_list/Insert to tail finished!" << std::endl;
            }

            std::cout << "\t\tChecking test_insert_3/Random access iteratorInsert to non-empty forward_list finished!" << std::endl;
        }

        std::cout << "\tChecking test_insert3/Random access iterator for ds::forward_list finished!" << std::endl;
    }

    // Todo : contiguous iterator (pointer)

    std::cout << "Checking iterator insert(size_type, ForwardIterator, ForwardIterator) for ds::forward_list finished!" << std::endl;
}
void forward_list_correctness::test_erase() {
    std::cout << "Start checking iterator erase(size_type, size_type) for ds::forward_list!" << std::endl;

    // erase from head
    {
        std::cout << "\tStart checking test_erase/Erase from head for ds::forward_list!" << std::endl;

        // erasion size is zero
        {
            std::cout << "\t\tStart checking test_erase/Erase from head/Erasion size is zero for ds::forward_list!" << std::endl;

            // empty
            {
                forward_list<int> f {};
                auto result {f.erase(0, 0)};
                assert(f.size() == 0);
                assert(f.empty());
                assert(f.begin() == f.end());
                assert(f.cbegin() == f.cend());
                assert(result == f.begin());
                assert(result == f.cbegin());
                assert(result == f.end());
                assert(result == f.cend());
                std::cout << "\t\t\tChecking test_erase/Erase from head/Erasion size is zero/Empty done." << std::endl;
            }

            // non-empty
            {
                auto count {this->generate_count()};
                while(count <= 1) {
                    count = this->generate_count();
                }
                const auto number {this->generate_a_random_number()};
                forward_list<int> f(count, number);
                auto result {f.erase(0, 0)};
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
                assert(result == f.begin());
                assert(result == f.cbegin());
                std::cout << "\t\t\tChecking test_erase/Erase from head/Erasion size is zero/Non-empty done." << std::endl;
            }

            std::cout << "\t\tChecking test_erase/Erase from head/Erasion size is zero for ds::forward_list finished!" << std::endl;
        }

        // erasion size is random
        {
            auto count {this->generate_count()};
            while(count <= 1) {
                count = this->generate_count();
            }
            const auto number {this->generate_a_random_number()};
            forward_list<int> f(count, number);
            const auto erasion_size {this->generate_a_random_number(1, count - 1)};
            auto result {f.erase(0, erasion_size)};
            assert(f.size() == count - erasion_size);
            assert(not f.empty());
            assert(advance(f.begin(), count - erasion_size) == f.end());
            assert(advance(f.cbegin(), count - erasion_size) == f.cend());
            assert(f.front() == number);
            for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                assert(*it == number);
            }
            for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                assert(*it == number);
            }
            assert(result == f.begin());
            assert(result == f.cbegin());
            std::cout << "\t\tChecking test_erase/Erase from head/Erasion size is random done." << std::endl;
        }

        // erase all
        {
            auto count {this->generate_count()};
            while(count <= 1) {
                count = this->generate_count();
            }
            const auto number {this->generate_a_random_number()};
            forward_list<int> f(count, number);
            auto result {f.erase(0, count)};
            assert(f.size() == 0);
            assert(f.empty());
            assert(f.begin() == f.end());
            assert(f.cbegin() == f.cend());
            assert(result == f.begin());
            assert(result == f.cbegin());
            assert(result == f.end());
            assert(result == f.cend());
            std::cout << "\t\tChecking test_erase/Erase from head/Erasion all done." << std::endl;
        }

        std::cout << "\tChecking test_erase/Erase from head for ds::forward_list finished!" << std::endl;
    }

    // erase from any position
    {
        std::cout << "\tStart checking test_erase/Erase from any position for ds::forward_list!" << std::endl;

        // erasion size is zero
        {
            auto count {this->generate_count()};
            while(count <= 1) {
                count = this->generate_count();
            }
            const auto number {this->generate_a_random_number()};
            forward_list<int> f(count, number);
            const auto erasion_position {this->generate_a_random_number(1, count - 1)};
            auto result {f.erase(erasion_position, 0)};
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
            assert(result == advance(f.begin(), erasion_position));
            assert(result == advance(f.cbegin(), erasion_position));
            std::cout << "\t\t\tChecking test_erase/Erase from head/Erase from any position/Erasion size is zero done." << std::endl;
        }

        // erasion size is not zero
        {
            auto count {this->generate_count()};
            while(count <= 1) {
                count = this->generate_count();
            }
            const auto number {this->generate_a_random_number()};
            forward_list<int> f(count, number);
            const auto erasion_position {this->generate_a_random_number(1, count - 1)};
            const auto erasion_size {this->generate_a_random_number(1, count - erasion_position)};
            auto result {f.erase(erasion_position, erasion_size)};
            assert(f.size() == count - erasion_size);
            assert(not f.empty());
            assert(advance(f.begin(), count - erasion_size) == f.end());
            assert(advance(f.cbegin(), count - erasion_size) == f.cend());
            assert(f.front() == number);
            for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                assert(*it == number);
            }
            for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                assert(*it == number);
            }
            assert(result == advance(f.begin(), erasion_position));
            assert(result == advance(f.cbegin(), erasion_position));
            std::cout << "\t\t\tChecking test_erase/Erase from head/Erase from any position/Erasion size is not zero done." << std::endl;
        }

        // erase to tail
        {
            auto count {this->generate_count()};
            while(count <= 1) {
                count = this->generate_count();
            }
            const auto number {this->generate_a_random_number()};
            forward_list<int> f(count, number);
            const auto erasion_position {this->generate_a_random_number(1, count - 1)};
            auto result {f.erase(erasion_position, count - erasion_position)};
            assert(f.size() == erasion_position);
            assert(not f.empty());
            assert(advance(f.begin(), erasion_position) == f.end());
            assert(advance(f.cbegin(), erasion_position) == f.cend());
            assert(f.front() == number);
            for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                assert(*it == number);
            }
            for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                assert(*it == number);
            }
            assert(result == advance(f.begin(), erasion_position));
            assert(result == advance(f.cbegin(), erasion_position));
            std::cout << "\t\t\tChecking test_erase/Erase from head/Erase from any position/Erase to tail done." << std::endl;
        }

        std::cout << "\tChecking test_erase/Erase from any position for ds::forward_list finished!" << std::endl;
    }

    std::cout << "Checking iterator erase(size_type, size_type) for ds::forward_list finished!" << std::endl;
}
void forward_list_correctness::test_allocator() {
    std::cout << "Start checking allocator for ds::forward_list!" << std::endl;

    forward_list<int> f {1, 2, 3};
    auto allocator {f.allocator()};
    static_assert(allocator == typename forward_list<int>::allocator_type {});
    static_assert(allocator == typename forward_list<char>::allocator_type {});

    std::cout << "Checking allocator for ds::forward_list finished!" << std::endl;
}
void forward_list_correctness::test_non_trivial() {
    std::cout << "Start checking non-trivial type for ds::forward_list!" << std::endl;

    // default constructor
    {
        forward_list<std::string> f {};
        assert(f.size() == 0);
        assert(f.empty());
        assert(f.begin() == f.end());
        assert(f.cbegin() == f.cend());
        std::cout << "\tChecking test_non_trivial/Default constructor done." << std::endl;
    }

    // forward_list(size_type)
    {
        std::cout << "\tStart checking test_non_trivial/forward_list(size_type)!" << std::endl;

        // empty
        {
            forward_list<std::string> f {};
            assert(f.size() == 0);
            assert(f.empty());
            assert(f.begin() == f.end());
            assert(f.cbegin() == f.cend());
            std::cout << "\t\tChecking test_non_trivial/forward_list(size_type)/Empty done." << std::endl;
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
            forward_list<std::string> f(count, s);
            assert(f.size() == count);
            assert(not f.empty());
            assert(advance(f.begin(), count) == f.end());
            assert(advance(f.cbegin(), count) == f.cend());
            assert(f.front() == s);
            for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                assert(*it == s);
            }
            for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                assert(*it == s);
            }
            std::cout << "\t\tChecking test_non_trivial/forward_list(size_type)/Not empty done." << std::endl;
        }

        std::cout << "\tChecking test_non_trivial/forward_list(size_type) finished!" << std::endl;
    }

    // forward_list(size_type, const_reference)
    {
        std::cout << "\tStart checking test_non_trivial/forward_list(size_type, const_reference)!" << std::endl;

        // empty
        {
            forward_list<std::string> f {};
            assert(f.size() == 0);
            assert(f.empty());
            assert(f.begin() == f.end());
            assert(f.cbegin() == f.cend());
            std::cout << "\t\tChecking test_non_trivial/forward_list(size_type, const_reference)/Empty done." << std::endl;
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
            forward_list<std::string> f(count, s);
            assert(f.size() == count);
            assert(not f.empty());
            assert(advance(f.begin(), count) == f.end());
            assert(advance(f.cbegin(), count) == f.cend());
            assert(f.front() == s);
            for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                assert(*it == s);
            }
            for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                assert(*it == s);
            }
            std::cout << "\t\tChecking test_non_trivial/forward_list(size_type, const_reference)/Empty done." << std::endl;
        }

        std::cout << "\tChecking test_non_trivial/forward_list(size_type, const_reference) finished!" << std::endl;
    }

    // forward_list(InputIterator, InputIterator)
    {
        std::cout << "\tStart checking test_non_trivial/forward_list(InputIterator, InputIterator)!" << std::endl;

        // empty
        {
            forward_list<std::string> f(std_string_input_iterator {}, std_string_input_iterator {});
            assert(f.size() == 0);
            assert(f.empty());
            assert(f.begin() == f.end());
            assert(f.cbegin() == f.cend());
            std::cout << "\t\tChecking test_non_trivial/forward_list(InputIterator, InputIterator)/Empty done." << std::endl;
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
            forward_list<std::string> f(std_string_input_iterator {stream}, {});
            assert(f.size() == count);
            assert(not f.empty());
            assert(advance(f.begin(), count) == f.end());
            assert(advance(f.cbegin(), count) == f.cend());
            assert(f.front() == s);
            for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                assert(*it == s);
            }
            for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                assert(*it == s);
            }
            std::cout << "\t\tChecking test_non_trivial/forward_list(InputIterator, InputIterator)/Not Empty done." << std::endl;
        }

        std::cout << "\tChecking test_non_trivial/forward_list(InputIterator, InputIterator)!" << std::endl;
    }

    // forward_list(ForwardIterator, ForwardIterator)
    {
        std::cout << "\tStart checking test_non_trivial/forward_list(ForwardIterator, ForwardIterator)!" << std::endl;

        // empty
        {
            forward_list<std::string> f(std_string_random_access_iterator {}, std_string_random_access_iterator {});
            assert(f.size() == 0);
            assert(f.empty());
            assert(f.begin() == f.end());
            assert(f.cbegin() == f.cend());
            std::cout << "\t\tChecking test_non_trivial/forward_list(ForwardIterator, ForwardIterator)/Empty done." << std::endl;
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
            forward_list<std::string> f(std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()});
            assert(f.size() == count);
            assert(not f.empty());
            assert(advance(f.begin(), count) == f.end());
            assert(advance(f.cbegin(), count) == f.cend());
            assert(f.front() == s);
            for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                assert(*it == s);
            }
            for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                assert(*it == s);
            }
            std::cout << "\t\tChecking test_non_trivial/forward_list(ForwardIterator, ForwardIterator)/Not Empty done." << std::endl;
        }

        std::cout << "\tChecking test_non_trivial/forward_list(ForwardIterator, ForwardIterator)!" << std::endl;
    }

    // resize
    {
        std::cout << "\tStart checking void resize(size_type) for ds::forward_list!" << std::endl;

        // empty to empty
        {
            forward_list<std::string> f {};
            f.resize(0);
            assert(f.size() == 0);
            assert(f.empty());
            assert(f.begin() == f.end());
            assert(f.cbegin() == f.cend());
            std::cout << "\t\tChecking test_non_trivial/Resize/Empty to empty done." << std::endl;
        }

        // empty to non-empty
        {
            forward_list<std::string> f {};
            auto count {this->generate_count()};
            while(count == 0) {
                count = this->generate_count();
            }
            f.resize(count);
            assert(f.size() == count);
            assert(not f.empty());
            assert(advance(f.begin(), count) == f.end());
            assert(advance(f.cbegin(), count) == f.cend());
            assert(f.front() == "");
            for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                assert(*it == "");
            }
            for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                assert(*it == "");
            }
            std::cout << "\t\tChecking test_non_trivial/Resize/Empty to non-empty done." << std::endl;
        }

        // non-empty to empty
        {
            const auto count {this->generate_count()};
            forward_list<std::string> f(count, "hello");
            f.resize(0);
            assert(f.size() == 0);
            assert(f.empty());
            assert(f.begin() == f.end());
            assert(f.cbegin() == f.cend());
            std::cout << "\t\tChecking test_non_trivial/Resize/Non-empty to empty done." << std::endl;
        }

        // non-empty to non-empty
        {
            std::cout << "\t\tStart checking test_non_trivial/Resize/Non-empty to non-empty for ds::forward_list!" << std::endl;

            // less than size
            {
                auto count {this->generate_count()};
                while(count <= 1) {
                    count = this->generate_count();
                }
                const auto new_size {this->generate_a_random_number(1, count - 1)};
                const std::string s {"hello"};
                forward_list<std::string> f(count, s);
                f.resize(new_size);
                assert(f.size() == new_size);
                assert(not f.empty());
                assert(advance(f.begin(), new_size) == f.end());
                assert(advance(f.cbegin(), new_size) == f.cend());
                assert(f.front() == s);
                for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                    assert(*it == s);
                }
                for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                    assert(*it == s);
                }
                std::cout << "\t\t\tChecking test_non_trivial/Resize/Non-empty to non-empty/Less than size done." << std::endl;
            }

            // equal to size
            {
                auto count {this->generate_count()};
                while(count == 0) {
                    count = this->generate_count();
                }
                const auto number {this->generate_a_random_number()};
                const std::string s {"hello"};
                forward_list<std::string> f(count, s);
                f.resize(count);
                assert(f.size() == count);
                assert(not f.empty());
                assert(advance(f.begin(), count) == f.end());
                assert(advance(f.cbegin(), count) == f.cend());
                assert(f.front() == s);
                for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                    assert(*it == s);
                }
                for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                    assert(*it == s);
                }
                std::cout << "\t\t\tChecking test_non_trivial/Resize/Non-empty to non-empty/Equal to size done." << std::endl;
            }

            // greater than size
            {
                auto count {this->generate_count(std::numeric_limits<int>::max() - 1)};
                while(count == 0) {
                    count = this->generate_count(std::numeric_limits<int>::max() - 1);
                }
                const auto new_size {this->generate_a_random_number(count + 1)};
                const auto number {this->generate_a_random_number()};
                const std::string s {"hello"};
                forward_list<std::string> f(count, s);
                f.resize(new_size);
                assert(f.size() == new_size);
                assert(not f.empty());
                assert(advance(f.begin(), new_size) == f.end());
                assert(advance(f.cbegin(), new_size) == f.cend());
                assert(f.front() == s);
                const auto end {advance(f.begin(), count)};
                for(auto it {f.begin()}; it not_eq end; ++it) {
                    assert(*it == s);
                }
                for(auto it {end}; it not_eq f.end(); ++it) {
                    assert(*it == "");
                }
                const auto cend {advance(f.cbegin(), count)};
                for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                    assert(*it == s);
                }
                for(auto it {cend}; it not_eq f.cend(); ++it) {
                    assert(*it == "");
                }
                std::cout << "\t\t\tChecking test_non_trivial/Resize/Non-empty to non-empty/Greater than size done." << std::endl;
            }

            std::cout << "\t\tChecking test_resize_1/Non-empty to non-empty for ds::forward_list finished!" << std::endl;
        }

        std::cout << "\tChecking void resize(size_type) for ds::forward_list finished!" << std::endl;
    }

    // iterator insert(size_type, const_reference, size_type)
    {
        std::cout << "\tStart checking test_non_trivial/iterator insert(size_type, const_reference, size_type) for ds::forward_list!" << std::endl;

        {
            // insert to empty forward_list
            {
                std::cout << "\t\tStart checking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to empty forward_list for ds::forward_list!" << std::endl;

                // insertion size equal to zero
                {
                    forward_list<std::string> f {};
                    const auto result {f.insert(0, "hello", 0)};
                    assert(f.size() == 0);
                    assert(f.empty());
                    assert(f.begin() == f.end());
                    assert(f.cbegin() == f.cend());
                    assert(result == f.begin());
                    assert(result == f.cbegin());
                    std::cout << "\t\t\tChecking test_insert_1/Insert to empty forward_list/Insertion size not equal to zero done." << std::endl;
                }

                // insertion size not equal to zero
                {
                    forward_list<std::string> f {};
                    auto insertion_size {this->generate_count()};
                    while(insertion_size == 0) {
                        insertion_size = this->generate_count();
                    }
                    const std::string s {"insertion"};
                    const auto result {f.insert(0, s, insertion_size)};
                    assert(f.size() == insertion_size);
                    assert(not f.empty());
                    assert(advance(f.begin(), insertion_size) == f.end());
                    assert(advance(f.cbegin(), insertion_size) == f.cend());
                    assert(f.front() == s);
                    for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                        assert(*it == s);
                    }
                    for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                        assert(*it == s);
                    }
                    assert(result == f.begin());
                    assert(result == f.cbegin());
                    std::cout << "\t\t\tChecking test_non_trivial/test_insert_1/Insert to empty forward_list/Insertion size not equal to zero done." << std::endl;
                }

                std::cout << "\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to empty forward_list for ds::forward_list finished!" << std::endl;
            }

            // insert to non-empty forward_list
            {
                std::cout << "\t\tStart checking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list!" << std::endl;

                // insert to head
                {
                    std::cout << "\t\t\tStart checking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to head!" << std::endl;

                    // without reallocation
                    {
                        std::cout << "\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, const_reference, size_type)/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to head/Without reallocation!" << std::endl;

                        // insertion size is zero
                        {
                            auto count {this->generate_count()};
                            while(count <= 1) {
                                count = this->generate_count();
                            }
                            const auto new_size {this->generate_a_random_number(1, count - 1)};
                            const std::string s {"init"};
                            forward_list<std::string> f(count, s);
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
                            const auto result {f.insert(0, "hello", 0)};
                            assert(f.size() == new_size);
                            assert(not f.empty());
                            assert(advance(f.begin(), new_size) == f.end());
                            assert(advance(f.cbegin(), new_size) == f.cend());
                            assert(f.front() == s);
                            for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                                assert(*it == s);
                            }
                            assert(result == f.begin());
                            assert(result == f.cbegin());
                            std::cout << "\t\t\t\t\tChecking test_insert_1/Insert to non-empty forward_list/Insert to head/Without reallocation/Insertion size is zero done." << std::endl;
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
                            forward_list<std::string> f(count + static_cast<size_t>(insertion_size) + spare, s);
                            auto erasion {&f.head};
                            for(auto i {count};; erasion = erasion->next) {
                                if(i-- == 0) {
                                    auto backup {erasion->next};
                                    erasion->next = nullptr;
                                    f.node_size.allocator().deallocate(backup->node(), insertion_size + spare);
                                    f.node_size() = count;
                                    break;
                                }
                            }
                            auto s2 {"insert"};
                            const auto result {f.insert(0, s2, insertion_size)};
                            assert(f.size() == count + static_cast<size_t>(insertion_size));
                            assert(not f.empty());
                            assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                            assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                            assert(f.front() == s2);
                            const auto end {advance(f.begin(), insertion_size)};
                            for(auto it {f.begin()}; it not_eq end; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {end}; it not_eq f.end(); ++it) {
                                assert(*it == s);
                            }
                            const auto cend {advance(f.cbegin(), insertion_size)};
                            for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {cend}; it not_eq f.cend(); ++it) {
                                assert(*it == s);
                            }
                            assert(result == f.begin());
                            assert(result == f.cbegin());
                            std::cout << "\t\t\t\t\tChecking test_insert_1/Insert to non-empty forward_list/Insert to head/Without reallocation/Insertion size less equal to tail size done." << std::endl;
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
                            forward_list<std::string> f(count + static_cast<size_t>(insertion_size) + spare, s);
                            auto erasion {&f.head};
                            for(auto i {count};; erasion = erasion->next) {
                                if(i-- == 0) {
                                    auto backup {erasion->next};
                                    erasion->next = nullptr;
                                    f.node_size.allocator().deallocate(backup->node(), static_cast<size_t>(insertion_size) + spare);
                                    f.node_size() = count;
                                    break;
                                }
                            }
                            const std::string s2 {"insert"};
                            const auto result {f.insert(0, s2, insertion_size)};
                            assert(f.size() == count + static_cast<size_t>(insertion_size));
                            assert(not f.empty());
                            assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                            assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                            assert(f.front() == s2);
                            const auto end {advance(f.begin(), insertion_size)};
                            for(auto it {f.begin()}; it not_eq end; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {end}; it not_eq f.end(); ++it) {
                                assert(*it == s);
                            }
                            const auto cend {advance(f.cbegin(), insertion_size)};
                            for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {cend}; it not_eq f.cend(); ++it) {
                                assert(*it == s);
                            }
                            assert(result == f.begin());
                            assert(result == f.cbegin());
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to head/Without reallocation/Insertion size greater than tail size done." << std::endl;
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
                            forward_list<std::string> f(count + static_cast<size_t>(insertion_size), s);
                            auto erasion {&f.head};
                            for(auto i {count};; erasion = erasion->next) {
                                if(i-- == 0) {
                                    auto backup {erasion->next};
                                    erasion->next = nullptr;
                                    f.node_size.allocator().deallocate(backup->node(), insertion_size);
                                    f.node_size() = count;
                                    break;
                                }
                            }
                            const std::string s2 {"insert"};
                            f.front() = s2;
                            auto result {f.insert(0, f.front(), insertion_size)};
                            assert(f.size() == count + static_cast<size_t>(insertion_size));
                            assert(not f.empty());
                            assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                            assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                            assert(f.front() == s2);
                            const auto end {advance(f.begin(), insertion_size + 1)};
                            for(auto it {f.begin()}; it not_eq end; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {end}; it not_eq f.end(); ++it) {
                                assert(*it == s);
                            }
                            const auto cend {advance(f.cbegin(), insertion_size + 1)};
                            for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {cend}; it not_eq f.cend(); ++it) {
                                assert(*it == s);
                            }
                            assert(result == f.begin());
                            assert(result == f.cbegin());
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to head/Without reallocation/The value is from self done." << std::endl;
                        }

                        std::cout << "\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to head/Without reallocation finished!" << std::endl;
                    }

                    // with reallocation
                    {
                        std::cout << "\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to head/With reallocation!" << std::endl;

                        // insertion size less equal to tail size
                        {
                            auto count {this->generate_count()};
                            while(count <= 1) {
                                count = this->generate_count();
                            }
                            auto insertion_size {this->generate_a_random_number(1, count)};
                            const std::string s {"init"};
                            forward_list<std::string> f(count, s);
                            const std::string s2 {"insert"};
                            const auto result {f.insert(0, s2, insertion_size)};
                            assert(f.size() == count + static_cast<size_t>(insertion_size));
                            assert(not f.empty());
                            assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                            assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                            assert(f.front() == s2);
                            const auto end {advance(f.begin(), insertion_size)};
                            for(auto it {f.begin()}; it not_eq end; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {end}; it not_eq f.end(); ++it) {
                                assert(*it == s);
                            }
                            const auto cend {advance(f.cbegin(), insertion_size)};
                            for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {cend}; it not_eq f.cend(); ++it) {
                                assert(*it == s);
                            }
                            assert(result == f.begin());
                            assert(result == f.cbegin());
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to head/With reallocation/Insertion size less equal to tail size done." << std::endl;
                        }

                        // insertion size greater than tail size
                        {
                            auto count {this->generate_count()};
                            while(count <= 1) {
                                count = this->generate_count();
                            }
                            const auto insertion_size {this->generate_a_random_number(count + 1)};
                            const std::string s {"init"};
                            forward_list<std::string> f(count, s);
                            const std::string s2 {"insert"};
                            const auto result {f.insert(0, s2, insertion_size)};
                            assert(f.size() == count + static_cast<size_t>(insertion_size));
                            assert(not f.empty());
                            assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                            assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                            assert(f.front() == s2);
                            const auto end {advance(f.begin(), insertion_size)};
                            for(auto it {f.begin()}; it not_eq end; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {end}; it not_eq f.end(); ++it) {
                                assert(*it == s);
                            }
                            const auto cend {advance(f.cbegin(), insertion_size)};
                            for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {cend}; it not_eq f.cend(); ++it) {
                                assert(*it == s);
                            }
                            assert(result == f.begin());
                            assert(result == f.cbegin());
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to head/With reallocation/Insertion size greater than tail size done." << std::endl;
                        }

                        // insertion size less equal to double capacity
                        {
                            auto count {this->generate_count()};
                            while(count <= 1) {
                                count = this->generate_count();
                            }
                            auto insertion_size {this->generate_a_random_number(1, count)};
                            const std::string s {"init"};
                            forward_list<std::string> f(count, s);
                            const std::string s2 {"insert"};
                            auto result {f.insert(0, s2, insertion_size)};
                            assert(f.size() == count + static_cast<size_t>(insertion_size));
                            assert(not f.empty());
                            assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                            assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                            assert(f.front() == s2);
                            const auto end {advance(f.begin(), insertion_size)};
                            for(auto it {f.begin()}; it not_eq end; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {end}; it not_eq f.end(); ++it) {
                                assert(*it == s);
                            }
                            const auto cend {advance(f.cbegin(), insertion_size)};
                            for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {cend}; it not_eq f.cend(); ++it) {
                                assert(*it == s);
                            }
                            assert(result == f.begin());
                            assert(result == f.cbegin());
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to head/With reallocation/Insertion size less equal to double capacity done." << std::endl;
                        }

                        // insertion size greater than double capacity
                        {
                            auto count {this->generate_count()};
                            while(count <= 1) {
                                count = this->generate_count();
                            }
                            const auto insertion_size {this->generate_a_random_number(2 * count + 1)};
                            const std::string s {"init"};
                            forward_list<std::string> f(count, s);
                            const auto s2 {"insert"};
                            auto result {f.insert(0, s2, insertion_size)};
                            assert(f.size() == count + static_cast<size_t>(insertion_size));
                            assert(not f.empty());
                            assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                            assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                            assert(f.front() == s2);
                            const auto end {advance(f.begin(), insertion_size)};
                            for(auto it {f.begin()}; it not_eq end; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {end}; it not_eq f.end(); ++it) {
                                assert(*it == s);
                            }
                            const auto cend {advance(f.cbegin(), insertion_size)};
                            for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {cend}; it not_eq f.cend(); ++it) {
                                assert(*it == s);
                            }
                            assert(result == f.begin());
                            assert(result == f.cbegin());
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to head/With reallocation/Insertion size greater than double capacity done." << std::endl;
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
                            forward_list<std::string> f(count, s);
                            const std::string s2 {"insert"};
                            f.front() = s2;
                            auto result {f.insert(0, f.front(), insertion_size)};
                            assert(f.size() == count + static_cast<size_t>(insertion_size));
                            assert(not f.empty());
                            assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                            assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                            assert(f.front() == s2);
                            const auto end {advance(f.begin(), insertion_size + 1)};
                            for(auto it {f.begin()}; it not_eq end; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {end}; it not_eq f.end(); ++it) {
                                assert(*it == s);
                            }
                            const auto cend {advance(f.cbegin(), insertion_size + 1)};
                            for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {cend}; it not_eq f.cend(); ++it) {
                                assert(*it == s);
                            }
                            assert(result == f.begin());
                            assert(result == f.cbegin());
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to head/With reallocation/The value is from self done." << std::endl;
                        }

                        std::cout << "\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to head/With reallocation finished!" << std::endl;
                    }

                    std::cout << "\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to head finished!" << std::endl;
                }

                // insert to random position
                {
                    std::cout << "\t\t\tStart checking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to random position!" << std::endl;

                    // without reallocation
                    {
                        std::cout << "\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to random position/Without reallocation!" << std::endl;

                        // insertion size is zero
                        {
                            auto count {this->generate_count()};
                            while(count <= 2) {
                                count = this->generate_count();
                            }
                            const auto new_size {this->generate_a_random_number(2, count - 1)};
                            const std::string s {"insert"};
                            const auto insertion_position {this->generate_a_random_number(1, new_size - 1)};
                            forward_list<std::string> f(count, s);
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
                            const auto result {f.insert(insertion_position, "hello", 0)};
                            assert(f.size() == new_size);
                            assert(not f.empty());
                            assert(advance(f.begin(), new_size) == f.end());
                            assert(advance(f.cbegin(), new_size) == f.cend());
                            assert(f.front() == s);
                            for(auto it {advance(f.begin(), 1)}; it not_eq f.end(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {advance(f.cbegin(), 1)}; it not_eq f.cend(); ++it) {
                                assert(*it == s);
                            }
                            assert(result == advance(f.begin(), insertion_position));
                            assert(result == advance(f.cbegin(), insertion_position));
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to random position/Without reallocation/Insertion size is zero done." << std::endl;
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
                            forward_list<std::string> f(count + static_cast<size_t>(insertion_size) + spare, s);
                            auto erasion {&f.head};
                            for(auto i {count};; erasion = erasion->next) {
                                if(i-- == 0) {
                                    auto backup {erasion->next};
                                    erasion->next = nullptr;
                                    f.node_size.allocator().deallocate(backup->node(), insertion_size + spare);
                                    f.node_size() = count;
                                    break;
                                }
                            }
                            auto s2 {"insert"};
                            const auto result {f.insert(insertion_position, s2, insertion_size)};
                            assert(f.size() == count + static_cast<size_t>(insertion_size));
                            assert(not f.empty());
                            assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                            assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                            assert(f.front() == s);
                            const auto end1 {advance(f.begin(), insertion_position)};
                            for(auto it {f.begin()}; it not_eq end1; ++it) {
                                assert(*it == s);
                            }
                            const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                            for(auto it {end1}; it not_eq end2; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {end2}; it not_eq f.end(); ++it) {
                                assert(*it == s);
                            }
                            const auto cend1 {advance(f.cbegin(), insertion_position)};
                            for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                                assert(*it == s);
                            }
                            const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                            for(auto it {cend1}; it not_eq cend2; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {cend2}; it not_eq f.cend(); ++it) {
                                assert(*it == s);
                            }
                            assert(result == advance(f.begin(), insertion_position));
                            assert(result == advance(f.cbegin(), insertion_position));
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to random position/Without reallocation/Insertion size less equal to tail size done." << std::endl;
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
                            forward_list<std::string> f(count + static_cast<size_t>(insertion_size) + spare, s);
                            auto erasion {&f.head};
                            for(auto i {count};; erasion = erasion->next) {
                                if(i-- == 0) {
                                    auto backup {erasion->next};
                                    erasion->next = nullptr;
                                    f.node_size.allocator().deallocate(backup->node(), static_cast<size_t>(insertion_size) + spare);
                                    f.node_size() = count;
                                    break;
                                }
                            }
                            const std::string s2 {"insert"};
                            const auto result {f.insert(insertion_position, s2, insertion_size)};
                            assert(f.size() == count + static_cast<size_t>(insertion_size));
                            assert(not f.empty());
                            assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                            assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                            assert(f.front() == s);
                            const auto end1 {advance(f.begin(), insertion_position)};
                            for(auto it {f.begin()}; it not_eq end1; ++it) {
                                assert(*it == s);
                            }
                            const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                            for(auto it {end1}; it not_eq end2; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {end2}; it not_eq f.end(); ++it) {
                                assert(*it == s);
                            }
                            const auto cend1 {advance(f.cbegin(), insertion_position)};
                            for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                                assert(*it == s);
                            }
                            const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                            for(auto it {cend1}; it not_eq cend2; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {cend2}; it not_eq f.cend(); ++it) {
                                assert(*it == s);
                            }
                            assert(result == advance(f.begin(), insertion_position));
                            assert(result == advance(f.cbegin(), insertion_position));
                            std::cout << "\t\t\t\t\tChecking test_test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to random position/Without reallocation/Insertion size greater than tail size done." << std::endl;
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
                            forward_list<std::string> f(count + static_cast<size_t>(insertion_size), s);
                            auto erasion {&f.head};
                            for(auto i {count};; erasion = erasion->next) {
                                if(i-- == 0) {
                                    auto backup {erasion->next};
                                    erasion->next = nullptr;
                                    f.node_size.allocator().deallocate(backup->node(), insertion_size);
                                    f.node_size() = count;
                                    break;
                                }
                            }
                            const std::string s2 {"insert"};
                            *advance(f.begin(), insertion_position) = s2;
                            auto result {f.insert(insertion_position, *advance(f.begin(), insertion_position), insertion_size)};
                            assert(f.size() == count + static_cast<size_t>(insertion_size));
                            assert(not f.empty());
                            assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                            assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                            assert(f.front() == s);
                            const auto end1 {advance(f.begin(), insertion_position)};
                            for(auto it {f.begin()}; it not_eq end1; ++it) {
                                assert(*it == s);
                            }
                            const auto end2 {advance(f.begin(), insertion_position + insertion_size + 1)};
                            for(auto it {end1}; it not_eq end2; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {end2}; it not_eq f.end(); ++it) {
                                assert(*it == s);
                            }
                            const auto cend1 {advance(f.cbegin(), insertion_position)};
                            for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                                assert(*it == s);
                            }
                            const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size + 1)};
                            for(auto it {cend1}; it not_eq cend2; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {cend2}; it not_eq f.cend(); ++it) {
                                assert(*it == s);
                            }
                            assert(result == advance(f.begin(), insertion_position));
                            assert(result == advance(f.cbegin(), insertion_position));
                            std::cout << "\t\t\t\t\tChecking test_test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to random position/Without reallocation/The value is from self done." << std::endl;
                        }

                        std::cout << "\t\t\t\tStart checking test_test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to random position/Without reallocation finished!" << std::endl;
                    }

                    // with reallocation
                    {
                        std::cout << "\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to random position/With reallocation!" << std::endl;

                        // insertion size less equal to tail size
                        {
                            auto count {this->generate_count()};
                            while(count <= 1) {
                                count = this->generate_count();
                            }
                            const auto insertion_position {this->generate_a_random_number(1, count - 1)};
                            auto insertion_size {this->generate_a_random_number(1, count - insertion_position)};
                            const std::string s {"init"};
                            forward_list<std::string> f(count, s);
                            const std::string s2 {"insert"};
                            const auto result {f.insert(insertion_position, s2, insertion_size)};
                            assert(f.size() == count + static_cast<size_t>(insertion_size));
                            assert(not f.empty());
                            assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                            assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                            assert(f.front() == s);
                            const auto end1 {advance(f.begin(), insertion_position)};
                            for(auto it {f.begin()}; it not_eq end1; ++it) {
                                assert(*it == s);
                            }
                            const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                            for(auto it {end1}; it not_eq end2; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {end2}; it not_eq f.end(); ++it) {
                                assert(*it == s);
                            }
                            const auto cend1 {advance(f.cbegin(), insertion_position)};
                            for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                                assert(*it == s);
                            }
                            const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                            for(auto it {cend1}; it not_eq cend2; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {cend2}; it not_eq f.cend(); ++it) {
                                assert(*it == s);
                            }
                            assert(result == advance(f.begin(), insertion_position));
                            assert(result == advance(f.cbegin(), insertion_position));
                            std::cout << "\t\t\t\t\tChecking test_insert_1/Insert to non-empty forward_list/Insert to random position/With reallocation/Insertion size less equal to tail size done." << std::endl;
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
                            forward_list<std::string> f(count, s);
                            const std::string s2 {"insert"};
                            const auto result {f.insert(insertion_position, s2, insertion_size)};
                            assert(f.size() == count + static_cast<size_t>(insertion_size));
                            assert(not f.empty());
                            assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                            assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                            assert(f.front() == s);
                            const auto end1 {advance(f.begin(), insertion_position)};
                            for(auto it {f.begin()}; it not_eq end1; ++it) {
                                assert(*it == s);
                            }
                            const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                            for(auto it {end1}; it not_eq end2; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {end2}; it not_eq f.end(); ++it) {
                                assert(*it == s);
                            }
                            const auto cend1 {advance(f.cbegin(), insertion_position)};
                            for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                                assert(*it == s);
                            }
                            const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                            for(auto it {cend1}; it not_eq cend2; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {cend2}; it not_eq f.cend(); ++it) {
                                assert(*it == s);
                            }
                            assert(result == advance(f.begin(), insertion_position));
                            assert(result == advance(f.cbegin(), insertion_position));
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to random position/With reallocation/Insertion size greater than tail size done." << std::endl;
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
                            forward_list<std::string> f(count, s);
                            const std::string s2 {"insert"};
                            auto result {f.insert(insertion_position, s2, insertion_size)};
                            assert(f.size() == count + static_cast<size_t>(insertion_size));
                            assert(not f.empty());
                            assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                            assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                            assert(f.front() == s);
                            const auto end1 {advance(f.begin(), insertion_position)};
                            for(auto it {f.begin()}; it not_eq end1; ++it) {
                                assert(*it == s);
                            }
                            const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                            for(auto it {end1}; it not_eq end2; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {end2}; it not_eq f.end(); ++it) {
                                assert(*it == s);
                            }
                            const auto cend1 {advance(f.cbegin(), insertion_position)};
                            for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                                assert(*it == s);
                            }
                            const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                            for(auto it {cend1}; it not_eq cend2; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {cend2}; it not_eq f.cend(); ++it) {
                                assert(*it == s);
                            }
                            assert(result == advance(f.begin(), insertion_position));
                            assert(result == advance(f.cbegin(), insertion_position));
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to random position/With reallocation/Insertion size less equal to double capacity done." << std::endl;
                        }

                        // insertion size greater than double capacity
                        {
                            auto count {this->generate_count()};
                            while(count <= 2) {
                                count = this->generate_count();
                            }
                            const auto insertion_position {this->generate_a_random_number(1, count - 2)};
                            const auto insertion_size {this->generate_a_random_number(2 * count + 1)};
                            const std::string s {"init"};
                            forward_list<std::string> f(count, s);
                            const std::string s2 {"insert"};
                            auto result {f.insert(insertion_position, s2, insertion_size)};
                            assert(f.size() == count + static_cast<size_t>(insertion_size));
                            assert(not f.empty());
                            assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                            assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                            assert(f.front() == s);
                            const auto end1 {advance(f.begin(), insertion_position)};
                            for(auto it {f.begin()}; it not_eq end1; ++it) {
                                assert(*it == s);
                            }
                            const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                            for(auto it {end1}; it not_eq end2; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {end2}; it not_eq f.end(); ++it) {
                                assert(*it == s);
                            }
                            const auto cend1 {advance(f.cbegin(), insertion_position)};
                            for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                                assert(*it == s);
                            }
                            const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                            for(auto it {cend1}; it not_eq cend2; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {cend2}; it not_eq f.cend(); ++it) {
                                assert(*it == s);
                            }
                            assert(result == advance(f.begin(), insertion_position));
                            assert(result == advance(f.cbegin(), insertion_position));
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to random position/With reallocation/Insertion size greater than double capacity done." << std::endl;
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
                            forward_list<std::string> f(count, s);
                            const std::string s2 {"insert"};
                            *advance(f.begin(), insertion_position) = s2;
                            auto result {f.insert(insertion_position, *advance(f.begin(), insertion_position), insertion_size)};
                            assert(f.size() == count + static_cast<size_t>(insertion_size));
                            assert(not f.empty());
                            assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                            assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                            assert(f.front() == s);
                            const auto end1 {advance(f.begin(), insertion_position)};
                            for(auto it {f.begin()}; it not_eq end1; ++it) {
                                assert(*it == s);
                            }
                            const auto end2 {advance(f.begin(), insertion_position + insertion_size + 1)};
                            for(auto it {end1}; it not_eq end2; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {end2}; it not_eq f.end(); ++it) {
                                assert(*it == s);
                            }
                            const auto cend1 {advance(f.cbegin(), insertion_position)};
                            for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                                assert(*it == s);
                            }
                            const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size + 1)};
                            for(auto it {cend1}; it not_eq cend2; ++it) {
                                assert(*it == s2);
                            }
                            for(auto it {cend2}; it not_eq f.cend(); ++it) {
                                assert(*it == s);
                            }
                            assert(result == advance(f.begin(), insertion_position));
                            assert(result == advance(f.cbegin(), insertion_position));
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to random position/With reallocation/The value is from self done." << std::endl;
                        }

                        std::cout << "\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to random position/With reallocation finished!" << std::endl;
                    }

                    std::cout << "\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to random position finished!" << std::endl;
                }

                // insert to tail
                {
                    std::cout << "\t\t\tStart checking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to tail!" << std::endl;

                    // without reallocation
                    {
                        std::cout << "\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to tail/Without reallocation!" << std::endl;

                        // insertion size is zero
                        {
                            auto count {this->generate_count()};
                            while(count <= 1) {
                                count = this->generate_count();
                            }
                            const auto new_size {this->generate_a_random_number(1, count - 1)};
                            const std::string s {"init"};
                            forward_list<std::string> f(count, s);
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
                            const auto result {f.insert(new_size, "hello", 0)};
                            assert(f.size() == new_size);
                            assert(not f.empty());
                            assert(advance(f.begin(), new_size) == f.end());
                            assert(advance(f.cbegin(), new_size) == f.cend());
                            assert(f.front() == s);
                            for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                                assert(*it == s);
                            }
                            for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                                assert(*it == s);
                            }
                            assert(result == f.end());
                            assert(result == f.cend());
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to tail/Without reallocation/Insertion size is zero done." << std::endl;
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
                            forward_list<std::string> f(count + static_cast<size_t>(insertion_size) + spare, s);
                            auto erasion {&f.head};
                            for(auto i {count};; erasion = erasion->next) {
                                if(i-- == 0) {
                                    auto backup {erasion->next};
                                    erasion->next = nullptr;
                                    f.node_size.allocator().deallocate(backup->node(), insertion_size + spare);
                                    f.node_size() = count;
                                    break;
                                }
                            }
                            const std::string s2 {"insert"};
                            const auto result {f.insert(count, s2, insertion_size)};
                            assert(f.size() == count + static_cast<size_t>(insertion_size));
                            assert(not f.empty());
                            assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                            assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                            assert(f.front() == s);
                            const auto end {advance(f.begin(), count)};
                            for(auto it {f.begin()}; it not_eq end; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {end}; it not_eq f.end(); ++it) {
                                assert(*it == s2);
                            }
                            const auto cend {advance(f.cbegin(), count)};
                            for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {cend}; it not_eq f.cend(); ++it) {
                                assert(*it == s2);
                            }
                            assert(result == advance(f.begin(), count));
                            assert(result == advance(f.cbegin(), count));
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to tail/Without reallocation/Insertion size less equal to tail size done." << std::endl;
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
                            forward_list<std::string> f(count + static_cast<size_t>(insertion_size) + spare, s);
                            auto erasion {&f.head};
                            for(auto i {count};; erasion = erasion->next) {
                                if(i-- == 0) {
                                    auto backup {erasion->next};
                                    erasion->next = nullptr;
                                    f.node_size.allocator().deallocate(backup->node(), static_cast<size_t>(insertion_size) + spare);
                                    f.node_size() = count;
                                    break;
                                }
                            }
                            const std::string s2 {"insert"};
                            const auto result {f.insert(count, s2, insertion_size)};
                            assert(f.size() == count + static_cast<size_t>(insertion_size));
                            assert(not f.empty());
                            assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                            assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                            assert(f.front() == s);
                            const auto end {advance(f.begin(), count)};
                            for(auto it {f.begin()}; it not_eq end; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {end}; it not_eq f.end(); ++it) {
                                assert(*it == s2);
                            }
                            const auto cend {advance(f.cbegin(), count)};
                            for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {cend}; it not_eq f.cend(); ++it) {
                                assert(*it == s2);
                            }
                            assert(result == advance(f.begin(), count));
                            assert(result == advance(f.cbegin(), count));
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to tail/Without reallocation/Insertion size greater than tail size done." << std::endl;
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
                            forward_list<std::string> f(count + static_cast<size_t>(insertion_size), s);
                            auto erasion {&f.head};
                            for(auto i {count};; erasion = erasion->next) {
                                if(i-- == 0) {
                                    auto backup {erasion->next};
                                    erasion->next = nullptr;
                                    f.node_size.allocator().deallocate(backup->node(), insertion_size);
                                    f.node_size() = count;
                                    break;
                                }
                            }
                            const std::string s2 {"insert"};
                            *advance(f.begin(), f.size() - 1) = s2;
                            const auto result {f.insert(count, *advance(f.begin(), f.size() - 1), insertion_size)};
                            assert(f.size() == count + static_cast<size_t>(insertion_size));
                            assert(not f.empty());
                            assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                            assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                            assert(f.front() == s);
                            const auto end {advance(f.begin(), count - 1)};
                            for(auto it {f.begin()}; it not_eq end; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {end}; it not_eq f.end(); ++it) {
                                assert(*it == s2);
                            }
                            const auto cend {advance(f.cbegin(), count - 1)};
                            for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {cend}; it not_eq f.cend(); ++it) {
                                assert(*it == s2);
                            }
                            assert(result == advance(f.begin(), count));
                            assert(result == advance(f.cbegin(), count));
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to tail/Without reallocation/The value is from self done." << std::endl;
                        }

                        std::cout << "\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to tail/Without reallocation finished!" << std::endl;
                    }

                    // with reallocation
                    {
                        std::cout << "\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to tail/With reallocation!" << std::endl;

                        // insertion size less equal to tail size
                        {
                            auto count {this->generate_count()};
                            while(count <= 1) {
                                count = this->generate_count();
                            }
                            auto insertion_size {this->generate_a_random_number(1, count)};
                            const std::string s {"init"};
                            forward_list<std::string> f(count, s);
                            const auto s2 {"insert"};
                            const auto result {f.insert(count, s2, insertion_size)};
                            assert(f.size() == count + static_cast<size_t>(insertion_size));
                            assert(not f.empty());
                            assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                            assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                            assert(f.front() == s);
                            const auto end {advance(f.begin(), count)};
                            for(auto it {f.begin()}; it not_eq end; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {end}; it not_eq f.end(); ++it) {
                                assert(*it == s2);
                            }
                            const auto cend {advance(f.cbegin(), count)};
                            for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {cend}; it not_eq f.cend(); ++it) {
                                assert(*it == s2);
                            }
                            assert(result == advance(f.begin(), count));
                            assert(result == advance(f.cbegin(), count));
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to tail/With reallocation/Insertion size less equal to tail size done." << std::endl;
                        }

                        // insertion size greater than tail size
                        {
                            auto count {this->generate_count()};
                            while(count <= 1) {
                                count = this->generate_count();
                            }
                            const auto insertion_size {this->generate_a_random_number(count + 1)};
                            const std::string s {"init"};
                            forward_list<std::string> f(count, s);
                            const std::string s2 {"insert"};
                            const auto result {f.insert(count, s2, insertion_size)};
                            assert(f.size() == count + static_cast<size_t>(insertion_size));
                            assert(not f.empty());
                            assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                            assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                            assert(f.front() == s);
                            const auto end {advance(f.begin(), count)};
                            for(auto it {f.begin()}; it not_eq end; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {end}; it not_eq f.end(); ++it) {
                                assert(*it == s2);
                            }
                            const auto cend {advance(f.cbegin(), count)};
                            for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {cend}; it not_eq f.cend(); ++it) {
                                assert(*it == s2);
                            }
                            assert(result == advance(f.begin(), count));
                            assert(result == advance(f.cbegin(), count));
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to tail/With reallocation/Insertion size greater than tail size done." << std::endl;
                        }

                        // insertion size less equal to double capacity
                        {
                            auto count {this->generate_count()};
                            while(count <= 1) {
                                count = this->generate_count();
                            }
                            auto insertion_size {this->generate_a_random_number(1, count)};
                            const std::string s {"init"};
                            forward_list<std::string> f(count, s);
                            const std::string s2 {"insert"};
                            auto result {f.insert(count, s2, insertion_size)};
                            assert(f.size() == count + static_cast<size_t>(insertion_size));
                            assert(not f.empty());
                            assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                            assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                            assert(f.front() == s);
                            const auto end {advance(f.begin(), count)};
                            for(auto it {f.begin()}; it not_eq end; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {end}; it not_eq f.end(); ++it) {
                                assert(*it == s2);
                            }
                            const auto cend {advance(f.cbegin(), count)};
                            for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {cend}; it not_eq f.cend(); ++it) {
                                assert(*it == s2);
                            }
                            assert(result == advance(f.begin(), count));
                            assert(result == advance(f.cbegin(), count));
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to tail/With reallocation/Insertion size less equal to double capacity done." << std::endl;
                        }

                        // insertion size greater than double capacity
                        {
                            auto count {this->generate_count()};
                            while(count <= 1) {
                                count = this->generate_count();
                            }
                            const auto insertion_size {this->generate_a_random_number(2 * count + 1)};
                            const std::string s {"init"};
                            forward_list<std::string> f(count, s);
                            const std::string s2 {"insert"};
                            auto result {f.insert(count, s2, insertion_size)};
                            assert(f.size() == count + static_cast<size_t>(insertion_size));
                            assert(not f.empty());
                            assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                            assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                            assert(f.front() == s);
                            const auto end {advance(f.begin(), count)};
                            for(auto it {f.begin()}; it not_eq end; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {end}; it not_eq f.end(); ++it) {
                                assert(*it == s2);
                            }
                            const auto cend {advance(f.cbegin(), count)};
                            for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {cend}; it not_eq f.cend(); ++it) {
                                assert(*it == s2);
                            }
                            assert(result == advance(f.begin(), count));
                            assert(result == advance(f.cbegin(), count));
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to tail/With reallocation/Insertion size greater than double capacity done." << std::endl;
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
                            forward_list<std::string> f(count, s);
                            const std::string s2 {"insert"};
                            *advance(f.begin(), f.size() - 1) = s2;
                            auto result {f.insert(count, *advance(f.begin(), f.size() - 1), insertion_size)};
                            assert(f.size() == count + static_cast<size_t>(insertion_size));
                            assert(not f.empty());
                            assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                            assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                            assert(f.front() == s);
                            const auto end {advance(f.begin(), count - 1)};
                            for(auto it {f.begin()}; it not_eq end; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {end}; it not_eq f.end(); ++it) {
                                assert(*it == s2);
                            }
                            const auto cend {advance(f.cbegin(), count - 1)};
                            for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                                assert(*it == s);
                            }
                            for(auto it {cend}; it not_eq f.cend(); ++it) {
                                assert(*it == s2);
                            }
                            assert(result == advance(f.begin(), count));
                            assert(result == advance(f.cbegin(), count));
                            std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to tail/With reallocation/The value is from self done." << std::endl;
                        }

                        std::cout << "\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to tail/With reallocation finished!" << std::endl;
                    }

                    std::cout << "\t\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list/Insert to tail finished!" << std::endl;
                }

                std::cout << "\t\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type)/Insert to non-empty forward_list finished!" << std::endl;
            }
        }

        std::cout << "\tChecking test_non_trivial/iterator insert(size_type, const_reference, size_type) for ds::forward_list finished!" << std::endl;
    }

    // iterator insert(size_type, ForwardIterator, ForwardIterator)
    {
        std::cout << "\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/ for ds::forward_list!" << std::endl;

        // insert to empty forward_list
        {
            std::cout << "\t\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to empty forward_list for ds::forward_list!" << std::endl;

            // insertion size equal to zero
            {
                forward_list<std::string> f {};
                const auto result {f.insert(0, std_string_random_access_iterator {}, std_string_random_access_iterator {})};
                assert(f.size() == 0);
                assert(f.empty());
                assert(f.begin() == f.end());
                assert(f.cbegin() == f.cend());
                assert(result == f.begin());
                assert(result == f.cbegin());
                std::cout << "\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to empty forward_list/Insertion size not equal to zero done." << std::endl;
            }

            // insertion size not equal to zero
            {
                forward_list<std::string> f {};
                auto insertion_size {this->generate_count()};
                while(insertion_size == 0) {
                    insertion_size = this->generate_count();
                }
                const std::vector<std::string> strings(insertion_size, "init");
                auto d {this->to_random_access_iterator(strings)};
                const auto result {f.insert(0, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                assert(f.size() == insertion_size);
                assert(not f.empty());
                assert(advance(f.begin(), insertion_size) == f.end());
                assert(advance(f.cbegin(), insertion_size) == f.cend());
                assert(f.front() == strings.front());\
                auto i {0uz};
                for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                    assert(*it == strings[i++]);
                }
                i = 0;
                for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                    assert(*it == strings[i++]);
                }
                assert(result == f.begin());
                assert(result == f.cbegin());
                std::cout << "\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to empty forward_list/Insertion size not equal to zero done." << std::endl;
            }

            std::cout << "\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to empty forward_list for ds::forward_list finished!" << std::endl;
        }

        // insert to non-empty forward_list
        {
            std::cout << "\t\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list!" << std::endl;

            // insert to head
            {
                std::cout << "\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to head!" << std::endl;

                // without reallocation
                {
                    std::cout << "\t\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to head/Without reallocation!" << std::endl;

                    // insertion size is zero
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto new_size {this->generate_a_random_number(1, count - 1)};
                        const std::string s {"init"};
                        forward_list<std::string> f(count, s);
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
                        const auto result {f.insert(0, std_string_random_access_iterator {}, std_string_random_access_iterator {})};
                        assert(f.size() == new_size);
                        assert(not f.empty());
                        assert(advance(f.begin(), new_size) == f.end());
                        assert(advance(f.cbegin(), new_size) == f.cend());
                        assert(f.front() == s);
                        for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                            assert(*it == s);
                        }
                        for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                            assert(*it == s);
                        }
                        assert(result == f.begin());
                        assert(result == f.cbegin());
                        std::cout << "\t\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to head/Without reallocation/Insertion size is zero done." << std::endl;
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
                        forward_list<std::string> f(count + static_cast<size_t>(insertion_size) + spare, s);
                        auto erasion {&f.head};
                        for(auto i {count};; erasion = erasion->next) {
                            if(i-- == 0) {
                                auto backup {erasion->next};
                                erasion->next = nullptr;
                                f.node_size.allocator().deallocate(backup->node(), insertion_size + spare);
                                f.node_size() = count;
                                break;
                            }
                        }
                        const auto result {f.insert(0, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == strings.front());
                        auto string_i {0uz};
                        const auto end {advance(f.begin(), insertion_size)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        const auto cend {advance(f.cbegin(), insertion_size)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == s);
                        }
                        assert(result == f.begin());
                        assert(result == f.cbegin());
                        std::cout << "\t\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to head/Without reallocation/Insertion size less equal to tail size done." << std::endl;
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
                        forward_list<std::string> f(count + static_cast<size_t>(insertion_size) + spare, s);
                        auto erasion {&f.head};
                        for(auto i {count};; erasion = erasion->next) {
                            if(i-- == 0) {
                                auto backup {erasion->next};
                                erasion->next = nullptr;
                                f.node_size.allocator().deallocate(backup->node(), static_cast<size_t>(insertion_size) + spare);
                                f.node_size() = count;
                                break;
                            }
                        }
                        const auto result {f.insert(0, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == strings.front());
                        auto string_i {0uz};
                        const auto end {advance(f.begin(), insertion_size)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        const auto cend {advance(f.cbegin(), insertion_size)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == s);
                        }
                        assert(result == f.begin());
                        assert(result == f.cbegin());
                        std::cout << "\t\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to head/Without reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    std::cout << "\t\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to head/Without reallocation finished!" << std::endl;
                }

                // with reallocation
                {
                    std::cout << "\t\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to head/With reallocation!" << std::endl;

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
                        forward_list<std::string> f(count, s);
                        const auto result {f.insert(0, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == strings.front());
                        auto string_i {0uz};
                        const auto end {advance(f.begin(), insertion_size)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        const auto cend {advance(f.cbegin(), insertion_size)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == s);
                        }
                        assert(result == f.begin());
                        assert(result == f.cbegin());
                        std::cout << "\t\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to head/With reallocation/Insertion size less equal to tail size done." << std::endl;
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
                        forward_list<std::string> f(count, s);
                        const auto result {f.insert(0, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == strings.front());
                        auto string_i {0uz};
                        const auto end {advance(f.begin(), insertion_size)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        const auto cend {advance(f.cbegin(), insertion_size)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == s);
                        }
                        assert(result == f.begin());
                        assert(result == f.cbegin());
                        std::cout << "\t\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to head/With reallocation/Insertion size greater than tail size done." << std::endl;
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
                        forward_list<std::string> f(count, s);
                        auto result {f.insert(0, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == strings.front());
                        auto string_i {0uz};
                        const auto end {advance(f.begin(), insertion_size)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        const auto cend {advance(f.cbegin(), insertion_size)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == s);
                        }
                        assert(result == f.begin());
                        assert(result == f.cbegin());
                        std::cout << "\t\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to head/With reallocation/Insertion size less equal to double capacity done." << std::endl;
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
                        forward_list<std::string> f(count, s);
                        auto result {f.insert(0, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == strings.front());
                        auto string_i {0uz};
                        const auto end {advance(f.begin(), insertion_size)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        const auto cend {advance(f.cbegin(), insertion_size)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == s);
                        }
                        assert(result == f.begin());
                        assert(result == f.cbegin());
                        std::cout << "\t\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to head/With reallocation/Insertion size greater than double capacity done." << std::endl;
                    }

                    std::cout << "\t\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to head/With reallocation finished!" << std::endl;
                }

                std::cout << "\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to head finished!" << std::endl;
            }

            // insert to random position
            {
                std::cout << "\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to random position!" << std::endl;

                // without reallocation
                {
                    std::cout << "\t\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to random position/Without reallocation!" << std::endl;

                    // insertion size is zero
                    {
                        auto count {this->generate_count()};
                        while(count <= 2) {
                            count = this->generate_count();
                        }
                        const auto new_size {this->generate_a_random_number(2, count - 1)};
                        const std::string s {"init"};
                        const auto insertion_position {this->generate_a_random_number(1, new_size - 1)};
                        forward_list<std::string> f(count, s);
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
                        const auto result {f.insert(insertion_position, std_string_random_access_iterator {}, std_string_random_access_iterator {})};
                        assert(f.size() == new_size);
                        assert(not f.empty());
                        assert(advance(f.begin(), new_size) == f.end());
                        assert(advance(f.cbegin(), new_size) == f.cend());
                        assert(f.front() == s);
                        for(auto it {advance(f.begin(), 1)}; it not_eq f.end(); ++it) {
                            assert(*it == s);
                        }
                        for(auto it {advance(f.cbegin(), 1)}; it not_eq f.cend(); ++it) {
                            assert(*it == s);
                        }
                        assert(result == advance(f.begin(), insertion_position));
                        assert(result == advance(f.cbegin(), insertion_position));
                        std::cout << "\t\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to random position/Without reallocation/Insertion size is zero done." << std::endl;
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
                        forward_list<std::string> f(count + static_cast<size_t>(insertion_size) + spare, s);
                        auto erasion {&f.head};
                        for(auto i {count};; erasion = erasion->next) {
                            if(i-- == 0) {
                                auto backup {erasion->next};
                                erasion->next = nullptr;
                                f.node_size.allocator().deallocate(backup->node(), insertion_size + spare);
                                f.node_size() = count;
                                break;
                            }
                        }
                        const auto result {f.insert(insertion_position, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == s);
                        auto string_i {0uz};
                        const auto end1 {advance(f.begin(), insertion_position)};
                        for(auto it {f.begin()}; it not_eq end1; ++it) {
                            assert(*it == s);
                        }
                        const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                        for(auto it {end1}; it not_eq end2; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {end2}; it not_eq f.end(); ++it) {
                            assert(*it == s);
                        }
                        const auto cend1 {advance(f.cbegin(), insertion_position)};
                        for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                        for(auto it {cend1}; it not_eq cend2; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {cend2}; it not_eq f.cend(); ++it) {
                            assert(*it == s);
                        }
                        assert(result == advance(f.begin(), insertion_position));
                        assert(result == advance(f.cbegin(), insertion_position));
                        std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to random position/Without reallocation/Insertion size less equal to tail size done." << std::endl;
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
                        forward_list<std::string> f(count + static_cast<size_t>(insertion_size) + spare, s);
                        auto erasion {&f.head};
                        for(auto i {count};; erasion = erasion->next) {
                            if(i-- == 0) {
                                auto backup {erasion->next};
                                erasion->next = nullptr;
                                f.node_size.allocator().deallocate(backup->node(), static_cast<size_t>(insertion_size) + spare);
                                f.node_size() = count;
                                break;
                            }
                        }
                        const auto result {f.insert(insertion_position, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == s);
                        auto string_i {0uz};
                        const auto end1 {advance(f.begin(), insertion_position)};
                        for(auto it {f.begin()}; it not_eq end1; ++it) {
                            assert(*it == s);
                        }
                        const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                        for(auto it {end1}; it not_eq end2; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {end2}; it not_eq f.end(); ++it) {
                            assert(*it == s);
                        }
                        const auto cend1 {advance(f.cbegin(), insertion_position)};
                        for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                        for(auto it {cend1}; it not_eq cend2; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {cend2}; it not_eq f.cend(); ++it) {
                            assert(*it == s);
                        }
                        assert(result == advance(f.begin(), insertion_position));
                        assert(result == advance(f.cbegin(), insertion_position));
                        std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to random position/Without reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    std::cout << "\t\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to random position/Without reallocation finished!" << std::endl;
                }

                // with reallocation
                {
                    std::cout << "\t\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to random position/With reallocation!" << std::endl;

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
                        forward_list<std::string> f(count, s);
                        const auto result {f.insert(insertion_position, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == s);
                        auto string_i {0uz};
                        const auto end1 {advance(f.begin(), insertion_position)};
                        for(auto it {f.begin()}; it not_eq end1; ++it) {
                            assert(*it == s);
                        }
                        const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                        for(auto it {end1}; it not_eq end2; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {end2}; it not_eq f.end(); ++it) {
                            assert(*it == s);
                        }
                        const auto cend1 {advance(f.cbegin(), insertion_position)};
                        for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                        for(auto it {cend1}; it not_eq cend2; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {cend2}; it not_eq f.cend(); ++it) {
                            assert(*it == s);
                        }
                        assert(result == advance(f.begin(), insertion_position));
                        assert(result == advance(f.cbegin(), insertion_position));
                        std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to random position/With reallocation/Insertion size less equal to tail size done." << std::endl;
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
                        forward_list<std::string> f(count, s);
                        const auto result {f.insert(insertion_position, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == s);
                        auto string_i {0uz};
                        const auto end1 {advance(f.begin(), insertion_position)};
                        for(auto it {f.begin()}; it not_eq end1; ++it) {
                            assert(*it == s);
                        }
                        const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                        for(auto it {end1}; it not_eq end2; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {end2}; it not_eq f.end(); ++it) {
                            assert(*it == s);
                        }
                        const auto cend1 {advance(f.cbegin(), insertion_position)};
                        for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                        for(auto it {cend1}; it not_eq cend2; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {cend2}; it not_eq f.cend(); ++it) {
                            assert(*it == s);
                        }
                        assert(result == advance(f.begin(), insertion_position));
                        assert(result == advance(f.cbegin(), insertion_position));
                        std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to random position/With reallocation/Insertion size greater than tail size done." << std::endl;
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
                        forward_list<std::string> f(count, s);
                        auto result {f.insert(insertion_position, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == s);
                        auto string_i {0uz};
                        const auto end1 {advance(f.begin(), insertion_position)};
                        for(auto it {f.begin()}; it not_eq end1; ++it) {
                            assert(*it == s);
                        }
                        const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                        for(auto it {end1}; it not_eq end2; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {end2}; it not_eq f.end(); ++it) {
                            assert(*it == s);
                        }
                        const auto cend1 {advance(f.cbegin(), insertion_position)};
                        for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                        for(auto it {cend1}; it not_eq cend2; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {cend2}; it not_eq f.cend(); ++it) {
                            assert(*it == s);
                        }
                        assert(result == advance(f.begin(), insertion_position));
                        assert(result == advance(f.cbegin(), insertion_position));
                        std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to random position/With reallocation/Insertion size less equal to double capacity done." << std::endl;
                    }

                    // insertion size greater than double capacity
                    {
                        auto count {this->generate_count()};
                        while(count <= 2) {
                            count = this->generate_count();
                        }
                        const auto insertion_position {this->generate_a_random_number(1, count - 2)};
                        const auto insertion_size {this->generate_a_random_number(2 * count + 1)};
                        const std::vector<std::string> strings(insertion_size, "init");
                        auto d {this->to_random_access_iterator(strings)};
                        const std::string s {"init"};
                        forward_list<std::string> f(count, s);
                        auto result {f.insert(insertion_position, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == s);
                        auto string_i {0uz};
                        const auto end1 {advance(f.begin(), insertion_position)};
                        for(auto it {f.begin()}; it not_eq end1; ++it) {
                            assert(*it == s);
                        }
                        const auto end2 {advance(f.begin(), insertion_position + insertion_size)};
                        for(auto it {end1}; it not_eq end2; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {end2}; it not_eq f.end(); ++it) {
                            assert(*it == s);
                        }
                        const auto cend1 {advance(f.cbegin(), insertion_position)};
                        for(auto it {f.cbegin()}; it not_eq cend1; ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        const auto cend2 {advance(f.cbegin(), insertion_position + insertion_size)};
                        for(auto it {cend1}; it not_eq cend2; ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        for(auto it {cend2}; it not_eq f.cend(); ++it) {
                            assert(*it == s);
                        }
                        assert(result == advance(f.begin(), insertion_position));
                        assert(result == advance(f.cbegin(), insertion_position));
                        std::cout << "\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to random position/With reallocation/Insertion size greater than double capacity done." << std::endl;
                    }

                    std::cout << "\t\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to random position/With reallocation finished!" << std::endl;
                }

                std::cout << "\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to random position finished!" << std::endl;
            }

            // insert to tail
            {
                std::cout << "\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to tail!" << std::endl;

                // without reallocation
                {
                    std::cout << "\t\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to tail/Without reallocation!" << std::endl;

                    // insertion size is zero
                    {
                        auto count {this->generate_count()};
                        while(count <= 1) {
                            count = this->generate_count();
                        }
                        const auto new_size {this->generate_a_random_number(1, count - 1)};
                        const std::string s {"init"};
                        forward_list<std::string> f(count, s);
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
                        const auto result {f.insert(new_size, std_string_random_access_iterator {}, std_string_random_access_iterator {})};
                        assert(f.size() == new_size);
                        assert(not f.empty());
                        assert(advance(f.begin(), new_size) == f.end());
                        assert(advance(f.cbegin(), new_size) == f.cend());
                        assert(f.front() == s);
                        for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                            assert(*it == s);
                        }
                        for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                            assert(*it == s);
                        }
                        assert(result == f.end());
                        assert(result == f.cend());
                        std::cout << "\t\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to tail/Without reallocation/Insertion size is zero done." << std::endl;
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
                        forward_list<std::string> f(count + static_cast<size_t>(insertion_size) + spare, s);
                        auto erasion {&f.head};
                        for(auto i {count};; erasion = erasion->next) {
                            if(i-- == 0) {
                                auto backup {erasion->next};
                                erasion->next = nullptr;
                                f.node_size.allocator().deallocate(backup->node(), insertion_size + spare);
                                f.node_size() = count;
                                break;
                            }
                        }
                        const auto result {f.insert(count, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == s);
                        auto string_i {0uz};
                        const auto end {advance(f.begin(), count)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == s);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        const auto cend {advance(f.cbegin(), count)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        assert(result == advance(f.begin(), count));
                        assert(result == advance(f.cbegin(), count));
                        std::cout << "\t\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to tail/Without reallocation/Insertion size less equal to tail size done." << std::endl;
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
                        forward_list<std::string> f(count + static_cast<size_t>(insertion_size) + spare, s);
                        auto erasion {&f.head};
                        for(auto i {count};; erasion = erasion->next) {
                            if(i-- == 0) {
                                auto backup {erasion->next};
                                erasion->next = nullptr;
                                f.node_size.allocator().deallocate(backup->node(), static_cast<size_t>(insertion_size) + spare);
                                f.node_size() = count;
                                break;
                            }
                        }
                        const auto result {f.insert(count, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == s);
                        auto string_i {0uz};
                        const auto end {advance(f.begin(), count)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == s);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        const auto cend {advance(f.cbegin(), count)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        assert(result == advance(f.begin(), count));
                        assert(result == advance(f.cbegin(), count));
                        std::cout << "\t\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to tail/Without reallocation/Insertion size greater than tail size done." << std::endl;
                    }

                    std::cout << "\t\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to tail/Without reallocation finished!" << std::endl;
                }

                // with reallocation
                {
                    std::cout << "\t\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to tail/With reallocation!" << std::endl;

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
                        forward_list<std::string> f(count, s);
                        const auto result {f.insert(count, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == s);
                        auto string_i {0uz};
                        const auto end {advance(f.begin(), count)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == s);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        const auto cend {advance(f.cbegin(), count)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        assert(result == advance(f.begin(), count));
                        assert(result == advance(f.cbegin(), count));
                        std::cout << "\t\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to tail/With reallocation/Insertion size less equal to tail size done." << std::endl;
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
                        forward_list<std::string> f(count, s);
                        const auto result {f.insert(count, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == s);
                        auto string_i {0uz};
                        const auto end {advance(f.begin(), count)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == s);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        const auto cend {advance(f.cbegin(), count)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        assert(result == advance(f.begin(), count));
                        assert(result == advance(f.cbegin(), count));
                        std::cout << "\t\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to tail/With reallocation/Insertion size greater than tail size done." << std::endl;
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
                        forward_list<std::string> f(count, s);
                        auto result {f.insert(count, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == s);
                        auto string_i {0uz};
                        const auto end {advance(f.begin(), count)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == s);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        const auto cend {advance(f.cbegin(), count)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        assert(result == advance(f.begin(), count));
                        assert(result == advance(f.cbegin(), count));
                        std::cout << "\t\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to tail/With reallocation/Insertion size less equal to double capacity done." << std::endl;
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
                        forward_list<std::string> f(count, s);
                        auto result {f.insert(count, std_string_random_access_iterator {d.begin()}, std_string_random_access_iterator {d.end()})};
                        assert(f.size() == count + static_cast<size_t>(insertion_size));
                        assert(not f.empty());
                        assert(advance(f.begin(), count + static_cast<size_t>(insertion_size)) == f.end());
                        assert(advance(f.cbegin(), count + static_cast<size_t>(insertion_size)) == f.cend());
                        assert(f.front() == s);
                        auto string_i {0uz};
                        const auto end {advance(f.begin(), count)};
                        for(auto it {f.begin()}; it not_eq end; ++it) {
                            assert(*it == s);
                        }
                        for(auto it {end}; it not_eq f.end(); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        const auto cend {advance(f.cbegin(), count)};
                        for(auto it {f.cbegin()}; it not_eq cend; ++it) {
                            assert(*it == s);
                        }
                        string_i = 0;
                        for(auto it {cend}; it not_eq f.cend(); ++it) {
                            assert(*it == strings[string_i++]);
                        }
                        assert(result == advance(f.begin(), count));
                        assert(result == advance(f.cbegin(), count));
                        std::cout << "\t\t\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to tail/With reallocation/Insertion size greater than double capacity done." << std::endl;
                    }

                    std::cout << "\t\t\t\t\tStart checking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to tail/With reallocation finished!" << std::endl;
                }

                std::cout << "\t\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list/Insert to tail finished!" << std::endl;
            }

            std::cout << "\t\t\tChecking test_non_trivial/iterator insert(size_type, ForwardIterator, ForwardIterator)/Insert to non-empty forward_list finished!" << std::endl;
        }

        std::cout << "\t\tChecking test_insert3/Random access iterator for ds::forward_list finished!" << std::endl;
    }

    // iterator erase(size_type, size_type)
    {
        std::cout << "\tStart checking test_non_trivial/iterator erase(size_type, size_type) for ds::forward_list!" << std::endl;

        // erase from head
        {
            std::cout << "\t\tStart checking test_non_trivial/iterator erase(size_type, size_type)/Erase from head for ds::forward_list!" << std::endl;

            // erasion size is zero
            {
                std::cout << "\t\t\tStart checking test_non_trivial/iterator erase(size_type, size_type)/Erase from head/Erasion size is zero for ds::forward_list!" << std::endl;

                // empty
                {
                    forward_list<std::string> f {};
                    auto result {f.erase(0, 0)};
                    assert(f.size() == 0);
                    assert(f.empty());
                    assert(f.begin() == f.end());
                    assert(f.cbegin() == f.cend());
                    assert(result == f.begin());
                    assert(result == f.cbegin());
                    assert(result == f.end());
                    assert(result == f.cend());
                    std::cout << "\t\t\t\tChecking test_non_trivial/iterator erase(size_type, size_type)/Erase from head/Erasion size is zero/Empty done." << std::endl;
                }

                // non-empty
                {
                    auto count {this->generate_count()};
                    while(count <= 1) {
                        count = this->generate_count();
                    }
                    const std::string s {"init"};
                    forward_list<std::string> f(count, s);
                    auto result {f.erase(0, 0)};
                    assert(f.size() == count);
                    assert(not f.empty());
                    assert(advance(f.begin(), count) == f.end());
                    assert(advance(f.cbegin(), count) == f.cend());
                    assert(f.front() == s);
                    for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                        assert(*it == s);
                    }
                    for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                        assert(*it == s);
                    }
                    assert(result == f.begin());
                    assert(result == f.cbegin());
                    std::cout << "\t\t\t\tChecking test_non_trivial/iterator erase(size_type, size_type)/Erase from head/Erasion size is zero/Non-empty done." << std::endl;
                }

                std::cout << "\t\t\tChecking test_non_trivial/iterator erase(size_type, size_type)/Erase from head/Erasion size is zero for ds::forward_list finished!" << std::endl;
            }

            // erasion size is random
            {
                auto count {this->generate_count()};
                while(count <= 1) {
                    count = this->generate_count();
                }
                const std::string s {"init"};
                forward_list<std::string> f(count, s);
                const auto erasion_size {this->generate_a_random_number(1, count - 1)};
                auto result {f.erase(0, erasion_size)};
                assert(f.size() == count - erasion_size);
                assert(not f.empty());
                assert(advance(f.begin(), count - erasion_size) == f.end());
                assert(advance(f.cbegin(), count - erasion_size) == f.cend());
                assert(f.front() == s);
                for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                    assert(*it == s);
                }
                for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                    assert(*it == s);
                }
                assert(result == f.begin());
                assert(result == f.cbegin());
                std::cout << "\t\t\tChecking test_non_trivial/iterator erase(size_type, size_type)/Erase from head/Erasion size is random done." << std::endl;
            }

            // erase all
            {
                auto count {this->generate_count()};
                while(count <= 1) {
                    count = this->generate_count();
                }
                const std::string s {"init"};
                forward_list<std::string> f(count, s);
                auto result {f.erase(0, count)};
                assert(f.size() == 0);
                assert(f.empty());
                assert(f.begin() == f.end());
                assert(f.cbegin() == f.cend());
                assert(result == f.begin());
                assert(result == f.cbegin());
                assert(result == f.end());
                assert(result == f.cend());
                std::cout << "\t\t\tChecking test_non_trivial/iterator erase(size_type, size_type)/Erase from head/Erasion all done." << std::endl;
            }

            std::cout << "\t\tChecking test_non_trivial/iterator erase(size_type, size_type)/Erase from head for ds::forward_list finished!" << std::endl;
        }

        // erase from any position
        {
            std::cout << "\t\tStart checking test_non_trivial/iterator erase(size_type, size_type)/Erase from any position for ds::forward_list!" << std::endl;

            // erasion size is zero
            {
                auto count {this->generate_count()};
                while(count <= 1) {
                    count = this->generate_count();
                }
                const std::string s {"init"};
                forward_list<std::string> f(count, s);
                const auto erasion_position {this->generate_a_random_number(1, count - 1)};
                auto result {f.erase(erasion_position, 0)};
                assert(f.size() == count);
                assert(not f.empty());
                assert(advance(f.begin(), count) == f.end());
                assert(advance(f.cbegin(), count) == f.cend());
                assert(f.front() == s);
                for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                    assert(*it == s);
                }
                for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                    assert(*it == s);
                }
                assert(result == advance(f.begin(), erasion_position));
                assert(result == advance(f.cbegin(), erasion_position));
                std::cout << "\t\t\t\tChecking test_non_trivial/iterator erase(size_type, size_type)/Erase from head/Erase from any position/Erasion size is zero done." << std::endl;
            }

            // erasion size is not zero
            {
                auto count {this->generate_count()};
                while(count <= 1) {
                    count = this->generate_count();
                }
                const std::string s {"init"};
                forward_list<std::string> f(count, s);
                const auto erasion_position {this->generate_a_random_number(1, count - 1)};
                const auto erasion_size {this->generate_a_random_number(1, count - erasion_position)};
                auto result {f.erase(erasion_position, erasion_size)};
                assert(f.size() == count - erasion_size);
                assert(not f.empty());
                assert(advance(f.begin(), count - erasion_size) == f.end());
                assert(advance(f.cbegin(), count - erasion_size) == f.cend());
                assert(f.front() == s);
                for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                    assert(*it == s);
                }
                for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                    assert(*it == s);
                }
                assert(result == advance(f.begin(), erasion_position));
                assert(result == advance(f.cbegin(), erasion_position));
                std::cout << "\t\t\t\tChecking test_non_trivial/iterator erase(size_type, size_type)/Erase from head/Erase from any position/Erasion size is not zero done." << std::endl;
            }

            // erase to tail
            {
                auto count {this->generate_count()};
                while(count <= 1) {
                    count = this->generate_count();
                }
                const std::string s {"init"};
                forward_list<std::string> f(count, s);
                const auto erasion_position {this->generate_a_random_number(1, count - 1)};
                auto result {f.erase(erasion_position, count - erasion_position)};
                assert(f.size() == erasion_position);
                assert(not f.empty());
                assert(advance(f.begin(), erasion_position) == f.end());
                assert(advance(f.cbegin(), erasion_position) == f.cend());
                assert(f.front() == s);
                for(auto it {f.begin()}; it not_eq f.end(); ++it) {
                    assert(*it == s);
                }
                for(auto it {f.cbegin()}; it not_eq f.cend(); ++it) {
                    assert(*it == s);
                }
                assert(result == advance(f.begin(), erasion_position));
                assert(result == advance(f.cbegin(), erasion_position));
                std::cout << "\t\t\t\tChecking test_non_trivial/iterator erase(size_type, size_type)/Erase from head/Erase from any position/Erase to tail done." << std::endl;
            }

            std::cout << "\t\tChecking test_non_trivial/iterator erase(size_type, size_type)/Erase from any position for ds::forward_list finished!" << std::endl;
        }

        std::cout << "\tChecking test_non_trivial/iterator erase(size_type, size_type) for ds::forward_list finished!" << std::endl;
    }

    std::cout << "Checking non-trivial type for ds::forward_list finished!" << std::endl;
}