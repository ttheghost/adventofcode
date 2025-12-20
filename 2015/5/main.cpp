#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

constexpr const char *input_file = "input";

bool is_naughty(std::string_view name) {
  int num_vowels = 0;
  char previous_char = 0;
  bool has_consecutive_letters = false;
  bool has_disallowed = false;
  for (char c : name) {
    switch (c) {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
      num_vowels++;
      break;

    case 'b':
      has_disallowed = (previous_char == 'a') ? true : has_disallowed;
      break;
    case 'd':
      has_disallowed = (previous_char == 'c') ? true : has_disallowed;
      break;
    case 'q':
      has_disallowed = (previous_char == 'p') ? true : has_disallowed;
      break;
    case 'y':
      has_disallowed = (previous_char == 'x') ? true : has_disallowed;
      break;
    default:
      break;
    }
    if (c == previous_char)
      has_consecutive_letters = true;
    previous_char = c;
  }
  return (num_vowels < 3) || has_disallowed || !has_consecutive_letters;
}

#include <iostream>
#include <string>
#include <unordered_map>

bool is_nice_2(std::string_view name) {
  if (name.length() < 3)
    return false;

  bool has_gap_repeat = false;
  bool has_pair_twice = false;

  std::unordered_map<std::string, size_t> pairs;

  for (size_t i = 0; i < name.length(); i++) {
    if (i >= 2 && name[i] == name[i - 2]) {
      has_gap_repeat = true;
    }

    if (i >= 1) {
      std::string pair;
      pair += name[i - 1];
      pair += name[i];

      if (pairs.contains(pair)) {
        if (i - pairs[pair] >= 2) {
          has_pair_twice = true;
        }
      } else {
        pairs[pair] = i;
      }
    }
  }

  return has_gap_repeat && has_pair_twice;
}

int main() {
  std::fstream file(input_file, std::ios::in);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open file " << input_file << std::endl;
    return 1;
  }
  std::string line;
  size_t nice_num = 0;
  size_t nice_num_2 = 0;
  while (std::getline(file, line)) {
    if (!is_naughty(line)) {
      nice_num++;
    }
    if (is_nice_2(line)) {
      nice_num_2++;
    }
  }
  std::cout << nice_num << " : " << nice_num_2 << "\n";
  return 0;
}
