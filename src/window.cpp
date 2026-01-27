#include "../headers/window.h"
#include <stdexcept>
#include <iostream>

using blossom::window;

window::window(int width, int height, const char* title) 
{
  if ( !glfwInit() ) 
  {
    glfwTerminate();
    throw std::runtime_error("ERROR: Failed to initialise GLFW.");
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);

  window_ptr = glfwCreateWindow(width, height, title, NULL, NULL);

  glfwMakeContextCurrent(window_ptr);
  glfwSetFramebufferSizeCallback(window_ptr, framebuffer_size_callback_);

  glewExperimental = (GLboolean)true;

  GLenum err = glewInit();
  if ( err != GLEW_OK )
  {
    std::string error_str = reinterpret_cast<const char*>(glewGetErrorString(err));
    if (error_str == "No GLX display")
    {
      std::cout << "Wayland detected: Ignoring GLX init error. Continuing..." << "\n";
    }
    else
    {
      glfwTerminate();
      throw std::runtime_error("ERROR: Failed to initialise GLEW. Reason: " + error_str);
    }
  }

  glfwSwapInterval(1); 
}

void window::enter_fullscreen() const
{
  GLFWmonitor* monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode* mode = glfwGetVideoMode(monitor);
  glfwSetWindowMonitor(window_ptr, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
}

void window::destroy()
{
  glfwTerminate();
  window_ptr = nullptr;
}

window::~window()
{
  destroy();
}

void window::framebuffer_size_callback_(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}
