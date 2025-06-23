#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <string>
#include "../headers/shader.h"

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
