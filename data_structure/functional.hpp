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

#ifndef DATA_STRUCTURE_FUNCTIONAL_HPP
#define DATA_STRUCTURE_FUNCTIONAL_HPP

#include "type_traits.hpp"
#include "memory.hpp"

namespace data_structure {
    template <typename T>
    class reference_wrapper {
    public:
        using type = T;
    private:
        type *pointer;
    public:
        constexpr reference_wrapper(type &ref) noexcept : pointer {address_of(ref)} {}
        reference_wrapper(const reference_wrapper &rhs) noexcept = default;
        reference_wrapper(reference_wrapper &&) noexcept = delete;
    public:
        reference_wrapper &operator=(const reference_wrapper &) noexcept = default;
        reference_wrapper &operator=(reference_wrapper &&) noexcept = delete;
        operator type &() const noexcept {
            return *pointer;
        }
        template <typename ...Args>
        typename invoke_result<type &, Args...>::type operator()(Args &&...args) const {
            return this->get()(forward<Args>(args)...);
        }
    public:
        type &get() const noexcept {
            return *pointer;
        }
    };
}

#endif //DATA_STRUCTURE_FUNCTIONAL_HPP