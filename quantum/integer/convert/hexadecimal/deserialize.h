// =============================================================================
// <integer/convert/hexadecimal/deserialize.c>
//
// Convert integral numbers from hexadecimal strings of explicit length and from
// null-terminated strings fast with no validation and no overflow protection.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_CEF0B38E15F5407AB73BCA9246C34888
#define H_CEF0B38E15F5407AB73BCA9246C34888

// -----------------------------------------------------------------------------

#include "../../../bswap.h"

// -----------------------------------------------------------------------------

#include "support/intro.h"

// =============================================================================
// Utility functions
// -----------------------------------------------------------------------------
// Validate series of hexadecimal digit characters
// -----------------------------------------------------------------------------
// Test if `x` characters contain only valid hexadecimal digit characters
// -----------------------------------------------------------------------------

static inline bint int_is_xdig2 (const char_t* s)
{
  uint x0 = chr_xdig_to_int (s[0]);
  uint x1 = chr_xdig_to_int (s[1]);

  return ((x0 | x1) <= 0xFu);
}

static inline bint int_is_xdig4 (const char_t* s)
{
  uint x0 = chr_xdig_to_int (s[0]);
  uint x1 = chr_xdig_to_int (s[1]);
  uint x2 = chr_xdig_to_int (s[2]);
  uint x3 = chr_xdig_to_int (s[3]);

  return ((x0 | x1 | x2 | x3) <= 0xFu);
}

// -----------------------------------------------------------------------------
// Returns `8` if all characters are valid hexadecimal digit characters
// or the index of the first non-hexadecimal character using SSE2
// -----------------------------------------------------------------------------

#if CPU(SSE2)

static inline uint int_is_xdig8 (const char_t* s)
{
#if CPU(SSE42)
  const xi128 r = _mm_setr_epi8
  (
    '0', '9', 'A', 'F', 'a', 'f',
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  );

  u64 v = *(u64*)s;

  return _mm_cmpistri (r, _mm_cvtsi64_si128 (v)
  , _SIDD_UBYTE_OPS | _SIDD_CMP_EQUAL_ANY | _SIDD_CMP_RANGES
  | _SIDD_NEGATIVE_POLARITY);
#else // CPU(SSE42)
  const xi128 v0 = _mm_set1_epi8 ('0');
  const xi128 v9 = _mm_set1_epi8 ('9');

  const xi128 va = _mm_set1_epi8 ('a');
  const xi128 vf = _mm_set1_epi8 ('f');

  u64 v = *(u64*)s;
  v |= (v & 0x4040404040404040u) >> 1;

  xi128 vi = _mm_cvtsi64_si128 (v);

  xi128 t1 = _mm_or_si128 (_mm_cmplt_epi8 (vi, v0), _mm_cmpgt_epi8 (vi, v9));
  xi128 t2 = _mm_or_si128 (_mm_cmplt_epi8 (vi, va), _mm_cmpgt_epi8 (vi, vf));

  xi128 t = _mm_or_si128 (t1, t2);

  register u32 m = _mm_movemask_epi8 (t);

  return bsf32 (m);
#endif // !CPU(SSE42)
}

#else // CPU(SSE2) ][

static inline bint int_is_xdig8 (const char_t* s)
{
  uint x0 = chr_xdig_to_int (s[0]);
  uint x1 = chr_xdig_to_int (s[1]);
  uint x2 = chr_xdig_to_int (s[2]);
  uint x3 = chr_xdig_to_int (s[3]);

  if (likely ((x0 | x1 | x2 | x3) > 0xFu)) return false;

  uint x4 = chr_xdig_to_int (s[4]);
  uint x5 = chr_xdig_to_int (s[5]);
  uint x6 = chr_xdig_to_int (s[6]);
  uint x7 = chr_xdig_to_int (s[7]);

  return ((x4 | x5 | x6 | x7) <= 0xFu);
}

#endif // !CPU(SSE2)

// -----------------------------------------------------------------------------
// Test 16 hexadecimal digit characters using SSE2
// -----------------------------------------------------------------------------

