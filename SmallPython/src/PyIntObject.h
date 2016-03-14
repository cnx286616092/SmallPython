#ifndef PY_INT_OBJECT_H
#define PY_INT_OBJECT_H

#include "Python.h"
#include "PyTypeObject.h"


typedef struct tagPyIntObject
{
	PyObject_HEAD;
	int value;
}PyIntObject;

extern PyObject* PyInt_Create(int);

extern PyTypeObject PyInt_Type;

#endif