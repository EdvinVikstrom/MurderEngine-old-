#ifndef ME_MATRIX_H
  #define ME_MATRIX_H

#define PROPERTY_PERSPECTIVE          1 << 0;
#define PROPERTY_ORTHONORMAL          1 << 1;
#define PROPERTY_IDENTITY             1 << 2;
#define PROPERTY_AFFINE               1 << 3;
#define PROPERTY_TRANSLATION          1 << 4;

#include "maths.hpp"

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

    inline void identify(real_t* matrix)
    {
      for (uint8_t i = 0; i < 16; i++)
        matrix[i] = 0;
      matrix[0] = 1;
      matrix[5] = 1;
      matrix[10] = 1;
      matrix[15] = 1;
    }

    /*
    real_t y_scale = (1.0F / me::maths::tan(fov / 2.0F)) * aspect;
    real_t x_scale = y_scale / aspect;
    real_t frustum_length = zfar - znear;

    matrix[0] = (x_scale);
    matrix[5] = (y_scale);
    matrix[10] = (-((zfar + znear) / frustum_length));
    matrix[11] = (-1.0F);
    matrix[14] = (-((2.0F * znear * zfar) / frustum_length));
    matrix[15] = (0.0F);
    */

    inline void perspective(real_t* matrix, real_t fov, real_t aspect, real_t znear, real_t zfar)
    {
      real_t hfov = me::maths::tan(fov / 2.0F);
      matrix[0] = (1.0F / (aspect * hfov));
      matrix[5] = (1.0F / (hfov));
      matrix[10] = (-(zfar + znear) / (zfar - znear));
      matrix[11] = (-1.0F);
      matrix[14] = (-(2.0F * zfar * znear) / (zfar - znear));
    }

    inline void frustum(real_t* matrix, real_t left, real_t right, real_t bottom, real_t top, real_t znear, real_t zfar)
    {
      matrix[0] = ((znear + znear) / (right - left));
      matrix[5] = ((znear + znear) / (top - bottom));
      matrix[8] = ((right + left) / (right - left));
      matrix[9] = ((top + bottom) / (top - bottom));
      matrix[10] = ((zfar + znear) / (znear - zfar));
      matrix[14] = ((zfar + zfar) * znear / (znear - zfar));
      matrix[11] = (-1.0F);
      matrix[15] = (0.0F);
    }

    inline void orthographic(mat &matrix, real_t left, real_t right, real_t bottom, real_t top, real_t znear, real_t zfar)
    {
      matrix[0] = (2.0F / (right - left));
      matrix[0] = (2.0F / (top - bottom));
      matrix[0] = (1.0F / (zfar - znear));
      matrix[0] = (-(right + left) / (right - left));
      matrix[0] = (-(top + bottom) / (top - bottom));
      matrix[0] = (-znear / (zfar - znear));
    }

    inline void look(mat &matrix, me::vec3 eye, me::vec3 center, me::vec3 up)
    {
      me::vec3 f(me::normalize(center - eye));
      me::vec3 s(me::normalize(me::cross(f, up)));
      me::vec3 u(me::cross(s, f));
      matrix[0] = (s.x);
      matrix[4] = (s.y);
      matrix[8] = (s.z);
      matrix[1] = (u.x);
      matrix[5] = (u.y);
      matrix[9] = (u.z);
      matrix[2] = (-f.x);
      matrix[6] = (-f.y);
      matrix[10] = (-f.z);
      matrix[12] = (-me::dot(s, eye));
      matrix[13] = (-me::dot(u, eye));
      matrix[14] = (-me::dot(f, eye));
    }

    inline void translate(mat &matrix, real_t x, real_t y, real_t z)
    {
      matrix[12] = x;
      matrix[13] = y;
      matrix[14] = z;
    }

    inline void scale(mat &matrix, real_t x, real_t y, real_t z)
    {
      matrix[0] = matrix[0] * x;
      matrix[5] = matrix[5] * y;
      matrix[10] = matrix[10] * z;
    }

    inline void rotate(mat &matrix, real_t rotX, real_t rotY, real_t rotZ)
    {
      real_t sinX = me::maths::sin(rotX);
      real_t cosX = me::maths::cos(rotX);
      real_t sinY = me::maths::sin(rotY);
      real_t cosY = me::maths::cos(rotY);
      real_t sinZ = me::maths::sin(rotZ);
      real_t cosZ = me::maths::cos(rotZ);
      real_t n_sinX = -sinX;
      real_t n_sinY = -sinY;
      real_t n_sinZ = -sinZ;

      real_t nm11 = cosX;
      real_t nm12 = sinX;
      real_t nm21 = n_sinX;
      real_t nm22 = cosX;

      real_t nm00 = cosY;
      real_t nm01 = nm21 * n_sinY;
      real_t nm02 = nm22 * n_sinY;

      matrix[8] = (sinY);
      matrix[9] = (nm21 * cosY);
      matrix[10] = (nm22 * cosY);

      matrix[0] = (nm00 * cosZ);
      matrix[1] = (nm01 * cosZ + nm11 * sinZ);
      matrix[2] = (nm02 * cosZ + nm12 * sinZ);
      matrix[4] = (nm00 * sinZ);
      matrix[5] = (nm01 * sinZ + nm11 * cosZ);
      matrix[6] = (nm02 * sinZ + nm12 * cosZ);
    }

    inline void rotateTranslation(mat mat, me::vec4 quat)
    {
      real_t w2 = quat.w * quat.w, x2 = quat.x * quat.x;
      real_t y2 = quat.y * quat.y, z2 = quat.z * quat.z;
      real_t zw = quat.z * quat.w, dzw = zw + zw, xy = quat.x * quat.y, dxy = xy + xy;
      real_t xz = quat.x * quat.z, dxz = xz + xz, yw = quat.y * quat.w, dyw = yw + yw;
      real_t yz = quat.y * quat.z, dyz = yz + yz, xw = quat.x * quat.w, dxw = xw + xw;
      real_t rm00 = w2 + x2 - z2 - y2;
      real_t rm01 = dxy + dzw;
      real_t rm02 = dxz - dyw;
      real_t rm10 = -dzw + dxy;
      real_t rm11 = y2 - z2 + w2 - x2;
      real_t rm12 = dyz + dxw;
      real_t rm20 = dyw + dxz;
      real_t rm21 = dyz - dxw;
      real_t rm22 = z2 - y2 - x2 + w2;
      mat[8] = (rm20);
      mat[9] = (rm21);
      mat[10] = (rm22);
      mat[11] = (0.0f);
      mat[0] = (rm00);
      mat[1] = (rm01);
      mat[2] = (rm02);
      mat[3] = (0.0f);
      mat[4] = (rm10);
      mat[5] = (rm11);
      mat[6] = (rm12);
      mat[7] = (0.0f);
      mat[12] = (mat[12]);
      mat[13] = (mat[13]);
      mat[14] = (mat[14]);
      mat[15] = (mat[15]);
    }

    inline void rotationX(mat &matrix, real_t angle)
    {
      real_t sin = me::maths::sin(angle);
      real_t cos = me::maths::cos(angle);

      matrix[5] = (cos);
      matrix[6] = (sin);
      matrix[9] = (-sin);
      matrix[10] = (cos);
    }

    inline void rotationY(mat &matrix, real_t angle)
    {
      real_t sin = me::maths::sin(angle);
      real_t cos = me::maths::cos(angle);

      matrix[0] = (cos);
      matrix[2] = (-sin);
      matrix[8] = (sin);
      matrix[10] = (cos);
    }

    inline void rotationZ(mat &matrix, real_t angle)
    {
      real_t sin = me::maths::sin(angle);
      real_t cos = me::maths::cos(angle);

      matrix[0] = (cos);
      matrix[1] = (sin);
      matrix[4] = (-sin);
      matrix[5] = (cos);
    }

    inline void print_matrix(real_t* matrix)
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
