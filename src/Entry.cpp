#include "utils/Entry.h"
#include "game/Game.h"

namespace banana
{
  Entry::Entry(WindowingSystem ws, GraphicsLibrary gl)
  {
    banana::Management::UsedWS = ws;
    banana::Management::UsedGL = gl;

    framework = Framework::GetFramework();
  }

  Entry::~Entry()
  {

  }
  
  void Entry::Init()
  {
    framework->Init(0);
    game::Game::Init();

    Run();
  }

  void Entry::Run()
  {
    Uint64 lastTime = 0;
    float frameTime = 0;
    Uint64 beginTime = 0;

    framework->SetColor(Window::GetMostRecentWindow()->BackgroundColor);
    int x = 0;
    while(x < 10)
    {      
      beginTime = framework->GetTicks();

      framework->Clear();

      // we have milliseconds
      game::Game::Loop((float)(frameTime / 1000));

      framework->Update(Window::GetMostRecentWindow()->GetWindow());

      lastTime = framework->GetTicks();

      frameTime = lastTime - beginTime;
      
      // useful for debugging
      framework->SetWindowTitle(Window::GetMostRecentWindow()->GetWindow(), std::to_string(1 / (frameTime / 1000)));
      x++;
    }
  }
};