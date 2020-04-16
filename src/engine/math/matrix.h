#ifndef ME_MATRIX_H
  #define ME_MATRIX_H

#define PROPERTY_PERSPECTIVE          1 << 0;
#define PROPERTY_ORTHONORMAL          1 << 1;
#define PROPERTY_IDENTITY             1 << 2;
#define PROPERTY_AFFINE               1 << 3;
#define PROPERTY_TRANSLATION          1 << 4;

#include "maths.h"

#include <iostream> // remove

namespace me {

  namespace maths {

    /*
    [
        [0]  [1]  [2]  [3]
    [0]  0,   1,   2,   3,
    [1]  4,   5,   6,   7,
    [2]  8,   9,   10,  11,
    [3]  12,  13,  14,  15
    ]
    */

    struct mat4 {

      static const int ROWS = 4, COLUMNS = 4;

      float* array;

      mat4(float* array)
      {
        this->array = array;
      }

      mat4()
      {
        array = new float[ROWS * COLUMNS];
        for (uint32_t i = 0; i < ROWS * COLUMNS; i++)
          array[i] = 0.0F;
        array[0] = 1.0F;
        array[5] = 1.0F;
        array[10] = 1.0F;
        array[15] = 1.0F;
      }

      inline int size()
      {
        return ROWS * COLUMNS;
      }

      inline void m00(float f) { array[0] = f; }
      inline void m01(float f) { array[1] = f; }
      inline void m02(float f) { array[2] = f; }
      inline void m03(float f) { array[3] = f; }
      inline void m10(float f) { array[4] = f; }
      inline void m11(float f) { array[5] = f; }
      inline void m12(float f) { array[6] = f; }
      inline void m13(float f) { array[7] = f; }
      inline void m20(float f) { array[8] = f; }
      inline void m21(float f) { array[9] = f; }
      inline void m22(float f) { array[10] = f; }
      inline void m23(float f) { array[11] = f; }
      inline void m30(float f) { array[12] = f; }
      inline void m31(float f) { array[13] = f; }
      inline void m32(float f) { array[14] = f; }
      inline void m33(float f) { array[15] = f; }

      inline float& m00() { return array[0]; }
      inline float& m01() { return array[0]; }
      inline float& m02() { return array[0]; }
      inline float& m03() { return array[0]; }
      inline float& m10() { return array[0]; }
      inline float& m11() { return array[0]; }
      inline float& m12() { return array[0]; }
      inline float& m13() { return array[0]; }
      inline float& m20() { return array[0]; }
      inline float& m21() { return array[0]; }
      inline float& m22() { return array[0]; }
      inline float& m23() { return array[0]; }
      inline float& m30() { return array[0]; }
      inline float& m31() { return array[0]; }
      inline float& m32() { return array[0]; }
      inline float& m33() { return array[0]; }

      inline void set(mat4 mat)
      {
        for (uint32_t i = 0; i < mat.size(); i++)
          array[i] = mat[i];
      }

      float& at(unsigned int row, unsigned int col)
      {
        return array[(row*ROWS) + col];
      }
      float& operator[](unsigned int index)
      {
        return array[index];
      }

      inline mat4& operator*=(mat4 &matrix)
      {
        for (unsigned int i = 0; i < ROWS; i++)
        {
          for (unsigned int j = 0; j < COLUMNS; j++)
            at(i, j)*=matrix.at(j, i);
        }
        return *this;
      }

