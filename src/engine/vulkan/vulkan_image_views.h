#ifndef VULKAN_IMAGE_VIEWS_H
  #define VULKAN_IMAGE_VIEWS_H

int me::vulkan_api::setup_image_views()
{
  swap_chain_image_views.resize(swap_chain_images.size());
  for (uint32_t i = 0; i < swap_chain_images.size(); i++)
  {
    VkImageViewCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    create_info.image = swap_chain_images[i];
    create_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
    create_info.format = swap_chain_image_format;

    create_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    create_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    create_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    create_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

    create_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    create_info.subresourceRange.baseMipLevel = 0;
    create_info.subresourceRange.levelCount = 1;
    create_info.subresourceRange.baseArrayLayer = 0;
    create_info.subresourceRange.layerCount = 1;

    VkResult result = vkCreateImageView(device, &create_info, nullptr, &swap_chain_image_views[i]);
    if (result != VK_SUCCESS)
    {
        std::cout << LOG_COLOR_RED << "[Vulkan] [ERR]: failed to create image views\n" << LOG_ANSI_RESET;
      return ME_ERR;
    }
  }
  return ME_FINE;
}

#endif
