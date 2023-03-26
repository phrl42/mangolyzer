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
    framework->SetColor(Window::GetMostRecentWindow()->BackgroundColor);
    while(1)
    {
      framework->Clear();
      game::Game::Loop(4.2f);
      framework->Update(Window::GetMostRecentWindow()->GetWindow());
    }
  }
};