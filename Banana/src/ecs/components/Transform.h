#pragma once
#include "_Banana.h"
#include "ecs/Component.h"

namespace Banana
{
  class Transform : public Component
  {
  public:
    virtual ~Transform() = default;

    Transform(const glm::vec3 &pos, const glm::vec2& size, const glm::vec4 &color, float rotation, Projection proj);

    virtual void OnUpdate(float dt) override;

  public:
    glm::vec3 pos;
    glm::vec2 size;
    glm::vec4 color;
    float rotation = 0;

    Projection proj = Projection::NONE;
  };
};