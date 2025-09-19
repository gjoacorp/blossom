#include "../headers/window.h"
#include "../headers/grid.h"
#include "../headers/perspective_camera.h"

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;
const char* WINDOW_TITLE = "Blossom Waves Example";

int main() 
{
  blossom::window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

  glClearColor(0.0, 0.0, 0.0, 1.0);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  const glm::vec3 camera_position = {25.0f, 7.5f, 25.0f};
  blossom::perspective_camera camera { camera_position, WINDOW_WIDTH, WINDOW_HEIGHT, 90.0f, 0.1f, 200.0f };
  camera.rotation.x = -45.0f;
  camera.update_view_matrix();

  blossom::shader waves_shader("shaders/waves.frag", "shaders/waves.vert");
  GLuint time_uniform_location = glGetUniformLocation(waves_shader.program_id, "time");

  blossom::grid grid(waves_shader.program_id, 500, 0.25f, 0.25f);
  grid.set_polygon_mode(GL_LINE);

  while (!glfwWindowShouldClose(window.window_ptr)) 
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    grid.draw(&camera);
    glUniform1f(time_uniform_location, glfwGetTime());
    glfwSwapBuffers(window.window_ptr); // swaps the front and back colour buffers
    glfwPollEvents();
  }
  window.destroy();
}
