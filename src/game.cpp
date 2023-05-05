#include "Game.h"

namespace game
{
  banana::BananaWindow Game::win;
  banana::BananaRectangle Game::rect;
  void Game::Init()
  {
    win.h = 720;
    win.w = 1080;
    win.title = "banana";
    win.color = {0.5f, 0.1f, 0.2f, 0.0f};

    banana::Banana::InitBananaWindow(&win);
    

    rect.x = 0;
    rect.y = 0;
    rect.w = 1;
    rect.h = 1;

    rect.r = 1.0;
    rect.g = 0.912;
    rect.b = 0.912;
    
    banana::Banana::AddRectangle(rect);
  }

  void Game::Loop(float dt)
  {
    LOG_GAME("FPS: " + std::to_string(1 / dt));
  }
};