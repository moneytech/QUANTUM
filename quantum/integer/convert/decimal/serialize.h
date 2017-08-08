// =============================================================================
// <integer/convert/decimal/serialize.c>
//
// Convert integral numbers to decimal strings fast
// with no formatting (except for negative sign).
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_E032A0AC9A644631AF888A1B2A6D5BA7
#define H_E032A0AC9A644631AF888A1B2A6D5BA7

// =============================================================================
// Constants
// -----------------------------------------------------------------------------

static const char_t int_dig_tbl[200] =
{
  '0', '0', '0', '1', '0', '2', '0', '3', '0', '4', '0', '5', '0', '6', '0', '7', '0', '8', '0', '9',
  '1', '0', '1', '1', '1', '2', '1', '3', '1', '4', '1', '5', '1', '6', '1', '7', '1', '8', '1', '9',
  '2', '0', '2', '1', '2', '2', '2', '3', '2', '4', '2', '5', '2', '6', '2', '7', '2', '8', '2', '9',
  '3', '0', '3', '1', '3', '2', '3', '3', '3', '4', '3', '5', '3', '6', '3', '7', '3', '8', '3', '9',
  '4', '0', '4', '1', '4', '2', '4', '3', '4', '4', '4', '5', '4', '6', '4', '7', '4', '8', '4', '9',
  '5', '0', '5', '1', '5', '2', '5', '3', '5', '4', '5', '5', '5', '6', '5', '7', '5', '8', '5', '9',
  '6', '0', '6', '1', '6', '2', '6', '3', '6', '4', '6', '5', '6', '6', '6', '7', '6', '8', '6', '9',
  '7', '0', '7', '1', '7', '2', '7', '3', '7', '4', '7', '5', '7', '6', '7', '7', '7', '8', '7', '9',
  '8', '0', '8', '1', '8', '2', '8', '3', '8', '4', '8', '5', '8', '6', '8', '7', '8', '8', '8', '9',
  '9', '0', '9', '1', '9', '2', '9', '3', '9', '4', '9', '5', '9', '6', '9', '7', '9', '8', '9', '9'
};

// -----------------------------------------------------------------------------

#if CPU(SSE2)
static const u8 int_sse_asciiz[16] aligned(16) = {REPEAT16 ('0')};

static const u16 int_sse_mul10[8] aligned(16) = {REPEAT8 (10u)};
static const u16 int_sse_div10[8] aligned(16) = {REPEAT8 (0x199Au)};

static const u16 int_sse_mul100[8] aligned(16) = {REPEAT8 (100u)};
static const u16 int_sse_div100[8] aligned(16) = {REPEAT8 (0x147Bu)};

static const u32 int_sse_mul10000[4] aligned(16) = {REPEAT4 (10000u)};
static const u32 int_sse_div10000[4] aligned(16) = {REPEAT4 (0xD1B71759u)};

static const u16 int_sse_div32[8] aligned(16) =
{
  8389u, 5243u, 13108u, 32768u, 8389u, 5243u, 13108u, 32768u
};

static const u16 int_sse_shr32[8] aligned(16) =
{
  1u << (16 - (23 + 2 - 16)),
  1u << (16 - (19 + 2 - 16)),
  1u << (16 - 1 - 2),
  1u << 15,
  1u << (16 - (23 + 2 - 16)),
  1u << (16 - (19 + 2 - 16)),
  1u << (16 - 1 - 2),
  1u << 15
};
#endif // CPU(SSE2)

// =============================================================================
// Utility functions
// -----------------------------------------------------------------------------
// Decimal integer length computation
// -----------------------------------------------------------------------------
// Generic decimal integer length computation microtemplate
#define int_len(val, len) do\
{                           \
  len = 0;                  \
                            \
  while (true)              \
  {                         \
    if ((val) < 1000u)      \
    {                       \
      len += 2u + ((val) > 99u) - ((val) < 10u);\
      break;     \
    }            \
                 \
    val /= 1000u;\
    len += 3u;\
  }       \
} while (0)

// -----------------------------------------------------------------------------
// Unsigned decimal integer length computation
// -----------------------------------------------------------------------------

static inline size_t int_u8_len (uf8 val)
{
#if HAVE(INT8)
  return 2u + (val > 99u) - (val < 10u);
#else
  size_t len;
  int_len (val, len);
  return len;
#endif
}

