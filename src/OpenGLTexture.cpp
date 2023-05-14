#include "renderer/opengl/OpenGLTexture.h"

#include "utils/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "utils/stb_image.h"

namespace banana
{
  void OpenGLTexture::LoadTexture(std::string path)
  {
    // opengl enables the use of 16 textures simultaneously 
    // you can have more textures though
    // generate 1 texture
    int w = 0;
    int h = 0;
    int channels = 0;

    unsigned char* data = 0;

    glGenTextures(1, &textureID);
    // use the newly generated texture
    glBindTexture(GL_TEXTURE_2D, textureID);
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
      LOG_CORE("Could not load texture: " + path);
      textureID = 0;
      return;
    }
    // load image into gpu
  
    if(channels == 4)
    {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    else
    {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    glGenerateMipmap(GL_TEXTURE_2D);
  
  
    stbi_image_free(data);
 
    // unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);
  }

  void OpenGLTexture::BindTexture()
  {
    glBindTexture(GL_TEXTURE_2D, textureID);
  }

  void OpenGLTexture::UnbindTexture()
  {
    glBindTexture(GL_TEXTURE_2D, 0);
  }
};