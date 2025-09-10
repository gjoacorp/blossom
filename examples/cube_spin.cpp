#include "../headers/shader.h"
#include "../headers/window.h"
//#include "../headers/mesh.h"
#include "../headers/cube.h"
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
GLuint model_loc, proj_loc, view_loc;

glm::mat4 p_mat, m_mat, v_mat;

glm::vec3 camera_pos;
glm::vec3 camera_rot;

const float speed = 2;

float yaw_angle = 0.0f;

void init_uniforms(GLFWwindow* window) 
{
  model_loc = glGetUniformLocation(rendering_program, "model");
  view_loc = glGetUniformLocation(rendering_program, "view");
  proj_loc = glGetUniformLocation(rendering_program, "projection");
}

void display(GLFWwindow* window, const blossom::cube& banana) 
{
  int width = 0;
  int height = 0;
  float aspect = 0.0f;

  glfwGetFramebufferSize(window, &width, &height);
  aspect = (float)width / (float)height;

  // camera def
  p_mat = glm::perspective(1.0472f, aspect, 0.1f, 100.0f);

  // camera location
  v_mat = glm::translate(glm::mat4(1.0f), -camera_pos);
  v_mat = glm::rotate(v_mat, -yaw_angle, glm::vec3(0, 1, 0));

  // cube pos
  m_mat = banana.calc_model_matrix();

  glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(v_mat));
  glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(p_mat));
  glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(m_mat) );
}

int main() 
{
  camera_pos = {0.0f, 1.0f, 5.0f};
  blossom::window w(WINDOW_WIDTH, WINDOW_HEIGHT, "Blossom Cube Example");
  w.init();

  glClearColor(0.0, 0.0, 0.0, 1.0);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  blossom::shader s("shaders/default.frag", "shaders/default.vert");
  rendering_program = s.program_id;

  init_uniforms(w.window_ptr);

  blossom::cube cube {s.program_id};

  while (!glfwWindowShouldClose(w.window_ptr)) 
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    double current_time = glfwGetTime();
    static double last_frame_time = 0.0;
    double delta_time = current_time - last_frame_time;
    last_frame_time = current_time;

    yaw_angle += speed * delta_time;

    display(w.window_ptr, cube);

    cube.draw();

    glfwSwapBuffers(w.window_ptr); // swaps the front and back colour buffers
    glfwPollEvents();
  }

  w.destroy();
  exit(EXIT_SUCCESS);
}
