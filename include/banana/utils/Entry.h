#pragma once

#include "incs.h"
#include "framework/Framework.h"

namespace banana 
{
  
  class Entry 
  {
  public:
    Entry(WindowingSystem ws, GraphicsLibrary gl);
    ~Entry();
    
    void Run();

    void Init();

  private:
    std::shared_ptr<Framework> framework;
  };

} // namespace banana
