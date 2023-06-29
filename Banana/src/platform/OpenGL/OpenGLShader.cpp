#include "platform/OpenGL/OpenGLShader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#include "glad.h"
#include "GLFW/glfw3.h"
 
namespace Banana
{
  OpenGLShader::OpenGLShader(const std::string& file_path)
  : file_path(file_path)
  {
    std::basic_ifstream<char> ifs(file_path);
    
    // save file content into string
    std::string content((std::istreambuf_iterator<char>(ifs)),
            (std::istreambuf_iterator<char>()));
    
    int vpos = content.find("#type vertex");
    int fpos = content.find("#type fragment");

    for(int i = vpos + 13; i < fpos; i++)
    {
      vertex_src += content[i];
    }

    for(int i = fpos + 15; i < content.size(); i++)
    {
      fragment_src += content[i];
    }
  
    LOG("Saved: " + file_path);
  }

  void OpenGLShader::Bind()
  {
    glUseProgram(id);
  }

  void OpenGLShader::Unbind()
  {
    glUseProgram(0);
  }

  void OpenGLShader::Compile()
  {
    unsigned int shaderID = 0;
    unsigned int vertexID = 4242;
    unsigned int fragmentID = 0;

    int success = 0;

    char log[200];
    memset(log, '\0', sizeof(char) * 200);
    
    vertexID = glCreateShader(GL_VERTEX_SHADER);

    // the hell is this casting
    const char* vertex = vertex_src.c_str();
    glShaderSource(vertexID, 1, &vertex, 0);

    glCompileShader(vertexID);

    // error handling
    glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success);

    if(!success)
    {
      glGetShaderInfoLog(vertexID, 200, NULL, log);
      LOG("Compiling vertex shader failed: " + std::string(log));
      return;
    }

    // the same applies for the fragment shader once again
    fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

    const char* fragmentshader = fragment_src.c_str();
    glShaderSource(fragmentID, 1, &fragmentshader, NULL);

    glCompileShader(fragmentID);

    glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);
    
    if(!success)
    {
      glGetShaderInfoLog(fragmentID, GL_COMPILE_STATUS, NULL, log);
      LOG("Compiling fragment shader failed: " + std::string(log));
      return;
    }
    // link shader

    shaderID = glCreateProgram();

    glAttachShader(shaderID, vertexID);
    glAttachShader(shaderID, fragmentID);

    glLinkProgram(shaderID);

    // delete unused shaders now
    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);

    this->id = shaderID;
  }

};