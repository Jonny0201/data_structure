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

#ifndef DATA_STRUCTURE_LIST_HPP
#define DATA_STRUCTURE_LIST_HPP

#include "type_traits.hpp"
#include "allocator.hpp"

namespace data_structure {
    template <typename T, typename Allocator = allocator<type_holder<T>>>
    class list final {
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
        using iterator = list_iterator<__dsa::list_node<value_type>, false>;
        using const_iterator = list_iterator<__dsa::list_node<value_type>, true>;
        using reverse_iterator = list_reverse_iterator<__dsa::list_node<value_type>, false>;
        using const_reverse_iterator = list_reverse_iterator<__dsa::list_node<value_type>, true>;
    private:
        using alloc_traits = allocator_traits<allocator_type>;
        using node_value_type = __dsa::list_node<value_type>;
        using node_type = typename add_pointer<node_value_type>::type;
        static_assert(is_same<typename __dsa::node_type_traits<node_value_type>::value_type,
                value_type>::value, "The list holds different value_type!");
    private:
        node_type tail;
    private:
        static node_type allocate();
        static void destroy(pointer) noexcept;
        static void handle_exception_from_constructor(node_type) noexcept;
        static node_type allocate_from_constructor(size_type);
        static node_type allocate_from_constructor(size_type, const_reference);
        template <typename InputIterator>
        static node_type allocate_from_constructor(typename enable_if<
                is_input_iterator<InputIterator>::value and not is_forward_iterator<InputIterator>::value,
                InputIterator>::type, InputIterator);
        template <typename ForwardIterator>
        static node_type allocate_from_constructor(typename enable_if<
                is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type, ForwardIterator);
        static void handle_exception(node_type) noexcept;
        static node_type insert_auxiliary(size_type, const_reference, node_type, node_type);
        template <typename InputIterator>
        static node_type insert_auxiliary(typename enable_if<
                is_input_iterator<InputIterator>::value and not is_forward_iterator<InputIterator>::value,
                InputIterator>::type, InputIterator, node_type, node_type);
        template <typename ForwardIterator>
        static node_type insert_auxiliary(typename enable_if<is_forward_iterator<ForwardIterator>::value,
                ForwardIterator>::type, ForwardIterator, node_type, node_type);
    public:
        list();
        explicit list(size_type);
        list(size_type, const_reference);
        template <typename InputIterator>
        list(typename enable_if<
                is_input_iterator<InputIterator>::value and not is_forward_iterator<InputIterator>::value,
                InputIterator>::type, InputIterator);
        template <typename ForwardIterator>
        list(typename enable_if<
                is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type, ForwardIterator);
        list(std::initializer_list<value_type>);
        list(const list &);
        list(list &&) noexcept;
        template <typename AllocatorRHS>
        list(const list<value_type, AllocatorRHS> &);
        template <typename AllocatorRHS>
        list(list<value_type, AllocatorRHS> &&) noexcept;
        ~list() noexcept;
    public:
        list &operator=(const list &);
        list &operator=(list &&) noexcept;
        list &operator=(std::initializer_list<value_type>);
        template <typename AllocatorRHS>
        list &operator=(const list<value_type, AllocatorRHS> &);
        template <typename AllocatorRHS>
        list &operator=(list<value_type, AllocatorRHS> &&) noexcept;
    public:
        void assign(size_type, const_reference = {});
        template <typename InputIterator>
        void assign(typename enable_if<
                is_input_iterator<InputIterator>::value and not is_forward_iterator<InputIterator>::value,
                InputIterator>::type, InputIterator);
        template <typename ForwardIterator>
        void assign(typename enable_if<is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type,
                ForwardIterator);
        void assign(std::initializer_list<value_type>);
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
        reference front() noexcept;
        [[nodiscard]]
        const_reference front() const noexcept;
        [[nodiscard]]
        reference back() noexcept;
        [[nodiscard]]
        const_reference back() const noexcept;
        [[nodiscard]]
        bool empty() const noexcept;
        [[nodiscard]]
        size_type size() const noexcept;
        [[nodiscard]]
        constexpr size_type max_size() const noexcept;
        iterator insert(difference_type, const_reference, size_type = 1);
        iterator insert(const_iterator, const_reference, size_type = 1);
        iterator insert(difference_type, rvalue_reference);
        iterator insert(const_iterator, rvalue_reference);
        template <typename InputIterator>
        iterator insert(difference_type, typename enable_if<
                is_input_iterator<InputIterator>::value and not is_forward_iterator<InputIterator>::value,
                InputIterator>::type, InputIterator);
        template <typename InputIterator>
        iterator insert(const_iterator, typename enable_if<
                is_input_iterator<InputIterator>::value and not is_forward_iterator<InputIterator>::value,
                InputIterator>::type, InputIterator);
        template <typename ForwardIterator>
        iterator insert(difference_type, typename enable_if<is_forward_iterator<ForwardIterator>::value,
                ForwardIterator>::type, ForwardIterator);
        template <typename ForwardIterator>
        iterator insert(const_iterator, typename enable_if<is_forward_iterator<ForwardIterator>::value,
                ForwardIterator>::type, ForwardIterator);
        iterator insert(difference_type, std::initializer_list<value_type>);
        iterator insert(const_iterator, std::initializer_list<value_type>);
        iterator erase(difference_type, size_type = 1) noexcept;
        iterator erase(const_iterator, size_type = 1) noexcept;
        static iterator erase(const_iterator, const_iterator) noexcept;
        static iterator erase(const_iterator) noexcept;
        template <typename ...Args>
        iterator emplace(difference_type, Args &&...);
        template <typename ...Args>
        iterator emplace(const_iterator, Args &&...);
        template <typename ...Args>
        void emplace_front(Args &&...);
        template <typename ...Args>
        void emplace_back(Args &&...);
        void push_front(const_reference);
        void push_front(rvalue_reference);
        void push_back(const_reference);
        void push_back(rvalue_reference);
        void pop_front() noexcept;
        void pop_back() noexcept;
        void resize(size_type, const_reference = {});
        void swap(list &) noexcept;
        template <typename AllocatorRHS>
        void swap(list<value_type, AllocatorRHS> &) noexcept;
        void clear() noexcept;
    public:
        void splice(difference_type, list &);
        void splice(const_iterator, list &);
        void splice(difference_type, list &&);
        void splice(const_iterator, list &&);
        void splice(difference_type, list &, const_iterator);
        void splice(const_iterator, list &, const_iterator);
        void splice(difference_type, list &&, const_iterator);
        void splice(const_iterator, list &&, const_iterator);
        void splice(difference_type, list &, difference_type);
        void splice(const_iterator, list &, difference_type);
        void splice(difference_type, list &&, difference_type);
        void splice(const_iterator, list &&, difference_type);
        void splice(difference_type, list &, difference_type, size_type);
        void splice(const_iterator, list &, difference_type, size_type);
        void splice(difference_type, list &&, difference_type, size_type);
        void splice(const_iterator, list &&, difference_type, size_type);
        void splice(difference_type, list &, const_iterator, const_iterator);
        void splice(const_iterator, list &, const_iterator, const_iterator);
        void splice(difference_type, list &&, const_iterator, const_iterator);
        void splice(const_iterator, list &&, const_iterator, const_iterator);
        void splice(difference_type, list &, const_iterator, size_type);
        void splice(const_iterator, list &, const_iterator, size_type);
        void splice(difference_type, list &&, const_iterator, size_type);
        void splice(const_iterator, list &&, const_iterator, size_type);
        template <typename AllocatorRHS>
        void splice(difference_type, list<value_type, AllocatorRHS> &);
        template <typename AllocatorRHS>
        void splice(const_iterator, list<value_type, AllocatorRHS> &);
        template <typename AllocatorRHS>
        void splice(difference_type, list<value_type, AllocatorRHS> &&);
        template <typename AllocatorRHS>
        void splice(const_iterator, list<value_type, AllocatorRHS> &&);
        template <typename AllocatorRHS>
        void splice(difference_type, list<value_type, AllocatorRHS> &, const_iterator);
        template <typename AllocatorRHS>
        void splice(const_iterator, list<value_type, AllocatorRHS> &, const_iterator);
        template <typename AllocatorRHS>
        void splice(difference_type, list<value_type, AllocatorRHS> &&, const_iterator);
        template <typename AllocatorRHS>
        void splice(const_iterator, list<value_type, AllocatorRHS> &&, const_iterator);
        template <typename AllocatorRHS>
        void splice(difference_type, list<value_type, AllocatorRHS> &, difference_type);
        template <typename AllocatorRHS>
        void splice(const_iterator, list<value_type, AllocatorRHS> &, difference_type);
        template <typename AllocatorRHS>
        void splice(difference_type, list<value_type, AllocatorRHS> &&, difference_type);
        template <typename AllocatorRHS>
        void splice(const_iterator, list<value_type, AllocatorRHS> &&, difference_type);
        template <typename AllocatorRHS>
        void splice(difference_type, list<value_type, AllocatorRHS> &, difference_type, size_type);
        template <typename AllocatorRHS>
        void splice(const_iterator, list<value_type, AllocatorRHS> &, difference_type, size_type);
        template <typename AllocatorRHS>
        void splice(difference_type, list<value_type, AllocatorRHS> &&, difference_type, size_type);
        template <typename AllocatorRHS>
        void splice(const_iterator, list<value_type, AllocatorRHS> &&, difference_type, size_type);
        template <typename AllocatorRHS>
        void splice(difference_type, list<value_type, AllocatorRHS> &, const_iterator, const_iterator);
        template <typename AllocatorRHS>
        void splice(const_iterator, list<value_type, AllocatorRHS> &, const_iterator, const_iterator);
        template <typename AllocatorRHS>
        void splice(difference_type, list<value_type, AllocatorRHS> &&, const_iterator, const_iterator);
        template <typename AllocatorRHS>
        void splice(const_iterator, list<value_type, AllocatorRHS> &&, const_iterator, const_iterator);
        template <typename AllocatorRHS>
        void splice(difference_type, list<value_type, AllocatorRHS> &, const_iterator, size_type);
        template <typename AllocatorRHS>
        void splice(const_iterator, list<value_type, AllocatorRHS> &, const_iterator, size_type);
        template <typename AllocatorRHS>
        void splice(difference_type, list<value_type, AllocatorRHS> &&, const_iterator, size_type);
        template <typename AllocatorRHS>
        void splice(const_iterator, list<value_type, AllocatorRHS> &&, const_iterator, size_type);
        void remove(const_reference) noexcept(has_nothrow_equal_to_operator<value_type>::value);
        template <typename Predicate>
        void remove_if(Predicate) noexcept(has_nothrow_function_call_operator<value_type>::value);
        void unique() noexcept(has_nothrow_equal_to_operator<value_type>::value);
        template <typename BinaryPredicate>
        void unique(BinaryPredicate) noexcept(has_nothrow_function_call_operator<value_type>::value);
        void merge(list &);
        void merge(list &&);
        template <typename AllocatorRHS>
        void merge(list<value_type, AllocatorRHS> &);
        template <typename AllocatorRHS>
        void merge(list<value_type, AllocatorRHS> &&);
        template <typename Compare>
        void merge(list &, Compare);
        template <typename Compare>
        void merge(list &&, Compare);
        template <typename Compare, typename AllocatorRHS>
        void merge(list<value_type, AllocatorRHS> &, Compare);
        template <typename Compare, typename AllocatorRHS>
        void merge(list<value_type, AllocatorRHS> &&, Compare);
        void sort();
        template <typename Compare>
        void sort(Compare);
        void reverse() noexcept;
    };
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    void swap(list<T, AllocatorLHS> &, list<T, AllocatorRHS> &) noexcept;
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    bool operator==(const list<T, AllocatorLHS> &, const list<T, AllocatorRHS> &);
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    bool operator!=(const list<T, AllocatorLHS> &, const list<T, AllocatorRHS> &);
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    bool operator<(const list<T, AllocatorLHS> &, const list<T, AllocatorRHS> &);
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    bool operator<=(const list<T, AllocatorLHS> &, const list<T, AllocatorRHS> &);
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    bool operator>(const list<T, AllocatorLHS> &, const list<T, AllocatorRHS> &);
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    bool operator>=(const list<T, AllocatorLHS> &, const list<T, AllocatorRHS> &);
}

