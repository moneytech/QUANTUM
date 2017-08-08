// =============================================================================
// <float/types/special.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_C6C504010ABE40E9BD6CFE617E152C2E
#define H_C6C504010ABE40E9BD6CFE617E152C2E

// -----------------------------------------------------------------------------

#include "../../stdlib/float.h"

#ifdef __SIZEOF_FLOAT128__
  // Quadruple-precision floating point type characteristics
  #include <quadmath.h>
#endif

// -----------------------------------------------------------------------------
// Stay on the safe side of things and define the special floating point types
// only if they conform to IEEE 754
#if FP(IEEE754)
  // Determine the binary format of `float`
  #if (FLT_MANT_DIG == 24) && (FLT_MIN_10_EXP == -37) && (FLT_MAX_10_EXP == 38)
    // Single-precision (binary32)
    #define HAVE_FLT32
    #define FLT_BINARY 32

    typedef float float32_t;
    typedef float f32;
  #elif (FLT_MANT_DIG == 11) && (FLT_MIN_10_EXP == -14) && (FLT_MAX_10_EXP == 15)
    // Half-precision (binary16)
    #define HAVE_FLT16
    #define FLT_BINARY 16

    typedef float float16_t;
    typedef float f16;
  #endif

  // Determine the binary format of `double`
  #if (DBL_MANT_DIG == 53) && (DBL_MIN_10_EXP == -307) && (DBL_MAX_10_EXP == 308)
    // Double-precision (binary64)
    #define HAVE_FLT64
    #define DBL_BINARY 64

    typedef double float64_t;
    typedef double f64;
  #elif (DBL_MANT_DIG == 24) && (DBL_MIN_10_EXP == -37) && (DBL_MAX_10_EXP == 38)
    // Single-precision (binary32)
    #define DBL_BINARY 32

    #if (DBL_BINARY != FLT_BINARY)
      #define HAVE_FLT32

      typedef double float32_t;
      typedef double f32;
    #endif
  #elif (DBL_MANT_DIG == 11) && (DBL_MIN_10_EXP == -14) && (DBL_MAX_10_EXP == 15)
    // Half-precision (binary16)
    #define DBL_BINARY 16

    #if (DBL_BINARY != FLT_BINARY)
      #define HAVE_FLT16

      typedef double float16_t;
      typedef double f16;
    #endif
  #endif

  // Determine the binary format of `long double`
  #if (LDBL_MANT_DIG == 113) && (LDBL_MIN_10_EXP == -4931) && (LDBL_MAX_10_EXP == 4932)
    // Quadruple-precision (binary128)
    #define LDBL_BINARY 128
    #define HAVE_FLT128

    typedef ldouble float128_t;
    typedef ldouble f128;
  #elif (LDBL_MANT_DIG == 64) && (LDBL_MIN_10_EXP == -4931) && (LDBL_MAX_10_EXP == 4932)
    // Extended precision (80 bits)
    #define LDBL_BINARY 80
    #define HAVE_FLT80

    typedef ldouble float80_t;
    typedef ldouble f80;
  #elif (LDBL_MANT_DIG == 53) && (LDBL_MIN_10_EXP == -307) && (LDBL_MAX_10_EXP == 308)
    // Double-precision (binary64)
    #define LDBL_BINARY 64

    #if (LDBL_BINARY != DBL_BINARY)
      #define HAVE_FLT64

      typedef ldouble float64_t;
      typedef ldouble f64;
    #endif
  #elif (LDBL_MANT_DIG == 24) && (LDBL_MIN_10_EXP == -37) && (LDBL_MAX_10_EXP == 38)
    // Single-precision (binary32)
    #define LDBL_BINARY 32

    #if (LDBL_BINARY != DBL_BINARY) && (LDBL_BINARY != FLT_BINARY)
      #define HAVE_FLT32

      typedef ldouble float32_t;
      typedef ldouble f32;
    #endif
  #elif (LDBL_MANT_DIG == 11) && (LDBL_MIN_10_EXP == -14) && (LDBL_MAX_10_EXP == 15)
    // Half-precision (binary16)
    #define LDBL_BINARY 16

    #if (LDBL_BINARY != DBL_BINARY) && (LDBL_BINARY != FLT_BINARY)
      #define HAVE_FLT16

      typedef ldouble float16_t;
      typedef ldouble f16;
    #endif
  #endif

  // Extended precision floating point data type
  // provided as a compiler extension
  #if !HAVE(FLT80) && defined(__SIZEOF_FLOAT80__)
    #define HAVE_FLT80

    typedef __float80 float80_t;
    typedef __float80 f80;
  #endif

  // Quadruple-precision floating point data type
  // provided as a compiler extension
  #if !HAVE(FLT128) && defined(__SIZEOF_FLOAT128__)
    #define HAVE_FLT128

    typedef __float128 float128_t;
    typedef __float128 f128;
  #endif
#endif

// -----------------------------------------------------------------------------

#endif
