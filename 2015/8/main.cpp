#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>

constexpr const char *input_file = "input";

int main() {
  std::fstream file(input_file, std::ios::in);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open file " << input_file << std::endl;
    return 1;
  }
  std::string line;
  size_t overhead = 0;
  size_t part2_overhead = 0;
  while (std::getline(file, line)) {
    size_t real_length = 0;
    size_t escaped_length = 0;
    size_t encoded_length = 0;
    bool is_escape = false;
    int is_hex = 0;
    for (size_t i = 0; i < line.length(); i++) {
      if (line[i] != '\n' && line[i] != '\r') {
        real_length++;
      }

      switch (line[i]) {
      case '\n':
      case '\r':
        break;
      case '\\':
        if (is_escape) {
          escaped_length++;
          is_escape = false;
        } else {
          is_escape = true;
        }
        break;
      case '"':
        if (is_escape) {
          is_escape = false;
        }
        escaped_length++;
        break;
      case 'x':
        if (is_escape) {
          is_escape = false;
          is_hex = 2;
        } else {
          escaped_length++;
        }
        break;
      default:
        if (is_escape) {       // unsuported escape
          escaped_length += 2; // the '\' and this char
        } else if (is_hex > 0) {
          if ((line[i] >= '0' && line[i] <= '9') ||
              (line[i] >= 'a' && line[i] <= 'f')) {
            is_hex--;
            if (is_hex == 0) {
              escaped_length++;
            }
          } else {
            escaped_length += 3 + (is_hex - 2);
            is_hex = 0; // unvalid hex char
          }
        } else {
          escaped_length++;
        }
        break;
      }
    }
    escaped_length -= 2; // remove the double quotes
    overhead += real_length - escaped_length;

    encoded_length += real_length + 2;
    for (char c : line) {
      if (c == '"' || c == '\\') {
        encoded_length++;
      }
    }
    part2_overhead += encoded_length - real_length;
  }
  std::cout << "Overhead: " << overhead << std::endl;
  std::cout << "Part 2 Overhead: " << part2_overhead << std::endl;
  return 0;
}
