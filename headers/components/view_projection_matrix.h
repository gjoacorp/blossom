#ifndef BLOSSOM_COMPONENT_VIEW_PROJECTION_MATRIX_H
#define BLOSSOM_COMPONENT_VIEW_PROJECTION_MATRIX_H

#include <glm/glm.hpp>

namespace blossom::component
{
  struct view_projection_matrix
  {
    glm::mat4 matrix {1.0F};
  };
}

#endif 
