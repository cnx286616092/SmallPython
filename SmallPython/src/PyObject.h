#ifndef PY_OBJECT_H
#define PY_OBJECT_H

#define PyObject_HEAD	\
		int reCount;	\
		struct tagPyTypeObject *type

#define PyObject_HEAD_INIT(typePtr) \
		0, typePtr

typedef struct tagPyObject
{
	PyObject_HEAD;
}PyObject;


#endif
