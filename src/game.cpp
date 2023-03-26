#include "Game.h"

namespace game
{
  banana::BananaWindow Game::win;
  void Game::Init()
  {
    win.h = 100;
    win.w = 100;
    win.title = "bomb";
    win.color = {1.0f, 1.0f, 1.0f, 0.0f};

    banana::Banana::InitBananaWindow(&win);
  }

  void Game::Loop(float dt)
  {
    LOG_GAME("bunker carlos " + std::to_string(dt));
  }
};