static inline size_t int_u16_len (uf16 val)
{
#if HAVE(INT16)
  if (val < 1000u)
  {
    return 2u + (val > 99u) - (val < 10u);
  }

  return 4u + (val > 9999u);
#else
  size_t len;
  int_len (val, len);
  return len;
#endif
}

static inline size_t int_u32_len (uf32 val)
{
#if HAVE(INT32)
  size_t len = (val == 0) ? 1u : (((bsr32 (val) + 1u) * 1233u) >> 12);
  return len - (val < i32_pow10_tbl[len]) + 1u;
#else
  size_t len;
  int_len (val, len);
  return len;
#endif
}

static inline size_t int_u64_len (uf64 val)
{
#if HAVE(INT64)
  size_t len = (val == 0) ? 1u : (((bsr64 (val) + 1u) * 1233u) >> 12);
  return len - (val < i64_pow10_tbl[len]) + 1u;
#else
  size_t len;
  int_len (val, len);
  return len;
#endif
}

#if HAVE(INT_LEAST128)
static inline size_t int_u128_len (uf128 val)
{
#if HAVE(INT128)
  size_t len = (val == 0) ? 1u : (((bsr128 (val) + 1u) * 1233u) >> 12);
  return len - (val < i128_pow10_tbl[len]) + 1u;
#else
  size_t len;
  int_len (val, len);
  return len;
#endif
}
#endif // HAVE(INT_LEAST128)

static inline size_t int_umax_len (uintmax_t val)
{
#if (INTMAX_BIT == 128)
  return int_u128_len (val);
#elif (INTMAX_BIT == 64)
  return int_u64_len (val);
#else
  size_t len;
  int_len (val, len);
  return len;
#endif
}

static inline size_t int_uptr_len (uintptr_t val)
{
#if (INTPTR_BIT == 64)
  return int_u64_len (val);
#elif (INTPTR_BIT == 32)
  return int_u32_len (val);
#else
  size_t len;
  int_len (val, len);
  return len;
#endif
}

// -----------------------------------------------------------------------------
// Signed decimal integer length computation
// -----------------------------------------------------------------------------

static inline size_t int_s8_len (sf8 val)
{
  return int_u8_len (int_s8_abs (val));
}

static inline size_t int_s16_len (sf16 val)
{
  return int_u16_len (int_s16_abs (val));
}

static inline size_t int_s32_len (sf32 val)
{
  return int_u32_len (int_s32_abs (val));
}

static inline size_t int_s64_len (sf64 val)
{
  return int_u64_len (int_s64_abs (val));
}

#if HAVE(INT_LEAST128)
static inline size_t int_s128_len (sf128 val)
{
  return int_u128_len (int_s128_abs (val));
}
#endif

static inline size_t int_smax_len (intmax_t val)
{
  return int_umax_len (int_max_abs (val));
}

static inline size_t int_sptr_len (intptr_t val)
{
  return int_uptr_len (int_ptr_abs (val));
}

// -----------------------------------------------------------------------------
// `char`
#if (CHAR_BIT == INT_FAST8_BIT)
  #define int_uchar_len int_u8_len
  #define int_schar_len int_s8_len
#elif (CHAR_BIT == INT_FAST16_BIT)
  #define int_uchar_len int_u16_len
  #define int_schar_len int_s16_len
#elif (CHAR_BIT == INT_FAST32_BIT)
  #define int_uchar_len int_u32_len
  #define int_schar_len int_s32_len
#elif (CHAR_BIT == INT_FAST64_BIT)
  #define int_uchar_len int_u64_len
  #define int_schar_len int_s64_len
#elif (CHAR_BIT == INTMAX_BIT)
  #define int_uchar_len int_umax_len
  #define int_schar_len int_smax_len
#endif

// -----------------------------------------------------------------------------
// `short`
#if (SHRT_BIT == INT_FAST16_BIT)
  #define int_ushort_len int_u16_len
  #define int_sshort_len int_s16_len
#elif (SHRT_BIT == INT_FAST32_BIT)
  #define int_ushort_len int_u32_len
  #define int_sshort_len int_s32_len
#elif (SHRT_BIT == INT_FAST64_BIT)
  #define int_ushort_len int_u64_len
  #define int_sshort_len int_s64_len
#elif (SHRT_BIT == INTMAX_BIT)
  #define int_ushort_len int_umax_len
  #define int_sshort_len int_smax_len
