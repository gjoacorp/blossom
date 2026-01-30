#ifndef BLOSSOM_COMPONENT_ORTHOGRAPHIC_CAMERA_H
#define BLOSSOM_COMPONENT_ORTHOGRAPHIC_CAMERA_H

#include <cstdint>
#include <glm/ext/matrix_float4x4.hpp>

namespace blossom::component
{
  struct orthographic_camera
  {
    uint16_t width = 800;
    uint16_t height = 600;

    float near = 0.1F;
    float far = 100.0F;

    glm::mat4 projection_matrix = glm::mat4(1.0F);
    glm::mat4 view_matrix = glm::mat4(1.0F);
  };
}

#endif 
