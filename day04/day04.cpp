#include "day04.hpp"

int main(int argc, char ** args) {
    uint32_t begin = 147981U;
    uint32_t end   = 691423U;

    uint32_t count = 0U;
    for (uint32_t password = begin; password < end + 1; ++password) {
        count += IsCodeValid(std::to_string(password));
    }

    std::cout << "There are " << std::to_string(count)
              << " valid codes in the given range." << std::endl;

    return 0;
}