#endif

// -----------------------------------------------------------------------------
// `int`
#if (INT_BIT == INT_FAST16_BIT)
  #define int_uint_len int_u16_len
  #define int_sint_len int_s16_len
#elif (INT_BIT == INT_FAST32_BIT)
  #define int_uint_len int_u32_len
  #define int_sint_len int_s32_len
#elif (INT_BIT == INT_FAST64_BIT)
  #define int_uint_len int_u64_len
  #define int_sint_len int_s64_len
#elif (INT_BIT == INTMAX_BIT)
  #define int_uint_len int_umax_len
  #define int_sint_len int_smax_len
#endif

// -----------------------------------------------------------------------------
// `long`
#if (LONG_BIT == INT_FAST32_BIT)
  #define int_ulong_len int_u32_len
  #define int_slong_len int_s32_len
#elif (LONG_BIT == INT_FAST64_BIT)
  #define int_ulong_len int_u64_len
  #define int_slong_len int_s64_len
#elif (LONG_BIT == INTMAX_BIT)
  #define int_ulong_len int_umax_len
  #define int_slong_len int_smax_len
#endif

// -----------------------------------------------------------------------------
// `llong`
#if (LLONG_BIT == INT_FAST64_BIT)
  #define int_ullong_len int_u64_len
  #define int_sllong_len int_s64_len
#elif (LLONG_BIT == INTMAX_BIT)
  #define int_ullong_len int_umax_len
  #define int_sllong_len int_smax_len
#endif

// -----------------------------------------------------------------------------

#undef int_len

// -----------------------------------------------------------------------------
// Convert an integer to a decimal string
// -----------------------------------------------------------------------------
// Produce `x` decimal digit characters
// -----------------------------------------------------------------------------

static inline void int_to_dig2 (char_t* b, uf8 u)
{
#if CPU(UNALIGNED_ACCESS) && HAVE(INT16) && (CHAR_BIT == 8)
  *(u16*)b = *(u16*)(int_dig_tbl + (u * 2));
#else
  b[0] = int_dig_tbl [u * 2];
  b[1] = int_dig_tbl [(u * 2) + 1];
#endif
}

static inline void int_to_dig4 (char_t* b, uf16 u)
{
  uf8 q = u / 100u;
  uf8 r = u % 100u;

  int_to_dig2 (b, q);
  int_to_dig2 (b + 2, r);
}

// -----------------------------------------------------------------------------

#if CPU(SSE2)

  #if 1

static void int_to_dig8 (char_t* b, u32 u)
{
  const xi128 m10000 = _mm_loadu_si128 ((const xi128*)int_sse_mul10000);
  const xi128 d10000 = _mm_loadu_si128 ((const xi128*)int_sse_div10000);

  const xi128 m100 = _mm_loadu_si128 ((const xi128*)int_sse_mul100);
  const xi128 d100 = _mm_loadu_si128 ((const xi128*)int_sse_div100);

  const xi128 m10 = _mm_loadu_si128 ((const xi128*)int_sse_mul10);
  const xi128 d10 = _mm_loadu_si128 ((const xi128*)int_sse_div10);

  const xi128 z = _mm_loadu_si128 ((const xi128*)int_sse_asciiz);

  xi128 x = _mm_cvtsi32_si128 (u);

  xi128 q = _mm_srli_epi64 (_mm_mul_epu32 (x, d10000), 45);
  xi128 r = _mm_sub_epi32 (x, _mm_mul_epu32 (q, m10000));

  xi128 qr = _mm_unpacklo_epi16 (q, r);

  q = _mm_srli_epi16 (_mm_mulhi_epu16 (qr, d100), 3);
  r = _mm_sub_epi16 (qr, _mm_mullo_epi16 (q, m100));

  qr = _mm_unpacklo_epi16 (q, r);

  q = _mm_mulhi_epu16 (qr, d10);
  r = _mm_sub_epi16 (qr, _mm_mullo_epi16 (q, m10));

  qr = _mm_unpacklo_epi16 (q, r);

  x = _mm_add_epi8 (_mm_packus_epi16 (qr, _mm_setzero_si128()), z);

  _mm_storel_epi64 ((xi128*)b, x);
}

  #else

