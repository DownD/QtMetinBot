#include "CMD.h"

CMD* CMD::instance = 0;

CMD::CMD(MetinSDK * sdk)
{
	this->sdk = sdk;
}


CMD::~CMD()
{
	recvFunctionHook->UnHookFunction();
	delete recvFunctionHook;
	instance = 0;
}

//AntiBotFishingMining 7
void CMD::Init(HMODULE hMod)
{
	BotFeature::setSDK(sdk);
#ifdef IMPERUS_SERVER
	recvFunctionHook = createHook();
#endif
	cmdMainLoop();
}

CMD * CMD::getInstance()
{
	return instance;
}

CMD* CMD::createInstance(MetinSDK* sdk)
{
	if (instance != 0)
		return getInstance();
	CMD* cmd = new CMD(sdk);
	instance = cmd;
	return cmd;
}


void CMD::cmdMainLoop()
{
	while (true) {
		system("cls");
		printOptions();
		char str[200] = { 0 };
		fgets(str, 200, stdin);
		fflush(stdin);
		int size = strlen(str);
		if (size > 0) {
			str[size - 2] = 0;
		}

		int option;
		try {
			option = std::atoi(str);
		}
		catch (std::exception &e) {
			printf("Incompatible format, try again\n");
			system("pause");
			continue;
		}

		switch (option) {
			case 1:
				testPythonCharacterPlayer();
				break;
			case 2:
				testInstanceBase();
				break;
			case 3:
				testPythonPlayer();
				break;
			case 4:
				testRecvIntercept();
				break;
			case 5:
				testNetwork();
				break;
			case 6:
				testPythonBackground();
				break;
			case 7:
				testPythonItem();
				break;
			case 8:
				return;
			default:
				break;
		}
		system("pause");
	}
}

void CMD::printOptions()
{
	printf("Tester\nWrite any of the following words\n\n");
	printf("1 - TestPythonCharacterPlayer\n");
	printf("2 - TestInstanceBase\n");
	printf("3 - TestPythonPlayer\n");
	printf("4 - RcvFunctionIntercept\n");
	printf("5 - TestPythonNetwork\n");
	printf("6 - TestPythonBackground\n");
	printf("7 - TestPythonItem\n");
	printf("8 - Exit\n");
}

void CMD::testPythonCharacterPlayer()
{
	while (true) {
		system("cls");
		printf("TestPythonCharacter\n");
		printf("1 - Test MainCharacter Arguments()\n");
		printf("2 - Print Entire List to file\n");
		printf("3 - Print Entire List\n");
		printf("4 - Print Entire List Name for 5 seconds\n");
		printf("5 - Exit\n");

		char str[200] = { 0 };
		fgets(str, 200, stdin);
		int size = strlen(str);
		if (size > 0) {
			str[size - 1] = 0;
		}

		std::vector<std::string> strings;
		split(str, ' ', &strings);
		if (strings.empty()) { continue; }

		int value = std::atoi(strings[0].data());

			switch (value) {
			case 1:
				printf("MainInstance: %#x", sdk->getPythonCharacterManager()->getMainInstance());
				break;
			case 2:
				freopen("log.txt", "w", stdout);
			case 3: {
				CPythonCharacterManager* manager = sdk->getPythonCharacterManager();
				auto begin = manager->getInstanceMap()->begin();
				auto end = manager->getInstanceMap()->end();
				printf("Printing %d Instances\n", manager->getInstanceMap()->getSize());
				for (; begin != end; ++begin) {
					printInstance((begin.getValue()));
				}
				freopen("CONOUT$", "wb", stdout);
				break; }
			case 4: {
				for (int i = 0; i < 200; i++) {
					CPythonCharacterManager* manager = sdk->getPythonCharacterManager();
					auto begin = manager->getInstanceMap()->begin();
					auto end = manager->getInstanceMap()->end();
					for (; begin != end; ++begin) {
						std::string name;
						begin.getValue()->getName(name);
						printf("%s\n",name.c_str());
					}
					Sleep(20);
					system("cls");
				}
				break;
			}
			case 5:
				return;
			default:
				break;
			}
			system("pause");
	}
	
}

