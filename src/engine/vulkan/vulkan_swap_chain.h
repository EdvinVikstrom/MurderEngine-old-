#ifndef VULKAN_SWAP_CHAIN_H
  #define VULKAN_SWAP_CHAIN_H

me::vulkan_api::SwapChainSupportDetails me::vulkan_api::query_swap_chain_support(VkPhysicalDevice device)
{
  SwapChainSupportDetails details;
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

  /* surface formats */
  uint32_t format_count;
  vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &format_count, nullptr);
  if (format_count != 0)
  {
    details.formats.resize(format_count);
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &format_count, details.formats.data());
  }

  /* surface present modes */
  uint32_t present_mode_count;
  vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &present_mode_count, nullptr);
  if (present_mode_count != 0)
  {
    details.present_modes.resize(present_mode_count);
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &present_mode_count, details.present_modes.data());
  }
  return details;
}

VkSurfaceFormatKHR me::vulkan_api::choose_swap_surface_format(const std::vector<VkSurfaceFormatKHR> &available_formats)
{
  for (const auto &available_format : available_formats)
  {
    if (available_format.format == VK_FORMAT_B8G8R8A8_SRGB && available_format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
      return available_format;
  }
  return available_formats[0];
}

VkPresentModeKHR me::vulkan_api::choose_swap_present_mode(const std::vector<VkPresentModeKHR> &available_present_modes)
{
  for (const auto &available_present_mode : available_present_modes)
  {
    if (available_present_mode == VK_PRESENT_MODE_MAILBOX_KHR)
      return available_present_mode;
  }
  return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D me::vulkan_api::choose_swap_extent(GLFWwindow* window, const VkSurfaceCapabilitiesKHR &capabilities)
{
  if (capabilities.currentExtent.width != UINT32_MAX)
    return capabilities.currentExtent;
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);

  VkExtent2D actual_extent = {static_cast<uint32_t>(width), static_cast<uint32_t>(height)};
  actual_extent.width = me::maths::max(capabilities.minImageExtent.width, me::maths::min(capabilities.maxImageExtent.width, actual_extent.width));
  actual_extent.height = me::maths::max(capabilities.minImageExtent.height, me::maths::min(capabilities.maxImageExtent.height, actual_extent.height));
  return actual_extent;
}

int me::vulkan_api::setup_swap_chain(GLFWwindow* window)
{
  SwapChainSupportDetails swap_chain_support = query_swap_chain_support(physical_device);
  VkSurfaceFormatKHR surface_format = choose_swap_surface_format(swap_chain_support.formats);
  VkPresentModeKHR present_mode = choose_swap_present_mode(swap_chain_support.present_modes);
  VkExtent2D extent = choose_swap_extent(window, swap_chain_support.capabilities);

  uint32_t image_count = swap_chain_support.capabilities.minImageCount + 1;
  if (swap_chain_support.capabilities.maxImageCount > 0 && image_count > swap_chain_support.capabilities.maxImageCount)
    image_count = swap_chain_support.capabilities.maxImageCount;

  VkSwapchainCreateInfoKHR create_info = {};
  create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  create_info.surface = surface;
  create_info.minImageCount = image_count;
  create_info.imageFormat = surface_format.format;
  create_info.imageColorSpace = surface_format.colorSpace;
  create_info.imageExtent = extent;
  create_info.imageArrayLayers = 1;
  create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

  QueueFamilyIndices indices = find_queue_families(physical_device);
  uint32_t queue_family_indices[] = {indices.graphics_family.value(), indices.present_family.value()};
  if (indices.graphics_family != indices.present_family)
  {
    create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
    create_info.queueFamilyIndexCount = 2;
    create_info.pQueueFamilyIndices = queue_family_indices;
  }else
  {
    create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    create_info.queueFamilyIndexCount = 0;
    create_info.pQueueFamilyIndices = nullptr;
  }
  create_info.preTransform = swap_chain_support.capabilities.currentTransform;
  create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
  create_info.presentMode = present_mode;
  create_info.clipped = VK_TRUE;
  create_info.oldSwapchain = VK_NULL_HANDLE;
  VkResult result = vkCreateSwapchainKHR(device, &create_info, nullptr, &swap_chain);
  if (result != VK_SUCCESS)
  {
    std::cout << LOG_COLOR_RED << "[Vulkan] [ERR]: failed to create swap chain\n" << LOG_ANSI_RESET;
    return ME_ERR;
  }
  vkGetSwapchainImagesKHR(device, swap_chain, &image_count, nullptr);
  swap_chain_images.resize(image_count);
  vkGetSwapchainImagesKHR(device, swap_chain, &image_count, swap_chain_images.data());

  swap_chain_image_format = surface_format.format;
  swap_chain_extent = extent;
  return ME_FINE;
}

#endif
