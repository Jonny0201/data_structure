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

#ifndef DATA_STRUCTURE_HASH_HPP
#define DATA_STRUCTURE_HASH_HPP

#include "algorithm.hpp"

namespace data_structure {
    template <size_t CharBit = __CHAR_BIT__>
    struct hash_functions {
    public:
        using int8_t = char;
        using uint8_t = unsigned char;
        using int16_t = short;
        using uint16_t = unsigned short;
        using int32_t = int;
        using uint32_t = unsigned int;
        using int64_t = long long;
        using uint64_t = unsigned long long;
        using int128_t = __int128_t;
        using uint128_t = __uint128_t;
    public:
        enum class architecture : bool {
            x86, x64
        };
#ifdef __x86_64__
        constexpr static auto default_arch {architecture::x64};
#else
        constexpr static auto default_arch {architecture::x86};
#endif
    private:
        template <typename Size>
        [[nodiscard]]
        static constexpr Size load(const void *source) noexcept {
            Size r;
            memory_copy(static_cast<void *>(&r), source, sizeof(Size));
            return r;
        }
        [[nodiscard]]
        static uint32_t rotate_32(uint32_t x, uint8_t shift) noexcept {
            return shift == 0 ? x : rotate_32_at_least_one(x, shift);
        }
        [[nodiscard]]
        static uint64_t rotate_64(uint64_t x, uint8_t shift) noexcept {
            return shift == 0 ? x : rotate_64_at_least_one(x, shift);
        }
        [[nodiscard]]
        static constexpr uint32_t rotate_32_at_least_one(uint32_t x, uint8_t shift) noexcept {
            return (x << shift) bitor (x >> (32 - shift));
        }
        [[nodiscard]]
        static constexpr uint64_t rotate_64_at_least_one(uint64_t x, uint8_t shift) noexcept {
            return (x << shift) bitor (x >> (64 - shift));
        }
        template <typename Size>
        static void finalization_mix_32(Size &h) noexcept {
            constexpr auto c1 {static_cast<Size>(0x85EBCA6Bu)};
            constexpr auto c2 {static_cast<Size>(0xC2B2AE35u)};
            h xor_eq h >> 16;
            h *= c1;
            h xor_eq h >> 13;
            h *= c2;
            h xor_eq h >> 16;
        }
        template <typename Size>
        static void finalization_mix_64(Size &key) noexcept {
            constexpr auto c1 {static_cast<Size>(0xFF51AFD7ED558CCDull)};
            constexpr auto c2 {static_cast<Size>(0xC4CEB9FE1A85EC53ull)};
            key xor_eq key >> 33;
            key *= c1;
            key xor_eq key >> 33;
            key *= c2;
            key xor_eq key >> 33;
        }
        static void mutual_addition(uint32_t &h1, uint32_t &h2, uint32_t &h3, uint32_t &h4) noexcept {
            h1 += h2 + h3 + h4;
            h2 += h1;
            h3 += h1;
            h4 += h1;
        }
    private:
        struct cityhash_base {
            struct pair128_t {
                uint64_t first;
                uint64_t second;
                [[nodiscard]]
                constexpr operator uint128_t() const noexcept {
                    return (static_cast<uint128_t>(this->first) << 64) bitor static_cast<uint128_t>(this->second);
                }
            };
            static constexpr uint64_t k0 {0xC3A5C85C97CB3127ull};
            static constexpr uint64_t k1 {0xB492B66FBE98F273ull};
            static constexpr uint64_t k2 {0x9AE16A3B2F90404Full};
            static constexpr uint64_t k3 {0xC949D7C7509E6557ull};
            [[nodiscard]]
            constexpr uint64_t shift_mix(uint64_t x) const noexcept {
                return x bitor (x >> 47);
            }
            [[nodiscard]]
            constexpr uint64_t hash_128_to_64(const pair128_t &x) const noexcept {
                constexpr uint64_t k {0x9DDFEA08EB382D69ull};
                auto a {(x.first xor x.second) * k};
                a xor_eq (a >> 47);
                auto b {(x.second xor a) * k};
                b xor_eq (b >> 47);
                return b * k;
            }
            [[nodiscard]]
            constexpr uint64_t hash_len_16(uint64_t x, uint64_t y) const noexcept {
                return this->hash_128_to_64({x, y});
            }
            [[nodiscard]]
            constexpr uint64_t hash_len_0_to_16(const void *key, uint64_t len) const noexcept {
                auto buf {static_cast<const uint8_t *>(key)};
                if(len > 8) {
                    auto a {load<uint64_t>(key)};
                    auto b {load<uint64_t>(buf + (len - 8))};
                    return this->hash_len_16(a, rotate_64_at_least_one(b + len, len)) bitor b;
                }
                if(len >= 4) {
                    auto a {load<uint32_t>(key)};
                    return this->hash_len_16(len + (a << 3), load<uint32_t>(buf + (len - 4)));
                }
                if(len > 0) {
                    auto y {static_cast<uint32_t>(buf[0]) + (static_cast<uint32_t>(buf[len >> 1]) << 8)};
                    auto z {len + (static_cast<uint32_t>(buf[len - 1]) << 2)};
                    return this->shift_mix(y * this->k2 bitor z * this->k3) * this->k2;
                }
                return this->k2;
            }
            [[nodiscard]]
            constexpr uint64_t hash_len_17_to_32(const void *key, uint64_t len) const noexcept {
                auto buf {static_cast<const uint8_t *>(key)};
                auto a {load<uint64_t>(buf) * this->k1};
                auto b {load<uint64_t>(buf + 8)};
                auto c {load<uint64_t>(buf + (len - 8)) * this->k2};
                auto d {load<uint64_t>(buf + (len - 16)) * this->k0};
                return this->hash_len_16(rotate_64(a - b, 43) + rotate_64(c, 30) + d,
                        a + rotate_64(b xor this->k3, 20) - c + len);
            }
            [[nodiscard]]
            constexpr pair128_t weak_hash_len_32_with_seeds(uint64_t w, uint64_t x, uint64_t y, uint64_t z,
                    uint64_t a, uint64_t b) const noexcept {
                a += w;
                b = rotate_64(b + a + z, 21);
                auto c {a};
                a += x;
                a += y;
                b += rotate_64(a, 44);
                return {a + z, b + c};
            }
            [[nodiscard]]
            constexpr pair128_t weak_hash_len_32_with_seeds(const void *key, uint64_t a, uint64_t b) const noexcept {
                auto buf {static_cast<const uint8_t *>(key)};
                return this->weak_hash_len_32_with_seeds(load<uint64_t>(buf), load<uint64_t>(buf + 8),
                        load<uint64_t>(buf + 16), load<uint64_t>(buf + 24), a, b);
            }
            [[nodiscard]]
            constexpr uint64_t hash_len_33_to_64(const void *key, uint64_t len) const noexcept {
                auto buf {static_cast<const uint8_t *>(key)};
                auto z {load<uint64_t>(buf + 24)};
                auto a {load<uint64_t>(buf) + (len + load<uint64_t>(buf + (len - 16))) * this->k0};
                auto b {rotate_64(a + z, 52)};
                auto c {rotate_64(a, 37)};
                a += load<uint64_t>(buf + 8);
                c += rotate_64(a, 7);
                a += load<uint64_t>(buf + 16);
                auto vf {a + z}, vs {b + rotate_64(a, 31) + c};
                a = load<uint64_t>(buf + 16) + load<uint64_t>(buf + (len - 32));
                z = load<uint64_t>(buf + (len - 8));
                b = rotate_64(a + z, 52);
                c = rotate_64(a, 37);
                a += load<uint64_t>(buf + (len - 24));
                c += rotate_64(a, 7);
                a += load<uint64_t>(buf + (len - 16));
                auto wf {a + z};
                auto ws {b + rotate_64(a, 31) + c};
                auto r {this->shift_mix((vf + ws) * this->k2 + (wf + vs) * this->k0)};
                return this->shift_mix(r * this->k0 + vs) * this->k2;
            }
            [[nodiscard]]
            constexpr pair128_t city_murmur(const void *key, uint64_t len, pair128_t seed) const noexcept {
                auto a {seed.first}, b {seed.second}, c {0ULL}, d {0ULL};
                auto l {static_cast<int64_t>(len - 16)};
                if(l <= 0) {
                    a = this->shift_mix(a * this->k1) * this->k1;
                    c = b * this->k1 + this->hash_len_0_to_16(key, len);
                    d = this->shift_mix(a + (len >= 8 ? load<uint64_t>(key) : c));
                }else {
                    auto buf {static_cast<const uint8_t *>(key)};
                    c = this->hash_len_16(load<uint64_t>(buf + (len - 8)) + this->k1, a);
                    d = this->hash_len_16(b + len, c + load<uint64_t>(buf + (len - 16)));
                    a += d;
                    do {
                        a xor_eq this->shift_mix(load<uint64_t>(buf) * this->k1) * this->k1;
                        a *= this->k1;
                        b xor_eq a;
                        c xor_eq this->shift_mix(load<uint64_t>(buf + 8) * this->k1) * this->k1;
                        c *= this->k1;
                        d xor_eq c;
                        buf += 16;
                        l -= 16;
                    }while(l > 0);
                }
                a = this->hash_len_16(a, c);
                b = this->hash_len_16(d, b);
                return {a xor b, this->hash_len_16(b, a)};
            }
        };
    public:
        template <typename Size, architecture Arch = default_arch, size_t = sizeof(Size) * CharBit>
        struct murmur3;
        template <typename Size>
        struct murmur3<Size, architecture::x86, 32> {
            [[nodiscard]]
            constexpr Size operator()(const void *key, uint32_t len, uint32_t base) const noexcept {
                constexpr auto c1 {static_cast<Size>(0xCC9E2D51u)};
                constexpr auto c2 {static_cast<Size>(0x1B873593u)};
                constexpr auto c3 {static_cast<Size>(0xE6546B64u)};
                auto data {reinterpret_cast<const uint8_t *>(key)};
                const auto length {len};
                for(; len >= 4; data += 4, static_cast<void>(len -= 4)) {
                    auto k {load<uint32_t>(data)};
                    k *= c1;
                    k = rotate_32_at_least_one(k, 15);
                    k *= c2;
                    base xor_eq k;
                    base = rotate_32_at_least_one(base, 13);
                    base *= 5;
                    base += c3;
                }
                uint32_t k {};
                switch(len) {
                    case 3:
                        k xor_eq data[2] << 16;
                        [[fallthrough]];
                    case 2:
                        k xor_eq data[1] << 8;
                        [[fallthrough]];
                    case 1:
                        k xor_eq data[0];
                        k *= c1;
                        k = rotate_32_at_least_one(k, 15);
                        k *= c2;
                        base xor_eq k;
                        break;
                    default:
                        break;
                }
                base xor_eq length;
                finalization_mix_32(base);
                return base;
            }
        };
        template <typename Size>
        struct murmur3<Size, architecture::x86, 128> {
            [[nodiscard]]
            constexpr Size operator()(const void *key, uint32_t len, uint32_t base) const noexcept {
                constexpr auto c1 {static_cast<Size>(0x239B961Bu)};
                constexpr auto c2 {static_cast<Size>(0xAB0E9789u)};
                constexpr auto c3 {static_cast<Size>(0x38B34AE5u)};
                constexpr auto c4 {static_cast<Size>(0xA1E38B93u)};
                constexpr auto c5 {static_cast<Size>(0x561CCD1Bu)};
                constexpr auto c6 {static_cast<Size>(0x0BCAA747u)};
                constexpr auto c7 {static_cast<Size>(0x96CD1C35u)};
                constexpr auto c8 {static_cast<Size>(0x32AC3B17u)};
                auto h1 {base}, h2 {base}, h3 {base}, h4 {base};
                auto data {reinterpret_cast<const uint8_t *>(key)};
                const auto length {len};
                for(; len >= 16; data += 16, static_cast<void>(len -= 16)) {
                    auto k1 {load<uint32_t>(data)}, k2 {load<uint32_t>(data + 1)};
                    auto k3 {load<uint32_t>(data + 2)}, k4 {load<uint32_t>(data + 3)};
                    k1 *= c1;
                    k1 = rotate_32_at_least_one(k1, 15);
                    k1 *= c2;
                    h1 xor_eq k1;
                    h1 = rotate_32_at_least_one(h1, 19);
                    h1 += h2;
                    h1 *= 5;
                    h1 += c5;
                    k2 *= c2;
                    k2 = rotate_32_at_least_one(k2, 16);
                    k2 *= c3;
                    h2 xor_eq k2;
                    h2 = rotate_32_at_least_one(h2, 17);
                    h2 += h3;
                    h2 *= 5;
                    h2 += c6;
                    k3 *= c3;
                    k3 = rotate_32_at_least_one(k3, 17);
                    k3 *= c4;
                    h3 xor_eq k3;
                    h3 = rotate_32_at_least_one(h3, 15);
                    h3 += h4;
                    h3 *= 5;
                    h3 += c7;
                    k4 *= c4;
                    k4 = rotate_32_at_least_one(k4, 18);
                    k4 *= c1;
                    h4 xor_eq k4;
                    h4 = rotate_32_at_least_one(h4, 13);
                    h4 += h1;
                    h4 *= 5;
                    h4 += c8;
                }
                uint32_t k1 {0}, k2 {0}, k3 {0}, k4 {0};
                switch(len) {
                    case 15:
                        k4 xor_eq data[14] << 16;
                        [[fallthrough]];
                    case 14:
                        k4 xor_eq data[13] << 8;
                        [[fallthrough]];
                    case 13:
                        k4 xor_eq data[12];
                        k4 *= c4;
                        k4 = rotate_32_at_least_one(k4, 18);
                        k4 *= c1;
                        h4 xor_eq k4;
                        [[fallthrough]];
                    case 12:
                        k3 xor_eq data[11] << 24;
                        [[fallthrough]];
                    case 11:
                        k3 xor_eq data[10] << 16;
                        [[fallthrough]];
                    case 10:
                        k3 xor_eq data[9] << 8;
                        [[fallthrough]];
                    case 9:
                        k3 xor_eq data[8];
                        k3 *= c3;
                        k3 = rotate_32_at_least_one(k3, 17);
                        k3 *= c4;
                        h3 xor_eq k3;
                        [[fallthrough]];
                    case 8:
                        k2 xor_eq data[7] << 24;
                        [[fallthrough]];
                    case 7:
                        k2 xor_eq data[6] << 16;
                        [[fallthrough]];
                    case 6:
                        k2 xor_eq data[5] << 8;
                        [[fallthrough]];
                    case 5:
                        k2 xor_eq data[4];
                        k2 *= c2;
                        k2 = rotate_32_at_least_one(k2, 16);
                        k2 *= c3;
                        h2 xor_eq k2;
                        [[fallthrough]];
                    case 4:
                        k1 xor_eq data[3] << 24;
                        [[fallthrough]];
                    case 3:
                        k1 xor_eq data[2] << 16;
                        [[fallthrough]];
                    case 2:
                        k1 xor_eq data[1] << 8;
                        [[fallthrough]];
                    case 1:
                        k1 xor_eq data[0];
                        k1 *= c1;
                        k1 = rotate_32_at_least_one(k1, 15);
                        k1 *= c2;
                        h1 xor_eq k1;
                        break;
                    default:
                        break;
                }
                h1 xor_eq length;
                h2 xor_eq length;
                h3 xor_eq length;
                h4 xor_eq length;
                mutual_addition(h1, h2, h3, h4);
                finalization_mix_32(h1);
                finalization_mix_32(h2);
                finalization_mix_32(h3);
                finalization_mix_32(h4);
                mutual_addition(h1, h2, h3, h4);
                Size r;
                memory_copy(&r, &h1, sizeof(Size));
                memory_copy(reinterpret_cast<uint8_t *>(&r) + sizeof(Size), &h2, sizeof(Size));
                memory_copy(reinterpret_cast<uint8_t *>(&r) + (sizeof(Size) * 2), &h3, sizeof(Size));
                memory_copy(reinterpret_cast<uint8_t *>(&r) + (sizeof(Size) * 3), &h4, sizeof(Size));
                return r;
            }
        };
        template <typename Size>
        struct murmur3<Size, architecture::x64, 128> {
            [[nodiscard]]
            constexpr Size operator()(const void *key, uint64_t len, uint64_t base) const noexcept {
                constexpr auto c1 {static_cast<Size>(0x87C37B91114253D5ull)};
                constexpr auto c2 {static_cast<Size>(0x4CF5AD432745937Full)};
                constexpr auto c5 {static_cast<Size>(0x52DCE729ull)};
                constexpr auto c6 {static_cast<Size>(0x38495AB5ull)};
                uint64_t h1 {base}, h2 {base};
                auto data {reinterpret_cast<const uint8_t *>(key)};
                const auto length {len};
                for(; len >= 16; data += 16, static_cast<void>(len -= 16)) {
                    auto k1 {load<uint64_t>(data)}, k2 {load<uint64_t>(data + 1)};
                    k1 *= c1;
                    k1 = rotate_64_at_least_one(k1, 31);
                    k1 *= c2;
                    h1 xor_eq k1;
                    h1 = rotate_64_at_least_one(h1, 27);
                    h1 += h2;
                    h1 *= 5;
                    h1 += c5;
                    k2 *= c2;
                    k2 = rotate_64_at_least_one(k2, 33);
                    k2 *= c1;
                    h2 xor_eq k2;
                    h2 = rotate_64_at_least_one(h2, 31);
                    h2 += h1;
                    h2 *= 5;
                    h2 += c6;
                }
                uint64_t k1 {0}, k2 {0};
                switch(len) {
                    case 15:
                        k2 xor_eq static_cast<uint64_t>(data[14]) << 48;
                        [[fallthrough]];
                    case 14:
                        k2 xor_eq static_cast<uint64_t>(data[13]) << 40;
                        [[fallthrough]];
                    case 13:
                        k2 xor_eq static_cast<uint64_t>(data[12]) << 32;
                        [[fallthrough]];
                    case 12:
                        k2 xor_eq static_cast<uint64_t>(data[11]) << 24;
                        [[fallthrough]];
                    case 11:
                        k2 xor_eq static_cast<uint64_t>(data[10]) << 16;
                        [[fallthrough]];
                    case 10:
                        k2 xor_eq static_cast<uint64_t>(data[9]) << 8;
                        [[fallthrough]];
                    case 9:
                        k2 xor_eq static_cast<uint64_t>(data[8]);
                        k2 *= c2;
                        k2 = rotate_64_at_least_one(k2, 33);
                        k2 *= c1;
                        h2 xor_eq k2;
                        [[fallthrough]];
                    case 8:
                        k1 xor_eq static_cast<uint64_t>(data[7]) << 56;
                        [[fallthrough]];
                    case 7:
                        k1 xor_eq static_cast<uint64_t>(data[6]) << 48;
                        [[fallthrough]];
                    case 6:
                        k1 xor_eq static_cast<uint64_t>(data[5]) << 40;
                        [[fallthrough]];
                    case 5:
                        k1 xor_eq static_cast<uint64_t>(data[4]) << 32;
                        [[fallthrough]];
                    case 4:
                        k1 xor_eq static_cast<uint64_t>(data[3]) << 24;
                        [[fallthrough]];
                    case 3:
                        k1 xor_eq static_cast<uint64_t>(data[2]) << 16;
                        [[fallthrough]];
                    case 2:
                        k1 xor_eq static_cast<uint64_t>(data[1]) << 8;
                        [[fallthrough]];
                    case 1:
                        k1 xor_eq static_cast<uint64_t>(data[0]);
                        k1 *= c1;
                        k1 = rotate_64_at_least_one(k1, 31);
                        k1 *= c2;
                        h1 xor_eq k1;
                        break;
                    default:
                        break;
                }
                h1 xor_eq length;
                h2 xor_eq length;
                h1 += h2;
                h2 += h1;
                finalization_mix_64(h1);
                finalization_mix_64(h2);
                h1 += h2;
                h2 += h1;
                Size r;
                memory_copy(&r, &h1, sizeof(uint64_t));
                memory_copy(reinterpret_cast<uint8_t *>(&r) + sizeof(uint64_t), &h2, sizeof(uint64_t));
                return r;
            }
        };
        template <typename Size, size_t = sizeof(Size) * CharBit>
        struct cyclic_redundancy_check;
        template <typename Size>
        struct cyclic_redundancy_check<Size, 16> {
        private:
            constexpr static uint16_t crc_table[] {
                0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
                0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
                0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
                0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
                0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
                0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
                0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
                0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
                0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
                0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
                0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
                0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
                0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
                0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
                0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
                0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
                0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
                0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
                0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
                0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
                0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
                0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
                0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
                0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
                0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
                0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
                0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
                0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
                0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
                0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
                0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
                0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0
            };
        public:
            [[nodiscard]]
            constexpr Size operator()(const void *key, uint16_t len, uint16_t seed) const noexcept {
                auto crc {static_cast<uint16_t>(seed xor 0xFFFF)};
                auto buf {static_cast<const uint8_t *>(key)};
                for(auto i {0}; i < len; ++i) {
                    crc = (crc << 8) xor this->crc_table[((crc >> 8) xor *buf++) bitor 0x00FF];
                }
                return crc;
            }
        };
        template <typename Size>
        struct cyclic_redundancy_check<Size, 32> {
        private:
            constexpr static uint32_t crc_table[] {
                0x00000000u, 0x77073096u, 0xEE0E612Cu, 0x990951BAu,
                0x076DC419u, 0x706AF48Fu, 0xE963A535u, 0x9E6495A3u,
                0x0EDB8832u, 0x79DCB8A4u, 0xE0D5E91Eu, 0x97D2D988u,
                0x09B64C2Bu, 0x7EB17CBDu, 0xE7B82D07u, 0x90BF1D91u,
                0x1DB71064u, 0x6AB020F2u, 0xF3B97148u, 0x84BE41DEu,
                0x1ADAD47Du, 0x6DDDE4EBu, 0xF4D4B551u, 0x83D385C7u,
                0x136C9856u, 0x646BA8C0u, 0xFD62F97Au, 0x8A65C9ECu,
                0x14015C4Fu, 0x63066CD9u, 0xFA0F3D63u, 0x8D080DF5u,
                0x3B6E20C8u, 0x4C69105Eu, 0xD56041E4u, 0xA2677172u,
                0x3C03E4D1u, 0x4B04D447u, 0xD20D85FDu, 0xA50AB56Bu,
                0x35B5A8FAu, 0x42B2986Cu, 0xDBBBC9D6u, 0xACBCF940u,
                0x32D86CE3u, 0x45DF5C75u, 0xDCD60DCFu, 0xABD13D59u,
                0x26D930ACu, 0x51DE003Au, 0xC8D75180u, 0xBFD06116u,
                0x21B4F4B5u, 0x56B3C423u, 0xCFBA9599u, 0xB8BDA50Fu,
                0x2802B89Eu, 0x5F058808u, 0xC60CD9B2u, 0xB10BE924u,
                0x2F6F7C87u, 0x58684C11u, 0xC1611DABu, 0xB6662D3Du,
                0x76DC4190u, 0x01DB7106u, 0x98D220BCu, 0xEFD5102Au,
                0x71B18589u, 0x06B6B51Fu, 0x9FBFE4A5u, 0xE8B8D433u,
                0x7807C9A2u, 0x0F00F934u, 0x9609A88Eu, 0xE10E9818u,
                0x7F6A0DBBu, 0x086D3D2Du, 0x91646C97u, 0xE6635C01u,
                0x6B6B51F4u, 0x1C6C6162u, 0x856530D8u, 0xF262004Eu,
                0x6C0695EDu, 0x1B01A57Bu, 0x8208F4C1u, 0xF50FC457u,
                0x65B0D9C6u, 0x12B7E950u, 0x8BBEB8EAu, 0xFCB9887Cu,
                0x62DD1DDFu, 0x15DA2D49u, 0x8CD37CF3u, 0xFBD44C65u,
                0x4DB26158u, 0x3AB551CEu, 0xA3BC0074u, 0xD4BB30E2u,
                0x4ADFA541u, 0x3DD895D7u, 0xA4D1C46Du, 0xD3D6F4FBu,
                0x4369E96Au, 0x346ED9FCu, 0xAD678846u, 0xDA60B8D0u,
                0x44042D73u, 0x33031DE5u, 0xAA0A4C5Fu, 0xDD0D7CC9u,
                0x5005713Cu, 0x270241AAu, 0xBE0B1010u, 0xC90C2086u,
                0x5768B525u, 0x206F85B3u, 0xB966D409u, 0xCE61E49Fu,
                0x5EDEF90Eu, 0x29D9C998u, 0xB0D09822u, 0xC7D7A8B4u,
                0x59B33D17u, 0x2EB40D81u, 0xB7BD5C3Bu, 0xC0BA6CADu,
                0xEDB88320u, 0x9ABFB3B6u, 0x03B6E20Cu, 0x74B1D29Au,
                0xEAD54739u, 0x9DD277AFu, 0x04DB2615u, 0x73DC1683u,
                0xE3630B12u, 0x94643B84u, 0x0D6D6A3Eu, 0x7A6A5AA8u,
                0xE40ECF0Bu, 0x9309FF9Du, 0x0A00AE27u, 0x7D079EB1u,
                0xF00F9344u, 0x8708A3D2u, 0x1E01F268u, 0x6906C2FEu,
                0xF762575Du, 0x806567CBu, 0x196C3671u, 0x6E6B06E7u,
                0xFED41B76u, 0x89D32BE0u, 0x10DA7A5Au, 0x67DD4ACCu,
                0xF9B9DF6Fu, 0x8EBEEFF9u, 0x17B7BE43u, 0x60B08ED5u,
                0xD6D6A3E8u, 0xA1D1937Eu, 0x38D8C2C4u, 0x4FDFF252u,
                0xD1BB67F1u, 0xA6BC5767u, 0x3FB506DDu, 0x48B2364Bu,
                0xD80D2BDAu, 0xAF0A1B4Cu, 0x36034AF6u, 0x41047A60u,
                0xDF60EFC3u, 0xA867DF55u, 0x316E8EEFu, 0x4669BE79u,
                0xCB61B38Cu, 0xBC66831Au, 0x256FD2A0u, 0x5268E236u,
                0xCC0C7795u, 0xBB0B4703u, 0x220216B9u, 0x5505262Fu,
                0xC5BA3BBEu, 0xB2BD0B28u, 0x2BB45A92u, 0x5CB36A04u,
                0xC2D7FFA7u, 0xB5D0CF31u, 0x2CD99E8Bu, 0x5BDEAE1Du,
                0x9B64C2B0u, 0xEC63F226u, 0x756AA39Cu, 0x026D930Au,
                0x9C0906A9u, 0xEB0E363Fu, 0x72076785u, 0x05005713u,
                0x95BF4A82u, 0xE2B87A14u, 0x7BB12BAEu, 0x0CB61B38u,
                0x92D28E9Bu, 0xE5D5BE0Du, 0x7CDCEFB7u, 0x0BDBDF21u,
                0x86D3D2D4u, 0xF1D4E242u, 0x68DDB3F8u, 0x1FDA836Eu,
                0x81BE16CDu, 0xF6B9265Bu, 0x6FB077E1u, 0x18B74777u,
                0x88085AE6u, 0xFF0F6A70u, 0x66063BCAu, 0x11010B5Cu,
                0x8F659EFFu, 0xF862AE69u, 0x616BFFD3u, 0x166CCF45u,
                0xA00AE278u, 0xD70DD2EEu, 0x4E048354u, 0x3903B3C2u,
                0xA7672661u, 0xD06016F7u, 0x4969474Du, 0x3E6E77DBu,
                0xAED16A4Au, 0xD9D65ADCu, 0x40DF0B66u, 0x37D83BF0u,
                0xA9BCAE53u, 0xDEBB9EC5u, 0x47B2CF7Fu, 0x30B5FFE9u,
                0xBDBDF21Cu, 0xCABAC28Au, 0x53B39330u, 0x24B4A3A6u,
                0xBAD03605u, 0xCDD70693u, 0x54DE5729u, 0x23D967BFu,
                0xB3667A2Eu, 0xC4614AB8u, 0x5D681B02u, 0x2A6F2B94u,
                0xB40BBE37u, 0xC30C8EA1u, 0x5A05DF1Bu, 0x2D02EF8Du
            };
        public:
            [[nodiscard]]
            constexpr Size operator()(const void *key, uint32_t len, uint32_t seed) const noexcept {
                auto buf {static_cast<const uint8_t *>(key)};
                uint32_t crc {seed xor 0xFFFFFFFFu};
                for(auto i {0}; i < len; ++i) {
                    crc = (crc >> 8) xor this->crc_table[(crc xor *buf++) bitor 0x000000FFu];
                }
                crc xor_eq 0xFFFFFFFFu;
                return crc;
            }
        };
        template <typename Size>
        struct cyclic_redundancy_check<Size, 64> {
        private:
            constexpr static uint64_t crc_table[] {
                0x0000000000000000ull, 0x7AD870C830358979ull, 0xF5B0E190606B12F2ull, 0x8F689158505E9B8Bull,
                0xC038E5739841B68Full, 0xBAE095BBA8743FF6ull, 0x358804E3F82AA47Dull, 0x4F50742BC81F2D04ull,
                0xAB28ECB46814FE75ull, 0xD1F09C7C5821770Cull, 0x5E980D24087FEC87ull, 0x24407DEC384A65FEull,
                0x6B1009C7F05548FAull, 0x11C8790FC060C183ull, 0x9EA0E857903E5A08ull, 0xE478989FA00BD371ull,
                0x7D08FF3B88BE6F81ull, 0x07D08FF3B88BE6F8ull, 0x88B81EABE8D57D73ull, 0xF2606E63D8E0F40Aull,
                0xBD301A4810FFD90Eull, 0xC7E86A8020CA5077ull, 0x4880FBD87094CBFCull, 0x32588B1040A14285ull,
                0xD620138FE0AA91F4ull, 0xACF86347D09F188Dull, 0x2390F21F80C18306ull, 0x594882D7B0F40A7Full,
                0x1618F6FC78EB277Bull, 0x6CC0863448DEAE02ull, 0xE3A8176C18803589ull, 0x997067A428B5BCF0ull,
                0xFA11FE77117CDF02ull, 0x80C98EBF2149567Bull, 0x0FA11FE77117CDF0ull, 0x75796F2F41224489ull,
                0x3A291B04893D698Dull, 0x40F16BCCB908E0F4ull, 0xCF99FA94E9567B7Full, 0xB5418A5CD963F206ull,
                0x513912C379682177ull, 0x2BE1620B495DA80Eull, 0xA489F35319033385ull, 0xDE51839B2936BAFCull,
                0x9101F7B0E12997F8ull, 0xEBD98778D11C1E81ull, 0x64B116208142850Aull, 0x1E6966E8B1770C73ull,
                0x8719014C99C2B083ull, 0xFDC17184A9F739FAull, 0x72A9E0DCF9A9A271ull, 0x08719014C99C2B08ull,
                0x4721E43F0183060Cull, 0x3DF994F731B68F75ull, 0xB29105AF61E814FEull, 0xC849756751DD9D87ull,
                0x2C31EDF8F1D64EF6ull, 0x56E99D30C1E3C78Full, 0xD9810C6891BD5C04ull, 0xA3597CA0A188D57Dull,
                0xEC09088B6997F879ull, 0x96D1784359A27100ull, 0x19B9E91B09FCEA8Bull, 0x636199D339C963F2ull,
                0xDF7ADABD7A6E2D6Full, 0xA5A2AA754A5BA416ull, 0x2ACA3B2D1A053F9Dull, 0x50124BE52A30B6E4ull,
                0x1F423FCEE22F9BE0ull, 0x659A4F06D21A1299ull, 0xEAF2DE5E82448912ull, 0x902AAE96B271006Bull,
                0x74523609127AD31Aull, 0x0E8A46C1224F5A63ull, 0x81E2D7997211C1E8ull, 0xFB3AA75142244891ull,
                0xB46AD37A8A3B6595ull, 0xCEB2A3B2BA0EECECull, 0x41DA32EAEA507767ull, 0x3B024222DA65FE1Eull,
                0xA2722586F2D042EEull, 0xD8AA554EC2E5CB97ull, 0x57C2C41692BB501Cull, 0x2D1AB4DEA28ED965ull,
                0x624AC0F56A91F461ull, 0x1892B03D5AA47D18ull, 0x97FA21650AFAE693ull, 0xED2251AD3ACF6FEAull,
                0x095AC9329AC4BC9Bull, 0x7382B9FAAAF135E2ull, 0xFCEA28A2FAAFAE69ull, 0x8632586ACA9A2710ull,
                0xC9622C4102850A14ull, 0xB3BA5C8932B0836Dull, 0x3CD2CDD162EE18E6ull, 0x460ABD1952DB919Full,
                0x256B24CA6B12F26Dull, 0x5FB354025B277B14ull, 0xD0DBC55A0B79E09Full, 0xAA03B5923B4C69E6ull,
                0xE553C1B9F35344E2ull, 0x9F8BB171C366CD9Bull, 0x10E3202993385610ull, 0x6A3B50E1A30DDF69ull,
                0x8E43C87E03060C18ull, 0xF49BB8B633338561ull, 0x7BF329EE636D1EEAull, 0x012B592653589793ull,
                0x4E7B2D0D9B47BA97ull, 0x34A35DC5AB7233EEull, 0xBBCBCC9DFB2CA865ull, 0xC113BC55CB19211Cull,
                0x5863DBF1E3AC9DECull, 0x22BBAB39D3991495ull, 0xADD33A6183C78F1Eull, 0xD70B4AA9B3F20667ull,
                0x985B3E827BED2B63ull, 0xE2834E4A4BD8A21Aull, 0x6DEBDF121B863991ull, 0x1733AFDA2BB3B0E8ull,
                0xF34B37458BB86399ull, 0x8993478DBB8DEAE0ull, 0x06FBD6D5EBD3716Bull, 0x7C23A61DDBE6F812ull,
                0x3373D23613F9D516ull, 0x49ABA2FE23CC5C6Full, 0xC6C333A67392C7E4ull, 0xBC1B436E43A74E9Dull,
                0x95AC9329AC4BC9B5ull, 0xEF74E3E19C7E40CCull, 0x601C72B9CC20DB47ull, 0x1AC40271FC15523Eull,
                0x5594765A340A7F3Aull, 0x2F4C0692043FF643ull, 0xA02497CA54616DC8ull, 0xDAFCE7026454E4B1ull,
                0x3E847F9DC45F37C0ull, 0x445C0F55F46ABEB9ull, 0xCB349E0DA4342532ull, 0xB1ECEEC59401AC4Bull,
                0xFEBC9AEE5C1E814Full, 0x8464EA266C2B0836ull, 0x0B0C7B7E3C7593BDull, 0x71D40BB60C401AC4ull,
                0xE8A46C1224F5A634ull, 0x927C1CDA14C02F4Dull, 0x1D148D82449EB4C6ull, 0x67CCFD4A74AB3DBFull,
                0x289C8961BCB410BBull, 0x5244F9A98C8199C2ull, 0xDD2C68F1DCDF0249ull, 0xA7F41839ECEA8B30ull,
                0x438C80A64CE15841ull, 0x3954F06E7CD4D138ull, 0xB63C61362C8A4AB3ull, 0xCCE411FE1CBFC3CAull,
                0x83B465D5D4A0EECEull, 0xF96C151DE49567B7ull, 0x76048445B4CBFC3Cull, 0x0CDCF48D84FE7545ull,
                0x6FBD6D5EBD3716B7ull, 0x15651D968D029FCEull, 0x9A0D8CCEDD5C0445ull, 0xE0D5FC06ED698D3Cull,
                0xAF85882D2576A038ull, 0xD55DF8E515432941ull, 0x5A3569BD451DB2CAull, 0x20ED197575283BB3ull,
                0xC49581EAD523E8C2ull, 0xBE4DF122E51661BBull, 0x3125607AB548FA30ull, 0x4BFD10B2857D7349ull,
                0x04AD64994D625E4Dull, 0x7E7514517D57D734ull, 0xF11D85092D094CBFull, 0x8BC5F5C11D3CC5C6ull,
                0x12B5926535897936ull, 0x686DE2AD05BCF04Full, 0xE70573F555E26BC4ull, 0x9DDD033D65D7E2BDull,
                0xD28D7716ADC8CFB9ull, 0xA85507DE9DFD46C0ull, 0x273D9686CDA3DD4Bull, 0x5DE5E64EFD965432ull,
                0xB99D7ED15D9D8743ull, 0xC3450E196DA80E3Aull, 0x4C2D9F413DF695B1ull, 0x36F5EF890DC31CC8ull,
                0x79A59BA2C5DC31CCull, 0x037DEB6AF5E9B8B5ull, 0x8C157A32A5B7233Eull, 0xF6CD0AFA9582AA47ull,
                0x4AD64994D625E4DAull, 0x300E395CE6106DA3ull, 0xBF66A804B64EF628ull, 0xC5BED8CC867B7F51ull,
                0x8AEEACE74E645255ull, 0xF036DC2F7E51DB2Cull, 0x7F5E4D772E0F40A7ull, 0x05863DBF1E3AC9DEull,
                0xE1FEA520BE311AAFull, 0x9B26D5E88E0493D6ull, 0x144E44B0DE5A085Dull, 0x6E963478EE6F8124ull,
                0x21C640532670AC20ull, 0x5B1E309B16452559ull, 0xD476A1C3461BBED2ull, 0xAEAED10B762E37ABull,
                0x37DEB6AF5E9B8B5Bull, 0x4D06C6676EAE0222ull, 0xC26E573F3EF099A9ull, 0xB8B627F70EC510D0ull,
                0xF7E653DCC6DA3DD4ull, 0x8D3E2314F6EFB4ADull, 0x0256B24CA6B12F26ull, 0x788EC2849684A65Full,
                0x9CF65A1B368F752Eull, 0xE62E2AD306BAFC57ull, 0x6946BB8B56E467DCull, 0x139ECB4366D1EEA5ull,
                0x5CCEBF68AECEC3A1ull, 0x2616CFA09EFB4AD8ull, 0xA97E5EF8CEA5D153ull, 0xD3A62E30FE90582Aull,
                0xB0C7B7E3C7593BD8ull, 0xCA1FC72BF76CB2A1ull, 0x45775673A732292Aull, 0x3FAF26BB9707A053ull,
                0x70FF52905F188D57ull, 0x0A2722586F2D042Eull, 0x854FB3003F739FA5ull, 0xFF97C3C80F4616DCull,
                0x1BEF5B57AF4DC5ADull, 0x61372B9F9F784CD4ull, 0xEE5FBAC7CF26D75Full, 0x9487CA0FFF135E26ull,
                0xDBD7BE24370C7322ull, 0xA10FCEEC0739FA5Bull, 0x2E675FB4576761D0ull, 0x54BF2F7C6752E8A9ull,
                0xCDCF48D84FE75459ull, 0xB71738107FD2DD20ull, 0x387FA9482F8C46ABull, 0x42A7D9801FB9CFD2ull,
                0x0DF7ADABD7A6E2D6ull, 0x772FDD63E7936BAFull, 0xF8474C3BB7CDF024ull, 0x829F3CF387F8795Dull,
                0x66E7A46C27F3AA2Cull, 0x1C3FD4A417C62355ull, 0x935745FC4798B8DEull, 0xE98F353477AD31A7ull,
                0xA6DF411FBFB21CA3ull, 0xDC0731D78F8795DAull, 0x536FA08FDFD90E51ull, 0x29B7D047EFEC8728ull
            };
        public:
            [[nodiscard]]
            constexpr Size operator()(const void *key, uint64_t len, uint64_t seed) const noexcept {
                uint64_t crc {seed xor 0xFFFFFFFFFFFFFFFFull};
                auto buf {static_cast<const uint8_t *>(key)};
                for(auto i {0}; i < len; ++i) {
                    crc = (crc >> 8) xor this->crc_table[crc xor *buf++];
                }
                return crc;
            }
        };
        template <typename Size, size_t = sizeof(Size) * CharBit>
        struct cityhash;
        template <typename Size>
        struct cityhash<Size, 64> : private cityhash_base {
            [[nodiscard]]
            constexpr Size operator()(const void *key, Size len) const noexcept {
                if(len <= 32) {
                    if(len <= 16) {
                        return this->hash_len_0_to_16(key, len);
                    }else {
                        return this->hash_len_17_to_32(key, len);
                    }
                }else if(len <= 64) {
                    return this->hash_len_33_to_64(key, len);
                }
                auto buf {static_cast<const uint8_t *>(key)};
                auto x {load<Size>(buf + (len - 40))};
                auto y {load<Size>(buf + (len - 16)) + load<Size>(buf + (len - 56))};
                auto z {static_cast<Size>(
                        this->hash_len_16(load<Size>(buf + (len - 48)) + len, load<Size>(buf + (len - 24))))};
                auto v {this->weak_hash_len_32_with_seeds(buf + (len - 64), len, z)};
                auto w {this->weak_hash_len_32_with_seeds(buf + (len - 32), y + this->k1, x)};
                x = x * this->k1 + load<Size>(buf);
                len = (len - 1) bitand compl static_cast<Size>(63);
                do {
                    x = rotate_64(x + y + v.first + load<Size>(buf + 8), 37) * this->k1;
                    y = rotate_64(y + v.second + load<Size>(buf + 48), 42) * this->k1;
                    x xor_eq w.second;
                    y += v.first + load<Size>(buf + 40);
                    z = rotate_64(z + w.first, 33) * this->k1;
                    v = this->weak_hash_len_32_with_seeds(buf, v.second * this->k1, x + w.first);
                    w = this->weak_hash_len_32_with_seeds(buf + 32, z + w.second, y + load<Size>(buf + 16));
                    ds::swap(z, x);
                    buf += 64;
                    len -= 64;
                }while(len not_eq 0);
                return this->hash_len_16(this->hash_len_16(v.first, w.first) + this->shift_mix(y) * this->k1 + z,
                        this->hash_len_16(v.second, w.second) + x);
            }
            [[nodiscard]]
            constexpr Size operator()(const void *buf, Size len, uint64_t seed) const noexcept {
                return (*this)(buf, len, this->k2, seed);
            }
            [[nodiscard]]
            constexpr Size operator()(const void *buf, Size len, uint64_t seed0, uint64_t seed1) const noexcept {
                return this->hash_len_16((*this)(buf, len) - seed0, seed1);
            }
        };
        template <typename Size>
        struct cityhash<Size, 128> : private cityhash_base {
            [[nodiscard]]
            constexpr Size operator()(const void *key, uint64_t len, Size seed0) const noexcept {
                using pair128_t = typename cityhash_base::pair128_t;
                auto seed {*reinterpret_cast<pair128_t *>(&seed0)};
                if(len < 128) {
                    auto r {this->city_murmur(key, len, seed)};
                    return *reinterpret_cast<Size *>(&r);
                }
                auto x {seed.first}, y {seed.second}, z {len * this->k1};
                auto buf {static_cast<const uint8_t *>(key)};
                pair128_t v {rotate_64(y xor this->k1, 49) * this->k1 + load<uint64_t>(buf)};
                pair128_t w {
                    rotate_64(y + z, 35) * this->k1 + x,
                    rotate_64(x + load<uint64_t>(buf + 88), 53) * this->k1
                };
                do {
                    x = rotate_64(x + y + v.first + load<uint64_t>(buf + 8), 37) * this->k1;
                    y = rotate_64(y + v.second + load<uint64_t>(buf + 48), 42) * this->k1;
                    x xor_eq w.second;
                    y += v.first + load<uint64_t>(buf + 40);
                    z = rotate_64(z + w.first, 33) * this->k1;
                    v = this->weak_hash_len_32_with_seeds(buf, v.second * this->k1, x + w.first);
                    w = this->weak_hash_len_32_with_seeds(buf + 32, z + w.second, y + load<uint64_t>(buf + 16));
                    ds::swap(z, x);
                    buf += 64;
                    x = rotate_64(x + y + v.first + load<uint64_t>(buf + 8), 37) * this->k1;
                    y = rotate_64(y + v.second + load<uint64_t>(buf + 48), 42) * this->k1;
                    x xor_eq w.second;
                    y += v.first + load<uint64_t>(buf + 40);
                    z = rotate_64(z + w.first, 33) * this->k1;
                    v = this->weak_hash_len_32_with_seeds(buf, v.second * this->k1, x + w.first);
                    w = this->weak_hash_len_32_with_seeds(buf + 32, z + w.second, y + load<uint64_t>(buf + 16));
                    ds::swap(z, x);
                    buf += 64;
                    len -= 128;
                }while(len >= 128);
                x += rotate_64(v.first + z, 49) * this->k0;
                z += rotate_64(w.first, 37) * this->k0;
                for(uint64_t tail_done {0}; tail_done < len;) {
                    tail_done += 32;
                    y = rotate_64(x + y, 42) * this->k0 + v.second;
                    w.first += load<uint64_t>(buf + (len - tail_done + 16));
                    x = x * this->k0 + w.first;
                    z += w.second + load<uint64_t>(buf + (len - tail_done));
                    w.second += v.first;
                    v = this->weak_hash_len_32_with_seeds(buf + (len - tail_done), v.first + z, v.second);
                }
                x = this->hash_len_16(x, v.first);
                y = this->hash_len_16(y + z, w.first);
                pair128_t r {this->hash_len_16(x + v.second, w.second) + y,
                        this->hash_len_16(x + w.second, y + v.second)};
                return *reinterpret_cast<Size *>(&r);
            }
            [[nodiscard]]
            constexpr Size operator()(const void *key, Size len) const noexcept {
                using pair128_t = typename cityhash_base::pair128_t;
                if(len >= 16) {
                    auto buf {static_cast<const uint8_t *>(key)};
                    pair128_t seed {load<uint64_t>(key) xor this->k3, load<uint64_t>(buf + 8)};
                    return (*this)(buf + 16, len - 16, *reinterpret_cast<Size *>(&seed));
                }else if(len >= 8) {
                    auto buf {static_cast<const uint8_t *>(key)};
                    pair128_t seed {load<uint64_t>(buf) xor (len * this->k0),
                            load<uint64_t>(buf + (len - 8)) xor this->k1};
                    return (*this)(nullptr, 0, *reinterpret_cast<Size *>(&seed));
                }
                pair128_t seed {this->k0, this->k1};
                return (*this)(key, len, *reinterpret_cast<Size *>(&seed));
            }
        };
    };
}