#if CPU(SSE2)

static inline uint int_is_xdig16 (const char_t* s)
{
#if CPU(SSE42)
  const xi128 r = _mm_setr_epi8 (
    '0', '9', 'A', 'F', 'a', 'f',
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  );

  return _mm_cmpistri (r, _mm_loadu_si128 ((const xi128*)s)
  , _SIDD_UBYTE_OPS | _SIDD_CMP_EQUAL_ANY | _SIDD_CMP_RANGES
  | _SIDD_NEGATIVE_POLARITY);
#else // CPU(SSE42)
  const xi128 v0 = _mm_set1_epi8 ('0');
  const xi128 v9 = _mm_set1_epi8 ('9');

  const xi128 va = _mm_set1_epi8 ('a');
  const xi128 vf = _mm_set1_epi8 ('f');

  const xi128 vb = _mm_set1_epi8 (0x40);

  xi128 vi = _mm_loadu_si128 ((const xi128*)s);

  xi128 vl = _mm_or_si128 (vi, _mm_srli_epi64 (_mm_and_si128 (vi, vb), 1));

  xi128 t1 = _mm_or_si128 (_mm_cmplt_epi8 (vl, v0), _mm_cmpgt_epi8 (vl, v9));
  xi128 t2 = _mm_or_si128 (_mm_cmplt_epi8 (vl, va), _mm_cmpgt_epi8 (vl, vf));

  xi128 t = _mm_or_si128 (t1, t2);

  register u32 m = _mm_movemask_epi8 (t);

  return (m == 0) ? 16u : bsf32 (m);
#endif // !CPU(SSE42)
}

#endif // CPU(SSE2)

// -----------------------------------------------------------------------------
// Test 32 hexadecimal digit characters using SSE2
// -----------------------------------------------------------------------------

#if CPU(SSE2) && CPU(64BIT) && HAVE(INT128)

static inline uint int_is_xdig32 (const char_t* s)
{
  register uint n = int_is_xdig16 (s);

  if (n != 16u) return n;

  n = int_is_xdig16 (s + 16);

  if (n != 16u) return 16u + n;

  return 32u;
}

#endif // CPU(SSE2) && CPU(64BIT) && HAVE(INT128)

// -----------------------------------------------------------------------------
// Convert series of hexadecimal digit characters
// -----------------------------------------------------------------------------
// Convert a sequence of `x` hexadecimal digit characters to their numeric value
// -----------------------------------------------------------------------------

static inline uf8 int_from_xdig2s (const char_t* s)
{
  return (chr_xdig_to_int_fast (s[0]) << 4)
  | (chr_xdig_to_int_fast (s[1]));
}

static inline uf16 int_from_xdig4s (const char_t* s)
{
  return (chr_xdig_to_int_fast (s[0]) << 12)
  | (chr_xdig_to_int_fast (s[1]) << 8)
  | (chr_xdig_to_int_fast (s[2]) << 4)
  | (chr_xdig_to_int_fast (s[3]));
}

// -----------------------------------------------------------------------------
// Convert a vector of `x` hexadecimal digit characters to their numeric value
// -----------------------------------------------------------------------------

static inline uf8 int_from_xdig2v (const char_t* s)
{
#if (CHAR_BIT == 8) && HAVE(INT16)
  register u16 v = *(const u16*)s;

  #if CPU(LITTLE_ENDIAN)
    v = bswap16 (v);
  #endif

  register u16 l = v & 0x4040u;

  v = (v + ((l >> 3) | (l >> 6))) & 0x0F0Fu;

  return (v | (v >> 4)) & 0x00FFu;
#else
  return int_from_xdig2s (s);
#endif
}

