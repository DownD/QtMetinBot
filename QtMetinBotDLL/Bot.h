#pragma once
#include "MetinSDK.h"
#include "FarmBot.h"
#include "FishingBot.h"
#include "Pickup.h"
#include "ItemUser.h"
#include <thread>
#include "JMPHook.h"
#include "Util.h"
#include "DamagePlus.h"
#include "BotProtectionBypass.h"
#include "NetworkProcessHook.h"
#include "SleepFunctionHook.h"
#include "ExpBot.h"
#include "SkillUser.h"


#define BOT_PROTECTION_STRING "AntiBotKod"
class Bot
{
protected:
	Bot(MetinSDK * sdk);
public:
	~Bot();

	void hookMainGameFunction();
	void unHookMainGameFunction();

	void hookSendChatPacket();
	void unHookSendChatPacket();


	//DO NOT EXECUTE THIS FUNCTION
	void hookLoop();

	FarmBot* getFarmBot();
	Pickup* getPickup();
	DamagePlus* getDmgHack();
	FishingBot* getFishingBot();
	ExpBot* getExpBot();
	SkillUser* getSkillBot();
	ItemUser* getItemUser();

	bool selectFishingBot();
	bool selectExpBot();
	bool selectFarmBot();

	bool startSelectedBot();
	bool stopSelectedBot();

	void injectPythonFileFromMainThread(char* path);

	//Singleton
	static Bot* getInstance();
	static Bot* createInstance(MetinSDK * sdk);
	static void destroy();

	MetinSDK* getSDK();

private:
	bool selectBotMode(BotMode* mode);

	static void __cdecl redirectionMainFunction();
	static void __cdecl sendChatPacketHook(char* commandLine);
private:

	BotMode* selectedMode;

	DamagePlus* dmgHack;
	ItemUser* general;
	Pickup* pickup;
	FarmBot* farmBot;
	FishingBot* fishBot;
	ExpBot* expBot;
	SkillUser* skillBot;
	BotProtectionBypass* bypass;
	HookFeature* mainHook;

	Hook* sendChatPacket;

	bool injectPython;
	std::string path;

	static Bot* instance;
	MetinSDK* sdk;
};


