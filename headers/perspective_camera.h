#ifndef BLOSSOM_PERSPECTIVE_CAMERA_H
#define BLOSSOM_PERSPECTIVE_CAMERA_H

#include "transform.h"
#include "camera.h"

namespace blossom
{
  class perspective_camera : public camera
  {
    public:
      /// @brief Specifies the field of view angle in the \f$y\f$ direction. Expressed in degrees. 
      float fov_y; 
      float near;
      float far;

      /// @param position is the position of the camera in world space.
      /// @param width is the width of the camera's viewport rectangle.
      /// @param height is the height of the camera's viewport rectangle.
      /// @param fov_y is the field of view angle in the \f$y\f$ direction (expressed in degrees.)
      /// @param near is the distance to the camera's near clipping plane.
      /// @param far is the distance to the camera's far clipping plane.
      perspective_camera(const glm::vec3& position, int width, int height, float fov_y, float near, float far) :
      camera(position, width, height, near, far),
      fov_y(fov_y)
      {
        update_view_matrix();
        update_projection_matrix();
      }

      /// @brief Updates the inherited `camera::projection_matrix` using `camera::width`, `camera::height`, `camera::near`, `camera::far`, and `perspective_camera::fov_y`.
      void update_projection_matrix()
      {
        const float aspect = static_cast<float>(width) / static_cast<float>(height);
        projection_matrix = glm::perspective(glm::radians(fov_y), aspect, near, far);
      }
  };
}

#endif
