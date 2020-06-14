#ifndef VULKAN_API_H
  #define VULKAN_API_H

#include "../../MurderEngine.hpp"
#include "../../kernel/common.hpp"

/* vulkan */
#define VK_USE_PLATFORM_XLIB_KHR
#include "../../../external/vulkan/source/Vulkan-Headers/include/vulkan/vulkan.hpp"
#include "../../../external/vulkan/source/Vulkan-Headers/include/vulkan/vulkan.hpp"

/* GLFW */
#define GLFW_EXPOSE_NATIVE_X11
#include "../../../external/glfw/include/GLFW/glfw3.hpp"
#include "../../../external/glfw/include/GLFW/glfw3native.hpp"


#include <vector>
#include <map>

namespace me {
  
  struct vulkan_api : MeRenderer {
    
    std::vector<const char*> instance_extensions;
    std::vector<const char*> device_extensions;
    
    /* widnow */
    GLFWwindow* window;
    uint32_t width, height;
    
    VkInstance instance;
    VkSurfaceKHR surface;
    VkDevice device;
    VkSwapchainKHR swapchain;
    
    VkFormat format;
    VkExtent2D swapchain_extent;
    
    VkPhysicalDevice physical_device;
    std::vector<VkPhysicalDevice> gpus;
    std::vector<VkQueueFamilyProperties> queue_properties;
    uint32_t queue_family_count;
    uint32_t graphics_queue_family_index;
    uint32_t present_queue_family_index;
    
    std::vector<VkImageView> buffers;
    uint32_t swapchain_image_count;
    
    /* graphics pipeline */
    VkCommandPool command_pool;
    VkCommandBuffer command_buffer;
    
    /* other */
    int init_queue_family_index(VkDeviceQueueCreateInfo &queue_info);
    
    int init_instance_extensions();
    int init_device_extensions();
    
    int window_spec();
    
    int init_instance();
    int init_enumerate_device();
    int init_surface();
    int init_device();
    int init_swapchain();
    int init_command_buffers();
    
    int initializeApi(MeInstance* instance);
    
    int setupMeshRenderer(MeInstance* instance);
    int setupImageRenderer(MeInstance* instance);
    int loadMesh(me::Mesh* mesh);
    int loadImage(me::Image* image);
    
    int uniformMatrix4(int location, me::maths::mat4 matrix);
    int uniformVec2(int location, me::vec2 vec);
    int uniformVec3(int location, me::vec3 vec);
    int uniformVec4(int location, me::vec4 vec);
    
    int renderFrame(MeInstance* instance, unsigned long current_frame, bool &framebuffer_resized);
    int cleanup();
    
  };
  
};

#endif
