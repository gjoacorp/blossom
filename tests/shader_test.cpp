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

// test that the constructor throws a std::runtime_error when there is no valid OpenGL context
TEST_F(shader_test, constructor_with_no_gl_context_throws)
{
  EXPECT_THROW(blossom::shader("", ""), std::runtime_error);
}

// test that print_log() throws a std::runtime_error when there is no valid OpenGL context
TEST_F(shader_test, print_log_with_no_gl_context_throws)
{
  EXPECT_THROW(blossom::shader::print_log(INVALID_SHADER_PROGRAM), std::runtime_error);
}

// test that print_log() throws a std::runtime_error when the passed shader is valid
TEST_F(shader_test, print_log_with_invalid_shader_throws)
{
  create_dummy_window_();
  EXPECT_THROW(blossom::shader::print_log(INVALID_SHADER_PROGRAM), std::runtime_error);
}

// test that read_source() throws a std::runtime_error when the passed path is invalid
TEST_F(shader_test, read_source_invalid_file_path_throws)
{
  const char* invalid_path = "abcdefghijklmnopqrstuvwxyz";
  EXPECT_THROW(blossom::shader::read_source(invalid_path), std::runtime_error);
}
