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
    using reference = T &;
    using const_reference = const T &;
    using rvalue_reference = T &&;
    using pointer = typename Allocator::pointer;
    using const_pointer = typename Allocator::const_pointer;
    using iterator = wrap_iterator<pointer>;
    using const_iterator = wrap_iterator<const_pointer>;
    using reverse_iterator = reverse_iterator<pointer>;
    using const_reverse_iterator = ds::reverse_iterator<const_pointer>;
    static_assert(is_same_v<T, typename Allocator::value_type>,
            "The value type of vector should same as the allocator's value_type!");
private:
    struct resize_handler;
    friend struct resize_handler;
private:
    pointer first {};
    pointer cursor {};
    __dsa::allocator_compressor<pointer, Allocator> last {};
private:
    void resize_and_move(size_type);
    void reallocate_and_move();
public:
    constexpr vector() noexcept(is_nothrow_default_constructible_v<Allocator>) = default;
    explicit constexpr vector(const Allocator &) noexcept;
    explicit constexpr vector(size_type, const Allocator & = {});
    constexpr vector(size_type, const T &, const Allocator & = {});
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
    constexpr T &operator[](difference_type) noexcept(is_nothrow_indexable_v<pointer, difference_type>);
    [[nodiscard]]
    constexpr const T &operator[](difference_type) const noexcept(is_nothrow_indexable_v<pointer, difference_type>);
public:
    constexpr void assign(size_type, const T & = {});
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
    constexpr void resize(size_type, const T &);
    [[nodiscard]]
    constexpr T &front() noexcept;
    [[nodiscard]]
    constexpr const T &front() const noexcept;
    [[nodiscard]]
    constexpr T &back() noexcept;
    [[nodiscard]]
    constexpr const T &back() const noexcept;
    [[nodiscard]]
    constexpr pointer data() noexcept;
    [[nodiscard]]
    constexpr const_pointer data() const noexcept;
    constexpr void push_back(const T &);
    constexpr void push_back(T &&);
    template <typename ...Args>
    constexpr void emplace_back(Args &&...);
    constexpr void pop_back() noexcept;
    constexpr void clear() noexcept;
    constexpr void swap(vector &) noexcept;
    constexpr iterator insert(difference_type, const T &, size_type = 1);
    constexpr iterator insert(const_iterator, const T &, size_type = 1);
    template <typename ...Args>
    constexpr iterator emplace(difference_type, Args &&...);
    template <typename ...Args>
    constexpr iterator emplace(const_iterator, Args &&...);
    constexpr iterator insert(difference_type, T &&);
    constexpr iterator insert(const_iterator, T &&);
    template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
    constexpr iterator insert(difference_type, InputIterator, InputIterator);
    template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
    constexpr iterator insert(const_iterator, InputIterator, InputIterator);
    template <IsForwardIterator ForwardIterator>
    constexpr iterator insert(difference_type, ForwardIterator, ForwardIterator);
    template <IsForwardIterator ForwardIterator>
    constexpr iterator insert(const_iterator, ForwardIterator, ForwardIterator);
    constexpr iterator insert(difference_type, initializer_list<T>);
    constexpr iterator insert(const_iterator, initializer_list<T>);
    constexpr iterator erase(difference_type, size_type = 1);
    constexpr iterator erase(const_iterator, size_type);
    constexpr iterator erase(const_iterator);
    constexpr iterator erase(const_iterator, const_iterator);
};
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(vector implementation)
/* private types */
template <typename T, typename Allocator>
struct vector<T, Allocator>::resize_handler {
    vector &v;
    pointer &new_place;
    size_type new_size;
    size_type i {0};
    explicit constexpr resize_handler(vector &v, pointer &new_place, size_type new_size) noexcept :
            v {v}, new_place {new_place}, new_size {new_size} {}
    constexpr void operator()() noexcept {
        ds::destroy(this->new_place, this->new_place + this->i);
        this->v.last.allocator().deallocate(this->new_place, this->new_size);
    }
};

