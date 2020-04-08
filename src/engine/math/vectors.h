#ifndef ME_VECTORS_H
  #define ME_VECTORS_H

#include "maths.h"

namespace me {

  enum vec_type {
    VEC2, VEC3, VEC4,
  };

  template<typename T>
  struct vector {

    vector() { }

    virtual int axis() = 0;
    virtual T& at(unsigned int index) = 0;

    inline T& operator[](unsigned int index)
    {
      return at(index);
    }

    inline vector<T>& add(vector<T> &vec)
    {
      for (unsigned int i = 0; i < maths::max(axis(), vec.axis()); i++)
        at(i % axis())+=vec[i % vec.axis()];
      return *this;
    }
    inline vector<T>& add(T value)
    {
      for (unsigned int i = 0; i < axis(); i++)
        at(i)+=value;
      return *this;
    }
    inline vector<T>& sub(vector<T> &vec)
    {
      for (unsigned int i = 0; i < maths::max(axis(), vec.axis()); i++)
        at(i % axis())-=vec[i % vec.axis()];
      return *this;
    }
    inline vector<T>& sub(T value)
    {
      for (unsigned int i = 0; i < axis(); i++)
        at(i)-=value;
      return *this;
    }
    inline vector<T>& mul(vector<T> &vec)
    {
      for (unsigned int i = 0; i < maths::max(axis(), vec.axis()); i++)
        at(i % axis())*=vec[i % vec.axis()];
      return *this;
    }
    inline vector<T>& mul(T value)
    {
      for (unsigned int i = 0; i < axis(); i++)
        at(i)*=value;
      return *this;
    }
    inline vector<T>& div(T value)
    {
      for (unsigned int i = 0; i < axis(); i++)
        at(i)/=value;
      return *this;
    }
    inline vector<T>& div(vector<T> &vec)
    {
      for (unsigned int i = 0; i < maths::max(axis(), vec.axis()); i++)
        at(i % axis())/=vec[i % vec.axis()];
      return *this;
    }

    virtual T lengthSquared() { return T(0); }
    virtual T length() { return T(0); };
    virtual vector<T>& normalize() { return *this; };

    inline vector<T>& operator+(vector &vec)
    {
      return add(vec);
    }
    inline vector<T>& operator+(T value)
    {
      return add(value);
    }
    inline vector<T>& operator-(vector &vec)
    {
      return sub(vec);
    }
    inline vector<T>& operator-(T value)
    {
      return sub(value);
    }
    inline vector<T>& operator*(vector &vec)
    {
      return mul(vec);
    }
    inline vector<T>& operator*(T value)
    {
      return mul(value);
    }
    inline vector<T>& operator/(vector &vec)
    {
      return div(vec);
    }
    inline vector<T>& operator/(T value)
    {
      return div(value);
    }

  };

  static float deff = 0.0F;
  static double defd = 0.0D;
  static int defi = 0;

