// =============================================================================
// <integer/convert/hexadecimal/format.c>
//
// Convert integral numbers to hexadecimal strings
// with `printf()`-like formatting options.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_F40DD6628BA74AD083E2F2C2AD7A5080
#define H_F40DD6628BA74AD083E2F2C2AD7A5080

// =============================================================================
// Functions
// -----------------------------------------------------------------------------
// 8-bit+
// -----------------------------------------------------------------------------

static inline size_t int_s8_xformat (char_t* buf, sf8 val, int_format_t fmt)
{
  #define t_int uf8

  #define t_int_abs int_s8_abs
  #define t_int_len int_u8_xlen

  #define T_SIGN

  #include "serialize/format/i8.c"
}

static inline size_t int_u8_xformat (char_t* buf, uf8 val, int_format_t fmt)
{
  #define t_int uf8

  #define t_int_len int_u8_xlen

  #include "serialize/format/i8.c"
}

// -----------------------------------------------------------------------------

static inline char_t* int_s8_xformati (char_t* buf, sf8 val, int_format_t fmt)
{
  size_t len = int_s8_xformat (buf, val, fmt);

  buf[len] = '\0';

  return buf + len;
}

static inline char_t* int_u8_xformati (char_t* buf, uf8 val, int_format_t fmt)
{
  size_t len = int_u8_xformat (buf, val, fmt);

  buf[len] = '\0';

  return buf + len;
}

// -----------------------------------------------------------------------------
// 16-bit+
// -----------------------------------------------------------------------------

static inline size_t int_s16_xformat (char_t* buf, sf16 val, int_format_t fmt)
{
  #define t_int uf16

  #define t_int_abs int_s16_abs
  #define t_int_len int_u16_xlen

  #define T_SIGN

  #include "serialize/format/i16.c"
}

static inline size_t int_u16_xformat (char_t* buf, uf16 val, int_format_t fmt)
{
  #define t_int uf16

  #define t_int_len int_u16_xlen

  #include "serialize/format/i16.c"
}

// -----------------------------------------------------------------------------

static inline char_t* int_s16_xformati (char_t* buf, sf16 val, int_format_t fmt)
{
  size_t len = int_s16_xformat (buf, val, fmt);

  buf[len] = '\0';

  return buf + len;
}

static inline char_t* int_u16_xformati (char_t* buf, uf16 val, int_format_t fmt)
{
  size_t len = int_u16_xformat (buf, val, fmt);

  buf[len] = '\0';

  return buf + len;
}

// -----------------------------------------------------------------------------
// 32-bit+
// -----------------------------------------------------------------------------

static inline size_t int_s32_xformat (char_t* buf, sf32 val, int_format_t fmt)
{
  #define t_int uf32

  #define t_int_abs int_s32_abs
  #define t_int_len int_u32_xlen

  #define T_SIGN

  #include "serialize/format/i32.c"
}

static inline size_t int_u32_xformat (char_t* buf, uf32 val, int_format_t fmt)
{
  #define t_int uf32

  #define t_int_len int_u32_xlen

  #include "serialize/format/i32.c"
}

// -----------------------------------------------------------------------------

static inline char_t* int_s32_xformati (char_t* buf, sf32 val, int_format_t fmt)
{
  size_t len = int_s32_xformat (buf, val, fmt);

  buf[len] = '\0';

  return buf + len;
}

static inline char_t* int_u32_xformati (char_t* buf, uf32 val, int_format_t fmt)
{
  size_t len = int_u32_xformat (buf, val, fmt);

  buf[len] = '\0';

  return buf + len;
}

// -----------------------------------------------------------------------------
// 64-bit+
// -----------------------------------------------------------------------------

static inline size_t int_s64_xformat (char_t* buf, sf64 val, int_format_t fmt)
{
  #define t_int uf64

  #define t_int_abs int_s64_abs
  #define t_int_len int_u64_xlen

  #define T_SIGN

  #include "serialize/format/i64.c"
}

static inline size_t int_u64_xformat (char_t* buf, uf64 val, int_format_t fmt)
{
  #define t_int uf64

  #define t_int_len int_u64_xlen

  #include "serialize/format/i64.c"
}

// -----------------------------------------------------------------------------

static inline char_t* int_s64_xformati (char_t* buf, sf64 val, int_format_t fmt)
{
  size_t len = int_s64_xformat (buf, val, fmt);

  buf[len] = '\0';

  return buf + len;
}

static inline char_t* int_u64_xformati (char_t* buf, uf64 val, int_format_t fmt)
{
  size_t len = int_u64_xformat (buf, val, fmt);

  buf[len] = '\0';

  return buf + len;
}

