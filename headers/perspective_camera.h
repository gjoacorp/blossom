#ifndef BLOSSOM_PERSPECTIVE_CAMERA_H
#define BLOSSOM_PERSPECTIVE_CAMERA_H

#include "transform.h"
#include "camera.h"

namespace blossom
{
  class perspective_camera : public camera
  {
    public:
      float fov_y; 
      float near;
      float far;

      perspective_camera(const glm::vec3& position, int width, int height, float fov_y, float near, float far) :
      camera(position, width, height, near, far),
      fov_y(fov_y)
      {
        update_view_matrix();
        update_projection_matrix();
      }

      void update_projection_matrix()
      {
        const float aspect = static_cast<float>(width) / static_cast<float>(height);
        projection_matrix = glm::perspective(glm::radians(fov_y), aspect, near, far);
      }
  };
}

#endif
