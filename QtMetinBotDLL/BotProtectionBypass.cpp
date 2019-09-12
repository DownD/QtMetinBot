#include "BotProtectionBypass.h"


bool BotProtectionBypass::sendFarmCode = false;;
std::string BotProtectionBypass::codeFarm = "";
DWORD BotProtectionBypass::attackThickCount = 0;

bool BotProtectionBypass::sendFishCode = 0;
std::string BotProtectionBypass::codeFish = "";
DWORD BotProtectionBypass::fishThickCount = 0;

BotProtectionBypass::BotProtectionBypass() : HookFeature(setupHook())
{
}


BotProtectionBypass::~BotProtectionBypass()
{
}


void BotProtectionBypass::bypassFarmBotProtection(const char * code)
{
	std::string str = BOT_SEND_COMMAND;
	str.append(code);
	DEBUG_INFO(COLOR_DEFAULT, "BYPASS_ATTACK_PROTECTION: Sending Combination: %s", str.data());
	sdk->getPythonNetwork()->SendChatPacket(str.data(), 0);
}

void BotProtectionBypass::bypassFishBotProtection(const char * code)
{
	std::string str = FISHING_BOT_PROTECTION_SEND;
	str.append(code);
	DEBUG_INFO(COLOR_DEFAULT, "BYPASS_FISHING_PROTECTION: Sending Combination: %s", str.data());
	sdk->getPythonNetwork()->SendChatPacket(str.data(), 0);
}

void BotProtectionBypass::ThreadLoop()
{
	DWORD tic = GetTickCount();
	if (sendFarmCode) {
		if (!codeFarm.empty()) {

			if (attackThickCount < tic) {
				sendFarmCode = false;
				bypassFarmBotProtection(codeFarm.data());
				sendFarmCode = false;
			}
		}
	}

	if (sendFishCode) {
		if (!codeFish.empty()) {
			if (fishThickCount < tic) {
				sendFishCode = false;
				bypassFishBotProtection(codeFish.data());
				sendFishCode = false;
			}
		}
	}



}

Hook * BotProtectionBypass::setupHook()
{
	return new JMPHook((void*)((int)sdk->getPythonNetwork()->getRecvServerCommandAddr()), serverCommand, 6,THIS_CALL);
}


void __cdecl BotProtectionBypass::serverCommand(char * serverCmd)
{
	int len = strnlen_s(serverCmd, 120);
	if (len < strlen(BOT_PROTECTION_STRING))
		return;

	std::vector<std::string> vec;
	split(serverCmd, ' ', &vec);
	if (vec.size() < 2)
		return;

	if (!vec.at(0).compare(BOT_PROTECTION_STRING)) {

		//avoid spam while packet travels
		static DWORD lastSentCode = 0;
		if (GetTickCount() - lastSentCode >= 2000) {

			if (!sendFarmCode) {
				std::string str = vec.at(1);
				std::vector<std::string> vec1;
				split((char*)str.data(), '#', &vec1);

				std::string code = vec1.at(1);
				if (code.size() <= 5) {

					attackThickCount = GetTickCount() + (rand() % (BOT_ATTACK_PROTECTION_WAIT_MAX_TIME - BOT_ATTACK_PROTECTION_WAIT_MIN_TIME) + BOT_ATTACK_PROTECTION_WAIT_MIN_TIME);
					sendFarmCode = true;
					lastSentCode = GetTickCount();
					codeFarm = code;
				}
			}
		}
	}

	if (!vec.at(0).compare(FISHING_BOT_PROTECTION_RCV)) {
		//avoid spam while packet travels
		static DWORD lastSentCode = 0;
		if (GetTickCount() - lastSentCode >= 2000) {

			if (sendFishCode)
				return;

			std::string str = vec.at(1);
			fishThickCount = GetTickCount() + (rand() % (BOT_ATTACK_PROTECTION_WAIT_MAX_TIME - BOT_ATTACK_PROTECTION_WAIT_MIN_TIME) + BOT_ATTACK_PROTECTION_WAIT_MIN_TIME);
			sendFishCode = true;
			lastSentCode = GetTickCount();
			codeFish = vec.at(1);
		}

	}
	return;

}
