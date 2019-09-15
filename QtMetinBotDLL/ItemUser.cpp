#include "ItemUser.h"



ItemUser::ItemUser()
{
	isActive = 0;
}


ItemUser::~ItemUser()
{
}

void ItemUser::Start()
{
	timeSave = 0;
	isActive = 1;
	DEBUG_INFO(COLOR_DEFAULT, "ITEM_USER: Start");
}

void ItemUser::ThreadLoop()
{
	if (!isActive)
		return;

	DWORD tick = GetTickCount();
	if (timeSave + TIME_POTS < tick) {
		DEBUG_INFO(COLOR_DEFAULT, "ITEM_USER: Using Items");

		auto player = sdk->getPythonPlayer();
		player->useItemIfAvailable(DRAGON_GOD_DEFENCE);
		player->useItemIfAvailable(DRAGON_GOD_ATTACK);
		player->useItemIfAvailable(DRAGON_GOD_LIFE);
		player->useItemIfAvailable(PIERCING_STRIKE);
		player->useItemIfAvailable(CRITICAL_STRIKE);

		player->useItemIfAvailable(ORANGE_DEW);
		player->useItemIfAvailable(BLUE_DEW);
		player->useItemIfAvailable(RED_DEW);
		player->useItemIfAvailable(SAMBO_WATER);
		player->useItemIfAvailable(ZIN_WATER);

		//Elixer
		AutoPotionInfo blueElixer = { 0 };
		AutoPotionInfo redElixer = { 0 };
		player->getPotionInfo(0, &blueElixer);
		player->getPotionInfo(1, &redElixer);

		DEBUG_INFO(COLOR_DEFAULT, "ITEM_USER: SlotIndex-> %d  IsActive-> %d  TotalAmount-> %d  CurrentAmount-> %d", redElixer.inventorySlotIndex, redElixer.bActivated, redElixer.totalAmount, redElixer.currentAmount);

		if (!blueElixer.bActivated && blueElixer.totalAmount != 0)
			player->setPotionInfo(0,blueElixer);
		
		if (!redElixer.bActivated && redElixer.totalAmount != 0)
			player->setPotionInfo(1,redElixer);

		timeSave = tick;
	}
}

void ItemUser::Stop()
{
	isActive = 0;
	DEBUG_INFO(COLOR_DEFAULT, "ITEM_USER: Stop");
}
