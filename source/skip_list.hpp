//
// Created by Jonny on 2024/10/27.
//

#ifndef DATA_STRUCTURE_SKIP_LIST_HPP
#define DATA_STRUCTURE_SKIP_LIST_HPP

#include "allocator.hpp"

namespace data_structure {

// Todo : make default random engine and all member functions constexpr
__DATA_STRUCTURE_START(skip list declaration)
template <typename T, typename Compare = std::less<T>, typename RandomEngine = __dsa::skip_list_default_random_engine,
        typename Probability = __dsa::skip_list_default_probability, typename Allocator = allocator<T>>
class skip_list {
public:
    using allocator_type = Allocator;
    using size_type = typename Allocator::size_type;
    using difference_type = typename Allocator::difference_type;
    using comparison_type = Compare;
    using random_engine_type = RandomEngine;
    using probability_type = Probability;
    using value_type = T;
    using reference = typename allocator_traits<Allocator>::reference;
    using const_reference = typename allocator_traits<Allocator>::const_reference;
    using rvalue_reference = typename allocator_traits<Allocator>::rvalue_reference;
    using pointer = typename allocator_traits<Allocator>::pointer;
    using const_pointer = typename allocator_traits<Allocator>::const_pointer;
    using iterator = __dsa::skip_list_iterator<T, true>;
    using const_iterator = __dsa::skip_list_iterator<T, true>;
    static_assert(is_same_v<T, typename Allocator::value_type>,
            "The value type of skip_list should be same as the allocator's value_type!");
private:
    __dsa::compressor<__dsa::skip_list_base_node<__dsa::skip_list_node<T>>,
            __dsa::compressor<Compare, __dsa::compressor<RandomEngine, Probability>>> head;
    __dsa::allocator_compressor<size_type, typename allocator_traits<Allocator>::template rebind<
            __dsa::skip_list_node<T>>> node_size;
private:
    __dsa::skip_list_node<T> *allocate() const;
    size_t level() const noexcept;
public:
    skip_list() = default;
    explicit skip_list(const Compare &);
    explicit skip_list(const RandomEngine &);
    explicit skip_list(const Probability &);
    explicit skip_list(const Allocator &);
    skip_list(const Compare &, const RandomEngine &, const Probability &, const Allocator &);
    explicit skip_list(size_type, const Compare & = {}, const RandomEngine & = {},
            const Probability & = {}, const Allocator & = {});
    skip_list(size_type, const_reference, const Compare & = {}, const RandomEngine & = {},
            const Probability & = {}, const Allocator & = {});
    template <IsInputIterator InputIterator>
    skip_list(InputIterator, InputIterator, const Compare & = {}, const RandomEngine & = {},
            const Probability & = {}, const Allocator & = {});
    skip_list(initializer_list<T>, const Compare & = {}, const RandomEngine & = {},
            const Probability & = {}, const Allocator & = {});
    skip_list(const skip_list &);
    skip_list(skip_list &&) noexcept;
    ~skip_list() noexcept;
public:
    skip_list &operator=(const skip_list &);
    skip_list &operator=(const skip_list &&) noexcept;
public:
    void assign(size_type, const_reference = {});
    template <IsInputIterator InputIterator>
    void assign(InputIterator, InputIterator);
    void assign(initializer_list<T>);
    [[nodiscard]]
    const_iterator before_begin() const noexcept;
    [[nodiscard]]
    const_iterator cbefore_begin() const noexcept;
    [[nodiscard]]
    const_iterator begin() const noexcept;
    [[nodiscard]]
    const_iterator cbegin() const noexcept;
    [[nodiscard]]
    constexpr const_iterator end() const noexcept;
    [[nodiscard]]
    constexpr const_iterator cend() const noexcept;
    [[nodiscard]]
    const_iterator level_before_begin(size_t) const noexcept;
    [[nodiscard]]
    const_iterator level_cbefore_begin(size_t) const noexcept;
    [[nodiscard]]
    bool empty() const noexcept;
    [[nodiscard]]
    size_type size() const noexcept;
    [[nodiscard]]
    size_t max_level() const noexcept;
    [[nodiscard]]
    const_reference front() const noexcept;
    [[nodiscard]]
    Compare compare() const noexcept;
    [[nodiscard]]
    RandomEngine random_engine() const noexcept;
    [[nodiscard]]
    Probability probability() const noexcept;
    [[nodiscard]]
    constexpr Allocator allocator() const noexcept;
    void clear() noexcept;
    void swap(skip_list &) noexcept;
    void pop_front() noexcept;
    const_iterator insert(size_type, const_reference = {});
    const_iterator insert(rvalue_reference);
    template <typename ...Args>
    const_iterator emplace(Args &&...);
    template <IsInputIterator InputIterator>
    const_iterator insert(InputIterator, InputIterator);
    const_iterator insert(initializer_list<T>);
    const_iterator erase(difference_type, size_type = 1) noexcept;
    const_iterator erase(const_iterator, size_type = 1) noexcept;
    const_iterator erase(const_iterator) noexcept;
    const_iterator erase(const_iterator, const_iterator) noexcept;
public:
    size_type remove(const_reference) noexcept;
    template <typename UnaryPredicate>
    size_type remove_if(UnaryPredicate) noexcept(is_nothrow_invocable_r_v<bool, UnaryPredicate, reference>);
    void unique() noexcept;
    template <typename UnaryPredicate>
    void unique_if(UnaryPredicate) noexcept(is_nothrow_invocable_r_v<bool, UnaryPredicate, reference>);
    [[nodiscard]]
    const_iterator find(const_reference) const noexcept;
    template <typename UnaryPredicate>
    [[nodiscard]]
    const_iterator find_if(UnaryPredicate) const
            noexcept(is_nothrow_invocable_r_v<bool, UnaryPredicate, const_reference>);
    [[nodiscard]]
    const_iterator find_first_of(const_reference) const noexcept;
    template <typename UnaryPredicate>
    [[nodiscard]]
    const_iterator find_first_of_if(UnaryPredicate) const
            noexcept(is_nothrow_invocable_r_v<bool, UnaryPredicate, const_reference>);
    [[nodiscard]]
    const_iterator find_last_of(const_reference) const noexcept;
    template <typename UnaryPredicate>
    [[nodiscard]]
    const_iterator find_last_of_if(UnaryPredicate) const
            noexcept(is_nothrow_invocable_r_v<bool, UnaryPredicate, const_reference>);
    [[nodiscard]]
    bool contains(const_reference) const noexcept;
    template <typename UnaryPredicate>
    [[nodiscard]]
    bool contains_if(UnaryPredicate) const noexcept(is_nothrow_invocable_r_v<bool, UnaryPredicate, const_reference>);
    [[nodiscard]]
    bool contains_range(const_reference, const_reference) const noexcept;
    [[nodiscard]]
    size_type count(const_reference) const noexcept;
    template <typename UnaryPredicate>
    [[nodiscard]]
    size_type count_if(UnaryPredicate) const noexcept(is_nothrow_invocable_r_v<bool, UnaryPredicate, const_reference>);
    void merge(skip_list &);
    void merge(skip_list &&);
    void splice(const_iterator, skip_list &);
    void splice(difference_type, skip_list &);
};
__DATA_STRUCTURE_END(skip list declaration)

}       // namespace data_structure

#endif      // DATA_STRUCTURE_SKIP_LIST_HPP
