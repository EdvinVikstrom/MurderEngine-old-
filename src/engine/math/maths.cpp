#include "maths.h"
#include <math.h>
#include <stdlib.h>

static bool fast_math = true; // TODO:

double me::maths::rand()
{
  return ((double) std::rand() / RAND_MAX);
}

// Trigonometric functions

/* cos */
long double me::maths::cos(long double angle)
{
  return ::cosl(angle);
}
double me::maths::cos(double angle)
{
  return ::cos(angle);
}
float me::maths::cos(float angle)
{
  return ::cosf(angle);
}

/* sin */
long double me::maths::sin(long double angle)
{
  return ::sinl(angle);
}
double me::maths::sin(double angle)
{
  return ::sin(angle);
}
float me::maths::sin(float angle)
{
  return ::sinf(angle);
}

/* tan */
long double me::maths::tan(long double angle)
{
  return ::tanl(angle);
}
double me::maths::tan(double angle)
{
  return ::tan(angle);
}
float me::maths::tan(float angle)
{
  return ::tanf(angle);
}

/* acos */
long double me::maths::acos(long double angle)
{

}
double me::maths::acos(double angle)
{

}
float me::maths::acos(float angle)
{

}

/* asin */
long double me::maths::asin(long double angle)
{

}
double me::maths::asin(double angle)
{

}
float me::maths::asin(float angle)
{

}

/* atan */
long double me::maths::atan(long double angle)
{

}
double me::maths::atan(double angle)
{

}
float me::maths::atan(float angle)
{

}

/* atan2 */
long double me::maths::atan2(long double y, long double x)
{

}
double me::maths::atan2(double y, double x)
{
  return ::atan2(y, x);
}
float me::maths::atan2(float y, float x)
{

}

/* cos from sin */
long double me::maths::cosfsin(long double sin, long double angle)
{
  return me::maths::sin(angle + H_PI);
}
double me::maths::cosfsin(double sin, double angle)
{
  return me::maths::sin(angle + H_PI);
}
float me::maths::cosfsin(float sin, float angle)
{
  return me::maths::sin(angle + H_PI);
}

// Hyperbolic functions

/* sinh */
long double me::maths::sinh(long double angle)
{

}
double me::maths::sinh(double angle)
{

}
float me::maths::sinh(float angle)
{

}

/* cosh */
long double me::maths::cosh(long double angle)
{

}
double me::maths::cosh(double angle)
{

}
float me::maths::cosh(float angle)
{

}

/* tanh */
long double me::maths::tanh(long double angle)
{

}
double me::maths::tanh(double angle)
{

}
float me::maths::tanh(float angle)
{

}

/* asinh */
long double me::maths::asinh(long double angle)
{

}
double me::maths::asinh(double angle)
{

}
float me::maths::asinh(float angle)
{

}

/* acosh */
long double me::maths::acosh(long double angle)
{

}
double me::maths::acosh(double angle)
{

}
float me::maths::acosh(float angle)
{

}

/* atanh */
long double me::maths::atanh(long double angle)
{

}
double me::maths::atanh(double angle)
{

}
float me::maths::atanh(float angle)
{

}

// rounding

/* ceil */
long double me::maths::ceil(long double a)
{

}
double me::maths::ceil(double a)
{

}
float me::maths::ceil(float a)
{

}

/* floor */
long double me::maths::floor(long double a)
{

}
double me::maths::floor(double a)
{

}
float me::maths::floor(float a)
{

}

/* trunc */
long double me::maths::trunc(long double a)
{

}
double me::maths::trunc(double a)
{

}
float me::maths::trunc(float a)
{

}

/* round */
long double me::maths::round(long double a)
{

}
double me::maths::round(double a)
{

}
float me::maths::round(float a)
{

}

/* nearbyint */
long double me::maths::nearbyint(long double a)
{

}
double me::maths::nearbyint(double a)
{

}
float me::maths::nearbyint(float a)
{

}

/* rint */
long double me::maths::rint(long double a)
{

}
double me::maths::rint(double a)
{

}
float me::maths::rint(float a)
{

}

