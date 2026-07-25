#ifndef BLOSSOM_SYSTEM_VK_RENDERER_H
#define BLOSSOM_SYSTEM_VK_RENDERER_H

#include <algorithm>
#include <concepts>
#include <memory>
#include <span>
#include <vector>
#include <vulkan/vulkan.h>

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

            static auto select_physical_device_() -> void
            {
                if (instance_ == VK_NULL_HANDLE)
                {
                    throw std::runtime_error("ERROR (blossom::vk_renderer): A valid Vulkan instance handle is required to call select_physical_device_.");
                }
                uint32_t physical_device_count = 0U;
                vkEnumeratePhysicalDevices(instance_, &physical_device_count, nullptr);
                auto physical_devices = std::make_unique<VkPhysicalDevice[]>(physical_device_count); // NOLINT
                vkEnumeratePhysicalDevices(instance_, &physical_device_count, physical_devices.get());
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
                static constexpr VkApplicationInfo APPLICATION_INFO
                {
                    .sType               = VK_STRUCTURE_TYPE_APPLICATION_INFO,
                        .pNext               = nullptr,
                        .pApplicationName    = nullptr, // TODO: Provide a way to obtain this
                        .applicationVersion  = 0,       // TODO: Provide a way to obtain this
                        .pEngineName         = "blossom", 
                        .apiVersion          = 0        // TODO: Provide a proper way of obtaining this 
                };

                if (!are_extensions_supported_(extension_names))
                {
                    throw std::runtime_error("ERROR (blossom::vk_renderer): Some requested instance extensions are not supported by the implementation.");
                }

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
                    .ppEnabledExtensionNames = enabled_extension_names.data()
                };

                return vkCreateInstance(&CREATE_INFO, nullptr, &instance_);
            }
    };
}

#endif
