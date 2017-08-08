// =============================================================================
// <integer/convert/hexadecimal/serialize.c>
//
// Convert integral numbers to hexadecimal strings fast
// with no formatting (except for character case).
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_F93453873C0A4832B9FEE811071D2702
#define H_F93453873C0A4832B9FEE811071D2702

// =============================================================================
// Utility functions
// -----------------------------------------------------------------------------
// Hexadecimal integer length computation
// -----------------------------------------------------------------------------
// Generic hexadecimal integer length computation microtemplate
#define int_xlen(val, len) do\
{                            \
  len = 0;                   \
                             \
  while (true)               \
  {                          \
    if ((val) < 0x10000u)    \
    {                        \
      len += ((val) > 0xFFu) \
      ? (3u + ((val) > 0xFFFu))\
      : (1u + ((val) > 0xFu));\
               \
      break;   \
    }          \
               \
    val >>= 16;\
    len += 4u;\
  }       \
          \
} while (0)

// -----------------------------------------------------------------------------
// Unsigned hexadecimal integer length computation
// -----------------------------------------------------------------------------

static inline size_t int_u8_xlen (uf8 val)
{
#if HAVE(INT8)
  return 1u + (val > 0xFu);
#else
  size_t len;
  int_xlen (val, len);
  return len;
#endif
}

static inline size_t int_u16_xlen (uf16 val)
{
#if HAVE(INT16)
  return ((val > 0xFFu) ? (3u + (val > 0xFFFu)) : (1u + (val > 0xFu)));
#else
  size_t len;
  int_xlen (val, len);
  return len;
#endif
}

static inline size_t int_u32_xlen (uf32 val)
{
#if HAVE(INT32)
  return ((val == 0) ? 1u : ((bsr32 (val) / 4u) + 1u));
#else
  size_t len;
  int_xlen (val, len);
  return len;
#endif
}

static inline size_t int_u64_xlen (uf64 val)
{
#if HAVE(INT64)
  return ((val == 0) ? 1u : ((bsr64 (val) / 4u) + 1u));
#else
  size_t len;
  int_xlen (val, len);
  return len;
#endif
}

#if HAVE(INT_LEAST128)
static inline size_t int_u128_xlen (uf128 val)
{
#if HAVE(INT128)
  return ((val == 0) ? 1u : ((bsr128 (val) / 4u) + 1u));
#else
  size_t len;
  int_xlen (val, len);
  return len;
#endif
}
#endif // HAVE(INT_LEAST128)

static inline size_t int_umax_xlen (uintmax_t val)
{
#if (INTMAX_BIT == 128)
  return int_u128_xlen (val);
#elif (INTMAX_BIT == 64)
  return int_u64_xlen (val);
#else
  size_t len;
  int_xlen (val, len);
  return len;
#endif
}

static inline size_t int_uptr_xlen (uintptr_t val)
{
#if (INTPTR_BIT == 64)
  return int_u64_xlen (val);
#elif (INTPTR_BIT == 32)
  return int_u32_xlen (val);
#else
  size_t len;
  int_xlen (val, len);
  return len;
#endif
}

// -----------------------------------------------------------------------------
// Signed hexadecimal integer length computation
// -----------------------------------------------------------------------------

static inline size_t int_s8_xlen (sf8 val)
{
  return int_u8_xlen (int_s8_abs (val));
}

static inline size_t int_s16_xlen (sf16 val)
{
  return int_u16_xlen (int_s16_abs (val));
}

static inline size_t int_s32_xlen (sf32 val)
{
  return int_u32_xlen (int_s32_abs (val));
}

static inline size_t int_s64_xlen (sf64 val)
{
  return int_u64_xlen (int_s64_abs (val));
}

#if HAVE(INT_LEAST128)
static inline size_t int_s128_xlen (sf128 val)
{
  return int_u128_xlen (int_s128_abs (val));
}
#endif

static inline size_t int_smax_xlen (intmax_t val)
{
  return int_umax_xlen (int_max_abs (val));
}

