#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <vector>
#include <sstream>

#define NO_LINE_FOUND 0x1
#define NO_VALUE_FOUND 0x2
#define QUESTION_MARK_SYNTAX_ERROR 0x3


//Reads a file and executes various operations:
//    Searches for a value at some position and line (the position is based on the separator
//    starting at 0) and returns a value in other position on the same line
//    The Values on the file need to be in between quotation marks
//	  Ignore lines that satrt with "//"
class FileReader{
public:
    FileReader(const char* filePath);
    ~FileReader();

	//Get Next Line
	//throws NO_LINE_FOUND if end of lines has reached
	std::vector<std::string> nextParsedLine(char delimiter);

    //Searches for a value at some position and returns a vector of string separated in order
    //this function also reset the iterator
    //throws NO_LINE_FOUND if no line is found1
    std::vector<std::string> searchParsedLine(std::string toSearch, char delimiter ,int toSearchPos);

    //Get the next line parsed
	//Without reseting the iterator
    //throws NO_LINE_FOUND if no line is found
    std::vector<std::string> searchNextParsedLine(std::string toSearch,char delimiter, int toSearchPos);

    //Sets the stream iterator to the beginning
    void resetFileIterator(){file.clear();file.seekg(0, std::ios_base::beg);}

    //Get String at a position more efficiently
    //Throws NO_VALUE_FOUND if the position doesn't eexist
    //Position starts at 0
    //throws QUESTION_MARK_SYNTAX_ERROR if question mark is not placed right
    static std::string getStringAtPosition(std::string line, char separator,int pos);
private:
    bool OpenFile(const char* filePath);


    //Return the line that contains the toSearch at the postiion delimiterPos
	//Ignore lines that satrt with "//"
    //throws NO_LINE_FOUND if no line is found
    std::string getLine(std::string toSearch, char delimiter , int delimiterPos);

    //Returns a string betwenn quotation marks
    //throws QUESTION_MARK_SYNTAX_ERROR if file is not correctly formated
    static std::string getInsideQuotationMarks(std::string str);

    //returns a vector for each value
    std::vector<std::string> parseLine(std::string, char delimiter);

private:
    std::ifstream file;
};