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

#include "buffer.hpp"

namespace data_structure::__data_structure_auxiliary {
    template <typename SizeType, typename Compare, bool>
    struct winner_tree_compress_auxiliary {
    public:
        SizeType size;
        Compare c;
    public:
        constexpr winner_tree_compress_auxiliary() = default;
        explicit winner_tree_compress_auxiliary(SizeType s) : size {ds::move(s)}, c {} {}
        explicit winner_tree_compress_auxiliary(Compare c) : size {}, c {ds::move(c)} {}
        winner_tree_compress_auxiliary(SizeType s, Compare c) : size {ds::move(s)}, c {ds::move(c)} {}
    public:
        Compare &compare() noexcept {
            return this->c;
        }
        const Compare &compare() const noexcept {
            return this->c;
        }
    };
    template <typename SizeType, typename Compare>
    struct winner_tree_compress_auxiliary<SizeType, Compare, true> : Compare {
    public:
        SizeType size;
    public:
        constexpr winner_tree_compress_auxiliary() = default;
        explicit winner_tree_compress_auxiliary(SizeType s) : size {ds::move(s)}, Compare {} {}
        explicit winner_tree_compress_auxiliary(Compare) : size {}, Compare {} {}
        winner_tree_compress_auxiliary(SizeType s, Compare) : size {ds::move(s)}, Compare {} {}
    public:
        Compare &compare() noexcept {
            return static_cast<Compare &>(*this);
        }
        const Compare &compare() const noexcept {
            return static_cast<Compare &>(*this);
        }
    };
    template <typename SizeType, typename Compare>
    using winner_tree_comparess_with_size_type = winner_tree_compress_auxiliary<SizeType, Compare,
            is_empty_v<Compare> and not is_final_v<Compare>>;
}

namespace data_structure {
    template <typename T, typename Compare = greater<>, size_t Group = 2,
            typename Allocator = allocator<type_holder<T>>>
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
        using iterator = __dsa::winner_tree_iterator<value_type>;
        using const_iterator = __dsa::winner_tree_iterator<value_type>;
    private:
        using contestant_value_type = __dsa::winner_tree_contestant_node<value_type>;
        using contestant_type = contestant_value_type *;
        using competition_value_type = __dsa::winner_tree_competition_node<value_type>;
        using competition_type = competition_value_type *;
        using alloc_traits = allocator_traits<allocator_type>;
        static_assert(is_same_v<value_type, typename alloc_traits::value_type>,
                "The Allocator::value_type must be the same as template argument value_type!");
        static_assert(Group >= 2, "The number of members in the Group must be greater than 2!");
    private:
        constexpr static auto trivial_copy_assignment {is_trivially_copy_assignable_v<contestant_value_type>};
        constexpr static auto trivial_destruction {is_trivially_destructible_v<value_type>};
        constexpr static auto nothrow_copy_construction {is_nothrow_copy_constructible_v<value_type>};
        constexpr static auto nothrow_move_construction {is_nothrow_move_constructible_v<value_type>};
        constexpr static auto nothrow_move_or_copy_construction {
            nothrow_move_construction or nothrow_copy_construction};
    private:
        __dsa::winner_tree_comparess_with_size_type<size_type, value_compare> contestant_size;
        contestant_type contestant;
    private:
        static contestant_type contestant_allocate(size_type);
        static competition_type competition_allocate(size_type);
        static void fill(contestant_type, contestant_type, size_type, contestant_type, contestant_type, size_type);
        template <typename CompetitionType>
        static difference_type max(CompetitionType, difference_type, difference_type, value_compare &)
                noexcept(has_nothrow_function_call_operator_v<value_compare, reference, reference>);
        static constexpr size_type parent_size(size_type) noexcept;
    private:
        competition_type tournament(contestant_type, size_type, size_type, value_compare &);
        void tournament(contestant_type, size_type);
        void deallocate() noexcept;
        competition_type top_node() const noexcept;
        const_reference max_k(contestant_type *, difference_type, difference_type, difference_type);
        template <typename ForwardIterator>
        void insert_auxiliary(difference_type, ForwardIterator, ForwardIterator);
        void rematch(competition_type, difference_type, size_type, value_compare &)
                noexcept(has_nothrow_function_call_operator_v<value_compare, reference, reference>);
    private:
        template <typename InputIterator>
        winner_tree(InputIterator, InputIterator, false_type);
        template <typename ForwardIterator>
        winner_tree(ForwardIterator, ForwardIterator, true_type);
    public:
        constexpr winner_tree() = default;
        explicit constexpr winner_tree(value_compare) noexcept(is_nothrow_copy_constructible_v<value_compare> or
                is_nothrow_move_constructible_v<value_compare>);
        template <typename InputIterator> requires is_input_iterator_v<InputIterator>
        winner_tree(InputIterator, InputIterator);
        winner_tree(initializer_list<value_type>);
        winner_tree(const winner_tree &);
        winner_tree(winner_tree &&) noexcept;
        ~winner_tree() noexcept;
    public:
        winner_tree &operator=(const winner_tree &);
        winner_tree &operator=(winner_tree &&) noexcept;
        winner_tree &operator=(initializer_list<value_type>);
        [[nodiscard]]
        const_reference operator[](difference_type) const;
    public:
        template <typename InputIterator> requires is_input_iterator_v<InputIterator>
        void assign(InputIterator, InputIterator);
        void assign(initializer_list<value_type>);
        [[nodiscard]]
        const_iterator begin() const noexcept;
        [[nodiscard]]
        const_iterator end() const noexcept;
        [[nodiscard]]
        const_iterator cbegin() const noexcept;
        [[nodiscard]]
        const_iterator cend() const noexcept;
        [[nodiscard]]
        size_type size() const noexcept;
        [[nodiscard]]
        size_type round() const noexcept;
        [[nodiscard]]
        bool empty() const noexcept;
        [[nodiscard]]
        const_reference top() const noexcept;
        [[nodiscard]]
        value_type winner(difference_type) const;
        [[nodiscard]]
        value_type winner(const_iterator) const;
        [[nodiscard]]
        value_type champion() const noexcept;
        [[nodiscard]]
        const_reference at(difference_type) const;
        [[nodiscard]]
        const_reference at(const_iterator) const;
        void swap(winner_tree &) noexcept;
        void clear() noexcept;
        const_reference insert(difference_type, const_reference);
        const_reference insert(const_iterator, const_reference);
        const_reference insert(difference_type, rvalue_reference);
        const_reference insert(const_iterator, rvalue_reference);
        template <typename InputIterator> requires is_input_iterator_v<InputIterator>
        const_reference insert(difference_type, InputIterator, InputIterator);
        template <typename InputIterator> requires is_input_iterator_v<InputIterator>
        const_reference insert(const_iterator, InputIterator, InputIterator);
        const_reference insert(difference_type, initializer_list<value_type>);
        const_reference insert(const_iterator, initializer_list<value_type>);
        const_reference erase(difference_type, size_type = 1);
        const_reference erase(const_iterator);
        const_reference erase(const_iterator, const_iterator);
        template <typename ...Args>
        const_reference emplace(difference_type, Args &&...);
        template <typename ...Args>
        const_reference emplace(const_iterator, Args &&...);
        template <typename ...Args>
        const_reference replace(difference_type, Args &&...)
                noexcept(has_nothrow_function_call_operator_v<value_compare, reference, reference> and
                        is_nothrow_move_assignable_v<value_type>);
        template <typename ...Args>
        const_reference replace(const_iterator, Args &&...)
                noexcept(has_nothrow_function_call_operator_v<value_compare, reference, reference> and
                        is_nothrow_move_assignable_v<value_type>);
        const_reference pop();
    public:
        value_compare &compare() noexcept;
        const value_compare &compare() const noexcept;
    };
    template <typename T, typename Compare, size_t Group, typename Allocator>
    void swap(winner_tree<T, Compare, Group, Allocator> &, winner_tree<T, Compare, Group, Allocator> &) noexcept;
    template <typename T, typename CompareLHS, typename CompareRHS, size_t GroupLHS, size_t GroupRHS,
            typename AllocatorLHS, typename AllocatorRHS>
    bool operator==(const winner_tree<T, CompareLHS, GroupLHS, AllocatorLHS> &,
            const winner_tree<T, CompareRHS, GroupRHS, AllocatorRHS> &) noexcept(has_nothrow_equal_to_operator_v<T>);
    template <typename T, typename CompareLHS, typename CompareRHS, size_t GroupLHS, size_t GroupRHS,
            typename AllocatorLHS, typename AllocatorRHS>
    bool operator!=(const winner_tree<T, CompareLHS, GroupLHS, AllocatorLHS> &,
            const winner_tree<T, CompareRHS, GroupRHS, AllocatorRHS> &) noexcept(has_nothrow_equal_to_operator_v<T>);
    template <typename T, typename CompareLHS, typename CompareRHS, size_t GroupLHS, size_t GroupRHS,
            typename AllocatorLHS, typename AllocatorRHS>
    bool operator<(const winner_tree<T, CompareLHS, GroupLHS, AllocatorLHS> &,
            const winner_tree<T, CompareRHS, GroupRHS, AllocatorRHS> &) noexcept(has_nothrow_less_operator_v<T>);
    template <typename T, typename CompareLHS, typename CompareRHS, size_t GroupLHS, size_t GroupRHS,
            typename AllocatorLHS, typename AllocatorRHS>
    bool operator<=(const winner_tree<T, CompareLHS, GroupLHS, AllocatorLHS> &,
            const winner_tree<T, CompareRHS, GroupRHS, AllocatorRHS> &) noexcept(has_nothrow_less_operator_v<T>);
    template <typename T, typename CompareLHS, typename CompareRHS, size_t GroupLHS, size_t GroupRHS,
            typename AllocatorLHS, typename AllocatorRHS>
    bool operator>(const winner_tree<T, CompareLHS, GroupLHS, AllocatorLHS> &,
            const winner_tree<T, CompareRHS, GroupRHS, AllocatorRHS> &) noexcept(has_nothrow_less_operator_v<T>);
    template <typename T, typename CompareLHS, typename CompareRHS, size_t GroupLHS, size_t GroupRHS,
            typename AllocatorLHS, typename AllocatorRHS>
    bool operator>=(const winner_tree<T, CompareLHS, GroupLHS, AllocatorLHS> &,
            const winner_tree<T, CompareRHS, GroupRHS, AllocatorRHS> &) noexcept(has_nothrow_less_operator_v<T>);
}