void CMD::testInstanceBase()
{
	while (true) {
		system("cls");
		printf("TestMainInstance\n");
		printf("1 - Test SetRotation Arguments(float)\n");
		printf("2 - Test EnableSkipCollisions Arguments(bool)\n");
		printf("3 - Test SetPosition Arguments(float,float)\n");
		printf("4 - Test Name Arguments()\n");
		printf("5 - Test isDead Arguments()\n");
		printf("6 - Test getID Arguments()\n");
		printf("7 - Test getType Arguments()\n");
		printf("8 - Test WalkToPosition Arguments(flaot,float)\n");
		printf("9 - Print all Info\n");
		printf("10 - Print Inventory\n");
		printf("11 - Exit\n");

		char str[200] = { 0 };
		fgets(str, 200, stdin);
		int size = strlen(str);
		if (size > 0) {
			str[size - 1] = 0;
		}

		std::vector<std::string> strings;
		split(str, ' ', &strings);
		if (strings.empty()) { continue; }

		int value = std::atoi(strings[0].data());

			CInstanceBase * main = sdk->getPythonCharacterManager()->getMainInstance();
			DEBUG_INFO(COLOR_DEFAULT, "MainInstance : %#x\n",main);
			switch (value) {
			case 1:
				main->setRotation(std::atof(strings[1].data()));
				break;
			case 2:
				main->EnableSkipCollisions(std::atoi(strings[1].data()));
				break;
			case 3: {
				Point2D a(std::atof(strings[1].data()), std::atof(strings[2].data()));
				main->setPosition(a);
				break;
			}
			case 4: {
				std::string buffer;
				main->getName(buffer);
				printf("\nName: %s\n", buffer.c_str());
				break;
			}
			case 5:
				printf("\nIsDead: %d\n", main->isDead());
				break;
			case 6:
				printf("\nID: %d\n", main->getID());
				break;
			case 7:
				printf("\nType: %d\n", main->getType());
				break;
			case 8: {
				Point2D a(std::atof(strings[1].data()), std::atof(strings[2].data()));
				main->WalkToPosition(a);
				break;
			}
			case 9:
				printInstance(main);
				break;
			case 10: {
				TItemPos pos;
				pos.windowType = MAIN_INVENTORY;
				for (int i = 0; i < MAIN_INVENTORY_SIZE; i++) {
					pos.itemSlot = i;
					printf("Item ID: %d     Slot: %d\n",i, sdk->getPythonPlayer()->getItemID(pos));
				}
				break;
			}
			case 11:
				return;
			default:
				break;
			}
			system("pause");
	}
}

void CMD::testPythonPlayer()
{
	while (true) {
		system("cls");
		printf("TestPythonPlayer\n");
		printf("1 - Test Pickup Arguments()\n");
		printf("2 - Test Attack Arguments(bool)\n");
		printf("3 - Test SendBattleAttack Arguments(VID)\n");
		printf("4 - Test SendBattlePacketSpam Arguments(VID,Number,intervalMS)\n");
		printf("5 - Test GetMainActorVID\n");
		printf("6 - Test GetMainInstancePositio\n");
		printf("7 - Test Rotation to Instance(VID)\n");
		printf("8 - Exit\n");

		char str[200] = { 0 };
		fgets(str, 200, stdin);
		int size = strlen(str);
		if (size > 0) {
			str[size - 1] = 0;
		}

		std::vector<std::string> strings;
		split(str, ' ', &strings);
		if (strings.empty()) { continue; }

		int value = std::atoi(strings[0].data());
		
			switch (value) {
			case 1:
				sdk->getPythonPlayer()->PickCloseItem();
				break;
			case 2:
				sdk->getPythonPlayer()->setAttack(std::atoi(strings[1].data()));
				break;
			case 4: {
				int a = std::atoi(strings[1].data());
				int b = std::atoi(strings[2].data());
				int c = std::atoi(strings[3].data());
				for (int i = 0; i < b; i++) {
					sdk->getPythonNetwork()->SendBattleAttack(0, a);
					Sleep(c);
				}
				break;
				}
			case 3:
				sdk->getPythonNetwork()->SendBattleAttack(0, std::atoi(strings[1].data()));
				break;
			case 5:
				printf("VID %d\n",sdk->getPythonNetwork()->GetMainActorVID());
				break;
			case 6: {
				Point2D a;
				sdk->getPythonPlayer()->getPosition(a);
				printf("Pos X:%f	 Y:%f\n", a.x,a.y);
				break;
			}
			case 7: {
				if (strings.size() < 2) {
					printf("Insuficient arguments\n");
					return;
				}
				float rot = sdk->getPythonPlayer()->calculateRotationToInstance(sdk->getPythonCharacterManager()->getInstanceByVID(std::atoi(strings[1].data())));
				sdk->getPythonPlayer()->setRotation(rot);
				printf("Turned to angle: %f\n", rot);
				break;
			}
			case 8:
				return;
			default:
				break;
			}
		system("pause");
	}

}

