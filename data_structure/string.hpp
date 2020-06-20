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

#ifndef DATA_STRUCTURE_STRING_HPP
#define DATA_STRUCTURE_STRING_HPP

#include "iterator.hpp"
#include "allocator.hpp"

namespace data_structure {
    template <typename RandomAccessIterator>
    typename iterator_traits<RandomAccessIterator>::size_type string_length(RandomAccessIterator str) {
        auto end {str};
        while(*end++ not_eq '\0');
        return static_cast<typename iterator_traits<RandomAccessIterator>::size_type>(end - str);
    }
    template <typename T>
    inline typename enable_if<is_char_type<T>::value, T>::type is_upper(T ch) noexcept {
        return ch >= 'A' and ch <= 'Z';
    }
    template <typename T>
    inline typename enable_if<is_char_type<T>::value, T>::type is_lower(T ch) noexcept {
        return ch >= 'a' and ch <= 'z';
    }
    template <typename T>
    inline T to_upper(T ch) noexcept {
        return ds::is_lower(ch) ? ch - 32 : ch;
    }
    template <typename T>
    inline T to_lower(T ch) noexcept {
        return ds::is_upper(ch) ? ch + 32 : ch;
    }
}

namespace data_structure::__data_structure_auxiliary {
    template <size_t Size = sizeof(wchar_t)>
    constexpr char16_t wchar_cast(wchar_t) noexcept;
    template <>
    constexpr char16_t wchar_cast<2>(wchar_t wch) noexcept {
        return static_cast<char16_t>(wch);
    }
    template <>
    constexpr char16_t wchar_cast<4>(wchar_t wch) noexcept {
        return static_cast<char16_t>(wch & 0xFFFF);
    }

    class char_t final {
    private:
        char16_t ch;
    public:
        constexpr char_t() noexcept : ch {} {}
        constexpr char_t(char16_t u16ch) noexcept : ch {u16ch} {}
        constexpr char_t(char ch) noexcept : ch {static_cast<char16_t>(ch)} {}
        constexpr char_t(unsigned char uch) noexcept : ch {static_cast<char16_t>(uch)} {}
        constexpr char_t(unsigned char uch_h, unsigned char uch_l) noexcept :
                ch {static_cast<char16_t>(static_cast<unsigned short>(uch_h) << 8 | uch_l)} {}
        constexpr char_t(short ch_s) noexcept : ch {static_cast<char16_t>(ch_s)} {}
        constexpr char_t(unsigned short ch_us) noexcept : ch {static_cast<char16_t>(ch_us)} {}
        constexpr char_t(int ch_i) noexcept : ch {static_cast<char16_t>(ch_i & 0xFFFF)} {}
        constexpr char_t(unsigned ch_ui) noexcept : ch {static_cast<char16_t>(ch_ui & 0xFFFF)} {}
        constexpr char_t(wchar_t wch) noexcept : ch {wchar_cast(wch)} {}
        constexpr char_t(char32_t u32ch) noexcept : ch {static_cast<char16_t>(u32ch & 0xFFFF)} {}
#ifdef _DATA_STRUCTURE_HAS_CHAR8_T
        constexpr char_t(char8_t u8ch) noexcept : ch {static_cast<char16_t>(u8ch)} {}
#endif
        constexpr char_t(const char_t &) noexcept = default;
        constexpr char_t(char_t &&) noexcept = default;
        ~char_t() noexcept = default;
    public:
        constexpr char_t &operator=(const char_t &) noexcept = default;
        constexpr char_t &operator=(char_t &&) noexcept = default;
        constexpr operator char16_t() const noexcept {
            return this->ch;
        }
    public:
        [[nodiscard]]
        constexpr bool empty() const noexcept {
            return this->ch;
        }
        [[nodiscard]]
        constexpr bool space() const noexcept {
            return this->ch == ' ' or (this->ch <= 0x0D and this->ch >= 0x09) or
                    (this->ch > 127 and (this->ch == 0x85 or this->ch == 0xa0));
        }
        [[nodiscard]]
        constexpr bool letter() const noexcept {
            return this->upper() or this->lower();
        }
        [[nodiscard]]
        constexpr bool number() const noexcept {
            return this->ch >= '0' and this->ch <= '9';
        }
        [[nodiscard]]
        constexpr bool lower() const noexcept {
            return this->ch >= 'a' and this->ch <= 'z';
        }
        [[nodiscard]]
        constexpr bool upper() const noexcept {
            return this->ch >= 'A' and this->ch <= 'Z';
        }
        [[nodiscard]]
        constexpr char16_t unicode() const noexcept {
            return this->ch;
        }
        [[nodiscard]]
        constexpr char16_t &unicode() noexcept {
            return this->ch;
        }
    };
}

#endif //DATA_STRUCTURE_STRING_HPP