static inline size_t int_sptr_xlen (intptr_t val)
{
  return int_uptr_xlen (int_ptr_abs (val));
}

// -----------------------------------------------------------------------------
// `char`
#if (CHAR_BIT == INT_FAST8_BIT)
  #define int_uchar_xlen int_u8_xlen
  #define int_schar_xlen int_s8_xlen
#elif (CHAR_BIT == INT_FAST16_BIT)
  #define int_uchar_xlen int_u16_xlen
  #define int_schar_xlen int_s16_xlen
#elif (CHAR_BIT == INT_FAST32_BIT)
  #define int_uchar_xlen int_u32_xlen
  #define int_schar_xlen int_s32_xlen
#elif (CHAR_BIT == INT_FAST64_BIT)
  #define int_uchar_xlen int_u64_xlen
  #define int_schar_xlen int_s64_xlen
#elif (CHAR_BIT == INTMAX_BIT)
  #define int_uchar_xlen int_umax_xlen
  #define int_schar_xlen int_smax_xlen
#endif

// -----------------------------------------------------------------------------
// `short`
#if (SHRT_BIT == INT_FAST16_BIT)
  #define int_ushort_xlen int_u16_xlen
  #define int_sshort_xlen int_s16_xlen
#elif (SHRT_BIT == INT_FAST32_BIT)
  #define int_ushort_xlen int_u32_xlen
  #define int_sshort_xlen int_s32_xlen
#elif (SHRT_BIT == INT_FAST64_BIT)
  #define int_ushort_xlen int_u64_xlen
  #define int_sshort_xlen int_s64_xlen
#elif (SHRT_BIT == INTMAX_BIT)
  #define int_ushort_xlen int_umax_xlen
  #define int_sshort_xlen int_smax_xlen
#endif

// -----------------------------------------------------------------------------
// `int`
#if (INT_BIT == INT_FAST16_BIT)
  #define int_uint_xlen int_u16_xlen
  #define int_sint_xlen int_s16_xlen
#elif (INT_BIT == INT_FAST32_BIT)
  #define int_uint_xlen int_u32_xlen
  #define int_sint_xlen int_s32_xlen
#elif (INT_BIT == INT_FAST64_BIT)
  #define int_uint_xlen int_u64_xlen
  #define int_sint_xlen int_s64_xlen
#elif (INT_BIT == INTMAX_BIT)
  #define int_uint_xlen int_umax_xlen
  #define int_sint_xlen int_smax_xlen
#endif

// -----------------------------------------------------------------------------
// `long`
#if (LONG_BIT == INT_FAST32_BIT)
  #define int_ulong_xlen int_u32_xlen
  #define int_slong_xlen int_s32_xlen
#elif (LONG_BIT == INT_FAST64_BIT)
  #define int_ulong_xlen int_u64_xlen
  #define int_slong_xlen int_s64_xlen
#elif (LONG_BIT == INTMAX_BIT)
  #define int_ulong_xlen int_umax_xlen
  #define int_slong_xlen int_smax_xlen
#endif

// -----------------------------------------------------------------------------
// `llong`
#if (LLONG_BIT == INT_FAST64_BIT)
  #define int_ullong_xlen int_u64_xlen
  #define int_sllong_xlen int_s64_xlen
#elif (LLONG_BIT == INTMAX_BIT)
  #define int_ullong_xlen int_umax_xlen
  #define int_sllong_xlen int_smax_xlen
#endif

// -----------------------------------------------------------------------------

#undef int_xlen

// -----------------------------------------------------------------------------
// Convert an integer to a hexadecimal string
// -----------------------------------------------------------------------------
// Produce `x` hexadecimal digit characters
// -----------------------------------------------------------------------------

#define int_to_xdig2(buf, val, lcase) int_to_xdig2f ((buf), (val), (lcase) * 0x20u)

static inline void int_to_xdig2s (char_t* b, uf8 u, uint l)
{
  uint b1 = u & 0xFu;
  uint b0 = u >> 4;

  b[0] = chr_xdig_from_int (b0) | l;
  b[1] = chr_xdig_from_int (b1) | l;
}

