#include "scene/layer/TestLayer.h"

#include "renderer/Renderer2D.h"

namespace SANDBOX
{
  TestLayer::TestLayer(const std::string& name)
  : name(name)
  {
    float x = 0.0f;
    float y = 0.0f;
    for(int i = 0; i < ARR_SIZE; i++)
    {
      bananas[i].pos = {x, y, 0};

      bananas[i].size = {1.0f, 1.0f};
      bananas[i].color = {0.5 + x / 100, -1.0f + y / 100, 1.0f + x / 42, 1.0f};
      bananas[i].rotation = 0;
      bananas[i].proj = Banana::Projection::PERSPECTIVE;

      x += 0.5;
      y -= 0.1;
    }
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
    
  }

  void TestLayer::OnUpdate(float dt)
  {
    int constant = 2;
    for(int i = 0; i < ARR_SIZE; i++)
    {
      bananas[i].rotation += 90.0f * dt;
      bananas[i].size.x += constant * dt;
      if(bananas[i].size.x >= 5)
      {
        constant = -2;
      }
      else if(bananas[i].size.x <= 5)
      {
        constant = 2;
      }
      RenderEntity2D(bananas[i]);
    }
  }
};