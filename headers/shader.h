#ifndef BLOSSOM_SHADER_H
#define BLOSSOM_SHADER_H

#include <string>
#include <GL/glew.h>
#include <gtest/gtest_prod.h>

namespace blossom 
{
  class shader 
  {
    private:
      /// @brief The path to the fragment shader's source. Specified relative to the project root.
      const char* frag_path_;
      /// @brief The path to the vertex shader's source. Specified relative to the project root.
      const char* vert_path_;

      /// @brief Compiles and links the vertex and fragment shader sources into an OpenGL program object. The OpenGL handle (ID) of this program object is stored in `shader::program_id`.
      void init_();

    public:
      /// @brief Reads the source located at `path` into the output.
      /// @return a `std::string` containing the source.
      /// @throws std::runtime_error if the source located at `path` cannot be found.
      static auto read_source(const char* path) -> std::string;
      /// @brief Retrieves and prints the info log for the shader object `shader`.
      /// Used primarily for debugging shader compilation errors and warnings.
      /// @param shader A shader object returned from [`glCreateShader()`](https://docs.gl/gl4/glCreateShader) or otherwise.

      /// @brief Prints the shader log of the shader object with name `shader`.
      /// @throws std::runtime_error if there is no current OpenGL context.
      /// @throws std::runtime_error if `shader` is not the name of a valid shader object.
      static void print_log(GLuint shader);
      /// @brief The OpenGL handle (ID) of the program object created in `shader::init_()`.
      GLuint program_id;

      /// @brief Constructs a program object to which the fragment shader at `frag_path` and vertex shader at `vert_path` are linked.
      /// The program object's OpenGL handle (ID) is stored in `shader::program_id`.
      /// @param frag_path is the path, relative to the project root, of the fragment shader's source.
      /// @param vert_path is the path, relative to the project root, of the vertex shader's source.
      shader(const char* frag_path, const char* vert_path);
      /// @brief Defaulted constructor.
      shader() = default;
  };
}

#endif
