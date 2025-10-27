#ifndef BLOSSOM_FACTORY_SPHERE_H
#define BLOSSOM_FACTORY_SPHERE_H

#include <entt/entt.hpp>
#include "../factories/mesh.h"

#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>

namespace blossom::factory
{
  /** @brief Factory for a sphere of given parameters.
   * @param[in] registry To be declared by Eugene.
   * @param[in] radius Radius of sphere in arbitrary units at present.
   * @param[in] sector_count Number of horizontal rings.
   * @param[in] stack_count Number of vertical rings.
   * @param[in] shader_program Shader program used on mesh.
   */
  inline auto sphere(entt::registry& registry, float radius, std::size_t sector_count, std::size_t stack_count, GLuint shader_program) -> entt::entity
  {
    std::vector<glm::vec3> verts;	/* Array of `glm::vec3` vectors for vertices of the sphere*/
    // Sets the increment spacing vertices in the loop.
    float sector_step = (2 * glm::pi<float>()) / static_cast<float>(sector_count);
    float stack_step = glm::pi<float>() / static_cast<float>(stack_count);

    if (radius <= 0.0F )
    {
      throw std::invalid_argument ("ERROR : Radius must be a float greater than zero.");
    }

    std::vector<glm::vec3> sphere_vertices;
    std::vector<GLuint> sphere_indices;

    std::size_t current_stack;
    std::size_t next_stack;

    for (std::size_t i = 0; i <= stack_count; ++i)
    {
      current_stack = i * (sector_count + 1);	
      next_stack    = current_stack + (sector_count + 1);

      const float STACK_ANGLE = glm::half_pi<float>() - (static_cast<float>(i) * stack_step);
      const float ZRAD        = glm::cos(STACK_ANGLE);

      for (std::size_t j = 0; j <= sector_count; ++j, ++current_stack, ++next_stack)
      {
        float sector_angle = static_cast<float>(j) * sector_step;	

        const float VERTEX_X = ZRAD * glm::cos(sector_angle);
        const float VERTEX_Y = ZRAD * glm::sin(sector_angle);
        const float VERTEX_Z =        glm::sin(STACK_ANGLE);

        sphere_vertices.emplace_back( VERTEX_X, VERTEX_Y, VERTEX_Z );

        if ( i < sector_count )
        {
          if (i != 0)
          {
            sphere_indices.emplace_back(current_stack);
            sphere_indices.emplace_back(next_stack);
            sphere_indices.emplace_back(current_stack + 1);
          }
          if (i != (stack_count - 1))
          {
            sphere_indices.emplace_back(current_stack + 1);
            sphere_indices.emplace_back(next_stack);
            sphere_indices.emplace_back(next_stack + 1);
          }
        }
      }
    }

    const glm::vec3 SPHERE_SCALE = { radius, radius, radius };

    return mesh(registry)
      .with_vertices(sphere_vertices)
      .with_indices(sphere_indices)
      .with_scale(SPHERE_SCALE)
      .with_shader_program(shader_program)
      .build();
  }
}

#endif 