      inline mat4 operator+(mat4 &matrix)
      {
        mat4 m;
        for (unsigned int i = 0; i < me::maths::min(size(), matrix.size()); i++)
          m[i] = array[i]+=matrix[i];
        return *this;
      }
      inline mat4 operator+(float fac)
      {
        mat4 m;
        for (unsigned int i = 0; i < size(); i++)
          m[i] = array[i] + fac;
        return m;
      }
      inline mat4 operator-(mat4 &matrix)
      {
        mat4 m;
        for (unsigned int i = 0; i < me::maths::min(size(), matrix.size()); i++)
          m[i] = array[i] - matrix[i];
        return m;
      }
      inline mat4 operator-(float fac)
      {
        mat4 m;
        for (unsigned int i = 0; i < size(); i++)
          m[i] = array[i] - fac;
        return m;
      }
      inline mat4 operator*(mat4 &matrix)
      {
        mat4 m;
        for (unsigned int i = 0; i < ROWS; i++)
        {
          for (unsigned int j = 0; j < COLUMNS; j++)
            m.at(i, j) = at(i, j) * matrix.at(j, i);
        }
        return m;
      }
      inline mat4 operator*(float fac)
      {
        mat4 m;
        for (unsigned int i = 0; i < size(); i++)
          m[i] = array[i] * fac;
        return m;
      }
      inline mat4 operator/(mat4 &matrix)
      {
        mat4 m;
        for (unsigned int i = 0; i < me::maths::min(size(), matrix.size()); i++)
          m[i] = array[i] / matrix[i];
        return m;
      }
      inline mat4 operator/(float fac)
      {
        mat4 m;
        for (unsigned int i = 0; i < size(); i++)
          m[i] = array[i] / fac;
        return m;
      }
      inline void operator|(mat4 &mat)
      {
        for (uint32_t i = 0; i < mat.size(); i++)
          array[i] = mat[i];
      }

      inline float x() { return m30(); }
      inline float y() { return m31(); }
      inline float z() { return m32(); }
      inline float w() { return m33(); }

    };

    inline void identify(mat4 &matrix)
    {
      for (int i = 0; i < 16; i++)
        matrix[i] = 0;
      matrix[0] = 1;
      matrix[5] = 1;
      matrix[10] = 1;
      matrix[15] = 1;
    }

    /*
    float y_scale = (1.0F / me::maths::tan(fov / 2.0F)) * aspect;
    float x_scale = y_scale / aspect;
    float frustum_length = zfar - znear;

    matrix.m00(x_scale);
    matrix.m11(y_scale);
    matrix.m22(-((zfar + znear) / frustum_length));
    matrix.m23(-1.0F);
    matrix.m32(-((2.0F * znear * zfar) / frustum_length));
    matrix.m33(0.0F);
    */

    inline void perspective(mat4 &matrix, float fov, float aspect, float znear, float zfar)
    {
      float hfov = me::maths::tan(fov / 2.0F);
      matrix.m00(1.0F / (aspect * hfov));
      matrix.m11(1.0F / (hfov));
      matrix.m22(-(zfar + znear) / (zfar - znear));
      matrix.m23(-1.0F);
      matrix.m32(-(2.0F * zfar * znear) / (zfar - znear));
    }

    inline void frustum(mat4 &matrix, float left, float right, float bottom, float top, float znear, float zfar)
    {
      matrix.m00((znear + znear) / (right - left));
      matrix.m11((znear + znear) / (top - bottom));
      matrix.m20((right + left) / (right - left));
      matrix.m21((top + bottom) / (top - bottom));
      matrix.m22((zfar + znear) / (znear - zfar));
      matrix.m32((zfar + zfar) * znear / (znear - zfar));
      matrix.m23(-1.0F);
      matrix.m33(0.0F);
    }

    inline void orthographic(mat4 &matrix, float left, float right, float bottom, float top, float znear, float zfar)
    {
      matrix.m00(2.0F / (right - left));
      matrix.m00(2.0F / (top - bottom));
      matrix.m00(1.0F / (zfar - znear));
      matrix.m00(-(right + left) / (right - left));
      matrix.m00(-(top + bottom) / (top - bottom));
      matrix.m00(-znear / (zfar - znear));
    }

    inline void look(mat4 &matrix, me::vec3 eye, me::vec3 center, me::vec3 up)
    {
      me::vec3 f(me::normalize(center - eye));
      me::vec3 s(me::normalize(me::cross(f, up)));
      me::vec3 u(me::cross(s, f));
      matrix.m00(s.x);
      matrix.m10(s.y);
      matrix.m20(s.z);
      matrix.m01(u.x);
      matrix.m11(u.y);
      matrix.m21(u.z);
      matrix.m02(-f.x);
      matrix.m12(-f.y);
      matrix.m22(-f.z);
      matrix.m30(-me::dot(s, eye));
      matrix.m31(-me::dot(u, eye));
      matrix.m32(-me::dot(f, eye));
    }

    inline void translate(mat4 &matrix, float x, float y, float z)
    {
      matrix[12] = x;
      matrix[13] = y;
      matrix[14] = z;
    }

