#pragma once
#include "utils/incs.h"

namespace banana
{
  enum class ShaderType {TRIANGLE = 0, RECTANGLE, CIRCLE, TEXT};

  class Shader 
  {
  public:
    virtual ~Shader() = default;
    virtual void LoadShader(std::string filePath) = 0;
    virtual void Compile() = 0;
    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual void Configure() = 0;
    virtual void SendToGPU() = 0;

    std::vector<float> vertex;
    std::vector<unsigned int> element;

    int ElementValue = 0;

    ShaderType Type;
    std::string FilePath = "";
    bool full = false;

    static std::shared_ptr<Shader> GetShader();
  };

};