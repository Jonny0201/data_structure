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

#ifndef DATA_STRUCTURE_STATIC_FORWARD_LIST_HPP
#define DATA_STRUCTURE_STATIC_FORWARD_LIST_HPP

#include "deque.hpp"

namespace data_structure {
    template <typename T, typename Container = deque<__dsa::static_forward_list_node<T>>>
    class static_forward_list final {
    private:
        using node_value_type = __dsa::static_forward_list_node<T>;
    public:
        using container_type = Container;
        using allocator_type = typename container_type::allocator_type;
        using size_type = typename container_type::size_type;
        using difference_type = ptrdiff_t;
        using value_type = T;
        using reference = typename add_lvalue_reference<value_type>::type;
        using const_reference = typename add_const_reference<value_type>::type;
        using rvalue_reference = typename add_rvalue_reference<value_type>::type;
        using pointer = typename add_pointer<value_type>::type;
        using const_pointer = typename add_const_pointer<value_type>::type;
        using iterator = __dsa::static_forward_list_iterator<value_type, container_type, false>;
        using const_iterator = __dsa::static_forward_list_iterator<value_type, container_type, true>;
    private:
        difference_type head;
        container_type c;
        difference_type empty_pos;
    private:
        void make_list(size_type) noexcept;
        [[nodiscard]]
        difference_type update_empty_pos() noexcept;
        void insert_at_back(difference_type, difference_type, const_reference, size_type);
        template <typename InputIterator>
        void insert_at_back(difference_type, difference_type, typename enable_if<
                is_input_iterator<InputIterator>::value, InputIterator>::type, InputIterator);
        iterator insert_auxiliary(difference_type, difference_type, const_reference, size_type);
        template <typename InputIterator>
        iterator insert_auxiliary(difference_type, difference_type, typename enable_if<
                is_input_iterator<InputIterator>::value, InputIterator>::type, InputIterator);
        void insert_on_head(const_reference, size_type);
        template <typename InputIterator>
        void insert_on_head(typename enable_if<is_input_iterator<InputIterator>::value, InputIterator>::type,
                InputIterator);
        void erase_on_head(const_iterator);
    public:
        constexpr static_forward_list() noexcept(is_nothrow_default_constructible<container_type>::value);
        explicit static_forward_list(size_type);
        static_forward_list(size_type, const_reference);
        template <typename InputIterator>
        static_forward_list(typename enable_if<
                is_input_iterator<InputIterator>::value and not is_forward_iterator<InputIterator>::value,
                InputIterator>::type, InputIterator);
        template <typename ForwardIterator>
        static_forward_list(typename enable_if<is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type,
                ForwardIterator);
        static_forward_list(initializer_list<value_type>);
        static_forward_list(const static_forward_list &) = default;
        static_forward_list(static_forward_list &&) noexcept = default;
        ~static_forward_list() noexcept = default;
    public:
        static_forward_list &operator=(const static_forward_list &) = default;
        static_forward_list &operator=(static_forward_list &&) noexcept = default;
        static_forward_list &operator=(initializer_list<value_type>);
    public:
        void assign(size_type, const_reference = {});
        template <typename InputIterator>
        void assign(typename enable_if<
                is_input_iterator<InputIterator>::value and not is_forward_iterator<InputIterator>::value,
                InputIterator>::type, InputIterator);
        template <typename ForwardIterator>
        void assign(typename enable_if<
                is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type, ForwardIterator);
        void assign(initializer_list<value_type>);
        [[nodiscard]]
        reference front() noexcept;
        [[nodiscard]]
        const_reference front() const noexcept;
        [[nodiscard]]
        iterator before_begin() noexcept;
        [[nodiscard]]
        const_iterator before_begin() const noexcept;
        [[nodiscard]]
        iterator begin() noexcept;
        [[nodiscard]]
        const_iterator begin() const noexcept;
        [[nodiscard]]
        constexpr iterator end() noexcept;
        [[nodiscard]]
        constexpr const_iterator end() const noexcept;
        [[nodiscard]]
        const_iterator cbefore_begin() const noexcept;
        [[nodiscard]]
        const_iterator cbegin() const noexcept;
        [[nodiscard]]
        constexpr const_iterator cend() const noexcept;
        [[nodiscard]]
        bool empty() const noexcept;
        [[nodiscard]]
        size_type size() const noexcept;
        [[nodiscard]]
        constexpr size_type max_size() const noexcept;
        void clear() noexcept;
        void swap(static_forward_list &) noexcept;
        void resize(size_type, const_reference = {});
        iterator insert(difference_type, const_reference, size_type = 1);
        iterator insert_after(const_iterator, const_reference, size_type = 1);
        iterator insert(difference_type, rvalue_reference);
        iterator insert_after(const_iterator, rvalue_reference);
        template <typename InputIterator>
        iterator insert(difference_type, typename enable_if<
                is_input_iterator<InputIterator>::value, InputIterator>::type, InputIterator);
        template <typename InputIterator>
        iterator insert_after(const_iterator, typename enable_if<
                is_input_iterator<InputIterator>::value, InputIterator>::type, InputIterator);
        iterator insert(difference_type, initializer_list<value_type>);
        iterator insert_after(const_iterator, initializer_list<value_type>);
        iterator erase(difference_type, size_type = 1) noexcept;
        iterator erase_after(const_iterator, size_type = 1) noexcept;
        iterator erase_after(const_iterator) noexcept;
        iterator erase_after(const_iterator, const_iterator) noexcept;
        template <typename ...Args>
        iterator emplace(difference_type, Args &&...);
        template <typename ...Args>
        iterator emplace_after(const_iterator, Args &&...);
        void push_front(const_reference);
        void push_front(rvalue_reference);
        template <typename ...Args>
        void emplace_front(Args &&...);
        void pop_front() noexcept;
    };
    template <typename T, typename Container>
    void swap(static_forward_list<T, Container> &, static_forward_list<T, Container> &) noexcept;
    template <typename T, typename Container>
    bool operator==(const static_forward_list<T, Container> &, const static_forward_list<T, Container> &);
    template <typename T, typename Container>
    bool operator!=(const static_forward_list<T, Container> &, const static_forward_list<T, Container> &);
}

