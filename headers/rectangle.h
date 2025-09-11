#ifndef BLOSSOM_RECTANGLE_H
#define BLOSSOM_RECTANGLE_H

#include "mesh.h"
#include "shader.h"

namespace blossom
{
  class rectangle : public mesh
  {
    public:
      rectangle(GLuint shader_program)
      {
        // B ──────────── A
        // │              │
        // │              │
        // │              │
        // C ──────────── D

        vertices_ = 
        {
          glm::vec3{ 1.0f,  1.0f, 0.0f}, // A
          glm::vec3{-1.0f,  1.0f, 0.0f}, // B
          glm::vec3{-1.0f, -1.0f, 0.0f}, // C
          glm::vec3{ 1.0f, -1.0f, 0.0f}  // D
        };

        indices_ = 
        {
          0, 1, 2, // ABC
          0, 2, 3  // ACD
        };

        shader_program_ = shader_program;
        init_buffers_();
      }
  };
}

#endif
