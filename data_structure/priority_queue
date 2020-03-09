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

#ifndef DATA_STRUCTURE_PRIORITY_QUEUE_HPP
#define DATA_STRUCTURE_PRIORITY_QUEUE_HPP

#include "vector.hpp"

namespace data_structure {
    template <typename T, typename Container = vector_base<T>,
            typename Compare = less<typename Container::value_type, typename Container::value_type>>
    class priority_queue final {
    public:
        using container_type = Container;
        using value_compare = Compare;
        using size_type = typename container_type::size_type;
        using difference_type = typename container_type::difference_type;
        using value_type = typename container_type::value_type;
        using reference = typename container_type::reference;
        using const_reference = typename container_type::const_reference;
        using rvalue_reference = typename container_type::rvalue_reference;
        using pointer = typename container_type::pointer;
        using const_pointer = typename container_type::const_pointer;
        static_assert(is_same<value_type, T>::value,
                "The Container::value_type must be the same as template argument T!");
    private:
        using compare_ref = typename add_lvalue_reference<value_compare>::type;
    private:
        container_type container;
        value_compare compare;
    public:
        constexpr priority_queue() noexcept(is_nothrow_default_constructible<container_type>::value and
                is_nothrow_default_constructible<value_compare>::value) = default;
        explicit priority_queue(const value_compare &compare)
                noexcept(is_nothrow_default_constructible<container_type>::value and
                        is_nothrow_copy_constructible<value_compare>::value) : container {}, compare {compare} {}
        explicit priority_queue(const container_type &container)
                noexcept(is_nothrow_copy_constructible<container_type>::value and
                        is_nothrow_default_constructible<value_compare>::value) : container {container}, compare {} {
            ds::make_heap<compare_ref>(this->container.begin(), this->container.end(), this->compare);
        }
        explicit priority_queue(container_type &&container)
                noexcept(is_nothrow_move_constructible<container_type>::value and
                        is_nothrow_default_constructible<value_compare>::value) :
                container {ds::move(container)}, compare {} {
            ds::make_heap<compare_ref>(this->container.begin(), this->container.end(), this->compare);
        }
        priority_queue(const container_type &container, const value_compare &compare)
                noexcept(is_nothrow_copy_constructible<container_type>::value and
                        is_nothrow_copy_constructible<value_compare>::value) :
                container {container}, compare {compare} {
            ds::make_heap<compare_ref>(this->container.begin(), this->container.end(), this->compare);
        }
        priority_queue(container_type &&container, const value_compare &compare)
                noexcept(is_nothrow_move_constructible<container_type>::value and
                        is_nothrow_copy_constructible<value_compare>::value) :
                container {ds::move(container)}, compare {compare} {
            ds::make_heap<compare_ref>(this->container.begin(), this->container.end(), this->compare);
        }
        priority_queue(const priority_queue &queue)
                noexcept(is_nothrow_copy_constructible<container_type>::value and
                        is_nothrow_copy_constructible<value_compare>::value) :
                container {queue.container}, compare {queue.compare} {}
        priority_queue(priority_queue &&queue)
                noexcept(is_nothrow_move_constructible<container_type>::value and
                        is_nothrow_copy_constructible<value_compare>::value) :
                container {ds::move(queue.container)}, compare {queue.compare} {}
        ~priority_queue() noexcept = default;
    public:
        priority_queue &operator=(const priority_queue &rhs)
                noexcept(is_nothrow_copy_assignable<container_type>::value and
                        is_nothrow_copy_assignable<value_compare>::value){
            if(this == &rhs) {
                return *this;
            }
            this->container = rhs.container;
            this->compare = rhs.compare;
            return *this;
        }
        priority_queue &operator=(priority_queue &&rhs)
                noexcept(is_nothrow_move_constructible<container_type>::value and
                        is_nothrow_copy_assignable<value_type>::value) {
            if(this == &rhs) {
                return *this;
            }
            this->container = ds::move(rhs.container);
            this->compare = rhs.compare;
            return *this;
        }
    public:
        const_reference top() const {
            return this->container.front();
        }
        [[nodiscard]]
        bool empty() const noexcept {
            return this->container.empty();
        }
        [[nodiscard]]
        size_type size() const noexcept {
            return this->container.size();
        }
        void push(const_reference value) {
            this->container.push_back(value);
            ds::push_heap<compare_ref>(this->container.begin(), this->container.end(), this->compare);
        }
        void push(rvalue_reference value) {
            this->container.push_back(ds::move(value));
            ds::push_heap<compare_ref>(this->container.begin(), this->container.end(), this->compare);
        }
        template <typename ...Args>
        void emplace(Args &&...args) {
            this->container.emplace_back(ds::forward<Args>(args)...);
            ds::push_heap<compare_ref>(this->container.begin(), this->container.end(), this->compare);
        }
        void pop() {
            ds::pop_heap<compare_ref>(this->container.begin(), this->container.end(), this->compare);
            this->container.pop_back();
        }
        void swap(priority_queue &queue) noexcept(is_nothrow_swappable<value_compare>::value) {
            this->container.swap(queue.container);
            ds::swap(this->compare, queue.compare);
        }
    };

    template <typename T, typename Container, typename Compare>
    inline void swap(priority_queue<T, Container, Compare> &lhs, priority_queue<T, Container, Compare> &rhs)
            noexcept(is_nothrow_swappable<Compare>::value) {
        lhs.swap(rhs);
    }
}

#endif //DATA_STRUCTURE_PRIORITY_QUEUE_HPP
