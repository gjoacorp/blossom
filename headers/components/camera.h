#ifndef BLOSSOM_COMPONENT_CAMERA_H
#define BLOSSOM_COMPONENT_CAMERA_H

#include <glm/ext/matrix_float4x4.hpp>

namespace blossom::component
{
  struct camera
  {
    enum class camera_type : uint8_t
    {
      ORTHOGRAPHIC,
      PERSPECTIVE
    };


    uint16_t width = 800;
    uint16_t height = 600;

    float near = 0.1F;
    float far = 100.0F;
    float fov_y = 90.0F; 

    camera_type type = camera_type::ORTHOGRAPHIC;

    GLuint ubo = 0;
  };
}

#endif 
