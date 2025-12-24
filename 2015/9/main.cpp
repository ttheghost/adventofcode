#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <algorithm>

constexpr const char *input_file = "input";

struct City {
  std::unordered_map<std::string, uint64_t> neighbours;
};

std::unordered_map<std::string, City> graph;

std::vector<std::string> cities;

int main() {
  std::fstream file(input_file, std::ios::in);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open file " << input_file << std::endl;
    return 1;
  }

  std::string from, to, trash;
  uint64_t dist;
  while (file >> from >> trash >> to >> trash >> dist) {
      graph[from].neighbours[to] = dist;
      graph[to].neighbours[from] = dist;
  }

  for (const auto& g: graph) {
    cities.push_back(g.first);
  }

  std::sort(cities.begin(), cities.end()); // needs to be sorted before next_permutation
  uint64_t min_dist = -1;
  uint64_t max_dist = 0;
  do {
    uint64_t current_dist = 0;
    bool possible = true;

    for (size_t i = 0; i < cities.size() - 1; ++i) {
      std::string& c1 = cities[i];
      std::string& c2 = cities[i+1];

      if (graph[c1].neighbours.count(c2)) {
        current_dist += graph[c1].neighbours[c2];
      } else {
        possible = false;
        break;
      }
    }

    if (possible) {
        if (current_dist < min_dist) min_dist = current_dist;
        if (current_dist > max_dist) max_dist = current_dist;
    }
  } while (std::next_permutation(cities.begin(), cities.end()));

  std::cout << "The shortest distance is: " << min_dist << "\n";
  std::cout << "The longest distance is: " << max_dist << "\n";
  return 0;
}
