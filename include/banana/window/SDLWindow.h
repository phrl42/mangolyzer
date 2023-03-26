#pragma once

#include "utils/incs.h"
#include "game/info.h"
#include "Window.h"

#include <SDL2/SDL.h>

namespace banana
{
  class SDLWindow : public Window
  {
  public:
    SDLWindow();
    ~SDLWindow() override;

    void Init(std::string title, int width, int height) override;

    void* GetWindow() override;

    void SetUseInfo();
  private:
    SDL_GLContext con;
    SDL_Window* win;
  };
};
