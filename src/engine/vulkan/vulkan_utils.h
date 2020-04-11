#ifndef VULKAN_UTILS_H
  #define VULKAN_UTILS_H

inline static const char* getVkStr(int code)
{
  switch(code)
  {
    case 1:
      return "VK_NOT_READY"; break;
    case 2:
      return "VK_TIMEOUT"; break;
    case 3:
      return "VK_EVENT_SET"; break;
    case 4:
      return "VK_EVENT_RESET"; break;
    case 5:
      return "VK_INCOMPLETE"; break;
    case -1:
      return "VK_ERROR_OUT_OF_HOST_MEMORY"; break;
    case -2:
      return "VK_ERROR_OUT_OF_DEVICE_MEMORY"; break;
    case -3:
      return "VK_ERROR_INITIALIZATION_FAILED"; break;
    case -4:
      return "VK_ERROR_DEVICE_LOST"; break;
    case -5:
      return "VK_ERROR_MEMORY_MAP_FAILED"; break;
    case -6:
      return "VK_ERROR_LAYER_NOT_PRESENT"; break;
    case -7:
      return "VK_ERROR_EXTENSION_NOT_PRESENT"; break;
    case -8:
      return "VK_ERROR_FEATURE_NOT_PRESENT"; break;
    case -9:
      return "VK_ERROR_INCOMPATIBLE_DRIVER"; break;
    case -10:
      return "VK_ERROR_TOO_MANY_OBJECTS"; break;
    case -11:
      return "VK_ERROR_FORMAT_NOT_SUPPORTED"; break;
    case -12:
      return "VK_ERROR_FRAGMENTED_POOL"; break;
    case -13:
      return "VK_ERROR_UNKNOWN"; break;
  }
  return "UNKNOWN";
}

me::vulkan_api::QueueFamilyIndices me::vulkan_api::find_queue_families(VkPhysicalDevice device)
{
  QueueFamilyIndices indices;
  uint32_t queue_family_count = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, nullptr);
  std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, queue_families.data());
  for (unsigned int i = 0; i < queue_families.size(); i++)
  {
    if (queue_families.at(i).queueFlags & VK_QUEUE_GRAPHICS_BIT)
      indices.graphics_family = i;

    VkBool32 present_supported = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &present_supported);
    if (present_supported)
      indices.present_family = i;

    if (indices.is_complete())
      break;
  }
  return indices;
}

bool me::vulkan_api::is_device_suitable(VkPhysicalDevice device)
{
  me::vulkan_api::QueueFamilyIndices indices = find_queue_families(device);
  bool extensions_supported = device_extension_supported(device);
  bool swap_chain_adequate = false;
  if (extensions_supported)
  {
    SwapChainSupportDetails swap_chain_support = query_swap_chain_support(device);
    swap_chain_adequate = !swap_chain_support.formats.empty() && !swap_chain_support.present_modes.empty();
  }

  return indices.is_complete() && extensions_supported && swap_chain_adequate;
}

bool me::vulkan_api::validation_layer_supported(const std::vector<const char*> &validation_layers)
{
  uint32_t layer_count;
  vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

  std::vector<VkLayerProperties> available_layers(layer_count);
  vkEnumerateInstanceLayerProperties(&layer_count, available_layers.data());
  #ifdef ME_DEBUG
    std::cout << LOG_COLOR_MAGENTA << "[Vulkan] available validation layers:\n" << LOG_ANSI_RESET;
    for (const auto &layer_properties : available_layers)
      std::cout << LOG_COLOR_MAGENTA << ">  " << layer_properties.layerName << "\n" << LOG_ANSI_RESET;
  #endif
  for (const char* layer : validation_layers)
  {
    bool found = false;
    for (const auto &layer_properties : available_layers)
    {
      if (strcmp(layer, layer_properties.layerName) == 0)
      {
        found = true;
        break;
      }
    }
    #ifdef ME_DEBUG
      std::cout << "-- [" << layer << "] is " << (found ? "\e[32msupported\e[0m" : "\e[31mnot supported\e[0m")  << "\n";
    #endif
    if (!found)
      return false;
  }
  return true;
}

bool me::vulkan_api::device_extension_supported(VkPhysicalDevice device)
{
  uint32_t extension_count;
  vkEnumerateDeviceExtensionProperties(device, nullptr, &extension_count, nullptr);
  std::vector<VkExtensionProperties> available_extensions(extension_count);
  vkEnumerateDeviceExtensionProperties(device, nullptr, &extension_count, available_extensions.data());
  std::set<std::string> required_extensions(device_extensions.begin(), device_extensions.end());
  for (const auto &extension : available_extensions) /* if extension is supported, remove it from required_extensions */
    required_extensions.erase(extension.extensionName);
  return required_extensions.empty();
}

uint32_t me::vulkan_api::find_memory_type(uint32_t type_filter, VkMemoryPropertyFlags properties)
{
  VkPhysicalDeviceMemoryProperties mem_properties;
  vkGetPhysicalDeviceMemoryProperties(physical_device, &mem_properties);
  for (uint32_t i = 0; i < mem_properties.memoryTypeCount; i++)
  {
    if ((type_filter & (1 << i)) && (mem_properties.memoryTypes[i].propertyFlags & properties) == properties)
      return i;
  }
  std::cout << LOG_COLOR_RED << "[Vulkan] [ERR]: failed to find memory type\n" << LOG_ANSI_RESET;
  return 0;
}

#endif
