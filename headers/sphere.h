#ifndef BLOSSOM_SPHERE_H
#define BLOSSOM_SPHERE_H

#include "mesh.h"
#include "shader.h"

#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>

float pi_f = glm::pi<float>();

std::vector<glm::vec3>& generate_sphere_verts(float radius, int sector_count, int stack_count) {
	std::vector<glm::vec3> verts;
	float sector_step = 2 * pi_f / sector_count;
	float stack_step = pi_f / stack_count;

	for (int i = 0; i <= stack_count; ++i) {
		float stack_angle = pi_f / 2 - i * stack_step;
		float xy = radius * glm::cos(stack_angle);
		float z = radius * glm::sin(stack_angle);

		for (int j = 0; j <= sector_count; ++j) {
			float sector_angle = j * sector_step;
			float x = xy * glm::cos(sector_angle);
			float y = xy * glm::sin(sector_angle);

			verts.push_back({ x,y,z });
		}
	}

	return verts;
}

std::vector<GLuint>& generate_sphere_indices(float radius, int sector_count, int stack_count) {
	std::vector<GLuint> indices;

	int k1, k2;	// current and next index

	for (int i = 0; i < stack_count; ++i) {
		k1 = i * (sector_count + 1);	//	index commencing current stack
		k2 = k1 + (sector_count + 1);		// index commencing next stack

		for (int j = 0; j < sector_count; ++j, ++k1, ++k2) {
			if (i != 0) {
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
			}
			if (i != (stack_count - 1)) {
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
			}
		}
	}

	return indices;
}

namespace blossom
{
	class sphere : public mesh
	{
	public:
		sphere(GLuint shader_program)
		{
			vertices_ = generate_sphere_verts(0.5, 32, 16);

			indices_ = generate_sphere_indices(0.5, 32, 16);

			shader_program_ = shader_program;
			init_buffers_();
			update_uniform_locations_();
		}
	};
}

#endif
