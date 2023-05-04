#pragma once 

#include "utils/incs.h"

namespace banana
{
  class Context 
  {
  public:
    virtual ~Context()  = default;
    static std::shared_ptr<Context> GetWindowContext();

    virtual void SetContext(void* win) = 0;
    virtual void* GetContext() = 0;
  };
};