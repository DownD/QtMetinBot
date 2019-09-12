#pragma once
#include "BotFeature.h"
#include "Hook.h"

//Abstract class that is used as an interface for some feature that works with a hook

class HookFeature : public BotFeature
{
public:
	HookFeature(Hook* hook) : hook(hook) { if (!hook) throw std::exception("Error Creating Hook"); };
	virtual ~HookFeature() { hook->UnHookFunction(); if(hook) delete hook; }

	// Inherited via BotFeature
	virtual void Start() override { hook->HookFunction(); }
	virtual void ThreadLoop() override {};
	virtual void Stop() override { hook->UnHookFunction(); }

private:
	Hook* hook;
};

