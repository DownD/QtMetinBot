#include "NetworkProcessHook.h"



NetworkProcessHook::NetworkProcessHook(tFunction toBeRedirected) : HookFeature(setupHook(toBeRedirected))
{
}


NetworkProcessHook::~NetworkProcessHook()
{
}

Hook * NetworkProcessHook::setupHook(tFunction toBeRedirected)
{
	return new JMPHook(sdk->getPythonNetwork()->getProcAddr(), toBeRedirected, 9,THIS_CALL);
}
