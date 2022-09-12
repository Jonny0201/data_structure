/*
    * Copyright © [2019 - 2022] [Jonny Charlotte]
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

namespace data_structure::__data_structure_auxiliary {
    struct buffer_construction_without_initialization {};
}

namespace data_structure {
    template <typename T, typename Allocator = allocator<void>>
    class buffer {
    public:
        using allocator_type = Allocator;
        using size_type = typename allocator_type::size_type;
        using difference_type = typename allocator_type::difference_type;
        using value_type = T;
        using reference = add_lvalue_reference_t<value_type>;
        using const_reference = add_const_reference_t<value_type>;
        using rvalue_reference = add_rvalue_reference_t<value_type>;
        using pointer = add_pointer_t<value_type>;
        using const_pointer = add_const_pointer_t<value_type>;
        using iterator = pointer;
        using const_iterator = const_pointer;
        using move_iterator = ds::move_iterator<iterator>;
    private:
        size_type buffer_size;
        pointer first;
    private:
        static pointer allocate(size_type);
    private:
        void move_to(pointer, size_type);
    private:
        template <typename InputIterator>
        buffer(InputIterator, InputIterator, false_type);
        template <typename ForwardIterator>
        buffer(ForwardIterator, ForwardIterator, true_type);
    public:
        buffer() = delete;
        explicit buffer(size_type);
        buffer(const_reference, size_type);
        template <typename InputIterator> requires is_input_iterator_v<InputIterator>
        buffer(InputIterator, InputIterator);
        buffer(initializer_list<value_type>);
        buffer(size_type, __dsa::buffer_construction_without_initialization);
        buffer(const buffer &);
        buffer(buffer &&) noexcept;
        ~buffer() noexcept = default;
    public:
        buffer &operator=(const buffer &) = delete;
        buffer &operator=(buffer &&) noexcept = delete;
        [[nodiscard]]
        reference operator[](difference_type) noexcept;
    public:
        [[nodiscard]]
        iterator begin() noexcept;
        [[nodiscard]]
        iterator end() noexcept;
        [[nodiscard]]
        move_iterator mbegin() noexcept;
        [[nodiscard]]
        move_iterator mend() noexcept;
        [[nodiscard]]
        size_type size() const noexcept;
        [[nodiscard]]
        bool empty() const noexcept;
    };
}

namespace data_structure {
    /* private functions */
    template <typename T, typename Allocator>
    typename buffer<T, Allocator>::pointer buffer<T, Allocator>::allocate(size_type n) {
        return static_cast<pointer>(allocator_type::operator new(sizeof(value_type) * n));
    }
    template <typename T, typename Allocator>
    void buffer<T, Allocator>::move_to(pointer new_buffer, size_type old_size) {
        if constexpr(is_trivially_copy_assignable_v<value_type>) {
            ds::memory_copy(new_buffer, this->first, sizeof(value_type) * old_size);
        }else {
            if constexpr(is_nothrow_move_constructible_v<value_type> or is_nothrow_copy_constructible_v<value_type>) {
                for(auto i {0}; i < old_size; ++i) {
                    ds::construct(new_buffer + i,
                            ds::move_if<is_nothrow_move_constructible_v<value_type>>(this->first[i]));
                }
            }else {
                difference_type i {0};
                try {
                    for(; i < old_size; ++i) {
                        ds::construct(new_buffer + i, this->first[i]);
                    }
                }catch(...) {
                    ds::destroy(this->first, this->first + static_cast<difference_type>(old_size));
                    ds::destroy(new_buffer, new_buffer + i);
                    allocator_type::operator delete(this->first);
                    allocator_type::operator delete(new_buffer);
                    throw;
                }
            }
        }
        ds::destroy(this->first, this->first + static_cast<difference_type>(old_size));
        allocator_type::operator delete(this->first);
        this->first = new_buffer;
    }
    template <typename T, typename Allocator>
    template <typename InputIterator>
    buffer<T, Allocator>::buffer(InputIterator begin, InputIterator end, false_type) :
            buffer_size {64}, first {this->allocate(this->buffer_size)} {
        difference_type i {0};
        if constexpr(is_nothrow_constructible_v<value_type, typename InputIterator::rvalue_reference> or
                is_nothrow_constructible_v<value_type, typename InputIterator::reference>) {
            for(; begin not_eq end; ++i) {
                ds::construct(this->first + i, ds::move_if<is_nothrow_constructible_v<
                        value_type, typename InputIterator::rvalue_reference>>(*begin++));
                if(i == this->buffer_size and begin not_eq end) {
                    this->buffer_size *= 2;
                    pointer new_first {};
                    try {
                        new_first = this->allocate(this->buffer_size);
                    }catch(...) {
                        ds::destroy(this->first, this->first + i);
                        allocator_type::operator delete(this->first);
                        throw;
                    }
                    this->move_to(new_first, static_cast<size_type>(i));
                }
            }
        }else {
            for(; begin not_eq end; ++i) {
                try {
                    ds::construct(this->first + i, *begin++);
                }catch(...) {
                    ds::destroy(this->first, this->first + i);
                    allocator_type::operator delete(this->first);
                    throw;
                }
                if(i == this->buffer_size and begin not_eq end) {
                    this->buffer_size *= 2;
                    pointer new_first {};
                    try {
                        new_first = this->allocate(this->buffer_size);
                    }catch(...) {
                        ds::destroy(this->first, this->first + i);
                        allocator_type::operator delete(this->first);
                        throw;
                    }
                    this->move_to(new_first, static_cast<size_type>(i));
                }
            }
        }
        if(i < this->buffer_size) {
            pointer new_first {};
            try {
                new_first = this->allocate(static_cast<size_type>(i));
            }catch(...) {
                ds::destroy(this->first, this->first + i);
                allocator_type::operator delete(this->first);
                throw;
            }
            this->move_to(new_first, static_cast<size_type>(i));
        }
    }
    template <typename T, typename Allocator>
    template <typename ForwardIterator>
    buffer<T, Allocator>::buffer(ForwardIterator begin, ForwardIterator end, true_type) :
            buffer_size {static_cast<size_type>(ds::distance(begin, end))},
            first {this->allocate(this->buffer_size)} {
        if constexpr(is_pointer_v<ForwardIterator> and is_trivially_copy_assignable_v<value_type>) {
            ds::memory_copy(this->first, begin, sizeof(value_type) * this->buffer_size);
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
                    allocator_type::operator delete(this->first);
                    throw;
                }
            }
        }
    }

    /* public functions */
    template <typename T, typename Allocator>
    buffer<T, Allocator>::buffer(size_type n) : buffer_size {n == 0 ? 64 : n},
            first {this->allocate(this->buffer_size)} {
        if constexpr(is_trivially_default_constructible_v<value_type>) {
            ds::memory_set(this->first, 0, sizeof(value_type) * this->buffer_size);
        }else {
            if constexpr(is_nothrow_default_constructible_v<value_type>) {
                for(auto i {0}; i < this->buffer_size; ++i) {
                    ds::construct(this->first + i);
                }
            }else {
                difference_type i {0};
                try {
                    for(; i < this->buffer_size; ++i) {
                        ds::construct(this->first + i);
                    }
                }catch(...) {
                    ds::destroy(this->first, this->first + i);
                    allocator_type::operator delete(this->first);
                    throw;
                }
            }
        }
    }
    template <typename T, typename Allocator>
    buffer<T, Allocator>::buffer(const_reference value, size_type n) : buffer_size {n == 0 ? 64 : n},
            first {this->allocate(this->buffer_size)} {
        if constexpr(is_nothrow_copy_constructible_v<value_type>) {
            for(auto i {0}; i < this->buffer_size; ++i) {
                ds::construct(this->first + i, value);
            }
        }else {
            difference_type i {0};
            try {
                for(; i < this->buffer_size; ++i) {
                    ds::construct(this->first + i, value);
                }
            }catch(...) {
                ds::destroy(this->first, this->first + i);
                allocator_type::operator delete(this->first);
                throw;
            }
        }
    }
    template <typename T, typename Allocator>
    template <typename InputIterator> requires is_input_iterator_v<InputIterator>
    buffer<T, Allocator>::buffer(InputIterator begin, InputIterator end) :
            buffer(begin, end, is_forward_iterator<InputIterator> {}) {}
    template <typename T, typename Allocator>
    buffer<T, Allocator>::buffer(initializer_list<value_type> init_list) :
            buffer(init_list.begin(), init_list.end()) {}
    template <typename T, typename Allocator>
    buffer<T, Allocator>::buffer(size_type n, __dsa::buffer_construction_without_initialization) :
            buffer_size {n == 0 ? 64 : n}, first {this->allocate(this->buffer_size)} {}
    template <typename T, typename Allocator>
    buffer<T, Allocator>::buffer(const buffer &rhs) : buffer(rhs.begin(), rhs.end()) {}
    template <typename T, typename Allocator>
    buffer<T, Allocator>::buffer(buffer &&rhs) noexcept : buffer_size {rhs.buffer_size}, first {rhs.first} {
        rhs.buffer_size = 0;
        rhs.first = nullptr;
    }
    template <typename T, typename Allocator>
    typename buffer<T, Allocator>::reference buffer<T, Allocator>::operator[](difference_type n) noexcept {
        return n >= 0 ? this->first[n] : this->first[static_cast<difference_type>(this->buffer_size + n)];
    }
    template <typename T, typename Allocator>
    typename buffer<T, Allocator>::iterator buffer<T, Allocator>::begin() noexcept {
        return this->first;
    }
    template <typename T, typename Allocator>
    typename buffer<T, Allocator>::iterator buffer<T, Allocator>::end() noexcept {
        return this->first + static_cast<difference_type>(this->buffer_size);
    }
    template <typename T, typename Allocator>
    typename buffer<T, Allocator>::move_iterator buffer<T, Allocator>::mbegin() noexcept {
        return move_iterator(this->first);
    }
    template <typename T, typename Allocator>
    typename buffer<T, Allocator>::move_iterator buffer<T, Allocator>::mend() noexcept {
        return move_iterator(this->first + static_cast<difference_type>(this->buffer_size));
    }
    template <typename T, typename Allocator>
    typename buffer<T, Allocator>::size_type buffer<T, Allocator>::size() const noexcept {
        return this->buffer_size;
    }
    template <typename T, typename Allocator>
    bool buffer<T, Allocator>::empty() const noexcept {
        return this->buffer_size == 0;
    }
}

#endif //DATA_STRUCTURE_BUFFER_HPP
