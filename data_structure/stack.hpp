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

#ifndef DATA_STRUCTURE_STACK_HPP
#define DATA_STRUCTURE_STACK_HPP

#include "deque.hpp"

namespace data_structure {
    template <typename T, typename Container = deque<T>, bool Bidirectional = false>
    class stack final {
        template <typename Type, typename ContainerType>
        friend bool operator==(const stack<Type, ContainerType, false> &lhs,
                const stack<Type, ContainerType, false> &rhs);
        template <typename Type, typename ContainerType>
        friend bool operator<(const stack<Type, ContainerType, false> &lhs,
                const stack<Type, ContainerType, false> &rhs);
    public:
        using container_type = Container;
        using size_type = typename container_type::size_type;
        using difference_type = typename container_type::difference_type;
        using value_type = T;
        using reference = typename container_type::reference;
        using const_reference = typename container_type::const_reference;
        using rvalue_reference = typename container_type::rvalue_reference;
        using pointer = typename container_type::pointer;
        using const_pointer = typename container_type::const_pointer;
        static_assert(is_same<value_type, typename container_type::value_type>::value,
                "The stack holds different value_type!");
    private:
        container_type c;
    public:
        constexpr stack() noexcept(is_nothrow_default_constructible<container_type>::value) = default;
        explicit stack(const container_type &c) : c {c} {}
        explicit stack(container_type &&c) noexcept : c {ds::move(c)} {}
        stack(const stack &) = default;
        stack(stack &&) noexcept = default;
        ~stack() noexcept = default;
    public:
        stack &operator=(const stack &) = default;
        stack &operator=(stack &&) noexcept = default;
        stack &operator=(const container_type &rhs) {
            this->c = rhs;
            return *this;
        }
        stack &operator=(container_type &&rhs) noexcept {
            this->c = ds::move(rhs);
            return *this;
        }
    public:
        [[nodiscard]]
        reference top() noexcept {
            return this->c.back();
        }
        [[nodiscard]]
        const_reference top() const noexcept {
            return this->c.back();
        }
        [[nodiscard]]
        bool empty() const noexcept {
            return this->c.empty();
        }
        [[nodiscard]]
        size_type size() const noexcept {
            return this->c.size();
        }
        [[nodiscard]]
        constexpr size_type max_size() const noexcept {
            return this->c.max_size();
        }
        void push(const_reference value) {
            this->c.push_back(value);
        }
        void push(rvalue_reference value) {
            this->c.push_back(ds::move(value));
        }
        template <typename ...Args>
        void emplace(Args &&...args) {
            this->c.push_back(value_type(ds::forward<Args>(args)...));
        }
        void pop() noexcept {
            this->c.pop_back();
        }
        void swap(stack &rhs) noexcept {
            this->c.swap(rhs.c);
        }
    };

    template <typename T, typename Container, bool Bidirectional>
    inline void swap(stack<T, Container, Bidirectional> &lhs,
            stack<T, Container, Bidirectional> &rhs) noexcept {
        lhs.swap(rhs);
    }
    template <typename T, typename Container>
    inline bool operator==(const stack<T, Container, false> &lhs, const stack<T, Container, false> &rhs) {
        return lhs.c == rhs.c;
    }
    template <typename T, typename Container>
    inline bool operator!=(const stack<T, Container, false> &lhs, const stack<T, Container, false> &rhs) {
        return lhs.c != rhs.c;
    }
    template <typename T, typename Container>
    inline bool operator<(const stack<T, Container, false> &lhs, const stack<T, Container, false> &rhs) {
        return lhs.c < rhs.c;
    }
    template <typename T, typename Container>
    inline bool operator<=(const stack<T, Container, false> &lhs, const stack<T, Container, false> &rhs) {
        return lhs.c <= rhs.c;
    }
    template <typename T, typename Container>
    inline bool operator>(const stack<T, Container, false> &lhs, const stack<T, Container, false> &rhs) {
        return lhs.c > rhs.c;
    }
    template <typename T, typename Container>
    inline bool operator>=(const stack<T, Container, false> &lhs, const stack<T, Container, false> &rhs) {
        return lhs.c >= rhs.c;
    }
}

