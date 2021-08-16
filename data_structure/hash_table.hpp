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
    struct hash_table_compress_auxiliary<Hash, true> : Hash {
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
    template <typename T, typename Hash = hash<T>, typename Allocator = allocator<type_holder<T>>>
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
        using local_iterator = __dsa::hash_table_local_iterator<value_type, false>;
        using const_local_iterator = __dsa::hash_table_local_iterator<value_type, true>;
    private:
        using node_value_type = __dsa::hash_table_node<value_type>;
        using node_type = node_value_type *;
        using bucket_type = node_type *;
        using alloc_traits = allocator_traits<allocator_type>;
        static_assert(is_same_v<value_type, typename alloc_traits::value_type>,
                "The Allocator::value_type must be the same as template argument value_type!");
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
        void rehash(bucket_type, size_type) noexcept;
        void clear_bucket() noexcept;
        void deallocate_list(node_type, node_type) noexcept;
    public:
        constexpr hash_table() noexcept(is_nothrow_default_constructible_v<hasher>);
        explicit constexpr hash_table(hasher)
                noexcept(is_nothrow_copy_constructible_v<hasher> or is_nothrow_move_constructible_v<hasher>);
        hash_table(const hash_table &);
        hash_table(hash_table &&) noexcept;
        template <typename AllocatorRHS>
        explicit hash_table(const hash_table<value_type, hasher, AllocatorRHS> &);
        template <typename AllocatorRHS>
        explicit hash_table(hash_table<value_type, hasher, AllocatorRHS> &&) noexcept;
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
        local_iterator begin(size_type) noexcept;
        [[nodiscard]]
        const_local_iterator begin(size_type) const noexcept;
        [[nodiscard]]
        constexpr local_iterator end(size_type) noexcept;
        [[nodiscard]]
        constexpr const_local_iterator end(size_type) const noexcept;
        [[nodiscard]]
        const_local_iterator cbegin(size_type) const noexcept;
        [[nodiscard]]
        constexpr const_local_iterator cend(size_type) const noexcept;
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
        template <typename InputIterator> requires is_input_iterator_v<InputIterator>
        void insert(InputIterator, InputIterator);
        void insert(initializer_list<value_type>);
        template <typename ...Args>
        iterator emplace(Args &&...);
        iterator erase(const_iterator) noexcept;
        iterator erase(const_iterator, const_iterator) noexcept;
        template <typename Equal = equal_to<value_type, value_type>>
        iterator remove(const_reference, size_type = 1, Equal = {})
                noexcept(has_nothrow_function_call_operator_v<Equal, value_type, value_type>);
        template <typename Equal = equal_to<value_type, value_type>>
        size_type count(const_reference, Equal = {}) const
                noexcept(has_nothrow_function_call_operator_v<Equal, value_type, value_type>);
        template <typename Equal = equal_to<value_type, value_type>>
        iterator find(const_reference, Equal = {})
                noexcept(has_nothrow_function_call_operator_v<Equal, value_type, value_type>);
        template <typename Equal = equal_to<value_type, value_type>>
        const_iterator find(const_reference, Equal = {}) const
                noexcept(has_nothrow_function_call_operator_v<Equal, value_type, value_type>);
        template <typename Equal = equal_to<value_type, value_type>>
        bool contains(const_reference, Equal = {}) const
                noexcept(has_nothrow_function_call_operator_v<Equal, value_type, value_type>);
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
        return n < 2 ? n : (static_cast<size_t>(1) <<
                (std::numeric_limits<size_t>::digits - __builtin_clzl(n - 1)));
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
    template <typename T, typename Hash, typename Allocator>
    void hash_table<T, Hash, Allocator>::copy_from_rhs(const hash_table &rhs, bucket_type bucket) {
        for(auto i {0}; i < rhs.size_of_bucket; ++i) {
            if(auto cursor {rhs.bucket.bucket()[i]}; cursor) {
                bucket[i] = this->node_allocate();
                auto bucket_last {bucket[i]};
                while(true) {
                    if constexpr(is_nothrow_copy_constructible_v<value_type>) {
                        alloc_traits::construct(ds::address_of(bucket_last->value), cursor->value);
                    }else {
                        try {
                            alloc_traits::construct(ds::address_of(bucket_last->value), cursor->value);
                        }catch(...) {
                            for(auto j {0}; j < i; ++j) {
                                for(auto b {bucket[j]}; b;) {
                                    auto backup {b};
                                    b = b->next;
                                    alloc_traits::destroy(ds::address_of(backup->value));
                                    alloc_traits::operator delete(backup);
                                }
                            }
                            for(auto b {bucket[i]}; b not_eq bucket_last;) {
                                auto backup {b};
                                b = b->next;
                                alloc_traits::destroy(ds::address_of(backup->value));
                                alloc_traits::operator delete(backup);
                            }
                            alloc_traits::operator delete(bucket_last);
                            alloc_traits::operator delete(bucket);
                            throw;
                        }
                    }
                    bucket_last->hash = cursor->hash;
                    if(not cursor->next) {
                        bucket_last->next = nullptr;
                        break;
                    }
                    try {
                        bucket_last->next = this->node_allocate();
                    }catch(...) {
                        bucket_last->next = nullptr;
                        for(auto j {0}; j <= i; ++j) {
                            for(auto b {bucket[j]}; b;) {
                                auto backup {b};
                                b = b->next;
                                alloc_traits::destroy(ds::address_of(backup->value));
                                alloc_traits::operator delete(backup);
                            }
                        }
                        alloc_traits::operator delete(bucket);
                        throw;
                    }
                }
            }
        }
    }
    template <typename T, typename Hash, typename Allocator>
    void hash_table<T, Hash, Allocator>::rehash(bucket_type bucket, size_type bucket_size) noexcept {
        ds::memory_initialize(bucket, bucket_size * sizeof(bucket_type));
        for(auto i {0}; i < this->size_of_bucket; ++i) {
            if(auto cursor {this->bucket.bucket()[i]}; cursor) {
                do {
                    auto backup {cursor};
                    cursor = cursor->next;
                    auto constrained {this->constrain_hash(backup->hash, bucket_size)};
                    backup->next = bucket[constrained];
                    bucket[constrained] = backup;
                }while(cursor);
            }
        }
    }
    template <typename T, typename Hash, typename Allocator>
    void hash_table<T, Hash, Allocator>::clear_bucket() noexcept {
        for(auto i {0}; i < this->size_of_bucket; ++i) {
            if(auto cursor {this->bucket.bucket()[i]}; cursor) {
                do {
                    auto backup {cursor};
                    cursor = cursor->next;
                    alloc_traits::destroy(ds::address_of(backup->value));
                    alloc_traits::operator delete(backup);
                }while(cursor);
            }
        }
        alloc_traits::operator delete(this->bucket.bucket());
    }
    template <typename T, typename Hash, typename Allocator>
    void hash_table<T, Hash, Allocator>::deallocate_list(node_type begin, node_type end) noexcept {
        while(begin not_eq end) {
            auto backup {begin};
            begin = begin->next;
            alloc_traits::destroy(ds::address_of(backup->value));
            alloc_traits::operator delete(backup);
        }
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
            bucket(rhs.bucket.bucket() ? this->bucket_allocate(rhs.size_of_bucket) : nullptr, rhs.hash_function()),
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
            bucket(rhs.bucket.bucket() ? this->bucket_allocate(rhs.size_of_bucket) : nullptr, rhs.hash_function()),
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
        this->clear_bucket();
    }
    template <typename T, typename Hash, typename Allocator>
    hash_table<T, Hash, Allocator> &hash_table<T, Hash, Allocator>::operator=(const hash_table &rhs) {
        if(&rhs not_eq this) {
            bucket_type bucket {rhs.bucket.bucket() ? this->bucket_allocate(rhs.size_of_bucket) : nullptr};
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
        auto pos {this->constrain_hash(this->bucket.hash()(value), this->size_of_bucket)};
        for(auto cursor {this->bucket.bucket()[pos]}; cursor; cursor = cursor->next) {
            if(value == cursor->value) {
                return pos;
            }
        }
        return this->size_of_bucket;
    }
    template <typename T, typename Hash, typename Allocator>
    typename hash_table<T, Hash, Allocator>::iterator
    hash_table<T, Hash, Allocator>::begin() noexcept {
        auto i {0};
        for(; i < this->size_of_bucket; ++i) {
            if(this->bucket.bucket()[i]) {
                break;
            }
        }
        return i == this->size_of_bucket ? this->end() : iterator(this->bucket.bucket()[i],
                this->bucket.bucket() + i, this->bucket.bucket(), this->size_of_bucket);
    }
    template <typename T, typename Hash, typename Allocator>
    inline typename hash_table<T, Hash, Allocator>::const_iterator
    hash_table<T, Hash, Allocator>::begin() const noexcept {
        return const_cast<hash_table *>(this)->begin();
    }
    template <typename T, typename Hash, typename Allocator>
    inline typename hash_table<T, Hash, Allocator>::iterator
    hash_table<T, Hash, Allocator>::end() noexcept {
        return iterator(nullptr, this->bucket.bucket() + this->size_of_bucket,
                this->bucket.bucket(), this->size_of_bucket);
    }
    template <typename T, typename Hash, typename Allocator>
    inline typename hash_table<T, Hash, Allocator>::const_iterator
    hash_table<T, Hash, Allocator>::end() const noexcept {
        return iterator(nullptr, this->bucket.bucket() + this->size_of_bucket,
                this->bucket.bucket(), this->size_of_bucket);
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
    inline typename hash_table<T, Hash, Allocator>::local_iterator
    hash_table<T, Hash, Allocator>::begin(size_type n) noexcept {
        return local_iterator(this->bucket.bucket()[n]);
    }
    template <typename T, typename Hash, typename Allocator>
    inline typename hash_table<T, Hash, Allocator>::const_local_iterator
    hash_table<T, Hash, Allocator>::begin(size_type n) const noexcept {
        return this->cbegin(n);
    }
    template <typename T, typename Hash, typename Allocator>
    inline constexpr typename hash_table<T, Hash, Allocator>::local_iterator
    hash_table<T, Hash, Allocator>::end(size_type) noexcept {
        return {};
    }
    template <typename T, typename Hash, typename Allocator>
    inline constexpr typename hash_table<T, Hash, Allocator>::const_local_iterator
    hash_table<T, Hash, Allocator>::end(size_type) const noexcept {
        return {};
    }
    template <typename T, typename Hash, typename Allocator>
    inline typename hash_table<T, Hash, Allocator>::const_local_iterator
    hash_table<T, Hash, Allocator>::cbegin(size_type n) const noexcept {
        return const_cast<hash_table *>(this)->begin(n);
    }
    template <typename T, typename Hash, typename Allocator>
    inline constexpr typename hash_table<T, Hash, Allocator>::const_local_iterator
    hash_table<T, Hash, Allocator>::cend(size_type) const noexcept {
        return {};
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
        return this->size() == 0;
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
        if(not this->is_hash_power_2(n)) {
            n = this->next_hash_power_2(n);
        }
        auto bucket {this->bucket_allocate(n)};
        this->rehash(bucket, n);
        alloc_traits::operator delete(this->bucket.bucket());
        this->bucket.bucket() = bucket;
        this->size_of_bucket = n;
    }
    template <typename T, typename Hash, typename Allocator>
    inline void hash_table<T, Hash, Allocator>::clear() noexcept {
        this->clear_bucket();
        this->bucket.bucket() = nullptr;
        this->size_of_bucket = 0;
    }
    template <typename T, typename Hash, typename Allocator>
    inline void hash_table<T, Hash, Allocator>::swap(hash_table &rhs) noexcept {
        ds::swap(rhs.bucket, this->bucket);
        ds::swap(this->size_of_bucket, rhs.size_of_bucket);
        ds::swap(this->factor, rhs.factor);
    }
    template <typename T, typename Hash, typename Allocator>
    template <typename AllocatorRHS>
    inline void hash_table<T, Hash, Allocator>::swap(hash_table<value_type, hasher, AllocatorRHS> &rhs) noexcept {
        this->swap(*reinterpret_cast<hash_table *>(&rhs));
    }
    template <typename T, typename Hash, typename Allocator>
    typename hash_table<T, Hash, Allocator>::iterator
    hash_table<T, Hash, Allocator>::insert(const_reference value, size_type size) {
        if(size == 0) {
            return this->end();
        }
        const auto total_size {this->size() + size};
        if(static_cast<double>(total_size) / this->size_of_bucket >= this->factor or this->size_of_bucket == 0) {
            this->rehash(total_size);
        }
        auto hash {this->bucket.hash()(value)};
        auto new_node {this->node_allocate()};
        node_type last;
        for(auto cursor {new_node};; cursor = cursor->next) {
            cursor->hash = hash;
            if constexpr(is_nothrow_copy_constructible_v<value_type>) {
                alloc_traits::construct(ds::address_of(cursor->value), value);
            }else {
                try {
                    alloc_traits::construct(ds::address_of(cursor->value), value);
                }catch(...) {
                    alloc_traits::operator delete(cursor);
                    for(auto i {new_node}; i->next not_eq cursor;) {
                        auto backup {i};
                        i = i->next;
                        alloc_traits::destroy(ds::address_of(backup->value));
                        alloc_traits::operator delete(backup);
                    }
                    throw;
                }
            }
            if(--size == 0) {
                last = cursor;
                break;
            }
            try {
                cursor->next = this->node_allocate();
            }catch(...) {
                for(auto i {new_node};;) {
                    auto backup {i};
                    i = i->next;
                    alloc_traits::destroy(ds::address_of(backup->value));
                    alloc_traits::operator delete(backup);
                    if(i == cursor) {
                        break;
                    }
                }
                throw;
            }
        }
        auto constrained {this->constrain_hash(hash, this->size_of_bucket)};
        last->next = this->bucket.bucket()[constrained];
        this->bucket.bucket()[constrained] = new_node;
        return iterator(new_node, this->bucket.bucket() + constrained, this->bucket.bucket(), this->size_of_bucket);
    }
    template <typename T, typename Hash, typename Allocator>
    inline typename hash_table<T, Hash, Allocator>::iterator
    hash_table<T, Hash, Allocator>::insert(rvalue_reference value) {
        return this->emplace(ds::move(value));
    }
    template <typename T, typename Hash, typename Allocator>
    template <typename InputIterator> requires is_input_iterator_v<InputIterator>
    void hash_table<T, Hash, Allocator>::insert(InputIterator begin, InputIterator end) {
        while(begin not_eq end) {
            if constexpr(is_input_iterator_v<InputIterator> and not is_forward_iterator_v<InputIterator>) {
                this->emplace(ds::move(*begin++));
            }else {
                this->emplace(*begin++);
            }
        }
    }
    template <typename T, typename Hash, typename Allocator>
    inline void hash_table<T, Hash, Allocator>::insert(initializer_list<value_type> init_list) {
        this->insert(init_list.begin(), init_list.end());
    }
    template <typename T, typename Hash, typename Allocator>
    template <typename ...Args>
    typename hash_table<T, Hash, Allocator>::iterator hash_table<T, Hash, Allocator>::emplace(Args &&...args) {
        const auto total_size {this->size() + 1};
        if(static_cast<double>(total_size) / this->size_of_bucket >= this->factor or this->size_of_bucket == 0) {
            this->rehash(total_size);
        }
        auto new_node {this->node_allocate()};
        if constexpr(is_nothrow_constructible_v<value_type, Args...>) {
            alloc_traits::construct(ds::address_of(new_node->value), ds::forward<Args>(args)...);
        }else {
            try {
                alloc_traits::construct(ds::address_of(new_node->value), ds::forward<Args>(args)...);
            }catch(...) {
                alloc_traits::operator delete(new_node);
                throw;
            }
        }
        new_node->hash = this->bucket.hash()(new_node->value);
        auto constrained {this->constrain_hash(new_node->hash, this->size_of_bucket)};
        new_node->next = this->bucket.bucket()[constrained];
        this->bucket.bucket()[constrained] = new_node;
        return iterator(new_node, this->bucket.bucket() + constrained,
                this->bucket.bucket(), this->size_of_bucket);
    }
    template <typename T, typename Hash, typename Allocator>
    typename hash_table<T, Hash, Allocator>::iterator
    hash_table<T, Hash, Allocator>::erase(const_iterator pos) noexcept {
        if(pos == this->cend()) {
            return this->end();
        }
        auto r {pos};
        ++r;
        if(pos.node == *pos.bucket) {
            *pos.bucket = pos.node->next;
        }else {
            for(auto cursor {*pos.bucket};; cursor = cursor->next) {
                if(cursor->next == pos.node) {
                    cursor->next = pos.node->next;
                    break;
                }
            }
        }
        alloc_traits::destroy(ds::address_of(pos.node->value));
        alloc_traits::operator delete(pos.node);
        return r;
    }
    template <typename T, typename Hash, typename Allocator>
    typename hash_table<T, Hash, Allocator>::iterator
    hash_table<T, Hash, Allocator>::erase(const_iterator begin, const_iterator end) noexcept {
        if(begin == end or begin == this->cend()) {
            return this->end();
        }
        if(begin.node == *begin.bucket) {
            *begin.bucket = nullptr;
        }else {
            for(auto cursor {*begin.bucket};; cursor = cursor->next) {
                if(cursor->next == begin.node) {
                    cursor->next = nullptr;
                    break;
                }
            }
        }
        this->deallocate_list(begin.node, nullptr);
        for(auto bucket_cursor {begin.bucket + 1};; ++bucket_cursor) {
            if(bucket_cursor == end.bucket) {
                break;
            }
            this->deallocate_list(*bucket_cursor, nullptr);
            *bucket_cursor = nullptr;
        }
        if(end.node not_eq *end.bucket) {
            this->deallocate_list(*end.bucket, end.node);
            *end.bucket = end.node;
        }
        return iterator(end.node, end.bucket, end.bucket_start, end.bucket_count);
    }
    template <typename T, typename Hash, typename Allocator>
    template <typename Equal>
    typename hash_table<T, Hash, Allocator>::iterator
    hash_table<T, Hash, Allocator>::remove(const_reference value, size_type size, Equal equal)
            noexcept(has_nothrow_function_call_operator_v<Equal, value_type, value_type>) {
        if(size == 0) {
            return this->end();
        }
        auto constrained {this->constrain_hash(this->bucket.hash()(value), this->size_of_bucket)};
        auto bucket {this->bucket.bucket() + constrained};
        auto cursor {*bucket};
        while(equal(cursor->value, value)) {
            *bucket = cursor->next;
            alloc_traits::destroy(ds::address_of(cursor->value));
            alloc_traits::operator delete(cursor);
            cursor = *bucket;
            if(--size == 0 or cursor == nullptr) {
                return iterator(cursor, bucket, this->bucket.bucket(), this->size_of_bucket);
            }
        }
        while(cursor->next) {
            if(equal(cursor->next->value, value)) {
                auto backup {cursor->next};
                cursor->next = backup->next;
                alloc_traits::destroy(ds::address_of(backup->value));
                alloc_traits::operator delete(backup);
                if(--size == 0) {
                    break;
                }
            }else {
                cursor = cursor->next;
            }
        }
        return iterator(cursor, bucket, this->bucket.bucket(), this->size_of_bucket);
    }
    template <typename T, typename Hash, typename Allocator>
    template <typename Equal>
    typename hash_table<T, Hash, Allocator>::size_type
    hash_table<T, Hash, Allocator>::count(const_reference value, Equal equal) const
            noexcept(has_nothrow_function_call_operator_v<Equal, value_type, value_type>) {
        auto constrained {this->constrain_hash(this->bucket.hash()(value), this->size_of_bucket)};
        size_type size {};
        for(auto cursor {this->bucket.bucket()[constrained]}; cursor; cursor = cursor->next) {
            if(equal(cursor->value, value)) {
                ++size;
            }
        }
        return size;
    }
    template <typename T, typename Hash, typename Allocator>
    template <typename Equal>
    typename hash_table<T, Hash, Allocator>::iterator hash_table<T, Hash, Allocator>::find(const_reference value,
            Equal equal) noexcept(has_nothrow_function_call_operator_v<Equal, value_type, value_type>) {
        auto constrained {this->constrain_hash(this->bucket.hash()(value), this->size_of_bucket)};
        for(auto cursor {this->bucket.bucket()[constrained]}; cursor; cursor = cursor->next) {
            if(equal(cursor->value), value) {
                return iterator(cursor, this->bucket.bucket() + constrained,
                        this->bucket.bucket(), this->size_of_bucket);
            }
        }
        return this->end();
    }
    template <typename T, typename Hash, typename Allocator>
    template <typename Equal>
    inline typename hash_table<T, Hash, Allocator>::const_iterator
    hash_table<T, Hash, Allocator>::find(const_reference value, Equal equal) const
            noexcept(has_nothrow_function_call_operator_v<Equal, value_type, value_type>) {
        return const_cast<hash_table *>(this)->find<add_lvalue_reference_t<Equal>>(value, equal);
    }
    template <typename T, typename Hash, typename Allocator>
    template <typename Equal>
    bool hash_table<T, Hash, Allocator>::contains(const_reference value, Equal equal) const
            noexcept(has_nothrow_function_call_operator_v<Equal, value_type, value_type>) {
        auto constrained {this->constrain_hash(this->bucket.hash()(value), this->size_of_bucket)};
        for(auto cursor {this->bucket.bucket()[constrained]}; cursor; cursor = cursor->next) {
            if(equal(cursor->value, value)) {
                return true;
            }
        }
        return false;
    }
    template <typename T, typename Hash, typename Allocator>
    inline typename hash_table<T, Hash, Allocator>::hasher
    hash_table<T, Hash, Allocator>::hash_function() const noexcept {
        return this->bucket.hash();
    }
}

namespace data_structure {
    template <typename T, typename Hash, typename AllocatorLHS, typename AllocatorRHS>
    inline void swap(hash_table<T, Hash, AllocatorLHS> &lhs, hash_table<T, Hash, AllocatorLHS> &rhs) noexcept {
        lhs.swap(rhs);
    }
    template <typename T, typename Hash, typename AllocatorLHS, typename AllocatorRHS>
    bool operator==(const hash_table<T, Hash, AllocatorLHS> &lhs, const hash_table<T, Hash, AllocatorLHS> &rhs)
            noexcept(has_nothrow_equal_to_operator_v<T>) {
        if(lhs.size() not_eq rhs.size()) {
            return false;
        }
        auto lhs_end {lhs.cend()};
        for(auto lhs_cursor {lhs.cbegin()}, rhs_cursor {rhs.cbegin()};; ++lhs_cursor, ++rhs_cursor) {
            if(lhs_cursor == lhs_end) {
                break;
            }
            if(*lhs_cursor not_eq *rhs_cursor) {
                return false;
            }
        }
        return true;
    }
    template <typename T, typename Hash, typename AllocatorLHS, typename AllocatorRHS>
    inline bool operator!=(const hash_table<T, Hash, AllocatorLHS> &lhs,
            const hash_table<T, Hash, AllocatorLHS> &rhs) noexcept(has_nothrow_equal_to_operator_v<T>) {
        return not(lhs == rhs);
    }
}

#endif //DATA_STRUCTURE_HASH_TABLE_HPP