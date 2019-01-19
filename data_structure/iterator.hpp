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

#ifndef DATA_STRUCTURE_ITERATOR_HPP
#define DATA_STRUCTURE_ITERATOR_HPP

namespace data_structure {
    struct output_iterator_tag {};
    struct input_iterator_tag {};
    struct forward_iterator_tag : input_iterator_tag {};
    struct bidirectional_iterator_tag : forward_iterator_tag {};
    struct random_access_iterator_tag : bidirectional_iterator_tag {};
}

namespace data_structure {
    template <typename Iterator>
    struct iterator_traits {
        using size_type = typename Iterator::size_type;
        using difference_type = typename Iterator::difference_type;
        using value_type = typename Iterator::value_type;
        using reference = typename Iterator::reference;
        using const_reference = typename Iterator::const_reference;
        using rvalue_reference = typename Iterator::rvalue_reference;
        using pointer = typename Iterator::pointer;
        using const_pointer = typename Iterator::const_pointer;
        using iterator_category = typename Iterator::iterator_category;
    };
    template <typename T>
    struct iterator_traits<T *> {
        using size_type = decltype(sizeof 0);
        using difference_type = decltype(static_cast<int *>(nullptr) - static_cast<int *>(nullptr));
        using value_type = T;
        using reference = value_type &;
        using const_reference = const value_type &;
        using rvalue_reference = value_type &&;
        using pointer = value_type *;
        using const_pointer = const value_type *;
        using iterator_category = random_access_iterator_tag;
    };
}

#endif //DATA_STRUCTURE_ITERATOR_HPP
