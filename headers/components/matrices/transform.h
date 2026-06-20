#ifndef BLOSSOM_COMPONENT_MATRIX_TRANSFORM_H
#define BLOSSOM_COMPONENT_MATRIX_TRANSFORM_H

#include <glm/ext/matrix_float4x4.hpp>

namespace blossom::component::matrix
{
  struct transform 
  {
    glm::mat4 data{ 1.0F };
  };
};

#endif 
