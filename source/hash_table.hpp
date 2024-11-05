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

// Todo 1 : replace rehash using allocate_buckets
// Todo 2 : implement erase_after instead of using erase
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
    static constexpr size_t make_power_2(size_t) noexcept;
    static constexpr size_t constrain_hash(size_t, size_t) noexcept;
    constexpr void allocate_buckets(size_type);
    template <typename ...Args>
    constexpr __dsa::hash_table_node<T> *allocate_node(Args &&...);
    constexpr bool need_rehash(size_type) const noexcept;
    constexpr const_iterator insert_node(__dsa::hash_table_node<T> *node) noexcept;
public:
    constexpr hash_table() = default;
    explicit constexpr hash_table(const Hash &) noexcept(
            is_nothrow_copy_constructible_v<Hash> and is_nothrow_default_constructible_v<node_allocator> and
            is_nothrow_default_constructible_v<bucket_allocator>);
    explicit constexpr hash_table(const Allocator &) noexcept(
            is_nothrow_default_constructible_v<Hash> and is_nothrow_default_constructible_v<node_allocator> and
            is_nothrow_default_constructible_v<bucket_allocator>);
    constexpr hash_table(const Hash &, const Allocator &) noexcept(
            is_nothrow_copy_constructible_v<Hash> and is_nothrow_default_constructible_v<node_allocator> and
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
    static constexpr const_local_iterator end(size_type) noexcept;
    [[nodiscard]]
    static constexpr const_local_iterator cend(size_type) noexcept;
    [[nodiscard]]
    constexpr size_type size() const noexcept;
    [[nodiscard]]
    constexpr size_type bucket_count() const noexcept;
    [[nodiscard]]
    constexpr float load_factor() const noexcept;
    constexpr void load_factor(float);
    [[nodiscard]]
    constexpr Hash hash_function() const noexcept(is_nothrow_copy_constructible_v<Hash>);
    [[nodiscard]]
    constexpr Allocator allocator() const noexcept(is_nothrow_default_constructible_v<Allocator>);
    [[nodiscard]]
    constexpr bool empty() const noexcept;
    constexpr void reserve(size_type);
    constexpr void rehash(size_type);
    constexpr void clear() noexcept;
    constexpr void swap(hash_table &) noexcept;
    constexpr const_iterator insert(const_reference);
    constexpr const_iterator insert(rvalue_reference);
    template <typename ...Args>
    constexpr const_iterator emplace(Args &&...);
    template <IsInputIterator InputIterator>
    constexpr void insert(InputIterator, InputIterator);
    constexpr void insert(initializer_list<T>);
    constexpr const_iterator erase(const_iterator) noexcept;
    constexpr void erase(const_iterator, const_iterator) noexcept;
public:
    constexpr void remove(const_reference) noexcept(is_nothrow_equal_to_comparable_v<const_reference>);
    template <typename UnaryPredicate>
    constexpr void remove_if(UnaryPredicate) noexcept(is_nothrow_invocable_r_v<bool, UnaryPredicate, const_reference>);
    constexpr void unique()  noexcept(is_nothrow_equal_to_comparable_v<const_reference>);
    template <typename UnaryPredicate>
    constexpr void unique_if(UnaryPredicate) noexcept(is_nothrow_invocable_r_v<bool, UnaryPredicate, const_reference>);
    [[nodiscard]]
    constexpr const_iterator find(const_reference) const noexcept(is_nothrow_equal_to_comparable_v<const_reference>);
    template <typename UnaryPredicate>
    [[nodiscard]]
    constexpr const_iterator find_if(UnaryPredicate) const noexcept(is_nothrow_invocable_r_v<bool,
            UnaryPredicate, const_reference>);
    [[nodiscard]]
    constexpr bool contains(const_reference) const noexcept(is_nothrow_equal_to_comparable_v<const_reference>);
    template <typename UnaryPredicate>
    [[nodiscard]]
    constexpr bool contains_if(UnaryPredicate) const noexcept(is_nothrow_invocable_r_v<bool,
            UnaryPredicate, const_reference>);
    [[nodiscard]]
    constexpr size_type count(const_reference) const noexcept(is_nothrow_equal_to_comparable_v<const_reference>);
    template <typename UnaryPredicate>
    [[nodiscard]]
    constexpr size_type count_if(UnaryPredicate) const noexcept(is_nothrow_invocable_r_v<bool,
            UnaryPredicate, const_reference>);
    constexpr void merge(hash_table &) noexcept;
    constexpr void merge(hash_table &&) noexcept;
};
__DATA_STRUCTURE_END(hash table declaration)