static void int_to_dig8 (char_t* b, u32 u)
{
  const xi128 m10000 = _mm_loadu_si128 ((const xi128*)int_sse_mul10000);
  const xi128 d10000 = _mm_loadu_si128 ((const xi128*)int_sse_div10000);

  const xi128 div32 = _mm_loadu_si128 ((const xi128*)int_sse_div32);
  const xi128 shr32 = _mm_loadu_si128 ((const xi128*)int_sse_shr32);

  const xi128 m10 = _mm_loadu_si128 ((const xi128*)int_sse_mul10);

  const xi128 z = _mm_loadu_si128 ((const xi128*)int_sse_asciiz);

  xi128 x = _mm_cvtsi32_si128 (u);

  xi128 q = _mm_srli_epi64 (_mm_mul_epu32 (x, d10000), 45);
  xi128 r = _mm_sub_epi32 (x, _mm_mul_epu32 (q, m10000));

  xi128 qr = _mm_unpacklo_epi16 (q, r);

  qr = _mm_unpacklo_epi16 (qr, qr);
  qr = _mm_unpacklo_epi32 (qr, qr);

  qr = _mm_slli_epi64 (qr, 2);

  qr = _mm_mulhi_epu16 (_mm_mulhi_epu16 (qr, div32), shr32);
  qr = _mm_sub_epi16 (qr, _mm_slli_epi64 (_mm_mullo_epi16 (qr, m10), 16));

  x = _mm_add_epi8 (_mm_packus_epi16 (qr, _mm_setzero_si128()), z);

  _mm_storel_epi64 ((xi128*)b, x);
}

  #endif

#else // CPU(SSE2) ][

static inline void int_to_dig8 (char_t* b, uf32 u)
{
  uf8 q = u / 1000000u;
  uf32 r = u % 1000000u;

  int_to_dig2 (b, q);

  q = r / 10000u;
  r = r % 10000u;

  int_to_dig2 (b + 2, q);

  q = r / 100u;
  r = r % 100u;

  int_to_dig2 (b + 4, q);
  int_to_dig2 (b + 6, r);
}

#endif // !CPU(SSE2)

// -----------------------------------------------------------------------------

#if HAVE(INT_LEAST128)

  #if CPU(SSE2)

static void int_to_dig16 (char_t* b, u64 u)
{
  const xi128 m10000 = _mm_loadu_si128 ((const xi128*)int_sse_mul10000);
  const xi128 d10000 = _mm_loadu_si128 ((const xi128*)int_sse_div10000);

  const xi128 m100 = _mm_loadu_si128 ((const xi128*)int_sse_mul100);
  const xi128 d100 = _mm_loadu_si128 ((const xi128*)int_sse_div100);

  const xi128 m10 = _mm_loadu_si128 ((const xi128*)int_sse_mul10);
  const xi128 d10 = _mm_loadu_si128 ((const xi128*)int_sse_div10);

  const xi128 z = _mm_loadu_si128 ((const xi128*)int_sse_asciiz);

  // Division by 100000000 would require multiplication by a 64-bit constant
  // which cannot be done with SSE in a straightforward, easy way.
  //
  // `pshufd`: store the quotient in a low 64-bit word as a 32-bit value
  // and the remainder in a high 64-bit word as a 32-bit value as well.
  xi128 x = _mm_shuffle_epi32 (_mm_cvtsi64_si128 (((u / 100000000u) << 32)
  | (u % 100000000u)), 0xCD);

  // Divide both 32-bit integers by 10000 through a multiplication and a shift.
  // Get a quotient and a remainder of this operation, which are four-digit values.
  xi128 q = _mm_srli_epi64 (_mm_mul_epu32 (x, d10000), 45);
  xi128 r = _mm_sub_epi32 (x, _mm_mul_epu32 (q, m10000));

  // Combine them in a single vector to continue the division process
  xi128 qr = _mm_or_si128 (q, _mm_shuffle_epi32 (r, 0xB3));

  // Continue dividing the resulting 16-bit integers by 100
  // to produce the two-digit values
  q = _mm_srli_epi16 (_mm_mulhi_epu16 (qr, d100), 3);
  r = _mm_sub_epi16 (qr, _mm_mullo_epi16 (q, m100));

  // Combine the two-digit values for the last division
  qr = _mm_or_si128 (q, _mm_slli_epi32 (r, 16));

  // Final division by 10 to obtain the single individual digit values
  q = _mm_mulhi_epu16 (qr, d10);
  r = _mm_sub_epi16 (qr, _mm_mullo_epi16 (q, m10));

  // Combine them to produce the 16-byte result vector
  qr = _mm_or_si128 (q, _mm_slli_epi16 (r, 8));

  // Add a vector of ASCII zeros to produce the final result vector
  // of 16 ASCII decimal digit characters
  x = _mm_add_epi8 (qr, z);

  // Store it in the provided buffer
  _mm_storeu_si128 ((xi128*)b, x);
}

  #else // CPU(SSE2) ][

