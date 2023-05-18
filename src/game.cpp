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
    rect.y = -1;
    rect.w = 1.8;
    rect.h = 1;

    rect.r = 1.0;
    rect.g = 1.0;
    rect.b = 1.0;
    rect.a = 1.0;
    
    rect2.x = -1.0;
    rect2.y = 0;
    rect2.w = 1.8;
    rect2.h = 1;

    rect2.r = 1.0;
    rect2.g = 1;
    rect2.b = 1;
    rect2.a = 1.0;

    rect3.x = -0.5;
    rect3.y = -0.324;
    rect3.w = 1.8;
    rect3.h = 1;

    rect3.r = -0.5;
    rect3.g = 0.912;
    rect3.b = 0.512;
    rect3.a = 1.0;
    
    rect.LoadTexture("src/img/bunker.png");

    Banana::RenderEntity(rect);
    Banana::RenderEntity(rect2);
    Banana::RenderEntity(rect3);
  }

  void Game::Loop(float dt)
  {
    if(banana::Input::IsKeyDown(SDL_SCANCODE_D))
    {
      rect.x += 0.001;
    }
    Banana::RenderEntity(rect);
    Banana::RenderEntity(rect2);
    Banana::RenderEntity(rect3);
  }
};