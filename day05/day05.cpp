#include "../intcode/intcode.hpp"

int main(int argc, char** args)
{
    std::ifstream file("day02input.txt");
    const std::vector<std::string> program = readCSVLine(file);
    file.close();

    // fill the program into memory
    for (std::string s : program)
    {
        memory.push(std::stoi(s));
    }

    // run the program
    int result = runprogram();

    // print the result
    std::cout << result << std::endl;
    return 0;
}
