#include "scene/layer/SampleLayer.h"

#include "renderer/Renderer2D.h"

#include "ecs/components/QuadComponent.h"
#include "ecs/components/TextComponent.h"

#include "scene/EntryScene.h"

namespace SANDBOX
{
  SampleLayer::SampleLayer(const std::string& name)
    : name(name)
  {

  }

  SampleLayer::~SampleLayer()
  {

  }

  void SampleLayer::OnAttach()
  {
    for(size_t i = 0; i < QUADS; i++)
    {
      ent[i].AddComponent(new Banana::QuadComponent());
    }
  }

  void SampleLayer::OnDetach()
  {

  }

  void SampleLayer::OnEvent(Banana::Event& event)
  {

  }

  void SampleLayer::OnUpdate(float dt)
  {
    float one_width = 2.0f / QUADS;
    for(size_t i = 0; i < QUADS; i++)
    {
      ent[i].transform.proj = Banana::Projection::NONE;
      ent[i].transform.pos = {(i * one_width) - 1, 0, 0};
      ent[i].transform.size = {one_width, EntryScene::samples[i], 0};
      ent[i].transform.color = {std::abs(EntryScene::samples[i] + 0.6), std::abs(EntryScene::samples[i]), std::abs(EntryScene::samples[i]), 1.0f};
      ent[i].Render(dt);
    }
  }
};