static inline uf16 int_from_xdig4v (const char_t* s)
{
#if (CHAR_BIT == 8) && HAVE(INT32)
  register u32 v = *(const u32*)s;

  #if CPU(LITTLE_ENDIAN)
    v = bswap32 (v);
  #endif

  register u32 l = v & 0x40404040u;

  v = (v + ((l >> 3) | (l >> 6))) & 0x0F0F0F0Fu;
  v = (v | (v >> 4)) & 0x00FF00FFu;

  return (v | (v >> 8)) & 0x0000FFFFu;
#else
  return int_from_xdig4s (s);
#endif
}

// -----------------------------------------------------------------------------
// Convert 8 hexadecimal digit characters using SSE2
// -----------------------------------------------------------------------------

#if CPU(SSE2)

#define int_from_xdig8s int_from_xdig8
#define int_from_xdig8v int_from_xdig8

static inline uf32 int_from_xdig8 (const char_t* s)
{
  const xi128 v0 = _mm_set1_epi8 ('0');
  const xi128 va = _mm_set1_epi8 ('a' - 1);
  const xi128 vd = _mm_set1_epi8 ('a' - '0' - 10);

  u64 v = *(u64*)s;
  v |= (v & 0x4040404040404040u) >> 1;

  xi128 vi = _mm_cvtsi64_si128 (v);

  xi128 vs = _mm_and_si128 (_mm_cmpgt_epi8 (vi, va), vd);
  xi128 vr = _mm_sub_epi8 (_mm_sub_epi8 (vi, v0), vs);

  xi128 vf = _mm_srli_epi16 (_mm_or_si128 (vr, _mm_slli_epi64 (vr, 12)), 8);
  xi128 vp = _mm_packus_epi16 (vf, vf);

  return bswap32 (_mm_cvtsi128_si32 (vp));
}

#else // CPU(SSE2) ][

static inline uf32 int_from_xdig8s (const char_t* s)
{
  return (chr_xdig_to_int_fast (s[0]) << 28)
  | (chr_xdig_to_int_fast (s[1]) << 24)
  | (chr_xdig_to_int_fast (s[2]) << 20)
  | (chr_xdig_to_int_fast (s[3]) << 16)
  | (chr_xdig_to_int_fast (s[4]) << 12)
  | (chr_xdig_to_int_fast (s[5]) << 8)
  | (chr_xdig_to_int_fast (s[6]) << 4)
  | (chr_xdig_to_int_fast (s[7]));
}

static inline uf32 int_from_xdig8v (const char_t* s)
{
#if (CHAR_BIT == 8) && HAVE(INT64)
  register u64 v = *(const u64*)s;

  #if CPU(LITTLE_ENDIAN)
    v = bswap64 (v);
  #endif

  register u64 l = v & 0x4040404040404040u;

  v = (v + ((l >> 3) | (l >> 6))) & 0x0F0F0F0F0F0F0F0Fu;
  v = (v | (v >> 4)) & 0x00FF00FF00FF00FFu;
  v = (v | (v >> 8)) & 0x0000FFFF0000FFFFu;

  return (v | (v >> 16)) & 0x00000000FFFFFFFFu;
#else
  return int_from_xdig8s (s);
#endif
}

#endif // !CPU(SSE2)

// -----------------------------------------------------------------------------
// Convert 16 hexadecimal digit characters using SSE2
// -----------------------------------------------------------------------------

#if CPU(SSE2)

#define int_from_xdig16s int_from_xdig16
#define int_from_xdig16v int_from_xdig16

static inline uf64 int_from_xdig16 (const char_t* s)
{
  const xi128 vb = _mm_set1_epi8 (0x40);
  const xi128 v0 = _mm_set1_epi8 ('0');
  const xi128 va = _mm_set1_epi8 ('a' - 1);
  const xi128 vd = _mm_set1_epi8 ('a' - '0' - 10);

  xi128 vi = _mm_loadu_si128 ((const xi128*)s);
  xi128 vn = _mm_or_si128 (vi, _mm_srli_epi64 (_mm_and_si128 (vi, vb), 1));

  xi128 vs = _mm_and_si128 (_mm_cmpgt_epi8 (vn, va), vd);
  xi128 vr = _mm_sub_epi8 (_mm_sub_epi8 (vn, v0), vs);

  xi128 vf = _mm_srli_epi16 (_mm_or_si128 (vr, _mm_slli_epi64 (vr, 12)), 8);
  xi128 vp = _mm_packus_epi16 (vf, vf);

  return bswap64 (_mm_cvtsi128_si64 (vp));
}

