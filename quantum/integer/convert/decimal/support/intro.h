// =============================================================================
// <integer/convert/decimal/support/intro.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../support/intro.h"

// -----------------------------------------------------------------------------
// Generic decimal string to integer conversion microtemplate
#define int_from_str(i, s, e, a) do\
{                                  \
  while ((s) != (e))               \
  {                                \
    register uint d = chr_dig_to_int (*(s));\
                             \
    if (unlikely (d > 9u)) a;\
                        \
    i = ((i) * 10u) + d;\
    (s)++;\
  }       \
} while (0)

// -----------------------------------------------------------------------------
// Version for implicit decimal strings
#define int_from_stri(i, s, a) do\
{                                \
  while (true)                   \
  {                              \
    register uint d = chr_dig_to_int (*(s));\
                             \
    if (unlikely (d > 9u)) a;\
                        \
    i = ((i) * 10u) + d;\
    (s)++;\
  }       \
} while (0)

// -----------------------------------------------------------------------------
// Microtemplates for validating a vector of `x` characters as decimal digit
// characters and converting them to their numeric value if they actually are.
//
// There are two kinds of validating functions.
//
// The first kind returns a boolean result value and an additional loop
// of `int_from_stri()` is required to obtain the remaining decimal digits
// in case if the validating function returns `false`.
//
// The second kind returns an integer value with precise position where
// the first non-decimal character occurs.
// -----------------------------------------------------------------------------
// Microtemplate for validating functions that return an integer
#define int_from_dig(i, s, d, m, a) do\
{                                     \
  register uint n = int_is_dig##d##v (s);\
                                      \
  if (n != (d)) a;                    \
                                      \
  i = ((i) * (m)) + int_from_dig##d##v (s);\
  s += (d);\
} while (0)

// -----------------------------------------------------------------------------
// Microtemplate for validating functions that return a boolean
#define int_from_digi(i, s, d, m, a) do\
{                                      \
  if (!int_is_dig##d##v (s)) a;        \
                                       \
  i = ((i) * (m)) + int_from_dig##d##v (s);\
  s += (d);\
} while (0)
