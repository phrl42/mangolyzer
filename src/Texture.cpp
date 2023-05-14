#include "renderer/Texture.h"

#include "renderer/opengl/OpenGLTexture.h"

namespace banana
{
  std::shared_ptr<Texture> Texture::GetTexture()
  {
    switch(Management::UsedGL)
    {
      case GraphicsLibrary::OpenGL:
        return std::make_shared<OpenGLTexture>();
        break;
      
      default:
        break;
    }
  }
};