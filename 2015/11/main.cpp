#include <string>
#include <iostream>
#include <stdexcept>
#include <vector>

void increment_password(std::string& s) {
    size_t i = s.length() - 1;
    while (true) {
        if (s[i] == 'z') {
            s[i] = 'a';
            if (i == 0) break;
            i--;
        } else {
            s[i]++;
            if (s[i] == 'i' || s[i] == 'o' || s[i] == 'l') {
                s[i]++;
            }
            break;
        }
    }
}

// Check the three rules
bool is_valid(const std::string& s) {
    // No i, o, l
    if (s.find_first_of("iol") != std::string::npos) return false;

    // (abc, xyz)
    bool has_straight = false;
    for (size_t i = 0; i < s.length() - 2; i++) {
        if (s[i+1] == s[i] + 1 && s[i+2] == s[i] + 2) {
            has_straight = true;
            break;
        }
    }
    if (!has_straight) return false;

    // (aa...bb)
    int pair_count = 0;
    for (size_t i = 0; i < s.length() - 1; i++) {
        if (s[i] == s[i+1]) {
            pair_count++;
            i++;
        }
    }
    return pair_count >= 2;
}

int main() {
    std::string current = "vzbxkghb";
    
    while (true) {
        increment_password(current);
        if (is_valid(current)) {
            std::cout << "Next valid password: " << current << std::endl;
            break;
        }
    }
    while (true) {
        increment_password(current);
        if (is_valid(current)) {
            std::cout << "Next valid password: " << current << std::endl;
            break;
        }
    }
    return 0;
}