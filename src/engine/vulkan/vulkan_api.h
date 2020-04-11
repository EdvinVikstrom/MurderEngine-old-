#ifndef VULKAN_API_H
  #define VULKAN_API_H

/* vulkan */
#define VK_USE_PLATFORM_XLIB_KHR
#include "../../external/vulkan/x86_64/include/vulkan/vulkan.hpp"
#include "../../external/vulkan/x86_64/include/vulkan/vulkan.h"

/* GLFW */
#define GLFW_EXPOSE_NATIVE_X11
#include "../../external/glfw/include/GLFW/glfw3.h"
#include "../../external/glfw/include/GLFW/glfw3native.h"

#include "../renderer/renderer_api.h"
#include <optional>

namespace me {

  struct vulkan_api : me::frenderer {

    struct QueueFamilyIndices {
      std::optional<uint32_t> graphics_family;
      std::optional<uint32_t> present_family;
      bool is_complete()
      {
        return graphics_family.has_value() && present_family.has_value();
      }
    };

    struct SwapChainSupportDetails {
      VkSurfaceCapabilitiesKHR capabilities;
      std::vector<VkSurfaceFormatKHR> formats;
      std::vector<VkPresentModeKHR> present_modes;
    };

    VkInstance instance;
    VkPhysicalDevice physical_device;
    VkDevice device;
    VkQueue graphics_queue;
    VkQueue present_queue;
    VkSurfaceKHR surface;
    VkSwapchainKHR swap_chain;
    VkFormat swap_chain_image_format;
    VkExtent2D swap_chain_extent;
    VkRenderPass render_pass;
    VkPipelineLayout pipeline_layout;
    VkPipeline graphics_pipeline;
    VkDebugUtilsMessengerEXT debug_messenger;

    std::vector<VkImage> swap_chain_images;
    std::vector<VkImageView> swap_chain_image_views;

    std::vector<VkViewport> viewports;
    std::vector<VkRect2D> scissors;

    uint32_t window_width, window_height;

    QueueFamilyIndices find_queue_families(VkPhysicalDevice device);
    bool is_device_suitable(VkPhysicalDevice device);
    bool validation_layer_supported(const std::vector<const char*> &validation_layers);
    bool device_extension_supported(VkPhysicalDevice device);

    /* swap chain */
    SwapChainSupportDetails query_swap_chain_support(VkPhysicalDevice device);
    VkSurfaceFormatKHR choose_swap_surface_format(const std::vector<VkSurfaceFormatKHR> &available_formats);
    VkPresentModeKHR choose_swap_present_mode(const std::vector<VkPresentModeKHR> &available_present_modes);
    VkExtent2D choose_swap_extent(const VkSurfaceCapabilitiesKHR &capabilities);

    /* graphics pipeline */
    VkShaderModule setup_shader_module(char* source, uint32_t size);
    int add_viewport(int x, int y, uint32_t width, uint32_t height);
    int setup_viewports(VkPipelineViewportStateCreateInfo &viewport_state);
    int setup_rasterization_state(
      VkPipelineRasterizationStateCreateInfo &rasterizer,
      VkPipelineMultisampleStateCreateInfo &multisampling,
      VkPipelineColorBlendAttachmentState &color_blend_attachment,
      VkPipelineColorBlendStateCreateInfo &color_blending,
      VkPipelineDynamicStateCreateInfo &dynamic_state
    );

    int init_instance();
    int setup_debug_messenger();
    int setup_window_surface(GLFWwindow* window);
    int setup_physical_device();
    int setup_logical_device();
    int setup_swap_chain();
    int setup_image_views();
    int setup_render_pass();
    int setup_graphics_pipeline(me::shader_program* program);

    int initializeApi(void* window, me::shader_program* program) override;
    int useProgram(me::shader_program &program) override;

    me::device_info getDeviceInfo() override;

    int clearFrame() override;
    int cleanup() override;

  };

};

#endif
