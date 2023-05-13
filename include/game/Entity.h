#pragma once
#include "utils/incs.h"

namespace banana
{
  enum class ShaderType {TRIANGLE = 0, RECTANGLE, CIRCLE, TEXT};
};

namespace game
{
  enum class Projection { NONE = 0, ORTHOGRAPHIC, PERSPECTIVE };

  struct Entity
  {
    virtual ~Entity() = default;

    static std::vector<std::shared_ptr<Entity>> EntityVector;

    float x = 0;
    float y = 0;

    float w = 0;
    float h = 0;

    float r = 0;
    float g = 0;
    float b = 0;
    float a = 0;

    enum banana::ShaderType type = banana::ShaderType::RECTANGLE;

    //std::shared_ptr<Texture> tex;

    Projection proj;

    // maybe use std::variant in Entity::EntityVectors because not every Entity needs an element std::vector
    std::vector<float> vertex;
    std::vector<unsigned int> element;
  };

  struct BananaRectangle : public Entity 
  {
    enum banana::ShaderType type = banana::ShaderType::RECTANGLE;
    
    ~BananaRectangle() override = default;
    BananaRectangle() = default;
  };
};