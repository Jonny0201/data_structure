/*
    * Copyright © [2019 - 2020] [Jonny Charlotte]
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

#include "allocator.hpp"
#include "iterator.hpp"
#include "algorithm.hpp"

namespace data_structure {
    template <typename T, typename Allocator = allocator<type_holder<T>>>
    class deque {
    private:
        using map_pointer = add_pointer_t<add_pointer_t<T>>;
    private:
        constexpr static auto buffer_size {64};
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
        using iterator = __dsa::deque_iterator<value_type, map_pointer, deque::buffer_size, false>;
        using const_iterator = __dsa::deque_iterator<value_type, map_pointer, deque::buffer_size, true>;
        using reverse_iterator = reverse_iterator<iterator>;
        using const_reverse_iterator = ds::reverse_iterator<const_iterator>;
    private:
        using alloc_traits = allocator_traits<allocator_type>;
        static_assert(is_same_v<T, allocator_traits_t(allocator_type, value_type)>,
                "The deque holds different value_types");
    private:
        size_type map_size;
        map_pointer map;
        iterator first;
        iterator last;
    private:
        static pointer allocate(size_type = deque::buffer_size);
        constexpr static size_type map_size_calculator(size_type) noexcept;
        static map_pointer map_allocate(size_type);
        static void destroy(iterator, iterator);
        static iterator copy_backward_if_trivial_auxiliary(iterator, iterator, iterator) noexcept;
        static iterator copy_backward_if_trivial(iterator, iterator, iterator) noexcept;
        template <bool = true>
        static void copy_assignment(iterator, iterator, iterator, iterator) noexcept;
        static iterator construct_in_empty_position(iterator, iterator, iterator)
                noexcept(is_nothrow_move_constructible_v<value_type>);
        template <bool = true>
        static void move_to(iterator, iterator, iterator)
                noexcept(is_nothrow_move_assignable_v<value_type> or is_nothrow_copy_assignable_v<value_type>);
    private:
        map_pointer create_map() const;
        void construct_if_trivial() noexcept;
        void construct() noexcept(is_nothrow_default_constructible_v<value_type>);
        void construct(const_reference) noexcept(is_nothrow_copy_constructible_v<value_type>);
        template <typename ForwardIterator>
        void construct(ForwardIterator, ForwardIterator) noexcept(is_nothrow_constructible_v<
                value_type, iterator_traits_t(ForwardIterator, reference)>);
        void handle_exception_when_constructing(iterator, iterator) noexcept;
        void expand_front(size_type);
        void expand_back(size_type);
        iterator map_last() noexcept;
        iterator map_first() noexcept;
        size_type spare_back() noexcept;
        size_type spare_front() noexcept;
        template <bool = true>
        void check_and_expand(size_type);
        void construct_front(const_reference, size_type) noexcept(is_nothrow_copy_constructible_v<value_type>);
        template <typename Iterator, typename = enable_if_t<is_input_iterator_v<Iterator>>>
        void construct_front(Iterator, Iterator)
                noexcept(is_nothrow_constructible_v<value_type, iterator_traits_t(Iterator, reference)>);
        void uninitialized_copy_to_front(iterator, iterator)
                noexcept(is_nothrow_move_constructible_v<value_type> or
                        is_nothrow_copy_constructible_v<value_type>);
    public:
        deque();
        explicit deque(size_type);
        deque(size_type, const_reference);
        template <typename InputIterator>
        deque(enable_if_t<is_input_iterator_v<InputIterator> and
                not is_forward_iterator_v<InputIterator>, InputIterator>, InputIterator);
        template <typename ForwardIterator>
        deque(enable_if_t<is_forward_iterator_v<ForwardIterator>, ForwardIterator>, ForwardIterator);
        deque(initializer_list<value_type>);
        deque(const deque &);
        deque(deque &&) noexcept;
        template <typename AllocatorRHS>
        explicit deque(const deque<value_type, AllocatorRHS> &);
        template <typename AllocatorRHS>
        explicit deque(deque<value_type, AllocatorRHS> &&) noexcept;
        ~deque() noexcept;
    public:
        deque &operator=(const deque &);
        deque &operator=(deque &&) noexcept;
        template <typename AllocatorRHS>
        deque &operator=(const deque<value_type, AllocatorRHS> &);
        template <typename AllocatorRHS>
        deque &operator=(deque<value_type, AllocatorRHS> &&) noexcept;
        deque &operator=(initializer_list<value_type>);
        [[nodiscard]]
        reference operator[](difference_type) noexcept;
        [[nodiscard]]
        const_reference operator[](difference_type) const noexcept;
    public:
        void assign(size_type, const_reference = {});
        template <typename InputIterator>
        void assign(enable_if_t<is_input_iterator_v<InputIterator>, InputIterator>, InputIterator);
        void assign(initializer_list<value_type>);
        [[nodiscard]]
        reference at(size_type) noexcept;
        [[nodiscard]]
        const_reference at(size_type) const noexcept;
        [[nodiscard]]
        reference front() noexcept;
        [[nodiscard]]
        const_reference front() const noexcept;
        [[nodiscard]]
        reference back() noexcept;
        [[nodiscard]]
        const_reference back() const noexcept;
        [[nodiscard]]
        iterator begin() noexcept;
        [[nodiscard]]
        const_iterator begin() const noexcept;
        [[nodiscard]]
        iterator end() noexcept;
        [[nodiscard]]
        const_iterator end() const noexcept;
        [[nodiscard]]
        const_iterator cbegin() const noexcept;
        [[nodiscard]]
        const_iterator cend() const noexcept;
        [[nodiscard]]
        reverse_iterator rbegin() noexcept;
        [[nodiscard]]
        const_reverse_iterator rbegin() const noexcept;
        [[nodiscard]]
        reverse_iterator rend() noexcept;
        [[nodiscard]]
        const_reverse_iterator rend() const noexcept;
        [[nodiscard]]
        const_reverse_iterator crbegin() const noexcept;
        [[nodiscard]]
        const_reverse_iterator crend() const noexcept;
        [[nodiscard]]
        bool empty() const noexcept;
        [[nodiscard]]
        size_type size() const noexcept;
        [[nodiscard]]
        static consteval size_type max_size() noexcept;
        void swap(deque &) noexcept;
        template <typename AllocatorRHS>
        void swap(deque<value_type, AllocatorRHS> &) noexcept;
        void clear() noexcept;
        void shrink_to_fit();
        void resize(size_type, const_reference = {});
        iterator insert(difference_type, const_reference, size_type = 1);
        iterator insert(const_iterator, const_reference, size_type = 1);
        iterator insert(difference_type, rvalue_reference);
        iterator insert(const_iterator, rvalue_reference);
        template <typename InputIterator>
        iterator insert(difference_type, enable_if_t<is_input_iterator_v<InputIterator> and
                not is_forward_iterator_v<InputIterator>, InputIterator>, InputIterator);
        template <typename InputIterator>
        iterator insert(const_iterator, enable_if_t<is_input_iterator_v<InputIterator> and
                not is_forward_iterator_v<InputIterator>, InputIterator>, InputIterator);
        template <typename ForwardIterator>
        iterator insert(difference_type,
                enable_if_t<is_forward_iterator_v<ForwardIterator>, ForwardIterator>, ForwardIterator);
        template <typename ForwardIterator>
        iterator insert(const_iterator,
                enable_if_t<is_forward_iterator_v<ForwardIterator>, ForwardIterator>, ForwardIterator);
        iterator insert(difference_type, initializer_list<value_type>);
        iterator insert(const_iterator, initializer_list<value_type>);
        iterator erase(difference_type, size_type = 1) noexcept(is_nothrow_copy_assignable_v<value_type>);
        iterator erase(const_iterator, size_type) noexcept(is_nothrow_copy_assignable_v<value_type>);
        iterator erase(const_iterator, const_iterator) noexcept(is_nothrow_copy_assignable_v<value_type>);
        iterator erase(const_iterator) noexcept(is_nothrow_copy_assignable_v<value_type>);
        template <typename ...Args>
        iterator emplace(difference_type, Args &&...);
        template <typename ...Args>
        iterator emplace(const_iterator, Args &&...);
        void push_back(const_reference);
        void push_back(rvalue_reference);
        void push_front(const_reference);
        void push_front(rvalue_reference);
        template <typename ...Args>
        void emplace_front(Args &&...);
        template <typename ...Args>
        void emplace_back(Args &&...);
        void pop_back() noexcept;
        void pop_front() noexcept;
    };

    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    void swap(deque<T, AllocatorLHS> &, deque<T, AllocatorRHS> &) noexcept;
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    bool operator==(const deque<T, AllocatorLHS> &, const deque<T, AllocatorRHS> &)
            noexcept(has_nothrow_equal_to_operator_v<T>);
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    bool operator!=(const deque<T, AllocatorLHS> &, const deque<T, AllocatorRHS> &)
            noexcept(has_nothrow_equal_to_operator_v<T>);
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    bool operator<(const deque<T, AllocatorLHS> &, const deque<T, AllocatorRHS> &)
            noexcept(has_nothrow_less_operator_v<T>);
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    bool operator<=(const deque<T, AllocatorLHS> &, const deque<T, AllocatorRHS> &)
            noexcept(has_nothrow_less_operator_v<T>);
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    bool operator>(const deque<T, AllocatorLHS> &, const deque<T, AllocatorRHS> &)
            noexcept(has_nothrow_less_operator_v<T>);
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    bool operator>=(const deque<T, AllocatorLHS> &, const deque<T, AllocatorRHS> &)
            noexcept(has_nothrow_less_operator_v<T>);
}

namespace data_structure {
    /* private functions */
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::pointer deque<T, Allocator>::allocate(size_type size) {
        return reinterpret_cast<pointer>(alloc_traits::operator new(size * sizeof(value_type)));
    }
    template <typename T, typename Allocator>
    constexpr inline typename deque<T, Allocator>::size_type
    deque<T, Allocator>::map_size_calculator(size_type size) noexcept {
        return size / deque::buffer_size + 1;
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::map_pointer deque<T, Allocator>::map_allocate(size_type size) {
        return reinterpret_cast<map_pointer>(alloc_traits::operator new(size * sizeof(pointer)));
    }
    template <typename T, typename Allocator>
    inline void deque<T, Allocator>::destroy(iterator begin, iterator end) {
        if constexpr(not is_trivially_destructible_v<value_type>) {
            while(begin not_eq end) {
                alloc_traits::destroy(begin.iter);
            }
        }
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::iterator deque<T, Allocator>::copy_backward_if_trivial_auxiliary(
            iterator begin, iterator end, iterator result) noexcept {
        const auto spare {result.surplus()};
        const auto distance {end.iter - begin.iter};
        if(distance <= spare) {
            result = {ds::copy(begin.iter, end.iter, result.iter), result.map};
            if(distance == spare) {
                result.next();
            }
        }else {
            ds::memory_copy(begin.iter, result.iter, static_cast<size_t>(spare) * sizeof(value_type));
            result.next();
            result = {ds::copy(begin.iter + spare, end.iter, result.iter), result.map};
        }
        return result;
    }
    template <typename T, typename Allocator>
    typename deque<T, Allocator>::iterator deque<T, Allocator>::copy_backward_if_trivial(
            iterator begin, iterator end, iterator result) noexcept {
        if(begin.map == end.map) {
            return deque::copy_backward_if_trivial_auxiliary(begin, end, result);
        }
        do {
            result = deque::copy_backward_if_trivial_auxiliary(
                    begin, iterator(begin.after_tail(), begin.map), result);
            begin.next();
        }while(begin.map not_eq end.map);
        if(begin.iter not_eq end.iter) {
            result = deque::copy_backward_if_trivial_auxiliary(begin, end, result);
        }
        return result;
    }
    template <typename T, typename Allocator>
    template <bool Back>
    void deque<T, Allocator>::copy_assignment(iterator begin, iterator end,
            iterator result, iterator last) noexcept {
        if(begin.map == end.map) {
            if constexpr(Back) {
                if(last.map == result.map) {
                    ds::copy<true>(begin.iter, end.iter, result.iter);
                }else {
                    do {
                        const auto first {last.first()};
                        const auto spare {last.iter - first};
                        ds::copy(begin.iter, begin.iter + spare, first);
                        begin.iter += spare;
                        last.previous();
                    }while(begin not_eq end);
                }
            }else {
                ds::copy(begin.iter, end.iter, result.iter);
            }
        }else {
            deque::copy_backward_if_trivial(begin, end, last - (end - begin));
        }
    }
    template <typename T, typename Allocator>
    typename deque<T, Allocator>::iterator
    deque<T, Allocator>::construct_in_empty_position(iterator begin, iterator end, iterator result)
            noexcept(is_nothrow_move_constructible_v<value_type>) {
        while(begin not_eq end) {
            alloc_traits::construct(result.iter++,
                    ds::move_if<is_nothrow_move_constructible_v<value_type>>(*begin++));
        }
        return result;
    }
    template <typename T, typename Allocator>
    template <bool Back>
    void deque<T, Allocator>::move_to(iterator begin, iterator end, iterator result)
            noexcept(is_nothrow_move_assignable_v<value_type> or is_nothrow_copy_assignable_v<value_type>) {
        while(begin not_eq end) {
            if constexpr(Back) {
                *(--result) = ds::move_if<is_nothrow_move_assignable_v<value_type>>(*begin++);
            }else {
                *result++ = ds::move_if<is_nothrow_move_assignable_v<value_type>>(*begin++);
            }
        }
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::map_pointer deque<T, Allocator>::create_map() const {
        auto map {this->map_allocate(this->map_size)};
        for(auto i {0}; i < this->map_size; ++i) {
            map[i] = this->allocate();
        }
        return map;
    }
    template <typename T, typename Allocator>
    void deque<T, Allocator>::construct_if_trivial() noexcept {
        auto cursor {this->first};
        for(; cursor.map not_eq this->last.map; cursor.next()) {
            ds::memory_initialize(cursor.iter, this->buffer_size * sizeof(value_type));
        }
        if(const auto distance {this->last - cursor}; distance > 0) {
            ds::memory_initialize(cursor.iter, static_cast<size_t>(distance) * sizeof(value_type));
        }
    }
    template <typename T, typename Allocator>
    void deque<T, Allocator>::construct() noexcept(is_nothrow_default_constructible_v<value_type>) {
        for(auto cursor {this->first}; cursor not_eq this->last;) {
            if constexpr(is_nothrow_default_constructible_v<value_type>) {
                alloc_traits::construct(cursor++.iter);
            }else {
                try {
                    alloc_traits::construct(cursor.iter);
                    ++cursor;
                }catch(...) {
                    this->handle_exception_when_constructing(this->first, cursor);
                    throw;
                }
            }
        }
    }
    template <typename T, typename Allocator>
    void deque<T, Allocator>::construct(const_reference value)
            noexcept(is_nothrow_copy_constructible_v<value_type>) {
        for(auto cursor {this->first}; cursor not_eq this->last;) {
            if constexpr(is_nothrow_default_constructible_v<value_type>) {
                alloc_traits::construct(cursor++.iter, value);
            }else {
                try {
                    alloc_traits::construct(cursor.iter, value);
                    ++cursor;
                }catch(...) {
                    this->handle_exception_when_constructing(this->first, cursor);
                    throw;
                }
            }
        }
    }
    template <typename T, typename Allocator>
    template <typename ForwardIterator>
    void deque<T, Allocator>::construct(ForwardIterator begin, ForwardIterator end)
            noexcept(is_nothrow_constructible_v<value_type, iterator_traits_t(ForwardIterator, reference)>) {
        using ref = iterator_traits_t(ForwardIterator, reference);
        for(auto cursor {this->first}; begin not_eq end; ++cursor) {
            if constexpr(is_nothrow_constructible_v<value_type, ref>) {
                alloc_traits::construct(cursor.iter, *begin++);
            }else {
                try {
                    alloc_traits::construct(cursor.iter, *begin++);
                }catch(...) {
                    this->handle_exception_when_constructing(this->first, cursor);
                    throw;
                }
            }
        }
    }
    template <typename T, typename Allocator>
    inline void deque<T, Allocator>::handle_exception_when_constructing(iterator begin, iterator end) noexcept {
        if constexpr(not is_trivially_destructible_v<value_type>) {
            while(begin.map not_eq end.map) {
                alloc_traits::destroy(begin.iter, begin.map + static_cast<difference_type>(this->buffer_size));
                begin.next();
            }
            if(begin.iter not_eq end.iter) {
                alloc_traits::destroy(begin.iter, end.iter);
            }
        }
        for(auto i {0}; i < this->map_size; ++i) {
            alloc_traits::operator delete(this->map[i]);
        }
        alloc_traits::operator delete(this->map);
    }
    template <typename T, typename Allocator>
    void deque<T, Allocator>::expand_front(size_type size) {
        const auto expanding {this->map_size_calculator(size)};
        this->map_size += expanding;
        const auto offset {this->first - iterator(*this->map, this->map)};
        auto map {this->map_allocate(this->map_size)};
        for(size_type i {expanding}, j {0}; i < this->map_size; ++i, static_cast<void>(++j)) {
            map[i] = this->map[j];
        }
        for(auto i {0}; i < expanding; ++i) {
            map[i] = this->allocate();
        }
        auto first {iterator(map[expanding], map + static_cast<ptrdiff_t>(expanding)) + offset};
        this->last = first + (this->last - this->first);
        this->first = first;
        alloc_traits::operator delete(this->map);
        this->map = map;
    }
    template <typename T, typename Allocator>
    void deque<T, Allocator>::expand_back(size_type size) {
        const auto expanding {this->map_size_calculator(size)};
        const auto total_size {this->map_size + expanding};
        const auto offset {this->first - iterator(*this->map, this->map)};
        auto map {this->map_allocate(total_size)};
        for(auto i {this->map_size}; i < total_size; ++i) {
            map[i] = this->allocate();
        }
        for(auto i {0}; i < this->map_size; ++i) {
            map[i] = this->map[i];
        }
        auto first {iterator(*map, map) + offset};
        this->last = first + (this->last - this->first);
        this->first = first;
        alloc_traits::operator delete(this->map);
        this->map = map;
        this->map_size = total_size;
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::iterator deque<T, Allocator>::map_last() noexcept {
        const auto last_map_node {this->map + static_cast<ptrdiff_t>(this->map_size - 1)};
        return iterator(*last_map_node + static_cast<difference_type>(this->buffer_size - 1), last_map_node);
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::iterator deque<T, Allocator>::map_first() noexcept {
        return iterator(*this->map, this->map);
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::size_type deque<T, Allocator>::spare_back() noexcept {
        return this->map_last() - this->last;
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::size_type deque<T, Allocator>::spare_front() noexcept {
        return this->first - this->map_first();
    }
    template <typename T, typename Allocator>
    template <bool Back>
    inline void deque<T, Allocator>::check_and_expand(size_type size) {
        if constexpr(Back) {
            const auto spare {this->spare_back()};
            if(size >= spare) {
                if(size not_eq spare) {
                    this->expand_back(size - spare);
                }else {
                    this->expand_back(size - spare + 1);
                }
            }
        }else {
            const auto spare {this->spare_front()};
            if(size > spare) {
                this->expand_front(size - spare);
            }
        }
    }
    template <typename T, typename Allocator>
    inline void deque<T, Allocator>::construct_front(const_reference value, size_type size)
            noexcept(is_nothrow_copy_constructible_v<value_type>) {
        do {
            alloc_traits::construct((this->first - 1).iter, value);
            --this->first;
        }while(--size > 0);
    }
    template <typename T, typename Allocator>
    template <typename Iterator, typename>
    inline void deque<T, Allocator>::construct_front(Iterator begin, Iterator end)
            noexcept(is_nothrow_constructible_v<value_type, iterator_traits_t(Iterator, reference)>) {
        do {
            alloc_traits::construct((this->first - 1).iter, *(--end));
            --this->first;
        }while(begin not_eq end);
    }
    template <typename T, typename Allocator>
    inline void deque<T, Allocator>::uninitialized_copy_to_front(iterator begin, iterator end) noexcept(
            is_nothrow_move_constructible_v<value_type> or is_nothrow_copy_constructible_v<value_type>) {
        while(begin not_eq end) {
            alloc_traits::construct((this->first - 1).iter,
                    ds::move_if<is_nothrow_move_assignable_v<value_type>>(*(--end)));
            --this->first;
        }
    }

    /* public functions */
    template <typename T, typename Allocator>
    inline deque<T, Allocator>::deque() : map_size {1}, map {this->create_map()},
            first {*this->map, this->map}, last {this->first + 1} {}
    template <typename T, typename Allocator>
    inline deque<T, Allocator>::deque(size_type size) : map_size {this->map_size_calculator(size)},
            map {this->create_map()}, first {*this->map, this->map},
            last {this->first + static_cast<difference_type>(size)} {
        if constexpr(is_trivially_constructible_v<value_type>) {
            this->construct_if_trivial();
        }else {
            this->construct();
        }
    }
    template <typename T, typename Allocator>
    inline deque<T, Allocator>::deque(size_type size, const_reference value) :
            map_size {this->map_size_calculator(size)}, map {this->create_map()},
            first {*this->map, this->map}, last {this->first + static_cast<difference_type>(size)} {
        this->construct(value);
    }
    template <typename T, typename Allocator>
    template <typename InputIterator>
    inline deque<T, Allocator>::deque(enable_if_t<is_input_iterator_v<InputIterator> and
            not is_forward_iterator_v<InputIterator>, InputIterator> begin, InputIterator end) :
            deque() {
        this->assign(begin, end);
    }
    template <typename T, typename Allocator>
    template <typename ForwardIterator>
    inline deque<T, Allocator>::deque(enable_if_t<is_forward_iterator_v<ForwardIterator>, ForwardIterator> begin,
            ForwardIterator end) : map_size {this->map_size_calculator(ds::distance(begin, end))},
            map {this->create_map()}, first {*this->map, this->map},
            last {this->first + static_cast<difference_type>(ds::distance(begin, end))} {
        this->construct(begin, end);
    }
    template <typename T, typename Allocator>
    inline deque<T, Allocator>::deque(initializer_list<value_type> init_list) :
            deque(init_list.begin(), init_list.end()) {}
    template <typename T, typename Allocator>
    inline deque<T, Allocator>::deque(const deque &rhs) : deque(rhs.cbegin(), rhs.cend()) {}
    template <typename T, typename Allocator>
    inline deque<T, Allocator>::deque(deque &&rhs) noexcept : map_size {rhs.map_size}, map {rhs.map},
            first {rhs.first}, last {rhs.last} {
        rhs.map_size = 0;
        rhs.map = nullptr;
        rhs.first = rhs.last = iterator();
    }
    template <typename T, typename Allocator>
    inline deque<T, Allocator>::~deque() noexcept {
        if(not this->empty()) {
            if constexpr(not is_trivially_destructible_v<value_type>) {
                for(auto cursor {this->first}; cursor not_eq this->last;) {
                    alloc_traits::destroy(cursor++.iter);
                }
            }
        }
        for(auto i {0}; i < this->map_size; ++i) {
            alloc_traits::operator delete(this->map[i]);
        }
        alloc_traits::operator delete(this->map);
    }
    template <typename T, typename Allocator>
    inline deque<T, Allocator> &deque<T, Allocator>::operator=(const deque &rhs) {
        if(&rhs == this) {
            return *this;
        }
        this->assign(rhs.first, rhs.last);
        return *this;
    }
    template <typename T, typename Allocator>
    inline deque<T, Allocator> &deque<T, Allocator>::operator=(deque &&rhs) noexcept {
        if(&rhs == this) {
            return *this;
        }
        this->~deque();
        this->map_size = rhs.map_size;
        this->map = rhs.map;
        this->first = rhs.first;
        this->last = rhs.last;
        rhs.map_size = 0;
        rhs.map = nullptr;
        rhs.first = rhs.last = iterator();
        return *this;
    }
    template <typename T, typename Allocator>
    template <typename AllocatorRHS>
    inline deque<T, Allocator> &deque<T, Allocator>::operator=(const deque<T, AllocatorRHS> &rhs) {
        this->assign(rhs.first, rhs.last);
        return *this;
    }
    template <typename T, typename Allocator>
    template <typename AllocatorRHS>
    inline deque<T, Allocator> &deque<T, Allocator>::operator=(deque<T, AllocatorRHS> &&rhs) noexcept {
        this->~deque();
        this->map_size = rhs.map_size;
        this->map = rhs.map;
        this->first = rhs.first;
        this->last = rhs.last;
        rhs.map_size = 0;
        rhs.map = nullptr;
        rhs.first = rhs.last = iterator();
        return *this;
    }
    template <typename T, typename Allocator>
    inline deque<T, Allocator> &deque<T, Allocator>::operator=(initializer_list<value_type> init_list) {
        this->assign(init_list.begin(), init_list.end());
        return *this;
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::reference
    deque<T, Allocator>::operator[](difference_type n) noexcept {
        return this->first[n];
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::const_reference
    deque<T, Allocator>::operator[](difference_type n) const noexcept {
        return this->first[n];
    }
    template <typename T, typename Allocator>
    void deque<T, Allocator>::assign(size_type size, const_reference value) {
        const auto holding {this->size()};
        if(size <= holding) {
            fill_n(this->first, size, value);
            this->erase(this->first + static_cast<difference_type>(size), this->last);
        }else {
            size -= holding;
            fill_n(this->first, holding, value);
            this->insert(this->cend(), value, size);
        }
    }
    template <typename T, typename Allocator>
    template <typename InputIterator>
    void deque<T, Allocator>::assign(enable_if_t<is_input_iterator_v<InputIterator>, InputIterator> begin,
            InputIterator end) {
        auto cursor {this->first};
        for(; cursor not_eq this->last and begin not_eq end;) {
            if constexpr(not is_forward_iterator_v<InputIterator>) {
                *cursor++ = ds::move(*begin++);
            }else {
                *cursor++ = *begin++;
            }
        }
        if(begin not_eq end) {
            this->insert(this->cend(), begin, end);
            return;
        }
        if(cursor not_eq this->last) {
            this->erase(cursor, this->last);
        }
    }
    template <typename T, typename Allocator>
    inline void deque<T, Allocator>::assign(initializer_list<value_type> init_list) {
        this->assign(init_list.begin(), init_list.end());
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::reference deque<T, Allocator>::at(size_type n) noexcept {
        return this->first[n];
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::const_reference deque<T, Allocator>::at(size_type n) const noexcept {
        return this->first[n];
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::reference deque<T, Allocator>::front() noexcept {
        return *this->first;
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::const_reference deque<T, Allocator>::front() const noexcept {
        return *this->first;
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::reference deque<T, Allocator>::back() noexcept {
        return *(this->last - 1);
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::const_reference deque<T, Allocator>::back() const noexcept {
        return *(this->last - 1);
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::iterator deque<T, Allocator>::begin() noexcept {
        return this->first;
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::const_iterator deque<T, Allocator>::begin() const noexcept {
        return static_cast<iterator>(this->first);
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::iterator deque<T, Allocator>::end() noexcept {
        return this->last;
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::const_iterator deque<T, Allocator>::end() const noexcept {
        return static_cast<iterator>(this->last);
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::const_iterator deque<T, Allocator>::cbegin() const noexcept {
        return static_cast<iterator>(this->first);
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::const_iterator deque<T, Allocator>::cend() const noexcept {
        return static_cast<iterator>(this->last);
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::reverse_iterator deque<T, Allocator>::rbegin() noexcept {
        return reverse_iterator(this->last - 1);
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::const_reverse_iterator deque<T, Allocator>::rbegin() const noexcept {
        return const_reverse_iterator(this->last - 1);
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::reverse_iterator deque<T, Allocator>::rend() noexcept {
        return reverse_iterator(this->first - 1);
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::const_reverse_iterator deque<T, Allocator>::rend() const noexcept {
        return const_reverse_iterator(this->first - 1);
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::const_reverse_iterator deque<T, Allocator>::crbegin() const noexcept {
        return const_reverse_iterator(this->last - 1);
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::const_reverse_iterator deque<T, Allocator>::crend() const noexcept {
        return const_reverse_iterator(this->first - 1);
    }
    template <typename T, typename Allocator>
    inline bool deque<T, Allocator>::empty() const noexcept {
        return this->first == this->last;
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::size_type deque<T, Allocator>::size() const noexcept {
        return this->last - this->first;
    }
    template <typename T, typename Allocator>
    inline consteval typename deque<T, Allocator>::size_type deque<T, Allocator>::max_size() noexcept {
        return std::numeric_limits<size_type>::max() / sizeof(value_type);
    }
    template <typename T, typename Allocator>
    inline void deque<T, Allocator>::swap(deque &rhs) noexcept {
        if(&rhs == this) {
            return;
        }
        ds::swap(this->first, rhs.first);
        ds::swap(this->last, rhs.last);
        ds::swap(this->map_size, rhs.map_size);
        ds::swap(this->map, rhs.map);
    }
    template <typename T, typename Allocator>
    template <typename AllocatorRHS>
    inline void deque<T, Allocator>::swap(deque<T, AllocatorRHS> &rhs) noexcept {
        ds::swap(this->first, rhs.first);
        ds::swap(this->last, rhs.last);
        ds::swap(this->map_size, rhs.map_size);
        ds::swap(this->map, rhs.map);
    }
    template <typename T, typename Allocator>
    void deque<T, Allocator>::clear() noexcept {
        if(this->empty()) {
            return;
        }
        if constexpr(not is_trivially_destructible_v<value_type>) {
            for(auto cursor {this->first}; cursor not_eq this->last;) {
                alloc_traits::destroy(cursor++.iter);
            }
        }
        this->last = this->first;
    }
    template <typename T, typename Allocator>
    void deque<T, Allocator>::shrink_to_fit() {
        this->map_size = this->last.map - this->first.map + 1;
        auto map {this->map_allocate(this->map_size)};
        const auto first_offset {this->first.map - *this->map};
        const auto last_offset {this->last.map - *this->map};
        for(auto i {0}; i < first_offset; ++i) {
            alloc_traits::operator delete(this->map[i]);
        }
        for(auto i {last_offset + 1}; i < this->map_size; ++i) {
            alloc_traits::operator delete(this->map[i]);
        }
        for(auto i {first_offset}, j {0}; i <= last_offset; ++i, static_cast<void>(++j)) {
            map[j] = this->map[i];
        }
        alloc_traits::operator delete(this->map);
        this->map = map;
    }
    template <typename T, typename Allocator>
    inline void deque<T, Allocator>::resize(size_type size, const_reference value) {
        const auto holding {this->size()};
        if(size < holding) {
            this->erase(this->first + static_cast<difference_type>(size), this->last);
        }else {
            this->insert(this->cend(), size - holding, value);
        }
    }
    template <typename T, typename Allocator>
    typename deque<T, Allocator>::iterator
    deque<T, Allocator>::insert(difference_type pos, const_reference value, size_type size) {
        if(size > 0) {
            if(const auto holding {this->size()}; holding / 2 <= pos) {
                this->check_and_expand(size);
                const auto position {this->first + pos};
                const auto old_last {this->last};
                if(auto backward_size {holding - pos}; size > backward_size) {
                    ds::uninitialized_fill_n<false, iterator &>(this->last, size - backward_size, value);
                    ds::uninitialized_copy<false, iterator &>(position, old_last, this->last);
                    ds::fill(position, old_last, value);
                }else {
                    const auto move_size {static_cast<difference_type>(backward_size - size)};
                    const auto stop_pos {position + move_size};
                    ds::uninitialized_copy<false, iterator &>(stop_pos, old_last, this->last);
                    this->move_to(position, stop_pos, old_last);
                    ds::fill_n(position, size, value);
                }
            }else {
                this->check_and_expand<false>(size);
                const auto position {this->first + pos}, old_first {this->first};
                if(size > pos) {
                    this->construct_front(value, size - pos);
                    this->uninitialized_copy_to_front(old_first, position);
                }else {
                    const auto stop_pos {this->first + static_cast<difference_type>(size)};
                    this->uninitialized_copy_to_front(old_first, stop_pos);
                    this->move_to<false>(stop_pos, position, old_first);
                }
                ds::fill(old_first, position, value);
            }
        }
        return this->first + pos;
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::iterator
    deque<T, Allocator>::insert(const_iterator pos, const_reference value, size_type size) {
        return this->insert(pos - this->first, value, size);
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::iterator
    deque<T, Allocator>::insert(difference_type pos, rvalue_reference value) {
        return this->emplace(pos, ds::move(value));
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::iterator
    deque<T, Allocator>::insert(const_iterator pos, rvalue_reference value) {
        return this->emplace(pos - this->first, ds::move(value));
    }
    template <typename T, typename Allocator>
    template <typename InputIterator>
    inline typename deque<T, Allocator>::iterator
    deque<T, Allocator>::insert(difference_type pos, enable_if_t<is_input_iterator_v<InputIterator> and
            not is_forward_iterator_v<InputIterator>, InputIterator> begin, InputIterator end) {
        while(begin not_eq end) {
            this->insert(pos++, ds::move(begin++));
        }
        return this->first + pos;
    }
    template <typename T, typename Allocator>
    template <typename InputIterator>
    inline typename deque<T, Allocator>::iterator
    deque<T, Allocator>::insert(const_iterator pos, enable_if_t<is_input_iterator_v<InputIterator> and
            not is_forward_iterator_v<InputIterator>, InputIterator> begin, InputIterator end) {
        return this->insert(pos - this->first, begin, end);
    }
    template <typename T, typename Allocator>
    template <typename ForwardIterator>
    typename deque<T, Allocator>::iterator
    deque<T, Allocator>::insert(difference_type pos,
            enable_if_t<is_forward_iterator_v<ForwardIterator>, ForwardIterator> begin, ForwardIterator end) {
        const auto size {ds::distance(begin, end)};
        if(size > 0) {
            if(const auto holding {this->size()}; holding / 2 <= pos) {
                this->check_and_expand(size);
                const auto position {this->first + pos};
                const auto old_last {this->last};
                if(auto backward_size {holding - pos}; size > backward_size) {
                    const auto fill_start {ds::advance(begin, backward_size)};
                    ds::uninitialized_copy<false, iterator &>(fill_start, end, this->last);
                    ds::uninitialized_copy<false, iterator &>(position, old_last, this->last);
                    ds::copy(begin, fill_start, position);
                }else {
                    const auto move_size {static_cast<difference_type>(backward_size - size)};
                    const auto stop_pos {position + move_size};
                    ds::uninitialized_copy<false, iterator &>(stop_pos, old_last, this->last);
                    this->move_to(position, stop_pos, old_last);
                    ds::copy(begin, end, position);
                }
            }else {
                this->check_and_expand<false>(size);
                const auto real_pos {pos + 1};
                const auto position {this->first + real_pos}, old_first {this->first};
                if(size > pos) {
                    ForwardIterator construction_end {};
                    if constexpr(is_bidirectional_iterator<ForwardIterator>::value) {
                        construction_end = ds::advance(end, -(real_pos));
                    }else {
                        construction_end = ds::advance(begin, size - (pos - 1));
                    }
                    this->construct_front(begin, construction_end);
                    this->uninitialized_copy_to_front(old_first, position);
                    ds::copy(construction_end, end, old_first);
                }else {
                    const auto stop_pos {this->first + static_cast<difference_type>(size)};
                    this->uninitialized_copy_to_front(old_first, stop_pos);
                    this->move_to<false>(stop_pos, position, old_first);
                    ds::copy(begin, end, position - size);
                }
            }
        }
        return this->first + pos;
    }
    template <typename T, typename Allocator>
    template <typename ForwardIterator>
    inline typename deque<T, Allocator>::iterator
    deque<T, Allocator>::insert(const_iterator pos,
            enable_if_t<is_forward_iterator_v<ForwardIterator>, ForwardIterator> begin, ForwardIterator end) {
        return this->insert(pos - this->first, begin, end);
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::iterator
    deque<T, Allocator>::insert(difference_type pos, initializer_list<value_type> init_list) {
        return this->insert(pos, init_list.begin(), init_list.end());
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::iterator
    deque<T, Allocator>::insert(const_iterator pos, initializer_list<value_type> init_list) {
        return this->insert(pos - this->first, init_list.begin(), init_list.end());
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::iterator
    deque<T, Allocator>::erase(difference_type pos, size_type size)
            noexcept(is_nothrow_copy_assignable_v<value_type>) {
        if(size > 0) {
            const auto begin {this->first + pos};
            if(const auto holding {this->size()}; holding / 2 <= pos) {
                ds::copy(begin + static_cast<difference_type>(size), this->last, begin);
                this->destroy(this->last - static_cast<difference_type>(size), this->last);
            }else {
                this->move_to<false>(this->first, this->first + pos, this->first + (pos + size));
                this->destroy(this->first, this->first + static_cast<difference_type>(size));
            }
        }
        return this->first + pos;
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::iterator
    deque<T, Allocator>::erase(const_iterator pos, size_type size)
            noexcept(is_nothrow_copy_assignable_v<value_type>) {
        return this->erase(pos - this->first, size);
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::iterator
    deque<T, Allocator>::erase(const_iterator begin, const_iterator end)
            noexcept(is_nothrow_copy_assignable_v<value_type>) {
        return this->erase(begin - this->first, end - begin);
    }
    template <typename T, typename Allocator>
    inline typename deque<T, Allocator>::iterator
    deque<T, Allocator>::erase(const_iterator pos) noexcept(is_nothrow_copy_assignable_v<value_type>) {
        return this->erase(pos - this->first);
    }
    template <typename T, typename Allocator>
    template <typename ...Args>
    typename deque<T, Allocator>::iterator
    deque<T, Allocator>::emplace(difference_type pos, Args &&...args) {
        if(const auto holding {this->size()}; holding / 2 <= pos) {
            this->push_back(ds::move_if<is_nothrow_move_constructible_v<value_type>>(this->back()));
            const auto old_last {this->last - 1};
            auto begin {this->first + pos};
            this->move_to(begin, old_last, old_last);
            *begin = value_type(ds::forward<Args>(args)...);
            return begin;
        }
        this->push_front(ds::move_if<is_nothrow_move_constructible_v<value_type>>(this->front()));
        const auto old_first {this->first + 1};
        auto begin {old_first + 1};
        auto position {begin + pos};
        this->move_to<false>(begin, position, old_first);
        *position = value_type(ds::forward<Args>(args)...);
        return position;
    }
    template <typename T, typename Allocator>
    template <typename ...Args>
    inline typename deque<T, Allocator>::iterator
    deque<T, Allocator>::emplace(const_iterator pos, Args &&...args) {
        return this->emplace(pos - this->first, ds::forward<Args>(args)...);
    }
    template <typename T, typename Allocator>
    inline void deque<T, Allocator>::push_back(const_reference value) {
        this->emplace_back(value);
    }
    template <typename T, typename Allocator>
    inline void deque<T, Allocator>::push_back(rvalue_reference value) {
        this->emplace_back(ds::move(value));
    }
    template <typename T, typename Allocator>
    inline void deque<T, Allocator>::push_front(const_reference value) {
        this->emplace_front(value);
    }
    template <typename T, typename Allocator>
    inline void deque<T, Allocator>::push_front(rvalue_reference value) {
        this->emplace_front(ds::move(value));
    }
    template <typename T, typename Allocator>
    template <typename ...Args>
    inline void deque<T, Allocator>::emplace_back(Args &&...args) {
        this->check_and_expand(1);
        alloc_traits::construct(this->last.iter, ds::forward<Args>(args)...);
        ++this->last;
    }
    template <typename T, typename Allocator>
    template <typename ...Args>
    inline void deque<T, Allocator>::emplace_front(Args &&...args) {
        this->check_and_expand<false>(1);
        alloc_traits::construct((this->first - 1).iter, ds::forward<Args>(args)...);
        --this->first;
    }
    template <typename T, typename Allocator>
    inline void deque<T, Allocator>::pop_back() noexcept {
        if(this->empty()) {
            return;
        }
        --this->last;
        if(not is_trivially_destructible_v<value_type>) {
            alloc_traits::destroy(this->last.iter);
        }
    }
    template <typename T, typename Allocator>
    inline void deque<T, Allocator>::pop_front() noexcept {
        if(this->empty()) {
            return;
        }
        if(not is_trivially_destructible_v<value_type>) {
            alloc_traits::destory(this->first.iter);
        }
        ++this->first;
    }
}

namespace data_structure {
    template <typename T, typename AllocatorLHS, typename AllocatorRHS>
    inline void swap(deque<T, AllocatorLHS> &lhs, deque<T, AllocatorRHS> &rhs) noexcept {
        lhs.swap(rhs);
    }
    template <typename T, typename AllocatorLHS, typename AllocatorRHS>
    bool operator==(const deque<T, AllocatorLHS> &lhs, const deque<T, AllocatorRHS> &rhs)
            noexcept(has_nothrow_equal_to_operator_v<T>) {
        if(lhs.size() not_eq rhs.size()) {
            return false;
        }
        const auto end {lhs.cend()};
        for(auto it {rhs.cbegin()}, begin {lhs.cbegin()}; begin not_eq end; ++it, static_cast<void>(++begin)) {
            if(not(*it == *begin)) {
                return false;
            }
        }
        return true;
    }
    template <typename T, typename AllocatorLHS, typename AllocatorRHS>
    inline bool operator!=(const deque<T, AllocatorLHS> &lhs, const deque<T, AllocatorRHS> &rhs)
            noexcept(has_nothrow_equal_to_operator_v<T>) {
        return not(lhs == rhs);
    }
    template <typename T, typename AllocatorLHS, typename AllocatorRHS>
    bool operator<(const deque<T, AllocatorLHS> &lhs, const deque<T, AllocatorRHS> &rhs)
            noexcept(has_nothrow_less_operator_v<T>) {
        auto lhs_cursor {lhs.cbegin()}, rhs_cursor {rhs.cbegin()};
        const auto lhs_end {lhs.cend()}, rhs_end {rhs.cend()};
        for(; rhs_cursor not_eq rhs_end; ++lhs_cursor, static_cast<void>(++rhs_cursor)) {
            if(lhs_cursor == lhs_end or *lhs_cursor < *rhs_cursor) {
                return true;
            }
            if(*rhs_cursor < *lhs_cursor) {
                return false;
            }
        }
        return false;
    }
    template <typename T, typename AllocatorLHS, typename AllocatorRHS>
    inline bool operator<=(const deque<T, AllocatorLHS> &lhs, const deque<T, AllocatorRHS> &rhs)
            noexcept(has_nothrow_less_operator_v<T>) {
        return not(rhs < lhs);
    }
    template <typename T, typename AllocatorLHS, typename AllocatorRHS>
    inline bool operator>(const deque<T, AllocatorLHS> &lhs, const deque<T, AllocatorRHS> &rhs)
            noexcept(has_nothrow_less_operator_v<T>) {
        return rhs < lhs;
    }
    template <typename T, typename AllocatorLHS, typename AllocatorRHS>
    inline bool operator>=(const deque<T, AllocatorLHS> &lhs, const deque<T, AllocatorRHS> &rhs)
            noexcept(has_nothrow_less_operator_v<T>) {
        return not(lhs < rhs);
    }
}

#endif //DATA_STRUCTURE_DEQUE_HPP
