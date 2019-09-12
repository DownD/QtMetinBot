#include "QtMetinBot.h"

QtMetinBot::QtMetinBot(Bot* bot, QWidget *parent)
	: QMainWindow(parent), bot(bot)
{
	ui.setupUi(this);

	if (!bot)
		throw std::runtime_error("Error creating GUI, argument 'bot' is Nullptr");


	setupConnections();
	//Initialize
	Init();
}

void QtMetinBot::stopStartBot(bool toggle)
{
	//No option selected need to be handled
	//ui.botModesBox.setDisabled(state);
	ui.botModesBox->setDisabled(toggle);
	if(toggle){
		bot->startSelectedBot();
	}
	else {
		bot->stopSelectedBot();
	}
}

void QtMetinBot::setupConnections()
{
	connect(ui.startButton, SIGNAL(toggled(bool)), this, SLOT(stopStartBot(bool)));

	//Bot options
	connect(ui.expButton, SIGNAL(toggled(bool)), this, SLOT(selectExpBot(bool)));
	connect(ui.farmButton, SIGNAL(toggled(bool)), this, SLOT(selectFarmBot(bool)));
	connect(ui.fishingButton, SIGNAL(toggled(bool)), this, SLOT(selectFishingBot(bool)));

	//General
	connect(ui.itemUserCheckBox, SIGNAL(toggled(bool)), this, SLOT(itemUserStartStop(bool)));
	connect(ui.runPythonButton, SIGNAL(clicked()), this, SLOT(executePythonFileClicked()));

	//Skill
	connect(ui.activateSkillBotCheckBox, SIGNAL(toggled(bool)), this, SLOT(skillBotStartStop(bool)));
	connect(ui.suraSkillsRadioButton, SIGNAL(toggled(bool)), this, SLOT(selectSuraSkills(bool)));
	connect(ui.warriorSkillsRadioButton, SIGNAL(toggled(bool)), this, SLOT(selectWarriorSkills(bool)));

	//Pickup
	connect(ui.activatePickupCheckBox, SIGNAL(toggled(bool)), this, SLOT(pickupStartStop(bool)));
	connect(ui.rangePickupCheckBox, SIGNAL(toggled(bool)), this, SLOT(enableRangePickup(bool)));


	//Damage
	connect(ui.waitDamageCheckBox, SIGNAL(toggled(bool)), this, SLOT(waitDamageStartStop(bool)));
	connect(ui.selectedDamageCheckBox, SIGNAL(toggled(bool)), this, SLOT(dmgHackSelectedStartStop(bool)));

	//Security
	connect(ui.waitHackSilentCheckBox, SIGNAL(toggled(bool)), this, SLOT(enableWaitHackSilent(bool)));
	connect(ui.dmgHackSilentCheckBox, SIGNAL(toggled(bool)), this, SLOT(enableDamageHackSilent(bool)));
	connect(ui.pickupSilentCheckBox, SIGNAL(toggled(bool)), this, SLOT(enableRagePickupSilent(bool)));
	connect(ui.enableSilentButton, SIGNAL(clicked()), this, SLOT(enableAllSilentOptions()));
	connect(ui.disableSilentButton, SIGNAL(clicked()), this, SLOT(disableAllSilentOptions()));
}

void QtMetinBot::Init()
{
	ui.farmButton->setChecked(true);
	ui.warriorSkillsRadioButton->setChecked(true);
}

void QtMetinBot::selectExpBot(bool toggle)
{
	if (toggle)
		bot->selectExpBot();
}

void QtMetinBot::selectFarmBot(bool toggle)
{
	if (toggle)
		bot->selectFarmBot();
}

void QtMetinBot::selectFishingBot(bool toggle)
{
	if (toggle)
		bot->selectFishingBot();
}

void QtMetinBot::itemUserStartStop(bool toggled)
{
	if (toggled) {
		bot->getItemUser()->Start();
	}
	else {
		bot->getItemUser()->Stop();
	}
}

void QtMetinBot::executePythonFileClicked()
{
	//bot->injectPythonFileFromMainThread();
}

void QtMetinBot::skillBotStartStop(bool toggled)
{
	if (toggled) { bot->getSkillBot()->Start(); }
	else { bot->getSkillBot()->Stop(); }
}

void QtMetinBot::selectSuraSkills(bool toggled)
{
	if (toggled) {
		bot->getSkillBot()->setupSuraWeaponsSkills();
	}
}

void QtMetinBot::selectWarriorSkills(bool toggled)
{
	if (toggled)
		bot->getSkillBot()->setupAuraAndBreserk();
}

void QtMetinBot::pickupStartStop(bool toggled)
{
	if (toggled) { bot->getPickup()->Start(); }
	else { bot->getPickup()->Stop(); }
}

void QtMetinBot::enableRangePickup(bool toggled)
{
	if (toggled) {bot->getPickup()->useRangePickup();}
	else { bot->getPickup()->stopRangePickup(); }
}

void QtMetinBot::waitDamageStartStop(bool toggled)
{
	if (toggled) { bot->getDmgHack()->startWaitDamage(); }
	else { bot->getDmgHack()->stopWaitDamage(); }
}

void QtMetinBot::dmgHackSelectedStartStop(bool toggled)
{
	if (toggled) { bot->getDmgHack()->startDmgSelectdInstance(); }
	else { bot->getDmgHack()->stopDmgSelectedInsatnce(); }
}

void QtMetinBot::enableRagePickupSilent(bool toggled)
{
	if (toggled) { bot->getPickup()->setSilentUse(true); }
	else { bot->getPickup()->setSilentUse(false); }
}

void QtMetinBot::enableWaitHackSilent(bool toggled)
{
	if (toggled) { bot->getDmgHack()->setSilentWaitDMG(true); }
	else { bot->getDmgHack()->setSilentWaitDMG(false); }
}

void QtMetinBot::enableDamageHackSilent(bool toggled)
{
	if (toggled) { bot->getDmgHack()->setSilentSelectedDMG(true); }
	else { bot->getDmgHack()->setSilentSelectedDMG(false); }
}

void QtMetinBot::enableAllSilentOptions()
{
	ui.pickupSilentCheckBox->setChecked(true);
	ui.dmgHackSilentCheckBox->setChecked(true);
	ui.waitHackSilentCheckBox->setChecked(true);
}

void QtMetinBot::disableAllSilentOptions()
{
	ui.pickupSilentCheckBox->setChecked(false);
	ui.dmgHackSilentCheckBox->setChecked(false);
	ui.waitHackSilentCheckBox->setChecked(false);
}
