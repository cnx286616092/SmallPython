#include "PyStrObject.h"

PyObject* PyStr_Create(const char* value)
{
	PyStrObject* object = new PyStrObject;

	object->reCount = 1;
	object->type = &PyString_Type;
	object->length = (NULL == value) ? 0 : strlen(value);
	object->hashValue = -1;

	memset(object->value, 0, 50);

	if (value != NULL)
	{
		strcpy_s(object->value, value);
	}

	return (PyObject*)object;
}
static void string_print(PyObject* object)
{
	PyStrObject* strObject = (PyStrObject*)object;
	printf("%s\n", strObject->value);
}
static long string_hash(PyObject* object)
{
	PyStrObject* strObject = (PyStrObject*)object;
	register int len;
	register unsigned char *p;
	register long x;

	if (strObject->hashValue != -1)
		return strObject->hashValue;

	len = strObject->length;
	p = (unsigned char*)strObject->value;
	x = *p << 7;
	
	while (--len >= 0)
		x = (1000003 * x) ^ *p++;
	x ^= strObject->length;
	if (-1 == x)
		x = -2;
	strObject->hashValue = x;

	return x;
}
static PyObject* string_add(PyObject* left, PyObject* right)
{
	PyStrObject* strLeft = (PyStrObject*)left;
	PyStrObject* strRight = (PyStrObject*)right;
	PyStrObject* result = (PyStrObject*)PyStr_Create(NULL);

	if (NULL == result)
	{
		printf("There is no enough memory\n");
		exit(1);
	}
	else
	{
		strcpy_s(result->value, strLeft->value);
		strcat_s(result->value, strRight->value);
	}
		
	return (PyObject*)result;
}

PyTypeObject PyString_Type =
{
	PyObject_HEAD_INIT(&PyType_Type),
	"str",
	string_print,
	string_add,
	string_hash
};