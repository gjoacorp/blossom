#ifndef BLOSSOM_ORTHOGRAPHIC_CAMERA_H
#define BLOSSOM_ORTHOGRAPHIC_CAMERA_H

#include "camera.h"

namespace blossom
{
  class orthographic_camera : public camera
  {
    public:
      orthographic_camera(const glm::vec3& position, int width, int height) :
        camera(position, width, height)
      {
        update_view_matrix();
        update_projection_matrix();
      }

      void update_projection_matrix()
      {
        projection_matrix = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), -10.0f, 10.0f);
      }
  };
}

#endif
