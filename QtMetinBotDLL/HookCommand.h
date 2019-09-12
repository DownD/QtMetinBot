#pragma once
#include "HookFeature.h"
#include "JMPHook.h"


typedef void(__cdecl*tHookCommand)(char* serverCmd);

class HookCommand : public HookFeature {
public:
	HookCommand(tHookCommand serverCommand);


private:

	Hook* setupHook();

private:
	static tHookCommand serverCommand;

};

