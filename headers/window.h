#include <GL/glew.h>
#include <GLFW/glfw3.h>

class window {
   public:
      GLFWwindow* window_ptr;

      window (const int& size_x, const int& size_y, const char* title);

      void init();
      void destroy() const;
};
