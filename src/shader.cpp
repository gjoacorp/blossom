#include "../headers/shader.h"
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <stdexcept>

shader::shader(const char* frag_path, const char* vert_path) : 
  frag_path(frag_path), 
  vert_path(vert_path) 
{
  init();
}

std::string shader::read_source(const char* path)
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

void shader::print_log(GLuint shader) const 
{
  int length = 0;
  int char_written = 0;
  char* log;

  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

  if (length > 0) 
  {
    log = (char*)malloc(length);
    glGetShaderInfoLog(shader, length, &char_written, log);
    std::cout << "Shader Log: " << log << std::endl;
    free(log);
  }
}

bool shader::check_gl_error() const 
{
  bool error_found = false;
  int gl_error = glGetError();

  while (gl_error != GL_NO_ERROR) 
  {
    std::cout << "gl_error: " << gl_error << std::endl;
    error_found = true;
    gl_error = glGetError();
  }
  return error_found;
}

void shader::init() 
{
  if (!glfwGetCurrentContext())
  {
    throw std::runtime_error("ERROR: Cannot initialise shader (there is no current OpenGL context.) Ensure that a GL context is active before shader initialisation.");
  }

  GLint vert_compiled, frag_compiled;

  std::string v_string = read_source(vert_path);
  std::string f_string = read_source(frag_path);

  const char* vert_source = v_string.c_str();
  const char* frag_source = f_string.c_str();

  GLuint v_shader = glCreateShader(GL_VERTEX_SHADER);
  GLuint f_shader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(v_shader, 1, &vert_source, NULL);
  glCompileShader(v_shader);

  // Checking that the vertex shader successfully compiles.
  check_gl_error();
  glGetShaderiv(v_shader, GL_COMPILE_STATUS, &vert_compiled);

  if (vert_compiled != 1) 
  {
    std::cout << "ERROR: Vertex shader compilation failed." << std::endl;
    print_log(v_shader);
  }

  glShaderSource(f_shader, 1, &frag_source, NULL);
  glCompileShader(f_shader);

  // Checking that the fragment shader successfully compiles. 
  check_gl_error();
  glGetShaderiv(f_shader, GL_COMPILE_STATUS, &frag_compiled);

  if (frag_compiled != 1) 
  {
    std::cout << "ERROR: Fragment shader compilation failed." << std::endl;
    print_log(f_shader);
  }

  GLuint vf_program = glCreateProgram();

  glAttachShader(vf_program, v_shader);
  glAttachShader(vf_program, f_shader);
  glLinkProgram(vf_program);

  glDeleteShader(v_shader);
  glDeleteShader(f_shader);

  program_id = vf_program;
}
