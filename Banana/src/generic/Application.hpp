#pragma once

#include "_Banana.h"
#include "Window.hpp"
#include "layer/LayerStack.h"

#include "glfw3.h"


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
    void PopLayer(Layer* layer);
  
  private:
    LayerStack layer_stack;
    std::unique_ptr<Window> window;
    bool running = true;
  };

  // definition is in client
  Application* CreateApplication();

};