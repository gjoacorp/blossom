#include "../headers/window.h"
#include "../headers/rectangle.h"
#include "../headers/orthographic_camera.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

const unsigned int WINDOW_WIDTH = 1920;
const unsigned int WINDOW_HEIGHT = 1080;
const char* WINDOW_TITLE = "Blossom Rectangle Camera Example";

const GLfloat CLEAR_COLOR[] = { 0.0f, 0.0f, 0.0f, 0.0f};

int main() 
{
  blossom::window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
  window.enter_fullscreen();

  blossom::shader rect_shader {"shaders/default.frag", "shaders/default.vert"};
  blossom::rectangle rect {rect_shader.program_id};

  rect.position = {500.0f, 500.0f, 0.0f};
  rect.scale = {200.0f, 100.0f, 0.0f};
  blossom::orthographic_camera camera {{0.0f, 0.0f, 0.0f}, WINDOW_WIDTH, WINDOW_HEIGHT};

  while ( !glfwWindowShouldClose(window.window_ptr) )
  {
    glClearBufferfv(GL_COLOR, 0, CLEAR_COLOR);
    rect.draw(&camera);
    glfwSwapBuffers(window.window_ptr);
    glfwPollEvents();
  }
  window.destroy();
}
