#include "GLFW/glfw3.h"
#include <vector>
#include <map>

#include "MurderEngine.h"
#include "EngineManager.h"
#include "renderer/renderer_api.h"
#include "renderer/opengl_api.h"

#include "loaders/shader_reader.h"

#include "utilities/Logger.h"

std::string engine_name = "Murder Engine";
unsigned int engine_version = 7;
std::string app_name = "Murder Engine Interface";
unsigned int app_version = 1;

std::string RENDERER_API_NAME = "vulkan";
renderer_api* rendererApi;

std::string w_title;
unsigned int w_width, w_height;
bool w_vSync, w_fullscreen;
GLFWwindow* window;

unsigned int fpsCount, fps;

static me::log* ME_LOGGER = new me::log("MurderEngine",
"\e[32m[%N] %T #%M \e[0m",
"\e[32m[%N] %T\e[0m \e[33m#%M \e[0m",
"\e[32m[%N] %T\e[0m \e[31m#%M \e[0m",
"\e[34m[%N] %T #%M \e[0m"
);

std::vector<me::event::engine_event*> engine_events;
std::vector<me::event::input_event*> input_events;
std::map<int, bool> keysPressed; // buttons and keys
double cursorPosX, cursorPosY;

bool me::event::input_event::isPressed(int key)
{
  if (keysPressed.count(key))
    return keysPressed[key];
  return false;
}
double me::event::input_event::mouseX()
{
  return cursorPosX;
}
double me::event::input_event::mouseY()
{
  return cursorPosY;
}

int me::engine_register_engine_event(me::event::engine_event* event)
{
  engine_events.push_back(event);
  return 0;
}

int me::engine_register_input_event(me::event::input_event* event)
{
  input_events.push_back(event);
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
  for (me::event::input_event* event : input_events)
    event->onMouseInput(ME_MOUSE_MOVE, offsetX, offsetY, 0);
  cursorPosX = xpos;
  cursorPosY = ypos;
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  for (me::event::input_event* event : input_events)
    event->onMouseInput(ME_MOUSE_SCROLL, xoffset, yoffset, 0);
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
  if (action==GLFW_PRESS)
    keysPressed[button] = true;
  else if (action==GLFW_RELEASE)
    keysPressed[button] = false;
  for (me::event::input_event* event : input_events)
    event->onMouseInput(action==GLFW_PRESS?ME_PRESS:(action==GLFW_RELEASE?ME_RELEASE:0), cursorPosX, cursorPosY, button);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (action==GLFW_PRESS)
    keysPressed[key] = true;
  else if (action==GLFW_RELEASE)
    keysPressed[key] = false;
  for (me::event::input_event* event : input_events)
    event->onKeyInput(action==GLFW_PRESS?ME_PRESS:(action==GLFW_RELEASE?ME_RELEASE:0), key);
}


int me::engine_window(const std::string &title, unsigned int width, unsigned int height, bool vSync, bool fullscreen)
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
    for (me::event::engine_event* event : engine_events)
      event->onLoop();
    for (me::event::engine_event* event : engine_events)
      event->onRender();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  rendererApi->terminate();
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

int me::engine_load_shaders(const std::string &shader_path)
{
  unsigned int shaderCount = 2;
  unsigned int* shaders = new unsigned int[shaderCount];
  unsigned int program;
  if (loader::loadShaders(shader_path, shaders, shaderCount) != ME_FINE)
    return ME_ERR;
  if (loader::linkShaders(program, shaders, shaderCount) != ME_FINE)
    return ME_ERR;
  rendererApi->useProgram(program);
  return ME_FINE;
}

int me::engine_setup_renderer_api(const std::string &apiName)
{
  if (apiName=="opengl")
    rendererApi = new opengl_api;
  else if (apiName=="vulkan")
  {
  }
  RENDERER_API_NAME = apiName;
  ME_LOGGER->out("Initializing Renderer API ...\n");
  if (rendererApi->initializeApi() != ME_FINE)
    return 1;
  ME_LOGGER->out(std::string("Renderer API initialized [") + RENDERER_API_NAME + "]\n");
  return 0;
}

void me::engine_window_size(unsigned int* width, unsigned int* height)
{
  *width = w_width;
  *height = w_height;
}
