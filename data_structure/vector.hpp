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
#include "algorithm.hpp"
#include "string.hpp"

namespace data_structure::__data_structure_auxiliary {
    template <typename T, typename Allocator = allocator<type_holder<T>>>
    class vector_base {
    public:
        using allocator_type = Allocator;
        using size_type = allocator_traits_t(allocator_type, size_type);
        using difference_type = allocator_traits_t(allocator_type, difference_type);
        using value_type = T;
        using reference = allocator_traits_t(allocator_type, reference);
        using const_reference = allocator_traits_t(allocator_type, const_reference);
        using rvalue_reference = allocator_traits_t(allocator_type, rvalue_reference);
        using pointer = allocator_traits_t(allocator_type, pointer);
        using const_pointer = allocator_traits_t(allocator_type, const_pointer);
        using iterator = wrap_iterator<pointer>;
        using const_iterator = wrap_iterator<const_pointer>;
        using reverse_iterator = reverse_iterator<iterator>;
        using const_reverse_iterator = ds::reverse_iterator<const_iterator>;
    private:
        using alloc_traits = allocator_traits<allocator_type>;
        static_assert(is_same_v<value_type, typename alloc_traits::value_type>,
                "The Allocator::value_type must be the same as template argument value_type!");
    protected:
        pointer first;
        pointer last;
        mutable pointer cursor;
    protected:
        constexpr static size_type alloc_size_ctor(size_type) noexcept;
        constexpr static size_type default_size() noexcept;
        static void handle_exception_from_alloc(pointer, pointer) noexcept;
        static void destroy_from_insert_or_erase(pointer, pointer) noexcept;
    protected:
        size_type recommend(size_type = 0) const noexcept;
        pointer allocate(size_type);
        void reallocate(size_type = 0);
        void deallocate_and_set_null() noexcept;
        void deallocate() noexcept(is_nothrow_destructible<value_type>::value);
        bool full() const noexcept;
        void resize_for_shrink_or_reserve(size_type);
    public:
        constexpr vector_base() noexcept;
        explicit vector_base(size_type);
        vector_base(size_type, const_reference);
        template <typename InputIterator>
        vector_base(typename enable_if<is_input_iterator<InputIterator>::value and
                                not is_forward_iterator<InputIterator>::value, InputIterator>::type,
                InputIterator);
        template <typename ForwardIterator>
        vector_base(typename enable_if<
                        is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type,
                ForwardIterator);
        vector_base(initializer_list<value_type>);
        vector_base(const vector_base &);
        vector_base(vector_base &&) noexcept;
        template <typename AllocatorRHS>
        vector_base(const vector_base<value_type, AllocatorRHS> &);
        template <typename AllocatorRHS>
        vector_base(vector_base<value_type, AllocatorRHS> &&) noexcept;
        ~vector_base() noexcept;
    public:
        vector_base &operator=(const vector_base &);
        vector_base &operator=(vector_base &&) noexcept;
        vector_base &operator=(initializer_list<value_type>);
        template <typename AllocatorRHS>
        vector_base &operator=(const vector_base<value_type, AllocatorRHS> &);
        template <typename AllocatorRHS>
        vector_base &operator=(vector_base<value_type, AllocatorRHS> &&) noexcept;
        reference operator[](difference_type) noexcept(has_nothrow_dereference_operator<pointer>::value);
        const_reference operator[](difference_type) const
                noexcept(has_nothrow_dereference_operator<pointer>::value);
    public:
        void assign(size_type, const_reference = {});
        template <typename InputIterator>
        typename enable_if<is_input_iterator<InputIterator>::value and
                not is_forward_iterator<InputIterator>::value, void>::type
        assign(InputIterator, InputIterator);
        template <typename ForwardIterator>
        typename enable_if<is_forward_iterator<ForwardIterator>::value, void>::type
        assign(ForwardIterator, ForwardIterator);
        void assign(initializer_list<value_type>);
        [[nodiscard]]
        iterator begin() noexcept;
        [[nodiscard]]
        const_iterator begin() const noexcept;
        [[nodiscard]]
        iterator end() noexcept;
        [[nodiscard]]
        const_iterator end() const noexcept;
        [[nodiscard]]
        reverse_iterator rbegin() noexcept;
        [[nodiscard]]
        const_reverse_iterator rbegin() const noexcept;
        [[nodiscard]]
        reverse_iterator rend() noexcept;
        [[nodiscard]]
        const_reverse_iterator rend() const noexcept;
        [[nodiscard]]
        const_iterator cbegin() const noexcept;
        [[nodiscard]]
        const_iterator cend() const noexcept;
        [[nodiscard]]
        const_reverse_iterator crbegin() const noexcept;
        [[nodiscard]]
        const_reverse_iterator crend() const noexcept;
        [[nodiscard]]
        size_type size() const noexcept;
        [[nodiscard]]
        size_type capacity() const noexcept;
        [[nodiscard]]
        bool empty() const noexcept;
        [[nodiscard]]
        constexpr size_type max_size() const noexcept;
        [[nodiscard]]
        size_type spare() const noexcept;
        void reserve(size_type);
        void shrink_to_fit();
        [[nodiscard]]
        reference at(difference_type) noexcept(has_nothrow_dereference_operator<pointer>::value);
        [[nodiscard]]
        const_reference at(difference_type) const noexcept(has_nothrow_dereference_operator<pointer>::value);
        [[nodiscard]]
        reference front() noexcept(has_nothrow_dereference_operator<pointer>::value);
        [[nodiscard]]
        const_reference front() const noexcept(has_nothrow_dereference_operator<pointer>::value);
        [[nodiscard]]
        reference back() noexcept(has_nothrow_dereference_operator<pointer>::value);
        [[nodiscard]]
        const_reference back() const noexcept(has_nothrow_dereference_operator<pointer>::value);
        [[nodiscard]]
        pointer data() noexcept;
        [[nodiscard]]
        const_pointer data() const noexcept;
        void push_back(const_reference);
        void push_back(rvalue_reference);
        void pop_back() noexcept;
        void clear() noexcept;
        void resize(size_type, const_reference = {});
        void swap(vector_base &) noexcept;
        template <typename AllocatorRHS>
        void swap(vector_base<value_type, AllocatorRHS> &) noexcept;
        iterator insert(difference_type, const_reference, size_type = 1);
        iterator insert(difference_type, rvalue_reference);
        iterator insert(const_iterator, const_reference, size_type = 1);
        iterator insert(const_iterator, rvalue_reference);
        iterator insert(const_iterator, initializer_list<value_type>);
        iterator insert(difference_type, initializer_list<value_type>);
        template <typename InputIterator>
        iterator insert(const_iterator, InputIterator,
                typename enable_if<is_input_iterator<InputIterator>::value and
                        not is_forward_iterator<InputIterator>::value, InputIterator>::type);
        template <typename InputIterator>
        iterator insert(difference_type, InputIterator,
                typename enable_if<is_input_iterator<InputIterator>::value and
                        not is_forward_iterator<InputIterator>::value, InputIterator>::type);
        template <typename ForwardIterator>
        iterator insert(const_iterator, ForwardIterator,
                typename enable_if<is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type);
        template <typename ForwardIterator>
        iterator insert(difference_type, ForwardIterator,
                typename enable_if<is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type);
        template <typename ...Args>
        void emplace_back(Args &&...);
        template <typename ...Args>
        iterator emplace(difference_type, Args &&...);
        template <typename ...Args>
        iterator emplace(const_iterator, Args &&...);
        iterator erase(difference_type, size_type = 1) noexcept;
        iterator erase(const_iterator, size_type) noexcept;
        iterator erase(const_iterator, const_iterator) noexcept;
        iterator erase(const_iterator) noexcept;
    };
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    void swap(vector_base<T, AllocatorLHS> &, vector_base<T, AllocatorRHS> &) noexcept;
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    [[nodiscard]]
    bool operator==(const vector_base<T, AllocatorLHS> &, const vector_base<T, AllocatorRHS> &)
            noexcept(has_nothrow_equal_to_operator<T>::value);
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    [[nodiscard]]
    bool operator!=(const vector_base<T, AllocatorLHS> &, const vector_base<T, AllocatorRHS> &)
            noexcept(has_nothrow_equal_to_operator<T>::value);
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    [[nodiscard]]
    bool operator<(const vector_base<T, AllocatorLHS> &, const vector_base<T, AllocatorRHS> &)
            noexcept(has_nothrow_less_operator<T>::value);
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    [[nodiscard]]
    bool operator<=(const vector_base<T, AllocatorLHS> &, const vector_base<T, AllocatorRHS> &)
            noexcept(has_nothrow_less_operator<T>::value and has_nothrow_equal_to_operator<T>::value);
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    [[nodiscard]]
    bool operator>(const vector_base<T, AllocatorLHS> &, const vector_base<T, AllocatorRHS> &)
            noexcept(has_nothrow_less_operator<T>::value and has_nothrow_equal_to_operator<T>::value);
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    [[nodiscard]]
    bool operator>=(const vector_base<T, AllocatorLHS> &, const vector_base<T, AllocatorRHS> &)
            noexcept(has_nothrow_less_operator<T>::value);
}

