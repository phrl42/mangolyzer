#include "renderer/Renderer.h"
#include <SDL2/SDL_render.h>
#include "renderer/opengl/OpenGLShader.h"

namespace banana
{
  struct RenderStruct
  {
    RenderStruct()
    {

    };
    OpenGLShader shader = OpenGLShader();
  };

  void Renderer::Init()
  {
    RenderStruct renderInfo;
    renderInfo.shader.LoadShader("src/shader/default.glsl");
  }

  void Renderer::AddRectangle()
  {
    
  }
};