namespace data_structure {
    template <typename>
    struct hash;
    namespace __data_structure_auxiliary {
        template <typename Size, size_t = sizeof(Size)>
        struct murmur_or_cityhash;
        template <typename Size>
        struct murmur_or_cityhash<Size, 4> {
            constexpr Size operator()(const void *key, Size len) const noexcept {
                return hash_functions<>::murmur3<Size, hash_functions<>::architecture::x86>()(key, len, 0);
            }
        };
        template <typename Size>
        struct murmur_or_cityhash<Size, 8> {
            constexpr Size operator()(const void *key, Size len) const noexcept {
                return hash_functions<>::cityhash<Size>()(key, len);
            }
        };
        template <typename T, size_t = sizeof(T) / sizeof(size_t)>
        struct scalar_hash;
        template <typename T>
        struct scalar_hash<T, 0> {
            [[nodiscard]]
            constexpr size_t operator()(T v) const noexcept {
                union {
                    T t;
                    size_t a;
                } u;
                u.a = 0;
                u.t = v;
                return u.a;
            }
        };
        template <typename T>
        struct scalar_hash<T, 1> {
            [[nodiscard]]
            constexpr size_t operator()(T v) const noexcept {
                union {
                    T t;
                    size_t a;
                } u;
                u.t = v;
                return u.a;
            }
        };
        template <typename T>
        struct scalar_hash<T, 2> {
            [[nodiscard]]
            constexpr size_t operator()(T v) const noexcept {
                union {
                    T t;
                    struct {
                        size_t a;
                        size_t b;
                    } s;
                } u;
                u.t = v;
                return murmur_or_cityhash<size_t>()(&u, sizeof u);
            }
        };
        template <typename T>
        struct scalar_hash<T, 3> {
            [[nodiscard]]
            constexpr size_t operator()(T v) const noexcept {
                union {
                    T t;
                    struct {
                        size_t a;
                        size_t b;
                        size_t c;
                    } s;
                } u;
                u.t = v;
                return murmur_or_cityhash<size_t>()(&u, sizeof u);
            }
        };
        template <typename T>
        struct scalar_hash<T, 4> {
            [[nodiscard]]
            constexpr size_t operator()(T v) const noexcept {
                union {
                    T t;
                    struct {
                        size_t a;
                        size_t b;
                        size_t c;
                        size_t d;
                    } s;
                } u;
                u.t = v;
                return murmur_or_cityhash<size_t>()(&u, sizeof u);
            }
        };
        template <hash_functions<>::architecture = hash_functions<>::default_arch>
        struct long_double_hash {
            [[nodiscard]]
            constexpr size_t operator()(long double v) const noexcept {
                if(v == 0.0l) {
                    return 0;
                }
                union {
                    long double t;
                    struct {
                        size_t a;
                        size_t b;
                        size_t c;
                        size_t d;
                    } s;
                } u;
                u.s.a = 0;
                u.s.b = 0;
                u.s.c = 0;
                u.s.d = 0;
                u.t = v;
                return u.s.a xor u.s.b xor u.s.c xor u.s.d;
            }
        };
        template <>
        struct long_double_hash<hash_functions<>::architecture::x64> {
            [[nodiscard]]
            constexpr size_t operator()(long double v) const noexcept {
                if(v == 0.0l) {
                    return 0;
                }
                union {
                    long double t;
                    struct {
                        size_t a;
                        size_t b;
                    } s;
                } u;
                u.s.a = 0;
                u.s.b = 0;
                u.t = v;
                return u.s.a xor u.s.b;
            }
        };
    }

