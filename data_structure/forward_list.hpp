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

#ifndef DATA_STRUCTURE_FORWARD_LIST_HPP
#define DATA_STRUCTURE_FORWARD_LIST_HPP

#include "allocator.hpp"
#include "iterator.hpp"

namespace data_structure {
    template <typename T, typename Allocator = allocator<type_holder<T>>>
    class forward_list final {
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
        using iterator = forward_list_iterator<__dsa::forward_list_node<value_type>, false>;
        using const_iterator = forward_list_iterator<__dsa::forward_list_node<value_type>, true>;
    private:
        using alloc_traits = allocator_traits<allocator_type>;
        using node_value_type = __dsa::forward_list_node<value_type>;
        using node_type = typename add_pointer<node_value_type>::type;
        static_assert(is_same<typename __dsa::node_type_traits<node_value_type>::value_type,
                value_type>::value, "The forward_list holds different value_type!");
    private:
         node_type head;
    private:
        static node_type allocate();
        static void destroy(pointer) noexcept;
        static void handle_exception_from_constructor(node_type) noexcept;
        static void handle_exception(node_type) noexcept;
        static node_type allocate_sized(size_type, const_reference);
        template <typename InputIterator>
        static node_type allocate_sized(typename enable_if<
                is_input_iterator<InputIterator>::value and not is_forward_iterator<InputIterator>::value,
                InputIterator>::type, InputIterator);
        template <typename ForwardIterator>
        static node_type allocate_sized(
                typename enable_if<is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type,
                ForwardIterator);
        static node_type allocate_from_constructor(size_type);
        static node_type allocate_from_constructor(size_type, const_reference);
        template <typename InputIterator>
        static node_type allocate_from_constructor(typename enable_if<
                is_input_iterator<InputIterator>::value and not is_forward_iterator<InputIterator>::value,
                InputIterator>::type, InputIterator);
        template <typename ForwardIterator>
        static node_type allocate_from_constructor(
                typename enable_if<is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type,
                ForwardIterator);
        static node_type insert_auxiliary(node_type, node_type, const_reference, size_type);
        template <typename InputIterator>
        static node_type insert_auxiliary(node_type, node_type, typename enable_if<
                is_input_iterator<InputIterator>::value and not is_forward_iterator<InputIterator>::value,
                InputIterator>::type, InputIterator);
        template <typename ForwardIterator>
        static node_type insert_auxiliary(node_type, node_type,
                typename enable_if<is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type,
                ForwardIterator);
        template <typename Compare>
        static node_type merge_auxiliary(node_type, node_type, Compare &) noexcept;
    public:
        forward_list();
        explicit forward_list(size_type);
        forward_list(size_type, const_reference);
        template <typename InputIterator>
        forward_list(typename enable_if<
                is_input_iterator<InputIterator>::value and not is_forward_iterator<InputIterator>::value,
                InputIterator>::type, InputIterator);
        template <typename ForwardIterator>
        forward_list(typename enable_if<is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type,
                ForwardIterator);
        forward_list(std::initializer_list<value_type>);
        forward_list(const forward_list &);
        forward_list(forward_list &&) noexcept;
        template <typename AllocatorRHS>
        forward_list(const forward_list<value_type, AllocatorRHS> &);
        template <typename AllocatorRHS>
        forward_list(forward_list<value_type, AllocatorRHS> &&) noexcept;
        ~forward_list() noexcept;
    public:
        forward_list &operator=(const forward_list &);
        forward_list &operator=(forward_list &&) noexcept;
        template <typename AllocatorRHS>
        forward_list &operator=(const forward_list<value_type, AllocatorRHS> &);
        template <typename AllocatorRHS>
        forward_list &operator=(forward_list<value_type, AllocatorRHS> &&) noexcept;
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
        reference front();
        const_reference front() const;
        iterator before_begin() noexcept;
        const_iterator before_begin() const noexcept;
        iterator begin() noexcept;
        const_iterator begin() const noexcept;
        const_iterator cbefore_begin() const noexcept;
        const_iterator cbegin() const noexcept;
        constexpr iterator end() noexcept;
        constexpr const_iterator end() const noexcept;
        constexpr const_iterator cend() const noexcept;
        bool empty() const noexcept;
        constexpr size_type max_size() const noexcept;
        void clear() noexcept;
        void swap(forward_list &) noexcept;
        template <typename AllocatorRHS>
        void swap(forward_list<value_type, AllocatorRHS> &) noexcept;
        void resize(size_type, const_reference = {});
        iterator insert(difference_type, const_reference, size_type = 1);
        static iterator insert_after(const_iterator, const_reference, size_type = 1);
        iterator insert(difference_type, rvalue_reference);
        static iterator insert_after(const_iterator, rvalue_reference);
        template <typename InputIterator>
        iterator insert(difference_type, typename enable_if<
                is_input_iterator<InputIterator>::value and not is_forward_iterator<InputIterator>::value,
                InputIterator>::type, InputIterator);
        template <typename InputIterator>
        static iterator insert_after(const_iterator, typename enable_if<
                is_input_iterator<InputIterator>::value and not is_forward_iterator<InputIterator>::value,
                InputIterator>::type, InputIterator);
        template <typename ForwardIterator>
        iterator insert(difference_type,
                typename enable_if<is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type,
                ForwardIterator);
        template <typename ForwardIterator>
        static iterator insert_after(const_iterator,
                typename enable_if<is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type,
                ForwardIterator);
        iterator insert(difference_type, std::initializer_list<value_type>);
        static iterator insert_after(const_iterator, std::initializer_list<value_type>);
        iterator erase(difference_type, size_type = 1) noexcept;
        static iterator erase_after(const_iterator, size_type = 1) noexcept;
        static iterator erase_after(const_iterator, const_iterator) noexcept;
        template <typename ...Args>
        iterator emplace_after(difference_type, Args &&...);
        template <typename ...Args>
        iterator emplace_after(const_iterator, Args &&...);
        template <typename ...Args>
        void emplace_front(Args &&...);
        void push_front(const_reference);
        void push_front(rvalue_reference);
        void pop_front() noexcept;
    public:
        void merge(forward_list &) noexcept(has_nothrow_less_operator<value_type>::value and
                has_nothrow_equal_to_operator<value_type>::value);
        void merge(forward_list &&) noexcept(has_nothrow_less_operator<value_type>::value and
                has_nothrow_equal_to_operator<value_type>::value);
        template <typename AllocatorRHS>
        void merge(forward_list<value_type, AllocatorRHS> &)
                noexcept(has_nothrow_less_operator<value_type>::value and
                        has_nothrow_equal_to_operator<value_type>::value);
        template <typename AllocatorRHS>
        void merge(forward_list<value_type, AllocatorRHS> &&)
                noexcept(has_nothrow_less_operator<value_type>::value and
                        has_nothrow_equal_to_operator<value_type>::value);
        template <typename Compare>
        void merge(forward_list &, Compare)
                noexcept(has_nothrow_function_call_operator<Compare, value_type, value_type>::value);
        template <typename Compare>
        void merge(forward_list &&, Compare)
                noexcept(has_nothrow_function_call_operator<Compare, value_type, value_type>::value);
        template <typename Compare, typename AllocatorRHS>
        void merge(forward_list<value_type, AllocatorRHS> &, Compare)
                noexcept(has_nothrow_function_call_operator<Compare, value_type, value_type>::value);
        template <typename Compare, typename AllocatorRHS>
        void merge(forward_list<value_type, AllocatorRHS> &&, Compare)
                noexcept(has_nothrow_function_call_operator<Compare, value_type, value_type>::value);
        void splice_after(difference_type, forward_list &) noexcept;
        void splice_after(const_iterator, forward_list &) noexcept;
        void splice_after(difference_type, forward_list &&) noexcept;
        void splice_after(const_iterator, forward_list &&) noexcept;
        void splice_after(difference_type, forward_list &, difference_type) noexcept;
        void splice_after(difference_type, forward_list &, const_iterator) noexcept;
        void splice_after(difference_type, forward_list &&, difference_type) noexcept;
        void splice_after(difference_type, forward_list &&, const_iterator) noexcept;
        void splice_after(const_iterator, forward_list &, difference_type) noexcept;
        void splice_after(const_iterator, forward_list &, const_iterator) noexcept;
        void splice_after(const_iterator, forward_list &&, difference_type) noexcept;
        void splice_after(const_iterator, forward_list &&, const_iterator) noexcept;
        void splice_after(difference_type, forward_list &, difference_type, size_type) noexcept;
        void splice_after(difference_type, forward_list &, const_iterator, size_type) noexcept;
        void splice_after(difference_type, forward_list &&, difference_type, size_type) noexcept;
        void splice_after(difference_type, forward_list &&, const_iterator, size_type) noexcept;
        void splice_after(const_iterator, forward_list &, difference_type, size_type) noexcept;
        void splice_after(const_iterator, forward_list &, const_iterator , size_type) noexcept;
        void splice_after(const_iterator , forward_list &&, difference_type, size_type) noexcept;
        void splice_after(const_iterator, forward_list &&, const_iterator, size_type) noexcept;
        void splice_after(difference_type, forward_list &, const_iterator, const_iterator) noexcept;
        void splice_after(difference_type, forward_list &&, const_iterator, const_iterator) noexcept;
        void splice_after(const_iterator, forward_list &, const_iterator, const_iterator) noexcept;
        void splice_after(const_iterator, forward_list &&, const_iterator, const_iterator) noexcept;
        template <typename AllocatorRHS>
        void splice_after(difference_type, forward_list<value_type, AllocatorRHS> &) noexcept;
        template <typename AllocatorRHS>
        void splice_after(const_iterator, forward_list<value_type, AllocatorRHS> &) noexcept;
        template <typename AllocatorRHS>
        void splice_after(difference_type, forward_list<value_type, AllocatorRHS> &&) noexcept;
        template <typename AllocatorRHS>
        void splice_after(const_iterator, forward_list<value_type, AllocatorRHS> &&) noexcept;
        template <typename AllocatorRHS>
        void splice_after(difference_type, forward_list<value_type, AllocatorRHS> &, difference_type) noexcept;
        template <typename AllocatorRHS>
        void splice_after(difference_type, forward_list<value_type, AllocatorRHS> &, const_iterator) noexcept;
        template <typename AllocatorRHS>
        void splice_after(difference_type, forward_list<value_type, AllocatorRHS> &&, difference_type) noexcept;
        template <typename AllocatorRHS>
        void splice_after(difference_type, forward_list<value_type, AllocatorRHS> &&, const_iterator) noexcept;
        template <typename AllocatorRHS>
        void splice_after(const_iterator, forward_list<value_type, AllocatorRHS> &, difference_type) noexcept;
        template <typename AllocatorRHS>
        void splice_after(const_iterator, forward_list<value_type, AllocatorRHS> &, const_iterator) noexcept;
        template <typename AllocatorRHS>
        void splice_after(const_iterator, forward_list<value_type, AllocatorRHS> &&, difference_type) noexcept;
        template <typename AllocatorRHS>
        void splice_after(const_iterator, forward_list<value_type, AllocatorRHS> &&, const_iterator) noexcept;
        template <typename AllocatorRHS>
        void splice_after(difference_type, forward_list<value_type, AllocatorRHS> &, difference_type, size_type)
                noexcept;
        template <typename AllocatorRHS>
        void splice_after(difference_type, forward_list<value_type, AllocatorRHS> &, const_iterator, size_type)
                noexcept;
        template <typename AllocatorRHS>
        void splice_after(difference_type, forward_list<value_type, AllocatorRHS> &&, difference_type, size_type)
                noexcept;
        template <typename AllocatorRHS>
        void splice_after(difference_type, forward_list<value_type, AllocatorRHS> &&, const_iterator, size_type)
                noexcept;
        template <typename AllocatorRHS>
        void splice_after(const_iterator, forward_list<value_type, AllocatorRHS> &, difference_type, size_type)
                noexcept;
        template <typename AllocatorRHS>
        void splice_after(const_iterator, forward_list<value_type, AllocatorRHS> &, const_iterator , size_type)
                noexcept;
        template <typename AllocatorRHS>
        void splice_after(const_iterator , forward_list<value_type, AllocatorRHS> &&, difference_type, size_type)
                noexcept;
        template <typename AllocatorRHS>
        void splice_after(const_iterator, forward_list<value_type, AllocatorRHS> &&, const_iterator, size_type)
                noexcept;
        template <typename AllocatorRHS>
        void splice_after(difference_type, forward_list<value_type, AllocatorRHS> &, const_iterator, const_iterator)
                noexcept;
        template <typename AllocatorRHS>
        void splice_after(difference_type, forward_list<value_type, AllocatorRHS> &&, const_iterator, const_iterator)
                noexcept;
        template <typename AllocatorRHS>
        void splice_after(const_iterator, forward_list<value_type, AllocatorRHS> &, const_iterator, const_iterator)
                noexcept;
        template <typename AllocatorRHS>
        void splice_after(const_iterator, forward_list<value_type, AllocatorRHS> &&, const_iterator, const_iterator)
                noexcept;
        void remove(const_reference) noexcept(has_nothrow_equal_to_operator<value_type>::value);
        template <typename UnaryPredicate>
        void remove_if(UnaryPredicate)
                noexcept(has_nothrow_function_call_operator<UnaryPredicate, value_type>::value);
        void unique() noexcept(has_nothrow_equal_to_operator<value_type>::value);
        template <typename BinaryPredicate>
        void unique(BinaryPredicate)
                noexcept(has_nothrow_function_call_operator<BinaryPredicate, value_type>::value);
        void sort() noexcept;
        template <typename Compare>
        void sort(Compare) noexcept;
        void reverse() noexcept;
    };
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    void swap(forward_list<T, AllocatorLHS> &, forward_list<T, AllocatorRHS> &) noexcept;
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    bool operator==(const forward_list<T, AllocatorLHS> &, const forward_list<T, AllocatorRHS> &);
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    bool operator!=(const forward_list<T, AllocatorLHS> &, const forward_list<T, AllocatorRHS> &);
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    bool operator<(const forward_list<T, AllocatorLHS> &, const forward_list<T, AllocatorRHS> &);
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    bool operator<=(const forward_list<T, AllocatorLHS> &, const forward_list<T, AllocatorRHS> &);
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    bool operator>(const forward_list<T, AllocatorLHS> &, const forward_list<T, AllocatorRHS> &);
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    bool operator>=(const forward_list<T, AllocatorLHS> &, const forward_list<T, AllocatorRHS> &);
}

