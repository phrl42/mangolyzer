#include "Application.hpp"
#include "imgui/IMGUILayer.h"

namespace Banana
{

  Application* Application::Instance = nullptr;

  Application::Application()
  {
    if(Instance)
    {
      LOG("Application already exists!");
    }

    Instance = this;

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
    for(Layer* layer : layer_stack)
    {
      layer->OnAttach();
    }

    while(running)
    {
      window->PollEvents();

      glClearColor(1, 0, 1, 1);

      for(Layer* layer : layer_stack)
      {
        layer->OnUpdate();
      }


      window->SwapBuffers();
      glClear(GL_COLOR_BUFFER_BIT);
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


  void Application::PopOverlay(Layer* layer)
  {
    layer_stack.PopOverlay(layer);
  }

  void Application::PushOverlay(Layer* layer)
  {
    layer_stack.PushOverlay(layer);
  }

  Application::~Application()
  {

  }

};