/* public functions */
template <typename T, typename Allocator>
constexpr vector<T, Allocator>::vector(const Allocator &allocator) noexcept : first {}, cursor {}, last(allocator) {}
template <typename T, typename Allocator>
constexpr vector<T, Allocator>::vector(size_type n, const Allocator &allocator) : first {}, cursor {}, last(allocator) {
    buffer b(n, allocator);
    this->first = b.release();
    this->cursor = this->last() = this->first + b.size();
}
template <typename T, typename Allocator>
constexpr vector<T, Allocator>::vector(size_type n, const T &value, const Allocator &allocator) :
        first {}, cursor {}, last(allocator) {
    buffer b(n, value, allocator);
    this->first = b.release();
    this->cursor = this->last() = this->first + b.size();
}
template <typename T, typename Allocator>
template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
constexpr vector<T, Allocator>::vector(InputIterator begin, InputIterator end, const Allocator &allocator,
        size_type default_size) : first {}, cursor {}, last(allocator) {
    buffer<T, Allocator> b(begin, end, allocator, default_size);
    this->cursor = this->first = b.release();
    this->last = this->first + b.size();
}
template <typename T, typename Allocator>
template <IsForwardIterator ForwardIterator>
constexpr vector<T, Allocator>::vector(ForwardIterator begin, ForwardIterator end, const Allocator &allocator) :
        first {}, cursor {}, last(allocator) {
    buffer<T, Allocator> b(begin, end, allocator);
    this->cursor = this->first = b.release();
    this->last = this->first + b.size();
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
    this->last.allocator().deallocate(this->first, this->cursor - this->first);
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
        this->cursor = ds::move(rhs.cusror);
        this->last = ds::move(rhs.last);
        rhs.first = rhs.cusror = rhs.last() = nullptr;
    }
    return *this;
}
template <typename T, typename Allocator>
constexpr vector<T, Allocator> &vector<T, Allocator>::operator=(initializer_list<T> init_list) {
    this->assign(init_list.begin(), init_list.end());
    return *this;
}
template <typename T, typename Allocator>
constexpr T &vector<T, Allocator>::operator[](difference_type n)
        noexcept(is_nothrow_indexable_v<pointer, difference_type>) {
    return this->first[n];
}
template <typename T, typename Allocator>
constexpr const T &vector<T, Allocator>::operator[](difference_type n) const
        noexcept(is_nothrow_indexable_v<pointer, difference_type>) {
    return this->first[n];
}
template <typename T, typename Allocator>
constexpr void vector<T, Allocator>::assign(size_type n, const T &value) {
    if(n == 0) {
        return;
    }
    if(n > this->capacity()) {
        buffer b(n, value, this->last.allocator());
        this->first = b.release();
        this->cursor = this->last() = this->first + b.size();
    }else {
        auto it {this->first};
        for(; it not_eq this->cursor and n not_eq 0; ++it, static_cast<void>(--n)) {
            *it = value;
        }
        if(n == 0) {
            if(it not_eq this->cursor) {
                ds::destroy(it, this->cursor);
                this->cursor = it;
            }
        }else for(; n not_eq 0; ++this->cursor, static_cast<void>(--n)) {
            ds::construct(this->cursor, value);
        }
    }
}
template <typename T, typename Allocator>
template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
constexpr void vector<T, Allocator>::assign(InputIterator begin, InputIterator end, size_type default_size) {
    buffer<T, Allocator> b(begin, end, this->last.allocator(), default_size);
    this->assign_with_iterator(b);
}
template <typename T, typename Allocator>
template <IsForwardIterator ForwardIterator>
constexpr void vector<T, Allocator>::assign(ForwardIterator begin, ForwardIterator end) {
    buffer<T, Allocator> b(begin, end, this->last.allocator());
    this->assign_with_iterator(b);
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
    return static_cast<size_type>(this->last - this->first);
}
template <typename T, typename Allocator>
constexpr typename vector<T, Allocator>::size_type vector<T, Allocator>::spare() const noexcept {
    return static_cast<size_type>(this->last - this->cursor);
}
template <typename T, typename Allocator>
constexpr void vector<T, Allocator>::reserve(size_type n) {
    if(n > this->capacity()) {
        auto &allocator {this->last.allocator()};
        if constexpr(is_trivially_copyable_v<T>) {
            this->first = allocator.reallocate(this->first, n);
        }else {
            auto new_first {allocator.allocate(n)};
            this->move_to(new_first, this->cursor);
        }
    }
}
template <typename T, typename Allocator>
constexpr void vector<T, Allocator>::shrink_to_fit() {
    if(this->cursor not_eq this->last) {
        this->resize_and_move(this->size());
    }
}
template <typename T, typename Allocator>
constexpr void vector<T, Allocator>::resize(size_type n) {
    const auto size {this->size()};
    if(n not_eq size) {
        this->resize_and_move(n);
        if(n > size) {
            if constexpr(is_trivially_default_constructible_v<T>) {
                ds::memory_default_initialization(this->cursor, sizeof(T) * (n - size));
            }else {
                do {
                    ds::construct(this->cursor);
                }while(++this->cursor not_eq this->last);
            }
        }
    }
}
template <typename T, typename Allocator>
constexpr void vector<T, Allocator>::resize(size_type n, const T &value) {
    const auto size {this->size()};
    if(n not_eq size) {
        this->resize_and_move(n);
        if(n > size) {
            do {
                ds::construct(this->cursor, value);
            }while(++this->cursor not_eq this->last);
        }
    }
}
template <typename T, typename Allocator>
constexpr T &vector<T, Allocator>::front() noexcept {
    return *this->first;
}
template <typename T, typename Allocator>
constexpr const T &vector<T, Allocator>::front() const noexcept {
    return *this->first;
}
template <typename T, typename Allocator>
constexpr T &vector<T, Allocator>::back() noexcept {
    return this->cursor[-1];
}
template <typename T, typename Allocator>
constexpr const T &vector<T, Allocator>::back() const noexcept {
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
constexpr void vector<T, Allocator>::push_back(const T &value) {
    this->emplace_back(value);
}
template <typename T, typename Allocator>
constexpr void vector<T, Allocator>::push_back(T &&value) {
    this->emplace_back(ds::move(value));
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
    ds::swap(this->first, rhs.first);
    ds::swap(this->cursor, rhs.cursor);
    ds::swap(this->last(), rhs.last());
}
__DATA_STRUCTURE_END

}       // namespace data_structure

#endif      //DATA_STRUCTURE_VECTOR_HPP