static inline void int_to_xdig2v (char_t* b, uf8 u, uint l)
{
#if HAVE(INT16) && (CHAR_BIT == 8) && 0
  u16 ne = u & 0x0Fu;
  u16 no = u & 0xF0u;

  u16 ve = (ne * 0x01u) & 0x00FFu;
  u16 vo = (no * 0x10u) & 0xFF00u;

  u16 v = ve | vo;

  #if CPU(LITTLE_ENDIAN)
    v = bswap16 (v);
  #endif

  u16 va = v + 0x3030u;
  u16 vt = v + 0x7676u;

  u16 vb = vt & 0x8080u;
  u16 vm = vb - (vb >> 7);

  *(u16*)b = (va + (vm & 0x2727u)) | (0x0101u * l);
#else
  int_to_xdig2s (b, u, l);
#endif
}

static inline void int_to_xdig2f (char_t* b, uf8 u, uint l)
{
#if CPU(UNALIGNED_ACCESS)
  int_to_xdig2v (b, u, l);
#else
  int_to_xdig2s (b, u, l);
#endif
}

// -----------------------------------------------------------------------------

#define int_to_xdig4(buf, val, lcase) int_to_xdig4f ((buf), (val), (lcase) * 0x20u)

static inline void int_to_xdig4s (char_t* b, uf16 u, uint l)
{
  uint b3 = u & 0xFu;
  uint b2 = (u >> 4) & 0xFu;
  uint b1 = (u >> 8) & 0xFu;
  uint b0 = u >> 12;

  b[0] = chr_xdig_from_int (b0) | l;
  b[1] = chr_xdig_from_int (b1) | l;
  b[2] = chr_xdig_from_int (b2) | l;
  b[3] = chr_xdig_from_int (b3) | l;
}

static inline void int_to_xdig4v (char_t* b, uf16 u, uint l)
{
#if HAVE(INT32) && (CHAR_BIT == 8)
  u32 ne = u & 0x0F0Fu;
  u32 no = u & 0xF0F0u;

  u32 ve = (ne * 0x0101u) & 0x00FF00FFu;
  u32 vo = (no * 0x1010u) & 0xFF00FF00u;

  u32 v = ve | vo;

  #if CPU(LITTLE_ENDIAN)
    v = bswap32 (v);
  #endif

  u32 va = v + 0x30303030u;
  u32 vt = v + 0x70707676u;

  u32 vb = vt & 0x80808080u;
  u32 vm = vb - (vb >> 7);

  *(u32*)b = (va + (vm & 0x27272727u)) | (0x01010101u * l);
#else
  int_to_xdig4s (b, u, l);
#endif
}

static inline void int_to_xdig4f (char_t* b, uf16 u, uint l)
{
#if CPU(UNALIGNED_ACCESS)
  int_to_xdig4v (b, u, l);
#else
  int_to_xdig4s (b, u, l);
#endif
}

// -----------------------------------------------------------------------------

#define int_to_xdig8(buf, val, lcase) int_to_xdig8f ((buf), (val), (lcase) * 0x20u)

static inline void int_to_xdig8s (char_t* b, uf32 u, uint l)
{
  uint b7 = u & 0xFu;
  uint b6 = (u >> 4) & 0xFu;
  uint b5 = (u >> 8) & 0xFu;
  uint b4 = (u >> 12) & 0xFu;
  uint b3 = (u >> 16) & 0xFu;
  uint b2 = (u >> 20) & 0xFu;
  uint b1 = (u >> 24) & 0xFu;
  uint b0 = u >> 28;

  b[0] = chr_xdig_from_int (b0) | l;
  b[1] = chr_xdig_from_int (b1) | l;
  b[2] = chr_xdig_from_int (b2) | l;
  b[3] = chr_xdig_from_int (b3) | l;
  b[4] = chr_xdig_from_int (b4) | l;
  b[5] = chr_xdig_from_int (b5) | l;
  b[6] = chr_xdig_from_int (b6) | l;
  b[7] = chr_xdig_from_int (b7) | l;
}

