#pragma once
#include "BotFeature.h"
#include "MetinSDK.h"


#define DEFAULT_DAMAGE_MS_SPEED 140
#define SMART_DMG_WAIT 400

#define MEGA_WAIT_DMG_WAIT 300
#define MEGA_WAIT_DMG_MAX_PACKETS 130
#define MEGA_WAIT_DMG_MAX_RANGE_ON_HORSE MAX_RANGE_TELEPORT_HORSE
#define MEGA_WAIT_DMG_MAX_RANGE_ON_GROUND MAX_RANGE_TELEPORT_GROUND

class DamagePlus : public BotFeature
{
public:
	DamagePlus();
	~DamagePlus();

	// Inherited via BotFeature
	virtual void Start() override;
	virtual void ThreadLoop() override;
	virtual void Stop() override;

	bool isMegaWaitDamageActive();
	void setSilentWaitDMG(bool var);
	void setSilentSelectedDMG(bool var);

	void startWaitDamage();
	void stopWaitDamage();

	void startDmgSelectdInstance();
	void stopDmgSelectedInsatnce();

private:
	struct MonsterHit {
		CInstanceBase* monster;
		bool isHit = 0;
	};

	void useDMGHackOnSelectedInstance();
	void useDMGHackSmart();
	void useMegaWaitDamage();

	//Return the number of packets sent
	int sendAttackToEveryMonsterClose(Point2D & a, std::vector<MonsterHit>& enemyList, int maxPacketsAllowed);

private:
	DWORD dmgSpeed_MS;
	int waitDmgRange;

	bool selectedDamageSilent;

	bool waitDamageToggle;
	bool ultraWaitDamage_SilentUse;
	bool ultraWaitDamageActive;
	bool ultraDamageAttackMoobsInWall;

	bool isActive;
};

