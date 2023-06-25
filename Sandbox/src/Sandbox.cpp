#include "Sandbox.h"
#include "_Sandbox.h"

#include "layer/TestLayer.h"

//-----EntryPoint.h-----
#include "EntryPoint.h"

namespace SANDBOX
{


  Sandbox::Sandbox()
  {
    PushLayer(new TestLayer());
    PushOverlay(new Banana::IMGUILayer());
  }

  Sandbox::~Sandbox()
  {

  }

};

Banana::Application* Banana::CreateApplication()
{
  return new SANDBOX::Sandbox();
}