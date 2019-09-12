#include "SkillUser.h"



SkillUser::SkillUser()
{
	state = STATE_WAITING;
	isActive = 0;
	setupAuraAndBreserk();
}


SkillUser::~SkillUser()
{
	Stop();
}

void SkillUser::Start()
{
	state = STATE_WAITING;
	isActive = true;
	resetTimers();
	DEBUG_INFO(COLOR_DEFAULT,"SKILL_USER: Start");
}

void SkillUser::ThreadLoop()
{
	if (!isActive)
		return;
	int currTime = GetTickCount();
	static int nextTime = 0;
	if (nextTime + SKILL_TIME_WAIT < currTime) {
		nextTime = currTime;


		switch (state) {
		case STATE_WAITING:
			stateWaiting(currTime);
			break;
		case STATE_MOUNT:
			stateMount();
			break;
		case STATE_UNMOUNT:
			stateUnmount();
			break;
		case STATE_USE_SKILL:
			stateUseSkill(currTime);
			break;
		default:
			state = STATE_WAITING;
		}
	}
}

void SkillUser::Stop()
{
	isActive = false;
	DEBUG_INFO(COLOR_DEFAULT, "SKILL_USER: Stop");
}

void SkillUser::setupSuraWeaponsSkills()
{
	skills.clear();
	Skill enchanted_blade(ENCHANTED_BLADE_WAIT,3);
	Skill black_armour(BLACK_ARMOR_WAIT, 5);
	Skill fear(FEAR_WAIT, 4);

	enchanted_blade.isActive = true;
	black_armour.isActive = true;
	fear.isActive = true;
	skills.push_back(enchanted_blade);
	skills.push_back(black_armour);
	skills.push_back(fear);
}

void SkillUser::resetTimers()
{
	for (auto skill : skills) {
		skill.resetTimer();
	}
}

void SkillUser::setupAuraAndBreserk()
{
	skills.clear();
	Skill aura(AURA_WAIT, 4);
	Skill breserk(BRESERK_WAIT, 3);

	aura.isActive = true;
	breserk.isActive = true;
	skills.push_back(aura);
	skills.push_back(breserk);
}

void SkillUser::stateWaiting(int time)
{
	//DEBUG_INFO(COLOR_DEFAULT, "SKILL_USER: Loop Waiting");

	static int waitFrame = 0;

	//Wait for skill to finish
	if (waitFrame) {
		waitFrame--;
		return;
	}


	for (Skill & skill : skills) {
		if (skill.skillIsReady(time)) {
			DEBUG_INFO(COLOR_DEFAULT, "SKILL_USER: Skill Index-> %d, Skill.LastTime-> %d, Skill.WaitTime-> %d, CurrTime: %d", skill.skillIndex, skill.nextTime, skill.timeWaitMs, time);
			currSkill = &skill;
			if (sdk->getPythonPlayer()->IsMountingHorse()) {state = STATE_UNMOUNT;}
			else { sdk->getPythonPlayer()->useSkill(currSkill->skillIndex); currSkill->setCurrTime(time); waitFrame = 4; }
			DEBUG_INFO(COLOR_DEFAULT, "SKILL_USER: Using Skill");
			return;
		}

	}
}

void SkillUser::stateMount()
{
	sdk->getPythonPlayer()->mountHorse();
	DEBUG_INFO(COLOR_DEFAULT, "SKILL_USER: Mounting");
	state = STATE_WAITING;
}

void SkillUser::stateUnmount()
{
	sdk->getPythonPlayer()->unMountHorse();
	state = STATE_USE_SKILL;
	DEBUG_INFO(COLOR_DEFAULT, "SKILL_USER: Unmounting");
}

void SkillUser::stateUseSkill(int time)
{
	sdk->getPythonPlayer()->useSkill(currSkill->skillIndex);
	currSkill->setCurrTime(time);
	DEBUG_INFO(COLOR_DEFAULT, "SKILL_USER: Using Skill after unmount");
	state = STATE_MOUNT;
}

SkillUser::Skill::Skill(int timeWaitMs, int skillIndex)
{
	this->timeWaitMs = timeWaitMs;
	this->skillIndex = skillIndex;
	isActive = 0;
	nextTime = 0;
}

bool SkillUser::Skill::skillIsReady(int currTime)
{
	if (isActive && (nextTime <= currTime))
		return true;
	return false;
}

void SkillUser::Skill::setCurrTime(int currTime)
{
	nextTime = currTime + timeWaitMs;
}

void SkillUser::Skill::resetTimer()
{
	nextTime = 0;
}
