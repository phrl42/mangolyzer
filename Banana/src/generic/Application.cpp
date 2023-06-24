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
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

    for(auto it = layer_stack.end(); it != layer_stack.begin();)
    {
      (*--it)->OnEvent(e);

      if(e.handled)
      {
        break;
      }
    }
  }

  bool Application::OnWindowClose(WindowCloseEvent& e)
  {
    running = false;
    return true;
  }

  void Application::Run()
  {
    while(running)
    {
      window->PollEvents();

      for(Layer* layer : layer_stack)
      {
        layer->OnUpdate();
      }
      glClearColor(1, 0, 1, 1);

      glClear(GL_COLOR_BUFFER_BIT);

      window->SwapBuffers();
    }
  }

  void Application::PopLayer(Layer* layer)
  {
    layer_stack.PopLayer(layer);
  }

  void Application::PushLayer(Layer* layer)
  {
    layer_stack.PushLayer(layer);
  }

  Application::~Application()
  {

  }

};