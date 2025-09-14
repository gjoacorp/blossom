#include "../headers/shader.h"
#include "../headers/window.h"
#include "../headers/mesh.h"
#include "../headers/perspective_camera.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <tuple>

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;
const char* WINDOW_TITLE = "Blossom Waves Example";

std::tuple<std::vector<glm::vec3>, std::vector<GLuint>> 
generate_grid(std::size_t size, float x_div, float y_div)
{
  // Vertex initialisation
  std::vector<glm::vec3> vertices;

  for (std::size_t y = 0; y < size; ++y) 
  {
    for (std::size_t x = 0; x < size; ++x) 
    {
      vertices.push_back({x * x_div, 0.0f, y * y_div}); 
    }
  }

  // Index initialisation
  std::vector<GLuint> indices;

  for (std::size_t y = 0; y < size - 1; ++y) 
  {
    for (std::size_t x = 0; x < size - 1; ++x) 
    {
      indices.push_back(x + (y * size));
      indices.push_back(x + 1 + (y * size));
      indices.push_back(x + ((y + 1) * size));
      indices.push_back(x + ((y + 1) * size));
      indices.push_back(x + 1 + (y * size));
      indices.push_back(x + 1 + ((y + 1) * size));
    }
  }
  return std::make_tuple(vertices, indices);
}

int main() 
{
  blossom::window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

  glClearColor(0.0, 0.0, 0.0, 1.0);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  const glm::vec3 camera_position = {25.0f, 5.0f, 25.0f};
  blossom::perspective_camera camera { camera_position, WINDOW_WIDTH, WINDOW_HEIGHT, 90.0f, 0.1f, 200.0f };
  camera.rotation.x = -45.0f;
  camera.update_view_matrix();

  blossom::shader waves_shader("shaders/waves.frag", "shaders/waves.vert");
  GLuint time_uniform_location = glGetUniformLocation(waves_shader.program_id, "time");

  auto grid_data = generate_grid(500, 0.1f, 0.1f);

  blossom::mesh grid {std::get<0>(grid_data), std::get<1>(grid_data), waves_shader.program_id};
  grid.set_polygon_mode(GL_LINE);

  while (!glfwWindowShouldClose(window.window_ptr)) 
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUniform1f(time_uniform_location, glfwGetTime());

    grid.draw(&camera);
    glfwSwapBuffers(window.window_ptr); // swaps the front and back colour buffers
    glfwPollEvents();
  }
  window.destroy();
}
