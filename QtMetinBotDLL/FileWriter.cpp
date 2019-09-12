#include "FileWriter.h"





FileWriter::FileWriter(const char * filePath)
{
	OpenFile(filePath);
}

FileWriter::~FileWriter()
{
	file.close();
}

void FileWriter::writeLine(std::vector<std::string>& vector, char delimiter)
{
	if (vector.size() <= 0) { return; }
	std::string str("");
	for (int i = 0; i < vector.size()-1;i++) {
		str.append(1, '"');
		str.append(vector[i]);
		str.append(1, '"');
		str.append(1, ' ');
		str.append(1, delimiter);
		str.append(1, ' ');
	}
	str.append(1, '"');
	str.append(vector[vector.size() - 1]);
	str.append(1, '"');
	str.append(1,'\n');
	file << str.data();
}

bool FileWriter::OpenFile(const char* filePath) {
	file.open(filePath, std::ifstream::in | std::ifstream::trunc);
	return file.is_open();
}