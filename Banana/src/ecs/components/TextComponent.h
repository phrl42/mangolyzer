#pragma once
#include "_Banana.h"
#include "ecs/Component.h"

namespace Banana
{
  class TextComponent : public Component
  {
  public:
    virtual ~TextComponent() = default;

    TextComponent(const std::string& text);

    virtual void OnUpdate(float dt, const Transform& transform) override;
    
  private:

  };
};