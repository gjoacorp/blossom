#ifndef BLOSSOM_SHADER_H
#define BLOSSOM_SHADER_H

#include <string>
#include <fstream>
#include <GL/glew.h>
#include <iostream>
#include <gtest/gtest_prod.h>

namespace blossom 
{
  class shader 
  {
    private:
      const char* frag_path;
      const char* vert_path;

      void init();

      std::string read_source(const char* path);
      bool check_gl_error() const;
      void print_log(GLuint shader) const;

    public:
      GLuint program_id;

      shader(const char* frag_path, const char* vert_path);
      shader() = default;
  };
}

#endif
