// =============================================================================
// <integer/types/special.h>
//
// Machine-specific integral type definitions.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_C055D0D3323A4127BF87EE819D399CF9
#define H_C055D0D3323A4127BF87EE819D399CF9

// -----------------------------------------------------------------------------

#include "../../stdlib/stdint.h"

#if C(CXX)
  // `int_fastx_t` and `int_leastx_t` aren't available without this
  #include <cstdint>
#endif

// =============================================================================
// Constants
// -----------------------------------------------------------------------------
// 8-bit+
// -----------------------------------------------------------------------------

#ifdef INT8_MAX
  #define HAVE_INT8

  #define INT8_DIG 3
  #define UINT8_DIG 3

  #define INT8_XDIG 2
  #define UINT8_XDIG 2

  #define INT8_ODIG 3
  #define UINT8_ODIG 3
#endif

// -----------------------------------------------------------------------------

#if (INT_FAST8_MAX == INT8_MAX)
  #define INT_FAST8_BIT 8

  #define INT_FAST8_DIG INT8_DIG
  #define UINT_FAST8_DIG UINT8_DIG

  #define INT_FAST8_XDIG INT8_XDIG
  #define UINT_FAST8_XDIG UINT8_XDIG

  #define INT_FAST8_ODIG INT8_ODIG
  #define UINT_FAST8_ODIG UINT8_ODIG
#else
  #define INT_FAST8_BIT INT_BIT_MAX (UINT_FAST8_MAX)

  #define INT_FAST8_DIG INT_DIG_MAX (INT_FAST8_BIT - 1)
  #define UINT_FAST8_DIG INT_DIG_MAX (INT_FAST8_BIT)

  #define INT_FAST8_XDIG INT_XDIG_MAX (INT_FAST8_BIT - 1)
  #define UINT_FAST8_XDIG INT_XDIG_MAX (INT_FAST8_BIT)

  #define INT_FAST8_ODIG INT_ODIG_MAX (INT_FAST8_BIT - 1)
  #define UINT_FAST8_ODIG INT_ODIG_MAX (INT_FAST8_BIT)
#endif

// -----------------------------------------------------------------------------

#if (INT_LEAST8_MAX == INT8_MAX)
  #define INT_LEAST8_BIT 8

  #define INT_LEAST8_DIG INT8_DIG
  #define UINT_LEAST8_DIG UINT8_DIG

  #define INT_LEAST8_XDIG INT8_XDIG
  #define UINT_LEAST8_XDIG UINT8_XDIG

  #define INT_LEAST8_ODIG INT8_ODIG
  #define UINT_LEAST8_ODIG UINT8_ODIG
#else
  #define INT_LEAST8_BIT INT_BIT_MAX (UINT_LEAST8_MAX)

  #define INT_LEAST8_DIG INT_DIG_MAX (INT_LEAST8_BIT - 1)
  #define UINT_LEAST8_DIG INT_DIG_MAX (INT_LEAST8_BIT)

  #define INT_LEAST8_XDIG INT_XDIG_MAX (INT_LEAST8_BIT - 1)
  #define UINT_LEAST8_XDIG INT_XDIG_MAX (INT_LEAST8_BIT)

  #define INT_LEAST8_ODIG INT_ODIG_MAX (INT_LEAST8_BIT - 1)
  #define UINT_LEAST8_ODIG INT_ODIG_MAX (INT_LEAST8_BIT)
#endif

// -----------------------------------------------------------------------------
// 16-bit+
// -----------------------------------------------------------------------------

#ifdef INT16_MAX
  #define HAVE_INT16

  #define INT16_DIG 5
  #define UINT16_DIG 5

  #define INT16_XDIG 4
  #define UINT16_XDIG 4

  #define INT16_ODIG 5
  #define UINT16_ODIG 6
#endif

// -----------------------------------------------------------------------------

#if (INT_FAST16_MAX == INT16_MAX)
  #define INT_FAST16_BIT 16

  #define INT_FAST16_DIG INT16_DIG
  #define UINT_FAST16_DIG UINT16_DIG

  #define INT_FAST16_XDIG INT16_XDIG
  #define UINT_FAST16_XDIG UINT16_XDIG

  #define INT_FAST16_ODIG INT16_ODIG
  #define UINT_FAST16_ODIG UINT16_ODIG
#else
  #define INT_FAST16_BIT INT_BIT_MAX (UINT_FAST16_MAX)

  #define INT_FAST16_DIG INT_DIG_MAX (INT_FAST16_BIT - 1)
  #define UINT_FAST16_DIG INT_DIG_MAX (INT_FAST16_BIT)

  #define INT_FAST16_XDIG INT_XDIG_MAX (INT_FAST16_BIT - 1)
  #define UINT_FAST16_XDIG INT_XDIG_MAX (INT_FAST16_BIT)

  #define INT_FAST16_ODIG INT_ODIG_MAX (INT_FAST16_BIT - 1)
  #define UINT_FAST16_ODIG INT_ODIG_MAX (INT_FAST16_BIT)
