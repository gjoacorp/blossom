#include "../headers/window.h"
#include "../headers/rectangle.h"
#include "../headers/orthographic_camera.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

const unsigned int WINDOW_WIDTH = 1920;
const unsigned int WINDOW_HEIGHT = 1080;
const GLfloat clear_color[] = { 0.0f, 0.0f, 0.0f, 0.0f};

int main() 
{
  blossom::window w(1920, 1080, "Triangle Example");
  w.enter_fullscreen();
  w.init();

  blossom::shader rect_shader {"shaders/default.frag", "shaders/default.vert"};
  blossom::rectangle rect {rect_shader.program_id};

  rect.position = {500.0f, 500.0, 0.0f};
  rect.scale = {200.0f, 100.0f, 0.0f};
  glm::mat4 model_matrix = rect.calc_model_matrix();
  blossom::orthographic_camera cam {{0.0f, 0.0f, 0.0f}, 1920, 1080};

  GLuint model_loc = glGetUniformLocation(rect_shader.program_id, "model");
  GLuint view_loc = glGetUniformLocation(rect_shader.program_id, "view");
  GLuint projection_loc = glGetUniformLocation(rect_shader.program_id, "projection");

  while ( !glfwWindowShouldClose(w.window_ptr) )
  {
    glClearBufferfv(GL_COLOR, 0, clear_color);
    rect.draw();
    glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model_matrix));
    glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(cam.view_matrix));
    glUniformMatrix4fv(projection_loc, 1, GL_FALSE, glm::value_ptr(cam.projection_matrix));
    glfwSwapBuffers(w.window_ptr);
    glfwPollEvents();
  }
  w.destroy();
}
