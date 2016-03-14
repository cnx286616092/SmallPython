#include "PyIntObject.h"

PyObject* PyInt_Create(int value)
{
	PyIntObject* object = new PyIntObject;
	object->reCount = 1;
	object->type = &PyInt_Type;
	object->value = value;
	return (PyObject*)object;
}

static void int_print(PyObject* object)
{
	PyIntObject* IntObject = (PyIntObject*)object;
	printf("%d\n", IntObject->value);
}

static PyObject* int_add(PyObject* left, PyObject* right)
{
	PyIntObject* leftInt = (PyIntObject*)left;
	PyIntObject* rightInt = (PyIntObject*)right;
	PyIntObject* result = (PyIntObject*)PyInt_Create(0);

	if (NULL == result)
	{
		printf("There is no enough memory!\n");
		exit(1);
	}
	else
	{
		result->value = leftInt->value + rightInt->value;
	}
	return (PyObject*)result;
}

static long int_hash(PyObject* object)
{
	return (long)((PyIntObject*)object)->value;
}

PyTypeObject PyInt_Type =
{
	PyObject_HEAD_INIT(&PyType_Type),
	"int",
	int_print,
	int_add,
	int_hash
};