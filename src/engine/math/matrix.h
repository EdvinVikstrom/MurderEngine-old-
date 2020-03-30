#ifndef ME_MATRIX_H
  #define ME_MATRIX_H

#include "maths.h"

namespace me {

  template<unsigned char ROWS, unsigned char COLS>
  struct matf {
    float** matrix;
    matf(float** matrix)
    {
      this->matrix = matrix;
    }
    ~matf()
    {
      for (unsigned char i = 0; i < ROWS; i++)
        delete[] matrix[i];
      delete[] matrix;
    }
    unsigned char rows()
    {
      return ROWS;
    }
    unsigned char cols()
    {
      return COLS;
    }
    void forEach(unsigned char rows, unsigned char cols, const std::function<void(unsigned char &i, unsigned char &j, float &f)> &event)
    {
      for (unsigned char i = 0; i < rows; i++)
      {
        for (unsigned char j = 0; j < cols; j++)
          event(i, j, matrix[i][j]);
      }
    }
    inline void add(me::matf* mat)
    {
      forEach(maths::mini(rows(), math->cols()), maths::mini(math->rows(), math->cols()),
      [&](unsigned char &i, unsigned char &j, float &f) {
        f = f + mat->matrix[i][j];
      });
    }
    inline void sub(me::matf* mat)
    {
      forEach(maths::mini(rows(), math->cols()), maths::mini(math->rows(), math->cols()),
      [&](unsigned char &i, unsigned char &j, float &f) {
        f = f - mat->matrix[i][j];
      });
    }
    inline void mul(me::matf* mat)
    {
      forEach(maths::mini(rows(), math->cols()), maths::mini(math->rows(), math->cols()),
      [&](unsigned char &i, unsigned char &j, float &f) {
        f = f * mat->matrix[i][j];
      });
    }
    inline void div(me::matf* mat)
    {
      forEach(maths::mini(rows(), math->cols()), maths::mini(math->rows(), math->cols()),
      [&](unsigned char &i, unsigned char &j, float &f) {
        f = f / mat->matrix[i][j];
      });
    }
  };

  template<unsigned char ROWS, unsigned char COLS>
  struct matd {
    double** matrix;
    matd(double** matrix)
    {
      this->matrix = matrix;
    }
    ~matd()
    {
      for (unsigned char i = 0; i < ROWS; i++)
        delete[] matrix[i];
      delete[] matrix;
    }
    unsigned char rows()
    {
      return ROWS;
    }
    unsigned char cols()
    {
      return COLS;
    }
    void forEach(unsigned char rows, unsigned char cols, const std::function<void(unsigned char &i, unsigned char &j, double &f)> &event)
    {
      for (unsigned char i = 0; i < rows; i++)
      {
        for (unsigned char j = 0; j < cols; j++)
          event(i, j, matrix[i][j]);
      }
    }
    inline void add(me::matf* mat)
    {
      forEach(maths::mini(rows(), math->cols()), maths::mini(math->rows(), math->cols()),
      [&](unsigned char &i, unsigned char &j, double &f) {
        f = f + mat->matrix[i][j];
      });
    }
    inline void sub(me::matf* mat)
    {
      forEach(maths::mini(rows(), math->cols()), maths::mini(math->rows(), math->cols()),
      [&](unsigned char &i, unsigned char &j, double &f) {
        f = f - mat->matrix[i][j];
      });
    }
    inline void mul(me::matf* mat)
    {
      forEach(maths::mini(rows(), math->cols()), maths::mini(math->rows(), math->cols()),
      [&](unsigned char &i, unsigned char &j, double &f) {
        f = f * mat->matrix[i][j];
      });
    }
    inline void div(me::matf* mat)
    {
      forEach(maths::mini(rows(), math->cols()), maths::mini(math->rows(), math->cols()),
      [&](unsigned char &i, unsigned char &j, double &f) {
        f = f / mat->matrix[i][j];
      });
    }
  };

