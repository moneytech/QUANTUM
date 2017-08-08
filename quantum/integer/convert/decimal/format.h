// =============================================================================
// <integer/convert/decimal/format.c>
//
// Convert integral numbers to decimal strings
// with `printf()`-like formatting options.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_C5C2D8514DC943A1B3A8A65DE0C48BF1
#define H_C5C2D8514DC943A1B3A8A65DE0C48BF1

// =============================================================================
// Functions
// -----------------------------------------------------------------------------
// 8-bit+
// -----------------------------------------------------------------------------

static inline size_t int_s8_format (char_t* buf, sf8 val, int_format_t fmt)
{
  #define t_int uf8

  #define t_int_abs int_s8_abs
  #define t_int_len int_u8_len

  #define T_SIGN

  #include "serialize/format/i8.c"
}

static inline size_t int_u8_format (char_t* buf, uf8 val, int_format_t fmt)
{
  #define t_int uf8

  #define t_int_len int_u8_len

  #include "serialize/format/i8.c"
}

// -----------------------------------------------------------------------------

static inline char_t* int_s8_formati (char_t* buf, sf8 val, int_format_t fmt)
{
  size_t len = int_s8_format (buf, val, fmt);

  buf[len] = '\0';

  return buf + len;
}

static inline char_t* int_u8_formati (char_t* buf, uf8 val, int_format_t fmt)
{
  size_t len = int_u8_format (buf, val, fmt);

  buf[len] = '\0';

  return buf + len;
}

// -----------------------------------------------------------------------------
// 16-bit+
// -----------------------------------------------------------------------------

static inline size_t int_s16_format (char_t* buf, sf16 val, int_format_t fmt)
{
  #define t_int uf16

  #define t_int_abs int_s16_abs
  #define t_int_len int_u16_len

  #define T_SIGN

  #include "serialize/format/i16.c"
}

static inline size_t int_u16_format (char_t* buf, uf16 val, int_format_t fmt)
{
  #define t_int uf16

  #define t_int_len int_u16_len

  #include "serialize/format/i16.c"
}

// -----------------------------------------------------------------------------

static inline char_t* int_s16_formati (char_t* buf, sf16 val, int_format_t fmt)
{
  size_t len = int_s16_format (buf, val, fmt);

  buf[len] = '\0';

  return buf + len;
}

static inline char_t* int_u16_formati (char_t* buf, uf16 val, int_format_t fmt)
{
  size_t len = int_u16_format (buf, val, fmt);

  buf[len] = '\0';

  return buf + len;
}

// -----------------------------------------------------------------------------
// 32-bit+
// -----------------------------------------------------------------------------

static inline size_t int_s32_format (char_t* buf, sf32 val, int_format_t fmt)
{
  #define t_int uf32

  #define t_int_abs int_s32_abs
  #define t_int_len int_u32_len

  #define T_SIGN

  #include "serialize/format/i32.c"
}

static inline size_t int_u32_format (char_t* buf, uf32 val, int_format_t fmt)
{
  #define t_int uf32

  #define t_int_len int_u32_len

  #include "serialize/format/i32.c"
}

// -----------------------------------------------------------------------------

static inline char_t* int_s32_formati (char_t* buf, sf32 val, int_format_t fmt)
{
  size_t len = int_s32_format (buf, val, fmt);

  buf[len] = '\0';

  return buf + len;
}

static inline char_t* int_u32_formati (char_t* buf, uf32 val, int_format_t fmt)
{
  size_t len = int_u32_format (buf, val, fmt);

  buf[len] = '\0';

  return buf + len;
}

// -----------------------------------------------------------------------------
// 64-bit+
// -----------------------------------------------------------------------------

static inline size_t int_s64_format (char_t* buf, sf64 val, int_format_t fmt)
{
  #define t_int uf64

  #define t_int_abs int_s64_abs
  #define t_int_len int_u64_len

  #define T_SIGN

  #include "serialize/format/i64.c"
}

static inline size_t int_u64_format (char_t* buf, uf64 val, int_format_t fmt)
{
  #define t_int uf64

  #define t_int_len int_u64_len

  #include "serialize/format/i64.c"
}

// -----------------------------------------------------------------------------

static inline char_t* int_s64_formati (char_t* buf, sf64 val, int_format_t fmt)
{
  size_t len = int_s64_format (buf, val, fmt);

  buf[len] = '\0';

  return buf + len;
}

