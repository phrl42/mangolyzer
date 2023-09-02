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
  float max_amp = 0;
  void save()
  {
    // also save the highest amplitude in the processed frame
    for(int i = 0; i < QUADS; i++)
    {
      goal[i] = abs(freqs[i]);
      if(goal[i] > max_amp)
      {
	max_amp = goal[i];
      }
    }    
  }

  void FreqLayer::OnUpdate(float dt)
  {
    fft(EntryScene::samples, 1, freqs, QUADS);

    float step = 0;
    for(int i = 0; i < QUADS; i++)
    {
      if(goal[i] == abs(freqs[i]))
      {
	save();
      }
      step = abs(freqs[i]) - goal[i];

      goal[i] += step * (dt * 2);
    }

    float one_width = 2.0f / QUADS;

    for(size_t i = 0; i < QUADS; i++)
    {
      ent[i].transform.proj = Banana::Projection::NONE;
      ent[i].transform.pos = {(i * one_width) - 1, -1, 0};
      ent[i].transform.size = {one_width, goal[i] / 3, 0};
      ent[i].transform.color = {goal[i], -0.3 + goal[i], 0.8 + goal[i], 1};
      ent[i].Render(dt);
    }

    
  }
};

