#ifndef BLOSSOM_ORTHOGRAPHIC_CAMERA_H
#define BLOSSOM_ORTHOGRAPHIC_CAMERA_H

#include "transform.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace blossom
{
  class orthographic_camera : public transform
  {
    public:
      int width;
      int height;

      glm::mat4 view_matrix = glm::mat4(1.0f);
      glm::mat4 projection_matrix = glm::mat4(1.0f);

      orthographic_camera(const glm::vec3& position, int width, int height) :
        transform(position),
        width(width),
        height(height)
      {
        update_view_matrix();
        update_projection_matrix();
      }

      void update_view_matrix()
      {
        glm::mat4 view_matrix = glm::mat4(1.0f);
        view_matrix = glm::rotate(view_matrix, -rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        view_matrix = glm::rotate(view_matrix, -rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        view_matrix = glm::rotate(view_matrix, -rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        view_matrix = glm::scale(view_matrix, scale); 
        view_matrix = glm::translate(view_matrix, -position);
      }

      void update_projection_matrix()
      {
        projection_matrix = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), -10.0f, 10.0f);
      }
  };
}

#endif
