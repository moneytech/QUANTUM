// =============================================================================
// <integer/convert/hexadecimal/parse.c>
//
// Parse integral numbers from hexadecimal strings of explicit length and from
// null-terminated strings validating the input and preventing overflow.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_E3EE08291DF441E288E85A03439E3966
#define H_E3EE08291DF441E288E85A03439E3966

// -----------------------------------------------------------------------------

#include "support/intro.h"

// =============================================================================
// Functions
// -----------------------------------------------------------------------------
// 8-bit+
// -----------------------------------------------------------------------------

static inline sf8 int_s8_xparse (const char_t* str, size_t len, int_parse_t* out)
{
  #define t_int uf8

  #define T_MAXVAL (uf8)INT_FAST8_MAX
  #define T_MAXDIG INT_FAST8_DIG
  #define T_MAXBIT (INT_FAST8_BIT - 1)

  #define T_SIGN
  #define T_VALID

  #include "deserialize/explicit/i8.c"
}

static inline uf8 int_u8_xparse (const char_t* str, size_t len, int_parse_t* out)
{
  #define t_int uf8

  #define T_MAXVAL UINT_FAST8_MAX
  #define T_MAXDIG UINT_FAST8_DIG
  #define T_MAXBIT INT_FAST8_BIT

  #define T_VALID

  #include "deserialize/explicit/i8.c"
}

// -----------------------------------------------------------------------------

static inline sf8 int_s8_xparsei (const char_t* str, int_parse_t* out)
{
  #define t_int uf8

  #define T_MAXVAL (uf8)INT_FAST8_MAX
  #define T_MAXDIG INT_FAST8_DIG
  #define T_MAXBIT (INT_FAST8_BIT - 1)

  #define T_SIGN
  #define T_VALID

  #include "deserialize/implicit/i8.c"
}

static inline uf8 int_u8_xparsei (const char_t* str, int_parse_t* out)
{
  #define t_int uf8

  #define T_MAXVAL UINT_FAST8_MAX
  #define T_MAXDIG UINT_FAST8_DIG
  #define T_MAXBIT INT_FAST8_BIT

  #define T_VALID

  #include "deserialize/implicit/i8.c"
}

// -----------------------------------------------------------------------------
// 16-bit+
// -----------------------------------------------------------------------------

static inline sf16 int_s16_xparse (const char_t* str, size_t len, int_parse_t* out)
{
  #define t_int uf16

  #define T_MAXVAL (uf16)INT_FAST16_MAX
  #define T_MAXDIG INT_FAST16_DIG
  #define T_MAXBIT (INT_FAST16_BIT - 1)

  #define T_SIGN
  #define T_VALID

  #include "deserialize/explicit/i16.c"
}

static inline uf16 int_u16_xparse (const char_t* str, size_t len, int_parse_t* out)
{
  #define t_int uf16

  #define T_MAXVAL UINT_FAST16_MAX
  #define T_MAXDIG UINT_FAST16_DIG
  #define T_MAXBIT INT_FAST16_BIT

  #define T_VALID

  #include "deserialize/explicit/i16.c"
}

// -----------------------------------------------------------------------------

static inline sf16 int_s16_xparsei (const char_t* str, int_parse_t* out)
{
  #define t_int uf16

  #define T_MAXVAL (uf16)INT_FAST16_MAX
  #define T_MAXDIG INT_FAST16_DIG
  #define T_MAXBIT (INT_FAST16_BIT - 1)

  #define T_SIGN
  #define T_VALID

  #include "deserialize/implicit/i16.c"
}

static inline uf16 int_u16_xparsei (const char_t* str, int_parse_t* out)
{
  #define t_int uf16

  #define T_MAXVAL UINT_FAST16_MAX
  #define T_MAXDIG UINT_FAST16_DIG
  #define T_MAXBIT INT_FAST16_BIT

  #define T_VALID

  #include "deserialize/implicit/i16.c"
}

// -----------------------------------------------------------------------------
// 32-bit+
// -----------------------------------------------------------------------------

static inline sf32 int_s32_xparse (const char_t* str, size_t len, int_parse_t* out)
{
  #define t_int uf32

  #define T_MAXVAL (uf32)INT_FAST32_MAX
  #define T_MAXDIG INT_FAST32_DIG
  #define T_MAXBIT (INT_FAST32_BIT - 1)

  #define T_SIGN
  #define T_VALID

  #include "deserialize/explicit/i32.c"
}

static inline uf32 int_u32_xparse (const char_t* str, size_t len, int_parse_t* out)
{
  #define t_int uf32

  #define T_MAXVAL UINT_FAST32_MAX
  #define T_MAXDIG UINT_FAST32_DIG
  #define T_MAXBIT INT_FAST32_BIT

  #define T_VALID

  #include "deserialize/explicit/i32.c"
}

