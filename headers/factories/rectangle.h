#ifndef BLOSSOM_FACTORY_RECTANGLE_H
#define BLOSSOM_FACTORY_RECTANGLE_H

#include <entt/entt.hpp>
#include "../factories/mesh.h"

namespace blossom::factory
{
  inline auto rectangle(entt::registry& registry, const glm::vec3& position, const glm::vec2& scale, GLuint shader_program) -> entt::entity
  {
    const std::vector<glm::vec3> VERTICES = 
    {
      glm::vec3{ 1.0F,  1.0F, 0.0F}, 
      glm::vec3{-1.0F,  1.0F, 0.0F}, 
      glm::vec3{-1.0F, -1.0F, 0.0F},
      glm::vec3{ 1.0F, -1.0F, 0.0F} 
    };
    
    const std::vector<GLuint> INDICES = 
    {
      0, 1, 2, 
      0, 2, 3 
    };

    const glm::vec3 SCALE = {scale.x, scale.y, 1.0F};

    return mesh(registry)
      .with_position(position)
      .with_scale(SCALE)
      .with_vertices(VERTICES)
      .with_indices(INDICES)
      .with_shader_program(shader_program)
      .build();
  }
}

#endif