#endif // CPU(SSE2)

// -----------------------------------------------------------------------------
// Convert 32 hexadecimal digit characters using SSE2
// -----------------------------------------------------------------------------

#if CPU(SSE2) && CPU(64BIT) && HAVE(INT128)

#define int_from_xdig32s int_from_xdig32
#define int_from_xdig32v int_from_xdig32

static inline uf128 int_from_xdig32 (const char_t* s)
{
  const xi128 vb = _mm_set1_epi8 (0x40);
  const xi128 v0 = _mm_set1_epi8 ('0');
  const xi128 va = _mm_set1_epi8 ('a' - 1);
  const xi128 vd = _mm_set1_epi8 ('a' - '0' - 10);

  xi128 vi1 = _mm_loadu_si128 ((const xi128*)s);
  xi128 vi2 = _mm_loadu_si128 ((const xi128*)(s + 16));

  xi128 vn1 = _mm_or_si128 (vi1, _mm_srli_epi64 (_mm_and_si128 (vi1, vb), 1));
  xi128 vn2 = _mm_or_si128 (vi2, _mm_srli_epi64 (_mm_and_si128 (vi2, vb), 1));

  xi128 vs1 = _mm_and_si128 (_mm_cmpgt_epi8 (vn1, va), vd);
  xi128 vs2 = _mm_and_si128 (_mm_cmpgt_epi8 (vn2, va), vd);

  xi128 vr1 = _mm_sub_epi8 (_mm_sub_epi8 (vn1, v0), vs1);
  xi128 vr2 = _mm_sub_epi8 (_mm_sub_epi8 (vn2, v0), vs2);

  xi128 vf1 = _mm_srli_epi16 (_mm_or_si128 (vr1, _mm_slli_epi64 (vr1, 12)), 8);
  xi128 vf2 = _mm_srli_epi16 (_mm_or_si128 (vr2, _mm_slli_epi64 (vr2, 12)), 8);

  xi128 vp = _mm_packus_epi16 (vf2, vf1);

  xi128_t v = {.x = vp};

  v.ui64[0] = bswap64 (v.ui64[0]);
  v.ui64[1] = bswap64 (v.ui64[1]);

  return v.ui128;
}

#endif // CPU(SSE2) && CPU(64BIT) && HAVE(INT128)

// -----------------------------------------------------------------------------
// Convert `x` hexadecimal digit characters to their numeric value
// -----------------------------------------------------------------------------

static inline uf16 int_from_xdig2 (const char_t* s)
{
#if CPU(UNALIGNED_ACCESS)
  return int_from_xdig2v (s);
#else
  return int_from_xdig2s (s);
#endif
}

static inline uf32 int_from_xdig4 (const char_t* s)
{
#if CPU(UNALIGNED_ACCESS)
  return int_from_xdig4v (s);
#else
  return int_from_xdig4s (s);
#endif
}

// -----------------------------------------------------------------------------
// Convert `x` misaligned hexadecimal digit characters
// before gaining the required alignment
// -----------------------------------------------------------------------------

#if 0

static inline uf16 int_from_xdig3s (const char_t* s, size_t n)
{
  register uf16 u = 0;

  if (n > 1u)
  {
    u = int_from_xdig2s (s);

    s += 2u;
    n -= 2u;
  }

  if (n != 0) u = (u << 4) + chr_xdig_to_int_fast (*s);

  return u;
}

static inline uf32 int_from_xdig7s (const char_t* s, size_t n)
{
  register uf32 u = 0;

  if (n > 3u)
  {
    u = int_from_xdig4s (s);

    s += 4u;
    n -= 4u;
  }

  if (n > 1u)
  {
    u = (u << 8) + int_from_xdig2s (s);

    s += 2u;
    n -= 2u;
  }

  if (n != 0) u = (u << 4) + chr_xdig_to_int_fast (*s);

  return u;
}

