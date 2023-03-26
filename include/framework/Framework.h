#pragma once
#include "utils/incs.h"

namespace banana
{
  class Framework
  {
  public:
    virtual ~Framework() = default;

    virtual void Init(Uint32 flags) = 0;

    virtual void SetColor(glm::vec4 color) = 0;
    virtual void Clear() = 0;

    virtual void Update(void* window) = 0;

    static std::shared_ptr<Framework> GetFramework();

  };
};