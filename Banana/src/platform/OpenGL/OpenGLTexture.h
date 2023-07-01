#pragma once
#include "renderer/Texture.h"

namespace Banana
{
  class OpenGLTexture2D : public Texture2D
  {
  public:
      
    OpenGLTexture2D(const std::string& path);
    virtual ~OpenGLTexture2D() override;
    
    virtual uint32_t GetWidth() const override { return width; }
    virtual uint32_t GetHeight() const override { return height; }

    virtual void Bind(uint32_t slot = 0) const override;
    virtual void Unbind() const override;

  private:
    std::string path;

    uint32_t width = 0;
    uint32_t height = 0;
    uint32_t id = 0;
  };
};