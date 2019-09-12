#pragma once
#include "CInstanceBase.h"
#include "CPythonPlayer.h"
#include "PythonCharacterManager.h"
#include "CPythonNetwork.h"
#include "CPythonBackground.h"
#include "CPythonItem.h"
#include "Memory.h"



//Classes that are not used as pointers (Example: CPythonCharacterManager or CPythonPlayer)
//Should be accessed only throught this object
//This object should only be created once
class MetinSDK
{
public:
	MetinSDK(HMODULE hMod);
	~MetinSDK();

	inline CPythonCharacterManager * getPythonCharacterManager() {return PythonCharacterManager;}
	inline CPythonPlayer * getPythonPlayer() { return PythonPlayer; }
	inline CPythonNetwork * getPythonNetwork() { return PythonNetwork; }
	inline CPythonBackground * getPythonBackground() { return PythonBackground; }
	inline CPythonItem* getPythonItem() { return PythonItem; }
	
private:
	bool Initialize(HMODULE hMod);

	CPythonCharacterManager * PythonCharacterManager;
	CPythonPlayer * PythonPlayer;
	CPythonNetwork * PythonNetwork;
	CPythonBackground * PythonBackground;
	CPythonItem * PythonItem;
};

