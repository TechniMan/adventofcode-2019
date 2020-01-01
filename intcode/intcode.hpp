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
