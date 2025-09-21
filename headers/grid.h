#ifndef BLOSSOM_GRID_H
#define BLOSSOM_GRID_H

#include "mesh.h"
#include "shader.h"
#include <exception>

namespace blossom
{
  class grid : public mesh
  {
    public:
      /// @brief Constructs a grid on the \f$xz\f$ plane. The grid's top left corner is taken to be its origin.
      /// @note The grid's origin is taken to be its top left corner. Furthermore, the \f$x\f$ width of the grid is `iterations * x_spacing` and the \f$z\f$ width of the grid is `iterations * z_spacing`.
      /// @param shader_program The program object used during rendering.
      /// @param iterations The number of grid squares to create in both the \f$x\f$ and \f$z\f$ directions.
      /// @param x_spacing The width of the grid squares in the \f$x\f$ direction.
      /// @param z_spacing The width of the grid squares in the \f$z\f$ direction.
      grid(GLuint shader_program, std::size_t iterations, float x_spacing, float z_spacing)
      {
        if ( x_spacing < 0.0f )
        {
          throw std::runtime_error("ERROR: Cannot construct a grid with negative x_spacing.");
        }

        if ( z_spacing < 0.0f )
        {
          throw std::runtime_error("ERROR: Cannot construct a grid with negative z_spacing.");
        }

        for (std::size_t z = 0; z < iterations; ++z) 
        {
          for (std::size_t x = 0; x < iterations; ++x) 
          {
            vertices_.push_back({x * x_spacing, 0.0f, z * z_spacing}); 
          }
        }

        for (std::size_t z = 0; z < iterations - 1; ++z) 
        {
          for (std::size_t x = 0; x < iterations - 1; ++x) 
          {
            indices_.push_back(x + (z * iterations));
            indices_.push_back(x + 1 + (z * iterations));
            indices_.push_back(x + ((z + 1) * iterations));
            indices_.push_back(x + ((z + 1) * iterations));
            indices_.push_back(x + 1 + (z * iterations));
            indices_.push_back(x + 1 + ((z + 1) * iterations));
          }
        }
        shader_program_ = shader_program;
        init_buffers_();
        update_uniform_locations_();
      }
  };
}

#endif
