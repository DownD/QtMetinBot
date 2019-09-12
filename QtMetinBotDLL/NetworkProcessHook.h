#pragma once
#include "HookFeature.h"
#include "JMPHook.h"
class NetworkProcessHook : public HookFeature
{
public:
	NetworkProcessHook(tFunction toBeRedirected);
	~NetworkProcessHook();

private:

	Hook* setupHook(tFunction toBeRedirected);
};

