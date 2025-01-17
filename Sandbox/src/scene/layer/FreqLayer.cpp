#include "scene/layer/FreqLayer.h"

#include "renderer/Renderer2D.h"

#include "ecs/components/QuadComponent.h"
#include "ecs/components/TextComponent.h"

#include "scene/EntryScene.h"

#include <dlfcn.h>
#include "fft.h"

namespace SANDBOX
{
  FreqLayer::FreqLayer(const std::string& name)
    : name(name)
  {
    
  }

  FreqLayer::~FreqLayer()
  {

  }


  void FreqLayer::OnAttach()
  {
    for(int i = 0; i < FREQ_QUADS; i++)
    {
      ent[i].AddComponent(new Banana::QuadComponent());
    }
  }

  void FreqLayer::OnDetach()
  {

  }

  void FreqLayer::OnEvent(Banana::Event& event)
  {

  }

  typedef void (*UpdateEntities) (float*, std::array<Banana::Entity, FREQ_QUADS>&, float);

  std::complex<float> freqs[FREQ_QUADS] = {0};

  float goal[FREQ_QUADS] = {0};
  
  void FreqLayer::OnUpdate(float dt)
  {
    // performing calculations and stuff
    fft(EntryScene::samples, 1, freqs, FREQ_QUADS);
    float max_amp = 1;
    float step = 0.1;

    // find maximum amplitude in current sample
    for(int i = 0; i < FREQ_QUADS; i++)
    {
      float value = abs(freqs[i]);
      if(value > max_amp && value != 0)
      {
	max_amp = value;
      }
    }
    
    for(int i = 0; i < FREQ_QUADS; i++)
    {
      float value = abs(freqs[i]);

      // this prevents idle overflowing
      if(goal[i] > 2)
      {
	goal[i] = 0;
      }
      step = ((value / max_amp) * 2) - goal[i];

      goal[i] += step * (dt * 10);
    }
/*
    float one_width = 2.0f / FREQ_QUADS;

    for(size_t i = 0; i < FREQ_QUADS; i++)
    {
      ent[i].transform.proj = Banana::Projection::NONE;
      ent[i].transform.pos = {(i * one_width) - 1, -1, 0};
      ent[i].transform.size = {2, goal[i], 0};
      ent[i].transform.color = {goal[i], -0.3 + goal[i], 0.8 + goal[i], 1};
      ent[i].Render(dt);
      }*/

    // hot reloading design
    
    void *libhandle = dlopen("bin/target/Debug/HotReloading/libHotReloading.so", RTLD_LAZY);

    if(libhandle == NULL)
    {
      LOG("Could not find shared library.");
      return;
    }

    UpdateEntities update_ent = reinterpret_cast<UpdateEntities>(dlsym(libhandle, "update_ent"));

    update_ent(goal, ent, dt);

    dlclose(libhandle);
    
  }
};