/* Manipulation functions  */

/* frexp */
long double me::maths::frexp(long double a, int* exp)
{

}
double me::maths::frexp(double a, int* exp)
{

}
float me::maths::frexp(float a, int* exp)
{

}

/* ldexp */
long double me::maths::ldexp(long double a, int exp)
{

}
double me::maths::ldexp(double a, int exp)
{

}
float me::maths::ldexp(float a, int exp)
{

}

/* modfl */
long double me::maths::modf(long double a, long double* iptr)
{

}
double me::maths::modf(double a, double* iptr)
{

}
float me::maths::modf(float a, float* iptr)
{

}

/* scalbn */
long double me::maths::scalbn(long double a, int exp)
{

}
double me::maths::scalbn(double a, int exp)
{

}
float me::maths::scalbn(float a, int exp)
{

}

/* nextafter */
long double me::maths::nextafter(long double from, long double to)
{

}
double me::maths::nextafter(double from, double to)
{

}
float me::maths::nextafter(float from, float to)
{

}

/* nexttoward */
long double me::maths::nexttoward(long double from, long double to)
{

}
double me::maths::nexttoward(double from, long double to)
{

}
float me::maths::nexttoward(float from, long double to)
{

}

/* copysign */
long double me::maths::copysign(long double a, long double b)
{

}
double me::maths::copysign(double a, double b)
{

}
float me::maths::copysign(float a, float b)
{

}

// ööö

/* absolute */
long double me::maths::abs(long double a)
{
  return a < 0 ? -a : a;
}
double me::maths::abs(double a)
{
  return a < 0 ? -a : a;
}
float me::maths::abs(float a)
{
  return a < 0 ? -a : a;
}
int me::maths::abs(int a)
{
  return a < 0 ? -a : a;
}
long me::maths::absl(long a)
{
  return a < 0 ? -a : a;
}

/* max */
long double me::maths::max(long double a, long double b)
{
  return a >= b ? a : b;
}
double me::maths::max(double a, double b)
{
  return a >= b ? a : b;
}
float me::maths::max(float a, float b)
{
  return a >= b ? a : b;
}
int me::maths::max(int a, int b)
{
  return a >= b ? a : b;
}
long me::maths::maxl(long a, long b)
{
  return a >= b ? a : b;
}

/* min */
long double me::maths::min(long double a, long double b)
{
  return a <= b ? a : b;
}
double me::maths::min(double a, double b)
{
  return a <= b ? a : b;
}
float me::maths::min(float a, float b)
{
  return a <= b ? a : b;
}
int me::maths::min(int a, int b)
{
  return a <= b ? a : b;
}
long me::maths::minl(long a, long b)
{
  return a <= b ? a : b;
}

// Exponential functions

/* exp */
long double me::maths::exp(long double a)
{

}
double me::maths::exp(double a)
{

}

long double me::maths::exp2(long double a)
{

}
double me::maths::exp2(double a)
{

}

long double me::maths::expm1(long double a)
{

}
double me::maths::expm1(double a)
{

}

/* log */
long double me::maths::log(long double a)
{

}
double me::maths::log(double a)
{

}

long double me::maths::log2(long double a)
{

}
double me::maths::log2(double a)
{

}

long double me::maths::log10(long double a)
{

}
double me::maths::log10(double a)
{

}

long double me::maths::log1p(long double a)
{

}
double me::maths::log1p(double a)
{

}

// Power functions

/* sqrt */
long double me::maths::sqrt(long double a)
{

}
double me::maths::sqrt(double a)
{
  return ::sqrt(a);
}

/* cbrt */
long double me::maths::cbrt(long double a)
{

}
double me::maths::cbrtl(double a)
{

}

/* hypot */
long double me::maths::hypot(long double a, long double b)
{

}
double me::maths::hypot(double a, double b)
{

}

/* pow */
long double me::maths::pow(long double a, long double b)
{
  return ::pow(a, b);
}
double me::maths::pow(double a, double b)
{
  return ::pow(a, b);
}
