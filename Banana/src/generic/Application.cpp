#include "Application.hpp"

#include "imgui/IMGUILayer.h"
#include "event/Input.hpp"
#include "event/KeyCode.h"

#include "renderer/Renderer.h"

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

    Renderer::Init();
    
  }

  void Application::OnEvent(Event& e)
  {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
    dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

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
  
  bool Application::OnWindowResize(WindowResizeEvent& e)
  {
    if(!e.getWidth() || !e.getHeight()) 
    {
      minimized = true;
      return false;
    }
    // tell opengl to resize framebuffer
    Renderer::OnWindowResize(e.getWidth(), e.getHeight());

    minimized = false;
    return false;
  }


  void Application::Run()
  {
    PushLayer(new Banana::IMGUILayer("IMGUILAYER"));

    for(Layer* layer : layer_stack)
    {
      layer->OnAttach();
    }

    double begin_time = 0.0f;
    double dt = 0.1f;
    while(running)
    {
      begin_time = window->GetTime();
      window->PollEvents();

      RenderCommand::SetClearColor(glm::vec4(1, 0, 1, 1));

      if(!minimized)
      {
        for(Layer* layer : layer_stack)
        {
          layer->OnUpdate(dt);
        }
      }

      window->SwapBuffers();
      
      RenderCommand::Clear();

      dt = window->GetTime() - begin_time;
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