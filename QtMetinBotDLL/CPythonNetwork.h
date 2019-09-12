#pragma once
#include "Patterns.h"
#include "Structs.h"
#include "CInstanceBase.h"
#include "PythonCharacterManager.h"
#include "Memory.h"


typedef void(__thiscall *tSendUseItemPacket)(CLASS_POINTER, TItemPos);
typedef void(__thiscall *tRecv)(CLASS_POINTER, void*, int);
typedef void(__thiscall *tSendChatPacket)(CLASS_POINTER, const char*, BYTE);
typedef void(__thiscall *tRecvServerCommand)(CLASS_POINTER, char*);
typedef void(__thiscall *tSendBattleAttack)(CLASS_POINTER, UINT, DWORD);
typedef void(__thiscall *tSendCharacterStatePacket)(CLASS_POINTER, const Point2D& c_rkPPosDst, float fDstRot, UINT eFunc, UINT uArg);
typedef void(__thiscall *tNetworkProcess)(CLASS_POINTER);
typedef void(__thiscall *tSendItemClickPacket)(CLASS_POINTER, DWORD);


class CPythonNetwork
{
public:
	CPythonNetwork(Memory* python, CPythonCharacterManager* manager);
	~CPythonNetwork();


	//Address to hooks
	inline void* getRecvFunctionAddr() { return (void*)fRecv; }
	inline void* getRecvServerCommandAddr() { return (void*)fRecvServerCommand; }
	inline void* getProcAddr() { return (void*)fNetworkProcess; }
	inline void* getSendChatPacketAddr() { return (void*)fSendChatPacket; } //Needs check, as function can be null

	inline void SendBattleAttack(UINT uMotAttack, DWORD VID) { return fSendBattleAttack(*NetworkClass,uMotAttack, VID); }
	inline CInstanceBase* getSelectedInstance() { return swSelectedInstance ? Py_GetSelectedInstance() : (CInstanceBase*)*(DWORD*)((int)*NetworkClass + m_SelectedInstanceOffset); }
	inline const char* getPhase() { return (const char*)((int)*NetworkClass + m_phaseStrOffset); }
	inline void SendCharacterStatePacket(Point2D& c_rkPPosDst, float fDstRot, UINT eFunc, UINT uArg) { c_rkPPosDst.absoluteY(),fSendCharacterState(*NetworkClass,c_rkPPosDst, fDstRot, eFunc, uArg); }
	inline void SendItemClickPacket(DWORD vid) { fSendItemClickPacket(*NetworkClass,vid); }

	//Wrappers
	inline void SendCharacterStateMovePacket(Point2D& c_rkPPosDst, float rot) { SendCharacterStatePacket(c_rkPPosDst, rot, TypeStateAttack::FUNC_ATTACK, 0); }
	inline void SendCharacterStateAttackPacket(Point2D& c_rkPPosDst, float rot,DWORD comboIndex) { SendCharacterStatePacket(c_rkPPosDst, rot, TypeStateAttack::FUNC_ATTACK, comboIndex); }

	//PYTHON FUNCTIONS
	DWORD GetMainActorVID();
	void SendUseItemPacket(TItemPos pos);
	void SendChatPacket(const char * c_szChat, int byType);


private:

	//PythonWrapper Functions Call
	CInstanceBase* Py_GetSelectedInstance();

	
	//Swicthes
	FunctionType swSelectedInstance;

	//C Functions

	CLASS_POINTER* NetworkClass;
	CPythonCharacterManager* manager;
	tRecvServerCommand fRecvServerCommand;
	tSendChatPacket fSendChatPacket;
	tSendBattleAttack fSendBattleAttack;
	tSendCharacterStatePacket fSendCharacterState;
	tNetworkProcess fNetworkProcess;
	tSendItemClickPacket fSendItemClickPacket;

	tRecv fRecv;

	DWORD m_SelectedInstanceOffset;
	DWORD m_phaseStrOffset;

	//Python Functions
	PythonFunction Py_GetMainActorVID;
	PythonFunction Py_SendItemUsePacket;
	PythonFunction Py_SendChatPacket;
	PythonFunction Py_GetTargetVID;

	
};

