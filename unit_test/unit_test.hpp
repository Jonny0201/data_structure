#ifndef DATA_STRUCTURE_UNIT_TEST_HPP
#define DATA_STRUCTURE_UNIT_TEST_HPP

#include <vector>
#include <random>
#include "../source/__config.hpp"

__DATA_STRUCTURE_START(correctness testing base class)
class unit_test_correctness {
protected:
    virtual int generate_count();
    virtual std::vector<int> generate_random_sequence() = 0;
    virtual std::vector<int> generate_random_sequence(int count) = 0;
    virtual std::vector<int> generate_random_sequence(int min, int max) = 0;
    virtual std::vector<int> generate_random_sequence(int min, int max, int count) = 0;
    virtual std::vector<int> generate_zero() = 0;
    virtual std::vector<int> generate_zero(int count) = 0;
    virtual std::vector<int> generate_max_number() = 0;
    virtual std::vector<int> generate_max_number(int count) = 0;
    virtual std::vector<int> generate_min_number() = 0;
    virtual std::vector<int> generate_min_number(int count) = 0;
    virtual std::vector<int> generate_number(int number) = 0;
    virtual std::vector<int> generate_number(int number, int count) = 0;
    virtual std::vector<int> generate_ascending_sequence() = 0;
    virtual std::vector<int> generate_ascending_sequence(int count) = 0;
    virtual std::vector<int> generate_descending_sequence() = 0;
    virtual std::vector<int> generate_descending_sequence(int count) = 0;
    virtual std::vector<int> generate_positive_sequence() = 0;
    virtual std::vector<int> generate_positive_sequence(int count) = 0;
    virtual std::vector<int> generate_negative_sequence() = 0;
    virtual std::vector<int> generate_negative_sequence(int count) = 0;
public:
    virtual ~unit_test_correctness() noexcept = 0;
};
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(type testing base class)
class unit_test_type;
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(exception testing base class)
class unit_test_exception;
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(memory testing base class)
class unit_test_memory;
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(thread testing base class)
class unit_test_thread;
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(data delivery testing base class)
class unit_test_data_delivery;
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(network testing base class)
class unit_test_network;
__DATA_STRUCTURE_END

#endif      //DATA_STRUCTURE_UNIT_TEST_HPP