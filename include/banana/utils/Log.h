#pragma once
#include "incs.h"

#define MAXLEN 1000

inline void LOG_CORE(std::string msg)
{
  std::cout << "[CORE]: " << msg << std::endl;
};

inline void LOG_GAME(std::string msg)
{
  std::cout << "[GAME]: " << msg << std::endl;
};