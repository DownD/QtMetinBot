#pragma once
#include "Patterns.h"
#include "Memory.h"
#include "Structs.h"

#define MOB_ACTOR_TYPE 0
#define NPC_ACTOR_TYPE 1
#define METIN_ACTOR_TYPE 2
#define PLAYER_ACTOR_TYPE 6
#define GM_ACTOR_TYPE 55
#define BOSS_ACTOR_TYPE 14


//Should be used as a pointer to memory
//The this pointer sould be the base adress in memory
//The function Initialise should be called before it can be used
//There are functions that are executed trought the python interpreter (PY_FUNCTIONS)
//and trought memory (C_FUNCTIONS)
//The python functions are slow due to the game using VIDs but allows for
//a wide range of compatibilty between servers without the need of patterns
//while the C_functions grants a major improvement on performance sacrificing
//compatability due to pattern missmatching
//The function Initialize will chose the functions to be used
//giving priority to functions that are on the Patterns file. The python functions
//will only be used if the currespondent pattern is'nt found or is missing
//There are some exceptions, where there is'nt a functions available on the interpreter
//wich are marked as Crtical and where there is no meaningfull performance benefits
//on using a C_Function in that case only the python function is available
class CInstanceBase
{
public:

	//THIS NEEDS TO BE CALLED BEFORE IT CAN BE USED AS A OBJECT POINTER
	static bool Initialize(Memory* mem);


	//Wrappers
	float distanceToInstance(CInstanceBase* target);
	inline bool isMonsterEnemy() { BYTE type = getType();return (type == MOB_ACTOR_TYPE) || (type == METIN_ACTOR_TYPE) || (type == BOSS_ACTOR_TYPE) ? true:false;} //includes boss and metins
	inline bool isBoss() { return (getType() == BOSS_ACTOR_TYPE) ? true : false;};
	inline bool isMetin() { return getType() == METIN_ACTOR_TYPE ? true : false;};
	inline bool isMonster() { return getType() == MOB_ACTOR_TYPE; };
	inline bool isPlayer() { return getType() == PLAYER_ACTOR_TYPE ? true : false;};
	inline bool isGM() { return getType() == GM_ACTOR_TYPE; }
	inline bool isPlayerOrGM() { BYTE type = getType();return (type == GM_ACTOR_TYPE) || (type == PLAYER_ACTOR_TYPE) ? true : false;}

	//Python and C Fuctions Supported
	inline BYTE  getType() { return Type_GetType ? Py_getType() : C_getType(); }
	inline DWORD getID() { return Type_getID ? Py_getID() : C_getID();}
	inline void getPosition(Point2D & p) { return Type_getPosition ? Py_getPosition(p) : C_getPosition(p);}
	inline void	 getName(std::string& buffer) { return Type_getName ? Py_getName(buffer) : C_getName(buffer); }
	inline void setRotation(float p) { return Type_Rotation ? Py_setRotation(p) : C_setRotation(p); };
	inline void WalkToPosition(Point2D &a) { return Type_WalkToPosition ? Py_WalkToPosition(a) : C_WalkToPosition(a); };
	inline void setPosition(Point2D & a){ return Type_setPosition ? Py_setPosition(a) : C_setPosition(a); }
	inline float getRotation(){ return Type_Rotation ? Py_getRotation() : C_getRotation(); }

	//Functions that are useless for now
	//inline float getRotation() { return *(float*)((int)this + (m_GraphicInstanceOffset + m_RotationOffset)); }
	

	//Critical
	inline bool isDead() { return *(bool*)((int)this + m_GraphicInstanceOffset + m_IsDead);}
	inline void EnableSkipCollisions(bool colision) { *(BYTE*)((int)this + m_GraphicInstanceOffset + m_EnableSkipCollisionOffset) = colision; }
	inline DWORD getVID() { return *(DWORD*)((int)this + m_GraphicInstanceOffset + m_VID); }

private:
	void SelectInstance(DWORD vid);


private:

	//C function Call
	inline BYTE	C_getType() { return *(BYTE*)((int)this + (m_GraphicInstanceOffset + m_ActorTypeOffset));}
	inline DWORD C_getID() { return *(DWORD*)((int)this + (m_GraphicInstanceOffset + m_IDOffset)); }
	inline void C_getPosition(Point2D & p) { p = *(Point2D*)((int)this + (m_GraphicInstanceOffset + m_PositionOffset)); p.absoluteY(); }
	void C_getName(std::string& buffer);
	inline void C_setRotation(float rot) { *(float*)((int)this + (m_GraphicInstanceOffset + m_RotationOffset)) = rot; }
	inline void C_WalkToPosition(Point2D &p){ p.absoluteY(); _WalkToPosition((DWORD)this, p); }
	inline void C_setPosition(Point2D & a) { _C_setPosition((DWORD)this, a.x, a.y); }
	inline float C_getRotation() { return *(float*)((int)this + (m_GraphicInstanceOffset + m_RotationOffset)); }
	
	
	//Py Function Call
	BYTE Py_getType();
	DWORD Py_getID();
	void Py_getPosition(Point2D & p);
	void Py_getName(std::string& buffer);
	void Py_setRotation(float p);
	void Py_WalkToPosition(Point2D pos);
	void Py_setPosition(Point2D a);
	float Py_getRotation();



private:
	static FunctionType			Type_GetType;
	static PythonFunction		_GetType;

	static FunctionType			Type_getID;
	static PythonFunction		_getID;

	static FunctionType			Type_getPosition;
	static PythonFunction		_getPosition;

	static FunctionType			Type_setPosition;
	static PythonFunction		_setPosition;

	static FunctionType			Type_getName;
	static PythonFunction		_getName;

	static FunctionType			Type_WalkToPosition;
	static PythonFunction		_moveToDestPosition;

	static FunctionType			Type_Rotation;
	static PythonFunction		_getRotation;
	static PythonFunction		_setRotation;

	static PythonFunction		_selectInstance;

private:
	static DWORD m_GraphicInstanceOffset;
	static BYTE m_NameOffset;

	static FunctionPtr<void, DWORD, Point2D&> _WalkToPosition;
	static FunctionPtr<void, DWORD, float, float> _C_setPosition;

	//ActorInstance
	static DWORD m_EnableSkipCollisionOffset;
	static DWORD m_ActorTypeOffset;
	static DWORD m_IDOffset;
	static DWORD m_PositionOffset;
	static DWORD m_RotationOffset;
	static DWORD m_IsDead;
	static DWORD m_VID;
};
