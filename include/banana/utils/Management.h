#pragma once

namespace banana
{
  enum class GraphicsLibrary { OpenGL = 0, Vulkan, None};
  enum class WindowingSystem { SDL2 = 0, GLFW, None};
  class Management
  {
  public:
    static GraphicsLibrary UsedGL;
    static WindowingSystem UsedWS;
  };
};