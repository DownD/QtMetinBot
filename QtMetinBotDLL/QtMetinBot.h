#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtMetinBot.h"
#include "Bot.h"

class QtMetinBot : public QMainWindow
{
	Q_OBJECT

public:
	QtMetinBot(Bot *bot,QWidget *parent = Q_NULLPTR);

private:
	void setupConnections();
	void Init();

private slots:

	void stopStartBot(bool state);
	void selectExpBot(bool state);
	void selectFarmBot(bool state);
	void selectFishingBot(bool state);

	//GeneralTab
	void itemUserStartStop(bool toogled);
	void executePythonFileClicked();

	//SkillBot
	void skillBotStartStop(bool toogled);
	void selectSuraSkills(bool toogled);
	void selectWarriorSkills(bool toogled);

	//Pickup
	void pickupStartStop(bool toogled);
	void enableRangePickup(bool toogled);

	//DamageHacks
	void waitDamageStartStop(bool toogled);
	void dmgHackSelectedStartStop(bool toogled);

	//Security
	void enableRagePickupSilent(bool toogled);
	void enableWaitHackSilent(bool toogled);
	void enableDamageHackSilent(bool toogled);
	
	void enableAllSilentOptions();
	void disableAllSilentOptions();

private:

	Bot * bot;
	Ui::QtMetinBotClass ui;
};
