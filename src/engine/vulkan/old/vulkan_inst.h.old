#ifndef VULKAN_INST_H
  #define VULKAN_INST_H

int me::vulkan_api::init_instance()
{
  if (enable_validation_layers && !validation_layer_supported(validation_layers))
  {
    std::cout << LOG_COLOR_RED << "[Vulkan] [ERR]: validation layer not supported\n" << LOG_ANSI_RESET;
    return ME_ERR;
  }
  VkApplicationInfo app_info = {};
  app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info.pApplicationName = "Murder Engine";
  app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  app_info.pEngineName = "Murder Engine";
  app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  app_info.apiVersion = VK_API_VERSION_1_2;

  VkInstanceCreateInfo create_info = {};
  create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  create_info.pApplicationInfo = &app_info;
  VkDebugUtilsMessengerCreateInfoEXT debug_create_info = {};
  if (enable_validation_layers)
  {
    create_info.enabledLayerCount = static_cast<uint32_t>(validation_layers.size());
    create_info.ppEnabledLayerNames = validation_layers.data();

    populate_debug_messenger_create_info(debug_create_info);
    create_info.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debug_create_info;
  }else
  {
    create_info.enabledLayerCount = 0;
    create_info.pNext = nullptr;
  }

  std::vector<const char*> extensions = required_extensions();
  create_info.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
  create_info.ppEnabledExtensionNames = extensions.data();

  create_info.enabledLayerCount = 0;

  VkResult result = vkCreateInstance(&create_info, nullptr, &instance);
  if (result != VK_SUCCESS)
  {
    std::cout << LOG_COLOR_RED << "[Vulkan] [ERR]: failed to create instance\n" << LOG_ANSI_RESET;
    return ME_ERR;
  }

  uint32_t ext_count = 0;
  vkEnumerateInstanceExtensionProperties(nullptr, &ext_count, nullptr);
  std::vector<VkExtensionProperties> extension_properties(ext_count);
  vkEnumerateInstanceExtensionProperties(nullptr, &ext_count, extension_properties.data());

  std::cout << LOG_COLOR_MAGENTA << "[Vulkan]: available extensions:\n" << LOG_ANSI_RESET;
  for (const auto &extension : extension_properties)
    std::cout << LOG_COLOR_MAGENTA << ">  " << extension.extensionName << "\n" << LOG_ANSI_RESET;
  return ME_FINE;
}

#endif
