#include "renderer/RenderAPI.h"
#include "renderer/opengl/OpenGLRenderAPI.h"
#include "utils/Management.h"

namespace banana
{

  std::shared_ptr<RenderAPI> RenderAPI::GetRenderAPI()
  {
    switch(banana::Management::UsedGL)
    {
      case banana::GraphicsLibrary::OpenGL:
        return OpenGLRenderAPI::GetOpenGLRenderAPI();
        break;
      
      default:
        break;
    }
  }
};