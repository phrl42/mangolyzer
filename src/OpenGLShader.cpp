#include "renderer/opengl/OpenGLShader.h"
#include "renderer/Shader.h"
#include <fstream>

#include "utils/glad.h"

namespace banana
{
  OpenGLShader::~OpenGLShader()
  {

  }

  void OpenGLShader::LoadShader(std::string filePath)
  {
    this->FilePath = filePath;
    // save shader into strings
    std::fstream fileShader(filePath);

    if(!fileShader.is_open())
    {
      LOG_CORE("Could not open" + filePath);
      return;
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
    unsigned int shaderID = 0;
    unsigned int vertexID = 4242;
    unsigned int fragmentID = 0;

    int success = 0;

    char log[200];
    memset(log, '\0', sizeof(char) * 200);
    
    // found ze uebeltaeter
    vertexID = glad_glCreateShader(GL_VERTEX_SHADER);

    // the hell is this casting
    const char* vertexshader = shader[VERTEX].c_str();
    glShaderSource(vertexID, 1, &vertexshader, NULL);

    glCompileShader(vertexID);

    // error handling
    glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success);

    LOG_CORE("bunker: " + std::to_string(success));
    if(!success)
    {
      glGetShaderInfoLog(vertexID, 200, NULL, log);
      LOG_CORE("Compiling vertex shader failed: " + std::string(log));
      return;
    }

    // the same applies for the fragment shader once again
    fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

    const char* fragmentshader = shader[FRAGMENT].c_str();
    glShaderSource(fragmentID, 1, &fragmentshader, NULL);

    glCompileShader(fragmentID);

    glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);
    
    if(!success)
    {
      glGetShaderInfoLog(fragmentID, GL_COMPILE_STATUS, NULL, log);
      LOG_CORE("Compiling fragment shader failed: " + std::string(log));
      return;
    }

    // link shaders altogether

    shaderID = glCreateProgram();

    glAttachShader(shaderID, vertexID);
    glAttachShader(shaderID, fragmentID);

    glLinkProgram(shaderID);

    // delete unused shaders now
    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);

    this->shaderID = shaderID;
  }

  void OpenGLShader::Bind()
  {
    glUseProgram(this->shaderID);
  }

  void OpenGLShader::Unbind()
  {
    glUseProgram(0);
  }

};