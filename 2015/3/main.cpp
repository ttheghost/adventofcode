#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>

constexpr const char *input_file = "input";

struct point {
public:
  int x, y;
  point() : x(0), y(0) {}
};

int main() {
  std::fstream file(input_file, std::ios::in);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open file " << input_file << std::endl;
    return 1;
  }

  std::string input;
  file >> input;

  std::unordered_set<long long> my_points{};
  my_points.insert(0);

  point current_santa_pnt{};
  point current_robot_pnt{};
  bool whos_turn = true; // true == santa
  for (size_t i = 0; i < input.length(); i++) {
    point &current_pnt = (whos_turn) ? current_santa_pnt : current_robot_pnt;
    switch (input[i]) {
    case '^':
      current_pnt.x++;
      break;
    case '<':
      current_pnt.y--;
      break;
    case '>':
      current_pnt.y++;
      break;
    case 'v':
      current_pnt.x--;
      break;
    default:
      break;
    }
    whos_turn = !whos_turn;

    my_points.insert(*(long long *)&current_pnt); // works on x64
  }

  std::cout << "Number of houses: " << my_points.size() << "\n";

  return 0;
}
