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
    
    ShaderType Type;
    std::string FilePath = "";

  private:
    std::vector<std::string> shader;
    const size_t VERTEX = 0;
    const size_t FRAGMENT = 1;

    unsigned int shaderID;
    unsigned int vaoID;
    unsigned int vboID;
    unsigned int eboID;
  };
};