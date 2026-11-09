#include "../headers/vk_renderer.h"
#include "../headers/utils/vk.h"
#include "../headers/window.h"
#include <span>

auto main() -> int 
{
  blossom::utils::print_available_instance_extension_names();

  blossom::window window(1920, 1080, "");

  uint32_t    glfw_extension_count = 0;
  const auto* glfw_extension_names = glfwGetRequiredInstanceExtensions(&glfw_extension_count);


  const auto EXTENSIONS_VIEW = std::span(glfw_extension_names, glfw_extension_count);

  std::array<const std::string, 1> layers {"VK_LAYER_KHRONOS_validation" };
  blossom::system::vk_renderer::create_instance(EXTENSIONS_VIEW, layers);
  blossom::system::vk_renderer::create_surface(window.window_ptr);
  blossom::system::vk_renderer::create_device();
}
