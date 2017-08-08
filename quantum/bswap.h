// =============================================================================
// <bswap.h>
//
// Reverse the order of bytes in integral variables.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_CDC242DAAEEA497DA96C9AEA7AD81C5D
#define H_CDC242DAAEEA497DA96C9AEA7AD81C5D

// =============================================================================
// Functions
// -----------------------------------------------------------------------------
// x86: GCC optimizes `bswap16()` into single `rol` instruction with `-O1`,
// but `bswap32()` and `bswap64()` are optimized into `bswap` only with `-O2`
// -----------------------------------------------------------------------------

#if HAVE(INT16)
static inline u16 bswap16 (u16 v)
{
#if C(GNU)
  return __builtin_bswap16 (v);
#else
  return ((v >> 8) | (v << 8));
#endif
}
#endif // HAVE(INT16)

// -----------------------------------------------------------------------------

#if HAVE(INT32)
static inline u32 bswap32 (u32 v)
{
#if C(GNU)
  return __builtin_bswap32 (v);
#else
  return ((v >> 24)
  | ((v & 0x00FF0000u) >> 8)
  | ((v & 0x0000FF00u) << 8)
  |  (v << 24));
#endif
}
#endif // HAVE(INT32)

// -----------------------------------------------------------------------------

#if HAVE(INT64)
static inline u64 bswap64 (u64 v)
{
#if C(GNU)
  return __builtin_bswap64 (v);
#else
  return ((v >> 56)
  | ((v & 0x00FF000000000000u) >> 40)
  | ((v & 0x0000FF0000000000u) >> 24)
  | ((v & 0x000000FF00000000u) >> 8)
  | ((v & 0x00000000FF000000u) << 8)
  | ((v & 0x0000000000FF0000u) << 24)
  | ((v & 0x000000000000FF00u) << 40)
  |  (v << 56));
#endif
}
#endif // HAVE(INT64)

// -----------------------------------------------------------------------------

#if HAVE(INT128) && HAVE(INT64)
static inline u128 bswap128 (u128 v)
{
  return ((u128)bswap64 (v) << 64) | bswap64 (v >> 64);
}
#endif

// =============================================================================
// Macros
// -----------------------------------------------------------------------------
// `short`
#if (SHRT_BIT == 16)
  #define bswap_short bswap16
#elif (SHRT_BIT == 32)
  #define bswap_short bswap32
#elif (SHRT_BIT == 64)
  #define bswap_short bswap64
#endif

// -----------------------------------------------------------------------------
// `int`
#if (INT_BIT == 16)
  #define bswap_int bswap16
#elif (INT_BIT == 32)
  #define bswap_int bswap32
#elif (INT_BIT == 64)
  #define bswap_int bswap64
#endif

// -----------------------------------------------------------------------------
// `long`
#if (LONG_BIT == 16)
  #define bswap_long bswap16
#elif (LONG_BIT == 32)
  #define bswap_long bswap32
#elif (LONG_BIT == 64)
  #define bswap_long bswap64
#endif

// -----------------------------------------------------------------------------
// `llong`
#if (LLONG_BIT == 16)
  #define bswap_llong bswap16
#elif (LLONG_BIT == 32)
  #define bswap_llong bswap32
#elif (LLONG_BIT == 64)
  #define bswap_llong bswap64
#endif

// -----------------------------------------------------------------------------

#endif
