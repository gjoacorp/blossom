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
      /// @brief The width of the camera's viewport rectangle.
      uint16_t width;
      /// @brief The height of the camera's viewport rectangle.
      uint16_t height;

      /// @brief Distance to the camera's near clipping plane.
      float near;
      /// @brief Distance to the camera's far clipping plane.
      float far;

      /// @brief The camera's view matrix.
      glm::mat4 view_matrix = glm::mat4(1.0F);
      /// @brief The camera's projection matrix.
      glm::mat4 projection_matrix = glm::mat4(1.0F);

      /// @param position is the world space position of the camera.
      /// @param width is the width of the camera's viewport rectangle.
      /// @param height is the height of the camera's viewport rectangle.
      /// @param near is the distance to the camera's near clipping plane.
      /// @param far is the distance to the camera's far clipping plane.
      camera(const glm::vec3& position, uint16_t width, uint16_t height, float near, float far);

      /// @brief Updates `camera::view_matrix` using the camera's inherited `transform::position`, `transform::rotation`, and `transform::scale` data.
      virtual void update_view_matrix();
      /// @brief Pure virtual function to be implemented in `camera` derived classes.
      virtual void update_projection_matrix() = 0;
  };
}

#endif
