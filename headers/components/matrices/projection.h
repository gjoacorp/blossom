#ifndef BLOSSOM_COMPONENT_MATRIX_PROJECTION_H
#define BLOSSOM_COMPONENT_MATRIX_PROJECTION_H

#include <glm/ext/matrix_float4x4.hpp>

namespace blossom::component::matrix
{
  struct projection 
  {
    glm::mat4 data{ 1.0F };
  };
};

#endif 
