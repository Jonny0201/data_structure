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

#ifndef DATA_STRUCTURE_SKIP_LIST_HPP
#define DATA_STRUCTURE_SKIP_LIST_HPP

#include "allocator.hpp"
#include "iterator.hpp"

namespace data_structure::__data_structure_auxiliary {
    struct skip_list_probability_generator {
        consteval double operator()() const noexcept {
            return 0.5;
        }
    };
    struct skip_list_random_number_generator {
        double operator()() const noexcept {
            static std::random_device d {};
            static std::default_random_engine e(d());
            static std::uniform_real_distribution<double> u(0.0, 1.0);
            return u(e);
        }
    };
    template <typename Compare, typename Random, typename Probability, bool, bool, bool>
    struct skip_list_compress_auxiliary {
    public:
        Compare c;
        Random r;
        Probability p;
    public:
        constexpr skip_list_compress_auxiliary() = default;
        explicit skip_list_compress_auxiliary(Compare c) : c {ds::move(c)}, r {}, p {} {}
        explicit skip_list_compress_auxiliary(Random r) : c {}, r {ds::move(r)}, p {} {}
        explicit skip_list_compress_auxiliary(Probability p) : c {}, r {}, p {ds::move(p)} {}
        skip_list_compress_auxiliary(Compare c, Random r) : c {ds::move(c)}, r {ds::move(r)}, p {} {}
        skip_list_compress_auxiliary(Compare c, Probability p) : c {ds::move(c)}, r {}, p {ds::move(p)} {}
        skip_list_compress_auxiliary(Random r, Probability p) : c {}, r {ds::move(r)}, p {ds::move(p)} {}
        skip_list_compress_auxiliary(Compare c, Random r, Probability p) :
                c {ds::move(c)}, r {ds::move(r)}, p {ds::move(p)} {}
    public:
        Compare &compare() noexcept {
            return this->c;
        }
        const Compare &compare() const noexcept {
            return this->c;
        }
        Random &random() noexcept {
            return this->r;
        }
        const Random &random() const noexcept {
            return this->r;
        }
        Probability &probability() noexcept {
            return this->p;
        }
        const Probability &probability() const noexcept {
            return this->p;
        }
    };
    template <typename Compare, typename Random, typename Probability>
    struct skip_list_compress_auxiliary<Compare, Random, Probability, true, false, false> : public Compare {
    public:
        Random r;
        Probability p;
    public:
        constexpr skip_list_compress_auxiliary() = default;
        explicit skip_list_compress_auxiliary(Compare) : Compare(), r {}, p {} {}
        explicit skip_list_compress_auxiliary(Random r) : Compare(), r {ds::move(r)}, p {} {}
        explicit skip_list_compress_auxiliary(Probability p) : Compare(), r {}, p {ds::move(p)} {}
        skip_list_compress_auxiliary(Compare, Random r) : Compare(), r {ds::move(r)}, p {} {}
        skip_list_compress_auxiliary(Compare, Probability p) : Compare(), r {}, p {ds::move(p)} {}
        skip_list_compress_auxiliary(Random r, Probability p) : Compare(), r {ds::move(r)}, p {ds::move(p)} {}
        skip_list_compress_auxiliary(Compare, Random r, Probability p) :
                Compare(), r {ds::move(r)}, p {ds::move(p)} {}
    public:
        Compare &compare() noexcept {
            return static_cast<Compare &>(*this);
        }
        const Compare &compare() const noexcept {
            return static_cast<const Compare &>(*this);
        }
        Random &random() noexcept {
            return this->r;
        }
        const Random &random() const noexcept {
            return this->r;
        }
        Probability &probability() noexcept {
            return this->p;
        }
        const Probability &probability() const noexcept {
            return this->p;
        }
    };
    template <typename Compare, typename Random, typename Probability>
    struct skip_list_compress_auxiliary<Compare, Random, Probability, false, true, false> : public Random {
    public:
        Compare c;
        Probability p;
    public:
        constexpr skip_list_compress_auxiliary() = default;
        explicit skip_list_compress_auxiliary(Compare c) : Random(), c {ds::move(c)}, p {} {}
        explicit skip_list_compress_auxiliary(Random) : Random(), c {}, p {} {}
        explicit skip_list_compress_auxiliary(Probability p) : Random(), c {}, p {ds::move(p)} {}
        skip_list_compress_auxiliary(Compare c, Random) : Random(), c {ds::move(c)}, p {} {}
        skip_list_compress_auxiliary(Compare c, Probability p) : Random(), c {ds::move(c)}, p {ds::move(p)} {}
        skip_list_compress_auxiliary(Random, Probability p) : Random(), c {}, p {ds::move(p)} {}
        skip_list_compress_auxiliary(Compare c, Random, Probability p) :
                Random(), c {ds::move(c)}, p {ds::move(p)} {}
    public:
        Compare &compare() noexcept {
            return this->c;
        }
        const Compare &compare() const noexcept {
            return this->c;
        }
        Random &random() noexcept {
            return static_cast<Random &>(*this);
        }
        const Random &random() const noexcept {
            return static_cast<const Random &>(*this);
        }
        Probability &probability() noexcept {
            return this->p;
        }
        const Probability &probability() const noexcept {
            return this->p;
        }
    };
    template <typename Compare, typename Random, typename Probability>
    struct skip_list_compress_auxiliary<Compare, Random, Probability, false, false, true> :
            public Probability {
    public:
        Compare c;
        Random r;
    public:
        constexpr skip_list_compress_auxiliary() = default;
        explicit skip_list_compress_auxiliary(Compare c) : Probability(), c {ds::move(c)}, r {} {}
        explicit skip_list_compress_auxiliary(Random r) : Probability(), c {}, r {ds::move(r)} {}
        explicit skip_list_compress_auxiliary(Probability) : Probability(), c {}, r {} {}
        skip_list_compress_auxiliary(Compare c, Random r) : Probability(), c {ds::move(c)}, r {ds::move(r)} {}
        skip_list_compress_auxiliary(Compare c, Probability) : Probability(), c {ds::move(c)}, r {} {}
        skip_list_compress_auxiliary(Random r, Probability) : Probability(), c {}, r {ds::move(r)} {}
        skip_list_compress_auxiliary(Compare c, Random r, Probability) :
                Probability(), c {ds::move(c)}, r {ds::move(r)} {}
    public:
        Compare &compare() noexcept {
            return this->c;
        }
        const Compare &compare() const noexcept {
            return this->c;
        }
        Random &random() noexcept {
            return this->r;
        }
        const Random &random() const noexcept {
            return this->r;
        }
        Probability &probability() noexcept {
            return static_cast<Probability &>(*this);
        }
        const Probability &probability() const noexcept {
            return static_cast<const Probability &>(*this);
        }
    };
    template <typename Compare, typename Random, typename Probability>
    struct skip_list_compress_auxiliary<Compare, Random, Probability, true, true, false> :
            public Compare, public Random {
    public:
        Probability p;
    public:
        constexpr skip_list_compress_auxiliary() = default;
        explicit skip_list_compress_auxiliary(Compare) : Compare(), Random(), p {} {}
        explicit skip_list_compress_auxiliary(Random) : Compare(), Random(), p {} {}
        explicit skip_list_compress_auxiliary(Probability p) : Compare(), Random(), p {ds::move(p)} {}
        skip_list_compress_auxiliary(Compare, Random) : Compare(), Random(), p {} {}
        skip_list_compress_auxiliary(Compare, Probability p) : Compare(), Random(), p {ds::move(p)} {}
        skip_list_compress_auxiliary(Random, Probability p) : Compare(), Random(), p {ds::move(p)} {}
        skip_list_compress_auxiliary(Compare, Random, Probability p) : Compare(), Random(), p {ds::move(p)} {}
    public:
        Compare &compare() noexcept {
            return static_cast<Compare &>(*this);
        }
        const Compare &compare() const noexcept {
            return static_cast<const Compare &>(*this);
        }
        Random &random() noexcept {
            return static_cast<Random &>(*this);
        }
        const Random &random() const noexcept {
            return static_cast<const Random &>(*this);
        }
        Probability &probability() noexcept {
            return this->p;
        }
        const Probability &probability() const noexcept {
            return this->p;
        }
    };
    template <typename Compare, typename Random, typename Probability>
    struct skip_list_compress_auxiliary<Compare, Random, Probability, true, false, true> :
            public Compare, public Probability {
    public:
        Random r;
    public:
        constexpr skip_list_compress_auxiliary() = default;
        explicit skip_list_compress_auxiliary(Compare) : Compare(), Probability(), r {} {}
        explicit skip_list_compress_auxiliary(Random r) : Compare(), Probability(), r {ds::move(r)} {}
        explicit skip_list_compress_auxiliary(Probability) : Compare(), Probability(), r {} {}
        skip_list_compress_auxiliary(Compare, Random r) : Compare(), Probability(), r {ds::move(r)} {}
        skip_list_compress_auxiliary(Compare, Probability) : Compare(), Probability(), r {} {}
        skip_list_compress_auxiliary(Random r, Probability) : Compare(), Probability(), r {ds::move(r)} {}
        skip_list_compress_auxiliary(Compare, Random r, Probability) :
                Compare(), Probability(), r {ds::move(r)} {}
    public:
        Compare &compare() noexcept {
            return static_cast<Compare &>(*this);
        }
        const Compare &compare() const noexcept {
            return static_cast<const Compare &>(*this);
        }
        Random &random() noexcept {
            return this->r;
        }
        const Random &random() const noexcept {
            return this->r;
        }
        Probability &probability() noexcept {
            return static_cast<Probability &>(*this);
        }
        const Probability &probability() const noexcept {
            return static_cast<const Probability &>(*this);
        }
    };
    template <typename Compare, typename Random, typename Probability>
    struct skip_list_compress_auxiliary<Compare, Random, Probability, false, true, true> :
            public Random, public Probability {
    public:
        Compare c;
    public:
        constexpr skip_list_compress_auxiliary() = default;
        explicit skip_list_compress_auxiliary(Compare c) : Random(), Probability(), c {ds::move(c)} {}
        explicit skip_list_compress_auxiliary(Random) : Random(), Probability(), c {} {}
        explicit skip_list_compress_auxiliary(Probability) : Random(), Probability(), c {} {}
        skip_list_compress_auxiliary(Compare c, Random) : Random(), Probability(), c {ds::move(c)} {}
        skip_list_compress_auxiliary(Compare c, Probability) : Random(), Probability(), c {ds::move(c)} {}
        skip_list_compress_auxiliary(Random, Probability) : Random(), Probability(), c {} {}
        skip_list_compress_auxiliary(Compare c, Random, Probability) :
                Random(), Probability(), c {ds::move(c)} {}
    public:
        Compare &compare() noexcept {
            return this->c;
        }
        const Compare &compare() const noexcept {
            return this->c;
        }
        Random &random() noexcept {
            return static_cast<Random &>(*this);
        }
        const Random &random() const noexcept {
            return static_cast<const Random &>(*this);
        }
        Probability &probability() noexcept {
            return static_cast<Probability &>(*this);
        }
        const Probability &probability() const noexcept {
            return static_cast<const Probability &>(*this);
        }
    };
    template <typename Compare, typename Random, typename Probability>
    struct skip_list_compress_auxiliary<Compare, Random, Probability, true, true, true> :
            public Compare, public Random, public Probability {
    public:
        constexpr skip_list_compress_auxiliary() = default;
        explicit skip_list_compress_auxiliary(Compare) noexcept : Compare(), Random(), Probability() {}
        explicit skip_list_compress_auxiliary(Random) noexcept : Compare(), Random(), Probability() {}
        explicit skip_list_compress_auxiliary(Probability) noexcept : Compare(), Random(), Probability() {}
        skip_list_compress_auxiliary(Compare, Random) noexcept : Compare(), Random(), Probability() {}
        skip_list_compress_auxiliary(Compare, Probability) noexcept : Compare(), Random(), Probability() {}
        skip_list_compress_auxiliary(Random, Probability) noexcept : Compare(), Random(), Probability() {}
        skip_list_compress_auxiliary(Compare, Random, Probability) noexcept :
                Compare(), Random(), Probability() {}
    public:
        Compare &compare() noexcept {
            return static_cast<Compare &>(*this);
        }
        const Compare &compare() const noexcept {
            return static_cast<const Compare &>(*this);
        }
        Random &random() noexcept {
            return static_cast<Random &>(*this);
        }
        const Random &random() const noexcept {
            return static_cast<const Random &>(*this);
        }
        Probability &probability() noexcept {
            return static_cast<Probability &>(*this);
        }
        const Probability &probability() const noexcept {
            return static_cast<const Probability &>(*this);
        }
    };
    template <typename Compare, typename Random, typename Probability>
    using skip_list_compress = skip_list_compress_auxiliary<Compare, Random, Probability,
            is_empty_v<Compare> and not is_final_v<Compare>,
            is_empty_v<Random> and not is_final_v<Random>,
            is_empty_v<Probability> and not is_final_v<Probability>>;
    template <typename NodeType, typename Compare, typename Random, typename Probability>
    struct skip_list_compress_with_node_type : skip_list_compress<Compare, Random, Probability> {
    public:
        NodeType n;
    public:
        constexpr skip_list_compress_with_node_type() = default;
        skip_list_compress_with_node_type(NodeType n) : skip_list_compress<Compare, Random, Probability>(),
                n {n} {}
        skip_list_compress_with_node_type(NodeType n, Compare c) :
                skip_list_compress<Compare, Random, Probability>(ds::move(c)), n {ds::move(n)} {}
        skip_list_compress_with_node_type(NodeType n, Random r) :
                skip_list_compress<Compare, Random, Probability>(ds::move(r)), n {ds::move(n)} {}
        skip_list_compress_with_node_type(NodeType n, Probability p) :
                skip_list_compress<Compare, Random, Probability>(ds::move(p)), n {ds::move(n)} {}
        skip_list_compress_with_node_type(NodeType n, Compare c, Random r) :
                skip_list_compress<Compare, Random, Probability>(ds::move(c), ds::move(r)), n {ds::move(n)} {}
        skip_list_compress_with_node_type(NodeType n, Compare c, Probability p) :
                skip_list_compress<Compare, Random, Probability>(ds::move(c), ds::move(p)), n {ds::move(n)} {}
        skip_list_compress_with_node_type(NodeType n, Random r, Probability p) :
                skip_list_compress<Compare, Random, Probability>(ds::move(r), ds::move(p)), n {ds::move(n)} {}
        skip_list_compress_with_node_type(NodeType n, Compare c, Random r, Probability p) :
                skip_list_compress<Compare, Random, Probability>(ds::move(c), ds::move(r), ds::move(p)),
                n {ds::move(n)} {}
    public:
        NodeType &node() noexcept {
            return this->n;
        }
        const NodeType &node() const noexcept {
            return this->n;
        }
    };
}

