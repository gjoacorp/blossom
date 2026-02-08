#ifndef BLOSSOM_FACTORY_LINE_H
#define BLOSSOM_FACTORY_LINE_H

#include <entt/entt.hpp>
#include "../factories/mesh.h"

namespace blossom::factory
{
  inline auto line(
      entt::registry& registry, 
      const GLuint shader_program, 
      const glm::vec3& start,
      const glm::vec3& end) -> entt::entity
  {
    return mesh(registry)
      .with_vertices({start, end})
      .with_primitive_type(GL_LINES)
      .with_shader_program(shader_program)
      .build();
  }

  inline auto line(
      entt::registry& registry, 
      const GLuint shader_program, 
      std::vector<glm::vec3>& points) -> entt::entity
  {
    return mesh(registry)
      .with_vertices(points)
      .with_primitive_type(GL_LINE_STRIP)
      .with_shader_program(shader_program)
      .build();
  }
}

#endif
