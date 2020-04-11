#ifndef VULKAN_DEBUG_H
  #define VULKAN_DEBUG_H

static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
{
  #ifdef ME_DEBUG
    std::cout << LOG_COLOR_RED << "[Vulkan] [ERR]: " << pCallbackData->pMessage << "\n" << LOG_ANSI_RESET;
  #endif
  if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
    std::cout << LOG_COLOR_RED << "[Vulkan] [ERR]: " << pCallbackData->pMessage << "\n" << LOG_ANSI_RESET;
  return VK_FALSE;
}

static VkResult create_DUMExt(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* create_info, const VkAllocationCallbacks* allocator, VkDebugUtilsMessengerEXT* debug_messenger)
{
  auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
  if (func != nullptr)
    return func(instance, create_info, allocator, debug_messenger);
  else
    return VK_ERROR_EXTENSION_NOT_PRESENT;
}

static void destroy_DUMExt(VkInstance instance, VkDebugUtilsMessengerEXT debug_messenger, const VkAllocationCallbacks* allocator)
{
  auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
  if (func != nullptr)
    func(instance, debug_messenger, allocator);
}

static void populate_debug_messenger_create_info(VkDebugUtilsMessengerCreateInfoEXT &create_info)
{
  create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
  create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
  create_info.pfnUserCallback = debug_callback;
  create_info.pUserData = nullptr;
}

int me::vulkan_api::setup_debug_messenger()
{
  if (!enable_validation_layers)
    return ME_FINE;
  VkDebugUtilsMessengerCreateInfoEXT create_info;
  populate_debug_messenger_create_info(create_info);
  VkResult result = create_DUMExt(instance, &create_info, nullptr, &debug_messenger);
  if (result != VK_SUCCESS)
  {
    std::cout << LOG_COLOR_RED << "[Vulkan] [ERR] [" << getVkStr(result) << "]: failed to setup debug messenger\n" << LOG_ANSI_RESET;
    return ME_ERR;
  }
  return ME_FINE;
}

#endif
