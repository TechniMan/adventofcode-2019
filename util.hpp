#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

std::string readline(std::istream& inStream) {
	std::string result;
	std::getline(inStream, result);
	return result;
}
const uint maxReadLength = 1024U;
char* readlineC(std::istream& inStream) {
	char* result = new char[maxReadLength];
	inStream.getline(result, maxReadLength);
	return result;
}

std::vector<std::string> readCSVLine(std::istream& inStream) {
	std::vector<std::string> result;
	auto line = readlineC(inStream);
	auto tok = strtok(line, ",");
	while(tok != nullptr) {
		result.push_back(std::string(tok));
		tok = strtok(nullptr, ",");
	}
	return result;
}