static inline void int_to_dig16 (char_t* b, uf64 u)
{
  uf8 q = u / 100000000000000u;
  uf64 r = u % 100000000000000u;

  int_to_dig2 (b, q);

  q = r / 1000000000000u;
  r = r % 1000000000000u;

  int_to_dig2 (b + 2, q);

  q = r / 10000000000u;
  r = r % 10000000000u;

  int_to_dig2 (b + 4, q);

  q = r / 100000000u;
  r = r % 100000000u;

  int_to_dig2 (b + 6, q);

  q = r / 1000000u;
  r = r % 1000000u;

  int_to_dig2 (b + 8, q);

  q = r / 10000u;
  r = r % 10000u;

  int_to_dig2 (b + 10, q);

  q = r / 100u;
  r = r % 100u;

  int_to_dig2 (b + 12, q);
  int_to_dig2 (b + 14, r);
}

  #endif // !CPU(SSE2)

#endif // HAVE(INT_LEAST128)

// -----------------------------------------------------------------------------
// Recursive division utility macros
// -----------------------------------------------------------------------------

#define int_left_dig() do\
{                        \
  *b = chr_dig_from_int (u);\
  return b + 1;\
} while (0)

#define int_left_dig2() do\
{                         \
  *b = int_dig_tbl [u * 2u];\
  b += (u >= 10u);        \
  *b = int_dig_tbl [(u * 2u) + 1u];\
               \
  return b + 1;\
} while (0)

#define int_left_dig3() do\
{                         \
  if (u >= 100u)          \
  {                       \
    uint q = u / 100u;    \
    uint r = u % 100u;    \
                          \
    *b = chr_dig_from_int (q);\
    int_to_dig2 (b + 1u, r);\
                 \
    return b + 3;\
  }       \
} while (0)

#define int_left_dig4() do\
{                      \
  if (u >= 1000u)      \
  {                    \
    int_to_dig4 (b, u);\
    return b + 4;\
  }       \
} while (0)

// -----------------------------------------------------------------------------
// Recursive division tail functions
// -----------------------------------------------------------------------------

static inline char_t* int_tail_dig (char_t* b, uint u)
{
  int_left_dig();
}

static inline char_t* int_tail_dig2 (char_t* b, uint u)
{
  int_left_dig2();
}

static inline char_t* int_tail_dig3 (char_t* b, uint u)
{
  int_left_dig3();
  int_left_dig2();
}

static inline char_t* int_tail_dig4 (char_t* b, uint u)
{
  int_left_dig4();
  int_left_dig3();
  int_left_dig2();
}

// -----------------------------------------------------------------------------

#undef int_left_dig
#undef int_left_dig2
#undef int_left_dig3
#undef int_left_dig4

// -----------------------------------------------------------------------------
// Recursive division functions
// -----------------------------------------------------------------------------

static inline char_t* int_div_dig (char_t* b, uf8 u)
{
  if (u >= 10u)
  {
    uint q = u / 10u;
    uint r = u % 10u;

    b = int_div_dig (b, q);
    *b = chr_dig_from_int (r);

    return b + 1;
  }

  return int_tail_dig (b, u);
}

static inline char_t* int_div_dig2 (char_t* b, uf16 u)
{
  if (u >= 100u)
  {
    uint q = u / 100u;
    uint r = u % 100u;

    b = int_div_dig2 (b, q);
    int_to_dig2 (b, r);

    return b + 2;
  }

  return int_tail_dig2 (b, u);
}

static inline char_t* int_div_dig4 (char_t* b, uf32 u)
{
  if (u >= 10000u)
  {
    uf32 q = u / 10000u;
    uf32 r = u % 10000u;

    b = int_div_dig4 (b, q);
    int_to_dig4 (b, r);

    return b + 4;
  }

  return int_tail_dig4 (b, u);
}