namespace data_structure {
    /* private functions */
    template <typename T, typename Container>
    void static_forward_list<T, Container>::make_list(size_type size) noexcept {
        auto i {0};
        for(--size; i < size; ++i) {
            this->c[i].next = i + 1;
        }
        this->c[i].set_null();
    }
    template <typename T, typename Container>
    inline typename static_forward_list<T, Container>::difference_type
    static_forward_list<T, Container>::update_empty_pos() noexcept {
        const auto end {static_cast<difference_type>(this->c.size())};
        for(auto cursor {this->empty_pos + 1}; cursor not_eq end; ++cursor) {
            if(this->c[cursor].is_empty()) {
                return cursor;
            }
        }
        for(auto cursor {this->empty_pos - 1}; cursor >= 0; --cursor) {
            if(this->c[cursor].is_empty()) {
                return cursor;
            }
        }
        return node_value_type::empty;
    }
    template <typename T, typename Allocator>
    void static_forward_list<T, Allocator>::insert_at_back(
            difference_type before, difference_type after, const_reference value, size_type size) {
        const auto container_size {this->c.size()};
        this->c.insert(this->c.cend(), {value}, size);
        const auto total_size {container_size + size - 1};
        auto i {container_size};
        for(; i < total_size; ++i) {
            this->c[i].next = i + 1;
        }
        if(before != -1) {
            this->c[before].next = container_size;
            this->c[i].next = after;
        }else {
            this->c[i].next = this->head;
            this->head = container_size;
        }
    }
    template <typename T, typename Allocator>
    template <typename InputIterator>
    void static_forward_list<T, Allocator>::insert_at_back(difference_type before, difference_type after,
            typename enable_if<is_input_iterator<InputIterator>::value, InputIterator>::type begin,
            InputIterator end) {
        const auto container_size {this->c.size()};
        while(begin not_eq end) {
            if constexpr(is_forward_iterator<InputIterator>::value) {
                this->c.push_back({*begin++});
            }else {
                this->c.push_back({ds::move(*begin++)});
            }
        }
        const auto total_size {this->c.size() - 1};
        auto i {container_size};
        for(; i < total_size; ++i) {
            this->c[i].next = i + 1;
        }
        if(before != -1) {
            this->c[before].next = container_size;
            this->c[i].next = after;
        }else {
            this->c[i].next = this->head;
            this->head = container_size;
        }
    }
    template <typename T, typename Container>
    typename static_forward_list<T, Container>::iterator
    static_forward_list<T, Container>::insert_auxiliary(difference_type before, difference_type after,
            const_reference value, size_type size) {
        if(this->empty_pos == node_value_type::empty) {
            this->insert_at_back(before, after, value, size);
            return iterator(this->c[before].next, this->c);
        }
        auto cursor {before};
        while(true) {
            this->c[cursor].next = this->empty_pos;
            this->c[this->empty_pos].value = value;
            if(--size == 0) {
                this->c[this->empty_pos].next = after;
                this->empty_pos = this->update_empty_pos();
                return iterator(this->c[before].next, this->c);
            }
            if(auto next {this->update_empty_pos()}; next not_eq node_value_type::empty) {
                cursor = this->empty_pos;
                this->empty_pos = next;
            }else {
                this->insert_at_back(this->empty_pos, after, value, size);
                this->empty_pos = node_value_type::empty;
                break;
            }
        }
        return iterator(this->c[before].next, this->c);
    }
    template <typename T, typename Container>
    template <typename InputIterator>
    typename static_forward_list<T, Container>::iterator
    static_forward_list<T, Container>::insert_auxiliary(difference_type before, difference_type after,
            typename enable_if<is_input_iterator<InputIterator>::value, InputIterator>::type begin,
            InputIterator end) {
        if(this->empty_pos == node_value_type::empty) {
            this->insert_at_back(before, after, begin, end);
            return iterator(this->c[before].next, this->c);
        }
        auto cursor {before};
        while(true) {
            this->c[cursor].next = this->empty_pos;
            if constexpr(is_forward_iterator<InputIterator>::value) {
                this->c[this->empty_pos].value = *begin;
            }else {
                this->c[this->empty_pos].value = ds::move(*begin);
            }
            if(++begin == end) {
                this->c[this->empty_pos].next = after;
                this->empty_pos = this->update_empty_pos();
                return iterator(this->c[before].next, this->c);
            }
            if(auto next {this->update_empty_pos()}; next not_eq node_value_type::empty) {
                cursor = this->empty_pos;
                this->empty_pos = next;
            }else {
                this->insert_at_back(this->empty_pos, after, begin, end);
                this->empty_pos = node_value_type::empty;
                break;
            }
        }
        return iterator(this->c[before].next, this->c);
    }
    template <typename T, typename Container>
    void static_forward_list<T, Container>::insert_on_head(const_reference value, size_type size) {
        if(this->empty_pos == node_value_type::empty) {
            this->insert_at_back(-1, {}, value, size);
            return;
        }
        auto backup {this->head};
        this->head = this->empty_pos;
        while(true) {
            this->c[this->empty_pos].value = value;
            if(--size == 0) {
                this->c[this->empty_pos].next = this->head;
                this->empty_pos = this->update_empty_pos();
                return;
            }
            if(auto next {this->update_empty_pos()}; next not_eq node_value_type::empty) {
                this->c[this->empty_pos].next = next;
                this->empty_pos = next;
            }else {
                this->insert_at_back(this->empty_pos, backup, value, size);
                this->empty_pos = node_value_type::empty;
                break;
            }
        }
    }
    template <typename T, typename Container>
    template <typename InputIterator>
    void static_forward_list<T, Container>::insert_on_head(typename enable_if<
            is_input_iterator<InputIterator>::value, InputIterator>::type begin, InputIterator end) {
        if(this->empty_pos == node_value_type::empty) {
            this->insert_at_back(-1, {}, begin, end);
            return;
        }
        auto backup {this->head};
        this->head = this->empty_pos;
        while(true) {
            if constexpr(is_forward_iterator<InputIterator>::value) {
                this->c[this->empty_pos].value = *begin++;
            }else {
                this->c[this->empty_pos].value = ds::move(*begin++);
            }
            if(begin == end) {
                this->c[this->empty_pos].next = this->head;
                this->empty_pos = this->update_empty_pos();
                return;
            }
            if(auto next {this->update_empty_pos()}; next not_eq node_value_type::empty) {
                this->c[this->empty_pos].next = next;
                this->empty_pos = next;
            }else {
                this->insert_at_back(this->empty_pos, backup, begin, end);
                this->empty_pos = node_value_type::empty;
                break;
            }
        }
    }
    template <typename T, typename Container>
    void static_forward_list<T, Container>::erase_on_head(const_iterator end) {
        auto cursor {this->head};
        this->head = end.node;
        while(cursor not_eq this->head) {
            auto backup {cursor};
            cursor = this->c[cursor].next;
            this->c[backup].set_empty();
        }
    }

