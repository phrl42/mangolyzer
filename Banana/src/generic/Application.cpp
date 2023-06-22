#include "Application.h"

namespace Banana
{

  Application::Application()
  {
    WindowProps prop;
    prop.Title = "Banana Engine";
    prop.height = 1280;
    prop.width = 720;

    window = Window::Create(prop);
  }

  void Application::Run()
  {
    while(running)
    {
      window->PollEvents();


      window->SwapBuffers();
    }
  }

  Application::~Application()
  {

  }

};