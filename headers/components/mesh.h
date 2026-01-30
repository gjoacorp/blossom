#ifndef BLOSSOM_COMPONENT_MESH_H
#define BLOSSOM_COMPONENT_MESH_H

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

namespace blossom::component
{
  struct mesh
  {
    std::vector<glm::vec3> vertices;
    std::vector<GLuint> indices;

    GLuint shader_program = 0;

    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint ebo = 0;

    GLenum polygon_mode = GL_FILL;
    GLenum primitive_type = GL_TRIANGLES;

    GLint model_uniform_location      = 0;
    GLint view_uniform_location       = 0;
    GLint projection_uniform_location = 0;
  };
}

#endif 
