#pragma once

#include <array>
#include <cstdint>
#include <cstring>
#include <string>
#include <string_view>
#include <vector>

class MD5 {
private:
  static constexpr std::array<uint32_t, 64> K = {
      0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a,
      0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
      0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340,
      0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
      0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8,
      0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
      0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa,
      0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
      0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92,
      0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
      0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

  static constexpr std::array<uint32_t, 64> S = {
      7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
      5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20,
      4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
      6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

  static constexpr uint32_t leftrotate(uint32_t x, uint32_t c) {
    return (x << c) | (x >> (32 - c));
  }

public:
  static std::string hash(std::string_view input) {
    uint32_t a = 0x67452301;
    uint32_t b = 0xefcdab89;
    uint32_t c = 0x98badcfe;
    uint32_t d = 0x10325476;

    std::vector<uint8_t> buffer(input.begin(), input.end());

    uint64_t original_bit_len = buffer.size() * 8;

    buffer.push_back(0x80);

    while ((buffer.size() % 64) != 56) {
      buffer.push_back(0x00);
    }

    for (int i = 0; i < 8; ++i) {
      buffer.push_back(
          static_cast<uint8_t>((original_bit_len >> (i * 8)) & 0xff));
    }

    for (size_t offset = 0; offset < buffer.size(); offset += 64) {
      uint32_t M[16];
      for (int j = 0; j < 16; ++j) {
        M[j] = static_cast<uint32_t>(buffer[offset + j * 4 + 0]) |
               (static_cast<uint32_t>(buffer[offset + j * 4 + 1]) << 8) |
               (static_cast<uint32_t>(buffer[offset + j * 4 + 2]) << 16) |
               (static_cast<uint32_t>(buffer[offset + j * 4 + 3]) << 24);
      }

      uint32_t A = a, B = b, C = c, D = d;

      for (int i = 0; i < 64; ++i) {
        uint32_t F, g;

        if (i < 16) {
          F = (B & C) | ((~B) & D);
          g = i;
        } else if (i < 32) {
          F = (D & B) | ((~D) & C);
          g = (5 * i + 1) % 16;
        } else if (i < 48) {
          F = B ^ C ^ D;
          g = (3 * i + 5) % 16;
        } else {
          F = C ^ (B | (~D));
          g = (7 * i) % 16;
        }

        uint32_t temp = D;
        D = C;
        C = B;
        B = B + leftrotate(A + F + K[i] + M[g], S[i]);
        A = temp;
      }

      a += A;
      b += B;
      c += C;
      d += D;
    }

    uint32_t result_arr[] = {a, b, c, d};
    char hex_buffer[33];
    for (int i = 0; i < 4; ++i) {
      uint8_t *bytes = reinterpret_cast<uint8_t *>(&result_arr[i]);
      sprintf(hex_buffer + i * 8, "%02x%02x%02x%02x", bytes[0], bytes[1],
              bytes[2], bytes[3]);
    }

    return std::string(hex_buffer);
  }
};
