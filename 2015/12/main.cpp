#include "json.hpp"
#include <fstream>
#include <iostream>

constexpr const char *input_file = "input";

static int64_t sumofnum = 0;
static int64_t sumofnum2 = 0;

struct JsonCalc {
  void operator()(std::monostate) const {}
  void operator()(double d) const { sumofnum += d; }
  void operator()(bool b) const {}
  void operator()(const std::string &s) const {}

  void operator()(const std::vector<WheelJSON::JsonValue> &arr) const {
    for (size_t i = 0; i < arr.size(); ++i) {
      std::visit(*this, arr[i].value);
    }
  }

  void
  operator()(const std::map<std::string, WheelJSON::JsonValue> &obj) const {
    for (auto it = obj.begin(); it != obj.end(); it++) {
      std::visit(*this, it->second.value);
    }
  }
};

struct JsonCacl2 {
  void operator()(std::monostate) const {}
  void operator()(double d) const { sumofnum2 += d; }
  void operator()(bool b) const {}
  void operator()(const std::string &s) const {}

  void operator()(const std::vector<WheelJSON::JsonValue> &arr) const {
    for (size_t i = 0; i < arr.size(); ++i) {
      std::visit(*this, arr[i].value);
    }
  }

  void
  operator()(const std::map<std::string, WheelJSON::JsonValue> &obj) const {
    const uint64_t _sumofnum2 = sumofnum2;
    for (auto it = obj.begin(); it != obj.end(); it++) {
      if (it->second.is_string() && it->second.as_string() == "red") {
        sumofnum2 = _sumofnum2;
        break;
      }
      std::visit(*this, it->second.value);
    }
  }
};

int main() {
  std::fstream file(input_file, std::ios::in);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open file " << input_file << std::endl;
    return 1;
  }
  std::string content;
  std::getline(file, content);
  auto json = WheelJSON::JsonParser::parse(content);

  std::visit(JsonCalc{}, json.value);
  std::cout << "Sum of all numbers :" << sumofnum << std::endl;

  std::visit(JsonCacl2{}, json.value);
  std::cout << "Sum of all numbers without red :" << sumofnum2 << std::endl;

  return 0;
}
