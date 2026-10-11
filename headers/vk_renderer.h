#ifndef BLOSSOM_SYSTEM_VK_RENDERER_H
#define BLOSSOM_SYSTEM_VK_RENDERER_H

#include <algorithm>
#include <concepts>
#include <functional>
#include <iostream>
#include <memory>
#include <optional>
#include <span>
#include <vector>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

namespace
{
    struct queue_family_indices
    {
        // Bogus value.
        uint32_t index = std::numeric_limits<uint32_t>::max(); 

        std::optional<uint32_t> graphics  = std::nullopt;
        std::optional<uint32_t> compute   = std::nullopt;
        std::optional<uint32_t> transfer  = std::nullopt;
        std::optional<uint32_t> present   = std::nullopt;

        [[nodiscard]] auto supports_graphics_and_presentation() const -> bool
        {
            return graphics.has_value() && present.has_value();
        }
    };
} // anonymous namespace

namespace blossom::system
{
    template <typename T>
        concept vk_string =
        std::convertible_to<std::remove_cvref_t<T>, const char*> || 
        (std::same_as<std::remove_cvref_t<T>, std::string> && std::is_lvalue_reference_v<T>);

    template <typename R>
        concept vk_string_range =
        std::ranges::input_range<R> && vk_string<std::ranges::range_reference_t<R>>;

    class vk_renderer
    {
        private:
            static inline VkInstance       instance_        = VK_NULL_HANDLE; // NOLINT
            static inline VkPhysicalDevice physical_device_ = VK_NULL_HANDLE; // NOLINT
            static inline VkSurfaceKHR     surface_         = VK_NULL_HANDLE; // NOLINT
            // -------------------------------------------------------------------------------------------------------
            // [action] Can be used to query whether certain extensions are supported by the implementation.
            // TODO: If not all are extensions supported, this should probably return the ones which AREN'T supported  
            // -------------------------------------------------------------------------------------------------------
            // [in]  extension_names -- A range of extension names to query implementation support for.
            // -------------------------------------------------------------------------------------------------------
            // [out] bool            -- true if all extensions are supported by the implementation, false otherwise.
            // -------------------------------------------------------------------------------------------------------
            static auto are_extensions_supported_(vk_string_range auto&& extension_names) -> bool
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
                                extension_names, 
                                [&property](const auto& name) -> auto { return name == property.extensionName; });

