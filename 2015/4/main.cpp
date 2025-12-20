/*
 * This file requires C++20 or later to compile
 */

#include "md5.hpp"
#include <iostream>
#include <limits>
#include <string>

int main() {
  std::string input = "yzbqklnj";
  bool answered = false;
  for (long long i = 0; i < std::numeric_limits<long long>::max(); i++) {
    std::string current_input = input + std::to_string(i);
    std::string hash = MD5::hash(current_input);
    if (hash.starts_with("00000")) {
      if (hash.starts_with("000000")) {
        std::cout << "The answer where the hash starts with 6 zeroes is " << i << " hash: " << hash << "\n";
        break;
      }
      if (!answered) {
        std::cout << "The answer where the hash starts with 5 zeroes is " << i << " hash: " << hash << "\n";
        answered = true;
      }
    }
  }
}
