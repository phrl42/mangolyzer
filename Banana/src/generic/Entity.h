#pragma once
#include "_Banana.h"
#include "renderer/Texture.h"

namespace Banana
{
  struct Entity2D
  {
    glm::vec3 pos;
    glm::vec2 size;
    glm::vec4 color;
    float rotation = 0;

    Shr<Texture2D> tex = nullptr;

    Banana::Projection proj = Banana::Projection::NONE;
  };
};