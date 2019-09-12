#pragma once
#include "Patterns.h"
#include "Structs.h"
#include "CPythonPlayer.h"
#include "Memory.h"


typedef Map<DWORD, SGroundItemInstance*> GroundItemMap;

class CPythonItem
{
public:
	CPythonItem(Memory* mem,CPythonPlayer* player);
	~CPythonItem();

	inline GroundItemMap* getGroundItemMap() { return groundItems; };
	SGroundItemInstance* getGroundItemByVID(int vid);
	std::string* getGroundItemOwnership(SGroundItemInstance* item) { return (std::string*)((DWORD)item + m_GrounItemOwnershipOffset); }
	bool getCloseItem(Point2D & origin, ItemGround * buffer, float maxDist,bool checkOwnership);

private:
	CPythonPlayer* player;

	CLASS_POINTER* C_PythonItem;

	GroundItemMap* groundItems;
	DWORD m_GrounItemOwnershipOffset; //Offset of a SGroundItemInstance

};

