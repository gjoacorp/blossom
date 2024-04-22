#include <string>
#include <fstream>
#include <GL/glew.h>
#include <iostream>

class shader {
   private:
      const char* frag_path;
      const char* vert_path;
      std::string read_source(const char* path);
      bool check_gl_error() const;
      void print_log(GLuint shader) const;

   public:
      shader(const char* frag_path, const char* vert_path);
      GLuint init();

};