    inline void scale(mat4 &matrix, float x, float y, float z)
    {
      matrix[0] = matrix[0] * x;
      matrix[5] = matrix[5] * y;
      matrix[10] = matrix[10] * z;
    }

    inline void rotate(mat4 &matrix, float rotX, float rotY, float rotZ)
    {
      float sinX = me::maths::sin(rotX);
      float cosX = me::maths::cos(rotX);
      float sinY = me::maths::sin(rotY);
      float cosY = me::maths::cos(rotY);
      float sinZ = me::maths::sin(rotZ);
      float cosZ = me::maths::cos(rotZ);
      float n_sinX = -sinX;
      float n_sinY = -sinY;
      float n_sinZ = -sinZ;

      float nm11 = cosX;
      float nm12 = sinX;
      float nm21 = n_sinX;
      float nm22 = cosX;

      float nm00 = cosY;
      float nm01 = nm21 * n_sinY;
      float nm02 = nm22 * n_sinY;

      matrix.m20(sinY);
      matrix.m21(nm21 * cosY);
      matrix.m22(nm22 * cosY);

      matrix.m00(nm00 * cosZ);
      matrix.m01(nm01 * cosZ + nm11 * sinZ);
      matrix.m02(nm02 * cosZ + nm12 * sinZ);
      matrix.m10(nm00 * sinZ);
      matrix.m11(nm01 * sinZ + nm11 * cosZ);
      matrix.m12(nm02 * sinZ + nm12 * cosZ);
    }

    inline void rotateTranslation(mat4 mat, me::vec4 quat)
    {
      float w2 = quat.w * quat.w, x2 = quat.x * quat.x;
      float y2 = quat.y * quat.y, z2 = quat.z * quat.z;
      float zw = quat.z * quat.w, dzw = zw + zw, xy = quat.x * quat.y, dxy = xy + xy;
      float xz = quat.x * quat.z, dxz = xz + xz, yw = quat.y * quat.w, dyw = yw + yw;
      float yz = quat.y * quat.z, dyz = yz + yz, xw = quat.x * quat.w, dxw = xw + xw;
      float rm00 = w2 + x2 - z2 - y2;
      float rm01 = dxy + dzw;
      float rm02 = dxz - dyw;
      float rm10 = -dzw + dxy;
      float rm11 = y2 - z2 + w2 - x2;
      float rm12 = dyz + dxw;
      float rm20 = dyw + dxz;
      float rm21 = dyz - dxw;
      float rm22 = z2 - y2 - x2 + w2;
      mat.m20(rm20);
      mat.m21(rm21);
      mat.m22(rm22);
      mat.m23(0.0f);
      mat.m00(rm00);
      mat.m01(rm01);
      mat.m02(rm02);
      mat.m03(0.0f);
      mat.m10(rm10);
      mat.m11(rm11);
      mat.m12(rm12);
      mat.m13(0.0f);
      mat.m30(mat.m30());
      mat.m31(mat.m31());
      mat.m32(mat.m32());
      mat.m33(mat.m33());
    }

    inline void rotationX(mat4 &matrix, float angle)
    {
      float sin = me::maths::sin(angle);
      float cos = me::maths::cos(angle);

      matrix.m11(cos);
      matrix.m12(sin);
      matrix.m21(-sin);
      matrix.m22(cos);
    }

    inline void rotationY(mat4 &matrix, float angle)
    {
      float sin = me::maths::sin(angle);
      float cos = me::maths::cos(angle);

      matrix.m00(cos);
      matrix.m02(-sin);
      matrix.m20(sin);
      matrix.m22(cos);
    }

    inline void rotationZ(mat4 &matrix, float angle)
    {
      float sin = me::maths::sin(angle);
      float cos = me::maths::cos(angle);

      matrix.m00(cos);
      matrix.m01(sin);
      matrix.m10(-sin);
      matrix.m11(cos);
    }

    inline void print_matrix(float* matrix)
    {
      std::cout << "----------------------\n";
      for (int i = 0; i < 16; i+=4)
      {
        std::cout << matrix[i] << ", ";
        std::cout << matrix[i+1] << ", ";
        std::cout << matrix[i+2] << ", ";
        std::cout << matrix[i+3] << "\n";
      }
      std::cout << "----------------------\n";
    }

  };

};

#endif
