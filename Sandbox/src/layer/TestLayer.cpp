#include "layer/TestLayer.h"

namespace SANDBOX
{
  TestLayer::TestLayer(const std::string& name)
  : name(name)
  {

  }

  TestLayer::~TestLayer()
  {

  }

  void TestLayer::OnAttach()
  {

  }

  void TestLayer::OnDetach()
  {
    
  }

  void TestLayer::OnEvent(Banana::Event& event)
  {
    LOG(event.ToString());
  }

  void TestLayer::OnUpdate(float dt)
  {
    
  }

  void TestLayer::ImguiRender()
  {

  }
  
};