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
    template <typename SizeType, typename Allocator, bool>
    struct allocator_compressor {
        SizeType buffer_size;
        Allocator alloc;
    public:
        constexpr allocator_compressor() noexcept = default;
        explicit allocator_compressor(SizeType size) noexcept : buffer_size {size}, alloc {} {}
        explicit allocator_compressor(Allocator allocator) noexcept :
                buffer_size {}, alloc {ds::move(allocator)} {}
        allocator_compressor(SizeType size, Allocator allocator) noexcept :
                buffer_size {size}, alloc {ds::move(allocator)} {}
        allocator_compressor(const allocator_compressor &rhs) noexcept :
                buffer_size(rhs.buffer_size), alloc {rhs.alloc} {}
        allocator_compressor(allocator_compressor &&rhs) noexcept :
                buffer_size(rhs.buffer_size), alloc {ds::move(rhs.alloc)} {}
    public:
        SizeType &operator()() noexcept {
            return this->buffer_size;
        }
        const SizeType &operator()() const noexcept {
            return this->buffer_size;
        }
        Allocator &allocator() noexcept {
            return this->alloc;
        }
        const Allocator &allocator() const noexcept {
            return this->alloc;
        }
    };
    template <typename SizeType, typename Allocator>
    struct allocator_compressor<SizeType, Allocator, false> : Allocator {
        SizeType buffer_size;
    public:
        constexpr allocator_compressor() noexcept = default;
        explicit allocator_compressor(SizeType size) noexcept : Allocator(), buffer_size {size} {}
        explicit allocator_compressor(Allocator allocator) noexcept : Allocator(allocator), buffer_size {} {}
        allocator_compressor(SizeType size, Allocator allocator) noexcept :
                Allocator(allocator), buffer_size {size} {}
        allocator_compressor(const allocator_compressor &rhs) noexcept :
                Allocator(rhs.allocator()), buffer_size {rhs.buffer_size} {}
        allocator_compressor(allocator_compressor &&rhs) noexcept :
                Allocator(ds::move(rhs.allocator())), buffer_size {rhs.buffer_size} {}
    public:
        SizeType &operator()() noexcept {
            return this->buffer_size;
        }
        const SizeType &operator()() const noexcept {
            return this->buffer_size;
        }
        Allocator &allocator() noexcept {
            return static_cast<Allocator &>(*this);
        }
        const Allocator &allocator() const noexcept {
            return static_cast<const Allocator &>(*this);
        }
    };
    template <typename SizeType, typename Allocator>
    using buffer_compressed_pair = allocator_compressor<SizeType, Allocator,
            is_empty_v<Allocator> and not is_final_v<Allocator>>;
}

namespace data_structure {
    template <typename T, typename Allocator = allocator<T>>
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
    public:
        struct construction_without_initialization {};
    private:
        __dsa::buffer_compressed_pair<size_type, allocator_type> buffer_size;
        pointer first;
    private:
        void move_to(pointer, size_type);
    private:
        template <typename InputIterator, typename AllocatorCopy>
        buffer(InputIterator, InputIterator, AllocatorCopy &&, false_type);
        template <typename ForwardIterator, typename AllocatorCopy>
        buffer(ForwardIterator, ForwardIterator, AllocatorCopy &&, true_type);
    public:
        buffer() = delete;
        explicit buffer(size_type, allocator_type = {});
        buffer(size_type, const_reference, allocator_type = {});
        template <typename InputIterator> requires is_input_iterator_v<InputIterator>
        buffer(InputIterator, InputIterator, allocator_type = {});
        buffer(initializer_list<value_type>, allocator_type = {});
        buffer(size_type, construction_without_initialization, allocator_type = {});
        buffer(const buffer &);
        buffer(const buffer &, allocator_type);
        buffer(buffer &&) noexcept;
        buffer(buffer &&, allocator_type) noexcept;
        ~buffer() noexcept = default;
    public:
        [[nodiscard]]
        buffer &operator=(const buffer &) = delete;
        [[nodiscard]]
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
        [[nodiscard]]
        allocator_type allocator() const noexcept;
        void clear() noexcept;
    };
}

