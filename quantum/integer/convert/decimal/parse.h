// =============================================================================
// <integer/convert/decimal/parse.h>
//
// Parse integral numbers from decimal strings of explicit length and from
// null-terminated strings validating the input and preventing overflow.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_B9E9391468244F7E8CDCD6E1E7CD3840
#define H_B9E9391468244F7E8CDCD6E1E7CD3840

// -----------------------------------------------------------------------------

#include "support/intro.h"

// =============================================================================
// Functions
// -----------------------------------------------------------------------------
// 8-bit+
// -----------------------------------------------------------------------------

static inline sf8 int_s8_parse (const char_t* str, size_t len, int_parse_t* out)
{
  #define t_int uf8

  #define T_SIGN
  #define T_VALID

  #define T_MAXVAL (uf8)INT_FAST8_MAX
  #define T_MAXDIG INT_FAST8_DIG

  #include "deserialize/explicit/i8.c"
}

static inline uf8 int_u8_parse (const char_t* str, size_t len, int_parse_t* out)
{
  #define t_int uf8

  #define T_VALID

  #define T_MAXVAL UINT_FAST8_MAX
  #define T_MAXDIG UINT_FAST8_DIG

  #include "deserialize/explicit/i8.c"
}

// -----------------------------------------------------------------------------

static inline sf8 int_s8_parsei (const char_t* str, int_parse_t* out)
{
  #define t_int uf8

  #define T_SIGN
  #define T_VALID

  #define T_MAXVAL (uf8)INT_FAST8_MAX
  #define T_MAXDIG INT_FAST8_DIG

  #include "deserialize/implicit/i8.c"
}

static inline uf8 int_u8_parsei (const char_t* str, int_parse_t* out)
{
  #define t_int uf8

  #define T_VALID

  #define T_MAXVAL UINT_FAST8_MAX
  #define T_MAXDIG UINT_FAST8_DIG

  #include "deserialize/implicit/i8.c"
}

// -----------------------------------------------------------------------------
// 16-bit+
// -----------------------------------------------------------------------------

static inline sf16 int_s16_parse (const char_t* str, size_t len, int_parse_t* out)
{
  #define t_int uf16

  #define T_SIGN
  #define T_VALID

  #define T_MAXVAL (uf16)INT_FAST16_MAX
  #define T_MAXDIG INT_FAST16_DIG

  #include "deserialize/explicit/i16.c"
}

static inline uf16 int_u16_parse (const char_t* str, size_t len, int_parse_t* out)
{
  #define t_int uf16

  #define T_VALID

  #define T_MAXVAL UINT_FAST16_MAX
  #define T_MAXDIG UINT_FAST16_DIG

  #include "deserialize/explicit/i16.c"
}

// -----------------------------------------------------------------------------

static inline sf16 int_s16_parsei (const char_t* str, int_parse_t* out)
{
  #define t_int uf16

  #define T_SIGN
  #define T_VALID

  #define T_MAXVAL (uf16)INT_FAST16_MAX
  #define T_MAXDIG INT_FAST16_DIG

  #include "deserialize/implicit/i16.c"
}

static inline uf16 int_u16_parsei (const char_t* str, int_parse_t* out)
{
  #define t_int uf16

  #define T_VALID

  #define T_MAXVAL UINT_FAST16_MAX
  #define T_MAXDIG UINT_FAST16_DIG

  #include "deserialize/implicit/i16.c"
}

// -----------------------------------------------------------------------------
// 32-bit+
// -----------------------------------------------------------------------------

static inline sf32 int_s32_parse (const char_t* str, size_t len, int_parse_t* out)
{
  #define t_int uf32

  #define T_SIGN
  #define T_VALID

  #define T_MAXVAL (uf32)INT_FAST32_MAX
  #define T_MAXDIG INT_FAST32_DIG

  #include "deserialize/explicit/i32.c"
}

static inline uf32 int_u32_parse (const char_t* str, size_t len, int_parse_t* out)
{
  #define t_int uf32

  #define T_VALID

  #define T_MAXVAL UINT_FAST32_MAX
  #define T_MAXDIG UINT_FAST32_DIG

  #include "deserialize/explicit/i32.c"
}

// -----------------------------------------------------------------------------