#endif

// -----------------------------------------------------------------------------

#if (INT_LEAST16_MAX == INT16_MAX)
  #define INT_LEAST16_BIT 16

  #define INT_LEAST16_DIG INT16_DIG
  #define UINT_LEAST16_DIG UINT16_DIG

  #define INT_LEAST16_XDIG INT16_XDIG
  #define UINT_LEAST16_XDIG UINT16_XDIG

  #define INT_LEAST16_ODIG INT16_ODIG
  #define UINT_LEAST16_ODIG UINT16_ODIG
#else
  #define INT_LEAST16_BIT INT_BIT_MAX (UINT_LEAST16_MAX)

  #define INT_LEAST16_DIG INT_DIG_MAX (INT_LEAST16_BIT - 1)
  #define UINT_LEAST16_DIG INT_DIG_MAX (INT_LEAST16_BIT)

  #define INT_LEAST16_XDIG INT_XDIG_MAX (INT_LEAST16_BIT - 1)
  #define UINT_LEAST16_XDIG INT_XDIG_MAX (INT_LEAST16_BIT)

  #define INT_LEAST16_ODIG INT_ODIG_MAX (INT_LEAST16_BIT - 1)
  #define UINT_LEAST16_ODIG INT_ODIG_MAX (INT_LEAST16_BIT)
#endif

// -----------------------------------------------------------------------------
// 32-bit+
// -----------------------------------------------------------------------------

#ifdef INT32_MAX
  #define HAVE_INT32

  #define INT32_DIG 10
  #define UINT32_DIG 10

  #define INT32_XDIG 8
  #define UINT32_XDIG 8

  #define INT32_ODIG 11
  #define UINT32_ODIG 11
#endif

// -----------------------------------------------------------------------------

#if (INT_FAST32_MAX == INT32_MAX)
  #define INT_FAST32_BIT 32

  #define INT_FAST32_DIG INT32_DIG
  #define UINT_FAST32_DIG UINT32_DIG

  #define INT_FAST32_XDIG INT32_XDIG
  #define UINT_FAST32_XDIG UINT32_XDIG

  #define INT_FAST32_ODIG INT32_ODIG
  #define UINT_FAST32_ODIG UINT32_ODIG
#else
  #define INT_FAST32_BIT INT_BIT_MAX (UINT_FAST32_MAX)

  #define INT_FAST32_DIG INT_DIG_MAX (INT_FAST32_BIT - 1)
  #define UINT_FAST32_DIG INT_DIG_MAX (INT_FAST32_BIT)

  #define INT_FAST32_XDIG INT_XDIG_MAX (INT_FAST32_BIT - 1)
  #define UINT_FAST32_XDIG INT_XDIG_MAX (INT_FAST32_BIT)

  #define INT_FAST32_ODIG INT_ODIG_MAX (INT_FAST32_BIT - 1)
  #define UINT_FAST32_ODIG INT_ODIG_MAX (INT_FAST32_BIT)
#endif

// -----------------------------------------------------------------------------

#if (INT_LEAST32_MAX == INT32_MAX)
  #define INT_LEAST32_BIT 32

  #define INT_LEAST32_DIG INT32_DIG
  #define UINT_LEAST32_DIG UINT32_DIG

  #define INT_LEAST32_XDIG INT32_XDIG
  #define UINT_LEAST32_XDIG UINT32_XDIG

  #define INT_LEAST32_ODIG INT32_ODIG
  #define UINT_LEAST32_ODIG UINT32_ODIG
#else
  #define INT_LEAST32_BIT INT_BIT_MAX (UINT_LEAST32_MAX)

  #define INT_LEAST32_DIG INT_DIG_MAX (INT_LEAST32_BIT - 1)
  #define UINT_LEAST32_DIG INT_DIG_MAX (INT_LEAST32_BIT)

  #define INT_LEAST32_XDIG INT_XDIG_MAX (INT_LEAST32_BIT - 1)
  #define UINT_LEAST32_XDIG INT_XDIG_MAX (INT_LEAST32_BIT)

  #define INT_LEAST32_ODIG INT_ODIG_MAX (INT_LEAST32_BIT - 1)
  #define UINT_LEAST32_ODIG INT_ODIG_MAX (INT_LEAST32_BIT)
#endif

// -----------------------------------------------------------------------------
// 64-bit+
// -----------------------------------------------------------------------------

