#pragma once
#include "MetinSDK.h"
#include "DebugInfo.h"
#include <vector>
#include "Util.h"
#include "JMPHook.h"
#include "HookCommand.h"


#define IMPERUS_HOOK_OFFSET 32
#define IMPERUS_RECV_SIZE_EBP_OFFSET 0x8
#define IMPERUS_RECV_BUFFER_EBP_OFFSET 0xC
class CMD
{
protected:
	CMD(MetinSDK *sdk);
public:
	~CMD();

public:

	void Init(HMODULE hMod);

	//Singleton
	static CMD* getInstance();
	static CMD* createInstance(MetinSDK* sdk);




private:
	void cmdMainLoop();
	void printOptions();

	void testPythonCharacterPlayer();
	void testInstanceBase();
	void testPythonPlayer();
	void testRecvIntercept();
	void testNetwork();
	void testPythonBackground();
	void testPythonItem();

	void printInstance(CInstanceBase * instance);

	static void redirectRecvFunction();
	static void InterceptRecvFunction(int size, void * buffer);


	static void __cdecl CommandLine(char* buffer);
	static void __cdecl SendChatPacketHook(char* buffer);
	static void __cdecl SendChatPacketHookInGamePrint(const char* buffer) { CMD::getInstance()->PrintInGame(buffer); }
	Hook* createHook();

	void PrintInGame(const char* str) { sdk->getPythonPlayer()->appendChat(str); }

private:
	MetinSDK* sdk;
	Hook* recvFunctionHook;
	static CMD* instance;

};

