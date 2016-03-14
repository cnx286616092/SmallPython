#ifndef PY_STR_OBJECT_H
#define PY_STR_OBJECT_H

#include "Python.h"
#include "PyTypeObject.h"

typedef struct tagPyStrObject
{
	PyObject_HEAD;
	int length;
	long hashValue;
	char value[50];
}PyStrObject;

extern PyObject* PyStr_Create(const char*);

extern PyTypeObject PyString_Type;

#endif