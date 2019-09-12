#pragma once
#include "BotMode.h"
#include "DamagePlus.h"

#define CAPE_ID 70038
#define SLEEP_TIME 200
#define MAXIMUM_RANGE 5000
#define CAPE_WAIT_TIME 3000
#define WAIT_TIME_BOT_PROTECTION 13000 

class ExpBot : public BotMode
{
public:
	ExpBot(DamagePlus* waitDmg);
	~ExpBot();

	// Inherited via BotMode
	virtual void Start() override;
	virtual void ThreadLoop() override;
	virtual void Stop() override;
	virtual bool IsRunning() override;

private:
	CInstanceBase * getClosestMonster();
	void useCape();
	bool isInRange(CInstanceBase* instance);

#ifdef IMPERUS_SERVER
	//Imperus only
	void sendRandomBotSimulatePacket();
#endif

private:
	int range;
	bool isActive;
	Point2D start;
	bool moveCenterIfNoTarget;

	DamagePlus* waitDmg;


};

