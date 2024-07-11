#include <iostream>
#include "unit_test.hpp"
#include "../source/forward_list.hpp"

using namespace ds;
class forward_list_unit_test : public unit_test_correctness {
public:
    ~forward_list_unit_test() noexcept override = default;
public:
    void test_default_constructor();
};

void forward_list_unit_test::test_default_constructor() {
    std::cout << "Start checking default constructor for ds::forward_list!" << std::endl;

    // the members which should be nothrow
    {
        forward_list<int> l {};
        const forward_list<int> cl {};
        static_assert(noexcept(forward_list<int, std::allocator<int>> {}));
        static_assert(noexcept(forward_list<int> {move(l)}));
        static_assert(noexcept(l = move(l)));
        static_assert(noexcept(l.begin()));
        static_assert(noexcept(cl.begin()));
        static_assert(noexcept(l.end()));
        static_assert(noexcept(cl.end()));
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