#include "CInstanceBase.h"

#define STRING_LENGTH_OFFSET 0x10
#define STRING_MAX_LENGTH 15

DWORD CInstanceBase::m_GraphicInstanceOffset = 0;
BYTE CInstanceBase::m_NameOffset = 0;

//ActorInstance
DWORD				CInstanceBase::m_EnableSkipCollisionOffset = 0;
DWORD				CInstanceBase::m_ActorTypeOffset = 0;
DWORD				CInstanceBase::m_IDOffset = 0;
DWORD				CInstanceBase::m_PositionOffset = 0;
DWORD				CInstanceBase::m_RotationOffset = 0;
DWORD				CInstanceBase::m_IsDead = 0;
DWORD				CInstanceBase::m_VID = 0;



FunctionType		CInstanceBase::Type_GetType = 0;
PythonFunction		CInstanceBase::_GetType = 0;
FunctionType		CInstanceBase::Type_getID = 0;
PythonFunction		CInstanceBase::_getID = 0;
FunctionType		CInstanceBase::Type_getPosition = 0;
PythonFunction		CInstanceBase::_getPosition = 0;
FunctionType		CInstanceBase::Type_setPosition = 0;
PythonFunction		CInstanceBase::_setPosition = 0;
FunctionType		CInstanceBase::Type_getName = 0;
PythonFunction		CInstanceBase::_getName = 0;
FunctionType		CInstanceBase::Type_WalkToPosition = 0;
PythonFunction		CInstanceBase::_moveToDestPosition = 0;
FunctionType		CInstanceBase::Type_Rotation = 0;
PythonFunction		CInstanceBase::_getRotation = 0;
PythonFunction		CInstanceBase::_setRotation = 0;
PythonFunction		CInstanceBase::_selectInstance = 0;

FunctionPtr<void, DWORD, Point2D&> CInstanceBase::_WalkToPosition = 0;
FunctionPtr<void, DWORD, float, float> CInstanceBase::_C_setPosition = 0;


