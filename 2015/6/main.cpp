#include <array>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>

constexpr const char *input_file = "input";

enum OP : uint8_t { TOGGLE = 0, TURNON, TURNOFF };

std::pair<std::pair<uint16_t, uint16_t>, size_t> get_point(std::string_view s) {
  uint16_t x = 0;
  uint16_t y = 0;
  bool current = false;
  bool coma_skiped = false;
  size_t i = 0;
  for (; i < s.length(); i++) {
    uint16_t &j = current ? y : x;
    const char c = s[i];
    if (c >= '0' && c <= '9') {
      j = (c - '0') + (j * 10);
    } else if (c == ',') {
      if (coma_skiped) {
        std::cerr << "Unvalid input: " << s << "\n";
        throw std::exception();
      } else {
        current = true;
        coma_skiped = true;
      }
    } else {
      if ((c == ' ' && coma_skiped) || c == 13) {
        break;
      }
      std::cerr << "Unvalid input: " << s << "\n";
      throw std::exception();
    }
  }
  return {{x, y}, i};
}

void toggle(std::array<std::array<bool, 1000>, 1000> &map) {}

int main() {
  std::fstream file(input_file, std::ios::in);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open file " << input_file << std::endl;
    return 1;
  }
  std::string line;
  static std::array<std::array<bool, 1000>, 1000> map;
  static std::array<std::array<unsigned short, 1000>, 1000> map_2;
  for (size_t i = 0; i < 1000; i++)
    for (size_t j = 0; j < 1000; j++)
      map[i][j] = false;

  while (std::getline(file, line)) {
    OP operation;
    size_t i = 0;
    if (line[1] == 'o') {
      operation = OP::TOGGLE;
      i = 7;
    } else if (line[6] == 'n') {
      operation = OP::TURNON;
      i = 8;
    } else {
      operation = OP::TURNOFF;
      i = 9;
    }
    auto a = get_point(std::string_view(line.data() + i, line.length() - i));
    auto start = a.first;
    i += a.second + 9; // skip " through "
    a = get_point(std::string_view(line.data() + i, line.length() - i));
    auto end = a.first;

    for (size_t x = start.first; x <= end.first; ++x) {
      for (size_t y = start.second; y <= end.second; y++) {
        switch (operation) {
        case OP::TOGGLE:
          map[x][y] = !map[x][y];
          map_2[x][y]+=2;
          break;
        case OP::TURNON:
          map[x][y] = true;
          map_2[x][y]++;
          break;
        case OP::TURNOFF:
          map[x][y] = false;
          if (map_2[x][y] > 0) map_2[x][y]--;
          break;
        }
      }
    }
  }

  size_t lights_on = 0;
  for (const auto &row : map) {
    for (bool light : row) {
      if (light)
        lights_on++;
    }
  }
  std::cout << "Lights on: " << lights_on << "\n";
  size_t total_brightness = 0;
  for (const auto &row : map_2) {
    for (auto& light : row) {
      total_brightness += light;
    }
  }
  std::cout << "Total brightness: " << total_brightness << "\n";
  return 0;
}