static inline void int_to_xdig8v (char_t* b, uf32 u, uint l)
{
#if HAVE(INT64) && (CHAR_BIT == 8)
  u64 ne = u & 0x0F0F0F0Fu;
  u64 no = u & 0xF0F0F0F0u;

  u64 ve = (ne * 0x01010101u) & 0x00FF00FF00FF00FFu;
  u64 vo = (no * 0x10101010u) & 0xFF00FF00FF00FF00u;

  u64 v = ve | vo;

  #if CPU(LITTLE_ENDIAN)
    v = bswap64 (v);
  #endif

  u64 va = v + 0x3030303030303030u;
  u64 vt = v + 0x7070767670707676u;

  u64 vb = vt & 0x8080808080808080u;
  u64 vm = vb - (vb >> 7);

  *(u64*)b = (va + (vm & 0x2727272727272727u)) | (0x0101010101010101u * l);
#else
  int_to_xdig8s (b, u, l);
#endif
}

static inline void int_to_xdig8f (char_t* b, uf32 u, uint l)
{
#if CPU(UNALIGNED_ACCESS)
  int_to_xdig8v (b, u, l);
#else
  int_to_xdig8s (b, u, l);
#endif
}

// -----------------------------------------------------------------------------

#if CPU(SSE2)

#define int_to_xdig16(buf, val, lcase) int_to_xdig16f ((buf), (val), (lcase) * 0x20u)

#define int_to_xdig16s int_to_xdig16f
#define int_to_xdig16v int_to_xdig16f

static inline void int_to_xdig16f (char_t* b, uf64 u, uint l)
{
  const xi128 vb = _mm_set1_epi8 (0xF);
  const xi128 vn = _mm_set1_epi8 (9);
  const xi128 v0 = _mm_set1_epi8 ('0');
  const xi128 vd = _mm_set1_epi8 ('a' - '0' - 10);

  xi128 vi = _mm_cvtsi64_si128 (u);

  xi128 ve = _mm_and_si128 (vi, vb);
  xi128 vo = _mm_and_si128 (_mm_srli_epi64 (vi, 8), vb);

  xi128 vx = _mm_unpacklo_epi8 (ve, vo);
  xi128 vm = _mm_cmpgt_epi8 (vx, vn);
  xi128 vr = _mm_add_epi8 (_mm_add_epi8 (vx, _mm_and_si128 (vm, vd)), v0);

  vr = _mm_or_si128 (vr, _mm_set1_epi8 (l));

  _mm_storeu_si128 ((xi128*)b, vr);
}

#endif // CPU(SSE2)

// -----------------------------------------------------------------------------
// Recursive division utility macros
// -----------------------------------------------------------------------------

#define int_left_xdig() do\
{                         \
  *b = chr_xdig_from_int (u) | l;\
  return b + 1;\
} while (0)

#define int_left_xdig2() do\
{                          \
  *b = chr_xdig_from_int (u >> 4) | l;\
  b += (u >= 0x10u);       \
  *b = chr_xdig_from_int (u & 0xFu) | l;\
               \
  return b + 1;\
} while (0)

#define int_left_xdig3() do\
{                          \
  if (u >= 0x100u)         \
  {                        \
    uint q = u >> 8;       \
    uint r = u & 0xFFu;    \
                           \
    *b = chr_xdig_from_int (q) | l;\
    int_to_xdig2f (b + 1, r, l);\
                 \
    return b + 3;\
  }       \
} while (0)

#define int_left_xdig4() do\
{                          \
  if (u >= 0x1000u)        \
  {                        \
    int_to_xdig4f (b, u, l);\
    return b + 4;\
  }       \
} while (0)

// -----------------------------------------------------------------------------
// Recursive division tail functions
// -----------------------------------------------------------------------------

static inline char_t* int_tail_xdig (char_t* b, uint u, uint l)
{
  int_left_xdig();
}

static inline char_t* int_tail_xdig2 (char_t* b, uint u, uint l)
{
  int_left_xdig2();
}

