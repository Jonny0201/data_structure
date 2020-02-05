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
    public:
        constexpr list() noexcept = default;
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
        iterator begin() noexcept;
        const_iterator begin() const noexcept;
        iterator end() noexcept;
        const_iterator end() const noexcept;
        const_iterator cbegin() const noexcept;
        const_iterator cend() const noexcept;
        reverse_iterator rbegin() noexcept;
        const_reverse_iterator rbegin() const noexcept;
        reverse_iterator rend() noexcept;
        const_reverse_iterator rend() const noexcept;
        const_reverse_iterator crbegin() const noexcept;
        const_reverse_iterator crend() const noexcept;
        reference front() noexcept;
        const_reference front() const noexcept;
        reference back() noexcept;
        const_reference back() const noexcept;
        bool empty() const noexcept;
        size_type size() const noexcept;
        constexpr size_type max_size() const noexcept;
        iterator insert(difference_type, const_reference, size_type = 1);
        static iterator insert(const_iterator, const_reference, size_type = 1);
        iterator insert(difference_type, rvalue_reference);
        static iterator insert(const_iterator, rvalue_reference);
        template <typename InputIterator>
        iterator insert(difference_type, typename enable_if<
                is_input_iterator<InputIterator>::value and not is_forward_iterator<InputIterator>::value,
                InputIterator>::type, InputIterator);
        template <typename InputIterator>
        static iterator insert(const_iterator, typename enable_if<
                is_input_iterator<InputIterator>::value and not is_forward_iterator<InputIterator>::value,
                InputIterator>::type, InputIterator);
        template <typename ForwardIterator>
        iterator insert(difference_type, typename enable_if<is_forward_iterator<ForwardIterator>::value,
                ForwardIterator>::type, ForwardIterator);
        template <typename ForwardIterator>
        static iterator insert(const_iterator, typename enable_if<is_forward_iterator<ForwardIterator>::value,
                ForwardIterator>::type, ForwardIterator);
        iterator insert(difference_type, std::initializer_list<value_type>);
        static iterator insert(const_iterator, std::initializer_list<value_type>);
        iterator erase(difference_type, size_type = 1) noexcept;
        iterator erase(const_iterator, size_type = 1) noexcept;
        iterator erase(const_iterator, const_iterator) noexcept;
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

#endif //DATA_STRUCTURE_LIST_HPP
