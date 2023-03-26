#include "renderer/RenderCommand.h"

#include "renderer/opengl/OpenGLRenderCommand.h"

namespace banana
{
  std::shared_ptr<RenderCommand> RenderCommand::GetRenderCommand()
  {
    switch(Management::UsedGL)
    {
      case GraphicsLibrary::OpenGL:
        return std::make_shared<OpenGLRenderCommand>();
        break;
      case GraphicsLibrary::Vulkan:
        LOG_CORE("Vulkan is currently not supported");
        return nullptr;
        break;
    }
  }
}