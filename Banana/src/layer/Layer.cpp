#include "layer/Layer.h"
#include "renderer/Renderer2D.h"

namespace Banana
{
  
  Layer::Layer(const std::string& name)
  : name(name)
  {

  }

  void Layer::RenderEntity2D(Entity2D &ent)
  {
    if(ent.tex == nullptr)
    {
      Banana::Renderer2D::DrawQuad(ent.pos, ent.size, ent.color, ent.rotation, ent.proj);
    }
    else 
    {
      Banana::Renderer2D::DrawQuad(ent.pos, ent.size, ent.color, ent.rotation, ent.tex, ent.proj);
    }
  }
  
};