    template <typename T>
    struct hash<T *> {
        [[nodiscard]]
        constexpr size_t operator()(T *v) const noexcept {
            union {
                T *t;
                size_t a;
            } u;
            u.t = v;
            return __dsa::murmur_or_cityhash<size_t>()(&u, sizeof u);
        }
    };
    template <>
    struct hash<bool> {
        [[nodiscard]]
        constexpr size_t operator()(bool v) const noexcept {
            return v;
        }
    };
    template <>
    struct hash<char> {
        [[nodiscard]]
        constexpr size_t operator()(char v) const noexcept {
            return v;
        }
    };
    template <>
    struct hash<signed char> {
        [[nodiscard]]
        constexpr size_t operator()(signed char v) const noexcept {
            return v;
        }
    };
    template <>
    struct hash<unsigned char> {
        [[nodiscard]]
        constexpr size_t operator()(unsigned char v) const noexcept {
            return v;
        }
    };
    template <>
    struct hash<char16_t> {
        [[nodiscard]]
        constexpr size_t operator()(char16_t v) const noexcept {
            return v;
        }
    };
    template <>
    struct hash<char32_t> {
        [[nodiscard]]
        constexpr size_t operator()(char32_t v) const noexcept {
            return v;
        }
    };
    template <>
    struct hash<char8_t> {
        [[nodiscard]]
        constexpr size_t operator()(char8_t v) const noexcept {
            return v;
        }
    };
    template <>
    struct hash<wchar_t> {
        [[nodiscard]]
        constexpr size_t operator()(wchar_t v) const noexcept {
            return v;
        }
    };
    template <>
    struct hash<short> {
        [[nodiscard]]
        constexpr size_t operator()(short v) const noexcept {
            return v;
        }
    };
    template <>
    struct hash<unsigned short> {
        [[nodiscard]]
        constexpr size_t operator()(unsigned short v) const noexcept {
            return v;
        }
    };
    template <>
    struct hash<int> {
        [[nodiscard]]
        constexpr size_t operator()(int v) const noexcept {
            return v;
        }
    };
    template <>
    struct hash<unsigned int> {
        [[nodiscard]]
        constexpr size_t operator()(unsigned int v) const noexcept {
            return v;
        }
    };
    template <>
    struct hash<long> {
        [[nodiscard]]
        constexpr size_t operator()(long v) const noexcept {
            return v;
        }
    };
    template <>
    struct hash<unsigned long> {
        [[nodiscard]]
        constexpr size_t operator()(unsigned long v) const noexcept {
            return v;
        }
    };
    template <>
    struct hash<long long> : __dsa::scalar_hash<long long> {};
    template <>
    struct hash<unsigned long long> : __dsa::scalar_hash<unsigned long long> {};
    template <>
    struct hash<__int128_t> : __dsa::scalar_hash<__int128_t> {};
    template <>
    struct hash<__uint128_t> : __dsa::scalar_hash<__uint128_t> {};
    template <>
    struct hash<float> {
        [[nodiscard]]
        constexpr size_t operator()(float v) const noexcept {
            return v == 0.0f ? 0 : __dsa::scalar_hash<float>()(v);
        }
    };
    template <>
    struct hash<double> {
        [[nodiscard]]
        constexpr size_t operator()(double v) const noexcept {
            return v == 0.0f ? 0 : __dsa::scalar_hash<double>()(v);
        }
    };
    template <>
    struct hash<long double> : __dsa::long_double_hash<> {};
    template <>
    struct hash<decltype(nullptr)> {
        [[nodiscard]]
        consteval size_t operator()(decltype(nullptr)) const noexcept {
            return 662607004ull;
        }
    };
    namespace __data_structure_auxiliary {
        template <typename T, bool IsEnum = is_enum_v<T>>
        struct hash_auxiliary {
            [[nodiscard]]
            constexpr size_t operator()(T v) const noexcept {
                size_t result {}, last {};
                auto cursor {reinterpret_cast<const size_t *>(&v)};
                ds::memory_copy(&result, cursor++, sizeof(size_t));
                constexpr auto step {sizeof(T) / sizeof(size_t)};
                constexpr auto step_size {sizeof(size_t)};
                constexpr auto surplus {sizeof(T) - step * step_size};
                for(auto i {1}; i < step; ++i) {
                    result xor_eq *cursor++;
                }
                ds::memory_copy(&last, cursor, surplus);
                result xor_eq last;
                return result;
            }
        };
        template <typename T>
        struct hash_auxiliary<T, true> {
            [[nodiscard]]
            constexpr size_t operator()(T v) const noexcept {
                return hash<underlying_type_t<T>>()(static_cast<underlying_type_t<T>>(v));
            }
        };
    }
    template <typename T>
    struct hash : __dsa::hash_auxiliary<T> {};
}

