#pragma once
#include "_Banana.h"
#include "glm.hpp"

namespace Banana
{
  class Camera 
  {
  public:
    Camera();
    ~Camera();

    inline void SetPosition(const glm::vec3& pos) { this->position = pos; CalcMatrix(); }
    inline void SetRotation(float rotation) { this->rotation = rotation; CalcMatrix(); }

    inline const glm::vec3& GetPosition() const { return this->position; }
    inline float GetRotation() const { return this->rotation; }

    inline const glm::mat4& GetProjectionMatrix() const { return this->projection_matrix; }
    inline const glm::mat4& GetViewMatrix() const { return this->view_matrix; }
    inline const glm::mat4& GetViewProjectionMatrix() const { return this->view_projection_matrix; }

  private:
    void CalcMatrix();
  private:
    glm::mat4 projection_matrix;
    glm::mat4 view_matrix;
    glm::mat4 view_projection_matrix;

    glm::vec3 position;
    float rotation = 0.0f;
  };
};