// =============================================================================
// <integer/absolute.h>
//
// Get the absolute integer value.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_E8AAD09D3EAB473AAE8715A72BD74D6A
#define H_E8AAD09D3EAB473AAE8715A72BD74D6A

// =============================================================================
// Macros
// -----------------------------------------------------------------------------
// Conditional two's complement integral negation.
// `c` must be either 1 (`true`, negation) or 0 (`false`, no negation).
#if CPU(TWOS_COMPLEMENT)
  #define int_negif(i, c) (((i) ^ -(c)) + (c))
#else
  #define int_negif negif
#endif

// -----------------------------------------------------------------------------
// Absolute integer value computation template
#if CPU(SIGN_EXTENSION)
  // Compute the absolute integral value
  // using the sign extension bit mask
  #define int_abs(type, bits)\
  type m = i >> (bits - 1u);\
  return (i + m) ^ m
#else
  // Portable variant ignoring the negative sign extension
  // and using the isolated sign bit
  #define int_abs(type, bits)\
  type b = (type)i >> (bits - 1u);\
  return int_negif (i, b)
#endif

// =============================================================================
// Functions
// -----------------------------------------------------------------------------
// `abs()` functions for all signed integral types
// -----------------------------------------------------------------------------

static inline uf8 int_s8_abs (sf8 i)
{
  int_abs (uf8, INT_FAST8_BIT);
}

static inline uf16 int_s16_abs (sf16 i)
{
  int_abs (uf16, INT_FAST16_BIT);
}

static inline uf32 int_s32_abs (sf32 i)
{
  int_abs (uf32, INT_FAST32_BIT);
}

static inline uf64 int_s64_abs (sf64 i)
{
  int_abs (uf64, INT_FAST64_BIT);
}

#if HAVE(INT_LEAST128)
static inline uf128 int_s128_abs (sf128 i)
{
  int_abs (uf128, INT_FAST128_BIT);
}
#endif

static inline uintmax_t int_max_abs (intmax_t i)
{
  int_abs (uintmax_t, INTMAX_BIT);
}

static inline uintptr_t int_ptr_abs (intptr_t i)
{
  int_abs (uintptr_t, INTPTR_BIT);
}

// =============================================================================
// Macros
// -----------------------------------------------------------------------------
// `char`
#if (CHAR_BIT == INT_FAST8_BIT)
  #define int_schar_abs int_s8_abs
#elif (CHAR_BIT == INT_FAST16_BIT)
  #define int_schar_abs int_s16_abs
#elif (CHAR_BIT == INT_FAST32_BIT)
  #define int_schar_abs int_s32_abs
#elif (CHAR_BIT == INT_FAST64_BIT)
  #define int_schar_abs int_s64_abs
#elif (CHAR_BIT == INTMAX_BIT)
  #define int_schar_abs int_smax_abs
#endif

// -----------------------------------------------------------------------------
// `short`
#if (SHRT_BIT == INT_FAST16_BIT)
  #define int_sshort_abs int_s16_abs
#elif (SHRT_BIT == INT_FAST32_BIT)
  #define int_sshort_abs int_s32_abs
#elif (SHRT_BIT == INT_FAST64_BIT)
  #define int_sshort_abs int_s64_abs
#elif (SHRT_BIT == INTMAX_BIT)
  #define int_sshort_abs int_smax_abs
#endif

// -----------------------------------------------------------------------------
// `int`
#if (INT_BIT == INT_FAST16_BIT)
  #define int_sint_abs int_s16_abs
#elif (INT_BIT == INT_FAST32_BIT)
  #define int_sint_abs int_s32_abs
#elif (INT_BIT == INT_FAST64_BIT)
  #define int_sint_abs int_s64_abs
#elif (INT_BIT == INTMAX_BIT)
  #define int_sint_abs int_smax_abs
#endif

// -----------------------------------------------------------------------------
// `long`
#if (LONG_BIT == INT_FAST32_BIT)
  #define int_slong_abs int_s32_abs
#elif (LONG_BIT == INT_FAST64_BIT)
  #define int_slong_abs int_s64_abs
#elif (LONG_BIT == INTMAX_BIT)
  #define int_slong_abs int_smax_abs
#endif

// -----------------------------------------------------------------------------
// `llong`
#if (LLONG_BIT == INT_FAST64_BIT)
  #define int_sllong_abs int_s64_abs
#elif (LLONG_BIT == INTMAX_BIT)
  #define int_sllong_abs int_smax_abs
#endif

// =============================================================================
// Cleanup
// -----------------------------------------------------------------------------

#undef int_abs

// -----------------------------------------------------------------------------

#endif