static inline char_t* int_u64_formati (char_t* buf, uf64 val, int_format_t fmt)
{
  size_t len = int_u64_format (buf, val, fmt);

  buf[len] = '\0';

  return buf + len;
}

// -----------------------------------------------------------------------------
// 128-bit+
// -----------------------------------------------------------------------------

#if HAVE(INT_LEAST128)

static inline size_t int_s128_format (char_t* buf, sf128 val, int_format_t fmt)
{
  #define t_int uf128

  #define t_int_abs int_s128_abs
  #define t_int_len int_u128_len

  #define T_SIGN

  #include "serialize/format/i128.c"
}

static inline size_t int_u128_format (char_t* buf, uf128 val, int_format_t fmt)
{
  #define t_int uf128

  #define t_int_len int_u128_len

  #include "serialize/format/i128.c"
}

// -----------------------------------------------------------------------------

static inline char_t* int_s128_formati (char_t* buf, sf128 val, int_format_t fmt)
{
  size_t len = int_s128_format (buf, val, fmt);

  buf[len] = '\0';

  return buf + len;
}

static inline char_t* int_u128_formati (char_t* buf, uf128 val, int_format_t fmt)
{
  size_t len = int_u128_format (buf, val, fmt);

  buf[len] = '\0';

  return buf + len;
}

#endif // HAVE(INT_LEAST128)

// -----------------------------------------------------------------------------
// Maximum
// -----------------------------------------------------------------------------

static inline size_t int_smax_format (char_t* buf, intmax_t val, int_format_t fmt)
{
  #define t_int uintmax_t

  #define t_int_abs int_max_abs
  #define t_int_len int_umax_len

  #define T_SIGN

#if (INTMAX_BIT >= 128)
  #include "serialize/format/i128.c"
#else
  #include "serialize/format/i64.c"
#endif
}

static inline size_t int_umax_format (char_t* buf, uintmax_t val, int_format_t fmt)
{
  #define t_int uintmax_t

  #define t_int_len int_umax_len

#if (INTMAX_BIT >= 128)
  #include "serialize/format/i128.c"
#else
  #include "serialize/format/i64.c"
#endif
}

// -----------------------------------------------------------------------------

static inline char_t* int_smax_formati (char_t* buf, intmax_t val, int_format_t fmt)
{
  size_t len = int_smax_format (buf, val, fmt);

  buf[len] = '\0';

  return buf + len;
}

static inline char_t* int_umax_formati (char_t* buf, uintmax_t val, int_format_t fmt)
{
  size_t len = int_umax_format (buf, val, fmt);

  buf[len] = '\0';

  return buf + len;
}

// -----------------------------------------------------------------------------
// Pointer
// -----------------------------------------------------------------------------

static inline size_t int_sptr_format (char_t* buf, intptr_t val, int_format_t fmt)
{
  #define t_int uintptr_t

  #define t_int_abs int_ptr_abs
  #define t_int_len int_uptr_len

  #define T_SIGN

#if (INTPTR_BIT >= 64)
  #include "serialize/format/i64.c"
#else
  #include "serialize/format/i32.c"
#endif
}

static inline size_t int_uptr_format (char_t* buf, uintptr_t val, int_format_t fmt)
{
  #define t_int uintptr_t

  #define t_int_len int_uptr_len

#if (INTPTR_BIT >= 64)
  #include "serialize/format/i64.c"
#else
  #include "serialize/format/i32.c"
#endif
}

// -----------------------------------------------------------------------------

static inline char_t* int_sptr_formati (char_t* buf, intptr_t val, int_format_t fmt)
{
  size_t len = int_sptr_format (buf, val, fmt);

  buf[len] = '\0';

  return buf + len;
}

static inline char_t* int_uptr_formati (char_t* buf, uintptr_t val, int_format_t fmt)
{
  size_t len = int_uptr_format (buf, val, fmt);

  buf[len] = '\0';

  return buf + len;
}

// =============================================================================
// Macros
// -----------------------------------------------------------------------------
// Map the decimal string formatting functions above
// to the fundamental integral types
// -----------------------------------------------------------------------------
// `char`
// -----------------------------------------------------------------------------

#if (CHAR_BIT == INTMAX_BIT)
  #define int_schar_format int_smax_format
  #define int_uchar_format int_umax_format

  #define int_schar_formati int_smax_formati
  #define int_uchar_formati int_umax_formati
