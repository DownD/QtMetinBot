#pragma once
#include "Patterns.h"
#include <iterator>
#include "CInstanceBase.h"
#include "DebugInfo.h"
#include "Structs.h"

class InstanceVectorIterator;


//Only one object should be created
typedef DWORD* VECTOR_POSITION;
typedef Map<DWORD, CInstanceBase*> InstanceMap;
typedef Vector<CInstanceBase*> InstanceVector;


class CPythonCharacterManager
{
public:
	CPythonCharacterManager(Memory* mem);
	~CPythonCharacterManager();

	
	inline CInstanceBase* getMainInstance(){ return (CInstanceBase*)*(DWORD*)(mainInstanceOffset + (int)*classPointer); }
	inline InstanceMap* getInstanceMap() { return (Map<DWORD, CInstanceBase*>*)((int)(*classPointer) + mapOffset); }
	inline InstanceVector* getInstanceVector() { return (InstanceVector*)(startOfInstanceList); }
	CInstanceBase* getInstanceByVID(int vid);

	//Returns a vector containing a list of players only
	void getPlayerList(std::vector<CInstanceBase*>* vec);




private:
	CLASS_POINTER* classPointer;
	DWORD* startOfInstanceList; //Not an offset

	BYTE mainInstanceOffset;
	BYTE mapOffset;
};


