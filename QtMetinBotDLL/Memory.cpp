#include "Memory.h"



Memory::Memory(HMODULE hMod)
{
	pat = new Patterns(hMod);
	if (!PythonDumper::getPythonModulesAndFunctions(&functions))
		throw std::exception("Error dumping python functions");
	this->hMod = hMod;
}
PythonFunction Memory::GetPythonMethod(const char* module, const char * func, bool isCritical) {
	PythonFunction pointer = getFunctionAddress(module, func);
	if (!pointer && isCritical) {
		DEBUG_INFO(COLOR_RED, "Critical PythonFunction -> %s not found on interpreter",func);
	}
	else {
		DEBUG_INFO(COLOR_GREEN, "PythonFunction %s found at %#x",func, pointer);
	}

	return pointer;
}


PythonFunction Memory::getFunctionAddress(const char * module, const char * function)
{
	auto it = functions.find(module);
	if (it == functions.end()) {
		DEBUG_INFO(COLOR_RED, "No python module with name %s found\n", module);
		return 0;
	}
	auto func_it = it->second.find(function);
	if (func_it == it->second.end()) {
		return 0;
	}

	return func_it->second;
}

Memory::~Memory()
{
	delete pat;
}