namespace data_structure {
    template <typename T, typename Container>
    class stack<T, Container, true> final {
        template <typename Type, typename ContainerType>
        friend bool operator==(const stack<Type, ContainerType, true> &,
                const stack<Type, ContainerType, true> &);
        template <typename Type, typename ContainerType>
        friend bool operator<(const stack<Type, ContainerType, true> &,
                const stack<Type, ContainerType, true> &);
    public:
        using container_type = Container;
        using size_type = typename container_type::size_type;
        using difference_type = typename container_type::difference_type;
        using value_type = T;
        using reference = typename container_type::reference;
        using const_reference = typename container_type::const_reference;
        using rvalue_reference = typename container_type::rvalue_reference;
        using pointer = typename container_type::pointer;
        using const_pointer = typename container_type::const_pointer;
        static_assert(is_same<value_type, typename container_type::value_type>::value,
                      "The stack holds different value_type!");
    private:
        container_type front;
        container_type back;
    private:
        template <typename Front, typename Back, typename = typename enable_if<
                is_same<typename remove_reference<Front>::type, container_type>::value and
                is_same<typename remove_reference<Back>::type, container_type>::value>::type>
        stack(Front &&front, Back &&back, void *) :
                front {ds::forward<Front>(front)}, back {ds::forward<Back>(back)} {}
    public:
        constexpr stack() noexcept(is_nothrow_default_constructible<container_type>::value) = default;
        template <typename Front, typename Back>
        stack(Front &&front, Back &&back) : stack(front, back, nullptr) {}
        stack(const stack &) = default;
        stack(stack &&) noexcept = default;
        ~stack() noexcept = default;
    public:
        stack &operator=(const stack &) = default;
        stack &operator=(stack &&) noexcept = default;
    public:
        [[nodiscard]]
        reference top_front() noexcept {
            return this->front.back();
        }
        [[nodiscard]]
        const_reference top_front() const noexcept {
            return this->front.back();
        }
        [[nodiscard]]
        reference top_back() noexcept {
            return this->back.back();
        }
        [[nodiscard]]
        const_reference top_back() const noexcept {
            return this->back.back();
        }
        [[nodiscard]]
        bool empty_front() const noexcept {
            return this->front.empty();
        }
        [[nodiscard]]
        bool empty_back() const noexcept {
            return this->back.empty();
        }
        [[nodiscard]]
        bool empty() const noexcept {
            return this->empty_front() and this->empty_back();
        }
        [[nodiscard]]
        size_type size_front() const noexcept {
            return this->front.size();
        }
        [[nodiscard]]
        size_type size_back() const noexcept {
            return this->back.size();
        }
        [[nodiscard]]
        size_type size() const noexcept {
            return this->size_front() + this->size_back();
        }
        [[nodiscard]]
        constexpr size_type max_size_front() const noexcept {
            return this->max_size() / 2;
        }
        [[nodiscard]]
        constexpr size_type max_size_back() const noexcept {
            return this->max_size() / 2;
        }
        [[nodiscard]]
        constexpr size_type max_size() const noexcept {
            return this->c.max_size();
        }
        void push_front(const_reference value) {
            this->front.push_back(value);
        }
        void push_front(rvalue_reference value) {
            this->front.push_back(ds::move(value));
        }
        void push_back(const_reference value) {
            this->back.push_back(value);
        }
        void push_back(rvalue_reference value) {
            this->back.push_back(ds::move(value));
        }
        void push(const_reference value) {
            this->push_back(value);
            this->push_front(value);
        }
        void push(rvalue_reference value) {
            this->push_back(value);
            this->push_front(ds::move(value));
        }
        template <typename ...Args>
        void emplace_front(Args &&...args) {
            this->front.push_back(value_type(ds::forward<Args>(args)...));
        }
        template <typename ...Args>
        void emplace_back(Args &&...args) {
            this->back.push_back(value_type(ds::forward<Args>(args)...));
        }
        template <typename ...Args>
        void emplace(Args &&...args) {
            this->emplace_front(ds::forward<Args>(args)...);
            this->emplace_back(ds::forward<Args>(args)...);
        }
        void pop_front() noexcept {
            this->front.pop_back();
        }
        void pop_back() noexcept {
            this->back.pop_back();
        }
        void pop() noexcept {
            this->pop_front();
            this->pop_back();
        }
        void swap_front(stack &rhs) noexcept {
            this->front.swap(rhs.front);
        }
        void swap_back(stack &rhs) noexcept {
            this->back.swap(rhs.back);
        }
        void swap(stack &rhs) noexcept {
            this->swap_front(rhs);
            this->swap_back(rhs);
        }
    };