static inline char_t* int_tail_xdig3 (char_t* b, uint u, uint l)
{
  int_left_xdig3();
  int_left_xdig2();
}

static inline char_t* int_tail_xdig4 (char_t* b, uint u, uint l)
{
  int_left_xdig4();
  int_left_xdig3();
  int_left_xdig2();
}

// -----------------------------------------------------------------------------

#undef int_left_xdig
#undef int_left_xdig2
#undef int_left_xdig3
#undef int_left_xdig4

// -----------------------------------------------------------------------------
// Recursive division functions
// -----------------------------------------------------------------------------

static inline char_t* int_div_xdig (char_t* b, uf8 u, uint l)
{
  if (u >= 0x10u)
  {
    uint q = u >> 4;
    uint r = u & 0xFu;

    b = int_div_xdig (b, q, l);
    *b = chr_xdig_from_int (r) | l;

    return b + 1;
  }

  return int_tail_xdig (b, u, l);
}

static inline char_t* int_div_xdig2 (char_t* b, uf16 u, uint l)
{
  if (u >= 0x100u)
  {
    uint q = u >> 8;
    uint r = u & 0xFFu;

    b = int_div_xdig2 (b, q, l);
    int_to_xdig2f (b, r, l);

    return b + 2;
  }

  return int_tail_xdig2 (b, u, l);
}

static inline char_t* int_div_xdig4 (char_t* b, uf32 u, uint l)
{
  if (u >= 0x10000u)
  {
    uf32 q = u >> 16;
    uf32 r = u & 0xFFFFu;

    b = int_div_xdig4 (b, q, l);
    int_to_xdig4f (b, r, l);

    return b + 4;
  }

  return int_tail_xdig4 (b, u, l);
}

static inline char_t* int_div_xdig8 (char_t* b, uf64 u, uint l)
{
  if (u >= 0x100000000u)
  {
    uf64 q = u >> 32;
    uf64 r = u & 0xFFFFFFFFu;

    b = int_div_xdig8 (b, q, l);
    int_to_xdig8f (b, r, l);

    return b + 8;
  }

  return int_div_xdig4 (b, u, l);
}

#if HAVE(INT_LEAST128)
static inline char_t* int_div_xdig16 (char_t* b, uf128 u, uint l)
{
  if (u >= ((uf128)1u << 64))
  {
    uf128 q = u >> 64;
    uf128 r = u & 0xFFFFFFFFFFFFFFFFu;

    b = int_div_xdig16 (b, q, l);
    int_to_xdig16f (b, r, l);

    return b + 16;
  }

  return int_div_xdig8 (b, u, l);
}
#endif

// =============================================================================
// Functions
// -----------------------------------------------------------------------------
// 8-bit+
// -----------------------------------------------------------------------------

static inline size_t int_s8_to_xstr (char_t* buf, sf8 val, bint lcase)
{
  #define t_int uf8

  #define T_SIGN

  #include "serialize/basic/i8.c"
}

static inline size_t int_u8_to_xstr (char_t* buf, uf8 val, bint lcase)
{
  #define t_int uf8

  #include "serialize/basic/i8.c"
}

// -----------------------------------------------------------------------------

static inline char_t* int_s8_to_xstri (char_t* buf, sf8 val, bint lcase)
{
  size_t len = int_s8_to_xstr (buf, val, lcase);

  buf[len] = '\0';

  return buf + len;
}

static inline char_t* int_u8_to_xstri (char_t* buf, uf8 val, bint lcase)
{
  size_t len = int_u8_to_xstr (buf, val, lcase);

  buf[len] = '\0';

  return buf + len;
}

// -----------------------------------------------------------------------------
// 16-bit+
// -----------------------------------------------------------------------------

static inline size_t int_s16_to_xstr (char_t* buf, sf16 val, bint lcase)
{
  #define t_int uf16

  #define T_SIGN

  #include "serialize/basic/i16.c"
}

static inline size_t int_u16_to_xstr (char_t* buf, uf16 val, bint lcase)
{
  #define t_int uf16

  #include "serialize/basic/i16.c"
}