__DATA_STRUCTURE_START(hash table implementation)
/* private functions */
template <typename T, typename Hash, typename Allocator>
constexpr size_t hash_table<T, Hash, Allocator>::make_power_2(size_t n) noexcept {
    if(n < 2) {
        return n;
    }
    if(n bitand n - 1) {
        // Todo : consider implementing __builtin_clzl
        return 1uz << (std::numeric_limits<size_t>::digits - __builtin_clzl(n - 1));
    }
    return n;
}
template <typename T, typename Hash, typename Allocator>
constexpr size_t hash_table<T, Hash, Allocator>::constrain_hash(size_t code, size_t bucket_size) noexcept {
    return not(bucket_size bitand (bucket_size - 1)) ? code bitand (bucket_size - 1) :
            (code < bucket_size ? code : code % bucket_size);
}
template <typename T, typename Hash, typename Allocator>
constexpr void hash_table<T, Hash, Allocator>::allocate_buckets(size_type n) {
    n = this->make_power_2(n);
    const auto new_buckets {this->bucket_size.allocator().allocate(n)};
    ds::memory_default_initialization(new_buckets, n * sizeof(__dsa::hash_table_node<T> *));
    if(const auto bucket_size {this->bucket_size()}; n < bucket_size) {
        for(auto i {0}; i < bucket_size; ++i) {
            if(this->buckets()[i]) {
                const auto new_position {this->constrain_hash(this->buckets()[i]->hash, n)};
                if(auto cursor {new_buckets[new_position]}; cursor) {
                    for(; cursor->next; cursor = cursor->next);
                    cursor->next = this->buckets()[i];
                }else {
                    new_buckets[new_position] = this->buckets()[i];
                }
            }
        }
    }else {
        ds::memory_copy(new_buckets, this->buckets(), bucket_size);
    }
    this->bucket_size.allocator().deallocate(this->buckets());
    this->buckets() = new_buckets;
    this->bucket_size() = n;
}
template <typename T, typename Hash, typename Allocator>
template <typename ...Args>
constexpr __dsa::hash_table_node<T> *hash_table<T, Hash, Allocator>::allocate_node(Args &&...args) {
    struct construction_handler {
        __dsa::hash_table_node<T> *node;
        node_allocator &allocator;
        bool construction_done {};
        constexpr construction_handler(__dsa::hash_table_node<T> *node, node_allocator &allocator) :
                node {node}, allocator {allocator} {}
        constexpr void operator()() noexcept {
            this->allocator.deallocate(this->node);
            if(this->construction_done) {
                ds::destroy(ds::address_of(this->node->value));
            }
        }
    };
    const auto node {this->node_size.allocator().allocate(1)};
    auto trans {transaction {construction_handler {node, this->node_size.allocator()}}};
    ds::construct(ds::address_of(node->value), ds::forward<Args>(args)...);
    trans.get_rollback().construction_done = true;
    node->hash = this->buckets.second()(node->value);
    trans.complete();
    return node;
}
template <typename T, typename Hash, typename Allocator>
constexpr bool hash_table<T, Hash, Allocator>::need_rehash(size_type new_node_size) const noexcept {
    if(this->bucket_size() == 0) {
        return true;
    }
    return new_node_size / this->bucket_size() > this->loading_factor;
}
template <typename T, typename Hash, typename Allocator>
constexpr typename hash_table<T, Hash, Allocator>::const_iterator
hash_table<T, Hash, Allocator>::insert_node(__dsa::hash_table_node<T> *node) noexcept {
    const auto location {this->constrain_hash(node->hash)};
    node->next = this->buckets()[location];
    this->buckets()[location] = node;
    ++this->node_size();
    return const_iterator {this->buckets[location], node, location, this->bucket_size()};
}

