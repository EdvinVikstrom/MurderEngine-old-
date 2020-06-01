#ifndef MURDER_ENGINE_H
  #define MURDER_ENGINE_H

#include "kernel/kernel.h"

/* utilities */
#include <vector>
#include <map>

enum MeShaderType {
  VERTEX = 0,
  TESSELLATION = 1,
  GEOMETRY = 2,
  RASTERIZATION = 3,
  FRAGMENT = 4,
  COLOR_BLENDING = 5,
  UNKNOWN_SHADER = -1
};

enum MeRendererAPI {
  ME_VULKAN = 0,
  ME_OPENGL = 1,
  ME_DIRECTX = 2,
  ME_METAL = 3,
  ME_GLES = 4
};

enum MeCommandName {
  ME_RENDER_FRAME_FUNC = 4,
  ME_POLL_EVENTS_FUNC = 5,
  ME_POLL_WINDOW_EVENTS_FUNC = 6,
  ME_SWAP_BUFFERS_FUNC = 7,
  ME_IDLE_FUNC = 8,
  ME_PULL_FUNCTION_FUNC = 9
};

struct MeInstance;
struct MeWindow;
struct MeRenderer;
struct MeCommandBuffer;
struct MeCommand;
struct MeShaderProgram;
struct MeInstanceInfo;
struct MeWindowInfo;
struct MeRendererInfo;

/* events */
#include "events/engine_event.h"

/* meshes, textures ... */
#include "scene/scene_content.h"

struct MeCommand {
  MeCommandName name;

  MeCommand(MeCommandName name)
  {
    this->name = name;
  }

  MeResult execute(MeInstance* instance);

};

struct MeShaderProgram {

  static const uint32_t MAX_LIGHTS = 8;
  static const uint32_t MAX_TEXTURES = 8;

  int projLoc = 0, viewLoc = 1, modelLoc = 2;
  int lightLoc = 3;
  int texLoc = 11;

  std::map<MeShaderType, std::string> shaders;
};

struct MeCommandBuffer {
  std::vector<MeCommand> commands;
  bool recording;
};

struct MeInstanceInfo {
  const char* appName;
  uint32_t appVersion;
};

struct MeWindowInfo {
  std::string title;
  uint32_t width, height;
  int posX, posY;
  int monitor;
};

struct MeRendererInfo {
  MeRendererAPI api;
  MeShaderProgram* shaderProgram;
  #define MESH_BUFF_CAP 2048
};

struct MeWindow {
  MeWindowInfo* info;
  void* window;

  bool framebufferResized;

  void destroy();
  bool shouldClose();

};

struct MeRenderer {

  MeRendererInfo* info;

  virtual int initializeApi(MeInstance* instance) = 0;

  virtual int uniformMatrix4(int location, me::maths::mat4 matrix) = 0;
  virtual int uniformVec2(int location, me::vec2 vec) = 0;
  virtual int uniformVec3(int location, me::vec3 vec) = 0;
  virtual int uniformVec4(int location, me::vec4 vec) = 0;

  virtual int pushMesh(me::Mesh* mesh);
  virtual int pullMesh(me::Mesh* mesh);

  virtual int renderFrame(MeInstance* instance, unsigned long current_frame, bool &framebuffer_resized) = 0;
  virtual int cleanup() = 0;

};

struct MeInstance {
  MeInstanceInfo* info;
  MeWindow* window;
  MeRenderer* renderer;
  MeCommandBuffer* commandBuffer;
  MeInputEventContext* inputContext;
  std::vector<MeEngineEvent*> events;

  struct Storage {
    std::vector<me::Mesh*> meshes;
    std::vector<me::Image*> images;
    std::vector<me::Material*> materials;

    bool registerItem(uint8_t type, void* ptr)
    {
      if (type == 0) meshes.push_back((me::Mesh*) ptr);
      else if (type == 1) images.push_back((me::Image*) ptr);
      else if (type == 2) materials.push_back((me::Material*) ptr);
      else
        return false;
      return true;
    }

  } storage;

  uint64_t currentFrame = 0;

  bool shouldExit();

};

typedef void (*MeEventFunc)();

MeResult meInitInstance(MeInstanceInfo* info, MeInstance* instance);
MeResult meInitWindow(MeInstance* instance, MeWindowInfo* info, MeWindow* window);
MeResult meInitRenderer(MeInstance* instance, MeRendererInfo* info);
MeResult meInitCommandBuffer(MeInstance* instance, MeCommandBuffer* commandBuffer);
MeResult meRunLoop(MeInstance* instance);

MeResult meLoadShaders(const char* filepath, MeShaderProgram* shaderProgram);

MeResult meRegisterEvent(MeInstance* instance, MeEngineEvent* event);

void meStartRecord(MeCommandBuffer* commandBuffer);
void meStopRecord(MeCommandBuffer* commandBuffer);

/* commands */
void meRenderFrame(MeCommandBuffer* commandBuffer);
void mePollEvents(MeCommandBuffer* commandBuffer);
void mePollWindowEvents(MeCommandBuffer* commandBuffer);
void meSwapBuffers(MeCommandBuffer* commandBuffer);
void meIdle(MeCommandBuffer* commandBuffer);
void mePullFunction(MeCommandBuffer* commandBuffer);

/* cleanup */
void meDestroyInstance(MeInstance* instance);
void meDestroyWindow(MeWindow* window);
void meDestroyRenderer(MeRenderer* renderer);

#endif
