#include "utils/Management.h"
#include "utils/incs.h"
#include "utils/Entry.h"

using namespace banana;

int main()
{
  banana::WindowingSystem ws = WindowingSystem::None;
  banana::GraphicsLibrary gl = GraphicsLibrary::None;

#ifdef MACRO_SDL2
ws = WindowingSystem::SDL2;
#endif

#ifdef MACRO_GLFW
ws = WindowingSystem::GLFW;
#endif

#ifdef MACRO_OPENGL
gl = GraphicsLibrary::OpenGL;
#endif

#ifdef MACRO_VULKAN
gl = GraphicsLibrary::Vulkan;
#endif

  // set desired options
  Entry entry = Entry(ws, gl);

  entry.Init();
  
  return 0;
}