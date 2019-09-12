#pragma once
#include "BotFeature.h"


#define AURA_WAIT 250000
#define BRESERK_WAIT 200000

#define ENCHANTED_BLADE_WAIT 395000
#define BLACK_ARMOR_WAIT 250000
#define FEAR_WAIT 250000

#define SKILL_TIME_WAIT 500

#define STATE_UNMOUNT 1
#define STATE_MOUNT 2
#define STATE_USE_SKILL 3
#define STATE_WAITING 4

class SkillUser : public BotFeature
{
private:
	struct Skill {
		Skill(int timeWaitMs, int skillIndex);
		bool skillIsReady(int currTime);
		void setCurrTime(int currTime);
		void resetTimer();
		bool isActive;
		int timeWaitMs;
		int nextTime;
		int skillIndex;
	};
public:
	SkillUser();
	~SkillUser();

	void setupAuraAndBreserk();
	void setupSuraWeaponsSkills();
	void resetTimers();

	// Inherited via BotFeature
	virtual void Start() override;

	virtual void ThreadLoop() override;

	virtual void Stop() override;

private:


	void stateWaiting(int time);
	void stateMount();
	void stateUnmount();
	void stateUseSkill(int time);

private:
	bool isActive;
	std::vector<Skill> skills;
	Skill* currSkill = 0;
	BYTE state = STATE_WAITING;
};

