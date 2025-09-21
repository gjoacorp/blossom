#ifndef BLOSSOM_CIRCLE_H
#define BLOSSOM_CIRCLE_H

#include "mesh.h"
#include "shader.h"
#include <exception>

namespace blossom
{
  class circle : public mesh
  {
    public:
      /// @brief Approximates a unit circle by computing `iterations` equally-spaced points on the unit circle's circumference.
      /// @param shader_program is an OpenGL handle (ID) of a program object obtained from [`glCreateProgram()`](https://docs.gl/gl4/glCreateProgram).
      /// @param iterations is the number of equally-spaced points to use in the circle's approximation.
      /// @throws std::invalid_argument if `iterations` is less than 3.
      circle(GLuint shader_program, std::size_t iterations)
      {
        if (iterations < 3)
        {
          throw std::invalid_argument("ERROR: iterations must be greater than or equal to 3.");
        }

        vertices_.push_back(glm::vec3(0.0f, 0.0f, 0.0f)); // centre of the circle

        for (std::size_t i = 0; i < iterations; ++i)
        {
          const float ANGLE = (2.0f * glm::pi<float>() * i) / iterations;

          const float X = glm::cos(ANGLE);
          const float Y = glm::sin(ANGLE);

          vertices_.push_back(glm::vec3(X, Y, 0.0f));

          indices_.push_back(0);
          indices_.push_back(i + 1);
          indices_.push_back((i + 1) % iterations + 1);
        }

        shader_program_ = shader_program;
        update_uniform_locations_();
        init_buffers_();
      }
  };
}

#endif
