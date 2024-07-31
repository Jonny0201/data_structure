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

#ifndef DATA_STRUCTURE_FORWARD_LIST_HPP
#define DATA_STRUCTURE_FORWARD_LIST_HPP

#include "buffer.hpp"

namespace data_structure {

__DATA_STRUCTURE_START(forward_list declaration)
template <typename T, typename Allocator = allocator<T>>
class forward_list {
private:
    using node_type = __dsa::forward_list_node<T> *;
    using real_allocator = __dsa::node_allocator<T, __dsa::forward_list_node, Allocator>;
public:
    using allocator_type = Allocator;
    using size_type = typename Allocator::size_type;
    using difference_type = typename Allocator::difference_type;
    using value_type = T;
    using reference = typename allocator_traits<Allocator>::reference;
    using const_reference = typename allocator_traits<Allocator>::const_reference;
    using rvalue_reference = typename allocator_traits<Allocator>::rvalue_reference;
    using pointer = typename allocator_traits<Allocator>::pointer;
    using const_pointer = typename allocator_traits<Allocator>::const_pointer;
    using iterator = __dsa::forward_list_iterator<T>;
    using const_iterator = __dsa::forward_list_iterator<T, true>;
    static_assert(is_same_v<T, typename Allocator::value_type>,
                  "The value type of forward_list should same as the allocator's value_type!");
private:
    struct linked_allocation_handler;
private:
    __dsa::forward_list_base_node<__dsa::forward_list_node<T>> head {};
    __dsa::allocator_compressor<size_type, real_allocator> node_size {};
private:
    template <bool = true>
    constexpr node_type allocate_n(size_type, const_reference = {}, node_type = {});
    template <bool = false, typename Iterator>
    constexpr node_type allocate_n(Iterator, Iterator, node_type = {});
    template <typename ...Args>
    constexpr node_type allocate_1(node_type, Args &&...);
    constexpr void deallocate_nodes(node_type, node_type) noexcept;
    constexpr void deallocate_nodes(node_type, size_type) noexcept;
public:
    constexpr forward_list() = default;
    explicit constexpr forward_list(const Allocator &)
            noexcept(is_nothrow_constructible_v<real_allocator, const Allocator &>);
    explicit constexpr forward_list(size_type, const Allocator & = {});
    constexpr forward_list(size_type, const_reference, const Allocator & = {});
    template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
    constexpr forward_list(InputIterator, InputIterator, const Allocator & = {}, size_type = 64);
    template <IsForwardIterator ForwardIterator>
    constexpr forward_list(ForwardIterator, ForwardIterator, const Allocator & = {});
    constexpr forward_list(initializer_list<T>, const Allocator & = {});
    constexpr forward_list(const forward_list &);
    constexpr forward_list(const forward_list &, const Allocator &);
    constexpr forward_list(forward_list &&) noexcept;
    constexpr forward_list(forward_list &&, const Allocator &) noexcept;
    constexpr ~forward_list() noexcept;
public:
    constexpr forward_list &operator=(const forward_list &);
    constexpr forward_list &operator=(forward_list &&) noexcept;
    constexpr forward_list &operator=(initializer_list<T>);
public:
    constexpr void assign(size_type, const_reference = {});
    template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
    constexpr void assign(InputIterator, InputIterator, size_type = 64);
    template <IsForwardIterator ForwardIterator>
    constexpr void assign(ForwardIterator, ForwardIterator);
    constexpr void assign(initializer_list<T>);
    [[nodiscard]]
    constexpr iterator before_begin() noexcept;
    [[nodiscard]]
    constexpr const_iterator before_begin() const noexcept;
    [[nodiscard]]
    constexpr const_iterator cbefore_begin() const noexcept;
    [[nodiscard]]
    constexpr iterator begin() noexcept;
    [[nodiscard]]
    constexpr const_iterator begin() const noexcept;
    [[nodiscard]]
    constexpr const_iterator cbegin() const noexcept;
    [[nodiscard]]
    constexpr iterator end() noexcept;
    [[nodiscard]]
    constexpr const_iterator end() const noexcept;
    [[nodiscard]]
    constexpr const_iterator cend() const noexcept;
    [[nodiscard]]
    constexpr size_type size() const noexcept;
    [[nodiscard]]
    constexpr bool empty() const noexcept;
    constexpr void resize(size_type);
    constexpr void resize(size_type, const_reference);
    [[nodiscard]]
    constexpr reference front() noexcept;
    [[nodiscard]]
    constexpr const_reference front() const noexcept;
    [[nodiscard]]
    constexpr Allocator allocator() const noexcept;
    constexpr void push_front(const_reference);
    constexpr void push_front(rvalue_reference);
    template <typename ...Args>
    constexpr void emplace_front(Args &&...);
    constexpr void pop_front() noexcept;
    constexpr void clear() noexcept;
    constexpr void swap(forward_list &) noexcept;
    constexpr iterator insert(size_type, const_reference, size_type = 1);
    constexpr iterator insert_after(const_iterator, const_reference, size_type = 1);
    template <typename ...Args>
    constexpr iterator emplace(size_type, Args &&...);
    template <typename ...Args>
    constexpr iterator emplace_after(const_iterator, Args &&...);
    constexpr iterator insert(size_type, rvalue_reference);
    constexpr iterator insert_after(const_iterator, rvalue_reference);
    template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
    constexpr iterator insert(size_type, InputIterator, InputIterator, size_type = 64);
    template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
    constexpr iterator insert_after(const_iterator, InputIterator, InputIterator, size_type = 64);
    template <IsForwardIterator ForwardIterator>
    constexpr iterator insert(size_type, ForwardIterator, ForwardIterator);
    template <IsForwardIterator ForwardIterator>
    constexpr iterator insert_after(const_iterator, ForwardIterator, ForwardIterator);
    constexpr iterator insert(size_type, initializer_list<T>);
    constexpr iterator insert_after(const_iterator, initializer_list<T>);
    constexpr iterator erase(size_type, size_type = 1);
    constexpr iterator erase_after(const_iterator, size_type);
    constexpr iterator erase_after(const_iterator);
    constexpr iterator erase_after(const_iterator, const_iterator);
    constexpr iterator erase_after(const_iterator, const_iterator, size_type);
};
template <typename T, typename Allocator>
inline constexpr void swap(forward_list<T, Allocator> &, forward_list<T, Allocator> &) noexcept;
// Todo : wait for header "compare.hpp"?
/*template <typename T, typename Allocator>
inline constexpr some_ordering operator<=>(forward_list<T, Allocator> &, forward_list<T, Allocator> &)
        noexcept(is_nothrow_three_way_comparable_v<T>);*/
__DATA_STRUCTURE_END(forward_list declaration)

__DATA_STRUCTURE_START(forward_list implementation)
/* exception handler */
namespace __data_structure_auxiliary {
template <typename NodeType, typename Allocator, bool>
struct forward_list_allocation_handler {
    NodeType begin;
    NodeType now;
    Allocator &allocator;
    constexpr forward_list_allocation_handler(NodeType begin, Allocator &allocator) noexcept :
            begin {begin}, now {begin}, allocator {allocator} {}
    constexpr void operator()() noexcept {
        this->now->next = nullptr;
        while(this->begin) {
            const auto backup {this->begin};
            this->begin = this->begin->next->node();
            this->allocator.deallocate(backup);
        }
    }
    constexpr void done() const noexcept {}
    constexpr void doing() const noexcept {}
};
template <typename NodeType, typename Allocator>
struct forward_list_allocation_handler<NodeType, Allocator, false> {
    NodeType begin;
    NodeType now;
    Allocator &allocator;
    bool value_construction_done {};
    constexpr forward_list_allocation_handler(NodeType begin, Allocator &allocator) noexcept :
            begin {begin}, now {begin}, allocator {allocator} {}
    constexpr void operator()() noexcept {
        this->now->next = nullptr;
        while(this->begin->next) {
            ds::destroy(ds::address_of(this->begin->value));
            const auto backup {this->begin};
            this->begin = this->begin->next;
            this->allocator.deallocate(backup);
        }
        if(this->value_construction_done) {
            ds::destroy(ds::address_of(this->begin->value));
        }
        this->allocator.deallocate(this->begin);
    }
    constexpr void done() noexcept {
        this->value_construction_done = true;
    }
    constexpr void doing() noexcept {
        this->value_construction_done = false;
    }
};
}

/* private type */
template <typename T, typename Allocator>
struct forward_list<T, Allocator>::linked_allocation_handler {
    node_type begin;
    size_type n;
    real_allocator &allocator;
    size_type i {0};
    constexpr linked_allocation_handler(node_type begin, real_allocator &allocator, size_type n) noexcept :
            begin {begin}, n {n}, allocator {allocator} {}
    constexpr void operator()() noexcept {
        for(auto cursor {this->begin}; this->i-- > 0; cursor = cursor->next->node()) {
            ds::destroy(ds::address_of(cursor->value));
        }
        this->allocator.deallocate(this->begin, &this->begin[this->n - 1], this->n);
    }
};

/* private functions */
template <typename T, typename Allocator>
template <bool CopyFromValue>
constexpr typename forward_list<T, Allocator>::node_type
forward_list<T, Allocator>::allocate_n(size_type n, const_reference value, node_type link_to) {
    if(n == 0) {
        return {};
    }
    auto &allocator {this->node_size.allocator()};
    if constexpr(__dsa::IsLinkedAfterAllocation<real_allocator>) {
        const auto result_node {allocator.allocate(n, link_to)};
        auto trans {transaction {linked_allocation_handler(result_node, this->node_size.allocator(), n)}};
        for(auto cursor {result_node};; cursor = cursor->next->node()) {
            if constexpr(CopyFromValue) {
                ds::construct(ds::address_of(cursor->value), value);
            }else {
                ds::construct(ds::address_of(cursor->value));
            }
            if(--n == 0) {
                break;
            }
        }
        trans.complete();
        return result_node;
    }
    const auto result_node {allocator.allocate(1)};
    auto trans {transaction {__dsa::forward_list_allocation_handler<node_type, real_allocator,
            is_trivially_destructible_v<T>>(result_node, allocator)}};
    auto &handler {trans.get_rollback()};
    while(--n not_eq 0) {
        if constexpr(CopyFromValue) {
            ds::construct(ds::address_of(handler.now->value), value);
        }else {
            ds::construct(ds::address_of(handler.now->value));
        }
        handler.done();
        handler.now->next = allocator.allocate(1);
        handler.doing();
    }
    handler.now->next = link_to;
    if constexpr(CopyFromValue) {
        ds::construct(ds::address_of(handler.now->value), value);
    }else {
        ds::construct(ds::address_of(handler.now->value));
    }
    handler.done();
    trans.complete();
    return result_node;
}
template <typename T, typename Allocator>
template <bool FromConstructor, typename Iterator>
constexpr typename forward_list<T, Allocator>::node_type
forward_list<T, Allocator>::allocate_n(Iterator begin, Iterator end, node_type link_to) {
    auto n {static_cast<size_type>(ds::distance(begin, end))};
    if constexpr(FromConstructor) {
        this->node_size() = n;
    }
    if(n == 0) {
        return {};
    }
    auto &allocator {this->node_size.allocator()};
    if constexpr(__dsa::IsLinkedAfterAllocation<real_allocator>) {
        const auto result_node {allocator.allocate(n, link_to)};
        auto trans {transaction {linked_allocation_handler(result_node, this->node_size.allocator(), n)}};
        for(auto cursor {result_node}; n not_eq 0; cursor = cursor->next->node(), static_cast<void>(--n)) {
            ds::construct(ds::address_of(cursor->value), *begin++);
        }
        trans.complete();
        return result_node;
    }
    const auto result_node {allocator.allocate(1)};
    auto trans {transaction {__dsa::forward_list_allocation_handler<node_type, real_allocator,
            is_trivially_destructible_v<T>>(result_node, allocator)}};
    auto &handler {trans.get_rollback()};
    while(--n not_eq 0) {
        ds::construct(ds::address_of(handler.now->value), *begin++);
        handler.done();
        handler.now->next = allocator.allocate(1);
        handler.doing();
    }
    handler.now->next = link_to;
    ds::construct(ds::address_of(handler.now->value), *begin);
    handler.done();
    trans.complete();
    return result_node;
}
template <typename T, typename Allocator>
template <typename ...Args>
constexpr typename forward_list<T, Allocator>::node_type
forward_list<T, Allocator>::allocate_1(node_type link_to, Args &&...args) {
    auto &allocator {this->node_size.allocator()};
    const auto result_node {allocator.allocate(1)};
    auto trans {transaction {__dsa::forward_list_allocation_handler<node_type, real_allocator,
            is_trivially_destructible_v<T>>(result_node, allocator)}};
    auto &handler {trans.get_rollback().now};
    ds::construct(ds::address_of(handler.now->value), ds::forward<Args>(args)...);
    handler.done();
    handler.now->next = link_to;
    trans.complete();
    return result_node;
}
template <typename T, typename Allocator>
constexpr void forward_list<T, Allocator>::deallocate_nodes(node_type begin, node_type end) noexcept {
    if constexpr(is_trivially_destructible_v<T>) {
        this->node_size.allocator().deallocate(begin, end);
    }else {
        size_type n {0};
        for(auto it {begin}; it not_eq end; ++it, static_cast<void>(++n)) {
            ds::destroy(ds::address_of(it->value));
        }
        this->node_size.allocator().deallocate(begin, end, n);
    }
}
template <typename T, typename Allocator>
constexpr void forward_list<T, Allocator>::deallocate_nodes(node_type begin, size_type n) noexcept {
    if constexpr(is_trivially_destructible_v<T>) {
        this->node_size.allocator().deallocate(begin, n);
    }else {
        auto end {begin};
        for(auto i {1}; i < n; ++i, static_cast<void>(end = end->next)) {
            ds::destroy(ds::address_of(end->value));
        }
        this->node_allocator().deallocate(begin, end, n);
    }
}

/* public functions */
template <typename T, typename Allocator>
constexpr forward_list<T, Allocator>::forward_list(const Allocator &allocator)
        noexcept(is_nothrow_constructible_v<real_allocator, const Allocator &>) :
        head {}, node_size(real_allocator {allocator}) {}
template <typename T, typename Allocator>
constexpr forward_list<T, Allocator>::forward_list(size_type n, const Allocator &allocator) :
        head {}, node_size(n, real_allocator {allocator}) {
    auto first_node {this->allocate_n<false>(n)};
    this->head.next = first_node;
}
template <typename T, typename Allocator>
constexpr forward_list<T, Allocator>::forward_list(size_type n, const_reference value, const Allocator &allocator) :
        head {}, node_size(n, real_allocator {allocator}) {
    auto first_node {this->allocate_n(n, value)};
    this->head.next = first_node;
}
template <typename T, typename Allocator>
template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
constexpr forward_list<T, Allocator>::forward_list(InputIterator begin, InputIterator end,
        const Allocator &allocator, size_type default_size) : head {}, node_size(real_allocator {allocator}) {
    buffer<T, Allocator> b(begin, end, allocator, default_size);
    auto first_node {this->allocate_n<true>(b.mbegin(), b.mend())};
    this->head.next = first_node;
}
template <typename T, typename Allocator>
template <IsForwardIterator ForwardIterator>
constexpr forward_list<T, Allocator>::forward_list(ForwardIterator begin, ForwardIterator end,
        const Allocator &allocator) : head {}, node_size(real_allocator {allocator}) {
    auto first_node {this->allocate_n<true>(begin, end)};
    this->head.next = first_node;
}
template <typename T, typename Allocator>
constexpr forward_list<T, Allocator>::forward_list(initializer_list<T> init_list, const Allocator &allocator) :
        forward_list(init_list.begin(), init_list.end(), allocator) {}
template <typename T, typename Allocator>
constexpr forward_list<T, Allocator>::forward_list(const forward_list &rhs) :
        forward_list(rhs.cbegin(), rhs.cend(), rhs.node_size.allocator()) {}
template <typename T, typename Allocator>
constexpr forward_list<T, Allocator>::forward_list(const forward_list &rhs, const Allocator &allocator) :
        forward_list(rhs.cbegin(), rhs.cend(), allocator) {}
template <typename T, typename Allocator>
constexpr forward_list<T, Allocator>::forward_list(forward_list &&rhs) noexcept : head {ds::move(rhs.head)},
        node_size {ds::move(rhs.node_size)} {
    rhs.head.next = nullptr;
    rhs.node_size() = 0;
}
template <typename T, typename Allocator>
constexpr forward_list<T, Allocator>::forward_list(forward_list &&rhs, const Allocator &allocator) noexcept :
        head {ds::move(rhs.head)}, node_size(ds::move(rhs.node_size()), allocator) {
    rhs.head = nullptr;
    rhs.node_size() = 0;
}
template <typename T, typename Allocator>
constexpr forward_list<T, Allocator>::~forward_list() noexcept {
    this->deallocate_nodes(this->head.next->node(), this->node_size());
}
template <typename T, typename Allocator>
constexpr forward_list<T, Allocator> &forward_list<T, Allocator>::operator=(const forward_list &rhs) {
    if(this not_eq &rhs) {
        this->deallocate_nodes(this->head.next->node(), this->node_size());
        this->node_size.allocator() = rhs.node_size.allocator();
        this->assign(rhs.cbegin(), rhs.cend());
    }
    return *this;
}
template <typename T, typename Allocator>
constexpr forward_list<T, Allocator> &forward_list<T, Allocator>::operator=(forward_list &&rhs) noexcept {
    if (this not_eq &rhs) {
        this->deallocate_nodes(this->head.next->node(), this->node_size());
        this->head = ds::move(rhs.head);
        this->node_size = ds::move(rhs.node_size);
        rhs.head.next = nullptr;
        rhs.node_size() = 0;
    }
    return *this;
}
template <typename T, typename Allocator>
constexpr forward_list<T, Allocator> &forward_list<T, Allocator>::operator=(initializer_list<T> init_list) {
    this->assign(init_list.begin(), init_list.end());
    return *this;
}
template <typename T, typename Allocator>
constexpr void forward_list<T, Allocator>::assign(size_type n, const_reference value) {
    const auto size {this->node_size()};
    if(n >= size) {
        for(auto it {this->head.next}; it; it = it->next) {
            it->value() = value;
        }
        if(const auto allocation_size {n - size}; allocation_size not_eq 0) {
            auto new_first_node {this->allocate_n(allocation_size, value, this->head.next->node())};
            this->head.next = new_first_node;
            this->node_size() += allocation_size;
        }
    }else {
        this->node_size() = n;
        auto it {&this->head};
        for(; n not_eq 0; --n, static_cast<void>(it = it->next)) {
            it->next->value() = value;
        }
        this->deallocate_nodes(static_cast<node_type>(it->next), size - n);
        it->next = nullptr;
    }
}
template <typename T, typename Allocator>
template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
constexpr void forward_list<T, Allocator>::assign(InputIterator begin, InputIterator end, size_type default_size) {
    buffer<T, Allocator> b(begin, end, static_cast<Allocator &>(this->node_size.allocator()), default_size);
    this->assign(b.mbegin(), b.mend());
}
template <typename T, typename Allocator>
template <IsForwardIterator ForwardIterator>
constexpr void forward_list<T, Allocator>::assign(ForwardIterator begin, ForwardIterator end) {
    const auto n {ds::distance(begin, end)};
    const auto size {this->node_size()};
    if(n >= size) {
        for(auto it {this->head.next}; it; it = it->next) {
            it->value() = *begin++;
        }
        if(const auto allocation_size {n - size}; allocation_size not_eq 0) {
            auto new_first_node {this->allocate_n(begin, end, this->head.next->node())};
            this->head.next = new_first_node;
            this->node_size() += allocation_size;
        }
    }else {
        this->node_size() = n;
        auto it {&this->head};
        for(auto assignment_size {n}; assignment_size not_eq 0;
                --assignment_size, static_cast<void>(it = it->next->node())) {
            it->next->value() = *begin++;
        }
        this->deallocate_nodes(static_cast<node_type>(it->next), size - n);
        it->next = nullptr;
    }
}
template <typename T, typename Allocator>
constexpr void forward_list<T, Allocator>::assign(initializer_list<T> init_list) {
    this->assign(init_list.begin(), init_list.end());
}
template <typename T, typename Allocator>
constexpr typename forward_list<T, Allocator>::iterator forward_list<T, Allocator>::before_begin() noexcept {
    return iterator {this->head};
}
template <typename T, typename Allocator>
constexpr typename forward_list<T, Allocator>::const_iterator
forward_list<T, Allocator>::before_begin() const noexcept {
    return const_iterator {this->head};
}
template <typename T, typename Allocator>
constexpr typename forward_list<T, Allocator>::const_iterator
forward_list<T, Allocator>::cbefore_begin() const noexcept {
    return const_iterator {this->head};
}
template <typename T, typename Allocator>
constexpr typename forward_list<T, Allocator>::iterator forward_list<T, Allocator>::begin() noexcept {
    return iterator {this->head.next};
}
template <typename T, typename Allocator>
constexpr typename forward_list<T, Allocator>::const_iterator forward_list<T, Allocator>::begin() const noexcept {
    return const_iterator {this->head.next};
}
template <typename T, typename Allocator>
constexpr typename forward_list<T, Allocator>::const_iterator forward_list<T, Allocator>::cbegin() const noexcept {
    return const_iterator {this->head.next};
}
template <typename T, typename Allocator>
constexpr typename forward_list<T, Allocator>::iterator forward_list<T, Allocator>::end() noexcept {
    return {};
}
template <typename T, typename Allocator>
constexpr typename forward_list<T, Allocator>::const_iterator forward_list<T, Allocator>::end() const noexcept {
    return {};
}
template <typename T, typename Allocator>
constexpr typename forward_list<T, Allocator>::const_iterator forward_list<T, Allocator>::cend() const noexcept {
    return {};
}
template <typename T, typename Allocator>
constexpr typename forward_list<T, Allocator>::size_type forward_list<T, Allocator>::size() const noexcept {
    return this->node_size();
}
template <typename T, typename Allocator>
constexpr bool forward_list<T, Allocator>::empty() const noexcept {
    return this->node_size() == 0;
}
template <typename T, typename Allocator>
constexpr void forward_list<T, Allocator>::resize(size_type n) {
    this->resize(n, {});
}
template <typename T, typename Allocator>
constexpr void forward_list<T, Allocator>::resize(size_type n, const_reference value) {
    const auto size {this->node_size()};
    if(n > size) {
        auto new_first_node {this->allocate_n(n - size, value, this->head->next)};
        this->head->next = new_first_node;
    }else if(n < size) {
        auto last_node {this->head};
        for(; n not_eq 0; --n, static_cast<void>(last_node = last_node->next));
        this->deallocate_nodes(last_node->next, size - n);
        last_node->next = nullptr;
    }
    this->node_size() = n;
}
template <typename T, typename Allocator>
constexpr typename forward_list<T, Allocator>::reference forward_list<T, Allocator>::front() noexcept {
    return this->head.next->value();
}
template <typename T, typename Allocator>
constexpr typename forward_list<T, Allocator>::const_reference forward_list<T, Allocator>::front() const noexcept {
    return this->head->next->value();
}
template <typename T, typename Allocator>
constexpr Allocator forward_list<T, Allocator>::allocator() const noexcept {
    return this->node_size.allocator();
}
template <typename T, typename Allocator>
constexpr void forward_list<T, Allocator>::push_front(const_reference value) {
    this->emplace_front(value);
}
template <typename T, typename Allocator>
constexpr void forward_list<T, Allocator>::push_front(rvalue_reference value) {
    this->emplace_front(ds::move(value));
}
template <typename T, typename Allocator>
template <typename ...Args>
constexpr void forward_list<T, Allocator>::emplace_front(Args &&...args) {
    auto new_first_node {this->allocate_1(this->head->next, ds::forward<Args>(args)...)};
    this->head->next = new_first_node;
    this->node_size() += 1;
}
template <typename T, typename Allocator>
constexpr void forward_list<T, Allocator>::pop_front() noexcept {
    auto backup {this->head->next};
    this->head->next = backup->next;
    this->deallocate_nodes(backup, 1);
    this->node_size() -= 1;
}
template <typename T, typename Allocator>
constexpr void forward_list<T, Allocator>::clear() noexcept {
    this->deallocate_nodes(this->head->next, this->node_size());
    this->head->next = nullptr;
    this->node_size() = 0;
}
template <typename T, typename Allocator>
constexpr void forward_list<T, Allocator>::swap(forward_list &rhs) noexcept {
    using ds::swap;
    swap(this->head, rhs.head);
    swap(this->node_size, rhs.node_size);
}
template <typename T, typename Allocator>
constexpr typename forward_list<T, Allocator>::iterator
forward_list<T, Allocator>::insert(size_type pos, const_reference value, size_type n) {
    auto begin {this->cbefore_begin()};
    for(; pos not_eq 0; --pos, static_cast<void>(++begin));
    return this->insert_after(begin, value, n);
}
template <typename T, typename Allocator>
constexpr typename forward_list<T, Allocator>::iterator
forward_list<T, Allocator>::insert_after(const_iterator pos, const_reference value, size_type n) {
    auto new_first_node {this->allocate_n(n, value, pos.node->next)};
    pos.node->next = new_first_node;
    this->node_size() += n;
    return iterator {new_first_node};
}
template <typename T, typename Allocator>
template <typename ...Args>
constexpr typename forward_list<T, Allocator>::iterator
forward_list<T, Allocator>::emplace(size_type pos, Args &&...args) {
    auto begin {this->cbefore_begin()};
    for(; pos not_eq 0; --pos, static_cast<void>(++begin));
    return this->emplace_after(begin, ds::forward<Args>(args)...);
}
template <typename T, typename Allocator>
template <typename ...Args>
constexpr typename forward_list<T, Allocator>::iterator
forward_list<T, Allocator>::emplace_after(const_iterator pos, Args &&...args) {
    auto new_first_node {this->allocate_1(pos.node->next, ds::forward<Args>(args)...)};
    pos.node->next = new_first_node;
    ++this->node_size();
    return iterator {new_first_node};
}
template <typename T, typename Allocator>
template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
constexpr typename forward_list<T, Allocator>::iterator forward_list<T, Allocator>::insert(
        size_type pos, InputIterator begin, InputIterator end, size_type default_size) {
    auto list_begin {this->cbefore_begin()};
    for(; pos not_eq 0; --pos, static_cast<void>(++begin));
    buffer<T, Allocator> b(begin, end, static_cast<Allocator &>(this->node_size.allocator()), default_size);
    return this->insert_after(list_begin, b.mbegin(), b.mend());
}
template <typename T, typename Allocator>
template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
constexpr typename forward_list<T, Allocator>::iterator forward_list<T, Allocator>::insert_after(
        const_iterator pos, InputIterator begin, InputIterator end, size_type default_size) {
    buffer<T, Allocator> b(begin, end, static_cast<Allocator &>(this->node_size.allocator()), default_size);
    return this->insert_after(pos, b.mbegin(), b.mend());
}
template <typename T, typename Allocator>
template <IsForwardIterator ForwardIterator>
constexpr typename forward_list<T, Allocator>::iterator
forward_list<T, Allocator>::insert(size_type pos, ForwardIterator begin, ForwardIterator end) {
    auto list_begin {this->cbefore_begin()};
    for(; pos not_eq 0; --pos, static_cast<void>(++begin));
    return this->insert_after(list_begin, begin, end);
}
template <typename T, typename Allocator>
template <IsForwardIterator ForwardIterator>
constexpr typename forward_list<T, Allocator>::iterator
forward_list<T, Allocator>::insert_after(const_iterator pos, ForwardIterator begin, ForwardIterator end) {
    auto new_first_node {this->allocate_n(begin, end, pos.node->next)};
    pos.node->next = new_first_node;
    this->node_size() += static_cast<size_type>(ds::distance(begin, end));
    return iterator {new_first_node};
}
template <typename T, typename Allocator>
constexpr typename forward_list<T, Allocator>::iterator
forward_list<T, Allocator>::insert(size_type pos, initializer_list<T> init_list) {
    auto begin {this->cbefore_begin()};
    for(; pos not_eq 0; --pos, static_cast<void>(++begin));
    return this->insert_after(begin, init_list.begin(), init_list.end());
}
template <typename T, typename Allocator>
constexpr typename forward_list<T, Allocator>::iterator
forward_list<T, Allocator>::insert_after(const_iterator pos, initializer_list<T> init_list) {
    return this->insert_after(pos, init_list.begin(), init_list.end());
}
template <typename T, typename Allocator>
constexpr typename forward_list<T, Allocator>::iterator
forward_list<T, Allocator>::erase(size_type pos, size_type n) {
    auto begin {this->cbefore_begin()};
    for(auto i {0}; i not_eq n; ++i, static_cast<void>(++begin));
    auto end {begin};
    for(; n not_eq 0; --n, static_cast<void>(++end));
    return this->erase_after(begin, end, n);
}
template <typename T, typename Allocator>
constexpr typename forward_list<T, Allocator>::iterator
forward_list<T, Allocator>::erase_after(const_iterator pos, size_type n) {
    auto end_pos {pos};
    for(auto i {0}; i not_eq n; ++i, static_cast<void>(++end_pos));
    return this->erase_after(pos, end_pos, n);
}
template <typename T, typename Allocator>
constexpr typename forward_list<T, Allocator>::iterator
forward_list<T, Allocator>::erase_after(const_iterator pos) {
    auto end_pos {pos};
    return this->erase_after(pos, ++end_pos, 1);
}
template <typename T, typename Allocator>
constexpr typename forward_list<T, Allocator>::iterator
forward_list<T, Allocator>::erase_after(const_iterator begin, const_iterator end) {
    return this->erase_after(begin, end, static_cast<size_type>(ds::distance(begin, end)));
}
template <typename T, typename Allocator>
constexpr typename forward_list<T, Allocator>::iterator
forward_list<T, Allocator>::erase_after(const_iterator begin, const_iterator end, size_type n) {
    auto link_to {end.node->next};
    this->deallocate(begin.node->next, end);
    begin.node->next = link_to;
    this->node_size() -= n;
    return iterator {link_to};
}
__DATA_STRUCTURE_END(forward_list implementation)

}

#endif      // DATA_STRUCTURE_FORWARD_LIST_HPP