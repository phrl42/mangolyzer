#include "Sandbox.h"
#include "_Sandbox.h"

//-----EntryPoint.h-----
#include "EntryPoint.h"

namespace SANDBOX
{
  Sandbox::Sandbox()
  {
    
  }

  Sandbox::~Sandbox()
  {

  }

  void Sandbox::Run()
  {

  }

};

Banana::Application* Banana::CreateApplication()
{
  return new SANDBOX::Sandbox();
}