/* public functions */
template <typename T, typename Hash, typename Allocator>
constexpr hash_table<T, Hash, Allocator>::hash_table(const Hash &hash) noexcept(
        is_nothrow_copy_constructible_v<Hash> and is_nothrow_default_constructible_v<node_allocator> and
        is_nothrow_default_constructible_v<bucket_allocator>) : buckets {{}, hash}, bucket_size {}, node_size {},
        loading_factor {1.2f} {}
template <typename T, typename Hash, typename Allocator>
constexpr hash_table<T, Hash, Allocator>::hash_table(const Allocator &) noexcept(
        is_nothrow_default_constructible_v<Hash> and is_nothrow_default_constructible_v<node_allocator> and
        is_nothrow_default_constructible_v<bucket_allocator>) : hash_table() {}
template <typename T, typename Hash, typename Allocator>
constexpr hash_table<T, Hash, Allocator>::hash_table(const Hash &hash, const Allocator &) noexcept(
        is_nothrow_copy_constructible_v<Hash> and is_nothrow_default_constructible_v<node_allocator> and
        is_nothrow_default_constructible_v<bucket_allocator>) : hash_table(hash) {}
template <typename T, typename Hash, typename Allocator>
constexpr hash_table<T, Hash, Allocator>::hash_table(size_type bucket_count, const Hash &hash,
        const Allocator &) : hash_table(hash) {
    this->rehash(bucket_count);
}
template <typename T, typename Hash, typename Allocator>
template <IsInputIterator InputIterator>
constexpr hash_table<T, Hash, Allocator>::hash_table(InputIterator begin, InputIterator end, const Hash &hash,
        const Allocator &) : hash_table(static_cast<size_type>(ds::distance(begin, end)), hash) {
    while(begin not_eq end) {
        this->emplace(ds::move_if<not is_forward_iterator_v<InputIterator>>(*begin++));
    }
}
template <typename T, typename Hash, typename Allocator>
constexpr hash_table<T, Hash, Allocator>::hash_table(initializer_list<T> init_list, const Hash &hash,
        const Allocator &) : hash_table(init_list.begin(), init_list.end(), hash) {}
template <typename T, typename Hash, typename Allocator>
constexpr hash_table<T, Hash, Allocator>::hash_table(const hash_table &rhs) : hash_table(rhs.cbegin(), rhs.cend()) {}
template <typename T, typename Hash, typename Allocator>
constexpr hash_table<T, Hash, Allocator>::hash_table(hash_table &&rhs) noexcept : buckets {ds::move(rhs.buckets)},
        bucket_size {ds::move(rhs.bucket_size)}, node_size {ds::move(rhs.node_size)},
        loading_factor {rhs.loading_factor} {
    rhs.buckets() = nullptr;
    rhs.bucket_size() = rhs.node_size() = 0;
}
template <typename T, typename Hash, typename Allocator>
constexpr hash_table<T, Hash, Allocator>::hash_table(const hash_table &rhs, const Hash &hash, const Allocator &) :
        hash_table(rhs.cbegin(), rhs.cend(), hash) {}
