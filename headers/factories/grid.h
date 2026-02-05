#ifndef BLOSSOM_FACTORY_GRID_H
#define BLOSSOM_FACTORY_GRID_H

#include <entt/entt.hpp>
#include "../factories/mesh.h"

namespace blossom::factory
{
  inline auto grid(entt::registry& registry, int32_t total_tiles, glm::vec2 tile_width, GLuint shader_program) -> entt::entity
  {
    if (tile_width.x < 0.0F)
    {
      throw std::invalid_argument("BLOSSOM_ERROR: tile_width.x must be non-negative.");
    }
    if (tile_width.y < 0.0F)
    {
      throw std::invalid_argument("BLOSSOM_ERROR: tile_width.y must be non-negative.");
    }

    std::vector<glm::vec3> grid_vertices;
    std::vector<GLuint> grid_indices;

    for (uint32_t z_step = 0; z_step < total_tiles; ++z_step) 
    {
      for (uint32_t x_step = 0; x_step < total_tiles; ++x_step) 
      {
        grid_vertices.emplace_back(
            static_cast<float>(x_step) * tile_width.x, 
            0.0F, 
            static_cast<float>(z_step) * tile_width.y); 

        if (z_step < total_tiles - 1 && x_step < total_tiles - 1)
        {
          grid_indices.emplace_back(x_step + (z_step * total_tiles));
          grid_indices.emplace_back(x_step + 1 + (z_step * total_tiles));
          grid_indices.emplace_back(x_step + ((z_step + 1) * total_tiles));
          grid_indices.emplace_back(x_step + ((z_step + 1) * total_tiles));
          grid_indices.emplace_back(x_step + 1 + (z_step * total_tiles));
          grid_indices.emplace_back(x_step + 1 + ((z_step + 1) * total_tiles));
        }
      }
    }
    return mesh(registry)
      .with_vertices(grid_vertices)
      .with_indices(grid_indices)
      .with_shader_program(shader_program)
      .with_polygon_mode(GL_LINE)
      .build();
  }
}

#endif 
