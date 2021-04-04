/*
    * Copyright © [2019 - 2021] [Jonny Charlotte]
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

#include "hash.hpp"
#include "iterator.hpp"
#include "allocator.hpp"

namespace data_structure::__data_structure_auxiliary {
    template <typename Hash, bool>
    struct hash_table_compress_auxiliary {
    public:
        Hash h;
    public:
        constexpr hash_table_compress_auxiliary() = default;
        explicit hash_table_compress_auxiliary(Hash h) : h {ds::move(h)} {}
    public:
        Hash &hash() noexcept {
            return this->h;
        }
        const Hash &hash() const noexcept {
            return this->h;
        }
    };
    template <typename Hash>
    struct hash_table_compress_auxiliary<Hash, true> : public Hash {
    public:
        constexpr hash_table_compress_auxiliary() = default;
        explicit hash_table_compress_auxiliary(Hash) : Hash() {}
    public:
        Hash &hash() noexcept {
            return static_cast<Hash &>(*this);
        }
        const Hash &hash() const noexcept {
            return static_cast<const Hash &>(*this);
        }
    };
    template <typename Hash>
    using hash_table_compress = hash_table_compress_auxiliary<Hash, is_empty_v<Compare> and not is_final_v<Compare>>;
    template <typename BucketType, typename Hash>
    struct hash_table_compress_with_bucket_type : hash_table_compress<Hash> {
    public:
        BucketType b;
    public:
        constexpr hash_table_compress_with_node_type() = default;
        explicit hash_table_compress_with_node_type(NodeType b) : hash_table_compress<Hash>(), b {ds::move(b)} {}
        hash_table_compress_with_node_type(NodeType b, Hash h) : hash_table_compress<Hash>(h), b {ds::move(b)} {}
    public:
        BucketType &bucket() noexcept {
            return this->b;
        }
        const BucketType &bucket() const noexcept {
            return this->b;
        }
    };
}

namespace data_structure {
    template <typename T, typename Hash = hash<T>, typename Allocator = allocator<ds::type_holder<T>>>
    class hash_table final {
    public:
        using allocator_type = Allocator;
        using hasher = Hash;
        using size_type = allocator_traits_t(allocator_type, size_type);
        using difference_type = allocator_traits_t(allocator_type, difference_type);
        using value_type = T;
        using reference = allocator_traits_t(allocator_type, reference);
        using const_reference = allocator_traits_t(allocator_type, const_reference);
        using rvalue_reference = allocator_traits_t(allocator_type, rvalue_reference);
        using pointer = allocator_traits_t(allocator_type, pointer);
        using const_pointer = allocator_traits_t(allocator_type, const_pointer);
        using iterator = __dsa::hash_table_iterator<value_type, false>;
        using const_iterator = __dsa::hash_table_iterator<value_type, true>;
    private:
        using node_value_type = __dsa::hash_table_node<value_type>;
        using node_type = node_value_type *;
        using bucket_type = node_type *;
        using alloc_traits = allocator_traits<allocator_type>;
        static_assert(is_same_v<value_type, typename alloc_traits::value_type>,
                "The Allocator::value_type must be the same as template argument BucketType!");
    private:
        __dsa::hash_table_compress_with_bucket_type<bucket_type, hasher> bucket;
        size_type bucket_count;
    private:
        static size_t next_prime(size_t) noexcept;
        static bool is_hash_power_2(size_type) noexcept;
        static size_t constrain_hash(size_t, size_type) noexcept;
        static size_t next_hash_power_2(size_t) noexcept;
    public:
        constexpr hash_table() noexcept(is_nothrow_default_constructible_v<hasher>) = default;
        explicit hash_table(hasher) noexcept(is_nothrow_copy_constructible_v<hasher>);
        explicit hash_table(size_type);
        hash_table(size_type, const_reference);
        template <typename InputIterator>
        hash_table(enable_if_t<is_input_iterator_v<InputIterator>, InputIterator>, InputIterator);
        hash_table(initializer_list);
        hash_table(const hash_table &);
        hash_table(hash_table &&) noexcept;
        template <typename AllocatorRHS>
        explicit hash_table(const hash_table<value_type, hasher, AllocatorRHS> &);
        template <typename AllocatorRHS>
        hash_table(hash_table<value_type, hasher, AllocatorRHS> &&) noexcept;
        ~hash_table() noexcept;
    public:
        hash_table &operator=(const hash_table &);
        hash_table &operator=(hash_table &&) noexcept;
        template <typename AllocatorRHS>
        hash_table &operator=(const hash_table<value_type, AllocatorRHS> &);
        template <typename AllocatorRHS>
        hash_table &operator=(hash_table<value_type, AllocatorRHS> &&) noexcept;
        hash_table &operator=(hasher) noexcept(is_nothrow_move_assignable_v<hasher>);
    public:
        [[nodiscard]]
        iterator begin() noexcept;
        [[nodiscard]]
        const_iterator begin() const noexcept;
        [[nodiscard]]
        iterator end() noexcept;
        [[nodiscard]]
        const_iterator end() const noexcept;
        [[nodiscard]]
        const_iterator cbegin() const noexcept;
        [[nodiscard]]
        const_iterator cend() const noexcept;
        [[nodiscard]]
        size_type size() const noexcept;
        [[nodiscard]]
        size_type bucket_count() const noexcept;
        [[nodiscard]]
        constexpr size_type max_bucket_count() const noexcept;
        [[nodiscard]]
        size_type bucket_size(size_type) const noexcept;
        [[nodiscard]]
        bool empty() const noexcept;
        [[nodiscard]]
        constexpr size_type max_size() const noexcept;
        [[nodiscard]]
        float load_factor() const noexcept;
        [[nodiscard]]
        constexpr float max_load_factor() const noexcept;
        void reserve(size_type);
        void rehash(size_type);
        void clear() noexcept;
        void swap(hash_table &) noexcept;
        template <typename AllocatorRHS>
        void swap(hash_table<value_type, hasher, AllocatorRHS> &) noexcept;
        iterator insert(const_reference, size_type = 1);
        iterator insert(rvalue_reference);
        iterator insert(const_iterator, const_reference, size_type = 1);
        iterator insert(const_iterator, rvalue_reference);
        template <typename InputIterator>
        void insert(enable_if_t<is_input_iterator_v<InputIterator>>, InputIterator);
        void insert(initializer_list<value_type>);
        template <typename ...Args>
        iterator emplace(Args &&...);
        template <typename ...Args>
        iterator emplace(const_iterator, Args &&...);
        iterator erase(const_iterator) noexcept;
        iterator erase(const_iterator, iterator) noexcept;
        iterator remove(const_reference, size_type = 1) noexcept(has_nothrow_equal_to_operator_v<value_type>);
        template <typename UnaryPredict>
        iterator remove_if(UnaryPredict, size_type = 1) noexcept
        size_type count(const_reference) const noexcept(has_nothrow_equal_to_operator_v<value_type>);
        template <typename UnaryPredict>
        size_type count_if(UnaryPredict) const
                noexcept(has_nothrow_function_call_operator_v<UnaryPredict, const_reference>);
        iterator find(const_reference) noexcept(has_nothrow_equal_to_operator_v<value_type>);
        const_iterator find(const_reference) const noexcept(has_nothrow_equal_to_operator_v<value_type>);
        template <typename UnaryPredict>
        iterator find_if(UnaryPredict) noexcept(has_nothrow_function_call_operator_v<UnaryPredict, value_type>);
        template <typename UnaryPredict>
        const_iterator find_if(UnaryPredict) const
                noexcept(has_nothrow_function_call_operator_v<UnaryPredict, value_type>);
        bool contains(const_reference) const noexcept(has_nothrow_equal_to_operator_v<value_type>);
        template <typename UnaryPredict>
        bool contains_if(UnaryPredict) const noexcept(has_nothrow_function_call_operator_v<UnaryPredict, value_type>);
    public:
        hasher hash_function() const noexcept;
    };
    template <typename T, typename Hash, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    void swap(hash_table<T, Hash, AllocatorLHS, AllocatorRHS> &,
            hash_table<T, Hash, AllocatorLHS, AllocatorRHS> &) noexcept;
    template <typename T, typename Hash, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    [[nodiscard]]
    bool operator==(const hash_table<T, Hash, AllocatorLHS, AllocatorRHS> &,
            const hash_table<T, Hash, AllocatorLHS, AllocatorRHS> &) noexcept(has_nothrow_equal_to_operator_v<T>);
    template <typename T, typename Hash, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    [[nodiscard]]
    bool operator!=(const hash_table<T, Hash, AllocatorLHS, AllocatorRHS> &,
            const hash_table<T, Hash, AllocatorLHS, AllocatorRHS> &) noexcept(has_nothrow_equal_to_operator_v<T>);
}

#endif //DATA_STRUCTURE_HASH_TABLE_HPP