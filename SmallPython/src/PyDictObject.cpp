#include "PyDictObject.h"

PyObject* PyDict_Create(void)
{
	PyDictObject* object = new PyDictObject;
	object->reCount = 1;
	object->type = &PyDict_Type;

	return (PyObject*)object;
}

PyObject* PyDict_GetItem(PyObject* target, PyObject* key)
{
	long keyHashValue = (key->type)->hash(key);
	std::map<long, PyObject*>& dict = ((PyDictObject*)target)->dict;
	std::map<long, PyObject*>::iterator it = dict.find(keyHashValue);
	std::map<long, PyObject*>::iterator end = dict.end();

	if (it == end)
		return NULL;

	return it->second;
}

int PyDict_SetItem(PyObject* target, PyObject* key, PyObject* value)
{
	long keyHashValue = (key->type)->hash(key);
	PyDictObject* dictObject = (PyDictObject*)target;
	(dictObject->dict)[keyHashValue] = value;
	return 0;
}

static void dict_print(PyObject* object)
{
	PyDictObject* dictObject = (PyDictObject*)object;
	printf("{");
	std::map<long, PyObject*>::iterator it = (dictObject->dict).begin();
	std::map<long, PyObject*>::iterator end = (dictObject->dict).end();

	for (; it != end; it++)
	{
		printf("%ld : ", it->first);
		PyObject* value = it->second;
		(value->type)->print(value);
		printf(" ");
	}
	printf("\n");
}

PyTypeObject PyDict_Type =
{
	PyObject_HEAD_INIT(&PyType_Type),
	"dict",
	dict_print,
	0,
	0
};