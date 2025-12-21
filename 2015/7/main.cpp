#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

constexpr const char *input_file = "input";

enum OpType { NONE, ASSIGN, AND, OR, NOT, LSHIFT, RSHIFT };

struct Wire {
  std::string lhs;
  std::string rhs;
  OpType op = NONE;
  uint16_t value = 0;
  bool computed = false;
};

std::unordered_map<std::string, Wire> circuit;

uint16_t get_signal(const std::string &key);

uint16_t eval(const std::string &wire_name) {
  Wire &wire = circuit[wire_name];

  if (wire.computed)
    return wire.value;

  uint16_t left_val = 0;
  uint16_t right_val = 0;

  if (!wire.lhs.empty())
    left_val = get_signal(wire.lhs);
  if (!wire.rhs.empty())
    right_val = get_signal(wire.rhs);

  switch (wire.op) {
  case ASSIGN:
    wire.value = left_val;
    break;
  case AND:
    wire.value = left_val & right_val;
    break;
  case OR:
    wire.value = left_val | right_val;
    break;
  case NOT:
    wire.value = ~left_val;
    break;
  case LSHIFT:
    wire.value = left_val << right_val;
    break;
  case RSHIFT:
    wire.value = left_val >> right_val;
    break;
  default:
    break;
  }

  wire.computed = true;
  return wire.value;
}

uint16_t get_signal(const std::string &key) {
  if (std::isdigit(key[0])) {
    return (uint16_t)std::stoi(key);
  }
  return eval(key);
}

int main() {
  std::fstream file(input_file, std::ios::in);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open file " << input_file << std::endl;
    return 1;
  }
  std::string line;
  while (std::getline(file, line)) {
    Wire current_wire;
    if (line[0] == 'N') // NOT
    {
      current_wire.op = OpType::NOT;
      size_t start = 4, end = 4;
      while (line[end] >= 'a' && line[end] <= 'z' ||
             line[end] >= '0' && line[end] <= '9') {
        end++;
      }
      current_wire.lhs = std::string(line.data() + start, line.data() + end);
      end += 4; // skip " -> "
      start = end;
      while (line[end] >= 'a' && line[end] <= 'z') {
        end++;
      }
      std::string wire_name{line.data() + start, line.data() + end};
      circuit[wire_name] = current_wire;
    } else { // binary op OR ASSIGN
      size_t start = 0, end = 0;
      while (line[end] >= 'a' && line[end] <= 'z' ||
             line[end] >= '0' && line[end] <= '9') {
        end++;
      }
      current_wire.lhs = std::string(line.data() + start, line.data() + end);
      end++; // skip whitespace
      switch (line[end]) {
      case 'A':
        current_wire.op = OpType::AND;
        end += 4; // "AND "
        break;
      case 'O':
        current_wire.op = OpType::OR;
        end += 3; // "OR "
        break;
      case 'L':
        current_wire.op = OpType::LSHIFT;
        end += 7; // "LSHIFT "
        break;
      case 'R':
        current_wire.op = OpType::RSHIFT;
        end += 7; // "RSHIFT "
        break;
      case '-':
        current_wire.op = ASSIGN;
        end += 3; // "-> "
        break;
      }
      if (current_wire.op != ASSIGN) {
        start = end;
        while (line[end] >= 'a' && line[end] <= 'z' ||
               line[end] >= '0' && line[end] <= '9') {
          end++;
        }
        current_wire.rhs = std::string(line.data() + start, line.data() + end);
        end += 4; // " -> "
      }
      start = end;
      while (line[end] >= 'a' && line[end] <= 'z') {
        end++;
      }
      std::string wire_name{line.data() + start, line.data() + end};
      circuit[wire_name] = current_wire;
    }
  }
  uint16_t signal_a = eval("a");
  std::cout << "Part 1 (Signal on a): " << signal_a << "\n";

  for (auto &pair : circuit) {
    pair.second.computed = false;
  }

  circuit["b"].op = ASSIGN;
  circuit["b"].lhs = std::to_string(signal_a);
  circuit["b"].rhs = "";
  circuit["b"].value = signal_a;
  circuit["b"].computed = true;

  uint16_t new_signal_a = eval("a");
  std::cout << "Part 2 (Signal on a after override): " << new_signal_a << "\n";

  return 0;
}
