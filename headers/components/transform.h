#ifndef BLOSSOM_COMPONENT_TRANSFORM_C_H
#define BLOSSOM_COMPONENT_TRANSFORM_C_H

#include <glm/glm.hpp>

namespace blossom::component
{
  struct transform
  {
    glm::vec3 position = { 0.0F, 0.0F, 0.0F };
    glm::vec3 rotation = { 0.0F, 0.0F, 0.0F };
    glm::vec3 scale    = { 1.0F, 1.0F, 1.0F };

    glm::mat4 matrix = glm::mat4(1.0F);
  };
}

#endif 
