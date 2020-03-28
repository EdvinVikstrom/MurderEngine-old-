#ifndef VECTORS_H
  #define VECTORS_H

namespace me {

  /* float */
  struct vec2f {
    float x, y;
    vec2f() { }
    vec2f(float x, float y);

    void add(me::vec2f &vec);
    void sub(me::vec2f &vec);
    void mul(me::vec2f &vec);
    void div(me::vec2f &vec);

  };
  struct vec3f {
    float x, y, z;
    vec3f() { }
    vec3f(float x, float y, float z);

    void add(me::vec3f &vec);
    void sub(me::vec3f &vec);
    void mul(me::vec3f &vec);
    void div(me::vec3f &vec);

  };
  struct vec4f {
    float x, y, z, w;
    vec4f() { }
    vec4f(float x, float y, float z, float w);

    void add(me::vec4f &vec);
    void sub(me::vec4f &vec);
    void mul(me::vec4f &vec);
    void div(me::vec4f &vec);

  };

  /* double */
  struct vec2d {
    double x, y;
    vec2d() { }
    vec2d(double x, double y);

    void add(me::vec2d &vec);
    void sub(me::vec2d &vec);
    void mul(me::vec2d &vec);
    void div(me::vec2d &vec);

  };
  struct vec3d {
    double x, y, z;
    vec3d() { }
    vec3d(double x, double y, double z);

    void add(me::vec3d &vec);
    void sub(me::vec3d &vec);
    void mul(me::vec3d &vec);
    void div(me::vec3d &vec);

  };
  struct vec4d {
    double x, y, z, w;
    vec4d() { }
    vec4d(double x, double y, double z, double w);

    void add(me::vec4d &vec);
    void sub(me::vec4d &vec);
    void mul(me::vec4d &vec);
    void div(me::vec4d &vec);

  };

  /* double */
  struct vec2i {
    int x, y;
    vec2i() { }
    vec2i(int x, int y);

    void add(me::vec2i &vec);
    void sub(me::vec2i &vec);
    void mul(me::vec2i &vec);
    void div(me::vec2i &vec);

  };
  struct vec3i {
    int x, y, z;
    vec3i() { }
    vec3i(int x, int y, int z);

    void add(me::vec3i &vec);
    void sub(me::vec3i &vec);
    void mul(me::vec3i &vec);
    void div(me::vec3i &vec);

  };
  struct vec4i {
    int x, y, z, w;
    vec4i() { }
    vec4i(int x, int y, int z, int w);

    void add(me::vec4i &vec);
    void sub(me::vec4i &vec);
    void mul(me::vec4i &vec);
    void div(me::vec4i &vec);

  };

  /* utilities */
  void toVec2f(float* array, me::vec2f* dest, unsigned int count);
  void toVec3f(float* array, me::vec3f* dest, unsigned int count);
  void toVec4f(float* array, me::vec4f* dest, unsigned int count);

  void toVec2d(double* array, me::vec2d* dest, unsigned int count);
  void toVec3d(double* array, me::vec3d* dest, unsigned int count);
  void toVec4d(double* array, me::vec4d* dest, unsigned int count);

  void toVec2i(int* array, me::vec2i* dest, unsigned int count);
  void toVec3i(int* array, me::vec3i* dest, unsigned int count);
  void toVec4i(int* array, me::vec4i* dest, unsigned int count);

  void randomVec2f(float length, me::vec2f &vec);
  void randomVec3f(float length, me::vec3f &vec);
  void randomVec4f(float length, me::vec4f &vec);

  void randomVec2d(double length, me::vec2d &vec);
  void randomVec3d(double length, me::vec3d &vec);
  void randomVec4d(double length, me::vec4d &vec);

  void randomVec2i(int length, me::vec2i &vec);
  void randomVec3i(int length, me::vec3i &vec);
  void randomVec4i(int length, me::vec4i &vec);

};

#endif
