#ifndef BLOSSOM_SPHERE_H
#define BLOSSOM_SPHERE_H

#include "mesh.h"
#include "shader.h"

#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>

float pi_f = glm::pi<float>();

namespace blossom
{
	class sphere : public mesh
	{
	public:
		/// @brief Generates the points of a radius `radius` sphere based on parameters for the vertical and horizontal rings, `sector_count` and `stack_count` respectively, and returns them as `glm::vec3` objects within an array.
		static std::vector<glm::vec3> generate_sphere_verts(float radius, std::size_t sector_count, std::size_t stack_count)
		{
			std::vector<glm::vec3> verts;	/**< Array of `glm::vec3` vectors for vertices of the sphere*/
			/// @brief Sets the increment spacing vertices in the loop.
			float sector_step = 2 * pi_f / sector_count;
			float stack_step = pi_f / stack_count;
			
			for (std::size_t i = 0; i <= stack_count; ++i)
			{
				float stack_angle = pi_f / 2 - i * stack_step;	/**< Fix angle for this vertical ring in this loop. */

				float z = radius * glm::sin(stack_angle);	/**< Fix height at this angle via projection of radius at stack_angle. */
				float zrad = radius * glm::cos(stack_angle);	/**< Fix radius at specific height by projection.*/

				for (std::size_t j = 0; j <= sector_count; ++j)
				{
					float sector_angle = j * sector_step;	/**< Fix angle of vertex for that horizontal ring.*/
					/// @brief Project radius at specific `z` height to find `x`, `y` coordinates.
					float x = zrad * glm::cos(sector_angle);
					float y = zrad * glm::sin(sector_angle);

					verts.push_back({ x,y,z });
				}
			}

			return verts;
		}
		/// @brief Generates the indices (tris) of a sphere based on parameters for the vertical and horizontal rings, `sector_count` and `stack_count` respectively, and returns them as `glm::vec3` objects within an array.
		static std::vector<GLuint> generate_sphere_indices(std::size_t sector_count, std::size_t stack_count)
		{

			std::vector<GLuint> indices; /**< A vector of `GLuint` objects that will hold the indices by way of index.*/

			int k1, k2;	// current and next index

			for (std::size_t i = 0; i < stack_count; ++i)
			{
				k1 = i * (sector_count + 1);	/**< Index of current stack. */
				k2 = k1 + (sector_count + 1);	/**< Index of next stack. */

				for (std::size_t j = 0; j < sector_count; ++j, ++k1, ++k2)
				{
					if (i != 0)
					{
						indices.push_back(k1);
						indices.push_back(k2);
						indices.push_back(k1 + 1);
					}
					if (i != (stack_count - 1))
					{
						indices.push_back(k1 + 1);
						indices.push_back(k2);
						indices.push_back(k2 + 1);
					}
				}
			}

			return indices;
		}

		/// @brief Constructor for a sphere with the default parameters of 0.5 radius, 32 points in each horizontal ring, of which there are 16.
		sphere(GLuint shader_program) // unit sphere with default parameters
		{
			vertices_ = generate_sphere_verts(0.5, 32, 16);

			indices_ = generate_sphere_indices(32, 16);

			shader_program_ = shader_program;
			init_buffers_();
			update_uniform_locations_();
		}
		/// @brief Constructor for sphere with specific parameters.
		sphere(GLuint shader_program, float radius, std::size_t sector_count, std::size_t stack_count)  // sphere with specific parameters
		{
			vertices_ = generate_sphere_verts(radius, sector_count, stack_count);

			indices_ = generate_sphere_indices(sector_count, stack_count);

			shader_program_ = shader_program;
			init_buffers_();
			update_uniform_locations_();
		}
	};
}

#endif
