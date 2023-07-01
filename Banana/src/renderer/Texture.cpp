#include "platform/OpenGL/OpenGLTexture.h"

#include "renderer/Renderer.h"

namespace Banana
{
  Shr<Texture2D> Texture2D::Create(const std::string& path)
  {
    switch(Renderer::GetAPI())
    {
      case RendererAPI::API::OpenGL: return MakeShr<OpenGLTexture2D>(path);
    }

    LOG("Could not find Renderer API in Texture");
    return nullptr;
  }
};