template <typename T, typename Hash, typename Allocator>
constexpr hash_table<T, Hash, Allocator>::hash_table(hash_table &&rhs, const Hash &hash, const Allocator &) noexcept :
        buckets {rhs.buckets(), hash}, bucket_size {ds::move(rhs.bucket_size)},
        node_size {ds::move(rhs.node_size)}, loading_factor {rhs.loading_factor} {
    rhs.buckets() = nullptr;
    rhs.bucket_size() = rhs.node_size() = 0;
}
template <typename T, typename Hash, typename Allocator>
constexpr hash_table<T, Hash, Allocator>::~hash_table() noexcept {
    for(size_type i {0}; i < this->node_size(); ++i) {
        for(auto cursor {*(this->buckets() + i)}; cursor; cursor = cursor->next) {
            ds::destroy(ds::address_of(cursor->value));
            this->node_size.allocator().deallocate(cursor, 1);
        }
    }
    this->bucket_size.allocator().deallocate(this->buckets());
}
template <typename T, typename Hash, typename Allocator>
constexpr hash_table<T, Hash, Allocator> &hash_table<T, Hash, Allocator>::operator=(const hash_table &rhs) {
    if(this not_eq &rhs) {
        this->assign(rhs.cbegin(), rhs.cend());
    }
    return *this;
}
template <typename T, typename Hash, typename Allocator>
constexpr hash_table<T, Hash, Allocator> &hash_table<T, Hash, Allocator>::operator=(hash_table &&rhs) noexcept {
    if(this not_eq &rhs) {
        this->~hash_table();
        this->buckets = ds::move(rhs.buckets);
        this->bucket_size = ds::move(rhs.bucket_size);
        this->node_size = ds::move(rhs.node_size);
        this->loading_factor = rhs.loading_factor;
        rhs.buckets() = nullptr;
        rhs.bucket_size() = rhs.node_size() = 0;
    }
    return *this;
}
template <typename T, typename Hash, typename Allocator>
constexpr hash_table<T, Hash, Allocator> &hash_table<T, Hash, Allocator>::operator=(initializer_list<T> init_list) {
    this->assign(init_list.begin(), init_list.end());
    return *this;
}
template <typename T, typename Hash, typename Allocator>
template <IsInputIterator InputIterator>
constexpr void hash_table<T, Hash, Allocator>::assign(InputIterator begin, InputIterator end) {
    for(size_type i {0}; i < this->node_size(); ++i) {
        for(auto cursor {*(this->buckets() + i)}; cursor; cursor = cursor->next) {
            ds::destroy(ds::address_of(cursor->value));
            this->node_size.allocator().deallocate(cursor, 1);
        }
    }
    this->bucket_size.allocator().deallocate(this->buckets());
    this->buckets() = nullptr;
    this->bucket_size() = this->node_size() = 0;
    this->rehash(static_cast<size_type>(ds::distance(begin, end)));
    while(begin not_eq end) {
        this->emplace(ds::move_if<not is_forward_iterator_v<InputIterator>>(*begin++));
    }
}
template <typename T, typename Hash, typename Allocator>
constexpr void hash_table<T, Hash, Allocator>::assign(initializer_list<T> init_list) {
    this->assign(init_list.begin(), init_list.end());
}
template <typename T, typename Hash, typename Allocator>
constexpr typename hash_table<T, Hash, Allocator>::const_iterator
hash_table<T, Hash, Allocator>::begin() noexcept {
    for(size_type i {0}; i < this->node_size(); ++i) {
        if(this->buckets[i]) {
            return const_iterator {this->buckets[i], *this->buckets[i], i, this->bucket_size()};
        }
    }
    return {};
}
template <typename T, typename Hash, typename Allocator>
constexpr typename hash_table<T, Hash, Allocator>::const_iterator
hash_table<T, Hash, Allocator>::begin() const noexcept {
    return const_cast<hash_table *>(this)->begin();
}
template <typename T, typename Hash, typename Allocator>
constexpr typename hash_table<T, Hash, Allocator>::const_iterator
hash_table<T, Hash, Allocator>::cbegin() const noexcept {
    return const_cast<hash_table *>(this)->begin();
}
template <typename T, typename Hash, typename Allocator>
constexpr typename hash_table<T, Hash, Allocator>::const_iterator
hash_table<T, Hash, Allocator>::end() noexcept {
    return {};
}
template <typename T, typename Hash, typename Allocator>
constexpr typename hash_table<T, Hash, Allocator>::const_iterator
hash_table<T, Hash, Allocator>::end() const noexcept {
    return {};
}
template <typename T, typename Hash, typename Allocator>
constexpr typename hash_table<T, Hash, Allocator>::const_iterator
hash_table<T, Hash, Allocator>::cend() const noexcept {
    return {};
}
template <typename T, typename Hash, typename Allocator>
constexpr typename hash_table<T, Hash, Allocator>::const_local_iterator
hash_table<T, Hash, Allocator>::begin(size_type location) noexcept {
    return const_local_iterator {*this->buckets[location]};
}
template <typename T, typename Hash, typename Allocator>
constexpr typename hash_table<T, Hash, Allocator>::const_local_iterator
hash_table<T, Hash, Allocator>::begin(size_type location) const noexcept {
    return const_local_iterator {*this->buckets[location]};
}
template <typename T, typename Hash, typename Allocator>
constexpr typename hash_table<T, Hash, Allocator>::const_local_iterator
hash_table<T, Hash, Allocator>::cbegin(size_type location) const noexcept {
    return const_local_iterator {*this->buckets[location]};
}
template <typename T, typename Hash, typename Allocator>
constexpr typename hash_table<T, Hash, Allocator>::const_local_iterator
hash_table<T, Hash, Allocator>::end(size_type location) noexcept {
    return {};
}
template <typename T, typename Hash, typename Allocator>
constexpr typename hash_table<T, Hash, Allocator>::const_local_iterator
hash_table<T, Hash, Allocator>::cend(size_type location) noexcept {
    return {};
}
template <typename T, typename Hash, typename Allocator>
constexpr typename hash_table<T, Hash, Allocator>::size_type
hash_table<T, Hash, Allocator>::size() const noexcept {
    return this->node_size();
}
template <typename T, typename Hash, typename Allocator>
constexpr typename hash_table<T, Hash, Allocator>::size_type
hash_table<T, Hash, Allocator>::bucket_count() const noexcept {
    return this->bucket_size();
}
template <typename T, typename Hash, typename Allocator>
constexpr float hash_table<T, Hash, Allocator>::load_factor() const noexcept {
    return this->loading_factor;
}
template <typename T, typename Hash, typename Allocator>
constexpr void hash_table<T, Hash, Allocator>::load_factor(float loading_factor) {
    if(this->node_size() / this->bucket_size() > (this->loading_factor = loading_factor)) {
        this->rehash(loading_factor * this->node_size());
    }
}
template <typename T, typename Hash, typename Allocator>
constexpr Hash hash_table<T, Hash, Allocator>::hash_function() const
        noexcept(is_nothrow_copy_constructible_v<Hash>) {
    return this->buckets.second();
}
template <typename T, typename Hash, typename Allocator>
constexpr Allocator hash_table<T, Hash, Allocator>::allocator() const
        noexcept(is_nothrow_default_constructible_v<Allocator>) {
    return {};
}
template <typename T, typename Hash, typename Allocator>
constexpr bool hash_table<T, Hash, Allocator>::empty() const noexcept {
    return this->node_size() == 0;
}
template <typename T, typename Hash, typename Allocator>
constexpr void hash_table<T, Hash, Allocator>::reserve(size_type n) {
    return this->rehash(n);
}