// -----------------------------------------------------------------------------

static inline char_t* int_s16_to_xstri (char_t* buf, sf16 val, bint lcase)
{
  size_t len = int_s16_to_xstr (buf, val, lcase);

  buf[len] = '\0';

  return buf + len;
}

static inline char_t* int_u16_to_xstri (char_t* buf, uf16 val, bint lcase)
{
  size_t len = int_u16_to_xstr (buf, val, lcase);

  buf[len] = '\0';

  return buf + len;
}

// -----------------------------------------------------------------------------
// 32-bit+
// -----------------------------------------------------------------------------

static inline size_t int_s32_to_xstr (char_t* buf, sf32 val, bint lcase)
{
  #define t_int uf32

  #define T_SIGN

  #include "serialize/basic/i32.c"
}

static inline size_t int_u32_to_xstr (char_t* buf, uf32 val, bint lcase)
{
  #define t_int uf32

  #include "serialize/basic/i32.c"
}

// -----------------------------------------------------------------------------

static inline char_t* int_s32_to_xstri (char_t* buf, sf32 val, bint lcase)
{
  size_t len = int_s32_to_xstr (buf, val, lcase);

  buf[len] = '\0';

  return buf + len;
}

static inline char_t* int_u32_to_xstri (char_t* buf, uf32 val, bint lcase)
{
  size_t len = int_u32_to_xstr (buf, val, lcase);

  buf[len] = '\0';

  return buf + len;
}

// -----------------------------------------------------------------------------
// 64-bit+
// -----------------------------------------------------------------------------

static inline size_t int_s64_to_xstr (char_t* buf, sf64 val, bint lcase)
{
  #define t_int uf64

  #define T_SIGN

  #include "serialize/basic/i64.c"
}

static inline size_t int_u64_to_xstr (char_t* buf, uf64 val, bint lcase)
{
  #define t_int uf64

  #include "serialize/basic/i64.c"
}

// -----------------------------------------------------------------------------

static inline char_t* int_s64_to_xstri (char_t* buf, sf64 val, bint lcase)
{
  size_t len = int_s64_to_xstr (buf, val, lcase);

  buf[len] = '\0';

  return buf + len;
}

static inline char_t* int_u64_to_xstri (char_t* buf, uf64 val, bint lcase)
{
  size_t len = int_u64_to_xstr (buf, val, lcase);

  buf[len] = '\0';

  return buf + len;
}

// -----------------------------------------------------------------------------
// 128-bit+
// -----------------------------------------------------------------------------

#if HAVE(INT_LEAST128)

static inline size_t int_s128_to_xstr (char_t* buf, sf128 val, bint lcase)
{
  #define t_int uf128

  #define T_SIGN

  #include "serialize/basic/i128.c"
}

static inline size_t int_u128_to_xstr (char_t* buf, uf128 val, bint lcase)
{
  #define t_int uf128

  #include "serialize/basic/i128.c"
}

// -----------------------------------------------------------------------------

static inline char_t* int_s128_to_xstri (char_t* buf, sf128 val, bint lcase)
{
  size_t len = int_s128_to_xstr (buf, val, lcase);

  buf[len] = '\0';

  return buf + len;
}

static inline char_t* int_u128_to_xstri (char_t* buf, uf128 val, bint lcase)
{
  size_t len = int_u128_to_xstr (buf, val, lcase);

  buf[len] = '\0';

  return buf + len;
}

#endif // HAVE(INT_LEAST128)

// -----------------------------------------------------------------------------
// Maximum
// -----------------------------------------------------------------------------

static inline size_t int_smax_to_xstr (char_t* buf, intmax_t val, bint lcase)
{
  #define t_int uintmax_t

  #define T_SIGN

#if (INTMAX_BIT >= 128)
  #include "serialize/basic/i128.c"
#else
  #include "serialize/basic/i64.c"
#endif
}

static inline size_t int_umax_to_xstr (char_t* buf, uintmax_t val, bint lcase)
{
  #define t_int uintmax_t

#if (INTMAX_BIT >= 128)
  #include "serialize/basic/i128.c"
#else
  #include "serialize/basic/i64.c"
#endif
}

