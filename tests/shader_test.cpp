#include "../headers/shader.h"
#include <GLFW/glfw3.h>
#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <string>
#include <stdexcept>

TEST(ShaderTest, ReadSourceReadsFileCorrectly) 
{
  shader s;
  const char* filename = "test_shader.txt";
  std::string expected_content = "A\nB\nC\nD\n";
  {
    std::ofstream ofs(filename);
    ofs << "A\nB\nC\nD\n";
  }

  std::string result = s.read_source(filename);

  ASSERT_EQ(result, expected_content);

  std::remove(filename);
}

TEST(ShaderTest, ReadSourceThrowsOnMissingFile)
{
  shader s;
  const char* missing_filename = "file_that_does_not_exist.xyz";
  std::remove (missing_filename); 
  EXPECT_THROW (s.read_source(missing_filename), std::runtime_error);
}

TEST(ShaderTest, ReadSourceReturnsEmptyStringOnEmptyFile)
{
  shader s;
  const char* empty_filename = "empty_shader.txt";
  std::ofstream ofs (empty_filename); 
  ASSERT_EQ (s.read_source(empty_filename), "");
  std::remove (empty_filename);
}

TEST(ShaderTest, ShaderCompilationFailsWithoutCurrentContext)
{
  glfwMakeContextCurrent(nullptr);
  
  EXPECT_THROW(shader red_triangle_shader("shaders/triangle.frag", "shaders/triangle.vert"), std::runtime_error);
}