namespace data_structure {
    /* private function */
    template <typename T, typename Allocator>
    inline typename forward_list<T, Allocator>::node_type forward_list<T, Allocator>::allocate() {
        return reinterpret_cast<node_type>(alloc_traits::operator new(sizeof(node_value_type)));
    }
    template <typename T, typename Allocator>
    inline void forward_list<T, Allocator>::destroy(pointer p) noexcept {
        alloc_traits::destroy(p);
    }
    template <typename T, typename Allocator>
    void forward_list<T, Allocator>::handle_exception_from_constructor(node_type begin) noexcept {
        auto cursor {begin->next};
        while(cursor->next) {
            auto backup {cursor};
            cursor = cursor->next;
            if constexpr(not is_trivially_destructible<value_type>::value) {
                alloc_traits::destroy(address_of(cursor->value));
            }
            alloc_traits::operator delete(backup);
        }
        alloc_traits::operator delete(cursor);
        alloc_traits::operator delete(begin);
    }
    template <typename T, typename Allocator>
    void forward_list<T, Allocator>::handle_exception(node_type begin) noexcept {
        while(begin->next) {
            auto backup {begin};
            begin = begin->next;
            if constexpr(not is_trivially_destructible<value_type>::value) {
                alloc_traits::destroy(address_of(backup->value));
            }
            alloc_traits::operator delete(backup);
        }
        alloc_traits::operator delete(begin);
    }
    template <typename T, typename Allocator>
    typename forward_list<T, Allocator>::node_type
    forward_list<T, Allocator>::allocate_sized(size_type size, const_reference value) {
        const auto first {forward_list::allocate()};
        auto cursor {first};
        while(true) {
            if constexpr(is_nothrow_copy_constructible<value_type>::value) {
                alloc_traits::construct(address_of(cursor->value), value);
            }else {
                try {
                    alloc_traits::construct(address_of(cursor->value), value);
                }catch(...) {
                    cursor->next = nullptr;
                    forward_list::handle_exception(first);
                    throw;
                }
            }
            if(not --size) {
                break;
            }
            try {
                cursor->next = forward_list::allocate();
            }catch(...) {
                cursor->next = nullptr;
                if constexpr(not is_trivially_destructible<value_type>::value) {
                    destroy(address_of(cursor->value));
                }
                forward_list::handle_exception(first);
                throw;
            }
            cursor = cursor->next;
        }
        cursor->next = nullptr;
        return first;
    }
    template <typename T, typename Allocator>
    template <typename InputIterator>
    typename forward_list<T, Allocator>::node_type
    forward_list<T, Allocator>::allocate_sized(typename enable_if<
            is_input_iterator<InputIterator>::value and not is_forward_iterator<InputIterator>::value,
            InputIterator>::type begin, InputIterator end) {
        const auto first {forward_list::allocate()};
        auto cursor {first};
        while(true) {
            if constexpr(is_nothrow_copy_constructible<value_type>::value) {
                alloc_traits::construct(address_of(cursor->value), move(*begin++));
            }else {
                try {
                    alloc_traits::construct(address_of(cursor->value), move(*begin++));
                }catch(...) {
                    cursor->next = nullptr;
                    forward_list::handle_exception(first);
                    throw;
                }
            }
            if(begin == end) {
                break;
            }
            try {
                cursor->next = forward_list::allocate();
            }catch(...) {
                cursor->next = nullptr;
                if constexpr(not is_trivially_destructible<value_type>::value) {
                    forward_list::destroy(address_of(cursor->value));
                }
                forward_list::handle_exception(first);
                throw;
            }
            cursor = cursor->next;
        }
        cursor->next = nullptr;
        return first;
    }
    template <typename T, typename Allocator>
    template <typename ForwardIterator>
    typename forward_list<T, Allocator>::node_type
    forward_list<T, Allocator>::allocate_sized(
            typename enable_if<is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type begin,
            ForwardIterator end) {
        const auto first {forward_list::allocate()};
        auto cursor {first};
        while(true) {
            if constexpr(is_nothrow_copy_constructible<value_type>::value) {
                alloc_traits::construct(address_of(cursor->value), *begin++);
            }else {
                try {
                    alloc_traits::construct(address_of(cursor->value), *begin++);
                }catch(...) {
                    cursor->next = nullptr;
                    forward_list::handle_exception(first);
                    throw;
                }
            }
            if(begin == end) {
                break;
            }
            try {
                cursor->next = forward_list::allocate();
            }catch(...) {
                cursor->next = nullptr;
                if constexpr(not is_trivially_destructible<value_type>::value) {
                    forward_list::destroy(address_of(cursor->value));
                }
                forward_list::handle_exception(first);
                throw;
            }
            cursor = cursor->next;
        }
        cursor->next = nullptr;
        return first;
    }
    template <typename T, typename Allocator>
    typename forward_list<T, Allocator>::node_type
    forward_list<T, Allocator>::allocate_from_constructor(size_type size) {
        const auto first {forward_list::allocate()};
        if(not size) {
            first->next = nullptr;
            return first;
        }
        auto cursor {first};
        while(size--) {
            try {
                cursor->next = forward_list::allocate();
            }catch(...) {
                cursor->next = nullptr;
                if constexpr(not is_trivially_destructible<value_type>::value) {
                    forward_list::destroy(address_of(cursor->value));
                }
                forward_list::handle_exception_from_constructor(first);
                throw;
            }
            if constexpr(is_nothrow_constructible<value_type>::value) {
                alloc_traits::construct(address_of(cursor->next->value));
            }else {
                try {
                    alloc_traits::construct(address_of(cursor->next->value));
                }catch(...) {
                    cursor->next = nullptr;
                    forward_list::handle_exception_from_constructor(first);
                    throw;
                }
            }
            cursor = cursor->next;
        }
        cursor->next = nullptr;
        return first;
    }
    template <typename T, typename Allocator>
    typename forward_list<T, Allocator>::node_type
    forward_list<T, Allocator>::allocate_from_constructor(size_type size, const_reference value) {
        const auto first {forward_list::allocate()};
        if(not size) {
            first->next = nullptr;
            return first;
        }
        auto cursor {first};
        while(size--) {
            try {
                cursor->next = forward_list::allocate();
            }catch(...) {
                cursor->next = nullptr;
                if constexpr(not is_trivially_destructible<value_type>::value) {
                    forward_list::destroy(address_of(cursor->value));
                }
                forward_list::handle_exception_from_constructor(first);
                throw;
            }
            if constexpr(is_nothrow_copy_constructible<value_type>::value) {
                alloc_traits::construct(address_of(cursor->next->value), value);
            }else {
                try {
                    alloc_traits::construct(address_of(cursor->next->value), value);
                }catch(...) {
                    cursor->next = nullptr;
                    forward_list::handle_exception_from_constructor(first);
                    throw;
                }
            }
            cursor = cursor->next;
        }
        cursor->next = nullptr;
        return first;
    }
    template <typename T, typename Allocator>
    template <typename InputIterator>
    typename forward_list<T, Allocator>::node_type
    forward_list<T, Allocator>::allocate_from_constructor(typename enable_if<
            is_input_iterator<InputIterator>::value and not is_forward_iterator<InputIterator>::value,
            InputIterator>::type begin, InputIterator end) {
        const auto first {forward_list::allocate()};
        if(begin == end) {
            first->next = nullptr;
            return first;
        }
        auto cursor {first};
        while(begin not_eq end) {
            try {
                cursor->next = forward_list::allocate();
            }catch(...) {
                cursor->next = nullptr;
                if constexpr(not is_trivially_destructible<value_type>::value) {
                    forward_list::destroy(address_of(cursor->value));
                }
                forward_list::handle_exception_from_constructor(first);
                throw;
            }
            if constexpr(is_nothrow_move_constructible<value_type>::value or
                    is_nothrow_copy_constructible<value_type>::value) {
                alloc_traits::construct(address_of(cursor->next->value), move(*begin++));
            }else {
                try {
                    alloc_traits::construct(address_of(cursor->next->value), move(*begin++));
                }catch(...) {
                    cursor->next = nullptr;
                    forward_list::handle_exception_from_constructor(first);
                    throw;
                }
            }
            cursor = cursor->next;
        }
        cursor->next = nullptr;
        return first;
    }
    template <typename T, typename Allocator>
    template <typename ForwardIterator>
    typename forward_list<T, Allocator>::node_type
    forward_list<T, Allocator>::allocate_from_constructor(
            typename enable_if<is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type begin,
            ForwardIterator end) {
        const auto first {forward_list::allocate()};
        if(begin == end) {
            first->next = nullptr;
            return first;
        }
        auto cursor {first};
        while(begin not_eq end) {
            try {
                cursor->next = forward_list::allocate();
            }catch(...) {
                cursor->next = nullptr;
                if constexpr(not is_trivially_destructible<value_type>::value) {
                    forward_list::destroy(address_of(cursor->value));
                }
                forward_list::handle_exception_from_constructor(first);
                throw;
            }
            if constexpr(is_nothrow_copy_constructible<value_type>::value) {
                alloc_traits::construct(address_of(cursor->next->value), *begin++);
            }else {
                try {
                    alloc_traits::construct(address_of(cursor->next->value), *begin++);
                }catch(...) {
                    cursor->next = nullptr;
                    forward_list::handle_exception_from_constructor(first);
                    throw;
                }
            }
            cursor = cursor->next;
        }
        cursor->next = nullptr;
        return first;
    }
    template <typename T, typename Allocator>
    typename forward_list<T, Allocator>::node_type forward_list<T, Allocator>::insert_auxiliary(
            node_type before_begin, node_type after_end, const_reference value, size_type size) {
        const auto first {forward_list::allocate()};
        auto cursor {first};
        while(true) {
            if constexpr(is_nothrow_copy_constructible<value_type>::value) {
                alloc_traits::construct(address_of(cursor->value), value);
            }else {
                try {
                    alloc_traits::construct(address_of(cursor->value), value);
                }catch(...) {
                    cursor->next = nullptr;
                    forward_list::handle_exception(first);
                    throw;
                }
            }
            if(not --size) {
                break;
            }
            try {
                cursor->next = forward_list::allocate();
            }catch(...) {
                cursor->next = nullptr;
                if constexpr(not is_trivially_destructible<value_type>::value) {
                    destroy(address_of(cursor->value));
                }
                forward_list::handle_exception(first);
                throw;
            }
            cursor = cursor->next;
        }
        before_begin->next = first;
        cursor->next = after_end;
        return first;
    }
    template <typename T, typename Allocator>
    template <typename InputIterator>
    typename forward_list<T, Allocator>::node_type forward_list<T, Allocator>::insert_auxiliary(
            node_type before_begin, node_type after_end, typename enable_if<
                    is_input_iterator<InputIterator>::value and not is_forward_iterator<InputIterator>::value,
                    InputIterator>::type begin, InputIterator end) {
        const auto first {forward_list::allocate()};
        auto cursor {first};
        while(true) {
            if constexpr(is_nothrow_move_constructible<value_type>::value or
                    is_nothrow_copy_constructible<value_type>::value) {
                alloc_traits::construct(address_of(cursor->value), move(*begin++));
            }else {
                try {
                    alloc_traits::construct(address_of(cursor->value), move(*begin++));
                }catch(...) {
                    cursor->next = nullptr;
                    forward_list::handle_exception(first);
                    throw;
                }
            }
            if(begin == end) {
                break;
            }
            try {
                cursor->next = forward_list::allocate();
            }catch(...) {
                cursor->next = nullptr;
                if constexpr(not is_trivially_destructible<value_type>::value) {
                    forward_list::destroy(address_of(cursor->value));
                }
                forward_list::handle_exception(first);
                throw;
            }
            cursor = cursor->next;
        }
        before_begin->next = first;
        cursor->next = after_end;
        return first;
    }
    template <typename T, typename Allocator>
    template <typename ForwardIterator>
    typename forward_list<T, Allocator>::node_type forward_list<T, Allocator>::insert_auxiliary(
            node_type before_begin, node_type after_end, typename enable_if<
                    is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type begin,
                    ForwardIterator end) {
        const auto first {forward_list::allocate()};
        auto cursor {first};
        while(true) {
            if constexpr(is_nothrow_copy_constructible<value_type>::value) {
                alloc_traits::construct(address_of(cursor->value), *begin++);
            }else {
                try {
                    alloc_traits::construct(address_of(cursor->value), *begin++);
                }catch(...) {
                    cursor->next = nullptr;
                    forward_list::handle_exception(first);
                    throw;
                }
            }
            if(begin == end) {
                break;
            }
            try {
                cursor->next = forward_list::allocate();
            }catch(...) {
                cursor->next = nullptr;
                if constexpr(not is_trivially_destructible<value_type>::value) {
                    forward_list::destroy(address_of(cursor->value));
                }
                forward_list::handle_exception(first);
                throw;
            }
            cursor = cursor->next;
        }
        before_begin->next = first;
        cursor->next = after_end;
        return first;
    }
    template <typename T, typename Allocator>
    template <typename Compare>
    typename forward_list<T, Allocator>::node_type
    forward_list<T, Allocator>::merge_auxiliary(node_type lhs, node_type rhs, Compare &cmp) noexcept {
        if(not lhs) {
            return rhs;
        }
        if(not rhs) {
            return lhs;
        }
        node_type result {};
        if(cmp(rhs->value, lhs->value)) {
            auto next {rhs};
            while(next->next and cmp(next->next->value, lhs->value)) {
                next = next->next;
            }
            result = rhs;
            rhs = next->next;
            next->next = lhs;
        }else {
            result = lhs;
        }
        auto before_lhs {lhs};
        lhs = lhs->next;
        while(lhs and rhs) {
            if(cmp(rhs->value, lhs->value)) {
                auto rhs_cursor {rhs};
                while(rhs_cursor->next and cmp(rhs_cursor->next->value, lhs->value)) {
                    rhs_cursor = rhs_cursor->next;
                }
                before_lhs->next = rhs;
                rhs = rhs_cursor->next;
                rhs_cursor->next = lhs;
            }
            before_lhs = lhs;
            lhs = lhs->next;
        }
        if(rhs) {
            before_lhs->next = rhs;
        }
        return result;
    }