bool CInstanceBase::Initialize(Memory* mem)
{
	m_GraphicInstanceOffset = mem->GetCMethod<DWORD>("m_GraphicInstance",DEREFERENCE,CRITICAL);
#ifdef ORIGINS_SERVER
	m_NameOffset = 0x10;
#else
#ifdef AELDRA_SERVER
	m_NameOffset = 0x1C;
#else
	m_NameOffset = mem->GetCMethod<DWORD>("m_InstanceName", DEREFERENCE, CRITICAL);
#endif
#endif

	if (m_GraphicInstanceOffset) {
#ifdef IMPERUS_SERVER
		m_EnableSkipCollisionOffset = 0x578;
#else
#ifdef ORIGINS_SERVER
		m_EnableSkipCollisionOffset = 0x644;
#else
		m_EnableSkipCollisionOffset = mem->GetCMethod<DWORD>("m_EnableSkipCollision", DEREFERENCE, 1);
#endif
#endif

		m_ActorTypeOffset = mem->GetCMethod<DWORD>("m_ActorType", DEREFERENCE);
		m_IDOffset = mem->GetCMethod<DWORD>("m_ID", DEREFERENCE);
		m_PositionOffset = mem->GetCMethod<DWORD>("m_Position", DEREFERENCE);
		m_RotationOffset = mem->GetCMethod<DWORD>("m_Rotation", DEREFERENCE);
		m_IsDead = mem->GetCMethod<DWORD>("m_IsDead", DEREFERENCE, CRITICAL);
		m_VID = mem->GetCMethod<DWORD>("m_VID", DEREFERENCE, CRITICAL);
	}

	_C_setPosition = mem->GetCMethod<FunctionPtr<void, DWORD, float, float>>("SetCurPixelPosition", NO_DEREFERENCE);
	_WalkToPosition = mem->GetCMethod<FunctionPtr<void, DWORD, Point2D&>>("MoveToFunc", NO_DEREFERENCE);

	_GetType = mem->GetPythonMethod(CHR_PYTHON_MODULE, "GetInstanceType");
	_getID = mem->GetPythonMethod(CHR_PYTHON_MODULE, "GetVirtualNumber");
	_getPosition = mem->GetPythonMethod(CHR_PYTHON_MODULE, "GetPixelPosition");
	_getName = mem->GetPythonMethod(CHR_PYTHON_MODULE, "GetNameByVID");
	_setRotation = mem->GetPythonMethod(CHR_PYTHON_MODULE, "SetRotation");
#ifndef AELDRA_SERVER
	_moveToDestPosition = mem->GetPythonMethod(CHR_PYTHON_MODULE, "MoveToDestPosition");
#endif
	_selectInstance = mem->GetPythonMethod(CHR_PYTHON_MODULE, "SelectInstance");
	_setPosition = mem->GetPythonMethod(CHR_PYTHON_MODULE, "SetPixelPosition");
	_getRotation = mem->GetPythonMethod(CHR_PYTHON_MODULE, "GetRotation");

	if (m_ActorTypeOffset && m_GraphicInstanceOffset) Type_GetType = C_FUNCTION; else Type_GetType = PY_FUNCTION;
	if (m_IDOffset && m_GraphicInstanceOffset) Type_getID =	C_FUNCTION; else Type_getID = PY_FUNCTION;
	if(m_PositionOffset && m_GraphicInstanceOffset) Type_getPosition = C_FUNCTION; else Type_getPosition = PY_FUNCTION;
	if (m_NameOffset) Type_getName = C_FUNCTION; else Type_getName = PY_FUNCTION;
	if (_WalkToPosition) Type_WalkToPosition = C_FUNCTION; else Type_WalkToPosition = PY_FUNCTION;
	if (m_RotationOffset && m_GraphicInstanceOffset) Type_Rotation = C_FUNCTION; else Type_Rotation = PY_FUNCTION;
	if (_C_setPosition) Type_setPosition = C_FUNCTION; else Type_setPosition = PY_FUNCTION;

	return true;
}
float CInstanceBase::distanceToInstance(CInstanceBase * target)
{
	Point2D a;
	Point2D b;
	getPosition(a);
	target->getPosition(b);
	return a.distance(&b);
}
void CInstanceBase::SelectInstance(DWORD vid)
{
	_selectInstance(NULL, Py_BuildValue("(i)", vid));
}
void CInstanceBase::C_getName(std::string& buffer)
{
	char* name = (char*)((int)this + m_NameOffset);
	int string_length = (int)*(int*)((int)name + STRING_LENGTH_OFFSET);
	if (string_length > STRING_MAX_LENGTH)
		name = (char*)*(char**)name;
	
	buffer = name;
}

BYTE CInstanceBase::Py_getType()
{
	PyObject* result = _GetType(NULL, Py_BuildValue("(i)", getVID()));

	int type = -1;
	type = PyInt_AS_LONG(result);
	return (BYTE)type;
}

DWORD CInstanceBase::Py_getID()
{
	PyObject* result = _getID(NULL, Py_BuildValue("(i)", getVID()));

	int id = -1;
	id = PyInt_AS_LONG(result);
	return (DWORD)id;
}

void CInstanceBase::Py_getPosition(Point2D & p)
{
	PyObject* result = _getPosition(NULL, Py_BuildValue("(i)", getVID()));
	PyTuple_GetFloat(result, 0, &p.x);
	PyTuple_GetFloat(result, 1, &p.y);
	p.absoluteY();
}

void CInstanceBase::Py_getName(std::string & buffer)
{
	char* name = 0;
	PyObject* result = _getName(NULL, Py_BuildValue("(i)", getVID()));
	name = PyString_AsString(result);
	buffer = name;
}

void CInstanceBase::Py_setRotation(float p)
{
	SelectInstance(getVID());
	_setRotation(NULL, Py_BuildValue("(f)",p));
}

void CInstanceBase::Py_WalkToPosition(Point2D pos)
{
	pos.absoluteY();
	_moveToDestPosition(NULL, Py_BuildValue("(iii)", getVID(), pos.getIntX(), pos.getIntY()));
}

void CInstanceBase::Py_setPosition(Point2D a)
{
	SelectInstance(getVID());
	a.absoluteY();
	_setPosition(NULL, Py_BuildValue("(ii)", a.getIntX(), a.getIntY()));
}

float CInstanceBase::Py_getRotation()
{
	PyObject* result = _setRotation(NULL, Py_BuildValue("()"));
	return (float)PyFloat_AS_DOUBLE(result);

}
