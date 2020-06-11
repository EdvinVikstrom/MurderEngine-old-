#ifndef VULKAN_GRAPHICS_PIPELINE_H
  #define VULKAN_GRAPHICS_PIPELINE_H

int me::vulkan_api::init_surface()
{
  /* xlib surface info */
  VkXlibSurfaceCreateInfoKHR create_info = {};
  create_info.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
  create_info.pNext = nullptr;
  create_info.window = glfwGetX11Window(window);
  VkResult result = vkCreateXlibSurfaceKHR(instance, &create_info, nullptr, &surface);

  /* graphics/present queue family index */
  VkBool32* supports_present = new VkBool32[queue_family_count];
  for (uint32_t i = 0; i < queue_family_count; i++)
    vkGetPhysicalDeviceSurfaceSupportKHR(physical_device, i, surface, &supports_present[i]);
  graphics_queue_family_index = UINT32_MAX;
  present_queue_family_index = UINT32_MAX;
  for (uint32_t i = 0; i < queue_family_count; i++)
  {
    if ((queue_properties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0)
    {
      if (graphics_queue_family_index == UINT32_MAX)
        graphics_queue_family_index = i;
      if (supports_present[i] == VK_TRUE)
      {
        graphics_queue_family_index = i;
        present_queue_family_index = i;
        break;
      }
    }
  }
  if (present_queue_family_index == UINT32_MAX)
  {
    for (uint32_t i = 0; i < queue_family_count; i++)
    {
      if (supports_present[i] == VK_TRUE)
        present_queue_family_index = i;
    }
  }
  delete[] supports_present;
  return ME_FINE;
}

int me::vulkan_api::init_swapchain()
{
  /* getting surface formats */
  uint32_t format_count;
  VkResult result = vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device, surface, &format_count, nullptr);
  VkSurfaceFormatKHR* surface_formats = new VkSurfaceFormatKHR[format_count];
  result = vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device, surface, &format_count, surface_formats);

  /* checking surface formats */
  if (format_count == 1 && surface_formats[0].format == VK_FORMAT_UNDEFINED)
    format = VK_FORMAT_B8G8R8A8_UNORM;
  else
    format = surface_formats[0].format;
  delete[] surface_formats;

  /* surface capabilities */
  VkSurfaceCapabilitiesKHR surface_capabilities;
  result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physical_device, surface, &surface_capabilities);

  /* present modes */
  uint32_t present_mode_count;
  result = vkGetPhysicalDeviceSurfacePresentModesKHR(physical_device, surface, &present_mode_count, nullptr);
  VkPresentModeKHR* present_modes = new VkPresentModeKHR[present_mode_count];
  result = vkGetPhysicalDeviceSurfacePresentModesKHR(physical_device, surface, &present_mode_count, present_modes);

  /* swapchain extent */
  if (surface_capabilities.currentExtent.width = 0xFFFFFFFF)
  {
    swapchain_extent.width = width;
    swapchain_extent.height = height;
    /* width */
    if (swapchain_extent.width < surface_capabilities.minImageExtent.width)
      swapchain_extent.width = surface_capabilities.minImageExtent.width;
    else if (swapchain_extent.width > surface_capabilities.maxImageExtent.width)
      swapchain_extent.width = surface_capabilities.maxImageExtent.width;

    /* height */
    if (swapchain_extent.height < surface_capabilities.minImageExtent.height)
      swapchain_extent.height = surface_capabilities.minImageExtent.height;
    else if (swapchain_extent.height > surface_capabilities.maxImageExtent.height)
      swapchain_extent.height = surface_capabilities.maxImageExtent.height;
  }else
    swapchain_extent = surface_capabilities.currentExtent;

  /* present mode */
  VkPresentModeKHR swapchain_present_mode = VK_PRESENT_MODE_FIFO_KHR;

  uint32_t desired_number_of_swapchain_images = surface_capabilities.minImageCount;
  VkSurfaceTransformFlagBitsKHR pre_transform;
  if (surface_capabilities.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR)
    pre_transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
  else
    pre_transform = surface_capabilities.currentTransform;

  /* composite */
  VkCompositeAlphaFlagBitsKHR composite_alpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
  VkCompositeAlphaFlagBitsKHR composite_alpha_flags[4] = {
    VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
    VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
    VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
    VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR
  };
  for (uint32_t i = 0; i < 4; i++)
  {
    if (surface_capabilities.supportedCompositeAlpha & composite_alpha_flags[i])
    {
      composite_alpha = composite_alpha_flags[i];
      break;
    }
  }

  /* swapchain info */
  VkSwapchainCreateInfoKHR swapchain_info = {};
  swapchain_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  swapchain_info.pNext = nullptr;
  swapchain_info.surface = surface;
  swapchain_info.minImageCount = desired_number_of_swapchain_images;
  swapchain_info.imageFormat = format;
  swapchain_info.imageExtent.width = swapchain_extent.width;
  swapchain_info.imageExtent.height = swapchain_extent.height;
  swapchain_info.preTransform = pre_transform;
  swapchain_info.compositeAlpha = composite_alpha;
  swapchain_info.imageArrayLayers = 1;
  swapchain_info.presentMode = swapchain_present_mode;
  swapchain_info.oldSwapchain = VK_NULL_HANDLE;
  swapchain_info.clipped = true;
  swapchain_info.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
  swapchain_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
  swapchain_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
  swapchain_info.queueFamilyIndexCount = 0;
  swapchain_info.pQueueFamilyIndices = nullptr;
  uint32_t queue_family_indices[2] = {graphics_queue_family_index, present_queue_family_index};
  if (graphics_queue_family_index != present_queue_family_index)
  {
    swapchain_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
    swapchain_info.queueFamilyIndexCount = 2;
    swapchain_info.pQueueFamilyIndices = queue_family_indices;
  }
  result = vkCreateSwapchainKHR(device, &swapchain_info, nullptr, &swapchain);

  /* swapchain images */
  result = vkGetSwapchainImagesKHR(device, swapchain, &swapchain_image_count, nullptr);
  VkImage* swapchain_images = new VkImage[swapchain_image_count];
  result = vkGetSwapchainImagesKHR(device, swapchain, &swapchain_image_count, swapchain_images);
  buffers.resize(swapchain_image_count);
  // TODO: for (uint32_t i = 0; i < swapchain_image_count; i++)
    // TODO: buffers[i].image = swapchain_images[i];
  delete[] swapchain_images;

  /* image view */
  for (uint32_t i = 0; i < swapchain_image_count; i++)
  {
    VkImageViewCreateInfo image_view_info = {};
    image_view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    image_view_info.pNext = nullptr;
    image_view_info.flags = 0;
    // TODO: image_view_info.image = buffers[i].image;
    image_view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
    image_view_info.format = format;
    image_view_info.components.r = VK_COMPONENT_SWIZZLE_R;
    image_view_info.components.g = VK_COMPONENT_SWIZZLE_G;
    image_view_info.components.b = VK_COMPONENT_SWIZZLE_B;
    image_view_info.components.a = VK_COMPONENT_SWIZZLE_A;
    image_view_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    image_view_info.subresourceRange.baseMipLevel = 0;
    image_view_info.subresourceRange.levelCount = 1;
    image_view_info.subresourceRange.baseArrayLayer = 0;
    image_view_info.subresourceRange.layerCount = 1;
    // TODO: result = vkCreateImageView(device, &image_view_info, nullptr, &buffers[i].view);
  }
  return ME_FINE;
}

int me::vulkan_api::init_command_buffers()
{
  /* create command pool */
  VkCommandPoolCreateInfo pool_info = {};
  pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  pool_info.pNext = nullptr;
  pool_info.queueFamilyIndex = graphics_queue_family_index;
  pool_info.flags = 0;
  VkResult result = vkCreateCommandPool(device, &pool_info, nullptr, &command_pool);
  if (result != VK_SUCCESS)
  {
    printf("[Vulkan] [ERR]: [%s] Failed to create command pool\n", vkErrStr(result));
    return ME_ERR;
  }

  /* create command buffer */
  VkCommandBufferAllocateInfo alloc_info = {};
  alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  alloc_info.pNext = nullptr;
  alloc_info.commandPool = command_pool;
  alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  alloc_info.commandBufferCount = 1;
  result = vkAllocateCommandBuffers(device, &alloc_info, &command_buffer);
  if (result != VK_SUCCESS)
  {
    printf("[Vulkan] [ERR]: [%s] Failed to create command buffer\n", vkErrStr(result));
    return ME_ERR;
  }
  return ME_FINE;
}

#endif