namespace data_structure {
    /* private functions */
    template <typename T, typename Allocator>
    inline typename list<T, Allocator>::node_type list<T, Allocator>::allocate() {
        return reinterpret_cast<node_type>(alloc_traits::operator new(sizeof(node_value_type)));
    }
    template <typename T, typename Allocator>
    inline void list<T, Allocator>::destroy(pointer p) noexcept {
        alloc_traits::destroy(p);
    }
    template <typename T, typename Allocator>
    void list<T, Allocator>::handle_exception_from_constructor(node_type begin) noexcept {
        auto cursor {begin->next};
        while(cursor not_eq begin) {
            auto backup {cursor};
            cursor = cursor->next;
            if constexpr(not is_trivially_destructible<value_type>::value) {
                list::destroy(ds::address_of(backup->value));
            }
            alloc_traits::operator delete(backup);
        }
        alloc_traits::operator delete(cursor);
    }
    template <typename T, typename Allocator>
    typename list<T, Allocator>::node_type list<T, Allocator>::allocate_from_constructor(size_type size) {
        auto first {list::allocate()};
        if(size == 0) {
            first->next = first;
            first->previous = first;
            return first;
        }
        auto cursor {first};
        do {
            try {
                cursor->next = list::allocate();
            }catch(...) {
                cursor->next = first;
                list::handle_exception_from_constructor(first);
                throw;
            }
            cursor->next->previous = cursor;
            cursor = cursor->next;
            if constexpr(is_nothrow_default_constructible<value_type>::value) {
                alloc_traits::construct(ds::address_of(cursor->value));
            }else {
                try {
                    alloc_traits::construct(ds::address_of(cursor->value));
                }catch(...) {
                    cursor->previous->next = first;
                    alloc_traits::operator delete(cursor);
                    list::handle_exception_from_constructor(first);
                    throw;
                }
            }
        }while(--size > 0);
        cursor->next = first;
        first->previous = cursor;
        return first;
    }
    template <typename T, typename Allocator>
    typename list<T, Allocator>::node_type list<T, Allocator>::allocate_from_constructor(
            size_type size, const_reference value) {
        auto first {list::allocate()};
        if(size == 0) {
            first->next = first;
            first->previous = first;
            return first;
        }
        auto cursor {first};
        do {
            try {
                cursor->next = list::allocate();
            }catch(...) {
                cursor->next = first;
                list::handle_exception_from_constructor(first);
                throw;
            }
            cursor->next->previous = cursor;
            cursor = cursor->next;
            if constexpr(is_nothrow_copy_constructible<value_type>::value) {
                alloc_traits::construct(ds::address_of(cursor->value), value);
            }else {
                try {
                    alloc_traits::construct(ds::address_of(cursor->value), value);
                }catch(...) {
                    cursor->previous->next = first;
                    alloc_traits::operator delete(cursor);
                    list::handle_exception_from_constructor(first);
                    throw;
                }
            }
        }while(--size > 0);
        cursor->next = first;
        first->previous = cursor;
        return first;
    }
    template <typename T, typename Allocator>
    template <typename InputIterator>
    typename list<T, Allocator>::node_type list<T, Allocator>::allocate_from_constructor(typename enable_if<
            is_input_iterator<InputIterator>::value and not is_forward_iterator<InputIterator>::value,
            InputIterator>::type begin, InputIterator end) {
        using iterator_value_type = typename iterator_traits<InputIterator>::rvalue_reference;
        auto first {list::allocate()};
        if(begin == end) {
            first->next = first;
            first->previous = first;
            return first;
        }
        auto cursor {first};
        do {
            try {
                cursor->next = list::allocate();
            }catch(...) {
                cursor->next = first;
                list::handle_exception_from_constructor(first);
                throw;
            }
            cursor->next->previous = cursor;
            cursor = cursor->next;
            if constexpr(is_nothrow_constructible<value_type, iterator_value_type>::value) {
                alloc_traits::construct(ds::address_of(cursor->value), move(*begin++));
            }else {
                try {
                    alloc_traits::construct(ds::address_of(cursor->value), move(*begin++));
                }catch(...) {
                    cursor->previous->next = first;
                    alloc_traits::operator delete(cursor);
                    list::handle_exception_from_constructor(first);
                    throw;
                }
            }
        }while(begin not_eq end);
        cursor->next = first;
        first->previous = cursor;
        return first;
    }
    template <typename T, typename Allocator>
    template <typename ForwardIterator>
    typename list<T, Allocator>::node_type list<T, Allocator>::allocate_from_constructor(typename enable_if<
            is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type begin, ForwardIterator end) {
        using iterator_value_type = typename iterator_traits<ForwardIterator>::reference;
        auto first {list::allocate()};
        if(begin == end) {
            first->next = first;
            first->previous = first;
            return first;
        }
        auto cursor {first};
        do {
            try {
                cursor->next = list::allocate();
            }catch(...) {
                cursor->next = first;
                list::handle_exception_from_constructor(first);
                throw;
            }
            cursor->next->previous = cursor;
            cursor = cursor->next;
            if constexpr(is_nothrow_constructible<value_type, iterator_value_type>::value) {
                alloc_traits::construct(ds::address_of(cursor->value), *begin++);
            }else {
                try {
                    alloc_traits::construct(ds::address_of(cursor->value), *begin++);
                }catch(...) {
                    cursor->previous->next = first;
                    alloc_traits::operator delete(cursor);
                    list::handle_exception_from_constructor(first);
                    throw;
                }
            }
        }while(begin not_eq end);
        cursor->next = first;
        first->previous = cursor;
        return first;
    }
    template <typename T, typename Allocator>
    void list<T, Allocator>::handle_exception(node_type begin) noexcept {
        while(begin->next) {
            auto backup {begin};
            begin = begin->next;
            if constexpr(not is_trivially_destructible<value_type>::value) {
                list::destroy(ds::address_of(backup->value));
            }
            alloc_traits::operator delete(backup);
        }
        alloc_traits::operator delete(begin);
    }
    template <typename T, typename Allocator>
    typename list<T, Allocator>::node_type list<T, Allocator>::insert_auxiliary(
            size_type size, const_reference value, node_type before, node_type next) {
        auto first {list::allocate()};
        auto cursor {first};
        while(true) {
            if constexpr(is_nothrow_copy_constructible<value_type>::value) {
                alloc_traits::construct(ds::address_of(cursor->value), value);
            }else {
                try {
                    alloc_traits::construct(ds::address_of(cursor->value), value);
                }catch(...) {
                    cursor->next = nullptr;
                    list::handle_exception(first);
                    throw;
                }
            }
            if(--size == 0) {
                break;
            }
            try {
                cursor->next = list::allocate();
            }catch(...) {
                cursor->next = nullptr;
                if(not is_trivially_destructible<value_type>::value) {
                    list::destroy(ds::address_of(cursor->value));
                }
                list::handle_exception(first);
                throw;
            }
            cursor->next->previous = cursor;
            cursor = cursor->next;
        }
        first->previous = before;
        before->next = first;
        cursor->next = next;
        next->previous = cursor;
        return first;
    }
    template <typename T, typename Allocator>
    template <typename InputIterator>
    typename list<T, Allocator>::node_type list<T, Allocator>::insert_auxiliary(typename enable_if<
            is_input_iterator<InputIterator>::value and not is_forward_iterator<InputIterator>::value,
            InputIterator>::type begin, InputIterator end, node_type before, node_type next) {
        using iterator_value_type = typename iterator_traits<InputIterator>::reference;
        auto first {list::allocate()};
        auto cursor {first};
        while(true) {
            if constexpr(is_nothrow_constructible<value_type, iterator_value_type>::value) {
                alloc_traits::construct(ds::address_of(cursor->value), ds::move(*begin++));
            }else {
                try {
                    alloc_traits::construct(ds::address_of(cursor->value), ds::move(*begin++));
                }catch(...) {
                    cursor->next = nullptr;
                    list::handle_exception(first);
                    throw;
                }
            }
            if(begin == end) {
                break;
            }
            try {
                cursor->next = list::allocate();
            }catch(...) {
                cursor->next = nullptr;
                if(not is_trivially_destructible<value_type>::value) {
                    list::destroy(ds::address_of(cursor->value));
                }
                list::handle_exception(first);
                throw;
            }
            cursor->next->previous = cursor;
            cursor = cursor->next;
        }
        first->previous = before;
        cursor->next = next;
        return first;
    }
    template <typename T, typename Allocator>
    template <typename ForwardIterator>
    typename list<T, Allocator>::node_type list<T, Allocator>::insert_auxiliary(typename enable_if<
            is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type begin,
            ForwardIterator end, node_type before, node_type next) {
        using iterator_value_type = typename iterator_traits<ForwardIterator>::reference;
        auto first {list::allocate()};
        auto cursor {first};
        while(true) {
            if constexpr(is_nothrow_constructible<value_type, iterator_value_type>::value) {
                alloc_traits::construct(ds::address_of(cursor->value), ds::move(*begin++));
            }else {
                try {
                    alloc_traits::construct(ds::address_of(cursor->value), ds::move(*begin++));
                }catch(...) {
                    cursor->next = nullptr;
                    list::handle_exception(first);
                    throw;
                }
            }
            if(begin == end) {
                break;
            }
            try {
                cursor->next = list::allocate();
            }catch(...) {
                cursor->next = nullptr;
                if(not is_trivially_destructible<value_type>::value) {
                    list::destroy(ds::address_of(cursor->value));
                }
                list::handle_exception(first);
                throw;
            }
            cursor->next->previous = cursor;
            cursor = cursor->next;
        }
        first->previous = before;
        cursor->next = next;
        return first;
    }

