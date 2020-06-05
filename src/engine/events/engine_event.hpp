#ifndef ENGINE_EVENT_H
  #define ENGINE_EVENT_H

enum MeKey {

  ME_KEY_NONE =                                         -1,

  ME_KEY_SPACE =                                        32,

  ME_KEY_A =                                            65,
  ME_KEY_B =                                            66,
  ME_KEY_C =                                            67,
  ME_KEY_D =                                            68,
  ME_KEY_E =                                            69,
  ME_KEY_F =                                            70,
  ME_KEY_G =                                            71,
  ME_KEY_H =                                            72,
  ME_KEY_I =                                            73,
  ME_KEY_J =                                            74,
  ME_KEY_K =                                            75,
  ME_KEY_L =                                            76,
  ME_KEY_M =                                            77,
  ME_KEY_N =                                            78,
  ME_KEY_O =                                            79,
  ME_KEY_P =                                            80,
  ME_KEY_Q =                                            81,
  ME_KEY_R =                                            82,
  ME_KEY_S =                                            83,
  ME_KEY_T =                                            84,
  ME_KEY_U =                                            85,
  ME_KEY_V =                                            86,
  ME_KEY_W =                                            87,
  ME_KEY_X =                                            88,
  ME_KEY_Y =                                            89,
  ME_KEY_Z =                                            90,

  ME_KEY_0 =                                            91,
  ME_KEY_1 =                                            92,
  ME_KEY_2 =                                            93,
  ME_KEY_3 =                                            94,
  ME_KEY_4 =                                            95,
  ME_KEY_5 =                                            96,
  ME_KEY_6 =                                            97,
  ME_KEY_7 =                                            98,
  ME_KEY_8 =                                            99,
  ME_KEY_9 =                                            100,

  ME_KEY_RIGHT =                                        262,
  ME_KEY_LEFT =                                         263,
  ME_KEY_DOWN =                                         264,
  ME_KEY_UP =                                           265,

  ME_MOUSE_LEFT_BUTTON =                                76697084,
  ME_MOUSE_MIDDLE_BUTTON =                              777368,
  ME_MOUSE_RIGHT_BUTTON =                               827184,

  ME_PRESS =                                            154,
  ME_RELEASE =                                          155,
  ME_REPEAT =                                           158,
  ME_MOUSE_MOVE =                                       167,
  ME_MOUSE_SCROLL =                                     168
};

enum MeInputType {
  ME_KEYBOARD =                                         286,
  ME_MOUSE =                                            287,
  ME_JOYSTICK =                                         289,
  ME_GAME_CONTROLLER =                                  290,
  ME_INPUT_TYPE_OTHER =                                 291
};

struct MeInputEventContext {

  MeInstance* instance;
  double cursorX, cursorY;
  std::map<int, bool> pressed;

};

struct MeEngineEvent {

  virtual void onPreInit(MeInstance* instance) = 0;
  virtual void onInit(MeInstance* instance) = 0;
  virtual void onDestroyed(MeInstance* instance) = 0;

  virtual void onLoop(MeInstance* instance) = 0;
  virtual void onRender(MeRenderer* renderer) = 0;

  virtual bool onMouseInput(MeInputEventContext* context, int action, double posX, double posY, int button) = 0;
  virtual bool onKeyInput(MeInputEventContext* context, int action, int key) = 0;

  static MeKey fromGLFW(int i, MeInputType type)
  {
    if (i==0 && type==ME_MOUSE)
      return ME_MOUSE_LEFT_BUTTON;
    else if (i==2 && type==ME_MOUSE)
      return ME_MOUSE_MIDDLE_BUTTON;
    else if (i==1 && type==ME_MOUSE)
      return ME_MOUSE_RIGHT_BUTTON;
    else if (i==1)
      return ME_PRESS;
    else if (i==0)
      return ME_RELEASE;
    else if (i==2)
      return ME_REPEAT;
    return ME_KEY_NONE;
  }

};

#endif
