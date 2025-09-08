#include "../headers/mesh.h"
#include <stdexcept>

using blossom::mesh;

void mesh::draw() const
{
  glUseProgram(shader_program_);
  glBindVertexArray(vao_);
  glPolygonMode(GL_FRONT_AND_BACK, polygon_mode_);

  if (indices_.size() > 0) 
  { 
    glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, (void*)0); 
  }
  else 
  { 
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertices_.size()); 
  }
}

mesh::mesh(const std::vector<glm::vec3>& vertices, GLuint shader_program) : 
  vertices_(vertices), 
  shader_program_(shader_program) 
  {
    init_();
  }

mesh::mesh(const std::vector<glm::vec3>& vertices, const std::vector<GLuint>& indices, GLuint shader_program) :
  vertices_(vertices),
  indices_(indices),
  shader_program_(shader_program)
  {
    init_();
  }

mesh::~mesh()
{
  if (vao_ != 0)
    glDeleteVertexArrays(1, &vao_);

  if (vbo_ != 0)
    glDeleteBuffers(1, &vbo_);

  if (ebo_ != 0)
    glDeleteBuffers(1, &ebo_);
}

void mesh::init_()
{
  if (!glfwGetCurrentContext())
  {
    throw std::runtime_error("ERROR: Cannot initialise mesh without current GL context.");
  }

  glCreateVertexArrays(1, &vao_);
  glBindVertexArray(vao_);

  glCreateBuffers(1, &vbo_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glNamedBufferStorage(vbo_, vertices_.size() * sizeof(glm::vec3), &vertices_[0], 0);

  if (indices_.size() > 0)
  {
    glCreateBuffers(1, &ebo_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glNamedBufferStorage(ebo_, indices_.size() * sizeof(GLuint), &indices_[0], 0);
  }

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);
}

void mesh::set_polygon_mode(GLenum polygon_mode)
{
  if ( !( polygon_mode == GL_FILL || polygon_mode == GL_LINE || polygon_mode == GL_POINT ) )
    throw std::runtime_error("ERROR: Invalid polygon mode. Must use one of: GL_FILL, GL_LINE, GL_POINT.");
  polygon_mode_ = polygon_mode;
}
