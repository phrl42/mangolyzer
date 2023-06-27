#include "platform/GLFW/GLFWInput.h"

#include "Application.hpp"

namespace Banana
{
  
  bool GLFWInput::IsKeyPressedImpl(int key)
  {
    auto state = glfwGetKey((GLFWwindow*)Application::GetInstance().GetWindow().GetNativeWindow(), key);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
  }

  bool GLFWInput::IsMouseButtonPressedImpl(int button)
  {
    auto state = glfwGetMouseButton((GLFWwindow*)Application::GetInstance().GetWindow().GetNativeWindow(), button);

    return state == GLFW_PRESS;
  }


  float GLFWInput::GetMouseXImpl()
  {
    double xpos = 0.0;
    glfwGetCursorPos((GLFWwindow*)Application::GetInstance().GetWindow().GetNativeWindow(), &xpos, nullptr);

    return (float)xpos;
  }

  float GLFWInput::GetMouseYImpl()
  {
    double ypos = 0.0;
    glfwGetCursorPos((GLFWwindow*)Application::GetInstance().GetWindow().GetNativeWindow(), nullptr, &ypos);

    return (float)ypos;
  }
  
};