#include "../headers/shader.h"
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <stdexcept>

using blossom::shader;

shader::shader(const char* frag_path, const char* vert_path) : 
  frag_path_(frag_path), 
  vert_path_(vert_path) 
{
  init_();
}

auto shader::read_source_(const char* path) -> std::string
{
  std::string file_content;
  std::ifstream file(path, std::ios::in);
  std::string line;

  while (std::getline(file, line)) 
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

void shader::print_log_(GLuint shader) const 
{
  int length = 0;
  int char_written = 0;
  char* log;

  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

  if (length > 0) 
  {
    log = (char*)malloc(length);
    glGetShaderInfoLog(shader, length, &char_written, log);
    std::cout << "Shader Log: " << log << "\n";
    free(log);
  }
}

void shader::init_() 
{
  if (!glfwGetCurrentContext())
  {
    throw std::runtime_error("ERROR: Cannot initialise shader (there is no current OpenGL context.) Ensure that a GL context is active before shader initialisation.");
  }

  std::string vertex_shader_source_string = read_source_(vert_path_);
  std::string fragment_shader_source_string = read_source_(frag_path_);

  const char* vertex_shader_source = vertex_shader_source_string.c_str();
  const char* fragment_shader_source = fragment_shader_source_string.c_str();

  const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
  glCompileShader(vertex_shader);
  
  GLint vertex_shader_compilation_status;
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &vertex_shader_compilation_status);

  if (vertex_shader_compilation_status == GL_FALSE) 
  {
    std::cout << "ERROR: Vertex shader compilation failed." << "\n";
    print_log_(vertex_shader);
  }

  glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr);
  glCompileShader(fragment_shader);

  GLint fragment_shader_compilation_status;
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &fragment_shader_compilation_status);

  if (fragment_shader_compilation_status == GL_FALSE) 
  {
    std::cout << "ERROR: Fragment shader compilation failed." << "\n";
    print_log_(fragment_shader);
  }

  GLuint shader_program = glCreateProgram();

  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  program_id = shader_program;
}