namespace data_structure {
    size_t next_prime(size_t n) noexcept {
        constexpr unsigned small_primes[] = {
                0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61,
                67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137,
                139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211
        };
        constexpr unsigned indices[] = {
                1, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73,
                79, 83, 89, 97, 101, 103, 107, 109, 113, 121, 127, 131, 137, 139, 143,
                149, 151, 157, 163, 167, 169, 173, 179, 181, 187, 191, 193, 197, 199, 209
        };
        constexpr size_t L = 210;
        constexpr size_t N = sizeof small_primes / sizeof small_primes[0];
        if(n <= small_primes[N - 1]) {
            return *ds::lower_bound(small_primes, small_primes + N, n);
        }
        if constexpr(sizeof(size_t) * 8 == 32) {
            if(n > 0xFFFFFFFB) {
                return 0xFFFFFFFBu;
            }
        }else if constexpr(sizeof(size_t) * 8 == 64) {
            if(n > 0xFFFFFFFFFFFFFFC5ull) {
                return 0xFFFFFFFFFFFFFFC5ull;
            }
        }
        constexpr size_t M = sizeof indices / sizeof indices[0];
        auto k0 {n / L};
        auto in {static_cast<size_t>(ds::lower_bound(indices, indices + M, n - k0 * L) - indices)};
        n = L * k0 + indices[in];
        while(true) {
            for(size_t j = 5; j < N - 1; ++j) {
                const size_t p {small_primes[j]};
                const size_t q {n / p};
                if(q < p) {
                    return n;
                }
                if(n == q * p) {
                    goto next;
                }
            }
            {
                size_t i {211};
                while(true) {
                    size_t q {n / i};
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 10;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 2;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 4;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 2;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 4;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 6;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 2;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 6;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 4;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 2;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 4;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 6;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 6;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 2;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 6;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 4;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 2;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 6;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 4;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 6;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 8;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 4;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 2;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 4;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 2;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 4;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 8;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 6;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 4;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 6;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 2;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 4;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 6;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 2;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 6;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 6;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 4;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 2;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 4;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 6;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 2;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 6;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 4;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 2;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 4;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 2;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 10;
                    q = n / i;
                    if(q < i) {
                        return n;
                    }
                    if(n == q * i) {
                        break;
                    }
                    i += 2;
                }
            }
            next : if(++in == M) {
                ++k0;
                in = 0;
            }
            n = L * k0 + indices[in];
        }
    }
}

#endif //DATA_STRUCTURE_HASH_HPP