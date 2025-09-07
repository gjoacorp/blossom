#include "../headers/mesh.h"
#include <stdexcept>

void mesh::draw() const
{
  glUseProgram(shader_program_);
  glPolygonMode(GL_FRONT_AND_BACK, polygon_mode_);

  if (indices.size() > 0) 
  { 
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0); 
  }
  else 
  { 
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertices.size()); 
  }
}

mesh::mesh(const std::vector<glm::vec3>& vertices, GLuint shader_program) : 
  vertices(vertices), 
  shader_program_(shader_program) {}

mesh::mesh(const std::vector<glm::vec3>& vertices, const std::vector<GLuint>& indices, GLuint shader_program) :
  vertices(vertices),
  indices(indices),
  shader_program_(shader_program) {}

mesh::~mesh()
{
  if (vao_ != 0)
    glDeleteVertexArrays(1, &vao_);

  if (vbo_ != 0)
    glDeleteBuffers(1, &vbo_);

  if (ibo_ != 0)
    glDeleteBuffers(1, &ibo_);
}

void mesh::init()
{
  if (!glfwGetCurrentContext())
  {
    throw std::runtime_error("ERROR: Cannot initialise mesh without current GL context.");
  }

  glCreateVertexArrays(1, &vao_);
  glBindVertexArray(vao_);

  glCreateBuffers(1, &vbo_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glNamedBufferStorage(vbo_, vertices.size() * sizeof(glm::vec3), &vertices[0], 0);

  if (indices.size() > 0)
  {
    glCreateBuffers(1, &ibo_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
    glNamedBufferStorage(ibo_, indices.size() * sizeof(GLuint), &indices[0], 0);
  }

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
  glEnableVertexAttribArray(0);
}

void mesh::set_draw_mode(GLenum draw_mode)
{
  if ( !( draw_mode == GL_FILL || draw_mode == GL_LINE || draw_mode == GL_POINT ) )
    throw std::runtime_error("ERROR: Invalid polygon mode. Must use one of: GL_FILL, GL_LINE, GL_POINT.");
  polygon_mode_ = draw_mode;
}
