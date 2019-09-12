#include "FishingBot.h"



FishingBot::FishingBot() : state(0), isActive(0), frameTime(TIME_WAIT), attackSet(0), timeWaitUntilPush(TIME_WAIT_TO_PUSH_ROD)
{
}


FishingBot::~FishingBot()
{
}

void FishingBot::Start()
{
	changeState(USING_BATE);
	isActive = 1;
	attackSet = 0;
	timer = 0;
}

void FishingBot::ThreadLoop()
{
	if (!isActive)
		return;

	static DWORD lastTick = GetTickCount();
	DWORD currTick = GetTickCount();

	if (currTick - lastTick < frameTime)
		return;
#ifdef IMPERUS_SERVER
	simulateClicks();
#endif

	lastTick = GetTickCount();
	if(attackSet)
		sdk->getPythonPlayer()->setAttack(0);

	if (timer > currTick)
		return;

	static DWORD timeMax = MAX_TIME_WAITING_FISH + currTick;
	switch (state) {
	case  WAITING_TO_HOOK:
		if (isFishHooked()) {
			changeState(FISH_HOOKED);
			timer = currTick + TIME_WAIT_TO_PUSH_ROD + ((rand() % 250) - 125);
			break;
		}
		if (timeMax < currTick) {
			changeState(USING_BATE);
			timer = currTick + 1000 + ((rand() % 250) - 125);
		}
		break;
	case  FISH_HOOKED:
		RodAction();
		timer = currTick + 5000 + (rand() % 1500);
		changeState(USING_BATE);
		break;
	case  USING_BATE:
		UseBait();
		RodAction();
		changeState(WAITING_TO_HOOK);
		timeMax = MAX_TIME_WAITING_FISH + currTick;
		break;

	default:
		changeState(USING_BATE);
	}

}

void FishingBot::Stop()
{
	isActive = 0;
	attackSet = 0;
}

bool FishingBot::IsRunning()
{
	return isActive;
}

void FishingBot::RodAction()
{
	sdk->getPythonPlayer()->setAttack(1);
	attackSet = true;
#ifdef IMPERUS_SERVER
	sdk->getPythonNetwork()->SendChatPacket("/flexio_bot_pohyb MoveUp",0);
#endif
}

void FishingBot::UseBait()
{
	sdk->getPythonPlayer()->useItemIfAvailable(BATE_ID);
}

bool FishingBot::isFishHooked()
{
	return !sdk->getPythonPlayer()->isPossibleEmiticon();
}

void FishingBot::changeState(BYTE state)
{
	DEBUG_INFO(COLOR_DEFAULT, "FISHBOT: Changing from  state %d to state %d", this->state, state);
	this->state = state;
}

void FishingBot::simulateClicks()
{
	static DWORD nextTime = 0;

	if (nextTime < GetTickCount()) {
		sdk->getPythonNetwork()->SendChatPacket("/flexio_bot_pohyb OnMouseRightButtonUp",0);
		nextTime = GetTickCount() + 12000 + (rand() % 20000);
	}
}
