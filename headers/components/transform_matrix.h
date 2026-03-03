#ifndef BLOSSOM_COMPONENT_TRANSFORM_MATRIX_H
#define BLOSSOM_COMPONENT_TRANSFORM_MATRIX_H

#include <glm/glm.hpp>

namespace blossom::component
{
  struct transform_matrix
  {
    glm::mat4 matrix {1.0F};
  };
}

#endif 