namespace data_structure {
    template <typename T, typename Allocator = allocator<type_holder<T>>,
            typename Compare = less<>, typename Random = __dsa::skip_list_random_number_generator,
            typename Probability = __dsa::skip_list_probability_generator>
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
    private:
        __dsa::skip_list_compress_with_node_type<node_type, value_compare,
                random_number_generator , probability_generator> head;
    private:
        [[nodiscard]]
        static node_type allocate();
        static void next_allocate(node_type, size_type);
        [[nodiscard]]
        static node_type default_construct();
        [[nodiscard]]
        static constexpr size_t suitable_max_level(size_type) noexcept;
        static void free_node(node_type) noexcept;
    private:
        [[nodiscard]]
        size_t generate_level(size_type) const noexcept;
        void connect(node_type) noexcept;
        [[nodiscard]]
        node_type allocate_n(size_type);
        [[nodiscard]]
        node_type allocate_n(size_type, const_reference);
        void free_from(node_type) noexcept;
        void copy_from_rhs(node_type);
        void erase_one_node(node_type) noexcept;
        void try_increment_max_level();
        [[nodiscard]]
        iterator hint(const_reference, size_t)
                noexcept(has_nothrow_function_call_operator_v<value_compare, value_type, value_type>);
    public:
        skip_list();
        explicit skip_list(size_type);
        skip_list(size_type, const_reference);
        explicit skip_list(value_compare);
        explicit skip_list(random_number_generator);
        explicit skip_list(probability_generator);
        skip_list(value_compare, random_number_generator);
        skip_list(value_compare, probability_generator);
        skip_list(random_number_generator, probability_generator);
        skip_list(value_compare, random_number_generator, probability_generator);
        template <typename Iterator>
        skip_list(enable_if_t<is_input_iterator_v<Iterator>, Iterator>, Iterator);
        skip_list(initializer_list<value_type>);
        skip_list(const skip_list &);
        skip_list(skip_list &&) noexcept;
        template <typename AllocatorRHS>
        explicit skip_list(const skip_list<value_type, AllocatorRHS, value_compare,
                random_number_generator, probability_generator> &);
        template <typename AllocatorRHS>
        explicit skip_list(skip_list<value_type, AllocatorRHS, value_compare,
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
                random_number_generator, probability_generator> &&) noexcept;
        skip_list &operator=(initializer_list<value_type>);
        skip_list &operator=(random_number_generator)
                noexcept(is_nothrow_move_assignable_v<random_number_generator> and
                        is_nothrow_copy_assignable_v<random_number_generator>);
        skip_list &operator=(probability_generator)
                noexcept(is_nothrow_move_assignable_v<probability_generator> and
                         is_nothrow_copy_assignable_v<probability_generator>);
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
        iterator lbefore_begin() noexcept;
        [[nodiscard]]
        const_iterator lbefore_begin() const noexcept;
        [[nodiscard]]
        const_iterator clbefore_begin() const noexcept;
        [[nodiscard]]
        iterator lbegin() noexcept;
        [[nodiscard]]
        const_iterator lbegin() const noexcept;
        [[nodiscard]]
        const_iterator clbegin() const noexcept;
        [[nodiscard]]
        bool empty() const noexcept;
        [[nodiscard]]
        size_type size() const noexcept;
        [[nodiscard]]
        static consteval size_type max_size() noexcept;
        void clear() noexcept;
        void swap(skip_list &) noexcept;
        template <typename AllocatorRHS>
        void swap(skip_list<value_type, AllocatorRHS, value_compare,
                random_number_generator, probability_generator> &) noexcept;
        iterator insert(const_reference, size_type = 1);
        iterator insert(rvalue_reference);
        template <typename Iterator>
        iterator insert(enable_if_t<is_input_iterator_v<Iterator>, Iterator>, Iterator);
        iterator insert(initializer_list<value_type>);
        iterator erase(difference_type, size_type = 1) noexcept;
        iterator erase_after(const_iterator, size_type) noexcept;
        iterator erase_after(const_iterator, const_iterator) noexcept;
        iterator erase_after(const_iterator) noexcept;
        template <typename ...Args>
        iterator emplace(Args &&...);
        void pop_front() noexcept;
    public:
        random_number_generator &get_random_number_generator() noexcept;
        const random_number_generator &get_random_number_generator() const noexcept;
        probability_generator &get_probability_generator() noexcept;
        const probability_generator &get_probability_generator() const noexcept;
        template <typename ...Args>
        void reset_random_number_generator(Args &&...)
                noexcept(is_nothrow_move_assignable_v<random_number_generator> or
                        (not is_move_assignable_v<random_number_generator> and
                        is_nothrow_copy_assignable_v<random_number_generator>));
        template <typename ...Args>
        void reset_probability_generator(Args &&...)
                noexcept(is_nothrow_move_assignable_v<probability_generator> or
                         (not is_move_assignable_v<probability_generator> and
                          is_nothrow_copy_assignable_v<probability_generator>));
    public:
        template <typename ValueType>
        size_type remove(const ValueType &) noexcept(has_nothrow_equal_to_operator_v<value_type, ValueType>);
        template <typename UnaryPredicate>
        size_type remove_if(UnaryPredicate)
                noexcept(has_nothrow_function_call_operator_v<UnaryPredicate, value_type>);
        void unique() noexcept(has_nothrow_equal_to_operator_v<value_type>);
        template <typename BinaryPredicate>
        void unique(BinaryPredicate)
                noexcept(has_nothrow_function_call_operator_v<BinaryPredicate, value_type, value_type>);
        template <typename ValueType>
        iterator find(const ValueType &) noexcept(has_nothrow_equal_to_operator_v<value_type, ValueType> and
                has_nothrow_function_call_operator_v<value_compare, value_type, ValueType>);
        template <typename ValueType>
        const_iterator find(const ValueType &) const
                noexcept(has_nothrow_equal_to_operator_v<value_type, ValueType> and
                        has_nothrow_function_call_operator_v<value_compare, value_type, ValueType>);
        template <typename UnaryPredicate>
        iterator find_if(UnaryPredicate)
                noexcept(has_nothrow_function_call_operator_v<UnaryPredicate, value_type>);
        template <typename UnaryPredicate>
        const_iterator find_if(UnaryPredicate) const
                noexcept(has_nothrow_function_call_operator_v<UnaryPredicate, value_type>);
        template <typename ValueType>
        bool contains(const ValueType &) const
                noexcept(has_nothrow_equal_to_operator_v<value_type, ValueType> and
                        has_nothrow_function_call_operator_v<value_compare, value_type, ValueType>);
        template <typename UnaryPredicate>
        bool contains_if(UnaryPredicate) const
                noexcept(has_nothrow_function_call_operator_v<UnaryPredicate, value_type>);
        template <typename ValueType>
        size_type count(const ValueType &) const
                noexcept(has_nothrow_equal_to_operator_v<value_type, ValueType> and
                        has_nothrow_function_call_operator_v<value_compare, value_type, ValueType>);
        template <typename UnaryPredicate>
        size_type count_if(UnaryPredicate) const
                noexcept(has_nothrow_function_call_operator_v<UnaryPredicate, value_type>);
    };
}

