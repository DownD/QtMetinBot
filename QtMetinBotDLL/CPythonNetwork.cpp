#include "CPythonNetwork.h"



CPythonNetwork::CPythonNetwork(Memory* mem,CPythonCharacterManager* manager)
{
	this->manager = manager;
	NetworkClass = mem->GetCMethod<CLASS_POINTER*>("NetworkClass",DEREFERENCE,CRITICAL);
	fRecv = mem->GetCMethod<tRecv>("RecvFunc",NO_DEREFERENCE);
	fRecvServerCommand = mem->GetCMethod<tRecvServerCommand>("ServerCommandFunc",NO_DEREFERENCE,CRITICAL);
	fSendBattleAttack = mem->GetCMethod<tSendBattleAttack>("SendBattleAttack",NO_DEREFERENCE,CRITICAL);
	fNetworkProcess = mem->GetCMethod<tNetworkProcess>("NetworkProcessFunc", NO_DEREFERENCE, CRITICAL);
	m_SelectedInstanceOffset = mem->GetCMethod<DWORD>("m_SelectedInstance", DEREFERENCE, NO_CRITICAL);
	fSendChatPacket = mem->GetCMethod<tSendChatPacket>("SendChatPacketFunc", NO_DEREFERENCE, NO_CRITICAL);
	fSendCharacterState = mem->GetCMethod<tSendCharacterStatePacket>("SendCharacterState", NO_DEREFERENCE, CRITICAL);
	m_phaseStrOffset = mem->GetCMethod<DWORD>("m_phaseStr", DEREFERENCE, CRITICAL);
	fSendItemClickPacket = mem->GetCMethod<tSendItemClickPacket>("SendItemClickPacket", NO_DEREFERENCE, CRITICAL);


	//Python
	Py_GetMainActorVID = mem->GetPythonMethod(NET_PYTHON_MODULE, "GetMainActorVID");
#ifdef ORIGINS_SERVER
	Py_SendItemUsePacket = mem->GetPythonMethod(NET_PYTHON_MODULE, "zs3fey4gh5hrntdb");
#else
	Py_SendItemUsePacket = mem->GetPythonMethod(NET_PYTHON_MODULE, "SendItemUsePacket");
#endif
	Py_SendChatPacket = mem->GetPythonMethod(NET_PYTHON_MODULE, "SendChatPacket");
	Py_GetTargetVID = mem->GetPythonMethod(PLAYER_PYTHON_MODULE, "GetTargetVID");

	//Switches
	if (m_SelectedInstanceOffset) swSelectedInstance = C_FUNCTION; else swSelectedInstance = PY_FUNCTION;

	DEBUG_INFO(COLOR_DEFAULT, "ClassNetwork Sucessfully Created");
}


CPythonNetwork::~CPythonNetwork()
{
}

DWORD CPythonNetwork::GetMainActorVID()
{
	PyObject* result = Py_GetMainActorVID(NULL, Py_BuildValue("()"));
	int num = 0;
	if (result)
		num = PyInt_AS_LONG(result);

	return num;
}

void CPythonNetwork::SendUseItemPacket(TItemPos pos)
{
#ifdef IMPERUS_SERVER
	Py_SendItemUsePacket(NULL, Py_BuildValue("(iBi)", pos.windowType, pos.itemSlot, 99));
#else
	Py_SendItemUsePacket(NULL, Py_BuildValue("(Bi)", pos.windowType, pos.itemSlot));
#endif
}

void CPythonNetwork::SendChatPacket(const char * c_szChat, int byType)
{
#ifdef IMPERUS_SERVER
	Py_SendChatPacket(NULL, Py_BuildValue("(isi)",99, c_szChat, byType));
#else
	Py_SendChatPacket(NULL, Py_BuildValue("(si)", c_szChat, byType));
#endif
}

CInstanceBase * CPythonNetwork::Py_GetSelectedInstance()
{
	PyObject* result = Py_GetTargetVID(NULL, Py_BuildValue("()"));
	int num;
	if (result) {
		num = PyInt_AS_LONG(result);
		auto map = manager->getInstanceMap();
		auto it = manager->getInstanceMap()->find((DWORD)num);
		if (it != map->end())
			return it.getValue();
	}
	return nullptr;

}

