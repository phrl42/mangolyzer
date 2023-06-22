#pragma once

#include "_Banana.h"
#include "Window.hpp"

#include "glfw3.h"

namespace Banana
{
  class Application
  {
  public:
    Application();
    virtual ~Application();

    void Run();
  
  private:
    std::unique_ptr<Window> window;
    bool running = true;
  };

  // definition is in client
  Application* CreateApplication();

};