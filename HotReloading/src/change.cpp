#include <iostream>

#include "ecs/Entity.h"
#include "fft.h"

#include "freq.h"

extern "C"
{

  std::complex<float> freqs[FREQ_QUADS] = {0};
  std::array<float, FREQ_QUADS> goal;

  void update_ent(float *audio_samples, std::array<Banana::Entity, FREQ_QUADS> &ent, float dt)
  {
    std::cout << "test" << std::endl;
    fft(audio_samples, 1, freqs, FREQ_QUADS);

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
    }
     
  }
}
