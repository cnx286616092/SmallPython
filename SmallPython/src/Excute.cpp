#include "Excute.h"


PyObject* m_LocalEnvironment;
const char* info = "********** Python Research **********\n";
const char* prompt = ">>>";

int main(void)
{
	m_LocalEnvironment = (PyObject*)PyDict_Create();
	Excute();
	return 0;
}

void ExcuteCommand(std::string& command)
{
	std::string::size_type pos = 0;
	if ((pos = command.find("print ")) != std::string::npos)
	{
		ExcutePrint(command.substr(6));
	}
	else if ((pos = command.find(" = ")) != std::string::npos)
	{
		std::string target = command.substr(0, pos);
		std::string source = command.substr(pos + 3);
		ExcuteAdd(target, source);
	}
}

static bool IsSourceAllDigit(std::string& source)
{
	int len = source.size();
	for (int i = 0; i < len; i++)
	{
		if (source[i]<'0' || source[i] > '9')
			return false;
	}
	return true;
}

void ExcuteAdd(std::string& target, std::string& source)
{
	std::string::size_type pos = 0;
	PyObject* strValue = NULL;
	PyObject* resultValue = NULL;
	if (IsSourceAllDigit(source))
	{
		PyObject* intValue = PyInt_Create(atoi(source.c_str()));
		PyObject* key = PyStr_Create(target.c_str());
		PyDict_SetItem(m_LocalEnvironment, key, intValue);
	}
	else if (source.find("\"") != std::string::npos)
	{
		strValue = PyStr_Create(source.substr(1, source.size() - 2).c_str());
		PyObject* key = PyStr_Create(target.c_str());
		PyDict_SetItem(m_LocalEnvironment, key, strValue);
	}
	else if ((pos = source.find("+")) != std::string::npos)
	{
		PyObject* leftObject = GetObjectBySymbol(source.substr(0, pos));
		PyObject* rightObject = GetObjectBySymbol(source.substr(pos + 1));
		if (leftObject != NULL && rightObject != NULL &&
			leftObject->type == rightObject->type)
		{
			resultValue = (leftObject->type)->add(leftObject, rightObject);
			PyObject* key = PyStr_Create(target.c_str());
			PyDict_SetItem(m_LocalEnvironment, key, resultValue);
		}
		//(m_LocalEnvironment->type)->print(m_LocalEnvironment);
	}
}

PyObject* GetObjectBySymbol(std::string& symbol)
{
	PyObject* key = PyStr_Create(symbol.c_str());
	PyObject* value = PyDict_GetItem(m_LocalEnvironment, key);
	if (NULL == value)
	{
		printf("[Error] : %s is not define!!\n", symbol.c_str());
		return NULL;
	}
	return value;
}

void ExcutePrint(std::string symbol)
{
	PyObject* object = GetObjectBySymbol(symbol);
	if (object != NULL)
	{
		object->type->print(object);
	}
}

void Excute(void)
{
	std::string m_Command;
	printf("%s%s", info, prompt);
	while (std::getline(std::cin, m_Command))
	{
		if (0 == m_Command.size())
		{
			printf("%s", prompt);
			continue;
		}
		else if ("exit" == m_Command)
		{
			return;
		}
		else
		{
			ExcuteCommand(m_Command);
		}
		printf("%s", prompt);
	}
}