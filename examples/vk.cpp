#include "../headers/vk_renderer.h"
#include "../headers/utils/vk.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <span>

auto main() -> int 
{
  blossom::utils::print_available_instance_extension_names();

  uint32_t    glfw_extension_count = 0;
  const auto* glfw_extension_names = glfwGetRequiredInstanceExtensions(&glfw_extension_count);

  const auto EXTENSIONS_VIEW = std::span(glfw_extension_names, glfw_extension_count);

  std::array<const std::string, 1> layers {"VK_LAYER_KHRONOS_validation" };
  blossom::system::vk_renderer::create_instance_(EXTENSIONS_VIEW, std::span(layers));
}