                    if (!SUPPORTS_PROPERTY) { return false; }
                }
                return true;
            }
            // -------------------------------------------------------------------------------------------------------
            // [action] Can be used to query whether certain layers are supported by the implementation.
            // -------------------------------------------------------------------------------------------------------
            // [in] layer_names               -- A range of layer names to query implementation support for.
            // -------------------------------------------------------------------------------------------------------
            // [out] std::vector<std::string> -- Contains all layers from layer_names which are unsupported by the
            //                                   implementation. Empty if all are supported.
            // -------------------------------------------------------------------------------------------------------
            static auto get_unsupported_layers_(vk_string_range auto&& layer_names) -> std::vector<std::string>
            {
                std::vector<std::string> unsupported_layers;

                uint32_t property_count = 0;
                vkEnumerateInstanceLayerProperties(&property_count, nullptr);
                auto properties = std::make_unique<VkLayerProperties[]>(property_count); // NOLINT
                vkEnumerateInstanceLayerProperties(&property_count, properties.get());

                std::span<const VkLayerProperties> properties_view(properties.get(), property_count);

                for (std::string_view name : layer_names)
                {
                    // Looking for unsupported layers.
                    auto result = std::ranges::find_if(
                            properties_view,
                            [&name](const auto& property) -> auto { return name == std::string_view(property.layerName); });

                    if (result == properties_view.end())
                    {
                        unsupported_layers.emplace_back(std::to_string(*result->layerName));
                    }
                }
                return unsupported_layers;
            }

            // -------------------------------------------------------------------------------------------------------
            // [action] Enumerates all physical devices, scores them using score_fn, and sets physical_device_ to
            //          the VkPhysicalDevice with the highest score.
            // -------------------------------------------------------------------------------------------------------
            // [in] score_fn -- This is the function used to score (and hence rank) physical devices.
            // -------------------------------------------------------------------------------------------------------
            // [out]         -- void
            // -------------------------------------------------------------------------------------------------------
            // [notes]       -- Notice that, by default, all physical devices are given the same score.
            // -------------------------------------------------------------------------------------------------------
            // TODO: Perhaps use a more sensible default score_fn that prioritises discrete GPUs?
            template<typename T = int>
            static auto select_physical_device_(const std::function<T(VkPhysicalDevice)>& score_fn = [](VkPhysicalDevice) -> T { return T{}; }) -> void
            {
                if (instance_ == VK_NULL_HANDLE)
                {
                    throw std::runtime_error("ERROR (blossom::vk_renderer): A valid Vulkan instance handle is required to call select_physical_device_.");
                }
                uint32_t physical_device_count = 0U;
                vkEnumeratePhysicalDevices(instance_, &physical_device_count, nullptr);

                if (physical_device_count == 0U)
                {
                    throw std::runtime_error("ERROR (blossom::vk_renderer): Failed to find any GPUs with Vulkan support.");
                }
                auto physical_devices = std::make_unique<VkPhysicalDevice[]>(physical_device_count); // NOLINT
                vkEnumeratePhysicalDevices(instance_, &physical_device_count, physical_devices.get());

                std::span<const VkPhysicalDevice> physical_devices_view(physical_devices.get(), physical_device_count);
                const auto HIGHEST_SCORE_IT = std::ranges::max_element(physical_devices_view, std::less{}, score_fn);

                if (HIGHEST_SCORE_IT == physical_devices_view.end())
                {
                    throw std::runtime_error("ERROR (blossom::vk_renderer): A suitable physical device was unable to be selected.");
                }
                physical_device_ = *HIGHEST_SCORE_IT;
            }

            static auto find_queue_families_(VkPhysicalDevice physical_device) -> queue_family_indices
            {
                queue_family_indices indices {};

                if (physical_device == VK_NULL_HANDLE)
                {
                    throw std::runtime_error("ERROR (blossom::vk_renderer): Cannot proceed to find queue families. Invalid physical device.");
                }
                // Querying how many queue families are available.
                uint32_t family_count = 0U;
                vkGetPhysicalDeviceQueueFamilyProperties2(physical_device, &family_count, nullptr);

                // Obtaining the properties of the queue families.
                std::vector<VkQueueFamilyProperties2> family_properties(family_count);
                vkGetPhysicalDeviceQueueFamilyProperties2(physical_device, &family_count, family_properties.data());

                for (uint32_t i = 0U; i < family_count; ++i)
                {
                    const auto& property = family_properties[i];
                    indices.index = i;

                    if ( (property.queueFamilyProperties.queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0 )
                    {
                        indices.graphics = i;
                    }

                    if ( (property.queueFamilyProperties.queueFlags & VK_QUEUE_COMPUTE_BIT) != 0 )
                    {
                        indices.compute = i;
                    }

                    if ( (property.queueFamilyProperties.queueFlags & VK_QUEUE_TRANSFER_BIT) != 0 )
                    {
                        indices.transfer = i;
                    }

                    VkBool32 supports_presentation = VK_FALSE;

                    if (surface_ != VK_NULL_HANDLE)
                    {
                        vkGetPhysicalDeviceSurfaceSupportKHR(
                                physical_device, 
                                indices.index,
                                surface_,
                                &supports_presentation
                                );

                        indices.present = (supports_presentation == VK_TRUE);
                    }
                    else
                    {
                        std::cout 
                            << "WARNING (blossom::vk_renderer): Unable to query queue family for presentation support. No surface was found. Returning VK_FALSE."
                            << "\n";
                    }
                }
                return indices;
            }

        static auto create_surface(GLFWwindow* window) -> void
        {
            // TODO: Check if these pointers are valid.
            glfwCreateWindowSurface(instance_, window, nullptr, &surface_);
        }
        public:
            // -------------------------------------------------------------------------------------------------------
            // [action] Attempts to create a Vulkan instance with the layers and extensions given in layers_names and
            //          extension_names enabled.
            // -------------------------------------------------------------------------------------------------------
            // [in] extension_names -- A range of extension names to use.
            // [in] layer_names     -- A range of layer names to use.
            // -------------------------------------------------------------------------------------------------------
            // [out] VkResult       -- The output from vkCreateInstance.
            // -------------------------------------------------------------------------------------------------------
            static auto create_instance(vk_string_range auto&& extension_names, vk_string_range auto&& layer_names) -> VkResult
            {
                // Populating application information.
                static constexpr VkApplicationInfo APPLICATION_INFO
                {
                    .sType               = VK_STRUCTURE_TYPE_APPLICATION_INFO,
                    .pNext               = nullptr,
                    .pApplicationName    = nullptr, // TODO: Provide a way to obtain this
                    .applicationVersion  = 0,       // TODO: Provide a way to obtain this
                    .pEngineName         = "blossom", 
                    .apiVersion          = 0,       // TODO: Provide a proper way of obtaining this 
                };

                // Checking whether requested extensions are supported.
                if (!are_extensions_supported_(extension_names))
                {
                    throw std::runtime_error("ERROR (blossom::vk_renderer): Some requested instance extensions are not supported by the implementation.");
                }

                // Obtain and print unsupported instance layers (if any).
                const auto UNSUPPORTED_LAYERS = get_unsupported_layers_(layer_names);

                if (!UNSUPPORTED_LAYERS.empty())
                {
                    std::string layers_str = "\n";
                    for (const auto& layer : UNSUPPORTED_LAYERS)
                    {
                        layers_str += layer + "\n";
                    }
                    throw std::runtime_error("ERROR (blossom::vk_renderer): The following requested instance layers are not supported by the implementation:" + layers_str);
                }
                // Copying extension names from the view to perform the std::string -> const char* conversion.
                std::vector<const char*> enabled_extension_names;
                enabled_extension_names.reserve(extension_names.size());
                for (std::string_view name : extension_names)
                {
                    enabled_extension_names.emplace_back(name.data());
                }

                const VkInstanceCreateInfo CREATE_INFO
                {
                    .sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
                    .pNext                   = nullptr, 
                    .flags                   = static_cast<VkInstanceCreateFlags>(0),
                    .pApplicationInfo        = &APPLICATION_INFO,
                    .enabledExtensionCount   = static_cast<uint32_t>(enabled_extension_names.size()),
                    .ppEnabledExtensionNames = enabled_extension_names.data(),
                };

                return vkCreateInstance(&CREATE_INFO, nullptr, &instance_);
            }
    };
}

#endif
