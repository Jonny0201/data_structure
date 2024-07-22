#include <random>
#include <sstream>
#include <iterator>
#include "unit_test.hpp"

__DATA_STRUCTURE_START(correctness testing base class implementation)
int unit_test_correctness::generate_count() {
    return this->generate_count(std::numeric_limits<int>::max());
}
int unit_test_correctness::generate_count(int max) {
    max = 10;
    std::uniform_int_distribution u(0, max);
    std::random_device d {};
    std::default_random_engine e(d());
    return u(e);
}
int unit_test_correctness::generate_a_random_number(int min, int max) {
    std::uniform_int_distribution u(min, max);
    std::random_device d {};
    std::default_random_engine e(d());
    return u(e);
}
std::vector<int> unit_test_correctness::generate_random_sequence() {
    return this->generate_random_sequence(std::numeric_limits<int>::min(),
            std::numeric_limits<int>::max(), this->generate_count());
}
std::vector<int> unit_test_correctness::generate_random_sequence(int count) {
    return this->generate_random_sequence(std::numeric_limits<int>::min(),
            std::numeric_limits<int>::max(), count);
}
std::vector<int> unit_test_correctness::generate_random_sequence(int min, int max) {
    std::uniform_int_distribution u(0, std::numeric_limits<int>::max());
    std::random_device d {};
    std::default_random_engine e(d());
    return this->generate_random_sequence(std::numeric_limits<int>::min(),
            std::numeric_limits<int>::max(), this->generate_count());
}
std::vector<int> unit_test_correctness::generate_random_sequence(int min, int max, int count) {
    std::uniform_int_distribution u(min, max);
    std::random_device d {};
    std::default_random_engine e(d());
    std::vector<int> result(count);
    for(auto i {0}; i < count; ++i) {
        result[i] = u(e);
    }
    return result;
}
std::vector<int> unit_test_correctness::generate_zero() {
    return this->generate_zero(this->generate_count());
}
std::vector<int> unit_test_correctness::generate_zero(int count) {
    return std::vector<int>(count);
}
std::vector<int> unit_test_correctness::generate_max_number() {
    return this->generate_max_number(this->generate_count());
}
std::vector<int> unit_test_correctness::generate_max_number(int count) {
    return std::vector<int>(count, std::numeric_limits<int>::max());
}
std::vector<int> unit_test_correctness::generate_min_number() {
    return this->generate_min_number(this->generate_count());
}
std::vector<int> unit_test_correctness::generate_min_number(int count) {
    return std::vector<int>(count, std::numeric_limits<int>::min());
}
std::vector<int> unit_test_correctness::generate_number(int number) {
    return this->generate_number(number, this->generate_count());
}
std::vector<int> unit_test_correctness::generate_number(int number, int count) {
    return std::vector<int>(number, this->generate_count());
}
std::vector<int> unit_test_correctness::generate_ascending_sequence() {
    return this->generate_ascending_sequence(this->generate_count());
}
std::vector<int> unit_test_correctness::generate_ascending_sequence(int count) {
    auto result {this->generate_random_sequence(count)};
    std::sort(result.begin(), result.end());
    return result;
}
std::vector<int> unit_test_correctness::generate_descending_sequence() {
    return this->generate_descending_sequence(this->generate_count());
}
std::vector<int> unit_test_correctness::generate_descending_sequence(int count) {
    auto result {this->generate_random_sequence(count)};
    std::sort(result.begin(), result.end(), std::greater {});
    return result;
}
std::vector<int> unit_test_correctness::generate_positive_sequence() {
    return this->generate_ascending_sequence(this->generate_count());
}
std::vector<int> unit_test_correctness::generate_positive_sequence(int count) {
    return this->generate_random_sequence(0, std::numeric_limits<int>::max(), count);
}
std::vector<int> unit_test_correctness::generate_negative_sequence() {
    return this->generate_negative_sequence(this->generate_count());
}
std::vector<int> unit_test_correctness::generate_negative_sequence(int count) {
    return this->generate_random_sequence(std::numeric_limits<int>::min(), 0, count);
}
std::stringstream unit_test_correctness::to_input_iterator(const std::vector<int> &source) {
    std::stringstream result {};
    for(auto i {0}; i < source.size(); ++i) {
        result << std::to_string(source[i]) + ' ';
    }
    return std::move(result);
}
std::stringstream unit_test_correctness::to_input_iterator(const std::vector<std::string> &source) {
    std::stringstream result {};
    for(const auto &element : source) {
        if(element.find(' ') == std::string::npos) {
            result << element << ' ';
        }
    }
    return std::move(result);
}
std::forward_list<int> unit_test_correctness::to_forward_iterator(const std::vector<int> &source) {
    return {source.cbegin(), source.cend()};
}
std::list<int> unit_test_correctness::to_bidirectional_iterator(const std::vector<int> &source) {
    return {source.cbegin(), source.cend()};
}
std::deque<int> unit_test_correctness::to_random_access_iterator(const std::vector<int> &source) {
    return {source.cbegin(), source.cend()};
}
std::deque<std::string> unit_test_correctness::to_random_access_iterator(const std::vector<std::string> &source) {
    std::deque<std::string> result {};
    for(const auto &element : source) {
        if(element.find(' ') == std::string::npos) {
            result.emplace_back(element);
        }
    }
    return result;
}
__DATA_STRUCTURE_END(correctness testing base class implementation)