namespace data_structure {
    /* private functions */
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
                    this->buffer_size.allocator().deallocate(this->first, old_size);
                    this->buffer_size.allocator().deallocate(new_buffer, this->buffer_size());
                    throw;
                }
            }
        }
        ds::destroy(this->first, this->first + static_cast<difference_type>(old_size));
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
                ds::construct(this->first + i, ds::move_if<is_nothrow_constructible_v<
                        value_type, typename InputIterator::rvalue_reference>>(*begin++));
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
            }
            if(i == 0) {
                this->buffer_size.allocator().deallocate(this->first, buffer_size);
                buffer_size = 0;
                this->first = nullptr;
                return;
            }
        }else {
            for(; begin not_eq end; ++i) {
                try {
                    ds::construct(this->first + i, *begin++);
                }catch(...) {
                    ds::destroy(this->first, this->first + i);
                    this->buffer_size.allocator().deallocate(this->first, buffer_size);
                    throw;
                }
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
    buffer<T, Allocator>::buffer(size_type n, allocator_type allocator) :
            buffer_size {n == 0 ? 64 : n, ds::move(allocator)},
            first {this->buffer_size.allocator().allocate(this->buffer_size())} {
        if constexpr(is_trivially_default_constructible_v<value_type>) {
            ds::memory_set(this->first, 0, sizeof(value_type) * this->buffer_size());
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
    buffer<T, Allocator>::buffer(size_type size, const_reference value, allocator_type allocator) :
            buffer_size {size == 0 ? 64 : size, ds::move(allocator)},
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
    template <typename InputIterator> requires is_input_iterator_v<InputIterator>
    buffer<T, Allocator>::buffer(InputIterator begin, InputIterator end, allocator_type allocator) :
            buffer(begin, end, allocator, is_forward_iterator<InputIterator> {}) {}
    template <typename T, typename Allocator>
    buffer<T, Allocator>::buffer(initializer_list<value_type> init_list, allocator_type allocator) :
            buffer(init_list.begin(), init_list.end(), ds::move(allocator), true_type {}) {}
    template <typename T, typename Allocator>
    buffer<T, Allocator>::buffer(size_type n, construction_without_initialization, allocator_type allocator) :
            buffer_size {n == 0 ? 64 : n, ds::move(allocator)},
            first {this->buffer_size.allocator().allocate(this->buffer_size())} {}
    template <typename T, typename Allocator>
    buffer<T, Allocator>::buffer(const buffer &rhs) : buffer(rhs.first,
            rhs.first + static_cast<difference_type>(rhs.buffer_size()), rhs.allocator(), true_type {}) {}
    template <typename T, typename Allocator>
    buffer<T, Allocator>::buffer(const buffer &rhs, allocator_type allocator) : buffer(rhs.first,
            rhs.first + static_cast<difference_type>(rhs.buffer_size()), ds::move(allocator), true_type {}) {}
    template <typename T, typename Allocator>
    buffer<T, Allocator>::buffer(buffer &&rhs) noexcept : buffer_size {ds::move(rhs.buffer_size)}, first {rhs.first} {
        rhs.buffer_size() = 0;
        rhs.first = nullptr;
    }
    template <typename T, typename Allocator>
    buffer<T, Allocator>::buffer(buffer &&rhs, allocator_type allocator) noexcept :
            buffer_size {rhs.buffer_size(), ds::move(allocator)}, first {rhs.first} {
        rhs.buffer_size() = 0;
        rhs.first = nullptr;
    }
    template <typename T, typename Allocator>
    typename buffer<T, Allocator>::reference buffer<T, Allocator>::operator[](difference_type n) noexcept {
        return n >= 0 ? this->first[n] : this->first[static_cast<difference_type>(this->buffer_size() + n)];
    }
    template <typename T, typename Allocator>
    typename buffer<T, Allocator>::iterator buffer<T, Allocator>::begin() noexcept {
        return this->first;
    }
    template <typename T, typename Allocator>
    typename buffer<T, Allocator>::iterator buffer<T, Allocator>::end() noexcept {
        return this->first + static_cast<difference_type>(this->buffer_size());
    }
    template <typename T, typename Allocator>
    typename buffer<T, Allocator>::move_iterator buffer<T, Allocator>::mbegin() noexcept {
        return move_iterator(this->first);
    }
    template <typename T, typename Allocator>
    typename buffer<T, Allocator>::move_iterator buffer<T, Allocator>::mend() noexcept {
        return move_iterator(this->first + static_cast<difference_type>(this->buffer_size()));
    }
    template <typename T, typename Allocator>
    typename buffer<T, Allocator>::size_type buffer<T, Allocator>::size() const noexcept {
        return this->buffer_size();
    }
    template <typename T, typename Allocator>
    bool buffer<T, Allocator>::empty() const noexcept {
        return this->buffer_size() == 0;
    }
    template <typename T, typename Allocator>
    typename buffer<T, Allocator>::allocator_type buffer<T, Allocator>::allocator() const noexcept {
        return this->buffer_size.allocator();
    }
    template <typename T, typename Allocator>
    void buffer<T, Allocator>::clear() noexcept {
        const auto &buffer_size {this->buffer_size()};
        ds::destroy(this->first, this->first + static_cast<difference_type>(buffer_size));
        this->buffer_size.allocator().deallocate(this->first, buffer_size);
    }
}

#endif //DATA_STRUCTURE_BUFFER_HPP
