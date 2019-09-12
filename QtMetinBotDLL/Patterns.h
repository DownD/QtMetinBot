#pragma once
#include <Windows.h>
#include "DebugInfo.h"
#include <Psapi.h>
#include <iostream>
#include <Shlwapi.h>
#include "PatternReader.h"
#include <tlhelp32.h>


#pragma comment(lib,"shlwapi.lib")
#pragma comment(lib,"psapi.lib")

#define VARIABLE_NAME(Var) (#Var)
#define READ_FILE_PATH "Resources\\patterns.txt"
#define READ_ALL_PATTERNS_PATH "Resources\\AllPatterns.txt"
#define WRITE_FILE_PATH "Resources\\workingPatterns.txt"

class Patterns {
public:
	Patterns(HMODULE hMod);
	~Patterns();

	template <typename T>
	inline T GetPattern(const char* nameInFile) { return (T)GetPatternFromFile(nameInFile, patternsFile); }

	//Test patterns on file
	void WriteWorkingPatterns(const char* readPath = nullptr,const char* writePath = nullptr);

protected:

	//bool InitPatternsFromFile(const char* string);
	void writeWorkingPatternsToFile(const char* readPath, const char* writePath);
	std::string appendToCurrentPath(const char* buffer);


private:
	bool Init();
	bool setCurrentPath();
	bool setModuleInfo();

	int getModuleSize(void* baseAddress);
	void printModules();

	//Finds Pattern in memory
	DWORD FindPattern(const char *pattern, const char *mask);
	//Wrapper for Find Pattern
	DWORD* GetPatternAddress(const char *pattern, const char *mask, int offset);

	DWORD* GetPatternFromFile(const char *searchValue, PatternReader *file);

private:
	HMODULE hMod;
	MODULEINFO mInfo;
	bool hasReadCorrectly;
	PatternReader* patternsFile;
	char dllPath[MAX_PATH];	//Path without the filename

};

