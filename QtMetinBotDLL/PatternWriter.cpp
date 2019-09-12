#include "PatternReader.h"


PatternWriter::PatternWriter(std::string file_path) : FileWriter(file_path.c_str())
{
}

void PatternWriter::writePattern(Pattern & pattern)
{
	std::vector<std::string> vec;
	vec.push_back(pattern.searchValue);
	vec.push_back(pattern.pattern);
	vec.push_back(pattern.Mask);
	vec.push_back(std::to_string(pattern.Offset));
	writeLine(vec, ':');
}
