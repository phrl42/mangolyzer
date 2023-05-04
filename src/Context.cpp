#include "window/Context.h"
#include "window/OpenGLContext.h"

namespace banana
{
  std::shared_ptr<Context> Context::GetWindowContext()
  {
    switch (Management::UsedGL)
    {
      case GraphicsLibrary::OpenGL:
        return std::make_shared<OpenGLContext>();
        break;

      case GraphicsLibrary::Vulkan:
        break;

      default:
        break;
    }
  }
};