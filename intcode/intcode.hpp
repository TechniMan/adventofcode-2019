#include "../util.hpp"

std::vector<std::string> memory;
int getvalueat(uint index) { return std::stoi(memory[index]); }
void setvalueat(uint index, int val) { memory[index] = std::to_string(val); }

int runprogram() {
	bool shouldEscape = false;
	int opcode = 0;
	for (uint progCounter = 0U; !shouldEscape;) {
        if (progCounter >= memory.size()) {
            shouldEscape = true;
            std::cout << "PROGRAM OVERFLOW ENCOUNTERED" << std::endl;
            break;
        }
        
        std::vector<ushort> paramModes = { 0U, 0U, 0U };
        std::string instruction = std::to_string(getvalueat(progCounter));
        // 2-digit opcode
		if (instruction.size() < 3) {
            opcode = std::stoi(instruction);
        }
        // 3 digits param modes
        else if (instruction.size() < 6) {
            opcode = std::stoi(instruction.substr(instruction.size() - 2));
            paramModes[2] = std::stoi(instruction.substr(0, 1));
            if (instruction.size() > 3) {
                paramModes[1] = std::stoi(instruction.substr(1, 1));
            }
            if (instruction.size() > 4) {
                paramModes[0] = std::stoi(instruction.substr(2, 1));
            }
        }
        else {
            std::cout << "ERRONEOUS PROGRAM INSTRUCTION" << std::endl;
            break;
        }

        std::string inp;
        int o;
		switch (opcode) {
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
        
        //inp
        case 3:
            std::cout << "INPUT REQUIRED: ";
            std::cin >> inp;
            int i = std::stoi(inp);
            setvalueat(progCounter + 1, i);
            break;
        
        //out
        case 4:
            o = getvalueat(getvalueat(progCounter + 1));
            std::cout << "OUTPUT: " << std::to_string(o) << std::endl;
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
