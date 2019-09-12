#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <vector>
#include <sstream>

class FileWriter
{
public:
	FileWriter(const char* filePath);
	~FileWriter();

	void writeLine(std::vector<std::string> &vector, char delimiter);

private:
	bool OpenFile(const char* filePath);
	std::ofstream file;
};

