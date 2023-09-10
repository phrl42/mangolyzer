#include <iostream>

#include "ecs/Entity.h"
#include "freq.h"

extern "C"
{

  void update_ent(float *goal, std::array<Banana::Entity, FREQ_QUADS> &ent, float dt)
  {
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
