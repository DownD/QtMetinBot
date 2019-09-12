#include "PythonUtils.h"



bool PyTuple_GetString(PyObject* poArgs, int pos, char** ret)
{
	PyObject* poItem = PyTuple_GetItem(poArgs, pos);

	if (!poItem)
		return false;

	*ret = PyString_AsString(poItem);
	return true;
}

bool PyTuple_GetInteger(PyObject* poArgs, int pos, int* ret)
{
	PyObject* poItem = PyTuple_GetItem(poArgs, pos);

	if (!poItem)
		return false;

	*ret = PyLong_AsLong(poItem);
	return true;
}

bool PyRunFile(char* full_path)
{
	/*FILE* file = fopen(full_path, "r");
	if (!file) {
		DEBUG_INFO(COLOR_DEFAULT, "Error Opening File %s", full_path);
		return false;
	}*/
	char* arr = new char[strlen(full_path)];
	strcpy(arr, full_path);
	PathStripPathA(arr);

	PyObject* PyFileObject = PyFile_FromString(full_path, (char*)"r");
	bool result = !PyRun_SimpleFileEx(PyFile_AsFile(PyFileObject), arr, 1);
	delete[] arr;
	return result;
}

bool PyRunLine(char * line)
{
	return PyRun_SimpleString(line);
}

bool PyTuple_GetByte(PyObject* poArgs, int pos, unsigned char* ret)
{
	int val;
	bool result = PyTuple_GetInteger(poArgs, pos, &val);
	*ret = unsigned char(val);
	return result;
}

bool PyTuple_GetFloat(PyObject* poArgs, int pos, float* ret)
{
	PyObject * poItem = PyTuple_GetItem(poArgs, pos);

	if (!poItem)
		return false;

	*ret = float(PyFloat_AsDouble(poItem));
	return true;
}