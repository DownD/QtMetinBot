#pragma once
#include <Windows.h>
#include "MetinSDK.h"
class BotFeature
{
public:

	//This needs to be set before any operation
	static void setSDK(MetinSDK* sdk) { BotFeature::sdk = sdk; };

	virtual void Start() = 0;
	virtual void ThreadLoop() = 0;
	virtual void Stop() = 0;

	virtual ~BotFeature() {};

protected:
	static MetinSDK *sdk;
};

