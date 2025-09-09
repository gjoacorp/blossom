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
        vertices_ = 
        {
          glm::vec3{ 1.0f,  1.0f, 0.0f}, // top-right
          glm::vec3{-1.0f,  1.0f, 0.0f}, // top-left
          glm::vec3{-1.0f, -1.0f, 0.0f}, // bottom-left
          glm::vec3{ 1.0f, -1.0f, 0.0f}  // bottom-right
        };

        indices_ = 
        {
          0, 1, 2, 
          0, 2, 3  
        };

        shader_program_ = shader_program;
        init_();
      }
  };
}

#endif