template <typename T, typename Hash, typename Allocator>
constexpr void hash_table<T, Hash, Allocator>::rehash(size_type bucket_count) {
    if(bucket_count > this->bucket_count()) {
        this->allocate_buckets(bucket_count);
    }
}
template <typename T, typename Hash, typename Allocator>
constexpr void hash_table<T, Hash, Allocator>::clear() noexcept {
    for(size_type i {0}; i < this->node_size(); ++i) {
        for(auto cursor {*(this->buckets() + i)}; cursor; cursor = cursor->next) {
            ds::destroy(ds::address_of(cursor->value));
            this->node_size.allocator().deallocate(cursor, 1);
        }
    }
    ds::memory_default_initialization(this->buckets(), this->bucket_size() * sizeof(__dsa::hash_table_node<T> *));
}
template <typename T, typename Hash, typename Allocator>
constexpr void hash_table<T, Hash, Allocator>::swap(hash_table &rhs) noexcept {
    ds::swap(this->buckets, rhs.buckets);
    ds::swap(this->bucket_size, rhs.bucket_size);
    ds::swap(this->node_size, rhs.node_size);
    ds::swap(this->loading_factor, rhs.loading_factor);
}
template <typename T, typename Hash, typename Allocator>
constexpr typename hash_table<T, Hash, Allocator>::const_iterator
hash_table<T, Hash, Allocator>::insert(const_reference value) {
    return this->emplace(value);
}
template <typename T, typename Hash, typename Allocator>
constexpr typename hash_table<T, Hash, Allocator>::const_iterator
hash_table<T, Hash, Allocator>::insert(rvalue_reference value) {
    return this->emplace(ds::move(value));
}
template <typename T, typename Hash, typename Allocator>
template <typename ...Args>
constexpr typename hash_table<T, Hash, Allocator>::const_iterator
hash_table<T, Hash, Allocator>::emplace(Args &&...args) {
    if(const auto new_node_size {this->node_size() + 1}; this->need_rehash(new_node_size)) {
        this->allocate_buckets(new_node_size);
    }
    return this->insert_node(this->allocate_node(ds::forward<Args>(args)...));
}
template <typename T, typename Hash, typename Allocator>
template <IsInputIterator InputIterator>
constexpr void hash_table<T, Hash, Allocator>::insert(InputIterator begin, InputIterator end) {
    if(const auto new_node_size {static_cast<size_type>(ds::distance(begin, end))}; this->need_rehash(new_node_size)) {
        this->allocate_buckets(new_node_size);
    }
    while(begin not_eq end) {
        this->insert_node(this->allocate_node(ds::move_if<not is_forward_iterator_v<InputIterator>>(*begin++)));
    }
}
template <typename T, typename Hash, typename Allocator>
constexpr void hash_table<T, Hash, Allocator>::insert(initializer_list<T> init_list) {
    this->insert(init_list.begin(), init_list.end());
}
template <typename T, typename Hash, typename Allocator>
constexpr typename hash_table<T, Hash, Allocator>::const_iterator
hash_table<T, Hash, Allocator>::erase(const_iterator pos) noexcept {
    auto result {pos};
    ++result;
    const auto location {this->constrain_hash(pos.node->hash)};
    if(this->buckets()[location] == pos.node) {
        this->buckets()[location] = pos.node->next;
    }else {
        for(auto cursor {pos.node};; cursor = cursor->next) {
            if(cursor->next == pos.node) {
                cursor->next = pos.node->next;
                break;
            }
        }
    }
    --this->node_size();
    ds::destroy(pos.operator->());
    this->node_size.allocator().deallocate(pos.node, 1);
    return result;
}
template <typename T, typename Hash, typename Allocator>
constexpr void hash_table<T, Hash, Allocator>::erase(const_iterator begin, const_iterator end) noexcept {
    while(begin not_eq end) {
        this->erase(begin++);
    }
}
template <typename T, typename Hash, typename Allocator>
constexpr void hash_table<T, Hash, Allocator>::remove(const_reference value)
        noexcept(is_nothrow_equal_to_comparable_v<const_reference>) {
    struct comparison_handler {
        __dsa::hash_table_node<T> *slow;
        __dsa::hash_table_node<T> *fast;
        constexpr void operator()() noexcept {
            this->slow->next = this->fast;
        }
    };
    const auto location {this->constrain_hash(this->buckets.second()(value))};
    auto trans {transaction {comparison_handler {}}};
    auto &slow {trans.get_rollback().slow};
    for(slow = this->buckets()[location]; slow;) {
        auto fast {slow->next};
        if(not fast) {
            break;
        }
        while(fast->value == value) {
            auto backup {fast};
            fast = fast->next;
            ds::destroy(ds::address_of(backup->value));
            this->node_size.allocator().deallocate(backup, 1);
            if(not fast) {
                break;
            }
        }
        slow->next = fast;
        slow = fast;
    }
    trans.complete();
    if(auto first_node {this->buckets()[location]}; first_node->value == value) {
        this->buckets()[location] = first_node->next;
        ds::destroy(ds::address_of(first_node->value));
        this->node_size.allocator().deallocate(first_node, 1);
    }
}
template <typename T, typename Hash, typename Allocator> template <typename UnaryPredicate>
constexpr void hash_table<T, Hash, Allocator>::remove_if(UnaryPredicate predicate)
        noexcept(is_nothrow_invocable_r_v<bool, UnaryPredicate, const_reference>) {
    for(auto it {this->cbegin()}; it not_eq this->cend(); ++it) {
        if(predicate(*it)) {
            this->erase(it);
        }
    }
}
template <typename T, typename Hash, typename Allocator>
constexpr void hash_table<T, Hash, Allocator>::unique() noexcept(is_nothrow_equal_to_comparable_v<const_reference>) {
    for(size_type i {0}; i < this->bucket_size(); ++i) {
        for(auto candidate {this->buckets()[i]}; candidate; candidate = candidate->next) {
            for(auto cursor {candidate->next}, linker {cursor}; cursor;) {
                if(candidate->value == cursor->value) {
                    auto backup {cursor};
                    cursor = cursor->next;
                    linker->next = cursor;
                    ds::destroy(ds::address_of(backup->value));
                    this->node_size.allocator().deallocate(backup, 1);
                }else {
                    linker = cursor;
                    cursor = cursor->next;
                }
            }
        }
    }
}
template <typename T, typename Hash, typename Allocator>
template <typename UnaryPredicate>
constexpr void hash_table<T, Hash, Allocator>::unique_if(UnaryPredicate predicate)
        noexcept(is_nothrow_invocable_r_v<bool, UnaryPredicate, const_reference>) {
    for(auto it {this->cbegin()}; it not_eq this->cend(); ++it) {
        if(predicate(*it)) {
            this->erase(it);
        }
    }
}
template <typename T, typename Hash, typename Allocator>
constexpr typename hash_table<T, Hash, Allocator>::const_iterator hash_table<T, Hash, Allocator>::find(
        const_reference value) const noexcept(is_nothrow_equal_to_comparable_v<const_reference>) {
    const auto location {this->constrain_hash(this->buckets.second()(value))};
    auto cursor {this->buckets()[location]};
    for(; cursor; cursor = cursor->next) {
        if(cursor->value == value) {
            return const_iterator {this->buckets() + location, cursor, location, this->bucket_size()};
        }
    }
    return this->cend();
}
template <typename T, typename Hash, typename Allocator>
template <typename UnaryPredicate>
constexpr typename hash_table<T, Hash, Allocator>::const_iterator hash_table<T, Hash, Allocator>::find_if(
        UnaryPredicate predicate) const noexcept(is_nothrow_invocable_r_v<bool, UnaryPredicate, const_reference>) {
    for(auto it {this->cbegin()}; it not_eq this->cend(); ++it) {
        if(predicate(*it)) {
            return it;
        }
    }
    return this->cend();
}
template <typename T, typename Hash, typename Allocator>
constexpr bool hash_table<T, Hash, Allocator>::contains(const_reference value) const
        noexcept(is_nothrow_equal_to_comparable_v<const_reference>) {
    const auto location {this->constrain_hash(this->buckets.second()(value))};
    auto cursor {this->buckets()[location]};
    for(; cursor; cursor = cursor->next) {
        if(cursor->value == value) {
            return true;
        }
    }
    return false;
}
template <typename T, typename Hash, typename Allocator>
template <typename UnaryPredicate>
constexpr bool hash_table<T, Hash, Allocator>::contains_if(UnaryPredicate predicate) const
        noexcept(is_nothrow_invocable_r_v<bool, UnaryPredicate, const_reference>) {
    for(auto it {this->cbegin()}; it not_eq this->cend(); ++it) {
        if(predicate(*it)) {
            return it;
        }
    }
    return this->cend();
}
template <typename T, typename Hash, typename Allocator>
constexpr typename hash_table<T, Hash, Allocator>::size_type hash_table<T, Hash, Allocator>::count(
        const_reference value) const noexcept(is_nothrow_equal_to_comparable_v<const_reference>) {
    size_type count {0};
    const auto location {this->constrain_hash(this->buckets.second()(value))};
    auto cursor {this->buckets()[location]};
    for(; cursor; cursor = cursor->next) {
        if(cursor->value == value) {
            ++count;
        }
    }
    return false;
}
template <typename T, typename Hash, typename Allocator>
template <typename UnaryPredicate>
constexpr typename hash_table<T, Hash, Allocator>::size_type hash_table<T, Hash, Allocator>::count_if(
        UnaryPredicate predicate) const noexcept(is_nothrow_invocable_r_v<bool, UnaryPredicate, const_reference>) {
    size_type count {0};
    for(auto it {this->cbegin()}; it not_eq this->cend(); ++it) {
        if(predicate(*it)) {
            ++count;
        }
    }
    return count;
}
template <typename T, typename Hash, typename Allocator>
constexpr void hash_table<T, Hash, Allocator>::merge(hash_table &rhs) noexcept {
    if(rhs.node_size() == 0) {
        return;
    }
    for(auto fast {rhs.cbegin()}, slow {fast++};; slow = fast, static_cast<void>(++fast)) {
        this->insert_node(slow.node);
    }
    ds::memory_default_initialization(rhs.buckets(), rhs.bucket_size() * sizeof(__dsa::hash_table_node<T> *));
}
template <typename T, typename Hash, typename Allocator>
constexpr void hash_table<T, Hash, Allocator>::merge(hash_table &&rhs) noexcept {
    this->merge(rhs);
}
__DATA_STRUCTURE_END(hash table implementation)

}       // namespace data_structure

#endif      // DATA_STRUCTURE_HASH_TABLE_HPP
