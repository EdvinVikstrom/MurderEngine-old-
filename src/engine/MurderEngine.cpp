#include "MurderEngine.hpp"
#include "EngineInit.hpp"

/* GLFW */
#define GLFW_EXPOSE_NATIVE_X11
#include "../external/glfw/include/GLFW/glfw3.h"
#include "../external/glfw/include/GLFW/glfw3native.h"

//#include "renderer/vulkan/vulkan_api.hpp"
#include "renderer/opengl/opengl_api.hpp"

static void error_callback(int error, const char* description)
{
  std::cout << "[GLFW] [ERR-" << error << "]: " << description << "\n";
}

static void framebuffer_resize_callback(GLFWwindow* window, int width, int height)
{
  MeInstance* instance = reinterpret_cast<MeInstance*>(glfwGetWindowUserPointer(window));
  instance->window->framebufferResized = true;
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
  MeInstance* instance = reinterpret_cast<MeInstance*>(glfwGetWindowUserPointer(window));

  for (MeScene* scene : instance->scenes)
    scene->MeScene_input(instance, DEV_MOUSE, 2, 0, xpos, ypos);

  instance->inputInfo.cursorX = xpos;
  instance->inputInfo.cursorY = ypos;
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  MeInstance* instance = reinterpret_cast<MeInstance*>(glfwGetWindowUserPointer(window));
  for (MeScene* scene : instance->scenes)
    scene->MeScene_input(instance, DEV_MOUSE, 3, 0, xoffset, yoffset);
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
  MeInstance* instance = reinterpret_cast<MeInstance*>(glfwGetWindowUserPointer(window));
  if (action==GLFW_PRESS)
    instance->inputInfo.pressedButtons.insert(button);
  if (action==GLFW_RELEASE)
    instance->inputInfo.pressedButtons.erase(button);

  for (MeScene* scene : instance->scenes)
    scene->MeScene_input(instance, DEV_MOUSE, action, button);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  MeInstance* instance = reinterpret_cast<MeInstance*>(glfwGetWindowUserPointer(window));
  if (action==GLFW_PRESS)
    instance->inputInfo.pressedKeys.insert(key);
  if (action==GLFW_RELEASE)
    instance->inputInfo.pressedKeys.erase(key);

  for (MeScene* scene : instance->scenes)
    scene->MeScene_input(instance, DEV_KEYBOARD, action, key);
}

MeResult MeCommand::execute(MeInstance* instance)
{
  return ME_SUCCESS;
}

void MeWindow::destroy()
{
  glfwDestroyWindow((GLFWwindow*)window);
}
bool MeWindow::shouldClose()
{
  return glfwWindowShouldClose((GLFWwindow*) window);
}

bool MeInstance::shouldExit()
{
  return window != nullptr ? window->shouldClose() : false;
}

MeResult meInitInstance(MeInstanceInfo* info, MeInstance* instance)
{
  instance->info = info;
  return ME_SUCCESS;
}
MeResult meInitWindow(MeInstance* instance, MeWindowInfo* info, MeWindow* window)
{
  glfwSetErrorCallback(error_callback);
  if (!glfwInit())
  {
    std::cout << "[GLFW] Failed to initialize\n";
    return ME_ERR;
  }
  instance->window = window;
  window->info = info;
  window->window = glfwCreateWindow(info->width, info->height, info->title.c_str(), nullptr, nullptr);
  glfwSetWindowUserPointer((GLFWwindow*)window->window, instance);

  /* callbacks */
  glfwSetFramebufferSizeCallback((GLFWwindow*)window->window, framebuffer_resize_callback);
  glfwSetCursorPosCallback((GLFWwindow*)window->window, cursor_position_callback);
  glfwSetScrollCallback((GLFWwindow*)window->window, scroll_callback);
  glfwSetMouseButtonCallback((GLFWwindow*)window->window, mouse_button_callback);
  glfwSetKeyCallback((GLFWwindow*)window->window, key_callback);

  glfwMakeContextCurrent((GLFWwindow*)window->window);
  glfwShowWindow((GLFWwindow*)window->window);
  glfwSwapInterval(1);
  return ME_SUCCESS;
}
MeResult meInitRenderer(MeInstance* instance, MeRendererInfo* info)
{
  switch(info->api)
  {
    case ME_VULKAN:
      // instance->renderer = new me::vulkan_api;
    break;
    case ME_OPENGL:
      instance->renderer = new me::opengl_api;
    break;
    default:
      std::cout << "API not supported\n";
      return ME_ERR;
    break;
  }
  instance->renderer->info = info;
  instance->renderer->initializeApi(instance);
  return ME_SUCCESS;
}
MeResult meInitCommandBuffer(MeInstance* instance, MeCommandBuffer* commandBuffer)
{
  instance->commandBuffer = commandBuffer;
  return ME_SUCCESS;
}
MeResult meRunLoop(MeInstance* instance)
{
  meInitEverything();
  for (MeScene* scene : instance->scenes)
    scene->MeScene_initialize(instance);
  while(instance->shouldExit() != true)
  {
    for (MeScene* scene : instance->scenes)
      scene->MeScene_tick(instance);
    instance->renderer->renderFrame(instance, instance->currentFrame, instance->window->framebufferResized);
    glfwSwapBuffers((GLFWwindow*)instance->window->window);
    glfwPollEvents();
    instance->currentFrame++;
  }
  for (MeScene* scene : instance->scenes)
    scene->MeScene_finalize(instance);
  meCleanupEverything();
  return ME_SUCCESS;
}

void meStartRecord(MeCommandBuffer* commandBuffer)
{
  commandBuffer->recording = true;
}
void meStopRecord(MeCommandBuffer* commandBuffer)
{
  commandBuffer->recording = false;
}

/* commands */
void meRenderFrame(MeCommandBuffer* commandBuffer)
{
  if (!commandBuffer->recording) return;
    commandBuffer->commands.push_back(MeCommand(ME_RENDER_FRAME_FUNC));
}
void mePollEvents(MeCommandBuffer* commandBuffer)
{
  if (!commandBuffer->recording) return;
    commandBuffer->commands.push_back(MeCommand(ME_POLL_EVENTS_FUNC));
}
void mePollWindowEvents(MeCommandBuffer* commandBuffer)
{
  if (!commandBuffer->recording) return;
    commandBuffer->commands.push_back(MeCommand(ME_POLL_WINDOW_EVENTS_FUNC));
}
void meSwapBuffers(MeCommandBuffer* commandBuffer)
{
  if (!commandBuffer->recording) return;
    commandBuffer->commands.push_back(MeCommand(ME_SWAP_BUFFERS_FUNC));
}
void meIdle(MeCommandBuffer* commandBuffer)
{
  if (!commandBuffer->recording) return;
    commandBuffer->commands.push_back(MeCommand(ME_IDLE_FUNC));
}
void mePullFunction(MeCommandBuffer* commandBuffer, MeEventFunc* func)
{
  // TODO:
}

/* cleanup */
void meDestroyInstance(MeInstance* instance)
{
}
void meDestroyWindow(MeWindow* window)
{
  window->destroy();
  glfwTerminate();
}
void meDestroyRenderer(MeRenderer* renderer)
{
  renderer->cleanup();
}
