#ifndef MURDER_ENGINE_HPP
  #define MURDER_ENGINE_HPP

#include "kernel/common.hpp"
#include "kernel/variable.hpp"
// #include "math/maths.hpp"

/* utilities */
#include <vector>
#include <map>
#include <set>

/* renderer stuff */
enum MeRendererAPI {
  ME_VULKAN = 0,
  ME_OPENGL = 1,
  ME_DIRECTX = 2,
  ME_METAL = 3,
  ME_GLES = 4
};

/* other stuff */
enum MeCommandName {
  ME_RENDER_FRAME_FUNC = 4,
  ME_POLL_EVENTS_FUNC = 5,
  ME_POLL_WINDOW_EVENTS_FUNC = 6,
  ME_SWAP_BUFFERS_FUNC = 7,
  ME_IDLE_FUNC = 8,
  ME_PULL_FUNCTION_FUNC = 9
};

/* hardware stuff */
enum MeDeviceType {
  DEV_KEYBOARD,
  DEV_MOUSE,
  DEV_GAMEPAD,
  DEV_JOYSTICK
};

struct MeInstance;
struct MeWindow;
struct MeRenderer;
struct MeFrameBuffer;
struct MeScene;
struct MeCommandBuffer;
struct MeCommand;
struct MeShaderProgram;
struct MeInstanceInfo;
struct MeWindowInfo;
struct MeRendererInfo;

#include "scene/scene.hpp"

struct MeCommand {
  MeCommandName name;

  MeCommand(MeCommandName name)
  {
    this->name = name;
  }

  MeResult execute(MeInstance* instance);

};

struct MeShader {
  uint32_t shaderID;
  uint8_t shaderType;
};

struct MeShaderProgram {
  uint32_t programID;
  struct {
    uint32_t
      projection,
      view,
      model;
  } locations;

  void loadLocations(MeRenderer* renderer);

};

struct MeShaders {
  std::string source;
  std::map<std::string, me::Var> variables;
  std::map<std::string, uint32_t> locations;
  MeShaderProgram program_final;
  MeShaderProgram program_ui;
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
  MeShaders* shaders;
  uint32_t frameBuffCap;
};

struct MeWindow {
  MeWindowInfo* info;
  void* window;

  bool framebufferResized;
  uint32_t width, height;

  void destroy();
  bool shouldClose();

};

struct MeRenderer {

  MeRendererAPI api;
  MeShaders* shaders;
  MeFrameBuffer* frameBuffer;

  virtual int initializeApi(MeInstance* instance) = 0;
  virtual int compileShader(const std::string &source, uint8_t type, MeShader &shader) = 0;
  virtual int makeShaderProgram(MeShader* shaders, uint8_t count, MeShaderProgram &program) = 0;
  virtual int makeFrameBuffer(MeFrameBuffer** frameBuffer, uint32_t capacity) = 0;

  virtual int uniform1f(int location, float* f, uint32_t count = 1) = 0;
  virtual int uniform2f(int location, me::vec2* vec, uint32_t count = 1) = 0;
  virtual int uniform3f(int location, me::vec3* vec, uint32_t count = 1) = 0;
  virtual int uniform4f(int location, me::vec4* vec, uint32_t count = 1) = 0;

  virtual int uniform1i(int location, int* i, uint32_t count = 1) = 0;
  virtual int uniform2i(int location, me::vec2i* vec, uint32_t count = 1) = 0;
  virtual int uniform3i(int location, me::vec3i* vec, uint32_t count = 1) = 0;
  virtual int uniform4i(int location, me::vec4i* vec, uint32_t count = 1) = 0;

  virtual int uniform1ui(int location, uint32_t* i, uint32_t count = 1) = 0;
  virtual int uniform2ui(int location, me::vec2ui* vec, uint32_t count = 1) = 0;
  virtual int uniform3ui(int location, me::vec3ui* vec, uint32_t count = 1) = 0;
  virtual int uniform4ui(int location, me::vec4ui* vec, uint32_t count = 1) = 0;

  virtual int uniformMat2x2(int location, real_t* mat, uint32_t count = 1) = 0;
  virtual int uniformMat3x3(int location, real_t* mat, uint32_t count = 1) = 0;
  virtual int uniformMat4x4(int location, real_t* mat, uint32_t count = 1) = 0;
  virtual int uniformMat2x3(int location, real_t* mat, uint32_t count = 1) = 0;
  virtual int uniformMat3x2(int location, real_t* mat, uint32_t count = 1) = 0;
  virtual int uniformMat2x4(int location, real_t* mat, uint32_t count = 1) = 0;
  virtual int uniformMat4x2(int location, real_t* mat, uint32_t count = 1) = 0;
  virtual int uniformMat3x4(int location, real_t* mat, uint32_t count = 1) = 0;
  virtual int uniformMat4x3(int location, real_t* mat, uint32_t count = 1) = 0;

  virtual uint32_t uniformLocation(MeShaderProgram* program, const char* str) = 0;

  virtual int pushMesh(me::Mesh* mesh) = 0;
  virtual int pullMesh(me::Mesh* mesh) = 0;

  virtual int pushImage(me::Image* image) = 0;
  virtual int pullImage(me::Image* image) = 0;

  virtual int renderFrame(MeInstance* instance, unsigned long current_frame, bool &framebuffer_resized) = 0;
  virtual int cleanup() = 0;

};

struct MeFrameBuffer {

  MeShaderProgram* program;

  virtual int useProgram(MeShaderProgram* program) = 0;

};

struct MeScene {
  virtual int MeScene_initialize(MeInstance* instance) = 0;
  virtual int MeScene_finalize(MeInstance* instance) = 0;
  virtual int MeScene_tick(MeInstance* instance) = 0;
  virtual int MeScene_render(MeRenderer* renderer, MeFrameBuffer* frameBuffer, unsigned long current_frame, bool &framebuffer_resized) = 0;

  /*
    action {
      0: pressed,
      1: released,
      2: move,
      3: scroll
    }
  */
  virtual int MeScene_input(MeInstance* instance, MeDeviceType deviceType, uint8_t action, uint8_t keyCode, double x = 0.0D, double y = 0.0D) = 0;
};

template<typename T>
struct MeMemPool {
  std::vector<T> items;

  void push(T item)
  {
    items.push_back(item);
  }

  void pull(T item)
  {
    items.erase(item);
  }

};

struct MeInstance {
  MeInstanceInfo* info;
  MeWindow* window;
  MeRenderer* renderer;
  MeCommandBuffer* commandBuffer;
  struct {
    std::set<uint8_t> pressedKeys;
    std::set<uint8_t> pressedButtons;
    double cursorX, cursorY;
  } inputInfo;
  std::vector<MeScene*> scenes;

  MeMemPool<me::Image*> memPool_textures;
  MeMemPool<me::Material*> memPool_materials;
  MeMemPool<me::Mesh*> memPool_meshes;

  uint64_t currentFrame = 0;

  bool shouldExit();

};

typedef void (*MeEventFunc)();

MeResult meInitInstance(MeInstanceInfo* info, MeInstance* instance);
MeResult meInitWindow(MeInstance* instance, MeWindowInfo* info, MeWindow* window);
MeResult meInitRenderer(MeInstance* instance, MeRendererInfo* info);
MeResult meInitCommandBuffer(MeInstance* instance, MeCommandBuffer* commandBuffer);
MeResult meRunLoop(MeInstance* instance);

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
