#pragma once
#include "HookFeature.h"
#include "JMPHook.h"
#include "Util.h"


#define BOT_PROTECTION_STRING "AntiBotKod"
#define BOT_SEND_COMMAND "/potvrzeni_kod "
#define FISHING_BOT_PROTECTION_RCV "AntiBotFishingMining"
#define FISHING_BOT_PROTECTION_SEND "/nejsem_bot " 

#define BOT_ATTACK_PROTECTION_WAIT_MAX_TIME 4000 
#define BOT_ATTACK_PROTECTION_WAIT_MIN_TIME 1500 

class BotProtectionBypass : public HookFeature
{
public:

	BotProtectionBypass();
	~BotProtectionBypass();

	void ThreadLoop() override;

private:

	static void __cdecl serverCommand(char* serverCmd);
	void bypassFarmBotProtection(const char * code);
	void bypassFishBotProtection(const char * code);


	Hook* setupHook();


private:
	static bool sendFarmCode;
	static bool sendFishCode;

	static std::string codeFarm;
	static std::string codeFish;

	static DWORD attackThickCount;
	static DWORD fishThickCount;
};

