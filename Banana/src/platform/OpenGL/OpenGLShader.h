#pragma once
#include "renderer/Shader.h"


namespace Banana
{
  class OpenGLShader : public Shader
  {
  public:
    OpenGLShader(const std::string& file_path);

    virtual ~OpenGLShader() override = default;
    virtual void Compile() override;
    virtual void Bind() override;
    virtual void Unbind() override;

  private:
    uint32_t id;
    const std::string file_path;

    std::string vertex_src = "";
    std::string fragment_src = "";

  };
};