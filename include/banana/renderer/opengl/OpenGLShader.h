#pragma once
#include "utils/incs.h"

#include "renderer/Shader.h"

namespace banana
{
  class OpenGLShader : public Shader
  {
  public:
    OpenGLShader();
    void LoadShader(std::string filePath) override;
    ~OpenGLShader() override;
    void Compile() override;
    void Bind() override;
    void Unbind() override;

    void Configure() override;
    void SendToGPU() override;

    std::vector<float> vertex;
    std::vector<unsigned int> element;

    int ElementValue = 0;
    
    ShaderType Type;
    std::string FilePath = "";

    bool full = false;
  private:
    std::vector<std::string> shader;
    const size_t VERTEX = 0;
    const size_t FRAGMENT = 0;

    unsigned int shaderID;
  };
};