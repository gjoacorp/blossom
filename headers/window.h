#ifndef BLOSSOM_WINDOW_H
#define BLOSSOM_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace blossom
{
  class window 
  {
    public:
      /// @brief The pointer returned by [glfwCreateWindow()](https://www.glfw.org/docs/latest/group__window.html#ga3555a418df92ad53f917597fe2f64aeb).
      /// This pointer is set in the `window` constructor.
      GLFWwindow* window_ptr;

      /// @brief Constructs a new window with an associated OpenGL context.
      /// @param width is width of the window in pixels.
      /// @param height is height of the window in pixels.
      /// @param title is title of the window.
      /// @throws std::runtime_error if GLFW initialisation fails.
      /// @throws std::runtime_error if GLEW initialisation fails.
      window (int width, int height, const char* title);
      /// @brief Calls `window::destroy()`.
      ~window();

      void enter_fullscreen() const;
      /// @brief Calls [`glfwTerminate()`](https://www.glfw.org/docs/latest/group__init.html#gaaae48c0a18607ea4a4ba951d939f0901) and nullifies `window::window_ptr`.
      void destroy();

    private:
      /// @brief Resizes the viewport when the window is resized.
      static void framebuffer_size_callback_(GLFWwindow* window, int width, int height);
  };
}

#endif
