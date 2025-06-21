 /* This example is adapted from the triangles.cpp example
 * given in OpenGL Programming Guide (Ninth Edition) by John Kessenich, Graham Sellers, and Dave Shreiner
 * on pages 5 to 7. */

#include "../headers/shader.h"
#include "../headers/window.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(void) 
{
   window w(1920, 1080, "Triangles Example");
   w.init();

   const GLfloat vertices[12] = 
   {
      -0.90, -0.90,
       0.85, -0.90,
      -0.90,  0.85, 
       0.90, -0.85,
       0.90,  0.90,
      -0.85,  0.90
   };

   GLuint arrays[1];
   GLuint buffers[1];

   glCreateVertexArrays (1, arrays);
   glBindVertexArray (arrays[0]);
   
   glCreateBuffers ( 1, buffers );
   glBindBuffer ( GL_ARRAY_BUFFER, buffers[0] );
   glNamedBufferStorage ( buffers[0], sizeof(vertices), vertices, 0 );

   shader s("shaders/triangles.frag", "shaders/triangles.vert");
   GLuint rendering_program = s.init();
   glUseProgram(rendering_program);

   glVertexAttribPointer ( 0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(0) );
   glEnableVertexAttribArray ( 0 );

   const GLfloat clear_color[] = { 0.0f, 0.0f, 0.0f, 0.0f};

   while ( !glfwWindowShouldClose(w.window_ptr) )
   {
      glClearBufferfv(GL_COLOR, 0, clear_color);
      glDrawArrays(GL_TRIANGLES, 0, 6);
      glfwSwapBuffers(w.window_ptr);
      glfwPollEvents();
   }

   w.destroy();
}
