#ifndef ME_VECTORS_H
  #define ME_VECTORS_H

namespace me {

  /* float */
  struct vec2f {
    float x, y;
    vec2f() { }
    vec2f(float x, float y);

    vec2f* add(me::vec2f &vec); vec2f* add(float fac);
    vec2f* sub(me::vec2f &vec); vec2f* sub(float fac);
    vec2f* mul(me::vec2f &vec); vec2f* mul(float fac);
    vec2f* div(me::vec2f &vec); vec2f* div(float fac);
    vec2f* mag(float mag);

    inline bool in_bounds(const me::vec2f &position, const me::vec2f &scale)
    {
      return x >= position.x && x <= position.x + scale.x && y >= position.y && y <= position.y + scale.y;
    }

  };
  struct vec3f {
    float x, y, z;
    vec3f() { }
    vec3f(float x, float y, float z);

    vec3f* add(me::vec3f &vec); vec3f* add(float fac);
    vec3f* sub(me::vec3f &vec); vec3f* sub(float fac);
    vec3f* mul(me::vec3f &vec); vec3f* mul(float fac);
    vec3f* div(me::vec3f &vec); vec3f* div(float fac);
    vec3f* mag(float mag);

    inline bool in_bounds(const me::vec3f &position, const me::vec3f &scale)
    {
      return x >= position.x && x <= position.x + scale.x && y >= position.y && y <= position.y + scale.y && z >= position.z && z <= position.z + scale.z;
    }

  };
  struct vec4f {
    float x, y, z, w;
    vec4f() { }
    vec4f(float x, float y, float z, float w);

    vec4f* add(me::vec4f &vec); vec4f* add(float fac);
    vec4f* sub(me::vec4f &vec); vec4f* sub(float fac);
    vec4f* mul(me::vec4f &vec); vec4f* mul(float fac);
    vec4f* div(me::vec4f &vec); vec4f* div(float fac);
    vec4f* mag(float mag);

  };

  /* double */
  struct vec2d {
    double x, y;
    vec2d() { }
    vec2d(double x, double y);

    vec2d* add(me::vec2d &vec); vec2d* add(double fac);
    vec2d* sub(me::vec2d &vec); vec2d* sub(double fac);
    vec2d* mul(me::vec2d &vec); vec2d* mul(double fac);
    vec2d* div(me::vec2d &vec); vec2d* div(double fac);
    vec2d* mag(double mag);

    inline bool in_bounds(const me::vec2d &position, const me::vec2d &scale)
    {
      return x >= position.x && x <= position.x + scale.x && y >= position.y && y <= position.y + scale.y;
    }

  };
  struct vec3d {
    double x, y, z;
    vec3d() { }
    vec3d(double x, double y, double z);

    vec3d* add(me::vec3d &vec); vec3d* add(double fac);
    vec3d* sub(me::vec3d &vec); vec3d* sub(double fac);
    vec3d* mul(me::vec3d &vec); vec3d* mul(double fac);
    vec3d* div(me::vec3d &vec); vec3d* div(double fac);
    vec3d* mag(double mag);

    inline bool in_bounds(const me::vec3d &position, const me::vec3d &scale)
    {
      return x >= position.x && x <= position.x + scale.x && y >= position.y && y <= position.y + scale.y && z >= position.z && z <= position.z + scale.z;
    }

  };
  struct vec4d {
    double x, y, z, w;
    vec4d() { }
    vec4d(double x, double y, double z, double w);

    vec4d* add(me::vec4d &vec); vec4d* add(double fac);
    vec4d* sub(me::vec4d &vec); vec4d* sub(double fac);
    vec4d* mul(me::vec4d &vec); vec4d* mul(double fac);
    vec4d* div(me::vec4d &vec); vec4d* div(double fac);
    vec4d* mag(double mag);

  };

  /* double */
  struct vec2i {
    int x, y;
    vec2i() { }
    vec2i(int x, int y);

    vec2i* add(me::vec2i &vec); vec2i* add(int fac);
    vec2i* sub(me::vec2i &vec); vec2i* sub(int fac);
    vec2i* mul(me::vec2i &vec); vec2i* mul(int fac);
    vec2i* div(me::vec2i &vec); vec2i* div(int fac);

    inline bool in_bounds(const me::vec2i &position, const me::vec2i &scale)
    {
      return x >= position.x && x <= position.x + scale.x && y >= position.y && y <= position.y + scale.y;
    }

  };
  struct vec3i {
    int x, y, z;
    vec3i() { }
    vec3i(int x, int y, int z);

    vec3i* add(me::vec3i &vec); vec3i* add(int fac);
    vec3i* sub(me::vec3i &vec); vec3i* sub(int fac);
    vec3i* mul(me::vec3i &vec); vec3i* mul(int fac);
    vec3i* div(me::vec3i &vec); vec3i* div(int fac);

    inline bool in_bounds(const me::vec3i &position, const me::vec3i &scale)
    {
      return x >= position.x && x <= position.x + scale.x && y >= position.y && y <= position.y + scale.y && z >= position.z && z <= position.z + scale.z;
    }

  };
  struct vec4i {
    int x, y, z, w;
    vec4i() { }
    vec4i(int x, int y, int z, int w);

    vec4i* add(me::vec4i &vec); vec4i* add(int fac);
    vec4i* sub(me::vec4i &vec); vec4i* sub(int fac);
    vec4i* mul(me::vec4i &vec); vec4i* mul(int fac);
    vec4i* div(me::vec4i &vec); vec4i* div(int fac);

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
