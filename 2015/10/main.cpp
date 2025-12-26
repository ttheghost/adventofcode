#include <iostream>
#include <string>

std::string Look_and_say(const std::string& input) {
    if (input.empty()) return "";
    std::string output = "";

    char current_char = input[0];
    size_t how_many = 0;

    for (const auto& c: input)
    {
        if (c == current_char)
        {
            how_many++;
        } else {
            output += std::to_string(how_many) + current_char;
            current_char = c;
            how_many = 1;
        }
    }
    output += std::to_string(how_many) + current_char;
    return output;
}

int main() {
    std::string input = "1113222113";
    std::string output_40 = input;

    for (size_t i = 0; i < 40; i++)
    {
        output_40 = Look_and_say(output_40);
    }

    std::string output_50 = output_40;
    
    for (size_t i = 0; i < 10; i++)
    {
        output_50 = Look_and_say(output_50);
    }

    std::cout << "40 times result length: " << output_40.length() << std::endl;
    std::cout << "50 times result length: " << output_50.length() << std::endl;
    return 0;
}