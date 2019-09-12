#include "FarmBot.h"

#define FARM_BOT_MS_WAIT 200
#define STATE_SEARCHING 1
#define STATE_GOING_TO_METIN 2
#define STATE_ATTACKING_METIN 3
#define STATE_METIN_DEAD 4

#define METIN_DEAD_TIME_WAIT 2000
#define HORSE_SKILL_WAIT_TIME 6000

FarmBot::FarmBot()
{ 
	noSteal = 1;
	isActive = 0;
	currentState = 0;
	attackBossFirst = 1; 
	targetIsBoss = 0;
}


FarmBot::~FarmBot()
{
}

void FarmBot::Start()
{
	DEBUG_INFO(COLOR_DEFAULT, "FARMBOT: Starting FarmBot");
	SetState(STATE_SEARCHING);
	lastTimeLoop = GetTickCount();
	target = 0;
	stateTimeCounter = GetTickCount();
	isActive = 1;
}

void FarmBot::ThreadLoop()
{
	if (!isActive) return;
	if (GetTickCount() - lastTimeLoop < FARM_BOT_MS_WAIT)
		return;

	//Timer per state, avoids any stuck position
	if (GetTickCount() > maxTimePerStateTick) {
		SetState(STATE_SEARCHING);
		skiped = target;
		target = nullptr;
	}


	switch (currentState) {
	case STATE_SEARCHING:
		StateSearching();
		break;
	case STATE_GOING_TO_METIN:
		StateWalkingToMetin();
		break;
	case STATE_ATTACKING_METIN:
		StateAttackingMetin();
		break;
	case STATE_METIN_DEAD:
		StateMetinDead();
		break;
	default:
		DEBUG_INFO(COLOR_RED, "FARMBOT: Farmbot state with invalid value, STATE_SEARCHING was set");
		SetState(STATE_SEARCHING);
	}
	lastTimeLoop = GetTickCount();
}

void FarmBot::Stop()
{
	isActive = 0;
	sdk->getPythonPlayer()->setAttack(0);

}

bool FarmBot::IsRunning()
{
	return isActive;
}

void FarmBot::StateSearching()
{
	target = getValidClosestMonster();
	if (target) {
		SetState(STATE_GOING_TO_METIN);
		Point2D a;
		target->getPosition(a);
		sdk->getPythonPlayer()->WalkToPosition(a);
		DEBUG_INFO(COLOR_DEFAULT, "FARMBOT: Metin Found: Address %#x , X: %f, Y: %f",target, a.x, a.y);
	}

}

void FarmBot::StateWalkingToMetin()
{
	if (!target) { SetState(STATE_SEARCHING); return; }
	Point2D a;
	target->getPosition(a);
	sdk->getPythonPlayer()->attackInstance(target);

#ifdef IMPERUS_SERVER
	SendChatSimulationPacket("/flexio_bot_pohyb OnMouseLeftButtonUp");
#endif

	if (GetTickCount() - stateTimeCounter > HORSE_SKILL_WAIT_TIME) {
		sdk->getPythonPlayer()->useSkill(SKILL_HORSE_ATTACK);
		stateTimeCounter = GetTickCount();
	}

	if (noSteal) {
		std::vector<CInstanceBase*> vec;
		sdk->getPythonCharacterManager()->getPlayerList(&vec);
		if (isPlayerNearInstance(target, &vec)) {
			SetState(STATE_SEARCHING); 
			return;
		}
	}

	if (sdk->getPythonPlayer()->distanceToInstance(target)< MAX_DISTANCE_TO_ATTACK) {
		DEBUG_INFO(COLOR_DEFAULT, "FARMBOT: Metin Reached, Attacking");
		sdk->getPythonPlayer()->attackInstance(target);
		SetState(STATE_ATTACKING_METIN);
	}
}

