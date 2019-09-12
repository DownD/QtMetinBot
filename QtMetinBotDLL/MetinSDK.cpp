#include "MetinSDK.h"
#include "DebugInfo.h"
#include "Memory.h"



MetinSDK::MetinSDK(HMODULE hMod)
{
	if(Initialize(hMod)) DEBUG_INFO(COLOR_DEFAULT, "SDK successfully set");
	
}




MetinSDK::~MetinSDK()
{
	delete PythonPlayer;
	delete PythonCharacterManager;
	delete PythonNetwork;
	delete PythonBackground;
}


bool MetinSDK::Initialize(HMODULE hMod)
{
	Memory* mem;
	try {
		mem = new Memory(hMod);
	}
	catch (std::exception &e) {
		DEBUG_INFO(COLOR_RED, "Error Initializing Memory Module");
		system("pause");
		return 0;
	}
	CInstanceBase::Initialize(mem);
	PythonCharacterManager = new CPythonCharacterManager(mem);
	PythonNetwork = new CPythonNetwork(mem, PythonCharacterManager);
	PythonPlayer = new CPythonPlayer(PythonCharacterManager,PythonNetwork, mem);
	PythonBackground = new CPythonBackground(mem);
	PythonItem = new CPythonItem(mem,PythonPlayer);
	delete mem;
#ifdef _DEBUG
	system("pause");
#endif
	return 1;
}
