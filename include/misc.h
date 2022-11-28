#ifndef __MISC_H__
#define __MISC_H__

#include "incs.h"

enum LogType {Error, Info};

int miscRand(int min, int max);

void Log(char *msg, enum LogType type);

#endif
