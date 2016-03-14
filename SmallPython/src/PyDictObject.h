#ifndef PY_DICT_OBJECT_H
#define PY_DICT_OBJECT_H

#include "Python.h"
#include "PyTypeObject.h"

typedef struct tagPyDictObject
{
	PyObject_HEAD;
	std::map<long, PyObject*> dict;
}PyDictObject;

extern PyObject* PyDict_Create(void);
extern PyObject* PyDict_GetItem(PyObject*, PyObject*);
extern int PyDict_SetItem(PyObject*, PyObject*, PyObject*);

extern PyTypeObject PyDict_Type;

#endif