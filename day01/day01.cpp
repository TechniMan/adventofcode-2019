#include "../util.hpp"

int fuelRequirement(int mass) {
	return (int)std::floor(mass / 3.0) - 2;
}

int main(int argc, char** args) {
	uint totalFuel = 0U;
	std::ifstream file("day01input.txt");
	while (!file.bad() && !file.eof()) {
		std::string in = readline(file);
		if (in.size() > 0) {
			auto mass = std::stoi(in);
			int fuelRequiredForModule = fuelRequirement(mass);
			totalFuel += fuelRequiredForModule;
			int fuel = fuelRequiredForModule;
			while (fuel > 0) {
				fuel = fuelRequirement(fuel);
				if (fuel > 0) {
					totalFuel += fuel;
				}
			}
		}
	}
	file.close();

	std::cout << "Total fuel required: " << totalFuel << std::endl;
}
