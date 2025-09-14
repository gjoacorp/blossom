#ifndef BLOSSOM_CAMERA_H
#define BLOSSOM_CAMERA_H

#include <glm/glm.hpp>
#include "transform.h"
#include <glm/gtc/matrix_transform.hpp>

namespace blossom
{
  class camera : public transform
  {
    public:
      int width;
      int height;

      float near;
      float far;

      glm::mat4 view_matrix = glm::mat4(1.0f);
      glm::mat4 projection_matrix = glm::mat4(1.0f);

      camera(const glm::vec3& position, int width, int height) : transform(position), width(width), height(height) {}

      virtual void update_view_matrix()
      {
        view_matrix = glm::mat4(1.0f);
        view_matrix = glm::rotate(view_matrix, -rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        view_matrix = glm::rotate(view_matrix, -rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        view_matrix = glm::rotate(view_matrix, -rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        view_matrix = glm::scale(view_matrix, scale); 
        view_matrix = glm::translate(view_matrix, -position);
      }

      virtual void update_projection_matrix() = 0;
  };
}

#endif
