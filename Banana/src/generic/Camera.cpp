#include "generic/Camera.h"
#include "gtc/matrix_transform.hpp"

#include "Application.hpp"
#include "matrix.hpp"

namespace Banana
{
  Camera::Camera()
  : projection_matrix(glm::perspective(glm::radians(90.0f), 
        (float)1280/(float)720, 0.1f, 100.0f)),
    view_matrix(glm::mat4(1.0f))
  {
    view_projection_matrix = projection_matrix * view_matrix;
  }

  Camera::~Camera()
  {

  }

  void Camera::CalcMatrix()
  {
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * 
                          glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0, 0, 1));

    view_matrix = glm::inverse(transform);

    view_projection_matrix = projection_matrix * view_matrix;
  }

};