static inline uf64 int_from_xdig15s (const char_t* s, size_t n)
{
  register uf64 u = 0;

  if (n > 7u)
  {
    u = int_from_xdig8s (s);

    s += 8u;
    n -= 8u;
  }

  if (n > 3u)
  {
    u = (u << 16) + int_from_xdig4s (s);

    s += 4u;
    n -= 4u;
  }

  if (n > 1u)
  {
    u = (u << 8) + int_from_xdig2s (s);

    s += 2u;
    n -= 2u;
  }

  if (n != 0) u = (u << 4) + chr_xdig_to_int_fast (*s);

  return u;
}

#endif

// -----------------------------------------------------------------------------
// Convert `x` remaining aligned hexadecimal digit characters
// -----------------------------------------------------------------------------

static inline uf16 int_from_xdig3v (const char_t* s, size_t n)
{
  register uf16 u = 0;

  if (n > 1u)
  {
    u = int_from_xdig2v (s);

    s += 2u;
    n -= 2u;
  }

  if (n != 0) u = (u << 4) + chr_xdig_to_int_fast (*s);

  return u;
}

static inline uf32 int_from_xdig7v (const char_t* s, size_t n)
{
  register uf32 u = 0;

  if (n > 3u)
  {
    u = int_from_xdig4v (s);

    s += 4u;
    n -= 4u;
  }

  if (n > 1u)
  {
    u = (u * 100u) + int_from_xdig2v (s);

    s += 2u;
    n -= 2u;
  }

  if (n != 0) u = (u * 10u) + chr_xdig_to_int_fast (*s);

  return u;
}

static inline uf64 int_from_xdig15v (const char_t* s, size_t n)
{
  register uf64 u = 0;

  if (n > 7u)
  {
    u = int_from_xdig8v (s);

    s += 8u;
    n -= 8u;
  }

  if (n > 3u)
  {
    u = (u << 16) + int_from_xdig4v (s);

    s += 4u;
    n -= 4u;
  }

  if (n > 1u)
  {
    u = (u << 8) + int_from_xdig2v (s);

    s += 2u;
    n -= 2u;
  }

  if (n != 0) u = (u << 4) + chr_xdig_to_int_fast (*s);

  return u;
}

#if HAVE(INT_LEAST128) && CPU(SSE2) && CPU(64BIT)
static inline uf128 int_from_xdig31v (const char_t* s, size_t n)
{
  register uf128 u = 0;

  if (n > 15u)
  {
    u = int_from_xdig16v (s);

    s += 16u;
    n -= 16u;
  }

  if (n > 7u)
  {
    u = (u << 32) + int_from_xdig8v (s);

    s += 8u;
    n -= 8u;
  }

  if (n > 3u)
  {
    u = (u << 16) + int_from_xdig4v (s);

    s += 4u;
    n -= 4u;
  }

  if (n > 1u)
  {
    u = (u << 8) + int_from_xdig2v (s);

    s += 2u;
    n -= 2u;
  }

  if (n != 0) u = (u << 4) + chr_xdig_to_int_fast (*s);

  return u;
}
#endif // HAVE(INT_LEAST128) && CPU(SSE2) && CPU(64BIT)

// =============================================================================
// Functions
// -----------------------------------------------------------------------------
// 8-bit+
// -----------------------------------------------------------------------------

static inline sf8 int_s8_from_xstr (const char_t* str, size_t len)
{
  #define t_int uf8

  #define T_SIGN

  #include "deserialize/explicit/i8.c"
}

static inline uf8 int_u8_from_xstr (const char_t* str, size_t len)
{
  #define t_int uf8

  #include "deserialize/explicit/i8.c"
}

// -----------------------------------------------------------------------------

static inline sf8 int_s8_from_xstri (const char_t* str)
{
  #define t_int uf8

  #define T_SIGN

  #include "deserialize/implicit/i8.c"
}

