#pragma once
#include "BotMode.h"


#define TIME_WAIT 200

#define MAX_TIME_WAITING_FISH 50000
#define TIME_WAIT_TO_PUSH_ROD 2200

#define WAITING_TO_HOOK 1
#define FISH_HOOKED 2
#define USING_BATE 3

#define BATE_ID 27801
class FishingBot : public BotMode
{
public:
	FishingBot();
	virtual ~FishingBot();

	// Inherited via BotMode
	void Start() override;
	void ThreadLoop() override;
	void Stop() override;
	bool IsRunning() override;

private:
	void RodAction();
	void UseBait();
	bool isFishHooked();

	void changeState(BYTE state);

	void simulateClicks();


private:
	int frameTime;

	BYTE state;
	bool isActive;
	bool attackSet;

	int timer;

	int timeWaitUntilPush;
};

