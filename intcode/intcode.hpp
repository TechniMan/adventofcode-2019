#include "../util.hpp"

enum PARAM_MODES {
    PARAM_MODE_POSITION = 0,
    PARAM_MODE_IMMEDIATE = 1
};

std::vector<uint> memory;
int getvalue(uint parameterMode, uint parameter) {
    if (parameterMode == PARAM_MODE_POSITION) {
        return memory[parameter];
    }
    else {
        return parameter;
    }
}
void setvalue(uint parameterMode, uint parameter, uint value) {
    if (parameterMode == PARAM_MODE_POSITION) {
        memory[index] = val;
    }
}
int getvalueat(uint index) {
    return std::stoi(memory[index]);
}
void setvalueat(uint index, int val) {
    memory[index] = std::to_string(val);
}

// This method assumes that the program has been loaded into memory already.
int runprogram() {
    bool shouldEscape = false;
    int opcode = 0;
    for (uint progCounter = 0U; !shouldEscape;) {
        if (progCounter >= memory.size()) {
            shouldEscape = true;
            std::cout << "PROGRAM OVERFLOW ENCOUNTERED" << std::endl;
            break;
        }

        // get the next instruction out of memory
        std::string instruction = std::to_string(getvalueat(progCounter));

        std::vector<ushort> paramModes = { 0U, 0U, 0U };
        // 2-digit opcode
        if (instruction.size() <= 2) {
            opcode = std::stoi(instruction);
        }
        // 3-5 digits: param modes
        else if (instruction.size() < 6) {
            opcode = std::stoi(instruction.substr(instruction.size() - 2));
            paramModes[0] = std::stoi(instruction.substr(0, 1));
            if (instruction.size() > 3) {
                paramModes[1] = std::stoi(instruction.substr(1, 1));
            }
            if (instruction.size() > 4) {
                paramModes[2] = std::stoi(instruction.substr(2, 1));
            }
        }
        else {
            std::cout << "ERRONEOUS PROGRAM INSTRUCTION: TOO LONG (" << instruction << ")" << std::endl;
            break;
        }

        std::string inp;
        int i;
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
            std::cout << "INPUT REQUIRED > ";
            std::cin >> inp;
            i = std::stoi(inp);
            setvalueat(progCounter + 1, i);
            break;

        //out
        case 4:
            i = getvalueat(getvalueat(progCounter + 1));
            std::cout << "OUTPUT > " << std::to_string(i) << std::endl;
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
