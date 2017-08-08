// =============================================================================
// <integer/convert/support/intro.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------
// Microtemplate for skipping leading zeros in an explicit string
#define int_skip_zeros(str, len) do\
{                                  \
  while ((len) != 0)               \
  {                                \
    if (likely (*(str) != '0')) break;\
            \
    (str)++;\
    (len)--;\
  }       \
} while (0)

// -----------------------------------------------------------------------------
// Version for implicit strings
#define int_skip_zerosi(str) do\
{                              \
  while (*(str) == '0') (str)++;\
} while (0)
