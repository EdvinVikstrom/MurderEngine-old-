#ifndef MATHS_H
  #define MATHS_H

#define PI            3.141592653589793D
#define H_PI          1.570796326794896D
#define TAU           6.283185307179586D

#define LPI           3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862L
#define LH_PI         1.57079632679489661923132169163975144209858469968755291048747229615390820314310449931L
#define LTAU          6.28318530717958647692528676655900576839433879875021164194988918461563281257241799724L

#define TO_RADIANS    0.017453292519943295D
#define TO_DEGREES    57.29577951308232D

#define ME_TYPE_FLOAT

#ifdef ME_TYPE_FLOAT
  #define real_t float
#elif ME_TYPE_DOUBLE
  #define real_t double
#endif

namespace me {

  namespace maths {

      double rand();

      inline bool isnan(long double a)
      {
        return a != a;
      }
      inline bool isnan(double a)
      {
        return a != a;
      }
      inline bool isnan(float a)
      {
        return a != a;
      }

      inline bool infinite(float f)
      {
        return f == 1.0F / 0.0 || f == -1.0F / 0.0;
      }

      inline double to_radians(double degrees)
      {
        return degrees * TO_RADIANS;
      }

      inline double to_degrees(double radians)
      {
        return radians * TO_DEGREES;
      }

      inline float to_radians(float degrees)
      {
        return degrees * (float) TO_RADIANS;
      }

      inline float to_degrees(float radians)
      {
        return radians * (float) TO_DEGREES;
      }

    // Trigonometric functions

      /* cos */
      long double cos(long double angle);
      double cos(double angle);
      float cos(float angle);

      /* sin */
      long double sin(long double angle);
      double sin(double angle);
      float sin(float angle);

      /* tan */
      long double tan(long double angle);
      double tan(double angle);
      float tan(float angle);

      /* acos */
      long double acos(long double angle);
      double acos(double angle);
      float acos(float angle);

      /* asin */
      long double asin(long double angle);
      double asin(double angle);
      float asin(float angle);

      /* atan */
      long double atan(long double angle);
      double atan(double angle);
      float atan(float angle);

      /* atan2 */
      long double atan2(long double y, long double x);
      double atan2(double y, double x);
      float atan2(float y, float x);

      /* cos from sin */
      long double cosfsin(long double sin, long double angle);
      double cosfsin(double sin, double angle);
      float cosfsin(float sin, float angle);

    // Hyperbolic functions

      /* sinh */
      long double sinh(long double angle);
      double sinh(double angle);
      float sinh(float angle);

      /* cosh */
      long double cosh(long double angle);
      double cosh(double angle);
      float cosh(float angle);

      /* tanh */
      long double tanh(long double angle);
      double tanh(double angle);
      float tanh(float angle);

      /* asinh */
      long double asinh(long double angle);
      double asinh(double angle);
      float asinh(float angle);

      /* acosh */
      long double acosh(long double angle);
      double acosh(double angle);
      float acosh(float angle);

      /* atanh */
      long double atanh(long double angle);
      double atanh(double angle);
      float atanh(float angle);

    // rounding

      /* ceil */
      long double ceil(long double a);
      double ceil(double a);
      float ceil(float a);

      /* floor */
      long double floor(long double a);
      double floor(double a);
      float floor(float a);

      /* trunc */
      long double trunc(long double a);
      double trunc(double a);
      float trunc(float a);

      /* round */
      long double round(long double a);
      double round(double a);
      float round(float a);

      /* nearbyint */
      long double nearbyint(long double a);
      double nearbyint(double a);
      float nearbyint(float a);

      /* rint */
      long double rint(long double a);
      double rint(double a);
      float rint(float a);

    /* Manipulation functions  */

      /* frexp */
      long double frexp(long double a, int* exp);
      double frexp(double a, int* exp);
      float frexp(float a, int* exp);

      /* ldexp */
      long double ldexp(long double a, int exp);
      double ldexp(double a, int exp);
      float ldexp(float a, int exp);

      /* modfl */
      long double modf(long double a, long double* iptr);
      double modf(double a, double* iptr);
      float modf(float a, float* iptr);

      /* scalbn */
      long double scalbn(long double a, int exp);
      double scalbn(double a, int exp);
      float scalbn(float a, int exp);

      /* nextafter */
      long double nextafter(long double from, long double to);
      double nextafter(double from, double to);
      float nextafter(float from, float to);

      /* nexttoward */
      long double nexttoward(long double from, long double to);
      double nexttoward(double from, long double to);
      float nexttoward(float from, long double to);

      /* copysign */
      long double copysign(long double a, long double b);
      double copysign(double a, double b);
      float copysign(float a, float b);

      long double sign(long double a);
      double sign(double a);
      float sign(float a);

    // ööö

      /* absolute */
      long double abs(long double a);
      double abs(double a);
      float abs(float a);
      int abs(int a);
      long absl(long a);

      /* max */
      long double max(long double a, long double b);
      double max(double a, double b);
      float max(float a, float b);
      int max(int a, int b);
      long maxl(long a, long b);

      /* min */
      long double min(long double a, long double b);
      double min(double a, double b);
      float min(float a, float b);
      int min(int a, int b);
      long minl(long a, long b);

    // Exponential functions

      /* exp */
      long double exp(long double a);
      double exp(double a);

      long double exp2(long double a);
      double exp2(double a);

      long double expm1(long double a);
      double expm1(double a);

      /* log */
      long double log(long double a);
      double log(double a);

      long double log2(long double a);
      double log2(double a);

      long double log10(long double a);
      double log10(double a);

      long double log1p(long double a);
      double log1p(double a);

    // Power functions

      /* sqrt */
      long double sqrt(long double a);
      double sqrt(double a);

      /* cbrt */
      long double cbrt(long double a);
      double cbrtl(double a);

      /* hypot */
      long double hypot(long double a, long double b);
      double hypot(double a, double b);

      /* pow */
      long double pow(long double a, long double b);
      double pow(double a, double b);

  };

};


#endif
