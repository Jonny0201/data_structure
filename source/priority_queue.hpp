/*
* Copyright © [2019 - 2024] [Jonny]
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
#include "heap.hpp"

namespace data_structure {

__DATA_STRUCTURE_START(priority queue implementation)
template <typename T, typename Container = vector<T>, typename Compare = std::less<T>>
class priority_queue {
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
    static_assert(is_same<T, typename container_type::value_type>::value,
            "The value type of priority queue should be same as the container's value_type!");
private:
    __dsa::partial_compressor<Container, Compare> container;
public:
    constexpr priority_queue() = default;
    template <typename Allocator>
    explicit constexpr priority_queue(const Allocator &allocator)
            noexcept(is_nothrow_constructible_v<Container, Allocator>) : container(allocator) {}
    explicit constexpr priority_queue(const Container &container) : container {container} {
        auto &c {this->container.first()};
        ds::make_heap(c.begin(), c.end(), this->container.second());
    }
    template <typename Allocator>
    explicit constexpr priority_queue(const Container &container, const Allocator &allocator) :
            container(container, allocator) {
        auto &c {this->container.first()};
        ds::make_heap(c.begin(), c.end(), this->container.second());
    }
    explicit constexpr priority_queue(Container &&container) noexcept : container {ds::move(container)} {
        auto &c {this->container.first()};
        ds::make_heap(c.begin(), c.end(), this->container.second());
    }
    template <typename Allocator>
    explicit constexpr priority_queue(Container &&container, const Allocator &allocator)
            noexcept(is_nothrow_constructible_v<Container, Container &&, const Allocator &>) :
            container(ds::move(container), allocator) {
        auto &c {this->container.first()};
        ds::make_heap(c.begin(), c.end(), this->container.second());
    }
    template <IsInputIterator InputIterator>
    constexpr priority_queue(InputIterator begin, InputIterator end) : container(ds::move(begin), ds::move(end)) {
        auto &container {this->container.first()};
        ds::make_heap(container.begin(), container.end(), this->container.second());
    }
    template <IsInputIterator InputIterator, typename Allocator>
    constexpr priority_queue(InputIterator begin, InputIterator end, const Allocator &allocator) :
            container(ds::move(begin), ds::move(end), allocator) {
        auto &container {this->container.first()};
        ds::make_heap(container.begin(), container.end(), this->container.second());
    }
    constexpr priority_queue(const priority_queue &) = default;
    template <typename Allocator>
    constexpr priority_queue(const priority_queue &rhs, const Allocator &allocator) :
            container(rhs.container, allocator) {}
    constexpr priority_queue(priority_queue &&) noexcept = default;
    template <typename Allocator>
    constexpr priority_queue(priority_queue &&rhs, const Allocator &allocator)
            noexcept(is_nothrow_constructible_v<Container, Container &&, const Allocator &>) :
            container(ds::move(rhs.container), allocator) {}
    constexpr ~priority_queue() noexcept = default;
public:
    constexpr priority_queue &operator=(const priority_queue &) = default;
    constexpr priority_queue &operator=(priority_queue &&) noexcept = default;
public:
    [[nodiscard]]
    constexpr reference top() noexcept {
        return this->container.first().front();
    }
    [[nodiscard]]
    constexpr const_reference top() const noexcept {
        return this->container.first().front();
    }
    [[nodiscard]]
    constexpr size_type size() const noexcept {
        return this->container.first().size();
    }
    [[nodiscard]]
    constexpr bool empty() const noexcept {
        return this->container.first().empty();
    }
    constexpr void swap(priority_queue &rhs) noexcept {
        ds::swap(this->container, rhs.container);
    }
    constexpr void push(const_reference value) {
        this->emplace(value);
    }
    constexpr void push(rvalue_reference value) {
        this->emplace(ds::move(value));
    }
    template <typename ...Args>
    constexpr void emplace(Args &&...args) {
        auto &container {this->container.first()};
        container.emplace_back(ds::forward<Args>(args)...);
        ds::push_heap(container.begin(), container.end(), this->container.second());
    }
    constexpr void pop() {
        auto &container {this->container.first()};
        ds::pop_heap(container.begin(), container.end(), this->container.second());
        container.pop_back();
    }
};
__DATA_STRUCTURE_END(priority queue implementation)
}       // namespace data_structure

#endif      // DATA_STRUCTURE_PRIORITY_QUEUE_HPP