// -----------------------------------------------------------------------------

static inline char_t* int_smax_to_xstri (char_t* buf, intmax_t val, bint lcase)
{
  size_t len = int_smax_to_xstr (buf, val, lcase);

  buf[len] = '\0';

  return buf + len;
}

static inline char_t* int_umax_to_xstri (char_t* buf, uintmax_t val, bint lcase)
{
  size_t len = int_umax_to_xstr (buf, val, lcase);

  buf[len] = '\0';

  return buf + len;
}

// -----------------------------------------------------------------------------
// Pointer
// -----------------------------------------------------------------------------

static inline size_t int_sptr_to_xstr (char_t* buf, intptr_t val, bint lcase)
{
  #define t_int uintptr_t

  #define T_SIGN

#if (INTPTR_BIT >= 64)
  #include "serialize/basic/i64.c"
#else
  #include "serialize/basic/i32.c"
#endif
}

static inline size_t int_uptr_to_xstr (char_t* buf, uintptr_t val, bint lcase)
{
  #define t_int uintptr_t

#if (INTPTR_BIT >= 64)
  #include "serialize/basic/i64.c"
#else
  #include "serialize/basic/i32.c"
#endif
}

// -----------------------------------------------------------------------------

static inline char_t* int_sptr_to_xstri (char_t* buf, intptr_t val, bint lcase)
{
  size_t len = int_sptr_to_xstr (buf, val, lcase);

  buf[len] = '\0';

  return buf + len;
}

static inline char_t* int_uptr_to_xstri (char_t* buf, uintptr_t val, bint lcase)
{
  size_t len = int_uptr_to_xstr (buf, val, lcase);

  buf[len] = '\0';

  return buf + len;
}

// =============================================================================
// Macros
// -----------------------------------------------------------------------------
// Map the hexadecimal string serialization functions above
// to the fundamental integral types
// -----------------------------------------------------------------------------
// `char`
// -----------------------------------------------------------------------------

#if (CHAR_BIT == INTMAX_BIT)
  #define int_schar_to_xstr int_smax_to_xstr
  #define int_uchar_to_xstr int_umax_to_xstr

  #define int_schar_to_xstri int_smax_to_xstri
  #define int_uchar_to_xstri int_umax_to_xstri
#elif (CHAR_BIT == INT_FAST64_BIT)
  #define int_schar_to_xstr int_s64_to_xstr
  #define int_uchar_to_xstr int_u64_to_xstr

  #define int_schar_to_xstri int_s64_to_xstri
  #define int_uchar_to_xstri int_u64_to_xstri
#elif (CHAR_BIT == INT_FAST32_BIT)
  #define int_schar_to_xstr int_s32_to_xstr
  #define int_uchar_to_xstr int_u32_to_xstr

  #define int_schar_to_xstri int_s32_to_xstri
  #define int_uchar_to_xstri int_u32_to_xstri
#elif (CHAR_BIT == INT_FAST16_BIT)
  #define int_schar_to_xstr int_s16_to_xstr
  #define int_uchar_to_xstr int_u16_to_xstr

  #define int_schar_to_xstri int_s16_to_xstri
  #define int_uchar_to_xstri int_u16_to_xstri
#elif (CHAR_BIT == INT_FAST8_BIT)
  #define int_schar_to_xstr int_s8_to_xstr
  #define int_uchar_to_xstr int_u8_to_xstr

  #define int_schar_to_xstri int_s8_to_xstri
  #define int_uchar_to_xstri int_u8_to_xstri
#endif

// -----------------------------------------------------------------------------
// `short`
// -----------------------------------------------------------------------------

#if (SHRT_BIT == INTMAX_BIT)
  #define int_sshort_to_xstr int_smax_to_xstr
  #define int_ushort_to_xstr int_umax_to_xstr

  #define int_sshort_to_xstri int_smax_to_xstri
  #define int_ushort_to_xstri int_umax_to_xstri
