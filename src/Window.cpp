#include "window/Window.h"
#include "window/SDLWindow.h"

namespace banana
{
  std::vector<std::shared_ptr<Window>> Window::Windows;

  std::shared_ptr<Window> Window::GetMostRecentWindow()
  {
    return Windows[Windows.size() - 1];
  }

  std::shared_ptr<Window> Window::GetWindowWS()
  {
    switch(banana::Management::UsedWS)
    {
      case WindowingSystem::SDL2:
        return std::make_shared<SDLWindow>();

      case WindowingSystem::GLFW:
        LOG_CORE("GLFW IS CURRENTLY NOT SUPPORTED");
        return nullptr;
      default:
        break;
    }
  }
};