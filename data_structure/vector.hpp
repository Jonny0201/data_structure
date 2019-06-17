/*
    * Copyright © [2019] [Jonny Charlotte]
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
#include "__config.hpp"

namespace data_structure {
    template <bool>
    class __vector_common {};
    extern template class __vector_common<true>;

    template <typename T, typename Allocator = allocator<type_holder<T>>>
    class vector_base : protected __vector_common<true> {
    public:
        using allocator_type = Allocator;
        using size_type = typename allocator_traits<allocator_type>::size_type;
        using difference_type = typename allocator_traits<allocator_type>::difference_type;
        using value_type = T;
        using reference = typename allocator_traits<allocator_type>::reference;
        using const_reference = typename allocator_traits<allocator_type>::const_reference;
        using rvalue_reference = typename allocator_traits<allocator_type>::rvalue_reference;
        using pointer = typename allocator_traits<allocator_type>::pointer;
        using const_pointer = typename allocator_traits<allocator_type>::const_pointer;
        using iterator = __wrap_iterator<pointer>;
        using const_iterator = __wrap_iterator<const_pointer>;
        using reverse_iterator = data_structure::reverse_iterator<iterator>;
        using const_reverse_iterator = data_structure::reverse_iterator<const_iterator>;
    private:
        using alloc_traits = allocator_traits<allocator_type>;
        static_assert(is_same<value_type, typename alloc_traits::value_type>::value,
                "The Allocator::value_type must be the same as template argument T!");
    protected:
        pointer first;
        pointer last;
        pointer cursor;
    private:
        constexpr static size_type alloc_size_ctor(size_type) noexcept;
#ifdef _DATA_STRUCTURE_HAS_CONSTEVAL
        consteval
#else
        constexpr
#endif
        static size_type default_size() noexcept;
        static void handle_exception_from_alloc(pointer, pointer) noexcept;
        static void destroy_from_insert_or_erase(pointer, pointer) noexcept;
    private:
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
        vector_base(std::initializer_list<value_type>);
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
        vector_base &operator=(std::initializer_list<value_type>);
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
        void assign(std::initializer_list<value_type>);
        iterator begin() noexcept;
        const_iterator begin() const noexcept;
        iterator end() noexcept;
        const_iterator end() const noexcept;
        reverse_iterator rbegin() noexcept;
        const_reverse_iterator rbegin() const noexcept;
        reverse_iterator rend() noexcept;
        const_reverse_iterator rend() const noexcept;
        const_iterator cbegin() const noexcept;
        const_iterator cend() const noexcept;
        const_reverse_iterator crbegin() const noexcept;
        const_reverse_iterator crend() const noexcept;
        size_type size() const noexcept;
        size_type capacity() const noexcept;
        bool empty() const noexcept;
#ifdef _DATA_STRUCTURE_HAS_CONSTEVAL
        consteval
#else
        constexpr
#endif
        size_type max_size() const noexcept;
        size_type remain() const noexcept;
        void reserve(size_type);
        void shrink_to_fit();
        reference at(difference_type) noexcept(has_nothrow_dereference_operator<pointer>::value);
        const_reference at(difference_type) const noexcept(has_nothrow_dereference_operator<pointer>::value);
        reference front() noexcept(has_nothrow_dereference_operator<pointer>::value);
        const_reference front() const noexcept(has_nothrow_dereference_operator<pointer>::value);
        reference back() noexcept(has_nothrow_dereference_operator<pointer>::value);
        const_reference back() const noexcept(has_nothrow_dereference_operator<pointer>::value);
        pointer data() noexcept;
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
        iterator insert(const_iterator, std::initializer_list<value_type>);
        iterator insert(difference_type, std::initializer_list<value_type>);
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
        iterator erase(difference_type, size_type = 1)
                noexcept((is_nothrow_move_assignable<value_type>::value or
                        is_nothrow_copy_assignable<value_type>::value) and
                        is_nothrow_destructible<value_type>::value);
        iterator erase(const_iterator, size_type = 1)
                noexcept((is_nothrow_move_assignable<value_type>::value or
                         is_nothrow_copy_assignable<value_type>::value) and
                         is_nothrow_destructible<value_type>::value);
        iterator erase(const_iterator, const_iterator)
                noexcept((is_nothrow_move_assignable<value_type>::value or
                         is_nothrow_copy_assignable<value_type>::value) and
                         is_nothrow_destructible<value_type>::value);
    };
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    void swap(vector_base<T, AllocatorLHS> &, vector_base<T, AllocatorRHS> &) noexcept;
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    bool operator==(const vector_base<T, AllocatorLHS> &, const vector_base<T, AllocatorRHS> &)
            noexcept(has_nothrow_equal_to_operator<T>::value);
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    bool operator!=(const vector_base<T, AllocatorLHS> &, const vector_base<T, AllocatorRHS> &)
            noexcept(has_nothrow_equal_to_operator<T>::value);
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    bool operator<(const vector_base<T, AllocatorLHS> &, const vector_base<T, AllocatorRHS> &)
            noexcept(has_nothrow_less_operator<T>::value);
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    bool operator<=(const vector_base<T, AllocatorLHS> &, const vector_base<T, AllocatorRHS> &)
            noexcept(has_nothrow_less_operator<T>::value and has_nothrow_equal_to_operator<T>::value);
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    bool operator>(const vector_base<T, AllocatorLHS> &, const vector_base<T, AllocatorRHS> &)
            noexcept(has_nothrow_less_operator<T>::value and has_nothrow_equal_to_operator<T>::value);
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    bool operator>=(const vector_base<T, AllocatorLHS> &, const vector_base<T, AllocatorRHS> &)
            noexcept(has_nothrow_less_operator<T>::value);
}

namespace data_structure {
    /* private function */
    template <typename T, typename Allocator>
    constexpr inline typename vector_base<T, Allocator>::size_type
    vector_base<T, Allocator>::alloc_size_ctor(size_type size) noexcept {
        return size > 5 ? size + size / 5 : size * 2;
    }
    template <typename T, typename Allocator>
