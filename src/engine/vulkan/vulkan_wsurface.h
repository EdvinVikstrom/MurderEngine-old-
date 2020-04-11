#ifndef VULKAN_WSURFACE_H
  #define VULKAN_WSURFACE_H

int me::vulkan_api::setup_window_surface(GLFWwindow *window)
{
  // TODO: OS
  VkXlibSurfaceCreateInfoKHR create_info = {};
  create_info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
  create_info.window = glfwGetX11Window(window);
  VkResult result = vkCreateXlibSurfaceKHR(instance, &create_info, nullptr, &surface);
  if (result != VK_SUCCESS)
  {
    std::cout << LOG_COLOR_RED << "[Vulkan] [ERR]: failed to create window surface\n" << LOG_ANSI_RESET;
    return ME_ERR;
  }
  result = glfwCreateWindowSurface(instance, window, nullptr, &surface);
  if (result != VK_SUCCESS)
  {
    std::cout << LOG_COLOR_RED << "[GLFW] [ERR]: failed to create window surface\n" << LOG_ANSI_RESET;
    return ME_ERR;
  }
  return ME_FINE;
}

#endif
