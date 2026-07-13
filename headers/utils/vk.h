#ifndef BLOSSOM_UTILS_VK_H
#define BLOSSOM_UTILS_VK_H

#include <vulkan/vulkan.h>
#include <array>
#include <iostream>

namespace blossom::utils
{
  // Queries for and prints all available Vulkan instance extension names.
  auto print_available_instance_extension_names() -> void
  {
    uint32_t count = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr);
    std::array<VkExtensionProperties, VK_MAX_EXTENSION_NAME_SIZE> properties;
    vkEnumerateInstanceExtensionProperties(nullptr, &count, properties.data());

    std::cout << "AVAILABLE INSTANCE EXTENSIONS:\n";
    for (uint32_t i = 0; i < count; ++i)
    {
      std::cout << properties[i].extensionName << "\n";
    }
  }
}

#endif 
