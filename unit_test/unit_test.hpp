#ifndef DATA_STRUCTURE_UNIT_TEST_HPP
#define DATA_STRUCTURE_UNIT_TEST_HPP

#include <vector>
#include <random>
#include <cassert>
#include <sstream>
#include <iterator>
#include <forward_list>
#include <list>
#include <deque>
#include "../source/iterator.hpp"

__DATA_STRUCTURE_START(correctness testing base class)
class unit_test_correctness {
public:
    struct int_input_iterator {
        using iterator_category = ds::input_iterator_tag;
        std::istream_iterator<int> it;
        operator std::istream_iterator<int>() const noexcept {
            return this->it;
        }
        bool operator==(const int_input_iterator &rhs) const noexcept {
            return this->it == rhs.it;
        }
        const int &operator*() const noexcept {
            return *this->it;
        }
        int_input_iterator &operator++() noexcept {
            ++this->it;
            return *this;
        }
        int_input_iterator operator++(int) noexcept {
            auto tmp {*this};
            ++*this;
            return tmp;
        }
    };
    struct std_string_input_iterator {
        using iterator_category = ds::input_iterator_tag;
        std::istream_iterator<std::string> it;
        operator std::istream_iterator<std::string>() const noexcept {
            return this->it;
        }
        bool operator==(const std_string_input_iterator &rhs) const noexcept {
            return this->it == rhs.it;
        }
        const std::string &operator*() const noexcept {
            return *this->it;
        }
        std_string_input_iterator &operator++() noexcept {
            ++this->it;
            return *this;
        }
        std_string_input_iterator operator++(int) noexcept {
            auto tmp {*this};
            ++*this;
            return tmp;
        }
    };
    struct int_forward_iterator {
        using difference_type = typename std::forward_list<int>::iterator::difference_type;
        using size_type = size_t;
        using value_type = int;
        using iterator_category = ds::forward_iterator_tag;
        typename std::forward_list<int>::iterator it;
        operator std::forward_list<int>::iterator() const noexcept {
            return this->it;
        }
        bool operator==(const int_forward_iterator &rhs) const noexcept {
            return this->it == rhs.it;
        }
        const int &operator*() const noexcept {
            return *this->it;
        }
        int_forward_iterator &operator++() noexcept {
            ++this->it;
            return *this;
        }
        int_forward_iterator operator++(int) noexcept {
            auto tmp {*this};
            ++*this;
            return tmp;
        }
    };
    struct int_bidirectional_iterator {
        using difference_type = typename std::list<int>::iterator::difference_type;
        using size_type = size_t;
        using value_type = int;
        using iterator_category = ds::bidirectional_iterator_tag;
        typename std::list<int>::iterator it;
        operator std::list<int>::iterator() const noexcept {
            return this->it;
        }
        bool operator==(const int_bidirectional_iterator &rhs) const noexcept {
            return this->it == rhs.it;
        }
        const int &operator*() const noexcept {
            return *this->it;
        }
        int_bidirectional_iterator &operator++() noexcept {
            ++this->it;
            return *this;
        }
        int_bidirectional_iterator operator++(int) noexcept {
            auto tmp {*this};
            ++*this;
            return tmp;
        }
    };
    struct int_random_access_iterator {
        using difference_type = typename std::deque<int>::iterator::difference_type;
        using size_type = size_t;
        using value_type = int;
        using iterator_category = ds::random_access_iterator_tag;
        typename std::deque<int>::iterator it;
        operator std::deque<int>::iterator() const noexcept {
            return this->it;
        }
        bool operator==(const int_random_access_iterator &rhs) const noexcept {
            return this->it == rhs.it;
        }
        const int &operator*() const noexcept {
            return *this->it;
        }
        int_random_access_iterator &operator++() noexcept {
            ++this->it;
            return *this;
        }
        int_random_access_iterator operator++(int) noexcept {
            auto tmp {*this};
            ++*this;
            return tmp;
        }
        difference_type operator-(const int_random_access_iterator &rhs) const noexcept {
            return this->it - rhs.it;
        }
    };
    struct std_string_random_access_iterator {
        using difference_type = typename std::deque<std::string>::iterator::difference_type;
        using size_type = size_t;
        using value_type = int;
        using iterator_category = ds::random_access_iterator_tag;
        typename std::deque<std::string>::iterator it;
        operator std::deque<std::string>::iterator() const noexcept {
            return this->it;
        }
        bool operator==(const std_string_random_access_iterator &rhs) const noexcept {
            return this->it == rhs.it;
        }
        const std::string &operator*() const noexcept {
            return *this->it;
        }
        std_string_random_access_iterator &operator++() noexcept {
            ++this->it;
            return *this;
        }
        std_string_random_access_iterator operator++(int) noexcept {
            auto tmp {*this};
            ++*this;
            return tmp;
        }
        difference_type operator-(const std_string_random_access_iterator &rhs) const noexcept {
            return this->it - rhs.it;
        }
    };
protected:
    virtual int generate_count();
    virtual int generate_count(int max);
    virtual int generate_a_random_number(int min = std::numeric_limits<int>::min(),
            int max = std::numeric_limits<int>::max());
    virtual std::vector<int> generate_random_sequence();
    virtual std::vector<int> generate_random_sequence(int count);
    virtual std::vector<int> generate_random_sequence(int min, int max);
    virtual std::vector<int> generate_random_sequence(int min, int max, int count);
    virtual std::vector<int> generate_zero();
    virtual std::vector<int> generate_zero(int count);
    virtual std::vector<int> generate_max_number();
    virtual std::vector<int> generate_max_number(int count);
    virtual std::vector<int> generate_min_number();
    virtual std::vector<int> generate_min_number(int count);
    virtual std::vector<int> generate_number(int number);
    virtual std::vector<int> generate_number(int number, int count);
    virtual std::vector<int> generate_ascending_sequence();
    virtual std::vector<int> generate_ascending_sequence(int count);
    virtual std::vector<int> generate_descending_sequence();
    virtual std::vector<int> generate_descending_sequence(int count);
    virtual std::vector<int> generate_positive_sequence();
    virtual std::vector<int> generate_positive_sequence(int count);
    virtual std::vector<int> generate_negative_sequence();
    virtual std::vector<int> generate_negative_sequence(int count);
    virtual std::stringstream to_input_iterator(const std::vector<int> &);
    virtual std::stringstream to_input_iterator(const std::vector<std::string> &);
    virtual std::forward_list<int> to_forward_iterator(const std::vector<int> &);
    virtual std::list<int> to_bidirectional_iterator(const std::vector<int> &);
    virtual std::deque<int> to_random_access_iterator(const std::vector<int> &);
    virtual std::deque<std::string> to_random_access_iterator(const std::vector<std::string> &);
public:
    virtual ~unit_test_correctness() noexcept = default;
};
__DATA_STRUCTURE_END(correctness testing base class)

__DATA_STRUCTURE_START(type testing base class)
class unit_test_type;
__DATA_STRUCTURE_END(type testing base class)

__DATA_STRUCTURE_START(exception testing base class)
class unit_test_exception;
__DATA_STRUCTURE_END(exception testing base class)

__DATA_STRUCTURE_START(memory testing base class)
class unit_test_memory;
__DATA_STRUCTURE_END(memory testing base class)

__DATA_STRUCTURE_START(stability testing base class)
class unit_test_stability;
__DATA_STRUCTURE_END(stability testing base class)

__DATA_STRUCTURE_START(thread testing base class)
class unit_test_thread;
__DATA_STRUCTURE_END(thread testing base class)

__DATA_STRUCTURE_START(data delivery testing base class)
class unit_test_data_delivery;
__DATA_STRUCTURE_END(data delivery testing base class)

__DATA_STRUCTURE_START(network testing base class)
class unit_test_network;
__DATA_STRUCTURE_END(network testing base class)

__DATA_STRUCTURE_START(improve unit test coverage)
class unit_test_coverage_improvement;
__DATA_STRUCTURE_END(improve unit test coverage)

#endif      //DATA_STRUCTURE_UNIT_TEST_HPP