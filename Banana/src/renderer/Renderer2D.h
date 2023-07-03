#pragma once
#include "_Banana.h"
#include "utility.h"

namespace Banana
{
  class Renderer2D
  {
  public:

    static void Init();
    static void Shutdown();

    static void BeginScene();
    static void EndScene();

    static void Flush();

    static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
  };
};