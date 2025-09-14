#ifndef BLOSSOM_ORTHOGRAPHIC_CAMERA_H
#define BLOSSOM_ORTHOGRAPHIC_CAMERA_H

#include "camera.h"

namespace blossom
{
  class orthographic_camera : public camera
  {
    public:
      orthographic_camera(const glm::vec3& position, int width, int height, float near, float far) :
        camera(position, width, height, near, far)
      {
        update_view_matrix();
        update_projection_matrix();
      }

      void update_projection_matrix()
      {
        projection_matrix = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), near, far);
      }
  };
}

#endif
