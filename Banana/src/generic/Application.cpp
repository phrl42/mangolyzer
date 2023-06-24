#include "Application.hpp"

namespace Banana
{

  Application::Application()
  {
    WindowProps prop;
    prop.Title = "Banana Engine";
    prop.height = 1280;
    prop.width = 720;

    window = Window::Create(prop);

    window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
  }

  void Application::OnEvent(Event& e)
  {
    LOG(e.ToString());
  }

  void Application::Run()
  {
    while(running)
    {
      window->PollEvents();
      //glClearColor(1, 0, 1, 1);

      //glClear(GL_COLOR_BUFFER_BIT);


      window->SwapBuffers();
    }
  }

  Application::~Application()
  {

  }

};