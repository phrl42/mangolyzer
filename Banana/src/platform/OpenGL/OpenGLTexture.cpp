#include "platform/OpenGL/OpenGLTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "glad.h"
#include "GLFW/glfw3.h"

namespace Banana
{
  OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
  {
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		
    stbi_uc* data = nullptr;
		
		data = stbi_load(path.c_str(), &width, &height, &channels, 0);
			
		if (!data)
		{
      LOG("Could not load image: " + path);
    }
      
    GLenum internalFormat = 0, dataFormat = 0;
    if (channels == 4)
    {
      internalFormat = GL_RGBA8;
      dataFormat = GL_RGBA;
    }
    else if (channels == 3)
    {
      internalFormat = GL_RGB8;
      dataFormat = GL_RGB;
    }

    if(!(internalFormat & dataFormat))
      LOG("Format not supported!");

    glCreateTextures(GL_TEXTURE_2D, 1, &id);
    glTextureStorage2D(id, 1, internalFormat, width, height);

    glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureSubImage2D(id, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
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