#include "vulkan_api.h"
#include "vulkan_utils.h"

#include <stdio.h>
#include <stdlib.h>

#include "vulkan_device.h"
#include "vulkan_graphics_pipeline.h"

int me::vulkan_api::init_instance()
{
  /* application info */
  VkApplicationInfo app_info = {};
  app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info.pNext = nullptr;
  app_info.pApplicationName = "Murder Engine";
  app_info.applicationVersion = VK_MAKE_VERSION(0, 2, 3);
  app_info.pEngineName = "MurderEngine";
  app_info.engineVersion = VK_MAKE_VERSION(0, 4, 7);
  app_info.apiVersion = VK_API_VERSION_1_2;

  /* instance info */
  VkInstanceCreateInfo instance_info = {};
  instance_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  instance_info.pNext = nullptr;
  instance_info.flags = 0;
  instance_info.pApplicationInfo = &app_info;
  instance_info.enabledLayerCount = 0;
  instance_info.enabledExtensionCount = 0;

  /* create instance */
  VkResult result = vkCreateInstance(&instance_info, nullptr, &instance);
  if (result == VK_ERROR_INCOMPATIBLE_DRIVER)
  {
    printf("[Vulkan] [ERR]: can't find a compatible Vulkan ICD\n");
    return ME_ERR;
  }else if (result != VK_SUCCESS)
  {
    printf("[Vulkan] [ERR]: %s\n", vkErrStr(result));
    return ME_ERR;
  }
  return ME_FINE;
}

int me::vulkan_api::init_instance_extensions()
{
  instance_extensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
  instance_extensions.push_back(VK_KHR_XLIB_SURFACE_EXTENSION_NAME);
  return ME_FINE;
}

int me::vulkan_api::init_device_extensions()
{
  device_extensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
  return ME_FINE;
}

int me::vulkan_api::initializeApi(MeInstance* instance)
{
  this->window = (GLFWwindow*)instance->window->window;
  this->width = instance->window->info->width;
  this->height = instance->window->info->height;

  init_instance_extensions();
  init_device_extensions();

  init_instance();
  init_enumerate_device();
  init_surface();
  init_device();
  init_swapchain();
  init_command_buffers();

  return ME_FINE;
}

int me::vulkan_api::setupMeshRenderer(MeInstance* instance)
{
  return ME_FINE;
}
int me::vulkan_api::setupImageRenderer(MeInstance* instance)
{
  return ME_FINE;
}
int me::vulkan_api::loadMesh(me::Mesh* mesh)
{
  return ME_FINE;
}
int me::vulkan_api::loadImage(me::Image* image)
{
  return ME_FINE;
}

int me::vulkan_api::uniformMatrix4(int location, me::maths::mat4 matrix)
{
  return ME_FINE;
}
int me::vulkan_api::uniformVec2(int location, me::vec2 vec)
{
  return ME_FINE;
}
int me::vulkan_api::uniformVec3(int location, me::vec3 vec)
{
  return ME_FINE;
}
int me::vulkan_api::uniformVec4(int location, me::vec4 vec)
{
  return ME_FINE;
}

int me::vulkan_api::renderFrame(MeInstance* instance, unsigned long current_frame, bool &framebuffer_resized)
{
  return ME_FINE;
}
int me::vulkan_api::cleanup()
{
  VkCommandBuffer command_buffers[1] = {command_buffer};
  vkFreeCommandBuffers(device, command_pool, 1, command_buffers);
  vkDestroyCommandPool(device, command_pool, nullptr);

  // TODO: for (uint32_t i = 0; i < swapchain_image_count; i++)
    // TODO: vkDestroyImageView(device, buffers[i].view, nullptr);
  vkDestroySwapchainKHR(device, swapchain, nullptr);
  vkDestroyDevice(device, nullptr);
  vkDestroyInstance(instance, nullptr);
  return ME_FINE;
}
