#include "Game.h"

namespace game
{
  banana::BananaWindow Game::win;
  void Game::Init()
  {
    win.h = 720;
    win.w = 1080;
    win.title = "banana";
    win.color = {1.0f, 1.0f, 1.0f, 0.0f};

    banana::Banana::InitBananaWindow(&win);
  }

  void Game::Loop(float dt)
  {
    LOG_GAME("FPS: " + std::to_string(1 / dt));
  }
};