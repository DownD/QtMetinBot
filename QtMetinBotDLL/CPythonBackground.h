#pragma once
#include "Patterns.h"
#include "Structs.h"
#include "Memory.h"


class CPythonBackground
{
public:
	CPythonBackground(Memory* mem);
	~CPythonBackground();

	inline bool isAttrOn(float x, float y, BYTE flagAttr) { return _isAttrOn(*CMapManager, x, y, flagAttr); }
	inline bool isLocationBlocked(float x, float y) { bool result = _isAttrOn(*CMapManager, x, y, MapFlags::ATTRIBUTE_BLOCK); return result; }

private:
	CLASS_POINTER* CMapManager;
	FunctionPtr<bool, CLASS_POINTER, float, float, BYTE> _isAttrOn;
};

