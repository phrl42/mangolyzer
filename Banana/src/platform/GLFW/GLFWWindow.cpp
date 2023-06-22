#include "GLFWWindow.h"

namespace Banana
{
  static bool glfw_init = false;
  static void ErrorCallback(int error, const char* msg)
  {
    LOG("GLFW ERROR " + std::to_string(error) + ":" + msg);
  }

  GLFWWindow::~GLFWWindow()
  {
    Quit();
  }
  
  GLFWWindow::GLFWWindow(const WindowProps& window_props)
  {
    Init(window_props);
  }

  void GLFWWindow::SwapBuffers()
  {
    glfwSwapBuffers(glfwWindow);
  }

  void GLFWWindow::Resize(unsigned int width, unsigned int height)
  {

  }

  void GLFWWindow::SetEventCallback(const EventCallbackFunction& callback_function)
  {

  }

  void* GLFWWindow::GetNativeWindow() const
  {
    return (void*)glfwWindow;
  }

  void GLFWWindow::EnableFullscreen(bool enabled)
  {

  }


  void GLFWWindow::Init(const WindowProps& window_props)
  {
    windowData.title = window_props.Title;
    windowData.height = window_props.height;
    windowData.width = window_props.width;

    if(!glfw_init)
    {
      if(!glfwInit())
      {
        LOG("Could not initialize glfw");
        exit(-1);
      }
    }

    glfwWindow = glfwCreateWindow((int)window_props.width, 
      (int)window_props.height, windowData.title.c_str(), nullptr, nullptr);

    glfwMakeContextCurrent(glfwWindow);
    glfwSetWindowUserPointer(glfwWindow, &windowData);

    SetVSync(true);

    // set glfw callbacks

    glfwSetWindowSizeCallback(glfwWindow, [](GLFWWindow* window, int width, int height)
    {
      
    } );

  unsigned int GLFWWindow::GetHeight()
  {
    return windowData.height;
  }

  unsigned int GLFWWindow::GetWidth()
  {
    return windowData.width;
  }

  float GLFWWindow::GetTime()
  {
    return 1.0f;
  }

  void GLFWWindow::PollEvents()
  {
    glfwPollEvents();
  }

  bool GLFWWindow::IsVSync() const
  {
    return windowData.vsync;
  }

  void GLFWWindow::SetVSync(bool set)
  {
    glfwSwapInterval(set);
    windowData.vsync = set;
  }

  void GLFWWindow::Quit() const
  {
    glfwDestroyWindow(this->glfwWindow);
  }

};