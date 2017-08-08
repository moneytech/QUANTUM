// =============================================================================
// <integer/convert/hexadecimal/support/intro.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../support/intro.h"

// -----------------------------------------------------------------------------
// Generic hexadecimal string to integer conversion microtemplate
#define int_from_xstr(i, s, e, a) do\
{                                   \
  while ((s) != (e))                \
  {                                 \
    register uint d = chr_xdig_to_int (*(s));\
                               \
    if (unlikely (d > 0xFu)) a;\
                       \
    i = ((i) << 4) | d;\
    (s)++;\
  }       \
} while (0)

// -----------------------------------------------------------------------------
// Version for implicit hexadecimal strings
#define int_from_xstri(i, s, a) do\
{                                 \
  while (true)                    \
  {                               \
    register uint d = chr_xdig_to_int (*(s));\
                               \
    if (unlikely (d > 0xFu)) a;\
                       \
    i = ((i) << 4) | d;\
    (s)++;\
  }       \
} while (0)

// -----------------------------------------------------------------------------
// Microtemplate for validating functions that return an integer
#define int_from_xdig(i, s, d, m, a) do\
{                                      \
  register uint n = int_is_xdig##d (s);\
                                       \
  if (n != (d)) a;                     \
                                       \
  s += (d);                            \
  i = ((i) << (m)) + int_from_xdig##d##v (s);\
} while (0)

// -----------------------------------------------------------------------------
// Microtemplate for validating functions that return a boolean
#define int_from_xdigi(i, s, d, m, a) do\
{                                       \
  if (!int_is_xdig##d (s)) a;           \
                                        \
  s += (d);                             \
  i = ((i) << (m)) + int_from_xdig##d##v (s);\
} while (0)