#ifdef _DATA_STRUCTURE_HAS_CONSTEVAL
    consteval
#else
    constexpr
#endif
    inline typename vector_base<T, Allocator>::size_type
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
            const auto capacity {this->capacity() * 2};
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
                alloc_traits::construct(new_cursor++, move(*cursor++));
            }else {
                try {
                    alloc_traits::construct(new_cursor, move(*cursor++));
                    ++new_cursor;
                }catch(...) {
                    //strong guarantee
                    this->handle_exception_from_alloc(new_first, new_cursor);
                    throw;
                }
            }
        }
        this->deallocate();
        this->first = move(new_first);
        this->cursor = move(new_cursor);
        this->last = this->first + move(size);
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
    inline vector_base<T, Allocator>::vector_base(std::initializer_list<value_type> list) :
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
        this->assign(rhs.cbegin(), rhs.cend());
        return *this;
    }
    template <typename T, typename Allocator>
    inline vector_base<T, Allocator> &vector_base<T, Allocator>::operator=(vector_base &&rhs) noexcept {
        if(this == &rhs) {
            return *this;
        }
        this->~vector_base();
        this->first = move(rhs.first);
        this->last = move(rhs.last);
        this->cursor = move(rhs.cursor);
        rhs.first = nullptr;
        return *this;
    }
    template <typename T, typename Allocator>
    inline vector_base<T, Allocator> &
    vector_base<T, Allocator>::operator=(std::initializer_list<value_type> list) {
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
        this->first = move(rhs.first);
        this->last = move(rhs.last);
        this->cursor = move(rhs.cursor);
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
                    this->cursor = move(cursor);
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
            alloc_traits::construct(this->cursor, move(*begin++));
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
        const size_type new_size {distance(begin, end)};
        if(new_size <= this->capacity()) {
            auto cursor {this->first};
            if(new_size <= this->size()) {
                while(begin not_eq end) {
                    *cursor++ = *begin++;
                }
                if(cursor not_eq this->cursor) {
                    alloc_traits::destroy(cursor, this->cursor);
                    this->cursor = move(cursor);
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
    inline void vector_base<T, Allocator>::assign(std::initializer_list<value_type> list) {
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
#ifdef _DATA_STRUCTURE_HAS_CONSTEVAL
    consteval
#else
    constexpr
#endif
    inline typename vector_base<T, Allocator>::size_type
    vector_base<T, Allocator>::max_size() const noexcept {
        return std::numeric_limits<size_type>::max() / sizeof(value_type);
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::size_type
    vector_base<T, Allocator>::remain() const noexcept {
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
        alloc_traits::construct(this->cursor, forward<rvalue_reference>(value));
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
                    alloc_traits::construct(new_cursor++, move(*cursor++));
                }else {
                    try {
                        alloc_traits::construct(new_cursor, move(*cursor++));
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
                        this->first = move(new_first);
                        this->cursor = move(new_cursor);
                        this->last = move(new_last);
                        throw;
                    }
                }
            }
        }else {
            while(size--) {
                if constexpr(is_nothrow_copy_constructible<value_type>::value or
                             is_nothrow_move_constructible<value_type>::value) {
                    alloc_traits::construct(new_cursor++, move(*cursor++));
                }else {
                    try {
                        alloc_traits::construct(new_cursor, move(*cursor++));
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
        this->first = move(new_first);
        this->cursor = move(new_cursor);
        this->last = move(new_last);
    }
    template <typename T, typename Allocator>
    inline void vector_base<T, Allocator>::swap(vector_base &rhs) noexcept {
        swap(this->first, rhs.first);
        swap(this->cursor, rhs.cursor);
        swap(this->last, rhs.last);
    }
    template <typename T, typename Allocator>
    template <typename AllocatorRHS>
    inline void vector_base<T, Allocator>::swap(vector_base<value_type, AllocatorRHS> &rhs) noexcept {
        swap(this->first, rhs.first);
        swap(this->cursor, rhs.cursor);
        swap(this->last, rhs.last);
    }
    template <typename T, typename Allocator>
    typename vector_base<T, Allocator>::iterator
    vector_base<T, Allocator>::insert(difference_type pos, const_reference value, size_type size) {
        if(not size) {
            return iterator(this->cursor);
        }
        const auto old_size {this->size()};
        if(size > this->remain()) {
            this->reallocate(size);
        }
        if(pos == old_size) {
            const auto return_pointer {this->cursor};
            while(size--) {
                this->push_back(value);
            }
            return iterator(return_pointer);
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
            this->push_back(forward<rvalue_reference>(value));
            return iterator(this->cursor - 1);
        }else if(pos > this->size()) {
            return iterator(this->cursor);
        }
        if constexpr(is_move_constructible<value_type>::value and
                not is_nothrow_move_constructible<value_type>::value) {
            try {
                alloc_traits::construct(this->cursor, move(*(this->cursor -1)));
            }catch(...) {
                [&]() mutable noexcept -> void {
                    alloc_traits::destroy(--this->cursor);
                }();
                throw;
            }
        }else {
            alloc_traits::construct(this->cursor, move(*this->cursor - 1));
        }
        auto move_cursor {this->cursor++};
        const auto move_size {this->size() - pos};
        while(--move_size) {
            if constexpr(is_nothrow_move_assignable<value_type>::value or
                    is_nothrow_copy_assignable<value_type>::value) {
                *move_cursor = move(*(move_cursor - 1));
                --move_cursor;
            }else {
                try {
                    *move_cursor = move(*(move_cursor - 1));
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
            *move_cursor = forward<rvalue_reference>(value);
        }else {
            try {
                *move_cursor = forward<rvalue_reference>(value);
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
        return this->insert(pos - const_iterator(this->first), forward<rvalue_reference>(value));
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::iterator
    vector_base<T, Allocator>::insert(difference_type pos, std::initializer_list<value_type> list) {
        return this->insert(pos, list.begin(), list.end());
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::iterator
    vector_base<T, Allocator>::insert(const_iterator pos, std::initializer_list<value_type> list) {
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
        size_type size {distance(begin, end)};
        if(not size) {
            return iterator(this->cursor);
        }
        const auto old_size {this->size()};
        if(size > this->remain()) {
            this->reallocate(size);
        }
        if(pos == old_size) {
            const auto return_pointer {this->cursor};
            while(size--) {
                this->push_back(*begin++);
            }
            return iterator(return_pointer);
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
                alloc_traits::construct(construct_cursor--, move(*move_cursor--));
            }else {
                try {
                    alloc_traits::construct(construct_cursor, move(*move_cursor--));
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
        this->push_back(value_type(forward<Args>(args)...));
    }
    template <typename T, typename Allocator>
    template <typename ...Args>
    inline typename vector_base<T, Allocator>::iterator
    vector_base<T, Allocator>::emplace(const_iterator pos, Args &&...args) {
        return this->insert(pos - const_iterator(this->first), value_type(forward<Args>(args)...));
    }
    template <typename T, typename Allocator>
    template <typename ...Args>
    inline typename vector_base<T, Allocator>::iterator
    vector_base<T, Allocator>::emplace(difference_type pos, Args &&...args) {
        return this->insert(pos, value_type(forward<Args>(args)...));
    }
    template <typename T, typename Allocator>
    typename vector_base<T, Allocator>::iterator
    vector_base<T, Allocator>::erase(difference_type pos, size_type size)
            noexcept((is_nothrow_move_assignable<value_type>::value or
                    is_nothrow_copy_assignable<value_type>::value) and
                    is_nothrow_destructible<value_type>::value) {
        auto move_cursor {this->first + pos};
        auto forward_cursor {move_cursor + size};
        while(forward_cursor not_eq this->cursor) {
            if constexpr(is_nothrow_copy_assignable<value_type>::value and
                    is_nothrow_move_assignable<value_type>::value) {
                *move_cursor++ = move(*forward_cursor++);
            }else {
                try {
                    *move_cursor++ = move(*forward_cursor++);
                }catch(...) {
                    this->destroy_from_insert_or_erase(move_cursor, this->cursor);
                    this->cursor = move_cursor;
                    throw;
                }
            }
        }
        this->destroy_from_insert_or_erase(move_cursor, this->cursor);
        this->cursor = move(move_cursor);
        return iterator(this->first + pos);
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::iterator
    vector_base<T, Allocator>::erase(const_iterator pos, size_type size)
            noexcept((is_nothrow_move_assignable<value_type>::value or
                     is_nothrow_copy_assignable<value_type>::value) and
                     is_nothrow_destructible<value_type>::value) {
        return this->erase(pos - const_iterator(this->first), size);
    }
    template <typename T, typename Allocator>
    inline typename vector_base<T, Allocator>::iterator
    vector_base<T, Allocator>::erase(const_iterator begin, const_iterator end)
            noexcept((is_nothrow_move_assignable<value_type>::value or
                     is_nothrow_copy_assignable<value_type>::value) and
                     is_nothrow_destructible<value_type>::value) {
        return this->erase(begin - const_iterator(this->first), end - begin);
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
        auto rhs_cursor {rhs.cbegin};
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
        return lhs < rhs or lhs == rhs;
    }
    template <typename T, typename AllocatorLHS, typename AllocatorRHS>
    inline
    bool operator>(const vector_base<T, AllocatorLHS> &lhs, const vector_base<T, AllocatorRHS> &rhs)
            noexcept(has_nothrow_less_operator<T>::value and has_nothrow_equal_to_operator<T>::value) {
        return not(lhs <= rhs);
    }
    template <typename T, typename AllocatorLHS, typename AllocatorRHS>
    inline
    bool operator>=(const vector_base<T, AllocatorLHS> &lhs, const vector_base<T, AllocatorRHS> &rhs)
            noexcept(has_nothrow_less_operator<T>::value) {
        return not(lhs < rhs);
    }
}

#endif //DATA_STRUCTURE_VECTOR_HPP
