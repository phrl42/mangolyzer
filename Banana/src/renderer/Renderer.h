#pragma once
#include "_Banana.h"

namespace Banana
{
  enum class RendererAPI
  {
    NONE = 0,
    OpenGL
  };

  class Renderer 
  {
  public:
    inline static RendererAPI GetAPI() { return api; }

  private:
    static RendererAPI api;
  };
};