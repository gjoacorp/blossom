#include <GL/glew.h>
#include <GLFW/glfw3.h>

class window 
{
  public:
    GLFWwindow* window_ptr;

    window (const int& size_x, const int& size_y, const char* title);

    void enter_fullscreen() const;

    void init();
    void destroy() const;

  private:
    static void framebuffer_size_callback_(GLFWwindow* window, int width, int height);
};
