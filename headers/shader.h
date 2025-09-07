#ifndef SHADER
#define SHADER

#include <string>
#include <fstream>
#include <GL/glew.h>
#include <iostream>
#include <gtest/gtest_prod.h>

class shader 
{
  private:
    const char* frag_path;
    const char* vert_path;

    void init();

    std::string read_source(const char* path);
    bool check_gl_error() const;
    void print_log(GLuint shader) const;

    FRIEND_TEST(ShaderTest, ReadSourceReadsFileCorrectly);
    FRIEND_TEST(ShaderTest, ReadSourceThrowsOnMissingFile);
    FRIEND_TEST(ShaderTest, ReadSourceReturnsEmptyStringOnEmptyFile);

  public:
    GLuint program_id;

    shader(const char* frag_path, const char* vert_path);
    shader() = default;
};

#endif
