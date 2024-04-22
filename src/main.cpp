#include "../headers/shader.h"
#include "../headers/window.h"
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<string>
#include<fstream>
#include "../glm/glm.hpp"
#include "../glm/ext.hpp"


using namespace std;

#define num_vaos 1 
#define num_vbos 2


GLuint rendering_program; 

glm::vec3 camera_pos;
glm::vec3 cube_pos;

GLuint vao[num_vaos]; 
GLuint vbo[num_vbos]; 

GLuint mv_loc, proj_loc;
int width, height;
float aspect;
glm::mat4 p_mat, v_mat, m_mat, mv_mat;

void init_vertices() {
   float vertex_positions[108] = {
      -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f,
      1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f,
      1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
      1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
      1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
      -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
      -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
      -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
      -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f,
      1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,
      -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f
   };
   
   glGenVertexArrays(1, vao); 
   glBindVertexArray(vao[0]);
   glGenBuffers(num_vbos, vbo);

   glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
   glEnableVertexAttribArray(0);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions), vertex_positions, GL_STATIC_DRAW);
}

void render_cube(GLFWwindow* window, glm::vec3 cube_pos) {
   mv_loc = glGetUniformLocation(rendering_program, "mv_matrix");
   proj_loc = glGetUniformLocation(rendering_program, "proj_matrix");

   // building the perspective matrix
   glfwGetFramebufferSize(window, &width, &height);
   aspect = (float)width / (float)height;
   p_mat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);

   // building the view, model, and model-view matrices

   v_mat = glm::translate(glm::mat4(1.0f), -camera_pos);
   m_mat = glm::translate(glm::mat4(1.0f), cube_pos);
   mv_mat = v_mat * m_mat;

   glUniformMatrix4fv(mv_loc, 1, GL_FALSE, glm::value_ptr(mv_mat));
   glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(p_mat));
}

void display(GLFWwindow* window) {
   glClearColor(0.3, 0.5, 0.15, 1.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glUseProgram(rendering_program);

   render_cube(window, {0.0f, 0.0f, 0.0f});

   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);
   glDrawArrays(GL_TRIANGLES, 0, 36);
}

int main(void) {
   camera_pos = {0.0f, 0.0f, 3.0f};

   window w(1280, 720, "Blossom");

   w.init();
   init_vertices();

   shader s("frag.txt", "vert.txt");
   rendering_program = s.init();


   while (!glfwWindowShouldClose(w.window_ptr)) {
      double current_time = glfwGetTime();
      static double last_frame_time = 0.0;
      double delta_time = current_time - last_frame_time;

      last_frame_time = current_time;
      std::cout << "FPS — " << 1.0 / delta_time << std::endl;

      if (glfwGetKey(w.window_ptr, GLFW_KEY_W) == GLFW_PRESS) {
          camera_pos[2] -= 5.0 * delta_time;
      }
      else if (glfwGetKey(w.window_ptr, GLFW_KEY_S) == GLFW_PRESS) {
          camera_pos[2] += 5.0 * delta_time;
      }
      else if (glfwGetKey(w.window_ptr, GLFW_KEY_D) == GLFW_PRESS) {
          camera_pos[0] += 5.0 * delta_time;
      }
      else if (glfwGetKey(w.window_ptr, GLFW_KEY_A) == GLFW_PRESS) {
          camera_pos[0] -= 5.0 * delta_time;
      }
      display(w.window_ptr);
      glfwSwapBuffers(w.window_ptr); // swaps the front and back color buffers
      glfwPollEvents();
   }

   w.destroy();

   exit(EXIT_SUCCESS);
}
