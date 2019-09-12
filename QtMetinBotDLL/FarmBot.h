#pragma once
#include "MetinSDK.h"
#include "BotMode.h"


#define MAX_TIME_PER_STATE 60000
class FarmBot : public BotMode
{
public:
	FarmBot();
	~FarmBot();

	void Start();
	void ThreadLoop();
	void Stop();
	bool IsRunning();

private:
	

	void StateSearching();
	void StateWalkingToMetin();
	void StateAttackingMetin();
	void StateMetinDead();

	void SendChatSimulationPacket(const char* str);

	void SetState(BYTE state);

	CInstanceBase* getValidClosestMonster();
	bool isPlayerNearInstance(CInstanceBase* instance, std::vector<CInstanceBase*> *vec);

private:
	bool noSteal;
	bool attackBossFirst;

	BYTE currentState;
	CInstanceBase * target;
	bool targetIsBoss;
	bool isActive;
	DWORD lastTimeLoop;
	DWORD stateTimeCounter;
	CInstanceBase * skiped;

	DWORD maxTimePerStateTick;
};