static inline char_t* int_div_dig8 (char_t* b, uf64 u)
{
  if (u >= 100000000u)
  {
    uf64 q = u / 100000000u;
    uf64 r = u % 100000000u;

    b = int_div_dig8 (b, q);
    int_to_dig8 (b, r);

    return b + 8;
  }

  return int_div_dig4 (b, u);
}

#if HAVE(INT_LEAST128)
static inline char_t* int_div_dig16 (char_t* b, uf128 u)
{
  if (u >= 10000000000000000u)
  {
    uf128 q = u / 10000000000000000u;
    uf128 r = u % 10000000000000000u;

    b = int_div_dig16 (b, q);
    int_to_dig16 (b, r);

    return b + 16;
  }

  return int_div_dig8 (b, u);
}
#endif

// =============================================================================
// Functions
// -----------------------------------------------------------------------------
// 8-bit+
// -----------------------------------------------------------------------------

static inline size_t int_s8_to_str (char_t* buf, sf8 val)
{
  #define t_int uf8

  #define T_SIGN

  #include "serialize/basic/i8.c"
}

static inline size_t int_u8_to_str (char_t* buf, uf8 val)
{
  #define t_int uf8

  #include "serialize/basic/i8.c"
}

// -----------------------------------------------------------------------------

static inline char_t* int_s8_to_stri (char_t* buf, sf8 val)
{
  size_t len = int_s8_to_str (buf, val);

  buf[len] = '\0';

  return buf + len;
}

static inline char_t* int_u8_to_stri (char_t* buf, uf8 val)
{
  size_t len = int_u8_to_str (buf, val);

  buf[len] = '\0';

  return buf + len;
}

// -----------------------------------------------------------------------------
// 16-bit+
// -----------------------------------------------------------------------------

static inline size_t int_s16_to_str (char_t* buf, sf16 val)
{
  #define t_int uf16

  #define T_SIGN

  #include "serialize/basic/i16.c"
}

static inline size_t int_u16_to_str (char_t* buf, uf16 val)
{
  #define t_int uf16

  #include "serialize/basic/i16.c"
}

// -----------------------------------------------------------------------------

static inline char_t* int_s16_to_stri (char_t* buf, sf16 val)
{
  size_t len = int_s16_to_str (buf, val);

  buf[len] = '\0';

  return buf + len;
}

static inline char_t* int_u16_to_stri (char_t* buf, uf16 val)
{
  size_t len = int_u16_to_str (buf, val);

  buf[len] = '\0';

  return buf + len;
}

// -----------------------------------------------------------------------------
// 32-bit+
// -----------------------------------------------------------------------------

static inline size_t int_s32_to_str (char_t* buf, sf32 val)
{
  #define t_int uf32

  #define T_SIGN

  #include "serialize/basic/i32.c"
}

static inline size_t int_u32_to_str (char_t* buf, uf32 val)
{
  #define t_int uf32

  #include "serialize/basic/i32.c"
}

// -----------------------------------------------------------------------------

static inline char_t* int_s32_to_stri (char_t* buf, sf32 val)
{
  size_t len = int_s32_to_str (buf, val);

  buf[len] = '\0';

  return buf + len;
}

static inline char_t* int_u32_to_stri (char_t* buf, uf32 val)
{
  size_t len = int_u32_to_str (buf, val);

  buf[len] = '\0';

  return buf + len;
}

// -----------------------------------------------------------------------------
// 64-bit+
// -----------------------------------------------------------------------------

static inline size_t int_s64_to_str (char_t* buf, sf64 val)
{
  #define t_int uf64

  #define T_SIGN

  #include "serialize/basic/i64.c"
}

static inline size_t int_u64_to_str (char_t* buf, uf64 val)
{
  #define t_int uf64

  #include "serialize/basic/i64.c"
}

// -----------------------------------------------------------------------------

static inline char_t* int_s64_to_stri (char_t* buf, sf64 val)
{
  size_t len = int_s64_to_str (buf, val);

  buf[len] = '\0';

  return buf + len;
}

static inline char_t* int_u64_to_stri (char_t* buf, uf64 val)
{
  size_t len = int_u64_to_str (buf, val);

  buf[len] = '\0';

  return buf + len;
}

// -----------------------------------------------------------------------------
// 128-bit+
// -----------------------------------------------------------------------------

#if HAVE(INT_LEAST128)