static inline uf8 int_u8_from_xstri (const char_t* str)
{
  #define t_int uf8

  #include "deserialize/implicit/i8.c"
}

// -----------------------------------------------------------------------------
// 16-bit+
// -----------------------------------------------------------------------------

static inline sf16 int_s16_from_xstr (const char_t* str, size_t len)
{
  #define t_int uf16

  #define T_SIGN

  #include "deserialize/explicit/i16.c"
}

static inline uf16 int_u16_from_xstr (const char_t* str, size_t len)
{
  #define t_int uf16

  #include "deserialize/explicit/i16.c"
}

// -----------------------------------------------------------------------------

static inline sf16 int_s16_from_xstri (const char_t* str)
{
  #define t_int uf16

  #define T_SIGN

  #include "deserialize/implicit/i16.c"
}

static inline uf16 int_u16_from_xstri (const char_t* str)
{
  #define t_int uf16

  #include "deserialize/implicit/i16.c"
}

// -----------------------------------------------------------------------------
// 32-bit+
// -----------------------------------------------------------------------------

static inline sf32 int_s32_from_xstr (const char_t* str, size_t len)
{
  #define t_int uf32

  #define T_SIGN

  #include "deserialize/explicit/i32.c"
}

static inline uf32 int_u32_from_xstr (const char_t* str, size_t len)
{
  #define t_int uf32

  #include "deserialize/explicit/i32.c"
}

// -----------------------------------------------------------------------------

static inline sf32 int_s32_from_xstri (const char_t* str)
{
  #define t_int uf32

  #define T_SIGN

  #include "deserialize/implicit/i32.c"
}

static inline uf32 int_u32_from_xstri (const char_t* str)
{
  #define t_int uf32

  #include "deserialize/implicit/i32.c"
}

// -----------------------------------------------------------------------------
// 64-bit+
// -----------------------------------------------------------------------------

static inline sf64 int_s64_from_xstr (const char_t* str, size_t len)
{
  #define t_int uf64

  #define T_SIGN

  #include "deserialize/explicit/i64.c"
}

static inline uf64 int_u64_from_xstr (const char_t* str, size_t len)
{
  #define t_int uf64

  #include "deserialize/explicit/i64.c"
}

// -----------------------------------------------------------------------------

static inline sf64 int_s64_from_xstri (const char_t* str)
{
  #define t_int uf64

  #define T_SIGN

  #include "deserialize/implicit/i64.c"
}

static inline uf64 int_u64_from_xstri (const char_t* str)
{
  #define t_int uf64

  #include "deserialize/implicit/i64.c"
}

// -----------------------------------------------------------------------------
// 128-bit+
// -----------------------------------------------------------------------------

#if HAVE(INT_LEAST128)

static inline sf128 int_s128_from_xstr (const char_t* str, size_t len)
{
  #define t_int uf128

  #define T_SIGN

  #include "deserialize/explicit/i128.c"
}

static inline uf128 int_u128_from_xstr (const char_t* str, size_t len)
{
  #define t_int uf128

  #include "deserialize/explicit/i128.c"
}

// -----------------------------------------------------------------------------

static inline sf128 int_s128_from_xstri (const char_t* str)
{
  #define t_int uf128

  #define T_SIGN

  #include "deserialize/implicit/i128.c"
}

static inline uf128 int_u128_from_xstri (const char_t* str)
{
  #define t_int uf128

  #include "deserialize/implicit/i128.c"
}

#endif // HAVE(INT_LEAST128)

// -----------------------------------------------------------------------------
// Maximum
// -----------------------------------------------------------------------------

static inline intmax_t int_smax_from_xstr (const char_t* str, size_t len)
{
  #define t_int uintmax_t

  #define T_SIGN

#if (INTMAX_BIT >= 128)
  #include "deserialize/explicit/i128.c"
#else
  #include "deserialize/explicit/i64.c"
#endif
}