namespace data_structure::__data_structure_auxiliary {
    /* private function */
    template <typename T, typename Allocator>
    constexpr inline typename vector_base<T, Allocator>::size_type
    vector_base<T, Allocator>::alloc_size_ctor(size_type size) noexcept {
        return size > 5 ? size + size / 5 : size * 2;
    }
    template <typename T, typename Allocator>
    constexpr inline typename vector_base<T, Allocator>::size_type
    vector_base<T, Allocator>::default_size() noexcept {
        return sizeof(value_type) > 128 ? 16 : 64;
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::size_type
    vector_base<T, Allocator>::recommend(size_type size) const noexcept {
        if(size == 0) {
            return this->default_size();
        }
        const auto capacity {this->capacity() * 2};
        if(capacity) {
            if(size > capacity) {
                return size;
            }
            return capacity;
        }
        return size;
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::pointer
    vector_base<T, Allocator>::allocate(size_type size) {
        return reinterpret_cast<pointer>(alloc_traits::operator new (size * sizeof(value_type)));
    }
    template <typename T, typename Allocator>
    inline void vector_base<T, Allocator>::deallocate_and_set_null() noexcept {
        alloc_traits::destroy(this->first, this->cursor);
        alloc_traits::operator delete (this->first);
        this->first = this->last = this->cursor = nullptr;
    }
    template <typename T, typename Allocator>
    inline void vector_base<T, Allocator>::reallocate(size_type n) {
        const auto new_size {[&]() noexcept -> size_type {
            auto capacity {this->capacity() * 2};
            if(capacity == 0) {
                capacity = this->default_size();
            }
            return capacity > n ? capacity : n + capacity;
        }()};
        auto new_first {this->allocate(new_size)};
        auto new_cursor {new_first};
        auto cursor {this->first};
        while(cursor not_eq this->cursor) {
            if constexpr(is_nothrow_copy_constructible<value_type>::value or
                    is_nothrow_move_constructible<value_type>::value) {
                alloc_traits::construct(new_cursor++, data_structure::move(*cursor++));
            }else {
                try {
                    alloc_traits::construct(new_cursor, data_structure::move(*cursor++));
                    ++new_cursor;
                }catch(...) {
                    this->handle_exception_from_alloc(new_first, new_cursor);
                    if constexpr(is_nothrow_move_constructible<value_type>::value) {
                        this->deallocate();
                        this->first = this->cursor = this->last = nullptr;
                    }
                    throw;
                }
            }
        }
        this->deallocate();
        this->first = data_structure::move(new_first);
        this->cursor = data_structure::move(new_cursor);
        this->last = this->first + new_size;
    }
    template <typename T, typename Allocator>
    inline void vector_base<T, Allocator>::deallocate()
            noexcept(is_nothrow_destructible<value_type>::value) {
        this->clear();
        alloc_traits::operator delete (this->first);
    }
    template <typename T, typename Allocator>
    inline bool vector_base<T, Allocator>::full() const noexcept {
        return this->last == this->cursor;
    }
    template <typename T, typename Allocator>
    inline void vector_base<T, Allocator>::handle_exception_from_alloc(pointer begin, pointer end) noexcept {
        if constexpr(not is_trivially_destructible<value_type>::value) {
            alloc_traits::destroy(begin, end);
        }
        alloc_traits::operator delete (begin);
    }
    template <typename T, typename Allocator>
    void vector_base<T, Allocator>::resize_for_shrink_or_reserve(size_type size) {
        auto new_first {this->allocate(size)};
        auto new_cursor {new_first};
        for(auto cursor {this->first}; cursor not_eq this->cursor;) {
            if constexpr(is_nothrow_move_constructible<value_type>::value or
                         is_nothrow_copy_constructible<value_type>::value) {
                alloc_traits::construct(new_cursor++, ds::move(*cursor++));
            }else {
                try {
                    alloc_traits::construct(new_cursor, ds::move(*cursor++));
                    ++new_cursor;
                }catch(...) {
                    //strong guarantee
                    this->handle_exception_from_alloc(new_first, new_cursor);
                    throw;
                }
            }
        }
        this->deallocate();
        this->first = ds::move(new_first);
        this->cursor = ds::move(new_cursor);
        this->last = this->first + ds::move(size);
    }
    template <typename T, typename Allocator>
    inline void vector_base<T, Allocator>::destroy_from_insert_or_erase(pointer begin, pointer end) noexcept {
        alloc_traits::destroy(begin, end);
    }

    /* public function */
    template <typename T, typename Allocator>
    constexpr inline vector_base<T, Allocator>::vector_base() noexcept :
            first {nullptr}, last {nullptr}, cursor {nullptr} {}
    template <typename T, typename Allocator>
    vector_base<T, Allocator>::vector_base(size_type size) :
            first {this->allocate(this->alloc_size_ctor(size))},
            last {this->first + this->alloc_size_ctor(size)}, cursor {this->first} {
        while(size--) {
            if constexpr(is_nothrow_default_constructible<value_type>::value) {
                alloc_traits::construct(this->cursor++);
            }else {
                try {
                    alloc_traits::construct(this->cursor);
                    ++this->cursor;
                }catch(...) {
                    this->deallocate();
                    throw;
                }
            }
        }
    }
    template <typename T, typename Allocator>
    vector_base<T, Allocator>::vector_base(size_type size, const_reference value) :
            first {this->allocate(this->alloc_size_ctor(size))},
            last {this->first + this->alloc_size_ctor(size)}, cursor {this->first} {
        while(size--) {
            if constexpr(is_nothrow_copy_constructible<value_type>::value) {
                alloc_traits::construct(this->cursor++, value);
            }else {
                try {
                    alloc_traits::construct(this->cursor, value);
                    ++this->cursor;
                }catch(...) {
                    this->deallocate();
                    throw;
                }
            }
        }
    }
    template <typename T, typename Allocator>
    template <typename InputIterator>
    vector_base<T, Allocator>::vector_base(typename enable_if<is_input_iterator<InputIterator>::value and
                    not is_forward_iterator<InputIterator>::value, InputIterator>::type begin,
            InputIterator end) : first {this->allocate(this->default_size())},
            last {this->first + this->default_size()}, cursor {this->first} {
        while(begin not_eq end) {
            try {
                this->push_back(move(*begin++));
            }catch(...) {
                this->deallocate();
                throw;
            }
        }
    }
    template <typename T, typename Allocator>
    template <typename ForwardIterator>
    vector_base<T, Allocator>::vector_base(
            typename enable_if<
                    is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type begin,
            ForwardIterator end) : first {this->allocate(this->alloc_size_ctor(distance(begin, end)))},
            last {this->first + this->alloc_size_ctor(distance(begin, end))}, cursor {this->first} {
        while(begin not_eq end) {
            if constexpr(is_nothrow_constructible<
                    value_type, typename iterator_traits<ForwardIterator>::reference>::value) {
                alloc_traits::construct(this->cursor++, *begin++);
            }else {
                try {
                    alloc_traits::construct(this->cursor, *begin++);
                    ++this->cursor;
                }catch(...) {
                    this->deallocate();
                    throw;
                }
            }
        }
    }
    template <typename T, typename Allocator>
    inline vector_base<T, Allocator>::vector_base(initializer_list<value_type> list) :
            vector_base(list.begin(), list.end()) {}
    template <typename T, typename Allocator>
    inline vector_base<T, Allocator>::vector_base(const vector_base &rhs) :
            vector_base(rhs.cbegin(), rhs.cend()) {}
    template <typename T, typename Allocator>
    inline vector_base<T, Allocator>::vector_base(vector_base &&rhs) noexcept :
            first {move(rhs.first)}, last {move(rhs.last)}, cursor {move(rhs.cursor)} {
        rhs.first = nullptr;
    }
    template <typename T, typename Allocator>
    template <typename AllocatorRHS>
    inline vector_base<T, Allocator>::vector_base(const vector_base<T, AllocatorRHS> &rhs) :
            vector_base(rhs.cbegin(), rhs.cend()) {}
    template <typename T, typename Allocator>
    template <typename AllocatorRHS>
    inline vector_base<T, Allocator>::vector_base(vector_base<T, AllocatorRHS> &&rhs) noexcept :
            first {move(rhs.first)}, last {move(rhs.last)}, cursor {move(rhs.cursor)} {
        rhs.first = nullptr;
    }
    template <typename T, typename Allocator>
    inline vector_base<T, Allocator>::~vector_base() noexcept {
        this->deallocate();
    }
    template <typename T, typename Allocator>
    inline vector_base<T, Allocator> &vector_base<T, Allocator>::operator=(const vector_base &rhs) {
        if(this not_eq &rhs) {
            this->assign(rhs.cbegin(), rhs.cend());
        }
        return *this;
    }
    template <typename T, typename Allocator>
    inline vector_base<T, Allocator> &vector_base<T, Allocator>::operator=(vector_base &&rhs) noexcept {
        if(this not_eq &rhs) {
            this->~vector_base();
            this->first = ds::move(rhs.first);
            this->last = ds::move(rhs.last);
            this->cursor = ds::move(rhs.cursor);
            rhs.first = nullptr;
        }
        return *this;
    }
    template <typename T, typename Allocator>
    inline vector_base<T, Allocator> &
    vector_base<T, Allocator>::operator=(initializer_list<value_type> list) {
        this->assign(list.begin(), list.end());
        return *this;
    }
    template <typename T, typename Allocator>
    template <typename AllocatorRHS>
    inline vector_base<T, Allocator> &
    vector_base<T, Allocator>::operator=(const vector_base<T, AllocatorRHS> &rhs) {
        this->assign(rhs.cbegin(), rhs.cend());
        return *this;
    }
    template <typename T, typename Allocator>
    template <typename AllocatorRHS>
    inline vector_base<T, Allocator> &
    vector_base<T, Allocator>::operator=(vector_base<T, AllocatorRHS> &&rhs) noexcept {
        this->~vector_base();
        this->first = ds::move(rhs.first);
        this->last = ds::move(rhs.last);
        this->cursor = ds::move(rhs.cursor);
        rhs.first = nullptr;
        return *this;
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::reference
    vector_base<T, Allocator>::operator[](difference_type n)
            noexcept(has_nothrow_dereference_operator<pointer>::value) {
        return *(this->first + n);
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::const_reference
    vector_base<T, Allocator>::operator[](difference_type n) const
            noexcept(has_nothrow_dereference_operator<pointer>::value) {
        return *(this->first + n);
    }
    template <typename T, typename Allocator>
    void vector_base<T, Allocator>::assign(size_type size, const_reference value) {
        if(size <= this->capacity()) {
            auto cursor {this->first};
            if(size <= this->size()) {
                while(size--) {
                    *cursor = value;
                }
                if(cursor not_eq this->cursor) {
                    this->destroy_from_insert_or_erase(cursor, this->cursor);
                    this->cursor = ds::move(cursor);
                }
                return;
            }
            while(cursor not_eq this->cursor) {
                *cursor = value;
                --size;
            }
            while(size--) {
                alloc_traits::construct(this->cursor, value);
                ++this->cursor;
            }
            return;
        }
        const auto new_size {recommend(size)};
        if(this->first) {
            this->deallocate();
        }
        this->first = this->cursor = this->allocate(new_size);
        this->last = this->first + new_size;
        while(size--) {
            alloc_traits::construct(this->cursor, value);
            ++this->cursor;
        }
    }
    template <typename T, typename Allocator>
    template <typename InputIterator>
    typename enable_if<is_input_iterator<InputIterator>::value and
                       not is_forward_iterator<InputIterator>::value, void>::type
    vector_base<T, Allocator>::assign(InputIterator begin, InputIterator end) {
        if(this->first) {
            this->clear();
        }else {
            this->first = this->cursor = this->allocate();
            this->last = this->first + this->default_size();
        }
        while(begin not_eq end) {
            alloc_traits::construct(this->cursor, ds::move(*begin++));
            ++this->cursor;
            if(this->full()) {
                this->reallocate();
            }
        }
    }
    template <typename T, typename Allocator>
    template <typename ForwardIterator>
    typename enable_if<is_forward_iterator<ForwardIterator>::value, void>::type
    vector_base<T, Allocator>::assign(ForwardIterator begin, ForwardIterator end) {
        const size_type new_size {static_cast<size_type>(distance(begin, end))};
        if(new_size <= this->capacity()) {
            auto cursor {this->first};
            if(new_size <= this->size()) {
                while(begin not_eq end) {
                    *cursor++ = *begin++;
                }
                if(cursor not_eq this->cursor) {
                    alloc_traits::destroy(cursor, this->cursor);
                    this->cursor = ds::move(cursor);
                }
                return;
            }
            while(cursor not_eq this->cursor) {
                *cursor = *begin++;
                ++cursor;
            }
            while(begin not_eq end) {
                alloc_traits::construct(this->cursor, *begin++);
                ++this->cursor;
            }
            return;
        }
        if(this->first) {
            this->deallocate();
        }
        this->first = this->cursor = this->allocate(new_size);
        this->last = this->first + new_size;
        while(begin not_eq end) {
            alloc_traits::construct(this->cursor, *begin++);
            ++this->cursor;
        }
    }
    template <typename T, typename Allocator>
    inline void vector_base<T, Allocator>::assign(initializer_list<value_type> list) {
        this->assign(list.begin(), list.end());
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::iterator vector_base<T, Allocator>::begin() noexcept {
        return iterator(this->first);
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::const_iterator
    vector_base<T, Allocator>::begin() const noexcept {
        return const_iterator {this->first};
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::iterator vector_base<T, Allocator>::end() noexcept {
        return iterator {this->cursor};
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::const_iterator
    vector_base<T, Allocator>::end() const noexcept {
        return const_iterator {this->cursor};
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::reverse_iterator
    vector_base<T, Allocator>::rbegin() noexcept {
        return reverse_iterator {this->cursor - 1};
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::const_reverse_iterator
    vector_base<T, Allocator>::rbegin() const noexcept {
        return const_reverse_iterator {this->cursor - 1};
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::reverse_iterator
    vector_base<T, Allocator>::rend() noexcept {
        return reverse_iterator {this->first - 1};
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::const_reverse_iterator
    vector_base<T, Allocator>::rend() const noexcept {
        return const_reverse_iterator {this->first - 1};
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::const_iterator
    vector_base<T, Allocator>::cbegin() const noexcept {
        return const_iterator {this->first};
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::const_iterator
    vector_base<T, Allocator>::cend() const noexcept {
        return const_iterator {this->cursor};
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::const_reverse_iterator
    vector_base<T, Allocator>::crbegin() const noexcept {
        return const_reverse_iterator {this->cursor - 1};
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::const_reverse_iterator
    vector_base<T, Allocator>::crend() const noexcept {
        return const_reverse_iterator {this->first - 1};
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::size_type vector_base<T, Allocator>::size() const noexcept {
        return this->cursor - this->first;
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::size_type
    vector_base<T, Allocator>::capacity() const noexcept {
        return this->last - this->first;
    }
    template <typename T, typename Allocator>
    inline bool vector_base<T, Allocator>::empty() const noexcept {
        return this->first == this->cursor;
    }
    template <typename T, typename Allocator>
    constexpr inline typename vector_base<T, Allocator>::size_type
    vector_base<T, Allocator>::max_size() const noexcept {
        return std::numeric_limits<size_type>::max() / sizeof(value_type);
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::size_type
    vector_base<T, Allocator>::spare() const noexcept {
        return this->last - this->cursor;
    }
    template <typename T, typename Allocator>
    inline void vector_base<T, Allocator>::reserve(size_type size) {
        if(size <= this->capacity()) {
            return;
        }
        this->resize_for_shrink_or_reserve(size);
    }
    template <typename T, typename Allocator>
    inline void vector_base<T, Allocator>::shrink_to_fit() {
        if(this->cursor == this->last) {
            return;
        }
        this->resize_for_shrink_or_reserve(this->size());
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::reference
    vector_base<T, Allocator>::at(difference_type n)
            noexcept(has_nothrow_dereference_operator<pointer>::value) {
        if(n >= 0) {
            return *(this->first + n);
        }
        return *(this->cursor - n);
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::const_reference
    vector_base<T, Allocator>::at(difference_type n) const
            noexcept(has_nothrow_dereference_operator<pointer>::value) {
        return static_cast<const_reference>(const_cast<vector_base *>(this)->at(n));
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::reference
    vector_base<T, Allocator>::front() noexcept(has_nothrow_dereference_operator<pointer>::value) {
        return *this->first;
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::const_reference
    vector_base<T, Allocator>::front() const noexcept(has_nothrow_dereference_operator<pointer>::value) {
        return *this->first;
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::reference
    vector_base<T, Allocator>::back() noexcept(has_nothrow_dereference_operator<pointer>::value) {
        return *(this->cursor - 1);
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::const_reference
    vector_base<T, Allocator>::back() const
            noexcept(has_nothrow_dereference_operator<pointer>::value) {
        return *(this->cursor - 1);
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::pointer vector_base<T, Allocator>::data() noexcept {
        return this->first;
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::const_pointer
    vector_base<T, Allocator>::data() const noexcept {
        return this->first;
    }
    template <typename T, typename Allocator>
    inline void vector_base<T, Allocator>::push_back(const_reference value) {
        if(this->full()) {
            this->reallocate();
        }
        alloc_traits::construct(this->cursor, value);
        ++this->cursor;
    }
    template <typename T, typename Allocator>
    inline void vector_base<T, Allocator>::push_back(rvalue_reference value) {
        if(this->full()) {
            this->reallocate();
        }
        alloc_traits::construct(this->cursor, ds::forward<rvalue_reference>(value));
        ++this->cursor;
    }
    template <typename T, typename Allocator>
    inline void vector_base<T, Allocator>::pop_back() noexcept {
        if(this->empty()) {
            return;
        }
        if constexpr(is_trivially_destructible<value_type>::value) {
            --this->cursor;
        }else {
            alloc_traits::destroy(this->cursor--);
        }
    }
    template <typename T, typename Allocator>
    inline void vector_base<T, Allocator>::clear() noexcept {
        if(this->first == this->cursor) {
            return;
        }
        if constexpr(not is_trivially_destructible<value_type>::value) {
            alloc_traits::destroy(this->first, this->cursor);
        }
        this->cursor = this->first;
    }
    template <typename T, typename Allocator>
    void vector_base<T, Allocator>::resize(size_type size, const_reference value) {
        if(size == this->capacity()) {
            if(this->full()) {
                return;
            }
            while(this->cursor not_eq this->last) {
                alloc_traits::construct(this->cursor, value);
                ++this->cursor;
            }
            return;
        }
        auto new_first {this->allocate(size)};
        auto new_cursor {new_first};
        auto new_last {new_first + size};
        auto cursor {this->first};
        if(size > this->size()) {
            while(cursor not_eq this->cursor) {
                if constexpr(is_nothrow_copy_constructible<value_type>::value or
                        is_nothrow_move_constructible<value_type>::value) {
                    alloc_traits::construct(new_cursor++, ds::move(*cursor++));
                }else {
                    try {
                        alloc_traits::construct(new_cursor, ds::move(*cursor++));
                        ++new_cursor;
                    }catch(...) {
                        this->handle_exception_from_alloc(new_first, new_cursor);
                        if constexpr(is_move_constructible<value_type>::value) {
                            this->deallocate();
                            this->first = this->cursor = this->last = nullptr;
                        }
                        throw;
                    }
                }
            }
            while(new_cursor not_eq new_last) {
                if constexpr(is_nothrow_copy_constructible<value_type>::value) {
                    alloc_traits::construct(new_cursor++, value);
                }else {
                    try {
                        alloc_traits::construct(new_cursor, value);
                        ++new_cursor;
                    }catch(...) {
                        this->deallocate();
                        this->first = ds::move(new_first);
                        this->cursor = ds::move(new_cursor);
                        this->last = ds::move(new_last);
                        throw;
                    }
                }
            }
        }else {
            while(size--) {
                if constexpr(is_nothrow_copy_constructible<value_type>::value or
                             is_nothrow_move_constructible<value_type>::value) {
                    alloc_traits::construct(new_cursor++, ds::move(*cursor++));
                }else {
                    try {
                        alloc_traits::construct(new_cursor, ds::move(*cursor++));
                        ++new_cursor;
                    }catch(...) {
                        this->handle_exception_from_alloc(new_first, new_cursor);
                        if constexpr(is_move_constructible<value_type>::value) {
                            this->deallocate();
                            this->first = this->cursor = this->last = nullptr;
                        }
                        throw;
                    }
                }
            }
        }
        this->first = ds::move(new_first);
        this->cursor = ds::move(new_cursor);
        this->last = ds::move(new_last);
    }
    template <typename T, typename Allocator>
    inline void vector_base<T, Allocator>::swap(vector_base &rhs) noexcept {
        ds::swap(this->first, rhs.first);
        ds::swap(this->cursor, rhs.cursor);
        ds::swap(this->last, rhs.last);
    }
    template <typename T, typename Allocator>
    template <typename AllocatorRHS>
    inline void vector_base<T, Allocator>::swap(vector_base<value_type, AllocatorRHS> &rhs) noexcept {
        ds::swap(this->first, rhs.first);
        ds::swap(this->cursor, rhs.cursor);
        ds::swap(this->last, rhs.last);
    }
    template <typename T, typename Allocator>
    typename vector_base<T, Allocator>::iterator
    vector_base<T, Allocator>::insert(difference_type pos, const_reference value, size_type size) {
        if(size == 0) {
            return iterator(this->cursor);
        }
        const auto old_size {this->size()};
        if(pos == old_size) {
            const auto return_pointer {this->cursor};
            while(size--) {
                this->push_back(value);
            }
            return iterator(return_pointer);
        }else if(pos > old_size) {
            return iterator(this->cursor);
        }
        if(size > this->spare()) {
            this->reallocate(size);
        }
        auto construct_cursor {this->cursor + (size - 1)};
        auto move_cursor {this->cursor - 1};
        const auto last_pos {move_cursor};
        const auto stop_pos {this->first + (pos - 1)};
        while(move_cursor not_eq stop_pos and construct_cursor not_eq last_pos) {
            if constexpr(is_nothrow_move_constructible<value_type>::value or
                    is_nothrow_copy_constructible<value_type>::value) {
                alloc_traits::construct(construct_cursor--, data_structure::move(*move_cursor--));
            }else {
                try {
                    alloc_traits::construct(construct_cursor, data_structure::move(*move_cursor--));
                    --construct_cursor;
                    --move_cursor;
                }catch(...) {
                    this->destroy_from_insert_or_erase(construct_cursor + 1,
                            construct_cursor + (this->cursor - move_cursor - 1));
                    if constexpr(is_move_constructible<value_type>::value) {
                        this->destroy_from_insert_or_erase(move_cursor, this->cursor);
                        this->cursor = move_cursor;
                    }
                    throw;
                }
            }
        }
        this->cursor += size;
        while(move_cursor not_eq stop_pos) {
            if constexpr(is_nothrow_copy_assignable<value_type>::value) {
                *construct_cursor-- = *move_cursor--;
            }else {
                try {
                    *construct_cursor = *move_cursor;
                    --construct_cursor;
                    --move_cursor;
                }catch(...) {
                    if constexpr(is_move_constructible<value_type>::value) {
                        this->destroy_from_insert_or_erase(stop_pos + 1, this->cursor);
                        this->cursor = stop_pos;
                    }else {
                        this->destroy_from_insert_or_erase(construct_cursor + 1, this->cursor);
                        this->cursor = construct_cursor;
                    }
                    throw;
                }
            }
        }
        if(construct_cursor - last_pos > 0) {
            while(construct_cursor not_eq last_pos) {
                if constexpr(is_nothrow_copy_constructible<value_type>::value) {
                    alloc_traits::construct(construct_cursor--, value);
                }else {
                    try {
                        alloc_traits::construct(construct_cursor, value);
                        --construct_cursor;
                    }catch(...) {
                        this->destroy_from_insert_or_erase(construct_cursor + 1, this->cursor);
                        if constexpr(is_move_constructible<value_type>::value) {
                            ++move_cursor;
                            this->destroy_from_insert_or_erase(move_cursor, last_pos + 1);
                            this->cursor = move_cursor;
                        }
                        throw;
                    }
                }
            }
        }
        while(construct_cursor not_eq stop_pos) {
            if constexpr(is_nothrow_copy_assignable<value_type>::value) {
                *construct_cursor-- = value;
            }else {
                try {
                    *construct_cursor = value;
                    --construct_cursor;
                }catch(...) {
                    if constexpr(is_move_constructible<value_type>::value) {
                        this->destroy_from_insert_or_erase(stop_pos + 1, this->cursor);
                        this->cursor = stop_pos;
                    }else {
                        this->destroy_from_insert_or_erase(construct_cursor + 1, this->cursor);
                        this->cursor = construct_cursor;
                    }
                    throw;
                }
            }
        }
        return iterator(this->first + pos);
    }
    template <typename T, typename Allocator>
    typename vector_base<T, Allocator>::iterator
    vector_base<T, Allocator>::insert(difference_type pos, rvalue_reference value) {
        if(this->full()) {
            this->reallocate();
        }
        if(pos == this->size()) {
            this->push_back(ds::forward<rvalue_reference>(value));
            return iterator(this->cursor - 1);
        }else if(pos > this->size()) {
            return iterator(this->cursor);
        }
        if constexpr(is_move_constructible<value_type>::value and
                not is_nothrow_move_constructible<value_type>::value) {
            try {
                alloc_traits::construct(this->cursor, ds::move(*(this->cursor -1)));
            }catch(...) {
                [&]() mutable noexcept -> void {
                    alloc_traits::destroy(--this->cursor);
                }();
                throw;
            }
        }else {
            alloc_traits::construct(this->cursor, ds::move(*(this->cursor - 1)));
        }
        auto move_cursor {this->cursor++};
        auto move_size {this->size() - pos};
        while(--move_size > 0) {
            if constexpr(is_nothrow_move_assignable<value_type>::value or
                    is_nothrow_copy_assignable<value_type>::value) {
                *move_cursor = ds::move(*(move_cursor - 1));
                --move_cursor;
            }else {
                try {
                    *move_cursor = ds::move(*(move_cursor - 1));
                    --move_cursor;
                }catch(...) {
                    if constexpr(is_move_assignable<value_type>::value) {
                        this->destroy_from_insert_or_erase(--move_cursor, this->cursor);
                    }else {
                        this->destroy_from_insert_or_erase(move_cursor, this->cursor);
                    }
                    this->cursor = move_cursor;
                    throw;
                }
            }
        }
        if constexpr(is_nothrow_move_assignable<value_type>::value or
                is_nothrow_copy_assignable<value_type>::value) {
            *move_cursor = ds::forward<rvalue_reference>(value);
        }else {
            try {
                *move_cursor = ds::forward<rvalue_reference>(value);
            }catch(...) {
                this->destroy_from_insert_or_erase(move_cursor, this->cursor);
                this->cursor = move_cursor;
                throw;
            }
        }
        return iterator(this->first + pos);
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::iterator
    vector_base<T, Allocator>::insert(const_iterator pos, const_reference value, size_type size) {
        return this->insert(pos - const_iterator(this->first), value, size);
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::iterator
    vector_base<T, Allocator>::insert(const_iterator pos, rvalue_reference value) {
        return this->insert(pos - const_iterator(this->first), ds::forward<rvalue_reference>(value));
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::iterator
    vector_base<T, Allocator>::insert(difference_type pos, initializer_list<value_type> list) {
        return this->insert(pos, list.begin(), list.end());
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::iterator
    vector_base<T, Allocator>::insert(const_iterator pos, initializer_list<value_type> list) {
        return this->insert(pos - const_iterator(this->first), list.begin(), list.end());
    }
    template <typename T, typename Allocator>
    template <typename InputIterator>
    inline typename vector_base<T, Allocator>::iterator
    vector_base<T, Allocator>::insert(const_iterator pos, InputIterator begin,
            typename enable_if<is_input_iterator<InputIterator>::value and
                    not is_forward_iterator<InputIterator>::value, InputIterator>::type end) {
        return this->insert(pos - const_iterator(this->first), begin, end);
    }
    template <typename T, typename Allocator>
    template <typename InputIterator>
    inline typename vector_base<T, Allocator>::iterator
    vector_base<T, Allocator>::insert(difference_type pos, InputIterator begin,
            typename enable_if<is_input_iterator<InputIterator>::value and
                    not is_forward_iterator<InputIterator>::value, InputIterator>::type end) {
        vector_base &&tmp_vec(begin, end);
        return this->insert(pos, tmp_vec.cbegin(), tmp_vec.cend());
    }
    template <typename T, typename Allocator>
    template <typename ForwardIterator>
    inline typename vector_base<T, Allocator>::iterator
    vector_base<T, Allocator>::insert(const_iterator pos, ForwardIterator begin,
            typename enable_if<is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type end) {
        return this->insert(pos - const_iterator(this->first), begin, end);
    }
    template <typename T, typename Allocator>
    template <typename ForwardIterator>
    typename vector_base<T, Allocator>::iterator
    vector_base<T, Allocator>::insert(difference_type pos, ForwardIterator begin,
            typename enable_if<is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type end) {
        auto size {static_cast<size_type>(ds::distance(begin, end))};
        if(not size) {
            return iterator(this->cursor);
        }
        const auto old_size {this->size()};
        if(size > this->spare()) {
            this->reallocate(size);
        }
        if(pos == old_size) {
            while(size--) {
                this->push_back(*begin++);
            }
            return this->begin() + old_size;
        }else if(pos > old_size) {
            return iterator(this->cursor);
        }
        auto construct_cursor {this->cursor + (size - 1)};
        auto move_cursor {this->cursor - 1};
        const auto last_pos {move_cursor};
        const auto stop_pos {this->first + (pos - 1)};
        while(move_cursor not_eq stop_pos and construct_cursor not_eq last_pos) {
            if constexpr(is_nothrow_move_constructible<value_type>::value or
                         is_nothrow_copy_constructible<value_type>::value) {
                alloc_traits::construct(construct_cursor--, ds::move(*move_cursor--));
            }else {
                try {
                    alloc_traits::construct(construct_cursor, ds::move(*move_cursor--));
                    --construct_cursor;
                    --move_cursor;
                }catch(...) {
                    this->destroy_from_insert_or_erase(construct_cursor + 1,
                            construct_cursor + (this->cursor - move_cursor - 1));
                    if constexpr(is_move_constructible<value_type>::value) {
                        this->destroy_from_insert_or_erase(move_cursor, this->cursor);
                        this->cursor = move_cursor;
                    }
                    throw;
                }
            }
        }
        this->cursor += size;
        while(move_cursor not_eq stop_pos) {
            if constexpr(is_nothrow_copy_assignable<value_type>::value) {
                *construct_cursor-- = *move_cursor--;
            }else {
                try {
                    *construct_cursor = *move_cursor;
                    --construct_cursor;
                    --move_cursor;
                }catch(...) {
                    if constexpr(is_move_constructible<value_type>::value) {
                        this->destroy_from_insert_or_erase(stop_pos + 1, this->cursor);
                        this->cursor = stop_pos;
                    }else {
                        this->destroy_from_insert_or_erase(construct_cursor + 1, this->cursor);
                        this->cursor = construct_cursor;
                    }
                    throw;
                }
            }
        }
        if(construct_cursor - last_pos > 0) {
            while(construct_cursor not_eq last_pos) {
                if constexpr(is_nothrow_copy_constructible<value_type>::value) {
                    alloc_traits::construct(construct_cursor--, *begin++);
                }else {
                    try {
                        alloc_traits::construct(construct_cursor, *begin);
                        --construct_cursor;
                        ++begin;
                    }catch(...) {
                        this->destroy_from_insert_or_erase(construct_cursor + 1, this->cursor);
                        if constexpr(is_move_constructible<value_type>::value) {
                            ++move_cursor;
                            this->destroy_from_insert_or_erase(move_cursor, last_pos + 1);
                            this->cursor = move_cursor;
                        }
                        throw;
                    }
                }
            }
        }
        while(construct_cursor not_eq stop_pos) {
            if constexpr(is_nothrow_copy_assignable<value_type>::value) {
                *construct_cursor-- = *begin;;
            }else {
                try {
                    *construct_cursor = *begin;
                    --construct_cursor;
                    ++begin;
                }catch(...) {
                    if constexpr(is_move_constructible<value_type>::value) {
                        this->destroy_from_insert_or_erase(stop_pos + 1, this->cursor);
                        this->cursor = stop_pos;
                    }else {
                        this->destroy_from_insert_or_erase(construct_cursor + 1, this->cursor);
                        this->cursor = construct_cursor;
                    }
                    throw;
                }
            }
        }
        return iterator(this->first + pos);
    }
    template <typename T, typename Allocator>
    template <typename ...Args>
    inline void vector_base<T, Allocator>::emplace_back(Args &&...args) {
        this->push_back(value_type(ds::forward<Args>(args)...));
    }
    template <typename T, typename Allocator>
    template <typename ...Args>
    inline typename vector_base<T, Allocator>::iterator
    vector_base<T, Allocator>::emplace(const_iterator pos, Args &&...args) {
        return this->insert(pos - const_iterator(this->first), value_type(ds::forward<Args>(args)...));
    }
    template <typename T, typename Allocator>
    template <typename ...Args>
    inline typename vector_base<T, Allocator>::iterator
    vector_base<T, Allocator>::emplace(difference_type pos, Args &&...args) {
        return this->insert(pos, value_type(ds::forward<Args>(args)...));
    }
    template <typename T, typename Allocator>
    typename vector_base<T, Allocator>::iterator
    vector_base<T, Allocator>::erase(difference_type pos, size_type size) noexcept {
        auto move_cursor {this->first + pos};
        auto forward_cursor {move_cursor + size};
        while(forward_cursor not_eq this->cursor) {
            if constexpr(is_nothrow_copy_assignable<value_type>::value and
                    is_nothrow_move_assignable<value_type>::value) {
                *move_cursor++ = ds::move(*forward_cursor++);
            }else {
                try {
                    *move_cursor++ = ds::move(*forward_cursor++);
                }catch(...) {
                    this->destroy_from_insert_or_erase(move_cursor, this->cursor);
                    this->cursor = move_cursor;
                    throw;
                }
            }
        }
        this->destroy_from_insert_or_erase(move_cursor, this->cursor);
        this->cursor = ds::move(move_cursor);
        return iterator(this->first + pos);
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::iterator
    vector_base<T, Allocator>::erase(const_iterator pos, size_type size) noexcept {
        return this->erase(pos - const_iterator(this->first), size);
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::iterator
    vector_base<T, Allocator>::erase(const_iterator begin, const_iterator end) noexcept {
        return this->erase(begin - const_iterator(this->first), end - begin);
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::iterator
    vector_base<T, Allocator>::erase(const_iterator iter) noexcept {
        return this->erase(iter, iter + 1);
    }
    template <typename T, typename AllocatorLHS, typename AllocatorRHS>
    inline void swap(vector_base<T, AllocatorLHS> &lhs, vector_base<T, AllocatorRHS> &rhs) noexcept {
        lhs.swap(rhs);
    }
    template <typename T, typename AllocatorLHS, typename AllocatorRHS>
    bool operator==(const vector_base<T, AllocatorLHS> &lhs, const vector_base<T, AllocatorRHS> &rhs)
            noexcept(has_nothrow_equal_to_operator<T>::value) {
        if(lhs.size() not_eq rhs.size()) {
            return false;
        }
        auto lhs_cursor {lhs.cbegin()};
        auto rhs_cursor {rhs.cbegin()};
        const auto lhs_end_pos {lhs.cend()};
        while(lhs_cursor not_eq lhs_end_pos) {
            if(*lhs_cursor++ not_eq *rhs_cursor++) {
                return false;
            }
        }
        return true;
    }
    template <typename T, typename AllocatorLHS, typename AllocatorRHS>
    inline
    bool operator!=(const vector_base<T, AllocatorLHS> &lhs, const vector_base<T, AllocatorRHS> &rhs)
            noexcept(has_nothrow_equal_to_operator<T>::value) {
        return not(lhs == rhs);
    }
    template <typename T, typename AllocatorLHS, typename AllocatorRHS>
    bool operator<(const vector_base<T, AllocatorLHS> &lhs, const vector_base<T, AllocatorRHS> &rhs)
            noexcept(has_nothrow_less_operator<T>::value) {
        auto lhs_cursor {lhs.cbegin()};
        auto rhs_cursor {rhs.cbegin()};
        if(lhs.size() < rhs.size()) {
            const auto lhs_end_pos {lhs.cend()};
            while(lhs_cursor not_eq lhs_end_pos) {
                if(not(*lhs_cursor++ < *rhs_cursor++)) {
                    return false;
                }
            }
            return true;
        }
        const auto rhs_end_pos {rhs.cend()};
        while(rhs_cursor not_eq rhs_end_pos) {
            if(not(*lhs_cursor++ < *rhs_cursor++)) {
                return false;
            }
        }
        return false;
    }
    template <typename T, typename AllocatorLHS, typename AllocatorRHS>
    inline
    bool operator<=(const vector_base<T, AllocatorLHS> &lhs, const vector_base<T, AllocatorRHS> &rhs)
            noexcept(has_nothrow_less_operator<T>::value and has_nothrow_equal_to_operator<T>::value) {
        return not(rhs < lhs);
    }
    template <typename T, typename AllocatorLHS, typename AllocatorRHS>
    inline
    bool operator>(const vector_base<T, AllocatorLHS> &lhs, const vector_base<T, AllocatorRHS> &rhs)
            noexcept(has_nothrow_less_operator<T>::value and has_nothrow_equal_to_operator<T>::value) {
        return rhs < lhs;
    }
    template <typename T, typename AllocatorLHS, typename AllocatorRHS>
    inline
    bool operator>=(const vector_base<T, AllocatorLHS> &lhs, const vector_base<T, AllocatorRHS> &rhs)
            noexcept(has_nothrow_less_operator<T>::value) {
        return not(lhs < rhs);
    }
}

namespace data_structure::__data_structure_auxiliary {
    template <typename T, typename Allocator = allocator<type_holder<T>>>
    class vector_char : public vector_base<T, Allocator> {
        static_assert(is_character_v<T>, "The first template parameter must be character type!");
    private:
        using base = vector_base<T, Allocator>;
        using alloc_traits = allocator_traits<typename base::allocator_type>;
    public:
        using allocator_type = typename base::allocator_type;
        using size_type = typename base::size_type;
        using difference_type = typename base::difference_type;
        using value_type = typename base::value_type;
        using reference = typename base::reference;
        using const_reference = typename base::const_reference;
        using rvalue_reference = typename base::rvalue_reference;
        using pointer = typename base::pointer;
        using const_pointer = typename base::const_pointer;
        using iterator = typename base::iterator;
        using const_iterator = typename base::const_iterator;
        using reverse_iterator = typename base::reverse_iterator;
        using const_reverse_iterator = typename base::const_reverse_iterator;
    public:
        constexpr static inline auto no_position {static_cast<size_type>(-1)};
    private:
        constexpr static const auto case_sensitive_compare {[](value_type a, value_type b) noexcept -> bool {
            return a == b;
        }};
        constexpr static const auto case_insensitive_compare {[](value_type a, value_type b) noexcept -> bool {
            return ds::to_upper(a) == ds::to_upper(b);
        }};
    private:
        template <typename VectorIterator, typename Compare>
        static VectorIterator find_auxiliary(VectorIterator, VectorIterator, value_type,
                difference_type, Compare &) noexcept;
        template <typename VectorIterator, typename Compare>
        static VectorIterator find_auxiliary(VectorIterator, VectorIterator,
                const_pointer, const_pointer, size_type, difference_type, Compare &) noexcept;
    private:
        template <bool = true, typename FindType>
        iterator find_last_of_auxiliary(FindType &&, difference_type) const noexcept;
        template <bool = true, typename FindType>
        iterator find_first_not_of_auxiliary(FindType &&, difference_type) const noexcept;
        template <bool = true, typename FindType>
        iterator remove_auxiliary(FindType &&) noexcept;
    public:
        using vector_base<T, Allocator>::vector_base;
        explicit vector_char(const_pointer, difference_type = 0, size_type = no_position);
        vector_char(const vector_char &, difference_type, size_type = no_position);
    public:
        using vector_base<T, Allocator>::operator=;
        vector_char &operator=(const_pointer);
        vector_char &operator+=(const vector_char &);
        vector_char &operator+=(const_pointer);
        vector_char &operator+=(value_type);
        vector_char &operator+=(initializer_list<value_type>);
    public:
        void assign(const vector_char &, difference_type = 0, size_type = no_position);
        void assign(const_pointer, difference_type = 0, size_type = no_position);
        [[nodiscard]]
        pointer c_str() noexcept;
        [[nodiscard]]
        const_pointer c_str() const noexcept;
        [[nodiscard]]
        size_type length() const noexcept;
        [[nodiscard]]
        size_type c_length() const noexcept;
        void append(value_type, size_type = 1);
        void append(const vector_char &, difference_type = 0, size_type = no_position);
        void append(const_pointer, difference_type = 0, size_type = no_position);
        template <typename InputIterator>
        void append(typename enable_if<is_input_iterator<InputIterator>::value and
                not is_forward_iterator<InputIterator>::value, InputIterator>::type, InputIterator);
        template <typename ForwardIterator>
        void append(typename enable_if<is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type,
                ForwardIterator);
        void append(initializer_list<value_type>);
        [[nodiscard]]
        bool starts_with(const vector_char &) const noexcept;
        [[nodiscard]]
        bool starts_with(const_pointer) const noexcept;
        [[nodiscard]]
        bool starts_with(value_type) const noexcept;
        [[nodiscard]]
        bool ends_with(const vector_char &) const noexcept;
        [[nodiscard]]
        bool ends_with(const_pointer) const noexcept;
        [[nodiscard]]
        bool ends_with(value_type) const noexcept;
        [[nodiscard]]
        bool upper() const noexcept;
        [[nodiscard]]
        bool lower() const noexcept;
        [[nodiscard]]
        bool number() const noexcept;
        [[nodiscard]]
        bool symbol() const noexcept;
        [[nodiscard]]
        bool c_end() const noexcept;
        void to_upper() noexcept;
        void to_lower() noexcept;
        vector_char substring(difference_type = 0, size_type = no_position) const;
        void substring(pointer, difference_type = 0, size_type = no_position) const noexcept;
        void copy(pointer, difference_type = 0, size_type = no_position) const noexcept;
        [[nodiscard]]
        int compare(const vector_char &) const noexcept;
        [[nodiscard]]
        int compare(const_pointer) const noexcept;
        [[nodiscard]]
        int compare_insensitive(const vector_char &) const noexcept;
        [[nodiscard]]
        int compare_insensitive(const_pointer) const noexcept;
        [[nodiscard]]
        iterator find(value_type, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator find(const vector_char &, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator find(const_pointer, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator find_insensitive(value_type, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator find_insensitive(const vector_char &, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator find_insensitive(const_pointer, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator rfind(value_type, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator rfind(const vector_char &, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator rfind(const_pointer, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator rfind_insensitive(value_type, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator rfind_insensitive(const vector_char &, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator rfind_insensitive(const_pointer, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator find_first_of(value_type, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator find_first_of(const vector_char &, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator find_first_of(const_pointer, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator find_first_of_insensitive(value_type, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator find_first_of_insensitive(const vector_char &, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator find_first_of_insensitive(const_pointer, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator find_last_of(value_type, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator find_last_of(const vector_char &, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator find_last_of(const_pointer, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator find_last_of_insensitive(value_type, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator find_last_of_insensitive(const vector_char &, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator find_last_of_insensitive(const_pointer, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator find_first_not_of(value_type, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator find_first_not_of(const vector_char &, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator find_first_not_of(const_pointer, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator find_first_not_of_insensitive(value_type, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator find_first_not_of_insensitive(const vector_char &, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator find_first_not_of_insensitive(const_pointer, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator find_last_not_of(value_type, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator find_last_not_of(const vector_char &, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator find_last_not_of(const_pointer, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator find_last_not_of_insensitive(value_type, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator find_last_not_of_insensitive(const vector_char &, difference_type = 0) const noexcept;
        [[nodiscard]]
        iterator find_last_not_of_insensitive(const_pointer, difference_type = 0) const noexcept;
        iterator remove(difference_type, size_type = 1) noexcept;
        iterator remove(value_type) noexcept;
        iterator remove(const_pointer) noexcept;
        iterator remove(const vector_char &) noexcept;
        iterator remove_insensitive(value_type) noexcept;
        iterator remove_insensitive(const_pointer) noexcept;
        iterator remove_insensitive(const vector_char &) noexcept;
    };
}

namespace data_structure::__data_structure_auxiliary {
    /* private functions */
    template <typename T, typename Allocator>
    template <typename VectorIterator, typename Compare>
    VectorIterator vector_char<T, Allocator>::find_auxiliary(VectorIterator begin,
            VectorIterator end, value_type ch, difference_type start_pos, Compare &cmp) noexcept {
        begin += start_pos;
        const auto size {end - begin};
        if(size <= 0) {
            return iterator(end);
        }
        do {
            if(cmp(*begin, ch)) {
                return iterator(begin);
            }
            ++begin;
        }while(begin not_eq end);
        return iterator(end);
    }
    template <typename T, typename Allocator>
    template <typename VectorIterator, typename Compare>
    VectorIterator vector_char<T, Allocator>::find_auxiliary(VectorIterator begin, VectorIterator end,
            const_pointer str_begin, const_pointer str_end,
            size_type str_size, difference_type start_pos, Compare &cmp) noexcept {
        begin += start_pos;
        const auto size {end - begin};
        if(size <= 0 or str_size == 0 or size < str_size) {
            return end;
        }
        auto str_cursor {str_begin};
        while(begin not_eq end) {
            auto backup {begin};
            while(true) {
                if(not cmp(*begin, *str_cursor)) {
                    break;
                }
                if(++str_cursor == str_end) {
                    return backup;
                }
                if(++begin == end) {
                    return end;
                }
            }
            begin = backup + 1;
            if(static_cast<size_type>(end - begin) < str_size) {
                return end;
            }
            if(str_cursor not_eq str_begin) {
                str_cursor = str_begin;
            }
        }
        return end;
    }
    template <typename T, typename Allocator>
    template <bool CaseSensitive, typename FindType>
    typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::find_last_of_auxiliary(
            FindType &&value, difference_type start_pos) const noexcept {
        vector_char *const remove_const_this {const_cast<vector_char *>(this)};
        const auto begin {remove_const_this->begin()};
        const auto end {remove_const_this->end()};
        if constexpr(CaseSensitive) {
            auto result {this->find(ds::forward<FindType>(value), start_pos)};
            while(true) {
                auto new_result{this->find(ds::forward<FindType>(value), start_pos + (result - begin))};
                if(new_result == end) {
                    break;
                }
                result = new_result;
            }
            return result;
        }else {
            auto result {this->find_insensitive(ds::forward<FindType>(value), start_pos)};
            while(true) {
                auto new_result{this->find_insensitive(
                        ds::forward<FindType>(value), start_pos + (result - begin))};
                if(new_result == end) {
                    break;
                }
                result = new_result;
            }
            return result;
        }
    }
    template <typename T, typename Allocator>
    template <bool CaseSensitive, typename FindType>
    typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::find_first_not_of_auxiliary(
            FindType &&value, difference_type start_pos) const noexcept {
        vector_char *const remove_const_this {const_cast<vector_char *>(this)};
        const auto begin {remove_const_this->begin()};
        const auto end {remove_const_this->end()};
        if constexpr(CaseSensitive) {
            auto result {this->find(ds::forward<FindType>(value), start_pos)};
            while(true) {
                auto new_result {this->find(ds::forward<FindType>(value), start_pos + (result - begin))};
                if(new_result == end) {
                    return result + 1;
                }
                if(new_result not_eq ++result) {
                    break;
                }
            }
            return result;
        }else {
            auto result {this->find(ds::forward<FindType>(value), start_pos)};
            while(true) {
                auto new_result {this->find_insensitive(
                        ds::forward<FindType>(value), start_pos + (result - begin))};
                if(new_result == end) {
                    return result + 1;
                }
                if(new_result not_eq ++result) {
                    break;
                }
            }
            return result;
        }
    }
    template <typename T, typename Allocator>
    template <bool CaseSensitive, typename FindType>
    typename vector_char<T, Allocator>::iterator
    vector_char<T, Allocator>::remove_auxiliary(FindType &&value) noexcept {
        if constexpr(CaseSensitive) {
            auto result {this->find(ds::forward<FindType>(value))};
            const auto begin {this->begin()};
            while(result not_eq this->end()) {
                const auto offset {result - begin};
                this->erase(result);
                result = this->find(ds::forward<FindType>(value), offset);
            }
            return result;
        }else {
            auto result {this->find_insensitive(ds::forward<FindType>(value))};
            const auto begin {this->begin()};
            while(result not_eq this->end()) {
                const auto offset {result - begin};
                this->erase(result);
                result = this->find_insensitive(ds::forward<FindType>(value), offset);
            }
            return result;
        }
    }

    /* public functions */
    template <typename T, typename Allocator>
    inline vector_char<T, Allocator>::vector_char(const_pointer str, difference_type start_pos, size_type size) :
            base(str + start_pos, str + (size == vector_char::no_position ?
                    ds::string_length(str) : static_cast<difference_type>(size))) {}
    template <typename T, typename Allocator>
    inline vector_char<T, Allocator>::vector_char(const vector_char &str, difference_type start_pos, size_type size) :
            base(str.cbegin() + start_pos, str.cbegin() +
                    (size == vector_char::no_position ? str.size() : static_cast<difference_type>(size))) {}
    template <typename T, typename Allocator>
    inline vector_char<T, Allocator> &vector_char<T, Allocator>::operator=(const_pointer str) {
        auto str_end {str};
        while(*str_end != '\0') {
            ++str_end;
        }
        this->assign(str, str_end);
        return *this;
    }
    template <typename T, typename Allocator>
    inline vector_char<T, Allocator> &vector_char<T, Allocator>::operator+=(const vector_char &str) {
        this->append(str);
        return *this;
    }
    template <typename T, typename Allocator>
    inline vector_char<T, Allocator> &vector_char<T, Allocator>::operator+=(const_pointer str) {
        this->append(str);
        return *this;
    }
    template <typename T, typename Allocator>
    inline vector_char<T, Allocator> &vector_char<T, Allocator>::operator+=(value_type ch) {
        this->push_back(ch);
        return *this;
    }
    template <typename T, typename Allocator>
    inline vector_char<T, Allocator> &vector_char<T, Allocator>::operator+=(initializer_list<value_type> init_list) {
        this->append(init_list.begin(), init_list.end());
        return *this;
    }
    template <typename T, typename Allocator>
    inline void vector_char<T, Allocator>::assign(const vector_char &str, difference_type start_pos, size_type size) {
        const auto begin {str.cbegin() + start_pos};
        this->assign(begin, begin + static_cast<difference_type>(size));
    }
    template <typename T, typename Allocator>
    inline void vector_char<T, Allocator>::assign(const_pointer str, difference_type start_pos, size_type size) {
        this->assign(str + start_pos, str + (start_pos + static_cast<difference_type>(size)));
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::pointer vector_char<T, Allocator>::c_str() noexcept {
        if(*(this->cursor - 1) == '\0') {
            return this->first;
        }
        alloc_traits::construct(this->cursor++, '\0');
        return this->first;
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::const_pointer vector_char<T, Allocator>::c_str() const noexcept {
        if(*(this->cursor - 1) == '\0') {
            return this->first;
        }
        alloc_traits::construct(this->cursor++, '\0');
        return this->first;
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::size_type vector_char<T, Allocator>::length() const noexcept {
        return this->size();
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::size_type vector_char<T, Allocator>::c_length() const noexcept {
        if(*(this->cursor - 1) == '\0') {
            return this->size();
        }
        alloc_traits::construct(this->cursor++, '\0');
        return this->size();
    }
    template <typename T, typename Allocator>
    void vector_char<T, Allocator>::append(value_type ch, size_type size) {
        if(size > this->spare()) {
            this->reallocate(size);
        }
        while(size--) {
            alloc_traits::construct(this->cursor++, ch);
        }
    }
    template <typename T, typename Allocator>
    void vector_char<T, Allocator>::append(const_pointer str, difference_type start_pos, size_type size) {
        const auto begin {str + start_pos};
        if((size == vector_char::no_position ? ds::string_length(str) : size) > this->spare()) {
            this->reallocate(size);
        }
        while(size--) {
            alloc_traits::construct(this->cursor++, *begin++);
        }
    }
    template <typename T, typename Allocator>
    void vector_char<T, Allocator>::append(const vector_char &str, difference_type start_pos, size_type size) {
        const auto begin {str.cbegin() + start_pos};
        if((size == vector_char::no_position ? ds::string_length(str) : size) > this->spare()) {
            this->reallocate(size);
        }
        while(size--) {
            alloc_traits::construct(this->cursor++, *begin++);
        }
    }
    template <typename T, typename Allocator>
    template <typename InputIterator>
    inline void vector_char<T, Allocator>::append(typename enable_if<
            is_input_iterator<InputIterator>::value and not
                    is_forward_iterator<InputIterator>::value, InputIterator>::type begin,
            InputIterator end) {
        this->insert(this->cend(), begin, end);
    }
    template <typename T, typename Allocator>
    template <typename ForwardIterator>
    inline void vector_char<T, Allocator>::append(typename enable_if<
            is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type begin, ForwardIterator end) {
        this->insert(this->cend(), begin, end);
    }
    template <typename T, typename Allocator>
    inline void vector_char<T, Allocator>::append(initializer_list<value_type> init_list) {
        this->insert(this->cend(), init_list.begin(), init_list.end());
    }
    template <typename T, typename Allocator>
    inline bool vector_char<T, Allocator>::starts_with(const vector_char &str) const noexcept {
        const auto str_size {str.size()};
        return this->size() < str_size and this->compare(str, 0, str_size) == 0;
    }
    template <typename T, typename Allocator>
    inline bool vector_char<T, Allocator>::starts_with(const_pointer str) const noexcept {
        const auto str_size {[str]() noexcept -> size_type {
            auto cursor {str};
            while(*cursor not_eq '\0') {
                ++cursor;
            }
            return static_cast<size_type>(cursor - str);
        }()};
        return this->size() < str_size and this->compare(str, 0, str_size) == 0;
    }
    template <typename T, typename Allocator>
    inline bool vector_char<T, Allocator>::starts_with(value_type ch) const noexcept {
        return this->empty() ? false : *this->first == ch;
    }
    template <typename T, typename Allocator>
    inline bool vector_char<T, Allocator>::ends_with(const vector_char &str) const noexcept {
        const auto str_size {str.size()};
        return this->size() < str_size and this->compare(str, str_size - 1) == 0;
    }
    template <typename T, typename Allocator>
    inline bool vector_char<T, Allocator>::ends_with(const_pointer str) const noexcept {
        const auto str_size {[str]() noexcept -> size_type {
            auto cursor {str};
            while(*cursor not_eq '\0') {
                ++cursor;
            }
            return static_cast<size_type>(cursor - str);
        }()};
        return this->size() < str_size and this->compare(str, str_size - 1) == 0;
    }
    template <typename T, typename Allocator>
    inline bool vector_char<T, Allocator>::ends_with(value_type ch) const noexcept {
        return this->empty() ? false : *(this->cursor - 1) == ch;
    }
    template <typename T, typename Allocator>
    bool vector_char<T, Allocator>::upper() const noexcept {
        auto cursor {this->first};
        while(cursor not_eq this->cursor) {
            if(*cursor > 'a' and *cursor < 'z') {
                return false;
            }
        }
        return true;
    }
    template <typename T, typename Allocator>
    bool vector_char<T, Allocator>::lower() const noexcept {
        auto cursor {this->first};
        while(cursor not_eq this->cursor) {
            if(*cursor > 'A' and *cursor < 'Z') {
                return false;
            }
        }
        return true;
    }
    template <typename T, typename Allocator>
    bool vector_char<T, Allocator>::number() const noexcept {
        auto cursor {this->first};
        while(cursor not_eq this->cursor) {
            if(*cursor < '0' or *cursor > '9') {
                return false;
            }
        }
        return true;
    }
    template <typename T, typename Allocator>
    inline bool vector_char<T, Allocator>::symbol() const noexcept {
        return not this->upper() and not this->lower() and this->number();
    }
    template <typename T, typename Allocator>
    inline bool vector_char<T, Allocator>::c_end() const noexcept {
        return *(this->cursor - 1) == '\0';
    }
    template <typename T, typename Allocator>
    void vector_char<T, Allocator>::to_upper() noexcept {
        auto cursor {this->first};
        while(cursor not_eq this->cursor) {
            if(*cursor > 'a' and *cursor < 'z') {
                *cursor -= 32;
            }
        }
    }
    template <typename T, typename Allocator>
    void vector_char<T, Allocator>::to_lower() noexcept {
        auto cursor {this->first};
        while(cursor not_eq this->cursor) {
            if(*cursor > 'a' and *cursor < 'z') {
                *cursor += 32;
            }
        }
    }
    template <typename T, typename Allocator>
    inline vector_char<T, Allocator> vector_char<T, Allocator>::substring(
            difference_type start_pos, size_type size) const {
        const auto begin {this->cbegin() + start_pos};
        return vector_char(begin, size > this->size() ? this->cend() : begin + static_cast<difference_type>(size));
    }
    template <typename T, typename Allocator>
    void vector_char<T, Allocator>::substring(
            pointer buffer, difference_type start_pos, size_type size) const noexcept {
        auto cursor {this->first + start_pos};
        if(size < this->size()) {
            while(size--) {
                *buffer++ = *cursor++;
            }
            return;
        }
        while(cursor not_eq this->cursor) {
            *buffer++ = *cursor++;
        }
    }
    template <typename T, typename Allocator>
    inline void vector_char<T, Allocator>::copy(
            pointer buffer, difference_type start_pos, size_type size) const noexcept {
        this->substring(buffer, start_pos, size);
    }
    template <typename T, typename Allocator>
    int vector_char<T, Allocator>::compare(const vector_char &str) const noexcept {
        if(this == &str) {
            return 0;
        }
        auto lhs_cursor {this->first};
        auto rhs_cursor {str.first};
        while(lhs_cursor not_eq this->cursor and rhs_cursor not_eq str.cursor) {
            if(vector_char::case_sensitive_compare(*lhs_cursor, *rhs_cursor)) {
                return *lhs_cursor - *rhs_cursor;
            }
            ++lhs_cursor;
            ++rhs_cursor;
        }
        if(lhs_cursor == this->cursor) {
            if(str == str.cursor) {
                return 0;
            }
            return *rhs_cursor;
        }
        return *lhs_cursor;
    }
    template <typename T, typename Allocator>
    int vector_char<T, Allocator>::compare(const_pointer str) const noexcept {
        auto lhs_cursor {this->first};
        auto rhs_cursor {str};
        while(lhs_cursor not_eq this->cursor and *rhs_cursor not_eq '\0') {
            if(vector_char::case_sensitive_compare(*lhs_cursor, *rhs_cursor)) {
                return *lhs_cursor - *rhs_cursor;
            }
            ++lhs_cursor;
            ++rhs_cursor;
        }
        if(lhs_cursor == this->cursor) {
            return *rhs_cursor;
        }
        return *lhs_cursor;
    }
    template <typename T, typename Allocator>
    int vector_char<T, Allocator>::compare_insensitive(const vector_char &str) const noexcept {
        if(this == &str) {
            return 0;
        }
        auto lhs_cursor {this->first};
        auto rhs_cursor {str.first};
        while(lhs_cursor not_eq this->cursor and rhs_cursor not_eq str.cursor) {
            if(vector_char::case_insensitive_compare(*lhs_cursor, *rhs_cursor)) {
                return *lhs_cursor - *rhs_cursor;
            }
            ++lhs_cursor;
            ++rhs_cursor;
        }
        if(lhs_cursor == this->cursor) {
            if(str == str.cursor) {
                return 0;
            }
            return *rhs_cursor;
        }
        return *lhs_cursor;
    }
    template <typename T, typename Allocator>
    int vector_char<T, Allocator>::compare_insensitive(const_pointer str) const noexcept {
        auto lhs_cursor {this->first};
        auto rhs_cursor {str};
        while(lhs_cursor not_eq this->cursor and *rhs_cursor not_eq '\0') {
            if(vector_char::case_insensitive_compare(*lhs_cursor, *rhs_cursor)) {
                return *lhs_cursor - *rhs_cursor;
            }
            ++lhs_cursor;
            ++rhs_cursor;
        }
        if(lhs_cursor == this->cursor) {
            return *rhs_cursor;
        }
        return *lhs_cursor;
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::find(
            value_type ch, difference_type start_pos) const noexcept {
        vector_char *const remove_const_this {const_cast<vector_char *>(this)};
        return vector_char::find_auxiliary(remove_const_this->begin(), remove_const_this->end(),
                ch, start_pos, vector_char::case_sensitive_compare);
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::find(
            const vector_char &str, difference_type start_pos) const noexcept {
        vector_char *const remove_const_this {const_cast<vector_char *>(this)};
        return vector_char::find_auxiliary(remove_const_this->begin(), remove_const_this->end(), str.first,
                str.cursor - str.c_end() ? 1 : 0,
                str.size(), start_pos, vector_char::case_sensitive_compare);
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::find(
            const_pointer str, difference_type start_pos) const noexcept {
        const auto length {string_length(str)};
        vector_char *const remove_const_this {const_cast<vector_char *>(this)};
        return vector_char::find_auxiliary(remove_const_this->begin(), remove_const_this->end(), str,
                str + (static_cast<ptrdiff_t>(length) - 1),
                length, start_pos, vector_char::case_sensitive_compare);
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::find_insensitive(
            value_type ch, difference_type start_pos) const noexcept {
        vector_char *const remove_const_this {const_cast<vector_char *>(this)};
        return vector_char::find_auxiliary(remove_const_this->begin(), remove_const_this->end(),
                ch, start_pos, vector_char::case_insensitive_compare);
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::find_insensitive(
            const vector_char &str, difference_type start_pos) const noexcept {
        vector_char *const remove_const_this {const_cast<vector_char *>(this)};
        return vector_char::find_auxiliary(remove_const_this->begin(), remove_const_this->end(),
                str.first, str.cursor - str.c_end() ? 1 : 0,
                str.size(), start_pos, vector_char::case_insensitive_compare);
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::find_insensitive(
            const_pointer str, difference_type start_pos) const noexcept {
        vector_char *const remove_const_this {const_cast<vector_char *>(this)};
        const auto length {string_length(str)};
        return vector_char::find_auxiliary(remove_const_this->begin(), remove_const_this->end(), str,
                str + (static_cast<ptrdiff_t>(length) - 1),
                length, start_pos, vector_char::case_insensitive_compare);
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::rfind(
            value_type ch, difference_type start_pos) const noexcept {
        vector_char *const remove_const_this {const_cast<vector_char *>(this)};
        return iterator(vector_char::find_auxiliary(remove_const_this->rbegin(), remove_const_this->rend(),
                ch, start_pos, vector_char::case_sensitive_compare).base());
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::rfind(
            const vector_char &str, difference_type start_pos) const noexcept {
        vector_char *const remove_const_this {const_cast<vector_char *>(this)};
        return iterator(vector_char::find_auxiliary(remove_const_this->rbegin(), remove_const_this->rend(),
                str.first, str.cursor - str.c_end() ? 1 : 0,
                str.size(), start_pos, vector_char::case_sensitive_compare).base());
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::rfind(
            const_pointer str, difference_type start_pos) const noexcept {
        vector_char *const remove_const_this {const_cast<vector_char *>(this)};
        const auto length {string_length(str)};
        return iterator(vector_char::find_auxiliary(remove_const_this->rbegin(),
                remove_const_this->rend(), str, str + (static_cast<ptrdiff_t>(length) - 1),
                length, start_pos, vector_char::case_sensitive_compare).base());
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::rfind_insensitive(
            value_type ch, difference_type start_pos) const noexcept {
        vector_char *const remove_const_this {const_cast<vector_char *>(this)};
        return iterator(vector_char::find_auxiliary(remove_const_this->rbegin(), remove_const_this->rend(),
                ch, start_pos, vector_char::case_insensitive_compare).base());
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::rfind_insensitive(
            const vector_char &str, difference_type start_pos) const noexcept {
        vector_char *const remove_const_this {const_cast<vector_char *>(this)};
        return iterator(vector_char::find_auxiliary(remove_const_this->rbegin(), remove_const_this->rend(),
                str.first, str.cursor - str.c_end() ? 1 : 0,
                str.size(), start_pos, vector_char::case_insensitive_compare).base());
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::rfind_insensitive(
            const_pointer str, difference_type start_pos) const noexcept {
        vector_char *const remove_const_this {const_cast<vector_char *>(this)};
        const auto length {string_length(str)};
        return iterator(vector_char::find_auxiliary(remove_const_this->rbegin(),
                remove_const_this->rend(), str, str + (static_cast<ptrdiff_t>(length) - 1),
                length, start_pos, vector_char::case_insensitive_compare).base());
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::find_first_of(
            value_type ch, difference_type start_pos) const noexcept {
        return this->find(ch, start_pos);
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::find_first_of(
            const vector_char &str, difference_type start_pos) const noexcept {
        return this->find(str, start_pos);
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::find_first_of(
            const_pointer str, difference_type start_pos) const noexcept {
        return this->find(str, start_pos);
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::find_first_of_insensitive(
            value_type ch, difference_type start_pos) const noexcept {
        return this->find_insensitive(ch, start_pos);
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::find_first_of_insensitive(
            const vector_char &str, difference_type start_pos) const noexcept {
        return this->find_insensitive(str, start_pos);
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::find_first_of_insensitive(
            const_pointer str, difference_type start_pos) const noexcept {
        return this->find_insensitive(str, start_pos);
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::find_last_of(
            value_type ch, difference_type start_pos) const noexcept {
        return this->find_last_of_auxiliary(ch, start_pos);
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::find_last_of(
            const vector_char &str, difference_type start_pos) const noexcept {
        return this->find_last_of_auxiliary(str, start_pos);
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::find_last_of(
            const_pointer str, difference_type start_pos) const noexcept {
        return this->find_last_of_auxiliary(str, start_pos);
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::find_last_of_insensitive(
            value_type ch, difference_type start_pos) const noexcept {
        return this->find_last_of_auxiliary<false>(ch, start_pos);
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::find_last_of_insensitive(
            const vector_char &str, difference_type start_pos) const noexcept {
        return this->find_last_of_auxiliary<false>(str, start_pos);
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::find_last_of_insensitive(
            const_pointer str, difference_type start_pos) const noexcept {
        return this->find_last_of_auxiliary<false>(str, start_pos);
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::find_first_not_of(
            value_type ch, difference_type start_pos) const noexcept {
        return this->find_first_not_of_auxiliary(ch, start_pos);
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::find_first_not_of(
            const vector_char &str, difference_type start_pos) const noexcept {
        return this->find_first_not_of_auxiliary(str, start_pos);
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::find_first_not_of(
            const_pointer str, difference_type start_pos) const noexcept {
        return this->find_first_not_of_auxiliary(str, start_pos);
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::find_first_not_of_insensitive(
            value_type ch, difference_type start_pos) const noexcept {
        return this->find_first_not_of_auxiliary<false>(ch, start_pos);
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::find_first_not_of_insensitive(
            const vector_char &str, difference_type start_pos) const noexcept {
        return this->find_first_not_of_auxiliary<false>(str, start_pos);
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::find_first_not_of_insensitive(
            const_pointer str, difference_type start_pos) const noexcept {
        return this->find_first_not_of_auxiliary<false>(str, start_pos);
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::find_last_not_of(
            value_type ch, difference_type start_pos) const noexcept {
        const auto result {this->find_last_of(ch, start_pos)};
        return result == const_cast<vector_char *>(this)->end() ? result : result + 1;
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::find_last_not_of(
            const vector_char &str, difference_type start_pos) const noexcept {
        const auto result {this->find_last_of(str, start_pos)};
        return result == const_cast<vector_char *>(this)->end() ?
                result : result + static_cast<difference_type>(str.size());
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::find_last_not_of(
            const_pointer str, difference_type start_pos) const noexcept {
        const auto result {this->find_last_of(str, start_pos)};
        return result == const_cast<vector_char *>(this)->end() ?
                result : result + static_cast<difference_type>(string_length(str));
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::find_last_not_of_insensitive(
            value_type ch, difference_type start_pos) const noexcept {
        const auto result {this->find_last_of_insensitive(ch, start_pos)};
        return result == const_cast<vector_char *>(this)->end() ? result : result + 1;
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::find_last_not_of_insensitive(
            const vector_char &str, difference_type start_pos) const noexcept {
        const auto result {this->find_last_of_insensitive(str, start_pos)};
        return result == const_cast<vector_char *>(this)->end() ?
               result : result + static_cast<difference_type>(str.size());
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator vector_char<T, Allocator>::find_last_not_of_insensitive(
            const_pointer str, difference_type start_pos) const noexcept {
        const auto result {this->find_last_of_insensitive(str, start_pos)};
        return result == const_cast<vector_char *>(this)->end() ?
               result : result + static_cast<difference_type>(string_length(str));
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator
    vector_char<T, Allocator>::remove(difference_type pos, size_type size) noexcept {
        return this->erase(pos, size);
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator
    vector_char<T, Allocator>::remove(value_type ch) noexcept {
        return this->remove_auxiliary(ch);
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator
    vector_char<T, Allocator>::remove(const vector_char &str) noexcept {
        return this->remove_auxiliary(str);
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator
    vector_char<T, Allocator>::remove(const_pointer str) noexcept {
        return this->remove_auxiliary(str);
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator
    vector_char<T, Allocator>::remove_insensitive(value_type ch) noexcept {
        return this->remove_auxiliary<false>(ch);
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator
    vector_char<T, Allocator>::remove_insensitive(const vector_char &str) noexcept {
        return this->remove_auxiliary<false>(str);
    }
    template <typename T, typename Allocator>
    inline typename vector_char<T, Allocator>::iterator
    vector_char<T, Allocator>::remove_insensitive(const_pointer str) noexcept {
        return this->remove_auxiliary<false>(str);
    }
    template <typename Stream, typename T, typename Allocator>
    Stream &operator<<(Stream &stream, const vector_char<T, Allocator> &str)
            noexcept(has_nothrow_left_shift_operator<Stream &, T>::value) {
        if(str.c_end()) {
            const auto end {str.cend() - 1};
            for(auto it {str.cbegin()}; it not_eq end; ++it) {
                auto ch {*it};
                stream << ch;
            }
            return stream;
        }
        for(auto c : str) {
            stream << c;
        }
        return stream;
    }
}

namespace data_structure {
    template <typename T, typename Allocator = allocator<type_holder<T>>>
    class vector final : public __dsa::vector_base<T, Allocator> {
    public:
        using __dsa::vector_base<T, Allocator>::vector_base;
    };

    template <typename Allocator>
    class vector<char, Allocator> final : public __dsa::vector_char<char, Allocator> {
    public:
        using __dsa::vector_char<char, Allocator>::vector_char;
    };

    template <typename Allocator>
    class vector<unsigned char, Allocator> final : public __dsa::vector_char<unsigned char, Allocator> {
    public:
        using __dsa::vector_char<unsigned char, Allocator>::vector_char;
    };

    template <typename Allocator>
    class vector<wchar_t, Allocator> final : public __dsa::vector_char<wchar_t, Allocator> {
    public:
        using __dsa::vector_char<wchar_t, Allocator>::vector_char;
    };

    template <typename Allocator>
    class vector<char16_t, Allocator> final : public __dsa::vector_char<char16_t, Allocator> {
    public:
        using __dsa::vector_char<char16_t, Allocator>::vector_char;
    };

    template <typename Allocator>
    class vector<char32_t, Allocator> final : public __dsa::vector_char<char32_t, Allocator> {
    public:
        using __dsa::vector_char<char32_t, Allocator>::vector_char;
    };

    template <typename Allocator>
    class vector<char8_t, Allocator> final : public __dsa::vector_char<char8_t, Allocator> {
    public:
        using __dsa::vector_char<char8_t, Allocator>::vector_char;
    };
}

#endif //DATA_STRUCTURE_VECTOR_HPP