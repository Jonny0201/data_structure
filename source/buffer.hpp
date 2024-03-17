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

__DATA_STRUCTURE_START(compressed pair with allocator for ds::buffer)
namespace data_structure::__data_structure_auxiliary {

template <typename Allocator, bool>
struct allocator_compressor {
    size_t buffer_size;
    Allocator alloc;
public:
    constexpr allocator_compressor() noexcept(is_nothrow_default_constructible_v<Allocator>) = default;
    explicit constexpr allocator_compressor(size_t size) noexcept(is_nothrow_default_constructible_v<Allocator>) :
            buffer_size {size}, alloc {} {}
    explicit constexpr allocator_compressor(const Allocator &allocator)
            noexcept(is_nothrow_copy_constructible_v<Allocator>) : buffer_size {}, alloc {allocator} {}
    constexpr allocator_compressor(size_t size, const Allocator &allocator)
            noexcept(is_nothrow_copy_constructible_v<Allocator>) : buffer_size {size}, alloc {allocator} {}
    constexpr allocator_compressor(const allocator_compressor &rhs)
            noexcept(is_nothrow_copy_constructible_v<Allocator>) : buffer_size(rhs.buffer_size), alloc {rhs.alloc} {}
    constexpr allocator_compressor(allocator_compressor &&rhs) noexcept :
            buffer_size(rhs.buffer_size), alloc {ds::move(rhs.alloc)} {}
public:
    size_t &operator()() noexcept {
        return this->buffer_size;
    }
    const size_t &operator()() const noexcept {
        return this->buffer_size;
    }
    Allocator &allocator() noexcept {
        return this->alloc;
    }
    const Allocator &allocator() const noexcept {
        return this->alloc;
    }
};
template <typename Allocator>
struct allocator_compressor<Allocator, true> : Allocator {
    size_t buffer_size;
public:
    constexpr allocator_compressor() noexcept(is_nothrow_default_constructible_v<Allocator>) = default;
    explicit allocator_compressor(size_t size) noexcept(is_nothrow_default_constructible_v<Allocator>) :
            Allocator(), buffer_size {size} {}
    explicit allocator_compressor(const Allocator &allocator) noexcept(is_nothrow_copy_constructible_v<Allocator>) :
            Allocator(allocator), buffer_size {} {}
    allocator_compressor(size_t size, const Allocator &allocator) noexcept(is_nothrow_copy_constructible_v<Allocator>) :
            Allocator(allocator), buffer_size {size} {}
    allocator_compressor(const allocator_compressor &rhs) noexcept(is_nothrow_copy_constructible_v<Allocator>) :
            Allocator(rhs.allocator()), buffer_size {rhs.buffer_size} {}
    allocator_compressor(allocator_compressor &&rhs) noexcept :
            Allocator(ds::move(rhs.allocator())), buffer_size {rhs.buffer_size} {}
public:
    size_t &operator()() noexcept {
        return this->buffer_size;
    }
    const size_t &operator()() const noexcept {
        return this->buffer_size;
    }
    Allocator &allocator() noexcept {
        return static_cast<Allocator &>(*this);
    }
    const Allocator &allocator() const noexcept {
        return static_cast<const Allocator &>(*this);
    }
};
template <typename Allocator>
using buffer_compressed_pair = allocator_compressor<Allocator, is_empty_v<Allocator> and not is_final_v<Allocator>>;

}       // namespace data_structure::__data_structure_auxiliary
__DATA_STRUCTURE_END

namespace data_structure {
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
    using pointer = T *;
    using const_pointer = const T *;
    using iterator = T *;
    using const_iterator = const T *;
    using move_iterator = ds::move_iterator<T *>;
private:
    __dsa::buffer_compressed_pair<Allocator> buffer_size;
    T *first;
private:
    void move_to(T *, size_t);
public:
    buffer() = delete;
    explicit constexpr buffer(size_t, const Allocator & = {});
    constexpr buffer(size_t, const T &, const Allocator & = {});
    template <IsInputIterator InputIterator>
    constexpr buffer(InputIterator, InputIterator, const Allocator & = {});
    constexpr buffer(initializer_list<T>, const Allocator & = {});
    buffer(const buffer &) = delete;
    buffer(buffer &&) = delete;
    constexpr ~buffer() noexcept;
public:
    buffer &operator=(const buffer &) = delete;
    buffer &operator=(buffer &&) = delete;
public:
    [[nodiscard]]
    constexpr const T *begin() const & noexcept;
    [[nodiscard]]
    constexpr const T *end() const & noexcept;
    [[nodiscard]]
    constexpr T *release() noexcept;
    [[nodiscard]]
    constexpr move_iterator mbegin() noexcept;
    [[nodiscard]]
    constexpr move_iterator mend() noexcept;
    [[nodiscard]]
    constexpr size_t size() const noexcept;
    [[nodiscard]]
    constexpr bool empty() const noexcept;
    [[nodiscard]]
    constexpr Allocator allocator() const noexcept;
};
}

