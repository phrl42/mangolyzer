#pragma once
#include "_Banana.h"

namespace Banana
{
  class Component
  {
  public:
    virtual ~Component() = default;

    virtual void OnUpdate(float dt) = 0;

    const std::string& GetName() const { return name; }
  protected:
    std::string name;
  };

};