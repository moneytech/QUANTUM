// =============================================================================
// <sse.h>
//
// x86 SSE definitions.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_E609F43029004FA091BF0F77BC79DEFF
#define H_E609F43029004FA091BF0F77BC79DEFF

// -----------------------------------------------------------------------------

#include "intrinsics.h"
#include "bitops.h"

// =============================================================================
// Constants
// -----------------------------------------------------------------------------
// SSE vector misalignment fixup lookup table
static const u8 sse_align_tbl[16][16] aligned(16) =
{
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
  {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
  {0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
  {0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
  {0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF}
};

// =============================================================================
// Types
// -----------------------------------------------------------------------------

typedef __m128i xi128;
typedef __m128 xf128;
typedef __m128d xd128;

// -----------------------------------------------------------------------------

typedef union xi128_u
{
  xi128 x;
#if HAVE(INT128)
  s128 si128;
  u128 ui128;
#endif
  s64 si64[2];
  u64 ui64[2];
  s32 si32[4];
  u32 ui32[4];
  s16 si16[8];
  u16 ui16[8];
  s8 si8[16];
  u8 ui8[16];
} xi128_t;

typedef union xf128_u
{
  xf128 x;
  float f[4];
} xf128_t;

typedef union xd128_u
{
  xd128 x;
  double d[2];
} xd128_t;

// =============================================================================
// Functions
// -----------------------------------------------------------------------------
// Helper memory functions
// -----------------------------------------------------------------------------
// `maskmovdqu` is broken:
// https://github.com/skywind3000/BasicBitmap/issues/2
// https://www.cendio.com/bugzilla/show_bug.cgi?id=4328
// -----------------------------------------------------------------------------

static inline void sse_buf_copy (u8* restrict dst, const u8* restrict src, size_t size)
{
  #define T_RESTRICT

  #include "string/buffer/copy/generic.c"
}

// -----------------------------------------------------------------------------

static inline void sse_buf_move_left (u8* dst, const u8* src, size_t size)
{
  #include "string/buffer/copy/generic.c"
}

static inline void sse_buf_move_right (u8* dst, const u8* src, size_t size)
{
  #include "string/buffer/rcopy/generic.c"
}

// -----------------------------------------------------------------------------

static inline void sse_buf_fill (u8* buf, u8 chr, size_t size)
{
  #include "string/buffer/fill/generic.c"
}

// -----------------------------------------------------------------------------

#if CPU(SSE2)

// -----------------------------------------------------------------------------
// Missing byte swapping operations
// -----------------------------------------------------------------------------
// Reverse order of bytes in each 16-bit word
static inline xi128 sse_bswap16 (xi128 x)
{
  return _mm_or_si128 (_mm_slli_epi16 (x, 8), _mm_srli_epi16 (x, 8));
}

// -----------------------------------------------------------------------------
// Reverse order of bytes in each 32-bit word
static inline xi128 sse_bswap32 (xi128 x)
{
#if CPU(SSSE3)
  return _mm_shuffle_epi8 (x, _mm_set_epi8
  (
    12, 13, 14, 15,
     8,  9, 10, 11,
     4,  5,  6,  7,
     0,  1,  2,  3
  ));
#else
  // Swap bytes in each 16-bit word
  xi128 v = sse_bswap16 (x);

  // Swap 16-bit words themselves
  v = _mm_shufflelo_epi16 (v, _MM_SHUFFLE (2, 3, 0, 1));
  return _mm_shufflehi_epi16 (v, _MM_SHUFFLE (2, 3, 0, 1));
#endif
}

// -----------------------------------------------------------------------------
// Reverse order of bytes in each 64-bit word
static inline xi128 sse_bswap64 (xi128 x)
{
#if CPU(SSSE3)
  return _mm_shuffle_epi8 (x, _mm_set_epi8
  (
     8,  9, 10, 11,
    12, 13, 14, 15,
     0,  1,  2,  3,
     4,  5,  6,  7
  ));
#else
  // Swap bytes in each 16-bit word
  xi128 v = sse_bswap16 (x);

  // Swap 16-bit words themselves
  v = _mm_shufflelo_epi16 (v, _MM_SHUFFLE (0, 1, 2, 3));
  return _mm_shufflehi_epi16 (v, _MM_SHUFFLE (0, 1, 2, 3));
#endif
}

// -----------------------------------------------------------------------------
// Reverse order of bytes in the 128-bit word
static inline xi128 sse_bswap128 (xi128 x)
{
#if CPU(SSSE3)
  return _mm_shuffle_epi8 (x, _mm_set_epi8
  (
     0,  1,  2,  3,
     4,  5,  6,  7,
     8,  9, 10, 11,
    12, 13, 14, 15
  ));
#else
  // Swap bytes in each 16-bit word
  xi128 v = sse_bswap16 (x);

  // Swap 16-bit words themselves
  v = _mm_shufflelo_epi16 (v, _MM_SHUFFLE (0, 1, 2, 3));
  v = _mm_shufflehi_epi16 (v, _MM_SHUFFLE (0, 1, 2, 3));

  // Swap 32-bit words
  return _mm_shuffle_epi32 (v, _MM_SHUFFLE (1, 0, 3, 2));
#endif
}

// -----------------------------------------------------------------------------
// Missing `_mm_cvtsi64_si128()` and `_mm_cvtsi128_si64()` intrinsics
// for 32-bit builds
// -----------------------------------------------------------------------------

#if CPU(32BIT)
static inline xi128 _mm_cvtsi64_si128 (s64 i)
{
  xi128_t xt = {.si64[0] = i};
  return xt.x;
}

static inline s64 _mm_cvtsi128_si64 (xi128 x)
{
  xi128_t xt = {.x = x};
  return xt.si64[0];
}
#endif // CPU(32BIT)

// -----------------------------------------------------------------------------

#endif // CPU(SSE2)

// -----------------------------------------------------------------------------

#endif
