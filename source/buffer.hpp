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

#ifndef DATA_STRUCTURE_BUFFER_HPP
#define DATA_STRUCTURE_BUFFER_HPP

#include "allocator.hpp"
#include "iterator.hpp"
#include "memory.hpp"

namespace data_structure {

__DATA_STRUCTURE_START(buffer declaration)
template <typename T, typename Allocator = allocator<T>>
class buffer {
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
    using iterator = pointer;
    using const_iterator = const_pointer;
    using move_iterator = ds::move_iterator<pointer>;
    static_assert(is_same_v<T, typename Allocator::value_type>,
            "The value type of buffer should same as the allocator's value_type!");
private:
    struct exception_handler;
    friend struct exception_handler;
private:
    __dsa::allocator_compressor<size_type, Allocator> buffer_size;
    pointer first;
private:
    template <bool = true>
    constexpr void initialize(const T &);
    constexpr void move_to(pointer, size_type);
    template <typename InputIterator>
    constexpr void initialize(InputIterator, InputIterator, false_type);
    template <typename ForwardIterator>
    constexpr void initialize(ForwardIterator, ForwardIterator, true_type);
public:
    buffer() = delete;
    explicit constexpr buffer(size_type, const Allocator & = {});
    constexpr buffer(size_type, const T &, const Allocator & = {});
    template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
    constexpr buffer(InputIterator, InputIterator, const Allocator & = {}, size_type = 64);
    template <IsForwardIterator ForwardIterator>
    constexpr buffer(ForwardIterator, ForwardIterator, const Allocator & = {});
    constexpr buffer(initializer_list<T>, const Allocator & = {});
    buffer(const buffer &) = delete;
    buffer(buffer &&) = delete;
    constexpr ~buffer() noexcept;
public:
    buffer &operator=(const buffer &) = delete;
    buffer &operator=(buffer &&) = delete;
public:
    [[nodiscard]]
    constexpr const_pointer begin() const & noexcept;
    [[nodiscard]]
    constexpr const_pointer end() const & noexcept;
    [[nodiscard]]
    constexpr pointer release() noexcept;
    [[nodiscard]]
    constexpr move_iterator mbegin() noexcept;
    [[nodiscard]]
    constexpr move_iterator mend() noexcept;
    [[nodiscard]]
    constexpr size_type size() const noexcept;
    [[nodiscard]]
    constexpr bool empty() const noexcept;
    [[nodiscard]]
    constexpr Allocator allocator() const noexcept;
};
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(buffer implementation)
/* private type */
template <typename T, typename Allocator>
struct buffer<T, Allocator>::exception_handler {
    buffer &b;
    size_type i {0};
    explicit constexpr exception_handler(buffer &b) noexcept : b {b} {}
    constexpr void operator()() noexcept {
        ds::destroy(this->b.first, this->b.first + this->i);
        this->b.buffer_size.allocator().deallocate(this->b.first, this->b.buffer_size());
    }
};

/* private functions */
template <typename T, typename Allocator>
constexpr void buffer<T, Allocator>::move_to(pointer new_buffer, size_type old_size) {
    auto &allocator {this->buffer_size.allocator()};
    if constexpr(is_trivially_copy_assignable_v<T>) {
        ds::memory_copy(new_buffer, this->first, sizeof(T) * old_size);
    }else {
        struct exception_handler {
            pointer old_buffer;
            pointer new_buffer;
            size_type old_size;
            size_type new_size;
            size_type i;
            Allocator &allocator;
            constexpr exception_handler(pointer old_buffer, size_type old_size, pointer new_buffer, size_type new_size,
                    Allocator &allocator) : old_buffer {old_buffer}, new_buffer {new_buffer}, old_size {old_size},
                    new_size {new_size}, i {0}, allocator {allocator} {}
            constexpr void operator()() noexcept {
                ds::destroy(this->old_buffer, this->old_buffer + this->old_size);
                ds::destroy(this->new_buffer, this->new_buffer + this->i);
                allocator.deallocate(this->old_buffer, this->old_size);
                allocator.deallocate(this->new_buffer, this->new_size);
            }
        };
        auto trans {transaction {exception_handler(this->first, old_size, new_buffer,
                this->buffer_size(), allocator)}};
        for(auto &i {trans.get_rollback().i}; i < old_size; ++i) {
            ds::construct(new_buffer + i, ds::move(this->first[i]));
        }
        trans.complete();
    }
    ds::destroy(this->first, this->first + old_size);
    allocator.deallocate(this->first, old_size);
    this->first = new_buffer;
}
template <typename T, typename Allocator>
template <bool CopyFromValue>
constexpr void buffer<T, Allocator>::initialize(const T &value) {
    const auto size {this->buffer_size()};
    this->first = this->buffer_size.allocator().allocate(size);
    auto trans {transaction {exception_handler(*this)}};
    if constexpr(not CopyFromValue and is_trivially_default_constructible_v<T>) {
        ds::memory_default_initialization(this->first, sizeof(T) * size);
    }else {
        for(auto &i {trans.get_rollback().i}; i < size; ++i) {
            if constexpr(CopyFromValue) {
                ds::construct(this->first + i, value);
            }else {
                ds::construct(this->first + i);
            }
        }
    }
    trans.complete();
}
template <typename T, typename Allocator>
template <typename InputIterator>
constexpr void buffer<T, Allocator>::initialize(InputIterator begin, InputIterator end, false_type) {
    auto &size {this->buffer_size()};
    this->first = this->buffer_size.allocator().allocate(size);
    auto &allocator {this->buffer_size.allocator()};
    auto trans {transaction {exception_handler(*this)}};
    auto &i {trans.get_rollback().i};
    for(; begin not_eq end; ++i) {
        if(i == size) {
            size *= 2;
            if constexpr(is_trivially_copyable_v<T>) {
                this->first = allocator.reallocate(this->first, size);
            }else {
                this->move_to(allocator.allocate(size), i);
            }
        }
        ds::construct(this->first + i, ds::move(*begin++));
    }
    if(i not_eq size) {
        if constexpr(is_trivially_copyable_v<T>) {
            this->first = allocator.reallocate(this->first, i);
        }else {
            this->move_to(allocator.allocate(i), i);
        }
        size = i;
    }
    trans.complete();
}
template <typename T, typename Allocator>
template <typename ForwardIterator>
constexpr void buffer<T, Allocator>::initialize(ForwardIterator begin, ForwardIterator end, true_type) {
    const auto size {this->buffer_size()};
    this->first = this->buffer_size.allocator().allocate(size);
    auto trans {transaction {exception_handler(*this)}};
    if constexpr(is_pointer_v<ForwardIterator> and is_trivially_copyable_v<T>) {
        ds::memory_copy(this->first, begin, sizeof(T) * this->buffer_size());
    }else {
        for(auto &i {trans.get_rollback().i}; i < size; ++i) {
            ds::construct(this->first + i, *begin++);
        }
    }
    trans.complete();
}

/* public functions */
template <typename T, typename Allocator>
constexpr buffer<T, Allocator>::buffer(size_type n, const Allocator &allocator) : buffer_size(n, allocator), first {} {
    this->initialize<false>({});
}
template <typename T, typename Allocator>
constexpr buffer<T, Allocator>::buffer(size_type n, const T &value, const Allocator &allocator) :
        buffer_size(n, allocator), first {} {
    this->initialize(value);
}
template <typename T, typename Allocator>
template <IsInputIterator InputIterator> requires (not is_forward_iterator_v<InputIterator>)
constexpr buffer<T, Allocator>::buffer(InputIterator begin, InputIterator end, const Allocator &allocator,
        size_type default_size) : buffer_size(default_size, allocator), first {} {
    this->initialize(begin, end, false_type {});
}
template <typename T, typename Allocator>
template <IsForwardIterator ForwardIterator>
constexpr buffer<T, Allocator>::buffer(ForwardIterator begin, ForwardIterator end, const Allocator &allocator) :
        buffer_size(ds::distance(begin, end), allocator), first {} {
    this->initialize(begin, end, true_type {});
}
template <typename T, typename Allocator>
constexpr buffer<T, Allocator>::buffer(initializer_list<T> init_list, const Allocator &allocator) :
        buffer(init_list.begin(), init_list.end(), allocator) {}

template <typename T, typename Allocator>
constexpr buffer<T, Allocator>::~buffer() noexcept {
    const auto size {this->buffer_size()};
    ds::destroy(this->first, this->first + size);
    this->buffer_size.allocator().deallocate(this->first, size);
}
template <typename T, typename Allocator>
constexpr typename buffer<T, Allocator>::const_pointer buffer<T, Allocator>::begin() const & noexcept {
    return this->first;
}
template <typename T, typename Allocator>
constexpr typename buffer<T, Allocator>::const_pointer buffer<T, Allocator>::end() const & noexcept {
    return this->first + this->buffer_size();
}
template <typename T, typename Allocator>
constexpr typename buffer<T, Allocator>::pointer buffer<T, Allocator>::release() noexcept {
    auto result {this->first};
    this->first = nullptr;
    return result;
}
template <typename T, typename Allocator>
constexpr typename buffer<T, Allocator>::move_iterator buffer<T, Allocator>::mbegin() noexcept {
    return move_iterator(this->first);
}
template <typename T, typename Allocator>
constexpr typename buffer<T, Allocator>::move_iterator buffer<T, Allocator>::mend() noexcept {
    return move_iterator(this->first + this->buffer_size());
}
template <typename T, typename Allocator>
constexpr typename buffer<T, Allocator>::size_type buffer<T, Allocator>::size() const noexcept {
    return this->buffer_size();
}
template <typename T, typename Allocator>
constexpr bool buffer<T, Allocator>::empty() const noexcept {
    return this->first == nullptr;
}
template <typename T, typename Allocator>
constexpr Allocator buffer<T, Allocator>::allocator() const noexcept {
    return this->buffer_size.allocator();
}
__DATA_STRUCTURE_END

}       // namespace data_structure

#endif      // DATA_STRUCTURE_BUFFER_HPP