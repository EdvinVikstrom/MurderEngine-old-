#include "vulkan_api.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "../MurderEngine.h"
#include "../scene/scene.h"
#include "../utilities/Logger.h"

extern std::string engine_name;
extern unsigned int engine_version;
extern std::string app_name;
extern unsigned int app_version;

me::log* VULKAN_LOGGER = new me::log("Vulkan", "\e[36m[%N] %T #%M \e[0m");

void vulkan_api::createInstance()
{
  /*
  #ifdef ME_DEBUG
    std::vector<std::string> validationLayers = {
      "VK_LAYER_KHRONOS_validation"
    };
    if (!layerSupport(validationLayers))
      VULKAN_LOGGER->err("Validation Layers not supported\n");
  #endif
  VkApplicationInfo appInfo = {
    VK_STRUCTURE_TYPE_APPLICATION_INFO,
    nullptr,
    app_name.c_str(),
    app_version,
    engine_name.c_str(),
    engine_version,
    VK_API_VERSION_1_2
  };
  VkInstanceCreateInfo createInfo = {
    VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
    &appInfo
  };
  #ifdef ME_DEBUG
    createInfo.enabledLayerCount = static_cast<unsigned int>(validationLayers.size());
    createInfo.ppEnabledExtensionNames = validationLayers.data();
  #else
    createInfo.enabledLayerCount = 0;
  #endif

  unsigned int glfw_extensionCount;
  const char** glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extensionCount);
  createInfo.enabledExtensionCount = glfw_extensionCount;
  createInfo.ppEnabledExtensionNames = glfw_extensions;
  createInfo.enabledLayerCount = 0;
  VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
  if (result != VK_SUCCESS)
    VULKAN_LOGGER->err("Failed to create vulkan instance\n");

  unsigned int extensionCount;
  vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
  std::vector<VkExtensionProperties> extensions(extensionCount);
  vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
  VULKAN_LOGGER->out("Extensions available: {\n");
  for (auto& extension : extensions)
    VULKAN_LOGGER->out(std::string("  ") + std::string(extension.extensionName) + "\n");
  VULKAN_LOGGER->out("}\n");
  */
}

int vulkan_api::initializeApi()
{
  vulkan_api::createInstance();

  return ME_FINE;
}

int vulkan_api::viewport(me::camera* camera, int x, int y, unsigned int width, unsigned int height)
{
  return ME_FINE;
}
int vulkan_api::useProgram(unsigned int program)
{
  return ME_FINE;
}

int vulkan_api::push()
{
  return ME_FINE;
}
int vulkan_api::pop()
{
  return ME_FINE;
}
int vulkan_api::clear()
{
  return ME_FINE;
}
int vulkan_api::vertex(float x, float y, float z)
{
  return ME_FINE;
}
int vulkan_api::renderStart(unsigned int type)
{
  return ME_FINE;
}
int vulkan_api::renderEnd()
{
  return ME_FINE;
}
int vulkan_api::bindMesh(me::mesh* mesh)
{
  return ME_FINE;
}
int vulkan_api::unbindMesh()
{
  return ME_FINE;
}
int vulkan_api::mesh(me::mesh* mesh)
{
  return ME_FINE;
}
int vulkan_api::bindImage(me::image* image)
{
  return ME_FINE;
}
int vulkan_api::unbindImage()
{
  return ME_FINE;
}
int vulkan_api::plane(double posX, double posY, double scaleX, double scaleY)
{
  return ME_FINE;
}
int vulkan_api::color(float red, float green, float blue, float alpha)
{
  return ME_FINE;
}

int vulkan_api::reset()
{
  return ME_FINE;
}
int vulkan_api::translate(double x, double y, double z, double w)
{
  return ME_FINE;
}
int vulkan_api::rotate(double x, double y, double z, double w)
{
  return ME_FINE;
}
int vulkan_api::scale(double x, double y, double z, double w)
{
  return ME_FINE;
}
int vulkan_api::modify(unsigned int p, float value)
{
  return ME_FINE;
}

int vulkan_api::terminate()
{
  vkDestroyInstance(instance, nullptr);
  return ME_FINE;
}