  struct vec2f : vector<float> {
    float x, y;
    vec2f()
    {
      this->x = 0.0F;
      this->y = 0.0F;
    }
    vec2f(float x, float y) : vector()
    {
      this->x = x;
      this->y = y;
    }
    vec2f(float value) : vector()
    {
      vec2f(value, value);
    }
    vec2f(vector<float> &vec) : vector()
    {
      this->x = vec.at(0);
      this->y = vec.at(1);
    }
    int axis() override
    {
      return 2;
    }
    float& at(unsigned int index) override
    {
      if (index==0) return x;
      else if (index==1) return y;
      return deff;
    }
    float lengthSquared() override
    {
      return x * x + y * y;
    }
    float length() override
    {
      return me::maths::sqrt(lengthSquared());
    }
    vector<float>& normalize() override
    {
      float len = 1.0F / length();
      x = x * len;
      y = y * len;
      return *this;
    }
  };
  struct vec3f : vector<float> {
    float x, y, z;
    vec3f()
    {
      this->x = 0.0F;
      this->y = 0.0F;
      this->z = 0.0F;
    }
    vec3f(float x, float y, float z) : vector()
    {
      this->x = x;
      this->y = y;
      this->z = z;
    }
    vec3f(float value) : vector()
    {
      vec3f(value, value, value);
    }
    vec3f(vector<float> &vec) : vector()
    {
      this->x = vec.at(0);
      this->y = vec.at(1);
      this->z = vec.at(2);
    }
    int axis() override
    {
      return 3;
    }
    float& at(unsigned int index) override
    {
      if (index==0) return x;
      else if (index==1) return y;
      else if (index==2) return z;
      return deff;
    }
    float lengthSquared() override
    {
      return x * x + y * y + z * z;
    }
    float length() override
    {
      return me::maths::sqrt(lengthSquared());
    }
    vector<float>& normalize() override
    {
      float len = 1.0F / length();
      x = x * len;
      y = y * len;
      z = z * len;
      return *this;
    }
  };
  struct vec4f : vector<float> {
    float x, y, z, w;
    vec4f()
    {
      this->x = 0.0F;
      this->y = 0.0F;
      this->z = 0.0F;
      this->w = 0.0F;
    }
    vec4f(float x, float y, float z, float w) : vector()
    {
      this->x = x;
      this->y = y;
      this->z = z;
      this->w = w;
    }
    vec4f(float value) : vector()
    {
      vec4f(value, value, value, value);
    }
    vec4f(vector<float> &vec) : vector()
    {
      this->x = vec.at(0);
      this->y = vec.at(1);
      this->z = vec.at(2);
      this->w = vec.at(3);
    }
    int axis() override
    {
      return 4;
    }
    float& at(unsigned int index) override
    {
      if (index==0) return x;
      else if (index==1) return y;
      else if (index==2) return z;
      else if (index==3) return w;
      return deff;
    }
    float lengthSquared() override
    {
      return x * x + y * y + z * z + w * w;
    }
    float length() override
    {
      return me::maths::sqrt(lengthSquared());
    }
    vector<float>& normalize() override
    {
      float len = 1.0F / length();
      x = x * len;
      y = y * len;
      z = z * len;
      w = w * len;
      return *this;
    }
  };