// -----------------------------------------------------------------------------

static inline sf32 int_s32_xparsei (const char_t* str, int_parse_t* out)
{
  #define t_int uf32

  #define T_MAXVAL (uf32)INT_FAST32_MAX
  #define T_MAXDIG INT_FAST32_DIG
  #define T_MAXBIT (INT_FAST32_BIT - 1)

  #define T_SIGN
  #define T_VALID

  #include "deserialize/implicit/i32.c"
}

static inline uf32 int_u32_xparsei (const char_t* str, int_parse_t* out)
{
  #define t_int uf32

  #define T_MAXVAL UINT_FAST32_MAX
  #define T_MAXDIG UINT_FAST32_DIG
  #define T_MAXBIT INT_FAST32_BIT

  #define T_VALID

  #include "deserialize/implicit/i32.c"
}

// -----------------------------------------------------------------------------
// 64-bit+
// -----------------------------------------------------------------------------

static inline sf64 int_s64_xparse (const char_t* str, size_t len, int_parse_t* out)
{
  #define t_int uf64

  #define T_MAXVAL (uf64)INT_FAST64_MAX
  #define T_MAXDIG INT_FAST64_DIG
  #define T_MAXBIT (INT_FAST64_BIT - 1)

  #define T_SIGN
  #define T_VALID

  #include "deserialize/explicit/i64.c"
}

static inline uf64 int_u64_xparse (const char_t* str, size_t len, int_parse_t* out)
{
  #define t_int uf64

  #define T_MAXVAL UINT_FAST64_MAX
  #define T_MAXDIG UINT_FAST64_DIG
  #define T_MAXBIT INT_FAST64_BIT

  #define T_VALID

  #include "deserialize/explicit/i64.c"
}

// -----------------------------------------------------------------------------

static inline sf64 int_s64_xparsei (const char_t* str, int_parse_t* out)
{
  #define t_int uf64

  #define T_MAXVAL (uf64)INT_FAST64_MAX
  #define T_MAXDIG INT_FAST64_DIG
  #define T_MAXBIT (INT_FAST64_BIT - 1)

  #define T_SIGN
  #define T_VALID

  #include "deserialize/implicit/i64.c"
}

static inline uf64 int_u64_xparsei (const char_t* str, int_parse_t* out)
{
  #define t_int uf64

  #define T_MAXVAL UINT_FAST64_MAX
  #define T_MAXDIG UINT_FAST64_DIG
  #define T_MAXBIT INT_FAST64_BIT

  #define T_VALID

  #include "deserialize/implicit/i64.c"
}

// -----------------------------------------------------------------------------
// 128-bit+
// -----------------------------------------------------------------------------

#if HAVE(INT_LEAST128)

static inline sf128 int_s128_xparse (const char_t* str, size_t len, int_parse_t* out)
{
  #define t_int uf128

  #define T_MAXVAL (uf128)INT_FAST128_MAX
  #define T_MAXDIG INT_FAST128_DIG
  #define T_MAXBIT (INT_FAST128_BIT - 1)

  #define T_SIGN
  #define T_VALID

  #include "deserialize/explicit/i128.c"
}

static inline uf128 int_u128_xparse (const char_t* str, size_t len, int_parse_t* out)
{
  #define t_int uf128

  #define T_MAXVAL UINT_FAST128_MAX
  #define T_MAXDIG UINT_FAST128_DIG
  #define T_MAXBIT INT_FAST128_BIT

  #define T_VALID

  #include "deserialize/explicit/i128.c"
}

// -----------------------------------------------------------------------------

static inline sf128 int_s128_xparsei (const char_t* str, int_parse_t* out)
{
  #define t_int uf128

  #define T_MAXVAL (uf128)INT_FAST128_MAX
  #define T_MAXDIG INT_FAST128_DIG
  #define T_MAXBIT (INT_FAST128_BIT - 1)

  #define T_SIGN
  #define T_VALID

  #include "deserialize/implicit/i128.c"
}

static inline uf128 int_u128_xparsei (const char_t* str, int_parse_t* out)
{
  #define t_int uf128

  #define T_MAXVAL UINT_FAST128_MAX
  #define T_MAXDIG UINT_FAST128_DIG
  #define T_MAXBIT INT_FAST128_BIT

  #define T_VALID

  #include "deserialize/implicit/i128.c"
}

#endif // HAVE(INT_LEAST128)

// -----------------------------------------------------------------------------
// Maximum
// -----------------------------------------------------------------------------

static inline intmax_t int_smax_xparse (const char_t* str, size_t len, int_parse_t* out)
{
  #define t_int uintmax_t

  #define T_MAXVAL (uintmax_t)INTMAX_MAX
  #define T_MAXDIG INTMAX_DIG
  #define T_MAXBIT (INTMAX_BIT - 1)

  #define T_SIGN
  #define T_VALID

#if (INTMAX_BIT >= 128)
  #include "deserialize/explicit/i128.c"
#else
  #include "deserialize/explicit/i64.c"
#endif
}

