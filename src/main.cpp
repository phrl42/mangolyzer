#include "utils/incs.h"
#include "utils/Entry.h"

using namespace banana;

int main()
{
  // set desired options
  Entry entry = Entry(WindowingSystem::SDL2, GraphicsLibrary::OpenGL);

  entry.Init();
  
  return 0;
}