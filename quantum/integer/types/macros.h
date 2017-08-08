// =============================================================================
// <integer/types/macros.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_B886B8F44D8B4B84A2A918C48F2B9984
#define H_B886B8F44D8B4B84A2A918C48F2B9984

// -----------------------------------------------------------------------------
// Determine the exact width of the particular integral type with bit precision.
//
// This macro returns the number of bits set in `INTTYPE_MAX`
// (passed in the `i` parameter), or in any `(1 << p) - 1`.
// -----------------------------------------------------------------------------

#if 1
  // Version for `0 <= p < 2040`
  #define INT_BIT_MAX(i)\
  (                     \
    ((i) / ((i) % 255 + 1) / 255 % 255 * 8)\
    + (7 - 86 / ((i) % 255 + 12))\
  )
#else
  // Version for `0 <= p < 3e10`
  #define INT_BIT_MAX(i)\
  (                     \
    ((i) / ((i) % 0x3FFFFFFF + 1) / 0x3FFFFFFF % 0x3FFFFFFF * 30)\
    + ((i) % 0x3FFFFFFF / ((i) % 31 + 1) / 31 % 31 * 5)\
    + (4 - 12 / ((i) % 31 + 3))\
  )
#endif

// -----------------------------------------------------------------------------
// Determine the exact number of decimal digits the particular integral type can
// represent. This can be inferred from its exact bit width with the help of the
// `INT_BIT_MAX` macro above.
#define INT_DIG_MAX(b) (((((b) - 1) / 10) * 3) + ((((b) - 1) % 10) / 3) + 1)

// -----------------------------------------------------------------------------
// Determine the exact number of hexadecimal digits the particular integral type
// can represent
#define INT_XDIG_MAX(b) (((b) / 4) + !!((b) % 4))

// -----------------------------------------------------------------------------
// Determine the exact number of octal digits the particular integral type can
// represent
#define INT_ODIG_MAX(b) (((b) / 3) + !!((b) % 3))

// -----------------------------------------------------------------------------

#endif
