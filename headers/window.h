#ifndef BLOSSOM_WINDOW_H
#define BLOSSOM_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace blossom
{
  class window 
  {
    public:
      GLFWwindow* window_ptr;

      window (int width, int height, const char* title);
      ~window();

      void enter_fullscreen() const;
      void destroy();

    private:
      static void framebuffer_size_callback_(GLFWwindow* window, int width, int height);
  };
}

#endif
