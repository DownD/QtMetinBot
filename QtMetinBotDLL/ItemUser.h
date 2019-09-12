#pragma once
#include "MetinSDK.h"
#include "BotFeature.h"


#define DRAGON_GOD_DEFENCE 71030
#define DRAGON_GOD_ATTACK 71028
#define DRAGON_GOD_LIFE 71027
#define PIERCING_STRIKE 71045
#define CRITICAL_STRIKE 71044

#define GREEN_POTION_M 27101 //Or 27111 
#define PINK_POTION_M 27104
#define RED_DEW 50821
#define ORANGE_DEW 50822
#define YELLOW_DEW 50823
#define GREEN_DEW 50824
#define BLUE_DEW 50825

#define SAMBO_WATER 50818
#define ZIN_WATER 50817

#define ENCHANT_ITEM 71084
#define GREEN_CHANGER 71151

#define TIME_POTS 30000


class ItemUser : public BotFeature
{
public:
	ItemUser();
	~ItemUser();

	// Inherited via BotFeature
	void Start() override;
	void ThreadLoop() override;
	void Stop() override;


private:
	DWORD timeSave;
	bool isActive;
};

