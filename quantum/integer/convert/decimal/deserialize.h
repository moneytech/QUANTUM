// =============================================================================
// <integer/convert/decimal/deserialize.h>
//
// Convert integral numbers from decimal strings of explicit length and from
// null-terminated strings fast with no validation and no overflow prevention.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_A19907145DFE40EE9EBF7CD5A3F97323
#define H_A19907145DFE40EE9EBF7CD5A3F97323

// -----------------------------------------------------------------------------

#include "support/intro.h"

// =============================================================================
// Utility functions
// -----------------------------------------------------------------------------
// Validate series of decimal digit characters
// -----------------------------------------------------------------------------
// Test if a sequence of `x` characters contains only valid
// decimal digit characters
// -----------------------------------------------------------------------------

static inline bint int_is_dig2s (const char_t* s)
{
  return (chr_is_dig (s[0]) & chr_is_dig (s[1]));
}

static inline bint int_is_dig4s (const char_t* s)
{
  return (chr_is_dig (s[0]) & chr_is_dig (s[1]) & chr_is_dig (s[2]) & chr_is_dig (s[3]));
}

static inline bint int_is_dig8s (const char_t* s)
{
  return (chr_is_dig (s[0]) & chr_is_dig (s[1]) & chr_is_dig (s[2]) & chr_is_dig (s[3])
  & chr_is_dig (s[4]) & chr_is_dig (s[5]) & chr_is_dig (s[6]) & chr_is_dig (s[7]));
}

// -----------------------------------------------------------------------------
// Test if a vector of `x` characters contains only valid
// decimal digit characters
// -----------------------------------------------------------------------------

static inline bint int_is_dig2v (const char_t* s)
{
#if (CHAR_BIT == 8) && HAVE(INT16)
  register u16 v = *(const u16*)s;

  if ((v & 0xF0F0u) != 0x3030u) return false;
  if ((v + 0x0606u) & 0x4040u) return false;

  return true;
#else
  return int_is_dig2s (s);
#endif
}

static inline bint int_is_dig4v (const char_t* s)
{
#if (CHAR_BIT == 8) && HAVE(INT32)
  register u32 v = *(const u32*)s;

  if ((v & 0xF0F0F0F0u) != 0x30303030u) return false;
  if ((v + 0x06060606u) & 0x40404040u) return false;

  return true;
#else
  return int_is_dig4s (s);
#endif
}

static inline bint int_is_dig8v (const char_t* s)
{
#if (CHAR_BIT == 8) && HAVE(INT64)
  register u64 v = *(const u64*)s;

  if ((v & 0xF0F0F0F0F0F0F0F0u) != 0x3030303030303030u) return false;
  if ((v + 0x0606060606060606u) & 0x4040404040404040u) return false;

  return true;
#else
  return int_is_dig8s (s);
#endif
}

// -----------------------------------------------------------------------------
// Test if `x` characters are valid decimal digit characters
// -----------------------------------------------------------------------------

static inline bint int_is_dig2 (const char_t* s)
{
#if CPU(UNALIGNED_ACCESS)
  return int_is_dig2v (s);
#else
  return int_is_dig2s (s);
#endif
}

static inline bint int_is_dig4 (const char_t* s)
{
#if CPU(UNALIGNED_ACCESS)
  return int_is_dig4v (s);
#else
  return int_is_dig4s (s);
#endif
}

static inline bint int_is_dig8 (const char_t* s)
{
#if CPU(UNALIGNED_ACCESS)
  return int_is_dig8v (s);
#else
  return int_is_dig8s (s);
#endif
}

// -----------------------------------------------------------------------------
// Returns 16 if all characters are valid decimal digit characters
// or the index of the first non-decimal character using SSE2
// -----------------------------------------------------------------------------

#if CPU(SSE2)

#define int_is_dig16s int_is_dig16
#define int_is_dig16v int_is_dig16