    /* public function */
    template <typename T, typename Allocator>
    inline forward_list<T, Allocator>::forward_list() : forward_list(0) {}
    template <typename T, typename Allocator>
    inline forward_list<T, Allocator>::forward_list(size_type size) :
            head {this->allocate_from_constructor(size)} {}
    template <typename T, typename Allocator>
    inline forward_list<T, Allocator>::forward_list(size_type size, const_reference value) :
            head {this->allocate_from_constructor(size, value)} {}
    template <typename T, typename Allocator>
    template <typename InputIterator>
    inline forward_list<T, Allocator>::forward_list(typename enable_if<
            is_input_iterator<InputIterator>::value and not is_forward_iterator<InputIterator>::value,
            InputIterator>::type begin, InputIterator end) :
                    head {this->allocate_from_constructor(begin, end)} {}
    template <typename T, typename Allocator>
    template <typename ForwardIterator>
    inline forward_list<T, Allocator>::forward_list(
            typename enable_if<is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type begin,
            ForwardIterator end) : head {this->allocate_from_constructor(begin, end)} {}
    template <typename T, typename Allocator>
    inline forward_list<T, Allocator>::forward_list(std::initializer_list<value_type> init_list) :
            forward_list(init_list.begin(), init_list.end()) {}
    template <typename T, typename Allocator>
    inline forward_list<T, Allocator>::forward_list(const forward_list &rhs) :
            forward_list(rhs.cbegin(), rhs.cend()) {}
    template <typename T, typename Allocator>
    inline forward_list<T, Allocator>::forward_list(forward_list &&rhs) noexcept : head {rhs.head} {
        rhs.head = nullptr;
    }
    template <typename T, typename Allocator>
    template <typename AllocatorRHS>
    inline forward_list<T, Allocator>::forward_list(const forward_list<T, AllocatorRHS> &rhs) :
            forward_list(rhs.cbegin(), rhs.cend()) {}
    template <typename T, typename Allocator>
    template <typename AllocatorRHS>
    inline forward_list<T, Allocator>::forward_list(forward_list<T, AllocatorRHS> &&rhs) noexcept :
            head {rhs.head} {
        rhs.head = nullptr;
    }
    template <typename T, typename Allocator>
    forward_list<T, Allocator>::~forward_list() noexcept {
        auto cursor {this->head->next};
        while(cursor) {
            auto backup {cursor};
            cursor = cursor->next;
            if constexpr(not is_trivially_destructible<value_type>::value) {
                forward_list::destroy(address_of(backup->value));
            }
            alloc_traits::operator delete(backup);
        }
        alloc_traits::operator delete(this->head);
    }
    template <typename T, typename Allocator>
    inline forward_list<T, Allocator> &forward_list<T, Allocator>::operator=(const forward_list &rhs) {
        if(this not_eq &rhs) {
            this->assign(rhs.cbegin(), rhs.cend());
        }
        return *this;
    }
    template <typename T, typename Allocator>
    inline forward_list<T, Allocator> &forward_list<T, Allocator>::operator=(forward_list &&rhs) noexcept {
        if(this not_eq &rhs) {
            this->~forward_list<T, Allocator>();
            this->head = rhs.head;
            rhs.head = nullptr;
        }
        return *this;
    }
    template <typename T, typename Allocator>
    template <typename AllocatorRHS>
    inline forward_list<T, Allocator> &
    forward_list<T, Allocator>::operator=(const forward_list<T, AllocatorRHS> &rhs) {
        this->assign(rhs.cbegin(), rhs.cend());
        return *this;
    }
    template <typename T, typename Allocator>
    template <typename AllocatorRHS>
    inline forward_list<T, Allocator> &
    forward_list<T, Allocator>::operator=(forward_list<T, AllocatorRHS> &&rhs) noexcept {
        this->~forward_list();
        this->head = rhs.head;
        rhs.head = nullptr;
        return *this;
    }
    template <typename T, typename Allocator>
    void forward_list<T, Allocator>::assign(size_type size, const_reference value) {
        auto before_cursor {this->before_begin()};
        auto cursor {this->begin()};
        const auto end {this->end()};
        while(cursor not_eq end and size) {
            *cursor++ = value;
            --size;
            ++before_cursor;
        }
        if(size) {
            this->insert_after(before_cursor, value, size);
        }
        if(cursor not_eq end) {
            this->erase_after(before_cursor, end);
        }
    }
    template <typename T, typename Allocator>
    template <typename InputIterator>
    void forward_list<T, Allocator>::assign(typename enable_if<
            is_input_iterator<InputIterator>::value and not is_forward_iterator<InputIterator>::value,
            InputIterator>::type begin, InputIterator end) {
        auto before_cursor {this->before_begin()};
        auto cursor {this->begin()};
        const auto last {this->end()};
        while(cursor not_eq last and begin not_eq end) {
            *cursor++ = move(*begin++);
            ++before_cursor;
        }
        if(begin not_eq end) {
            this->insert_after(before_cursor, begin, end);
        }
        if(cursor not_eq last) {
            this->erase_after(before_cursor, last);
        }
    }
    template <typename T, typename Allocator>
    template <typename ForwardIterator>
    void forward_list<T, Allocator>::assign(typename enable_if<
            is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type begin, ForwardIterator end) {
        auto before_cursor {this->before_begin()};
        auto cursor {this->begin()};
        const auto last {this->end()};
        while(cursor not_eq last and begin not_eq end) {
            *cursor++ = *begin++;
            ++before_cursor;
        }
        if(begin not_eq end) {
            this->insert_after(before_cursor, begin, end);
        }
        if(cursor not_eq last) {
            this->erase_after(before_cursor, last);
        }
    }
    template <typename T, typename Allocator>
    inline void forward_list<T, Allocator>::assign(std::initializer_list<value_type> init_list) {
        this->assign(init_list.begin(), init_list.end());
    }
    template <typename T, typename Allocator>
    inline typename forward_list<T, Allocator>::reference forward_list<T, Allocator>::front() {
        return this->head->next->value;
    }
    template <typename T, typename Allocator>
    inline typename forward_list<T, Allocator>::const_reference forward_list<T, Allocator>::front() const {
        return this->head->next->value;
    }
    template <typename T, typename Allocator>
    inline typename forward_list<T, Allocator>::iterator forward_list<T, Allocator>::before_begin() noexcept {
        return iterator(this->head);
    }
    template <typename T, typename Allocator>
    inline typename forward_list<T, Allocator>::const_iterator
    forward_list<T, Allocator>::before_begin() const noexcept {
        return const_iterator(this->head);
    }
    template <typename T, typename Allocator>
    inline typename forward_list<T, Allocator>::const_iterator
    forward_list<T, Allocator>::cbefore_begin() const noexcept {
        return const_iterator(this->head);
    }
    template <typename T, typename Allocator>
    inline typename forward_list<T, Allocator>::iterator forward_list<T, Allocator>::begin() noexcept {
        return iterator(this->head->next);
    }
    template <typename T, typename Allocator>
    inline typename forward_list<T, Allocator>::const_iterator
    forward_list<T, Allocator>::begin() const noexcept {
        return const_iterator(this->head->next);
    }
    template <typename T, typename Allocator>
    inline typename forward_list<T, Allocator>::const_iterator
    forward_list<T, Allocator>::cbegin() const noexcept {
        return const_iterator(this->head->next);
    }
    template <typename T, typename Allocator>
    constexpr inline typename forward_list<T, Allocator>::iterator forward_list<T, Allocator>::end() noexcept {
        return iterator(nullptr);
    }
    template <typename T, typename Allocator>
    constexpr inline typename forward_list<T, Allocator>::const_iterator
    forward_list<T, Allocator>::end() const noexcept {
        return const_iterator(nullptr);
    }
    template <typename T, typename Allocator>
    constexpr inline typename forward_list<T, Allocator>::const_iterator
    forward_list<T, Allocator>::cend() const noexcept {
        return const_iterator(nullptr);
    }
    template <typename T, typename Allocator>
    inline bool forward_list<T, Allocator>::empty() const noexcept {
        return this->head->next;
    }
    template <typename T, typename Allocator>
    constexpr inline typename forward_list<T, Allocator>::size_type
    forward_list<T, Allocator>::max_size() const noexcept {
        return std::numeric_limits<size_type>::max() / sizeof(value_type);
    }
    template <typename T, typename Allocator>
    inline void forward_list<T, Allocator>::clear() noexcept {
        if(not this->head->next) {
            return;
        }
        this->erase_after(this->cbefore_begin(), this->cend());
    }
    template <typename T, typename Allocator>
    inline void forward_list<T, Allocator>::swap(forward_list &rhs) noexcept {
        __DS::swap(this->head, rhs.head);
    }
    template <typename T, typename Allocator>
    template <typename AllocatorRHS>
    inline void forward_list<T, Allocator>::swap(forward_list<T, AllocatorRHS> &rhs) noexcept {
        __DS::swap(this->head, rhs.head);
    }
    template <typename T, typename Allocator>
    inline void forward_list<T, Allocator>::resize(size_type size, const_reference value) {
        this->assign(size, value);
    }
    template <typename T, typename Allocator>
    inline typename forward_list<T, Allocator>::iterator
    forward_list<T, Allocator>::insert(difference_type pos, const_reference value, size_type size) {
        if(not size) {
            return iterator(nullptr);
        }
        auto cursor {this->head};
        while(pos and cursor->next) {
            cursor = cursor->next;
            --pos;
        }
        if(pos) {
            return iterator(nullptr);
        }
        return iterator(this->insert_auxiliary(cursor, cursor->next, value, size));
    }
    template <typename T, typename Allocator>
    inline typename forward_list<T, Allocator>::iterator
    forward_list<T, Allocator>::insert_after(const_iterator pos, const_reference value, size_type size) {
        if(not size or not pos.node) {
            return iterator(nullptr);
        }
        return iterator(forward_list::insert_auxiliary(pos.node, pos.node->next, value, size));
    }
    template <typename T, typename Allocator>
    inline typename forward_list<T, Allocator>::iterator
    forward_list<T, Allocator>::insert(difference_type pos, rvalue_reference value) {
        auto cursor {this->head};
        while(pos and cursor->next) {
            cursor = cursor->next;
            --pos;
        }
        if(pos) {
            return iterator(nullptr);
        }
        auto new_node {this->allocate()};
        if constexpr(is_nothrow_move_constructible<value_type>::value or
                is_nothrow_copy_constructible<value_type>::value) {
            alloc_traits::construct(address_of(new_node->value), move(value));
        }else {
            try {
                alloc_traits::construct(address_of(new_node->value), move(value));
            }catch(...) {
                alloc_traits::operator delete(new_node);
            }
        }
        new_node->next = cursor->next;
        cursor->next = new_node;
        return iterator(new_node);
    }
    template <typename T, typename Allocator>
    inline typename forward_list<T, Allocator>::iterator
    forward_list<T, Allocator>::insert_after(const_iterator pos, rvalue_reference value) {
        auto new_node {forward_list::allocate()};
        if constexpr(is_nothrow_move_constructible<value_type>::value or
                is_nothrow_copy_constructible<value_type>::value) {
            alloc_traits::construct(address_of(new_node->value), move(value));
        }else {
            try {
                alloc_traits::construct(address_of(new_node->value), move(value));
            }catch(...) {
                alloc_traits::operator delete(new_node);
            }
        }
        new_node->next = pos.node->next;
        pos.node->next = new_node;
        return iterator(pos.node);
    }
    template <typename T, typename Allocator>
    template <typename InputIterator>
    inline typename forward_list<T, Allocator>::iterator
    forward_list<T, Allocator>::insert(difference_type pos, typename enable_if<
            is_input_iterator<InputIterator>::value and not is_forward_iterator<InputIterator>::value,
            InputIterator>::type begin, InputIterator end) {
        if(begin == end) {
            return iterator(nullptr);
        }
        auto cursor {this->head};
        while(pos and cursor->next) {
            cursor = cursor->next;
            --pos;
        }
        if(pos) {
            return iterator(nullptr);
        }
        return this->insert_auxiliary(cursor, cursor->next, begin, end);
    }
    template <typename T, typename Allocator>
    template <typename InputIterator>
    inline typename forward_list<T, Allocator>::iterator
    forward_list<T, Allocator>::insert_after(const_iterator pos, typename enable_if<
            is_input_iterator<InputIterator>::value and not is_forward_iterator<InputIterator>::value,
            InputIterator>::type begin, InputIterator end) {
        if(begin == end) {
            return iterator(nullptr);
        }
        return forward_list::insert_auxiliary(pos.node, begin, end);
    }
    template <typename T, typename Allocator>
    template <typename ForwardIterator>
    inline typename forward_list<T, Allocator>::iterator
    forward_list<T, Allocator>::insert(difference_type pos, typename enable_if<
            is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type begin, ForwardIterator end) {
        if(begin == end) {
            return iterator(nullptr);
        }
        auto cursor {this->head};
        while(pos and cursor->next) {
            cursor = cursor->next;
            --pos;
        }
        if(pos) {
            return iterator(nullptr);
        }
        return this->insert_auxiliary(cursor, cursor->next, begin, end);
    }
    template <typename T, typename Allocator>
    template <typename ForwardIterator>
    inline typename forward_list<T, Allocator>::iterator
    forward_list<T, Allocator>::insert_after(const_iterator pos, typename enable_if<
            is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type begin, ForwardIterator end) {
        if(begin == end) {
            return iterator(nullptr);
        }
        return iterator(forward_list::insert_auxiliary(pos.node, pos.node->next, begin, end));
    }
    template <typename T, typename Allocator>
    inline typename forward_list<T, Allocator>::iterator
    forward_list<T, Allocator>::insert(difference_type pos, std::initializer_list<value_type> init_list) {
        return this->insert(pos, init_list.begin(), init_list.end());
    }
    template <typename T, typename Allocator>
    inline typename forward_list<T, Allocator>::iterator
    forward_list<T, Allocator>::insert_after(const_iterator pos, std::initializer_list<value_type> init_list) {
        return forward_list::insert_after(pos, init_list.begin(), init_list.end());
    }
    template <typename T, typename Allocator>
    typename forward_list<T, Allocator>::iterator
    forward_list<T, Allocator>::erase(difference_type pos, size_type size) noexcept {
        if(not this->head or not size) {
            return iterator(nullptr);
        }
        auto cursor {this->head};
        while(pos and cursor->next) {
            cursor = cursor->next;
            --pos;
        }
        if(pos or not cursor->next) {
            return iterator(nullptr);
        }
        auto chasm {cursor};
        auto backup {cursor->next};
        do {
            cursor = backup;
            backup = cursor->next;
            if constexpr(not is_trivially_destructible<value_type>::value) {
                alloc_traits::destroy(address_of(cursor->value));
            }
            alloc_traits::operator delete(cursor);
        }while(--size and backup);
        chasm->next = backup;
        return iterator(backup);
    }
    template <typename T, typename Allocator>
    inline typename forward_list<T, Allocator>::iterator
    forward_list<T, Allocator>::erase_after(const_iterator pos, size_type size) noexcept {
        if(not pos.node or not size) {
            return iterator(nullptr);
        }
        auto cursor {pos.node->next};
        while(size-- and cursor) {
            auto backup {cursor};
            cursor = cursor->next;
            if constexpr(not is_trivially_destructible<value_type>::value) {
                alloc_traits::destroy(address_of(backup->value));
            }
            alloc_traits::operator delete(backup);
        }
        pos.node->next = cursor;
        return iterator(cursor);
    }
    template <typename T, typename Allocator>
    inline typename forward_list<T, Allocator>::iterator
    forward_list<T, Allocator>::erase_after(const_iterator begin, const_iterator end) noexcept {
        if(not begin.node or begin == end) {
            return iterator(nullptr);
        }
        auto cursor {begin.node->next};
        while(cursor not_eq end.node and cursor) {
            auto backup {cursor};
            cursor = cursor->next;
            if constexpr(not is_trivially_destructible<value_type>::value) {
                alloc_traits::destroy(address_of(backup->value));
            }
            alloc_traits::operator delete(backup);
        }
        begin.node->next = end.node;
        return end;
    }
    template <typename T, typename Allocator>
    template <typename ...Args>
    inline typename forward_list<T, Allocator>::iterator
    forward_list<T, Allocator>::emplace_after(difference_type pos, Args &&...args) {
        return this->insert_after(pos, value_type(forward<Args>(args)...));
    }
    template <typename T, typename Allocator>
    template <typename ...Args>
    inline typename forward_list<T, Allocator>::iterator
    forward_list<T, Allocator>::emplace_after(const_iterator pos, Args &&...args) {
        return this->insert_after(pos, value_type(forward<Args>(args)...));
    }
    template <typename T, typename Allocator>
    template <typename ...Args>
    inline void forward_list<T, Allocator>::emplace_front(Args &&...args) {
        this->push_front(value_type(forward<Args>(args)...));
    }
    template <typename T, typename Allocator>
    void forward_list<T, Allocator>::push_front(const_reference value) {
        auto new_node {this->allocate()};
        if constexpr(not is_nothrow_copy_constructible<value_type>::value) {
            alloc_traits::construct(address_of(new_node->value), value);
        }else {
            try {
                alloc_traits::construct(address_of(new_node->value), value);
            }catch(...) {
                alloc_traits::operator delete(new_node);
                this->head->next = nullptr;
                throw;
            }
        }
        const auto next {this->head->next};
        this->head->next = new_node;
        new_node->next = next;
    }
    template <typename T, typename Allocator>
    void forward_list<T, Allocator>::push_front(rvalue_reference value) {
        auto new_node {this->allocate()};
        if constexpr(is_nothrow_move_constructible<value_type>::value or
                is_nothrow_copy_constructible<value_type>::value) {
            alloc_traits::construct(address_of(new_node->value), move(value));
        }else {
            try {
                alloc_traits::construct(address_of(new_node->value), move(value));
            }catch(...) {
                alloc_traits::operator delete(new_node);
                this->head->next = nullptr;
                throw;
            }
        }
        const auto next {this->head->next};
        this->head->next = new_node;
        new_node->next = next;
    }
    template <typename T, typename Allocator>
    void forward_list<T, Allocator>::pop_front() noexcept {
        auto deprecated_node {this->head->next};
        if(not deprecated_node) {
            return;
        }
        const auto next {deprecated_node->next};
        if constexpr(not is_trivially_destructible<value_type>::value) {
            alloc_traits::destroy(address_of(deprecated_node->value));
        }
        alloc_traits::operator delete(deprecated_node);
        this->head->next = next;
    }
}

