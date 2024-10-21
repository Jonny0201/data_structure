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

#ifndef DATA_STRUCTURE_DEQUE_HPP
#define DATA_STRUCTURE_DEQUE_HPP

#include <deque>
#include <map>

#include "allocator.hpp"

namespace data_structure {

__DATA_STRUCTURE_START(deque declaration)
template <typename T, typename Allocator = allocator<T>>
class deque {
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
    using iterator = __dsa::deque_iterator<T>;
    using const_iterator = __dsa::deque_iterator<T, true>;
    using reverse_iterator = reverse_iterator<iterator>;
    using const_reverse_iterator = ds::reverse_iterator<const_iterator>;
    static_assert(is_same_v<T, typename Allocator::value_type>,
            "The value type of deque should be same as the allocator's value_type!");
private:
    using map_allocator = typename allocator_traits<Allocator>::template rebind<T *>;
    template <bool>
    struct map_allocation_handler;
    struct construction_handler;
public:
    static constexpr auto block_size {sizeof(T) < 256 ? 4096 / sizeof(T) : 16};
private:
    T **map;
    __dsa::allocator_compressor<size_type, map_allocator> map_size;
    size_type first;
    __dsa::allocator_compressor<size_type, Allocator> element_size;
private:
    template <bool, bool>
    constexpr void allocate_blocks(size_type n);
    template <typename ...Args>
    constexpr void construct_with_value(size_type, size_type, Args &&...)
            noexcept(is_nothrow_constructible_v<T, Args...>);
    template <IsInputIterator InputIterator>
    constexpr void construct_with_range(size_type, size_type, InputIterator)
            noexcept(is_nothrow_constructible_v<T, typename iterator_traits<InputIterator>::reference>);
    constexpr void move_range(size_type, size_type, size_type)
            noexcept(is_nothrow_move_assignable_v<T> or is_nothrow_copy_assignable_v<T>);
public:
    constexpr deque() noexcept(is_nothrow_copy_constructible_v<Allocator> and
            is_nothrow_default_constructible_v<map_allocator>) = default;
    explicit constexpr deque(const Allocator &) noexcept(is_nothrow_copy_constructible_v<Allocator> and
            is_nothrow_default_constructible_v<map_allocator>);
    explicit constexpr deque(size_type, const Allocator & = {});
    constexpr deque(size_type, const_reference, const Allocator & = {});
    template <IsInputIterator InputIterator>
    constexpr deque(InputIterator, InputIterator, const Allocator & = {});
    constexpr deque(initializer_list<T>, const Allocator & = {});
    constexpr deque(const deque &);
    constexpr deque(const deque &, const Allocator &);
    constexpr deque(deque &&) noexcept;
    constexpr deque(deque &&, const Allocator &) noexcept(is_nothrow_copy_constructible_v<Allocator>);
    constexpr ~deque() noexcept;
public:
    constexpr deque &operator=(const deque &);
    constexpr deque &operator=(deque &&) noexcept;
    constexpr deque &operator=(initializer_list<T>);
    constexpr reference operator[](size_type) noexcept;
    constexpr const_reference operator[](size_type) const noexcept;
public:
    constexpr void assign(size_type, const_reference = {});
    template <IsInputIterator InputIterator>
    constexpr void assign(InputIterator, InputIterator);
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
    [[nodiscard]]
    constexpr size_type capacity() const noexcept;
    [[nodiscard]]
    constexpr size_type front_spare() const noexcept;
    [[nodiscard]]
    constexpr size_type back_spare() const noexcept;
    [[nodiscard]]
    constexpr size_type spare() const noexcept;
    constexpr void reserve_back(size_type);
    constexpr void reserve_front(size_type);
    constexpr void shrink_to_fit();
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
    constexpr void push_back(const_reference);
    constexpr void push_back(rvalue_reference);
    template <typename ...Args>
    constexpr void emplace_back(Args &&...);
    constexpr void push_front(const_reference);
    constexpr void push_front(rvalue_reference);
    template <typename ...Args>
    constexpr void emplace_front(Args &&...);
    constexpr void pop_back() noexcept;
    constexpr void pop_front() noexcept;
    constexpr void clear() noexcept;
    constexpr void swap(deque &) noexcept;
    constexpr iterator insert(size_type, const_reference, size_type = 1);
    constexpr iterator insert(const_iterator, const_reference, size_type = 1);
    template <typename ...Args>
    constexpr iterator emplace(size_type, Args &&...);
    template <typename ...Args>
    constexpr iterator emplace(const_iterator, Args &&...);
    constexpr iterator insert(size_type, rvalue_reference);
    constexpr iterator insert(const_iterator, rvalue_reference);
    template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
    constexpr iterator insert(size_type, InputIterator, InputIterator);
    template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
    constexpr iterator insert(const_iterator, InputIterator, InputIterator);
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
__DATA_STRUCTURE_END(deque declaration)

__DATA_STRUCTURE_START(deque implementation)
/* exception handlers */
template <typename T, typename Allocator>
template <bool AppendToTail>
struct deque<T, Allocator>::map_allocation_handler {
    T **map;
    size_type map_size;
    size_type i {0};
    Allocator &allocator;
    typename allocator_traits<Allocator>::template rebind<T *> &map_allocator;
    constexpr map_allocation_handler(T **map, size_type map_size, Allocator &allocator,
            typename allocator_traits<Allocator>::template rebind<T *> &map_allocator) :
            map {map}, map_size {map_size}, allocator {allocator}, map_allocator {map_allocator} {}
    constexpr void operator()() const noexcept {
        while(i not_eq 0) {
            if constexpr(AppendToTail) {
                this->allocator.deallocate(this->map[this->map_size - (i + 1)], deque::block_size);
            }else {
                this->allocator.deallocate(this->map[i], deque::block_size);
            }
            --i;
        }
        this->map_allocator.deallocate(this->map, this->map_size);
    }
};
template <typename T, typename Allocator>
struct deque<T, Allocator>::construction_handler {
    T *const *map;
    size_type from;
    size_type i {0};
    constexpr void operator()() noexcept {
        if(i - from <= deque::block_size) {
            const auto start_from {*this->map + this->from};
            ds::destroy(start_from, start_from + this->i);
        }else {
            ds::destroy(*this->map + this->from, *this->map + deque::block_size);
            ++this->map;
            this->from += deque::block_size - this->from % deque::block_size;
            while(this->i - this->from > deque::block_size) {
                ds::destroy(*this->map, *this->map + deque::block_size);
                ++this->map;
                this->from += deque::block_size;
            }
            if(const auto remaining {this->i - this->from}; remaining > 0) {
                ds::destroy(*this->map, *this->map + remaining);
            }
        }
    }
};

/* private functions */
template <typename T, typename Allocator>
template <bool AppendToTail, bool FromConstructor>
constexpr void deque<T, Allocator>::allocate_blocks(size_type n) {
    const auto offset_in_block {n % deque::block_size};
    const auto append_size {n / deque::block_size + (offset_in_block == 0 ? 0 : 1)};
    auto &map_size {this->map_size()};
    const auto allocation_size {append_size + this->map_size()};
    auto &map_allocator {this->map_size.allocator()};
    const auto new_map {map_allocator.allocate(allocation_size)};
    if constexpr(not FromConstructor) {
        if constexpr(AppendToTail) {
            ds::memory_set(new_map, this->map, this->map_size() * sizeof(T **));
        }else {
            ds::memory_set(new_map + append_size, this->map, this->map_size() * sizeof(T **));
        }
    }
    auto &allocator {this->element_size.allocator()};
    auto trans {transaction {map_allocation_handler<AppendToTail>(new_map, allocation_size, allocator,
            this->map_size.allocator())}};
    for(auto &i {trans.get_rollback().i}; i < append_size; ++i) {
        if constexpr(FromConstructor or not AppendToTail) {
            this->map[i] = allocator.allocate(deque::block_size);
        }else {
            this->map[map_size + i] = allocator.allocate(deque::block_size);
        }
    }
    trans.complete();
    map_allocator.deallocate(this->map, map_size);
    this->map = new_map;
    this->map_size = allocation_size;
}
template <typename T, typename Allocator>
template <typename ...Args>
constexpr void deque<T, Allocator>::construct_with_value(size_type from, size_type to, Args &&...args)
        noexcept(is_nothrow_constructible_v<T, Args...>) {
    T *const *map {this->map + from / deque::block_size};
    auto trans {transaction {construction_handler {map, from}}};
    if(const auto first_block_end {(from / deque::block_size + 1) * deque::block_size}; to < first_block_end) {
        from %= deque::block_size;
        to %= deque::block_size;
        while(from not_eq to) {
            ds::construct(*map + from, ds::forward<Args>(args)...);
        }
        trans.complete();
        return;
    }else {
        from %= deque::block_size;
        while(from < deque::block_size) {
            ds::construct(*map + from, ds::forward<Args>(args)...);
        }
        from = first_block_end;
    }
    ++map;
    while(to - from > deque::block_size) {
        for(auto i {0}; i < deque::block_size; ++i) {
            ds::construct(*map + i, ds::forward<Args>(args)...);
        }
        from += deque::block_size;
        ++map;
    }
    if(from not_eq to) {
        to %= deque::block_size;
        size_type i {0};
        do {
            ds::construct(*map + i, ds::forward<Args>(args)...);
            ++i;
        }while(i not_eq to);
    }
    trans.complete();
}
template <typename T, typename Allocator>
template <IsInputIterator InputIterator>
constexpr void deque<T, Allocator>::construct_with_range(size_type from, size_type to, InputIterator begin)
        noexcept(is_nothrow_constructible_v<T, typename iterator_traits<InputIterator>::reference>) {
    T *const *map {this->map + from / deque::block_size};
    auto trans {transaction {construction_handler {map, from}}};
    if(const auto first_block_end {(from / deque::block_size + 1) * deque::block_size}; to < first_block_end) {
        from %= deque::block_size;
        to %= deque::block_size;
        while(from not_eq to) {
            ds::construct(*map + from, ds::move_if<not is_forward_iterator_v<InputIterator>>(*begin++));
        }
        trans.complete();
        return;
    }else {
        from %= deque::block_size;
        while(from < deque::block_size) {
            ds::construct(*map + from, ds::move_if<not is_forward_iterator_v<InputIterator>>(*begin++));
        }
        from = first_block_end;
    }
    ++map;
    while(to - from > deque::block_size) {
        for(auto i {0}; i < deque::block_size; ++i) {
            ds::construct(*map + i, ds::move_if<not is_forward_iterator_v<InputIterator>>(*begin++));
        }
        from += deque::block_size;
        ++map;
    }
    if(from not_eq to) {
        to %= deque::block_size;
        size_type i {0};
        do {
            ds::construct(*map + i, ds::move_if<not is_forward_iterator_v<InputIterator>>(*begin++));
            ++i;
        }while(i not_eq to);
    }
    trans.complete();
}
template <typename T, typename Allocator>
constexpr void deque<T, Allocator>::move_range(size_type from, size_type to, size_type destination)
        noexcept(is_nothrow_move_assignable_v<T> or is_nothrow_copy_assignable_v<T>) {
    if constexpr(is_trivially_copy_assignable_v<T>) {
        auto start {this->begin() + from};
        auto end {this->begin() + --to};
        auto new_end {this->begin() + (destination + to - from)};
        while(start not_eq end) {
            const auto end_offset {static_cast<size_type>(end.map == start.map ?
                    end.pos - start.pos : end.pos - *end.map) + 1};
            const auto new_end_offset {static_cast<size_type>(new_end.pos - *new_end.map) + 1};
            if(new_end_offset < end_offset) {
                ds::memory_move(*new_end.map, end.pos - (new_end_offset - 1), new_end_offset * sizeof(T));
                end -= new_end_offset;
                new_end -= new_end_offset;
            }else {
                ds::memory_move(new_end.pos - (end_offset - 1), *end.map, end_offset * sizeof(T));
                end -= end_offset;
                new_end -= end_offset;
            }
        }
    }else {
        auto start {this->begin() + from};
        auto end {this->begin() + --to};
        auto new_end {this->begin() + (destination + to - from)};
        while(start not_eq end) {
            *new_end-- = ds::move(*end--);
        }
    }
}
template <typename T, typename Allocator>
constexpr deque<T, Allocator>::size_type deque<T, Allocator>::total_size() const noexcept {

}

/* public functions */
template <typename T, typename Allocator>
constexpr deque<T, Allocator>::deque(const Allocator &allocator) noexcept(is_nothrow_copy_constructible_v<Allocator> and
    is_nothrow_default_constructible_v<map_allocator>) : map {}, map_size {}, first {}, element_size(allocator) {}
template <typename T, typename Allocator>
constexpr deque<T, Allocator>::deque(size_type n, const Allocator &allocator) : deque(allocator) {
    this->allocate_blocks<true, true>(n);
    this->construct_with_value(0, n + 1);
    this->element_size() = n;
}
template <typename T, typename Allocator>
constexpr deque<T, Allocator>::deque(size_type n, const_reference value, const Allocator &allocator) :
        deque(allocator) {
    this->allocate_blocks<true, true>(n);
    this->construct_with_value(0, n + 1, value);
    this->element_size() = n;
}
template <typename T, typename Allocator>
template <IsInputIterator InputIterator>
constexpr deque<T, Allocator>::deque(InputIterator begin, InputIterator end, const Allocator &allocator) :
        deque(allocator) {
    const auto n {static_cast<size_type>(ds::distance(begin, end))};
    this->allocate_blocks<true, true>(n);
    this->construct_with_range(0, n + 1, begin);
    this->element_size() = n;
}
template <typename T, typename Allocator>
constexpr deque<T, Allocator>::deque(initializer_list<T> init_list, const Allocator &allocator) :
        deque(init_list.begin(), init_list.end(), allocator) {}
template <typename T, typename Allocator>
constexpr deque<T, Allocator>::deque(const deque &rhs) : deque(rhs.cbegin(), rhs.cend(), rhs.allocator()) {}
template <typename T, typename Allocator>
constexpr deque<T, Allocator>::deque(const deque &rhs, const Allocator &allocator) :
        deque(rhs.cbegin(), rhs.cend(), allocator) {}
template <typename T, typename Allocator>
constexpr deque<T, Allocator>::deque(deque &&rhs) noexcept : map {ds::move(rhs.map)}, map_size {ds::move(rhs.map_size)},
        first {ds::move(rhs.first)}, element_size {ds::move(rhs.element_size)} {
    rhs.map = nullptr;
    rhs.map_size() = 0;
    rhs.first = 0;
    rhs.element_size() = 0;
}
template <typename T, typename Allocator>
constexpr deque<T, Allocator>::deque(deque &&rhs, const Allocator &allocator) : map {ds::move(rhs.map)},
        map_size {ds::move(rhs.map_size)}, first {ds::move(rhs.first)},
        element_size(ds::move(rhs.element_size()), allocator) {
    rhs.map = nullptr;
    rhs.map_size() = 0;
    rhs.first = 0;
    rhs.element_size() = 0;
}
template <typename T, typename Allocator>
constexpr deque<T, Allocator>::~deque() noexcept {
    const auto end {this->end()};
    for(auto it {this->begin()}; it not_eq end; ++it) {
        ds::destroy(ds::address_of(*it));
    }
    auto &allocator {this->element_size.allocator()};
    for(auto i {0}; i < this->map_size(); ++i) {
        allocator.deallocate(this->map[i]);
    }
    this->map_size.allocator().deallocate(this->map);
}
template <typename T, typename Allocator>
constexpr deque<T, Allocator> &deque<T, Allocator>::operator=(const deque &rhs) {
    if(&rhs not_eq this) {
        this->assign(rhs.begin(), rhs.end());
    }
    return *this;
}
template <typename T, typename Allocator>
constexpr deque<T, Allocator> &deque<T, Allocator>::operator=(deque &&rhs) noexcept {
    if(&rhs not_eq this) {
        this->~deque();
        this->map = rhs.map;
        this->map_size = ds::move(rhs.map_size);
        this->first = ds::move(rhs.first);
        this->element_size = ds::move(rhs.element_size);
    }
    return *this;
}
template <typename T, typename Allocator>
constexpr deque<T, Allocator> &deque<T, Allocator>::operator=(initializer_list<T> init_list) {
    this->assign(init_list.begin(), init_list.end());
    return *this;
}
template <typename T, typename Allocator>
constexpr typename deque<T, Allocator>::reference deque<T, Allocator>::operator[](size_type i) noexcept {
    return *(this->begin() + i);
}
template <typename T, typename Allocator>
constexpr typename deque<T, Allocator>::const_reference deque<T, Allocator>::operator[](size_type i) const noexcept {
    return *(this->cbegin() + i);
}
template <typename T, typename Allocator>
constexpr void deque<T, Allocator>::assign(size_type n, const_reference value) {
    auto it {this->begin()};
    const auto end {this->end()};
    size_type i {0};
    const auto size {this->element_size()};
    this->element_size() = n;
    for(; i not_eq n and it not_eq end; ++i) {
        *it++ = value;
    }
    if(it not_eq end) {
        do {
            ds::destroy(ds::address_of(*it++));
        }while(it not_eq end);
        return;
    }
    const auto remaining {n - i};
    if(remaining < this->back_spare()) {
        this->construct_with_range(size, n, value);
        return;
    }
    if(const auto capacity {this->capacity()}; n < capacity) {
        this->construct_with_range(size, capacity, value);
        this->construct_with_range(this->first - (remaining - (capacity - size)), this->first, value);
        return;
    }
    this->allocate_blocks<true, false>(remaining);
    this->construct_with_range(size, size + remaining, value);
}
template <typename T, typename Allocator>
template <IsInputIterator InputIterator>
constexpr void deque<T, Allocator>::assign(InputIterator begin, InputIterator end) {
    const auto n {ds::distance(begin, end)};
    auto it {this->begin()};
    const auto end {this->end()};
    size_type i {0};
    const auto size {this->element_size()};
    this->element_size() = n;
    for(; i not_eq n and it not_eq end; ++i) {
        *it++ = *begin++;
    }
    if(it not_eq end) {
        do {
            ds::destroy(ds::address_of(*it++));
        }while(it not_eq end);
        return;
    }
    const auto remaining {n - i};
    if(remaining < this->back_spare()) {
        this->construct_with_range(size, n, begin);
        return;
    }
    this->allocate_blocks<true, false>(remaining);
    this->construct_with_range(size, size + remaining, begin);
}
template <typename T, typename Allocator>
constexpr void deque<T, Allocator>::assign(initializer_list<T> init_list) {
    this->assign(init_list.begin(), init_list.end());
}
template <typename T, typename Allocator>
constexpr typename deque<T, Allocator>::iterator deque<T, Allocator>::begin() noexcept {
    const auto map {this->map + this->first / deque::block_size};
    return iterator(map, *map + this->first % deque::block_size);
}
template <typename T, typename Allocator>
constexpr typename deque<T, Allocator>::const_iterator deque<T, Allocator>::begin() const noexcept {
    const auto map {this->map + this->first / deque::block_size};
    return const_iterator(map, *map + this->first % deque::block_size);
}
template <typename T, typename Allocator>
constexpr typename deque<T, Allocator>::const_iterator deque<T, Allocator>::cbegin() const noexcept {
    return this->begin();
}
template <typename T, typename Allocator>
constexpr typename deque<T, Allocator>::iterator deque<T, Allocator>::end() noexcept {
    const auto last {this->first + this->element_size()};
    const auto map {this->map + last / deque::block_size};
    return iterator(map, *map + last % deque::block_size);
}
template <typename T, typename Allocator>
constexpr typename deque<T, Allocator>::const_iterator deque<T, Allocator>::end() const noexcept {
    const auto last {this->first + this->element_size()};
    const auto map {this->map + last / deque::block_size};
    return const_iterator(map, *map + last % deque::block_size);
}
template <typename T, typename Allocator>
constexpr typename deque<T, Allocator>::const_iterator deque<T, Allocator>::cend() const noexcept {
    return this->end();
}
template <typename T, typename Allocator>
constexpr typename deque<T, Allocator>::reverse_iterator deque<T, Allocator>::rbegin() noexcept {
    return reverse_iterator {this->begin()};
}
template <typename T, typename Allocator>
constexpr typename deque<T, Allocator>::const_reverse_iterator deque<T, Allocator>::rbegin() const noexcept {
    return const_reverse_iterator {this->begin()};
}
template <typename T, typename Allocator>
constexpr typename deque<T, Allocator>::const_reverse_iterator deque<T, Allocator>::crbegin() const noexcept {
    return const_reverse_iterator {this->begin()};
}
template <typename T, typename Allocator>
constexpr typename deque<T, Allocator>::reverse_iterator deque<T, Allocator>::rend() noexcept {
    return reverse_iterator {this->end()};
}
template <typename T, typename Allocator>
constexpr typename deque<T, Allocator>::const_reverse_iterator deque<T, Allocator>::rend() const noexcept {
    return const_reverse_iterator {this->end()};
}
template <typename T, typename Allocator>
constexpr typename deque<T, Allocator>::const_reverse_iterator deque<T, Allocator>::crend() const noexcept {
    return const_reverse_iterator {this->end()};
}
template <typename T, typename Allocator>
constexpr typename deque<T, Allocator>::size_type deque<T, Allocator>::size() const noexcept {
    return this->element_size();
}
template <typename T, typename Allocator>
constexpr bool deque<T, Allocator>::empty() const noexcept {
    return this->element_size() == 0;
}
template <typename T, typename Allocator>
constexpr typename deque<T, Allocator>::size_type deque<T, Allocator>::capacity() const noexcept {
    return this->map_size() * deque::block_size;
}
template <typename T, typename Allocator>
constexpr typename deque<T, Allocator>::size_type deque<T, Allocator>::front_spare() const noexcept {
    return this->first;
}
template <typename T, typename Allocator>
constexpr typename deque<T, Allocator>::size_type deque<T, Allocator>::back_spare() const noexcept {
    return this->capacity() - this->element_size();
}
template <typename T, typename Allocator>
constexpr typename deque<T, Allocator>::size_type deque<T, Allocator>::spare() const noexcept {
    return this->first + this->capacity() - this->element_size();
}
template <typename T, typename Allocator>
constexpr void deque<T, Allocator>::reserve_back(size_type n) {
    const auto back_spare {this->back_spare()};
    if(n <= back_spare) {
        return;
    }
    this->allocate_blocks<true, false>(n - back_spare);
}
template <typename T, typename Allocator>
constexpr void deque<T, Allocator>::reserve_front(size_type n) {
    const auto front_spare {this->front_spare()};
    if(n <= front_spare) {
        return;
    }
    this->allocate_blocks<false, false>(n - front_spare);
}
__DATA_STRUCTURE_END(deque implementation)

}

#endif      //DATA_STRUCTURE_DEQUE_HPP