#ifdef INT64_MAX
  #define HAVE_INT64

  #define INT64_DIG 19
  #define UINT64_DIG 20

  #define INT64_XDIG 16
  #define UINT64_XDIG 16

  #define INT64_ODIG 21
  #define UINT64_ODIG 22
#endif

// -----------------------------------------------------------------------------

#if (INT_FAST64_MAX == INT64_MAX)
  #define INT_FAST64_BIT 64

  #define INT_FAST64_DIG INT64_DIG
  #define UINT_FAST64_DIG UINT64_DIG

  #define INT_FAST64_XDIG INT64_XDIG
  #define UINT_FAST64_XDIG UINT64_XDIG

  #define INT_FAST64_ODIG INT64_ODIG
  #define UINT_FAST64_ODIG UINT64_ODIG
#else
  #define INT_FAST64_BIT INT_BIT_MAX (UINT_FAST64_MAX)

  #define INT_FAST64_DIG INT_DIG_MAX (INT_FAST64_BIT - 1)
  #define UINT_FAST64_DIG INT_DIG_MAX (INT_FAST64_BIT)

  #define INT_FAST64_XDIG INT_XDIG_MAX (INT_FAST64_BIT - 1)
  #define UINT_FAST64_XDIG INT_XDIG_MAX (INT_FAST64_BIT)

  #define INT_FAST64_ODIG INT_ODIG_MAX (INT_FAST64_BIT - 1)
  #define UINT_FAST64_ODIG INT_ODIG_MAX (INT_FAST64_BIT)
#endif

// -----------------------------------------------------------------------------

#if (INT_LEAST64_MAX == INT64_MAX)
  #define INT_LEAST64_BIT 64

  #define INT_LEAST64_DIG INT64_DIG
  #define UINT_LEAST64_DIG UINT64_DIG

  #define INT_LEAST64_XDIG INT64_XDIG
  #define UINT_LEAST64_XDIG UINT64_XDIG

  #define INT_LEAST64_ODIG INT64_ODIG
  #define UINT_LEAST64_ODIG UINT64_ODIG
#else
  #define INT_LEAST64_BIT INT_BIT_MAX (UINT_LEAST64_MAX)

  #define INT_LEAST64_DIG INT_DIG_MAX (INT_LEAST64_BIT - 1)
  #define UINT_LEAST64_DIG INT_DIG_MAX (INT_LEAST64_BIT)

  #define INT_LEAST64_XDIG INT_XDIG_MAX (INT_LEAST64_BIT - 1)
  #define UINT_LEAST64_XDIG INT_XDIG_MAX (INT_LEAST64_BIT)

  #define INT_LEAST64_ODIG INT_ODIG_MAX (INT_LEAST64_BIT - 1)
  #define UINT_LEAST64_ODIG INT_ODIG_MAX (INT_LEAST64_BIT)
#endif

// -----------------------------------------------------------------------------
// 128-bit+
// -----------------------------------------------------------------------------

#ifdef __SIZEOF_INT128__
  #define HAVE_INT128
  #define HAVE_INT_LEAST128

  #define INT128_MIN ((s128)1 << 127)
  #define INT128_MAX (~(s128)0 >> 1)
  #define UINT128_MAX ~(u128)0

  #define INT128_DIG 39
  #define UINT128_DIG 39

  #define INT128_XDIG 32
  #define UINT128_XDIG 32

  #define INT128_ODIG 43
  #define UINT128_ODIG 43

  // Fast
  #define INT_FAST128_BIT 128

  #define INT_FAST128_MIN INT128_MIN
  #define INT_FAST128_MAX INT128_MAX
  #define UINT_FAST128_MAX UINT128_MAX

  #define INT_FAST128_DIG INT128_DIG
  #define UINT_FAST128_DIG UINT128_DIG

  #define INT_FAST128_XDIG INT128_XDIG
  #define UINT_FAST128_XDIG UINT128_XDIG

  #define INT_FAST128_ODIG INT128_ODIG
  #define UINT_FAST128_ODIG UINT128_ODIG

  // Least
  #define INT_LEAST128_BIT 128

  #define INT_LEAST128_MIN INT128_MIN
  #define INT_LEAST128_MAX INT128_MAX
  #define UINT_LEAST128_MAX UINT128_MAX

  #define INT_LEAST128_DIG INT128_DIG
  #define UINT_LEAST128_DIG UINT128_DIG

  #define INT_LEAST128_XDIG INT128_XDIG
  #define UINT_LEAST128_XDIG UINT128_XDIG

  #define INT_LEAST128_ODIG INT128_ODIG
  #define UINT_LEAST128_ODIG UINT128_ODIG
#endif

// -----------------------------------------------------------------------------
// Maximum
// -----------------------------------------------------------------------------

