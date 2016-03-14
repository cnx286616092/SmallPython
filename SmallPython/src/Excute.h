#ifndef EXCUTE_H
#define EXCUTE_H

#include "Python.h"
#include "Common.h"

extern void ExcuteCommand(std::string&);
extern void ExcuteAdd(std::string&, std::string&);
extern PyObject* GetObjectBySymbol(std::string&);
extern void ExcutePrint(std::string);
extern void Excute(void);

#endif