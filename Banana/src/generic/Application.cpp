#include "Application.hpp"

#include "imgui/IMGUILayer.h"
#include "event/Input.hpp"
#include "event/KeyCode.h"

#include "renderer/RenderCommand.hpp"

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
    PushLayer(new Banana::IMGUILayer("IMGUILAYER"));

    for(Layer* layer : layer_stack)
    {
      layer->OnAttach();
    }
    

    while(running && !Input::IsKeyPressed(KEY_ESCAPE))
    {
      window->PollEvents();

      RenderCommand::SetClearColor(glm::vec4(1, 0, 1, 1));

      // toggling
      static bool press = false;
      static bool debug = true;

      if(Input::IsKeyPressed(KEY_U) && !press)
      {
        press = true;
        debug = !debug;
      }

      if(!Input::IsKeyPressed(KEY_U))
      {
        press = false;
      }

      for(Layer* layer : layer_stack)
      {
        if(layer->GetName() == "IMGUILAYER" && !debug)
        {
          continue;
        }
        layer->OnUpdate();

      }

      window->SwapBuffers();

      RenderCommand::Clear();
    }

    for(Layer* layer : layer_stack)
    {
      layer->OnDetach();
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