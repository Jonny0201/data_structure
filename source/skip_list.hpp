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

#ifndef DATA_STRUCTURE_SKIP_LIST_HPP
#define DATA_STRUCTURE_SKIP_LIST_HPP

#include "allocator.hpp"

namespace data_structure {

// Todo : make the default random engine and all member functions constexpr
__DATA_STRUCTURE_START(skip list declaration)
template <typename T, typename Compare = std::less<T>, typename RandomEngine = __dsa::skip_list_default_random_engine,
        typename Probability = __dsa::skip_list_default_probability, typename Allocator = allocator<T>>
class skip_list {
public:
    using allocator_type = Allocator;
    using size_type = typename Allocator::size_type;
    using difference_type = typename Allocator::difference_type;
    using comparator = Compare;
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
    struct allocation_handler;
    struct constructor_handler;
    struct comparison_handler;
private:
    __dsa::compressor<__dsa::skip_list_base_node<__dsa::skip_list_node<T>>,
            __dsa::compressor<Compare, __dsa::compressor<RandomEngine, Probability>>> head {};
    __dsa::allocator_compressor<size_type, __dsa::compressor<typename allocator_traits<Allocator>::template rebind<
            __dsa::skip_list_node<T>>, typename allocator_traits<Allocator>::template rebind<
            __dsa::skip_list_node<T> *>>> node_size {};
private:
    template <typename ...Args>
    __dsa::skip_list_node<T> *allocate(Args &&...);
    size_t generate_level() noexcept;
    void insert_a_node(__dsa::skip_list_node<T> *node) noexcept;
    template <bool, typename UnaryPredicate>
    iterator find_from(UnaryPredicate, __dsa::skip_list_base_node<T> *)
            noexcept(is_nothrow_invocable_r_v<bool, UnaryPredicate, const_reference>);
public:
    skip_list();
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
    skip_list(const skip_list &, const Compare &, const RandomEngine &, const Probability &, const Allocator &);
    skip_list(skip_list &&, const Compare &, const RandomEngine &, const Probability &, const Allocator &) noexcept;
    ~skip_list() noexcept;
public:
    skip_list &operator=(const skip_list &);
    skip_list &operator=(skip_list &&) noexcept;
    skip_list &operator=(initializer_list<T>);
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
    static constexpr const_iterator end() noexcept;
    [[nodiscard]]
    static constexpr const_iterator cend() noexcept;
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
    static constexpr Allocator allocator() noexcept;
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
    const_iterator erase(size_type, size_type = 1) noexcept;
    const_iterator erase_after(const_iterator, size_type) noexcept;
    const_iterator erase_after(const_iterator) noexcept;
    const_iterator erase_after(const_iterator, const_iterator) noexcept;
public:
    size_type remove(const_reference) noexcept(is_nothrow_equal_to_comparable_v<const_reference>);
    template <typename UnaryPredicate>
    size_type remove_if(UnaryPredicate) noexcept(is_nothrow_invocable_r_v<bool, UnaryPredicate, const_reference>);
    void unique() noexcept(is_nothrow_equal_to_comparable_v<const_reference>);
    template <typename BinaryPredicate>
    void unique_if(BinaryPredicate) noexcept(is_nothrow_invocable_r_v<bool, BinaryPredicate,
            const_reference, const_reference>);
    template <bool = false>
    [[nodiscard]]
    const_iterator find(const_reference) const noexcept(is_nothrow_equal_to_comparable_v<const_reference>);
    template <bool = false, typename UnaryPredicate>
    [[nodiscard]]
    const_iterator find_if(UnaryPredicate) const
            noexcept(is_nothrow_invocable_r_v<bool, UnaryPredicate, const_reference>);
    [[nodiscard]]
    bool contains(const_reference) const noexcept(is_nothrow_equal_to_comparable_v<const_reference>);
    template <typename UnaryPredicate>
    [[nodiscard]]
    bool contains_if(UnaryPredicate) const noexcept(is_nothrow_invocable_r_v<bool, UnaryPredicate, const_reference>);
    [[nodiscard]]
    bool contains_range(const_reference, const_reference) const
            noexcept(is_nothrow_equal_to_comparable_v<const_reference>);
    [[nodiscard]]
    size_type count(const_reference) const noexcept(is_nothrow_equal_to_comparable_v<const_reference>);
    template <typename UnaryPredicate>
    [[nodiscard]]
    size_type count_if(UnaryPredicate) const noexcept(is_nothrow_invocable_r_v<bool, UnaryPredicate, const_reference>);
};
__DATA_STRUCTURE_END(skip list declaration)

__DATA_STRUCTURE_START(skip list implementation)
/* exceptional handler */
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
struct skip_list<T, Compare, RandomEngine, Probability, Allocator>::allocation_handler {
    __dsa::skip_list_node<T> *node;
    typename allocator_traits<Allocator>::template rebind<__dsa::skip_list_node<T>> &node_allocator;
    typename allocator_traits<Allocator>::template rebind<__dsa::skip_list_node<T> *> &next_allocator;
    bool last_next_allocation_done {};
    constexpr allocation_handler(__dsa::skip_list_node<T> *node,
            typename allocator_traits<Allocator>::template rebind<__dsa::skip_list_node<T>> &node_allocator,
            typename allocator_traits<Allocator>::template rebind<__dsa::skip_list_node<T> *> &next_allocator) :
            node {node}, node_allocator {node_allocator}, next_allocator {next_allocator} {}
    constexpr void operator()() noexcept {
        if(this->last_next_allocation_done) {
            this->next_allocator.deallocate(this->node->next);
        }
        this->node_allocator.deallocate(this->node);
    }
};
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
struct skip_list<T, Compare, RandomEngine, Probability, Allocator>::constructor_handler {
    __dsa::skip_list_base_node<T> *first;
    typename allocator_traits<Allocator>::template rebind<__dsa::skip_list_node<T>> &node_allocator;
    typename allocator_traits<Allocator>::template rebind<__dsa::skip_list_node<T> *> &next_allocator;
    constexpr constructor_handler(__dsa::skip_list_node<T> *first,
            typename allocator_traits<Allocator>::template rebind<__dsa::skip_list_node<T>> &node_allocator,
            typename allocator_traits<Allocator>::template rebind<__dsa::skip_list_node<T> *> &next_allocator) :
            first {first}, node_allocator {node_allocator}, next_allocator {next_allocator} {}
    constexpr void operator()() noexcept {
        for(auto cursor {this->first->next[0]}; cursor;) {
            auto backup {cursor};
            cursor = this->first->next[0];
            ds::destroy(ds::address_of(backup->value()));
            this->next_allocator.deallocate(backup->next);
            this->node_allocator.deallocate(backup);
        }
        this->next_allocator.deallocate(this->first->next);
    }
};
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
struct skip_list<T, Compare, RandomEngine, Probability, Allocator>::comparison_handler {
    __dsa::skip_list_node<T> *node;
    typename allocator_traits<Allocator>::template rebind<__dsa::skip_list_node<T>> &node_allocator;
    typename allocator_traits<Allocator>::template rebind<__dsa::skip_list_node<T> *> &next_allocator;
    constexpr comparison_handler(__dsa::skip_list_node<T> *node,
            typename allocator_traits<Allocator>::template rebind<__dsa::skip_list_node<T>> &node_allocator,
            typename allocator_traits<Allocator>::template rebind<__dsa::skip_list_node<T> *> &next_allocator) :
            node {node}, node_allocator {node_allocator}, next_allocator {next_allocator} {}
    constexpr void operator()() noexcept {
        ds::destroy(ds::address_of(this->node->value));
        this->next_allocator.deallocate(this->node->next);
        this->node_allocator.deallocate(this->node);
    }
};

/* private functions */
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
template <typename ...Args>
__dsa::skip_list_node<T> *skip_list<T, Compare, RandomEngine, Probability, Allocator>::allocate(Args &&...args) {
    auto &allocators {this->node_size.allocator()};
    auto &node_allocator {allocators.first()};
    auto &next_allocator {allocators.second()};
    const auto level {this->generate_level()};
    const auto result {node_allocator.allocate(1)};
    auto trans {transaction {allocation_handler {result, node_allocator, next_allocator}}};
    result->next = next_allocator.allocate(result->level = level);
    trans.get_rollback().last_next_allocation_done = true;
    ds::construct(ds::address_of(result->value), ds::forward<Args>(args)...);
    trans.complete();
    return result;
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
size_t skip_list<T, Compare, RandomEngine, Probability, Allocator>::generate_level() noexcept {
    auto level {1uz};
    auto &random {this->head.second().second().first()};
    auto &probability {this->head.second().second().second()};
    auto &head {this->head.first()};
    const auto max_level {head.level + 1};
    for(auto upgrade {random() <= probability()}; upgrade; upgrade = (random() <= probability())) {
        if(++level == max_level) {
            auto &next_allocator {this->node_size.allocator().second()};
            auto new_next {next_allocator.allocate(level)};
            ds::memory_copy(new_next, head.next, head.level);
            new_next[head.level++] = nullptr;
            next_allocator.deallocate(head.next);
            head.next = new_next;
            break;
        }
    }
    return level;
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
void skip_list<T, Compare, RandomEngine, Probability, Allocator>::insert_a_node(
        __dsa::skip_list_node<T> *node) noexcept {
    auto trans {transaction {comparison_handler {node, this->node_size.allocator().first(),
            this->node_size.allocator().second()}}};
    auto cursor {&this->head.first()};
    for(auto i {node->level};; --i) {
        for(; cursor->next[i] and compare(node->value, cursor->next[i]->value()); cursor = cursor->next[i]);
        node->next[i] = cursor->next[i];
        cursor->next[i] = node;
        if(i == 0) {
            break;
        }
    }
    trans.complete();
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
template <bool ReturnBefore, typename UnaryPredicate>
typename skip_list<T, Compare, RandomEngine, Probability, Allocator>::iterator
skip_list<T, Compare, RandomEngine, Probability, Allocator>::find_from(UnaryPredicate predicate,
        __dsa::skip_list_base_node<T> *from) noexcept(is_nothrow_invocable_r_v<bool, UnaryPredicate, const_reference>) {
    // Todo : confirm the relationship between the level and the searching start node
    auto level {from->level - 1};
    while(true) {
        for(; not from->next[level]; --level) {
            if(level == 0) {
                return this->cend();
            }
        }
        if(predicate(from->next[level])) {
            from = from->next[level];
        }else {
            break;
        }
    }
    if constexpr(ReturnBefore) {
        return const_iterator {from, 0};
    }
    return const_iterator {from->next[level], 0};
}

/* public functions */
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
skip_list<T, Compare, RandomEngine, Probability, Allocator>::skip_list() : head {}, node_size {} {
    this->head.first().next = this->node_size.allocator().second().allocate(1);
    this->head.first().level = 1;
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
skip_list<T, Compare, RandomEngine, Probability, Allocator>::skip_list(const Compare &compare) :
        head {{}, {compare, {}}}, node_size {} {
    this->head.first().next = this->node_size.allocator().second().allocate(1);
    this->head.first().level = 1;
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
skip_list<T, Compare, RandomEngine, Probability, Allocator>::skip_list(const RandomEngine &random_engine) :
        head {{}, {{}, {random_engine}}}, node_size {} {
    this->head.first().next = this->node_size.allocator().second().allocate(1);
    this->head.first().level = 1;
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
skip_list<T, Compare, RandomEngine, Probability, Allocator>::skip_list(const Probability &probability) :
        head {{}, {{}, {probability}}}, node_size {} {
    this->head.first().next = this->node_size.allocator().second().allocate(1);
    this->head.first().level = 1;
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
skip_list<T, Compare, RandomEngine, Probability, Allocator>::skip_list(const Allocator &) : skip_list() {}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
skip_list<T, Compare, RandomEngine, Probability, Allocator>::skip_list(const Compare &compare,
        const RandomEngine &random_engine, const Probability &probability, const Allocator &allocator) :
        head {{}, {compare, {random_engine, probability}}}, node_size {} {
    this->head.first().next = this->node_size.allocator().second().allocate(1);
    this->head.first().level = 1;
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
skip_list<T, Compare, RandomEngine, Probability, Allocator>::skip_list(size_type n, const Compare &compare,
        const RandomEngine &random_engine, const Probability &probability, const Allocator &allocator) :
        head {{}, {compare, {random_engine, probability}}}, node_size {} {
    this->head.first().next = this->node_size.allocator().second().allocate(1);
    this->head.first().level = 1;
    auto &allocators {this->node_size.allocator()};
    auto trans {transaction {constructor_handler {this->head.first(), allocators.first(), allocator.second()}}};
    for(; n not_eq 0; --n) {
        this->emplace();
    }
    trans.complete();
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
skip_list<T, Compare, RandomEngine, Probability, Allocator>::skip_list(size_type n, const_reference value,
        const Compare &compare, const RandomEngine &random_engine, const Probability &probability,
        const Allocator &allocator) : head {{}, {compare, {random_engine, probability}}}, node_size {} {
    this->head.first().next = this->node_size.allocator().second().allocate(1);
    this->head.first().level = 1;
    auto &allocators {this->node_size.allocator()};
    auto trans {transaction {constructor_handler {this->head.first(), allocators.first(), allocator.second()}}};
    for(; n not_eq 0; --n) {
        this->emplace(value);
    }
    trans.complete();
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
template <IsInputIterator InputIterator>
skip_list<T, Compare, RandomEngine, Probability, Allocator>::skip_list(InputIterator begin, InputIterator end,
        const Compare &compare, const RandomEngine &random_engine, const Probability &probability,
        const Allocator &allocator) : head {{}, {compare, {random_engine, probability}}}, node_size {} {
    this->head.first().next = this->node_size.allocator().second().allocate(1);
    this->head.first().level = 1;
    auto &allocators {this->node_size.allocator()};
    auto trans {transaction {constructor_handler {this->head.first(), allocators.first(), allocator.second()}}};
    while(begin not_eq end) {
        this->emplace(ds::move_if<not is_forward_iterator_v<InputIterator>>(*begin++));
    }
    trans.complete();
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
skip_list<T, Compare, RandomEngine, Probability, Allocator>::skip_list(initializer_list<T> init_list,
        const Compare &compare, const RandomEngine &random_engine, const Probability &probability,
        const Allocator &allocator) : skip_list(init_list.begin(), init_list.end(), compare,
        random_engine, probability, allocator) {}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
skip_list<T, Compare, RandomEngine, Probability, Allocator>::skip_list(const skip_list &rhs) :
        skip_list(rhs.cbegin(), rhs.cend(), rhs.compare(), rhs.random_engine(), rhs.probability()) {}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
skip_list<T, Compare, RandomEngine, Probability, Allocator>::skip_list(skip_list &&rhs) noexcept :
        head {ds::move(rhs.head)}, node_size {ds::move(rhs.node_size)} {
    auto &head {rhs.head.first()};
    for(auto i {0}; i < head.level; ++i) {
        rhs.head.next[i] = nullptr;
    }
    rhs.node_size() = 0;
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
skip_list<T, Compare, RandomEngine, Probability, Allocator>::skip_list(const skip_list &rhs,
        const Compare &compare, const RandomEngine &random_engine, const Probability &probability,
        const Allocator &allocator) : skip_list(rhs.cbegin(), rhs.cend(), compare, random_engine,
        probability, allocator) {}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
skip_list<T, Compare, RandomEngine, Probability, Allocator>::skip_list(skip_list &&rhs,
        const Compare &compare, const RandomEngine &random_engine, const Probability &probability,
        const Allocator &allocator) noexcept : head {ds::move(rhs.head.first()),
                {compare, {random_engine,probability}}}, node_size {ds::move(rhs.node_size()), {}} {
    auto &head {rhs.head.first()};
    for(auto i {0}; i < head.level; ++i) {
        rhs.head.next[i] = nullptr;
    }
    rhs.node_size() = 0;
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
skip_list<T, Compare, RandomEngine, Probability, Allocator>::~skip_list() noexcept {
    auto &head {this->head.first()};
    auto &node_allocator {this->node_size.allocator().first()};
    auto &next_allocator {this->node_size.allocator().second()};
    for(auto cursor {head.next[0]}; cursor;) {
        auto backup {cursor};
        cursor = backup->next[0];
        ds::destroy(ds::address_of(backup->value()));
        next_allocator.deallocate(backup->next);
        node_allocator.deallocate(backup);
    }
    next_allocator.deallocate(head.next);
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
skip_list<T, Compare, RandomEngine, Probability, Allocator> &
skip_list<T, Compare, RandomEngine, Probability, Allocator>::operator=(const skip_list &rhs) {
    if(this not_eq &rhs) {
        this->assign(rhs.cbegin(), rhs.cend());
    }
    return *this;
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
skip_list<T, Compare, RandomEngine, Probability, Allocator> &
skip_list<T, Compare, RandomEngine, Probability, Allocator>::operator=(skip_list &&rhs) noexcept {
    if(this not_eq &rhs) {
        this->~skip_list();
        this->head = ds::move(rhs.head);
        this->node_size = ds::move(rhs.node_size);
    }
    return *this;
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
skip_list<T, Compare, RandomEngine, Probability, Allocator> &
skip_list<T, Compare, RandomEngine, Probability, Allocator>::operator=(initializer_list<T> init_list) {
    this->assign(init_list.begin(), init_list.end());
    return *this;
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
void skip_list<T, Compare, RandomEngine, Probability, Allocator>::assign(size_type n, const_reference value) {
    this->clear();
    for(; n not_eq 0; --n) {
        this->emplace(value);
    }
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
template <IsInputIterator InputIterator>
void skip_list<T, Compare, RandomEngine, Probability, Allocator>::assign(InputIterator begin, InputIterator end) {
    this->clear();
    while(begin not_eq end) {
        this->emplace(ds::move_if<not is_forward_iterator_v<InputIterator>>(*begin++));
    }
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
void skip_list<T, Compare, RandomEngine, Probability, Allocator>::assign(initializer_list<T> init_list) {
    this->assign(init_list.begin(), init_list.end());
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
typename skip_list<T, Compare, RandomEngine, Probability, Allocator>::const_iterator
skip_list<T, Compare, RandomEngine, Probability, Allocator>::before_begin() const noexcept {
    return const_iterator {this->head.first().node(), 0};
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
typename skip_list<T, Compare, RandomEngine, Probability, Allocator>::const_iterator
skip_list<T, Compare, RandomEngine, Probability, Allocator>::cbefore_begin() const noexcept {
    return const_iterator {this->head.first().node(), 0};
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
typename skip_list<T, Compare, RandomEngine, Probability, Allocator>::const_iterator
skip_list<T, Compare, RandomEngine, Probability, Allocator>::begin() const noexcept {
    return const_iterator {this->head.first().next->node(), 0};
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
typename skip_list<T, Compare, RandomEngine, Probability, Allocator>::const_iterator
skip_list<T, Compare, RandomEngine, Probability, Allocator>::cbegin() const noexcept {
    return const_iterator {this->head.first().next->node(), 0};
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
constexpr typename skip_list<T, Compare, RandomEngine, Probability, Allocator>::const_iterator
skip_list<T, Compare, RandomEngine, Probability, Allocator>::end() noexcept {
    return {};
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
constexpr typename skip_list<T, Compare, RandomEngine, Probability, Allocator>::const_iterator
skip_list<T, Compare, RandomEngine, Probability, Allocator>::cend() noexcept {
    return {};
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
typename skip_list<T, Compare, RandomEngine, Probability, Allocator>::const_iterator
skip_list<T, Compare, RandomEngine, Probability, Allocator>::level_before_begin(size_t level) const noexcept {
    return const_iterator {this->head.first().node(), level};
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
typename skip_list<T, Compare, RandomEngine, Probability, Allocator>::const_iterator
skip_list<T, Compare, RandomEngine, Probability, Allocator>::level_cbefore_begin(size_t level) const noexcept {
    return const_iterator {this->head.first().node(), level};
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
bool skip_list<T, Compare, RandomEngine, Probability, Allocator>::empty() const noexcept {
    return this->head.first().next[0] == nullptr;
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
typename skip_list<T, Compare, RandomEngine, Probability, Allocator>::size_type
skip_list<T, Compare, RandomEngine, Probability, Allocator>::size() const noexcept {
    return this->node_size();
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
size_t skip_list<T, Compare, RandomEngine, Probability, Allocator>::max_level() const noexcept {
    return this->head.first().level;
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
typename skip_list<T, Compare, RandomEngine, Probability, Allocator>::const_reference
skip_list<T, Compare, RandomEngine, Probability, Allocator>::front() const noexcept {
    return this->head.first().next[0]->value();
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
Compare skip_list<T, Compare, RandomEngine, Probability, Allocator>::compare() const noexcept {
    return this->head.second().first();
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
RandomEngine skip_list<T, Compare, RandomEngine, Probability, Allocator>::random_engine() const noexcept {
    return this->head.second().second().first();
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
Probability skip_list<T, Compare, RandomEngine, Probability, Allocator>::probability() const noexcept {
    return this->head.second().second().second();
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
constexpr Allocator skip_list<T, Compare, RandomEngine, Probability, Allocator>::allocator() noexcept {
    return {};
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
void skip_list<T, Compare, RandomEngine, Probability, Allocator>::clear() noexcept {
    auto &head {this->head.first()};
    auto &node_allocator {this->node_size.allocator().first()};
    auto &next_allocator {this->node_size.allocator().second()};
    for(auto cursor {head.next[0]}; cursor;) {
        auto backup {cursor};
        cursor = backup->next[0];
        ds::destroy(ds::address_of(backup->value()));
        next_allocator.deallocate(backup->next);
        node_allocator.deallocate(backup);
    }
    for(auto i {0}; i < head.level; ++i) {
        head.next[i] = nullptr;
    }
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
void skip_list<T, Compare, RandomEngine, Probability, Allocator>::swap(skip_list &rhs) noexcept {
    ds::swap(this->head, rhs.head);
    ds::swap(this->node_size, rhs.node_size);
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
void skip_list<T, Compare, RandomEngine, Probability, Allocator>::pop_front() noexcept {
    this->erase_after(this->cbefore_begin());
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
typename skip_list<T, Compare, RandomEngine, Probability, Allocator>::iterator
skip_list<T, Compare, RandomEngine, Probability, Allocator>::insert(size_type n, const_reference value) {
    if(n == 0) {
        return this->end();
    }
    while(true) {
        if(n not_eq 1) {
            this->emplace(value);
        }else {
            return this->emplace(value);
        }
        --n;
    }
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
typename skip_list<T, Compare, RandomEngine, Probability, Allocator>::iterator
skip_list<T, Compare, RandomEngine, Probability, Allocator>::insert(rvalue_reference value) {
    return this->emplace(ds::move(value));
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
template <typename ...Args>
typename skip_list<T, Compare, RandomEngine, Probability, Allocator>::iterator
skip_list<T, Compare, RandomEngine, Probability, Allocator>::emplace(Args &&...args) {
    const auto result {this->allocate(ds::forward<Args>(args)...)};
    auto &compare {this->head.second().first()};
    auto trans {transaction {comparison_handler {result, this->node_size.allocator().first(),
            this->node_size.allocator().second()}}};
    auto cursor {&this->head.first()};
    for(auto i {result->level};; --i) {
        for(; cursor->next[i] and compare(result->value, cursor->next[i]->value()); cursor = cursor->next[i]);
        result->next[i] = cursor->next[i];
        cursor->next[i] = result;
        if(i == 0) {
            break;
        }
    }
    trans.complete();
    ++this->node_size();
    return iterator {result, 0};
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
template <IsInputIterator InputIterator>
typename skip_list<T, Compare, RandomEngine, Probability, Allocator>::iterator
skip_list<T, Compare, RandomEngine, Probability, Allocator>::insert(InputIterator begin, InputIterator end) {
    if(begin == end) {
        return this->end();
    }
    const auto result {this->emplace(ds::move_if<not is_forward_iterator_v<InputIterator>>(*begin++))};
    while(begin not_eq end) {
        this->emplace(ds::move_if<not is_forward_iterator_v<InputIterator>>(*begin++));
    }
    return result;
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
typename skip_list<T, Compare, RandomEngine, Probability, Allocator>::iterator
skip_list<T, Compare, RandomEngine, Probability, Allocator>::insert(initializer_list<T> init_list) {
    return this->insert(init_list.begin(), init_list.end());
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
typename skip_list<T, Compare, RandomEngine, Probability, Allocator>::iterator
skip_list<T, Compare, RandomEngine, Probability, Allocator>::erase(size_type pos, size_type n) noexcept {
    const auto begin {this->cbefore_begin()};
    for(; pos not_eq 0; --pos, static_cast<void>(++begin));
    return this->erase_after(begin, n);
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
typename skip_list<T, Compare, RandomEngine, Probability, Allocator>::iterator
skip_list<T, Compare, RandomEngine, Probability, Allocator>::erase_after(const_iterator begin, size_type n) noexcept {
    if(n == 0) {
        return iterator {begin.node, 0};
    }
    for(; n not_eq 1; --n, static_cast<void>(++begin)) {
        this->erase_after(begin);
    }
    return this->erase_after(begin);
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
typename skip_list<T, Compare, RandomEngine, Probability, Allocator>::iterator
skip_list<T, Compare, RandomEngine, Probability, Allocator>::erase_after(const_iterator pos) noexcept {
    for(auto i {0}; i < pos.node->level; ++i) {
        pos.node->next[i] = pos.node->next[i]->next[i];
    }
    const auto result {pos.node->next[0]};
    ds::destroy(ds::address_of(pos.node->value()));
    this->node_size.allocator().second().deallocate(pos.node->next);
    this->node_size.allocator().first().deallocate(pos.node);
    --this->node_size();
    return iterator {result, 0};
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
typename skip_list<T, Compare, RandomEngine, Probability, Allocator>::iterator
skip_list<T, Compare, RandomEngine, Probability, Allocator>::erase_after(const_iterator begin,
        const_iterator end) noexcept {
    if(begin == end) {
        return iterator {begin.node, 0};
    }
    while(begin not_eq end) {
        this->erase_after(begin++);
    }
    return iterator {end.node, 0};
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
typename skip_list<T, Compare, RandomEngine, Probability, Allocator>::size_type
skip_list<T, Compare, RandomEngine, Probability, Allocator>::remove(const_reference value)
        noexcept(is_nothrow_equal_to_comparable_v<const_reference>) {
    return this->remove([&value](const_reference candidate)
            noexcept(is_nothrow_equal_to_comparable_v<const_reference>) {
        return value == candidate;
    });
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
template <typename UnaryPredicate>
typename skip_list<T, Compare, RandomEngine, Probability, Allocator>::size_type
skip_list<T, Compare, RandomEngine, Probability, Allocator>::remove_if(UnaryPredicate predicate)
        noexcept(is_nothrow_invocable_r_v<bool, UnaryPredicate, const_reference>) {
    size_type count {0};
    auto result {this->find_from<true, add_lvalue_reference_t<UnaryPredicate>>(predicate, &this->head.first())};
    for(; result.node not_eq nullptr; ++count) {
        this->erase_after(result);
        result = this->find_from<true, add_lvalue_reference_t<UnaryPredicate>>(predicate, result.node);
    }
    return count;
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
void skip_list<T, Compare, RandomEngine, Probability, Allocator>::unique()
        noexcept(is_nothrow_equal_to_comparable_v<const_reference>) {
    this->unique([](const_reference lhs, const_reference rhs)
                noexcept(is_nothrow_equal_to_comparable_v<const_reference>) {
        return lhs == rhs;
    });
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
template <typename BinaryPredicate>
void skip_list<T, Compare, RandomEngine, Probability, Allocator>::unique_if(BinaryPredicate predicate)
        noexcept(is_nothrow_invocable_r_v<bool, BinaryPredicate, const_reference, const_reference>) {
    auto slow {this->cbegin()};
    if(not slow) {
        return;
    }
    auto fast {slow};
    for(++fast; fast;) {
        if(predicate(*slow, *fast)) {
            fast = this->erase_after(slow);
        }else {
            ++slow;
            ++fast;
        }
    }
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
template <bool ReturnBefore>
typename skip_list<T, Compare, RandomEngine, Probability, Allocator>::const_iterator
skip_list<T, Compare, RandomEngine, Probability, Allocator>::find(const_reference value) const
        noexcept(is_nothrow_equal_to_comparable_v<const_reference>) {
    return this->find_if<ReturnBefore>([&value](const_reference candidate)
            noexcept(is_nothrow_equal_to_comparable_v<const_reference>) {
        return value == candidate;
    });
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
template <bool ReturnBefore, typename UnaryPredicate>
typename skip_list<T, Compare, RandomEngine, Probability, Allocator>::const_iterator
skip_list<T, Compare, RandomEngine, Probability, Allocator>::find_if(UnaryPredicate predicate) const
        noexcept(is_nothrow_invocable_r_v<bool, UnaryPredicate, const_reference>) {
    return this->find_from<ReturnBefore, add_lvalue_reference_t<UnaryPredicate>>(predicate, &this->head.first());
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
bool skip_list<T, Compare, RandomEngine, Probability, Allocator>::contains(const_reference value) const
        noexcept(is_nothrow_equal_to_comparable_v<const_reference>) {
    return this->contains([&value](const_reference candidate) {
        return value == candidate;
    });
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
template <typename UnaryPredicate>
bool skip_list<T, Compare, RandomEngine, Probability, Allocator>::contains_if(UnaryPredicate predicate) const
        noexcept(is_nothrow_invocable_r_v<bool, UnaryPredicate, const_reference>) {
    return this->find_from<false, add_lvalue_reference_t<UnaryPredicate>>(predicate,
            &this->head.first()) not_eq this->cend();
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
bool skip_list<T, Compare, RandomEngine, Probability, Allocator>::contains_range(const_reference from,
        const_reference to) const noexcept(is_nothrow_equal_to_comparable_v<const_reference>) {
    auto &compare {this->head.second().first()};
    const auto it {this->find_from<false>([&from, &compare](const_reference value)
            noexcept(is_nothrow_invocable_r_v<bool, Compare, const_reference, const_reference>) {
        return not compare(value, from);
    }, &this->head.first())};
    if(it == this->cend()) {
        return false;
    }
    return this->find_from<false>([&to, &compare](const_reference value)
            noexcept(is_nothrow_invocable_r_v<bool, Compare, const_reference, const_reference>) {
        return compare(to, value);
    }) not_eq this->cend();
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
typename skip_list<T, Compare, RandomEngine, Probability, Allocator>::size_type
skip_list<T, Compare, RandomEngine, Probability, Allocator>::count(const_reference value) const
        noexcept(is_nothrow_equal_to_comparable_v<const_reference>) {
    auto cursor {this->find_from<false>([&value](const_reference candidate)
            noexcept(is_nothrow_equal_to_comparable_v<const_reference>) {
        return value == candidate;
    }, &this->head.first())};
    if(cursor not_eq this->cend()) {
        size_type count {1};
        for(++cursor; *cursor == value; ++count, static_cast<void>(++cursor));
        return count;
    }
    return 0;
}
template <typename T, typename Compare, typename RandomEngine, typename Probability, typename Allocator>
template <typename UnaryPredicate>
typename skip_list<T, Compare, RandomEngine, Probability, Allocator>::size_type
skip_list<T, Compare, RandomEngine, Probability, Allocator>::count_if(UnaryPredicate predicate) const
        noexcept(is_nothrow_invocable_r_v<bool, UnaryPredicate, const_reference>) {
    size_type count {0};
    for(const auto &value : *this) {
        if(predicate(value)) {
            ++count;
        }
    }
    return count;
}
__DATA_STRUCTURE_END(skip list implementation)

}       // namespace data_structure

#endif      // DATA_STRUCTURE_SKIP_LIST_HPP
