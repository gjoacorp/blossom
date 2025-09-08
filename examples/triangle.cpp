#include "../headers/shader.h"
#include "../headers/mesh.h"
#include "../headers/window.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

const unsigned int WINDOW_WIDTH = 1920;
const unsigned int WINDOW_HEIGHT = 1080;
const GLfloat clear_color[] = { 0.0f, 0.0f, 0.0f, 0.0f};

int main(void) 
{
  blossom::window w(1920, 1080, "Triangle Example");
  w.enter_fullscreen();
  w.init();

  std::vector<glm::vec3> vertices =
  {
    { 0.0f,   0.577f, 0.0f},
    {-0.5f,  -0.289f,  0.0f},
    { 0.5f,  -0.289f, 0.0f}
  };

  blossom::shader triangle_shader {"shaders/triangle.frag", "shaders/triangle.vert"};
  blossom::mesh triangle(vertices, triangle_shader.program_id);

  while ( !glfwWindowShouldClose(w.window_ptr) )
  {
    glClearBufferfv(GL_COLOR, 0, clear_color);
    triangle.draw();
    glfwSwapBuffers(w.window_ptr);
    glfwPollEvents();
  }

  w.destroy();
}
