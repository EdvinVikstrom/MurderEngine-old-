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
#include "../math/vectors.h"
#include <optional>

namespace me {

  struct vulkan_api : me::frenderer {

    struct vvertex {
      me::vec2 pos;
      me::vec3 color;
      static VkVertexInputBindingDescription get_binding_description()
      {
        VkVertexInputBindingDescription binding_description = {};
        binding_description.binding = 0;
        binding_description.stride = sizeof(vvertex);
        binding_description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        return binding_description;
      }
      static std::array<VkVertexInputAttributeDescription, 2> get_attribute_descriptions()
      {
        std::array<VkVertexInputAttributeDescription, 2> attribute_descriptions = {};
        attribute_descriptions[0].binding = 0;
        attribute_descriptions[0].location = 0;
        attribute_descriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
        attribute_descriptions[0].offset = offsetof(vvertex, pos);
        attribute_descriptions[1].binding = 0;
        attribute_descriptions[1].location = 1;
        attribute_descriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attribute_descriptions[1].offset = offsetof(vvertex, color);
        return attribute_descriptions;
      }
    };

    struct vmesh {
      VkBuffer vertex_buffer;
      VkDeviceMemory vertex_buffer_mem;
      std::vector<vvertex> vertices;
    };

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

    const int max_frames_in_flight = 2;

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
    VkCommandPool command_pool;
    std::vector<VkSemaphore> image_available_semaphores;
    std::vector<VkSemaphore> render_finished_semaphores;
    std::vector<VkFence> in_flight_fences;
    std::vector<VkFence> images_in_flight;
    VkDebugUtilsMessengerEXT debug_messenger;

    std::vector<VkImage> swap_chain_images;
    std::vector<VkImageView> swap_chain_image_views;
    std::vector<VkFramebuffer> swap_chain_framebuffers;

    std::vector<VkCommandBuffer> command_buffers;

    std::vector<VkViewport> viewports;
    std::vector<VkRect2D> scissors;

    std::vector<vmesh*> meshes;

    uint32_t window_width, window_height;

    QueueFamilyIndices find_queue_families(VkPhysicalDevice device);
    bool is_device_suitable(VkPhysicalDevice device);
    bool validation_layer_supported(const std::vector<const char*> &validation_layers);
    bool device_extension_supported(VkPhysicalDevice device);
    uint32_t find_memory_type(uint32_t type_filter, VkMemoryPropertyFlags properties);

    /* swap chain */
    SwapChainSupportDetails query_swap_chain_support(VkPhysicalDevice device);
    VkSurfaceFormatKHR choose_swap_surface_format(const std::vector<VkSurfaceFormatKHR> &available_formats);
    VkPresentModeKHR choose_swap_present_mode(const std::vector<VkPresentModeKHR> &available_present_modes);
    VkExtent2D choose_swap_extent(GLFWwindow* window, const VkSurfaceCapabilitiesKHR &capabilities);

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
    int setup_swap_chain(GLFWwindow* window);
    int setup_image_views();
    int setup_render_pass();
    int setup_graphics_pipeline(me::shader_program* program);
    int setup_framebuffers();
    int setup_command_pool();
    int setup_buffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer &buffer, VkDeviceMemory &buffer_mem);
    int setup_vertex_buffer(vmesh &mesh);
    int setup_command_buffers();
    int setup_synced_objects();

    int cleanup_swap_chain();
    int update_swap_chain(GLFWwindow* window, me::shader_program* program);

    int initializeApi() override;
    int useProgram(me::shader_program &program) override;

    me::device_info getDeviceInfo() override;

    int renderFrame(unsigned long current_frame, bool &framebuffer_resized) override;
    int clearFrame() override;
    int cleanup() override;

  };

};

#endif
