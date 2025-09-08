#include "../headers/shader.h"
#include "../headers/window.h"
#include "../headers/mesh.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <tuple>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

GLuint rendering_program; 
GLuint mv_loc, proj_loc, t_loc;

glm::mat4 p_mat, mv_mat;

glm::vec3 camera_pos;
glm::vec3 camera_rot;

float yaw_angle = 0.0f;

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

void init_uniforms(GLFWwindow* window) 
{
  mv_loc = glGetUniformLocation(rendering_program, "mv_matrix");
  proj_loc = glGetUniformLocation(rendering_program, "proj_matrix");
  t_loc = glGetUniformLocation(rendering_program, "time");
}

void display(GLFWwindow* window) 
{
  int width = 0;
  int height = 0;
  float aspect = 0.0f;

  glfwGetFramebufferSize(window, &width, &height);
  aspect = (float)width / (float)height;

  p_mat = glm::perspective(1.0472f, aspect, 0.1f, 100.0f);
  mv_mat = glm::translate(glm::mat4(1.0f), -camera_pos);
  mv_mat = glm::rotate(mv_mat, -yaw_angle, glm::vec3(0, 1, 0));

  glUniformMatrix4fv(mv_loc, 1, GL_FALSE, glm::value_ptr(mv_mat));
  glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(p_mat));
  glUniform1f(t_loc, glfwGetTime());
}

int main() 
{
  camera_pos = {0.0f, 1.0f, 5.0f};
  window w(WINDOW_WIDTH, WINDOW_HEIGHT, "Blossom Waves Example");
  w.init();

  glClearColor(0.0, 0.0, 0.0, 1.0);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  shader s("shaders/waves.frag", "shaders/waves.vert");
  rendering_program = s.program_id;

  auto grid_data = generate_grid(100, 0.1f, 0.1f);

  mesh grid {std::get<0>(grid_data), std::get<1>(grid_data), rendering_program};
  grid.set_draw_mode(GL_LINE);
  init_uniforms(w.window_ptr);

  while (!glfwWindowShouldClose(w.window_ptr)) 
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    double current_time = glfwGetTime();
    static double last_frame_time = 0.0;
    double delta_time = current_time - last_frame_time;
    last_frame_time = current_time;

    yaw_angle += 0.25f * delta_time;

    display(w.window_ptr);
    grid.draw();
    glfwSwapBuffers(w.window_ptr); // swaps the front and back colour buffers
    glfwPollEvents();
  }

  w.destroy();
  exit(EXIT_SUCCESS);
}
