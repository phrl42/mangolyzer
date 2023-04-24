#include "renderer/Batch.h"
#include "renderer/opengl/OpenGLBatch.h"

namespace banana
{
  std::shared_ptr<Batch> Batch::GetBatch()
  {
    switch(Management::UsedGL)
    {
      case GraphicsLibrary::OpenGL:
        return std::make_shared<OpenGLBatch>();
        break;
      case GraphicsLibrary::Vulkan:
        LOG_CORE("Vulkan is currently not supported");
        return nullptr;
        break;
    }
  }
};