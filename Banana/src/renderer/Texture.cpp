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
  
  Shr<Texture2D> Texture2D::Create(const void* pixels, int texture_width, int texture_height)
  {
    switch(Renderer::GetAPI())
    {
      case RendererAPI::API::OpenGL: return MakeShr<OpenGLTexture2D>(pixels, texture_width, texture_height);
    }
    
    LOG("Could not find Renderer API in Texture");
    return nullptr;
  }
};