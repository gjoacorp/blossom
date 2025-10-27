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
       const float PI_F = glm::pi<float>();

       std::vector<glm::vec3> verts;	/* Array of `glm::vec3` vectors for vertices of the sphere*/
       // Sets the increment spacing vertices in the loop.
       float sector_step = 2 * PI_F / sector_count;
       float stack_step = PI_F / stack_count;

      if (radius <= 0.0F )
      {
         throw std::invalid_argument ("ERROR : Radius must be a float greater than zero.");
      }

      std::vector<glm::vec3> sphere_vertices;
      std::vector<GLuint> sphere_indices;

      std::size_t current_stack, next_stack;

      for (std::size_t i = 0; i <= stack_count; ++i)
      {
         current_stack = i * (sector_count + 1);	/* Index of current stack. */
         next_stack = current_stack + (sector_count + 1);	/* Index of next stack. */

         const float STACK_ANGLE = PI_F / 2 - i * stack_step;	/* Fix angle for this vertical ring in this loop. */

         const float Z = radius * glm::sin(STACK_ANGLE);	/* Fix height at this angle via projection of radius at stack_angle. */
         const float ZRAD = radius * glm::cos(STACK_ANGLE);	/* Fix radius at specific height by projection.*/

         for (std::size_t j = 0; j <= sector_count; ++j, ++current_stack, ++next_stack)
         {
            float sector_angle = j * sector_step;	/* Fix angle of vertex for that horizontal ring.*/
            // Project radius at specific `z` height to find `x`, `y` coordinates.
            const float X = ZRAD * glm::cos(sector_angle);
            const float Y = ZRAD * glm::sin(sector_angle);

            sphere_vertices.push_back({ X, Y, Z });

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

      return mesh(registry)
         .with_vertices(sphere_vertices)
         .with_indices(sphere_indices)
         .with_shader_program(shader_program)
         .build();
   }
}

#endif 