    /* public functions */
    template <typename T, typename Allocator>
    inline list<T, Allocator>::list() : tail {list::allocate_from_constructor(0)} {}
    template <typename T, typename Allocator>
    inline list<T, Allocator>::list(size_type size) : tail {list::allocate_from_constructor(size)} {}
    template <typename T, typename Allocator>
    inline list<T, Allocator>::list(size_type size, const_reference value) :
            tail {list::allocate_from_constructor(size, value)} {}
    template <typename T, typename Allocator>
    template <typename InputIterator>
    inline list<T, Allocator>::list(typename enable_if<
            is_input_iterator<InputIterator>::value and not is_forward_iterator<InputIterator>::value,
            InputIterator>::type begin, InputIterator end) : tail {list::allocate_from_constructor(begin, end)} {}
    template <typename T, typename Allocator>
    template <typename ForwardIterator>
    inline list<T, Allocator>::list(typename enable_if<
            is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type begin, ForwardIterator end) :
            tail {list::allocate_from_constructor(begin, end)} {}
    template <typename T, typename Allocator>
    inline list<T, Allocator>::list(initializer_list<value_type> init_list) :
            list(init_list.begin(), init_list.end()) {}
    template <typename T, typename Allocator>
    inline list<T, Allocator>::list(const list &rhs) : tail {allocate_from_constructor(rhs.cbegin(), rhs.cend())} {}
    template <typename T, typename Allocator>
    inline list<T, Allocator>::list(list &&rhs) noexcept : tail {rhs.tail} {
        rhs.tail = nullptr;
    }
    template <typename T, typename Allocator>
    template <typename AllocatorRHS>
    inline list<T, Allocator>::list(const list<T, AllocatorRHS> &rhs) :
            tail {allocate_from_constructor(rhs.cbegin(), rhs.cend())} {}
    template <typename T, typename Allocator>
    template <typename AllocatorRHS>
    inline list<T, Allocator>::list(list<T, AllocatorRHS> &&rhs) noexcept : tail {rhs.tail} {
        rhs.tail = nullptr;
    }
    template <typename T, typename Allocator>
    list<T, Allocator>::~list() noexcept {
        if(not this->tail) {
            return;
        }
        auto cursor {this->tail->next};
        while(cursor not_eq this->tail) {
            auto backup {cursor};
            cursor = cursor->next;
            if constexpr(not is_trivially_destructible<value_type>::value) {
                alloc_traits::destroy(ds::address_of(backup->value));
            }
            alloc_traits::operator delete(backup);
        }
        alloc_traits::operator delete(this->tail);
    }
    template <typename T, typename Allocator>
    list<T, Allocator> &list<T, Allocator>::operator=(const list &rhs) {
        if(&rhs not_eq this) {
            this->assign(rhs.cbegin(), rhs.cend());
        }
        return *this;
    }
    template <typename T, typename Allocator>
    list<T, Allocator> &list<T, Allocator>::operator=(list &&rhs) noexcept {
        if(&rhs not_eq this) {
            this->~list();
            this->tail = rhs.tail;
            rhs.tail = nullptr;
        }
        return *this;
    }
    template <typename T, typename Allocator>
    list<T, Allocator> &list<T, Allocator>::operator=(initializer_list<value_type> init_list) {
        this->assign(init_list.begin(), init_list.end());
        return *this;
    }
    template <typename T, typename Allocator>
    template <typename AllocatorRHS>
    list<T, Allocator> &list<T, Allocator>::operator=(const list<T, AllocatorRHS> &rhs) {
        this->assign(rhs.cbegin(), rhs.cend());
        return *this;
    }
    template <typename T, typename Allocator>
    template <typename AllocatorRHS>
    list<T, Allocator> &list<T, Allocator>::operator=(list<T, AllocatorRHS> &&rhs) noexcept {
        this->~list();
        this->tail = rhs.tail;
        rhs.tail = nullptr;
        return *this;
    }
    template <typename T, typename Allocator>
    void list<T, Allocator>::assign(size_type size, const_reference value) {
        if(size == 0) {
            return;
        }
        auto cursor {this->tail->next};
        while(size > 0 and cursor not_eq this->tail) {
            cursor->value = value;
            --size;
            cursor = cursor->next;
        }
        if(size > 0) {
            this->insert(const_iterator(cursor), value, size);
            return;
        }
        if(cursor not_eq this->tail) {
            this->erase(const_iterator(cursor), this->cend());
        }
    }
    template <typename T, typename Allocator>
    template <typename InputIterator>
    void list<T, Allocator>::assign(typename enable_if<
            is_input_iterator<InputIterator>::value and not is_forward_iterator<InputIterator>::value,
            InputIterator>::type begin, InputIterator end) {
        if(begin == end) {
            return;
        }
        auto cursor {this->tail->next};
        while(begin not_eq end and cursor not_eq this->tail) {
            cursor->value = ds::move(*begin++);
            cursor = cursor->next;
        }
        if(begin not_eq end) {
            this->insert(const_iterator(cursor), begin, end);
            return;
        }
        if(cursor not_eq this->tail) {
            this->erase(const_iterator(cursor), this->cend());
        }
    }
    template <typename T, typename Allocator>
    template <typename ForwardIterator>
    void list<T, Allocator>::assign(typename enable_if<
            is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type begin, ForwardIterator end) {
        if(begin == end) {
            return;
        }
        auto cursor {this->tail->next};
        while(begin not_eq end and cursor->next not_eq this->tail) {
            cursor->value = *begin++;
            cursor = cursor->next;
        }
        if(begin not_eq end) {
            this->insert(const_iterator(cursor), begin, end);
            return;
        }
        if(cursor not_eq this->tail) {
            this->erase(const_iterator(cursor), this->cend());
        }
    }
    template <typename T, typename Allocator>
    inline void list<T, Allocator>::assign(initializer_list<value_type> init_list) {
        this->assign(init_list.begin(), init_list.end());
    }
    template <typename T, typename Allocator>
    inline typename list<T, Allocator>::iterator list<T, Allocator>::begin() noexcept {
        return iterator(this->tail->next);
    }
    template <typename T, typename Allocator>
    inline typename list<T, Allocator>::const_iterator list<T, Allocator>::begin() const noexcept {
        return const_iterator(this->tail->next);
    }
    template <typename T, typename Allocator>
    inline typename list<T, Allocator>::iterator list<T, Allocator>::end() noexcept {
        return iterator(this->tail);
    }
    template <typename T, typename Allocator>
    inline typename list<T, Allocator>::const_iterator list<T, Allocator>::end() const noexcept {
        return const_iterator(this->tail);
    }
    template <typename T, typename Allocator>
    inline typename list<T, Allocator>::const_iterator list<T, Allocator>::cbegin() const noexcept {
        return const_iterator(this->tail->next);
    }
    template <typename T, typename Allocator>
    inline typename list<T, Allocator>::const_iterator list<T, Allocator>::cend() const noexcept {
        return const_iterator(this->tail);
    }
    template <typename T, typename Allocator>
    inline typename list<T, Allocator>::reverse_iterator list<T, Allocator>::rbegin() noexcept {
        return reverse_iterator(this->tail->previous);
    }
    template <typename T, typename Allocator>
    inline typename list<T, Allocator>::const_reverse_iterator list<T, Allocator>::rbegin() const noexcept {
        return const_reverse_iterator(this->tail->previous);
    }
    template <typename T, typename Allocator>
    inline typename list<T, Allocator>::reverse_iterator list<T, Allocator>::rend() noexcept {
        return reverse_iterator(this->tail);
    }
    template <typename T, typename Allocator>
    inline typename list<T, Allocator>::const_reverse_iterator list<T, Allocator>::rend() const noexcept {
        return const_reverse_iterator(this->tail);
    }
    template <typename T, typename Allocator>
    inline typename list<T, Allocator>::const_reverse_iterator list<T, Allocator>::crbegin() const noexcept {
        return const_reverse_iterator(this->tail->previous);
    }
    template <typename T, typename Allocator>
    inline typename list<T, Allocator>::const_reverse_iterator list<T, Allocator>::crend() const noexcept {
        return const_reverse_iterator(this->tail);
    }
    template <typename T, typename Allocator>
    inline typename list<T, Allocator>::reference list<T, Allocator>::front() noexcept {
        return this->tail->next->value;
    }
    template <typename T, typename Allocator>
    inline typename list<T, Allocator>::const_reference list<T, Allocator>::front() const noexcept {
        return this->tail->next->value;
    }
    template <typename T, typename Allocator>
    inline typename list<T, Allocator>::reference list<T, Allocator>::back() noexcept {
        return this->tail->previous->value;
    }
    template <typename T, typename Allocator>
    inline typename list<T, Allocator>::const_reference list<T, Allocator>::back() const noexcept {
        return this->tail->previous->value;
    }
    template <typename T, typename Allocator>
    inline bool list<T, Allocator>::empty() const noexcept {
        return this->tail->next == this->tail;
    }
    template <typename T, typename Allocator>
    typename list<T, Allocator>::size_type list<T, Allocator>::size() const noexcept {
        size_type size {};
        auto cursor {this->tail->next};
        while(cursor not_eq this->tail) {
            ++size;
            cursor = cursor->next;
        }
        return size;
    }
    template <typename T, typename Allocator>
    inline constexpr typename list<T, Allocator>::size_type list<T, Allocator>::max_size() const noexcept {
        return std::numeric_limits<size_type>::max() / sizeof(node_value_type);
    }
    template <typename T, typename Allocator>
    inline typename list<T, Allocator>::iterator list<T, Allocator>::insert(
            difference_type pos, const_reference value, size_type size) {
        if(size == 0) {
            return iterator(this->tail);
        }
        auto cursor {this->tail->next};
        while(pos > 0 and cursor not_eq this->tail) {
            cursor = cursor->next;
            --pos;
        }
        if(pos > 0) {
            return iterator(this->tail);
        }
        return iterator(list::insert_auxiliary(size, value, cursor->previous, cursor));
    }
    template <typename T, typename Allocator>
    inline typename list<T, Allocator>::iterator list<T, Allocator>::insert(
            const_iterator pos, const_reference value, size_type size) {
        if(size == 0) {
            return iterator(this->tail);
        }
        return iterator(list::insert_auxiliary(size, value, pos.node->previous, pos.node));
    }
    template <typename T, typename Allocator>
    typename list<T, Allocator>::iterator list<T, Allocator>::insert(difference_type pos, rvalue_reference value) {
        auto cursor {this->tail->next};
        while(pos > 0 and cursor not_eq this->tail) {
            cursor = cursor->next;
            --pos;
        }
        if(pos > 0) {
            return iterator(this->tail);
        }
        auto new_node {list::allocate()};
        if constexpr(is_nothrow_move_constructible<value_type>::value or
                (not is_move_constructible<value_type>::value and is_nothrow_copy_constructible<value_type>::value)) {
            alloc_traits::construct(ds::address_of(new_node->value), move(value));
        }else {
            try {
                alloc_traits::construct(ds::address_of(new_node->value), move(value));
            }catch(...) {
                alloc_traits::operator delete(new_node);
                throw;
            }
        }
        new_node->next = cursor->next;
        cursor->next->previous = new_node;
        cursor->next = new_node;
        new_node->previous = cursor;
        return iterator(new_node);
    }
    template <typename T, typename Allocator>
    typename list<T, Allocator>::iterator list<T, Allocator>::insert(const_iterator pos, rvalue_reference value) {
        auto new_node {list::allocate()};
        if constexpr(is_nothrow_move_constructible<value_type>::value or
                (not is_move_constructible<value_type>::value and is_nothrow_copy_constructible<value_type>::value)) {
            alloc_traits::construct(ds::address_of(new_node->value), move(value));
        }else {
            try {
                alloc_traits::construct(ds::address_of(new_node->value), move(value));
            }catch(...) {
                alloc_traits::operator delete(new_node);
                throw;
            }
        }
        new_node->next = pos.node->next;
        pos.node->next->previous = new_node;
        pos.node->next = new_node;
        new_node->previous = pos.node;
        return iterator(new_node);
    }
    template <typename T, typename Allocator>
    template <typename InputIterator>
    inline typename list<T, Allocator>::iterator list<T, Allocator>::insert(difference_type pos, typename enable_if<
            is_input_iterator<InputIterator>::value and not is_forward_iterator<InputIterator>::value,
            InputIterator>::type begin, InputIterator end) {
        if(begin == end) {
            return iterator(this->tail);
        }
        auto cursor {this->tail->next};
        while(pos > 0 and cursor not_eq this->tail) {
            cursor = cursor->next;
            --pos;
        }
        if(pos > 0) {
            return iterator(this->tail);
        }
        return iterator(list::insert_auxiliary(begin, end, cursor->previous, cursor));
    }
    template <typename T, typename Allocator>
    template <typename InputIterator>
    inline typename list<T, Allocator>::iterator list<T, Allocator>::insert(const_iterator pos, typename enable_if<
            is_input_iterator<InputIterator>::value and not is_forward_iterator<InputIterator>::value,
            InputIterator>::type begin, InputIterator end) {
        if(begin == end) {
            return iterator(this->tail);
        }
        return iterator(list::insert_auxiliary(begin, end, pos.node->previous, pos.node));
    }
    template <typename T, typename Allocator>
    template <typename ForwardIterator>
    inline typename list<T, Allocator>::iterator list<T, Allocator>::insert(difference_type pos, typename enable_if<
            is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type begin, ForwardIterator end) {
        if(begin == end) {
            return iterator(this->tail);
        }
        auto cursor {this->tail->next};
        while(pos > 0 and cursor not_eq this->tail) {
            cursor = cursor->next;
            --pos;
        }
        if(pos > 0) {
            return iterator(this->tail);
        }
        return iterator(list::insert_auxiliary(begin, end, cursor->previous, cursor));
    }
    template <typename T, typename Allocator>
    template <typename ForwardIterator>
    inline typename list<T, Allocator>::iterator list<T, Allocator>::insert(const_iterator pos, typename enable_if<
            is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type begin, ForwardIterator end) {
        if(begin == end) {
            return iterator(this->tail);
        }
        return iterator(list::insert_auxiliary(begin, end, pos.node->previous, pos.node));
    }
    template <typename T, typename Allocator>
    inline typename list<T, Allocator>::iterator list<T, Allocator>::insert(
            difference_type pos, initializer_list<value_type> init_list) {
        return this->insert(pos, init_list.begin(), init_list.end());
    }
    template <typename T, typename Allocator>
    inline typename list<T, Allocator>::iterator list<T, Allocator>::insert(
            const_iterator pos, initializer_list<value_type> init_list) {
        return this->insert(pos, init_list.begin(), init_list.end());
    }
    template <typename T, typename Allocator>
    typename list<T, Allocator>::iterator list<T, Allocator>::erase(difference_type pos, size_type size) noexcept {
        if(size == 0) {
            return iterator(this->tail);
        }
        auto cursor {this->tail->next};
        while(pos > 0 and cursor not_eq this->tail) {
            cursor = cursor->next;
            --pos;
        }
        if(pos > 0) {
            return iterator(this->tail);
        }
        auto before {cursor->previous};
        while(size--) {
            auto backup {cursor};
            cursor = cursor->next;
            if constexpr(not is_trivially_destructible<value_type>::value) {
                list::destroy(ds::address_of(backup->value));
            }
            alloc_traits::operator delete(backup);
        }
        before->next = cursor;
        cursor->previous = before;
        return iterator(cursor);
    }
    template <typename T, typename Allocator>
    typename list<T, Allocator>::iterator list<T, Allocator>::erase(const_iterator pos, size_type size) noexcept {
        if(size == 0 or not pos.node) {
            return iterator(this->tail);
        }
        auto before {pos.node->previous};
        while(size--) {
            auto backup {pos.node};
            ++pos;
            if constexpr(not is_trivially_destructible<value_type>::value) {
                list::destroy(ds::address_of(backup->value));
            }
            alloc_traits::operator delete(backup);
        }
        before->next = pos.node;
        pos.node->previous = before;
    }
    template <typename T, typename Allocator>
    typename list<T, Allocator>::iterator list<T, Allocator>::erase(
            const_iterator begin, const_iterator end) noexcept {
        if(begin == end or not begin.node) {
            return end;
        }
        auto before {begin.node->previous};
        while(begin not_eq end) {
            auto backup {begin.node};
            ++begin;
            if constexpr(not is_trivially_destructible<value_type>::value) {
                list::destroy(ds::address_of(backup->value));
            }
            alloc_traits::operator delete(backup);
        }
        before->next = begin.node;
        begin.node->previous = before;
        return end;
    }
    template <typename T, typename Allocator>
    inline typename list<T, Allocator>::iterator list<T, Allocator>::erase(const_iterator pos) noexcept {
        auto return_node {pos.node->next};
        pos.node->previous->next = return_node;
        return_node->previous = pos.node->previous;
        if constexpr(not is_trivially_destructible<value_type>::value) {
            list::destroy(ds::address_of(pos.node->value));
        }
        alloc_traits::operator delete(pos.node);
        return return_node;
    }
    template <typename T, typename Allocator>
    template <typename ...Args>
    inline typename list<T, Allocator>::iterator list<T, Allocator>::emplace(difference_type pos, Args &&...args) {
        return this->insert(pos, value_type(ds::forward<Args>(args)...));
    }
    template <typename T, typename Allocator>
    template <typename ...Args>
    inline typename list<T, Allocator>::iterator list<T, Allocator>::emplace(const_iterator pos, Args &&...args) {
        return this->insert(pos, value_type(ds::forward<Args>(args)...));
    }
    template <typename T, typename Allocator>
    template <typename ...Args>
    inline void list<T, Allocator>::emplace_front(Args &&...args) {
        this->push_front(value_type(ds::forward<Args>(args)...));
    }
    template <typename T, typename Allocator>
    template <typename ...Args>
    inline void list<T, Allocator>::emplace_back(Args &&...args) {
        this->push_back(value_type(ds::forward<Args>(args)...));
    }
    template <typename T, typename Allocator>
    void list<T, Allocator>::push_front(const_reference value) {
        auto new_node {list::allocate()};
        if constexpr(is_nothrow_copy_constructible<value_type>::value) {
            alloc_traits::construct(ds::address_of(new_node->value), value);
        }else {
            try {
                alloc_traits::construct(ds::address_of(new_node->value), value);
            }catch(...) {
                alloc_traits::operator delete(new_node);
                throw;
            }
        }
        new_node->next = this->tail->next;
        new_node->previous = this->tail;
        this->tail->next->previous = new_node;
        this->tail->next = new_node;
    }
    template <typename T, typename Allocator>
    void list<T, Allocator>::push_front(rvalue_reference value) {
        auto new_node {list::allocate()};
        if constexpr(is_nothrow_move_constructible<value_type>::value or
                (not is_move_constructible<value_type>::value and is_nothrow_copy_constructible<value_type>::value)) {
            alloc_traits::construct(ds::address_of(new_node->value), ds::move(value));
        }else {
            try {
                alloc_traits::construct(ds::address_of(new_node->value), ds::move(value));
            }catch(...) {
                alloc_traits::operator delete(new_node);
                throw;
            }
        }
        new_node->next = this->tail->next;
        new_node->previous = this->tail;
        this->tail->next->previous = new_node;
        this->tail->next = new_node;
    }
    template <typename T, typename Allocator>
    void list<T, Allocator>::push_back(const_reference value) {
        auto new_node {list::allocate()};
        if constexpr(is_nothrow_copy_constructible<value_type>::value) {
            alloc_traits::construct(ds::address_of(new_node->value), value);
        }else {
            try {
                alloc_traits::construct(ds::address_of(new_node->value), value);
            }catch(...) {
                alloc_traits::operator delete(new_node);
                throw;
            }
        }
        new_node->next = this->tail;
        new_node->previous = this->tail->previous;
        this->tail->previous->next = new_node;
        this->tail->previous = new_node;
    }
    template <typename T, typename Allocator>
    void list<T, Allocator>::push_back(rvalue_reference value) {
        auto new_node {list::allocate()};
        if constexpr(is_nothrow_move_constructible<value_type>::value or
                (not is_move_constructible<value_type>::value and is_nothrow_copy_constructible<value_type>::value)) {
            alloc_traits::construct(ds::address_of(new_node->value), ds::move(value));
        }else {
            try {
                alloc_traits::construct(ds::address_of(new_node->value), ds::move(value));
            }catch(...) {
                alloc_traits::operator delete(new_node);
                throw;
            }
        }
        new_node->next = this->tail;
        new_node->previous = this->tail->previous;
        this->tail->previous->next = new_node;
        this->tail->previous = new_node;
    }
    template <typename T, typename Allocator>
    inline void list<T, Allocator>::pop_front() noexcept {
        if(this->empty()) {
            return;
        }
        this->erase(this->cbegin());
    }
    template <typename T, typename Allocator>
    inline void list<T, Allocator>::pop_back() noexcept {
        if(this->empty()) {
            return;
        }
        this->erase(--this->cend());
    }
    template <typename T, typename Allocator>
    inline void list<T, Allocator>::resize(size_type size, const_reference value) {
        this->assign(size, value);
    }
    template <typename T, typename Allocator>
    inline void list<T, Allocator>::swap(list &rhs) noexcept {
        if(this == &rhs) {
            return;
        }
        ds::swap(this->tail, rhs.tail);
    }
    template <typename T, typename Allocator>
    template <typename AllocatorRHS>
    inline void list<T, Allocator>::swap(list<T, AllocatorRHS> &rhs) noexcept {
        ds::swap(this->tail, rhs.tail);
    }
    template <typename T, typename Allocator>
    inline void list<T, Allocator>::clear() noexcept {
        this->erase(this->cbegin(), this->cend());
    }
}

