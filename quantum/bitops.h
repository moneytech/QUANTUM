// =============================================================================
// <bitops.h>
//
// Access and manipulate individual bits of integral variables.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_AF65D935F9114F679E6DE8C863E6C260
#define H_AF65D935F9114F679E6DE8C863E6C260

// -----------------------------------------------------------------------------

#if C(MSC)
  #include "intrinsics.h"
#endif

// =============================================================================
// Bit manipulation
// -----------------------------------------------------------------------------
// The integer type is specified manually to prevent shifting `1u` out of range
#define bit_get(t, i, n) ((i) & ((t)1u << (n)))
#define bit_set(t, i, n) ((i) | ((t)1u << (n)))
#define bit_tgl(t, i, n) ((i) ^ ((t)1u << (n)))
#define bit_clr(t, i, n) ((i) & ~((t)1u << (n)))

// -----------------------------------------------------------------------------
// Variant of `bit_get()` that returns a boolean value
#define bit_is_set(i, n) (((i) >> (n)) & 1u)

// -----------------------------------------------------------------------------
// Similar macros for bitmasks (like flags)
#define flag_get(i, f) ((i) & (f))
#define flag_set(i, f) ((i) | (f))
#define flag_tgl(i, f) ((i) ^ (f))
#define flag_clr(i, f) ((i) & ~(f))

// =============================================================================
// Bit scanning
// -----------------------------------------------------------------------------
// Bit scan forward
// -----------------------------------------------------------------------------

#if C(MSC)
  #pragma intrinsic(_BitScanForward)
#endif

// -----------------------------------------------------------------------------

#if HAVE(INT32)
static inline uint bsf32 (u32 i)
{
  register uint bit;

#if C(GNU) && (INT_BIT == 32)
  bit = __builtin_ffs (i) - 1;
#elif C(GNU) && (LONG_BIT == 32)
  bit = __builtin_ffsl (i) - 1;
#elif C(MSC)
  _BitScanForward (&bit, i);
#else
  static const uint debruijn_tbl[32] =
  {
     0, 1, 10,  2, 11, 14, 22,  3, 30, 12, 15, 17, 19, 23, 26, 4,
    31, 9, 13, 21, 29, 16, 18, 25,  8, 20, 28, 24,  7, 27,  6, 5
  };

  // Extract the LSB
  i &= -i;

  bit = debruijn_tbl[(i * 0x07C4ACDDu) >> 27];
#endif

  return bit;
}
#endif // HAVE(INT32)

// -----------------------------------------------------------------------------

#if HAVE(INT64)
static inline uint bsf64 (u64 i)
{
  register uint bit;

#if C(GNU) && (LONG_BIT == 64)
  bit = __builtin_ffsl (i) - 1;
#elif C(GNU) && (LLONG_BIT == 64)
  bit = __builtin_ffsll (i) - 1;
#elif C(MSC)
  _BitScanForward64 (&bit, i);
#else
  static const uint debruijn_tbl[64] =
  {
     0,  1, 12,  2, 13, 17, 30,  3, 14, 23, 18, 42, 26, 31, 49,  4,
    62, 15, 21, 24, 19, 35, 37, 43, 27, 39, 32, 54, 45, 50, 57,  5,
    63, 11, 16, 29, 22, 41, 25, 48, 61, 20, 34, 36, 38, 53, 44, 56,
    10, 28, 40, 47, 60, 33, 52, 55,  9, 46, 59, 51,  8, 58,  7,  6
  };

  i &= -i;

  bit = debruijn_tbl[(i * 0x03F08A4C6ACB9DBDu) >> 58];
#endif

  return bit;
}
#endif // HAVE(INT64)

// -----------------------------------------------------------------------------

#if HAVE(INT128)
static inline uint bsf128 (u128 i)
{
  u64 lo = i & 0xFFFFFFFFFFFFFFFFu;

  if (lo != 0) return bsf64 (lo);

  u64 hi = i >> 64;

  return 64u + bsf64 (hi);
}
#endif