    /* public functions */
    template <typename T, typename Container>
    constexpr inline static_forward_list<T, Container>::static_forward_list()
            noexcept(is_nothrow_default_constructible<container_type>::value) :
            head {node_value_type::null}, c {}, empty_pos {node_value_type::empty} {}
    template <typename T, typename Container>
    inline static_forward_list<T, Container>::static_forward_list(size_type size) :
            head {0}, c(size), empty_pos {node_value_type::empty} {
        this->make_list(size);
    }
    template <typename T, typename Container>
    inline static_forward_list<T, Container>::static_forward_list(size_type size, const_reference value) :
            head {0}, c(size, {value}), empty_pos {node_value_type::empty} {
        this->make_list(size);
    }
    template <typename T, typename Container>
    template <typename InputIterator>
    static_forward_list<T, Container>::static_forward_list(typename enable_if<
            is_input_iterator<InputIterator>::value and !is_forward_iterator<InputIterator>::value,
            InputIterator>::type begin, InputIterator end) : head {0}, c {}, empty_pos {node_value_type::empty} {
        auto next {1};
        while(begin not_eq end) {
            this->c.push_back({ds::move(*begin++), next++});
        }
        this->c.back().set_null();
    }
    template <typename T, typename Container>
    template <typename ForwardIterator>
    static_forward_list<T, Container>::static_forward_list(
            typename enable_if<is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type begin,
            ForwardIterator end) : head {0}, c {}, empty_pos {node_value_type::empty} {
        auto next {1};
        while(begin not_eq end) {
            this->c.push_back({*begin++, next++});
        }
        this->c.back().set_null();
    }
    template <typename T, typename Container>
    inline static_forward_list<T, Container>::static_forward_list(initializer_list<value_type> init_list) :
            static_forward_list(init_list.begin(), init_list.end()) {}
    template <typename T, typename Container>
    inline static_forward_list<T, Container> &
    static_forward_list<T, Container>::operator=(initializer_list<value_type> init_list) {
        this->assign(init_list.begin(), init_list.end());
        return *this;
    }
    template <typename T, typename Container>
    void static_forward_list<T, Container>::assign(size_type size, const_reference value) {
        if(this->empty() or size == 0) {
            return;
        }
        const auto before_cursor {this->cbefore_begin()};
        auto cursor {this->begin()};
        const auto end {this->end()};
        while(cursor not_eq end and size-- > 0) {
            *cursor++ = value;
            ++before_cursor;
        }
        if(size > 0) {
            this->insert_after(before_cursor, value, size);
            return;
        }
        if(cursor not_eq end) {
            this->erase_after(before_cursor, end);
        }
    }
    template <typename T, typename Container>
    template <typename InputIterator>
    void static_forward_list<T, Container>::assign(typename enable_if<
            is_input_iterator<InputIterator>::value and !is_forward_iterator<InputIterator>::value,
            InputIterator>::type begin, InputIterator end) {
        if(this->empty() or begin == end) {
            return;
        }
        auto before_cursor {this->cbefore_begin()};
        auto cursor {this->begin()};
        const auto last {this->end()};
        while(cursor not_eq last and begin not_eq end) {
            *cursor++ = ds::move(*begin++);
            ++before_cursor;
        }
        if(begin not_eq end) {
            this->insert_after(before_cursor, begin, end);
            return;
        }
        if(cursor not_eq last) {
            this->erase_after(before_cursor, last);
        }
    }
    template <typename T, typename Container>
    template <typename ForwardIterator>
    void static_forward_list<T, Container>::assign(typename enable_if<
            is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type begin, ForwardIterator end) {
        if(this->empty() or begin == end) {
            return;
        }
        auto before_cursor {this->cbefore_begin()};
        auto cursor {this->begin()};
        const auto last {this->end()};
        while(cursor not_eq last and begin not_eq end) {
            *cursor++ = *begin++;
            ++before_cursor;
        }
        if(begin not_eq end) {
            this->insert_after(before_cursor, begin, end);
            return;
        }
        if(cursor not_eq last) {
            this->erase_after(before_cursor, last);
        }
    }
    template <typename T, typename Container>
    inline void static_forward_list<T, Container>::assign(initializer_list<value_type> init_list) {
        this->assign(init_list.begin(), init_list.end());
    }
    template <typename T, typename Container>
    inline typename static_forward_list<T, Container>::reference
    static_forward_list<T, Container>::front() noexcept {
        return this->c[this->c[0].next].value;
    }
    template <typename T, typename Container>
    inline typename static_forward_list<T, Container>::const_reference
    static_forward_list<T, Container>::front() const noexcept {
        return this->c[this->c[0].next].value;
    }
    template <typename T, typename Container>
    inline typename static_forward_list<T, Container>::iterator
    static_forward_list<T, Container>::before_begin() noexcept {
        return iterator(this->head, this->c, true);
    }
    template <typename T, typename Container>
    inline typename static_forward_list<T, Container>::const_iterator
    static_forward_list<T, Container>::before_begin() const noexcept {
        return const_iterator(this->head, const_cast<static_forward_list *>(this)->c, true);
    }
    template <typename T, typename Container>
    inline typename static_forward_list<T, Container>::iterator
    static_forward_list<T, Container>::begin() noexcept {
        return iterator(this->head, this->c);
    }
    template <typename T, typename Container>
    inline typename static_forward_list<T, Container>::const_iterator
    static_forward_list<T, Container>::begin() const noexcept {
        return const_iterator(this->head, const_cast<static_forward_list *>(this)->c);
    }
    template <typename T, typename Container>
    constexpr inline typename static_forward_list<T, Container>::iterator
    static_forward_list<T, Container>::end() noexcept {
        return iterator(node_value_type::null, this->c);
    }
    template <typename T, typename Container>
    constexpr inline typename static_forward_list<T, Container>::const_iterator
    static_forward_list<T, Container>::end() const noexcept {
        return const_iterator(node_value_type::null, const_cast<static_forward_list *>(this)->c);
    }
    template <typename T, typename Container>
    inline typename static_forward_list<T, Container>::const_iterator
    static_forward_list<T, Container>::cbefore_begin() const noexcept {
        return this->before_begin();
    }
    template <typename T, typename Container>
    inline typename static_forward_list<T, Container>::const_iterator
    static_forward_list<T, Container>::cbegin() const noexcept {
        return this->begin();
    }
    template <typename T, typename Container>
    constexpr inline typename static_forward_list<T, Container>::const_iterator
    static_forward_list<T, Container>::cend() const noexcept {
        return this->end();
    }
    template <typename T, typename Container>
    inline bool static_forward_list<T, Container>::empty() const noexcept {
        return this->head == node_value_type::null;
    }
    template <typename T, typename Container>
    inline typename static_forward_list<T, Container>::size_type
    static_forward_list<T, Container>::size() const noexcept {
        auto cursor {this->c[0].next};
        size_type size {0};
        for(; cursor not_eq node_value_type::null; cursor = this->c[cursor].next, static_cast<void>(++size));
        return size;
    }
    template <typename T, typename Container>
    constexpr inline typename static_forward_list<T, Container>::size_type
    static_forward_list<T, Container>::max_size() const noexcept {
        return std::numeric_limits<ptrdiff_t>::max() / sizeof(node_value_type);
    }
    template <typename T, typename Container>
    void static_forward_list<T, Container>::clear() noexcept {
        if(this->empty()) {
            return;
        }
        this->c.clear();
        this->head = node_value_type::null;
        this->empty_pos = node_value_type::empty;
    }
    template <typename T, typename Container>
    inline void static_forward_list<T, Container>::swap(static_forward_list &rhs) noexcept {
        ds::swap(this->head, rhs.head);
        this->c.swap(rhs.c);
        ds::swap(this->empty_pos, rhs.empty_pos);
    }
    template <typename T, typename Container>
    void static_forward_list<T, Container>::resize(size_type size, const_reference value) {
        size_type this_size {0};
        auto cursor {this->cbefore_begin()};
        for(; not cursor->is_null(); ++cursor, static_cast<void>(++size));
        if(this_size < size) {
            this->insert_after(cursor, value, size - this_size);
        }
    }
    template <typename T, typename Container>
    inline typename static_forward_list<T, Container>::iterator
    static_forward_list<T, Container>::insert(difference_type pos, const_reference value, size_type size) {
        if(size == 0) {
            return this->end();
        }
        if(pos == 0) {
            this->insert_on_head(value, size);
            return this->begin();
        }
        auto cursor {this->head};
        for(; --pos > 0 and cursor not_eq node_value_type::null; cursor = this->c[cursor].next);
        return this->insert_auxiliary(cursor, this->c[cursor].next, value, size);
    }
    template <typename T, typename Container>
    inline typename static_forward_list<T, Container>::iterator
    static_forward_list<T, Container>::insert_after(const_iterator pos, const_reference value, size_type size) {
        if(size == 0) {
            return this->end();
        }
        if(pos.head) {
            this->insert_on_head(value, size);
            return this->begin();
        }
        return this->insert_auxiliary(pos.node, this->c[pos.node].next, value, size);
    }
    template <typename T, typename Container>
    inline typename static_forward_list<T, Container>::iterator
    static_forward_list<T, Container>::insert(difference_type pos, rvalue_reference value) {
        auto cursor {this->head};
        for(auto i {pos}; --i > 0 and cursor not_eq node_value_type::null; cursor = this->c[cursor].next);
        return this->insert_after(const_iterator(cursor, this->c, pos == 0), ds::move(value));
    }
    template <typename T, typename Container>
    typename static_forward_list<T, Container>::iterator
    static_forward_list<T, Container>::insert_after(const_iterator pos, rvalue_reference value) {
        if(pos.head) {
            this->push_front(ds::move(value));
            return this->begin();
        }
        const auto after {this->c[pos.node].next};
        if(this->empty_pos == node_value_type::empty) {
            const auto size {static_cast<difference_type>(this->c.size())};
            this->c[pos.node].next = size;
            this->c.push_back({ds::move(value), after});
            return iterator(size, this->c);
        }
        this->c[pos.node].next = this->empty_pos;
        this->c[this->empty_pos].value = ds::move(value);
        this->c[this->empty_pos].next = after;
        this->empty_pos = this->update_empty_pos();
        return iterator(after, this->c);
    }
    template <typename T, typename Container>
    template <typename InputIterator>
    inline typename static_forward_list<T, Container>::iterator
    static_forward_list<T, Container>::insert(difference_type pos, typename enable_if<
            is_input_iterator<InputIterator>::value, InputIterator>::type begin, InputIterator end) {
        if(begin == end) {
            return this->end();
        }
        if(pos == 0) {
            this->insert_on_head(begin, end);
            return this->begin();
        }
        auto cursor {this->head};
        for(; --pos > 0 and cursor not_eq node_value_type::null; cursor = this->c[cursor].next);
        return this->insert_auxiliary(cursor, this->c[cursor].next, begin, end);
    }
    template <typename T, typename Container>
    template <typename InputIterator>
    inline typename static_forward_list<T, Container>::iterator
    static_forward_list<T, Container>::insert_after(const_iterator pos, typename enable_if<
            is_input_iterator<InputIterator>::value, InputIterator>::type begin, InputIterator end) {
        if(begin == end) {
            return this->end();
        }
        if(pos.head) {
            this->insert_on_head(begin, end);
            return this->begin();
        }
        auto cursor {this->head};
        for(; --pos > 0 and cursor not_eq node_value_type::empty; cursor = this->c[cursor].next);
        return this->insert_auxiliary(cursor, this->c[cursor].next, begin, end);
    }
    template <typename T, typename Container>
    inline typename static_forward_list<T, Container>::iterator
    static_forward_list<T, Container>::insert(difference_type pos, initializer_list<value_type> init_list) {
        return this->insert(pos, init_list.begin(), init_list.end());
    }
    template <typename T, typename Container>
    typename static_forward_list<T, Container>::iterator
    static_forward_list<T, Container>::insert_after(const_iterator pos, initializer_list<value_type> init_list) {
        return this->insert(pos, init_list.begin(), init_list.end());
    }
    template <typename T, typename Container>
    inline typename static_forward_list<T, Container>::iterator
    static_forward_list<T, Container>::erase(difference_type pos, size_type size) noexcept {
        auto cursor {this->head};
        for(auto i {pos}; --i > 0 and cursor not_eq node_value_type::null; cursor = this->c[cursor].next);
        auto last {cursor};
        if(pos != 0) {
            ++size;
        }
        for(; size-- > 0 and last not_eq node_value_type::null; last = this->c[last].next);
        return this->erase_after(const_iterator(cursor, this->c, pos == 0), const_iterator(last, this->c));
    }
    template <typename T, typename Container>
    inline typename static_forward_list<T, Container>::iterator
    static_forward_list<T, Container>::erase_after(const_iterator pos, size_type size) noexcept {
        auto last {pos};
        const auto end {this->cend()};
        for(++size; size-- > 0 and last not_eq end; ++last);
        return this->erase_after(pos, last);
    }
    template <typename T, typename Container>
    inline typename static_forward_list<T, Container>::iterator
    static_forward_list<T, Container>::erase_after(const_iterator pos) noexcept {
        return this->erase_after(pos, 1);
    }
    template <typename T, typename Container>
    typename static_forward_list<T, Container>::iterator
    static_forward_list<T, Container>::erase_after(const_iterator begin, const_iterator end) noexcept {
        if(begin == end) {
            return this->end();
        }
        if(begin.head) {
            this->erase_on_head(end);
            return this->begin();
        }
        auto backup {this->c[begin.node].next};
        this->c[begin.node].next = end.node;
        if(this->empty_pos == node_value_type::empty) {
            this->empty_pos = backup;
        }
        while(backup not_eq end.node) {
            auto next {this->c[backup].next};
            this->c[backup].set_empty();
            backup = next;
        }
        return iterator(backup, this->c);
    }
    template <typename T, typename Container>
    template <typename ...Args>
    inline typename static_forward_list<T, Container>::iterator
    static_forward_list<T, Container>::emplace(difference_type pos, Args &&...args) {
        return this->insert(pos, value_type(ds::forward<Args>(args)...));
    }
    template <typename T, typename Container>
    template <typename ...Args>
    inline typename static_forward_list<T, Container>::iterator
    static_forward_list<T, Container>::emplace_after(const_iterator pos, Args &&...args) {
        return this->insert_after(pos, value_type(ds::forward<Args>(args)...));
    }
    template <typename T, typename Container>
    void static_forward_list<T, Container>::push_front(const_reference value) {
        if(this->empty_pos == node_value_type::null) {
            const auto size {static_cast<difference_type>(this->c.size())};
            this->c.insert(this->c.cbegin(), {value, this->head});
            this->head = size;
            return;
        }
        this->c[this->empty_pos].value = value;
        this->c[this->empty_pos].next = this->head;
        this->head = this->empty_pos;
        this->empty_pos = this->update_empty_pos();
    }
    template <typename T, typename Container>
    void static_forward_list<T, Container>::push_front(rvalue_reference value) {
        if(this->empty_pos == node_value_type::null) {
            const auto size {static_cast<difference_type>(this->c.size())};
            this->c.insert(this->c.cbegin(), {ds::move(value), this->head});
            this->head = size;
            return;
        }
        this->c[this->empty_pos].value = ds::move(value);
        this->c[this->empty_pos].next = this->head;
        this->head = this->empty_pos;
        this->empty_pos = this->update_empty_pos();
    }
    template <typename T, typename Container>
    template <typename ...Args>
    inline void static_forward_list<T, Container>::emplace_front(Args &&...args) {
        this->push_front(value_type(ds::forward<Args>(args)...));
    }
    template <typename T, typename Container>
    inline void static_forward_list<T, Container>::pop_front() noexcept {
        auto backup {this->head};
        this->head = this->c[this->head].next;
        this->c[backup].set_empty();
    }
}

namespace data_structure {
    template <typename T, typename Container>
    inline void swap(const static_forward_list<T, Container> &lhs,
            const static_forward_list<T, Container> &rhs) noexcept {
        lhs.swap(rhs);
    }
    template <typename T, typename Container>
    bool operator==(const static_forward_list<T, Container> &lhs, const static_forward_list<T, Container> &rhs) {
        auto lhs_begin {lhs.cbegin()};
        auto rhs_begin {rhs.cbegin()};
        const auto lhs_end {lhs.cend()};
        while(lhs_begin not_eq lhs_end) {
            if(*lhs_begin not_eq *rhs_begin) {
                return false;
            }
            ++lhs_begin;
            ++rhs_begin;
        }
        return rhs_begin == rhs.cend();
    }
    template <typename T, typename Container>
    bool operator!=(const static_forward_list<T, Container> &lhs, const static_forward_list<T, Container> &rhs) {
        return not(lhs == rhs);
    }
}

#endif //DATA_STRUCTURE_STATIC_FORWARD_LIST_HPP