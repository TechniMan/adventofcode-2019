#include "../util.hpp"

std::vector<std::string> memory;
int getvalueat(uint index) { return std::stoi(memory[index]); }
void setvalueat(uint index, int val) { memory[index] = std::to_string(val); }

int runprogram() {
	bool shouldEscape = false;
	int opcode = 0;
	for (uint progCounter = 0U; !shouldEscape;)
	{
		opcode = getvalueat(progCounter);
		switch (opcode)
		{
		//add
		case 1:
			setvalueat(getvalueat(progCounter + 3),
				getvalueat(getvalueat(progCounter + 1)) +
				getvalueat(getvalueat(progCounter + 2)));
			progCounter += 4;
			break;

		//mul
		case 2:
			setvalueat(getvalueat(progCounter + 3),
				getvalueat(getvalueat(progCounter + 1)) *
				getvalueat(getvalueat(progCounter + 2)));
			progCounter += 4;
			break;

		//esc
		case 99:
			shouldEscape = true;
			break;

		//exp
		default:
			std::cout << "Erroneous opcode: " << opcode << "\n  at position " << std::to_string(progCounter) << std::endl;
			shouldEscape = true;
			return -1;
		}
	}
	return getvalueat(0);
}

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