static inline uintmax_t int_umax_xparse (const char_t* str, size_t len, int_parse_t* out)
{
  #define t_int uintmax_t

  #define T_MAXVAL UINTMAX_MAX
  #define T_MAXDIG UINTMAX_DIG
  #define T_MAXBIT INTMAX_BIT

  #define T_VALID

#if (INTMAX_BIT >= 128)
  #include "deserialize/explicit/i128.c"
#else
  #include "deserialize/explicit/i64.c"
#endif
}

// -----------------------------------------------------------------------------

static inline intmax_t int_smax_xparsei (const char_t* str, int_parse_t* out)
{
  #define t_int uintmax_t

  #define T_MAXVAL (uintmax_t)INTMAX_MAX
  #define T_MAXDIG INTMAX_DIG
  #define T_MAXBIT (INTMAX_BIT - 1)

  #define T_SIGN
  #define T_VALID

#if (INTMAX_BIT >= 128)
  #include "deserialize/implicit/i128.c"
#else
  #include "deserialize/implicit/i64.c"
#endif
}

static inline uintmax_t int_umax_xparsei (const char_t* str, int_parse_t* out)
{
  #define t_int uintmax_t

  #define T_MAXVAL UINTMAX_MAX
  #define T_MAXDIG UINTMAX_DIG
  #define T_MAXBIT INTMAX_BIT

  #define T_VALID

#if (INTMAX_BIT >= 128)
  #include "deserialize/implicit/i128.c"
#else
  #include "deserialize/implicit/i64.c"
#endif
}

// -----------------------------------------------------------------------------
// Pointer
// -----------------------------------------------------------------------------

static inline intptr_t int_sptr_xparse (const char_t* str, size_t len, int_parse_t* out)
{
  #define t_int uintptr_t

  #define T_MAXVAL (uintptr_t)INTPTR_MAX
  #define T_MAXDIG INTPTR_DIG
  #define T_MAXBIT (INTPTR_BIT - 1)

  #define T_SIGN
  #define T_VALID

#if (INTPTR_BIT >= 64)
  #include "deserialize/explicit/i64.c"
#else
  #include "deserialize/explicit/i32.c"
#endif
}

static inline uintptr_t int_uptr_xparse (const char_t* str, size_t len, int_parse_t* out)
{
  #define t_int uintptr_t

  #define T_MAXVAL UINTPTR_MAX
  #define T_MAXDIG UINTPTR_DIG
  #define T_MAXBIT INTPTR_BIT

  #define T_VALID

#if (INTPTR_BIT >= 64)
  #include "deserialize/explicit/i64.c"
#else
  #include "deserialize/explicit/i32.c"
#endif
}

// -----------------------------------------------------------------------------

static inline intptr_t int_sptr_xparsei (const char_t* str, int_parse_t* out)
{
  #define t_int uintptr_t

  #define T_MAXVAL (uintptr_t)INTPTR_MAX
  #define T_MAXDIG INTPTR_DIG
  #define T_MAXBIT (INTPTR_BIT - 1)

  #define T_SIGN

#if (INTPTR_BIT >= 64)
  #include "deserialize/implicit/i64.c"
#else
  #include "deserialize/implicit/i32.c"
#endif
}

static inline uintptr_t int_uptr_xparsei (const char_t* str, int_parse_t* out)
{
  #define t_int uintptr_t

  #define T_MAXVAL UINTPTR_MAX
  #define T_MAXDIG UINTPTR_DIG
  #define T_MAXBIT INTPTR_BIT


#if (INTPTR_BIT >= 64)
  #include "deserialize/implicit/i64.c"
#else
  #include "deserialize/implicit/i32.c"
#endif
}

// =============================================================================
// Macros
// -----------------------------------------------------------------------------
// Map the hexadecimal string parsing functions above
// to the fundamental integral types
// -----------------------------------------------------------------------------
// `char`
// -----------------------------------------------------------------------------

#if (CHAR_BIT == INTMAX_BIT)
  #define int_schar_xparse int_smax_xparse
  #define int_uchar_xparse int_umax_xparse

  #define int_schar_xparsei int_smax_xparsei
  #define int_uchar_xparsei int_umax_xparsei
#elif (CHAR_BIT == INT_FAST64_BIT)
  #define int_schar_xparse int_s64_xparse
  #define int_uchar_xparse int_u64_xparse

  #define int_schar_xparsei int_s64_xparsei
  #define int_uchar_xparsei int_u64_xparsei
#elif (CHAR_BIT == INT_FAST32_BIT)
  #define int_schar_xparse int_s32_xparse
  #define int_uchar_xparse int_u32_xparse

  #define int_schar_xparsei int_s32_xparsei
  #define int_uchar_xparsei int_u32_xparsei