static inline sf32 int_s32_parsei (const char_t* str, int_parse_t* out)
{
  #define t_int uf32

  #define T_SIGN
  #define T_VALID

  #define T_MAXVAL (uf32)INT_FAST32_MAX
  #define T_MAXDIG INT_FAST32_DIG

  #include "deserialize/implicit/i32.c"
}

static inline uf32 int_u32_parsei (const char_t* str, int_parse_t* out)
{
  #define t_int uf32

  #define T_VALID

  #define T_MAXVAL UINT_FAST32_MAX
  #define T_MAXDIG UINT_FAST32_DIG

  #include "deserialize/implicit/i32.c"
}

// -----------------------------------------------------------------------------
// 64-bit+
// -----------------------------------------------------------------------------

static inline sf64 int_s64_parse (const char_t* str, size_t len, int_parse_t* out)
{
  #define t_int uf64

  #define T_SIGN
  #define T_VALID

  #define T_MAXVAL (uf64)INT_FAST64_MAX
  #define T_MAXDIG INT_FAST64_DIG

  #include "deserialize/explicit/i64.c"
}

static inline uf64 int_u64_parse (const char_t* str, size_t len, int_parse_t* out)
{
  #define t_int uf64

  #define T_VALID

  #define T_MAXVAL UINT_FAST64_MAX
  #define T_MAXDIG UINT_FAST64_DIG

  #include "deserialize/explicit/i64.c"
}

// -----------------------------------------------------------------------------

static inline sf64 int_s64_parsei (const char_t* str, int_parse_t* out)
{
  #define t_int uf64

  #define T_SIGN
  #define T_VALID

  #define T_MAXVAL (uf64)INT_FAST64_MAX
  #define T_MAXDIG INT_FAST64_DIG

  #include "deserialize/implicit/i64.c"
}

static inline uf64 int_u64_parsei (const char_t* str, int_parse_t* out)
{
  #define t_int uf64

  #define T_VALID

  #define T_MAXVAL UINT_FAST64_MAX
  #define T_MAXDIG UINT_FAST64_DIG

  #include "deserialize/implicit/i64.c"
}

// -----------------------------------------------------------------------------
// 128-bit+
// -----------------------------------------------------------------------------

#if HAVE(INT_LEAST128)

static inline sf128 int_s128_parse (const char_t* str, size_t len, int_parse_t* out)
{
  #define t_int uf128

  #define T_SIGN
  #define T_VALID

  #define T_MAXVAL (uf128)INT_FAST128_MAX
  #define T_MAXDIG INT_FAST128_DIG

  #include "deserialize/explicit/i128.c"
}

static inline uf128 int_u128_parse (const char_t* str, size_t len, int_parse_t* out)
{
  #define t_int uf128

  #define T_VALID

  #define T_MAXVAL UINT_FAST128_MAX
  #define T_MAXDIG UINT_FAST128_DIG

  #include "deserialize/explicit/i128.c"
}

// -----------------------------------------------------------------------------

static inline sf128 int_s128_parsei (const char_t* str, int_parse_t* out)
{
  #define t_int uf128

  #define T_SIGN
  #define T_VALID

  #define T_MAXVAL (uf128)INT_FAST128_MAX
  #define T_MAXDIG INT_FAST128_DIG

  #include "deserialize/implicit/i128.c"
}

static inline uf128 int_u128_parsei (const char_t* str, int_parse_t* out)
{
  #define t_int uf128

  #define T_VALID

  #define T_MAXVAL UINT_FAST128_MAX
  #define T_MAXDIG UINT_FAST128_DIG

  #include "deserialize/implicit/i128.c"
}

#endif // HAVE(INT_LEAST128)

// -----------------------------------------------------------------------------
// Maximum
// -----------------------------------------------------------------------------

static inline intmax_t int_smax_parse (const char_t* str, size_t len, int_parse_t* out)
{
  #define t_int uintmax_t

  #define T_SIGN
  #define T_VALID

  #define T_MAXVAL (uintmax_t)INTMAX_MAX
  #define T_MAXDIG INTMAX_DIG

#if (INTMAX_BIT >= 128)
  #include "deserialize/explicit/i128.c"
#else
  #include "deserialize/explicit/i64.c"
#endif
}

