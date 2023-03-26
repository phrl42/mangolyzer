#include "framework/Framework.h"
#include "framework/SDLFramework.h"

namespace banana
{
std::shared_ptr<Framework> Framework::GetFramework()
{
  switch(banana::Management::UsedWS)
  {
    case banana::WindowingSystem::SDL2:
      return std::make_shared<SDLFramework>();
      break;
    
    case banana::WindowingSystem::GLFW:
      LOG_CORE("GLFW IS CURRENTLY NOT SUPPORTED");
      return nullptr;
    default:
      return nullptr;
      break;
    };
}

};