    template <typename T, typename Container>
    inline void swap(const stack<T, Container, true> &lhs, const stack<T, Container, true> &rhs) noexcept {
        lhs.swap(rhs);
    }
    template <typename T, typename Container>
    inline bool operator==(const stack<T, Container, true> &lhs, const stack<T, Container, true> &rhs) {
        return lhs.front == rhs.front and lhs.back == rhs.back;
    }
    template <typename T, typename Container>
    inline bool operator!=(const stack<T, Container, true> &lhs, const stack<T, Container, true> &rhs) {
        return not(lhs == rhs);
    }
    template <typename T, typename Container>
    inline bool operator<(const stack<T, Container, true> &lhs, const stack<T, Container, true> &rhs) {
        return lhs.front < rhs.front and lhs.back < rhs.back;
    }
    template <typename T, typename Container>
    inline bool operator<=(const stack<T, Container, true> &lhs, const stack<T, Container, true> &rhs) {
        return not(rhs < lhs);
    }
    template <typename T, typename Container>
    inline bool operator>(const stack<T, Container, true> &lhs, const stack<T, Container, true> &rhs) {
        return rhs < lhs;
    }
    template <typename T, typename Container>
    inline bool operator>=(const stack<T, Container, true> &lhs, const stack<T, Container, true> &rhs) {
        return not(lhs < rhs);
    }
}

