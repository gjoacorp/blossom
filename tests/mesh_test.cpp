#include <gtest/gtest.h>
#include <stdexcept>
#include "../headers/mesh.h"
#include "../headers/window.h"

// vsp -> vertices, shader program
TEST(mesh_test, vsp_constructor_with_no_gl_context_throws) 
{
  std::vector<glm::vec3> empty_vertices;
  auto invalid_id = static_cast<GLuint>(0);
  EXPECT_THROW(blossom::mesh invalid_mesh(empty_vertices, invalid_id), std::runtime_error);
}

// visp -> vertices, indices, shader program
TEST(mesh_test, visp_constructor_with_no_gl_context_throws)
{
  std::vector<glm::vec3> empty_vertices;
  std::vector<GLuint> empty_indices;
  auto invalid_id = static_cast<GLuint>(0);
  EXPECT_THROW(blossom::mesh invalid_mesh(empty_vertices, empty_indices, invalid_id), std::runtime_error);
}

TEST(mesh_test, vsp_constructor_with_zero_shader_program_throws)
{
  blossom::window dummy_window(1, 1, "");
  std::vector<glm::vec3> empty_vertices;
  auto invalid_id = static_cast<GLuint>(0);
  EXPECT_THROW(blossom::mesh invalid_mesh(empty_vertices, invalid_id), std::invalid_argument);
}

TEST(mesh_test, visp_constructor_with_zero_shader_program_throws)
{
  blossom::window dummy_window(1, 1, "");
  std::vector<glm::vec3> empty_vertices;
  std::vector<GLuint> empty_indices;
  auto invalid_id = static_cast<GLuint>(0);
  EXPECT_THROW(blossom::mesh invalid_mesh(empty_vertices, empty_indices, invalid_id), std::invalid_argument);
}

TEST(mesh_test, set_polygon_mode_throws_on_invalid_enum)
{
  blossom::mesh empty_mesh;
  GLenum invalid_enum = GL_TEXTURE_2D;
  EXPECT_THROW(empty_mesh.set_polygon_mode(invalid_enum), std::invalid_argument);
}
