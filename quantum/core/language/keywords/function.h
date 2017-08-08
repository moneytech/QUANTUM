// =============================================================================
// <core/language/keywords/function.h>
//
// Function keywords.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_A64344C1D93442DA82AE61257E202F2A
#define H_A64344C1D93442DA82AE61257E202F2A

// -----------------------------------------------------------------------------
// C11 `noreturn` function specifier
#include "../../../stdlib/stdnoreturn.h"

// -----------------------------------------------------------------------------
// `inline`: suggest the function for inlining
#if !HAVE(C99)
  #if C(GNU)
    #define inline __inline__
  #elif C(MSC)
    #if (C_MSC_VER >= 1900)
      // Visual Studio 2015 and later support the `inline` specifier natively
    #elif (C_MSC_VER >= 1310)
      // Visual Studio 2003 .NET and later provide the `__inline` specifier
      #define inline __inline
    #else
      #define inline
    #endif
  #else
    #define inline
  #endif
#endif

// -----------------------------------------------------------------------------
// `forceinline`: force the compiler to inline the function
#if C(GNU)
  // For GCC or Clang the `always_inline` attribute *must* be
  // combined with the `inline` specifier
  #define forceinline inline __attribute__((always_inline))
#elif (C_MSC_VER >= 1310)
  // For Microsoft C `inline` specifier can be omitted
  #define forceinline __forceinline
#else
  // Fallback to simply `inline`
  #define forceinline inline
#endif

// -----------------------------------------------------------------------------
// `noinline`: instruct the compiler to never inline the function
#if C(GNU)
  #define noinline __attribute__((noinline))
#elif (C_MSC_VER >= 1310)
  #define noinline __declspec(noinline)
#endif

// -----------------------------------------------------------------------------
// `noreturn`: the function doesn't return to its point of invocation
#if !HAVE(C11)
  #if C(GNU)
    #if C(CXX)
      #define noreturn
    #else
      #define noreturn __attribute__((noreturn))
    #endif
  #elif (C_MSC_VER >= 1310)
    #define noreturn __declspec(noreturn)
  #else
    #define noreturn
  #endif
#endif

// -----------------------------------------------------------------------------

#endif