static inline size_t int_s128_to_str (char_t* buf, sf128 val)
{
  #define t_int uf128

  #define T_SIGN

  #include "serialize/basic/i128.c"
}

static inline size_t int_u128_to_str (char_t* buf, uf128 val)
{
  #define t_int uf128

  #include "serialize/basic/i128.c"
}

// -----------------------------------------------------------------------------

static inline char_t* int_s128_to_stri (char_t* buf, sf128 val)
{
  size_t len = int_s128_to_str (buf, val);

  buf[len] = '\0';

  return buf + len;
}

static inline char_t* int_u128_to_stri (char_t* buf, uf128 val)
{
  size_t len = int_u128_to_str (buf, val);

  buf[len] = '\0';

  return buf + len;
}

#endif // HAVE(INT_LEAST128)

// -----------------------------------------------------------------------------
// Maximum
// -----------------------------------------------------------------------------

static inline size_t int_smax_to_str (char_t* buf, intmax_t val)
{
  #define t_int uintmax_t

  #define T_SIGN

#if (INTMAX_BIT >= 128)
  #include "serialize/basic/i128.c"
#else
  #include "serialize/basic/i64.c"
#endif
}

static inline size_t int_umax_to_str (char_t* buf, uintmax_t val)
{
  #define t_int uintmax_t

#if (INTMAX_BIT >= 128)
  #include "serialize/basic/i128.c"
#else
  #include "serialize/basic/i64.c"
#endif
}

// -----------------------------------------------------------------------------

static inline char_t* int_smax_to_stri (char_t* buf, intmax_t val)
{
  size_t len = int_smax_to_str (buf, val);

  buf[len] = '\0';

  return buf + len;
}

static inline char_t* int_umax_to_stri (char_t* buf, uintmax_t val)
{
  size_t len = int_umax_to_str (buf, val);

  buf[len] = '\0';

  return buf + len;
}

// -----------------------------------------------------------------------------
// Pointer
// -----------------------------------------------------------------------------

static inline size_t int_sptr_to_str (char_t* buf, intptr_t val)
{
  #define t_int uintptr_t

  #define T_SIGN

#if (INTPTR_BIT >= 64)
  #include "serialize/basic/i64.c"
#else
  #include "serialize/basic/i32.c"
#endif
}

static inline size_t int_uptr_to_str (char_t* buf, uintptr_t val)
{
  #define t_int uintptr_t

#if (INTPTR_BIT >= 64)
  #include "serialize/basic/i64.c"
#else
  #include "serialize/basic/i32.c"
#endif
}

// -----------------------------------------------------------------------------

static inline char_t* int_sptr_to_stri (char_t* buf, intptr_t val)
{
  size_t len = int_sptr_to_str (buf, val);

  buf[len] = '\0';

  return buf + len;
}

static inline char_t* int_uptr_to_stri (char_t* buf, uintptr_t val)
{
  size_t len = int_uptr_to_str (buf, val);

  buf[len] = '\0';

  return buf + len;
}

// =============================================================================
// Macros
// -----------------------------------------------------------------------------
// Map the decimal string serialization functions above
// to the fundamental integral types
// -----------------------------------------------------------------------------
// `char`
// -----------------------------------------------------------------------------

#if (CHAR_BIT == INTMAX_BIT)
  #define int_schar_to_str int_smax_to_str
  #define int_uchar_to_str int_umax_to_str

  #define int_schar_to_stri int_smax_to_stri
  #define int_uchar_to_stri int_umax_to_stri
#elif (CHAR_BIT == INT_FAST64_BIT)
  #define int_schar_to_str int_s64_to_str
  #define int_uchar_to_str int_u64_to_str

  #define int_schar_to_stri int_s64_to_stri
  #define int_uchar_to_stri int_u64_to_stri
#elif (CHAR_BIT == INT_FAST32_BIT)
  #define int_schar_to_str int_s32_to_str
  #define int_uchar_to_str int_u32_to_str

  #define int_schar_to_stri int_s32_to_stri
  #define int_uchar_to_stri int_u32_to_stri
#elif (CHAR_BIT == INT_FAST16_BIT)
  #define int_schar_to_str int_s16_to_str
  #define int_uchar_to_str int_u16_to_str

  #define int_schar_to_stri int_s16_to_stri
  #define int_uchar_to_stri int_u16_to_stri
