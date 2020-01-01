#include "day04.hpp"

int main(int argc, char** args) {
    bool test1Result = IsCodeValid("112233") == true;
    bool test2Result = IsCodeValid("123444") == false;
    bool test3Result = IsCodeValid("111122") == true;

    std::cout << "Test 1: ";
    if (test1Result) std::cout << "SUCCESS";
    else std::cout << "FAIL";
    std::cout << std::endl;

    std::cout << "Test 2: ";
    if (test2Result) std::cout << "SUCCESS";
    else std::cout << "FAIL";
    std::cout << std::endl;

    std::cout << "Test 3: ";
    if (test3Result) std::cout << "SUCCESS";
    else std::cout << "FAIL";
    std::cout << std::endl;

    return 0;
}
