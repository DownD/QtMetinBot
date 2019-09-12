#include "Pickup.h"

#define PICKUP_MS_WAIT 600


Pickup::Pickup()
{
	isNormalActive = 0;
	isRangeActive = 0;
	checkOwnership = true;
	silentRangePickup = true;
}

Pickup::~Pickup()
{
}

void Pickup::Start()
{
	DEBUG_INFO(COLOR_DEFAULT, "PICKUP: Starting pickup");
	isNormalActive = 1;
}


void Pickup::ThreadLoop()
{
	if (isNormalActive) {

		if (GetTickCount() - lastTimeLoop < PICKUP_MS_WAIT)
			return;

		lastTimeLoop = GetTickCount();

		if (isRangeActive) {
			RangePickup();
			return;
		}

		sdk->getPythonPlayer()->PickCloseItem();
	}


}

void Pickup::Stop()
{
	isNormalActive = 0;
}

void Pickup::setSilentUse(bool var)
{
	silentRangePickup = var;
}

bool Pickup::getValidClosestItem(ItemGround * buffer, std::vector<ItemGround> * groundItems)
{
	CPythonItem* item = sdk->getPythonItem();
	CInstanceBase* mainInstance = sdk->getPythonPlayer()->getMainInstance();

	float closestDist = maxRangeTeleport;
	Point2D origin;

	mainInstance->getPosition(origin);

	for (auto &curritem : *groundItems) {

		Point2D itemPos = curritem.item->getItemPosition2D();

		if (sdk->getPythonBackground()->isLocationBlocked(itemPos.x, itemPos.y))
			continue;

		float currDist = origin.distance(&itemPos);
		if (currDist < closestDist) {
			buffer->item = curritem.item;
			buffer->vnum = curritem.vnum;
			closestDist = currDist;
		}
	}

	if (closestDist != maxRangeTeleport)
		return true;
	return false;

}

void Pickup::pickEveryItemInRange(Point2D player, std::vector<ItemGround>* groundItems)
{
	CPythonNetwork* net = sdk->getPythonNetwork();
	for (auto & currItem : *groundItems) {
		Point2D itemPos = currItem.item->getItemPosition2D();
		float dist = player.distance(&itemPos);
		if (dist < maxRangePick) {
			DEBUG_INFO(COLOR_DEFAULT, "RANGE_PICKUP: Item in Range, picking");
			net->SendItemClickPacket(currItem.vnum);
		}
	}
}

void Pickup::getPickableItemsVector(std::vector<ItemGround> * buffer)
{
	CPythonItem* item = sdk->getPythonItem();
	CInstanceBase* mainInstance = sdk->getPythonPlayer()->getMainInstance();

	auto map = item->getGroundItemMap();
	GroundItemMap::iterator begin = map->begin();
	GroundItemMap::iterator end = map->end();

	std::string mainPlayerName;

	mainInstance->getName(mainPlayerName);

	for (; begin != end; ++begin) {
		SGroundItemInstance* curr = begin.getValue();

		if (checkOwnership) {
			std::string* itemName = item->getGroundItemOwnership(curr);
			if (!itemName->empty()) {
				DEBUG_INFO(COLOR_DEFAULT, "Item Ownership: %s -> Size %d  -> Address %#x\n", itemName->data(), itemName->size(), itemName);
				if (itemName->compare(mainPlayerName.data()) != 0)
					continue;
			}
		}
			buffer->push_back({ curr,begin.getKey() });
	}
}

void Pickup::RangePickup()
{

	if (silentRangePickup) {
		std::vector<CInstanceBase*> vec;
		sdk->getPythonCharacterManager()->getPlayerList(&vec);

		if (vec.size() >0) {
			sdk->getPythonPlayer()->PickCloseItem();
			return;
		}

	}

	std::vector<ItemGround> items;
	getPickableItemsVector(&items);
	
	Point2D currPos;
	sdk->getPythonPlayer()->getPosition(currPos);
	ItemGround item;
	if (getValidClosestItem(&item,&items)) {
		DEBUG_INFO(COLOR_DEFAULT,"RANGE_PICKUP: Picking close items");
		Point2D itemPos = item.item->getItemPosition2D();
		CPythonNetwork* net = sdk->getPythonNetwork();

		net->SendCharacterStateMovePacket(itemPos, 0.5f);
		net->SendCharacterStatePacket(itemPos, 0.5f, FUNC_WAIT, 0);
		pickEveryItemInRange(itemPos, &items);
		net->SendCharacterStateMovePacket(currPos, 0.5f);
		net->SendCharacterStatePacket(itemPos, 0.5f, FUNC_WAIT, 0);
	}
}
