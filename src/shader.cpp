#include "../headers/shader.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <vector>

using blossom::shader;

auto shader::read_source(const std::string& path) -> std::string
{
  std::string file_content;
  std::ifstream file(path, std::ios::in);
  std::string line;

  while ( std::getline(file, line) ) 
  {
    file_content.append(line + '\n');
  }

  if ( !file.is_open() ) 
  {
    throw std::runtime_error("ERROR: The file " + path + " doesn't exist.");
  }
  file.close();
  return file_content;
}

void shader::print_log_(GLuint shader)
{
  if ( glfwGetCurrentContext() == nullptr )
  {
    throw std::runtime_error("ERROR: Cannot print shader log. There is no current OpenGL context.");
  }

  GLsizei max_length = 0;

  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);

  if ( max_length > 0 ) 
  {
    std::vector<GLchar> info_log(max_length);
    GLsizei length = 0;

    glGetShaderInfoLog(shader, max_length, &length, info_log.data());

    const std::string INFO_LOG_STR(info_log.begin(), info_log.begin() + length);
    std::cout << "Shader Log: " << INFO_LOG_STR << "\n";
  }
}

void shader::print_program_log_(GLuint shader_program)
{
  if ( glfwGetCurrentContext() == nullptr )
  {
    throw std::runtime_error("ERROR: Cannot print program log. There is no current OpenGL context.");
  }

  GLsizei max_length = 0;

  glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &max_length);

  if ( max_length > 0 ) 
  {
    std::vector<GLchar> info_log(max_length);
    GLsizei length = 0;

    glGetProgramInfoLog(shader_program, max_length, &length, info_log.data());

    const std::string INFO_LOG_STR(info_log.begin(), info_log.begin() + length);
    std::cout << "Program Log: " << INFO_LOG_STR << "\n";
  }
}

auto shader::compile(const shader_info& info) -> GLuint
{
  if (glfwGetCurrentContext() == nullptr)
  {
    throw std::runtime_error("ERROR (blossom::shader): Cannot compile shaders. There is no current OpenGL context.");
  }

  GLuint shader_program = glCreateProgram();

  std::string vertex_shader_source_code   = read_source(info.vertex_shader_path);
  std::string geometry_shader_source_code;
  std::string fragment_shader_source_code = read_source(info.fragment_shader_path);

  const bool SHOULD_COMPILE_GEOMETRY_SHADER = !info.geometry_shader_path.empty();

  compile_shader_<shader_type::VERTEX>(vertex_shader_source_code, shader_program);

  if (SHOULD_COMPILE_GEOMETRY_SHADER)
  {
    geometry_shader_source_code = read_source(info.geometry_shader_path);
    compile_shader_<shader_type::GEOMETRY>(geometry_shader_source_code, shader_program);
  }

  compile_shader_<shader_type::FRAGMENT>(fragment_shader_source_code, shader_program);

  GLint successfully_linked = 0;
  glLinkProgram(shader_program);
  glGetProgramiv(shader_program, GL_LINK_STATUS, &successfully_linked);

  if (successfully_linked == 0)
  {
    print_program_log_(shader_program);
    throw std::runtime_error("ERROR (blossom::shader): Shader program linking failed!");
  }

  return shader_program;
}
