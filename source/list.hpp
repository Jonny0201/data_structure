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


#ifndef DATA_STRUCTURE_LIST_HPP
#define DATA_STRUCTURE_LIST_HPP

#include "buffer.hpp"

namespace data_structure {

__DATA_STRUCTURE_START(list declaration)
template <typename T, typename Allocator = allocator<T>,typename NodeAllocator = __dsa::node_allocator<Allocator,
        __dsa::list_node, __dsa::list_node_linker>>
class list {
private:
    using node_type = __dsa::list_node<T> *;
    using real_allocator = conditional_t<is_void_v<NodeAllocator>,
            typename allocator_traits<Allocator>::template rebind<__dsa::list_node<T>>, NodeAllocator>;
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
    using iterator = __dsa::list_iterator<T>;
    using const_iterator = __dsa::list_iterator<T, true>;
    using reverse_iterator = reverse_iterator<iterator>;
    using const_reverse_iterator = ds::reverse_iterator<const_iterator>;
    static_assert(is_same_v<T, typename Allocator::value_type>,
            "The value type of list should be same as the allocator's value_type!");
private:
    __dsa::list_base_node<__dsa::list_node<T>> tail {};
    __dsa::allocator_compressor<size_type, real_allocator> node_size {};
private:
    template <typename ...Args>
    constexpr auto allocate_values(size_type, Args &&...);
    template <IsInputIterator InputIterator>
    constexpr auto allocate_range(size_type, InputIterator);
    constexpr void erase(node_type, node_type, size_type) noexcept;
public:
    constexpr list() noexcept(is_nothrow_default_constructible_v<real_allocator>) = default;
    explicit constexpr list(const Allocator &) noexcept(is_nothrow_constructible_v<real_allocator, const Allocator &>);
    explicit constexpr list(size_type, const Allocator & = {});
    constexpr list(size_type, const_reference, const Allocator & = {});
    template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
    constexpr list(InputIterator, InputIterator, const Allocator & = {}, size_type = 64);
    template <IsForwardIterator ForwardIterator>
    constexpr list(ForwardIterator, ForwardIterator, const Allocator & = {});
    constexpr list(initializer_list<T>, const Allocator & = {});
    constexpr list(const list &);
    constexpr list(const list &, const Allocator &);
    constexpr list(list &&) noexcept;
    constexpr list(list &&, const Allocator &) noexcept;
    constexpr ~list() noexcept;
public:
    constexpr list &operator=(const list &);
    constexpr list &operator=(list &&) noexcept;
    constexpr list &operator=(initializer_list<T>);
public:
    constexpr void assign(size_type, const_reference = {});
    template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
    constexpr void assign(InputIterator, InputIterator, size_type = 64);
    template <IsForwardIterator ForwardIterator>
    constexpr void assign(ForwardIterator, ForwardIterator);
    constexpr void assign(initializer_list<T>);
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
    constexpr reverse_iterator rbegin() noexcept;
    [[nodiscard]]
    constexpr const_reverse_iterator rbegin() const noexcept;
    [[nodiscard]]
    constexpr const_reverse_iterator crbegin() const noexcept;
    [[nodiscard]]
    constexpr reverse_iterator rend() noexcept;
    [[nodiscard]]
    constexpr const_reverse_iterator rend() const noexcept;
    [[nodiscard]]
    constexpr const_reverse_iterator crend() const noexcept;
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
    constexpr reference back() noexcept;
    [[nodiscard]]
    constexpr const_reference back() const noexcept;
    [[nodiscard]]
    constexpr Allocator allocator() const noexcept;
    constexpr void push_front(const_reference);
    constexpr void push_front(rvalue_reference);
    constexpr void push_back(const_reference);
    constexpr void push_back(rvalue_reference);
    template <typename ...Args>
    constexpr void emplace_front(Args &&...);
    template <typename ...Args>
    constexpr void emplace_back(Args &&...);
    constexpr void pop_front() noexcept;
    constexpr void pop_back() noexcept;
    constexpr void clear() noexcept;
    constexpr void swap(list &) noexcept;
    constexpr iterator insert(size_type, const_reference, size_type = 1);
    constexpr iterator insert(const_iterator, const_reference, size_type = 1);
    template <typename ...Args>
    constexpr iterator emplace(size_type, Args &&...);
    template <typename ...Args>
    constexpr iterator emplace(const_iterator, Args &&...);
    constexpr iterator insert(size_type, rvalue_reference);
    constexpr iterator insert(const_iterator, rvalue_reference);
    template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
    constexpr iterator insert(size_type, InputIterator, InputIterator, size_type = 64);
    template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
    constexpr iterator insert(const_iterator, InputIterator, InputIterator, size_type = 64);
    template <IsForwardIterator ForwardIterator>
    constexpr iterator insert(size_type, ForwardIterator, ForwardIterator);
    template <IsForwardIterator ForwardIterator>
    constexpr iterator insert(const_iterator, ForwardIterator, ForwardIterator);
    constexpr iterator insert(size_type, initializer_list<T>);
    constexpr iterator insert(const_iterator, initializer_list<T>);
    constexpr iterator erase(size_type, size_type = 1);
    constexpr iterator erase(const_iterator, size_type);
    constexpr iterator erase(const_iterator);
    constexpr iterator erase(const_iterator, const_iterator);
};
__DATA_STRUCTURE_END(list declaration)

__DATA_STRUCTURE_START(list implementation)
/* exceptional handler */
namespace __data_structure_auxiliary {
template <typename NodeType, typename Allocator, bool>
struct list_allocation_handler {
    NodeType begin;
    NodeType now;
    Allocator &allocator;
    constexpr list_allocation_handler(NodeType begin, Allocator &allocator) noexcept :
            begin {begin}, now {begin}, allocator {allocator} {}
    constexpr void operator()() noexcept {
        this->now->next = nullptr;
        while(this->begin->next) {
            ds::destroy(ds::address_of(this->begin->value));
            const auto backup {this->begin};
            this->begin = this->begin->next->node();
            this->allocator.deallocate(backup);
        }
        this->allocator.deallocate(this->begin);
    }
    constexpr void done() const noexcept {}
    constexpr void doing() const noexcept {}
};
template <typename NodeType, typename Allocator>
struct list_allocation_handler<NodeType, Allocator, false> {
    NodeType begin;
    NodeType now;
    Allocator &allocator;
    bool value_construction_done {};
    constexpr list_allocation_handler(NodeType begin, Allocator &allocator) noexcept :
            begin {begin}, now {begin}, allocator {allocator} {}
    constexpr void operator()() noexcept {
        this->now->next = nullptr;
        while(this->begin->next) {
            ds::destroy(ds::address_of(this->begin->value));
            const auto backup {this->begin};
            this->begin = this->begin->next->node();
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

/* private functions */
template <typename T, typename Allocator, typename NodeAllocator>
template <typename ...Args>
constexpr auto list<T, Allocator, NodeAllocator>::allocate_values(size_type n, Args &&...args) {
    if constexpr(__dsa::IsLinkedAfterAllocation<real_allocator>) {
        return this->node_size.allocator().allocate_with_value(n, ds::forward<Args>(args)...);
    }else {
        struct return_pair {
            node_type first_node;
            node_type last_node;
            constexpr operator node_type() noexcept {
                return this>first_node;
            }
        };
        auto &allocator {this->node_size.allocator()};
        auto trans {transaction {__dsa::list_allocation_handler<node_type, real_allocator,
                is_trivially_destructible_v<T>>(allocator.allocate(1), allocator)}};
        auto handler {trans.get_rollback()};
        while(--n not_eq 0) {
            ds::construct(ds::address_of(handler.now->value()), ds::forward<Args>(args)...);
            handler.done();
            handler.now->next = allocator.allocate(1);
            handler.doing();
        }
        ds::construct(ds::address_of(handler.now->value()), ds::forward<Args>(args)...);
        handler.done();
        trans.complete();
        return return_pair {handler.begin, handler.now};
    }
}
template <typename T, typename Allocator, typename NodeAllocator>
template <IsInputIterator InputIterator>
constexpr auto list<T, Allocator, NodeAllocator>::allocate_range(size_type n, InputIterator begin) {
    if constexpr(__dsa::IsLinkedAfterAllocation<real_allocator>) {
        return this->node_size.allocator().allocate_with_range(n, begin);
    }else {
        struct return_pair {
            node_type first_node;
            node_type last_node;
            constexpr operator node_type() noexcept {
                return this>first_node;
            }
        };
        auto &allocator {this->node_size.allocator()};
        auto trans {transaction {__dsa::list_allocation_handler<node_type, real_allocator,
                is_trivially_destructible_v<T>>(allocator.allocate(1), allocator)}};
        auto handler {trans.get_rollback()};
        while(--n not_eq 0) {
            ds::construct(ds::address_of(handler.now->value()),
                    ds::move_if<not IsForwardIterator<InputIterator>>(*begin++));
            handler.done();
            handler.now->next = allocator.allocate(1);
            handler.doing();
        }
        ds::construct(ds::address_of(handler.now->value()),
                ds::move_if<not IsForwardIterator<InputIterator>>(*begin++));
        handler.done();
        trans.complete();
        return return_pair {handler.begin, handler.now};
    }
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr void list<T, Allocator, NodeAllocator>::erase(node_type begin, node_type end, size_type size) noexcept {
    auto &allocator {this->node_size.allocator()};
    if constexpr(__dsa::IsLinkedAfterAllocation<real_allocator>) {
        end->next->previous = begin->previous;
        begin->previous->next = end->next;
        allocator.deallocate<true>(begin, end, size);
    }else {
        for(auto cursor {begin};;) {
            auto backup {cursor->node()};
            cursor = cursor->next;
            ds::destroy(ds::address_of(backup->value));
            allocator.deallocate(backup);
            if(cursor == end) {
                ds::destroy(ds::address_of(cursor->value));
                allocator.deallocate(cursor);
                this->node_size() -= size;
                return;
            }
        }
    }
}

/* public functions */
template <typename T, typename Allocator, typename NodeAllocator>
constexpr list<T, Allocator, NodeAllocator>::list(const Allocator &allocator)
        noexcept(is_nothrow_constructible_v<real_allocator, const Allocator &>) : tail {},
        node_size(real_allocator {allocator}) {}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr list<T, Allocator, NodeAllocator>::list(size_type n, const Allocator &allocator) :
        tail {}, node_size(n, real_allocator {allocator}) {
    const auto [first_node, last_node] {this->allocate_values(n)};
    this->tail.next = first_node;
    this->tail.previous = last_node;
    first_node->previous = this->tail;
    last_node->next = this->tail;
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr list<T, Allocator, NodeAllocator>::list(size_type n, const_reference value, const Allocator &allocator) :
        tail {}, node_size(n, real_allocator {allocator}) {
    const auto [first_node, last_node] {this->allocate_values(n, value)};
    this->tail.next = first_node;
    this->tail.previous = last_node;
    first_node->previous = this->tail;
    last_node->next = this->tail;
}
template <typename T, typename Allocator, typename NodeAllocator>
template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
constexpr list<T, Allocator, NodeAllocator>::list(InputIterator begin, InputIterator end, const Allocator &allocator,
        size_type default_size) : tail {}, node_size(real_allocator {allocator}) {
    buffer<T, Allocator> b(begin, end, allocator, default_size);
    const auto [first_node, last_node] {this->allocate_range(this->node_size() = b.size(), b.mbegin())};
    this->tail.next = first_node;
    this->tail.previous = last_node;
    first_node->previous = this->tail;
    last_node->next = this->tail;
}
template <typename T, typename Allocator, typename NodeAllocator>
template <IsForwardIterator ForwardIterator>
constexpr list<T, Allocator, NodeAllocator>::list(ForwardIterator begin, ForwardIterator end,
        const Allocator &allocator) : tail {}, node_size(real_allocator {allocator}) {
    const auto [first_node, last_node] {this->allocate_range(
            this->node_size() = static_cast<size_type>(ds::distance(begin, end)), begin)};
    this->tail.next = first_node;
    this->tail.previous = last_node;
    first_node->previous = this->tail;
    last_node->next = this->tail;
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr list<T, Allocator, NodeAllocator>::list(initializer_list<T> init_list, const Allocator &allocator):
        list(init_list.begin(), init_list.end(), allocator) {}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr list<T, Allocator, NodeAllocator>::list(const list &rhs) : tail {}, node_size(rhs.node_size) {
    const auto [first_node, last_node] {this->allocate_range(rhs.size(), rhs.cbegin())};
    this->tail.next = first_node;
    this->tail.previous = last_node;
    first_node->previous = this->tail;
    last_node->next = this->tail;
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr list<T, Allocator, NodeAllocator>::list(const list &rhs, const Allocator &allocator) :
        list(rhs.cbegin(), rhs.cend(), allocator) {}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr list<T, Allocator, NodeAllocator>::list(list &&rhs) noexcept : tail {ds::move(rhs.tail)},
        node_size {ds::move(rhs.node_size)} {
    rhs.tail.next = rhs.tail.previous = nullptr;
    rhs.node_size() = 0;
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr list<T, Allocator, NodeAllocator>::list(list &&rhs, const Allocator &allocator) noexcept :
        tail {ds::move(rhs.tail)}, node_size(ds::move(rhs.node_size()), real_allocator {allocator}) {
    rhs.tail.next = rhs.tail.previous = nullptr;
    rhs.node_size() = 0;
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr list<T, Allocator, NodeAllocator>::~list() noexcept {
    this->node_size.allocator().deallocate<true>(this->tail.next->node(), this->tail.previous->node(),
            this->node_size());
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr list<T, Allocator, NodeAllocator> &list<T, Allocator, NodeAllocator>::operator=(const list &rhs) {
    if(this not_eq &rhs) {
        this->assign(rhs.cbegin(), rhs.cend());
    }
    return *this;
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr list<T, Allocator, NodeAllocator> &list<T, Allocator, NodeAllocator>::operator=(list &&rhs) noexcept {
    if(this not_eq &rhs) {
        this->~list();
        this->tail = ds::move(rhs.tail);
        this->node_size = ds::move(rhs.node_size);
        rhs.tail.next = rhs.tail.previous = nullptr;
        rhs.node_size() = 0;
    }
    return *this;
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr list<T, Allocator, NodeAllocator> &
list<T, Allocator, NodeAllocator>::operator=(initializer_list<T> init_list) {
    this->assign(init_list.begin(), init_list.end());
    return *this;
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr void list<T, Allocator, NodeAllocator>::assign(size_type n, const_reference value) {
    auto &size {this->node_size()};
    if(n >= size) {
        for(auto it {this->tail.next}; it; it = it->next) {
            it->value() = value;
        }
        if(const auto allocation_size {n - size}; allocation_size not_eq 0) {
            auto [first_node, last_node] {this->allocate_values(allocation_size, this->tail.next->node(), value)};
            last_node->next = this->tail.next;
            this->tail.next = first_node;
            first_node->previous = this->tail.previous;
            this->tail.previous = last_node;
            size += allocation_size;
        }
    }else {
        const auto erasion_size {size - n};
        auto cursor {this->tail};
        auto &allocator {this->node_size.allocator()};
        size = n;
        if(erasion_size < n) {
            for(auto i {0}; i < erasion_size; ++i) {
                cursor = cursor->previous;
            }
            this->tail->previous = cursor->previous;
            cursor->previous->next = &this->tail;
            allocator.deallocate(cursor->node(), this->tail->previous->node(), erasion_size);
        }else {
            while(n-- not_eq 0) {
                cursor = cursor->next;
            }
            this->tail->previous = cursor;
            const auto backup {cursor->next};
            cursor->next = &this->tail;
            allocator.deallocate(backup->node(), this->tail->previous->node(), erasion_size);
        }
    }
}
template <typename T, typename Allocator, typename NodeAllocator>
template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
constexpr void list<T, Allocator, NodeAllocator>::assign(InputIterator begin, InputIterator end,
        size_type default_size) {
    buffer<T, Allocator> b(begin, end, default_size);
    this->assign(b.mbegin(), b.mend());
}
template <typename T, typename Allocator, typename NodeAllocator>
template <IsForwardIterator ForwardIterator>
constexpr void list<T, Allocator, NodeAllocator>::assign(ForwardIterator begin, ForwardIterator end) {
    auto n {static_cast<size_type>(ds::distance(begin, end))};
    auto &size {this->node_size()};
    if(n >= size) {
        for(auto it {this->tail.next}; it; it = it->next) {
            it->value() = *begin++;
        }
        if(const auto allocation_size {n - size}; allocation_size not_eq 0) {
            auto [first_node, last_node] {this->allocate_values(allocation_size, this->tail.next->node(), begin)};
            last_node->next = this->tail.next;
            this->tail.next = first_node;
            first_node->previous = this->tail.previous;
            this->tail.previous = last_node;
            size += allocation_size;
        }
    }else {
        for(auto it {this->tail.next}; begin not_eq end; it = it->next) {
            it->value() = *begin++;
        }
        const auto erasion_size {size - n};
        auto cursor {this->tail};
        auto &allocator {this->node_size.allocator()};
        size = n;
        if(erasion_size < n) {
            for(auto i {0}; i < erasion_size; ++i) {
                cursor = cursor->previous;
            }
            this->tail->previous = cursor->previous;
            cursor->previous->next = &this->tail;
            allocator.deallocate(cursor->node(), this->tail->previous->node(), erasion_size);
        }else {
            while(n-- not_eq 0) {
                cursor = cursor->next;
            }
            this->tail->previous = cursor;
            const auto backup {cursor->next};
            cursor->next = &this->tail;
            allocator.deallocate(backup->node(), this->tail->previous->node(), erasion_size);
        }
    }
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr void list<T, Allocator, NodeAllocator>::assign(initializer_list<T> init_list) {
    this->assign(init_list.begin(), init_list.end());
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr typename list<T, Allocator, NodeAllocator>::iterator list<T, Allocator, NodeAllocator>::begin() noexcept {
    return iterator {this->tail->next};
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr typename list<T, Allocator, NodeAllocator>::const_iterator
list<T, Allocator, NodeAllocator>::begin() const noexcept {
    return const_iterator {this->tail->next};
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr typename list<T, Allocator, NodeAllocator>::const_iterator
list<T, Allocator, NodeAllocator>::cbegin() const noexcept {
    return const_iterator {this->tail->next};
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr typename list<T, Allocator, NodeAllocator>::iterator list<T, Allocator, NodeAllocator>::end() noexcept {
    return iterator {this->tail};
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr typename list<T, Allocator, NodeAllocator>::const_iterator
list<T, Allocator, NodeAllocator>::end() const noexcept {
    return const_iterator {this->tail};
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr typename list<T, Allocator, NodeAllocator>::const_iterator
list<T, Allocator, NodeAllocator>::cend() const noexcept {
    return const_iterator {this->tail};
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr typename list<T, Allocator, NodeAllocator>::reverse_iterator
list<T, Allocator, NodeAllocator>::rbegin() noexcept {
    return reverse_iterator {this->tail->previous};
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr typename list<T, Allocator, NodeAllocator>::const_reverse_iterator
list<T, Allocator, NodeAllocator>::rbegin() const noexcept {
    return const_reverse_iterator {this->tail->previous};
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr typename list<T, Allocator, NodeAllocator>::const_reverse_iterator
list<T, Allocator, NodeAllocator>::crbegin() const noexcept {
    return const_reverse_iterator {this->tail->previous};
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr typename list<T, Allocator, NodeAllocator>::reverse_iterator
list<T, Allocator, NodeAllocator>::rend() noexcept {
    return reverse_iterator {this->tail};
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr typename list<T, Allocator, NodeAllocator>::const_reverse_iterator
list<T, Allocator, NodeAllocator>::rend() const noexcept {
    return const_reverse_iterator {this->tail};
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr typename list<T, Allocator, NodeAllocator>::const_reverse_iterator
list<T, Allocator, NodeAllocator>::crend() const noexcept {
    return const_reverse_iterator {this->tail};
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr typename list<T, Allocator, NodeAllocator>::size_type
list<T, Allocator, NodeAllocator>::size() const noexcept {
    return this->node_size();
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr bool list<T, Allocator, NodeAllocator>::empty() const noexcept {
    return this->node_size() == 0;
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr void list<T, Allocator, NodeAllocator>::resize(size_type n) {
    this->resize(n, {});
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr void list<T, Allocator, NodeAllocator>::resize(size_type n, const_reference value) {
    const auto size {this->node_size()};
    if(n > size) {
        const auto [first_node, last_node] {this->allocate_values(n - size, value)};
        first_node->previous = this->tail->previous;
        this->tail->previous->next = first_node;
        last_node->next = &this->tail;
        this->tail->previous = last_node;
        this->node_size() = n;
    }else if(n < size) {
        this->node_size() = n;
        const auto erasion_size {size - n};
        auto cursor {this->tail};
        auto &allocator {this->node_size.allocator()};
        if(erasion_size < n) {
            for(auto i {0}; i < erasion_size; ++i) {
                cursor = cursor->previous;
            }
            this->tail->previous = cursor->previous;
            cursor->previous->next = &this->tail;
            allocator.deallocate(cursor->node(), this->tail->previous->node(), erasion_size);
        }else {
            while(n-- not_eq 0) {
                cursor = cursor->next;
            }
            this->tail->previous = cursor;
            const auto backup {cursor->next};
            cursor->next = &this->tail;
            allocator.deallocate(backup->node(), this->tail->previous->node(), erasion_size);
        }
    }
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr typename list<T, Allocator, NodeAllocator>::reference list<T, Allocator, NodeAllocator>::front() noexcept {
    return this->tail.next->value();
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr typename list<T, Allocator, NodeAllocator>::const_reference
list<T, Allocator, NodeAllocator>::front() const noexcept {
    return this->tail.next->value();
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr typename list<T, Allocator, NodeAllocator>::reference list<T, Allocator, NodeAllocator>::back() noexcept {
    return this->tail.previous->value();
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr typename list<T, Allocator, NodeAllocator>::const_reference
list<T, Allocator, NodeAllocator>::back() const noexcept {
    return this->tail.previous->value();
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr Allocator list<T, Allocator, NodeAllocator>::allocator() const noexcept {
    if constexpr(__dsa::IsLinkedAfterAllocation<real_allocator>) {
        return this->node_size.allocator();
    }
    return {};
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr void list<T, Allocator, NodeAllocator>::push_front(const_reference value) {
    this->emplace_front(value);
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr void list<T, Allocator, NodeAllocator>::push_front(rvalue_reference value) {
    this->emplace_front(ds::move(value));
}
template <typename T, typename Allocator, typename NodeAllocator>
template <typename ...Args>
constexpr void list<T, Allocator, NodeAllocator>::emplace_front(Args &&...args) {
    const node_type node {this->allocate_values(1, ds::forward<Args>(args)...)};
    node->next = this->tail.next;
    this->tail.next->previous = node;
    node->previous = &this->tail;
    this->tail.next = node;
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr void list<T, Allocator, NodeAllocator>::push_back(const_reference value) {
    this->emplace_back(value);
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr void list<T, Allocator, NodeAllocator>::push_back(rvalue_reference value) {
    this->emplace_back(ds::move(value));
}
template <typename T, typename Allocator, typename NodeAllocator>
template <typename ...Args>
constexpr void list<T, Allocator, NodeAllocator>::emplace_back(Args &&...args) {
    const node_type node {this->allocate_values(1, ds::forward<Args>(args)...)};
    node->previous = this->tail.previous;
    node->next = &this->tail;
    this->tail.previous->next = node;
    this->tail.previous = node;
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr void list<T, Allocator, NodeAllocator>::pop_front() noexcept {
    const auto backup {this->tail.next};
    backup->next->previous = &this->tail;
    this->tail.next = backup->next;
    this->node_size.allocator().deallocate(backup);
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr void list<T, Allocator, NodeAllocator>::pop_back() noexcept {
    const auto backup {this->tail.previous};
    backup->previous->next = &this->tail;
    this->tail.previous = backup->previous;
    this->node_size.allocator().deallocate(backup);
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr void list<T, Allocator, NodeAllocator>::clear() noexcept {
    auto &size {this->node_size()};
    if(size == 0) {
        return;
    }
    this->node_size.allocator().deallocate(this->tail.next, this->tail.previous, size);
    this->tail.next = &this->tail;
    this->tail.previous = &this->tail;
    size = 0;
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr void list<T, Allocator, NodeAllocator>::swap(list &rhs) noexcept {
    ds::swap(this->node_size, rhs.node_size);
    ds::swap(this->tail, rhs.tail);
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr typename list<T, Allocator, NodeAllocator>::iterator
list<T, Allocator, NodeAllocator>::insert(size_type pos, const_reference value, size_type n) {
    auto cursor {this->tail.next};
    while(pos-- not_eq 0) {
        cursor = cursor->next;
    }
    return this->insert(const_iterator {cursor->node()}, value, n);
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr typename list<T, Allocator, NodeAllocator>::iterator
list<T, Allocator, NodeAllocator>::insert(const_iterator pos, const_reference value, size_type n) {
    if(n == 0) {
        return iterator {pos.node};
    }
    const auto [first_node, last_node] {this->allocate_values(n, value)};
    first_node->previous = pos.node->previous;
    last_node->next = pos.node;
    pos.node->previous->next = first_node;
    pos.node->previous = last_node;
    this->node_size() += n;
    return iterator {first_node};
}
template <typename T, typename Allocator, typename NodeAllocator>
template <typename ...Args>
constexpr typename list<T, Allocator, NodeAllocator>::iterator
list<T, Allocator, NodeAllocator>::emplace(size_type pos, Args &&...args) {
    auto cursor {this->tail.next};
    while(pos-- not_eq 0) {
        cursor = cursor->next;
    }
    return this->emplace(const_iterator {cursor->node()}, ds::forward<Args>(args)...);
}
template <typename T, typename Allocator, typename NodeAllocator>
template <typename ...Args>
constexpr typename list<T, Allocator, NodeAllocator>::iterator
list<T, Allocator, NodeAllocator>::emplace(const_iterator pos, Args &&...args) {
    const node_type node {this->allocate_values(1, ds::forward<Args>(args)...)};
    node->next = pos.node;
    node->previous = pos.node->previous;
    pos.node->previous->next = node;
    pos.node->previous = node;
    return iterator {pos.node};
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr typename list<T, Allocator, NodeAllocator>::iterator
list<T, Allocator, NodeAllocator>::insert(size_type pos, rvalue_reference value) {
    auto cursor {this->tail.next};
    while(pos-- not_eq 0) {
        cursor = cursor->next;
    }
    return this->emplace(const_iterator {cursor->node()}, ds::move(value));
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr typename list<T, Allocator, NodeAllocator>::iterator
list<T, Allocator, NodeAllocator>::insert(const_iterator pos, rvalue_reference value) {
    return this->emplace(pos, ds::move(value));
}
template <typename T, typename Allocator, typename NodeAllocator>
template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
constexpr typename list<T, Allocator, NodeAllocator>::iterator
list<T, Allocator, NodeAllocator>::insert(size_type pos, InputIterator begin, InputIterator end,
        size_type default_size) {
    buffer<T, Allocator> b(begin, end, default_size);
    auto cursor {this->tail.next};
    while(pos-- not_eq 0) {
        cursor = cursor->next;
    }
    return this->insert(const_iterator {cursor->node()}, b.mbegin(), b.mend());
}
template <typename T, typename Allocator, typename NodeAllocator>
template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
constexpr typename list<T, Allocator, NodeAllocator>::iterator
list<T, Allocator, NodeAllocator>::insert(const_iterator pos, InputIterator begin, InputIterator end,
        size_type default_size) {
    buffer<T, Allocator> b(begin, end, default_size);
    return this->insert(pos, b.mbegin(), b.mend());
}
template <typename T, typename Allocator, typename NodeAllocator>
template <IsForwardIterator ForwardIterator>
constexpr typename list<T, Allocator, NodeAllocator>::iterator
list<T, Allocator, NodeAllocator>::insert(size_type pos, ForwardIterator begin, ForwardIterator end) {
    auto cursor {this->tail.next};
    while(pos-- not_eq 0) {
        cursor = cursor->next;
    }
    return this->insert(const_iterator {cursor->node()}, begin, end);
}
template <typename T, typename Allocator, typename NodeAllocator>
template <IsForwardIterator ForwardIterator>
constexpr typename list<T, Allocator, NodeAllocator>::iterator
list<T, Allocator, NodeAllocator>::insert(const_iterator pos, ForwardIterator begin, ForwardIterator end) {
    if(begin == end) {
        return iterator {pos.node};
    }
    const auto n {static_cast<size_type>(ds::distance(begin, end))};
    const auto [first_node, last_node] {this->allocate_values(n, begin)};
    first_node->previous = pos.node->previous;
    last_node->next = pos.node;
    pos.node->previous->next = first_node;
    pos.node->previous = last_node;
    this->node_size() += n;
    return iterator {first_node};
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr typename list<T, Allocator, NodeAllocator>::iterator
list<T, Allocator, NodeAllocator>::insert(size_type pos, initializer_list<T> init_list) {
    auto cursor {this->tail.next};
    while(pos-- not_eq 0) {
        cursor = cursor->next;
    }
    return this->insert(const_iterator {cursor->node()}, init_list.begin(), init_list.end());
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr typename list<T, Allocator, NodeAllocator>::iterator
list<T, Allocator, NodeAllocator>::insert(const_iterator pos, initializer_list<T> init_list) {
    return this->insert(pos, init_list.begin(), init_list.end());
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr typename list<T, Allocator, NodeAllocator>::iterator
list<T, Allocator, NodeAllocator>::erase(size_type pos, size_type n) {
    auto begin {this->tail.next};
    while(pos-- not_eq 0) {
        begin = begin->next;
    }
    auto end {begin};
    for(auto i {0}; i < n; ++i, static_cast<void>(end = end->next));
    return this->erase(const_iterator {begin}, const_iterator {end}, n);
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr typename list<T, Allocator, NodeAllocator>::iterator
list<T, Allocator, NodeAllocator>::erase(const_iterator begin, size_type n) {
    auto end {begin};
    for(auto i {0}; i < n; ++i, static_cast<void>(end = end->next));
    return this->erase(const_iterator {begin}, const_iterator {end}, n);
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr typename list<T, Allocator, NodeAllocator>::iterator
list<T, Allocator, NodeAllocator>::erase(const_iterator pos) {
    const auto result_node {pos.node->next};
    result_node->previous = pos.node->previous;
    pos.node->previous->next = result_node;
    if constexpr(__dsa::IsLinkedAfterAllocation<real_allocator>) {
        ds::destroy(ds::address_of(pos.node->value));
        this->node_size.allocator().deallocate(pos.node);
    }else {
        this->node_size.allocator().deallocate<true>(pos.node);
    }
    return iterator {result_node->node()};
}
template <typename T, typename Allocator, typename NodeAllocator>
constexpr typename list<T, Allocator, NodeAllocator>::iterator
list<T, Allocator, NodeAllocator>::erase(const_iterator begin, const_iterator end) {
    const auto result_node {end.node->next};
    this->erase(begin.node, end.node, static_cast<size_type>(ds::distance(begin, end)));
    return iterator {result_node->node()};
}
__DATA_STRUCTURE_END(list implementation)

}       // namespace data_structure

#endif      // DATA_STRUCTURE_LIST_HPP