#include <process.h> 
#include "MetinSDK.h"
#include "Bot.h"
#include "CMD.h"
#include "QtMetinBot.h"
#include <QtWidgets/QApplication>

#ifdef NADA
#define WRITE_FILE
#define WRITE_CONSOLE
#define TEST_MODE
#endif

#ifdef _DEBUG
#define WRITE_CONSOLE
#endif

HMODULE Module;
MetinSDK *sdk;

void Leave() {
	Bot::destroy();
	delete sdk;

	fclose(stdin);
	fclose(stdout);
	fclose(stderr);
	FreeConsole();
	FreeLibraryAndExitThread(Module, 0);
}

void SetupConsole()
{
	AllocConsole();
	freopen("CONOUT$", "wb", stdout);
	freopen("CONOUT$", "wb", stderr);
	freopen("CONIN$", "rb", stdin);
	SetConsoleTitle(L"Debug Console");
}

void Init()
{
#ifdef _DEBUG
	SetupConsole();
#endif
	sdk = new MetinSDK(Module);
#ifdef TEST_MODE
	CMD *cmd = CMD::createInstance(sdk);
	cmd->Init(Module);
	return false;
#endif

	//SAfer way to hook would be better
	Bot* bot = Bot::createInstance(sdk);
	bot->hookMainGameFunction();
	DEBUG_INFO(COLOR_GREEN,"Initiating GUI");
	
	int argc = 0;
	char argv[1][1] = { {} };
	//QApplication app()
	QApplication a(argc, (char**)argv);
	QtMetinBot w(bot);
	w.show();
	DEBUG_INFO(COLOR_GREEN, "GUI sucessfuly Initiated");
	a.exec();
}

DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	Init();
	Leave();
	return true;
}

BOOL WINAPI DllMain(_In_ HINSTANCE hinstDLL,_In_ DWORD     fdwReason,_In_ LPVOID    lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		Module = (HMODULE)hinstDLL;
		CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
		break;
	case DLL_THREAD_ATTACH: break;
	case DLL_THREAD_DETACH: break;
	case DLL_PROCESS_DETACH:
		Leave();
		break;
	}

	return TRUE;
}