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

#ifndef DATA_STRUCTURE_VECTOR_HPP
#define DATA_STRUCTURE_VECTOR_HPP

#include "allocator.hpp"
#include "iterator.hpp"
#include "buffer.hpp"

namespace data_structure {

__DATA_STRUCTURE_START(vector declaration)
template <typename T, typename Allocator = allocator<T>>
class vector {
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
    using iterator = wrap_iterator<pointer>;
    using const_iterator = wrap_iterator<const_pointer>;
    using reverse_iterator = reverse_iterator<pointer>;
    using const_reverse_iterator = ds::reverse_iterator<const_pointer>;
    static_assert(is_same_v<T, typename Allocator::value_type>,
            "The value type of vector should be same as the allocator's value_type!");
private:
    struct resize_handler;
    friend struct resize_handler;
    struct insertion_handler;
    struct reallocation_handler;
private:
    pointer first {};
    pointer cursor {};
    __dsa::allocator_compressor<pointer, Allocator> last {};
private:
    constexpr void move_to(pointer, pointer, pointer, size_type);
    template <bool = false>
    constexpr void assign_with_buffer(buffer<T, Allocator> &&b) noexcept;
    constexpr void resize_and_move(size_type, size_type);
    template <typename ...Args>
    constexpr void copy_value(pointer, size_type, size_type, size_type, Args &&...)
            noexcept(is_nothrow_constructible_v<T, Args...>);
    template <typename Iterator>
    constexpr void copy_range(pointer, size_type, size_type, Iterator, Iterator)
            noexcept(is_nothrow_constructible_v<T, typename iterator_traits<Iterator>::reference>);
    template <bool = true, typename ...Args>
    constexpr void reallocate_when_insertion(size_type, size_type, size_type, Args &&...);
    constexpr bool is_insertion_value_need_fix(const_pointer, const_pointer) noexcept;
public:
    constexpr vector() noexcept(is_nothrow_default_constructible_v<Allocator>) = default;
    explicit constexpr vector(const Allocator &) noexcept;
    explicit constexpr vector(size_type, const Allocator & = {});
    constexpr vector(size_type, const_reference, const Allocator & = {});
    template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
    constexpr vector(InputIterator, InputIterator, const Allocator & = {}, size_type = 64);
    template <IsForwardIterator ForwardIterator>
    constexpr vector(ForwardIterator, ForwardIterator, const Allocator & = {});
    constexpr vector(initializer_list<T>, const Allocator & = {});
    constexpr vector(const vector &);
    constexpr vector(const vector &, const Allocator &);
    constexpr vector(vector &&) noexcept;
    constexpr vector(vector &&, const Allocator &) noexcept;
    constexpr ~vector() noexcept;
public:
    constexpr vector &operator=(const vector &);
    constexpr vector &operator=(vector &&) noexcept;
    constexpr vector &operator=(initializer_list<T>);
    [[nodiscard]]
    constexpr reference operator[](size_type) noexcept(is_nothrow_indexable_v<pointer, size_type>);
    [[nodiscard]]
    constexpr const_reference operator[](size_type) const
            noexcept(is_nothrow_indexable_v<pointer, size_type>);
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
    [[nodiscard]]
    constexpr size_type capacity() const noexcept;
    [[nodiscard]]
    constexpr size_type spare() const noexcept;
    constexpr void reserve(size_type);
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
    constexpr pointer data() noexcept;
    [[nodiscard]]
    constexpr const_pointer data() const noexcept;
    [[nodiscard]]
    constexpr Allocator allocator() const noexcept;
    constexpr void push_back(const_reference);
    constexpr void push_back(rvalue_reference);
    template <typename ...Args>
    constexpr void emplace_back(Args &&...);
    constexpr void pop_back() noexcept;
    constexpr void clear() noexcept;
    constexpr void swap(vector &) noexcept;
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
template <typename T, typename Allocator>
inline constexpr void swap(vector<T, Allocator> &, vector<T, Allocator> &) noexcept;
// Todo : wait for header "compare.hpp"?
/*template <typename T, typename Allocator>
inline constexpr some_ordering operator<=>(vector<T, Allocator> &, vector<T, Allocator> &)
        noexcept(is_nothrow_three_way_comparable_v<T>);*/
__DATA_STRUCTURE_END(vector declaration)

__DATA_STRUCTURE_START(vector implementation)

/* private types */
template <typename T, typename Allocator>
struct vector<T, Allocator>::resize_handler {
    Allocator &allocator;
    pointer &new_place;
    size_type new_size;
    size_type i {0};
    constexpr resize_handler(vector &v, pointer &new_place, size_type new_size) noexcept :
            allocator {v.last.allocator()}, new_place {new_place}, new_size {new_size} {}
    constexpr void operator()() noexcept {
        ds::destroy(this->new_place, this->new_place + this->i);
        this->allocator.deallocate(this->new_place, this->new_size);
    }
};
template <typename T, typename Allocator>
struct vector<T, Allocator>::insertion_handler {
    pointer begin;
    pointer end;
    constexpr void operator()() noexcept {
        ds::destroy(this->begin, this->end);
    }
};
template <typename T, typename Allocator>
struct vector<T, Allocator>::reallocation_handler {
    Allocator &allocator;
    pointer new_place;
    pointer begin;
    size_type new_size;
    size_type i {0};
    reallocation_handler(vector &v, pointer new_place, pointer begin, size_type new_size) noexcept :
            allocator {v.last.allocator()}, new_place {new_place}, begin {begin}, new_size {new_size} {}
    constexpr void operator()() noexcept {
        ds::destroy(this->begin, this->begin + i);
        this->allocator.deallocate(this->new_place, this->new_size);
    }
};

/* private functions */
template <typename T, typename Allocator>
constexpr void vector<T, Allocator>::move_to(pointer new_place, pointer begin, pointer end, size_type n) {
    if constexpr(is_pointer_v<pointer> and is_trivially_copyable_v<T>) {
        ds::memory_copy(new_place, begin, sizeof(T) * static_cast<size_t>(end - begin));
    }else {
        auto trans {transaction {resize_handler(*this, new_place, n)}};
        for(auto &i {trans.get_rollback().i}; begin not_eq end; ++i) {
            ds::construct(new_place + i, ds::move(*begin++));
        }
        trans.complete();
    }
}
template <typename T, typename Allocator>
template <bool ReleaseThis>
constexpr void vector<T, Allocator>::assign_with_buffer(buffer<T, Allocator> &&b) noexcept {
    if constexpr(ReleaseThis) {
        this->~vector();
    }
    this->first = b.release();
    this->cursor = this->last() = this->first + b.size();
}
template <typename T, typename Allocator>
constexpr void vector<T, Allocator>::resize_and_move(size_type n, size_type size) {
    if constexpr(is_trivially_copyable_v<T>) {
        this->first = this->last.allocator().reallocate(this->first, n);
    }else {
        auto new_first {this->last.allocator().allocate(n)};
        auto trans {transaction {resize_handler(*this, new_first, n)}};
        const auto move_size {size < n ? size : n};
        for(auto &i {trans.get_rollback().i}; i < move_size; ++i) {
            ds::construct(new_first + i, ds::move(this->first[i]));
        }
        this->first = ds::move(new_first);
        trans.complete();
    }
}
template <typename T, typename Allocator>
template <typename ...Args>
constexpr void vector<T, Allocator>::copy_value(pointer new_first, size_type n, size_type pos,
        size_type allocation_size, Args &&...args) noexcept(is_nothrow_constructible_v<T, Args...>) {
    transaction trans {reallocation_handler(*this, new_first, new_first + pos, allocation_size)};
    for(auto &i {trans.get_rollback().i}; i < n; ++i) {
        ds::construct(new_first + (pos + i), ds::forward<Args>(args)...);
    }
    trans.complete();
}
template <typename T, typename Allocator>
template <typename Iterator>
constexpr void vector<T, Allocator>::copy_range(pointer new_first, size_type pos, size_type allocation_size,
        Iterator begin, Iterator end)
        noexcept(is_nothrow_constructible_v<T, typename iterator_traits<Iterator>::reference>) {
    transaction trans {reallocation_handler(*this, new_first, new_first + pos, allocation_size)};
    for(auto &i {trans.get_rollback().i}; begin not_eq end; ++i) {
        ds::construct(new_first + (pos + i), *begin++);
    }
    trans.complete();
}
template <typename T, typename Allocator>
template <bool Value, typename ...Args>
constexpr void vector<T, Allocator>::reallocate_when_insertion(size_type n, size_type old_size, size_type pos,
        Args &&...args) {
    auto allocation_size {this->capacity() * 2};
    const auto new_size {old_size + n};
    if(allocation_size < new_size) {
        allocation_size = new_size;
    }
    auto new_first {this->last.allocator().allocate(allocation_size)};
    if constexpr(Value) {
        this->copy_value(new_first, n, pos, allocation_size, ds::forward<Args>(args)...);
    }else {
        this->copy_range(new_first, pos, allocation_size, ds::forward<Args>(args)...);
    }
    if constexpr(is_trivially_copyable_v<T> and is_pointer_v<pointer>) {
        if(old_size > 0) {
            ds::memory_copy(new_first, this->first, sizeof(T) * pos);
            ds::memory_copy(new_first + pos + n, this->first + pos, sizeof(T) * (old_size - pos));
        }
        this->first = ds::move(new_first);
    }else {
        transaction trans {resize_handler(*this, new_first, allocation_size)};
        auto &i {trans.get_rollback().i};
        for(; i < pos; ++i) {
            ds::construct(new_first + i, ds::move(this->first[i]));
        }
        i += n;
        const auto total_size {old_size + n};
        for(auto j {pos}; i < total_size; ++i, static_cast<void>(++j)) {
            ds::construct(new_first + i, ds::move(this->first[j]));
        }
        trans.complete();
        this->first = ds::move(new_first);
    }
    this->cursor = this->first + new_size;
    this->last() = this->first + allocation_size;
}
template <typename T, typename Allocator>
constexpr bool vector<T, Allocator>::is_insertion_value_need_fix(const_pointer position,
        const_pointer pointer_to_value) noexcept {
    // Todo : The comparison is not allowed in compile time
    return position <= pointer_to_value and pointer_to_value < this->cursor;
}

/* public functions */
template <typename T, typename Allocator>
constexpr vector<T, Allocator>::vector(const Allocator &allocator) noexcept : first {}, cursor {}, last(allocator) {}
template <typename T, typename Allocator>
constexpr vector<T, Allocator>::vector(size_type n, const Allocator &allocator) : first {}, cursor {}, last(allocator) {
    this->assign_with_buffer(buffer<T, Allocator>(n, allocator));
}
template <typename T, typename Allocator>
constexpr vector<T, Allocator>::vector(size_type n, const_reference value, const Allocator &allocator) :
        first {}, cursor {}, last(allocator) {
    this->assign_with_buffer(buffer<T, Allocator>(n, value, allocator));
}
template <typename T, typename Allocator>
template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
constexpr vector<T, Allocator>::vector(InputIterator begin, InputIterator end, const Allocator &allocator,
        size_type default_size) : first {}, cursor {}, last(allocator) {
    this->assign_with_buffer(buffer<T, Allocator>(begin, end, allocator, default_size));
}
template <typename T, typename Allocator>
template <IsForwardIterator ForwardIterator>
constexpr vector<T, Allocator>::vector(ForwardIterator begin, ForwardIterator end, const Allocator &allocator) :
        first {}, cursor {}, last(allocator) {
    this->assign_with_buffer(buffer<T, Allocator>(begin, end, allocator));
}
template <typename T, typename Allocator>
constexpr vector<T, Allocator>::vector(initializer_list<T> init_list, const Allocator &allocator) :
        vector(init_list.begin(), init_list.end(), allocator) {}
template <typename T, typename Allocator>
constexpr vector<T, Allocator>::vector(const vector &rhs) : vector(rhs.cbegin(), rhs.cend(), rhs.allocator()) {}
template <typename T, typename Allocator>
constexpr vector<T, Allocator>::vector(const vector &rhs, const Allocator &allocator) :
        vector(rhs.cbegin(), rhs.cend(), allocator) {}
template <typename T, typename Allocator>
constexpr vector<T, Allocator>::vector(vector &&rhs) noexcept : first {ds::move(rhs.first)},
        cursor {ds::move(rhs.cursor)}, last {ds::move(rhs.last)} {
    rhs.first = rhs.cursor = rhs.last() = nullptr;
}
template <typename T, typename Allocator>
constexpr vector<T, Allocator>::vector(vector &&rhs, const Allocator &allocator) noexcept : first {ds::move(rhs.first)},
        cursor {ds::move(rhs.cursor)}, last(ds::move(rhs.last()), allocator) {
    rhs.first = rhs.cursor = rhs.last() = nullptr;
}
template <typename T, typename Allocator>
constexpr vector<T, Allocator>::~vector() noexcept {
    ds::destroy(this->first, this->cursor);
    this->last.allocator().deallocate(this->first, static_cast<size_type>(this->cursor - this->first));
}
template <typename T, typename Allocator>
constexpr vector<T, Allocator> &vector<T, Allocator>::operator=(const vector<T, Allocator> &rhs) {
    if(this not_eq &rhs) {
        this->assign(rhs.cbegin(), rhs.cend());
    }
    return *this;
}
template <typename T, typename Allocator>
constexpr vector<T, Allocator> &vector<T, Allocator>::operator=(vector<T, Allocator> &&rhs) noexcept {
    if(this not_eq &rhs) {
        this->~vector();
        this->first = ds::move(rhs.first);
        this->cursor = ds::move(rhs.cursor);
        this->last = ds::move(rhs.last);
        rhs.first = rhs.cursor = rhs.last() = nullptr;
    }
    return *this;
}
template <typename T, typename Allocator>
constexpr vector<T, Allocator> &vector<T, Allocator>::operator=(initializer_list<T> init_list) {
    this->assign(init_list.begin(), init_list.end());
    return *this;
}
template <typename T, typename Allocator>
constexpr typename vector<T, Allocator>::reference vector<T, Allocator>::operator[](size_type n)
        noexcept(is_nothrow_indexable_v<pointer, size_type>) {
    return this->first[n];
}
template <typename T, typename Allocator>
constexpr typename vector<T, Allocator>::const_reference vector<T, Allocator>::operator[](size_type n) const
        noexcept(is_nothrow_indexable_v<pointer, size_type>) {
    return this->first[n];
}
template <typename T, typename Allocator>
constexpr void vector<T, Allocator>::assign(size_type n, const_reference value) {
    if(n > this->capacity()) {
        this->assign_with_buffer<true>(buffer<T, Allocator>(n, value, this->last.allocator()));
    }else {
        auto it {this->first};
        for(; n not_eq 0 and it not_eq this->cursor; ++it, static_cast<void>(--n)) {
            *it = value;
        }
        if(n == 0) {
            if(it not_eq this->cursor) {
                ds::destroy(it, this->cursor);
                this->cursor = it;
            }
        }else do {
            ds::construct(this->cursor, value);
            ++this->cursor;
            --n;
        }while(n not_eq 0);
    }
}
template <typename T, typename Allocator>
template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
constexpr void vector<T, Allocator>::assign(InputIterator begin, InputIterator end, size_type default_size) {
    this->assign_with_buffer<true>(buffer<T, Allocator>(begin, end, this->last.allocator(), default_size));
}
template <typename T, typename Allocator>
template <IsForwardIterator ForwardIterator>
constexpr void vector<T, Allocator>::assign(ForwardIterator begin, ForwardIterator end) {
    // Todo : If ForwardIterator is pointer?
    auto n {ds::distance(begin, end)};
    if(n > this->capacity()) {
        this->assign_with_buffer<true>(buffer<T, Allocator>(begin, end, this->last.allocator()));
    }else {
        auto it {this->first};
        for(; n not_eq 0 and it not_eq this->cursor; ++it, static_cast<void>(--n)) {
            *it = *begin++;
        }
        if(n == 0) {
            if(it not_eq this->cursor) {
                ds::destroy(it, this->cursor);
                this->cursor = it;
            }
        }else do {
            ds::construct(this->cursor, *begin++);
            ++this->cursor;
            --n;
        }while(n not_eq 0);
    }
}
template <typename T, typename Allocator>
constexpr void vector<T, Allocator>::assign(initializer_list<T> init_list) {
    this->assign(init_list.begin(), init_list.end());
}
template <typename T, typename Allocator>
constexpr typename vector<T, Allocator>::iterator vector<T, Allocator>::begin() noexcept {
    return iterator {this->first};
}
template <typename T, typename Allocator>
constexpr typename vector<T, Allocator>::const_iterator vector<T, Allocator>::begin() const noexcept {
    return const_iterator {this->first};
}
template <typename T, typename Allocator>
constexpr typename vector<T, Allocator>::const_iterator vector<T, Allocator>::cbegin() const noexcept {
    return const_iterator {this->first};
}
template <typename T, typename Allocator>
constexpr typename vector<T, Allocator>::iterator vector<T, Allocator>::end() noexcept {
    return iterator {this->cursor};
}
template <typename T, typename Allocator>
constexpr typename vector<T, Allocator>::const_iterator vector<T, Allocator>::end() const noexcept {
    return const_iterator {this->cursor};
}
template <typename T, typename Allocator>
constexpr typename vector<T, Allocator>::const_iterator vector<T, Allocator>::cend() const noexcept {
    return const_iterator {this->cursor};
}
template <typename T, typename Allocator>
constexpr typename vector<T, Allocator>::reverse_iterator vector<T, Allocator>::rbegin() noexcept {
    return reverse_iterator {this->cursor - 1};
}
template <typename T, typename Allocator>
constexpr typename vector<T, Allocator>::const_reverse_iterator vector<T, Allocator>::rbegin() const noexcept {
    return const_reverse_iterator {this->cursor - 1};
}
template <typename T, typename Allocator>
constexpr typename vector<T, Allocator>::const_reverse_iterator vector<T, Allocator>::crbegin() const noexcept {
    return const_reverse_iterator {this->cursor - 1};
}
template <typename T, typename Allocator>
constexpr typename vector<T, Allocator>::reverse_iterator vector<T, Allocator>::rend() noexcept {
    return reverse_iterator {this->first - 1};
}
template <typename T, typename Allocator>
constexpr typename vector<T, Allocator>::const_reverse_iterator vector<T, Allocator>::rend() const noexcept {
    return const_reverse_iterator {this->first - 1};
}
template <typename T, typename Allocator>
constexpr typename vector<T, Allocator>::const_reverse_iterator vector<T, Allocator>::crend() const noexcept {
    return const_reverse_iterator {this->first - 1};
}
template <typename T, typename Allocator>
constexpr typename vector<T, Allocator>::size_type vector<T, Allocator>::size() const noexcept {
    return static_cast<size_type>(this->cursor - this->first);
}
template <typename T, typename Allocator>
constexpr bool vector<T, Allocator>::empty() const noexcept {
    return this->first == this->cursor;
}
template <typename T, typename Allocator>
constexpr typename vector<T, Allocator>::size_type vector<T, Allocator>::capacity() const noexcept {
    return static_cast<size_type>(this->last() - this->first);
}
template <typename T, typename Allocator>
constexpr typename vector<T, Allocator>::size_type vector<T, Allocator>::spare() const noexcept {
    return static_cast<size_type>(this->last() - this->cursor);
}
template <typename T, typename Allocator>
constexpr void vector<T, Allocator>::reserve(size_type n) {
    const auto size {this->size()};
    if(n > this->capacity()) {
        auto &allocator {this->last.allocator()};
        if constexpr(is_trivially_copyable_v<T>) {
            auto new_first {allocator.reallocate(this->first, n)};
            if(new_first not_eq this->first) {
                this->first = ds::move(new_first);
                this->cursor = this->first + size;
                this->last() = this->first + n;
            }
        }else {
            auto new_first {allocator.allocate(n)};
            this->move_to(new_first, this->first, this->cursor, n);
            this->~vector();
            this->first = ds::move(new_first);
            this->cursor = this->first + size;
            this->last() = this->first + n;
        }
    }
}
template <typename T, typename Allocator>
constexpr void vector<T, Allocator>::shrink_to_fit() {
    if(this->cursor not_eq this->last()) {
        const auto size {this->size()};
        this->resize_and_move(size, size);
        if(size == 0) {
            this->cursor = this->last() = nullptr;
        }else {
            this->cursor = this->last() = this->first + size;
        }
    }
}
template <typename T, typename Allocator>
constexpr void vector<T, Allocator>::resize(size_type n) {
    const auto size {this->size()};
    if(n not_eq size) [[likely]] {
        this->resize_and_move(n, size);
    }else {
        return;
    }
    if(n > size) {
        if constexpr(is_pointer_v<pointer> and is_trivially_default_constructible_v<T>) {
            ds::memory_default_initialization(this->first + size, sizeof(T) * (n - size));
        }else {
            this->cursor = this->first + size;
            this->last() = this->first + n;
            do {
                ds::construct(this->cursor);
            }while(++this->cursor not_eq this->last());
            return;
        }
    }
    this->last() = this->cursor = this->first + n;
}
template <typename T, typename Allocator>
constexpr void vector<T, Allocator>::resize(size_type n, const_reference value) {
    const auto size {this->size()};
    if(n not_eq size) [[likely]] {
        this->resize_and_move(n, size);
    }else {
        return;
    }
    if(n > size) {
        this->cursor = this->first + size;
        this->last() = this->first + n;
        do {
            ds::construct(this->cursor, value);
        }while(++this->cursor not_eq this->last());
        return;
    }
    this->last() = this->cursor = this->first + n;
}
template <typename T, typename Allocator>
constexpr typename vector<T, Allocator>::reference vector<T, Allocator>::front() noexcept {
    return *this->first;
}
template <typename T, typename Allocator>
constexpr typename vector<T, Allocator>::const_reference vector<T, Allocator>::front() const noexcept {
    return *this->first;
}
template <typename T, typename Allocator>
constexpr typename vector<T, Allocator>::reference vector<T, Allocator>::back() noexcept {
    return this->cursor[-1];
}
template <typename T, typename Allocator>
constexpr typename vector<T, Allocator>::const_reference vector<T, Allocator>::back() const noexcept {
    return this->cursor[-1];
}
template <typename T, typename Allocator>
constexpr typename vector<T, Allocator>::pointer vector<T, Allocator>::data() noexcept {
    return this->first;
}
template <typename T, typename Allocator>
constexpr typename vector<T, Allocator>::const_pointer vector<T, Allocator>::data() const noexcept {
    return this->first;
}
template <typename T, typename Allocator>
constexpr Allocator vector<T, Allocator>::allocator() const noexcept {
    return this->last.allocator();
}
template <typename T, typename Allocator>
constexpr void vector<T, Allocator>::push_back(const_reference value) {
    this->emplace_back(value);
}
template <typename T, typename Allocator>
constexpr void vector<T, Allocator>::push_back(rvalue_reference value) {
    this->emplace_back(ds::move(value));
}
template <typename T, typename Allocator>
template <typename ...Args>
constexpr void vector<T, Allocator>::emplace_back(Args &&...args) {
    if(this->cursor == this->last()) {
        const auto size {this->size()};
        const auto allocation_size {size == 0 ? 1 : size * 2};
        if constexpr(is_trivially_copyable_v<T>) {
            this->first = this->last.allocator().reallocate(this->first, allocation_size);
        }else {
            auto new_first {this->last.allocator().allocate(allocation_size)};
            this->move_to(new_first, this->first, this->last, allocation_size);
            this->~vector();
            this->first = ds::move(new_first);
        }
        this->cursor = this->first + size;
        this->last() = this->first + allocation_size;
    }
    ds::construct(this->cursor, ds::forward<Args>(args)...);
    ++this->cursor;
}
template <typename T, typename Allocator>
constexpr void vector<T, Allocator>::pop_back() noexcept {
    ds::destroy(--this->cursor);
}
template <typename T, typename Allocator>
constexpr void vector<T, Allocator>::clear() noexcept {
    ds::destroy(this->first, this->cursor);
    this->cursor = this->first;
}
template <typename T, typename Allocator>
constexpr void vector<T, Allocator>::swap(vector &rhs) noexcept {
    using ds::swap;
    swap(this->first, rhs.first);
    swap(this->cursor, rhs.cursor);
    swap(this->last(), rhs.last());
}
template <typename T, typename Allocator>
constexpr typename vector<T, Allocator>::iterator
vector<T, Allocator>::insert(size_type pos, const_reference value, size_type n) {
    if(n == 0) {
        return iterator {this->first + pos};
    }
    const auto size {this->size()};
    if(n > this->spare()) {
        this->reallocate_when_insertion(n, size, pos, value);
        return iterator {this->first + pos};
    }
    if constexpr(is_pointer_v<pointer> and is_trivially_copyable_v<T>) {
        const auto start_pos {this->first + pos};
        const auto stop_pos {start_pos + n};
        const auto tail_size {size - pos};
        ds::memory_move(stop_pos, start_pos, sizeof(T) * tail_size);
        for(auto it {start_pos}; it not_eq stop_pos; ++it) {
            *it = value;
        }
        this->cursor = stop_pos + tail_size;
        return iterator {start_pos};
    }
    auto uninitialized_size {n};
    const auto construction_stop_at {this->cursor - 1};
    const auto last_element {construction_stop_at + n};
    auto trans {transaction {insertion_handler {last_element, last_element + 1}}};
    auto move_start_from {construction_stop_at};
    const auto result {this->first + pos};
    const auto move_stop_at {result - 1};
    for(auto &it {trans.get_rollback().begin}; move_start_from not_eq move_stop_at; --it) {
        ds::construct(it, ds::move(*move_start_from--));
        if(--uninitialized_size == 0) {
            trans.complete();
            while(move_start_from not_eq move_stop_at) {
                *(--it) = ds::move(*move_start_from--);
            }
            trans.restart();
            break;
        }
    }
    auto pointer_to_value {&value};
    const auto cursor_advance_size {n};
    if(this->is_insertion_value_need_fix(result, pointer_to_value)) {
        pointer_to_value += cursor_advance_size;
    }
    for(auto &it {trans.get_rollback().begin}; uninitialized_size not_eq 0;
        --it, static_cast<void>(--uninitialized_size), --n) {
        ds::construct(it, *pointer_to_value);
    }
    trans.complete();
    this->cursor += cursor_advance_size;
    for(auto it {result}; n not_eq 0; --n) {
        *it++ = *pointer_to_value;
    }
    return iterator {result};
}
template <typename T, typename Allocator>
constexpr typename vector<T, Allocator>::iterator
vector<T, Allocator>::insert(const_iterator pos, const_reference value, size_type n) {
    return this->insert(pos - this->begin(), value, n);
}
template <typename T, typename Allocator>
template <typename ...Args>
constexpr typename vector<T, Allocator>::iterator vector<T, Allocator>::emplace(size_type pos, Args &&...args) {
    if(this->spare() == 0) {
        this->reallocate_when_insertion(1, this->size(), pos, ds::forward<Args>(args)...);
        return iterator {this->first + pos};
    }
    const auto result {this->first + pos};
    if(result == this->cursor) {
        ds::construct(this->cursor, ds::forward<Args>(args)...);
        ++this->cursor;
        return iterator {result};
    }
    ds::construct(this->cursor, this->cursor[-1]);
    for(auto it {this->cursor++}; it not_eq result; --it) {
        *it = ds::move(it[-1]);
    }
    *result = T(ds::forward<Args>(args)...);
    return iterator {result};
}
template <typename T, typename Allocator>
template <typename ...Args>
constexpr typename vector<T, Allocator>::iterator vector<T, Allocator>::emplace(const_iterator pos, Args &&...args) {
    return this->emplace(pos - this->cbegin(), ds::forward<Args>(args)...);
}
template <typename T, typename Allocator>
constexpr typename vector<T, Allocator>::iterator
vector<T, Allocator>::insert(size_type pos, rvalue_reference value) {
    return this->emplace(pos, ds::move(value));
}
template <typename T, typename Allocator>
constexpr typename vector<T, Allocator>::iterator
vector<T, Allocator>::insert(const_iterator pos, rvalue_reference value) {
    return this->emplace(pos - this->cbegin(), ds::move(value));
}
template <typename T, typename Allocator>
template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
constexpr typename vector<T, Allocator>::iterator
vector<T, Allocator>::insert(size_type pos, InputIterator begin, InputIterator end) {
    buffer<T, Allocator> b(begin, end, this->last.allocator());
    return this->insert(pos, b.mbegin(), b.mend());
}
template <typename T, typename Allocator>
template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
constexpr typename vector<T, Allocator>::iterator
vector<T, Allocator>::insert(const_iterator pos, InputIterator begin, InputIterator end) {
    buffer<T, Allocator> b(begin, end, this->last.allocator());
    return this->insert(pos - this->cbegin(), b.mbegin(), b.mend());
}
template <typename T, typename Allocator>
template <IsForwardIterator ForwardIterator>
constexpr typename vector<T, Allocator>::iterator
vector<T, Allocator>::insert(size_type pos, ForwardIterator begin, ForwardIterator end) {
    // Todo : if ForwardIterator is pointer?
    auto n {static_cast<size_type>(ds::distance(begin, end))};
    if(n == 0) {
        return iterator {this->first + pos};
    }
    const auto size {this->size()};
    if(n > this->spare()) {
        this->reallocate_when_insertion<false>(n, size, pos, begin, end);
        return iterator {this->first + pos};
    }
    if constexpr(is_pointer_v<pointer> and is_trivially_copyable_v<T>) {
        const auto start_pos {this->first + pos};
        const auto stop_pos {start_pos + n};
        const auto tail_size {size - pos};
        ds::memory_move(stop_pos, start_pos, sizeof(T) * tail_size);
        if constexpr(is_pointer_v<ForwardIterator>) {
            ds::memory_copy(start_pos, begin, sizeof(T) * n);
        }
        for(auto it {start_pos}; it not_eq stop_pos; ++it) {
            *it = *begin++;
        }
        this->cursor = stop_pos + tail_size;
        return iterator {start_pos};
    }
    auto uninitialized_size {n};
    const auto construction_stop_at {this->cursor - 1};
    const auto last_element {construction_stop_at + n};
    auto trans {transaction {insertion_handler {last_element, last_element + 1}}};
    auto move_start_from {construction_stop_at};
    const auto result {this->first + pos};
    const auto move_stop_at {result - 1};
    for(auto &it {trans.get_rollback().begin}; move_start_from not_eq move_stop_at; --it) {
        ds::construct(it, ds::move(*move_start_from--));
        if(--uninitialized_size == 0) {
            trans.complete();
            while(move_start_from not_eq move_stop_at) {
                *(--it) = ds::move(*move_start_from--);
            }
            trans.restart();
            break;
        }
    }
    const auto cursor_advance_size {n};
    if constexpr(is_pointer_v<ForwardIterator>) {
        if(this->is_insertion_value_need_fix(result, begin)) {
            begin += cursor_advance_size;
            end += cursor_advance_size;
        }
    }
    for(auto &it {trans.get_rollback().begin}; uninitialized_size not_eq 0;
        --it, static_cast<void>(--uninitialized_size), --n) {
        ds::construct(it, *begin++);
    }
    trans.complete();
    this->cursor += cursor_advance_size;
    for(auto it {result}; n not_eq 0; --n) {
        *it++ = *begin++;
    }
    return iterator {result};
}
template <typename T, typename Allocator>
template <IsForwardIterator ForwardIterator>
constexpr typename vector<T, Allocator>::iterator
vector<T, Allocator>::insert(const_iterator pos, ForwardIterator begin, ForwardIterator end) {
    return this->insert(pos - this->cbegin(), begin, end);
}
template <typename T, typename Allocator>
constexpr typename vector<T, Allocator>::iterator
vector<T, Allocator>::insert(size_type pos, initializer_list<T> init_list) {
    return this->insert(pos, init_list.begin(), init_list.end());
}
template <typename T, typename Allocator>
constexpr typename vector<T, Allocator>::iterator
vector<T, Allocator>::insert(const_iterator pos, initializer_list<T> init_list) {
    return this->insert(pos - this->cbegin(), init_list.begin(), init_list.end());
}
template <typename T, typename Allocator>
constexpr typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(size_type pos, size_type n) {
    const auto result {this->first + pos};
    if(n == 0) {
        return iterator {result};
    }
    if constexpr(is_pointer_v<pointer> and is_trivially_copyable_v<T>) {
        ds::memory_move(result, result + n, sizeof(T) * (this->size() - (pos + n)));
    }else {
        auto left {result};
        for(auto right {result + n}; right not_eq this->cursor;) {
            *left++ = ds::move(*right++);
        }
        ds::destroy(left, this->cursor);
    }
    this->cursor -= n;
    return iterator {result};
}
template <typename T, typename Allocator>
constexpr typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(const_iterator pos, size_type n) {
    return this->erase(pos - this->cbegin(), n);
}
template <typename T, typename Allocator>
constexpr typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(const_iterator pos) {
    return this->erase(pos - this->cbegin());
}
template <typename T, typename Allocator>
constexpr typename vector<T, Allocator>::iterator
vector<T, Allocator>::erase(const_iterator begin, const_iterator end) {
    return this->erase(begin - this->cbegin(), static_cast<size_type>(end - begin));
}

/* global functions */
template <typename T, typename Allocator>
constexpr void swap(vector<T, Allocator> &lhs, vector<T, Allocator> &rhs) noexcept {
    lhs.swap(rhs);
}
__DATA_STRUCTURE_END(vector implementation)

}       // namespace data_structure

#endif      //DATA_STRUCTURE_VECTOR_HPP