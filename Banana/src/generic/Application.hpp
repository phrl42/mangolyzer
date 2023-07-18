#pragma once

#include "_Banana.h"
#include "Window.hpp"
#include "layer/LayerStack.h"

#include "renderer/Framebuffer.h"

namespace Banana
{
  class Application
  {
  public:
    Application();
    virtual ~Application();

    void OnEvent(Event& e);
    void Run();

    void PushLayer(Layer* layer);
    
    void PushOverlay(Layer* layer);
    void PopOverlay(Layer* layer);

    void PopLayer(Layer* layer);

    inline Window& GetWindow() { return *window; }

    inline static Application& GetInstance() { return *Instance; }
  
  private:
    bool OnWindowClose(WindowCloseEvent& e);
    bool OnWindowResize(WindowResizeEvent& e);

    LayerStack layer_stack;
    std::unique_ptr<Window> window;

    static Application* Instance;

    bool running = true;
    bool minimized = false;
  public:
    Banana::Shr<Banana::Framebuffer> fb;
  };

  // definition is in client
  Application* CreateApplication();

};