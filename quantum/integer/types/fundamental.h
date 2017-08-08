// =============================================================================
// <integer/types/fundamental.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_B9BD4CAB117A49BA94A9F5AD7F27BDE8
#define H_B9BD4CAB117A49BA94A9F5AD7F27BDE8

// -----------------------------------------------------------------------------

#include "../../stdlib/limits.h"

// =============================================================================
// Types
// -----------------------------------------------------------------------------
// Signed integral types
// -----------------------------------------------------------------------------

typedef signed char sbyte;

typedef signed char schar;
typedef signed short int sshort;
typedef signed int sint;
typedef signed long int slong;

typedef long long int llong;
typedef signed long long int sllong;

// -----------------------------------------------------------------------------
// Unsigned integral types
// -----------------------------------------------------------------------------

typedef unsigned char byte;
typedef unsigned char ubyte;

typedef unsigned char uchar;
typedef unsigned short int ushort;
typedef unsigned int uint;
typedef unsigned long int ulong;

typedef unsigned long long int ullong;

// =============================================================================
// Constants
// -----------------------------------------------------------------------------
// Determine the limits of `long long int`
// -----------------------------------------------------------------------------

#ifndef ULLONG_MAX
  #if (C_MSC_VER >= 1400)
    // Visual Studio 2005 and later come with `long long` limit definitions
    #define LLONG_MIN _I64_MIN
    #define LLONG_MAX _I64_MAX
    #define ULLONG_MAX _UI64_MAX
  #elif C(MSC)
    // These should reasonably work for previous versions
    #define LLONG_MIN (-9223372036854775807i64 - 1)
    #define LLONG_MAX 9223372036854775807i64
    #define ULLONG_MAX 0xFFFFFFFFFFFFFFFFui64
  #endif
#endif

// -----------------------------------------------------------------------------
// Determine the exact bit widths of fundamental integral types.
// (Equivalents of `CHAR_BIT` for all fundamental integral types.)
// -----------------------------------------------------------------------------

#define SHRT_BIT INT_BIT_MAX (USHRT_MAX)
#define INT_BIT INT_BIT_MAX (UINT_MAX)
#define LONG_BIT INT_BIT_MAX (ULONG_MAX)

#if C(MSC)
  #define LLONG_BIT 64
#else
  #define LLONG_BIT INT_BIT_MAX (ULLONG_MAX)
#endif

// -----------------------------------------------------------------------------
// Determine the maximum number of decimal digits
// each fundamental integral type can represent
// -----------------------------------------------------------------------------

#define SCHAR_DIG INT_DIG_MAX (CHAR_BIT - 1)
#define UCHAR_DIG INT_DIG_MAX (CHAR_BIT)

#if (CHAR_MIN == 0)
  #define CHAR_DIG UCHAR_DIG
#else
  #define CHAR_DIG SCHAR_DIG
#endif

#define SHRT_DIG INT_DIG_MAX (SHRT_BIT - 1)
#define USHRT_DIG INT_DIG_MAX (SHRT_BIT)

#define INT_DIG INT_DIG_MAX (INT_BIT - 1)
#define UINT_DIG INT_DIG_MAX (INT_BIT)

#define LONG_DIG INT_DIG_MAX (LONG_BIT - 1)
#define ULONG_DIG INT_DIG_MAX (LONG_BIT)

#if C(MSC)
  #define LLONG_DIG 19
  #define ULLONG_DIG 20
#else
  #define LLONG_DIG INT_DIG_MAX (LLONG_BIT - 1)
  #define ULLONG_DIG INT_DIG_MAX (LLONG_BIT)
#endif

// -----------------------------------------------------------------------------
// Determine the maximum number of hexadecimal digits
// each fundamental integral type can represent
// -----------------------------------------------------------------------------

#define CHAR_XDIG INT_XDIG_MAX (CHAR_BIT - 1)
#define UCHAR_XDIG INT_XDIG_MAX (CHAR_BIT)

#define SHRT_XDIG INT_XDIG_MAX (SHRT_BIT - 1)
#define USHRT_XDIG INT_XDIG_MAX (SHRT_BIT)

#define INT_XDIG INT_XDIG_MAX (INT_BIT - 1)
#define UINT_XDIG INT_XDIG_MAX (INT_BIT)

#define LONG_XDIG INT_XDIG_MAX (LONG_BIT - 1)
#define ULONG_XDIG INT_XDIG_MAX (LONG_BIT)

#if C(MSC)
  #define LLONG_XDIG 16
  #define ULLONG_XDIG 16
#else
  #define LLONG_XDIG INT_XDIG_MAX (LLONG_BIT - 1)
  #define ULLONG_XDIG INT_XDIG_MAX (LLONG_BIT)
#endif

// -----------------------------------------------------------------------------
// Determine the maximum number of octal digits
// each fundamental integral type can represent
// -----------------------------------------------------------------------------

#define CHAR_ODIG INT_ODIG_MAX (CHAR_BIT - 1)
#define UCHAR_ODIG INT_ODIG_MAX (CHAR_BIT)

#define SHRT_ODIG INT_ODIG_MAX (SHRT_BIT - 1)
#define USHRT_ODIG INT_ODIG_MAX (SHRT_BIT)

#define INT_ODIG INT_ODIG_MAX (INT_BIT - 1)
#define UINT_ODIG INT_ODIG_MAX (INT_BIT)

#define LONG_ODIG INT_ODIG_MAX (LONG_BIT - 1)
#define ULONG_ODIG INT_ODIG_MAX (LONG_BIT)

#if C(MSC)
  #define LLONG_ODIG 21
  #define ULLONG_ODIG 22
#else
  #define LLONG_ODIG INT_ODIG_MAX (LLONG_BIT - 1)
  #define ULLONG_ODIG INT_ODIG_MAX (LLONG_BIT)
#endif

// -----------------------------------------------------------------------------

#endif
