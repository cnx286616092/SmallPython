#ifndef PY_TYPE_OBJECT_H
#define PY_TYPE_OBJECT_H

#include "PyObject.h"

typedef void(*PrintFun)(PyObject* object);
typedef PyObject* (*AddFun)(PyObject* left, PyObject* right);
typedef long(*HashFun)(PyObject* object);

typedef struct tagPyTypeObject
{
	PyObject_HEAD;
	char* name;
	PrintFun print;
	AddFun   add;
	HashFun  hash;
}PyTypeObject;

extern PyTypeObject PyType_Type;

#endif
