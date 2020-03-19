#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <vector>
#include <string>

#include "MurderEngine.h"
#include "EngineManager.h"
#include "renderer/RendererApi.h"
#include "renderer/OpenGLApi.h"

#include "utilities/Logger.h"

std::string RENDERER_API_NAME = "opengl";
IRendererApi* RENDERER_API;

std::string w_title;
unsigned int w_width, w_height;
bool w_vSync, w_fullscreen;
GLFWwindow* window;
std::vector<me::scene*> scenes;

unsigned int fpsCount, fps;

me::log* ME_LOGGER = new me::log("MurderEngine", "\e[32m[%N] %T #%M \e[0m");

std::vector<IEngineEvent*> events;

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
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
}


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
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
  RENDERER_API->initializeApi()
  while(!glfwWindowShouldClose(window))
  {
    RENDERER_API->clear();
    for (IEngineEvent* event : events)
      event->onLoop();
    for (me::scene* scene : scenes)
      scene->updateScene();
    for (me::scene* scene : scenes)
      scene->renderScene();
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
    RENDERER_API = new OpenGLApi();
  else if (apiName=="vulkan") { }
  RENDERER_API_NAME = apiName;
  return 0;
}

int me::engine_register_scene(me::scene* scene)
{
  scenes.push_back(scene);
}

int me::engine_unregister_scene(me::scene* scene)
{
  // TODO:
}

void me::engine_window_size(unsigned int* width, unsigned int* height)
{
  *width = w_width;
  *height = w_height;
}
