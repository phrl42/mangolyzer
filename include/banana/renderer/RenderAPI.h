#pragma once
#include "utils/incs.h"

namespace banana
{
  class RenderAPI
  {
  public:    
    static std::shared_ptr<RenderAPI> GetRenderAPI();
    virtual ~RenderAPI() = default;

    virtual void Init() = 0;
  private:

  };
};