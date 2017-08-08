// =============================================================================
// <integer/divide.h>
//
// Integral division.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_CCCCAC9DF0944F2097963880742C6BC5
#define H_CCCCAC9DF0944F2097963880742C6BC5

// =============================================================================
// Macros
// -----------------------------------------------------------------------------

#if HAVE(C99) || C(MSC)
  #define INT_DIV_CORRECT 0
#else
  #define INT_DIV_CORRECT 1
#endif

#define int_div_s(type)\
  type quot;\
  type rem

#define int_div(type)\
  type##_div_t res;  \
                     \
  res.quot = numer / denom;\
  res.rem = numer % denom;\
                     \
  if (INT_DIV_CORRECT && (numer < 0) && (res.rem > 0))\
  {                  \
    res.quot++;      \
    res.rem -= denom;\
  }        \
           \
  return res

// =============================================================================
// Types
// -----------------------------------------------------------------------------

typedef struct s8_div_s
{
  int_div_s (sl8);
} s8_div_t;

typedef struct s16_div_s
{
  int_div_s (sl16);
} s16_div_t;

typedef struct s32_div_s
{
  int_div_s (sl32);
} s32_div_t;

typedef struct s64_div_s
{
  int_div_s (sl64);
} s64_div_t;

#if HAVE(INT_LEAST128)
typedef struct s128_div_s
{
  int_div_s (sl128);
} s128_div_t;
#endif

typedef struct intmax_div_s
{
  int_div_s (intmax_t);
} intmax_div_t;

typedef struct intptr_div_s
{
  int_div_s (intptr_t);
} intptr_div_t;

// =============================================================================
// Functions
// -----------------------------------------------------------------------------

static inline s8_div_t int_s8_div (sf8 numer, sf8 denom)
{
  int_div (s8);
}

static inline s16_div_t int_s16_div (sf16 numer, sf16 denom)
{
  int_div (s16);
}

static inline s32_div_t int_s32_div (sf32 numer, sf32 denom)
{
  int_div (s32);
}

static inline s64_div_t int_s64_div (sf64 numer, sf64 denom)
{
  int_div (s64);
}

#if HAVE(INT_LEAST128)
static inline s128_div_t int_s128_div (sf128 numer, sf128 denom)
{
  int_div (s128);
}
#endif

static inline intmax_div_t int_max_div (intmax_t numer, intmax_t denom)
{
  int_div (intmax);
}

static inline intptr_div_t int_ptr_div (intptr_t numer, intptr_t denom)
{
  int_div (intptr);
}

// =============================================================================
// Macros
// -----------------------------------------------------------------------------
// `char`
#if (CHAR_BIT == INT_FAST8_BIT)
  #define int_schar_div int_s8_div
#elif (CHAR_BIT == INT_FAST16_BIT)
  #define int_schar_div int_s16_div
#elif (CHAR_BIT == INT_FAST32_BIT)
  #define int_schar_div int_s32_div
#elif (CHAR_BIT == INT_FAST64_BIT)
  #define int_schar_div int_s64_div
#elif (CHAR_BIT == INTMAX_BIT)
  #define int_schar_div int_smax_div
#endif

// -----------------------------------------------------------------------------
// `short`
#if (SHRT_BIT == INT_FAST16_BIT)
  #define int_sshort_div int_s16_div
#elif (SHRT_BIT == INT_FAST32_BIT)
  #define int_sshort_div int_s32_div
#elif (SHRT_BIT == INT_FAST64_BIT)
  #define int_sshort_div int_s64_div
#elif (SHRT_BIT == INTMAX_BIT)
  #define int_sshort_div int_smax_div
#endif

// -----------------------------------------------------------------------------
// `int`
#if (INT_BIT == INT_FAST16_BIT)
  #define int_sint_div int_s16_div
#elif (INT_BIT == INT_FAST32_BIT)
  #define int_sint_div int_s32_div
#elif (INT_BIT == INT_FAST64_BIT)
  #define int_sint_div int_s64_div
#elif (INT_BIT == INTMAX_BIT)
  #define int_sint_div int_smax_div
#endif

// -----------------------------------------------------------------------------
// `long`
#if (LONG_BIT == INT_FAST32_BIT)
  #define int_slong_div int_s32_div
#elif (LONG_BIT == INT_FAST64_BIT)
  #define int_slong_div int_s64_div
#elif (LONG_BIT == INTMAX_BIT)
  #define int_slong_div int_smax_div
#endif

// -----------------------------------------------------------------------------
// `llong`
#if (LLONG_BIT == INT_FAST64_BIT)
  #define int_sllong_div int_s64_div
#elif (LLONG_BIT == INTMAX_BIT)
  #define int_sllong_div int_smax_div
#endif

// =============================================================================
// Cleanup
// -----------------------------------------------------------------------------

#undef INT_DIV_CORRECT
#undef int_div_s
#undef int_div

// -----------------------------------------------------------------------------

#endif
