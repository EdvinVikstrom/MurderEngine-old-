#ifndef VULKAN_DEVICE_H
  #define VULKAN_DEVICE_H

int me::vulkan_api::setup_physical_device()
{
  uint32_t device_count = 0;
  vkEnumeratePhysicalDevices(instance, &device_count, nullptr);
  if (device_count == 0)
  {
    std::cout << LOG_COLOR_RED << "[Vulkan] [ERR]: no GPUs with vulkan support found\n" << LOG_ANSI_RESET;
    return ME_ERR;
  }
  std::vector<VkPhysicalDevice> devices(device_count);
  vkEnumeratePhysicalDevices(instance, &device_count, devices.data());
  // TODO: if multiples GPUs. do what?
  for (const auto &device : devices)
  {
    if (is_device_suitable(device))
    {
      physical_device = device;
      break;
    }
  }
  if (physical_device == VK_NULL_HANDLE)
  {
    std::cout << LOG_COLOR_RED << "[Vulkan] [ERR]: no suitable GPU found\n" << LOG_ANSI_RESET;
    return ME_ERR;
  }
  return ME_FINE;
}

int me::vulkan_api::setup_logical_device()
{
  me::vulkan_api::QueueFamilyIndices indices = find_queue_families(physical_device);
  std::vector<VkDeviceQueueCreateInfo> queue_create_infos;
  std::set<uint32_t> unique_queue_families = {indices.graphics_family.value(), indices.present_family.value()};

  float queue_priority = 1.0F;
  for (uint32_t queue_family : unique_queue_families)
  {
    VkDeviceQueueCreateInfo queue_create_info = {};
    queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_create_info.queueFamilyIndex = queue_family;
    queue_create_info.queueCount = 1;
    queue_create_info.pQueuePriorities = &queue_priority;
    queue_create_infos.push_back(queue_create_info);
  }
  VkPhysicalDeviceFeatures device_features = {};
  VkDeviceCreateInfo create_info = {};
  create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  create_info.queueCreateInfoCount = static_cast<uint32_t>(queue_create_infos.size());
  create_info.pQueueCreateInfos = queue_create_infos.data();
  create_info.pEnabledFeatures = &device_features;
  create_info.enabledExtensionCount = static_cast<uint32_t>(device_extensions.size());
  create_info.ppEnabledExtensionNames = device_extensions.data();
  if (enable_validation_layers)
  {
    create_info.enabledLayerCount = static_cast<uint32_t>(validation_layers.size());
    create_info.ppEnabledLayerNames = validation_layers.data();
  }else
    create_info.enabledLayerCount = 0;
  VkResult result = vkCreateDevice(physical_device, &create_info, nullptr, &device);
  if (result != VK_SUCCESS)
  {
    std::cout << LOG_COLOR_RED << "[Vulkan] [ERR]: failed to create logical device\n" << LOG_ANSI_RESET;
    return ME_ERR;
  }
  vkGetDeviceQueue(device, indices.graphics_family.value(), 0, &graphics_queue);
  vkGetDeviceQueue(device, indices.present_family.value(), 0, &present_queue);
  return ME_FINE;
}

#endif
