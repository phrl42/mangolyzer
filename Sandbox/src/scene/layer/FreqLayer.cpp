#include "scene/layer/FreqLayer.h"

#include "renderer/Renderer2D.h"

#include "ecs/components/QuadComponent.h"
#include "ecs/components/TextComponent.h"

#include "scene/EntryScene.h"

#include <dlfcn.h>


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
  
  void FreqLayer::OnUpdate(float dt)
  {
    void *libhandle = dlopen("bin/target/Debug/HotReloading/libHotReloading.so", RTLD_LAZY);

    if(libhandle == NULL)
    {
      LOG("Could not find shared library.");
      return;
    }

    UpdateEntities update_ent = reinterpret_cast<UpdateEntities>(dlsym(libhandle, "update_ent"));

    LOG(dlerror());
    update_ent(EntryScene::samples, ent, dt);



    dlclose(libhandle);
    
    /*fft(EntryScene::samples, 1, freqs, FREQ_QUADS);
    float max_amp = 1;
    float step = 0.1;
    for(int i = 0; i < FREQ_QUADS; i++)
    {
      float value = abs(freqs[i]);
      if(max_amp < value && value != 0)
      {
	max_amp = value;
      }
      step = ((value / max_amp) * 2) - goal[i];

      goal[i] += step * (dt * 10);
    }

    float one_width = 2.0f / FREQ_QUADS;

    for(size_t i = 0; i < FREQ_QUADS; i++)
    {
      ent[i].transform.proj = Banana::Projection::NONE;
      ent[i].transform.pos = {(i * one_width) - 1, -1, 0};
      ent[i].transform.size = {one_width, goal[i], 0};
      ent[i].transform.color = {goal[i], -0.3 + goal[i], 0.8 + goal[i], 1};
      ent[i].Render(dt);
      }*/
    
  }
};

