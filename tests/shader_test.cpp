#include <gtest/gtest.h>
#include <stdexcept>
#include "../headers/shader.h"
#include "../headers/window.h"

class shader_test : public ::testing::Test 
{
  protected:
    std::unique_ptr<blossom::window> dummy_window_;
    const GLuint INVALID_SHADER_PROGRAM = 12345;

    void SetUp() override {}

    void create_dummy_window_()
    {
      dummy_window_ = std::make_unique<blossom::window>(1, 1, "");
    }
};

TEST_F(shader_test, compile_with_no_gl_context_throws_runtime_error)
{
  const blossom::shader_info INFO = {.vertex_shader_path="shaders/default.vert", .fragment_shader_path="shaders/default.frag"};
  EXPECT_THROW(blossom::shader::compile(INFO), std::runtime_error);
}

TEST_F(shader_test, compile_with_invalid_vertex_shader_throws_runtime_error)
{
  create_dummy_window_();
  const blossom::shader_info INFO
  {
    .vertex_shader_path   = "shaders/squiggle.geom", 
    .fragment_shader_path = "shaders/default.frag"
  };
  EXPECT_THROW(blossom::shader::compile(INFO), std::runtime_error);
}

TEST_F(shader_test, compile_with_invalid_fragment_shader_throws_runtime_error)
{
  create_dummy_window_();
  const blossom::shader_info INFO
  {
    .vertex_shader_path   = "shaders/default.vert",
    .fragment_shader_path = "shaders/default.vert"
  };
  EXPECT_THROW(blossom::shader::compile(INFO), std::runtime_error);
}
