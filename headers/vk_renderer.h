#ifndef BLOSSOM_SYSTEM_VK_RENDERER_H
#define BLOSSOM_SYSTEM_VK_RENDERER_H

#include <algorithm>
#include <cstring>
#include <concepts>
#include <memory>
#include <span>
#include <vector>
#include <vulkan/vulkan.h>

namespace blossom::system
{
    template <typename T>
        concept string_viewable_range = 
        std::ranges::input_range<T>                                               // Is it a range?
        && 
        std::convertible_to<std::ranges::range_reference_t<T>, std::string_view>; // Can its elements be converted to std::string_view?

    class vk_renderer
    {
        public:
            static inline VkInstance instance_ = VK_NULL_HANDLE; // NOLINT
            // -------------------------------------------------------------------------------------------------------
            // Returns true if all extensions are supported by the implementation, false otherwise. 
            // TODO: If not all are extensions supported, this should probably return the ones which AREN'T supported  
            // -------------------------------------------------------------------------------------------------------
            // [in] extensions -- A span of constant string views into strings containing extension names.
            // -------------------------------------------------------------------------------------------------------
            static auto are_extensions_supported_(string_viewable_range auto&& extensions) -> bool
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
                                extensions, 
                                [&property](const auto& extension) -> auto { return extension == property.extensionName; });

                    if (!SUPPORTS_PROPERTY) { return false; }
                }
                return true;
            }

            // Checks the layers in requested_layer_names_view against the layers supported by the implementation.
            // Returns a vector of unsupported layer names, which is empty if all of the requested layers are supported.
            static auto get_unsupported_layers_(string_viewable_range auto&& requested_layer_names) -> std::vector<std::string>
            {
                std::vector<std::string> unsupported_layers;

                // Querying to find which layers are supported by the implementation.
                uint32_t supported_layer_count = 0;
                vkEnumerateInstanceLayerProperties(&supported_layer_count, nullptr);
                auto supported_layer_properties = std::make_unique<VkLayerProperties[]>(supported_layer_count); // NOLINT
                vkEnumerateInstanceLayerProperties(&supported_layer_count, supported_layer_properties.get());

                std::span<const VkLayerProperties> supported_layer_properties_view(supported_layer_properties.get(), supported_layer_count);

                for (std::string_view name : requested_layer_names)
                {
                    // Looking for unsupported layers.
                    auto result = std::ranges::find_if_not(
                            supported_layer_properties_view,
                            [&name](const auto& supported_layer_property) -> auto { return name, supported_layer_property.layerName; });

                    if (result != supported_layer_properties_view.end())
                    {
                        unsupported_layers.emplace_back(std::to_string(*result->layerName));
                    }
                }
                return unsupported_layers;
            }

            static auto create_instance_(string_viewable_range auto&& extensions_view, string_viewable_range auto&& layers_view) -> VkResult
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

                if (!are_extensions_supported_(extensions_view))
                {
                    throw std::runtime_error("ERROR (blossom::vk_renderer): Some requested instance extensions are not supported by the implementation.");
                }

                const auto unsupported_layers = get_unsupported_layers_(layers_view);
                if (!unsupported_layers.empty())
                {
                    std::string layers_str = "\n";
                    for (const auto& layer : unsupported_layers)
                    {
                        layers_str += layer + "\n";
                    }
                    throw std::runtime_error("ERROR (blossom::vk_renderer): The following requested instance layers are not supported by the implementation:" + layers_str);
                }

                // Copying extension names from the view to perform the std::string -> const char* const* conversion.
                std::vector<const char*> extension_names;
                extension_names.reserve(extensions_view.size());
                for (std::string_view view : extensions_view)
                {
                    extension_names.emplace_back(view.data());
                }

                const VkInstanceCreateInfo CREATE_INFO
                {
                    .sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
                    .pNext                   = nullptr, 
                    .flags                   = static_cast<VkInstanceCreateFlags>(0),
                    .pApplicationInfo        = &APPLICATION_INFO,
                    .enabledExtensionCount   = static_cast<uint32_t>(extensions_view.size()),
                    .ppEnabledExtensionNames = extension_names.data()
                };

                return vkCreateInstance(&CREATE_INFO, nullptr, &instance_);
            }
    };
}

#endif
