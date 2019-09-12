#include "FileReader.h"


FileReader::FileReader(const char* filePath){
    if(!OpenFile(filePath)){
        throw std::exception("Error Opening File");
    }
}   

FileReader::~FileReader(){
    file.close();
}

std::vector<std::string> FileReader::nextParsedLine(char delimiter)
{
	static int tst = 0;
	std::string line;
	if(!std::getline(file, line)){throw NO_LINE_FOUND;}
	if(line.size()>=2)
		if (line.at(0) == '/' && line.at(1) == '/')
			return nextParsedLine(delimiter);
	return parseLine(line, delimiter);
}

std::vector<std::string> FileReader::searchNextParsedLine(std::string toSearch,char delimiter, int toSearchPos){
    std::string line = getLine(toSearch,delimiter,toSearchPos);
    return parseLine(line,delimiter);
}


std::string FileReader::getInsideQuotationMarks(std::string str){
    if(str.empty())
		throw QUESTION_MARK_SYNTAX_ERROR;

    int start = str.find("\"");
    if(start == std::string::npos)
        throw QUESTION_MARK_SYNTAX_ERROR;
	start++;

    int stop = str.rfind("\"");
    int delta = stop-start;
    if(delta<0)
        throw QUESTION_MARK_SYNTAX_ERROR;           
    return str.substr(start,delta);
}

std::vector<std::string> FileReader::parseLine(std::string line, char delimiter){

	std::vector<std::string> stringVec;
	std::stringstream lineStream(line);
	std::string item;
	while (std::getline(lineStream, item, delimiter)) {
		try {
			item = getInsideQuotationMarks(item);
		}
		catch (int e) {
			continue;
		}
		stringVec.push_back(item);
	}

    return stringVec;
}

std::vector<std::string> FileReader::searchParsedLine(std::string toSearch, char delimiter ,int toSearchPos){
    resetFileIterator();
	std::vector<std::string> vec = searchNextParsedLine(toSearch,delimiter,toSearchPos);
	return vec;
}

std::string FileReader::getStringAtPosition(std::string line, char delimiter,int pos){
    int nextDelimiter = line.find(delimiter);
    int startString = 0;
    int currPosition;

    for(currPosition = 0; nextDelimiter!=std::string::npos ;currPosition++){
        if(currPosition == pos)
            return getInsideQuotationMarks(line.substr(startString,nextDelimiter - startString));
        
        startString = nextDelimiter+1;
        nextDelimiter = line.find(delimiter,startString);
    }
    //check last position
    if(currPosition == pos)
        return  getInsideQuotationMarks(line.substr(startString, line.size()-startString));

    throw NO_VALUE_FOUND;

}


std::string FileReader::getLine(std::string toSearch, char delimiter, int delimiterPos){
    std::string buffer;
    std::string line;
    while(std::getline(file,line)){
		if (line.length() > 2) {
			if(line.at(0) == '/' && line.at(1) == '/')
				continue;
		}
        try{
            buffer = getStringAtPosition(line, delimiter ,delimiterPos);
        }catch(int e){
            continue;
        }

        if(buffer.compare(toSearch)==0){
            return line;
        }
    }

    throw NO_LINE_FOUND;
}

bool FileReader::OpenFile(const char* filePath){
    file.open(filePath,std::ifstream::out);
    return file.is_open();
}
