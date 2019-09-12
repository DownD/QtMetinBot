#include "CPythonBackground.h"



CPythonBackground::CPythonBackground(Memory* mem)
{
	_isAttrOn = mem->GetCRelativeMethod<FunctionPtr<bool, CLASS_POINTER, float, float, BYTE>,DWORD>("isAttrOnFunc", 1, CRITICAL);
	CMapManager = mem->GetCMethod<CLASS_POINTER*>("CMapManager", DEREFERENCE, CRITICAL);

}


CPythonBackground::~CPythonBackground()
{
}
