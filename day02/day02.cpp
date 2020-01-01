#include "../intcode/intcode.hpp"

int main(int argc, char** args)
{
	std::ifstream file("day02input.txt");
	const std::vector<std::string> program = readCSVLine(file);
	file.close();

	int result;
	for (int j = 0; j < 99; j++)
	{
		for (int i = 0; i < 99; i++)
		{
			memory = program;
			memory[1] = std::to_string(i);
			memory[2] = std::to_string(j);
			result = runprogram();

			if (result == 19690720) {
				std::cout << "1: " << i << " 2: " << j << std::endl;
				return 0;
			}
			else if (result == -1) {
				return -1;
			}
		}
	}

	std::cout << program.at(0) << std::endl;
	return 0;
}