void CMD::testRecvIntercept()
{
	while (true) {
		system("CLS");
		printf("Recive Packet Interceptor - Not Working\n\n");

		printf("1 - Print packets for 2 seconds\n");
		printf("2 - Print packets to file\n");
		printf("3 - Exit\n");


		char str[200] = { 0 };
		fgets(str, 200, stdin);
		int size = strlen(str);
		if (size > 0) {
			str[size - 1] = 0;
		}

		std::vector<std::string> strings;
		split(str, ' ', &strings);
		if (strings.empty()) { continue; }

		int value = std::atoi(strings[0].data());

		switch (value) {
		case 1:
			return;
			recvFunctionHook->HookFunction();
			printf("Waiting\n");
			system("pause");
			printf("Stopped\n");
			Sleep(2000);
			recvFunctionHook->UnHookFunction();
			break;
		case 2:
			return;
			printf("Press an hotkey to stop intercepting\n");
			freopen("packReader.txt", "wb", stdout);
			recvFunctionHook->HookFunction();
			system("pause");
			recvFunctionHook->UnHookFunction();
			freopen("CONOUT$", "wb", stdout);
			continue;
			break;
		case 3:
			return;
		default:
			continue;
		}
		system("puase");
	}
}

void CMD::testNetwork()
{
	while (true) {
		system("CLS");
		printf("Network\n\n");

		printf("1 - Hook commandLine\n");
		printf("2 - Hook SendChatPacket and print on console\n");
		printf("3 - Hook SendChatPacket and Print on game\n");
		printf("4 - UnHook SendChatPacket and Print on game\n");
		printf("5 - SendChatPacket(string)\n");
		printf("6 - SendBattelPacket and CharacterPosition(WAITHACK) (VID)\n");
		printf("7 - SendCharacterMovePacket (float,float)\n");
		printf("8 - Exit\n");


		char str[200] = { 0 };
		fgets(str, 200, stdin);
		int size = strlen(str);
		if (size > 0) {
			str[size - 1] = 0;
		}

		std::vector<std::string> strings;
		split(str, ' ', &strings);
		if (strings.empty()) { continue; }

		int value = std::atoi(strings[0].data());

		static Hook* gamehook = 0;

		switch (value) {
		case 1: {
			Hook* hook =  new JMPHook(sdk->getPythonNetwork()->getRecvServerCommandAddr(), CommandLine, 6, THIS_CALL);
			printf("Press an hotkey to stop intercepting\n");
			hook->HookFunction();
			system("pause");
			hook->UnHookFunction();
			delete hook;
			break;
		}
		case 2: {
			if (gamehook) {
				printf("Already Hooked\n");
				break;
			}
			Hook* hk = new JMPHook(sdk->getPythonNetwork()->getSendChatPacketAddr(),SendChatPacketHook,7,THIS_CALL);
			printf("Press an hotkey to stop intercepting\n");
			hk->HookFunction();
			system("pause");
			hk->UnHookFunction();
			delete hk;
			break;
		}
		case 3: {
			if (gamehook) {
				printf("Already Hooked\n");
				break;
			}
			gamehook = new JMPHook(sdk->getPythonNetwork()->getSendChatPacketAddr(), SendChatPacketHookInGamePrint, 7, THIS_CALL);
			gamehook->HookFunction();
			printf("Hooked\n");
			break;
		}
		case 4: {
			if (gamehook) {
				gamehook->UnHookFunction();
				printf("UnHooked\n");
				delete gamehook;
				gamehook = 0;
				break;
			}
			printf("Function not hooked\n");
			break;
		}
		case 5: {
			sdk->getPythonNetwork()->SendChatPacket(strings.at(1).data(),0);
			printf("Sent %s\n", strings.at(1).data());
			break;
		}
		case 6: {
			CInstanceBase* target = sdk->getPythonCharacterManager()->getInstanceByVID(std::atoi(strings[1].data()));
			if (!target) {
				printf("No target with that VID\n");
				break;
			}
			Point2D pos;
			target->getPosition(pos);
			//sdk->getPythonNetwork()->SendCharacterStateMovePacket(pos, 20.0);
			printf("Moving to X: %f, %f\n",pos.x,pos.y);
			sdk->getPythonNetwork()->SendCharacterStateMovePacket(pos,20.0);
			sdk->getPythonNetwork()->SendCharacterStateAttackPacket(pos, 20.0, FIRST_HORSE_ATTACK);
			Sleep(50);
			sdk->getPythonNetwork()->SendBattleAttack(0, target->getVID());
			break;
		}
		case 7: {
			Point2D pos;
			pos.x = std::atof(strings[1].data());
			pos.y = std::atof(strings[2].data());
			//sdk->getPythonNetwork()->SendCharacterStateAttackPacket(pos,20.0,FIRST_HORSE_ATTACK);
			sdk->getPythonNetwork()->SendCharacterStateMovePacket(pos, 20.0);
			break;
		}
		case 8:
			return;
		default:
			continue;
		}
		system("pause");
	}
}

