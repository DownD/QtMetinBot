#pragma once
#include "CInstanceBase.h"
#include "PythonCharacterManager.h"
//#include "typedef.h"
#include "CPythonNetwork.h"
#include "Memory.h"


#define MAX_DISTANCE_TO_ATTACK 300
#define SKILL_HORSE_ATTACK 9

#define MAIN_INVENTORY 1
#define MAIN_INVENTORY_SIZE 40

#define PICKUP_PYTHON_FUNCTION "PickCloseItem"

#ifdef IMPERUS_SERVER
#define PICKUP_PYTHON_FUNCTION "PickCloseItemVector"
#endif

#ifdef ORIGINS_SERVER
#define PICKUP_PYTHON_FUNCTION "PickCloseItemAround"
#endif


typedef void (__thiscall *tPickCloseItem)(CLASS_POINTER);
typedef void(__thiscall *tUseSkill)(CLASS_POINTER,BYTE);
typedef TItemData* (__thiscall *tGetItemData)(CLASS_POINTER,TItemPos);

//Only one object should be created
class CPythonPlayer
{
public:
	CPythonPlayer(CPythonCharacterManager* manager, CPythonNetwork* network, Memory* mem);
	inline void PickCloseItem(){ return swPickCloseItem ? PyPickCloseItem() : _CPickCloseItem(*ClassPointer); }

	//Python Only
	void setAttack(bool attack);
	void useSkill(BYTE slotSkill);
	void useItemIfAvailable(DWORD id);
	DWORD getItemCount(TItemPos pos);
	DWORD getItemCountByID(DWORD id);
	DWORD getItemID(TItemPos pos);
	TItemPos getSlotFromID(int id);
	void getPosition(Point2D & p);
	void appendChat(const char* str,int num = 3);
	bool isPossibleEmiticon();
	bool IsMountingHorse();




	//Goes to Monster if is not close enought
	void attackInstance(CInstanceBase* instance);

	float calculateRotationToInstance(CInstanceBase* instance);
	float distanceToInstance(CInstanceBase* instance);

	void mountHorse();
	void unMountHorse();



	//Wrappers
	inline void WalkToPosition(Point2D &p) { manager->getMainInstance()->WalkToPosition(p); }
	inline void setRotation(float rot) { manager->getMainInstance()->setRotation(rot); }
	inline void EnableSkipCollisions(bool colision) { manager->getMainInstance()->EnableSkipCollisions(colision); }
	inline void setPosition(Point2D& p) { manager->getMainInstance()->setPosition(p); }
	inline float getRotation() { return manager->getMainInstance()->getRotation(); }
	inline bool isDead() { return manager->getMainInstance()->isDead(); }
	inline CInstanceBase* getMainInstance() { return manager->getMainInstance(); }



	~CPythonPlayer();

private:

	//PythonFunctions
	void PyPickCloseItem();


private:
	CLASS_POINTER* ClassPointer;
	CPythonCharacterManager* manager;
	CPythonNetwork * network;

	//Switches
	FunctionType swPickCloseItem;

	//Python Memory Functions
	PythonFunction _PyPickCloseItem;
	PythonFunction _PySetAttackKeyState;
	PythonFunction _PyClickSkillSlot;
	PythonFunction _PyGetItemCount;
	PythonFunction _PyGetItemCountByVnum;
	PythonFunction _PyGetItemIndex;
	PythonFunction _PyGetMainCharacterPosition;
	PythonFunction _PyAppendChat;
	PythonFunction _PyIsPossibleEmoticon;
	PythonFunction _PyIsMountingHorse;

	//C Memory Functions
	tPickCloseItem _CPickCloseItem;



	//Functions
	tGetItemData fGetItemData;
};

