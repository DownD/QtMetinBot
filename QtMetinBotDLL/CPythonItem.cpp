#include "CPythonItem.h"


#define ITEM_MAP_OFFSET 0x4

CPythonItem::CPythonItem(Memory* mem, CPythonPlayer * player)
{
	this->player = player;
	C_PythonItem = mem->GetCMethod<CLASS_POINTER*>("CPythonItem", DEREFERENCE);
	if (C_PythonItem) {
		groundItems = (GroundItemMap*)((int)*C_PythonItem + ITEM_MAP_OFFSET);

#ifdef _DEBUG
		m_GrounItemOwnershipOffset = mem->GetCMethod<DWORD>("m_GroundItemOwnership", DEREFERENCE) - 4;
#else
		m_GrounItemOwnershipOffset = mem->GetCMethod<DWORD>("m_GroundItemOwnership", DEREFERENCE);
#endif
	}
}


CPythonItem::~CPythonItem()
{
}

SGroundItemInstance * CPythonItem::getGroundItemByVID(int vid)
{
	auto map = getGroundItemMap();
	GroundItemMap::iterator begin = map->begin();
	GroundItemMap::iterator end = map->end();

	for (; begin != end; ++begin) {
		if (begin.getKey() == vid)
			return begin.getValue();
	}
	return nullptr;
}

bool CPythonItem::getCloseItem(Point2D & origin, ItemGround * buffer,float maxDist,bool checkOwnership)
{
	auto map = getGroundItemMap();
	GroundItemMap::iterator begin = map->begin();
	GroundItemMap::iterator end = map->end();

	float closestDist = maxDist;
	std::string mainPlayerName;
	player->getMainInstance()->getName(mainPlayerName);

	for (; begin != end; ++begin) {
		SGroundItemInstance* curr = begin.getValue();

		if (checkOwnership) {
			std::string* itemName = getGroundItemOwnership(curr);
			if (!itemName->empty()) {
				if (itemName->compare(mainPlayerName.data()) != 0)
					continue;
			}
		}

		Point2D a = curr->getItemPosition2D();
		float currDist = origin.distance(&curr->getItemPosition2D());
		if (currDist < closestDist) {
			buffer->item = curr;
			buffer->vnum = begin.getKey();
			closestDist = currDist;
		}
	}

	if (closestDist != maxDist)
		return true;
	return false;
}
