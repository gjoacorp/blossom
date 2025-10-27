#ifndef BLOSSOM_CIRCLE_FACTORY_H
#define BLOSSOM_CIRCLE_FACTORY_H

#include <entt/entt.hpp>
#include <stdexcept>
#include <glm/gtc/constants.hpp>
#include "../factories/mesh_factory.h"

namespace blossom::factory
{
  struct circle_radius     { float   value; };
  struct circle_iterations { uint8_t value; };

  inline auto circle(
      entt::registry& registry, 
      const GLuint shader_program, 
      const glm::vec3& position, 
      const circle_radius radius, 
      const circle_iterations iterations) -> entt::entity
  {
    if (iterations.value < 3)
    {
      throw std::invalid_argument("BLOSSOM_ERROR: Iterations must be greater than or equal to 3.");
    }
    if (radius.value <= 0.0F)
    {
      throw std::invalid_argument("BLOSSOM_ERROR: Circle radius must be greater than 0.");
    }

    std::vector<glm::vec3> circle_vertices;
    std::vector<GLuint> circle_indices;

    circle_vertices.emplace_back(0.0F, 0.0F, 0.0F); // centre of the circle

    for (uint8_t i = 0; i < iterations.value; ++i)
    {
      const float ANGLE = ( 2.0F * glm::pi<float>() * static_cast<float>(i) ) / static_cast<float>(iterations.value);
      const float POS_X = glm::cos(ANGLE);
      const float POS_Y = glm::sin(ANGLE);

      circle_vertices.emplace_back(POS_X, POS_Y, 0.0F);

      circle_indices.emplace_back(0);
      circle_indices.emplace_back(i + 1);
      circle_indices.emplace_back( ( (i + 1) % iterations.value ) + 1 );
    }

    return mesh(registry)
      .with_position(position)
      .with_scale(glm::vec3(radius.value, radius.value, 1.0F))
      .with_vertices(circle_vertices)
      .with_indices(circle_indices)
      .with_shader_program(shader_program)
      .build();
  }
}

#endif
