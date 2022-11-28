#include "../include/misc.h"

int miscRand(int min, int max)
{
    int diff = max - min;
    // stackoverflow magic
    return (int)(((double)(diff + 1) / RAND_MAX) * rand() + min); // math is powerful / useful(!!)
}
void Log(char *msg, enum LogType type)
{
  switch(type)
  {
    case Error:
      printf("\033[0;31m%s\033[0m\n", msg);
      break;
    case Info:
      printf("\033[0;34m%s\033[0m\n", msg);
      break;
    default:
      break;
  }
}