// -----------------------------------------------------------------------------
// Deprecated BSD bit scanning function definitions
// -----------------------------------------------------------------------------

#ifndef ffs
  #if (INT_BIT == 32)
    #define ffs(i) (bsf32 (i) + 1u)
  #elif (INT_BIT == 64)
    #define ffs(i) (bsf64 (i) + 1u)
  #endif
#endif

#ifndef ffsl
  #if (LONG_BIT == 32)
    #define ffsl(i) (bsf32 (i) + 1u)
  #elif (LONG_BIT == 64)
    #define ffsl(i) (bsf64 (i) + 1u)
  #endif
#endif

#ifndef ffsll
  #if (LLONG_BIT == 32)
    #define ffsll(i) (bsf32 (i) + 1u)
  #elif (LLONG_BIT == 64)
    #define ffsll(i) (bsf64 (i) + 1u)
  #endif
#endif

// -----------------------------------------------------------------------------
// Bit scan reverse
// -----------------------------------------------------------------------------

#if C(MSC)
  #pragma intrinsic(_BitScanReverse)
#endif

// -----------------------------------------------------------------------------

#if HAVE(INT32)
static inline uint bsr32 (u32 i)
{
  register uint bit;

#if C(GNU) && (INT_BIT == 32)
  bit = 31 - __builtin_clz (i);
#elif C(GNU) && (LONG_BIT == 32)
  bit = 31 - __builtin_clzl (i);
#elif C(MSC)
  _BitScanReverse (&bit, i);
#else
  static const uint debruijn_tbl[32] =
  {
     0,  9,  1, 10, 13, 21,  2, 29, 11, 14, 16, 18, 22, 25, 3, 30,
     8, 12, 20, 28, 15, 17, 24,  7, 19, 27, 23,  6, 26,  5, 4, 31
  };

  // Round to one less than a next power of two
  // (broadcast the MSB to all lower bits)
  i |= i >> 1;
  i |= i >> 2;
  i |= i >> 4;
  i |= i >> 8;
  i |= i >> 16;

  bit = debruijn_tbl[(i * 0x07C4ACDDu) >> 27];
#endif

  return bit;
}
#endif // HAVE(INT32)

// -----------------------------------------------------------------------------

#if HAVE(INT64)
static inline uint bsr64 (u64 i)
{
  register uint bit;

#if C(GNU) && (LONG_BIT == 64)
  bit = 63 - __builtin_clzl (i);
#elif C(GNU) && (LLONG_BIT == 64)
  bit = 63 - __builtin_clzll (i);
#elif C(MSC)
  _BitScanReverse64 (&bit, i);
#else
  static const uint debruijn_tbl[64] =
  {
     0, 11,  1, 12, 16, 29,  2, 13, 22, 17, 41, 25, 30, 48,  3, 61,
    14, 20, 23, 18, 34, 36, 42, 26, 38, 31, 53, 44, 49, 56,  4, 62,
    10, 15, 28, 21, 40, 24, 47, 60, 19, 33, 35, 37, 52, 43, 55,  9,
    27, 39, 46, 59, 32, 51, 54,  8, 45, 58, 50,  7, 57,  6,  5, 63
  };

  i |= i >> 1;
  i |= i >> 2;
  i |= i >> 4;
  i |= i >> 8;
  i |= i >> 16;
  i |= i >> 32;

  bit = debruijn_tbl[(i * 0x03F08A4C6ACB9DBDu) >> 58];
#endif

  return bit;
}
#endif // HAVE(INT64)

// -----------------------------------------------------------------------------

#if HAVE(INT128)
static inline uint bsr128 (u128 i)
{
  u64 hi = i >> 64;

  if (hi != 0) return 64u + bsr64 (hi);

  u64 lo = i & 0xFFFFFFFFFFFFFFFFu;

  return bsr64 (lo);
}
#endif

// -----------------------------------------------------------------------------

#endif
