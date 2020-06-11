#ifndef VULKAN_DEVICE_H
  #define VULKAN_DEVICE_H

int me::vulkan_api::init_enumerate_device()
{
  /* getting the GPUs */
  uint32_t gpu_count;
  VkResult result = vkEnumeratePhysicalDevices(instance, &gpu_count, nullptr);
  gpus.resize(gpu_count);
  result = vkEnumeratePhysicalDevices(instance, &gpu_count, gpus.data());
  // TODO: find the best GPU
  physical_device = gpus[0];
  return ME_FINE;
}

int me::vulkan_api::init_queue_family_index(VkDeviceQueueCreateInfo &queue_info)
{
  /* device queue family properties */
  uint32_t queue_family_count;
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, nullptr);
  queue_properties.resize(queue_family_count);
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, queue_properties.data());

  /* finding a property with VK_QUEUE_GRAPHICS_BIT */
  for (uint32_t i = 0; i < queue_family_count; i++)
  {
    if (queue_properties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
    {
      queue_info.queueFamilyIndex = i;
      break;
    }
  }
  return ME_FINE;
}

int me::vulkan_api::init_device()
{
  /* queue info */
  VkDeviceQueueCreateInfo queue_info = {};
  init_queue_family_index(queue_info);
  float queue_priorities[1] = { 0.0F };
  queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  queue_info.pNext = nullptr;
  queue_info.queueCount = 1;
  queue_info.pQueuePriorities = queue_priorities;

  /* device info */
  VkDeviceCreateInfo device_info = {};
  device_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  device_info.pNext = nullptr;
  device_info.queueCreateInfoCount = 1;
  device_info.pQueueCreateInfos = &queue_info;
  device_info.enabledExtensionCount = 0;
  device_info.ppEnabledExtensionNames = nullptr;
  device_info.enabledLayerCount = 0;
  device_info.ppEnabledLayerNames = nullptr;
  device_info.pEnabledFeatures = nullptr;
  VkResult result = vkCreateDevice(physical_device, &device_info, nullptr, &device);
  if (result != VK_SUCCESS)
  {
    printf("[Vulkan] [ERR]: { %s } Failed to create device\n", vkErrStr(result));
    return ME_ERR;
  }
  return ME_FINE;
}

#endif