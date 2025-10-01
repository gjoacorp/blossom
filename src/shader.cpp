#include "../headers/shader.h"
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <vector>

using blossom::shader;

shader::shader(const char* frag_path, const char* vert_path) : 
  frag_path_(frag_path), 
  vert_path_(vert_path) 
{
  init_();
}

auto shader::read_source(const char* path) -> std::string
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
    throw std::runtime_error("The file" + std::string(path) + "doesn't exist.");
  }

  file.close();
  return file_content;
}

void shader::print_log(GLuint shader)
{
  if ( glfwGetCurrentContext() == nullptr )
  {
    throw std::runtime_error("ERROR: Cannot print shader log. There is no current OpenGL context.");
  }

  if ( glIsShader(shader) == GL_FALSE )
  {
    throw std::runtime_error("ERROR: Unable to print the shader log of an invalid shader object.");
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

void shader::init_() 
{
  if ( glfwGetCurrentContext() == nullptr )
  {
    throw std::runtime_error("ERROR: Cannot initialise shader (there is no current OpenGL context.) Ensure that a GL context is active before shader initialisation.");
  }

  std::string vertex_shader_source_string = read_source(vert_path_);
  std::string fragment_shader_source_string = read_source(frag_path_);

  const char* vertex_shader_source = vertex_shader_source_string.c_str();
  const char* fragment_shader_source = fragment_shader_source_string.c_str();

  const GLuint VERTEX_SHADER = glCreateShader(GL_VERTEX_SHADER);
  const GLuint FRAGMENT_SHADER = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(VERTEX_SHADER, 1, &vertex_shader_source, nullptr);
  glCompileShader(VERTEX_SHADER);
  
  GLint vertex_shader_compilation_status;
  glGetShaderiv(VERTEX_SHADER, GL_COMPILE_STATUS, &vertex_shader_compilation_status);

  if ( vertex_shader_compilation_status == GL_FALSE ) 
  {
    std::cout << "ERROR: Vertex shader compilation failed." << "\n";
    print_log(VERTEX_SHADER);
  }

  glShaderSource(FRAGMENT_SHADER, 1, &fragment_shader_source, nullptr);
  glCompileShader(FRAGMENT_SHADER);

  GLint fragment_shader_compilation_status;
  glGetShaderiv(FRAGMENT_SHADER, GL_COMPILE_STATUS, &fragment_shader_compilation_status);

  if ( fragment_shader_compilation_status == GL_FALSE ) 
  {
    std::cout << "ERROR: Fragment shader compilation failed." << "\n";
    print_log(FRAGMENT_SHADER);
  }

  GLuint shader_program = glCreateProgram();

  glAttachShader(shader_program, VERTEX_SHADER);
  glAttachShader(shader_program, FRAGMENT_SHADER);
  glLinkProgram(shader_program);

  glDeleteShader(VERTEX_SHADER);
  glDeleteShader(FRAGMENT_SHADER);

  program_id = shader_program;
}