namespace data_structure {
    template <typename T>
    struct stack<T, T *, false> final {
        template <typename Type>
        friend bool operator==(const stack<Type, Type *, false> &, const stack<Type, Type *, false> &);
        template <typename Type>
        friend bool operator<(const stack<Type, Type *, false> &, const stack<Type, Type *, false> &);
    public:
        using container_type = T *;
        using size_type = typename container_type::size_type;
        using difference_type = typename container_type::difference_type;
        using value_type = T;
        using reference = typename container_type::reference;
        using const_reference = typename container_type::const_reference;
        using rvalue_reference = typename container_type::rvalue_reference;
        using pointer = typename container_type::pointer;
        using const_pointer = typename container_type::const_pointer;
    private:
        using allocator_type = allocator<type_holder<T>>;
        using alloc_traits = allocator_traits<allocator_type>;
    private:
        constexpr static inline size_type base_size {64};
    private:
        pointer first;
        pointer cursor;
        pointer last;
    private:
        [[nodiscard]]
        static pointer allocate(size_type size = stack::base_size) {
            return reinterpret_cast<pointer>(alloc_traits::operator new(size * sizeof(value_type)));
        }
    private:
        void full() {
            if(this->cursor == this->last) {
                this->reallocate(this->capacity() * 2, *this);
            }
        }
        void reallocate(size_type size, const stack &rhs) {
            auto new_first {this->allocate(size)};
            auto new_cursor {new_first};
            __dsa::construct_ranges<alloc_traits, value_type, pointer &>(
                    new_first, {}, new_cursor, rhs.first, rhs.cursor);
            if constexpr(not is_trivially_destructible<value_type>::value) {
                alloc_traits::destroy(this->first, this->cursor);
            }
            alloc_traits::operator delete(this->first);
            this->first = new_first;
            this->cursor = new_cursor;
            this->last = new_first + static_cast<difference_type>(size);
        }
    public:
        stack() : first {this->allocate()}, cursor {this->first},
                last {this->first + static_cast<difference_type>(this->base_size)} {}
        stack(const stack &rhs) : first {this->allocate(rhs.capacity())}, cursor {this->first},
                last {this->first + rhs.capacity()} {
            __dsa::construct_ranges<alloc_traits, value_type, pointer &>(
                    this->first, {}, this->cursor, rhs.first, rhs.cursor);
        }
        stack(stack &&rhs) noexcept : first {rhs.first}, cursor {rhs.cursor}, last {rhs.last} {
            rhs.first = rhs.cursor = rhs.last = nullptr;
        }
        ~stack() noexcept {
            alloc_traits::destroy(this->first, this->cursor);
            alloc_traits::operator delete(this->first);
        }
    public:
        stack &operator=(const stack &rhs) {
            if(&rhs == this) {
                return *this;
            }
            this->reallocate(rhs.capacity(), rhs);
            return *this;
        }
        stack &operator=(stack &&rhs) noexcept {
            if(&rhs == this) {
                return *this;
            }
            this->~stack();
            this->first = rhs.first;
            this->cursor = rhs.cursor;
            this->last = rhs.last;
            rhs.first = rhs.cursor = rhs.last = nullptr;
            return *this;
        }
    public:
        [[nodiscard]]
        reference top() noexcept {
            return *(this->cursor - 1);
        }
        [[nodiscard]]
        const_reference top() const noexcept {
            return *(this->cursor - 1);
        }
        [[nodiscard]]
        bool empty() const noexcept {
            return this->first == this->cursor;
        }
        [[nodiscard]]
        size_type size() const noexcept {
            return this->cursor - this->first;
        }
        [[nodiscard]]
        size_type capacity() const noexcept {
            return this->last - this->first;
        }
        [[nodiscard]]
        size_type spare() const noexcept {
            return this->last - this->cursor;
        }
        [[nodiscard]]
        constexpr size_type max_size() const noexcept {
            return std::numeric_limits<size_type>::max() / sizeof(value_type);
        }
        void push(const_reference value) {
            this->full();
            alloc_traits::construct(this->cursor, value);
            ++this->cursor;
        }
        void push(rvalue_reference value) {
            this->full();
            alloc_traits::construct(this->cursor, ds::move(value));
            ++this->cursor;
        }
        template <typename ...Args>
        void emplace(Args &&...args) {
            this->push(value_type(ds::forward<Args>(args)...));
        }
        void pop() noexcept {
            if(this->empty()) {
                return;
            }
            --this->cursor;
            if constexpr(not is_trivially_destructible<value_type>::value) {
                alloc_traits::destroy(this->cursor);
            }
        }
        void swap(stack &rhs) noexcept {
            ds::swap(this->first, rhs.first);
            ds::swap(this->cursor, rhs.cursor);
            ds::swap(this->last, rhs.last);
        }
    };

