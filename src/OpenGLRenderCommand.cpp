#include "renderer/opengl/OpenGLRenderCommand.h"

#ifdef MACRO_SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#endif

#include "window/Window.h"

namespace banana
{

  OpenGLRenderCommand::OpenGLRenderCommand()
  {
  }

  OpenGLRenderCommand::~OpenGLRenderCommand()
  {
    
  }

  void OpenGLRenderCommand::Clear()
  {
    glClear(GL_COLOR_BUFFER_BIT);
  }

  void OpenGLRenderCommand::SetColor(glm::vec4 color)
  {
    glClearColor(color.r, color.g, color.b, color.a);
  }

  void OpenGLRenderCommand::Update(void* window)
  {
    switch(banana::Management::UsedWS)
    {
      case WindowingSystem::SDL2:
        SDL_GL_SwapWindow((SDL_Window*)window);
        break;
      default:
        break;
    }
  }
};