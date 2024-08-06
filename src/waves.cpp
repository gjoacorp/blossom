#include "../headers/shader.h"
#include "../headers/window.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "../glm/glm.hpp"
#include "../glm/ext.hpp"


using namespace std;

#define num_vaos 1 
#define num_vbos 2


GLuint rendering_program; 

glm::vec3 camera_pos;

int width, height;
float aspect;

int init_vertices() {
   GLuint vao[1]; 
   GLuint vbo[1]; 
   GLuint ibo[1];

   std::vector<glm::vec3> grid_vertices;
   std::vector<GLuint> grid_indices;

   int grid_length = 1000;

   for (int y = 0; y < grid_length; ++y) {
      for (int x = 0; x < grid_length; ++x) {
         grid_vertices.push_back({x * 0.1f, 0.0f, y * 0.1f});
      }
   }

   std::cout << "Total Vertices: " << grid_vertices.size() << std::endl;

   for (int y = 0; y < grid_length - 1; ++y) {
      for (int x = 0; x < grid_length - 1; ++x) {
         grid_indices.push_back(x + (y * grid_length));
         grid_indices.push_back(x + 1 + (y * grid_length));
         grid_indices.push_back(x + ((y + 1) * grid_length));
         grid_indices.push_back(x + ((y + 1) * grid_length));
         grid_indices.push_back(x + 1 + (y * grid_length));
         grid_indices.push_back(x + 1 + ((y + 1) * grid_length));
      }
   }

   std::cout << "Total Indices: " << grid_indices.size() << std::endl;
   
   glGenVertexArrays(1, vao); 
   glGenBuffers(num_vbos, vbo);
   glGenBuffers(1, ibo);

   glBindVertexArray(vao[0]);
   glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo[0]);

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, grid_indices.size() * sizeof(GLuint), grid_indices.data(), GL_STATIC_DRAW);
   glBufferData(GL_ARRAY_BUFFER, grid_vertices.size() * 3 * sizeof(float), grid_vertices.data(), GL_STATIC_DRAW);
   glEnableVertexAttribArray(0);
   return grid_indices.size();
}

void render_grid(GLFWwindow* window, double& time) {
   GLuint mv_loc, proj_loc, t_loc;
   glm::mat4 p_mat, v_mat, m_mat, mv_mat;

   mv_loc = glGetUniformLocation(rendering_program, "mv_matrix");
   proj_loc = glGetUniformLocation(rendering_program, "proj_matrix");
   t_loc = glGetUniformLocation(rendering_program, "time");

   // building the perspective matrix

   glfwGetFramebufferSize(window, &width, &height);
   aspect = (float)width / (float)height;
   p_mat = glm::perspective(1.0472f, aspect, 0.1f, 100.0f);

   // building the view, model, and model-view matrices

   v_mat = glm::translate(glm::mat4(1.0f), -camera_pos);
   mv_mat = v_mat;

   glUniformMatrix4fv(mv_loc, 1, GL_FALSE, glm::value_ptr(mv_mat));
   glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(p_mat));
   glUniform1f(t_loc, time);
}

void display(GLFWwindow* window, int size, double time) {
   glClearColor(0.0, 0.0, 0.0, 1.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glUseProgram(rendering_program);
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);
   glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);

   render_grid(window, time);
}

int main(void) {
   camera_pos = {5.0f, 1.0f, 10.0f};

   window w(1920, 1080, "Blossom");

   w.init();
   int size = init_vertices();

   shader s("shaders/frag.txt", "shaders/vert.txt");
   rendering_program = s.init();
   glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );


   while (!glfwWindowShouldClose(w.window_ptr)) {
      double current_time = glfwGetTime();
      static double last_frame_time = 0.0;
      double delta_time = current_time - last_frame_time;

      last_frame_time = current_time;
      // std::cout << "FPS — " << 1.0 / delta_time << std::endl;

      if (glfwGetKey(w.window_ptr, GLFW_KEY_W) == GLFW_PRESS) {
          camera_pos[2] -= 10.0 * delta_time;
      }
      else if (glfwGetKey(w.window_ptr, GLFW_KEY_S) == GLFW_PRESS) {
          camera_pos[2] += 10.0 * delta_time;
      }
      else if (glfwGetKey(w.window_ptr, GLFW_KEY_D) == GLFW_PRESS) {
          camera_pos[0] += 10.0 * delta_time;
      }
      else if (glfwGetKey(w.window_ptr, GLFW_KEY_A) == GLFW_PRESS) {
          camera_pos[0] -= 10.0 * delta_time;
      }
      else if (glfwGetKey(w.window_ptr, GLFW_KEY_SPACE) == GLFW_PRESS) {
          camera_pos[1] += 10.0 * delta_time;
      }
      else if (glfwGetKey(w.window_ptr, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
          camera_pos[1] -= 10.0 * delta_time;
      }
      display(w.window_ptr, size, glfwGetTime());
      glfwSwapBuffers(w.window_ptr); // swaps the front and back colour buffers
      glfwPollEvents();
   }

   w.destroy();

   exit(EXIT_SUCCESS);
}
