#include "DamagePlus.h"



DamagePlus::DamagePlus()
{
	dmgSpeed_MS = DEFAULT_DAMAGE_MS_SPEED;
	waitDmgRange = MEGA_WAIT_DMG_MAX_RANGE_ON_GROUND;
	ultraWaitDamage_SilentUse = true;
	ultraWaitDamageActive = false;
	ultraDamageAttackMoobsInWall = false;

	waitDamageToggle = false;
	isActive = false;
	selectedDamageSilent = true;
}


DamagePlus::~DamagePlus()
{
}

void DamagePlus::Start()
{

}

void DamagePlus::ThreadLoop()
{
	if (waitDamageToggle) {
		useMegaWaitDamage();
	}

	if (isActive) {
		useDMGHackOnSelectedInstance();
	}
}

void DamagePlus::Stop()
{
	waitDamageToggle = false;
	isActive = false;
}

bool DamagePlus::isMegaWaitDamageActive()
{
	return ultraWaitDamageActive;
}

void DamagePlus::setSilentWaitDMG(bool var)
{
	ultraWaitDamage_SilentUse = var;
}

void DamagePlus::setSilentSelectedDMG(bool var)
{
	selectedDamageSilent = var;
}

void DamagePlus::startWaitDamage()
{
	waitDamageToggle = true;
	ultraWaitDamageActive = true;
}

void DamagePlus::stopWaitDamage()
{
	waitDamageToggle = false;
	ultraWaitDamageActive = false;
}

void DamagePlus::startDmgSelectdInstance()
{
	isActive = true;
}

void DamagePlus::stopDmgSelectedInsatnce()
{
	isActive = false;
}

void DamagePlus::useDMGHackOnSelectedInstance()
{
	static DWORD nextTime = GetTickCount();

	DWORD elapsedTime = GetTickCount() - nextTime;
	if (elapsedTime < dmgSpeed_MS)
		return;
	nextTime = GetTickCount();

	CPythonNetwork* net = sdk->getPythonNetwork();
	CInstanceBase* base = net->getSelectedInstance();
	if (!base)
		return;

	std::vector<CInstanceBase*> players;
	sdk->getPythonCharacterManager()->getPlayerList(&players);

	if (selectedDamageSilent && players.size()>0) {
		return;
	}

	if (!base->isMonsterEnemy() || base->isDead()) {
		return;
	}

	/*static int counter = 9;
	if (!counter) {
		nextTime += 400;
		counter = 9;
		return;
	}
	counter--;*/
	Point2D enemyPos;
	Point2D myPos;
	base->getPosition(enemyPos);
	sdk->getPythonPlayer()->getPosition(myPos);

	if (sdk->getPythonBackground()->isLocationBlocked(enemyPos.x, enemyPos.y)) {
		return;
	}

	net->SendCharacterStateAttackPacket(enemyPos, 0.2, FIRST_HORSE_ATTACK); //Might be possible to make shorter
	//net->SendCharacterStatePacket(enemyPos, 0.2, FUNC_WAIT, 0);
	net->SendBattleAttack(0, base->getVID());

	//net->SendCharacterStatePacket(enemyPos, 0.2, FUNC_WAIT, 0);
	net->SendCharacterStateMovePacket(myPos, 0.2f);
	DEBUG_INFO(COLOR_DEFAULT, "DMG_HACK: Packet Sent to VID: %d, Instance %#x,  ElapsedTime: %d", base->getVID(), base, elapsedTime);
}

void DamagePlus::useDMGHackSmart()
{
	static DWORD nextTime = GetTickCount();

	DWORD elapsedTime = GetTickCount() - nextTime;
	if (elapsedTime < SMART_DMG_WAIT)
		return;

	CPythonCharacterManager* manager = sdk->getPythonCharacterManager();
	CPythonPlayer* player = sdk->getPythonPlayer();

	auto begin = manager->getInstanceMap()->begin();
	auto end = manager->getInstanceMap()->end();


	CPythonNetwork* net = sdk->getPythonNetwork();
	CInstanceBase* selectedInstance = net->getSelectedInstance();
	CInstanceBase* mainInstance = player->getMainInstance();
	if (!selectedInstance)
		return;

	for (; begin != end; ++begin) {
		CInstanceBase* target = begin.getValue();
		float dist = player->distanceToInstance(target);
		if (dist < MAX_DISTANCE_TO_ATTACK) {
			if (target != selectedInstance && target != mainInstance && !target->isDead()) {
					DEBUG_INFO(COLOR_DEFAULT, "DMG_HACK: Sending Packet");
					net->SendBattleAttack(0, target->getVID());
					net->SendBattleAttack(0, selectedInstance->getVID());
			}
		}
	}
	nextTime = GetTickCount();
}

