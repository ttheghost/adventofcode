#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>

constexpr const char *input_file = "input";

int main() {
  std::cout << "Input file: " << input_file << std::endl;

  std::fstream file(input_file, std::ios::in);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open file " << input_file << std::endl;
    return 1;
  }
  std::string line;
  size_t total_area = 0;
  size_t total_ribbon = 0;
  while (std::getline(file, line)) {
    unsigned int dim[3] = {0, 0, 0};
    unsigned int areas[3];
    unsigned int min_area = 0;
    int current_dim = 0;
    for (size_t i = 0; i < line.length(); i++) {
      const char c = line[i];
      if (c >= '0' && c <= '9') {
        dim[current_dim] = (c - '0') + (10 * dim[current_dim]);
      }
      if (c == 'x') {
        current_dim++;
      }
    }
    areas[0] = dim[0] * dim[1];
    areas[1] = dim[1] * dim[2];
    areas[2] = dim[0] * dim[2];
    min_area = std::min(areas[0], std::min(areas[1], areas[2]));
    total_area += 2 * areas[0] + 2 * areas[1] + 2 * areas[2] + min_area;

    unsigned int sorted_dim[2] = {0xffff, 0xffff};
    for (short i = 0; i < 3; i++) {
      if (dim[i] < sorted_dim[0]) {
        sorted_dim[1] = sorted_dim[0];
        sorted_dim[0] = dim[i];
      } else if (dim[i] < sorted_dim[1]) {
        sorted_dim[1] = dim[i];
      }
    }

    std::cout << dim[0] << ":" << dim[1] << ":" << dim[2] << "\n"
              << sorted_dim[0] << ":" << sorted_dim[1] << "\n"
              << areas[0] << ":" << areas[1] << ":" << areas[2] << "\n";
    total_ribbon += (sorted_dim[0] + sorted_dim[1])*2 + (dim[0] * dim[1] * dim[2]);
  }
  std::cout << "The total area is: " << total_area << "\n";
  std::cout << "The total ribbon needed is: " << total_ribbon << "\n";
  // Parse the input
  file.close();
  return 0;
}
