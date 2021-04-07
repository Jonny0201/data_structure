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
#include "allocator.hpp"

namespace data_structure::__data_structure_auxiliary {
    template <typename Hash, bool>
    struct hash_table_compress_auxiliary {
    public:
        Hash h;
    public:
        constexpr hash_table_compress_auxiliary() = default;
        explicit hash_table_compress_auxiliary(Hash h)
                noexcept(is_nothrow_copy_constructible_v<Hash> or is_nothrow_move_constructible_v<Hash>) :
                h {ds::move_if<is_nothrow_move_constructible_v<Hash>>(h)} {}
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
        explicit hash_table_compress_auxiliary(Hash) noexcept : Hash() {}
    public:
        Hash &hash() noexcept {
            return static_cast<Hash &>(*this);
        }
        const Hash &hash() const noexcept {
            return static_cast<const Hash &>(*this);
        }
    };
    template <typename Hash>
    using hash_table_compress = hash_table_compress_auxiliary<Hash, is_empty_v<Hash> and not is_final_v<Hash>>;
    template <typename BucketType, typename Hash>
    struct hash_table_compress_with_bucket_type : hash_table_compress<Hash> {
    public:
        BucketType b;
    public:
        constexpr hash_table_compress_with_bucket_type() = default;
        explicit hash_table_compress_with_bucket_type(BucketType b)
                noexcept(is_nothrow_default_constructible_v<hash_table_compress<Hash>>) :
                hash_table_compress<Hash>(), b {ds::move(b)} {}
        hash_table_compress_with_bucket_type(BucketType b, Hash h)
                noexcept(is_nothrow_copy_constructible_v<Hash> or is_nothrow_move_constructible_v<Hash>) :
                hash_table_compress<Hash>(ds::move_if<is_nothrow_move_constructible_v<Hash>>(h)), b {ds::move(b)} {}
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
        size_type size_of_bucket;
        double factor;
    private:
        static constexpr bool is_hash_power_2(size_t) noexcept;
        static constexpr size_t constrain_hash(size_t, size_type) noexcept;
        static constexpr size_t next_hash_power_2(size_t) noexcept;
        static bucket_type bucket_allocate(size_type);
        static node_type node_allocate();
    private:
        void copy_from_rhs(const hash_table &, bucket_type);
        void rehash(bucket_type) noexcept;
    public:
        constexpr hash_table() noexcept(is_nothrow_default_constructible_v<hasher>);
        explicit constexpr hash_table(hasher)
                noexcept(is_nothrow_copy_constructible_v<hasher> or is_nothrow_move_constructible_v<hasher>);
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
        hash_table &operator=(const hash_table<value_type, hasher, AllocatorRHS> &);
        template <typename AllocatorRHS>
        hash_table &operator=(hash_table<value_type, hasher, AllocatorRHS> &&) noexcept;
        size_type operator[](const_reference) noexcept(has_nothrow_equal_to_operator_v<value_type>);
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
        constexpr size_type max_size() const noexcept;
        [[nodiscard]]
        size_type bucket_count() const noexcept;
        [[nodiscard]]
        constexpr size_type max_bucket_count() const noexcept;
        [[nodiscard]]
        size_type bucket_size(size_type) const noexcept;
        [[nodiscard]]
        bool empty() const noexcept;
        [[nodiscard]]
        double load_factor() const noexcept;
        [[nodiscard]]
        double max_load_factor() const noexcept;
        void max_load_factor(double) noexcept;
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
        template <typename InputIterator> requires is_input_iterator_v<InputIterator>
        void insert(InputIterator, InputIterator);
        void insert(initializer_list<value_type>);
        template <typename ...Args>
        iterator emplace(Args &&...);
        template <typename ...Args>
        iterator emplace(const_iterator, Args &&...);
        iterator erase(const_iterator) noexcept;
        iterator erase(const_iterator, iterator) noexcept;
        iterator remove(const_reference, size_type = 1) noexcept(has_nothrow_equal_to_operator_v<value_type>);
        template <typename UnaryPredict>
        iterator remove_if(UnaryPredict, size_type = 1) noexcept;
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
    void swap(hash_table<T, Hash, AllocatorLHS> &, hash_table<T, Hash, AllocatorLHS> &) noexcept;
    template <typename T, typename Hash, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    [[nodiscard]]
    bool operator==(const hash_table<T, Hash, AllocatorLHS> &, const hash_table<T, Hash, AllocatorLHS> &)
            noexcept(has_nothrow_equal_to_operator_v<T>);
    template <typename T, typename Hash, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    [[nodiscard]]
    bool operator!=(const hash_table<T, Hash, AllocatorLHS> &, const hash_table<T, Hash, AllocatorLHS> &)
            noexcept(has_nothrow_equal_to_operator_v<T>);
}

namespace data_structure {
    /* private functions */
    template <typename T, typename Hash, typename Allocator>
    inline constexpr bool hash_table<T, Hash, Allocator>::is_hash_power_2(size_t bucket_count) noexcept {
        return bucket_count > 2 and not(bucket_count bitand (bucket_count - 1));
    }
    template <typename T, typename Hash, typename Allocator>
    inline constexpr size_t hash_table<T, Hash, Allocator>::constrain_hash(
            size_t h, size_type bucket_count) noexcept {
        return not(bucket_count bitand (bucket_count - 1)) ?
                h bitand (bucket_count - 1) : (h < bucket_count ? h : h % bucket_count);
    }
    template <typename T, typename Hash, typename Allocator>
    inline constexpr size_t hash_table<T, Hash, Allocator>::next_hash_power_2(size_t n) noexcept {
        return n < 2 ? n : (static_cast<size_t>(1) << (std::numeric_limits<size_t>::digits - __builtin_clzl(n - 1)));
    }
    template <typename T, typename Hash, typename Allocator>
    inline typename hash_table<T, Hash, Allocator>::bucket_type
    hash_table<T, Hash, Allocator>::bucket_allocate(size_type size) {
        return reinterpret_cast<bucket_type>(alloc_traits::operator new(sizeof(node_type) * size));
    }
    template <typename T, typename Hash, typename Allocator>
    inline typename hash_table<T, Hash, Allocator>::node_type hash_table<T, Hash, Allocator>::node_allocate() {
        return reinterpret_cast<node_type>(alloc_traits::operator new(sizeof(node_value_type)));
    }