//Can be imporved
void DamagePlus::useMegaWaitDamage()
{
	static DWORD nextTime = GetTickCount();

	DWORD elapsedTime = GetTickCount() - nextTime;
	if (elapsedTime < MEGA_WAIT_DMG_WAIT)
		return;

	nextTime = GetTickCount();

	CPythonCharacterManager* manager = sdk->getPythonCharacterManager();
	CPythonPlayer* player = sdk->getPythonPlayer();
	CPythonNetwork* net = sdk->getPythonNetwork();
	CPythonBackground* background = sdk->getPythonBackground();

	auto map = manager->getInstanceMap();
	auto begin = map->begin();
	auto end = map->end();
	

	std::vector<MonsterHit> enemyList;
	for (; begin != end; ++begin) {
		CInstanceBase* target = begin.getValue();

		//If any player close, dont send packets
		if (ultraWaitDamage_SilentUse && target->isPlayerOrGM() && target != manager->getMainInstance()) {
			ultraWaitDamageActive = false;
			return;
		}
		else {
			ultraWaitDamageActive = true;
		}
		
		if (target->isMonsterEnemy()) {

			if (!target->isDead()) {
				enemyList.push_back({ target,false });
			}
		}
	}
	if (player->IsMountingHorse())
		waitDmgRange = MEGA_WAIT_DMG_MAX_RANGE_ON_HORSE;
	else
		waitDmgRange = MEGA_WAIT_DMG_MAX_RANGE_ON_GROUND;

	static Point2D oldPos = {};
	player->getPosition(oldPos);

	Point2D lastInstancePosition = oldPos;
	int packetCounter = 0;

	if (enemyList.size() < 1)
		return;

	for (MonsterHit & it : enemyList) {
		CInstanceBase* target = it.monster;
		if (it.isHit)
			continue;

		Point2D currTargetPosition;
		target->getPosition(currTargetPosition);

		//Check for moob inside wall
		if (!ultraDamageAttackMoobsInWall) {
			if (background->isLocationBlocked(currTargetPosition.x, currTargetPosition.y)) {
				continue;
			}
		}
		float rot = player->calculateRotationToInstance(target);
		float dist = oldPos.distance(&currTargetPosition);

		if (dist < waitDmgRange && lastInstancePosition.distance(&currTargetPosition) < waitDmgRange) {
			DEBUG_INFO(COLOR_DEFAULT, "MEGA_WAIT_HACK: teleporting to VID: %d",target->getVID());
			packetCounter += 6;
			if (packetCounter >= MEGA_WAIT_DMG_MAX_PACKETS) {
				DEBUG_INFO(COLOR_RED, "MEGA_WAIT_HACK: Max Packets Reached -> Skiping");
				net->SendCharacterStateMovePacket(oldPos, 0.2);
				//net->SendCharacterStatePacket(currTargetPosition, rot, FUNC_WAIT, 0);
				return;
			}

			//net->SendCharacterStateMovePacket(currTargetPosition, rot);
			net->SendCharacterStateAttackPacket(currTargetPosition, rot, FIRST_HORSE_ATTACK); //Might be possible to make shorter
			//net->SendCharacterStatePacket(currTargetPosition, rot, FUNC_WAIT, 0);

			packetCounter += sendAttackToEveryMonsterClose(currTargetPosition, enemyList, MEGA_WAIT_DMG_MAX_PACKETS - packetCounter);
			lastInstancePosition = currTargetPosition;
		}
	}
	DEBUG_INFO(COLOR_DEFAULT, "\n");
	net->SendCharacterStateMovePacket(oldPos, 0.2);
	//net->SendCharacterStatePacket(oldPos, 0.2, FUNC_WAIT, 0);
}

int DamagePlus::sendAttackToEveryMonsterClose(Point2D &a ,std::vector<MonsterHit>& enemyList, int maxPacketsAllowed)
{
	CPythonCharacterManager* manager = sdk->getPythonCharacterManager();
	CPythonPlayer* player = sdk->getPythonPlayer();
	CPythonNetwork* net = sdk->getPythonNetwork();

	int packetCounter = 0;
	for (MonsterHit & it : enemyList) {
		CInstanceBase* target = it.monster;
		if (it.isHit)
			continue;
		Point2D targetPos;
		target->getPosition(targetPos);
		targetPos.absoluteY();
		float dist = a.distance(&targetPos);
		if (dist < MAX_DISTANCE_TO_ATTACK) {
			net->SendBattleAttack(0, target->getVID());
			//DEBUG_INFO(COLOR_DEFAULT, "Sending attack to VID: %d", target->getVID());
			it.isHit = true;
			packetCounter++;
			if (packetCounter >= maxPacketsAllowed)
				return packetCounter;
		}
	}
	return packetCounter;
}

