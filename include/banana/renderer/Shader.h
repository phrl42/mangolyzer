#pragma once
#include "utils/incs.h"

namespace banana
{

  class Shader 
  {
  public:

    virtual ~Shader() = default;
    virtual void LoadShader(std::string filepath) = 0;
    virtual void Compile() = 0;
    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    static std::shared_ptr<Shader> GetShader();
  };

};