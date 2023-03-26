#pragma once

namespace banana
{
  enum class GraphicsLibrary { OpenGL = 0, Vulkan};
  enum class WindowingSystem { SDL2 = 0, GLFW };
  class Management
  {
  public:
    static GraphicsLibrary UsedGL;
    static WindowingSystem UsedWS;
  };
};