namespace data_structure {
    template <typename T, typename AllocatorLHS, typename AllocatorRHS>
    inline void swap(list<T, AllocatorLHS> &lhs, list<T, AllocatorRHS> &rhs) noexcept {
        lhs.swap(rhs);
    }
    template <typename T, typename AllocatorLHS, typename AllocatorRHS>
    bool operator==(const list<T, AllocatorLHS> &lhs, const list<T, AllocatorRHS> &rhs) {
        auto lhs_cursor {lhs.cbegin()};
        auto rhs_cursor {rhs.cbegin()};
        while(lhs_cursor and rhs_cursor) {
            if(not(*lhs_cursor == *rhs_cursor)) {
                return false;
            }
        }
        return not(static_cast<bool>(lhs_cursor) or static_cast<bool>(rhs_cursor));
    }
    template <typename T, typename AllocatorLHS, typename AllocatorRHS>
    inline bool operator!=(const list<T, AllocatorLHS> &lhs, const list<T, AllocatorRHS> &rhs) {
        return not(lhs == rhs);
    }
    template <typename T, typename AllocatorLHS, typename AllocatorRHS>
    bool operator<(const list<T, AllocatorLHS> &lhs, const list<T, AllocatorRHS> &rhs) {
        auto lhs_cursor {lhs.cbegin()};
        auto rhs_cursor {rhs.cbegin()};
        while(lhs_cursor and rhs_cursor) {
            if(not(*lhs_cursor < *rhs_cursor)) {
                return false;
            }
        }
        return not(static_cast<bool>(lhs_cursor));
    }
    template <typename T, typename AllocatorLHS, typename AllocatorRHS>
    inline bool operator<=(const list<T, AllocatorLHS> &lhs, const list<T, AllocatorRHS> &rhs) {
        return not(rhs > lhs);
    }
    template <typename T, typename AllocatorLHS, typename AllocatorRHS>
    inline bool operator>(const list<T, AllocatorLHS> &lhs, const list<T, AllocatorRHS> &rhs) {
        return rhs < lhs;
    }
    template <typename T, typename AllocatorLHS, typename AllocatorRHS>
    inline bool operator>=(const list<T, AllocatorLHS> &lhs, const list<T, AllocatorRHS> &rhs) {
        return not(lhs < rhs);
    }
}

#endif //DATA_STRUCTURE_LIST_HPP
