#include "FileReader.h"
#include <string>
#include "FileWriter.h"
#include <map>
#define EXCEPTION_NO_PATTERN_FOUND 0x100
#define EXCEPTION_TO_FEW_ARGUMENTS 0x101
#define EXCEPTION_UKNOWN_EXCEPTION 0x102


struct Pattern {
	std::string searchValue;
	std::string pattern;
	std::string Mask;
	int Offset;
};

class PatternReader : protected FileReader{
public:
    PatternReader(std::string file_path);

	//returns the next Pattern, mask, and offset
	// throws EXCEPTION_NO_PATTERN_FOUND if the EOF has been reached and the iterator is restarted
	// EXCEPTION_TO_FEW_ARGUMENTS if the vector has size less then 3
	Pattern getPattern(std::string searchValue);
	Pattern getNextPattern(std::string searchValue);

	//Get nextLine
	//pattern is not fixed!! fixByteStream needs to be called
	//thorws NO_LINE_FOUND if the end is reached
	Pattern getNextLine();

	virtual ~PatternReader() {};

public:
	static std::string fixByteStream(std::string &str);

};

class PatternWriter : protected FileWriter {
public:
	PatternWriter(std::string file_path);


	void writePattern(Pattern & patern);
};



