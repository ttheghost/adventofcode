#include <iostream>
#include <fstream>

constexpr const char* input_file = "input";

int main() {
    std::cout << "Input file: " << input_file << std::endl;

    std::fstream file(input_file, std::ios::in);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << input_file << std::endl;
        return 1;
    }
    std::string content;
    file >> content;
    file.close();
    long long floor = 0;
    size_t floor_1_pos = 0;
    for (size_t i = 0; i < content.length(); i++)
    {
        if (content[i] == '(') {
            floor++;
        } else { // we can check if it's ')', but the input is assumed to be valid '(' or ')'
            floor--;
            // Since the floor variable starts at 0, it is mathematically impossible to reach -1 by going up.
            if (floor == -1 && floor_1_pos == 0)
            {
                floor_1_pos = i + 1;
            }
        }
    }
    std::cout << "Part one: Final floor: " << floor << std::endl;
    std::cout << "Part two: Position of first entry to basement: " << floor_1_pos << std::endl;
    return 0;
}