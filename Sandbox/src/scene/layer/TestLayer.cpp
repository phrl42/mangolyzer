#include "scene/layer/TestLayer.h"
#include "Banana.h"

#include "renderer/Renderer2D.h"

namespace SANDBOX
{
  TestLayer::TestLayer(const std::string& name)
  : name(name)
  {
    mango_tex = Banana::Texture2D::Create("assets/textures/bunny_stalin.jpg");
    banana_tex = Banana::Texture2D::Create("assets/textures/finito.png");
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
    static float banana_rotation = 0.0f;

    banana_rotation += 90 * dt;  

    Banana::Renderer2D::DrawQuad({0, 0, 0}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, banana_rotation, mango_tex, Banana::Projection::PERSPECTIVE);
    Banana::Renderer2D::DrawQuad({0.0f, -0.5f, 0}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, banana_rotation, banana_tex, Banana::Projection::NONE);
    Banana::Renderer2D::DrawQuad({-1.0, -1.0, 0}, {1.0f, 1.0f}, {0.5f, -0.5f, 1.0f, 1.0f}, 0.0f, Banana::Projection::PERSPECTIVE);
  }
};