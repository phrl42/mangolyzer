#pragma once
#include "utils/incs.h"
#include "renderer/Batch.h"

namespace banana
{
  class Shader 
  {
  public:
    virtual ~Shader() = default;
    virtual void LoadShader(std::string filePath) = 0;
    virtual void Compile() = 0;
    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual void SetTexUni(int val) = 0;

    ShaderType Type;
    std::string FilePath = "";

    static std::shared_ptr<Shader> GetShader();
  };

};