  struct vec2d : vector<double> {
    double x, y;
    vec2d()
    {
      this->x = 0.0D;
      this->y = 0.0D;
    }
    vec2d(double x, double y) : vector()
    {
      this->x = x;
      this->y = y;
    }
    vec2d(double value) : vector()
    {
      vec2d(value, value);
    }
    vec2d(vector<double> &vec) : vector()
    {
      this->x = vec.at(0);
      this->y = vec.at(1);
    }
    int axis() override
    {
      return 2;
    }
    double& at(unsigned int index) override
    {
      if (index==0) return x;
      else if (index==1) return y;
      return defd;
    }
    double lengthSquared() override
    {
      return x * x + y * y;
    }
    double length() override
    {
      return me::maths::sqrt(lengthSquared());
    }
    vector<double>& normalize() override
    {
      double len = 1.0D / length();
      x = x * len;
      y = y * len;
      return *this;
    }
  };
  struct vec3d : vector<double> {
    double x, y, z;
    vec3d()
    {
      this->x = 0.0D;
      this->y = 0.0D;
      this->z = 0.0D;
    }
    vec3d(double x, double y, double z) : vector()
    {
      this->x = x;
      this->y = y;
      this->z = z;
    }
    vec3d(double value) : vector()
    {
      vec3d(value, value, value);
    }
    vec3d(vector<double> &vec) : vector()
    {
      this->x = vec.at(0);
      this->y = vec.at(1);
      this->z = vec.at(2);
    }
    int axis() override
    {
      return 3;
    }
    double& at(unsigned int index) override
    {
      if (index==0) return x;
      else if (index==1) return y;
      else if (index==2) return z;
      return defd;
    }
    double lengthSquared() override
    {
      return x * x + y * y + z * z;
    }
    double length() override
    {
      return me::maths::sqrt(lengthSquared());
    }
    vector<double>& normalize() override
    {
      double len = 1.0D / length();
      x = x * len;
      y = y * len;
      z = z * len;
      return *this;
    }
  };
  struct vec4d : vector<double> {
    double x, y, z, w;
    vec4d()
    {
      this->x = 0.0D;
      this->y = 0.0D;
      this->z = 0.0D;
      this->w = 0.0D;
    }
    vec4d(double x, double y, double z, double w) : vector()
    {
      this->x = x;
      this->y = y;
      this->z = z;
      this->w = w;
    }
    vec4d(double value) : vector()
    {
      vec4d(value, value, value, value);
    }
    vec4d(vector<double> &vec) : vector()
    {
      this->x = vec.at(0);
      this->y = vec.at(1);
      this->z = vec.at(2);
      this->w = vec.at(3);
    }
    int axis() override
    {
      return 4;
    }
    double& at(unsigned int index) override
    {
      if (index==0) return x;
      else if (index==1) return y;
      else if (index==2) return z;
      else if (index==3) return w;
      return defd;
    }
    double lengthSquared() override
    {
      return x * x + y * y + z * z + w * w;
    }
    double length() override
    {
      return me::maths::sqrt(lengthSquared());
    }
    vector<double>& normalize() override
    {
      double len = 1.0D / length();
      x = x * len;
      y = y * len;
      z = z * len;
      w = w * len;
      return *this;
    }
  };

  struct vec2i : vector<int> {
    int x, y;
    vec2i()
    {
      this->x = 0;
      this->y = 0;
    }
    vec2i(int x, int y) : vector()
    {
      this->x = x;
      this->y = y;
    }
    vec2i(int value) : vector()
    {
      vec2i(value, value);
    }
    vec2i(vector<int> &vec) : vector()
    {
      this->x = vec.at(0);
      this->y = vec.at(1);
    }
    int axis() override
    {
      return 2;
    }
    int& at(unsigned int index) override
    {
      if (index==0) return x;
      else if (index==1) return y;
      return defi;
    }
  };
  struct vec3i : vector<int> {
    int x, y, z;
    vec3i()
    {
      this->x = 0;
      this->y = 0;
      this->z = 0;
    }
    vec3i(int x, int y, int z) : vector()
    {
      this->x = x;
      this->y = y;
      this->z = z;
    }
    vec3i(int value) : vector()
    {
      vec3i(value, value, value);
    }
    vec3i(vector<int> &vec) : vector()
    {
      this->x = vec.at(0);
      this->y = vec.at(1);
      this->z = vec.at(2);
    }
    int axis() override
    {
      return 3;
    }
    int& at(unsigned int index) override
    {
      if (index==0) return x;
      else if (index==1) return y;
      else if (index==2) return z;
      return defi;
    }
  };
  struct vec4i : vector<int> {
    int x, y, z, w;
    vec4i()
    {
      this->x = 0;
      this->y = 0;
      this->z = 0;
      this->w = 0;
    }
    vec4i(int x, int y, int z, int w) : vector()
    {
      this->x = x;
      this->y = y;
      this->z = z;
      this->w = w;
    }
    vec4i(int value) : vector()
    {
      vec4i(value, value, value, value);
    }
    vec4i(vector<int> &vec) : vector()
    {
      this->x = vec.at(0);
      this->y = vec.at(1);
      this->z = vec.at(2);
      this->w = vec.at(3);
    }
    int axis() override
    {
      return 4;
    }
    int& at(unsigned int index) override
    {
      if (index==0) return x;
      else if (index==1) return y;
      else if (index==2) return z;
      else if (index==3) return w;
      return defi;
    }
  };

};

#endif
