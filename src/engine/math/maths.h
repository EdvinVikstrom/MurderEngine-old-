#ifndef MATHS_H
  #define MATHS_H

#define PI     3.141592653589793D
#define H_PI   1.570796326794896D
#define TAU    6.283185307179586D

#define LPI    3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862L
#define LH_PI  1.57079632679489661923132169163975144209858469968755291048747229615390820314310449931L
#define LTAU   6.28318530717958647692528676655900576839433879875021164194988918461563281257241799724L

namespace maths {

  double rand();

  inline bool inbox(double x, double y, double fx, double fy, double tx, double ty)
  {
    return x >= fx && x <= fx + tx && y >= fy && y <= fy + ty;
  }

// Trigonometric functions

  /* cos */
  long double cosl(long double angle);
  double cosd(double angle);
  float cosf(float angle);

  /* sin */
  long double sinl(long double angle);
  double sind(double angle);
  float sinf(float angle);

  /* tan */
  long double tanl(long double angle);
  double tand(double angle);
  float tanf(float angle);

  /* acos */
  long double acosl(long double angle);
  double acosd(double angle);
  float acosf(float angle);

  /* asin */
  long double asinl(long double angle);
  double asind(double angle);
  float asinf(float angle);

  /* atan */
  long double atanl(long double angle);
  double atand(double angle);
  float atanf(float angle);

  /* atan2 */
  long double atan2l(long double angle);
  double atan2d(double angle);
  float atan2f(float angle);

  /* cos from sin */
  long double cosfsinl(long double sin, long double angle);
  double cosfsind(double sin, double angle);
  float cosfsinf(float sin, float angle);

// Hyperbolic functions

  /* sinh */
  long double sinhl(long double angle);
  double sinhd(double angle);
  float sinhf(float angle);

  /* cosh */
  long double coshl(long double angle);
  double coshd(double angle);
  float coshf(float angle);

  /* tanh */
  long double tanhl(long double angle);
  double tanhd(double angle);
  float tanhf(float angle);

  /* asinh */
  long double asinhl(long double angle);
  double asinhd(double angle);
  float asinhf(float angle);

  /* acosh */
  long double acoshl(long double angle);
  double acoshd(double angle);
  float acoshf(float angle);

  /* atanh */
  long double atanhl(long double angle);
  double atanhd(double angle);
  float atanhf(float angle);

// rounding

  /* ceil */
  long double ceill(long double a);
  double ceild(double a);
  float ceilf(float a);

  /* floor */
  long double floorl(long double a);
  double floord(double a);
  float floorf(float a);

  /* trunc */
  long double truncl(long double a);
  double truncd(double a);
  float truncf(float a);

  /* round */
  long double roundl(long double a);
  double roundd(double a);
  float roundf(float a);

  /* nearbyint */
  long double nearbyintl(long double a);
  double nearbyintd(double a);
  float nearbyintf(float a);

  /* rint */
  long double rintl(long double a);
  double rintd(double a);
  float rintf(float a);

/* Manipulation functions  */

  /* frexp */
  long double frexpl(long double a, int* exp);
  double frexpd(double a, int* exp);
  float frexpf(float a, int* exp);

  /* ldexp */
  long double ldexpl(long double a, int exp);
  double ldexpd(double a, int exp);
  float ldexpf(float a, int exp);

  /* modfl */
  long double modfl(long double a, long double* iptr);
  double modfd(double a, double* iptr);
  float modff(float a, float* iptr);

  /* scalbn */
  long double scalbnl(long double a, int exp);
  double scalbnd(double a, int exp);
  float scalbnf(float a, int exp);

  /* nextafter */
  long double nextafterl(long double from, long double to);
  double nextafterd(double from, double to);
  float nextafterf(float from, float to);

  /* nexttoward */
  long double nexttowardl(long double from, long double to);
  double nexttowardd(double from, long double to);
  float nexttowardf(float from, long double to);

  /* copysign */
  long double copysignl(long double a, long double b);
  double copysignd(double a, double b);
  float copysignf(float a, float b);

// ööö

  /* absolute */
  long double absl(long double a);
  double absd(double a);
  float absf(float a);
  int absi(int a);
  long absl(long a);

  /* max */
  long double maxl(long double a, long double b);
  double maxd(double a, double b);
  float maxf(float a, float b);
  int maxi(int a, int b);
  long maxl(long a, long b);

  /* min */
  long double minl(long double a, long double b);
  double mind(double a, double b);
  float minf(float a, float b);
  int mini(int a, int b);
  long minl(long a, long b);

// Exponential functions

  /* exp */
  long double expl(long double a);
  double expd(double a);

  long double exp2l(long double a);
  double exp2d(double a);

  long double expm1l(long double a);
  double expm1d(double a);

  /* log */
  long double logl(long double a);
  double logd(double a);

  long double log2l(long double a);
  double log2d(double a);

  long double log10l(long double a);
  double log10d(double a);

  long double log1pl(long double a);
  double log1pd(double a);

// Power functions

  /* sqrt */
  long double sqrtl(long double a);
  double sqrtl(double a);

  /* cbrt */
  long double cbrtl(long double a);
  double cbrtl(double a);

  /* hypot */
  long double hypotl(long double a, long double b);
  double hypotd(double a, double b);

  /* pow */
  long double powl(long double a, long double b);
  double powd(double a, double b);

};


#endif