  template<unsigned char ROWS, unsigned char COLS>
  struct mati {
    int** matrix;
    mati(int** matrix)
    {
      this->matrix = matrix;
    }
    ~mati()
    {
      for (unsigned char i = 0; i < ROWS; i++)
        delete[] matrix[i];
      delete[] matrix;
    }
    unsigned char rows()
    {
      return ROWS;
    }
    unsigned char cols()
    {
      return COLS;
    }
    void forEach(unsigned char rows, unsigned char cols, const std::function<void(unsigned char &i, unsigned char &j, int &f)> &event)
    {
      for (unsigned char i = 0; i < rows; i++)
      {
        for (unsigned char j = 0; j < cols; j++)
          event(i, j, matrix[i][j]);
      }
    }
    inline void add(me::matf* mat)
    {
      forEach(maths::mini(rows(), math->cols()), maths::mini(math->rows(), math->cols()),
      [&](unsigned char &i, unsigned char &j, int &f) {
        f = f + mat->matrix[i][j];
      });
    }
    inline void sub(me::matf* mat)
    {
      forEach(maths::mini(rows(), math->cols()), maths::mini(math->rows(), math->cols()),
      [&](unsigned char &i, unsigned char &j, int &f) {
        f = f - mat->matrix[i][j];
      });
    }
    inline void mul(me::matf* mat)
    {
      forEach(maths::mini(rows(), math->cols()), maths::mini(math->rows(), math->cols()),
      [&](unsigned char &i, unsigned char &j, int &f) {
        f = f * mat->matrix[i][j];
      });
    }
    inline void div(me::matf* mat)
    {
      forEach(maths::mini(rows(), math->cols()), maths::mini(math->rows(), math->cols()),
      [&](unsigned char &i, unsigned char &j, int &f) {
        f = f / mat->matrix[i][j];
      });
    }
  };

  struct mat3x2f : matf<3, 2> {
    mat3x2f(float** matrix) : matf(matrix) { }
    mat3x2f() : matf(new float[3][2]) { }
  };
  struct mat3x3f : matf<3, 3> {
    mat3x3f(float** matrix) : matf(matrix) { }
    mat3x3f() : matf(new float[3][3]) { }
  };
  struct mat4x3f : matf<4, 3> {
    mat4x3f(float** matrix) : matf(matrix) { }
    mat4x3f() : matf(new float[4][3]) { }
  };
  struct mat4x4f : matf<4, 4> {
    mat4x4f(float** matrix) : matf(matrix) { }
    mat4x4f() : matf(new float[4][4]) { }
  };

  struct mat3x2d : matd<3, 2> {
    mat3x2d(double** matrix) : matd(matrix) { }
    mat3x2d() : matd(new double[3][2]) { }
  };
  struct mat3x3d : matd<3, 3> {
    mat3x3d(double** matrix) : matd(matrix) { }
    mat3x3d() : matd(new double[3][3]) { }
  };
  struct mat4x3d : matd<4, 3> {
    mat4x3d(double** matrix) : matd(matrix) { }
    mat4x3d() : matd(new double[4][3]) { }
  };
  struct mat4x4d : matd<4, 4> {
    mat4x4d(double** matrix) : matd(matrix) { }
    mat4x4d() : matd(new double[4][4]) { }
  };

  struct mat3x2i : mati<3, 2> {
    mat3x2i(int** matrix) : mati(matrix) { }
    mat3x2i() : mati(new int[3][2]) { }
  };
  struct mat3x3i : mati<3, 3> {
    mat3x3i(int** matrix) : mati(matrix) { }
    mat3x3i() : mati(new int[3][3]) { }
  };
  struct mat4x3i : mati<4, 3> {
    mat4x3i(int** matrix) : mati(matrix) { }
    mat4x3i() : mati(new int[4][3]) { }
  };
  struct mat4x4i : mati<4, 4> {
    mat4x4i(int** matrix) : mati(matrix) { }
    mat4x4i() : mati(new int[4][4]) { }
  };


};

#endif