#if C(MSC)
  #define INTMAX_BIT 64

  #define INTMAX_DIG INT64_DIG
  #define UINTMAX_DIG UINT64_DIG

  #define INTMAX_XDIG INT64_XDIG
  #define UINTMAX_XDIG UINT64_XDIG

  #define INTMAX_ODIG INT64_ODIG
  #define UINTMAX_ODIG UINT64_ODIG
#else
  #define INTMAX_BIT INT_BIT_MAX (UINTMAX_MAX)

  #define INTMAX_DIG INT_DIG_MAX (INTMAX_BIT - 1)
  #define UINTMAX_DIG INT_DIG_MAX (INTMAX_BIT)

  #define INTMAX_XDIG INT_XDIG_MAX (INTMAX_BIT - 1)
  #define UINTMAX_XDIG INT_XDIG_MAX (INTMAX_BIT)

  #define INTMAX_ODIG INT_ODIG_MAX (INTMAX_BIT - 1)
  #define UINTMAX_ODIG INT_ODIG_MAX (INTMAX_BIT)
#endif

// -----------------------------------------------------------------------------
// Pointer
// -----------------------------------------------------------------------------

#if C(MSC)
  #if OS(WIN32)
    #define INTPTR_BIT 32

    #define INTPTR_DIG INT32_DIG
    #define UINTPTR_DIG UINT32_DIG

    #define INTPTR_XDIG INT32_XDIG
    #define UINTPTR_XDIG UINT32_XDIG

    #define INTPTR_ODIG INT32_ODIG
    #define UINTPTR_ODIG UINT32_ODIG
  #elif OS(WIN64)
    #define INTPTR_BIT 64

    #define INTPTR_DIG INT64_DIG
    #define UINTPTR_DIG UINT64_DIG

    #define INTPTR_XDIG INT64_XDIG
    #define UINTPTR_XDIG UINT64_XDIG

    #define INTPTR_ODIG INT64_ODIG
    #define UINTPTR_ODIG UINT64_ODIG
  #endif
#else
  #define INTPTR_BIT INT_BIT_MAX (UINTPTR_MAX)

  #define INTPTR_DIG INT_DIG_MAX (INTPTR_BIT - 1)
  #define UINTPTR_DIG INT_DIG_MAX (INTPTR_BIT)

  #define INTPTR_XDIG INT_XDIG_MAX (INTPTR_BIT - 1)
  #define UINTPTR_XDIG INT_XDIG_MAX (INTPTR_BIT)

  #define INTPTR_ODIG INT_ODIG_MAX (INTPTR_BIT - 1)
  #define UINTPTR_ODIG INT_ODIG_MAX (INTPTR_BIT)
#endif

// =============================================================================
// Types
// -----------------------------------------------------------------------------
// 8-bit+
// -----------------------------------------------------------------------------

#if HAVE(INT8)
  typedef int8_t s8;
  typedef uint8_t u8;
#endif

typedef int_fast8_t sf8;
typedef uint_fast8_t uf8;

typedef int_least8_t sl8;
typedef uint_least8_t ul8;

// -----------------------------------------------------------------------------
// 16-bit+
// -----------------------------------------------------------------------------

#if HAVE(INT16)
  typedef int16_t s16;
  typedef uint16_t u16;
#endif

typedef int_fast16_t sf16;
typedef uint_fast16_t uf16;

typedef int_least16_t sl16;
typedef uint_least16_t ul16;

// -----------------------------------------------------------------------------
// 32-bit+
// -----------------------------------------------------------------------------

#if HAVE(INT32)
  typedef int32_t s32;
  typedef uint32_t u32;
#endif

typedef int_fast32_t sf32;
typedef uint_fast32_t uf32;

typedef int_least32_t sl32;
typedef uint_least32_t ul32;

// -----------------------------------------------------------------------------
// 64-bit+
// -----------------------------------------------------------------------------

#if HAVE(INT64)
  typedef int64_t s64;
  typedef uint64_t u64;
#endif

typedef int_fast64_t sf64;
typedef uint_fast64_t uf64;

typedef int_least64_t sl64;
typedef uint_least64_t ul64;

// -----------------------------------------------------------------------------
// 128-bit+
// -----------------------------------------------------------------------------

#if HAVE(INT128)
  typedef __int128_t int128_t;
  typedef __uint128_t uint128_t;

  typedef __int128_t int_fast128_t;
  typedef __uint128_t uint_fast128_t;

  typedef __int128_t int_least128_t;
  typedef __uint128_t uint_least128_t;

  typedef int128_t s128;
  typedef uint128_t u128;

  typedef int128_t sf128;
  typedef uint128_t uf128;

  typedef int128_t sl128;
  typedef uint128_t ul128;
#endif

// -----------------------------------------------------------------------------

#endif
