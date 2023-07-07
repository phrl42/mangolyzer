#include "platform/OpenGL/OpenGLFramebuffer.h"
#include "renderer/Renderer.h"

namespace Banana
{
  Shr<Framebuffer> Framebuffer::Create()
  {
    switch(Renderer::GetAPI())
    {
      case RendererAPI::API::OpenGL: return MakeShr<OpenGLFramebuffer>();
    }
    
    LOG("RendererAPI in Framebuffer not found.");
    return nullptr;
  }
};