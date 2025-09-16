#define STB_IMAGE_IMPLEMENTATION


#include "../headers/mesh.h"
#include "../headers/shader.h"
#include "../headers/window.h"
#include "../headers/cube.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "../include/stb_image.h"

//
GLuint model_loc, proj_loc, view_loc;

glm::mat4 p_mat, m_mat, v_mat;

glm::vec3 camera_pos;
glm::vec3 camera_rot;

const float speed = 2;

float yaw_angle = 0.0f;
//

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

unsigned int texture;
int width, height, nrChannels;

void init_uniforms(GLFWwindow* window, GLuint rendering_program) 
{
  model_loc = glGetUniformLocation(rendering_program, "model");
  view_loc = glGetUniformLocation(rendering_program, "view");
  proj_loc = glGetUniformLocation(rendering_program, "projection");
}

void display(GLFWwindow* window, const blossom::mesh& mesh) 
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
  m_mat = mesh.calc_model_matrix();

  glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(v_mat));
  glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(p_mat));
  glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(m_mat) );
}

int main()
{
  camera_pos = {0.0f, 1.0f, 5.0f};
  blossom::window windy(WINDOW_WIDTH, WINDOW_HEIGHT, "textures");
  windy.init();

  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  unsigned char *data = stbi_load("../textures/waffledog.png", &width, &height, &nrChannels, 0);

  if (data)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    std::cout << "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);
  
  blossom::shader s("shaders/default.frag", "shaders/default.vert");

  init_uniforms(windy.window_ptr, s.program_id);

  blossom::cube cube(s.program_id);
  cube.scale = glm::vec3(2.0f, 2.0f, 2.0f);

  while (!glfwWindowShouldClose(windy.window_ptr)) 
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    double current_time = glfwGetTime();
    static double last_frame_time = 0.0;
    double delta_time = current_time - last_frame_time;
    last_frame_time = current_time;

    yaw_angle += speed * delta_time;

    display(windy.window_ptr, cube);

    cube.draw(texture);

    glfwSwapBuffers(windy.window_ptr); // swaps the front and back colour buffers
    glfwPollEvents();
  }

  windy.destroy();
  exit(EXIT_SUCCESS);
}
