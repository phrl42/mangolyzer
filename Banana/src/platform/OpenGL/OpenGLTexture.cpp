#include "platform/OpenGL/OpenGLTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "glad.h"
#include "GLFW/glfw3.h"

namespace Banana
{
  OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
  {
    // opengl enables the use of 16 textures simultaneously 
    // you can have more textures though
    // generate 1 texture
    int w = 0;
    int h = 0;
    int channels = 0;

    unsigned char* data = 0;

    glGenTextures(1, &id);
    // use the newly generated texture
    glBindTexture(GL_TEXTURE_2D, id);
    // adjust settings of the texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 
    // load and save texture
    // flip the picture on the y-axis
    stbi_set_flip_vertically_on_load(true);

    data = stbi_load(path.c_str(), &w, &h, &channels, 0);
    if(!data)
    {
      LOG("Could not load texture: " + path);
      id = 0;
      return;
    }
    
    GLenum data_format = 0;
    GLenum internal_format = 0;
    if(channels == 4)
    {
      data_format = GL_RGBA;
      internal_format = GL_RGBA8;
      
    }
    if(channels == 3)
    {
      data_format = GL_RGB8;
      internal_format = GL_RGB8;
    }

    if(!data_format || !internal_format) LOG("Data format of image is faulty");

    glTexImage2D(GL_TEXTURE_2D, 0, internal_format, w, h, 0, data_format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  
  
    stbi_image_free(data);
 
    // unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);

  }

  OpenGLTexture2D::~OpenGLTexture2D()
  {
    glDeleteTextures(1, &id);
  }

  void OpenGLTexture2D::Bind(uint32_t slot) const
  {
    glBindTextureUnit(slot, id);
  }

  void OpenGLTexture2D::Unbind() const
  {
    glBindTexture(GL_TEXTURE_2D, 0);
  }

};