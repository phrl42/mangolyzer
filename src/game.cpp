#include "Game.h"

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
    rect.x = 0;
    rect.y = 0;
    rect.w = 1;
    rect.h = 1;

    rect.r = 0.0;
    rect.g = -0.912;
    rect.b = 0.512;
    rect.a = 1.0;

    // set second rectangle vars
    rect2.x = -1.0;
    rect2.y = 0;
    rect2.w = 1.0;
    rect2.h = 1;

    rect2.r = 1.0;
    rect2.g = -0.912;
    rect2.b = -0.512;
    rect2.a = 1.0;

    Banana::RenderEntity(rect);
    Banana::RenderEntity(rect2);
  }

  void Game::Loop(float dt)
  {
    LOG_GAME("FPS: " + std::to_string(1 / dt));
    
    if(rect.y <= -1.0f)
    {
      rect.y = 1.0 - rect.h;
    }

    if(rect2.x >= 1.0f)
    {
      rect2.x = -1.0f;
    }

    rect.y -= 0.9 * dt;
    rect2.x += 0.9 * dt;

    Banana::RenderEntity(rect);
    Banana::RenderEntity(rect2);
  }
};