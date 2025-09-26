#include <gtest/gtest.h>
#include <stdexcept>
#include "../headers/mesh.h"
#include "../headers/window.h"

class mesh_test : public ::testing::Test 
{
  protected:
    std::vector<glm::vec3> empty_vertices_;
    std::vector<GLuint> empty_indices_;
    GLuint invalid_id_;

    std::unique_ptr<blossom::window> dummy_window_;

    void SetUp() override 
    {
      empty_vertices_.clear();
      empty_indices_.clear();
      invalid_id_ = static_cast<GLuint>(0);
    }

    void create_dummy_window_()
    {
      dummy_window_ = std::make_unique<blossom::window>(1, 1, "");
    }
};

// vsp -> vertices, shader program
TEST_F(mesh_test, vsp_constructor_with_no_gl_context_throws) 
{
  EXPECT_THROW(blossom::mesh invalid_mesh(empty_vertices_, invalid_id_), std::runtime_error);
}

// visp -> vertices, indices, shader program
TEST_F(mesh_test, visp_constructor_with_no_gl_context_throws)
{
  EXPECT_THROW(blossom::mesh invalid_mesh(empty_vertices_, empty_indices_, invalid_id_), std::runtime_error);
}

TEST_F(mesh_test, vsp_constructor_with_zero_shader_program_throws)
{
  create_dummy_window_();
  EXPECT_THROW(blossom::mesh invalid_mesh(empty_vertices_, invalid_id_), std::invalid_argument);
}

TEST_F(mesh_test, visp_constructor_with_zero_shader_program_throws)
{
  create_dummy_window_();
  EXPECT_THROW(blossom::mesh invalid_mesh(empty_vertices_, empty_indices_, invalid_id_), std::invalid_argument);
}

TEST_F(mesh_test, set_polygon_mode_throws_on_invalid_enum)
{
  blossom::mesh empty_mesh;
  GLenum invalid_enum = GL_TEXTURE_2D;
  EXPECT_THROW(empty_mesh.set_polygon_mode(invalid_enum), std::invalid_argument);
}
