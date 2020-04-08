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

    struct mat {
      char rows, columns;
      int properties;
      float* array;
      mat(char rows, char columns, int properties, float* array)
      {
        this->rows = rows;
        this->columns = columns;
        this->properties = properties;
        this->array = array;
      }

      inline int size()
      {
        return rows * columns;
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

      virtual float& at(unsigned int row, unsigned int col) = 0;
      virtual float& operator[](unsigned int index) = 0;
      inline mat& operator+(mat &matrix)
      {
        for (unsigned int i = 0; i < me::maths::min(size(), matrix.size()); i++)
          array[i]+=matrix[i];
        return *this;
      }
      inline mat& operator+(float fac)
      {
        for (unsigned int i = 0; i < size(); i++)
          array[i]+=fac;
        return *this;
      }
      inline mat& operator-(mat &matrix)
      {
        for (unsigned int i = 0; i < me::maths::min(size(), matrix.size()); i++)
          array[i]-=matrix[i];
        return *this;
      }
      inline mat& operator-(float fac)
      {
        for (unsigned int i = 0; i < size(); i++)
          array[i]-=fac;
        return *this;
      }
      inline mat& operator*(mat &matrix)
      {
        for (unsigned int i = 0; i < me::maths::min(size(), matrix.size()); i++)
          at(i / rows, i % columns)*=matrix.at(i % matrix.rows, i / matrix.columns);
        return *this;
      }
      inline mat& operator*(float fac)
      {
        for (unsigned int i = 0; i < size(); i++)
          array[i]*=fac;
        return *this;
      }
      inline mat& operator/(mat &matrix)
      {
        for (unsigned int i = 0; i < me::maths::min(size(), matrix.size()); i++)
          at(i / rows, i % columns)/=matrix.at(i % matrix.rows, i / matrix.columns);
        return *this;
      }
      inline mat& operator/(float fac)
      {
        for (unsigned int i = 0; i < size(); i++)
          array[i]/=fac;
        return *this;
      }

    };

    struct mat4 : mat {

      mat4(int properties, float* array) : mat(4, 4, properties, array) { }
      mat4(float* array) : mat(4, 4, 0, array) { }
      mat4() : mat(4, 4, 0, new float[16]) { }

      inline float& at(unsigned int row, unsigned int col) override
      {
        return array[(row*4) + col];
      }

      inline float& operator[](unsigned int index) override
      {
        return array[index];
      }

    };

    inline void identify(mat &matrix)
    {
      for (int i = 0; i < 16; i++)
        matrix[i] = 0;
      matrix[0] = 1;
      matrix[5] = 1;
      matrix[10] = 1;
      matrix[15] = 1;
    }

    inline void perspective(mat &matrix, float fov, float aspect, float znear, float zfar)
    {
      float y_scale = (1.0F / me::maths::tan(fov / 2.0F)) * aspect;
      float x_scale = y_scale / aspect;
      float frustum_length = zfar - znear;

      matrix.m00(x_scale);
      matrix.m11(y_scale);
      matrix.m22(-((zfar + znear) / frustum_length));
      matrix.m23(-1.0F);
      matrix.m32(-((2.0F * znear * zfar) / frustum_length));
      matrix.m33(0.0F);
    }

    inline void frustum(mat &matrix, float left, float right, float bottom, float top, float znear, float zfar)
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

    inline void orthographic(mat &matrix, float left, float right, float bottom, float top, float znear, float zfar)
    {
      matrix[0] = 2 / (right - left);
      matrix[5] = 2 / (top - bottom);
      matrix[10] = -2 / (zfar - znear);
      matrix[3] = right + left / (right - left);
      matrix[7] = top + bottom / (top - bottom);
      matrix[11] = zfar + znear / (zfar - znear);
      matrix[15] = 1;

    }

    inline void translate(mat &matrix, float x, float y, float z)
    {
      matrix[12] = x;
      matrix[13] = y;
      matrix[14] = z;
    }

    inline void scale(mat &matrix, float x, float y, float z)
    {
      matrix[0] = matrix[0] * x;
      matrix[5] = matrix[5] * y;
      matrix[10] = matrix[10] * z;
    }

    inline void rotate(mat &matrix, float angle, me::vec3f vec)
    {
      float cos = me::maths::cos(angle);
      float sin = me::maths::sin(angle);
      // TODO: normalize x, y, z
      me::vec3f axis(vec.normalize());
      me::vec3f temp(axis * (1.0F - cos));
      mat4 rotate;
      //rotate.m00(cos + )
    }

    inline void rotationX(mat &matrix, float angle)
    {
      float sin = me::maths::sin(angle);
      float cos = me::maths::cos(angle);

      matrix.m11(cos);
      matrix.m12(sin);
      matrix.m21(-sin);
      matrix.m22(cos);
    }

    inline void rotationY(mat &matrix, float angle)
    {
      float sin = me::maths::sin(angle);
      float cos = me::maths::cos(angle);

      matrix.m00(cos);
      matrix.m02(-sin);
      matrix.m20(sin);
      matrix.m22(cos);
    }

    inline void rotationZ(mat &matrix, float angle)
    {
      float sin = me::maths::sin(angle);
      float cos = me::maths::cos(angle);

      matrix[0] = cos;
      matrix[1] = sin;
      matrix[4] = -sin;
      matrix[5] = cos;
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
