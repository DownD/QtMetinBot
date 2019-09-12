#pragma once

#define UPDATE_ALL 0
class UserInterface
{
public:
	UserInterface();
	virtual ~UserInterface() = 0;

	virtual void update(int args = UPDATE_ALL) = 0;
};

