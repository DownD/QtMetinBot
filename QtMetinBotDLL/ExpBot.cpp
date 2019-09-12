#include "ExpBot.h"

#ifdef IMPERUS_SERVER

#define BOT_CONTROL_ARRAY_SIZE 7
const char* ImperusBotControlStrings[] = {
	"/flexio_bot_pohyb OnMouseRightButtonUp",
	"/flexio_bot_pohyb PickUpItem",
	"/flexio_bot_pohyb OnMouseLeftButtonUp",
	"/flexio_bot_pohyb MoveUp",
	"/flexio_bot_pohyb MoveLeft",
	"/flexio_bot_pohyb MoveDown",
	"/flexio_bot_pohyb MoveRight"
};

#endif

ExpBot::ExpBot(DamagePlus* waitDmg)
{
	this->waitDmg = waitDmg;
	isActive = false;
	range = MAXIMUM_RANGE;
	moveCenterIfNoTarget = true;
}


ExpBot::~ExpBot()
{
}

void ExpBot::Start()
{
	sdk->getPythonPlayer()->getPosition(start);
	isActive = true;
	DEBUG_INFO(COLOR_DEFAULT, "EXPBOT: Start Position X:%f  Y:%f",start.x,start.y);
}

void ExpBot::ThreadLoop()
{
	if (isActive) {
		static DWORD nextTime = GetTickCount();
		DWORD elapsedTime = GetTickCount() - nextTime;
		if (elapsedTime < SLEEP_TIME)
			return;

		nextTime = GetTickCount();
		useCape();
#ifdef IMPERUS_SERVER
		sendRandomBotSimulatePacket();
#endif

		CInstanceBase* closestTarget = getClosestMonster();
		if (!closestTarget) {
			DEBUG_INFO(COLOR_DEFAULT, "EXPBOT: No Target Found");
			if (moveCenterIfNoTarget)
				sdk->getPythonPlayer()->WalkToPosition(start);
			return;
		}
		if (waitDmg->isMegaWaitDamageActive()) {
			Point2D pos;
			closestTarget->getPosition(pos);
			sdk->getPythonPlayer()->WalkToPosition(pos);
			sdk->getPythonPlayer()->setAttack(0);
		}
		else {
			sdk->getPythonPlayer()->attackInstance(closestTarget);
		}
	}


}

void ExpBot::Stop()
{
	sdk->getPythonPlayer()->setAttack(0);
	isActive = false;
}

bool ExpBot::IsRunning()
{
	return isActive;
}

CInstanceBase * ExpBot::getClosestMonster()
{
	CPythonCharacterManager* manager = sdk->getPythonCharacterManager();
	auto begin = manager->getInstanceMap()->begin();
	auto end = manager->getInstanceMap()->end();

	CInstanceBase * main = sdk->getPythonCharacterManager()->getMainInstance();
	CInstanceBase * buffer = 0;
	float distance = FLT_MAX;

	DEBUG_INFO(COLOR_DEFAULT, "Scanning %d Instances", manager->getInstanceMap()->getSize());

	for (; begin != end; ++begin) {
		CInstanceBase * current = begin.getValue();
		if (!current->isMonsterEnemy())
			continue;
		if (current->isDead())
			continue;
		if (!isInRange(current))
			continue;
		float dist = main->distanceToInstance(current);
		if (dist > distance)
			continue;

		buffer = current;
		distance = dist;
		}

	return buffer;
}

void ExpBot::useCape()
{
	static DWORD time = GetTickCount();
	DWORD elapsedTime  = GetTickCount() -time;
	if (elapsedTime > CAPE_WAIT_TIME) {
		sdk->getPythonPlayer()->useItemIfAvailable(CAPE_ID);
		time = GetTickCount();
	}
}

bool ExpBot::isInRange(CInstanceBase * instance)
{
	Point2D b;
	instance->getPosition(b);
	if (start.distance(&b)<range) 
		return true;

	return false;
}
#ifdef IMPERUS_SERVER
void ExpBot::sendRandomBotSimulatePacket()
{
	static DWORD time = GetTickCount();
	if (time< GetTickCount()) {
		sdk->getPythonNetwork()->SendChatPacket(ImperusBotControlStrings[rand() % BOT_CONTROL_ARRAY_SIZE], 0);
		time = GetTickCount() + WAIT_TIME_BOT_PROTECTION + rand() % 5000;
	}
}
#endif