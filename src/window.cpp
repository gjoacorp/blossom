#include "../headers/window.h"
#include <stdexcept>
#include <iostream>

using blossom::window;

window::window(int width, int height, const char* title) 
{
  glfwSetErrorCallback(fatal_error_callback_);

  glfwInit();

  const int PLATFORM = glfwGetPlatform();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

  window_ptr = glfwCreateWindow(width, height, title, nullptr, nullptr);

  glfwMakeContextCurrent(window_ptr);
  glfwSetFramebufferSizeCallback(window_ptr, framebuffer_size_callback_);

  const bool GL_LOADED = gladLoadGL(glfwGetProcAddress);
  if (!GL_LOADED)
  {
      glfwTerminate();
      throw std::runtime_error("ERROR > glad failed to initialize.");
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
  const std::string ERROR_STRING = "ERROR > " + get_error_name_(error) + "\nDESCRIPTION > " + std::string(description);
  glfwTerminate();
  throw std::runtime_error(ERROR_STRING);
}

auto window::get_error_name_(int error) -> std::string 
{
  std::string output;
  switch (error) 
  {
    default:
      output = "";
      break;
    case GLFW_NO_ERROR:
      output = "GLFW_NO_ERROR";
      break;
    case GLFW_NOT_INITIALIZED:  
      output = "GLFW_NOT_INITIALIZED";
      break;
    case GLFW_NO_CURRENT_CONTEXT:  
      output = "GLFW_NO_CURRENT_CONTEXT";
      break;
    case GLFW_INVALID_ENUM:  
      output = "GLFW_INVALID_ENUM";
      break;
    case GLFW_OUT_OF_MEMORY:  
      output = "GLFW_OUT_OF_MEMORY";;
      break;
    case GLFW_API_UNAVAILABLE:  
      output = "GLFW_API_UNAVAILABLE";;
      break;
    case GLFW_VERSION_UNAVAILABLE:  
      output = "GLFW_VERSION_UNAVAILABLE";
      break;
    case GLFW_PLATFORM_ERROR:  
      output = "GLFW_PLATFORM_ERROR";
      break;
    case GLFW_FORMAT_UNAVAILABLE:  
      output = "GLFW_FORMAT_UNAVAILABLE";
      break;
    case GLFW_NO_WINDOW_CONTEXT:  
      output = "GLFW_NO_WINDOW_CONTEXT";
      break;
  }
  return output;
}