#elif (CHAR_BIT == INT_FAST64_BIT)
  #define int_schar_format int_s64_format
  #define int_uchar_format int_u64_format

  #define int_schar_formati int_s64_formati
  #define int_uchar_formati int_u64_formati
#elif (CHAR_BIT == INT_FAST32_BIT)
  #define int_schar_format int_s32_format
  #define int_uchar_format int_u32_format

  #define int_schar_formati int_s32_formati
  #define int_uchar_formati int_u32_formati
#elif (CHAR_BIT == INT_FAST16_BIT)
  #define int_schar_format int_s16_format
  #define int_uchar_format int_u16_format

  #define int_schar_formati int_s16_formati
  #define int_uchar_formati int_u16_formati
#elif (CHAR_BIT == INT_FAST8_BIT)
  #define int_schar_format int_s8_format
  #define int_uchar_format int_u8_format

  #define int_schar_formati int_s8_formati
  #define int_uchar_formati int_u8_formati
#endif

// -----------------------------------------------------------------------------
// `short`
// -----------------------------------------------------------------------------

#if (SHRT_BIT == INTMAX_BIT)
  #define int_sshort_format int_smax_format
  #define int_ushort_format int_umax_format

  #define int_sshort_formati int_smax_formati
  #define int_ushort_formati int_umax_formati
#elif (SHRT_BIT == INT_FAST64_BIT)
  #define int_sshort_format int_s64_format
  #define int_ushort_format int_u64_format

  #define int_sshort_formati int_s64_formati
  #define int_ushort_formati int_u64_formati
#elif (SHRT_BIT == INT_FAST32_BIT)
  #define int_sshort_format int_s32_format
  #define int_ushort_format int_u32_format

  #define int_sshort_formati int_s32_formati
  #define int_ushort_formati int_u32_formati
#elif (SHRT_BIT == INT_FAST16_BIT)
  #define int_sshort_format int_s16_format
  #define int_ushort_format int_u16_format

  #define int_sshort_formati int_s16_formati
  #define int_ushort_formati int_u16_formati
#endif

// -----------------------------------------------------------------------------
// `int`
// -----------------------------------------------------------------------------

#if (INT_BIT == INTMAX_BIT)
  #define int_sint_format int_smax_format
  #define int_uint_format int_umax_format

  #define int_sint_formati int_smax_formati
  #define int_uint_formati int_umax_formati
#elif (INT_BIT == INT_FAST64_BIT)
  #define int_sint_format int_s64_format
  #define int_uint_format int_u64_format

  #define int_sint_formati int_s64_formati
  #define int_uint_formati int_u64_formati
#elif (INT_BIT == INT_FAST32_BIT)
  #define int_sint_format int_s32_format
  #define int_uint_format int_u32_format

  #define int_sint_formati int_s32_formati
  #define int_uint_formati int_u32_formati
#elif (INT_BIT == INT_FAST16_BIT)
  #define int_sint_format int_s16_format
  #define int_uint_format int_u16_format

  #define int_sint_formati int_s16_formati
  #define int_uint_formati int_u16_formati
#endif

// -----------------------------------------------------------------------------
// `long`
// -----------------------------------------------------------------------------

#if (LONG_BIT == INTMAX_BIT)
  #define int_slong_format int_smax_format
  #define int_ulong_format int_umax_format

  #define int_slong_formati int_smax_formati
  #define int_ulong_formati int_umax_formati
#elif (LONG_BIT == INT_FAST64_BIT)
  #define int_slong_format int_s64_format
  #define int_ulong_format int_u64_format

  #define int_slong_formati int_s64_formati
  #define int_ulong_formati int_u64_formati
#elif (LONG_BIT == INT_FAST32_BIT)
  #define int_slong_format int_s32_format
  #define int_ulong_format int_u32_format

  #define int_slong_formati int_s32_formati
  #define int_ulong_formati int_u32_formati
#endif

// -----------------------------------------------------------------------------
// `llong`
// -----------------------------------------------------------------------------

#if (LLONG_BIT == INTMAX_BIT)
  #define int_sllong_format int_smax_format
  #define int_ullong_format int_umax_format

  #define int_sllong_formati int_smax_formati
  #define int_ullong_formati int_umax_formati
#elif (LLONG_BIT == INT_FAST64_BIT)
  #define int_sllong_format int_s64_format
  #define int_ullong_format int_u64_format

  #define int_sllong_formati int_s64_formati
  #define int_ullong_formati int_u64_formati
#endif

// -----------------------------------------------------------------------------

#endif
