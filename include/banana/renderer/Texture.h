#pragma once

#include "utils/incs.h"

namespace banana
{
  class Texture
  {
  public:
    virtual ~Texture() = default;

    static std::shared_ptr<Texture> GetTexture();

    virtual void LoadTexture(std::string path) = 0;
    virtual void BindTexture(size_t textureSlot) = 0;
    virtual void UnbindTexture() = 0;

    int texID = -1;
  };
};