/*
    * Copyright © [2019 - 2024] [Jonny]
    *
    * Licensed under the Apache License, Version 2.0 (the "License");
    * you may not use this file except in compliance with the License.
    * You may obtain a copy of the License at
    *
    *     http://www.apache.org/licenses/LICENSE-2.0
    *
    * Unless required by applicable law or agreed to in writing, software
    * distributed under the License is distributed on an "AS IS" BASIS,
    * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    * See the License for the specific language governing permissions and
    * limitations under the License.
*/

#ifndef DATA_STRUCTURE_HASH_TABLE_HPP
#define DATA_STRUCTURE_HASH_TABLE_HPP

#include "allocator.hpp"

namespace data_structure {

__DATA_STRUCTURE_START(hash table declaration)
template <typename T, typename Hash, typename Allocator = allocator<T>>
class hash_table {
public:
    using allocator_type = Allocator;
    using size_type = typename Allocator::size_type;
    using difference_type = typename Allocator::difference_type;
    using hasher = Hash;
    using value_type = T;
    using reference = typename allocator_traits<Allocator>::reference;
    using const_reference = typename allocator_traits<Allocator>::const_reference;
    using rvalue_reference = typename allocator_traits<Allocator>::rvalue_reference;
    using pointer = typename allocator_traits<Allocator>::pointer;
    using const_pointer = typename allocator_traits<Allocator>::const_pointer;
    using iterator = __dsa::hash_table_iterator<T, true>;
    using const_iterator = __dsa::hash_table_iterator<T, true>;
    using local_iterator = __dsa::hash_table_local_iterator<T, true>;
    using const_local_iterator = __dsa::hash_table_local_iterator<T, true>;
    static_assert(is_same_v<T, typename Allocator::value_type>,
            "The value type of hash_table should be same as the allocator's value_type!");
private:
    using node_allocator = typename allocator_traits<Allocator>::template rebind<__dsa::hash_table_node<T>>;
    using bucket_allocator = typename allocator_traits<Allocator>::template rebind<__dsa::hash_table_node<T> *>;
private:
    __dsa::partial_compressor<__dsa::hash_table_node<T> **, Hash> buckets {};
    __dsa::allocator_compressor<size_type, bucket_allocator> bucket_size {};
    __dsa::allocator_compressor<size_type, node_allocator> node_size {};
    float loading_factor {1.2f};
private:
    static constexpr bool is_hash_power_2(size_t) noexcept;
    static constexpr size_t next_hash_power_2(size_t) noexcept;
    static constexpr size_t constrain_hash(size_t) noexcept;
    constexpr __dsa::hash_table_node<T> **allocate_bucket(size_type);
    template <typename ...Args>
    constexpr __dsa::hash_table_node<T> *allocate_node(Args &&...);
    constexpr void insert_a_node(__dsa::hash_table_node<T> *node)
            noexcept(is_nothrow_invocable_r_v<bool, Hash, const_reference>);
public:
    constexpr hash_table() = default;
    explicit constexpr hash_table(const Hash &) noexcept(
            is_nothrow_copy_constructible_v<Hash> and is_nothrow_default_constructible_v<node_allocator> and
            is_nothrow_default_constructible_v<bucket_allocator>);
    explicit constexpr hash_table(const Allocator &) noexcept(
            is_nothrow_default_constructible_v<Hash> and is_nothrow_default_constructible_v<node_allocator> and
            is_nothrow_default_constructible_v<bucket_allocator>);
    constexpr hash_table(const Hash &, const Allocator &) noexcept(
            is_nothrow_default_constructible_v<Hash> and is_nothrow_default_constructible_v<node_allocator> and
            is_nothrow_default_constructible_v<bucket_allocator>);
    explicit constexpr hash_table(size_type, const Hash & = {}, const Allocator & = {});
    template <IsInputIterator InputIterator>
    constexpr hash_table(InputIterator, InputIterator, const Hash & = {}, const Allocator & = {});
    constexpr hash_table(initializer_list<T>, const Hash & = {}, const Allocator & = {});
    constexpr hash_table(const hash_table &);
    constexpr hash_table(hash_table &&) noexcept;
    constexpr hash_table(const hash_table &, const Hash &, const Allocator & = {});
    constexpr hash_table(hash_table &&, const Hash &, const Allocator & = {}) noexcept;
    constexpr ~hash_table() noexcept;
public:
    constexpr hash_table &operator=(const hash_table &);
    constexpr hash_table &operator=(hash_table &&) noexcept;
    constexpr hash_table &operator=(initializer_list<T>);
public:
    template <IsInputIterator InputIterator>
    constexpr void assign(InputIterator, InputIterator);
    constexpr void assign(initializer_list<T>);
    [[nodiscard]]
    constexpr const_iterator begin() noexcept;
    [[nodiscard]]
    constexpr const_iterator begin() const noexcept;
    [[nodiscard]]
    constexpr const_iterator cbegin() const noexcept;
    [[nodiscard]]
    constexpr const_iterator end() noexcept;
    [[nodiscard]]
    constexpr const_iterator end() const noexcept;
    [[nodiscard]]
    constexpr const_iterator cend() const noexcept;
    [[nodiscard]]
    constexpr const_local_iterator begin(size_type) noexcept;
    [[nodiscard]]
    constexpr const_local_iterator begin(size_type) const noexcept;
    [[nodiscard]]
    constexpr const_local_iterator cbegin(size_type) const noexcept;
    [[nodiscard]]
    constexpr const_local_iterator end(size_type) noexcept;
    [[nodiscard]]
    constexpr const_local_iterator end(size_type) const noexcept;
    [[nodiscard]]
    constexpr const_local_iterator cend(size_type) const noexcept;
    [[nodiscard]]
    constexpr size_type size() const noexcept;
    [[nodiscard]]
    constexpr size_type bucket_count() const noexcept;
    [[nodiscard]]
    constexpr float &load_factor() noexcept;
    [[nodiscard]]
    constexpr float load_factor() const noexcept;
    [[nodiscard]]
    constexpr Hash hash_function() const noexcept(is_nothrow_copy_constructible_v<Hash>);
    [[nodiscard]]
    constexpr Allocator allocator() const noexcept(is_nothrow_copy_constructible_v<Allocator>);
    [[nodiscard]]
    constexpr bool empty() const noexcept;
    constexpr void reserve(size_type);
    constexpr void rehash(size_type);
    constexpr void clear() noexcept;
    void swap(hash_table &) noexcept;
    const_iterator insert(const_reference);
    const_iterator insert(rvalue_reference);
    template <typename ...Args>
    const_iterator emplace(Args &&...);
    template <IsInputIterator InputIterator>
    void insert(InputIterator, InputIterator);
    void insert(initializer_list<T>);
    const_iterator erase(const_iterator) noexcept;
    const_iterator erase(const_iterator, const_iterator) noexcept;
public:
    const_iterator remove(const_reference) noexcept(is_nothrow_equal_to_comparable_v<const_reference>);
    template <typename UnaryPredicate>
    const_iterator remove_if(UnaryPredicate) noexcept(is_nothrow_invocable_r_v<bool, UnaryPredicate, const_reference>);
    void unique()  noexcept(is_nothrow_equal_to_comparable_v<const_reference>);
    template <typename UnaryPredicate>
    void unique_if(UnaryPredicate) noexcept(is_nothrow_invocable_r_v<bool, UnaryPredicate, const_reference>);
    [[nodiscard]]
    const_iterator find(const_reference) noexcept(is_nothrow_equal_to_comparable_v<const_reference>);
    template <typename UnaryPredicate>
    [[nodiscard]]
    const_iterator find_if(UnaryPredicate) noexcept(is_nothrow_invocable_r_v<bool, UnaryPredicate, const_reference>);
    [[nodiscard]]
    bool contains(const_reference) noexcept(is_nothrow_equal_to_comparable_v<const_reference>);
    template <typename UnaryPredicate>
    [[nodiscard]]
    bool contains_if(UnaryPredicate) noexcept(is_nothrow_invocable_r_v<bool, UnaryPredicate, const_reference>);
    [[nodiscard]]
    size_type count(const_reference) const noexcept(is_nothrow_equal_to_comparable_v<const_reference>);
    template <typename UnaryPredicate>
    [[nodiscard]]
    size_type count_if(UnaryPredicate) noexcept(is_nothrow_invocable_r_v<bool, UnaryPredicate, const_reference>);
    void merge(hash_table &) noexcept(is_nothrow_invocable_r_v<size_t, Hash, const_reference>);
    void merge(hash_table &&) noexcept(is_nothrow_invocable_r_v<size_t, Hash, const_reference>);
};
__DATA_STRUCTURE_END(hash table declaration)

}       // namespace data_structure

#endif      // DATA_STRUCTURE_HASH_TABLE_HPP
