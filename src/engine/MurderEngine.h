#ifndef MURDER_ENGINE
  #define MURDER_ENGINE

#define ME_FILE_FORMAT_RAW                   0x1

#define ME_FILE_FORMAT_PNG                   0x48
#define ME_FILE_FORMAT_JPEG                  0x49
#define ME_FILE_FORMAT_GIF                   0x50
#define ME_FILE_FORMAT_BMP                   0x51

#define ME_FILE_FORMAT_MP3                   0x65
#define ME_FILE_FORMAT_WAVE                  0x64
#define ME_FILE_FORMAT_OGG                   0x66
#define ME_FILE_FORMAT_FLAC                  0x67
#define ME_FILE_FORMAT_ALAC                  0x68

#define ME_TEX_FORMAT_RGBA8                  0x1238
#define ME_TEX_FORMAT_RGBA16                 0x12316
#define ME_TEX_FORMAT_RGBA24                 0x12324
#define ME_TEX_FORMAT_RGBA32                 0x12332
#define ME_TEX_FORMAT_RGB8                   0x128
#define ME_TEX_FORMAT_RGB16                  0x1216
#define ME_TEX_FORMAT_RGB24                  0x1224
#define ME_TEX_FORMAT_RGB32                  0x1232
#define ME_TEX_FORMAT_GRAY8                  0x18
#define ME_TEX_FORMAT_GRAY16                 0x116
#define ME_TEX_FORMAT_GRAY24                 0x124
#define ME_TEX_FORMAT_GRAY32                 0x132
#define ME_TEX_FORMAT_BINARY                 0x11

#define ME_MOUSE_LEFT_BUTTON                            0x54
#define ME_MOUSE_MIDDLE_BUTTON                          0x55
#define ME_MOUSE_RIGHT_BUTTON                           0x56

#define ME_KEY_A                                        0x65
#define ME_KEY_B                                        0x66
#define ME_KEY_C                                        0x67
#define ME_KEY_D                                        0x68
#define ME_KEY_E                                        0x69
#define ME_KEY_F                                        0x70
#define ME_KEY_G                                        0x71
#define ME_KEY_H                                        0x72
#define ME_KEY_I                                        0x73
#define ME_KEY_J                                        0x74
#define ME_KEY_K                                        0x75
#define ME_KEY_L                                        0x76
#define ME_KEY_M                                        0x77
#define ME_KEY_N                                        0x78
#define ME_KEY_O                                        0x79
#define ME_KEY_P                                        0x80
#define ME_KEY_Q                                        0x81
#define ME_KEY_R                                        0x82
#define ME_KEY_S                                        0x83
#define ME_KEY_T                                        0x84
#define ME_KEY_U                                        0x85
#define ME_KEY_V                                        0x86
#define ME_KEY_W                                        0x87
#define ME_KEY_X                                        0x88
#define ME_KEY_Y                                        0x89
#define ME_KEY_Z                                        0x90

#define ME_KEY_0                                        0x91
#define ME_KEY_1                                        0x92
#define ME_KEY_2                                        0x93
#define ME_KEY_3                                        0x94
#define ME_KEY_4                                        0x95
#define ME_KEY_5                                        0x96
#define ME_KEY_6                                        0x97
#define ME_KEY_7                                        0x98
#define ME_KEY_8                                        0x99
#define ME_KEY_9                                        0x100

#define ME_SHADER_VERTEX                                0x234
#define ME_SHADER_FRAGMENT                              0x235

#define ME_TEXTURE_2D                                   0x355
#define ME_TEXTURE_3D                                   0x356

#include "scene/scene.h"

class IEngineEvent {

public:

  virtual void onRender() = 0;
  virtual void onLoop() = 0;

  virtual void onMouseInput(int action, double posX, double posY, int button) = 0;
  virtual void onKeyInput(int action, int key) = 0;

};

namespace me {

  int engine_register_event(IEngineEvent* event);
  int engine_init();
  int engine_window(std::string title, unsigned int width, unsigned int height, bool vSync, bool fullscreen);
  int engine_loop();
  int engine_setup_renderer_api(std::string apiName);
  int engine_register_scene(me::scene* scene);
  int engine_unregister_scene(me::scene* scene);

  void engine_window_size(unsigned int* width, unsigned int* height);

};

#endif