#elif (CHAR_BIT == INT_FAST16_BIT)
  #define int_schar_xparse int_s16_xparse
  #define int_uchar_xparse int_u16_xparse

  #define int_schar_xparsei int_s16_xparsei
  #define int_uchar_xparsei int_u16_xparsei
#elif (CHAR_BIT == INT_FAST8_BIT)
  #define int_schar_xparse int_s8_xparse
  #define int_uchar_xparse int_u8_xparse

  #define int_schar_xparsei int_s8_xparsei
  #define int_uchar_xparsei int_u8_xparsei
#endif

// -----------------------------------------------------------------------------
// `short`
// -----------------------------------------------------------------------------

#if (SHRT_BIT == INTMAX_BIT)
  #define int_sshort_xparse int_smax_xparse
  #define int_ushort_xparse int_umax_xparse

  #define int_sshort_xparsei int_smax_xparsei
  #define int_ushort_xparsei int_umax_xparsei
#elif (SHRT_BIT == INT_FAST64_BIT)
  #define int_sshort_xparse int_s64_xparse
  #define int_ushort_xparse int_u64_xparse

  #define int_sshort_xparsei int_s64_xparsei
  #define int_ushort_xparsei int_u64_xparsei
#elif (SHRT_BIT == INT_FAST32_BIT)
  #define int_sshort_xparse int_s32_xparse
  #define int_ushort_xparse int_u32_xparse

  #define int_sshort_xparsei int_s32_xparsei
  #define int_ushort_xparsei int_u32_xparsei
#elif (SHRT_BIT == INT_FAST16_BIT)
  #define int_sshort_xparse int_s16_xparse
  #define int_ushort_xparse int_u16_xparse

  #define int_sshort_xparsei int_s16_xparsei
  #define int_ushort_xparsei int_u16_xparsei
#endif

// -----------------------------------------------------------------------------
// `int`
// -----------------------------------------------------------------------------

#if (INT_BIT == INTMAX_BIT)
  #define int_sint_xparse int_smax_xparse
  #define int_uint_xparse int_umax_xparse

  #define int_sint_xparsei int_smax_xparsei
  #define int_uint_xparsei int_umax_xparsei
#elif (INT_BIT == INT_FAST64_BIT)
  #define int_sint_xparse int_s64_xparse
  #define int_uint_xparse int_u64_xparse

  #define int_sint_xparsei int_s64_xparsei
  #define int_uint_xparsei int_u64_xparsei
#elif (INT_BIT == INT_FAST32_BIT)
  #define int_sint_xparse int_s32_xparse
  #define int_uint_xparse int_u32_xparse

  #define int_sint_xparsei int_s32_xparsei
  #define int_uint_xparsei int_u32_xparsei
#elif (INT_BIT == INT_FAST16_BIT)
  #define int_sint_xparse int_s16_xparse
  #define int_uint_xparse int_u16_xparse

  #define int_sint_xparsei int_s16_xparsei
  #define int_uint_xparsei int_u16_xparsei
#endif

// -----------------------------------------------------------------------------
// `long`
// -----------------------------------------------------------------------------

#if (LONG_BIT == INTMAX_BIT)
  #define int_slong_xparse int_smax_xparse
  #define int_ulong_xparse int_umax_xparse

  #define int_slong_xparsei int_smax_xparsei
  #define int_ulong_xparsei int_umax_xparsei
#elif (LONG_BIT == INT_FAST64_BIT)
  #define int_slong_xparse int_s64_xparse
  #define int_ulong_xparse int_u64_xparse

  #define int_slong_xparsei int_s64_xparsei
  #define int_ulong_xparsei int_u64_xparsei
#elif (LONG_BIT == INT_FAST32_BIT)
  #define int_slong_xparse int_s32_xparse
  #define int_ulong_xparse int_u32_xparse

  #define int_slong_xparsei int_s32_xparsei
  #define int_ulong_xparsei int_u32_xparsei
#endif

// -----------------------------------------------------------------------------
// `llong`
// -----------------------------------------------------------------------------

#if (LLONG_BIT == INTMAX_BIT)
  #define int_sllong_xparse int_smax_xparse
  #define int_ullong_xparse int_umax_xparse

  #define int_sllong_xparsei int_smax_xparsei
  #define int_ullong_xparsei int_umax_xparsei
#elif (LLONG_BIT == INT_FAST64_BIT)
  #define int_sllong_xparse int_s64_xparse
  #define int_ullong_xparse int_u64_xparse

  #define int_sllong_xparsei int_s64_xparsei
  #define int_ullong_xparsei int_u64_xparsei
#endif

// -----------------------------------------------------------------------------

#include "support/outro.h"

// -----------------------------------------------------------------------------

#endif
