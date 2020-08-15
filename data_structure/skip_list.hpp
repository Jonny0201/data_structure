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

#ifndef DATA_STRUCTURE_SKIP_LIST_HPP
#define DATA_STRUCTURE_SKIP_LIST_HPP

#include "allocator.hpp"
#include "iterator.hpp"

namespace data_structure::__data_structure_auxiliary {
    static constexpr inline double skip_list_probability() noexcept {
        return 0.5;
    }
    static inline size_t skip_list_random() noexcept {
        static std::random_device d {};
        static std::default_random_engine e(d());
        static std::uniform_real_distribution<double> u(0.0, 1.0);
        return u(e);
    }
}

namespace data_structure {
    template <typename T, typename Allocator = allocator<type_holder<T>>, typename Compare = less<T, T>,
            typename Random = decltype(__dsa::skip_list_probability) *,
            typename Probability = decltype(__dsa::skip_list_random) *>
    class skip_list {
    public:
        using allocator_type = Allocator;
        using value_compare = Compare;
        using random_number_generator = Random;
        using probability_generator = Probability;
        using size_type = allocator_traits_t(allocator_type, size_type);
        using difference_type = allocator_traits_t(allocator_type, difference_type);
        using value_type = T;
        using reference = allocator_traits_t(allocator_type, reference);
        using const_reference = allocator_traits_t(allocator_type, const_reference);
        using rvalue_reference = allocator_traits_t(allocator_type, rvalue_reference);
        using pointer = allocator_traits_t(allocator_type, pointer);
        using const_pointer = allocator_traits_t(allocator_type, const_pointer);
        using iterator = __dsa::skip_list_iterator<T, false>;
        using const_iterator = __dsa::skip_list_iterator<T, true>;
    private:
        using alloc_traits = allocator_traits<allocator_type>;
        using node_value_type = __dsa::skip_list_node<T>;
        using node_type = node_value_type *;
        static_assert(is_same_v<T, allocator_traits_t(allocator_type, value_type)>,
                "The deque holds different value_types");
    private:
        node_type head;
        value_compare compare;
        random_number_generator random;
        probability_generator probability;
    private:
        static node_type allocate();
        static node_type construct(size_type);
    public:
        skip_list();
        explicit skip_list(size_type);
        skip_list(size_type, const_reference);
        explicit skip_list(const value_compare &);
        explicit skip_list(const random_number_generator &);
        explicit skip_list(const probability_generator &);
        skip_list(const random_number_generator &, const probability_generator &);
        skip_list(const value_compare &, const random_number_generator &, const probability_generator &);
        template <typename Iterator>
        skip_list(enable_if_t<is_input_iterator_v<Iterator>, Iterator>, Iterator);
        skip_list(initializer_list<value_type>);
        skip_list(const skip_list &);
        skip_list(skip_list &&) noexcept;
        template <typename AllocatorRHS>
        skip_list(const skip_list<value_type, AllocatorRHS, value_compare,
                random_number_generator, probability_generator> &);
        template <typename AllocatorRHS>
        skip_list(skip_list<value_type, AllocatorRHS, value_compare,
                random_number_generator, probability_generator> &&);
        ~skip_list() noexcept;
    public:
        skip_list &operator=(const skip_list &);
        skip_list &operator=(skip_list &&) noexcept;
        template <typename AllocatorRHS>
        skip_list &operator=(const skip_list<value_type, AllocatorRHS, value_compare,
                random_number_generator, probability_generator> &);
        template <typename AllocatorRHS>
        skip_list &operator=(skip_list<value_type, AllocatorRHS, value_compare,
                random_number_generator, probability_generator> &&);
        skip_list &operator=(initializer_list<value_type>);
        skip_list &operator=(const random_number_generator &);
        skip_list &operator=(random_number_generator &&);
        skip_list &operator=(const probability_generator &);
        skip_list &operator=(probability_generator &&);
    public:
        void assign(size_type, const_reference = {});
        template <typename Iterator>
        void assign(enable_if_t<is_input_iterator_v<Iterator>, Iterator>, Iterator);
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
        void swap(skip_list &) noexcept;
        template <typename AllocatorRHS>
        void swap(skip_list<value_type, AllocatorRHS, value_compare,
                random_number_generator, probability_generator> &) noexcept;
        void resize(size_type, const_reference = {});
        iterator insert(const_reference, size_type = 1);
        iterator insert(rvalue_reference);
        template <typename Iterator>
        iterator insert(enable_if_t<is_input_iterator_v<Iterator>, Iterator>, Iterator);
        iterator insert(initializer_list<value_type>);
        iterator erase(difference_type, size_type = 1) noexcept;
        static iterator erase_after(const_iterator, size_type = 1) noexcept;
        static iterator erase_after(const_iterator, const_iterator) noexcept;
        static iterator erase_after(const_iterator) noexcept;
        iterator remove(const_reference) noexcept;
        void unique() noexcept;
        template <typename BinaryPredicate>
        void unique(BinaryPredicate) noexcept;
        template <typename ...Args>
        iterator emplace(Args &&...);
        template <typename ...Args>
        iterator emplace(size_type, Args &&...);
        void pop_front() noexcept;
        template <typename ...Args>
        random_number_generator reset_random_number_generator(Args &&...);
        template <typename ...Args>
        probability_generator reset_probability_generator(Args &&...);
    };
}
