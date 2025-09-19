#ifndef BLOSSOM_CUBE_H
#define BLOSSOM_CUBE_H

#include "mesh.h"
#include "shader.h"

namespace blossom
{
  class cube : public mesh
  {
    public:
      cube(GLuint shader_program)
      {
        //     H──────G
        //    /│     /│
        //   E──────F │
        //   │ │    │ │
        //   │ D────┼─C
        //   │/     │/
        //   A──────B

        vertices_ =
        {
          // bottom face 
          glm::vec3{-0.5f, -0.5f,  0.5f}, //  A
          glm::vec3{ 0.5f, -0.5f,  0.5f}, //  B
          glm::vec3{ 0.5f, -0.5f, -0.5f}, //  C
          glm::vec3{-0.5f, -0.5f, -0.5f}, //  D
          // top face 
          glm::vec3{-0.5f,  0.5f,  0.5f}, //  E
          glm::vec3{ 0.5f,  0.5f,  0.5f}, //  F
          glm::vec3{ 0.5f,  0.5f, -0.5f}, //  G
          glm::vec3{-0.5f,  0.5f, -0.5f}, //  H
        };

        indices_ =
        {
          // bottom face
          0, 1, 2,
          0, 2, 3,
          // top face
          4, 5, 6,
          4, 6, 7,
          // front face
          0, 1, 5,
          0, 5, 4,
          // right face
          1, 5, 6,
          1, 6, 2,
          // back face
          2, 6, 7,
          2, 7, 3,
          // left face
          3, 7, 4,
          3, 4, 0,
        };

        normals_ = 
        {
          glm::vec3{-0.577f, -0.577f,  0.577f},  // vertex 0
          glm::vec3{ 0.577f, -0.577f,  0.577f},  // vertex 1
          glm::vec3{ 0.577f, -0.577f, -0.577f},  // vertex 2
          glm::vec3{-0.577f, -0.577f, -0.577f},  // vertex 3
          glm::vec3{-0.577f,  0.577f,  0.577f},  // vertex 4
          glm::vec3{ 0.577f,  0.577f,  0.577f},  // vertex 5
          glm::vec3{ 0.577f,  0.577f, -0.577f},  // vertex 6
          glm::vec3{-0.577f,  0.577f, -0.577f},  // vertex 7
        };


        shader_program_ = shader_program;
        init_buffers_();
        update_uniform_locations_();
      }
  };
}

#endif