static inline uint int_is_dig16 (const char_t* s)
{
#if CPU(SSE42)
  const xi128 r = _mm_setr_epi8 ('0', '9'
  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

  return _mm_cmpistri (r, _mm_loadu_si128 ((const xi128*)s)
  , _SIDD_UBYTE_OPS | _SIDD_CMP_EQUAL_ANY | _SIDD_CMP_RANGES
  | _SIDD_NEGATIVE_POLARITY);
#else // CPU(SSE42) ][
  const xi128 z = _mm_set1_epi8 ('0');
  const xi128 n = _mm_set1_epi8 ('9');

  xi128 v = _mm_loadu_si128 ((const xi128*)s);
  xi128 r = _mm_or_si128 (_mm_cmplt_epi8 (v, z), _mm_cmpgt_epi8 (v, n));

  register uint m = _mm_movemask_epi8 (r);

  return ((m == 0) ? 16u : bsf32 (m));
#endif // !CPU(SSE42)
}

#endif // CPU(SSE2)

// -----------------------------------------------------------------------------
// SSE4.1 version for 32 decimal digit characters
// -----------------------------------------------------------------------------

#if CPU(SSE41) && CPU(64BIT) && HAVE(INT128)

#define int_is_dig32s int_is_dig32
#define int_is_dig32v int_is_dig32

static inline uint int_is_dig32 (const char_t* s)
{
  register uint n = int_is_dig16 (s);

  if (n != 16u) return n;

  n = int_is_dig16 (s + 16);

  if (n != 16u) return 16u + n;

  return 32u;
}

#endif // CPU(SSE41) && CPU(64BIT) && HAVE(INT128)

// -----------------------------------------------------------------------------
// Convert series of decimal digit characters
// -----------------------------------------------------------------------------
// Convert a sequence of `x` decimal digit characters to their numeric value
// -----------------------------------------------------------------------------

static inline uf8 int_from_dig2s (const char_t* s)
{
  return ((uf8)10u * s[0]) + s[1]
  - ((uf8)11u * '0');
}

static inline uf16 int_from_dig4s (const char_t* s)
{
  return ((uf16)1000u * s[0]) + ((uf16)100u * s[1])
  + ((uf16)10u * s[2]) + s[3]
  - ((uf16)1111u * '0');
}

static inline uf32 int_from_dig8s (const char_t* s)
{
  return ((uf32)10000000u * s[0]) + ((uf32)1000000u * s[1])
  + ((uf32)100000u * s[2]) + ((uf32)10000u * s[3])
  + ((uf32)1000u * s[4]) + ((uf32)100u * s[5])
  + ((uf32)10u * s[6]) + s[7]
  - ((uf32)11111111u * '0');
}

// -----------------------------------------------------------------------------
// Convert a vector of `x` decimal digit characters to their numeric value
// -----------------------------------------------------------------------------

static inline uf8 int_from_dig2v (const char_t* s)
{
#if HAVE(INT16)
  register u16 v = *(const u16*)s;
  register u16 d = v - 0x3030u;

  #if CPU(LITTLE_ENDIAN)
    return ((d * ((u16)256u * 10u + 1u)) >> 8) & 0x00FFu;
  #else
    return ((d * ((u16)256u + 10u + 1u)) >> 8) & 0x00FFu;
  #endif
#else
  return int_from_dig2s (s);
#endif
}

static inline uf16 int_from_dig4v (const char_t* s)
{
#if HAVE(INT32)
  register u32 v = *(const u32*)s;
  register u32 d1 = v - 0x30303030u;

  #if CPU(LITTLE_ENDIAN)
    register u32 d2 = ((d1 * 10u) + (d1 >> 8)) & 0x00FF00FFu;
    return (d2 * ((u32)65535u * 100u + 101u)) >> 16;
  #else
    register u32 d2 = (((d1 * 10u) >> 8) + d1) & 0x00FF00FFu;
    return (d2 * ((u32)65535u + 100u + 1u)) >> 16;
  #endif
#else
  return int_from_dig4s (s);
#endif
}

static inline uf32 int_from_dig8v (const char_t* s)
{
#if HAVE(INT64)
  register u64 v = *(const u64*)s;
  register u64 d1 = v - 0x3030303030303030u;

  #if CPU(LITTLE_ENDIAN)
    register u64 d2 = ((d1 * 10u) + (d1 >> 8)) & 0x00FF00FF00FF00FFu;
    register u64 d4 = ((d2 * ((u64)65535u * 100u + 101u)) >> 16) & 0x0000FFFF0000FFFFu;

    return (d4 * ((u64)4294967295u * 10000u + 10001u)) >> 32;
  #else
    register u64 d2 = (((d1 * 10u) >> 8) + d1) & 0x00FF00FF00FF00FFu;
    register u64 d4 = ((d2 * ((u64)65535u + 100u + 1u)) >> 16) & 0x0000FFFF0000FFFFu;

    return (d4 * ((u64)4294967295u + 10000u + 1u)) >> 32;
  #endif
#else
  return int_from_dig8s (s);
#endif
}

// -----------------------------------------------------------------------------
// Convert `x` decimal digit characters to their numeric value
// -----------------------------------------------------------------------------

static inline uf8 int_from_dig2 (const char_t* s)
{
#if CPU(UNALIGNED_ACCESS)
  return int_from_dig2v (s);
#else
  return int_from_dig2s (s);
#endif
}

static inline uf16 int_from_dig4 (const char_t* s)
{
#if CPU(UNALIGNED_ACCESS)
  return int_from_dig4v (s);
#else
  return int_from_dig4s (s);
#endif
}

static inline uf32 int_from_dig8 (const char_t* s)
{
#if CPU(UNALIGNED_ACCESS)
  return int_from_dig8v (s);
#else
  return int_from_dig8s (s);
#endif
}

// -----------------------------------------------------------------------------
// Convert 16 decimal digit characters using SSE2
// -----------------------------------------------------------------------------

#if CPU(SSE2)

#define int_from_dig16s int_from_dig16
#define int_from_dig16v int_from_dig16

static inline u64 int_from_dig16 (const char_t* s)
{
  // ASCII zeros
  const xi128 z = _mm_set1_epi8 ('0');

  // Even & odd digit multipliers
  const xi128 me = _mm_setr_epi16 (1000, 10, 1000, 10, 1000, 10, 1000, 10);
  const xi128 mo = _mm_setr_epi16 (100, 1, 100, 1, 100, 1, 100, 1);

  // Result vector multiplier
  const xi128 mr = _mm_setr_epi16 (10000, 1, 0, 0, 10000, 1, 0, 0);

  // Get the input digits
  xi128 i = _mm_sub_epi8 (_mm_loadu_si128 ((const xi128*)s), z);

  // Split the the even & odd 16-bit words across two vectors
  xi128 e = _mm_srli_epi16 (_mm_slli_epi16 (i, 8), 8);
  xi128 o = _mm_srli_epi16 (i, 8);

  // Multiply the even & odd digit vectors with their respective multipliers
  xi128 em = _mm_madd_epi16 (e, me);
  xi128 om = _mm_madd_epi16 (o, mo);

  // Merge the two resulting vectors
  xi128 c = _mm_add_epi16 (em, om);

  // Because `pmaddwd` produces packed 32-bit words,
  // we need to reconstruct the resulting vector back
  // into 16-bit words for the final multiplication
  xi128 r = _mm_or_si128 (c, _mm_srli_epi64 (c, 16));

  // Compute the final 64-bit result
  xi128 rm = _mm_madd_epi16 (r, mr);

  // Extract the 64-bit value
  xi128_t v = {.x = rm};

  return ((u64)(v.ui32[0]) * 100000000u) + v.ui32[2];
}

#endif // CPU(SSE2)

// -----------------------------------------------------------------------------
// Convert 32 decimal digit characters using SSE4.1
// -----------------------------------------------------------------------------

#if CPU(SSE41) && CPU(64BIT) && HAVE(INT128)

#define int_from_dig32s int_from_dig32
#define int_from_dig32v int_from_dig32

static inline u128 int_from_dig32 (const char_t* s)
{
  // ASCII zeros
  const xi128 z = _mm_set1_epi8 ('0');

  // Even & odd digit multipliers
  const xi128 me = _mm_setr_epi16 (1000, 10, 1000, 10, 1000, 10, 1000, 10);
  const xi128 mo = _mm_setr_epi16 (100, 1, 100, 1, 100, 1, 100, 1);

  // Final vector multipliers
  const xi128 mr = _mm_setr_epi16 (10000, 1, 10000, 1, 10000, 1, 10000, 1);
  const xi128 mf = _mm_setr_epi32 (100000000, 0, 100000000, 0);

  // Get the input digits
  xi128 i1 = _mm_sub_epi8 (_mm_loadu_si128 ((const xi128*)s), z);
  xi128 i2 = _mm_sub_epi8 (_mm_loadu_si128 ((const xi128*)(s + 16)), z);

  // Split into the even & odd 16-bit words across two vectors
  xi128 e1 = _mm_srli_epi16 (_mm_slli_epi16 (i1, 8), 8);
  xi128 e2 = _mm_srli_epi16 (_mm_slli_epi16 (i2, 8), 8);
  xi128 o1 = _mm_srli_epi16 (i1, 8);
  xi128 o2 = _mm_srli_epi16 (i2, 8);

  // Multiply the even & odd digit vectors with their respective multipliers
  xi128 e1m = _mm_madd_epi16 (e1, me);
  xi128 e2m = _mm_madd_epi16 (e2, me);
  xi128 o1m = _mm_madd_epi16 (o1, mo);
  xi128 o2m = _mm_madd_epi16 (o2, mo);

  // Merge the four resulting vectors pairwise
  xi128 s1 = _mm_add_epi16 (e1m, o1m);
  xi128 s2 = _mm_add_epi16 (e2m, o2m);

  // Merge all 32 processed digits into the single vector
  xi128 r = _mm_packus_epi32 (s1, s2);
  xi128 rm = _mm_madd_epi16 (r, mr);

  // Produce the final 128-bit result
  xi128 fm = _mm_mul_epi32 (rm, mf);
  xi128 f = _mm_add_epi64 (fm, _mm_srli_epi64 (rm, 32));

  // Extract the 128-bit value
  xi128_t v = {.x = f};

  return (((u128)(v.ui64[0]) * 100000000u) * 100000000u) + v.ui64[1];
}

#endif // CPU(SSE41) && CPU(64BIT) && HAVE(INT128)

// -----------------------------------------------------------------------------
// Convert `x` misaligned decimal digit characters
// before gaining the required alignment
// -----------------------------------------------------------------------------

#if 0

static inline uf16 int_from_dig3s (const char_t* s, size_t n)
{
  register uf16 u = 0;

  if (n > 1u)
  {
    u = int_from_dig2s (s);

    s += 2u;
    n -= 2u;
  }

  if (n != 0) u = (u * 10u) + chr_dig_to_int (*s);

  return u;
}

static inline uf32 int_from_dig7s (const char_t* s, size_t n)
{
  register uf32 u = 0;

  if (n > 3u)
  {
    u = int_from_dig4s (s);

    s += 4u;
    n -= 4u;
  }

  if (n > 1u)
  {
    u = (u * 100u) + int_from_dig2s (s);

    s += 2u;
    n -= 2u;
  }

  if (n != 0) u = (u * 10u) + chr_dig_to_int (*s);

  return u;
}

static inline uf64 int_from_dig15s (const char_t* s, size_t n)
{
  register uf64 u = 0;

  if (n > 7u)
  {
    u = int_from_dig8s (s);

    s += 8u;
    n -= 8u;
  }

  if (n > 3u)
  {
    u = (u * 10000u) + int_from_dig4s (s);

    s += 4u;
    n -= 4u;
  }

  if (n > 1u)
  {
    u = (u * 100u) + int_from_dig2s (s);

    s += 2u;
    n -= 2u;
  }

  if (n != 0) u = (u * 10u) + chr_dig_to_int (*s);

  return u;
}

#endif

// -----------------------------------------------------------------------------
// Convert `x` remaining aligned decimal digit characters
// -----------------------------------------------------------------------------

static inline uf16 int_from_dig3v (const char_t* s, size_t n)
{
  register uf16 u = 0;

  if (n > 1u)
  {
    u = int_from_dig2v (s);

    s += 2u;
    n -= 2u;
  }

  if (n != 0) u = (u * 10u) + chr_dig_to_int (*s);

  return u;
}

static inline uf32 int_from_dig7v (const char_t* s, size_t n)
{
  register uf32 u = 0;

  if (n > 3u)
  {
    u = int_from_dig4v (s);

    s += 4u;
    n -= 4u;
  }

  if (n > 1u)
  {
    u = (u * 100u) + int_from_dig2v (s);

    s += 2u;
    n -= 2u;
  }

  if (n != 0) u = (u * 10u) + chr_dig_to_int (*s);

  return u;
}

static inline uf64 int_from_dig15v (const char_t* s, size_t n)
{
  register uf64 u = 0;

  if (n > 7u)
  {
    u = int_from_dig8v (s);

    s += 8u;
    n -= 8u;
  }

  if (n > 3u)
  {
    u = (u * 10000u) + int_from_dig4v (s);

    s += 4u;
    n -= 4u;
  }

  if (n > 1u)
  {
    u = (u * 100u) + int_from_dig2v (s);

    s += 2u;
    n -= 2u;
  }

  if (n != 0) u = (u * 10u) + chr_dig_to_int (*s);

  return u;
}

#if HAVE(INT_LEAST128) && CPU(SSE41) && CPU(64BIT)
static inline uf128 int_from_dig31v (const char_t* s, size_t n)
{
  register uf128 u = 0;

  if (n > 15u)
  {
    u = int_from_dig16v (s);

    s += 16u;
    n -= 16u;
  }

  if (n > 7u)
  {
    u = (u * 100000000u) + int_from_dig8v (s);

    s += 8u;
    n -= 8u;
  }

  if (n > 3u)
  {
    u = (u * 10000u) + int_from_dig4v (s);

    s += 4u;
    n -= 4u;
  }

  if (n > 1u)
  {
    u = (u * 100u) + int_from_dig2v (s);

    s += 2u;
    n -= 2u;
  }

  if (n != 0) u = (u * 10u) + chr_dig_to_int (*s);

  return u;
}
#endif // HAVE(INT_LEAST128) && CPU(SSE41) && CPU(64BIT)

// =============================================================================
// Functions
// -----------------------------------------------------------------------------
// 8-bit+
// -----------------------------------------------------------------------------

static inline sf8 int_s8_from_str (const char_t* str, size_t len)
{
  #define t_int uf8

  #define T_SIGN

  #include "deserialize/explicit/i8.c"
}

static inline uf8 int_u8_from_str (const char_t* str, size_t len)
{
  #define t_int uf8

  #include "deserialize/explicit/i8.c"
}

// -----------------------------------------------------------------------------

static inline sf8 int_s8_from_stri (const char_t* str)
{
  #define t_int uf8

  #define T_SIGN

  #include "deserialize/implicit/i8.c"
}

static inline uf8 int_u8_from_stri (const char_t* str)
{
  #define t_int uf8

  #include "deserialize/implicit/i8.c"
}

// -----------------------------------------------------------------------------
// 16-bit+
// -----------------------------------------------------------------------------

static inline sf16 int_s16_from_str (const char_t* str, size_t len)
{
  #define t_int uf16

  #define T_SIGN

  #include "deserialize/explicit/i16.c"
}

static inline uf16 int_u16_from_str (const char_t* str, size_t len)
{
  #define t_int uf16

  #include "deserialize/explicit/i16.c"
}

// -----------------------------------------------------------------------------

static inline sf16 int_s16_from_stri (const char_t* str)
{
  #define t_int uf16

  #define T_SIGN

  #include "deserialize/implicit/i16.c"
}

static inline uf16 int_u16_from_stri (const char_t* str)
{
  #define t_int uf16

  #include "deserialize/implicit/i16.c"
}

// -----------------------------------------------------------------------------
// 32-bit+
// -----------------------------------------------------------------------------

static inline sf32 int_s32_from_str (const char_t* str, size_t len)
{
  #define t_int uf32

  #define T_SIGN

  #include "deserialize/explicit/i32.c"
}

static inline uf32 int_u32_from_str (const char_t* str, size_t len)
{
  #define t_int uf32

  #include "deserialize/explicit/i32.c"
}

// -----------------------------------------------------------------------------

static inline sf32 int_s32_from_stri (const char_t* str)
{
  #define t_int uf32

  #define T_SIGN

  #include "deserialize/implicit/i32.c"
}

static inline uf32 int_u32_from_stri (const char_t* str)
{
  #define t_int uf32

  #include "deserialize/implicit/i32.c"
}

// -----------------------------------------------------------------------------
// 64-bit+
// -----------------------------------------------------------------------------

static inline sf64 int_s64_from_str (const char_t* str, size_t len)
{
  #define t_int uf64

  #define T_SIGN

  #include "deserialize/explicit/i64.c"
}

static inline uf64 int_u64_from_str (const char_t* str, size_t len)
{
  #define t_int uf64

  #include "deserialize/explicit/i64.c"
}

// -----------------------------------------------------------------------------

static inline sf64 int_s64_from_stri (const char_t* str)
{
  #define t_int uf64

  #define T_SIGN

  #include "deserialize/implicit/i64.c"
}

static inline uf64 int_u64_from_stri (const char_t* str)
{
  #define t_int uf64

  #include "deserialize/implicit/i64.c"
}

// -----------------------------------------------------------------------------
// 128-bit+
// -----------------------------------------------------------------------------

#if HAVE(INT_LEAST128)

static inline sf128 int_s128_from_str (const char_t* str, size_t len)
{
  #define t_int uf128

  #define T_SIGN

  #include "deserialize/explicit/i128.c"
}

static inline uf128 int_u128_from_str (const char_t* str, size_t len)
{
  #define t_int uf128

  #include "deserialize/explicit/i128.c"
}

// -----------------------------------------------------------------------------

static inline sf128 int_s128_from_stri (const char_t* str)
{
  #define t_int uf128

  #define T_SIGN

  #include "deserialize/implicit/i128.c"
}

static inline uf128 int_u128_from_stri (const char_t* str)
{
  #define t_int uf128

  #include "deserialize/implicit/i128.c"
}

#endif // HAVE(INT_LEAST128)

// -----------------------------------------------------------------------------
// Maximum
// -----------------------------------------------------------------------------

static inline intmax_t int_smax_from_str (const char_t* str, size_t len)
{
  #define t_int uintmax_t

  #define T_SIGN

#if (INTMAX_BIT >= 128)
  #include "deserialize/explicit/i128.c"
#else
  #include "deserialize/explicit/i64.c"
#endif
}

static inline uintmax_t int_umax_from_str (const char_t* str, size_t len)
{
  #define t_int uintmax_t

#if (INTMAX_BIT >= 128)
  #include "deserialize/explicit/i128.c"
#else
  #include "deserialize/explicit/i64.c"
#endif
}

// -----------------------------------------------------------------------------

static inline intmax_t int_smax_from_stri (const char_t* str)
{
  #define t_int uintmax_t

  #define T_SIGN

#if (INTMAX_BIT >= 128)
  #include "deserialize/implicit/i128.c"
#else
  #include "deserialize/implicit/i64.c"
#endif
}

static inline uintmax_t int_umax_from_stri (const char_t* str)
{
  #define t_int uintmax_t

#if (INTMAX_BIT >= 128)
  #include "deserialize/implicit/i128.c"
#else
  #include "deserialize/implicit/i64.c"
#endif
}

// -----------------------------------------------------------------------------
// Pointer
// -----------------------------------------------------------------------------

static inline intptr_t int_sptr_from_str (const char_t* str, size_t len)
{
  #define t_int uintptr_t

  #define T_SIGN

#if (INTPTR_BIT >= 64)
  #include "deserialize/explicit/i64.c"
#else
  #include "deserialize/explicit/i32.c"
#endif
}

static inline uintptr_t int_uptr_from_str (const char_t* str, size_t len)
{
  #define t_int uintptr_t

#if (INTPTR_BIT >= 64)
  #include "deserialize/explicit/i64.c"
#else
  #include "deserialize/explicit/i32.c"
#endif
}

// -----------------------------------------------------------------------------

static inline intptr_t int_sptr_from_istr (const char_t* str)
{
  #define t_int uintptr_t

  #define T_SIGN

#if (INTPTR_BIT >= 64)
  #include "deserialize/implicit/i64.c"
#else
  #include "deserialize/implicit/i32.c"
#endif
}

static inline uintptr_t int_uptr_from_istr (const char_t* str)
{
  #define t_int uintptr_t

#if (INTPTR_BIT >= 64)
  #include "deserialize/implicit/i64.c"
#else
  #include "deserialize/implicit/i32.c"
#endif
}

// =============================================================================
// Macros
// -----------------------------------------------------------------------------
// Map the decimal string conversion functions above
// to the fundamental integral types
// -----------------------------------------------------------------------------
// `char`
// -----------------------------------------------------------------------------

#if (CHAR_BIT == INTMAX_BIT)
  #define int_schar_from_str int_smax_from_str
  #define int_uchar_from_str int_umax_from_str

  #define int_schar_from_stri int_smax_from_stri
  #define int_uchar_from_stri int_umax_from_stri
#elif (CHAR_BIT == INT_FAST64_BIT)
  #define int_schar_from_str int_s64_from_str
  #define int_uchar_from_str int_u64_from_str

  #define int_schar_from_stri int_s64_from_stri
  #define int_uchar_from_stri int_u64_from_stri
#elif (CHAR_BIT == INT_FAST32_BIT)
  #define int_schar_from_str int_s32_from_str
  #define int_uchar_from_str int_u32_from_str

  #define int_schar_from_stri int_s32_from_stri
  #define int_uchar_from_stri int_u32_from_stri
#elif (CHAR_BIT == INT_FAST16_BIT)
  #define int_schar_from_str int_s16_from_str
  #define int_uchar_from_str int_u16_from_str

  #define int_schar_from_stri int_s16_from_stri
  #define int_uchar_from_stri int_u16_from_stri
#elif (CHAR_BIT == INT_FAST8_BIT)
  #define int_schar_from_str int_s8_from_str
  #define int_uchar_from_str int_u8_from_str

  #define int_schar_from_stri int_s8_from_stri
  #define int_uchar_from_stri int_u8_from_stri
#endif

// -----------------------------------------------------------------------------
// `short`
// -----------------------------------------------------------------------------

#if (SHRT_BIT == INTMAX_BIT)
  #define int_sshort_from_str int_smax_from_str
  #define int_ushort_from_str int_umax_from_str

  #define int_sshort_from_stri int_smax_from_stri
  #define int_ushort_from_stri int_umax_from_stri
#elif (SHRT_BIT == INT_FAST64_BIT)
  #define int_sshort_from_str int_s64_from_str
  #define int_ushort_from_str int_u64_from_str

  #define int_sshort_from_stri int_s64_from_stri
  #define int_ushort_from_stri int_u64_from_stri
#elif (SHRT_BIT == INT_FAST32_BIT)
  #define int_sshort_from_str int_s32_from_str
  #define int_ushort_from_str int_u32_from_str

  #define int_sshort_from_stri int_s32_from_stri
  #define int_ushort_from_stri int_u32_from_stri
#elif (SHRT_BIT == INT_FAST16_BIT)
  #define int_sshort_from_str int_s16_from_str
  #define int_ushort_from_str int_u16_from_str

  #define int_sshort_from_stri int_s16_from_stri
  #define int_ushort_from_stri int_u16_from_stri
#endif

// -----------------------------------------------------------------------------
// `int`
// -----------------------------------------------------------------------------

#if (INT_BIT == INTMAX_BIT)
  #define int_sint_from_str int_smax_from_str
  #define int_uint_from_str int_umax_from_str

  #define int_sint_from_stri int_smax_from_stri
  #define int_uint_from_stri int_umax_from_stri
#elif (INT_BIT == INT_FAST64_BIT)
  #define int_sint_from_str int_s64_from_str
  #define int_uint_from_str int_u64_from_str

  #define int_sint_from_stri int_s64_from_stri
  #define int_uint_from_stri int_u64_from_stri
#elif (INT_BIT == INT_FAST32_BIT)
  #define int_sint_from_str int_s32_from_str
  #define int_uint_from_str int_u32_from_str

  #define int_sint_from_stri int_s32_from_stri
  #define int_uint_from_stri int_u32_from_stri
#elif (INT_BIT == INT_FAST16_BIT)
  #define int_sint_from_str int_s16_from_str
  #define int_uint_from_str int_u16_from_str

  #define int_sint_from_stri int_s16_from_stri
  #define int_uint_from_stri int_u16_from_stri
#endif

// -----------------------------------------------------------------------------
// `long`
// -----------------------------------------------------------------------------

#if (LONG_BIT == INTMAX_BIT)
  #define int_slong_from_str int_smax_from_str
  #define int_ulong_from_str int_umax_from_str

  #define int_slong_from_stri int_smax_from_stri
  #define int_ulong_from_stri int_umax_from_stri
#elif (LONG_BIT == INT_FAST64_BIT)
  #define int_slong_from_str int_s64_from_str
  #define int_ulong_from_str int_u64_from_str

  #define int_slong_from_stri int_s64_from_stri
  #define int_ulong_from_stri int_u64_from_stri
#elif (LONG_BIT == INT_FAST32_BIT)
  #define int_slong_from_str int_s32_from_str
  #define int_ulong_from_str int_u32_from_str

  #define int_slong_from_stri int_s32_from_stri
  #define int_ulong_from_stri int_u32_from_stri
#endif

// -----------------------------------------------------------------------------
// `llong`
// -----------------------------------------------------------------------------

#if (LLONG_BIT == INTMAX_BIT)
  #define int_sllong_from_str int_smax_from_str
  #define int_ullong_from_str int_umax_from_str

  #define int_sllong_from_stri int_smax_from_stri
  #define int_ullong_from_stri int_umax_from_stri
#elif (LLONG_BIT == INT_FAST64_BIT)
  #define int_sllong_from_str int_s64_from_str
  #define int_ullong_from_str int_u64_from_str

  #define int_sllong_from_stri int_s64_from_stri
  #define int_ullong_from_stri int_u64_from_stri
#endif

// -----------------------------------------------------------------------------

#include "support/outro.h"

// -----------------------------------------------------------------------------

#endif
