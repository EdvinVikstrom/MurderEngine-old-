#ifndef INPUT_EVENT_H
  #define INPUT_EVENT_H

#define ME_MOUSE_LEFT_BUTTON                            0
#define ME_MOUSE_RIGHT_BUTTON                           1
#define ME_MOUSE_MIDDLE_BUTTON                          2

#define ME_KEY_A                                        65
#define ME_KEY_B                                        66
#define ME_KEY_C                                        67
#define ME_KEY_D                                        68
#define ME_KEY_E                                        69
#define ME_KEY_F                                        70
#define ME_KEY_G                                        71
#define ME_KEY_H                                        72
#define ME_KEY_I                                        73
#define ME_KEY_J                                        74
#define ME_KEY_K                                        75
#define ME_KEY_L                                        76
#define ME_KEY_M                                        77
#define ME_KEY_N                                        78
#define ME_KEY_O                                        79
#define ME_KEY_P                                        80
#define ME_KEY_Q                                        81
#define ME_KEY_R                                        82
#define ME_KEY_S                                        83
#define ME_KEY_T                                        84
#define ME_KEY_U                                        85
#define ME_KEY_V                                        86
#define ME_KEY_W                                        87
#define ME_KEY_X                                        88
#define ME_KEY_Y                                        89
#define ME_KEY_Z                                        90

#define ME_KEY_0                                        91
#define ME_KEY_1                                        92
#define ME_KEY_2                                        93
#define ME_KEY_3                                        94
#define ME_KEY_4                                        95
#define ME_KEY_5                                        96
#define ME_KEY_6                                        97
#define ME_KEY_7                                        98
#define ME_KEY_8                                        99
#define ME_KEY_9                                        100

#define ME_KEY_LEFT_SHIFT                               340

#define ME_PRESS                                        154
#define ME_RELEASE                                      155
#define ME_MOUSE_MOVE                                   167
#define ME_MOUSE_SCROLL                                 168

namespace me {

  namespace event {

    struct input_event {

      virtual bool onMouseInput(int action, double posX, double posY, int button) = 0;
      virtual bool onKeyInput(int action, int key) = 0;

      bool isPressed(int key);

    };

  };

};

#endif
