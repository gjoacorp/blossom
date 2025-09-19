#ifndef BLOSSOM_ORTHOGRAPHIC_CAMERA_H
#define BLOSSOM_ORTHOGRAPHIC_CAMERA_H

#include "camera.h"

namespace blossom
{
  class orthographic_camera : public camera
  {
    public:
      /// @brief Sets the inherited attributes `transform::position`, `camera::width`, `camera::height`, `camera::near`, and `camera::far`.
      /// Calls `camera::update_view_matrix()` and `orthographic_camera::update_projection_matrix()`.
      /// @param position is the position of the camera in world space.
      /// @param width is the width of the camera's viewport rectangle.
      /// @param height is the height of the camera's viewport rectangle.
      /// @param near is the distance to the camera's near clipping plane.
      /// @param far is the distance to the camera's far clipping plane.
      orthographic_camera(const glm::vec3& position, int width, int height, float near, float far) :
        camera(position, width, height, near, far)
      {
        update_view_matrix();
        update_projection_matrix();
      }

      /// @brief Constructs a \f$4 \times 4\f$ projection matrix using [glm::ortho()](https://glm.g-truc.net/0.9.9/api/a00665.html#ga6615d8a9d39432e279c4575313ecb456).
      /// This matrix is stored in the inherited attribute `camera::projection_matrix`.
      void update_projection_matrix()
      {
        projection_matrix = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), near, far);
      }
  };
}

#endif