// -----------------------------------------------------------------------------
// 128-bit+
// -----------------------------------------------------------------------------

#if HAVE(INT_LEAST128)

static inline size_t int_s128_xformat (char_t* buf, sf128 val, int_format_t fmt)
{
  #define t_int uf128

  #define t_int_abs int_s128_abs
  #define t_int_len int_u128_xlen

  #define T_SIGN

  #include "serialize/format/i128.c"
}

static inline size_t int_u128_xformat (char_t* buf, uf128 val, int_format_t fmt)
{
  #define t_int uf128

  #define t_int_len int_u128_xlen

  #include "serialize/format/i128.c"
}

// -----------------------------------------------------------------------------

static inline char_t* int_s128_xformati (char_t* buf, sf128 val, int_format_t fmt)
{
  size_t len = int_s128_xformat (buf, val, fmt);

  buf[len] = '\0';

  return buf + len;
}

static inline char_t* int_u128_xformati (char_t* buf, uf128 val, int_format_t fmt)
{
  size_t len = int_u128_xformat (buf, val, fmt);

  buf[len] = '\0';

  return buf + len;
}

#endif // HAVE(INT_LEAST128)

// -----------------------------------------------------------------------------
// Maximum
// -----------------------------------------------------------------------------

static inline size_t int_smax_xformat (char_t* buf, intmax_t val, int_format_t fmt)
{
  #define t_int uintmax_t

  #define t_int_abs int_max_abs
  #define t_int_len int_umax_xlen

  #define T_SIGN

#if (INTMAX_BIT >= 128)
  #include "serialize/format/i128.c"
#else
  #include "serialize/format/i64.c"
#endif
}

static inline size_t int_umax_xformat (char_t* buf, uintmax_t val, int_format_t fmt)
{
  #define t_int uintmax_t

  #define t_int_len int_umax_xlen

#if (INTMAX_BIT >= 128)
  #include "serialize/format/i128.c"
#else
  #include "serialize/format/i64.c"
#endif
}

// -----------------------------------------------------------------------------

static inline char_t* int_smax_xformati (char_t* buf, intmax_t val, int_format_t fmt)
{
  size_t len = int_smax_xformat (buf, val, fmt);

  buf[len] = '\0';

  return buf + len;
}

static inline char_t* int_umax_xformati (char_t* buf, uintmax_t val, int_format_t fmt)
{
  size_t len = int_umax_xformat (buf, val, fmt);

  buf[len] = '\0';

  return buf + len;
}

// -----------------------------------------------------------------------------
// Pointer
// -----------------------------------------------------------------------------

static inline size_t int_sptr_xformat (char_t* buf, intptr_t val, int_format_t fmt)
{
  #define t_int uintptr_t

  #define t_int_abs int_ptr_abs
  #define t_int_len int_uptr_xlen

  #define T_SIGN

#if (INTPTR_BIT >= 64)
  #include "serialize/format/i64.c"
#else
  #include "serialize/format/i32.c"
#endif
}

static inline size_t int_uptr_xformat (char_t* buf, uintptr_t val, int_format_t fmt)
{
  #define t_int uintptr_t

  #define t_int_len int_uptr_xlen

#if (INTPTR_BIT >= 64)
  #include "serialize/format/i64.c"
#else
  #include "serialize/format/i32.c"
#endif
}

// -----------------------------------------------------------------------------

static inline char_t* int_sptr_xformati (char_t* buf, intptr_t val, int_format_t fmt)
{
  size_t len = int_sptr_xformat (buf, val, fmt);

  buf[len] = '\0';

  return buf + len;
}

static inline char_t* int_uptr_xformati (char_t* buf, uintptr_t val, int_format_t fmt)
{
  size_t len = int_uptr_xformat (buf, val, fmt);

  buf[len] = '\0';

  return buf + len;
}

// =============================================================================
// Macros
// -----------------------------------------------------------------------------
// Map the hexadecimal string formatting functions above
// to the fundamental integral types
// -----------------------------------------------------------------------------
// `char`
// -----------------------------------------------------------------------------

#if (CHAR_BIT == INTMAX_BIT)
  #define int_schar_xformat int_smax_xformat
  #define int_uchar_xformat int_umax_xformat

  #define int_schar_xformati int_smax_xformati
  #define int_uchar_xformati int_umax_xformati
#elif (CHAR_BIT == INT_FAST64_BIT)
  #define int_schar_xformat int_s64_xformat
  #define int_uchar_xformat int_u64_xformat

  #define int_schar_xformati int_s64_xformati
  #define int_uchar_xformati int_u64_xformati