#elif (CHAR_BIT == INT_FAST8_BIT)
  #define int_schar_to_str int_s8_to_str
  #define int_uchar_to_str int_u8_to_str

  #define int_schar_to_stri int_s8_to_stri
  #define int_uchar_to_stri int_u8_to_stri
#endif

// -----------------------------------------------------------------------------
// `short`
// -----------------------------------------------------------------------------

#if (SHRT_BIT == INTMAX_BIT)
  #define int_sshort_to_str int_smax_to_str
  #define int_ushort_to_str int_umax_to_str

  #define int_sshort_to_stri int_smax_to_stri
  #define int_ushort_to_stri int_umax_to_stri
#elif (SHRT_BIT == INT_FAST64_BIT)
  #define int_sshort_to_str int_s64_to_str
  #define int_ushort_to_str int_u64_to_str

  #define int_sshort_to_stri int_s64_to_stri
  #define int_ushort_to_stri int_u64_to_stri
#elif (SHRT_BIT == INT_FAST32_BIT)
  #define int_sshort_to_str int_s32_to_str
  #define int_ushort_to_str int_u32_to_str

  #define int_sshort_to_stri int_s32_to_stri
  #define int_ushort_to_stri int_u32_to_stri
#elif (SHRT_BIT == INT_FAST16_BIT)
  #define int_sshort_to_str int_s16_to_str
  #define int_ushort_to_str int_u16_to_str

  #define int_sshort_to_stri int_s16_to_stri
  #define int_ushort_to_stri int_u16_to_stri
#endif

// -----------------------------------------------------------------------------
// `int`
// -----------------------------------------------------------------------------

#if (INT_BIT == INTMAX_BIT)
  #define int_sint_to_str int_smax_to_str
  #define int_uint_to_str int_umax_to_str

  #define int_sint_to_stri int_smax_to_stri
  #define int_uint_to_stri int_umax_to_stri
#elif (INT_BIT == INT_FAST64_BIT)
  #define int_sint_to_str int_s64_to_str
  #define int_uint_to_str int_u64_to_str

  #define int_sint_to_stri int_s64_to_stri
  #define int_uint_to_stri int_u64_to_stri
#elif (INT_BIT == INT_FAST32_BIT)
  #define int_sint_to_str int_s32_to_str
  #define int_uint_to_str int_u32_to_str

  #define int_sint_to_stri int_s32_to_stri
  #define int_uint_to_stri int_u32_to_stri
#elif (INT_BIT == INT_FAST16_BIT)
  #define int_sint_to_str int_s16_to_str
  #define int_uint_to_str int_u16_to_str

  #define int_sint_to_stri int_s16_to_stri
  #define int_uint_to_stri int_u16_to_stri
#endif

// -----------------------------------------------------------------------------
// `long`
// -----------------------------------------------------------------------------

#if (LONG_BIT == INTMAX_BIT)
  #define int_slong_to_str int_smax_to_str
  #define int_ulong_to_str int_umax_to_str

  #define int_slong_to_stri int_smax_to_stri
  #define int_ulong_to_stri int_umax_to_stri
#elif (LONG_BIT == INT_FAST64_BIT)
  #define int_slong_to_str int_s64_to_str
  #define int_ulong_to_str int_u64_to_str

  #define int_slong_to_stri int_s64_to_stri
  #define int_ulong_to_stri int_u64_to_stri
#elif (LONG_BIT == INT_FAST32_BIT)
  #define int_slong_to_str int_s32_to_str
  #define int_ulong_to_str int_u32_to_str

  #define int_slong_to_stri int_s32_to_stri
  #define int_ulong_to_stri int_u32_to_stri
#endif

// -----------------------------------------------------------------------------
// `llong`
// -----------------------------------------------------------------------------

#if (LLONG_BIT == INTMAX_BIT)
  #define int_sllong_to_str int_smax_to_str
  #define int_ullong_to_str int_umax_to_str

  #define int_sllong_to_stri int_smax_to_stri
  #define int_ullong_to_stri int_umax_to_stri
#elif (LLONG_BIT == INT_FAST64_BIT)
  #define int_sllong_to_str int_s64_to_str
  #define int_ullong_to_str int_u64_to_str

  #define int_sllong_to_stri int_s64_to_stri
  #define int_ullong_to_stri int_u64_to_stri
#endif

// -----------------------------------------------------------------------------

#endif
