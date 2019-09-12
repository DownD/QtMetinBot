#pragma once
#include "BotFeature.h"
class BotMode : public BotFeature
{
public:

	virtual void Start() = 0;
	virtual void ThreadLoop() = 0;
	virtual void Stop() = 0;
	virtual bool IsRunning() = 0;

	virtual ~BotMode() {};
};

