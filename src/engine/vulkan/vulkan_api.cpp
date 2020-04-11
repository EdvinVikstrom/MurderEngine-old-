#include "vulkan_api.h"

/* utilities */
#include "../kernel/kernel.h"
#include "../kernel/log.h"
#include "../math/maths.h"
#include <vector>
#include <set>
#include <cstring>
#include <cstdint>
#include <iostream>

#ifdef ME_DEBUG
  const bool enable_validation_layers = true;
#else
  const bool enable_validation_layers = false;
#endif

const std::vector<const char*> validation_layers = {
  "VK_LAYER_LUNARG_standard_validation"
};

const std::vector<const char*> device_extensions = {
  VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

static std::vector<const char*> required_extensions()
{
  uint32_t glfw_ext_count = 0;
  const char** glfw_exts;
  glfw_exts = glfwGetRequiredInstanceExtensions(&glfw_ext_count);

  std::vector<const char*> extensions(glfw_exts, glfw_exts + glfw_ext_count);
  if (enable_validation_layers)
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
  extensions.push_back("VK_KHR_xlib_surface");
  return extensions;
}

#include "vulkan_utils.h"

#include "vulkan_debug.h"
#include "vulkan_device.h"
#include "vulkan_inst.h"
#include "vulkan_wsurface.h"
#include "vulkan_swap_chain.h"
#include "vulkan_image_views.h"

int me::vulkan_api::initializeApi(void *window)
{
  int result = ME_FINE;

  int width = 0, height = 0;
  glfwGetWindowSize((GLFWwindow*)window, &width, &height);
  window_width = (uint32_t) (width < 0 ? 0 : width);
  window_height = (uint32_t) (height < 0 ? 0 : height);

  /* create instance */
  result = init_instance();
  if (result != ME_FINE) return result;
  std::cout << LOG_COLOR_GREEN << "[Vulkan]: Instance Created!\n" << LOG_ANSI_RESET;

  /* setup debug messenger */
  result = setup_debug_messenger();
  if (result != ME_FINE) return result;
  std::cout << LOG_COLOR_GREEN << "[Vulkan]: Debug Messenger Created!\n" << LOG_ANSI_RESET;

  /* setup window surface */
  result = setup_window_surface((GLFWwindow*)window);
  if (result != ME_FINE) return result;
  std::cout << LOG_COLOR_GREEN << "[Vulkan]: Window Surface Created!\n" << LOG_ANSI_RESET;

  /* setup physical device */
  result = setup_physical_device();
  if (result != ME_FINE) return result;
  std::cout << LOG_COLOR_GREEN << "[Vulkan]: Physical Device Created!\n" << LOG_ANSI_RESET;

  /* setup logical device */
  result = setup_logical_device();
  if (result != ME_FINE) return result;
  std::cout << LOG_COLOR_GREEN << "[Vulkan]: Logical Device Created!\n" << LOG_ANSI_RESET;

  /* setup swap chain */
  result = setup_swap_chain();
  if (result != ME_FINE) return result;
  std::cout << LOG_COLOR_GREEN << "[Vulkan]: Swap Chain Created!\n" << LOG_ANSI_RESET;

  /* setup image views */
  result = setup_image_views();
  if (result != ME_FINE) return result;
  std::cout << LOG_COLOR_GREEN << "[Vulkan]: Image Views Created!\n" << LOG_ANSI_RESET;

  return ME_FINE;
}
int me::vulkan_api::useProgram(me::shader_program &program)
{
  return ME_FINE;
}

me::device_info me::vulkan_api::getDeviceInfo()
{
  return {"", "", "", ""};
}

int me::vulkan_api::clearFrame()
{
  return ME_FINE;
}
int me::vulkan_api::cleanup()
{
  destroy_DUMExt(instance, debug_messenger, nullptr);
  for (auto image_view : swap_chain_image_views)
    vkDestroyImageView(device, image_view, nullptr);
  vkDestroySwapchainKHR(device, swap_chain, nullptr);
  vkDestroySurfaceKHR(instance, surface, nullptr);
  vkDestroyDevice(device, nullptr);
  vkDestroyInstance(instance, nullptr);
  return ME_FINE;
}