static inline uintmax_t int_umax_from_xstr (const char_t* str, size_t len)
{
  #define t_int uintmax_t

#if (INTMAX_BIT >= 128)
  #include "deserialize/explicit/i128.c"
#else
  #include "deserialize/explicit/i64.c"
#endif
}

// -----------------------------------------------------------------------------

static inline intmax_t int_smax_from_xstri (const char_t* str)
{
  #define t_int uintmax_t

  #define T_SIGN

#if (INTMAX_BIT >= 128)
  #include "deserialize/implicit/i128.c"
#else
  #include "deserialize/implicit/i64.c"
#endif
}

static inline uintmax_t int_umax_from_xstri (const char_t* str)
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

static inline intptr_t int_sptr_from_xstr (const char_t* str, size_t len)
{
  #define t_int uintptr_t

  #define T_SIGN

#if (INTPTR_BIT >= 64)
  #include "deserialize/explicit/i64.c"
#else
  #include "deserialize/explicit/i32.c"
#endif
}

static inline uintptr_t int_uptr_from_xstr (const char_t* str, size_t len)
{
  #define t_int uintptr_t

#if (INTPTR_BIT >= 64)
  #include "deserialize/explicit/i64.c"
#else
  #include "deserialize/explicit/i32.c"
#endif
}

// -----------------------------------------------------------------------------

static inline intptr_t int_sptr_from_xstri (const char_t* str)
{
  #define t_int uintptr_t

  #define T_SIGN

#if (INTPTR_BIT >= 64)
  #include "deserialize/implicit/i64.c"
#else
  #include "deserialize/implicit/i32.c"
#endif
}

static inline uintptr_t int_uptr_from_xstri (const char_t* str)
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
// Map the hexadecimal string conversion functions above
// to the fundamental integral types
// -----------------------------------------------------------------------------
// `char`
// -----------------------------------------------------------------------------

#if (CHAR_BIT == INTMAX_BIT)
  #define int_schar_from_xstr int_smax_from_xstr
  #define int_uchar_from_xstr int_umax_from_xstr

  #define int_schar_from_xstri int_smax_from_xstri
  #define int_uchar_from_xstri int_umax_from_xstri
#elif (CHAR_BIT == INT_FAST64_BIT)
  #define int_schar_from_xstr int_s64_from_xstr
  #define int_uchar_from_xstr int_u64_from_xstr

  #define int_schar_from_xstri int_s64_from_xstri
  #define int_uchar_from_xstri int_u64_from_xstri
#elif (CHAR_BIT == INT_FAST32_BIT)
  #define int_schar_from_xstr int_s32_from_xstr
  #define int_uchar_from_xstr int_u32_from_xstr

  #define int_schar_from_xstri int_s32_from_xstri
  #define int_uchar_from_xstri int_u32_from_xstri
#elif (CHAR_BIT == INT_FAST16_BIT)
  #define int_schar_from_xstr int_s16_from_xstr
  #define int_uchar_from_xstr int_u16_from_xstr

  #define int_schar_from_xstri int_s16_from_xstri
  #define int_uchar_from_xstri int_u16_from_xstri
#elif (CHAR_BIT == INT_FAST8_BIT)
  #define int_schar_from_xstr int_s8_from_xstr
  #define int_uchar_from_xstr int_u8_from_xstr

  #define int_schar_from_xstri int_s8_from_xstri
  #define int_uchar_from_xstri int_u8_from_xstri
#endif

// -----------------------------------------------------------------------------
// `short`
// -----------------------------------------------------------------------------

#if (SHRT_BIT == INTMAX_BIT)
  #define int_sshort_from_xstr int_smax_from_xstr
  #define int_ushort_from_xstr int_umax_from_xstr

  #define int_sshort_from_xstri int_smax_from_xstri
  #define int_ushort_from_xstri int_umax_from_xstri
