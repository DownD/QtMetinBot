#include "HookCommand.h"


tHookCommand HookCommand::serverCommand = 0;

HookCommand::HookCommand(tHookCommand serverCommand) : HookFeature(setupHook())
{
	this->serverCommand = serverCommand;
}

Hook * HookCommand::setupHook()
{
	return new JMPHook((void*)((int)sdk->getPythonNetwork()->getRecvServerCommandAddr()), serverCommand,6,THIS_CALL);
}
