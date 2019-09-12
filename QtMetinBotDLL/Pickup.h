#pragma once
#include "BotFeature.h"
#include <vector>

#define NORMAL_MAX_RANGE_PICKUP 600

class Pickup : public BotFeature
{
public:
	Pickup();
	~Pickup();

	// Inherited via BotFeature
	void Start() override;
	void ThreadLoop() override;
	void Stop() override;

	inline void useRangePickup() { isRangeActive = true; }
	inline void stopRangePickup() { isRangeActive = false; }

	void setSilentUse(bool var);

private:
	bool getValidClosestItem(ItemGround* buffer, std::vector<ItemGround> * groundItems);
	void pickEveryItemInRange(Point2D player, std::vector<ItemGround> * groundItems);
	void getPickableItemsVector(std::vector<ItemGround> * buffer);



	void RangePickup();

private:
	bool isNormalActive;
	bool checkOwnership;
	bool silentRangePickup;

	DWORD lastTimeLoop;


	bool isRangeActive;
	const float maxRangeTeleport = MAX_RANGE_TELEPORT_GROUND;
	const int maxRangePick = NORMAL_MAX_RANGE_PICKUP;

};

