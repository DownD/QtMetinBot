#pragma once
#include "HookFeature.h"
#include "JMPHook.h"

class SleepFunctionHook : public HookFeature
{
public:
	SleepFunctionHook(tFunction toBeRedirected);
	~SleepFunctionHook();

private:
	Hook* setupHook(tFunction toBeRedirected);
};

