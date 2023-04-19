#include "renderer/Shader.h"
#include "renderer/opengl/OpenGLShader.h"

namespace banana
{
  std::shared_ptr<Shader> Shader::GetShader()
  {
    switch(Management::UsedGL)
    {
      case GraphicsLibrary::OpenGL:
        return std::make_shared<OpenGLShader>();
        break;
      case GraphicsLibrary::Vulkan:
        LOG_CORE("Vulkan is currently not supported");
        return nullptr;
        break;
    }
  }
};