#include "MurderEngine.h"
#include "EngineInit.h"

/* GLFW */
#define GLFW_EXPOSE_NATIVE_X11
#include "../external/glfw/include/GLFW/glfw3.h"
#include "../external/glfw/include/GLFW/glfw3native.h"

#include "renderer/vulkan/vulkan_api.h"
#include "renderer/opengl/opengl_api.h"

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
  for (MeEngineEvent* event : instance->events)
    event->onMouseInput(instance, ME_MOUSE_MOVE, instance->window->cursorX - xpos, instance->window->cursorY - ypos, ME_KEY_NONE);
  instance->window->cursorX = xpos;
  instance->window->cursorY = ypos;
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  MeInstance* instance = reinterpret_cast<MeInstance*>(glfwGetWindowUserPointer(window));
  for (MeEngineEvent* event : instance->events)
    event->onMouseInput(instance, ME_MOUSE_SCROLL, xoffset, yoffset, ME_KEY_NONE);
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
  MeInstance* instance = reinterpret_cast<MeInstance*>(glfwGetWindowUserPointer(window));
  if (action==GLFW_PRESS)
    instance->window->pressedKeys[MeEngineEvent::fromGLFW(button, ME_MOUSE)] = ME_TRUE;
  if (action==GLFW_RELEASE)
    instance->window->pressedKeys[MeEngineEvent::fromGLFW(button, ME_MOUSE)] = ME_FALSE;
  for (MeEngineEvent* event : instance->events)
    event->onMouseInput(instance, MeEngineEvent::fromGLFW(action, ME_INPUT_TYPE_OTHER), instance->window->cursorX, instance->window->cursorY, button);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  MeInstance* instance = reinterpret_cast<MeInstance*>(glfwGetWindowUserPointer(window));
  if (action==GLFW_PRESS)
    instance->window->pressedKeys[static_cast<MeKey>(key)] = ME_TRUE;
  if (action==GLFW_RELEASE)
    instance->window->pressedKeys[static_cast<MeKey>(key)] = ME_FALSE;
  for (MeEngineEvent* event : instance->events)
    event->onKeyInput(instance, MeEngineEvent::fromGLFW(action, ME_INPUT_TYPE_OTHER), key);
}

bool MeEngineEvent::isPressed(MeInstance* instance, int key)
{
  if (!instance->window->pressedKeys.count(key))
    return false;
  return instance->window->pressedKeys[key];
}

MeResult MeCommand::execute(MeInstance* instance)
{
  return ME_SUCCESS;
}

void MeWindow::destroy()
{
  glfwDestroyWindow((GLFWwindow*)window);
}
MeBool MeWindow::shouldClose()
{
  return glfwWindowShouldClose((GLFWwindow*)window) ? ME_TRUE : ME_FALSE;
}

MeBool MeInstance::shouldExit()
{
  return window != nullptr ? window->shouldClose() : ME_FALSE;
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
      instance->renderer = new me::vulkan_api;
    break;
    case ME_OPENGL:
      instance->renderer = new me::opengl_api;
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
  for (MeEngineEvent* event : instance->events)
    event->onInit(instance);
  while(instance->shouldExit() != ME_TRUE)
  {
    instance->renderer->renderFrame(instance, instance->currentFrame, instance->window->framebufferResized);
    for (MeEngineEvent* event : instance->events)
      event->onLoop(instance);
    for (MeEngineEvent* event : instance->events)
      event->onRender(instance->renderer);
    glfwSwapBuffers((GLFWwindow*)instance->window->window);
    glfwPollEvents();
    instance->currentFrame++;
  }
  meCleanupEverything();
  return ME_SUCCESS;
}

MeResult meLoadShaders(const char* filepath, MeShaderProgram* shaderProgram)
{

  return ME_SUCCESS;
}

MeResult meRegisterEvent(MeInstance* instance, MeEngineEvent* event)
{
  instance->events.push_back(event);
  return ME_SUCCESS;
}

void meStartRecord(MeCommandBuffer* commandBuffer)
{
  commandBuffer->recording = ME_TRUE;
}
void meStopRecord(MeCommandBuffer* commandBuffer)
{
  commandBuffer->recording = ME_FALSE;
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
  for (MeEngineEvent* event : instance->events)
    event->onDestroyed(instance);
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
