#include "../headers/window.h"
#include <stdexcept>

using blossom::window;

window::window(int width, int height, const char* title) 
{
  glfwSetErrorCallback(fatal_error_callback_);

  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  window_ptr = glfwCreateWindow(width, height, title, NULL, NULL);

  glfwMakeContextCurrent(window_ptr);
  glfwSetFramebufferSizeCallback(window_ptr, framebuffer_size_callback_);

  GLenum err = glewInit();
  if ( err != GLEW_OK )
  {
      const std::string description = reinterpret_cast<const char*>(glewGetErrorString(err));
      const std::string error_string = "ERROR > glewInit failed. \nREASON > " + description;
      glfwTerminate();
      throw std::runtime_error(error_string);
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

void window::fatal_error_callback_(int error, const char* description) 
{
    const std::string error_string = "ERROR > " + get_error_name_(error) + "\nDESCRIPTION > " + std::string(description);
    glfwTerminate();
    throw std::runtime_error(error_string);
}

std::string window::get_error_name_(int error) 
{
    switch (error) 
    {
        case GLFW_NO_ERROR:  return "GLFW_NO_ERROR";
        case GLFW_NOT_INITIALIZED:  return "GLFW_NOT_INITIALIZED";
        case GLFW_NO_CURRENT_CONTEXT:  return "GLFW_NO_CURRENT_CONTEXT";
        case GLFW_INVALID_ENUM:  return "GLFW_INVALID_ENUM";
        case GLFW_OUT_OF_MEMORY:  return "GLFW_OUT_OF_MEMORY";;
        case GLFW_API_UNAVAILABLE:  return "GLFW_API_UNAVAILABLE";;
        case GLFW_VERSION_UNAVAILABLE:  return "GLFW_VERSION_UNAVAILABLE";
        case GLFW_PLATFORM_ERROR:  return "GLFW_PLATFORM_ERROR";
        case GLFW_FORMAT_UNAVAILABLE:  return "GLFW_FORMAT_UNAVAILABLE";
        case GLFW_NO_WINDOW_CONTEXT:  return "GLFW_NO_WINDOW_CONTEXT";
    }
}
