#pragma once

#include "renderer/Texture.h"

namespace banana
{
  class OpenGLTexture : public Texture
  {
  public:
    ~OpenGLTexture() override = default;
    OpenGLTexture() = default;

    void LoadTexture(std::string path) override;
    void BindTexture() override;
    void UnbindTexture() override;
  };
};