#include "utils/incs.h"
#include "renderer/opengl/OpenGLType.h"
#include "renderer/Type.h"

namespace banana
{
  std::unique_ptr<Type> Type::GetType()
  {
      switch(Management::UsedGL)
      {
        case GraphicsLibrary::OpenGL:
          return std::make_unique<OpenGLType>();
          break;

        case GraphicsLibrary::Vulkan:
          break;

        default:
          break;
      }
  }
};