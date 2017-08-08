// =============================================================================
// <core/platform/compiler.h>
//
// C compiler definitions.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_B473A60DD6934B288CC54E707246A88C
#define H_B473A60DD6934B288CC54E707246A88C

// -----------------------------------------------------------------------------

#define C(feat) (defined(C_##feat))

// -----------------------------------------------------------------------------
// Determine the C compiler
// -----------------------------------------------------------------------------

#if defined(__clang__)
  // Clang LLVM compiler front end
  #define C_CLANG
  #define C_CLANG_VER ((__clang_major__ * 10000) + (__clang_minor__ * 100) + __clang_patchlevel__)
#elif defined(__GNUC__)
  // GNU Compiler Collection
  #define C_GCC
  #define C_GCC_VER ((__GNUC__ * 10000) + (__GNUC_MINOR__ * 100) + __GNUC_PATCHLEVEL__)
#elif defined(_MSC_VER)
  // Microsoft C compiler
  #define C_MSC
  #define C_MSC_VER _MSC_VER
#elif defined(__INTEL_COMPILER) || defined(__ICC) || defined(__ECC)
  // Intel C compiler
  #define C_ICC
#endif

// -----------------------------------------------------------------------------
// Shorthand macro for features shared by both Clang and GCC
#ifdef __GNUC__
  #define C_GNU
#endif

// -----------------------------------------------------------------------------
// Determine the Visual Studio version
// -----------------------------------------------------------------------------

#if C(MSC)
  #if (C_MSC_VER == 1900)
    #define C_MSVS_VER 2015
  #elif (C_MSC_VER == 1800)
    #define C_MSVS_VER 2013
  #elif (C_MSC_VER == 1700)
    #define C_MSVS_VER 2012
  #elif (C_MSC_VER == 1600)
    #define C_MSVS_VER 2010
  #elif (C_MSC_VER == 1500)
    #define C_MSVS_VER 2008
  #elif (C_MSC_VER == 1400)
    #define C_MSVS_VER 2005
  #elif (C_MSC_VER == 1310)
    #define C_MSVS_VER 2003
  #elif (C_MSC_VER == 1300)
    #define C_MSVS_VER 7
  #elif (C_MSC_VER == 1200)
    #define C_MSVS_VER 6
  #elif (C_MSC_VER == 1100)
    #define C_MSVS_VER 5
  #endif
#endif

// -----------------------------------------------------------------------------
// Detect the MinGW compiler
// -----------------------------------------------------------------------------

#ifdef __MINGW32__
  #define C_MINGW32
#endif

#ifdef __MINGW64__
  #define C_MINGW64
#endif

#if C(MINGW32) || C(MINGW64)
  #define C_MINGW
#endif

// -----------------------------------------------------------------------------
// Determine the most recent C standard version supported by the compiler
// -----------------------------------------------------------------------------
// Standard version
// -----------------------------------------------------------------------------

#define C_STD90_VER 199000L
#define C_STD95_VER 199409L
#define C_STD99_VER 199901L
#define C_STD11_VER 201112L

#if defined(__STDC_VERSION__)
  #define C_STD_VER __STDC_VERSION__
#elif defined(__ANSI__)
  #define C_STD_VER C_STD90_VER
#endif

// -----------------------------------------------------------------------------
// Boolean flags
// -----------------------------------------------------------------------------

#if (C_STD_VER > C_STD99_VER)
  #define HAVE_C11
  #define HAVE_C99
  #define HAVE_C95
#elif (C_STD_VER > C_STD95_VER)
  #define HAVE_C99
  #define HAVE_C95
#elif (C_STD_VER > C_STD90_VER)
  #define HAVE_C95
#endif

// -----------------------------------------------------------------------------
// Optional features
// -----------------------------------------------------------------------------

#ifdef __STDC_ANALYZABLE__
  #define HAVE_C_ANALYZABLE
#endif

#ifdef __STDC_LIB_EXT1__
  #define HAVE_C_BOUNDS_CHECKS
#endif

#ifndef __STDC_NO_THREADS__
  #define HAVE_C_THREADS
#endif

#ifndef __STDC_NO_ATOMICS__
  #define HAVE_C_ATOMICS
#endif

#ifdef __STDC_IEC_559__
  #define HAVE_C_IEEE754
#endif

#ifndef __STDC_NO_COMPLEX__
  #define HAVE_C_COMPLEX
#endif

#ifdef __STDC_IEC_559_COMPLEX__
  #define HAVE_C_IEEE754_COMPLEX
#endif

#ifndef __STDC_NO_VLA__
  #define HAVE_C_VLA
#endif

// -----------------------------------------------------------------------------
// Detect the C++ compiler
// -----------------------------------------------------------------------------

#ifdef __cplusplus
  #define C_CXX
  #define C_CXX_VER __cplusplus
#endif

// -----------------------------------------------------------------------------

#endif
