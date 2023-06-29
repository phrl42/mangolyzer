#include "renderer/Renderer.h"

namespace Banana
{
  #ifdef MACRO_OPENGL
  RendererAPI Renderer::api = RendererAPI::OpenGL;
  #else
  RendererAPI Renderer::api = RendererAPI::NONE;
  #endif
  
};