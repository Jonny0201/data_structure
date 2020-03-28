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

#ifndef DATA_STRUCTURE_META_HPP
#define DATA_STRUCTURE_META_HPP

#include "type_traits.hpp"

namespace data_structure {
    struct dynamic final {
        constexpr dynamic() noexcept = default;
        constexpr dynamic(const dynamic &) noexcept = default;
        constexpr dynamic(dynamic &&) noexcept = default;
        constexpr dynamic &operator=(const dynamic &) noexcept = default;
        constexpr dynamic &operator=(dynamic &&) noexcept = default;
        template <typename T>
        constexpr dynamic(T) noexcept {}
        template <typename T>
        constexpr operator T() noexcept(is_nothrow_default_constructible<T>::value) {
            return {};
        }
        template <typename T>
        constexpr operator T() const noexcept(is_nothrow_default_constructible<T>::value) {
            return {};
        }
    };
    template <typename ...>
    struct multi_dynamic final {
        constexpr multi_dynamic() noexcept = default;
        constexpr multi_dynamic(const multi_dynamic &) noexcept = default;
        constexpr multi_dynamic(multi_dynamic &&) noexcept = default;
        constexpr multi_dynamic &operator=(const multi_dynamic &) noexcept = default;
        constexpr multi_dynamic &operator=(multi_dynamic &&) noexcept = default;
        template <typename ...Args>
        constexpr multi_dynamic(Args &&...) noexcept {}
        template <typename T>
        constexpr operator T() noexcept(is_nothrow_default_constructible<T>::value) {
            return {};
        }
        template <typename T>
        constexpr operator T() const noexcept(is_nothrow_default_constructible<T>::value) {
            return {};
        }
    };
    struct nil final {};
    struct null_type final {};
}

#endif //DATA_STRUCTURE_META_HPP