#elif (SHRT_BIT == INT_FAST64_BIT)
  #define int_sshort_to_xstr int_s64_to_xstr
  #define int_ushort_to_xstr int_u64_to_xstr

  #define int_sshort_to_xstri int_s64_to_xstri
  #define int_ushort_to_xstri int_u64_to_xstri
#elif (SHRT_BIT == INT_FAST32_BIT)
  #define int_sshort_to_xstr int_s32_to_xstr
  #define int_ushort_to_xstr int_u32_to_xstr

  #define int_sshort_to_xstri int_s32_to_xstri
  #define int_ushort_to_xstri int_u32_to_xstri
#elif (SHRT_BIT == INT_FAST16_BIT)
  #define int_sshort_to_xstr int_s16_to_xstr
  #define int_ushort_to_xstr int_u16_to_xstr

  #define int_sshort_to_xstri int_s16_to_xstri
  #define int_ushort_to_xstri int_u16_to_xstri
#endif

// -----------------------------------------------------------------------------
// `int`
// -----------------------------------------------------------------------------

#if (INT_BIT == INTMAX_BIT)
  #define int_sint_to_xstr int_smax_to_xstr
  #define int_uint_to_xstr int_umax_to_xstr

  #define int_sint_to_xstri int_smax_to_xstri
  #define int_uint_to_xstri int_umax_to_xstri
#elif (INT_BIT == INT_FAST64_BIT)
  #define int_sint_to_xstr int_s64_to_xstr
  #define int_uint_to_xstr int_u64_to_xstr

  #define int_sint_to_xstri int_s64_to_xstri
  #define int_uint_to_xstri int_u64_to_xstri
#elif (INT_BIT == INT_FAST32_BIT)
  #define int_sint_to_xstr int_s32_to_xstr
  #define int_uint_to_xstr int_u32_to_xstr

  #define int_sint_to_xstri int_s32_to_xstri
  #define int_uint_to_xstri int_u32_to_xstri
#elif (INT_BIT == INT_FAST16_BIT)
  #define int_sint_to_xstr int_s16_to_xstr
  #define int_uint_to_xstr int_u16_to_xstr

  #define int_sint_to_xstri int_s16_to_xstri
  #define int_uint_to_xstri int_u16_to_xstri
#endif

// -----------------------------------------------------------------------------
// `long`
// -----------------------------------------------------------------------------

#if (LONG_BIT == INTMAX_BIT)
  #define int_slong_to_xstr int_smax_to_xstr
  #define int_ulong_to_xstr int_umax_to_xstr

  #define int_slong_to_xstri int_smax_to_xstri
  #define int_ulong_to_xstri int_umax_to_xstri
#elif (LONG_BIT == INT_FAST64_BIT)
  #define int_slong_to_xstr int_s64_to_xstr
  #define int_ulong_to_xstr int_u64_to_xstr

  #define int_slong_to_xstri int_s64_to_xstri
  #define int_ulong_to_xstri int_u64_to_xstri
#elif (LONG_BIT == INT_FAST32_BIT)
  #define int_slong_to_xstr int_s32_to_xstr
  #define int_ulong_to_xstr int_u32_to_xstr

  #define int_slong_to_xstri int_s32_to_xstri
  #define int_ulong_to_xstri int_u32_to_xstri
#endif

// -----------------------------------------------------------------------------
// `llong`
// -----------------------------------------------------------------------------

#if (LLONG_BIT == INTMAX_BIT)
  #define int_sllong_to_xstr int_smax_to_xstr
  #define int_ullong_to_xstr int_umax_to_xstr

  #define int_sllong_to_xstri int_smax_to_xstri
  #define int_ullong_to_xstri int_umax_to_xstri
#elif (LLONG_BIT == INT_FAST64_BIT)
  #define int_sllong_to_xstr int_s64_to_xstr
  #define int_ullong_to_xstr int_u64_to_xstr

  #define int_sllong_to_xstri int_s64_to_xstri
  #define int_ullong_to_xstri int_u64_to_xstri
#endif

// -----------------------------------------------------------------------------

#endif
