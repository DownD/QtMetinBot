#include "Bot.h"
Bot* Bot::instance = 0;

Bot::Bot(MetinSDK * sdk)
{
	DEBUG_INFO(COLOR_DEFAULT, "Creating Bot Object");
	BotFeature::setSDK(sdk);
	this->sdk = sdk;
	pickup = new Pickup();
	farmBot = new FarmBot();
	general = new ItemUser();
	dmgHack = new DamagePlus();
	skillBot = new SkillUser();
	fishBot = new FishingBot();
	expBot = new ExpBot(dmgHack);
	mainHook = new NetworkProcessHook(redirectionMainFunction);
	bypass = 0;
	//mainHook = new SleepFunctionHook(redirectionMainFunction);

	sendChatPacket =  new JMPHook(sdk->getPythonNetwork()->getSendChatPacketAddr(), sendChatPacketHook, 7, THIS_CALL);
	selectedMode = 0;

	if (mainHook == 0) {
		MessageBox(NULL, L"Error Creating Main Hook", L"ERROR", MB_OK);
	}
	injectPython = false;
}

Bot::~Bot()
{
	mainHook->Stop();
	delete bypass;
	delete pickup;
	delete farmBot;
	delete general;
	delete dmgHack;
	delete mainHook;
	delete sendChatPacket;
	delete fishBot;
	delete expBot;
	delete skillBot;
	instance = 0;
}


bool Bot::selectBotMode(BotMode * mode)
{
	if (selectedMode && selectedMode->IsRunning()) {
		selectedMode->Stop();
	}
	selectedMode = mode; //Atomic type, so no undefined beahviour

	return true;
}

void Bot::redirectionMainFunction()
{
	instance->hookLoop();
}

void __cdecl Bot::sendChatPacketHook(char* commandLine)
{
	std::string str(commandLine);
	Bot::getInstance()->getSDK()->getPythonPlayer()->appendChat(commandLine);
}

void Bot::hookLoop()
{
	if (strcmp(GAME_PHASE,sdk->getPythonNetwork()->getPhase())!=0)
		return;

	skillBot->ThreadLoop();
	pickup->ThreadLoop();
	general->ThreadLoop();
	dmgHack->ThreadLoop();
	if(selectedMode)
		selectedMode->ThreadLoop();
#ifdef IMPERUS_SERVER
	bypass->ThreadLoop();
#endif
	if (injectPython) {
		if (PyRunFile((char*)path.c_str())) { DEBUG_INFO(COLOR_RED, "Error executing Python File"); }
		else{ DEBUG_INFO(COLOR_DEFAULT, "Python file executed with success"); }
		injectPython = false;
	}
}

void Bot::hookMainGameFunction() {
	mainHook->Start();
	if(bypass)
		bypass->Start();
	DEBUG_INFO(COLOR_DEFAULT,"Function hooked");
}

void Bot::unHookMainGameFunction() {
	if (bypass)
		bypass->Stop();
	mainHook->Stop();
	DEBUG_INFO(COLOR_DEFAULT, "Function unhooked");
}

void Bot::hookSendChatPacket()
{
	if(sendChatPacket)
		sendChatPacket->HookFunction();
}

void Bot::unHookSendChatPacket()
{
	if (sendChatPacket)
		sendChatPacket->UnHookFunction();
}

FarmBot * Bot::getFarmBot()
{
	return farmBot;
}

Pickup * Bot::getPickup()
{
	return pickup;
}

DamagePlus * Bot::getDmgHack()
{
	return dmgHack;
}

FishingBot * Bot::getFishingBot()
{
	return fishBot;
}

ExpBot * Bot::getExpBot()
{
	return expBot;
}

SkillUser * Bot::getSkillBot()
{
	return skillBot;
}

ItemUser * Bot::getItemUser()
{
	return general;
}

bool Bot::selectFishingBot()
{
	return selectBotMode(fishBot);
}

bool Bot::selectExpBot()
{
	return selectBotMode(expBot);
}

bool Bot::selectFarmBot()
{
	return selectBotMode(farmBot);
}

bool Bot::startSelectedBot()
{
	if (selectedMode)
		selectedMode->Start();

	return true;
}

bool Bot::stopSelectedBot()
{
	if (selectedMode)
		selectedMode->Stop();

	return true;
}

void Bot::injectPythonFileFromMainThread(char * path)
{
	injectPython = true;
	this->path = path;
}

Bot * Bot::getInstance()
{
	return instance;
}

Bot * Bot::createInstance(MetinSDK * sdk)
{
	if (instance != 0)
		return getInstance();
	Bot* bot = new Bot(sdk);
	instance = bot;
	return bot;
}

void Bot::destroy()
{
	if (instance)
		delete instance;
}

MetinSDK * Bot::getSDK()
{
	return sdk;
}
