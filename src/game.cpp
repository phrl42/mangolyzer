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
    
    rect.x = 0;
    rect.y = 0;
    rect.w = 1;
    rect.h = 1;

    rect.r = 0.0;
    rect.g = -0.912;
    rect.b = 0.512;
    rect.a = 1.0;

    rect2.x = -1.0;
    rect2.y = 0;
    rect2.w = 1.0;
    rect2.h = 1;

    rect2.r = 1.0;
    rect2.g = -0.912;
    rect2.b = -0.512;
    rect2.a = 1.0;
    
    Banana::AddRectangle(rect);
    Banana::AddRectangle(rect2);
  }

  void Game::Loop(float dt)
  {
    LOG_GAME("FPS: " + std::to_string(1 / dt));
  }
};