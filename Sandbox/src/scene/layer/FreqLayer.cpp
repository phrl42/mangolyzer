#include "scene/layer/FreqLayer.h"

#include "renderer/Renderer2D.h"

#include "ecs/components/QuadComponent.h"
#include "ecs/components/TextComponent.h"

#include "scene/EntryScene.h"

#include "fft.h"

#include <cstring>

namespace SANDBOX
{
  FreqLayer::FreqLayer(const std::string& name)
    : name(name)
  {
    
  }

  FreqLayer::~FreqLayer()
  {

  }

  std::complex<float> freqs[QUADS];

  void FreqLayer::OnAttach()
  {
    for(int i = 0; i < QUADS; i++)
    {
      ent[i].AddComponent(new Banana::QuadComponent());
    }
    memset(freqs, 0, sizeof(float) * QUADS);
  }

  void FreqLayer::OnDetach()
  {
  }

  void FreqLayer::OnEvent(Banana::Event& event)
  {

  }
  float goal[QUADS] = {0};

  void FreqLayer::OnUpdate(float dt)
  {
    fft(EntryScene::samples, 1, freqs, QUADS);
    float max_amp = 1;
    float step = 0;
    for(int i = 0; i < QUADS; i++)
    {
      if(max_amp < abs(freqs[i]))
      {
	max_amp = abs(freqs[i]);
      }
      step = ((abs(freqs[i]) / max_amp) * 2) - goal[i];

      goal[i] += step * (dt * 10);
    }

    float one_width = 2.0f / QUADS;

    for(size_t i = 0; i < QUADS; i++)
    {
      ent[i].transform.proj = Banana::Projection::NONE;
      ent[i].transform.pos = {(i * one_width) - 1, -1, 0};
      ent[i].transform.size = {one_width, goal[i], 0};
      ent[i].transform.color = {goal[i], -0.3 + goal[i], 0.8 + goal[i], 1};
      ent[i].Render(dt);
    }

    
  }
};

