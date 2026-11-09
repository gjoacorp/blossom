#ifndef BLOSSOM_WINDOW_H
#define BLOSSOM_WINDOW_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace blossom
{
    class window 
    {
        public:
            /// @brief The GLFW window handle created by the constructor.
            GLFWwindow* window_ptr = nullptr;

            /// @brief Constructs a GLFW window with no client API, suitable for Vulkan rendering.
            /// @param width is width of the window in pixels.
            /// @param height is height of the window in pixels.
            /// @param title is title of the window.
            /// @throws std::runtime_error if GLFW initialisation fails.
            window (int width, int height, const char* title);
            /// @brief Calls `window::destroy()`.
            ~window();

            void enter_fullscreen() const;
            /// @brief Calls [`glfwTerminate()`](https://www.glfw.org/docs/latest/group__init.html#gaaae48c0a18607ea4a4ba951d939f0901) and nullifies `window::window_ptr`.
            void destroy();

        private:
            /// @brief Reports GLFW errors. Exceptions must not escape this C callback.
            static void fatal_error_callback_(int error, const char* description);
            /// @brief Manually defined retrieval of error name from GLFW error int.
            static auto get_error_name_(int error) -> std::string;
    };
}

#endif
