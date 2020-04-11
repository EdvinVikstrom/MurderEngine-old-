#include "MurderEngine.h"

/* GLFW */
#include "../external/glfw/include/GLFW/glfw3.h"

#include "vulkan/vulkan_api.h"
#include "loaders/modules/glsl/glsl_reader.h"

#include "EngineManager.h"
#include "renderer/renderer_api.h"

#include "utilities/Logger.h"

static me::log* ME_LOGGER = new me::log("MurderEngine",
"\e[32m[%N] %T #%M \e[0m",
"\e[32m[%N] %T\e[0m \e[33m#%M \e[0m",
"\e[32m[%N] %T\e[0m \e[31m#%M \e[0m",
"\e[34m[%N] %T #%M \e[0m"
);

std::string engine_name = "Murder Engine";
unsigned int engine_version = 7;
std::string app_name = "Murder Engine Interface";
unsigned int app_version = 1;

std::string RENDERER_API_NAME = "vulkan";
me::frenderer* renderer;
me::shader_program* program;

std::string w_title;
unsigned int w_width, w_height;
bool w_vSync, w_fullscreen;
GLFWwindow* window;

unsigned int fpsCount, fps;
unsigned long current_frame = 0;
bool framebuffer_resized = false;

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

static void framebuffer_resize_callback(GLFWwindow* window, int width, int height)
{
  framebuffer_resized = true;
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
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  window = glfwCreateWindow(width, height, title.c_str(), fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
  glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
  glfwSetCursorPosCallback(window, cursor_position_callback);
  glfwSetScrollCallback(window, scroll_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);
  glfwSetKeyCallback(window, key_callback);
  glfwShowWindow(window);
  glfwSwapInterval(vSync ? 1 : 0);
  return ME_FINE;
}

int me::engine_loop()
{
  while(!glfwWindowShouldClose(window))
  {
    renderer->clearFrame();
    renderer->renderFrame(current_frame, framebuffer_resized);
    for (me::event::engine_event* event : engine_events)
      event->onLoop();
    for (me::event::engine_event* event : engine_events)
      event->onRender();
    glfwSwapBuffers(window);
    glfwPollEvents();
    current_frame++;
  }
  renderer->cleanup();
  glfwDestroyWindow(window);
  glfwTerminate();
  return ME_FINE;
}

int me::engine_load_shaders(const std::string &shader_path)
{
  return ME_FINE;
}

int me::engine_setup_renderer_api(const std::string &apiName, const std::string &shader_filepath)
{
  if (apiName=="opengl") { } // who uses opengl? =P
  else if (apiName=="vulkan")
  {
    renderer = new me::vulkan_api;
  }
  RENDERER_API_NAME = apiName;
  program = new me::shader_program;
  ME_LOGGER->out("Loading shaders ...\n");
  if (me::glsl_reader::read_shader_file(shader_filepath.c_str(), program) != ME_FINE)
    return ME_ERR;
  ME_LOGGER->out("Initializing Renderer API ...\n");
  if (renderer->initializeApi() != ME_FINE)
    return ME_ERR;
  me::device_info info = renderer->getDeviceInfo();
  ME_LOGGER->out("<--- [Device Info] --->\n");
  ME_LOGGER->out(std::string("Renderer API initialized [") + RENDERER_API_NAME + "]\n");
  ME_LOGGER->out(std::string("-- Company: ") + info.company + "\n");
  ME_LOGGER->out(std::string("-- Model: ") + info.model + "\n");
  ME_LOGGER->out(std::string("-- Version: ") + info.version + "\n");
  ME_LOGGER->out(std::string("-- GLSL Version: ") + info.sl_version + "\n");
  return ME_FINE;
}

void* me::get_param(int param)
{
  if (param == ME_INST_PROGRAM)
    return program;
  else if (param == ME_INST_RENDERER)
    return renderer;
  else if (param == ME_INST_CURRENT_FRAME)
    return &current_frame;
  else if (param == ME_INST_FULLSCREEN)
    return &w_fullscreen;
  else if (param == ME_INST_VSYNC)
    return &w_vSync;
  else if (param == ME_INST_WIN_X)
    return nullptr; // TODO:
  else if (param == ME_INST_WIN_Y)
    return nullptr; // TODO:
  else if (param == ME_INST_WIN_WIDTH)
    return &w_width;
  else if (param == ME_INST_WIN_HEIGHT)
    return &w_height;
  else if (param == ME_INST_WINDOW)
    return window;
  else if (param == ME_INST_WIN_TITLE)
    return &w_title;
  else if (param == ME_INST_FRAMEBUFFER_RESIZED)
    return &framebuffer_resized;
  return nullptr;
}
int me::set_param(int param, void* value)
{
  // TODO:
  if (param == ME_INST_FRAMEBUFFER_RESIZED)
  {
    framebuffer_resized = *((bool*)value);
    return ME_FINE;
  }
  return ME_ERR;
}
