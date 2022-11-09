/*
    * Copyright © [2019 - 2022] [Jonny Charlotte]
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

#include "../buffer.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

template <typename T>
struct stateful_allocator : ds::allocator<T> {
    void *p {};
};

template <typename T>
class memory_recorder {
public:
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using value_type = T;
    using reference = ds::add_lvalue_reference_t<value_type>;
    using const_reference = ds::add_const_reference_t<value_type>;
    using rvalue_reference = ds::add_rvalue_reference_t<value_type>;
    using pointer = ds::add_pointer_t<value_type>;
    using const_pointer = ds::add_const_pointer_t<value_type>;
private:
    static std::vector<void *> record;
public:
    constexpr memory_recorder() noexcept = default;
    constexpr memory_recorder(const memory_recorder &) noexcept = default;
    constexpr memory_recorder(memory_recorder &&) noexcept = default;
    constexpr ~memory_recorder() noexcept = default;
public:
    memory_recorder &operator=(const memory_recorder &) noexcept = default;
    memory_recorder &operator=(memory_recorder &&) noexcept = default;
    std::strong_ordering operator<=>(const memory_recorder &) const noexcept = default;
public:
    pointer allocate(size_type n) {
        auto result {::operator new(n * sizeof(value_type))};
        this->record.emplace_back(result);
        return static_cast<pointer>(result);
    }
    void deallocate(void *ptr, size_type) {
        if(ptr == nullptr) {
            return;
        }
        auto it {std::find(this->record.cbegin(), this->record.cend(), ptr)};
        this->record.erase(it);
        ::operator delete(ptr);
    }
    bool release_check() {
        return this->record.empty();
    }
};

template <typename T>
std::vector<void *> memory_recorder<T>::record {};

void buffer_unit_test() {
    using namespace ds;
    using namespace std;
    // default allocator
    {
        // constructor buffer(size_type)
        {
            struct s {
                int a;
                char b;
                long c;
                s() noexcept(false) {}
                s(const s &rhs) noexcept(false) : a {rhs.a}, b {rhs.b}, c {rhs.c} {}
                s(s &&rhs) noexcept(false) : a {rhs.a}, b {rhs.b}, c {rhs.c} {}
                s &operator=(const s &) = delete;
                s &operator=(s &&) = delete;
            };
            buffer<int> b1(0);
            buffer<string> b2(0);
            buffer<s> b3(0);
            buffer<int> b4(42);
            buffer<string> b5(42);
            buffer<s> b6(42);
            assert(b1.size() == 64);
            assert(b2.size() == 64);
            assert(b3.size() == 64);
            assert(b4.size() == 42);
            assert(b5.size() == 42);
            assert(b6.size() == 42);
            assert(not b1.empty());
            assert(not b2.empty());
            assert(not b3.empty());
            assert(not b4.empty());
            assert(not b5.empty());
            assert(not b6.empty());
            for(auto i {0}; i < 64; ++i) {
                assert(b1.begin()[i] == 0);
                assert(b2.begin()[i].empty());
                assert(b3.begin()[i].a == 0 and b3.begin()[i].b == 0 and b3.begin()[i].c == 0);
            }
            for(auto i {0}; i < 42; ++i) {
                assert(b4.begin()[i] == 0);
                assert(b5.begin()[i].empty());
                assert(b6.begin()[i].a == 0 and b6.begin()[i].b == 0 and b6.begin()[i].c == 0);
            }
            b1.clear();
            b2.clear();
            b3.clear();
            b4.clear();
            b5.clear();
            b6.clear();
        }

        // constructor buffer(size_type, const_reference)
        {
            struct s {
                int a;
                char b;
                long c;
                s(int a, char b, long c) noexcept(false) : a {a}, b {b}, c {c} {}
                s(const s &rhs) noexcept(false) : a {rhs.a}, b {rhs.b}, c {rhs.c} {}
                s(s &&rhs) noexcept(false) : a {rhs.a}, b {rhs.b}, c {rhs.c} {}
                s &operator=(const s &) = delete;
                s &operator=(s &&) = delete;
            };
            buffer<int> b1(0, 42);
            buffer<string> b2(0, "hello world!");
            buffer<s> b3(0, s(1, 'c', 42));
            buffer<int> b4(42, 42);
            buffer<string> b5(42, "hello world!");
            buffer<s> b6(42, s(1, 'c', 42));
            assert(b1.size() == 64);
            assert(b2.size() == 64);
            assert(b3.size() == 64);
            assert(b4.size() == 42);
            assert(b5.size() == 42);
            assert(b6.size() == 42);
            assert(not b1.empty());
            assert(not b2.empty());
            assert(not b3.empty());
            assert(not b4.empty());
            assert(not b5.empty());
            assert(not b6.empty());
            for(auto i {0}; i < 64; ++i) {
                assert(b1.begin()[i] == 42);
                assert(b2.begin()[i] == "hello world!");
                assert(b3.begin()[i].a == 1 and b3.begin()[i].b == 'c' and b3.begin()[i].c == 42);
            }
            for(auto i {0}; i < 42; ++i) {
                assert(b1.begin()[i] == 42);
                assert(b2.begin()[i] == "hello world!");
                assert(b3.begin()[i].a == 1 and b3.begin()[i].b == 'c' and b3.begin()[i].c == 42);
            }
            b1.clear();
            b2.clear();
            b3.clear();
            b4.clear();
            b5.clear();
            b6.clear();
        }

        // constructor buffer(InputIterator, InputIterator)
        {
            struct int_input_iterator {
                using iterator_category = ds::input_iterator_tag;
                using rvalue_reference = int &&;
                using reference = int &;
                istream_iterator<int> it;
                operator istream_iterator<int>() const noexcept {
                    return this->it;
                }
                bool operator==(const int_input_iterator &rhs) const noexcept {
                    return this->it == rhs.it;
                }
                const int &operator*() const noexcept {
                    return *this->it;
                }
                int_input_iterator &operator++() noexcept {
                    ++this->it;
                    return *this;
                }
                int_input_iterator operator++(int) noexcept {
                    auto tmp {*this};
                    ++*this;
                    return tmp;
                }
            };
            struct string_input_iterator {
                using iterator_category = ds::input_iterator_tag;
                using rvalue_reference = string &&;
                using reference = string &;
                istream_iterator<string> it;
                operator istream_iterator<string>() const noexcept {
                    return this->it;
                }
                bool operator==(const string_input_iterator &rhs) const noexcept {
                    return this->it == rhs.it;
                }
                const string &operator*() const noexcept {
                    return *this->it;
                }
                string_input_iterator &operator++() noexcept {
                    ++this->it;
                    return *this;
                }
                string_input_iterator operator++(int) noexcept {
                    auto tmp {*this};
                    ++*this;
                    return tmp;
                }
            };
            struct s {
                int a;
                s() = default;
                s(int a) noexcept(false) : a {a} {}
                s(const s &rhs) noexcept(false) : a {rhs.a} {}
                s(s &&rhs) noexcept(false) : a {rhs.a} {}
                s &operator=(const s &) = delete;
                s &operator=(s &&) = delete;
                operator int &() noexcept {
                    return this->a;
                }
                operator const int &() const noexcept {
                    return this->a;
                }
            };
            struct s_input_iterator {
                using iterator_category = ds::input_iterator_tag;
                using rvalue_reference = s &&;
                using reference = s &;
                istream_iterator<s> it;
                operator istream_iterator<s>() const noexcept {
                    return this->it;
                }
                bool operator==(const s_input_iterator &rhs) const noexcept {
                    return this->it == rhs.it;
                }
                const s &operator*() const noexcept {
                    return *this->it;
                }
                s_input_iterator &operator++() noexcept {
                    ++this->it;
                    return *this;
                }
                s_input_iterator operator++(int) noexcept {
                    auto tmp {*this};
                    ++*this;
                    return tmp;
                }
            };
            istringstream empty {};
            istringstream number {"1 2 3 4 5 6 7 8 9 10"};
            istringstream strings {"hello1 hello2 hello3 hello4 hello5 hello6 hello7 hello8 hello9 hello10"};
            istringstream for_s {"42 42 42 42 42 42 42 42 42 42 42 42 42 42 42 42 42 42 42 42"};
            buffer<int> b1(int_input_iterator {empty}, {});
            buffer<int> b2(int_input_iterator {number}, {});
            buffer<string> b3(string_input_iterator {empty}, {});
            buffer<string> b4(string_input_iterator {strings}, {});
            buffer<s> b5(s_input_iterator {empty}, {});
            buffer<s> b6(s_input_iterator {for_s}, {});
            assert(b1.size() == 0);
            assert(b2.size() == 10);
            assert(b3.size() == 0);
            assert(b4.size() == 10);
            assert(b5.size() == 0);
            assert(b6.size() == 20);
            assert(b1.empty());
            assert(not b2.empty());
            assert(b3.empty());
            assert(not b4.empty());
            assert(b5.empty());
            assert(not b6.empty());
            for(auto i {0}; i < 10; ++i) {
                assert(b2.begin()[i] == i + 1);
                assert(b4.begin()[i] == string("hello") + to_string(i + 1));
            }
            for(auto i {0}; i < 20; ++i) {
                assert(b6.begin()[i].a == 42);
            }
            b1.clear();
            b2.clear();
            b3.clear();
            b4.clear();
            b5.clear();
            b6.clear();
        }

        // constructor buffer(ForwardIterator, ForwardIterator)
        {
            struct s {
                int a;
                s() = default;
                s(int a) noexcept(false) : a {a} {}
                s(const s &rhs) noexcept(false) : a {rhs.a} {}
                s(s &&rhs) noexcept(false) : a {rhs.a} {}
                s &operator=(const s &) = delete;
                s &operator=(s &&) = delete;
            };
            int arr[] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
            string str_arr[] {"hello1", "hello2", "hello3", "hello4", "hello5", "hello6", "hello7"};
            s s_arr[] {{42}, {}, {42}, {}, {42}, {}, {42}, {}, {42}, {}, {42}, {}};
            buffer<int> b1(static_cast<int *>(nullptr), static_cast<int *>(nullptr));
            buffer<int> b2(begin(arr), end(arr));
            buffer<string> b3(static_cast<string *>(nullptr), static_cast<string *>(nullptr));
            buffer<string> b4(begin(str_arr), end(str_arr));
            buffer<s> b5(static_cast<s *>(nullptr), static_cast<s *>(nullptr));
            buffer<s> b6(begin(s_arr), end(s_arr));
            assert(b1.size() == 0);
            assert(b2.size() == 10);
            assert(b3.size() == 0);
            assert(b4.size() == 7);
            assert(b5.size() == 0);
            assert(b6.size() == 12);
            assert(b1.empty());
            assert(not b2.empty());
            assert(b3.empty());
            assert(not b4.empty());
            assert(b5.empty());
            assert(not b6.empty());
            for(auto i {0}; i < 10; ++i) {
                assert(b2.begin()[i] == i + 1);
            }
            for(auto i {0}; i < 7; ++i) {
                assert(b4.begin()[i] == "hello" + to_string(i + 1));
            }
            for(auto i {0}; i < 12; ++i) {
                assert(b6.begin()[i].a == i % 2 == 0 ? 42 : 0);
            }
            b1.clear();
            b2.clear();
            b3.clear();
            b4.clear();
            b5.clear();
            b6.clear();
        }

        // copy and move
        {
            struct s {
                int a;
                s() = default;
                s(int a) noexcept(false) : a {a} {}
                s(const s &rhs) noexcept(false) : a {rhs.a} {}
                s(s &&rhs) noexcept(false) : a {rhs.a} {}
                s &operator=(const s &) = delete;
                s &operator=(s &&) = delete;
            };
            buffer<int> b1 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
            buffer<int> b2 {b1};
            buffer<int> b3 {ds::move(b1)};
            buffer<string> b4 {"hello1", "hello2", "hello3", "hello4", "hello5", "hello6", "hello7"};
            buffer<string> b5 {b4};
            buffer<string> b6 {ds::move(b4)};
            buffer<s> b7 {{42}, {}, {42}, {}, {42}, {}, {42}, {}, {42}, {}, {42}, {}};
            buffer<s> b8 {b7};
            buffer<s> b9 {ds::move(b7)};
            assert(b1.size() == 0);
            assert(b2.size() == 10);
            assert(b3.size() == 10);
            assert(b4.size() == 0);
            assert(b5.size() == 7);
            assert(b6.size() == 7);
            assert(b7.size() == 0);
            assert(b8.size() == 12);
            assert(b9.size() == 12);
            assert(b1.empty());
            assert(not b2.empty());
            assert(not b3.empty());
            assert(b4.empty());
            assert(not b5.empty());
            assert(not b6.empty());
            assert(b7.empty());
            assert(not b8.empty());
            assert(not b9.empty());
            for(auto i {0}; i < 10; ++i) {
                assert(b2.begin()[i] == i + 1);
                assert(b3.begin()[i] == i + 1);
            }
            for(auto i {0}; i < 7; ++i) {
                assert(b5.begin()[i] == "hello" + to_string(i + 1));
                assert(b6.begin()[i] == "hello" + to_string(i + 1));
            }
            for(auto i {0}; i < 11; ++i) {
                assert(b8.begin()[i].a == i % 2 == 0 ? 42 : 0);
                assert(b9.begin()[i].a == i % 2 == 0 ? 42 : 0);
            }
            b1.clear();
            b2.clear();
            b3.clear();
            b4.clear();
            b5.clear();
            b6.clear();
        }

        // operator[]
        {
            buffer<int> b1 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
            buffer<string> b2 {"hello1", "hello2", "hello3", "hello4", "hello5"};
            for(auto i {0}; i < 10; ++i) {
                assert(b1[i] == i + 1);
            }
            for(auto i {0}; i < 5; ++i) {
                assert(b2[i] == "hello" + to_string(i + 1));
            }
            b1.clear();
            b2.clear();
        }

        // mbegin and mend
        {
            buffer<string> b {"hello1", "hello2", "hello3", "hello4", "hello5"};
            for(auto it {b.mbegin()}; it not_eq b.mend(); ++it) {
                auto tmp {*it};
            }
            for(auto i {0}; i < 5; ++i) {
                assert(b[i].empty());
            }
            b.clear();
        }
    }

    // stateful allocator
    {
        // constructor buffer(size_type)
        {
            struct s {
                int a;
                char b;
                long c;
                s() noexcept(false) {}
                s(const s &rhs) noexcept(false) : a {rhs.a}, b {rhs.b}, c {rhs.c} {}
                s(s &&rhs) noexcept(false) : a {rhs.a}, b {rhs.b}, c {rhs.c} {}
                s &operator=(const s &) = delete;
                s &operator=(s &&) = delete;
            };
            buffer<int, stateful_allocator<int>> b1(0);
            buffer<string, stateful_allocator<string>> b2(0);
            buffer<s, stateful_allocator<s>> b3(0);
            buffer<int, stateful_allocator<int>> b4(42);
            buffer<string, stateful_allocator<string>> b5(42);
            buffer<s, stateful_allocator<s>> b6(42);
            assert(b1.size() == 64);
            assert(b2.size() == 64);
            assert(b3.size() == 64);
            assert(b4.size() == 42);
            assert(b5.size() == 42);
            assert(b6.size() == 42);
            assert(not b1.empty());
            assert(not b2.empty());
            assert(not b3.empty());
            assert(not b4.empty());
            assert(not b5.empty());
            assert(not b6.empty());
            for(auto i {0}; i < 64; ++i) {
                assert(b1.begin()[i] == 0);
                assert(b2.begin()[i].empty());
                //assert(b3.begin()[i].a == 0 and b3.begin()[i].b == 0 and b3.begin()[i].c == 0);
            }
            for(auto i {0}; i < 42; ++i) {
                assert(b4.begin()[i] == 0);
                assert(b5.begin()[i].empty());
                //assert(b6.begin()[i].a == 0 and b6.begin()[i].b == 0 and b6.begin()[i].c == 0);
            }
            b1.clear();
            b2.clear();
            b3.clear();
            b4.clear();
            b5.clear();
            b6.clear();
        }

        // constructor buffer(size_type, const_reference)
        {
            struct s {
                int a;
                char b;
                long c;
                s(int a, char b, long c) noexcept(false) : a {a}, b {b}, c {c} {}
                s(const s &rhs) noexcept(false) : a {rhs.a}, b {rhs.b}, c {rhs.c} {}
                s(s &&rhs) noexcept(false) : a {rhs.a}, b {rhs.b}, c {rhs.c} {}
                s &operator=(const s &) = delete;
                s &operator=(s &&) = delete;
            };
            buffer<int, stateful_allocator<int>> b1(0, 42);
            buffer<string, stateful_allocator<string>> b2(0, "hello world!");
            buffer<s, stateful_allocator<s>> b3(0, s(1, 'c', 42));
            buffer<int, stateful_allocator<int>> b4(42, 42);
            buffer<string, stateful_allocator<string>> b5(42, "hello world!");
            buffer<s, stateful_allocator<s>> b6(42, s(1, 'c', 42));
            assert(b1.size() == 64);
            assert(b2.size() == 64);
            assert(b3.size() == 64);
            assert(b4.size() == 42);
            assert(b5.size() == 42);
            assert(b6.size() == 42);
            assert(not b1.empty());
            assert(not b2.empty());
            assert(not b3.empty());
            assert(not b4.empty());
            assert(not b5.empty());
            assert(not b6.empty());
            for(auto i {0}; i < 64; ++i) {
                assert(b1.begin()[i] == 42);
                assert(b2.begin()[i] == "hello world!");
                assert(b3.begin()[i].a == 1 and b3.begin()[i].b == 'c' and b3.begin()[i].c == 42);
            }
            for(auto i {0}; i < 42; ++i) {
                assert(b1.begin()[i] == 42);
                assert(b2.begin()[i] == "hello world!");
                assert(b3.begin()[i].a == 1 and b3.begin()[i].b == 'c' and b3.begin()[i].c == 42);
            }
            b1.clear();
            b2.clear();
            b3.clear();
            b4.clear();
            b5.clear();
            b6.clear();
        }

        // constructor buffer(InputIterator, InputIterator)
        {
            struct int_input_iterator {
                using iterator_category = ds::input_iterator_tag;
                using rvalue_reference = int &&;
                using reference = int &;
                istream_iterator<int> it;
                operator istream_iterator<int>() const noexcept {
                    return this->it;
                }
                bool operator==(const int_input_iterator &rhs) const noexcept {
                    return this->it == rhs.it;
                }
                const int &operator*() const noexcept {
                    return *this->it;
                }
                int_input_iterator &operator++() noexcept {
                    ++this->it;
                    return *this;
                }
                int_input_iterator operator++(int) noexcept {
                    auto tmp {*this};
                    ++*this;
                    return tmp;
                }
            };
            struct string_input_iterator {
                using iterator_category = ds::input_iterator_tag;
                using rvalue_reference = string &&;
                using reference = string &;
                istream_iterator<string> it;
                operator istream_iterator<string>() const noexcept {
                    return this->it;
                }
                bool operator==(const string_input_iterator &rhs) const noexcept {
                    return this->it == rhs.it;
                }
                const string &operator*() const noexcept {
                    return *this->it;
                }
                string_input_iterator &operator++() noexcept {
                    ++this->it;
                    return *this;
                }
                string_input_iterator operator++(int) noexcept {
                    auto tmp {*this};
                    ++*this;
                    return tmp;
                }
            };
            struct s {
                int a;
                s() = default;
                s(int a) noexcept(false) : a {a} {}
                s(const s &rhs) noexcept(false) : a {rhs.a} {}
                s(s &&rhs) noexcept(false) : a {rhs.a} {}
                s &operator=(const s &) = delete;
                s &operator=(s &&) = delete;
                operator int &() noexcept {
                    return this->a;
                }
                operator const int &() const noexcept {
                    return this->a;
                }
            };
            struct s_input_iterator {
                using iterator_category = ds::input_iterator_tag;
                using rvalue_reference = s &&;
                using reference = s &;
                istream_iterator<s> it;
                operator istream_iterator<s>() const noexcept {
                    return this->it;
                }
                bool operator==(const s_input_iterator &rhs) const noexcept {
                    return this->it == rhs.it;
                }
                const s &operator*() const noexcept {
                    return *this->it;
                }
                s_input_iterator &operator++() noexcept {
                    ++this->it;
                    return *this;
                }
                s_input_iterator operator++(int) noexcept {
                    auto tmp {*this};
                    ++*this;
                    return tmp;
                }
            };
            istringstream empty {};
            istringstream number {"1 2 3 4 5 6 7 8 9 10"};
            istringstream strings {"hello1 hello2 hello3 hello4 hello5 hello6 hello7 hello8 hello9 hello10"};
            istringstream for_s {"42 42 42 42 42 42 42 42 42 42 42 42 42 42 42 42 42 42 42 42"};
            buffer<int, stateful_allocator<int>> b1(int_input_iterator {empty}, {});
            buffer<int, stateful_allocator<int>> b2(int_input_iterator {number}, {});
            buffer<string, stateful_allocator<string>> b3(string_input_iterator {empty}, {});
            buffer<string, stateful_allocator<string>> b4(string_input_iterator {strings}, {});
            buffer<s, stateful_allocator<s>> b5(s_input_iterator {empty}, {});
            buffer<s, stateful_allocator<s>> b6(s_input_iterator {for_s}, {});
            assert(b1.size() == 0);
            assert(b2.size() == 10);
            assert(b3.size() == 0);
            assert(b4.size() == 10);
            assert(b5.size() == 0);
            assert(b6.size() == 20);
            assert(b1.empty());
            assert(not b2.empty());
            assert(b3.empty());
            assert(not b4.empty());
            assert(b5.empty());
            assert(not b6.empty());
            for(auto i {0}; i < 10; ++i) {
                assert(b2.begin()[i] == i + 1);
                assert(b4.begin()[i] == string("hello") + to_string(i + 1));
            }
            for(auto i {0}; i < 20; ++i) {
                assert(b6.begin()[i].a == 42);
            }
            b1.clear();
            b2.clear();
            b3.clear();
            b4.clear();
            b5.clear();
            b6.clear();
        }

        // constructor buffer(ForwardIterator, ForwardIterator)
        {
            struct s {
                int a;
                s() = default;
                s(int a) noexcept(false) : a {a} {}
                s(const s &rhs) noexcept(false) : a {rhs.a} {}
                s(s &&rhs) noexcept(false) : a {rhs.a} {}
                s &operator=(const s &) = delete;
                s &operator=(s &&) = delete;
            };
            int arr[] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
            string str_arr[] {"hello1", "hello2", "hello3", "hello4", "hello5", "hello6", "hello7"};
            s s_arr[] {{42}, {}, {42}, {}, {42}, {}, {42}, {}, {42}, {}, {42}, {}};
            buffer<int, stateful_allocator<int>> b1(static_cast<int *>(nullptr), static_cast<int *>(nullptr));
            buffer<int, stateful_allocator<int>> b2(begin(arr), end(arr));
            buffer<string, stateful_allocator<string>> b3(static_cast<string *>(nullptr), static_cast<string *>(nullptr));
            buffer<string, stateful_allocator<string>> b4(begin(str_arr), end(str_arr));
            buffer<s, stateful_allocator<s>> b5(static_cast<s *>(nullptr), static_cast<s *>(nullptr));
            buffer<s, stateful_allocator<s>> b6(begin(s_arr), end(s_arr));
            assert(b1.size() == 0);
            assert(b2.size() == 10);
            assert(b3.size() == 0);
            assert(b4.size() == 7);
            assert(b5.size() == 0);
            assert(b6.size() == 12);
            assert(b1.empty());
            assert(not b2.empty());
            assert(b3.empty());
            assert(not b4.empty());
            assert(b5.empty());
            assert(not b6.empty());
            for(auto i {0}; i < 10; ++i) {
                assert(b2.begin()[i] == i + 1);
            }
            for(auto i {0}; i < 7; ++i) {
                assert(b4.begin()[i] == "hello" + to_string(i + 1));
            }
            for(auto i {0}; i < 12; ++i) {
                assert(b6.begin()[i].a == i % 2 == 0 ? 42 : 0);
            }
            b1.clear();
            b2.clear();
            b3.clear();
            b4.clear();
            b5.clear();
            b6.clear();
        }

        // copy and move
        {
            struct s {
                int a;
                s() = default;
                s(int a) noexcept(false) : a {a} {}
                s(const s &rhs) noexcept(false) : a {rhs.a} {}
                s(s &&rhs) noexcept(false) : a {rhs.a} {}
                s &operator=(const s &) = delete;
                s &operator=(s &&) = delete;
            };
            buffer<int, stateful_allocator<int>> b1 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
            buffer<int, stateful_allocator<int>> b2 {b1};
            buffer<int, stateful_allocator<int>> b3 {ds::move(b1)};
            buffer<string, stateful_allocator<string>> b4 {"hello1", "hello2", "hello3", "hello4", "hello5", "hello6", "hello7"};
            buffer<string, stateful_allocator<string>> b5 {b4};
            buffer<string, stateful_allocator<string>> b6 {ds::move(b4)};
            buffer<s, stateful_allocator<s>> b7 {{42}, {}, {42}, {}, {42}, {}, {42}, {}, {42}, {}, {42}, {}};
            buffer<s, stateful_allocator<s>> b8 {b7};
            buffer<s, stateful_allocator<s>> b9 {ds::move(b7)};
            assert(b1.size() == 0);
            assert(b2.size() == 10);
            assert(b3.size() == 10);
            assert(b4.size() == 0);
            assert(b5.size() == 7);
            assert(b6.size() == 7);
            assert(b7.size() == 0);
            assert(b8.size() == 12);
            assert(b9.size() == 12);
            assert(b1.empty());
            assert(not b2.empty());
            assert(not b3.empty());
            assert(b4.empty());
            assert(not b5.empty());
            assert(not b6.empty());
            assert(b7.empty());
            assert(not b8.empty());
            assert(not b9.empty());
            for(auto i {0}; i < 10; ++i) {
                assert(b2.begin()[i] == i + 1);
                assert(b3.begin()[i] == i + 1);
            }
            for(auto i {0}; i < 7; ++i) {
                assert(b5.begin()[i] == "hello" + to_string(i + 1));
                assert(b6.begin()[i] == "hello" + to_string(i + 1));
            }
            for(auto i {0}; i < 11; ++i) {
                assert(b8.begin()[i].a == i % 2 == 0 ? 42 : 0);
                assert(b9.begin()[i].a == i % 2 == 0 ? 42 : 0);
            }
            b1.clear();
            b2.clear();
            b3.clear();
            b4.clear();
            b5.clear();
            b6.clear();
        }

        // operator[]
        {
            buffer<int, stateful_allocator<int>> b1 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
            buffer<string, stateful_allocator<string>> b2 {"hello1", "hello2", "hello3", "hello4", "hello5"};
            for(auto i {0}; i < 10; ++i) {
                assert(b1[i] == i + 1);
            }
            for(auto i {0}; i < 5; ++i) {
                assert(b2[i] == "hello" + to_string(i + 1));
            }
            b1.clear();
            b2.clear();
        }

        // mbegin and mend
        {
            buffer<string, stateful_allocator<string>> b {"hello1", "hello2", "hello3", "hello4", "hello5"};
            for(auto it {b.mbegin()}; it not_eq b.mend(); ++it) {
                auto tmp {*it};
            }
            for(auto i {0}; i < 5; ++i) {
                assert(b[i].empty());
            }
            b.clear();
        }
    }

    // memory_recorder be allocator
    {
        // constructor buffer(size_type)
        {
            struct s {
                int a;
                char b;
                long c;
                s() noexcept(false) {}
                s(const s &rhs) noexcept(false) : a {rhs.a}, b {rhs.b}, c {rhs.c} {}
                s(s &&rhs) noexcept(false) : a {rhs.a}, b {rhs.b}, c {rhs.c} {}
                s &operator=(const s &) = delete;
                s &operator=(s &&) = delete;
            };
            buffer<int, memory_recorder<int>> b1(0);
            buffer<string, memory_recorder<string>> b2(0);
            buffer<s, memory_recorder<s>> b3(0);
            buffer<int, memory_recorder<int>> b4(42);
            buffer<string, memory_recorder<string>> b5(42);
            buffer<s, memory_recorder<s>> b6(42);
            assert(b1.size() == 64);
            assert(b2.size() == 64);
            assert(b3.size() == 64);
            assert(b4.size() == 42);
            assert(b5.size() == 42);
            assert(b6.size() == 42);
            assert(not b1.empty());
            assert(not b2.empty());
            assert(not b3.empty());
            assert(not b4.empty());
            assert(not b5.empty());
            assert(not b6.empty());
            assert(not b1.allocator().release_check());
            assert(not b2.allocator().release_check());
            assert(not b3.allocator().release_check());
            assert(not b4.allocator().release_check());
            assert(not b5.allocator().release_check());
            assert(not b6.allocator().release_check());
            for(auto i {0}; i < 64; ++i) {
                assert(b1.begin()[i] == 0);
                assert(b2.begin()[i].empty());
                //assert(b3.begin()[i].a == 0 and b3.begin()[i].b == 0 and b3.begin()[i].c == 0);
            }
            for(auto i {0}; i < 42; ++i) {
                assert(b4.begin()[i] == 0);
                assert(b5.begin()[i].empty());
                //assert(b6.begin()[i].a == 0 and b6.begin()[i].b == 0 and b6.begin()[i].c == 0);
            }
            b1.clear();
            b2.clear();
            b3.clear();
            b4.clear();
            b5.clear();
            b6.clear();
            assert(b1.allocator().release_check());
            assert(b2.allocator().release_check());
            assert(b3.allocator().release_check());
            assert(b4.allocator().release_check());
            assert(b5.allocator().release_check());
            assert(b6.allocator().release_check());
        }

        // constructor buffer(size_type, const_reference)
        {
            struct s {
                int a;
                char b;
                long c;
                s(int a, char b, long c) noexcept(false) : a {a}, b {b}, c {c} {}
                s(const s &rhs) noexcept(false) : a {rhs.a}, b {rhs.b}, c {rhs.c} {}
                s(s &&rhs) noexcept(false) : a {rhs.a}, b {rhs.b}, c {rhs.c} {}
                s &operator=(const s &) = delete;
                s &operator=(s &&) = delete;
            };
            buffer<int, memory_recorder<int>> b1(0, 42);
            buffer<string, memory_recorder<string>> b2(0, "hello world!");
            buffer<s, memory_recorder<s>> b3(0, s(1, 'c', 42));
            buffer<int, memory_recorder<int>> b4(42, 42);
            buffer<string, memory_recorder<string>> b5(42, "hello world!");
            buffer<s, memory_recorder<s>> b6(42, s(1, 'c', 42));
            assert(b1.size() == 64);
            assert(b2.size() == 64);
            assert(b3.size() == 64);
            assert(b4.size() == 42);
            assert(b5.size() == 42);
            assert(b6.size() == 42);
            assert(not b1.empty());
            assert(not b2.empty());
            assert(not b3.empty());
            assert(not b4.empty());
            assert(not b5.empty());
            assert(not b6.empty());
            assert(not b1.allocator().release_check());
            assert(not b2.allocator().release_check());
            assert(not b3.allocator().release_check());
            assert(not b4.allocator().release_check());
            assert(not b5.allocator().release_check());
            assert(not b6.allocator().release_check());
            for(auto i {0}; i < 64; ++i) {
                assert(b1.begin()[i] == 42);
                assert(b2.begin()[i] == "hello world!");
                assert(b3.begin()[i].a == 1 and b3.begin()[i].b == 'c' and b3.begin()[i].c == 42);
            }
            for(auto i {0}; i < 42; ++i) {
                assert(b1.begin()[i] == 42);
                assert(b2.begin()[i] == "hello world!");
                assert(b3.begin()[i].a == 1 and b3.begin()[i].b == 'c' and b3.begin()[i].c == 42);
            }
            b1.clear();
            b2.clear();
            b3.clear();
            b4.clear();
            b5.clear();
            b6.clear();
            assert(b1.allocator().release_check());
            assert(b2.allocator().release_check());
            assert(b3.allocator().release_check());
            assert(b4.allocator().release_check());
            assert(b5.allocator().release_check());
            assert(b6.allocator().release_check());
        }

        // constructor buffer(InputIterator, InputIterator)
        {
            struct int_input_iterator {
                using iterator_category = ds::input_iterator_tag;
                using rvalue_reference = int &&;
                using reference = int &;
                istream_iterator<int> it;
                operator istream_iterator<int>() const noexcept {
                    return this->it;
                }
                bool operator==(const int_input_iterator &rhs) const noexcept {
                    return this->it == rhs.it;
                }
                const int &operator*() const noexcept {
                    return *this->it;
                }
                int_input_iterator &operator++() noexcept {
                    ++this->it;
                    return *this;
                }
                int_input_iterator operator++(int) noexcept {
                    auto tmp {*this};
                    ++*this;
                    return tmp;
                }
            };
            struct string_input_iterator {
                using iterator_category = ds::input_iterator_tag;
                using rvalue_reference = string &&;
                using reference = string &;
                istream_iterator<string> it;
                operator istream_iterator<string>() const noexcept {
                    return this->it;
                }
                bool operator==(const string_input_iterator &rhs) const noexcept {
                    return this->it == rhs.it;
                }
                const string &operator*() const noexcept {
                    return *this->it;
                }
                string_input_iterator &operator++() noexcept {
                    ++this->it;
                    return *this;
                }
                string_input_iterator operator++(int) noexcept {
                    auto tmp {*this};
                    ++*this;
                    return tmp;
                }
            };
            struct s {
                int a;
                s() = default;
                s(int a) noexcept(false) : a {a} {}
                s(const s &rhs) noexcept(false) : a {rhs.a} {}
                s(s &&rhs) noexcept(false) : a {rhs.a} {}
                s &operator=(const s &) = delete;
                s &operator=(s &&) = delete;
                operator int &() noexcept {
                    return this->a;
                }
                operator const int &() const noexcept {
                    return this->a;
                }
            };
            struct s_input_iterator {
                using iterator_category = ds::input_iterator_tag;
                using rvalue_reference = s &&;
                using reference = s &;
                istream_iterator<s> it;
                operator istream_iterator<s>() const noexcept {
                    return this->it;
                }
                bool operator==(const s_input_iterator &rhs) const noexcept {
                    return this->it == rhs.it;
                }
                const s &operator*() const noexcept {
                    return *this->it;
                }
                s_input_iterator &operator++() noexcept {
                    ++this->it;
                    return *this;
                }
                s_input_iterator operator++(int) noexcept {
                    auto tmp {*this};
                    ++*this;
                    return tmp;
                }
            };
            istringstream empty {};
            istringstream number {"1 2 3 4 5 6 7 8 9 10"};
            istringstream strings {"hello1 hello2 hello3 hello4 hello5 hello6 hello7 hello8 hello9 hello10"};
            istringstream for_s {"42 42 42 42 42 42 42 42 42 42 42 42 42 42 42 42 42 42 42 42"};
            buffer<int, memory_recorder<int>> b1(int_input_iterator {empty}, {});
            buffer<int, memory_recorder<int>> b2(int_input_iterator {number}, {});
            buffer<string, memory_recorder<string>> b3(string_input_iterator {empty}, {});
            buffer<string, memory_recorder<string>> b4(string_input_iterator {strings}, {});
            buffer<s, memory_recorder<s>> b5(s_input_iterator {empty}, {});
            buffer<s, memory_recorder<s>> b6(s_input_iterator {for_s}, {});
            assert(b1.size() == 0);
            assert(b2.size() == 10);
            assert(b3.size() == 0);
            assert(b4.size() == 10);
            assert(b5.size() == 0);
            assert(b6.size() == 20);
            assert(b1.empty());
            assert(not b2.empty());
            assert(b3.empty());
            assert(not b4.empty());
            assert(b5.empty());
            assert(not b6.empty());
            assert(not b1.allocator().release_check());
            assert(not b2.allocator().release_check());
            assert(not b3.allocator().release_check());
            assert(not b4.allocator().release_check());
            assert(not b5.allocator().release_check());
            assert(not b6.allocator().release_check());
            for(auto i {0}; i < 10; ++i) {
                assert(b2.begin()[i] == i + 1);
                assert(b4.begin()[i] == string("hello") + to_string(i + 1));
            }
            for(auto i {0}; i < 20; ++i) {
                assert(b6.begin()[i].a == 42);
            }
            b1.clear();
            b2.clear();
            b3.clear();
            b4.clear();
            b5.clear();
            b6.clear();
            assert(b1.allocator().release_check());
            assert(b2.allocator().release_check());
            assert(b3.allocator().release_check());
            assert(b4.allocator().release_check());
            assert(b5.allocator().release_check());
            assert(b6.allocator().release_check());
        }

        // constructor buffer(ForwardIterator, ForwardIterator)
        {
            struct s {
                int a;
                s() = default;
                s(int a) noexcept(false) : a {a} {}
                s(const s &rhs) noexcept(false) : a {rhs.a} {}
                s(s &&rhs) noexcept(false) : a {rhs.a} {}
                s &operator=(const s &) = delete;
                s &operator=(s &&) = delete;
            };
            int arr[] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
            string str_arr[] {"hello1", "hello2", "hello3", "hello4", "hello5", "hello6", "hello7"};
            s s_arr[] {{42}, {}, {42}, {}, {42}, {}, {42}, {}, {42}, {}, {42}, {}};
            buffer<int, memory_recorder<int>> b1(static_cast<int *>(nullptr), static_cast<int *>(nullptr));
            buffer<int, memory_recorder<int>> b2(begin(arr), end(arr));
            buffer<string, memory_recorder<string>> b3(static_cast<string *>(nullptr), static_cast<string *>(nullptr));
            buffer<string, memory_recorder<string>> b4(begin(str_arr), end(str_arr));
            buffer<s, memory_recorder<s>> b5(static_cast<s *>(nullptr), static_cast<s *>(nullptr));
            buffer<s, memory_recorder<s>> b6(begin(s_arr), end(s_arr));
            assert(b1.size() == 0);
            assert(b2.size() == 10);
            assert(b3.size() == 0);
            assert(b4.size() == 7);
            assert(b5.size() == 0);
            assert(b6.size() == 12);
            assert(b1.empty());
            assert(not b2.empty());
            assert(b3.empty());
            assert(not b4.empty());
            assert(b5.empty());
            assert(not b6.empty());
            assert(not b1.allocator().release_check());
            assert(not b2.allocator().release_check());
            assert(not b3.allocator().release_check());
            assert(not b4.allocator().release_check());
            assert(not b5.allocator().release_check());
            assert(not b6.allocator().release_check());
            for(auto i {0}; i < 10; ++i) {
                assert(b2.begin()[i] == i + 1);
            }
            for(auto i {0}; i < 7; ++i) {
                assert(b4.begin()[i] == "hello" + to_string(i + 1));
            }
            for(auto i {0}; i < 12; ++i) {
                assert(b6.begin()[i].a == i % 2 == 0 ? 42 : 0);
            }
            b1.clear();
            b2.clear();
            b3.clear();
            b4.clear();
            b5.clear();
            b6.clear();
            assert(b1.allocator().release_check());
            assert(b2.allocator().release_check());
            assert(b3.allocator().release_check());
            assert(b4.allocator().release_check());
            assert(b5.allocator().release_check());
            assert(b6.allocator().release_check());
        }

        // copy and move
        {
            struct s {
                int a;
                s() = default;
                s(int a) noexcept(false) : a {a} {}
                s(const s &rhs) noexcept(false) : a {rhs.a} {}
                s(s &&rhs) noexcept(false) : a {rhs.a} {}
                s &operator=(const s &) = delete;
                s &operator=(s &&) = delete;
            };
            buffer<int, memory_recorder<int>> b1 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
            buffer<int, memory_recorder<int>> b2 {b1};
            buffer<int, memory_recorder<int>> b3 {ds::move(b1)};
            buffer<string, memory_recorder<string>> b4 {"hello1", "hello2", "hello3", "hello4", "hello5", "hello6", "hello7"};
            buffer<string, memory_recorder<string>> b5 {b4};
            buffer<string, memory_recorder<string>> b6 {ds::move(b4)};
            buffer<s, memory_recorder<s>> b7 {{42}, {}, {42}, {}, {42}, {}, {42}, {}, {42}, {}, {42}, {}};
            buffer<s, memory_recorder<s>> b8 {b7};
            buffer<s, memory_recorder<s>> b9 {ds::move(b7)};
            assert(b1.size() == 0);
            assert(b2.size() == 10);
            assert(b3.size() == 10);
            assert(b4.size() == 0);
            assert(b5.size() == 7);
            assert(b6.size() == 7);
            assert(b7.size() == 0);
            assert(b8.size() == 12);
            assert(b9.size() == 12);
            assert(b1.empty());
            assert(not b2.empty());
            assert(not b3.empty());
            assert(b4.empty());
            assert(not b5.empty());
            assert(not b6.empty());
            assert(b7.empty());
            assert(not b8.empty());
            assert(not b9.empty());
            assert(not b1.allocator().release_check());
            assert(not b2.allocator().release_check());
            assert(not b3.allocator().release_check());
            assert(not b4.allocator().release_check());
            assert(not b5.allocator().release_check());
            assert(not b6.allocator().release_check());
            assert(not b7.allocator().release_check());
            assert(not b8.allocator().release_check());
            assert(not b9.allocator().release_check());
            for(auto i {0}; i < 10; ++i) {
                assert(b2.begin()[i] == i + 1);
                assert(b3.begin()[i] == i + 1);
            }
            for(auto i {0}; i < 7; ++i) {
                assert(b5.begin()[i] == "hello" + to_string(i + 1));
                assert(b6.begin()[i] == "hello" + to_string(i + 1));
            }
            for(auto i {0}; i < 11; ++i) {
                assert(b8.begin()[i].a == i % 2 == 0 ? 42 : 0);
                assert(b9.begin()[i].a == i % 2 == 0 ? 42 : 0);
            }
            b1.clear();
            b2.clear();
            b3.clear();
            b4.clear();
            b5.clear();
            b6.clear();
            b7.clear();
            b8.clear();
            b9.clear();
            assert(b1.allocator().release_check());
            assert(b2.allocator().release_check());
            assert(b3.allocator().release_check());
            assert(b4.allocator().release_check());
            assert(b5.allocator().release_check());
            assert(b6.allocator().release_check());
            assert(b7.allocator().release_check());
            assert(b8.allocator().release_check());
            assert(b9.allocator().release_check());
        }

        // operator[]
        {
            buffer<int, memory_recorder<int>> b1 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
            buffer<string, memory_recorder<string>> b2 {"hello1", "hello2", "hello3", "hello4", "hello5"};
            for(auto i {0}; i < 10; ++i) {
                assert(b1[i] == i + 1);
            }
            for(auto i {0}; i < 5; ++i) {
                assert(b2[i] == "hello" + to_string(i + 1));
            }
            assert(not b1.allocator().release_check());
            assert(not b2.allocator().release_check());
            b1.clear();
            b2.clear();
            assert(b1.allocator().release_check());
            assert(b2.allocator().release_check());
        }

        // mbegin and mend
        {
            buffer<string, memory_recorder<string>> b {"hello1", "hello2", "hello3", "hello4", "hello5"};
            for(auto it {b.mbegin()}; it not_eq b.mend(); ++it) {
                auto tmp {*it};
            }
            for(auto i {0}; i < 5; ++i) {
                assert(b[i].empty());
            }
            assert(not b.allocator().release_check());
            b.clear();
            assert(b.allocator().release_check());
        }
    }
}
