#include "../headers/window.h"
#include <iostream>

using blossom::window;

window::window(int width, int height, const char* title) 
{
  if ( !glfwInit() ) 
  {
    std::cout << "Failed to initialise GLFW." << std::endl;
    exit(EXIT_FAILURE); 
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  window_ptr = glfwCreateWindow(width, height, title, NULL, NULL);
  glfwSetFramebufferSizeCallback(window_ptr, framebuffer_size_callback_);
}

void window::enter_fullscreen() const
{
  GLFWmonitor* monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode* mode = glfwGetVideoMode(monitor);
  glfwSetWindowMonitor(window_ptr, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
}

void window::init() 
{
  glfwMakeContextCurrent(window_ptr);

  if ( glewInit() != GLEW_OK ) 
  { 
    exit(EXIT_FAILURE); 
  }

  glfwSwapInterval(1); // sets the color buffer swap interval (i.e. vsync)
}

void window::destroy() const 
{
  glfwDestroyWindow(window_ptr);
  glfwTerminate();
}

void window::framebuffer_size_callback_(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}
