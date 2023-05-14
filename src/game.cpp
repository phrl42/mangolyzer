#include "Game.h"

#include "events/Input.h"

namespace game
{
  void Game::Init()
  {
    win.h = 720;
    win.w = 1080;
    win.title = "banana";
    win.color = {0.5f, 0.1f, 0.2f, 0.0f};

    Banana::InitBananaWindow(win);
    
    // set first rectangle vars
    rect.x = -1.0;
    rect.y = 0;
    rect.w = 1.8;
    rect.h = 1;

    rect.r = 0.0;
    rect.g = -0.912;
    rect.b = 0.512;
    rect.a = 1.0;

    Banana::RenderEntity(rect);
  }

  void Game::Loop(float dt)
  {
    Banana::RenderEntity(rect);
  }
};