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

#ifndef DATA_STRUCTURE_BINARY_TREE_HPP
#define DATA_STRUCTURE_BINARY_TREE_HPP

#include "allocator.hpp"
#include "iterator.hpp"

namespace data_structure {
    template <typename T, typename Allocator = allocator<type_holder<T>>>
    class binary_tree final {
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
        using iterator = __dsa::binary_tree_iterator<value_type, false>;
        using const_iterator = __dsa::binary_tree_iterator<value_type, true>;
        using reverse_iterator = ds::reverse_iterator<iterator>;
        using const_reverse_iterator = ds::reverse_iterator<const_iterator>;
    private:
        using node_value_type = __dsa::binary_tree_node<value_type>;
        using node_type = node_value_type *;
        using alloc_traits = allocator_traits<allocator_type>;
        static_assert(is_same_v<value_type, typename alloc_traits::value_type>,
                "The Allocator::value_type must be the same as template argument value_type!");
    public:
        enum class order {
            pre, in, post, level
        };
        enum class children {
            left, right
        };
    private:
        node_type root;
    private:
        [[nodiscard]]
        static node_type node_allocate();
    public:
        constexpr binary_tree() noexcept = default;
        explicit binary_tree(const_reference);
        explicit binary_tree(rvalue_reference);
        binary_tree(const binary_tree &);
        binary_tree(binary_tree &&) noexcept;
        template <typename AllocatorRHS>
        explicit binary_tree(const binary_tree<value_type, AllocatorRHS> &);
        template <typename AllocatorRHS>
        explicit binary_tree(binary_tree<value_type, AllocatorRHS> &&) noexcept;
        ~binary_tree() noexcept;
    public:
        binary_tree &operator=(const binary_tree &);
        binary_tree &operator=(binary_tree &&) noexcept;
        template <typename AllocatorRHS>
        binary_tree &operator=(const binary_tree<value_type, AllocatorRHS> &);
        template <typename AllocatorRHS>
        binary_tree &operator=(binary_tree<value_type, AllocatorRHS> &&) noexcept;
    public:
        void assign(const_reference) noexcept(is_nothrow_copy_assignable_v<value_type>);
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
        size_type size() const noexcept;
        [[nodiscard]]
        size_type level() const noexcept;
        [[nodiscard]]
        bool empty() const noexcept;
        [[nodiscard]]
        constexpr size_type max_size() const noexcept;
        [[nodiscard]]
        reference top() noexcept;
        [[nodiscard]]
        const_reference top() const noexcept;
        void swap(binary_tree &) noexcept;
        template <typename AllocatorRHS>
        void swap(binary_tree<value_type, AllocatorRHS> &) noexcept;
        void clear() noexcept;
        template <typename UnaryPredict>
        void traversal(UnaryPredict, binary_tree::order = binary_tree::order::in);
        iterator insert_under(const_iterator, const_reference, binary_tree::children);
        iterator insert_under(const_iterator, rvalue_reference, binary_tree::children);
        bool insert_under(const_iterator, const_reference);
        void erase_under(const_iterator, binary_tree::children) noexcept;
        void erase_under(const_iterator) noexcept;
        template <typename ...Args>
        iterator emplace_under(const_iterator, binary_tree::children = binary_tree::children::left, Args &&...);
        bool push_front(const_reference, binary_tree::children = binary_tree::children::left);
        bool push_front(rvalue_reference, binary_tree::children = binary_tree::children::left);
        template <typename ...Args>
        bool emplace_front(binary_tree::children = binary_tree::children::left, Args &&...);
    };
}

#endif //DATA_STRUCTURE_BINARY_TREE_HPP