#include "../util.hpp"

bool IsCodeValid(std::string code) {
    bool valid = true;

    if (code.length() != 6) {
        valid = false;
    }
    else {
        char prev = code[0];
        std::map<char, int> repeats;
        for (int idx = 1; idx < 6; ++idx) {
            char current = code[idx];
            if (current < prev) {
                valid = false;
                break;
            }
            // if a digit repeats, record it
            if (current == prev) {
                auto it = repeats.find(current);
                if (it != repeats.end()) {
                    it->second++;
                }
                else {
                    repeats.emplace(current, 2);
                }
            }
            prev = current;
        }

        if (valid) {
            bool containsPair = false;
            for (auto repeat : repeats) {
                if (repeat.second == 2) {
                    containsPair = true;
                    break;
                }
            }
            valid = containsPair;
        }
    }

    return valid;
}