namespace data_structure {
    /* private functions */
    template <typename T, typename Compare, size_t Group, typename Allocator>
    typename winner_tree<T, Compare, Group, Allocator>::contestant_type
    winner_tree<T, Compare, Group, Allocator>::contestant_allocate(size_type n) {
        return static_cast<contestant_type>(alloc_traits::operator new(sizeof(contestant_value_type) * n));
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    typename winner_tree<T, Compare, Group, Allocator>::competition_type
    winner_tree<T, Compare, Group, Allocator>::competition_allocate(size_type n) {
        return static_cast<competition_type>(alloc_traits::operator new(sizeof(competition_value_type) * n));
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    void winner_tree<T, Compare, Group, Allocator>::fill(contestant_type left, contestant_type new_left,
            size_type left_size, contestant_type right, contestant_type new_right, size_type right_size) {
        if constexpr(trivial_copy_assignment) {
            ds::memory_copy(new_left, left, sizeof(contestant_value_type) * left_size);
            ds::memory_copy(new_right, right, sizeof(contestant_value_type) * right_size);
        }else {
            if constexpr(nothrow_move_or_copy_construction) {
                for(auto i {0}; i < left_size; ++i) {
                    alloc_traits::construct(ds::address_of(new_left[i].value), left[i].value);
                }
                for(auto i {0}; i < right_size; ++i) {
                    alloc_traits::construct(ds::address_of(new_right[i].value), right[i].value);
                }
            }else {
                difference_type i {0};
                try {
                    for(; i < left_size; ++i) {
                        alloc_traits::construct(ds::address_of(new_left[i].value), left[i].value);
                    }
                }catch(...) {
                    if constexpr(not trivial_destruction) {
                        for(auto j {0}; j < i; ++j) {
                            alloc_traits::destroy(ds::address_of(new_left[j].value));
                        }
                    }
                    alloc_traits::operator delete(new_left);
                    throw;
                }
                i = 0;
                try {
                    for(; i < right_size; ++i) {
                        alloc_traits::construct(ds::address_of(new_right[i].value), right[i].value);
                    }
                }catch(...) {
                    if constexpr(not trivial_destruction) {
                        for(auto j {0}; j < i; ++j) {
                            alloc_traits::destroy(ds::address_of(new_left[j].value));
                        }
                        for(i = 0; i < left_size; ++i) {
                            alloc_traits::destroy(ds::address_of(new_left[i].value));
                        }
                    }
                    alloc_traits::operator delete(new_left);
                    throw;
                }
            }
        }
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    typename winner_tree<T, Compare, Group, Allocator>::const_reference
    winner_tree<T, Compare, Group, Allocator>::max_k(contestant_type *begin, difference_type left,
            difference_type right, difference_type k) {
        auto &compare {this->contestant_size.compare()};
        switch(this->contestant_size.size) {
            case 1:
                return this->contestant->value;
            case 2:
                return compare(this->contestant->value, this->contestant[1].value) ?
                        this->contestant->value : this->contestant[1].value;
            case 3:
                if(compare(this->contestant->value, this->contestant[1].value)) {
                    return compare(this->contestant->value, this->contestant[2].value) ?
                            this->contestant->value : this->contestant[2].value;
                }
                return compare(this->contestant[1].value, this->contestant[2].value) ?
                        this->contestant[1].value : this->contestant[2].value;
            default:
                break;
        }
        auto pivot {begin[right]};
        auto move_flag {true};
        auto left_cursor {left}, right_cursor {right};
        while(left_cursor not_eq right_cursor) {
            if(move_flag) {
                while(compare(begin[left_cursor]->value, pivot->value) and left_cursor < right_cursor) {
                    ++left_cursor;
                }
                if(left_cursor < right_cursor) {
                    begin[right_cursor--] = begin[left_cursor];
                    move_flag = false;
                    continue;
                }
            }else {
                while(compare(pivot->value, begin[right_cursor]->value) and left_cursor < right_cursor) {
                    --right_cursor;
                }
                if(left_cursor < right_cursor) {
                    begin[left_cursor++] = begin[right_cursor];
                    move_flag = true;
                    continue;
                }
            }
        }
        begin[left_cursor] = pivot;
        if(left_cursor < k) {
            return this->max_k(begin, left_cursor + 1, right, k);
        }else if(left_cursor > k) {
            return this->max_k(begin, left, left_cursor - 1, k);
        }
        return pivot->value;
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    template <typename CompetitionType>
    typename winner_tree<T, Compare, Group, Allocator>::difference_type
    winner_tree<T, Compare, Group, Allocator>::max(CompetitionType contestant, difference_type start,
            difference_type end, value_compare &compare)
            noexcept(has_nothrow_function_call_operator_v<value_compare, reference, reference>) {
        auto min {start};
        for(auto i {start + 1}; i < end; ++i) {
            if constexpr(is_same_v<CompetitionType, contestant_type>) {
                if(compare(contestant[i].value, contestant[min].value)) {
                    min = i;
                }
            }else {
                if(compare(contestant[i].winner->value, contestant[min].winner->value)) {
                    min = i;
                }
            }
        }
        return min;
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    constexpr typename winner_tree<T, Compare, Group, Allocator>::size_type
    winner_tree<T, Compare, Group, Allocator>::parent_size(size_type size) noexcept {
        return size / Group + (size % Group == 0 ? 0 : 1);
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    typename winner_tree<T, Compare, Group, Allocator>::competition_type
    winner_tree<T, Compare, Group, Allocator>::tournament(contestant_type contestant,
            size_type size, size_type parent_size, value_compare &cmp) {
        auto competition_parent {[&]() -> competition_type {
            try {
                return this->competition_allocate(parent_size);
            }catch(...) {
                if constexpr(not trivial_destruction) {
                    for(auto i {0}; i < size; ++i) {
                        alloc_traits::destroy(ds::address_of(contestant[i].value));
                    }
                }
                alloc_traits::operator delete(contestant);
                throw;
            }
        }()};
        if constexpr(has_nothrow_function_call_operator_v<value_compare, reference, reference>) {
            for(auto i {0}, j {0};; i += Group, static_cast<void>(++j)) {
                if(j + 1 == parent_size) {
                    const auto left {size - i};
                    switch(left) {
                        case 0:
                            break;
                        case 1:
                            contestant[i].parent = competition_parent + j;
                            competition_parent[j].winner = contestant + i;
                            break;
                        case 2:
                            competition_parent[j].winner = cmp(contestant[i].value, contestant[i + 1].value) ?
                                    contestant + i : contestant + (i + 1);
                            contestant[i].parent = contestant[i + 1].parent = competition_parent + j;
                            break;
                        default:
                            competition_parent[j].winner = contestant + this->max(contestant, i, size, cmp);
                            for(auto k {i}; k < size; ++k) {
                                contestant[k].parent = competition_parent + j;
                            }
                            break;
                    }
                    break;
                }
                if constexpr(Group == 2) {
                    competition_parent[j].winner = cmp(contestant[i].value, contestant[i + 1].value) ?
                            contestant + i : contestant + (i + 1);
                    contestant[i].parent = contestant[i + 1].parent = competition_parent + j;
                }else if constexpr(Group == 3) {
                    if(cmp(contestant[i].value, contestant[i + 1].value)) {
                        if(cmp(contestant[i].value, contestant[i + 2].value)) {
                            competition_parent[j].winner = contestant + i;
                        }else {
                            competition_parent[j].winner = contestant + (i + 2);
                        }
                    }else {
                        if(cmp(contestant[i + 1].value, contestant[i + 2].value)) {
                            competition_parent[j].winner = contestant + (i + 1);
                        }else {
                            competition_parent[j].winner = contestant + (i + 2);
                        }
                    }
                    contestant[i].parent = contestant[i + 1].parent =
                            contestant[i + 2].parent = competition_parent + j;
                }else {
                    const auto end {i + static_cast<difference_type>(Group)};
                    competition_parent[j].winner = contestant + this->max(contestant, i, end, cmp);
                    for(auto k {i}; k < end; ++k) {
                        contestant[k].parent = competition_parent + j;
                    }
                }
            }
        }else {
            try {
                for(auto i {0}, j {0};; i += Group, static_cast<void>(++j)) {
                    if(j + 1 == parent_size) {
                        const auto left {size - i};
                        switch(left) {
                            case 0:
                                break;
                            case 1:
                                contestant[i].parent = competition_parent + j;
                                competition_parent[j].winner = contestant + i;
                                break;
                            case 2:
                                competition_parent[j].winner = cmp(contestant[i].value, contestant[i + 1].value) ?
                                        contestant + i : contestant + (i + 1);
                                contestant[i].parent = contestant[i + 1].parent = competition_parent + j;
                                break;
                            default:
                                competition_parent[j].winner = contestant + this->max(contestant, i, size, cmp);
                                for(auto k {i}; k < size; ++k) {
                                    contestant[k].parent = competition_parent + j;
                                }
                                break;
                        }
                        break;
                    }
                    if constexpr(Group == 2) {
                        competition_parent[j].winner = cmp(contestant[i].value, contestant[i + 1].value) ?
                                contestant + i : contestant + (i + 1);
                        contestant[i].parent = contestant[i + 1].parent = competition_parent + j;
                    }else if constexpr(Group == 3) {
                        if(cmp(contestant[i].value, contestant[i + 1].value)) {
                            if(cmp(contestant[i].value, contestant[i + 2].value)) {
                                competition_parent[j].winner = contestant + i;
                            }else {
                                competition_parent[j].winner = contestant + (i + 2);
                            }
                        }else {
                            if(cmp(contestant[i + 1].value, contestant[i + 2].value)) {
                                competition_parent[j].winner = contestant + (i + 1);
                            }else {
                                competition_parent[j].winner = contestant + (i + 2);
                            }
                        }
                        contestant[i].parent = contestant[i + 1].parent =
                                contestant[i + 2].parent = competition_parent + j;
                    }else {
                        const auto end {i + static_cast<difference_type>(Group)};
                        competition_parent[j].winner = contestant + this->max(contestant, i, end, cmp);
                        for(auto k {i}; k < end; ++k) {
                            contestant[k].parent = competition_parent + j;
                        }
                    }
                }
            }catch(...) {
                if constexpr(not trivial_destruction) {
                    for(auto i {0}; i < size; ++i) {
                        alloc_traits::destroy(ds::address_of(contestant[i].value));
                    }
                }
                alloc_traits::operator delete(contestant);
                alloc_traits::operator delete(competition_parent);
                throw;
            }
        }
        return competition_parent;
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    void winner_tree<T, Compare, Group, Allocator>::tournament(contestant_type contestant, size_type size) {
        auto parent_size {this->parent_size(size)};
        auto &cmp {this->contestant_size.compare()};
        auto competition {this->tournament(contestant, size, parent_size, cmp)};
        const auto size_backup {size};
        size = parent_size;
        parent_size = this->parent_size(size);
        auto competition_parent {[&]() -> competition_type {
            try {
                return this->competition_allocate(parent_size);
            }catch(...) {
                if constexpr(not trivial_destruction) {
                    for(auto i {0}; i < size_backup; ++i) {
                        alloc_traits::destroy(ds::address_of(contestant[i].value));
                    }
                }
                alloc_traits::operator delete(contestant);
                alloc_traits::operator delete(competition);
                throw;
            }
        }()};
        if constexpr(has_nothrow_function_call_operator_v<value_compare, reference, reference>) {
            while(true) {
                for(auto i {0}, j {0};; i += Group, static_cast<void>(++j)) {
                    if(j + 1 == parent_size) {
                        auto left {size - i};
                        switch(left) {
                            case 0:
                                break;
                            case 1:
                                competition[i].parent = competition_parent + j;
                                competition_parent[j].winner = competition[i].winner;
                                break;
                            case 2:
                                competition_parent[j].winner =
                                        cmp(competition[i].winner->value, competition[i + 1].winner->value) ?
                                        competition[i].winner : competition[i + 1].winner;
                                competition[i].parent = competition[i + 1].parent = competition_parent + j;
                                break;
                            default:
                                competition_parent[j].winner =
                                        competition[this->max(competition, i, size, cmp)].winner;
                                for(auto k {i}; k < size; ++k) {
                                    competition[k].parent = competition_parent + j;
                                }
                                break;
                        }
                        break;
                    }
                    if constexpr(Group == 2) {
                        competition_parent[j].winner =
                                cmp(competition[i].winner->value, competition[i + 1].winner->value) ?
                                competition[i].winner : competition[i + 1].winner;
                        competition[i].parent = competition[i + 1].parent = competition_parent + j;
                    }else if constexpr(Group == 3) {
                        if(cmp(competition[i].winner->value, competition[i + 1].winner->value)) {
                            if(cmp(competition[i].winner->value, competition[i + 2].winner->value)) {
                                competition_parent[j].winner = competition[i].winner;
                            }else {
                                competition_parent[j].winner = competition[i + 1].winner;
                            }
                        }else {
                            if(cmp(competition[i + 1].winner->value, competition[i + 2].winner->value)) {
                                competition_parent[j].winner = competition[i + 1].winner;
                            }else {
                                competition_parent[j].winner = competition[i + 2].winner;
                            }
                        }
                        competition[i].parent = competition[i + 1].parent = competition[i + 2].parent =
                                competition_parent + j;
                    }else {
                        const auto end {i + static_cast<difference_type>(Group)};
                        competition_parent[j].winner = competition[this->max(competition, i, end, cmp)].winner;
                        for(auto k {i}; k < end; ++k) {
                            competition[k].parent = competition_parent + j;
                        }
                    }
                }
                if(parent_size == 1) {
                    competition_parent->parent = nullptr;
                    break;
                }
                competition = competition_parent;
                size = parent_size;
                parent_size = this->parent_size(size);
                competition_parent = this->competition_allocate(parent_size);
            }
        }else {
            try {
                while(true) {
                    for(auto i {0}, j {0};; i += Group, static_cast<void>(++j)) {
                        if(j + 1 == parent_size) {
                            auto left {size - i};
                            switch(left) {
                                case 0:
                                    break;
                                case 1:
                                    competition[i].parent = competition_parent + j;
                                    competition_parent[j].winner = competition[i].winner;
                                    break;
                                case 2:
                                    competition[i].parent = competition[i + 1].parent = competition_parent + j;
                                    competition_parent[j].winner =
                                            cmp(competition[i].winner->value, competition[i + 1].winner->value) ?
                                                    competition[i].winner : competition[i + 1].winner;
                                    break;
                                default:
                                    for(auto k {i}; k < size; ++k) {
                                        competition[k].parent = competition_parent + j;
                                    }
                                    competition_parent[j].winner =
                                            competition[this->max(competition, i, size, cmp)].winner;
                                    break;
                            }
                            break;
                        }
                        if constexpr(Group == 2) {
                            competition[i].parent = competition[i + 1].parent = competition_parent + j;
                            competition_parent[j].winner =
                                    cmp(competition[i].winner->value, competition[i + 1].winner->value) ?
                                            competition[i].winner : competition[i + 1].winner;
                        }else if constexpr(Group == 3) {
                            competition[i].parent = competition[i + 1].parent = competition[i + 2].parent =
                                    competition_parent + j;
                            if(cmp(competition[i].winner->value, competition[i + 1].winner->value)) {
                                if(cmp(competition[i].winner->value, competition[i + 2].winner->value)) {
                                    competition_parent[j].winner = competition[i].winner;
                                }else {
                                    competition_parent[j].winner = competition[i + 1].winner;
                                }
                            }else {
                                if(cmp(competition[i + 1].winner->value, competition[i + 2].winner->value)) {
                                    competition_parent[j].winner = competition[i + 1].winner;
                                }else {
                                    competition_parent[j].winner = competition[i + 2].winner;
                                }
                            }
                        }else {
                            const auto end {i + static_cast<difference_type>(Group)};
                            for(auto k {i}; k < end; ++k) {
                                competition[k].parent = competition_parent + j;
                            }
                            competition_parent[j].winner = competition[this->max(competition, i, end, cmp)].winner;
                        }
                    }
                    if(parent_size == 1) {
                        competition_parent->parent = nullptr;
                        break;
                    }
                    competition = competition_parent;
                    size = parent_size;
                    parent_size = this->parent_size(size);
                    competition_parent = this->competition_allocate(parent_size);
                }
            }catch(...) {
                auto parent {contestant->parent};
                while(parent not_eq competition_parent) {
                    auto backup {parent};
                    parent = parent->parent;
                    alloc_traits::operator delete(backup);
                }
                alloc_traits::operator delete(competition_parent);
                if constexpr(not trivial_destruction) {
                    for(auto i {0}; i < size_backup; ++i) {
                        alloc_traits::destroy(ds::address_of(contestant[i].value));
                    }
                }
                alloc_traits::operator delete(contestant);
                throw;
            }
        }
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    void winner_tree<T, Compare, Group, Allocator>::deallocate() noexcept {
        if(this->contestant) {
            auto parent {this->contestant->parent};
            while(parent) {
                auto backup {parent};
                parent = parent->parent;
                alloc_traits::operator delete(backup);
            }
            if constexpr(not trivial_destruction) {
                for(auto i {0}; i < this->contestant_size.size; ++i) {
                    alloc_traits::destroy(ds::address_of(this->contestant[i].value));
                }
            }
            alloc_traits::operator delete(this->contestant);
        }
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    typename winner_tree<T, Compare, Group, Allocator>::competition_type
    winner_tree<T, Compare, Group, Allocator>::top_node() const noexcept {
        auto result {this->contestant->parent};
        while(result->parent) {
            result = result->parent;
        }
        return result;
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    template <typename ForwardIterator>
    void winner_tree<T, Compare, Group, Allocator>::insert_auxiliary(difference_type pos, ForwardIterator begin,
            ForwardIterator end) {
        const auto distance {ds::distance(begin, end)};
        const auto new_size {this->contestant_size.size + static_cast<size_type>(distance)};
        auto new_contestant {this->contestant_allocate(new_size)};
        this->fill(this->contestant, new_contestant, static_cast<size_type>(pos),
                this->contestant + pos, new_contestant + (pos + distance),
                this->contestant_size.size - static_cast<size_type>(pos));
        if constexpr(nothrow_copy_construction) {
            for(auto i {pos}; i < distance; ++i) {
                alloc_traits::construct(new_contestant + i, *begin++);
            }
        }else {
            auto i {pos};
            try {
                for(; i < distance; ++i) {
                    alloc_traits::construct(new_contestant + i, *begin++);
                }
            }catch(...) {
                if constexpr(not trivial_destruction) {
                    for(auto j {0}; j < i; ++j) {
                        alloc_traits::operator delete(new_contestant + j);
                    }
                    for(auto j {pos + distance}; j < new_size; ++j) {
                        alloc_traits::operator delete(new_contestant + j);
                    }
                }
                alloc_traits::operator delete(new_contestant);
                throw;
            }
        }
        this->tournament(new_contestant, new_size);
        this->deallocate();
        this->contestant = new_contestant;
        this->contestant_size.size = new_size;
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    void winner_tree<T, Compare, Group, Allocator>::rematch(competition_type head, difference_type pos, size_type size,
            value_compare &cmp) noexcept(has_nothrow_function_call_operator_v<value_compare, reference, reference>) {
        if constexpr(Group == 2) {
            if(pos + 1 not_eq size) {
                auto cmp_index {pos % Group == 0 ? pos + 1 : pos - 1};
                if(cmp(head[pos].winner->value, head[cmp_index].winner->value)) {
                    if(head[pos].parent->winner not_eq head[pos].winner) {
                        head[pos].parent->winner = head[pos].winner;
                    }
                    this->rematch(head->parent, head[pos].parent - head->parent, this->parent_size(size), cmp);
                }
            }
        }else if constexpr(Group == 3) {
            auto group {pos - pos % static_cast<difference_type>(Group)};
            const auto tail_size {size - group};
            switch(tail_size) {
                case 1:
                    break;
                case 2: {
                    auto cmp_index {group == pos ? group + 1 : group};
                    if(cmp(head[pos].winner->value, head[cmp_index].winner->value)) {
                        if(head[pos].parent->winner not_eq head[pos].winner) {
                            head[pos].parent->winner = head[pos].winner;
                        }
                        this->rematch(head->parent, head[pos].parent - head->parent, this->parent_size(size), cmp);
                    }
                }
                    break;
                default: {
                    auto [cmp_index1, cmp_index2] = [group, pos]() -> auto {
                        struct s {
                            difference_type x;
                            difference_type y;
                        };
                        if(group == pos) {
                            return s {group + 1, group + 2};
                        }
                        if(group + 1 == pos) {
                            return s {group, group + 2};
                        }
                        return s {group, group + 1};
                    }();
                    if(cmp(head[pos].winner->value, head[cmp_index1].winner->value)) {
                        if(cmp(head[pos].winner->value, head[cmp_index2].winner->value)) {
                            const auto index_pos {head[pos].winner};
                            if(head[pos].parent->winner not_eq index_pos) {
                                head[pos].parent->winner = index_pos;
                            }
                            this->rematch(head->parent, head[pos].parent - head->parent, this->parent_size(size), cmp);
                        }else {
                            const auto index_pos {head[cmp_index2].winner};
                            if(head[pos].parent->winner not_eq index_pos) {
                                this->contestant[pos].parent->winner = index_pos;
                            }

                        }
                    }else {
                        if(cmp(head[cmp_index1].winner->value, head[cmp_index2].winner->value)) {
                            const auto index_pos {head[cmp_index1].winner};
                            if(head[pos].parent->winner not_eq index_pos) {
                                head[pos].parent->winner = index_pos;
                            }
                            this->rematch(head->parent, head[pos].parent - head->parent, this->parent_size(size), cmp);
                        }else {
                            const auto index_pos {head[cmp_index2].winner};
                            if(head[pos].parent->winner not_eq index_pos) {
                                head[pos].parent->winner = index_pos;
                            }
                            this->rematch(head->parent, head[pos].parent - head->parent, this->parent_size(size), cmp);
                        }
                    }
                }
                    break;
            }
        }else {
            auto group {pos - pos % static_cast<difference_type>(Group)};
            const auto index_pos {head[this->max(head, group, size - group < Group ?
                    static_cast<difference_type>(size) : group + static_cast<difference_type>(Group), cmp)].winner};
            if(index_pos not_eq head[pos].parent->winner) {
                head[pos].parent->winner = index_pos;
            }
            if(head->parent->parent == nullptr) {
                return;
            }
            this->rematch(head->parent, head[pos].parent - head->parent, this->parent_size(size), cmp);
        }
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    template <typename InputIterator>
    winner_tree<T, Compare, Group, Allocator>::winner_tree(InputIterator begin, InputIterator end, false_type) :
            contestant_size {}, contestant {} {
        ds::buffer<value_type, allocator_type> buffer(begin, end);
        if constexpr(not trivial_copy_assignment and nothrow_move_construction) {
            winner_tree temp(buffer.mbegin(), buffer.mend());
            this->contestant_size = temp.contestant_size;
            this->contestant = temp.contestant;
            temp.contestant = nullptr;
        }else {
            winner_tree temp(buffer.begin(), buffer.end());
            this->contestant_size = temp.contestant_size;
            this->contestant = temp.contestant;
            temp.contestant = nullptr;
        }
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    template <typename ForwardIterator>
    winner_tree<T, Compare, Group, Allocator>::winner_tree(ForwardIterator begin, ForwardIterator end,
            true_type) : contestant_size {static_cast<size_type>(ds::distance(begin, end))},
            contestant {this->contestant_allocate(this->contestant_size.size)}{
        if constexpr(is_nothrow_constructible_v<value_type, iterator_traits_t(ForwardIterator, reference)>) {
            for(auto i {0}; begin not_eq end; ++i) {
                alloc_traits::construct(ds::address_of(this->contestant[i].value), *begin++);
            }
        }else {
            difference_type i {0};
            try {
                for(; begin not_eq end; ++i) {
                    alloc_traits::construct(ds::address_of(this->contestant[i].value), *begin++);
                }
            }catch(...) {
                if constexpr(not trivial_destruction) {
                    for(auto j {0}; j < i; ++j) {
                        alloc_traits::destroy(ds::address_of(this->contestant[j].value));
                    }
                }
                alloc_traits::operator delete(this->contestant);
                throw;
            }
        }
        this->tournament(this->contestant, this->contestant_size.size);
    }

    /* public functions */
    template <typename T, typename Compare, size_t Group, typename Allocator>
    constexpr winner_tree<T, Compare, Group, Allocator>::winner_tree(value_compare compare)
            noexcept(is_nothrow_copy_constructible_v<value_compare> or
                    is_nothrow_move_constructible_v<value_compare>) :
            contestant_size {0, ds::move(compare)}, contestant {nullptr} {}
    template <typename T, typename Compare, size_t Group, typename Allocator>
    template <typename InputIterator> requires is_input_iterator_v<InputIterator>
    winner_tree<T, Compare, Group, Allocator>::winner_tree(InputIterator begin, InputIterator end) :
            winner_tree(begin, end, is_forward_iterator<InputIterator> {}) {}
    template <typename T, typename Compare, size_t Group, typename Allocator>
    winner_tree<T, Compare, Group, Allocator>::winner_tree(initializer_list<value_type> init_list) :
            winner_tree(init_list.begin(), init_list.end()) {}
    template <typename T, typename Compare, size_t Group, typename Allocator>
    winner_tree<T, Compare, Group, Allocator>::winner_tree(const winner_tree &rhs) :
            winner_tree(rhs.cbegin(), rhs.cend()) {}
    template <typename T, typename Compare, size_t Group, typename Allocator>
    winner_tree<T, Compare, Group, Allocator>::winner_tree(winner_tree &&rhs) noexcept :
            contestant_size {rhs.contestant_size}, contestant {rhs.contestant} {
        rhs.contestant_size.size = 0;
        rhs.contestant = nullptr;
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    winner_tree<T, Compare, Group, Allocator>::~winner_tree() noexcept {
        this->deallocate();
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    winner_tree<T, Compare, Group, Allocator> &
    winner_tree<T, Compare, Group, Allocator>::operator=(const winner_tree &rhs) {
        if(&rhs not_eq this) {
            auto new_contestant {this->contestant_allocate(rhs.contestant_size.size)};
            if constexpr(trivial_copy_assignment) {
                ds::memory_copy(new_contestant, rhs.contestant,
                        rhs.contestant_size.size * sizeof(contestant_value_type));
            }else {
                if constexpr(nothrow_copy_construction) {
                    for(auto i {0}; i < rhs.contestant_size.size; ++i) {
                        alloc_traits::construct(ds::address_of(new_contestant[i].value), rhs.contestant[i].value);
                    }
                }else {
                    difference_type i {0};
                    try {
                        for(; i < rhs.contestant_size.size; ++i) {
                            alloc_traits::construct(ds::address_of(new_contestant[i].value), rhs.contestant[i].value);
                        }
                    }catch(...) {
                        if constexpr(not trivial_destruction) {
                            for(auto j {0}; j < i; ++j) {
                                alloc_traits::destroy(ds::address_of(new_contestant[j].value));
                            }
                        }
                        alloc_traits::operator delete(new_contestant);
                        throw;
                    }
                }
            }
            this->tournament(new_contestant, rhs.contestant_size.size);
            this->deallocate();
            this->contestant_size = rhs.contestant_size;
            this->contestant = new_contestant;
        }
        return *this;
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    winner_tree<T, Compare, Group, Allocator> &
    winner_tree<T, Compare, Group, Allocator>::operator=(winner_tree &&rhs) noexcept {
        if(&rhs not_eq this) {
            this->deallocate();
            this->contestant = rhs.contestant;
            this->contestant_size = rhs.contestant_size;
            rhs.contestant = nullptr;
            rhs.contestant_size.size = 0;
        }
        return *this;
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    winner_tree<T, Compare, Group, Allocator> &
    winner_tree<T, Compare, Group, Allocator>::operator=(initializer_list<value_type> init_list) {
        return this->operator=(winner_tree {init_list});
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    typename winner_tree<T, Compare, Group, Allocator>::const_reference
    winner_tree<T, Compare, Group, Allocator>::operator[](difference_type k) const {
        return this->at(k);
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    template <typename InputIterator> requires is_input_iterator_v<InputIterator>
    void winner_tree<T, Compare, Group, Allocator>::assign(InputIterator begin, InputIterator end) {
        *this = winner_tree(begin, end);
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    void winner_tree<T, Compare, Group, Allocator>::assign(initializer_list<value_type> init_list) {
        *this = winner_tree {init_list};
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    typename winner_tree<T, Compare, Group, Allocator>::const_iterator
    winner_tree<T, Compare, Group, Allocator>::begin() const noexcept {
        return const_iterator(this->contestant);
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    typename winner_tree<T, Compare, Group, Allocator>::const_iterator
    winner_tree<T, Compare, Group, Allocator>::end() const noexcept {
        return const_iterator(this->contestant + static_cast<difference_type>(this->contestant_size.size));
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    typename winner_tree<T, Compare, Group, Allocator>::const_iterator
    winner_tree<T, Compare, Group, Allocator>::cbegin() const noexcept {
        return const_iterator(this->contestant);
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    typename winner_tree<T, Compare, Group, Allocator>::const_iterator
    winner_tree<T, Compare, Group, Allocator>::cend() const noexcept {
        return const_iterator(this->contestant + static_cast<difference_type>(this->contestant_size.size));
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    typename winner_tree<T, Compare, Group, Allocator>::size_type
    winner_tree<T, Compare, Group, Allocator>::size() const noexcept {
        return this->contestant_size.size;
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    typename winner_tree<T, Compare, Group, Allocator>::size_type
    winner_tree<T, Compare, Group, Allocator>::round() const noexcept {
        return this->contestant_size.size % Group == 0 ?
                 this->contestant_size.size / Group : this->contestant_size / Group + 1;
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    bool winner_tree<T, Compare, Group, Allocator>::empty() const noexcept {
        return this->contestant == nullptr;
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    typename winner_tree<T, Compare, Group, Allocator>::const_reference
    winner_tree<T, Compare, Group, Allocator>::top() const noexcept {
        return this->top_node()->winner->value;
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    typename winner_tree<T, Compare, Group, Allocator>::value_type
    winner_tree<T, Compare, Group, Allocator>::winner(difference_type k) const {
        return this->at(k);
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    typename winner_tree<T, Compare, Group, Allocator>::value_type
    winner_tree<T, Compare, Group, Allocator>::winner(const_iterator pos) const {
        return this->winner(pos.contestant - this->contestant);
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    typename winner_tree<T, Compare, Group, Allocator>::value_type
    winner_tree<T, Compare, Group, Allocator>::champion() const noexcept {
        return this->top_node()->winner->value;
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    typename winner_tree<T, Compare, Group, Allocator>::const_reference
    winner_tree<T, Compare, Group, Allocator>::at(difference_type k) const {
        auto buffer {ds::buffer<contestant_type>(this->contestant_size.size, {})};
        auto begin {buffer.begin()};
        for(auto i {0}; i < this->contestant_size.size; ++i) {
            begin[i] = this->contestant + i;
        }
        return const_cast<winner_tree *>(this)->max_k(buffer.begin(), 0,
                static_cast<difference_type>(this->contestant_size.size - 1), k);
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    typename winner_tree<T, Compare, Group, Allocator>::const_reference
    winner_tree<T, Compare, Group, Allocator>::at(const_iterator pos) const {
        return this->at(pos.contestant - this->contestant);
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    void winner_tree<T, Compare, Group, Allocator>::swap(winner_tree &rhs) noexcept {
        ds::swap(this->contestant);
        ds::swap(this->contestant_size);
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    void winner_tree<T, Compare, Group, Allocator>::clear() noexcept {
        this->deallocate();
        this->contestant = nullptr;
        this->contestant_size.size = 0;
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    typename winner_tree<T, Compare, Group, Allocator>::const_reference
    winner_tree<T, Compare, Group, Allocator>::insert(difference_type pos, const_reference value) {
        return this->emplace(pos, value);
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    typename winner_tree<T, Compare, Group, Allocator>::const_reference
    winner_tree<T, Compare, Group, Allocator>::insert(const_iterator pos, const_reference value) {
        return this->emplace(pos.contestant - this->contestant, value);
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    typename winner_tree<T, Compare, Group, Allocator>::const_reference
    winner_tree<T, Compare, Group, Allocator>::insert(difference_type pos, rvalue_reference value) {
        return this->emplace(pos, ds::move(value));
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    typename winner_tree<T, Compare, Group, Allocator>::const_reference
    winner_tree<T, Compare, Group, Allocator>::insert(const_iterator pos, rvalue_reference value) {
        return this->emplace(pos.contestant - this->contestant, ds::move(value));
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    template <typename InputIterator> requires is_input_iterator_v<InputIterator>
    typename winner_tree<T, Compare, Group, Allocator>::const_reference
    winner_tree<T, Compare, Group, Allocator>::insert(difference_type pos, InputIterator begin, InputIterator end) {
        if(pos >= 0 and pos < this->contestant_size.size and begin not_eq end) {
            if constexpr(is_forward_iterator_v<InputIterator>) {
                this->insert_auxiliary(pos, begin, end);
            }else {
                auto buffer {ds::buffer<value_type, allocator_type>(begin, end)};
                const auto buffer_size {buffer.size()};
                if constexpr(not trivial_copy_assignment and nothrow_move_construction) {
                    this->insert_auxiliary(pos, buffer.mbegin(), buffer.mend());
                }else {
                    this->insert_auxiliary(pos, buffer, static_cast<difference_type>(buffer_size));
                }
                if constexpr(not trivial_destruction) {
                    for(auto i {0}; i < buffer_size; ++i) {
                        alloc_traits::destroy(ds::address_of(buffer[i].value));
                    }
                }
                alloc_traits::operator delete(buffer);
            }
        }
        return this->top_node()->winner->value;
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    template <typename InputIterator> requires is_input_iterator_v<InputIterator>
    typename winner_tree<T, Compare, Group, Allocator>::const_reference
    winner_tree<T, Compare, Group, Allocator>::insert(const_iterator pos, InputIterator begin, InputIterator end) {
        return this->insert(pos.contestant - this->contestant, begin, end);
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    typename winner_tree<T, Compare, Group, Allocator>::const_reference
    winner_tree<T, Compare, Group, Allocator>::insert(difference_type pos, initializer_list<value_type> init_list) {
        return this->insert(pos, init_list.begin(), init_list.end());
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    typename winner_tree<T, Compare, Group, Allocator>::const_reference
    winner_tree<T, Compare, Group, Allocator>::insert(const_iterator pos, initializer_list<value_type> init_list) {
        return this->insert(pos.contestant - this->contestant, init_list.begin(), init_list.end());
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    typename winner_tree<T, Compare, Group, Allocator>::const_reference
    winner_tree<T, Compare, Group, Allocator>::erase(difference_type pos, size_type size) {
        if(pos >= 0 and pos < this->contestant_size.size and size <= this->contestant_size.size) {
            const auto new_size {this->contestant_size.size - size};
            auto new_contestant {this->contestant_allocate(new_size)};
            this->fill(this->contestant, new_contestant, static_cast<size_type>(pos),
                    this->contestant + (pos + static_cast<difference_type>(size)), new_contestant + pos,
                    this->contestant_size.size - (static_cast<size_type>(pos) + size));
            this->tournament(new_contestant, new_size);
            this->deallocate();
            this->contestant_size.size = new_size;
            this->contestant = new_contestant;
        }
        return this->top_node()->winner->value;
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    typename winner_tree<T, Compare, Group, Allocator>::const_reference
    winner_tree<T, Compare, Group, Allocator>::erase(const_iterator pos) {
        return this->erase(pos.contestant - this->contestant);
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    typename winner_tree<T, Compare, Group, Allocator>::const_reference
    winner_tree<T, Compare, Group, Allocator>::erase(const_iterator begin, const_iterator end) {
        return this->erase(begin.contestant - this->contestant, end - begin);
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    template <typename ...Args>
    typename winner_tree<T, Compare, Group, Allocator>::const_reference
    winner_tree<T, Compare, Group, Allocator>::emplace(difference_type pos, Args &&...args) {
        if(pos >= 0 and pos <= this->contestant_size.size) {
            const auto new_size {this->contestant_size.size + 1};
            auto new_contestant {this->contestant_allocate(new_size)};
            this->fill(this->contestant, new_contestant, static_cast<size_type>(pos), this->contestant + pos,
                    new_contestant + (pos + 1), this->contestant_size.size - static_cast<difference_type>(pos));
            if constexpr(is_nothrow_constructible_v<value_type, Args...>) {
                alloc_traits::construct(ds::address_of(new_contestant[pos].value), ds::forward<Args>(args)...);
            }else {
                try {
                    alloc_traits::construct(ds::address_of(new_contestant[pos].value), ds::forward<Args>(args)...);
                }catch(...) {
                    if constexpr(not trivial_destruction) {
                        for(auto i {0}; i < pos; ++i) {
                            alloc_traits::destroy(ds::address_of(new_contestant[i].value));
                        }
                        for(auto i {pos + 1}; i < new_size; ++i) {
                            alloc_traits::destroy(ds::address_of(new_contestant[i].value));
                        }
                    }
                    alloc_traits::operator delete(new_contestant);
                }
            }
            this->tournament(new_contestant, new_size);
            this->deallocate();
            this->contestant = new_contestant;
            this->contestant_size.size = new_size;
        }
        return this->top_node()->winner->value;
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    template <typename ...Args>
    typename winner_tree<T, Compare, Group, Allocator>::const_reference
    winner_tree<T, Compare, Group, Allocator>::emplace(const_iterator pos, Args &&...args) {
        return this->emplace(pos.contestant - this->contestant, ds::forward<Args>(args)...);
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    template <typename ...Args>
    typename winner_tree<T, Compare, Group, Allocator>::const_reference
    winner_tree<T, Compare, Group, Allocator>::replace(difference_type pos, Args &&...args)
            noexcept(has_nothrow_function_call_operator_v<value_compare, reference, reference> and
                    is_nothrow_move_assignable_v<value_type>) {
        if(pos >= 0 and pos < this->contestant_size.size) {
            auto &cmp {this->contestant_size.compare()};
            this->contestant[pos].value = value_type(ds::forward<Args>(args)...);
            if constexpr(Group == 2) {
                if(pos + 1 not_eq this->contestant_size.size) {
                    auto cmp_index {pos % Group == 0 ? pos + 1 : pos - 1};
                    const auto index_pos {this->contestant + pos};
                    if(cmp(this->contestant[pos].value, this->contestant[cmp_index].value)) {
                        if(this->contestant[pos].parent->winner not_eq index_pos) {
                            this->contestant[pos].parent->winner = index_pos;
                        }
                        this->rematch(this->contestant->parent,
                                this->contestant[pos].parent - this->contestant->parent,
                                this->parent_size(this->contestant_size.size), cmp);
                    }
                }
            }else if constexpr(Group == 3) {
                auto group {pos - pos % static_cast<difference_type>(Group)};
                const auto tail_size {this->contestant_size.size - group};
                switch(tail_size) {
                    case 1:
                        break;
                    case 2: {
                        auto cmp_index {group == pos ? group + 1 : group};
                        const auto index_pos {this->contestant + pos};
                        if(cmp(this->contestant[pos].value, this->contestant[cmp_index].value)) {
                            if(this->contestant[pos].parent->winner not_eq index_pos) {
                                this->contestant[pos].parent->winner = index_pos;
                            }
                            this->rematch(this->contestant->parent,
                                    this->contestant[pos].parent - this->contestant->parent,
                                    this->parent_size(this->contestant_size.size), cmp);
                        }
                    }
                        break;
                    default: {
                        auto [cmp_index1, cmp_index2] = [group, pos]() -> auto {
                            struct s {
                                difference_type x;
                                difference_type y;
                            };
                            if(group == pos) {
                                return s {group + 1, group + 2};
                            }
                            if(group + 1 == pos) {
                                return s {group, group + 2};
                            }
                            return s {group, group + 1};
                        }();
                        if(cmp(this->contestant[pos].value, this->contestant[cmp_index1].value)) {
                            if(cmp(this->contestant[pos].value, this->contestant[cmp_index2].value)) {
                                const auto index_pos {this->contestant + pos};
                                if(this->contestant[pos].parent->winner not_eq index_pos) {
                                    this->contestant[pos].parent->winner = index_pos;
                                }
                                this->rematch(this->contestant->parent,
                                        this->contestant[pos].parent - this->contestant->parent,
                                        this->parent_size(this->contestant_size.size), cmp);
                            }else {
                                const auto index_pos {this->contestant + cmp_index2};
                                if(this->contestant[pos].parent->winner not_eq index_pos) {
                                    this->contestant[pos].parent->winner = index_pos;
                                }
                                this->rematch(this->contestant->parent,
                                        this->contestant[pos].parent - this->contestant->parent,
                                        this->parent_size(this->contestant_size.size), cmp);
                            }
                        }else {
                            if(cmp(this->contestant[cmp_index1].value, this->contestant[cmp_index2].value)) {
                                const auto index_pos {this->contestant + cmp_index1};
                                if(this->contestant[pos].parent->winner not_eq index_pos) {
                                    this->contestant[pos].parent->winner = index_pos;
                                }
                                this->rematch(this->contestant->parent,
                                        this->contestant[pos].parent - this->contestant->parent,
                                        this->parent_size(this->contestant_size.size), cmp);
                            }else {
                                const auto index_pos {this->contestant + cmp_index2};
                                if(this->contestant[pos].parent->winner not_eq index_pos) {
                                    this->contestant[pos].parent->winner = index_pos;
                                }
                                this->rematch(this->contestant->parent,
                                        this->contestant[pos].parent - this->contestant->parent,
                                        this->parent_size(this->contestant_size.size), cmp);
                            }
                        }
                    }
                        break;
                }
            }else {
                auto result {true};
                if(this->contestant[pos].parent->winner not_eq this->contestant + pos) {
                    result = cmp(this->contestant[pos].value, this->contestant[pos].parent->winner->value);
                }
                if(result) {
                    auto group {pos - pos % static_cast<difference_type>(Group)};
                    const auto index_pos {this->contestant + this->max(this->contestant, group,
                            this->contestant_size.size - group < Group ?
                                    static_cast<difference_type>(this->contestant_size.size) :
                                    group + static_cast<difference_type>(Group),
                            cmp)};
                    if(index_pos not_eq this->contestant[pos].parent->winner) {
                        this->contestant[pos].parent->winner = index_pos;
                    }
                    this->rematch(this->contestant->parent,
                            this->contestant[pos].parent - this->contestant->parent,
                            this->parent_size(this->contestant_size.size), cmp);
                }
            }
        }
        return this->top_node()->winner->value;
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    template <typename ...Args>
    typename winner_tree<T, Compare, Group, Allocator>::const_reference
    winner_tree<T, Compare, Group, Allocator>::replace(const_iterator pos, Args &&...args)
            noexcept(has_nothrow_function_call_operator_v<value_compare, reference, reference> and
                    is_nothrow_move_assignable_v<value_type>) {
        return this->replace(pos.contestant - this->contestant, ds::forward<Args>(args)...);
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    typename winner_tree<T, Compare, Group, Allocator>::const_reference
    winner_tree<T, Compare, Group, Allocator>::pop() {
        return this->erase(this->top_node()->winner - this->contestant);
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    typename winner_tree<T, Compare, Group, Allocator>::value_compare &
    winner_tree<T, Compare, Group, Allocator>::compare() noexcept {
        return this->contestant_size.compare();
    }
    template <typename T, typename Compare, size_t Group, typename Allocator>
    const typename winner_tree<T, Compare, Group, Allocator>::value_compare &
    winner_tree<T, Compare, Group, Allocator>::compare() const noexcept {
        return this->contestant_size.compare();
    }
}

namespace data_structure {
    template <typename T, typename Compare, size_t Group, typename Allocator>
    inline void swap(winner_tree<T, Compare, Group, Allocator> &lhs,
            winner_tree<T, Compare, Group, Allocator> &rhs) noexcept {
        lhs.swap(rhs);
    }
    template <typename T, typename CompareLHS, typename CompareRHS, size_t GroupLHS, size_t GroupRHS,
            typename AllocatorLHS, typename AllocatorRHS>
    inline bool operator==(const winner_tree<T, CompareLHS, GroupLHS, AllocatorLHS> &lhs,
            const winner_tree<T, CompareRHS, GroupRHS, AllocatorRHS> &rhs)
            noexcept(has_nothrow_equal_to_operator_v<T>) {
        return lhs.top() == rhs.top();
    }
    template <typename T, typename CompareLHS, typename CompareRHS, size_t GroupLHS, size_t GroupRHS,
            typename AllocatorLHS, typename AllocatorRHS>
    inline bool operator!=(const winner_tree<T, CompareLHS, GroupLHS, AllocatorLHS> &lhs,
            const winner_tree<T, CompareRHS, GroupRHS, AllocatorRHS> &rhs)
            noexcept(has_nothrow_equal_to_operator_v<T>) {
        return lhs.top() not_eq rhs.top();
    }
    template <typename T, typename CompareLHS, typename CompareRHS, size_t GroupLHS, size_t GroupRHS,
            typename AllocatorLHS, typename AllocatorRHS>
    inline bool operator<(const winner_tree<T, CompareLHS, GroupLHS, AllocatorLHS> &lhs,
            const winner_tree<T, CompareRHS, GroupRHS, AllocatorRHS> &rhs)
            noexcept(has_nothrow_less_operator_v<T>) {
        return lhs.top() < rhs.top();
    }
    template <typename T, typename CompareLHS, typename CompareRHS, size_t GroupLHS, size_t GroupRHS,
            typename AllocatorLHS, typename AllocatorRHS>
    inline bool operator<=(const winner_tree<T, CompareLHS, GroupLHS, AllocatorLHS> &lhs,
            const winner_tree<T, CompareRHS, GroupRHS, AllocatorRHS> &rhs)
            noexcept(has_nothrow_less_operator_v<T>) {
        return lhs.top() <= rhs.top();
    }
    template <typename T, typename CompareLHS, typename CompareRHS, size_t GroupLHS, size_t GroupRHS,
            typename AllocatorLHS, typename AllocatorRHS>
    inline bool operator>(const winner_tree<T, CompareLHS, GroupLHS, AllocatorLHS> &lhs,
            const winner_tree<T, CompareRHS, GroupRHS, AllocatorRHS> &rhs)
            noexcept(has_nothrow_less_operator_v<T>) {
        return lhs.top() > rhs.top();
    }
    template <typename T, typename CompareLHS, typename CompareRHS, size_t GroupLHS, size_t GroupRHS,
            typename AllocatorLHS, typename AllocatorRHS>
    inline bool operator>=(const winner_tree<T, CompareLHS, GroupLHS, AllocatorLHS> &lhs,
            const winner_tree<T, CompareRHS, GroupRHS, AllocatorRHS> &rhs)
            noexcept(has_nothrow_less_operator_v<T>) {
        return lhs.top() >= rhs.top();
    }
}

#endif //DATA_STRUCTURE_WINNER_TREE_HPP
