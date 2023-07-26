#include "Transform.h"

namespace Banana
{
  Transform::Transform(const glm::vec3 &pos, const glm::vec2& size, const glm::vec4 &color, float rotation, Projection proj)
  :pos(pos), size(size), color(color), rotation(rotation), proj(proj)
  {

  }

  void Transform::OnUpdate(float dt)
  {

  }

  
};