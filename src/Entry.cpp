#include "utils/Entry.h"

#include "events/Input.h"

#include "renderer/Renderer.h"

namespace banana
{
  Entry::Entry()
  {


  }

  Entry::~Entry()
  {

  }
  
  void Entry::Init()
  {
    #ifdef MACRO_SDL2
    banana::Management::UsedWS = WindowingSystem::SDL2;
    #endif

    #ifdef MACRO_GLFW
    banana::Management::UsedWS = WindowingSystem::GLFW;
    #endif

    #ifdef MACRO_OPENGL
    banana::Management::UsedGL = GraphicsLibrary::OpenGL;
    #endif

    #ifdef MACRO_VULKAN
    banana::Management::UsedGL = GraphicsLibrary::Vulkan;
    #endif

    framework = Framework::GetFramework();

    renderAPI = RenderAPI::GetRenderAPI();

    renderCommand = RenderCommand::GetRenderCommand();

    framework->Init(0);

    GameScene = std::make_shared<game::Game>();
      
    GameScene->Init();
      
    renderAPI->Init();
      
    Run();
  }

  void Entry::Run()
  {
    Uint64 lastTime = 0;
    float frameTime = 0;
    Uint64 beginTime = 0;

    framework->SetColor(Window::GetMostRecentWindow()->BackgroundColor);

    Renderer::Init();
    //Input::Check();
    
    while(!Input::IsKeyDown(SDL_SCANCODE_ESCAPE))
    {
      Input::Check();
      beginTime = framework->GetTicks();

      framework->Clear();

      // we have milliseconds
      GameScene->Loop((float)(frameTime / 1000));
      
      Renderer::Render();

      framework->Update(Window::GetMostRecentWindow()->GetWindow());


      lastTime = framework->GetTicks();

      frameTime = lastTime - beginTime;
      
      // useful for debugging
      framework->SetWindowTitle(Window::GetMostRecentWindow()->GetWindow(), std::to_string(1 / (frameTime / 1000)));

    }
  }
};