    /* public functions */
    template <typename T, typename Hash, typename Allocator>
    constexpr inline hash_table<T, Hash, Allocator>::hash_table()
            noexcept(is_nothrow_default_constructible_v<hasher>) :
            bucket(nullptr), size_of_bucket {0}, factor {1.0} {}
    template <typename T, typename Hash, typename Allocator>
    constexpr inline hash_table<T, Hash, Allocator>::hash_table(hasher hash)
            noexcept(is_nothrow_copy_constructible_v<hasher> or is_nothrow_move_constructible_v<hasher>) :
            bucket(nullptr, ds::move_if<is_nothrow_move_constructible_v<hasher>>(hash)),
            size_of_bucket {0}, factor {1.0} {}
    template <typename T, typename Hash, typename Allocator>
    inline hash_table<T, Hash, Allocator>::hash_table(const hash_table &rhs) :
            bucket(this->bucket_allocate(rhs.size_of_bucket), rhs.hash_function()),
            size_of_bucket {rhs.size_of_bucket}, factor {rhs.factor}{
        this->copy_from_rhs(rhs, this->bucket.bucket());
    }
    template <typename T, typename Hash, typename Allocator>
    inline hash_table<T, Hash, Allocator>::hash_table(hash_table &&rhs) noexcept :
            bucket(rhs.bucket), size_of_bucket {rhs.size_of_bucket}, factor {rhs.factor} {
        rhs.bucket.bucket() = nullptr;
    }
    template <typename T, typename Hash, typename Allocator>
    template <typename AllocatorRHS>
    inline hash_table<T, Hash, Allocator>::hash_table(const hash_table<value_type, hasher, AllocatorRHS> &rhs) :
            bucket(this->bucket_allocate(rhs.size_of_bucket), rhs.hash_function()),
            size_of_bucket {rhs.size_of_bucket}, factor {rhs.factor} {
        this->copy_from_rhs(rhs, this->bucket.bucket());
    }
    template <typename T, typename Hash, typename Allocator>
    template <typename AllocatorRHS>
    inline hash_table<T, Hash, Allocator>::hash_table(hash_table<value_type, hasher, AllocatorRHS> &&rhs) noexcept :
            bucket(rhs.bucket), size_of_bucket {rhs.size_of_bucket}, factor {rhs.factor} {
        rhs.bucket.bucket() = nullptr;
    }
    template <typename T, typename Hash, typename Allocator>
    inline hash_table<T, Hash, Allocator>::~hash_table() noexcept {
        this->clear();
    }
    template <typename T, typename Hash, typename Allocator>
    hash_table<T, Hash, Allocator> &hash_table<T, Hash, Allocator>::operator=(const hash_table &rhs) {
        if(&rhs not_eq this) {
            bucket_type bucket {this->bucket_allocate(rhs.size_of_bucket)};
            this->copy_from_rhs(rhs, bucket);
            this->clear();
            this->bucket.bucket() = bucket;
            this->size_of_bucket = rhs.size_of_bucket;
            this->factor = rhs.factor;
        }
        return *this;
    }
    template <typename T, typename Hash, typename Allocator>
    inline hash_table<T, Hash, Allocator> &hash_table<T, Hash, Allocator>::operator=(hash_table &&rhs) noexcept {
        if(&rhs not_eq this) {
            this->clear();
            this->bucket = rhs.bucket;
            this->size_of_bucket = rhs.size_of_bucket;
            this->factor = rhs.factor;
        }
        return *this;
    }
    template <typename T, typename Hash, typename Allocator>
    template <typename AllocatorRHS>
    hash_table<T, Hash, Allocator> &hash_table<T, Hash, Allocator>::operator=(
            const hash_table <value_type, hasher, AllocatorRHS> &rhs) {
        bucket_type bucket {this->bucket_allocate(rhs.size_of_bucket)};
        this->copy_from_rhs(rhs, bucket);
        this->clear();
        this->bucket.bucket() = bucket;
        this->size_of_bucket = rhs.size_of_bucket;
        this->factor = rhs.factor;
        return *this;
    }
    template <typename T, typename Hash, typename Allocator>
    template <typename AllocatorRHS>
    inline hash_table<T, Hash, Allocator> &hash_table<T, Hash, Allocator>::operator=(
            hash_table <value_type, hasher, AllocatorRHS> &&rhs) noexcept {
        this->clear();
        this->bucket = rhs.bucket;
        this->size_of_bucket = rhs.size_of_bucket;
        this->factor = rhs.factor;
        return *this;
    }
    template <typename T, typename Hash, typename Allocator>
    inline typename hash_table<T, Hash, Allocator>::size_type
    hash_table<T, Hash, Allocator>::operator[](const_reference value)
            noexcept(has_nothrow_equal_to_operator_v<value_type>) {
        auto pos {this->constrain_hash(this->bucket.hash(value), this->size_of_bucket)};
        for(auto cursor {this->bucket.bucket()[pos]}; cursor; cursor = cursor->next) {
            if(value == cursor->value) {
                return pos;
            }
        }
        return this->size_of_bucket;
    }
    template <typename T, typename Hash, typename Allocator>
    inline typename hash_table<T, Hash, Allocator>::iterator
    hash_table<T, Hash, Allocator>::begin() noexcept {
        return iterator(*this->bucket.bucket(), this->bucket.bucket());
    }
    template <typename T, typename Hash, typename Allocator>
    inline typename hash_table<T, Hash, Allocator>::const_iterator
    hash_table<T, Hash, Allocator>::begin() const noexcept {
        auto r {const_cast<hash_table *>(this)};
        return const_iterator(*r->bucket.bucket(), r->bucket.bucket());
    }
    template <typename T, typename Hash, typename Allocator>
    inline typename hash_table<T, Hash, Allocator>::iterator
    hash_table<T, Hash, Allocator>::end() noexcept {
        return iterator(nullptr, this->bucket.bucket() + this->size_of_bucket);
    }
    template <typename T, typename Hash, typename Allocator>
    inline typename hash_table<T, Hash, Allocator>::const_iterator
    hash_table<T, Hash, Allocator>::end() const noexcept {
        return const_iterator(nullptr, const_cast<hash_table *>(this)->bucket.bucket());
    }
    template <typename T, typename Hash, typename Allocator>
    inline typename hash_table<T, Hash, Allocator>::const_iterator
    hash_table<T, Hash, Allocator>::cbegin() const noexcept {
        return this->begin();
    }
    template <typename T, typename Hash, typename Allocator>
    inline typename hash_table<T, Hash, Allocator>::const_iterator
    hash_table<T, Hash, Allocator>::cend() const noexcept {
        return this->end();
    }
    template <typename T, typename Hash, typename Allocator>
    typename hash_table<T, Hash, Allocator>::size_type hash_table<T, Hash, Allocator>::size() const noexcept {
        size_type size {0};
        for(auto i {0}; i < this->size_of_bucket; ++i) {
            size += this->bucket_size(i);
        }
        return size;
    }
    template <typename T, typename Hash, typename Allocator>
    inline constexpr typename hash_table<T, Hash, Allocator>::size_type
    hash_table<T, Hash, Allocator>::max_size() const noexcept {
        return std::numeric_limits<size_type>::max() / sizeof(node_value_type);
    }
    template <typename T, typename Hash, typename Allocator>
    inline typename hash_table<T, Hash, Allocator>::size_type
    hash_table<T, Hash, Allocator>::bucket_count() const noexcept {
        return this->size_of_bucket;
    }
    template <typename T, typename Hash, typename Allocator>
    inline constexpr typename hash_table<T, Hash, Allocator>::size_type
    hash_table<T, Hash, Allocator>::max_bucket_count() const noexcept {
        return this->max_size();
    }
    template <typename T, typename Hash, typename Allocator>
    typename hash_table<T, Hash, Allocator>::size_type
    hash_table<T, Hash, Allocator>::bucket_size(size_type n) const noexcept {
        size_type size {0};
        for(auto cursor {this->bucket.bucket()[n]}; cursor; ++size, static_cast<void>(cursor = cursor->next));
        return size;
    }
    template <typename T, typename Hash, typename Allocator>
    inline bool hash_table<T, Hash, Allocator>::empty() const noexcept {
        return this->bucket.bucket();
    }
    template <typename T, typename Hash, typename Allocator>
    inline double hash_table<T, Hash, Allocator>::load_factor() const noexcept {
        return this->size() / this->size_of_bucket;
    }
    template <typename T, typename Hash, typename Allocator>
    inline double hash_table<T, Hash, Allocator>::max_load_factor() const noexcept {
        return this->factor;
    }
    template <typename T, typename Hash, typename Allocator>
    inline void hash_table<T, Hash, Allocator>::max_load_factor(double factor) noexcept {
        if(factor >= this->load_factor()) {
            this->factor = factor;
        }
    }
    template <typename T, typename Hash, typename Allocator>
    inline void hash_table<T, Hash, Allocator>::reserve(size_type n) {
        this->rehash(static_cast<size_type>(std::ceil(n / this->factor)));
    }
    template <typename T, typename Hash, typename Allocator>
    void hash_table<T, Hash, Allocator>::rehash(size_type n) {
        if(n <= this->size_of_bucket) {
            return;
        }
        auto bucket {this->bucket_allocate(n)};
        this->rehash(bucket);
        this->clear();
        this->bucket.bucket() = bucket;
        this->size_of_bucket = n;
    }
}

#endif //DATA_STRUCTURE_HASH_TABLE_HPP