#ifndef BLOSSOM_CUBE_FACTORY_H
#define BLOSSOM_CUBE_FACTORY_H

#include <entt/entt.hpp>
#include "../factories/mesh_factory.h"

namespace blossom::factory
{
  inline auto cube(entt::registry& registry, GLuint shader_program, const glm::vec3& position, const glm::vec3& scale) -> entt::entity
  {
    //     H──────G
    //    /│     /│
    //   E──────F │
    //   │ │    │ │
    //   │ D────┼─C
    //   │/     │/
    //   A──────B
    const std::vector<glm::vec3> CUBE_VERTICES = 
    {
      glm::vec3 {-0.5F, -0.5F,  0.5F}, //  A
      glm::vec3 { 0.5F, -0.5F,  0.5F}, //  B
      glm::vec3 { 0.5F, -0.5F, -0.5F}, //  C
      glm::vec3 {-0.5F, -0.5F, -0.5F}, //  D
      glm::vec3 {-0.5F,  0.5F,  0.5F}, //  E
      glm::vec3 { 0.5F,  0.5F,  0.5F}, //  g
      glm::vec3 { 0.5F,  0.5F, -0.5F}, //  G
      glm::vec3 {-0.5F,  0.5F, -0.5F}, //  H
    };
    
    const std::vector<GLuint> CUBE_INDICES = 
    {
      // bottom face
      0, 1, 2,
      0, 2, 3,
      // top face
      4, 5, 6,
      4, 6, 7,
      // front face
      0, 1, 5,
      0, 5, 4,
      // right face
      1, 5, 6,
      1, 6, 2,
      // back face
      2, 6, 7,
      2, 7, 3,
      // left face
      3, 7, 4,
      3, 4, 0,
    };

    return mesh(registry)
      .with_position(position)
      .with_scale(scale)
      .with_vertices(CUBE_VERTICES)
      .with_indices(CUBE_INDICES)
      .with_shader_program(shader_program)
      .build();
  }
}

#endif