namespace data_structure {
    /* private functions */
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline typename skip_list<T, Allocator, Compare, Random, Probability>::node_type
    skip_list<T, Allocator, Compare, Random, Probability>::allocate() {
        return reinterpret_cast<node_type>(alloc_traits::operator new(sizeof(node_value_type)));
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline void skip_list<T, Allocator, Compare, Random, Probability>::next_allocate(
            node_type node, size_type size) {
        node->next = reinterpret_cast<node_type *>(alloc_traits::operator new(++size * sizeof(node_type)));
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline typename skip_list<T, Allocator, Compare, Random, Probability>::node_type
    skip_list<T, Allocator, Compare, Random, Probability>::default_construct() {
        auto first {skip_list::allocate()};
        first->max_level = 0;
        try {
            skip_list::next_allocate(first, 0);
        }catch(...) {
            alloc_traits::operator delete(first);
            throw;
        }
        first->next[0] = nullptr;
        return first;
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline constexpr size_t skip_list<T, Allocator, Compare, Random, Probability>::suitable_max_level(
            size_type size) noexcept {
        return size * 3 / 4;
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline void skip_list<T, Allocator, Compare, Random, Probability>::free_node(node_type begin) noexcept {
        for(auto cursor {begin->next[0]}; cursor;) {
            auto next {cursor->next[0]};
            alloc_traits::destroy(ds::address_of(cursor->value));
            alloc_traits::operator delete(cursor->next);
            alloc_traits::operator delete(cursor);
            cursor = next;
        }
        alloc_traits::operator delete(begin->next);
        alloc_traits::operator delete(begin);
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    void skip_list<T, Allocator, Compare, Random, Probability>::connect(node_type begin) noexcept {
        for(auto i {1}; i <= begin->max_level; ++i) {
            auto stop {begin};
            for(auto next {stop->next[0]}; next; next = next->next[0]) {
                if(next->max_level >= i) {
                    stop->next[i] = next;
                    stop = next;
                }
            }
            stop->next[i] = nullptr;
        }
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline size_t skip_list<T, Allocator, Compare, Random, Probability>::generate_level(
            size_type max_level) const noexcept {
        size_t level {};
        while(level < max_level) {
            if(this->head.random()() < this->head.probability()()) {
                ++level;
            }else {
                break;
            }
        }
        return level;
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    typename skip_list<T, Allocator, Compare, Random, Probability>::node_type
    skip_list<T, Allocator, Compare, Random, Probability>::allocate_n(size_type size) {
        auto first {skip_list::allocate()};
        first->max_level = this->suitable_max_level(size);
        try {
            this->next_allocate(first, first->max_level);
        }catch(...) {
            alloc_traits::operator delete(first);
            throw;
        }
        auto cursor {first};
        while(size-- > 0) {
            try {
                cursor->next[0] = skip_list::allocate();
            }catch(...) {
                cursor->next[0] = nullptr;
                this->free_node(first);
                throw;
            }
            try {
                this->next_allocate(cursor->next[0],
                        cursor->next[0]->max_level = this->generate_level(first->max_level));
            }catch(...) {
                alloc_traits::operator delete(cursor->next[0]);
                cursor->next[0] = nullptr;
                this->free_node(first);
                throw;
            }
            if constexpr(is_nothrow_constructible_v<value_type>) {
                alloc_traits::construct(ds::address_of(cursor->next[0]->value));
            }else {
                try {
                    alloc_traits::construct(ds::address_of(cursor->next[0]->value));
                }catch(...) {
                    alloc_traits::operator delete(cursor->next[0]->next);
                    alloc_traits::operator delete(cursor->next[0]);
                    cursor->next[0] = nullptr;
                    this->free_node(first);
                    throw;
                }
            }
            cursor = cursor->next[0];
        }
        cursor->next[0] = nullptr;
        this->connect(first);
        return first;
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    typename skip_list<T, Allocator, Compare, Random, Probability>::node_type
    skip_list<T, Allocator, Compare, Random, Probability>::allocate_n(size_type size, const_reference value) {
        auto first {skip_list::allocate()};
        first->max_level = this->suitable_max_level(size);
        try {
            this->next_allocate(first, first->max_level);
        }catch(...) {
            alloc_traits::operator delete(first);
            throw;
        }
        auto cursor {first};
        while(size-- > 0) {
            try {
                cursor->next[0] = skip_list::allocate();
            }catch(...) {
                cursor->next[0] = nullptr;
                this->free_node(first);
                throw;
            }
            try {
                this->next_allocate(cursor->next[0],
                        cursor->next[0]->max_level = this->generate_level(first->max_level));
            }catch(...) {
                alloc_traits::operator delete(cursor->next[0]);
                cursor->next[0] = nullptr;
                this->free_node(first);
                throw;
            }
            if constexpr(is_nothrow_constructible_v<value_type>) {
                alloc_traits::construct(ds::address_of(cursor->next[0]->value), value);
            }else {
                try {
                    alloc_traits::construct(ds::address_of(cursor->next[0]->value), value);
                }catch(...) {
                    alloc_traits::operator delete(cursor->next[0]->next);
                    alloc_traits::operator delete(cursor->next[0]);
                    cursor->next[0] = nullptr;
                    this->free_node(first);
                    throw;
                }
            }
            cursor = cursor->next[0];
        }
        cursor->next[0] = nullptr;
        this->connect(first);
        return first;
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline void skip_list<T, Allocator, Compare, Random, Probability>::free_from(node_type begin) noexcept {
        while(begin) {
            auto next {begin->next[0]};
            alloc_traits::destroy(ds::address_of(begin->value));
            alloc_traits::operator delete(begin->next);
            alloc_traits::operator delete(begin);
            begin = next;
        }
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    void skip_list<T, Allocator, Compare, Random, Probability>::copy_from_rhs(node_type begin) {
        alloc_traits::operator delete(this->head.node()->next);
        this->next_allocate(this->head.node(), this->head.node()->max_level = begin->max_level);
        auto cursor {this->head.node()};
        begin = begin->next[0];
        while(begin) {
            cursor->next[0] = allocate();
            try {
                this->next_allocate(cursor->next[0], cursor->next[0]->max_level = begin->max_level);
            }catch(...) {
                alloc_traits::operator delete(cursor->next[0]);
                cursor->next[0] = nullptr;
                throw;
            }
            alloc_traits::construct(ds::address_of(cursor->next[0]->value), begin->value);
            cursor = cursor->next[0];
            begin = begin->next[0];
        }
        cursor->next[0] = nullptr;
        this->connect(this->head.node());
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline void skip_list<T, Allocator, Compare, Random, Probability>::erase_one_node(node_type node) noexcept {
        auto erase_node {node->next[0]};
        for(auto i {erase_node->max_level}; i > 0; --i) {
            for(auto cursor {this->head.node()};; cursor = cursor->next[i]) {
                if(cursor->next[i] == erase_node) {
                    cursor->next[i] = erase_node->next[i];
                    break;
                }
            }
        }
        node->next[0] = erase_node->next[0];
        alloc_traits::destroy(ds::address_of(erase_node->value));
        alloc_traits::operator delete(erase_node->next);
        alloc_traits::operator delete(erase_node);
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    void skip_list<T, Allocator, Compare, Random, Probability>::try_increment_max_level() {
        auto &max_level {this->head.node()->max_level};
        if(this->head.node()->next[max_level] and this->head.random()() < this->head.probability()()) {
            auto new_max_level {max_level + 1};
            auto new_next {reinterpret_cast<node_type *>(alloc_traits::operator new(
                    (new_max_level + 1) * sizeof(node_type)))};
            for(auto i {0}; i < new_max_level; ++i) {
                new_next[i] = this->head.node()->next[i];
            }
            new_next[new_max_level] = nullptr;
            alloc_traits::operator delete(this->head.node()->next);
            this->head.node()->next = new_next;
            max_level = new_max_level;
        }
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    typename skip_list<T, Allocator, Compare, Random, Probability>::iterator
    skip_list<T, Allocator, Compare, Random, Probability>::hint(const_reference value, size_t min_level)
            noexcept(has_nothrow_function_call_operator_v<value_compare, value_type, value_type>) {
        auto result {this->before_begin()};
        while(true) {
            auto next {result};
            ++next;
            if(next) {
                if(this->head.compare()(value, *next)) {
                    if(result.level == min_level) {
                        break;
                    }
                    -result;
                }else {
                    ++result;
                }
            }else {
                if(result.level == min_level) {
                    break;
                }
                -result;
            }
        }
        return result;
    }

    /* public functions */
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline skip_list<T, Allocator, Compare, Random, Probability>::skip_list() :
            head(this->default_construct()) {}
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline skip_list<T, Allocator, Compare, Random, Probability>::skip_list(size_type size) :
            head(size not_eq 0 ? this->allocate_n(size) : this->default_construct()) {}
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline skip_list<T, Allocator, Compare, Random, Probability>::skip_list(
            size_type size, const_reference value) :
            head(size not_eq 0 ? this->allocate_n(size, value) : this->default_construct()) {}
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline skip_list<T, Allocator, Compare, Random, Probability>::skip_list(value_compare c) :
            head(this->default_construct(), ds::move(c)) {}
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline skip_list<T, Allocator, Compare, Random, Probability>::skip_list(random_number_generator r) :
            head(this->default_construct(), ds::move(r)) {}
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline skip_list<T, Allocator, Compare, Random, Probability>::skip_list(probability_generator p) :
            head(this->default_construct(), ds::move(p)) {}
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline skip_list<T, Allocator, Compare, Random, Probability>::skip_list(
            value_compare c, random_number_generator r) :
            head(this->default_construct(), ds::move(c), ds::move(r)) {}
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline skip_list<T, Allocator, Compare, Random, Probability>::skip_list(
            value_compare c, probability_generator r) :
            head(this->default_construct(), ds::move(c), ds::move(r)) {}
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline skip_list<T, Allocator, Compare, Random, Probability>::skip_list(
            random_number_generator r, probability_generator p) :
            head(this->default_construct(), ds::move(r), ds::move(p)) {}
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline skip_list<T, Allocator, Compare, Random, Probability>::skip_list(
            value_compare c, random_number_generator r, probability_generator p) :
            head(this->default_construct(), ds::move(c), ds::move(r), ds::move(p)) {}
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    template <typename Iterator>
    inline skip_list<T, Allocator, Compare, Random, Probability>::skip_list(
            enable_if_t<is_input_iterator_v<Iterator>, Iterator> begin, Iterator end) : skip_list() {
        this->assign(begin, end);
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline skip_list<T, Allocator, Compare, Random, Probability>::skip_list(
            initializer_list<value_type> init_list) : skip_list(init_list.begin(), init_list.end()) {}
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline skip_list<T, Allocator, Compare, Random, Probability>::skip_list(const skip_list &rhs) :
            skip_list() {
        this->copy_from_rhs(rhs.head.node());
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline skip_list<T, Allocator, Compare, Random, Probability>::skip_list(skip_list &&rhs) noexcept :
            head(rhs.head.node()) {
        rhs.head.node() = nullptr;
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    template <typename AllocatorRHS>
    inline skip_list<T, Allocator, Compare, Random, Probability>::skip_list(const skip_list<value_type,
            AllocatorRHS, value_compare, random_number_generator, probability_generator> &rhs) :
            skip_list() {
        this->copy_from_rhs(rhs.head.node());
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    template <typename AllocatorRHS>
    inline skip_list<T, Allocator, Compare, Random, Probability>::skip_list(
            skip_list<value_type, AllocatorRHS, value_compare,
            random_number_generator, probability_generator> &&rhs) : head(rhs.head.node()) {
        rhs.head.node() = nullptr;
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline skip_list<T, Allocator, Compare, Random, Probability>::~skip_list() noexcept {
        if(this->head.node()) {
            this->free_node(this->head.node());
        }
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline skip_list<T, Allocator, Compare, Random, Probability> &
    skip_list<T, Allocator, Compare, Random, Probability>::operator=(const skip_list &rhs) {
        if(&rhs == this) {
            return *this;
        }
        this->clear();
        this->copy_from_rhs(rhs.head.node());
        return *this;
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline skip_list<T, Allocator, Compare, Random, Probability> &
    skip_list<T, Allocator, Compare, Random, Probability>::operator=(skip_list &&rhs) noexcept {
        if(&rhs == this) {
            return *this;
        }
        this->~skip_list();
        this->head.node() = rhs.head.node();
        rhs.head.node = nullptr;
        return *this;
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    template <typename AllocatorRHS>
    inline skip_list<T, Allocator, Compare, Random, Probability> &
    skip_list<T, Allocator, Compare, Random, Probability>::operator=(const skip_list<
            value_type, AllocatorRHS, value_compare, random_number_generator, probability_generator> &rhs) {
        this->clear();
        this->copy_from_rhs(rhs.head.node());
        return *this;
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    template <typename AllocatorRHS>
    inline skip_list<T, Allocator, Compare, Random, Probability> &
    skip_list<T, Allocator, Compare, Random, Probability>::operator=(skip_list<value_type, AllocatorRHS,
            value_compare, random_number_generator, probability_generator> &&rhs) noexcept {
        this->~skip_list();
        this->head.node() = rhs.head.node();
        rhs.head.node = nullptr;
        return *this;
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline skip_list<T, Allocator, Compare, Random, Probability> &
    skip_list<T, Allocator, Compare, Random, Probability>::operator=(initializer_list<value_type> init_list) {
        this->assign(init_list.begin(), init_list.end());
        return *this;
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline skip_list<T, Allocator, Compare, Random, Probability> &
    skip_list<T, Allocator, Compare, Random, Probability>::operator=(random_number_generator r)
            noexcept(is_nothrow_move_assignable_v<random_number_generator> and
                    is_nothrow_copy_assignable_v<random_number_generator>) {
        if constexpr(not is_stateless_v<random_number_generator>) {
            this->head.random() = ds::move(r);
        }
        return *this;
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline skip_list<T, Allocator, Compare, Random, Probability> &
    skip_list<T, Allocator, Compare, Random, Probability>::operator=(probability_generator p)
            noexcept(is_nothrow_move_assignable_v<probability_generator> and
                         is_nothrow_copy_assignable_v<probability_generator>) {
        if constexpr(not is_stateless_v<probability_generator>) {
            this->head.probability() = ds::move(p);
        }
        return *this;
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    void skip_list<T, Allocator, Compare, Random, Probability>::assign(size_type size, const_reference value) {
        if(size == 0) {
            return;
        }
        constexpr const auto end {this->cend()};
        auto cursor {this->cbegin()};
        auto before_cursor {this->cbefore_begin()};
        while(cursor not_eq end and size > 0) {
            *cursor++ = value;
            --size, static_cast<void>(++before_cursor);
        }
        if(size) {
            this->insert(value, size);
            return;
        }
        if(cursor not_eq end) {
            this->free_from(cursor);
        }
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    template <typename Iterator>
    void skip_list<T, Allocator, Compare, Random, Probability>::assign(
            enable_if_t<is_input_iterator_v<Iterator>, Iterator> begin, Iterator end) {
        if(begin == end) {
            return;
        }
        auto cursor {this->head.node()};
        if(cursor->next[0]) {
            cursor = cursor->next[0];
            if constexpr(is_forward_iterator_v<Iterator>) {
                cursor->value = *begin++;
            }else {
                cursor->value = ds::move(*begin++);
            }
            while(cursor->next[0] and begin not_eq end) {
                if constexpr(is_forward_iterator_v<Iterator>) {
                    if(this->head.compare()(cursor->value, *begin)) {
                        cursor->next[0]->value = *begin++;
                    }else {
                        break;
                    }
                }else {
                    auto value {ds::move(*begin++)};
                    if(this->head.compare()(cursor->value, value)) {
                        cursor->next[0]->value = ds::move(value);
                    }else {
                        break;
                    }
                }
            }
        }
        if(cursor not_eq this->head.node()) {
            this->free_from(cursor);
        }
        if(begin not_eq end) {
            this->insert(begin, end);
        }
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline void skip_list<T, Allocator, Compare, Random, Probability>::assign(
            initializer_list<value_type> init_list) {
        this->assign(init_list.begin(), init_list.end());
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline typename skip_list<T, Allocator, Compare, Random, Probability>::reference
    skip_list<T, Allocator, Compare, Random, Probability>::front() noexcept {
        return this->head.node()->next[0]->value;
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline typename skip_list<T, Allocator, Compare, Random, Probability>::const_reference
    skip_list<T, Allocator, Compare, Random, Probability>::front() const noexcept {
        return this->head.node()->next[0]->value;
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline typename skip_list<T, Allocator, Compare, Random, Probability>::iterator
    skip_list<T, Allocator, Compare, Random, Probability>::before_begin() noexcept {
        return iterator(this->head.node(), this->head.node()->max_level);
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline typename skip_list<T, Allocator, Compare, Random, Probability>::const_iterator
    skip_list<T, Allocator, Compare, Random, Probability>::before_begin() const noexcept {
        return const_iterator(this->head.node(), this->head.node()->max_level);
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline typename skip_list<T, Allocator, Compare, Random, Probability>::iterator
    skip_list<T, Allocator, Compare, Random, Probability>::begin() noexcept {
        return iterator(this->head.node()->next[0], this->head.node()->next[0]->max_level);
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline typename skip_list<T, Allocator, Compare, Random, Probability>::const_iterator
    skip_list<T, Allocator, Compare, Random, Probability>::begin() const noexcept {
        return const_iterator(this->head.node()->next[0], this->head.node()->next[0]->max_level);
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline constexpr typename skip_list<T, Allocator, Compare, Random, Probability>::iterator
    skip_list<T, Allocator, Compare, Random, Probability>::end() noexcept {
        return {};
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline constexpr typename skip_list<T, Allocator, Compare, Random, Probability>::const_iterator
    skip_list<T, Allocator, Compare, Random, Probability>::end() const noexcept {
        return {};
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline typename skip_list<T, Allocator, Compare, Random, Probability>::const_iterator
    skip_list<T, Allocator, Compare, Random, Probability>::cbefore_begin() const noexcept {
        return const_iterator(this->head.node(), this->head.node()->max_level);
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline typename skip_list<T, Allocator, Compare, Random, Probability>::const_iterator
    skip_list<T, Allocator, Compare, Random, Probability>::cbegin() const noexcept {
        return const_iterator(this->head.node()->next[0], this->head.node()->next[0]->max_level);
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline constexpr typename skip_list<T, Allocator, Compare, Random, Probability>::const_iterator
    skip_list<T, Allocator, Compare, Random, Probability>::cend() const noexcept {
        return {};
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline typename skip_list<T, Allocator, Compare, Random, Probability>::iterator
    skip_list<T, Allocator, Compare, Random, Probability>::lbefore_begin() noexcept {
        return iterator(this->head.node(), 0);
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline typename skip_list<T, Allocator, Compare, Random, Probability>::const_iterator
    skip_list<T, Allocator, Compare, Random, Probability>::lbefore_begin() const noexcept {
        return const_iterator(this->head.node(), 0);
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline typename skip_list<T, Allocator, Compare, Random, Probability>::const_iterator
    skip_list<T, Allocator, Compare, Random, Probability>::clbefore_begin() const noexcept {
        return const_iterator(this->head.node(), 0);
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline typename skip_list<T, Allocator, Compare, Random, Probability>::iterator
    skip_list<T, Allocator, Compare, Random, Probability>::lbegin() noexcept {
        return iterator(this->head.node()->next[0], 0);
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline typename skip_list<T, Allocator, Compare, Random, Probability>::const_iterator
    skip_list<T, Allocator, Compare, Random, Probability>::lbegin() const noexcept {
        return const_iterator(this->head.node()->next[0], 0);
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline typename skip_list<T, Allocator, Compare, Random, Probability>::const_iterator
    skip_list<T, Allocator, Compare, Random, Probability>::clbegin() const noexcept {
        return const_iterator(this->head.node()->next[0], 0);
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline bool skip_list<T, Allocator, Compare, Random, Probability>::empty() const noexcept {
        return this->head.node()->next[0];
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline typename skip_list<T, Allocator, Compare, Random, Probability>::size_type
    skip_list<T, Allocator, Compare, Random, Probability>::size() const noexcept {
        size_type size {0};
        for(auto cursor {this->head.node()}; cursor->next[0];
                cursor = cursor->next[0], static_cast<void>(++size));
        return size;
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline consteval typename skip_list<T, Allocator, Compare, Random, Probability>::size_type
    skip_list<T, Allocator, Compare, Random, Probability>::max_size() noexcept {
        return std::numeric_limits<size_type>::max() / sizeof(node_value_type);
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    void skip_list<T, Allocator, Compare, Random, Probability>::clear() noexcept {
        if(this->empty()) {
            return;
        }
        this->free_from(this->head.node()->next[0]);
        for(auto i {0}; i <= this->head.node()->max_level; ++i) {
            this->head.node()->next[i] = nullptr;
        }
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline void skip_list<T, Allocator, Compare, Random, Probability>::swap(skip_list &rhs) noexcept {
        ds::swap(this->head.node(), rhs.head.node());
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    template <typename AllocatorRHS>
    inline void skip_list<T, Allocator, Compare, Random, Probability>::swap(skip_list<T, AllocatorRHS,
            value_compare, random_number_generator, probability_generator> &rhs) noexcept {
        ds::swap(this->head.node(), rhs.head.node());
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    typename skip_list<T, Allocator, Compare, Random, Probability>::iterator
    skip_list<T, Allocator, Compare, Random, Probability>::insert(const_reference value, size_type size) {
        if(size == 0) {
            return this->end();
        }
        while(--size > 0) {
            this->emplace(value);
        }
        return this->emplace(value);
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline typename skip_list<T, Allocator, Compare, Random, Probability>::iterator
    skip_list<T, Allocator, Compare, Random, Probability>::insert(rvalue_reference value) {
        return this->emplace(ds::move(value));
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    template <typename Iterator>
    typename skip_list<T, Allocator, Compare, Random, Probability>::iterator
    skip_list<T, Allocator, Compare, Random, Probability>::insert(
            enable_if_t<is_input_iterator_v<Iterator>, Iterator> begin, Iterator end) {
        iterator result {this->end()};
        while(begin not_eq end) {
            if constexpr(is_forward_iterator_v<Iterator>) {
                result = this->emplace(*begin++);
            }else {
                result = this->emplace(ds::move(*begin++));
            }
        }
        return result;
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline typename skip_list<T, Allocator, Compare, Random, Probability>::iterator
    skip_list<T, Allocator, Compare, Random, Probability>::insert(initializer_list<value_type> init_list) {
        return this->insert(init_list.begin(), init_list.end());
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    typename skip_list<T, Allocator, Compare, Random, Probability>::iterator
    skip_list<T, Allocator, Compare, Random, Probability>::erase(
            difference_type pos, size_type size) noexcept {
        if(size == 0) {
            return this->end();
        }
        auto cursor {this->head.node()};
        while(--pos > 0 and cursor->next[0]) {
            cursor = cursor->next[0];
        }
        while(size-- > 0) {
            this->erase_one_node(cursor->next[0]);
        }
        return iterator(cursor->next[0], cursor->next[0]->max_level);
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    typename skip_list<T, Allocator, Compare, Random, Probability>::iterator
    skip_list<T, Allocator, Compare, Random, Probability>::erase_after(
            const_iterator pos, size_type size) noexcept {
        if(size == 0) {
            return this->end();
        }
        while(size-- > 0) {
            this->erase_one_node(pos.iter->next[0]);
        }
        return iterator(pos.iter->next[0], pos.iter->next[0]->max_level);
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    typename skip_list<T, Allocator, Compare, Random, Probability>::iterator
    skip_list<T, Allocator, Compare, Random, Probability>::erase_after(
            const_iterator begin, const_iterator end) noexcept {
        if(begin == end) {
            return this->end();
        }
        while(begin.iter->next[0] not_eq end.iter) {
            this->erase_one_node(begin.iter->next[0]);
        }
        return iterator(begin.iter->next[0], begin.iter->next[0]->max_level);
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline typename skip_list<T, Allocator, Compare, Random, Probability>::iterator
    skip_list<T, Allocator, Compare, Random, Probability>::erase_after(const_iterator pos) noexcept {
        return this->erase_after(pos, 1);
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    template <typename ...Args>
    typename skip_list<T, Allocator, Compare, Random, Probability>::iterator
    skip_list<T, Allocator, Compare, Random, Probability>::emplace(Args &&...args) {
        auto new_node {this->allocate()};
        if constexpr(is_nothrow_constructible_v<value_type>) {
            alloc_traits::construct(ds::address_of(new_node->value), ds::forward<Args>(args)...);
        }else {
            try {
                alloc_traits::construct(ds::address_of(new_node->value), ds::forward<Args>(args)...);
            }catch(...) {
                alloc_traits::operator delete(new_node);
                throw;
            }
        }
        try {
            this->try_increment_max_level();
            this->next_allocate(new_node,
                    new_node->max_level = this->generate_level(this->head.node()->max_level));
        }catch(...) {
            alloc_traits::destroy(ds::address_of(new_node->value));
            alloc_traits::operator delete(new_node);
            throw;
        }
        for(auto i {0}; i <= new_node->max_level; ++i) {
            if constexpr(has_nothrow_function_call_operator_v<value_compare, value_type, value_type>) {
                auto before {this->hint(new_node->value, i).iter};
                new_node->next[i] = before->next[i];
                before->next[i] = new_node;
            }else {
                try {
                    auto before {this->hint(new_node->value, i).iter};
                    new_node->next[i] = before->next[i];
                    before->next[i] = new_node;
                }catch(...) {
                    alloc_traits::destroy(ds::address_of(new_node->value));
                    alloc_traits::operator delete(new_node);
                    throw;
                }
            }
        }
        return iterator(new_node, new_node->max_level);
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    void skip_list<T, Allocator, Compare, Random, Probability>::pop_front() noexcept {
        if(this->empty()) {
            return;
        }
        auto pop_node {this->head.node()->next[0]};
        for(auto i {0}; i <= pop_node->max_level; ++i) {
            this->head.node()->next[i] = pop_node->next[i];
        }
        alloc_traits::destroy(ds::address_of(pop_node->value));
        alloc_traits::operator delete(pop_node->next);
        alloc_traits::operator delete(pop_node);
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline typename skip_list<T, Allocator, Compare, Random, Probability>::random_number_generator &
    skip_list<T, Allocator, Compare, Random, Probability>::get_random_number_generator() noexcept {
        return this->head.random();
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline const typename skip_list<T, Allocator, Compare, Random, Probability>::random_number_generator &
    skip_list<T, Allocator, Compare, Random, Probability>::get_random_number_generator() const noexcept {
        return this->head.random();
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline typename skip_list<T, Allocator, Compare, Random, Probability>::probability_generator &
    skip_list<T, Allocator, Compare, Random, Probability>::get_probability_generator() noexcept {
        return this->head.probability();
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline const typename skip_list<T, Allocator, Compare, Random, Probability>::probability_generator &
    skip_list<T, Allocator, Compare, Random, Probability>::get_probability_generator() const noexcept {
        return this->head.probability();
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    template <typename ...Args>
    inline void skip_list<T, Allocator, Compare, Random, Probability>::reset_random_number_generator(
            Args &&...args) noexcept(is_nothrow_move_assignable_v<random_number_generator> or
                    (not is_move_assignable_v<random_number_generator> and
                    is_nothrow_copy_assignable_v<random_number_generator>)) {
        if constexpr(not is_stateless_v<random_number_generator>) {
            this->head.random() = random_number_generator(ds::forward<Args>(args)...);
        }
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    template <typename ...Args>
    inline void skip_list<T, Allocator, Compare, Random, Probability>::reset_probability_generator(
            Args &&...args) noexcept(is_nothrow_move_assignable_v<probability_generator> or
                    (not is_move_assignable_v<probability_generator> and
                    is_nothrow_copy_assignable_v<probability_generator>)) {
        if constexpr(not is_stateless_v<probability_generator>) {
            this->head.random() = probability_generator(ds::forward<Args>(args)...);
        }
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    template <typename ValueType>
    typename skip_list<T, Allocator, Compare, Random, Probability>::size_type
    skip_list<T, Allocator, Compare, Random, Probability>::remove(const ValueType &value)
            noexcept(has_nothrow_equal_to_operator_v<value_type, ValueType>) {
        if(value < *this->cbegin()) {
            return 0;
        }
        size_type size {0};
        bool removed {};
        for(auto cursor {this->head.node()};;) {
            if(cursor->next[0]->value == value) {
                this->erase_one_node(cursor);
                ++size;
                if(not removed) {
                    removed = true;
                }
            }else {
                if(removed) {
                    break;
                }
                cursor = cursor->next[0];
            }
            if(not cursor->next[0]) {
                break;
            }
        }
        return size;
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    template <typename UnaryPredicate>
    typename skip_list<T, Allocator, Compare, Random, Probability>::size_type
    skip_list<T, Allocator, Compare, Random, Probability>::remove_if(UnaryPredicate pred)
            noexcept(has_nothrow_function_call_operator_v<UnaryPredicate, value_type>) {
        size_type size {0};
        for(auto cursor {this->head.node()}; cursor->next[0];) {
            if(pred(cursor->next[0]->value)) {
                this->erase_one_node(cursor);
                ++size;
            }else {
                cursor = cursor->next[0];
            }
        }
        return size;
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    inline void skip_list<T, Allocator, Compare, Random, Probability>::unique()
            noexcept(has_nothrow_equal_to_operator_v<value_type>) {
        this->unique(equal_to<value_type>());
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    template <typename BinaryPredicate>
    void skip_list<T, Allocator, Compare, Random, Probability>::unique(BinaryPredicate pred)
            noexcept(has_nothrow_function_call_operator_v<BinaryPredicate, value_type, value_type>) {
        for(auto cursor {this->head.node()}; cursor->next[0] and cursor->next[0]->next[0];) {
            if(pred(cursor->next[0]->value, cursor->next[0]->next[0]->value)) {
                this->erase_one_node(cursor);
            }else {
                cursor = cursor->next[0];
            }
        }
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    template <typename ValueType>
    typename skip_list<T, Allocator, Compare, Random, Probability>::iterator
    skip_list<T, Allocator, Compare, Random, Probability>::find(const ValueType &value)
            noexcept(has_nothrow_equal_to_operator_v<value_type, ValueType> and
                    has_nothrow_function_call_operator_v<value_compare, value_type, ValueType>) {
        auto cursor {this->head.node()};
        auto level {cursor->max_level};
        while(true) {
            if(not cursor->next[level]) {
                --level;
                continue;
            }
            const auto &value_to_compare {cursor->next[level]->value};
            if(value_to_compare == value) {
                return iterator(cursor->next[level], cursor->next[level]->max_level);
            }
            if(this->head.compare()(value, value_to_compare)) {
                if(level > 0) {
                    --level;
                }else if(level == 0) {
                    break;
                }
            }else {
                if(level == 0) {
                    break;
                }
                cursor = cursor->next[level];
            }
        }
        return this->end();
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    template <typename ValueType>
    typename skip_list<T, Allocator, Compare, Random, Probability>::const_iterator
    skip_list<T, Allocator, Compare, Random, Probability>::find(const ValueType &value) const
            noexcept(has_nothrow_equal_to_operator_v<value_type, ValueType> and
                    has_nothrow_function_call_operator_v<value_compare, value_type, ValueType>) {
        return const_cast<skip_list *>(this)->find(value);
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    template <typename UnaryPredicate>
    typename skip_list<T, Allocator, Compare, Random, Probability>::iterator
    skip_list<T, Allocator, Compare, Random, Probability>::find_if(UnaryPredicate pred)
            noexcept(has_nothrow_function_call_operator_v<UnaryPredicate, value_type>) {
        for(auto cursor {this->head.node()}; cursor->next[0];) {
            if(pred(cursor->next[0]->value)) {
                return iterator(cursor, cursor->max_level);
            }else {
                cursor = cursor->next[0];
            }
        }
        return this->end();
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    template <typename UnaryPredicate>
    typename skip_list<T, Allocator, Compare, Random, Probability>::const_iterator
    skip_list<T, Allocator, Compare, Random, Probability>::find_if(UnaryPredicate pred) const
            noexcept(has_nothrow_function_call_operator_v<UnaryPredicate, value_type>) {
        return const_cast<skip_list *>(this)->find_if<add_lvalue_reference_t<UnaryPredicate>>(pred);
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    template <typename ValueType>
    inline bool skip_list<T, Allocator, Compare, Random, Probability>::contains(const ValueType &value)
            const noexcept(has_nothrow_equal_to_operator_v<value_type, ValueType> and
                    has_nothrow_function_call_operator_v<value_compare, value_type, ValueType>) {
        return this->find(value) not_eq this->cend();
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    template <typename UnaryPredicate>
    inline bool skip_list<T, Allocator, Compare, Random, Probability>::contains_if(UnaryPredicate pred)
            const noexcept(has_nothrow_function_call_operator_v<UnaryPredicate, value_type>) {
        return this->find_if<add_lvalue_reference_t<UnaryPredicate>>(pred) not_eq this->cend();
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    template <typename ValueType>
    typename skip_list<T, Allocator, Compare, Random, Probability>::size_type
    skip_list<T, Allocator, Compare, Random, Probability>::count(const ValueType &value) const
            noexcept(has_nothrow_equal_to_operator_v<value_type, ValueType> and
                    has_nothrow_function_call_operator_v<value_compare, value_type, ValueType>) {
        size_type size {0};
        auto cursor {this->head.node()};
        auto level {cursor->max_level};
        bool found {};
        while(true) {
            const auto &value_to_compare {cursor->next[level]->value};
            if(value_to_compare == value) {
                found = true;
                ++size;
            }
            if(this->head.compare()(value, value_to_compare)) {
                if(level > 0) {
                    --level;
                }else if(level == 0) {
                    break;
                }
            }else {
                if(found or level == 0) {
                    break;
                }
                cursor = cursor->next[level];
            }
        }
        return size;
    }
    template <typename T, typename Allocator, typename Compare, typename Random, typename Probability>
    template <typename UnaryPredicate>
    typename skip_list<T, Allocator, Compare, Random, Probability>::size_type
    skip_list<T, Allocator, Compare, Random, Probability>::count_if(UnaryPredicate pred) const
            noexcept(has_nothrow_function_call_operator_v<UnaryPredicate, value_type>) {
        size_type size {0};
        for(auto cursor {this->head.node()}; cursor->next[0];) {
            if(pred(cursor->next[0]->value)) {
                ++size;
            }else {
                cursor = cursor->next[0];
            }
        }
        return size;
    }
}

#endif //DATA_STRUCTURE_SKIP_LIST_HPP