static inline uintmax_t int_umax_parse (const char_t* str, size_t len, int_parse_t* out)
{
  #define t_int uintmax_t

  #define T_VALID

  #define T_MAXVAL UINTMAX_MAX
  #define T_MAXDIG UINTMAX_DIG

#if (INTMAX_BIT >= 128)
  #include "deserialize/explicit/i128.c"
#else
  #include "deserialize/explicit/i64.c"
#endif
}

// -----------------------------------------------------------------------------

static inline intmax_t int_smax_parsei (const char_t* str, int_parse_t* out)
{
  #define t_int uintmax_t

  #define T_SIGN
  #define T_VALID

  #define T_MAXVAL (uintmax_t)INTMAX_MAX
  #define T_MAXDIG INTMAX_DIG

#if (INTMAX_BIT >= 128)
  #include "deserialize/implicit/i128.c"
#else
  #include "deserialize/implicit/i64.c"
#endif
}

static inline uintmax_t int_umax_parsei (const char_t* str, int_parse_t* out)
{
  #define t_int uintmax_t

  #define T_VALID

  #define T_MAXVAL UINTMAX_MAX
  #define T_MAXDIG UINTMAX_DIG

#if (INTMAX_BIT >= 128)
  #include "deserialize/implicit/i128.c"
#else
  #include "deserialize/implicit/i64.c"
#endif
}

// -----------------------------------------------------------------------------
// Pointer
// -----------------------------------------------------------------------------

static inline intptr_t int_sptr_parse (const char_t* str, size_t len, int_parse_t* out)
{
  #define t_int uintptr_t

  #define T_SIGN
  #define T_VALID

  #define T_MAXVAL (uintptr_t)INTPTR_MAX
  #define T_MAXDIG INTPTR_DIG

#if (INTPTR_BIT >= 64)
  #include "deserialize/explicit/i64.c"
#else
  #include "deserialize/explicit/i32.c"
#endif
}

static inline uintptr_t int_uptr_parse (const char_t* str, size_t len, int_parse_t* out)
{
  #define t_int uintptr_t

  #define T_VALID

  #define T_MAXVAL UINTPTR_MAX
  #define T_MAXDIG UINTPTR_DIG

#if (INTPTR_BIT >= 64)
  #include "deserialize/explicit/i64.c"
#else
  #include "deserialize/explicit/i32.c"
#endif
}

// -----------------------------------------------------------------------------

static inline intptr_t int_sptr_parsei (const char_t* str, int_parse_t* out)
{
  #define t_int uintptr_t

  #define T_SIGN

  #define T_MAXVAL (uintptr_t)INTPTR_MAX
  #define T_MAXDIG INTPTR_DIG

#if (INTPTR_BIT >= 64)
  #include "deserialize/implicit/i64.c"
#else
  #include "deserialize/implicit/i32.c"
#endif
}

static inline uintptr_t int_uptr_parsei (const char_t* str, int_parse_t* out)
{
  #define t_int uintptr_t

  #define T_MAXVAL UINTPTR_MAX
  #define T_MAXDIG UINTPTR_DIG

#if (INTPTR_BIT >= 64)
  #include "deserialize/implicit/i64.c"
#else
  #include "deserialize/implicit/i32.c"
#endif
}

// =============================================================================
// Macros
// -----------------------------------------------------------------------------
// Map the decimal string parsing functions above
// to the fundamental integral types
// -----------------------------------------------------------------------------
// `char`
// -----------------------------------------------------------------------------

#if (CHAR_BIT == INTMAX_BIT)
  #define int_schar_parse int_smax_parse
  #define int_uchar_parse int_umax_parse

  #define int_schar_parsei int_smax_parsei
  #define int_uchar_parsei int_umax_parsei
#elif (CHAR_BIT == INT_FAST64_BIT)
  #define int_schar_parse int_s64_parse
  #define int_uchar_parse int_u64_parse

  #define int_schar_parsei int_s64_parsei
  #define int_uchar_parsei int_u64_parsei
#elif (CHAR_BIT == INT_FAST32_BIT)
  #define int_schar_parse int_s32_parse
  #define int_uchar_parse int_u32_parse

  #define int_schar_parsei int_s32_parsei
  #define int_uchar_parsei int_u32_parsei
#elif (CHAR_BIT == INT_FAST16_BIT)
  #define int_schar_parse int_s16_parse
  #define int_uchar_parse int_u16_parse

  #define int_schar_parsei int_s16_parsei
  #define int_uchar_parsei int_u16_parsei
