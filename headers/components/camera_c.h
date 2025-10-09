#ifndef BLOSSOM_CAMERA_C_H
#define BLOSSOM_CAMERA_C_H

#include <cstdint>
#include <glm/ext/matrix_float4x4.hpp>

enum class camera_type : std::uint8_t
{
  PERSPECTIVE,
  ORTHOGRAPHIC
};

struct camera_c
{
  camera_type type;

  uint16_t width;
  uint16_t height;

  float near;
  float far;
  float fov_y; // only relevant for perspective cameras

  glm::mat4 projection_matrix = glm::mat4(1.0F);
  glm::mat4 view_matrix = glm::mat4(1.0F);
};

#endif 
