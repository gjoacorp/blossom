#include <algorithm>
#include <cstring>
#include <memory>
#include <span>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

namespace blossom::system
{
  class vk_renderer
  {
    public:
    private:
      static VkInstance instance_; // NOLINT
      
      // Returns true if all extensions in extensions_view are supported by the implementation, false otherwise.
      // TODO: If not all are extensions supported, this should probably return the ones which AREN'T supported
      static auto are_extensions_supported_(std::span<const char* const> extensions_view) -> bool
      {
        uint32_t property_count = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &property_count, nullptr);
        auto properties = std::make_unique<VkExtensionProperties[]>(property_count); // NOLINT
        vkEnumerateInstanceExtensionProperties(nullptr, &property_count, properties.get());

        std::span<const VkExtensionProperties> properties_view(properties.get(), property_count);
        
        for (const auto& property : properties_view)
        {
          const bool SUPPORTS_PROPERTY = 
            std::ranges::none_of(
              extensions_view, 
              [&property](const auto& extension_property) -> auto { return strcmp(extension_property, property.extensionName) == 0; });

          if (!SUPPORTS_PROPERTY) { return false; }
        }
        return true;
      }

      static auto create_instance_() -> VkResult
      {
        static constexpr VkApplicationInfo APPLICATION_INFO
        {
          .sType               = VK_STRUCTURE_TYPE_APPLICATION_INFO,
          .pNext               = nullptr,
          .pApplicationName    = nullptr, // TODO: Provide a way to obtain this
          .applicationVersion  = 0,       // TODO: Provide a way to obtain this
          .pEngineName         = "blossom", 
          .apiVersion          = 0        // TODO: Provide a proper way of obtaining this 
        };

        uint32_t    glfw_extension_count = 0;
        const auto* glfw_extension_names = glfwGetRequiredInstanceExtensions(&glfw_extension_count);

        if (!are_extensions_supported_(std::span(glfw_extension_names, glfw_extension_count)))
        {
          throw std::runtime_error("ERROR (blossom::vk_renderer): GLFW-required instance extensions are not supported by the implementation.");
        }

        constexpr VkInstanceCreateInfo CREATE_INFO
        {
          .sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
          .pNext            = nullptr, 
          .flags            = static_cast<VkInstanceCreateFlags>(0),
          .pApplicationInfo = &APPLICATION_INFO,
        };

        return vkCreateInstance(&CREATE_INFO, nullptr, &instance_);
      }
  };
}
