#include "../headers/window.h"
#include <iostream>


window::window(const int& size_x, const int& size_y, const char* title) {
   if (!glfwInit()) {
      std::cout << "Failed to initialise GLFW." << std::endl;
      exit(EXIT_FAILURE); 
   }
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   this->window_ptr = glfwCreateWindow(size_x, size_y, title, NULL, NULL);
}


void window::init() {
   glfwMakeContextCurrent(window_ptr);
   if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
   glfwSwapInterval(1); // sets the color buffer swap interval (i.e. vsync)
}

void window::destroy() const {
   glfwDestroyWindow(window_ptr);
   glfwTerminate();
}
