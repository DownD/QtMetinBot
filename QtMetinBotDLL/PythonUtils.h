#pragma once
#if defined(_DEBUG)
# undef _DEBUG
# include <Python.h>
# define _DEBUG
#else
# include <Python.h>
#endif
#include <shlwapi.h>
#include "DebugInfo.h"
#include "stdio.h"
#include <string>



bool PyTuple_GetString(PyObject* poArgs, int pos, char** ret);
bool PyTuple_GetByte(PyObject* poArgs, int pos, unsigned char* ret);
bool PyTuple_GetFloat(PyObject* poArgs, int pos, float* ret);
bool PyTuple_GetInteger(PyObject* poArgs, int pos, int* ret);

//Full_path will be changed
bool PyRunFile(char* full_path);
bool PyRunLine(char* line);