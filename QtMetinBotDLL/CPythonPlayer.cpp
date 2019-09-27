#include "CPythonPlayer.h"



CPythonPlayer::CPythonPlayer(CPythonCharacterManager* manager, CPythonNetwork* network, Memory* mem)
{
	this->manager = manager;
	this->network = network;
	_CPickCloseItem = mem->GetCMethod<tPickCloseItem>("PickClosestItemFunc",NO_DEREFERENCE);

	ClassPointer = mem->GetCMethod<CLASS_POINTER*>("CPythonPlayer",DEREFERENCE,CRITICAL);


	_PyPickCloseItem = mem->GetPythonMethod(PLAYER_PYTHON_MODULE,PICKUP_PYTHON_FUNCTION);
	_PySetAttackKeyState = mem->GetPythonMethod(PLAYER_PYTHON_MODULE, "SetAttackKeyState");

#ifdef ORIGINS_SERVER
	_PyClickSkillSlot = mem->GetPythonMethod(PLAYER_PYTHON_MODULE, "zoprobarketkwonu");
#else
	_PyClickSkillSlot = mem->GetPythonMethod(PLAYER_PYTHON_MODULE, "ClickSkillSlot");
#endif
	_PyGetItemCount = mem->GetPythonMethod(PLAYER_PYTHON_MODULE, "GetItemCount");
	_PyGetItemCountByVnum = mem->GetPythonMethod(PLAYER_PYTHON_MODULE, "GetItemCountByVnum");
	_PyGetItemIndex = mem->GetPythonMethod(PLAYER_PYTHON_MODULE, "GetItemIndex");
	_PyGetMainCharacterPosition = mem->GetPythonMethod(PLAYER_PYTHON_MODULE, "GetMainCharacterPosition");
	_PyAppendChat = mem->GetPythonMethod(CHAT_PYTHON_MODULE, "AppendChat");
	_PyIsPossibleEmoticon = mem->GetPythonMethod(CHRMGR_PYTHON_MODULE, "IsPossibleEmoticon");
	_PyIsMountingHorse = mem->GetPythonMethod(PLAYER_PYTHON_MODULE, "IsMountingHorse");
	_PySetAutoPotionInfo = mem->GetPythonMethod(PLAYER_PYTHON_MODULE, "SetAutoPotionInfo");
	_PyGetAutoPotionInfo = mem->GetPythonMethod(PLAYER_PYTHON_MODULE, "GetAutoPotionInfo");

	if (_CPickCloseItem) swPickCloseItem = C_FUNCTION; else swPickCloseItem = PY_FUNCTION;
	DEBUG_INFO(COLOR_GREEN, "PythonPlayer Sucessfully set");
}

void CPythonPlayer::setAttack(bool attack)
{
	_PySetAttackKeyState(NULL, Py_BuildValue("(i)", (int)attack));
}

void CPythonPlayer::useSkill(BYTE slotSkill)
{
	_PyClickSkillSlot(NULL, Py_BuildValue("(i)", (int)slotSkill));
}

void CPythonPlayer::useItemIfAvailable(DWORD vnum) {
	TItemPos pos = getSlotFromID(vnum);
	if (pos.windowType == 0)
		return;
	network->SendUseItemPacket(pos);
	DEBUG_INFO(COLOR_DEFAULT,"SDK: Using Item at Position: %d", (int)pos.itemSlot);
}

void CPythonPlayer::getPosition(Point2D & p)
{
	PyObject* obj = _PyGetMainCharacterPosition(NULL, Py_BuildValue("()"));
	PyTuple_GetFloat(obj, 0, &p.x);
	PyTuple_GetFloat(obj, 1, &p.y);
	p.absoluteY();
}

void CPythonPlayer::appendChat(const char * str, int num)
{
	_PyAppendChat(NULL, Py_BuildValue("(is)", num, str));
}

