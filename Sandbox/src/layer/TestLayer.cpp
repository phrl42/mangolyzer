#include "layer/TestLayer.h"
#include "Banana.h"

#include "renderer/Renderer2D.h"
#include "renderer/Texture.h"

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
    //LOG(event.ToString());
  }

  void TestLayer::OnUpdate(float dt)
  {
    Banana::Renderer2D::BeginScene();
      Banana::Renderer2D::DrawQuad({0, 0, 0}, {1.0f, 1.0f}, {0.5f, -0.5f, 1.0f, 1.0f}, Banana::Texture2D::Create("assets/textures/krauss.png"));
      Banana::Renderer2D::DrawQuad({-1.0, -1.0, 0}, {1.0f, 1.0f}, {0.5f, -0.5f, 1.0f, 1.0f});
    Banana::Renderer2D::EndScene();
  }

  void TestLayer::ImguiRender()
  {

  }
  
};