#elif (CHAR_BIT == INT_FAST32_BIT)
  #define int_schar_xformat int_s32_xformat
  #define int_uchar_xformat int_u32_xformat

  #define int_schar_xformati int_s32_xformati
  #define int_uchar_xformati int_u32_xformati
#elif (CHAR_BIT == INT_FAST16_BIT)
  #define int_schar_xformat int_s16_xformat
  #define int_uchar_xformat int_u16_xformat

  #define int_schar_xformati int_s16_xformati
  #define int_uchar_xformati int_u16_xformati
#elif (CHAR_BIT == INT_FAST8_BIT)
  #define int_schar_xformat int_s8_xformat
  #define int_uchar_xformat int_u8_xformat

  #define int_schar_xformati int_s8_xformati
  #define int_uchar_xformati int_u8_xformati
#endif

// -----------------------------------------------------------------------------
// `short`
// -----------------------------------------------------------------------------

#if (SHRT_BIT == INTMAX_BIT)
  #define int_sshort_xformat int_smax_xformat
  #define int_ushort_xformat int_umax_xformat

  #define int_sshort_xformati int_smax_xformati
  #define int_ushort_xformati int_umax_xformati
#elif (SHRT_BIT == INT_FAST64_BIT)
  #define int_sshort_xformat int_s64_xformat
  #define int_ushort_xformat int_u64_xformat

  #define int_sshort_xformati int_s64_xformati
  #define int_ushort_xformati int_u64_xformati
#elif (SHRT_BIT == INT_FAST32_BIT)
  #define int_sshort_xformat int_s32_xformat
  #define int_ushort_xformat int_u32_xformat

  #define int_sshort_xformati int_s32_xformati
  #define int_ushort_xformati int_u32_xformati
#elif (SHRT_BIT == INT_FAST16_BIT)
  #define int_sshort_xformat int_s16_xformat
  #define int_ushort_xformat int_u16_xformat

  #define int_sshort_xformati int_s16_xformati
  #define int_ushort_xformati int_u16_xformati
#endif

// -----------------------------------------------------------------------------
// `int`
// -----------------------------------------------------------------------------

#if (INT_BIT == INTMAX_BIT)
  #define int_sint_xformat int_smax_xformat
  #define int_uint_xformat int_umax_xformat

  #define int_sint_xformati int_smax_xformati
  #define int_uint_xformati int_umax_xformati
#elif (INT_BIT == INT_FAST64_BIT)
  #define int_sint_xformat int_s64_xformat
  #define int_uint_xformat int_u64_xformat

  #define int_sint_xformati int_s64_xformati
  #define int_uint_xformati int_u64_xformati
#elif (INT_BIT == INT_FAST32_BIT)
  #define int_sint_xformat int_s32_xformat
  #define int_uint_xformat int_u32_xformat

  #define int_sint_xformati int_s32_xformati
  #define int_uint_xformati int_u32_xformati
#elif (INT_BIT == INT_FAST16_BIT)
  #define int_sint_xformat int_s16_xformat
  #define int_uint_xformat int_u16_xformat

  #define int_sint_xformati int_s16_xformati
  #define int_uint_xformati int_u16_xformati
#endif

// -----------------------------------------------------------------------------
// `long`
// -----------------------------------------------------------------------------

#if (LONG_BIT == INTMAX_BIT)
  #define int_slong_xformat int_smax_xformat
  #define int_ulong_xformat int_umax_xformat

  #define int_slong_xformati int_smax_xformati
  #define int_ulong_xformati int_umax_xformati
#elif (LONG_BIT == INT_FAST64_BIT)
  #define int_slong_xformat int_s64_xformat
  #define int_ulong_xformat int_u64_xformat

  #define int_slong_xformati int_s64_xformati
  #define int_ulong_xformati int_u64_xformati
#elif (LONG_BIT == INT_FAST32_BIT)
  #define int_slong_xformat int_s32_xformat
  #define int_ulong_xformat int_u32_xformat

  #define int_slong_xformati int_s32_xformati
  #define int_ulong_xformati int_u32_xformati
#endif

// -----------------------------------------------------------------------------
// `llong`
// -----------------------------------------------------------------------------

#if (LLONG_BIT == INTMAX_BIT)
  #define int_sllong_xformat int_smax_xformat
  #define int_ullong_xformat int_umax_xformat

  #define int_sllong_xformati int_smax_xformati
  #define int_ullong_xformati int_umax_xformati
#elif (LLONG_BIT == INT_FAST64_BIT)
  #define int_sllong_xformat int_s64_xformat
  #define int_ullong_xformat int_u64_xformat

  #define int_sllong_xformati int_s64_xformati
  #define int_ullong_xformati int_u64_xformati
#endif

// -----------------------------------------------------------------------------

#endif
