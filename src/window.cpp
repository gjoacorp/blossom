#include "../headers/window.h"
#include <stdexcept>
#include <iostream>

using blossom::window;

window::window(int width, int height, const char* title) 
{
    glfwSetErrorCallback(fatal_error_callback_);

    if (glfwInit() != GLFW_TRUE)
    {
        throw std::runtime_error("ERROR > Failed to initialise GLFW.");
    }

    // Vulkan supplies its own rendering API; GLFW must not create an OpenGL context.
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    window_ptr = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window_ptr == nullptr)
    {
        glfwTerminate();
        throw std::runtime_error("ERROR > Failed to create GLFW window.");
    }
}

void window::enter_fullscreen() const
{
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    glfwSetWindowMonitor(window_ptr, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
}

void window::destroy()
{
    if (window_ptr != nullptr)
    {
        glfwDestroyWindow(window_ptr);
        window_ptr = nullptr;
        glfwTerminate();
    }
}

window::~window()
{
    destroy();
}

void window::fatal_error_callback_(int error, const char* description) 
{
    std::cerr << "ERROR > " << get_error_name_(error)
        << "\nDESCRIPTION > " << description << '\n';
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
            output = "GLFW_OUT_OF_MEMORY";
            break;
        case GLFW_API_UNAVAILABLE:  
            output = "GLFW_API_UNAVAILABLE";
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
