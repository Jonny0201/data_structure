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

#ifndef DATA_STRUCTURE_WINNER_TREE_HPP
#define DATA_STRUCTURE_WINNER_TREE_HPP

#include "allocator.hpp"
#include "iterator.hpp"

namespace data_structure {
    template <typename T, typename Compare = less<>, typename Allocator = allocator<type_holder<T>>>
    class winner_tree final {
    public:
        using allocator_type = Allocator;
        using value_compare = Compare;
        using size_type = allocator_traits_t(allocator_type, size_type);
        using difference_type = allocator_traits_t(allocator_type, difference_type);
        using value_type = T;
        using reference = allocator_traits_t(allocator_type, reference);
        using const_reference = allocator_traits_t(allocator_type, const_reference);
        using rvalue_reference = allocator_traits_t(allocator_type, rvalue_reference);
        using pointer = allocator_traits_t(allocator_type, pointer);
        using const_pointer = allocator_traits_t(allocator_type, const_pointer);
        using iterator = __dsa::binary_tree_iterator<value_type, true>;
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
    private:
        node_type root;
        size_type contestant_size;
    private:
        static node_type node_allocate();
        static node_type *contestant_allocate();
    public:
        constexpr winner_tree() = default;
        explicit winner_tree(value_compare) noexcept(is_nothrow_copy_constructible_v<value_compare> or
                is_nothrow_move_constructible_v<value_compare>);
        template <typename InputIterator> requires is_input_iterator_v<InputIterator>
        winner_tree(InputIterator, InputIterator);
        winner_tree(initializer_list<value_type>);
        winner_tree(const winner_tree &);
        winner_tree(winner_tree &&) noexcept;
        template <typename AllocatorRHS>
        winner_tree(const winner_tree<value_type, value_compare, AllocatorRHS> &);
        template <typename AllocatorRHS>
        winner_tree(winner_tree<value_type, value_compare, AllocatorRHS> &&) noexcept;
        ~winner_tree() noexcept;
    public:
        winner_tree &operator=(const winner_tree &);
        winner_tree &operator=(winner_tree &&) noexcept;
        template <typename AllocatorRHS>
        winner_tree &operator=(const winner_tree<value_type, value_compare, AllocatorRHS> &);
        template <typename AllocatorRHS>
        winner_tree &operator=(winner_tree<value_type, value_compare, AllocatorRHS> &&) noexcept;
        winner_tree &operator=(initializer_list<value_type>);
        reference operator[](difference_type) noexcept;
        const_reference operator[](difference_type) const noexcept;
    public:
        template <typename InputIterator> requires is_input_iterator_v<InputIterator>
        void assign(InputIterator, InputIterator);
        void assign(initializer_list<value_type>);
        [[nodiscard]]
        iterator begin() noexcept;
        [[nodiscard]]
        const_iterator begin() const noexcept;
        [[nodiscard]]
        iterator tbegin() noexcept;
        [[nodiscard]]
        const_iterator tbegin() const noexcept;
        [[nodiscard]]
        constexpr iterator end() noexcept;
        [[nodiscard]]
        constexpr const_iterator end() const noexcept;
        [[nodiscard]]
        const_iterator cbegin() const noexcept;
        [[nodiscard]]
        const_iterator ctbegin() const noexcept;
        [[nodiscard]]
        constexpr const_iterator cend() const noexcept;
        [[nodiscard]]
        reverse_iterator rbegin() noexcept;
        [[nodiscard]]
        const_reverse_iterator rbegin() const noexcept;
        [[nodiscard]]
        reverse_iterator rtbegin() noexcept;
        [[nodiscard]]
        const_reverse_iterator rtbegin() const noexcept;
        [[nodiscard]]
        constexpr reverse_iterator rend() noexcept;
        [[nodiscard]]
        constexpr const_reverse_iterator rend() const noexcept;
        [[nodiscard]]
        const_reverse_iterator crbegin() const noexcept;
        [[nodiscard]]
        const_reverse_iterator crtbegin() const noexcept;
        [[nodiscard]]
        constexpr const_reverse_iterator crend() const noexcept;
        [[nodiscard]]
        size_type size() const noexcept;
        [[nodiscard]]
        constexpr bool empty() const noexcept;
        [[nodiscard]]
        constexpr size_type max_size() const noexcept;
        [[nodiscard]]
        const_reference top() const noexcept;
        [[nodiscard]]
        value_type winner(difference_type) const noexcept;
        [[nodiscard]]
        value_type champion() const noexcept;
        [[nodiscard]]
        const_reference at(difference_type) const noexcept;
        [[nodiscard]]
        const_pointer data() const noexcept;
        void swap(winner_tree &) noexcept;
        template <typename AllocatorRHS>
        void swap(winner_tree<value_type, value_compare, AllocatorRHS> &) noexcept;
        void clear() noexcept;
        template <typename UnaryPrediction>
        void traversal(UnaryPrediction, winner_tree::order = winner_tree::order::in) const
                noexcept(has_nothrow_function_call_operator_v<UnaryPrediction, const_reference>);
        template <typename UnaryPrediction>
        void contestant_traversal(UnaryPrediction) const
                noexcept(has_nothrow_function_call_operator_v<UnaryPrediction, const_reference>);
        template <typename BinaryFunction>
        void contest(BinaryFunction) const
                noexcept(has_nothrow_function_call_operator_v<BinaryFunction, const_reference, const_reference>);
        const_reference insert(const_reference, difference_type = -1);
        const_reference insert(const_iterator, const_reference);
        const_reference insert(rvalue_reference, difference_type = -1);
        const_reference insert(const_iterator, rvalue_reference);
        template <typename InputIterator> requires is_input_iterator_v<InputIterator>
        const_reference insert(InputIterator, InputIterator, difference_type = -1);
        template <typename InputIterator> requires is_input_iterator_v<InputIterator>
        const_reference insert(const_iterator, InputIterator, InputIterator);
        const_reference insert(initializer_list<value_type>, difference_type = -1);
        const_reference insert(const_iterator, initializer_list<value_type>);
        const_reference erase(difference_type, size_type = 1);
        const_reference erase(const_iterator);
        const_reference erase(const_iterator, const_iterator);
        template <typename ...Args>
        const_reference emplace(difference_type, Args &&...);
        template <typename ...Args>
        const_reference emplace(const_iterator, Args &&...);
        const_reference push_front(const_reference);
        const_reference push_front(rvalue_reference);
        const_reference push_back(const_reference);
        const_reference push_back(rvalue_reference);
        template <typename ...Args>
        const_reference emplace_front(Args &&...);
        template <typename ...Args>
        const_reference emplace_back(Args &&...);
        void pop_front() noexcept;
        void pop_back() noexcept;
    };
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    void swap(winner_tree<T, AllocatorLHS> &, winner_tree<T, AllocatorRHS> &) noexcept;
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    bool operator==(const winner_tree<T, AllocatorLHS> &, const winner_tree<T, AllocatorRHS> &)
            noexcept(has_nothrow_equal_to_operator_v<T>);
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    bool operator!=(const winner_tree<T, AllocatorLHS> &, const winner_tree<T, AllocatorRHS> &)
            noexcept(has_nothrow_equal_to_operator_v<T>);
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    bool operator<(const winner_tree<T, AllocatorLHS> &, const winner_tree<T, AllocatorRHS> &)
            noexcept(has_nothrow_less_operator_v<T>);
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    bool operator<=(const winner_tree<T, AllocatorLHS> &, const winner_tree<T, AllocatorRHS> &)
            noexcept(has_nothrow_less_operator_v<T>);
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    bool operator>(const winner_tree<T, AllocatorLHS> &, const winner_tree<T, AllocatorRHS> &)
            noexcept(has_nothrow_less_operator_v<T>);
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    bool operator>=(const winner_tree<T, AllocatorLHS> &, const winner_tree<T, AllocatorRHS> &)
            noexcept(has_nothrow_less_operator_v<T>);
}

#endif //DATA_STRUCTURE_WINNER_TREE_HPP
