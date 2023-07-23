#include "scene/layer/TestLayer.h"

#include "renderer/Renderer2D.h"

namespace SANDBOX
{
  TestLayer::TestLayer(const std::string& name)
  : name(name)
  {
    banana.pos = {0, 0, 0};
    banana.size = {1.0f, 1.0f};
    banana.color = {1.0f, 1.0f, 1.0f, 1.0f};
    banana.rotation = 0;

    banana.tex = Banana::Texture2D::Create("assets/textures/finito.png");

    banana.proj = Banana::Projection::PERSPECTIVE;
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
    banana.pos.x += 0.3 * dt;

    RenderEntity2D(banana);
  }
};