    template <typename T>
    inline void swap(const stack<T, T *, false> &lhs, const stack<T, T *, false> &rhs) noexcept {
        lhs.swap(rhs);
    }
    template <typename T>
    bool operator==(const stack<T, T *, false> &lhs, const stack<T, T *, false> &rhs) {
        if(lhs.size() not_eq rhs.size()) {
            return false;
        }
        auto lhs_cursor {lhs.first};
        const auto lhs_end {lhs.cursor};
        for(auto cursor {rhs.first}; lhs_cursor not_eq lhs_end; ++cursor, static_cast<void>(++lhs_cursor)) {
            if(*lhs_cursor not_eq *cursor) {
                return false;
            }
        }
        return true;
    }
    template <typename T>
    inline bool operator!=(const stack<T, T *, false> &lhs, const stack<T, T *, false> &rhs) {
        return not(lhs == rhs);
    }
    template <typename T>
    bool operator<(const stack<T, T *, false> &lhs, const stack<T, T *, false> &rhs) {
        auto lhs_cursor {lhs.first}, rhs_cursor {rhs.first};
        const auto lhs_end {lhs.cursor}, rhs_end {rhs.cursor};
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
    template <typename T>
    inline bool operator<=(const stack<T, T *, false> &lhs, const stack<T, T *, false> &rhs) {
        return not(rhs < lhs);
    }
    template <typename T>
    inline bool operator>(const stack<T, T *, false> &lhs, const stack<T, T *, false> &rhs) {
        return rhs < lhs;
    }
    template <typename T>
    inline bool operator>=(const stack<T, T *, false> &lhs, const stack<T, T *, false> &rhs) {
        return not(lhs < rhs);
    }
}

namespace data_structure {
    template <typename T>
    class stack<T, T *, true> final {
        template <typename Type>
        friend bool operator==(const stack<Type, Type *, true> &, const stack<Type, Type *, true> &);
        template <typename Type>
        friend bool operator<(const stack<Type, Type *, true> &, const stack<Type, Type *, true> &);
    public:
        using container_type = T *;
        using size_type = typename container_type::size_type;
        using difference_type = typename container_type::difference_type;
        using value_type = T;
        using reference = typename container_type::reference;
        using const_reference = typename container_type::const_reference;
        using rvalue_reference = typename container_type::rvalue_reference;
        using pointer = typename container_type::pointer;
        using const_pointer = typename container_type::const_pointer;
    private:
        using allocator_type = allocator<type_holder<T>>;
        using alloc_traits = allocator_traits<allocator_type>;
    private:
        constexpr static inline size_type base_size {4};
    private:
        pointer first;
        pointer cursor_front;
        pointer cursor_back;
        pointer last;
    private:
        [[nodiscard]]
        static pointer allocate(size_type size = stack::base_size) {
            return reinterpret_cast<pointer>(alloc_traits::operator new(size * sizeof(value_type)));
        }
    private:
        void full() {
            if(this->cursor_front == this->cursor_back) {
                this->reallocate(this->capacity() * 2, *this);
            }
        }
        void reallocate(size_type size, const stack &rhs) {
            auto new_first {this->allocate(size)};
            auto new_cursor_front {new_first};
            auto new_last {new_first + static_cast<difference_type>(size)};
            auto new_cursor_back {new_last - static_cast<difference_type>(rhs.size_back())};
            __dsa::construct_ranges<alloc_traits, value_type, pointer &>(
                    new_first, {}, new_cursor_front, rhs.first, rhs.cursor_front);
            __dsa::construct_ranges<alloc_traits, value_type, pointer, true>(
                    new_first, new_cursor_front, new_cursor_back, rhs.cursor_back, rhs.last);
            if constexpr(not is_trivially_destructible<value_type>::value) {
                alloc_traits::destroy(this->first, this->cursor_front);
                alloc_traits::destroy(this->cursor_back + 1, this->last);
            }
            alloc_traits::operator delete(this->first);
            this->first = new_first;
            this->cursor_front = new_cursor_front;
            this->cursor_back = new_cursor_back - 1;
            this->last = new_last;
        }
    public:
        stack() : first {this->allocate()}, cursor_front {this->first},
                cursor_back {this->first + static_cast<difference_type>(this->base_size - 1)},
                last {this->first + static_cast<difference_type>(this->base_size)} {}
        stack(const stack &rhs) : first {this->allocate(rhs.capacity())}, cursor_front {this->first},
                cursor_back {this->first + static_cast<difference_type>(rhs.capacity() - rhs.size_back())},
                last {this->first + static_cast<difference_type>(rhs.capacity())} {
            __dsa::construct_ranges<alloc_traits, value_type, pointer &>(
                    this->first, {}, this->cursor, rhs.first, rhs.cursor_front);
            __dsa::construct_ranges<alloc_traits, value_type, pointer, true>(
                    this->first, this->cursor_front, this->cursor_back, rhs.cursor_back, rhs.last);
            --this->cursor_back;
        }
        stack(stack &&rhs) noexcept : first {rhs.first}, cursor_front {rhs.cursor_front},
                cursor_back {rhs.cursor_back}, last {rhs.last} {
            rhs.first = rhs.cursor_front = rhs.cursor_back = rhs.last = nullptr;
        }
        ~stack() noexcept {
            if constexpr(not is_trivially_destructible<value_type>::value) {
                alloc_traits::destroy(this->first, this->cursor_front);
                alloc_traits::destroy(this->cursor_back + 1, this->last);
            }
            alloc_traits::operator delete(this->first);
        }
    public:
        stack &operator=(const stack &rhs) {
            if(&rhs == this) {
                return *this;
            }
            this->reallocate(rhs.capacity(), rhs);
            return *this;
        }
        stack &operator=(stack &&rhs) noexcept {
            if(&rhs == this) {
                return *this;
            }
            this->~stack();
            this->first = rhs.first;
            this->cursor_front = rhs.cursor_front;
            this->cursor_back = rhs.cursor_back;
            this->last = rhs.last;
            rhs.first = rhs.cursor_front = rhs.cursor_back = rhs.last = nullptr;
        }
    public:
        [[nodiscard]]
        reference top_front() noexcept {
            return *(this->cursor_front - 1);
        }
        [[nodiscard]]
        const_reference top_front() const noexcept {
            return *(this->cursor_front - 1);
        }
        [[nodiscard]]
        reference top_back() noexcept {
            return *(this->cursor_back + 1);
        }
        [[nodiscard]]
        const_reference top_back() const noexcept {
            return *(this->cursor_back + 1);
        }
        [[nodiscard]]
        bool empty_front() const noexcept {
            return this->first == this->cursor_front;
        }
        [[nodiscard]]
        bool empty_back() const noexcept {
            return this->cursor_back + 1 == this->last;
        }
        [[nodiscard]]
        bool empty() const noexcept {
            return this->empty_front() and this->empty_back();
        }
        [[nodiscard]]
        size_type size_front() const noexcept {
            return this->cursor_front - this->first;
        }
        [[nodiscard]]
        size_type size_back() const noexcept {
            return this->last - this->cursor_back - 1;
        }
        [[nodiscard]]
        size_type size() const noexcept {
            return this->size_front() + this->size_back();
        }
        [[nodiscard]]
        size_type capacity() const noexcept {
            return this->last - this->first;
        }
        [[nodiscard]]
        size_type spare() const noexcept {
            return this->cursor_back - this->cursor_front - 1;
        }
        [[nodiscard]]
        constexpr size_type max_size_front() const noexcept {
            return this->max_size() / 2;
        }
        [[nodiscard]]
        constexpr size_type max_size_back() const noexcept {
            return this->max_size() / 2;
        }
        [[nodiscard]]
        constexpr size_type max_size() const noexcept {
            return std::numeric_limits<size_type>::max() / sizeof(value_type);
        }
        void push_front(const_reference value) {
            this->full();
            alloc_traits::construct(this->cursor_front, value);
            ++this->cursor_front;
        }
        void push_front(rvalue_reference value) {
            this->full();
            alloc_traits::construct(this->cursor_front, ds::move(value));
            ++this->cursor_front;
        }
        void push_back(const_reference value) {
            this->full();
            alloc_traits::construct(this->cursor_back, value);
            --this->cursor_back;
        }
        void push_back(rvalue_reference value) {
            this->full();
            alloc_traits::construct(this->cursor_back, ds::move(value));
            --this->cursor_back;
        }
        void push(const_reference value) {
            this->push_back(value);
            this->push_front(value);
        }
        void push(rvalue_reference value) {
            this->push_back(value);
            this->push_front(ds::move(value));
        }
        template <typename ...Args>
        void emplace_front(Args &&...args) {
            this->push_front(value_type(ds::forward<Args>(args)...));
        }
        template <typename ...Args>
        void emplace_back(Args &&...args) {
            this->push_back(value_type(ds::forward<Args>(args)...));
        }
        template <typename ...Args>
        void emplace(Args &&...args) {
            this->emplace_front(ds::forward<Args>(args)...);
            this->emplace_back(ds::forward<Args>(args)...);
        }
        void pop_front() noexcept {
            if(this->empty_front()) {
                return;
            }
            --this->cursor_front;
            if constexpr(not is_trivially_destructible<value_type>::value) {
                alloc_traits::destroy(this->cursor_front);
            }
        }
        void pop_back() noexcept {
            if(this->empty_back()) {
                return;
            }
            ++this->cursor_back;
            if constexpr(not is_trivially_destructible<value_type>::value) {
                alloc_traits::destroy(this->cursor_back);
            }
        }
        void pop() noexcept {
            this->pop_front();
            this->pop_back();
        }
        void swap(stack &rhs) noexcept {
            ds::swap(this->first, rhs.first);
            ds::swap(this->cursor_front, rhs.cursor_front);
            ds::swap(this->cursor_back, rhs.cursor_back);
            ds::swap(this->last, rhs.last);
        }
    };