void FarmBot::StateAttackingMetin()
{
	if (!target) { SetState(STATE_SEARCHING); return; }
	sdk->getPythonPlayer()->attackInstance(target);
#ifdef IMPERUS_SERVER
	SendChatSimulationPacket("/flexio_bot_pohyb OnMouseRightButtonUp");
#endif
	if (sdk->getPythonPlayer()->distanceToInstance(target) > MAX_DISTANCE_TO_ATTACK) {
		SetState(STATE_GOING_TO_METIN);
		sdk->getPythonPlayer()->attackInstance(target);
	}
	if (target->isDead()) {
		DEBUG_INFO(COLOR_DEFAULT, "FARMBOT: Metin Dead");
		SetState(STATE_METIN_DEAD);
	}
}

void FarmBot::StateMetinDead()
{
	sdk->getPythonPlayer()->setAttack(0);
#ifdef IMPERUS_SERVER
	SendChatSimulationPacket("/flexio_bot_pohyb PickUpItem");
#endif
	if (GetTickCount() - stateTimeCounter > METIN_DEAD_TIME_WAIT) {
		DEBUG_INFO(COLOR_DEFAULT, "FARMBOT: Time elapsed after metin dead %d", GetTickCount() - stateTimeCounter);
		target = 0;
		SetState(STATE_SEARCHING);
	}
}

void FarmBot::SendChatSimulationPacket(const char * str)
{
	static DWORD timer = GetTickCount();
	if (timer > GetTickCount())
		return;
	sdk->getPythonNetwork()->SendChatPacket(str,0);
	timer = GetTickCount() + 11000 + (rand() % 6500);
}

void FarmBot::SetState(BYTE state)
{
	maxTimePerStateTick = GetTickCount() + MAX_TIME_PER_STATE;
	DEBUG_INFO(COLOR_DEFAULT, "FARMBOT: Moving to state %d ",state);
	currentState = state;
	stateTimeCounter = GetTickCount();
	/*
	if (state == STATE_METIN_DEAD && targetIsBoss) {
		int channel = 1 + (rand() % 4);
		std::string chChange("/ch ");
		chChange.append(std::to_string(channel));
		sdk->getPythonNetwork()->SendChatPacket(chChange.c_str(),0);
		stateTimeCounter += 5000;
	}
	*/

#ifdef IMPERUS_SERVER
	if (state == STATE_ATTACKING_METIN) {
		sdk->getPythonNetwork()->SendChatPacket("/flexio_bot_pohyb_aa",0);
	}
#endif
}

bool FarmBot::isPlayerNearInstance(CInstanceBase* instance, std::vector<CInstanceBase*> *vec) {
	CInstanceBase* main = sdk->getPythonCharacterManager()->getMainInstance();
	for (int i = 0;i< vec->size() ; i++) {
		CInstanceBase * current = vec->operator[](i);
		if (main == current) { continue; }
		float dist = instance->distanceToInstance(current);
		if (dist < MAX_DISTANCE_TO_ATTACK)
			return true;
	}

	return false;
}

CInstanceBase * FarmBot::getValidClosestMonster()
{
	CPythonCharacterManager* manager = sdk->getPythonCharacterManager();
	auto begin = manager->getInstanceMap()->begin();
	auto end = manager->getInstanceMap()->end();

	CInstanceBase * main = sdk->getPythonCharacterManager()->getMainInstance();
	CInstanceBase * buffer = 0;
	float distance = FLT_MAX;

	std::vector<CInstanceBase*> players;
	if (noSteal)
		manager->getPlayerList(&players);

	DEBUG_INFO(COLOR_DEFAULT,"Scanning %d Instances", manager->getInstanceMap()->getSize());

	for (; begin != end; ++begin) {
		CInstanceBase * current = begin.getValue();
		if (attackBossFirst && current->isBoss()) {
			//if (BossMap.find(current->getID()) != BossMap.end()) {
				targetIsBoss = true;
				return current;
			//}
		}

		if (!current->isMetin())
			continue;
		if (current->isDead())
			continue;
		float dist = main->distanceToInstance(current);
		if (dist > distance)
			continue;
		if (current == skiped)
			continue;
		if (noSteal) {
			if(isPlayerNearInstance(current, &players)) {continue;}
		}

		buffer = current;
		distance = dist;
	}

	targetIsBoss = false;
	return buffer;
}
