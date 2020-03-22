#include "GLFW/glfw3.h"
#include <vector>
#include <map>
#include <string>

#include "MurderEngine.h"
#include "EngineManager.h"
#include "renderer/RendererApi.h"
#include "renderer/OpenGLApi.h"

#include "utilities/Logger.h"

std::string RENDERER_API_NAME = "opengl";
IRendererApi* rendererApi;

std::string w_title;
unsigned int w_width, w_height;
bool w_vSync, w_fullscreen;
GLFWwindow* window;

unsigned int fpsCount, fps;

me::log* ME_LOGGER = new me::log("MurderEngine", "\e[32m[%N] %T #%M \e[0m");

std::vector<me::IEngineEvent*> events;
std::map<int, bool> keysPressed; // buttons and keys
double cursorPosX, cursorPosY;

bool me::IEngineEvent::isPressed(int key)
{
  if (keysPressed.count(key))
    return keysPressed[key];
  return false;
}

int me::engine_register_event(IEngineEvent* event)
{
  events.push_back(event);
  return 0;
}

int me::engine_init()
{
  ME_LOGGER->out("Initialize Engine!\n");
  return 0;
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
  double offsetX = xpos-cursorPosX;
  double offsetY = ypos-cursorPosY;
  for (me::IEngineEvent* event : events)
    event->onMouseInput(ME_MOUSE_MOVE, offsetX, offsetY, 0);
  cursorPosX = xpos;
  cursorPosY = ypos;
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  for (me::IEngineEvent* event : events)
    event->onMouseInput(ME_MOUSE_SCROLL, xoffset, yoffset, 0);
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
  if (action==GLFW_PRESS)
    keysPressed[button] = true;
  else if (action==GLFW_RELEASE)
    keysPressed[button] = false;
  for (me::IEngineEvent* event : events)
    event->onMouseInput(action==GLFW_PRESS?ME_PRESS:(action==GLFW_RELEASE?ME_RELEASE:0), cursorPosX, cursorPosY, button);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (action==GLFW_PRESS)
    keysPressed[key] = true;
  else if (action==GLFW_RELEASE)
    keysPressed[key] = false;
  for (me::IEngineEvent* event : events)
    event->onKeyInput(action==GLFW_PRESS?ME_PRESS:(action==GLFW_RELEASE?ME_RELEASE:0), key);
}


int me::engine_window(std::string title, unsigned int width, unsigned int height, bool vSync, bool fullscreen)
{
  if (!glfwInit())
    ME_LOGGER->out("GLFW don't wanna Initialize\n");
  w_title = title;
  w_width = width;
  w_height = height;
  w_vSync = vSync;
  w_fullscreen = fullscreen;
  window = glfwCreateWindow(width, height, title.c_str(), fullscreen?glfwGetPrimaryMonitor():NULL, NULL);
  glfwSetCursorPosCallback(window, cursor_position_callback);
  glfwSetScrollCallback(window, scroll_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);
  glfwSetKeyCallback(window, key_callback);
  glfwMakeContextCurrent(window);
  glfwShowWindow(window);
  glfwSwapInterval(vSync?1:0);
  return 0;
}

int me::engine_loop()
{
  while(!glfwWindowShouldClose(window))
  {
    rendererApi->clear();
    for (me::IEngineEvent* event : events)
      event->onLoop();
    for (me::IEngineEvent* event : events)
      event->onRender();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

int me::engine_setup_renderer_api(std::string apiName)
{
  if (apiName=="opengl")
    rendererApi = new OpenGLApi();
  else if (apiName=="vulkan") { }
  RENDERER_API_NAME = apiName;
  ME_LOGGER->out("Initializing Renderer API ...\n");
  rendererApi->initializeApi();
  ME_LOGGER->out(std::string("Renderer API initialized [" + RENDERER_API_NAME + "]\n"));
  return 0;
}

void me::engine_window_size(unsigned int* width, unsigned int* height)
{
  *width = w_width;
  *height = w_height;
}
