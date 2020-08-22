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

#ifndef DATA_STRUCTURE_QUEUE_HPP
#define DATA_STRUCTURE_QUEUE_HPP

#include "deque.hpp"

namespace data_structure {
    template <typename T, typename Container = deque<T>,
            bool Circular = is_pointer<Container>::value, bool Tag = false>
    class queue;
}

namespace data_structure {
    template <typename T, typename Container>
    class queue<T, Container, false, false> final {
        template <typename Type, typename ContainerType>
        friend bool operator==(const queue<Type, ContainerType, false, false> &,
                const queue<Type, ContainerType, false, false> &);
        template <typename Type, typename ContainerType>
        friend bool operator<(const queue<Type, ContainerType, false, false> &,
                const queue<Type, ContainerType, false, false> &);
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
        constexpr queue() noexcept(is_nothrow_default_constructible<container_type>::value) = default;
        explicit queue(const container_type &c) : c {c} {}
        explicit queue(container_type &&c) noexcept : c {ds::move(c)} {}
        queue(const queue &) = default;
        queue(queue &&) noexcept = default;
        ~queue() noexcept = default;
    public:
        queue &operator=(const queue &) = default;
        queue &operator=(queue &&) noexcept = default;
        queue &operator=(const container_type &rhs) {
            this->c = rhs;
            return *this;
        }
        queue &operator=(container_type &&rhs) noexcept {
            this->c = ds::move(rhs);
            return *this;
        }
    public:
        [[nodiscard]]
        reference front() noexcept {
            return this->c.front();
        }
        [[nodiscard]]
        const_reference front() const noexcept {
            return this->c.front();
        }
        [[nodiscard]]
        reference back() noexcept {
            return this->c.back();
        }
        [[nodiscard]]
        const_reference back() const noexcept {
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
            this->c.pop_front();
        }
        void swap(queue &rhs) noexcept {
            this->c.swap(rhs.c);
        }
    };


    template <typename T, typename Container>
    inline bool operator==(const queue<T, Container, false, false> &lhs,
            const queue<T, Container, false, false> &rhs) {
        return lhs.c == rhs.c;
    }
    template <typename T, typename Container>
    inline bool operator!=(const queue<T, Container, false, false> &lhs,
            const queue<T, Container, false, false> &rhs) {
        return not(lhs == rhs);
    }
    template <typename T, typename Container>
    inline bool operator<(const queue<T, Container, false, false> &lhs,
            const queue<T, Container, false, false> &rhs) {
        return lhs < rhs;
    }
    template <typename T, typename Container>
    inline bool operator<=(const queue<T, Container, false, false> &lhs,
            const queue<T, Container, false, false> &rhs) {
        return not(rhs < lhs);
    }
    template <typename T, typename Container>
    inline bool operator>(const queue<T, Container, false, false> &lhs,
            const queue<T, Container, false, false> &rhs) {
        return rhs < lhs;
    }
    template <typename T, typename Container>
    inline bool operator>=(const queue<T, Container, false, false> &lhs,
            const queue<T, Container, false, false> &rhs) {
        return not(lhs < rhs);
    }
}