namespace data_structure {
    template <typename T, typename AllocatorLHS, typename AllocatorRHS>
    inline void swap(forward_list<T, AllocatorLHS> &lhs, forward_list<T, AllocatorRHS> &rhs) noexcept {
        lhs.swap(rhs);
    }
    template <typename T, typename AllocatorLHS, typename AllocatorRHS>
    bool operator==(const forward_list<T, AllocatorLHS> &lhs, const forward_list<T, AllocatorRHS> &rhs) {
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
    bool operator!=(const forward_list<T, AllocatorLHS> &lhs, const forward_list<T, AllocatorRHS> &rhs) {
        return not(lhs == rhs);
    }
    template <typename T, typename AllocatorLHS, typename AllocatorRHS>
    bool operator<(const forward_list<T, AllocatorLHS> &lhs, const forward_list<T, AllocatorRHS> &rhs) {
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
    inline bool operator<=(const forward_list<T, AllocatorLHS> &lhs, const forward_list<T, AllocatorRHS> &rhs) {
        return lhs < rhs or lhs == rhs;
    }
    template <typename T, typename AllocatorLHS, typename AllocatorRHS>
    inline bool operator>(const forward_list<T, AllocatorLHS> &lhs, const forward_list<T, AllocatorRHS> &rhs) {
        return rhs < lhs;
    }
    template <typename T, typename AllocatorLHS, typename AllocatorRHS>
    inline bool operator>=(const forward_list<T, AllocatorLHS> &lhs, const forward_list<T, AllocatorRHS> &rhs) {
        return not(lhs < rhs);
    }
}

namespace data_structure {
    template <typename T, typename Allocator>
    void forward_list<T, Allocator>::merge(forward_list<value_type, Allocator> &rhs)
            noexcept(has_nothrow_less_operator<value_type>::value and
                    has_nothrow_equal_to_operator<value_type>::value) {
        if(not rhs.head->next or &rhs == this) {
            return;
        }
        if(distance(this->cbegin(), this->cend()) < distance(rhs.cbegin(), rhs.cend())) {
            this->swap(rhs);
        }
        auto current_lhs {this->head->next};
        auto current_rhs {rhs.head->next};
        auto before_current {this->head};
        while(current_lhs and current_rhs) {
            if constexpr(has_nothrow_less_operator<value_type>::value and
                    has_nothrow_equal_to_operator<value_type>::value) {
                if(current_rhs->value < current_lhs->value or current_rhs->value == current_lhs->value) {
                    before_current->next = current_rhs;
                    while(current_rhs->next and (current_rhs->next->value < current_lhs->value or
                                                 current_rhs->next->value == current_lhs->value)) {
                        current_rhs = current_rhs->next;
                    }
                    auto backup {current_rhs->next};
                    current_rhs->next = current_lhs;
                    current_rhs = backup;
                }
            }else {
                try {
                    if(current_rhs->value < current_lhs->value or current_rhs->value == current_lhs->value) {
                        before_current->next = current_rhs;
                        while(current_rhs->next and (current_rhs->next->value < current_lhs->value or
                                                     current_rhs->next->value == current_lhs->value)) {
                            current_rhs = current_rhs->next;
                        }
                        auto backup {current_rhs->next};
                        current_rhs->next = current_lhs;
                        current_rhs = backup;
                    }
                }catch(...) {
                    rhs.head->next = current_rhs;
                    throw;
                }
            }
            before_current = current_lhs;
            current_lhs = current_lhs->next;
        }
        if(current_rhs) {
            before_current->next = current_rhs;
        }
        rhs.head->next = nullptr;
    }
    template <typename T, typename Allocator>
    inline void forward_list<T, Allocator>::merge(forward_list &&rhs)
            noexcept(has_nothrow_less_operator<value_type>::value and
                    has_nothrow_equal_to_operator<value_type>::value) {
        this->merge(rhs);
    }
    template <typename T, typename Allocator>
    template <typename AllocatorRHS>
    inline void forward_list<T, Allocator>::merge(forward_list<value_type, AllocatorRHS> &rhs)
            noexcept(has_nothrow_less_operator<value_type>::value and
                     has_nothrow_equal_to_operator<value_type>::value) {
        this->merge(*reinterpret_cast<forward_list *>(&rhs));
    }
    template <typename T, typename Allocator>
    template <typename AllocatorRHS>
    inline void forward_list<T, Allocator>::merge(forward_list<value_type, AllocatorRHS> &&rhs)
            noexcept(has_nothrow_less_operator<value_type>::value and
                   has_nothrow_equal_to_operator<value_type>::value) {
        this->merge(*reinterpret_cast<forward_list *>(&rhs));
    }
    template <typename T, typename Allocator>
    template <typename Compare>
    void forward_list<T, Allocator>::merge(forward_list &rhs, Compare cmp)
            noexcept(has_nothrow_function_call_operator<Compare, value_type, value_type>::value) {
        if(not rhs.head->next or &rhs == this) {
            return;
        }
        if(distance(this->cbegin(), this->cend()) < distance(rhs.cbegin(), rhs.cend())) {
            this->swap(rhs);
        }
        auto current_lhs {this->head->next};
        auto current_rhs {rhs.head->next};
        auto before_current {this->head};
        while(current_lhs and current_rhs) {
            if constexpr(has_nothrow_function_call_operator<Compare, value_type, value_type>::value) {
                if(cmp(current_rhs->value, current_lhs->value)) {
                    before_current->next = current_rhs;
                    while(current_rhs->next and cmp(current_rhs->next->value, current_lhs->value)) {
                        current_rhs = current_rhs->next;
                    }
                    auto backup {current_rhs->next};
                    current_rhs->next = current_lhs;
                    current_rhs = backup;
                }
            }else {
                try {
                    if(cmp(current_rhs->value, current_lhs->value)) {
                        before_current->next = current_rhs;
                        while(current_rhs->next and cmp(current_rhs->next->value, current_lhs->value)) {
                            current_rhs = current_rhs->next;
                        }
                        auto backup {current_rhs->next};
                        current_rhs->next = current_lhs;
                        current_rhs = backup;
                    }
                }catch(...) {
                    rhs.head->next = current_rhs;
                    throw;
                }
            }
            before_current = current_lhs;
            current_lhs = current_lhs->next;
        }
        if(current_rhs) {
            before_current->next = current_rhs;
        }
        rhs.head->next = nullptr;
    }
    template <typename T, typename Allocator>
    template <typename Compare>
    inline void forward_list<T, Allocator>::merge(forward_list &&rhs, Compare cmp)
            noexcept(has_nothrow_function_call_operator<Compare, value_type, value_type>::value) {
        this->merge<typename add_lvalue_reference<Compare>::type>(rhs, cmp);
    }
    template <typename T, typename Allocator>
    template <typename Compare, typename AllocatorRHS>
    inline void forward_list<T, Allocator>::merge(forward_list<value_type, AllocatorRHS> &rhs, Compare cmp)
            noexcept(has_nothrow_function_call_operator<Compare, value_type, value_type>::value) {
        this->merge<typename add_lvalue_reference<Compare>::type>(
                *reinterpret_cast<forward_list *>(&rhs), cmp);
    }
    template <typename T, typename Allocator>
    template <typename Compare, typename AllocatorRHS>
    inline void forward_list<T, Allocator>::merge(forward_list<value_type, AllocatorRHS> &&rhs, Compare cmp)
            noexcept(has_nothrow_function_call_operator<Compare, value_type, value_type>::value) {
        this->merge<typename add_lvalue_reference<Compare>::type>(
                *reinterpret_cast<forward_list *>(&rhs), cmp);
    }
    template <typename T, typename Allocator>
    void forward_list<T, Allocator>::remove(const_reference value)
            noexcept(has_nothrow_equal_to_operator<value_type>::value) {
        auto cursor {this->head};
        auto next {cursor->next};
        while(next) {
            if(next->value == value) {
                auto backup {next};
                next = next->next;
                cursor->next = next;
                this->destroy(backup);
            }
        }
    }
    template <typename T, typename Allocator>
    template <typename UnaryPredicate>
    void forward_list<T, Allocator>::remove_if(UnaryPredicate pred)
            noexcept(has_nothrow_function_call_operator<UnaryPredicate, value_type>::value) {
        auto cursor {this->head};
        auto next {cursor->next};
        while(next) {
            if(UnaryPredicate(next->value)) {
                auto backup {next};
                next = next->next;
                cursor->next = next;
                this->destroy(backup);
            }
        }
    }
    template <typename T, typename Allocator>
    void forward_list<T, Allocator>::reverse() noexcept {
        auto current {this->head->next};
        if(not current) {
            return;
        }
        auto backup {current->next};
        current->next = nullptr;
        while(backup) {
            auto next {backup->next};
            backup->next = current;
            current = backup;
            backup = next;
        }
        this->head->next = current;
    }
}

#endif //DATA_STRUCTURE_FORWARD_LIST_HPP