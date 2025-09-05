#include "../headers/mesh.h"

void mesh::draw() const
{
  glUseProgram(shader_program_);
  glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertices.size());
}

mesh::mesh(const std::vector<glm::vec3>& vertices, GLuint shader_program) : 
  vertices(vertices), 
  shader_program_(shader_program) {}

mesh::~mesh()
{
  if (vao_ != 0)
    glDeleteVertexArrays(1, &vao_);

  if (vbo_ != 0)
    glDeleteBuffers(1, &vbo_);
}

void mesh::init()
{
  glCreateVertexArrays(1, &vao_);
  glBindVertexArray(vao_);

  glCreateBuffers(1, &vbo_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glNamedBufferStorage(vbo_, vertices.size() * sizeof(glm::vec3), &vertices[0], 0);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
  glEnableVertexAttribArray(0);
}
