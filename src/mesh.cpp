#include "../headers/mesh.h"

#include <stdexcept>
#include <glm/gtc/type_ptr.hpp>

using blossom::mesh;

void mesh::draw(const camera* const cam) const
{
  glUseProgram(shader_program_);
  glUniformMatrix4fv(
      model_uniform_location_, 
      1, 
      GL_FALSE, 
      glm::value_ptr( calc_model_matrix() ) );

  if (cam != nullptr)
  {
    glUniformMatrix4fv(
        view_uniform_location_, 
        1, 
        GL_FALSE, 
        glm::value_ptr(cam->view_matrix) );
    
    glUniformMatrix4fv(
        projection_uniform_location_, 
        1, 
        GL_FALSE, 
        glm::value_ptr(cam->projection_matrix) );
  }
  else
  {
    glUniformMatrix4fv(
        view_uniform_location_, 
        1, 
        GL_FALSE, 
        glm::value_ptr( glm::mat4(1.0F) ) );

    glUniformMatrix4fv(
        projection_uniform_location_, 
        1, 
        GL_FALSE, 
        glm::value_ptr( glm::mat4(1.0F) ) );
  }
  glBindVertexArray(vao_);
  glPolygonMode(GL_FRONT_AND_BACK, polygon_mode_);

  if ( !indices_.empty() ) 
  { 
    // this check is probably irrelevant
    if ( indices_.size() > static_cast<size_t>(std::numeric_limits<GLsizei>::max()) )
    {
      throw std::runtime_error("ERROR: indices_.size() is too large to safely cast to GLsizei");
    }

    glDrawElements(
        GL_TRIANGLES, 
        static_cast<GLsizei>( indices_.size() ),
        GL_UNSIGNED_INT, 
        nullptr ); 
  }
  else 
  { 
    glDrawArrays(
        GL_TRIANGLES, 
        0, 
        (GLsizei)vertices_.size() ); 
  }
}

mesh::mesh(const std::vector<glm::vec3>& vertices, GLuint shader_program) : 
  vertices_(vertices), 
  shader_program_(shader_program) 
  {
    if (glfwGetCurrentContext() == nullptr)
    {
      throw std::runtime_error("ERROR: mesh construction failed. There is no current OpenGL context.");
    }
    if ( glIsProgram(shader_program) == GL_FALSE )
    {
      throw std::invalid_argument("ERROR: shader_program must be a valid program object.");
    }
    update_uniform_locations_();
    init_buffers_();
  }

mesh::mesh(const std::vector<glm::vec3>& vertices, const std::vector<GLuint>& indices, GLuint shader_program) :
  vertices_(vertices),
  indices_(indices),
  shader_program_(shader_program)
  {
    if (glfwGetCurrentContext() == nullptr)
    {
      throw std::runtime_error("ERROR: mesh construction failed. There is no current OpenGL context.");
    }
    if ( glIsProgram(shader_program) == GL_FALSE )
    {
      throw std::invalid_argument("ERROR: shader_program must be a valid program object.");
    }
    update_uniform_locations_();
    init_buffers_();
  }

mesh::~mesh()
{
  if (vao_ != 0)
  {
    glDeleteVertexArrays(1, &vao_);
  }

  if (vbo_ != 0)
  {
    glDeleteBuffers(1, &vbo_);
  }

  if (ebo_ != 0)
  {
    glDeleteBuffers(1, &ebo_);
  }
}

void mesh::init_buffers_()
{
  glCreateVertexArrays(1, &vao_);
  glBindVertexArray(vao_);

  glCreateBuffers(1, &vbo_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glNamedBufferStorage(
      vbo_, 
      static_cast<GLsizeiptr>( vertices_.size() * sizeof(glm::vec3) ), 
      vertices_.data(), 
      0);

  if (indices_.size() > 0)
  {
    glCreateBuffers(1, &ebo_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glNamedBufferStorage(
        ebo_, 
        static_cast<GLsizeiptr>( indices_.size() * sizeof(GLuint) ), 
        indices_.data(), 
        0);
  }

  glVertexAttribPointer(
      0, 
      3, 
      GL_FLOAT, 
      GL_FALSE, 
      sizeof(glm::vec3), 
      nullptr );

  glEnableVertexAttribArray(0);
  glBindVertexArray(0);
}

void mesh::set_polygon_mode(GLenum polygon_mode)
{
  if ( polygon_mode != GL_FILL && polygon_mode != GL_LINE && polygon_mode != GL_POINT )
  {
    throw std::invalid_argument("ERROR: Invalid polygon mode. Must use one of: GL_FILL, GL_LINE, GL_POINT.");
  }
  polygon_mode_ = polygon_mode;
}

void mesh::update_uniform_locations_()
{
  model_uniform_location_ = glGetUniformLocation(shader_program_, "model");
  view_uniform_location_ = glGetUniformLocation(shader_program_, "view");
  projection_uniform_location_ = glGetUniformLocation(shader_program_, "projection");
}
