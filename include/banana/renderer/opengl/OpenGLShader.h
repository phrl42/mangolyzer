#pragma once
#include "utils/incs.h"

#include "renderer/Shader.h"

namespace banana
{
  class OpenGLShader : public Shader
  {
  public:
    OpenGLShader();
    void LoadShader(std::string filepath) override;
    ~OpenGLShader() override;
    void Compile() override;
    void Bind() override;
    void Unbind() override;

  private:
    std::vector<std::string> shader;
    const size_t VERTEX = 0;
    const size_t FRAGMENT = 0;

    unsigned int shaderID;
  };
};