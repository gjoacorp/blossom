#ifndef BLOSSOM_COMPONENT_MATRIX_VIEW_H
#define BLOSSOM_COMPONENT_MATRIX_VIEW_H

#include <glm/ext/matrix_float4x4.hpp>

namespace blossom::component::matrix
{
  struct view 
  {
    glm::mat4 data{ 1.0F };
  };
};

#endif 
