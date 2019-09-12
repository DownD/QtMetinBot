#pragma once
#include "Patterns.h"
#include "PythonDumper.h"
#include "DebugInfo.h"

#define CRITICAL 1
#define NO_CRITICAL 0

#define DEREFERENCE 1
#define NO_DEREFERENCE 0

typedef PyObject* (*PythonFunction)(PyObject* self, PyObject* args);

class Memory
{
public:
	Memory(HMODULE hMod);
	~Memory();

	//If is critical will print a debug error
	PythonFunction GetPythonMethod(const char* module, const char * func, bool isCritical = CRITICAL);

	//If is critical will print a debug error
	template <class T>
	T GetCMethod(const char* name, bool dereferece, bool isCritical = NO_CRITICAL)
	{
		T var = 0;
		if (dereferece) {
			T* addr = pat->GetPattern<T*>(name);
			__try {
				var = *addr;
			}
			__except (EXCEPTION_EXECUTE_HANDLER) {
				var = 0;
				//DEBUG_INFO(COLOR_DEFAULT,"Fail dereferencing pointer");
			}
		}
		else {
			var = pat->GetPattern<T>(name);
		}


		if (isCritical && var == 0) {
			DEBUG_INFO(COLOR_RED, "Critical CFunction -> %s  not found", name);
		}

		return var;
	}

	//Adds the baseModule to the value queryed
	template<class Function,class Offset>
	Function GetCRelativeMethod(const char* name, WORD offsetPos, bool isCritical = NO_CRITICAL) {
		DWORD location = GetCMethod<DWORD>(name, NO_DEREFERENCE, isCritical);

		if (!location) {
			return 0;
		}
		

		Offset offset = 0;
		__try {
			offset = *(Offset*)(location + offsetPos);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			if(isCritical)
				DEBUG_INFO(COLOR_RED, "Critical CRelativeFunction -> %s  not sucessfull dereferenced", name);
			return 0;
		}

		Function result = (Function)(location + (DWORD)offset + offsetPos + sizeof(Offset));
		DEBUG_INFO(COLOR_DEFAULT, "Relative Function %s Found at %#x", name, result);
		return result;
	}

private:
	//return 0 if no function was found
	PythonFunction getFunctionAddress(const char* module, const char* function);

private:
	PythonModuleMap functions;
	Patterns* pat;
	HMODULE hMod;
};

