#include "SleepFunctionHook.h"



SleepFunctionHook::SleepFunctionHook(tFunction toBeRedirected) : HookFeature(setupHook(toBeRedirected))
{
}


SleepFunctionHook::~SleepFunctionHook()
{
}

Hook * SleepFunctionHook::setupHook(tFunction toBeRedirected)
{
	HMODULE mod = GetModuleHandle(L"KERNELBASE");
	if (!mod) {
		DEBUG_INFO(COLOR_RED, "Error finding KERNELBASE dll for hooking %d", GetLastError()); return NULL;
	}

	void* sleepFunction = GetProcAddress(mod, "Sleep");
	if (!sleepFunction) { DEBUG_INFO(COLOR_RED, "Error finding Sleep Function for Hooking Error Code: %d", GetLastError()); return NULL; }

	return new JMPHook(sleepFunction, toBeRedirected, 5,THIS_CALL);
}