namespace data_structure {
    template <typename T>
    class queue<T, T *, false, false> final {
        template <typename Type>
        friend bool operator==(const queue<Type, Type *, false, false> &,
                const queue<Type, Type *, false, false> &);
        template <typename Type>
        friend bool operator<(const queue<Type, Type *, false, false> &,
                const queue<Type, Type *, false, false> &);
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
        static pointer allocate(size_type size = queue::base_size) {
            return reinterpret_cast<pointer>(alloc_traits::operator new(size * sizeof(value_type)));
        }
    private:
        void full() {
            if(this->cursor == this->last) {
                this->reallocate(this->capacity() * 2, *this);
            }
        }
        void reallocate(size_type size, const queue &rhs) {
            auto first {this->allocate(size)};
            auto cursor {first};
            __dsa::construct_ranges<alloc_traits, value_type, pointer &>(
                    first, {}, cursor, rhs.first, rhs.cursor);
            if constexpr(not is_trivially_destructible<value_type>::value) {
                alloc_traits::destroy(this->first, this->cursor);
            }
            alloc_traits::operator delete(this->first);
            this->first = first;
            this->cursor = cursor;
            this->last = this->first + static_cast<difference_type>(size);
        }
    public:
        queue() : first {this->allocate()}, cursor {this->first},
                last {this->first + static_cast<difference_type>(this->base_size)} {}
        queue(const queue &rhs) : first {this->allocate(rhs.capacity())}, cursor {this->first},
                last {this->first + static_cast<difference_type>(rhs.capacity())} {
            __dsa::construct_ranges<alloc_traits, value_type, pointer &>(
                    this->first, {}, this->cursor, rhs.first, rhs.cursor);
        }
        queue(queue &&rhs) noexcept : first {rhs.first}, cursor {rhs.cursor}, last {rhs.last} {
            rhs.first = rhs.cursor = rhs.last = nullptr;
        }
        ~queue() noexcept {
            if constexpr(not is_trivially_destructible<value_type>::value) {
                alloc_traits::destroy(this->first, this->cursor);
            }
            alloc_traits::operator delete(this->first);
        }
    public:
        queue &operator=(const queue &rhs) {
            if(&rhs == this) {
                return *this;
            }
            this->reallocate(rhs.capacity(), rhs);
            return *this;
        }
        queue &operator=(queue &&rhs) noexcept {
            if(&rhs == this) {
                return *this;
            }
            this->~queue();
            this->first = rhs.first;
            this->cursor = rhs.cursor;
            this->last = rhs.last;
            rhs.first = rhs.cursor = rhs.last = nullptr;
            return *this;
        }
    public:
        [[nodiscard]]
        reference front() noexcept {
            return *this->first;
        }
        [[nodiscard]]
        const_reference front() const noexcept {
            return *this->first;
        }
        [[nodiscard]]
        reference back() noexcept {
            return *(this->cursor - 1);
        }
        [[nodiscard]]
        const_reference back() const noexcept {
            return *(this->cursor - 1);
        }
        [[nodiscard]]
        bool empty() const noexcept {
            return this->first == this->cursor;
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
        size_type size() const noexcept {
            return this->cursor - this->first;
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
        void pop() {
            if(this->empty()) {
                return;
            }
            this->cursor = ds::copy(this->first + 1, this->cursor, this->first);
            if constexpr(not is_trivially_destructible<value_type>::value) {
                alloc_traits::destroy(this->cursor + 1);
            }
        }
        void swap(queue &rhs) noexcept {
            ds::swap(this->first, rhs.first);
            ds::swap(this->cursor, rhs.cursor);
            ds::swap(this->last, rhs.last);
        }
    };

    template <typename T>
    bool operator==(const queue<T, T *, false, false> &lhs, const queue<T, T *, false, false> &rhs) {
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
    inline bool operator!=(const queue<T, T *, false, false> &lhs, const queue<T, T *, false, false> &rhs) {
        return not(lhs == rhs);
    }
    template <typename T>
    bool operator<(const queue<T, T *, false, false> &lhs, const queue<T, T *, false, false> &rhs) {
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
    inline bool operator<=(const queue<T, T *, false, false> &lhs, const queue<T, T *, false, false> &rhs) {
        return not(rhs < lhs);
    }
    template <typename T>
    inline bool operator>(const queue<T, T *, false, false> &lhs, const queue<T, T *, false, false> &rhs) {
        return rhs < lhs;
    }
    template <typename T>
    inline bool operator>=(const queue<T, T *, false, false> &lhs, const queue<T, T *, false, false> &rhs) {
        return not(lhs < rhs);
    }
}

namespace data_structure {
    template <typename T>
    class queue<T, T *, true, false> final {
        template <typename Type, bool Tag>
        friend bool operator==(const queue<Type, Type *, true, Tag> &,
                const queue<Type, Type *, true, Tag> &);
        template <typename Type, bool Tag>
        friend bool operator<(const queue<Type, Type *, true, Tag> &,
                const queue<Type, Type *, true, Tag> &);
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
        pointer front_cursor;
        pointer back_cursor;
        pointer last;
    private:
        [[nodiscard]]
        static pointer allocate(size_type size = queue::base_size) {
            return reinterpret_cast<pointer>(alloc_traits::operator new(size * sizeof(value_type)));
        }
    private:
        void full() {
            if(this->front_cursor == this->back_cursor) {
                this->reallocate(this->capacity() * 2, *this);
            }
        }
        void reallocate(size_type size, const queue & rhs) {
            auto first {this->allocate(size)};
            auto cursor {first + 1};
            if(rhs.back_cursor - rhs.front_cursor > 0) {
                __dsa::construct_ranges<alloc_traits, value_type, pointer &, false, true>(
                        cursor, {}, cursor, rhs.front_cursor + 1, rhs.back_cursor);
            }else {
                __dsa::construct_ranges<alloc_traits, value_type, pointer &, false, true>(
                        cursor, {}, cursor, rhs.front_cursor + 1, rhs.last);
                __dsa::construct_ranges<alloc_traits, value_type, pointer &, false, true>(
                        cursor, {}, cursor, rhs.first, rhs.back_cursor);
            }
            if constexpr(not is_trivially_destructible<value_type>::value) {
                if(this->back_cursor - this->front_cursor > 0) {
                    alloc_traits::destroy(this->front_cursor + 1, this->back_cursor);
                }else {
                    alloc_traits::destroy(this->front_cursor + 1, this->last);
                    alloc_traits::destroy(this->first, this->back_cursor);
                }
            }
            alloc_traits::operator delete(this->first);
            this->first = first;
            this->front_cursor = this->first;
            this->back_cursor = cursor;
            this->last = this->first + static_cast<difference_type>(size);
        }
        [[nodiscard]]
        pointer advance(pointer ptr) noexcept {
            const auto advanced {ptr + 1};
            return advanced != this->last ? advanced : this->first;
        }
        [[nodiscard]]
        const_pointer advance(const_pointer ptr) const noexcept {
            return this->advance(const_cast<pointer>(ptr));
        }
        [[nodiscard]]
        pointer decline(pointer ptr) noexcept {
            const auto declined {ptr - 1};
            return declined != this->first - 1 ? declined : this->last - 1;
        }
        [[nodiscard]]
        const_pointer decline(const_pointer ptr) const noexcept {
            return this->decline(const_cast<pointer>(ptr));
        }
    public:
        queue() : first {this->allocate(this->base_size)},
                front_cursor {this->first}, back_cursor {this->first + 1},
                last {this->first + static_cast<difference_type>(this->base_size)} {}
        queue(const queue &rhs) : first {this->allocate(rhs.capacity())},
                front_cursor {this->first}, back_cursor {this->first + 1},
                last {this->first + static_cast<difference_type>(rhs.capacity())} {
            if(rhs.back_cursor - rhs.front_cursor > 0) {
                __dsa::construct_ranges<alloc_traits, value_type, pointer &, false, true>(
                        this->back_cursor, {}, this->back_cursor, rhs.front_cursor + 1, rhs.back_cursor);
            }else {
                __dsa::construct_ranges<alloc_traits, value_type, pointer &, false, true>(
                        this->back_cursor, {}, this->back_cursor, rhs.front_cursor + 1, rhs.last);
                __dsa::construct_ranges<alloc_traits, value_type, pointer &, false, true>(
                        this->back_cursor, {}, this->back_cursor, rhs.first, rhs.back_cursor);
            }
        }
        queue(queue &&rhs) noexcept : first {rhs.first}, front_cursor {rhs.front_cursor},
                back_cursor {rhs.back_cursor}, last {rhs.last} {
            rhs.first = rhs.front_cursor = rhs.back_cursor = rhs.last = nullptr;
        }
        ~queue() noexcept {
            if constexpr(not is_trivially_destructible<value_type>::value) {
                if(this->back_cursor - this->front_cursor > 0) {
                    alloc_traits::destroy(this->front_cursor, this->back_cursor);
                }else {
                    alloc_traits::destroy(this->front_cursor, this->last);
                    alloc_traits::destroy(this->first, this->back_cursor);
                }
            }
            alloc_traits::operator delete(this->first);
        }
    public:
        queue &operator=(const queue &rhs) {
            if(&rhs not_eq this) {
                this->reallocate(rhs.capacity(), rhs);
            }
            return *this;
        }
        queue &operator=(queue &&rhs) noexcept {
            if(&rhs not_eq this) {
                this->~queue();
                this->first = rhs.first;
                this->front_cursor = rhs.front_cursor;
                this->back_cursor = rhs.back_cursor;
                this->last = rhs.last;
                rhs.first = rhs.front_cursor = rhs.back_cursor = rhs.last = nullptr;
            }
            return *this;
        }
    public:
        [[nodiscard]]
        reference front() noexcept {
            return *this->advance(this->first);
        }
        [[nodiscard]]
        const_reference front() const noexcept {
            return *this->advance(this->first);
        }
        [[nodiscard]]
        reference back() noexcept {
            return *this->decline(this->back_cursor);
        }
        [[nodiscard]]
        const_reference back() const noexcept {
            return *this->decline(this->back_cursor);
        }
        [[nodiscard]]
        bool empty() const noexcept {
            return this->advance(this->front_cursor) == this->back_cursor;
        }
        [[nodiscard]]
        size_type capacity() const noexcept {
            return this->last - this->first;
        }
        [[nodiscard]]
        size_type spare() const noexcept {
            return this->capacity() - this->size() - 1;
        }
        [[nodiscard]]
        size_type size() const noexcept {
            const auto offset {static_cast<size_type>(this->front_cursor - this->back_cursor - 1)};
            return offset > 0 ? offset : this->capacity() +offset;
        }
        [[nodiscard]]
        constexpr size_type max_size() const noexcept {
            return std::numeric_limits<size_type>::max() / sizeof(value_type);
        }
        void push(const_reference value) {
            this->full();
            auto next {this->advance(this->back_cursor)};
            alloc_traits::construct(this->back_cursor, value);
            this->back_cursor = next;
        }
        void push(rvalue_reference value) {
            this->full();
            auto next {this->advance(this->back_cursor)};
            alloc_traits::construct(this->back_cursor, ds::move(value));
            this->back_cursor = next;
        }
        template <typename ...Args>
        void emplace(Args &&...args) {
            this->push(value_type(ds::forward<Args>(args)...));
        }
        void pop() noexcept {
            if(this->empty()) {
                return;
            }
            this->first = this->advance(this->first);
            if constexpr(not is_trivially_destructible<value_type>::value) {
                alloc_traits::destroy(this->first);
            }
        }
        void swap(queue &rhs) noexcept {
            ds::swap(this->first, rhs.first);
            ds::swap(this->front_cursor, rhs.front_cursor);
            ds::swap(this->back_cursor, rhs.back_cursor);
            ds::swap(this->last, rhs.last);
        }
    };
}

namespace data_structure {
    template <typename T>
    class queue<T, T *, true, true> final {
        template <typename Type, bool Tag>
        friend bool operator==(const queue<Type, Type *, true, Tag> &,
                const queue<Type, Type *, true, Tag> &);
        template <typename Type, bool Tag>
        friend bool operator<(const queue<Type, Type *, true, Tag> &,
                const queue<Type, Type *, true, Tag> &);
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
        pointer front_cursor;
        pointer back_cursor;
        pointer last;
        bool is_full;
    private:
        [[nodiscard]]
        static pointer allocate(size_type size = queue::base_size) {
            return reinterpret_cast<pointer>(alloc_traits::operator new(size * sizeof(value_type)));
        }
    private:
        void full() {
            if(this->front_cursor == this->back_cursor and this->is_full) {
                this->reallocate(this->capacity() * 2, *this);
            }
        }
        void reallocate(size_type size, const queue &rhs) {
            auto first {this->allocate(size)};
            auto cursor {first};
            if(rhs.back_cursor - rhs.front_cursor > 0) {
                __dsa::construct_ranges<alloc_traits, value_type, pointer &>(
                        first, {}, cursor, rhs.front_cursor + 1, rhs.back_cursor);
            }else {
                __dsa::construct_ranges<alloc_traits, value_type, pointer &>(
                        first, {}, cursor, rhs.front_cursor + 1, rhs.last);
                __dsa::construct_ranges<alloc_traits, value_type, pointer &>(
                        first, {}, cursor, rhs.first, rhs.back_cursor);
            }
            this->first = first;
            this->front_cursor = this->first;
            this->back_cursor = cursor;
            this->last = this->first + static_cast<difference_type>(size);
            this->is_full = &rhs == this ? false : rhs.is_full;
        }
        [[nodiscard]]
        pointer advance(pointer ptr) noexcept {
            const auto advanced {ptr + 1};
            return advanced != this->last ? advanced : this->first;
        }
        [[nodiscard]]
        const_pointer advance(const_pointer ptr) const noexcept {
            return this->advance(const_cast<pointer>(ptr));
        }
        [[nodiscard]]
        pointer decline(pointer ptr) noexcept {
            const auto declined {ptr - 1};
            return declined != this->first - 1 ? declined : this->last - 1;
        }
        [[nodiscard]]
        const_pointer decline(const_pointer ptr) const noexcept {
            return this->decline(const_cast<pointer>(ptr));
        }
    public:
        queue() : first {this->allocate(this->base_size)},
                  front_cursor {this->first}, back_cursor {this->first},
                  last {this->first + static_cast<difference_type>(this->base_size)}, is_full {false} {}
        queue(const queue &rhs) : first {this->allocate(rhs.capacity())},
                front_cursor {this->first}, back_cursor {this->first + 1},
                last {this->first + static_cast<difference_type>(rhs.capacity())}, is_full {rhs.is_full} {
            if(rhs.back_cursor - rhs.front_cursor > 0) {
                __dsa::construct_ranges<alloc_traits, value_type, pointer &>(
                        this->first, {}, this->back_cursor, rhs.front_cursor + 1, rhs.back_cursor);
            }else {
                __dsa::construct_ranges<alloc_traits, value_type, pointer &>(
                        this->first, {}, this->back_cursor, rhs.front_cursor + 1, rhs.last);
                __dsa::construct_ranges<alloc_traits, value_type, pointer &>(
                        this->first, {}, this->back_cursor, rhs.first, rhs.back_cursor);
            }
        }
        queue(queue &&rhs) noexcept : first {rhs.first}, front_cursor {rhs.front_cursor},
                                      back_cursor {rhs.back_cursor}, last {rhs.last},
                                      is_full {rhs.is_full} {
            rhs.first = rhs.front_cursor = rhs.back_cursor = rhs.last = nullptr;
        }
        ~queue() noexcept {
            if constexpr(not is_trivially_destructible<value_type>::value) {
                if(this->back_cursor - this->front_cursor > 0) {
                    alloc_traits::destroy(this->front_cursor, this->back_cursor);
                }else {
                    alloc_traits::destroy(this->front_cursor, this->last);
                    alloc_traits::destroy(this->first, this->back_cursor);
                }
            }
            alloc_traits::operator delete(this->first);
        }
    public:
        queue &operator=(const queue &rhs) {
            if(&rhs not_eq this) {
                this->reallocate(rhs.capacity(), rhs);
            }
            return *this;
        }
        queue &operator=(queue &&rhs) noexcept {
            if(&rhs not_eq this) {
                this->~queue();
                this->first = rhs.first;
                this->front_cursor = rhs.front_cursor;
                this->back_cursor = rhs.back_cursor;
                this->last = rhs.last;
                this->is_full = rhs.is_full;
                rhs.first = rhs.front_cursor = rhs.back_cursor = rhs.last = nullptr;
            }
            return *this;
        }
    public:
        [[nodiscard]]
        reference front() noexcept {
            return *this->first;
        }
        [[nodiscard]]
        const_reference front() const noexcept {
            return *this->first;
        }
        [[nodiscard]]
        reference back() noexcept {
            return *this->decline(this->back_cursor);
        }
        [[nodiscard]]
        const_reference back() const noexcept {
            return *this->decline(this->back_cursor);
        }
        [[nodiscard]]
        bool empty() const noexcept {
            return this->front_cursor == this->back_cursor and not this->is_full;
        }
        [[nodiscard]]
        size_type capacity() const noexcept {
            return this->last - this->first;
        }
        [[nodiscard]]
        size_type spare() const noexcept {
            return this->capacity() - this->size();
        }
        [[nodiscard]]
        size_type size() const noexcept {
            const auto offset {static_cast<size_type>(this->front_cursor - this->back_cursor)};
            return this->full ? this->capacity() : (offset > 0 ? offset : this->capacity() + offset);
        }
        [[nodiscard]]
        constexpr size_type max_size() const noexcept {
            return std::numeric_limits<size_type>::max() / sizeof(value_type);
        }
        void push(const_reference value) {
            this->full();
            auto next {this->advance(this->back_cursor)};
            alloc_traits::construct(this->back_cursor, value);
            this->back_cursor = next;
        }
        void push(rvalue_reference value) {
            this->full();
            auto next {this->advance(this->back_cursor)};
            alloc_traits::construct(this->back_cursor, ds::move(value));
            this->back_cursor = next;
        }
        template <typename ...Args>
        void emplace(Args &&...args) {
            this->push(value_type(ds::forward<Args>(args)...));
        }
        void pop() noexcept {
            if(this->empty()) {
                return;
            }
            if constexpr(not is_trivially_destructible<value_type>::value) {
                alloc_traits::destroy(this->first);
            }
            ++this->first;
            if(this->is_full) {
                this->is_full = false;
            }
        }
        void swap(queue &rhs) noexcept {
            ds::swap(this->first, rhs.first);
            ds::swap(this->front_cursor, rhs.front_cursor);
            ds::swap(this->back_cursor, rhs.back_cursor);
            ds::swap(this->last, rhs.last);
            ds::swap(this->is_full, rhs.is_full);
        }
    };

    template <typename T, typename Container, bool Circular, bool Tag>
    inline void swap(const queue<T, Container, Circular, Tag> &lhs,
            const queue<T, Container, Circular, Tag> &rhs) noexcept {
        lhs.swap(rhs);
    }
    template <typename T, bool Tag>
    bool operator==(const queue<T, T *, true, Tag> &lhs, const queue<T, T *, true, Tag> &rhs) {
        if(lhs.size() not_eq rhs.size()) {
            return false;
        }
        using queue_t = typename remove_const_reference<decltype(lhs)>::type;
        using pointer_t = typename queue_t::const_pointer;
        const auto advance {[](pointer_t &ptr, const queue_t &q) noexcept -> void {
            ptr = q.advance(ptr);
        }};
        if(lhs.back_cursor - lhs.front_cursor > 0) {
            if(rhs.back_cursor - rhs.front_cursor > 0) {
                for(auto lhs_cursor {lhs.front_cursor}, cursor {rhs.front_cursor};
                    lhs_cursor not_eq lhs.back_cursor; ++cursor, static_cast<void>(++lhs_cursor)) {
                    if(*lhs_cursor not_eq *cursor) {
                        return false;
                    }
                }
                return true;
            }else {
                for(auto lhs_cursor {lhs.front_cursor}, cursor {rhs.front_cursor};
                    lhs_cursor not_eq lhs.back_cursor; ++lhs_cursor, advance(cursor, rhs)) {
                    if(*lhs_cursor not_eq *cursor) {
                        return false;
                    }
                }
                return true;
            }
        }
        if(rhs.back_cursor - rhs.front_cursor > 0) {
            for(auto lhs_cursor {lhs.front_cursor}, cursor {rhs.front_cursor};
                lhs_cursor not_eq lhs.back_cursor; ++cursor, advance(lhs_cursor, lhs)) {
                if(*lhs_cursor not_eq *cursor) {
                    return false;
                }
            }
            return true;
        }
        for(auto lhs_cursor {lhs.front_cursor}, cursor {rhs.front_cursor};
            lhs_cursor not_eq lhs.back_cursor; advance(cursor, rhs), advance(lhs_cursor, lhs)) {
            if(*lhs_cursor not_eq *cursor) {
                return false;
            }
        }
        return true;
    }
    template <typename T, bool Tag>
    inline bool operator!=(const queue<T, T *, true, Tag> &lhs, const queue<T, T *, true, Tag> &rhs) {
        return not(lhs == rhs);
    }
    template <typename T, bool Tag>
    bool operator<(const queue<T, T *, true, Tag> &lhs, const queue<T, T *, true, Tag> &rhs) {
        using queue_t = typename remove_const_reference<decltype(lhs)>::type;
        using pointer_t = typename queue_t::const_pointer;
        const auto advance {[](pointer_t &ptr, const queue_t &q) noexcept -> void {
            ptr = q.advance(ptr);
        }};
        if(lhs.back_cursor - lhs.front_cursor > 0) {
            if(rhs.back_cursor - rhs.front_cursor > 0) {
                auto lhs_cursor {lhs.front_cursor}, rhs_cursor {rhs.front_cursor};
                const auto lhs_end {lhs.back_cursor}, rhs_end {rhs.back_cursor};
                for(; rhs_cursor not_eq rhs_end; ++lhs_cursor, static_cast<void>(++rhs_cursor)) {
                    if(lhs_cursor == lhs_end or *lhs_cursor < *rhs_cursor) {
                        return true;
                    }
                    if(*rhs_cursor < *lhs_cursor) {
                        return false;
                    }
                }
                return false;
            }else {
                auto lhs_cursor {lhs.front_cursor}, rhs_cursor {rhs.front_cursor};
                const auto lhs_end {lhs.back_cursor}, rhs_end {rhs.back_cursor};
                for(; rhs_cursor not_eq rhs_end; ++lhs_cursor, advance(rhs_cursor, rhs)) {
                    if(lhs_cursor == lhs_end or *lhs_cursor < *rhs_cursor) {
                        return true;
                    }
                    if(*rhs_cursor < *lhs_cursor) {
                        return false;
                    }
                }
                return false;
            }
        }
        if(rhs.back_cursor - rhs.front_cursor > 0) {
            auto lhs_cursor {lhs.front_cursor}, rhs_cursor {rhs.front_cursor};
            const auto lhs_end {lhs.back_cursor}, rhs_end {rhs.back_cursor};
            for(; rhs_cursor not_eq rhs_end; ++rhs_cursor, advance(lhs_cursor, lhs)) {
                if(lhs_cursor == lhs_end or *lhs_cursor < *rhs_cursor) {
                    return true;
                }
                if(*rhs_cursor < *lhs_cursor) {
                    return false;
                }
            }
            return false;
        }
        auto lhs_cursor {lhs.front_cursor}, rhs_cursor {rhs.front_cursor};
        const auto lhs_end {lhs.back_cursor}, rhs_end {rhs.back_cursor};
        for(; rhs_cursor not_eq rhs_end; advance(lhs_cursor, lhs), advance(rhs_cursor, rhs)) {
            if(lhs_cursor == lhs_end or *lhs_cursor < *rhs_cursor) {
                return true;
            }
            if(*rhs_cursor < *lhs_cursor) {
                return false;
            }
        }
        return false;
    }
    template <typename T, bool Tag>
    inline bool operator<=(const queue<T, T *, true, Tag> &lhs, const queue<T, T *, true, Tag> &rhs) {
        return not(rhs < lhs);
    }
    template <typename T, bool Tag>
    inline bool operator>(const queue<T, T *, true, Tag> &lhs, const queue<T, T *, true, Tag> &rhs) {
        return rhs < lhs;
    }
    template <typename T, bool Tag>
    inline bool operator>=(const queue<T, T *, true, Tag> &lhs, const queue<T, T *, true, Tag> &rhs) {
        return not(lhs < rhs);
    }
}

#endif //DATA_STRUCTURE_QUEUE_HPP
