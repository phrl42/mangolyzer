#include "renderer/opengl/OpenGLRenderAPI.h"

#ifdef MACRO_SDL2
#include <SDL2/SDL.h>
#define PROCADDRESS SDL_GL_GetProcAddress
#endif

#include "utils/glad.h"

namespace banana
{

  static void OpenGLMessageCallback(
	unsigned source,
	unsigned type,
	unsigned id,
	unsigned severity,
	int length,
	const char* message,
	const void* userParam)
	{
		LOG_CORE(std::string(message));
	}

  OpenGLRenderAPI::OpenGLRenderAPI()
  {

  }

  OpenGLRenderAPI::~OpenGLRenderAPI()
  {

  }

  std::shared_ptr<OpenGLRenderAPI> OpenGLRenderAPI::GetOpenGLRenderAPI()
  {
    std::shared_ptr<OpenGLRenderAPI> rendapi = std::make_shared<OpenGLRenderAPI>();
    return rendapi;
  }

  void OpenGLRenderAPI::Init()
  {
    if (!gladLoadGLLoader((GLADloadproc)PROCADDRESS))
    {
      LOG_CORE("Failed to initialize GLAD");
      return;
    }
		
    glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
    
  }
};