bool CPythonPlayer::isPossibleEmiticon()
{
	PyObject* result;
#ifdef AELDRA_SERVER
	result = _PyIsPossibleEmoticon(NULL, Py_BuildValue("(ii)",-1,938));
#else
	result = _PyIsPossibleEmoticon(NULL, Py_BuildValue("(i)", -1));
#endif
	return (bool)PyInt_AsLong(result);
}

bool CPythonPlayer::IsMountingHorse()
{
	PyObject* obj = _PyIsMountingHorse(NULL, Py_BuildValue("()"));
	DWORD result = (DWORD)PyInt_AsLong(obj);
	return (bool)result;
}

void CPythonPlayer::getPotionInfo(int potionType, AutoPotionInfo * potionInfo)
{
	PyObject* obj = _PyGetAutoPotionInfo(NULL, Py_BuildValue("(i)", potionType));
	PyTuple_GetByte(obj, 0, (unsigned char*)&potionInfo->bActivated);
	PyTuple_GetInteger(obj, 1, (int*)&potionInfo->currentAmount);
	PyTuple_GetInteger(obj, 2, (int*)&potionInfo->totalAmount);
	PyTuple_GetInteger(obj, 3, (int*)&potionInfo->inventorySlotIndex);
}

void CPythonPlayer::setPotionInfo(int potionType, AutoPotionInfo & potion)
{
	PyObject* obj = _PySetAutoPotionInfo(NULL, Py_BuildValue("(ibiii)",potionType, potion.bActivated, potion.currentAmount, potion.totalAmount, potion.inventorySlotIndex));
}
DWORD CPythonPlayer::getItemCount(TItemPos pos)
{
	PyObject* obj = _PyGetItemCount(NULL, Py_BuildValue("(bi)", pos.windowType, pos.itemSlot));
	return (DWORD)PyInt_AsLong(obj);
}

DWORD CPythonPlayer::getItemCountByID(DWORD id)
{
	PyObject* obj = _PyGetItemCountByVnum(NULL, Py_BuildValue("(i)", id));
	return (DWORD)PyInt_AsLong(obj);
}

DWORD CPythonPlayer::getItemID(TItemPos pos)
{
	PyObject* obj = _PyGetItemIndex(NULL, Py_BuildValue("(bi)", pos.windowType, pos.itemSlot));
	return (DWORD)PyInt_AsLong(obj);

}

void CPythonPlayer::attackInstance(CInstanceBase* instance)
{
	if (distanceToInstance(instance) < MAX_DISTANCE_TO_ATTACK) {
		setAttack(1);
		setRotation(calculateRotationToInstance(instance));
		return;
	}
	else {
		setAttack(0);
		Point2D a;
		instance->getPosition(a);
		WalkToPosition(a);
	}
	

}

float CPythonPlayer::calculateRotationToInstance(CInstanceBase * instance)
{
	Point2D a;
	Point2D b;
	getPosition(a);
	instance->getPosition(b);
	return a.angle(&b);
}

float CPythonPlayer::distanceToInstance(CInstanceBase * instance)
{
	Point2D a;
	Point2D b;
	getPosition(a);
	instance->getPosition(b);
	return a.distance(&b);
}

void CPythonPlayer::mountHorse()
{
#ifdef AELDRA_SERVER
	network->SendChatPacket("/user_mount_action",0);
#else
	throw std::runtime_error("No Mount horse Function");
#endif
}

void CPythonPlayer::unMountHorse()
{
#ifdef AELDRA_SERVER
	network->SendChatPacket("/user_mount_action", 0);
#else
	throw std::runtime_error("No Mount horse Function");
#endif
}



TItemPos CPythonPlayer::getSlotFromID(int id) {

	TItemPos pos;
	pos.windowType = MAIN_INVENTORY;

	for (int i = 0; i < MAIN_INVENTORY_SIZE; i++) {
		pos.itemSlot = i;
		if (getItemID(pos) == id)
			return pos;
		
	}

	pos.itemSlot = 0;
	pos.windowType = 0;
	return pos;
}

CPythonPlayer::~CPythonPlayer()
{
}

void CPythonPlayer::PyPickCloseItem()
{
	_PyPickCloseItem(NULL, Py_BuildValue("()"));
}

