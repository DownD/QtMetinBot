#include "PatternReader.h"



Pattern PatternReader::getPattern(std::string searchValue) {

	resetFileIterator();
	return getNextPattern(searchValue);
}

Pattern PatternReader::getNextPattern(std::string searchValue)
{
	std::vector<std::string> arr;
	try {
		arr = searchNextParsedLine(searchValue, ':', 0);
	}
	catch (int e) {

		if (e == NO_LINE_FOUND) {
			resetFileIterator();
			throw EXCEPTION_NO_PATTERN_FOUND;
		}

		else throw EXCEPTION_UKNOWN_EXCEPTION;
	}

	if (arr.size() < 4) {
		throw EXCEPTION_TO_FEW_ARGUMENTS;
	}

	Pattern pat;
	pat.searchValue = arr[0];
	pat.pattern = fixByteStream(arr[1]);
	pat.Mask = arr[2];
	pat.Offset = std::atoi(arr[3].c_str());
	return pat;
}

Pattern PatternReader::getNextLine()
{
	std::vector<std::string> vec = nextParsedLine(':');

	if (vec.size() < 4) { throw  EXCEPTION_TO_FEW_ARGUMENTS; }
	Pattern pat;
	pat.searchValue = vec[0];
	pat.pattern = vec[1];
	pat.Mask = vec[2];
	pat.Offset = std::atoi(vec[3].c_str());

	return pat;
}

std::string PatternReader::fixByteStream(std::string &str)
{
	std::string result;
	for (int i = 0; i < str.size(); i+=4) {
		long number = strtoul(str.substr(i + 2, i + 3).c_str(),NULL,16);
		result+=(char)number;
	}
	return result;
}

PatternReader::PatternReader(std::string file_path) : FileReader(file_path.c_str()) {
}

