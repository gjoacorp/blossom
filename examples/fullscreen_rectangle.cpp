#include "../headers/window.h"
#include "../headers/rectangle.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

const unsigned int WINDOW_WIDTH = 1920;
const unsigned int WINDOW_HEIGHT = 1080;
const GLfloat clear_color[] = { 0.0f, 0.0f, 0.0f, 0.0f};

int main(void) 
{
  blossom::window w(1920, 1080, "Blossom Rectangle Example");
  w.enter_fullscreen();
  w.init();

  blossom::shader rect_shader {"shaders/rectangle.frag", "shaders/rectangle.vert"};
  blossom::rectangle rect {rect_shader.program_id};

  while ( !glfwWindowShouldClose(w.window_ptr) )
  {
    glClearBufferfv(GL_COLOR, 0, clear_color);
    rect.draw();
    glfwSwapBuffers(w.window_ptr);
    glfwPollEvents();
  }

  w.destroy();
}
