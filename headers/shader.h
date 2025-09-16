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
      const char* frag_path_;
      const char* vert_path_;

      void init_();

      std::string read_source_(const char* path);
      bool check_gl_error_() const;
      void print_log_(GLuint shader) const;

    public:
      GLuint program_id;

      shader(const char* frag_path, const char* vert_path);
      shader() = default;
  };
}

#endif
