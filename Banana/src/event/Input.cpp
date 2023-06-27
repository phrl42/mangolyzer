#include "platform/GLFW/GLFWInput.h"

namespace Banana
{
  Input *Input::Instance = new GLFWInput();
};