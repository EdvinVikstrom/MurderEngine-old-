#include "maths.h"
#include <math.h>
#include <stdlib.h>

static bool fast_math = true; // TODO:

double maths::rand()
{
  return ((double) std::rand() / RAND_MAX);
}

// Trigonometric functions

/* cos */
long double maths::cosl(long double angle)
{
  return cosl(angle);
}
double maths::cosd(double angle)
{
  return cos(angle);
}
float maths::cosf(float angle)
{
  return cosf(angle);
}

/* sin */
long double maths::sinl(long double angle)
{
  return sinl(angle);
}
double maths::sind(double angle)
{
  return sin(angle);
}
float maths::sinf(float angle)
{
  return sinf(angle);
}

/* tan */
long double maths::tanl(long double angle)
{
  return tanl(angle);
}
double maths::tand(double angle)
{
  return tan(angle);
}
float maths::tanf(float angle)
{
  return tanf(angle);
}

/* acos */
long double maths::acosl(long double angle)
{

}
double maths::acosd(double angle)
{

}
float maths::acosf(float angle)
{

}

/* asin */
long double maths::asinl(long double angle)
{

}
double maths::asind(double angle)
{

}
float maths::asinf(float angle)
{

}

/* atan */
long double maths::atanl(long double angle)
{

}
double maths::atand(double angle)
{

}
float maths::atanf(float angle)
{

}

/* atan2 */
long double maths::atan2l(long double y, long double x)
{

}
double maths::atan2d(double y, double x)
{
  return atan2(y, x);
}
float maths::atan2f(float y, float x)
{

}

/* cos from sin */
long double maths::cosfsinl(long double sin, long double angle)
{
  return maths::sinl(angle + H_PI);
}
double maths::cosfsind(double sin, double angle)
{
  return maths::sind(angle + H_PI);
}
float maths::cosfsinf(float sin, float angle)
{
  return maths::sinf(angle + H_PI);
}

// Hyperbolic functions

/* sinh */
long double maths::sinhl(long double angle)
{

}
double maths::sinhd(double angle)
{

}
float maths::sinhf(float angle)
{

}

/* cosh */
long double maths::coshl(long double angle)
{

}
double maths::coshd(double angle)
{

}
float maths::coshf(float angle)
{

}

/* tanh */
long double maths::tanhl(long double angle)
{

}
double maths::tanhd(double angle)
{

}
float maths::tanhf(float angle)
{

}

/* asinh */
long double maths::asinhl(long double angle)
{

}
double maths::asinhd(double angle)
{

}
float maths::asinhf(float angle)
{

}

/* acosh */
long double maths::acoshl(long double angle)
{

}
double maths::acoshd(double angle)
{

}
float maths::acoshf(float angle)
{

}

/* atanh */
long double maths::atanhl(long double angle)
{

}
double maths::atanhd(double angle)
{

}
float maths::atanhf(float angle)
{

}

// rounding

/* ceil */
long double maths::ceill(long double a)
{

}
double maths::ceild(double a)
{

}
float maths::ceilf(float a)
{

}

/* floor */
long double maths::floorl(long double a)
{

}
double maths::floord(double a)
{

}
float maths::floorf(float a)
{

}

/* trunc */
long double maths::truncl(long double a)
{

}
double maths::truncd(double a)
{

}
float maths::truncf(float a)
{

}

/* round */
long double maths::roundl(long double a)
{

}
double maths::roundd(double a)
{

}
float maths::roundf(float a)
{

}

/* nearbyint */
long double maths::nearbyintl(long double a)
{

}
double maths::nearbyintd(double a)
{

}
float maths::nearbyintf(float a)
{

}

/* rint */
long double maths::rintl(long double a)
{

}
double maths::rintd(double a)
{

}
float maths::rintf(float a)
{

}

/* Manipulation functions  */

/* frexp */
long double maths::frexpl(long double a, int* exp)
{

}
double maths::frexpd(double a, int* exp)
{

}
float maths::frexpf(float a, int* exp)
{

}

/* ldexp */
long double maths::ldexpl(long double a, int exp)
{

}
double maths::ldexpd(double a, int exp)
{

}
float maths::ldexpf(float a, int exp)
{

}

/* modfl */
long double maths::modfl(long double a, long double* iptr)
{

}
double maths::modfd(double a, double* iptr)
{

}
float maths::modff(float a, float* iptr)
{

}

/* scalbn */
long double maths::scalbnl(long double a, int exp)
{

}
double maths::scalbnd(double a, int exp)
{

}
float maths::scalbnf(float a, int exp)
{

}

/* nextafter */
long double maths::nextafterl(long double from, long double to)
{

}
double maths::nextafterd(double from, double to)
{

}
float maths::nextafterf(float from, float to)
{

}

/* nexttoward */
long double maths::nexttowardl(long double from, long double to)
{

}
double maths::nexttowardd(double from, long double to)
{

}
float maths::nexttowardf(float from, long double to)
{

}

/* copysign */
long double maths::copysignl(long double a, long double b)
{

}
double maths::copysignd(double a, double b)
{

}
float maths::copysignf(float a, float b)
{

}

// ööö

/* absolute */
long double maths::absl(long double a)
{
  return a < 0 ? -a : a;
}
double maths::absd(double a)
{
  return a < 0 ? -a : a;
}
float maths::absf(float a)
{
  return a < 0 ? -a : a;
}
int maths::absi(int a)
{
  return a < 0 ? -a : a;
}
long maths::absl(long a)
{
  return a < 0 ? -a : a;
}

/* max */
long double maths::maxl(long double a, long double b)
{
  return a >= b ? a : b;
}
double maths::maxd(double a, double b)
{
  return a >= b ? a : b;
}
float maths::maxf(float a, float b)
{
  return a >= b ? a : b;
}
int maths::maxi(int a, int b)
{
  return a >= b ? a : b;
}
long maths::maxl(long a, long b)
{
  return a >= b ? a : b;
}

/* min */
long double maths::minl(long double a, long double b)
{
  return a <= b ? a : b;
}
double maths::mind(double a, double b)
{
  return a <= b ? a : b;
}
float maths::minf(float a, float b)
{
  return a <= b ? a : b;
}
int maths::mini(int a, int b)
{
  return a <= b ? a : b;
}
long maths::minl(long a, long b)
{
  return a <= b ? a : b;
}

// Exponential functions

/* exp */
long double maths::expl(long double a)
{

}
double maths::expd(double a)
{

}

long double maths::exp2l(long double a)
{

}
double maths::exp2d(double a)
{

}

long double maths::expm1l(long double a)
{

}
double maths::expm1d(double a)
{

}

/* log */
long double maths::logl(long double a)
{

}
double maths::logd(double a)
{

}

long double maths::log2l(long double a)
{

}
double maths::log2d(double a)
{

}

long double maths::log10l(long double a)
{

}
double maths::log10d(double a)
{

}

long double maths::log1pl(long double a)
{

}
double maths::log1pd(double a)
{

}

// Power functions

/* sqrt */
long double maths::sqrtl(long double a)
{

}
double maths::sqrtd(double a)
{
  return sqrt(a);
}

/* cbrt */
long double maths::cbrtl(long double a)
{

}
double maths::cbrtl(double a)
{

}

/* hypot */
long double maths::hypotl(long double a, long double b)
{

}
double maths::hypotd(double a, double b)
{

}

/* pow */
long double maths::powl(long double a, long double b)
{
  return pow(a, b);
}
double maths::powd(double a, double b)
{
  return pow(a, b);
}
