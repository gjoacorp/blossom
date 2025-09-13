#ifndef BLOSSOM_CAMERA_H
#define BLOSSOM_CAMERA_H

#include <glm/glm.hpp>

namespace blossom
{
  class camera 
  {
    public:
      int width;
      int height;

      glm::mat4 view_matrix = glm::mat4(1.0f);
      glm::mat4 projection_matrix = glm::mat4(1.0f);

      camera(int width, int height) : width(width), height(height) {}

      virtual void update_view_matrix() = 0;
      virtual void update_projection_matrix() = 0;
  };
}

#endif