    template <typename T>
    inline void swap(const stack<T, T *, true> &lhs, const stack<T, T *, true> &rhs) noexcept {
        lhs.swap(rhs);
    }
    template <typename T>
    bool operator==(const stack<T, T *, true> &lhs, const stack<T, T *, true> &rhs) {
        if(lhs.size_front() not_eq rhs.size_front() or lhs.size_back() not_eq rhs.size_back()) {
            return false;
        }
        auto lhs_cursor {lhs.first}, rhs_cursor {rhs.first};
        for(; lhs_cursor not_eq lhs.cursor_front; ++lhs_cursor, static_cast<void>(++rhs_cursor)) {
            if(not(*lhs_cursor == *rhs_cursor)) {
                return false;
            }
        }
        lhs_cursor = lhs.last - 1, static_cast<void>(rhs_cursor = rhs.last - 1);
        for(; lhs_cursor not_eq lhs.cursor_back; --lhs_cursor, static_cast<void>(--rhs_cursor)) {
            if(not(*lhs_cursor == *rhs_cursor)) {
                return false;
            }
        }
        return true;
    }
    template <typename T>
    bool operator!=(const stack<T, T *, true> &lhs, const stack<T, T *, true> &rhs) {
        return not(lhs == rhs);
    }
    template <typename T>
    bool operator<(const stack<T, T *, true> &lhs, const stack<T, T *, true> &rhs) {
        auto lhs_cursor {lhs.first}, rhs_cursor {rhs.first};
        for(; rhs_cursor not_eq rhs.cursor_front; ++lhs_cursor, static_cast<void>(++rhs_cursor)) {
            if(lhs_cursor == lhs.cursor_front or *lhs_cursor < *rhs_cursor) {
                break;
            }
            if(*rhs_cursor < *lhs_cursor) {
                return false;
            }
        }
        lhs_cursor = lhs.last - 1, static_cast<void>(rhs_cursor = rhs.last - 1);
        for(; rhs_cursor not_eq rhs.cursor_back; --lhs_cursor, static_cast<void>(--rhs_cursor)) {
            if(lhs_cursor == lhs.cursor_back or *lhs_cursor < *rhs_cursor) {
                return true;
            }
            if(*rhs_cursor < *lhs_cursor) {
                return false;
            }
        }
        return false;
    }
    template <typename T>
    inline bool operator<=(const stack<T, T *, true> &lhs, const stack<T, T *, true> &rhs) {
        return not(rhs < lhs);
    }
    template <typename T>
    inline bool operator>(const stack<T, T *, true> &lhs, const stack<T, T *, true> &rhs) {
        return rhs < lhs;
    }
    template <typename T>
    inline bool operator>=(const stack<T, T *, true> &lhs, const stack<T, T *, true> &rhs) {
        return not(lhs < rhs);
    }
}

#endif //DATA_STRUCTURE_STACK_HPP