namespace data_structure {
/* private functions */
template <typename T, typename Allocator>
void buffer<T, Allocator>::move_to(T *new_buffer, size_t old_size) {
    if constexpr(is_trivially_copy_assignable_v<T>) {
        ds::memory_copy(new_buffer, this->first, sizeof(T) * old_size);
    }else {
        constexpr auto nothrow_move_constructible {is_nothrow_move_constructible_v<T>};
        if constexpr(nothrow_move_constructible or is_nothrow_copy_constructible_v<T>) {
            for(auto i {0}; i < old_size; ++i) {
                ds::construct(new_buffer + i, ds::move_if<nothrow_move_constructible>(this->first[i]));
            }
        }else {
            auto i {0uz};
            try {
                for(; i < old_size; ++i) {
                    ds::construct(new_buffer + i, this->first[i]);
                }
            }catch(...) {
                ds::destroy(this->first, this->first + static_cast<difference_type>(old_size));
                ds::destroy(new_buffer, new_buffer + i);
                this->buffer_size.allocator().deallocate(this->first, old_size);
                this->buffer_size.allocator().deallocate(new_buffer, this->buffer_size());
                throw;
            }
        }
    }
    ds::destroy(this->first, this->first + old_size);
    this->buffer_size.allocator().deallocate(this->first, old_size);
    this->first = new_buffer;
}
template <typename T, typename Allocator>
template <typename InputIterator, typename AllocatorCopy>
buffer<T, Allocator>::buffer(InputIterator begin, InputIterator end, AllocatorCopy &&allocator, false_type) :
        buffer_size {64, ds::move(allocator)},
        first {this->buffer_size.allocator().allocate(this->buffer_size())} {
    difference_type i {0};
    auto &buffer_size {this->buffer_size()};
    if constexpr(is_nothrow_constructible_v<value_type, typename InputIterator::rvalue_reference> or
            is_nothrow_constructible_v<value_type, typename InputIterator::reference>) {
        for(; begin not_eq end; ++i) {
            if(i == buffer_size and begin not_eq end) {
                buffer_size *= 2;
                pointer new_first {};
                try {
                    new_first = this->buffer_size.allocator().allocate(buffer_size);
                }catch(...) {
                    ds::destroy(this->first, this->first + i);
                    this->buffer_size.allocator().deallocate(this->first, buffer_size);
                    throw;
                }
                this->move_to(new_first, static_cast<size_type>(i));
            }
            ds::construct(this->first + i, ds::move_if<is_nothrow_constructible_v<
                    value_type, typename InputIterator::rvalue_reference>>(*begin++));
        }
        if(i == 0) {
            this->buffer_size.allocator().deallocate(this->first, buffer_size);
            buffer_size = 0;
            this->first = nullptr;
            return;
        }
    }else {
        for(; begin not_eq end; ++i) {
            if(i == buffer_size and begin not_eq end) {
                buffer_size *= 2;
                pointer new_first {};
                try {
                    new_first = this->buffer_size.allocator().allocate(buffer_size);
                }catch(...) {
                    ds::destroy(this->first, this->first + i);
                    this->buffer_size.allocator().deallocate(this->first, buffer_size);
                    throw;
                }
                this->move_to(new_first, static_cast<size_type>(i));
            }
            try {
                ds::construct(this->first + i, *begin++);
            }catch(...) {
                ds::destroy(this->first, this->first + i);
                this->buffer_size.allocator().deallocate(this->first, buffer_size);
                throw;
            }
        }
        if(i == 0) {
            this->buffer_size.allocator().deallocate(this->first, buffer_size);
            buffer_size = 0;
            this->first = nullptr;
            return;
        }
    }
    if(i < buffer_size) {
        pointer new_first {};
        try {
            new_first = this->buffer_size.allocator().allocate(static_cast<size_type>(i));
        }catch(...) {
            ds::destroy(this->first, this->first + i);
            this->buffer_size.allocator().deallocate(this->first, i);
            throw;
        }
        this->move_to(new_first, static_cast<size_type>(i));
        buffer_size = i;
    }
}
template <typename T, typename Allocator>
template <typename ForwardIterator, typename AllocatorCopy>
buffer<T, Allocator>::buffer(ForwardIterator begin, ForwardIterator end, AllocatorCopy &&allocator, true_type) :
        buffer_size {static_cast<size_type>(ds::distance(begin, end)), ds::move(allocator)},
        first {this->buffer_size() == 0 ? nullptr : this->buffer_size.allocator().allocate(this->buffer_size())} {
    if(begin == end) {
        return;
    }
    if constexpr(is_pointer_v<ForwardIterator> and is_trivially_copy_assignable_v<value_type>) {
        ds::memory_copy(this->first, begin, sizeof(value_type) * this->buffer_size());
    }else {
        if constexpr(is_nothrow_constructible_v<value_type, iterator_traits_t(ForwardIterator, reference)>) {
            for(auto i {0}; begin not_eq end; ++i) {
                ds::construct(this->first + i, *begin++);
            }
        }else {
            difference_type i {0};
            try {
                for(; begin not_eq end; ++i) {
                    ds::construct(this->first + i, *begin++);
                }
            }catch(...) {
                ds::destroy(this->first, this->first + i);
                this->buffer_size.allocator().deallocate(this->first, this->buffer_size());
                throw;
            }
        }
    }
}

/* public functions */
template <typename T, typename Allocator>
constexpr buffer<T, Allocator>::buffer(size_t n, const Allocator &allocator) :
        buffer_size {n == 0 ? 64 : n, allocator},
        first {this->buffer_size.allocator().allocate(this->buffer_size())} {
    if constexpr(is_trivially_default_constructible_v<value_type>) {
        ds::memory_default_initialization(this->first, sizeof(value_type) * this->buffer_size());
    }else {
        if constexpr(is_nothrow_default_constructible_v<value_type>) {
            for(auto i {0}; i < this->buffer_size(); ++i) {
                ds::construct(this->first + i);
            }
        }else {
            difference_type i {0};
            try {
                for(; i < this->buffer_size(); ++i) {
                    ds::construct(this->first + i);
                }
            }catch(...) {
                ds::destroy(this->first, this->first + i);
                this->buffer_size.allocator().deallocate(this->first, this->buffer_size());
                throw;
            }
        }
    }
}
template <typename T, typename Allocator>
constexpr buffer<T, Allocator>::buffer(size_t size, const T &value, const Allocator &allocator) :
        buffer_size {size == 0 ? 64 : size, allocator},
        first {this->buffer_size.allocator().allocate(this->buffer_size())} {
    if constexpr(is_nothrow_copy_constructible_v<value_type>) {
        for(auto i {0}; i < this->buffer_size(); ++i) {
            ds::construct(this->first + i, value);
        }
    }else {
        difference_type i {0};
        try {
            for(; i < this->buffer_size(); ++i) {
                ds::construct(this->first + i, value);
            }
        }catch(...) {
            ds::destroy(this->first, this->first + i);
            this->buffer_size.allocator().deallocate(this->first, static_cast<size_type>(i));
            throw;
        }
    }
}
template <typename T, typename Allocator>
template <IsInputIterator InputIterator>
constexpr buffer<T, Allocator>::buffer(InputIterator begin, InputIterator end, const Allocator &allocator) :
        buffer(begin, end, allocator, is_forward_iterator<InputIterator> {}) {}
template <typename T, typename Allocator>
constexpr buffer<T, Allocator>::buffer(initializer_list<T> init_list, const Allocator &allocator) :
        buffer(init_list.begin(), init_list.end(), allocator, true_type {}) {}
template <typename T, typename Allocator>
constexpr const T *buffer<T, Allocator>::begin() const & noexcept {
    return this->first;
}
template <typename T, typename Allocator>
constexpr const T *buffer<T, Allocator>::end() const & noexcept {
    return this->first + this->buffer_size();
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
constexpr size_t buffer<T, Allocator>::size() const noexcept {
    return this->buffer_size();
}
template <typename T, typename Allocator>
constexpr bool buffer<T, Allocator>::empty() const noexcept {
    return this->buffer_size() == 0;
}
template <typename T, typename Allocator>
constexpr Allocator buffer<T, Allocator>::allocator() const noexcept {
    return this->buffer_size.allocator();
}
}

#endif //DATA_STRUCTURE_BUFFER_HPP