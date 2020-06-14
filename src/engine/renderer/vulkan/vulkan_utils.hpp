#ifndef VULKAN_UTILS_H
  #define VULKAN_UTILS_H

static const char* vkErrStr(VkResult err)
{
  switch(err)
  {
    case VK_ERROR_DEVICE_LOST:
    return "VK_ERROR_DEVICE_LOST"; break;
    case VK_ERROR_FRAGMENTATION:
    return "VK_ERROR_FRAGMENTATION"; break;
    case VK_ERROR_FRAGMENTED_POOL:
    return "VK_ERROR_FRAGMENTED_POOL"; break;
    case VK_ERROR_MEMORY_MAP_FAILED:
    return "VK_ERROR_MEMORY_MAP_FAILED"; break;
    case VK_ERROR_LAYER_NOT_PRESENT:
    return "VK_ERROR_LAYER_NOT_PRESENT"; break;
    case VK_ERROR_INVALID_SHADER_NV:
    return "VK_ERROR_INVALID_SHADER_NV"; break;
    case VK_ERROR_FEATURE_NOT_PRESENT:
    return "VK_ERROR_FEATURE_NOT_PRESENT"; break;
    case VK_ERROR_INCOMPATIBLE_DRIVER:
    return "VK_ERROR_INCOMPATIBLE_DRIVER"; break;
    case VK_ERROR_FORMAT_NOT_SUPPORTED:
    return "VK_ERROR_FORMAT_NOT_SUPPORTED"; break;
    case VK_ERROR_INITIALIZATION_FAILED:
    return "VK_ERROR_INITIALIZATION_FAILED"; break;
    case VK_ERROR_EXTENSION_NOT_PRESENT:
    return "VK_ERROR_EXTENSION_NOT_PRESENT"; break;
    case VK_ERROR_INVALID_EXTERNAL_HANDLE:
    return "VK_ERROR_INVALID_EXTERNAL_HANDLE"; break;
    case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
    return "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR"; break;
    case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
    return "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS"; break;
    case VK_ERROR_UNKNOWN:
    default:
    return "UNKNOWN"; break;
  }
  return "*this message should not exists*\n";
}

static const char* vkDeviceType(VkPhysicalDeviceType type)
{
  switch(type)
  {
    case VK_PHYSICAL_DEVICE_TYPE_CPU:
    return "CPU"; break;
    case VK_PHYSICAL_DEVICE_TYPE_OTHER:
    return "OTHER"; break;
    case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
    return "VIRTUAL GPU"; break;
    case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
    return "DISCRETE GPU"; break;
    case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
    return "INTERGRATED GPU"; break;
    default:
    return "Unknow"; break;
  }
  return "*this message should not exists*\n";
}

#endif
