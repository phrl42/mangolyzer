#include "framework/SDLFramework.h"

#include <SDL2/SDL.h>

namespace banana {

SDLFramework::SDLFramework()
{
  renderCommand = RenderCommand::GetRenderCommand();
}

SDLFramework::~SDLFramework()
{
  SDL_Quit();
}

void SDLFramework::Init(Uint32 flags) 
{
  // use 0 for fallback
  /* flags:
  SDL_INIT_TIMER: timer subsystem
  SDL_INIT_AUDIO: audio subsystem
  SDL_INIT_VIDEO: video subsystem; automatically initializes the events
  subsystem SDL_INIT_JOYSTICK: joystick subsystem; automatically initializes the
  events subsystem SDL_INIT_HAPTIC: haptic (force feedback) subsystem
  SDL_INIT_GAMECONTROLLER: controller subsystem; automatically initializes the
  joystick subsystem SDL_INIT_EVENTS: events subsystem SDL_INIT_EVERYTHING: all
  of the above subsystems (fallback) SDL_INIT_NOPARACHUTE: compatibility; this
  flag is ignored
  */

  // 0 = SDL_INIT_EVERYTHING
  if (flags == (Uint32)0)
    flags = SDL_INIT_EVERYTHING;

  // error handling
  if (SDL_Init(flags) != 0) 
  {
    LOG_CORE("Failed to initialize SDL");
    return;
  }
}

void SDLFramework::Clear()
{
  switch(banana::Management::UsedGL)
  {
    case GraphicsLibrary::OpenGL:
      renderCommand->Clear();
      break;
    default:
      break;
  }
}

void SDLFramework::SetColor(glm::vec4 color)
{
  switch(banana::Management::UsedGL)
  {
    case GraphicsLibrary::OpenGL:
      renderCommand->SetColor(color);
      break;
    default:
      break;
  }
}

Uint64 SDLFramework::GetTicks()
{
  return SDL_GetTicks64();
}

void SDLFramework::SetWindowTitle(void* window, std::string title)
{
  SDL_SetWindowTitle((SDL_Window*)window, title.c_str());
}

void SDLFramework::Update(void* window)
{
  switch(banana::Management::UsedGL)
  {
    case GraphicsLibrary::OpenGL:
      renderCommand->Update(window);
      break;
    default:
      break;
  }
}

}; // namespace banana