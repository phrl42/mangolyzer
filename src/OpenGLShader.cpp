#include "renderer/opengl/OpenGLShader.h"
#include "renderer/Shader.h"
#include <fstream>


#ifdef MACRO_SDL2
#define GL_GLEXT_PROTOTYPES

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#endif

namespace banana
{
  OpenGLShader::~OpenGLShader()
  {

  }
  void OpenGLShader::LoadShader(std::string filepath)
  {
    // save shader into strings
    std::fstream fileShader(filepath);

    if(!fileShader.is_open())
    {
      LOG_CORE("Could not open" + filepath);
    }

    std::string line;
    size_t linecount = 1;
    
    while(getline(fileShader, line))
    {
      // validation check
      if(line.find("#version") == std::string::npos && linecount == 0)
      {
        LOG_CORE("Shader is not valid.");
        return;
      }
      if(line.find("#version") != std::string::npos)
      {
        shader.push_back("");
      }

      line += "\n";
      shader[shader.size() - 1] += line;

      linecount++;
    }
  }

  OpenGLShader::OpenGLShader()
  {

  }

  void OpenGLShader::Compile()
  {
    unsigned int shaderID;
    unsigned int vertexID;
    unsigned int fragmentID;

    int success;

    std::string log;

    vertexID = glCreateShader(GL_VERTEX_SHADER);

    // the hell is this casting
    glShaderSource(vertexID, 1, (const GLchar *const*)shader[0].c_str(), NULL);

    glCompileShader();
  }

  void OpenGLShader::Use()
  {

  }

};