void CMD::testPythonBackground()
{
	while (true) {
		system("CLS");
		printf("Background\n\n");

		printf("1 - Is location blocked (float,float)\n");
		printf("2 - Exit\n");


		char str[200] = { 0 };
		fgets(str, 200, stdin);
		int size = strlen(str);
		if (size > 0) {
			str[size - 1] = 0;
		}

		std::vector<std::string> strings;
		split(str, ' ', &strings);
		if (strings.empty()) { continue; }

		int value = std::atoi(strings[0].data());

		static Hook* gamehook = 0;

		switch (value) {
		case 1: {
			if (strings.size() < 3) {
				printf("The command takes 3 arguments\n");
				break;
			}
			printf("Result: %d\n" ,sdk->getPythonBackground()->isLocationBlocked(std::atof(strings[1].data()), std::atof(strings[2].data())));
			break;
		}
		case 2:
			return;
		default:
			continue;
		}
		system("pause");
	}
}

void CMD::testPythonItem()
{
	while (true) {
		system("CLS");
		printf("PythonItem\n\n");

		printf("1 - SendItemClickPacket(VID)\n");
		printf("2 - Print every ground item\n");
		printf("3 - Exit\n");


		char str[200] = { 0 };
		fgets(str, 200, stdin);
		int size = strlen(str);
		if (size > 0) {
			str[size - 1] = 0;
		}

		std::vector<std::string> strings;
		split(str, ' ', &strings);
		if (strings.empty()) { continue; }

		int value = std::atoi(strings[0].data());

		static Hook* gamehook = 0;

		switch (value) {
		case 1: {
			if (strings.size() <2) {
				printf("The command takes 1 arguments\n");
				break;
			}
			sdk->getPythonNetwork()->SendItemClickPacket(std::atoi(strings[1].data()));
			break;
		}
		case 2: {
			CPythonItem* item = sdk->getPythonItem();
			CInstanceBase* mainInstance = sdk->getPythonPlayer()->getMainInstance();

			auto map = item->getGroundItemMap();
			GroundItemMap::iterator begin = map->begin();
			GroundItemMap::iterator end = map->end();

			Point2D mainPos;
			mainInstance->getPosition(mainPos);


			for (; begin != end; ++begin) {
				SGroundItemInstance* curr = begin.getValue();
				std::string* itemName = item->getGroundItemOwnership(curr);
				Point2D pos = curr->getItemPosition2D();
				printf("Owner Name: %s\nPosition: X->%f	 Y->%f\nDistance: %f\nID: %d\nVID: %d\n\n", itemName->data(), pos.x, pos.y, mainPos.distance(&pos), curr->dwVirtualNumber, begin.getKey());
			}
			break;
		}
		case 3:
			return;
		default:
			break;
		}
		system("pause");
	}
}

void CMD::printInstance(CInstanceBase * instance)
{
	printf("CInstanceBase address: %#x\n", instance);
	std::string str;
	instance->getName(str);
	printf("Name: %s\n", str.c_str());
	printf("IsDead: %d\n", instance->isDead());
	printf("ID: %d\n", instance->getID());
	printf("Type: %d\n", instance->getType());
	printf("Rotation %f\n", instance->getRotation());
	printf("VID: %d\n", instance->getVID());
	Point2D a;
	instance->getPosition(a);
	printf("Location X:%f  Y:%f\n", a.x, a.y);
	printf("\n");

}

void CMD::InterceptRecvFunction(int size, void * buffer) {

	unsigned char* buf = (unsigned char*)buffer;
	printf("Size: %d\n",size);
	printf("Buffer in Hex: ");
	for (int i = 0; i < size; i++) {
		printf("%#x ", buf[i]);
	}
	printf("\n\n");
}

__declspec(naked) void CMD::redirectRecvFunction()
{
	__asm {
		push [ebp + IMPERUS_RECV_BUFFER_EBP_OFFSET];
		push [ebp + IMPERUS_RECV_SIZE_EBP_OFFSET];
		call InterceptRecvFunction;
		add esp, 8;
		ret;
	}
}


void __cdecl CMD::CommandLine(char * buffer)
{
	printf("Executing: %s\n", buffer);
}

void __cdecl CMD::SendChatPacketHook(char * buffer)
{
	printf("Sending: %s\n", buffer);
}

Hook * CMD::createHook()
{
	void *addr = (void*)((int)(sdk->getPythonNetwork()->getRecvFunctionAddr()) + IMPERUS_HOOK_OFFSET);
	DEBUG_INFO(COLOR_DEFAULT,"Hook Created at: %#x", addr);
	return new JMPHook(addr,redirectRecvFunction,5,MID_FUNCTION);
}
