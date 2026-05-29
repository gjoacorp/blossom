#ifndef BLOSSOM_SHADER_H
#define BLOSSOM_SHADER_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <glad/gl.h>
#include <gtest/gtest_prod.h>

namespace blossom 
{
  struct shader_info
  {
    std::string vertex_shader_path;
    std::string geometry_shader_path;
    std::string fragment_shader_path;
  };

  class shader 
  {
    enum class shader_type : uint8_t
    {
      VERTEX,
      FRAGMENT,
      GEOMETRY,
    };

    private:
      static void print_log_(GLuint shader);
      static void print_program_log_(GLuint shader_program);

      static auto get_gl_shader_type_(shader_type type) -> GLenum
      {
        switch(type)
        {
          case (shader_type::VERTEX):
            return GL_VERTEX_SHADER;

          case(shader_type::GEOMETRY):
            return GL_GEOMETRY_SHADER;

          case(shader_type::FRAGMENT):
            return GL_FRAGMENT_SHADER;
          default:
            std::cout << "WARNING (blossom::shader): Unknown shader type passed to shader::get_gl_shader_type_(). Returning 0.\n";
            return 0;
        }
      }

      static auto get_name_from_type_(shader_type type) -> std::string
      {
        switch(type)
        {
          case (shader_type::VERTEX):
            return "Vertex";
          case (shader_type::GEOMETRY):
            return "Geometry";
          case (shader_type::FRAGMENT):
            return "Fragment";
          default:
            return "Unknown";
        }
      }

      template<shader_type ST>
      static void compile_shader_(const std::string& shader_source, GLuint program)
      {
        const char* ss_ptr = shader_source.c_str();

        GLuint shader = 0;
        GLint shader_compilation_status = 0;

        const GLenum SHADER_GL_TYPE = get_gl_shader_type_(ST);

        shader = glCreateShader(SHADER_GL_TYPE);
        glShaderSource(shader, 1, &ss_ptr, nullptr);
        glCompileShader(shader);

        glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_compilation_status);

        if ( shader_compilation_status == GL_FALSE ) 
        {
          print_log_(shader);
          const std::string SHADER_NAME = get_name_from_type_(ST);
          throw std::runtime_error("ERROR (blossom::shader): " + SHADER_NAME + " shader compilation failed!");
        }

        glAttachShader(program, shader);
        glDeleteShader(shader);
      }

    public:
      static auto read_source(const std::string& path) -> std::string;
      static auto compile(const shader_info& info) -> GLuint;
  };
}

#endif