#elif (CHAR_BIT == INT_FAST8_BIT)
  #define int_schar_parse int_s8_parse
  #define int_uchar_parse int_u8_parse

  #define int_schar_parsei int_s8_parsei
  #define int_uchar_parsei int_u8_parsei
#endif

// -----------------------------------------------------------------------------
// `short`
// -----------------------------------------------------------------------------

#if (SHRT_BIT == INTMAX_BIT)
  #define int_sshort_parse int_smax_parse
  #define int_ushort_parse int_umax_parse

  #define int_sshort_parsei int_smax_parsei
  #define int_ushort_parsei int_umax_parsei
#elif (SHRT_BIT == INT_FAST64_BIT)
  #define int_sshort_parse int_s64_parse
  #define int_ushort_parse int_u64_parse

  #define int_sshort_parsei int_s64_parsei
  #define int_ushort_parsei int_u64_parsei
#elif (SHRT_BIT == INT_FAST32_BIT)
  #define int_sshort_parse int_s32_parse
  #define int_ushort_parse int_u32_parse

  #define int_sshort_parsei int_s32_parsei
  #define int_ushort_parsei int_u32_parsei
#elif (SHRT_BIT == INT_FAST16_BIT)
  #define int_sshort_parse int_s16_parse
  #define int_ushort_parse int_u16_parse

  #define int_sshort_parsei int_s16_parsei
  #define int_ushort_parsei int_u16_parsei
#endif

// -----------------------------------------------------------------------------
// `int`
// -----------------------------------------------------------------------------

#if (INT_BIT == INTMAX_BIT)
  #define int_sint_parse int_smax_parse
  #define int_uint_parse int_umax_parse

  #define int_sint_parsei int_smax_parsei
  #define int_uint_parsei int_umax_parsei
#elif (INT_BIT == INT_FAST64_BIT)
  #define int_sint_parse int_s64_parse
  #define int_uint_parse int_u64_parse

  #define int_sint_parsei int_s64_parsei
  #define int_uint_parsei int_u64_parsei
#elif (INT_BIT == INT_FAST32_BIT)
  #define int_sint_parse int_s32_parse
  #define int_uint_parse int_u32_parse

  #define int_sint_parsei int_s32_parsei
  #define int_uint_parsei int_u32_parsei
#elif (INT_BIT == INT_FAST16_BIT)
  #define int_sint_parse int_s16_parse
  #define int_uint_parse int_u16_parse

  #define int_sint_parsei int_s16_parsei
  #define int_uint_parsei int_u16_parsei
#endif

// -----------------------------------------------------------------------------
// `long`
// -----------------------------------------------------------------------------

#if (LONG_BIT == INTMAX_BIT)
  #define int_slong_parse int_smax_parse
  #define int_ulong_parse int_umax_parse

  #define int_slong_parsei int_smax_parsei
  #define int_ulong_parsei int_umax_parsei
#elif (LONG_BIT == INT_FAST64_BIT)
  #define int_slong_parse int_s64_parse
  #define int_ulong_parse int_u64_parse

  #define int_slong_parsei int_s64_parsei
  #define int_ulong_parsei int_u64_parsei
#elif (LONG_BIT == INT_FAST32_BIT)
  #define int_slong_parse int_s32_parse
  #define int_ulong_parse int_u32_parse

  #define int_slong_parsei int_s32_parsei
  #define int_ulong_parsei int_u32_parsei
#endif

// -----------------------------------------------------------------------------
// `llong`
// -----------------------------------------------------------------------------

#if (LLONG_BIT == INTMAX_BIT)
  #define int_sllong_parse int_smax_parse
  #define int_ullong_parse int_umax_parse

  #define int_sllong_parsei int_smax_parsei
  #define int_ullong_parsei int_umax_parsei
#elif (LLONG_BIT == INT_FAST64_BIT)
  #define int_sllong_parse int_s64_parse
  #define int_ullong_parse int_u64_parse

  #define int_sllong_parsei int_s64_parsei
  #define int_ullong_parsei int_u64_parsei
#endif

// -----------------------------------------------------------------------------

#include "support/outro.h"

// -----------------------------------------------------------------------------

#endif