#elif (SHRT_BIT == INT_FAST64_BIT)
  #define int_sshort_from_xstr int_s64_from_xstr
  #define int_ushort_from_xstr int_u64_from_xstr

  #define int_sshort_from_xstri int_s64_from_xstri
  #define int_ushort_from_xstri int_u64_from_xstri
#elif (SHRT_BIT == INT_FAST32_BIT)
  #define int_sshort_from_xstr int_s32_from_xstr
  #define int_ushort_from_xstr int_u32_from_xstr

  #define int_sshort_from_xstri int_s32_from_xstri
  #define int_ushort_from_xstri int_u32_from_xstri
#elif (SHRT_BIT == INT_FAST16_BIT)
  #define int_sshort_from_xstr int_s16_from_xstr
  #define int_ushort_from_xstr int_u16_from_xstr

  #define int_sshort_from_xstri int_s16_from_xstri
  #define int_ushort_from_xstri int_u16_from_xstri
#endif

// -----------------------------------------------------------------------------
// `int`
// -----------------------------------------------------------------------------

#if (INT_BIT == INTMAX_BIT)
  #define int_sint_from_xstr int_smax_from_xstr
  #define int_uint_from_xstr int_umax_from_xstr

  #define int_sint_from_xstri int_smax_from_xstri
  #define int_uint_from_xstri int_umax_from_xstri
#elif (INT_BIT == INT_FAST64_BIT)
  #define int_sint_from_xstr int_s64_from_xstr
  #define int_uint_from_xstr int_u64_from_xstr

  #define int_sint_from_xstri int_s64_from_xstri
  #define int_uint_from_xstri int_u64_from_xstri
#elif (INT_BIT == INT_FAST32_BIT)
  #define int_sint_from_xstr int_s32_from_xstr
  #define int_uint_from_xstr int_u32_from_xstr

  #define int_sint_from_xstri int_s32_from_xstri
  #define int_uint_from_xstri int_u32_from_xstri
#elif (INT_BIT == INT_FAST16_BIT)
  #define int_sint_from_xstr int_s16_from_xstr
  #define int_uint_from_xstr int_u16_from_xstr

  #define int_sint_from_xstri int_s16_from_xstri
  #define int_uint_from_xstri int_u16_from_xstri
#endif

// -----------------------------------------------------------------------------
// `long`
// -----------------------------------------------------------------------------

#if (LONG_BIT == INTMAX_BIT)
  #define int_slong_from_xstr int_smax_from_xstr
  #define int_ulong_from_xstr int_umax_from_xstr

  #define int_slong_from_xstri int_smax_from_xstri
  #define int_ulong_from_xstri int_umax_from_xstri
#elif (LONG_BIT == INT_FAST64_BIT)
  #define int_slong_from_xstr int_s64_from_xstr
  #define int_ulong_from_xstr int_u64_from_xstr

  #define int_slong_from_xstri int_s64_from_xstri
  #define int_ulong_from_xstri int_u64_from_xstri
#elif (LONG_BIT == INT_FAST32_BIT)
  #define int_slong_from_xstr int_s32_from_xstr
  #define int_ulong_from_xstr int_u32_from_xstr

  #define int_slong_from_xstri int_s32_from_xstri
  #define int_ulong_from_xstri int_u32_from_xstri
#endif

// -----------------------------------------------------------------------------
// `llong`
// -----------------------------------------------------------------------------

#if (LLONG_BIT == INTMAX_BIT)
  #define int_sllong_from_xstr int_smax_from_xstr
  #define int_ullong_from_xstr int_umax_from_xstr

  #define int_sllong_from_xstri int_smax_from_xstri
  #define int_ullong_from_xstri int_umax_from_xstri
#elif (LLONG_BIT == INT_FAST64_BIT)
  #define int_sllong_from_xstr int_s64_from_xstr
  #define int_ullong_from_xstr int_u64_from_xstr

  #define int_sllong_from_xstri int_s64_from_xstri
  #define int_ullong_from_xstri int_u64_from_xstri
#endif

// -----------------------------------------------------------------------------

#include "support/outro.h"

// -----------------------------------------------------------------------------

#endif
