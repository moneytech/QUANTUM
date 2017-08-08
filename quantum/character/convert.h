// =============================================================================
// <character/convert.h>
//
// Convert characters to other values.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_C961BAAA507945FA9F7182071C85F689
#define H_C961BAAA507945FA9F7182071C85F689

// -----------------------------------------------------------------------------
// Binary
// -----------------------------------------------------------------------------
// Convert a binary digit character to its numeric value
#define chr_bdig_to_int(c) chr_to_int (c)

// -----------------------------------------------------------------------------
// Convert a numeric value to its binary digit character
#define chr_bdig_from_int(i) chr_from_int (i)

// -----------------------------------------------------------------------------
// Octal
// -----------------------------------------------------------------------------
// Convert an octal digit character to its numeric value
#define chr_odig_to_int(c) chr_to_int (c)

// -----------------------------------------------------------------------------
// Convert an numeric value to its octal digit character
#define chr_odig_from_int(i) chr_from_int (i)

// -----------------------------------------------------------------------------
// Decimal
// -----------------------------------------------------------------------------
// Convert a decimal digit character to its numeric value
#define chr_dig_to_int(c) chr_to_int (c)

// -----------------------------------------------------------------------------
// Convert a numeric value to its decimal digit character
#define chr_dig_from_int(i) chr_from_int (i)

// -----------------------------------------------------------------------------
// Hexadecimal
// -----------------------------------------------------------------------------
// Convert a hexadecimal digit character of any case to its numeric value
static inline uint chr_xdig_to_int_fast (uint c)
{
#if 1
  register uint l = c & 0x40u;
  return (c + ((l >> 3) | (l >> 6))) & 0xFu;
#elif 0
  return ((c <= (uint)'9') ? (c - (uint)'0')
  : (chr_to_lcase_fast (c) - (uint)'a' + 10u));
#else
  return (c % 39) - 9;
#endif
}

// -----------------------------------------------------------------------------
// Validating variant of `chr_xdig_to_int_fast()` which simultaneously tests
// for hexadecimal digit character of any case and gets its numeric value
static inline uint chr_xdig_to_int (uint c)
{
  // GCC produces the fastest code when written exactly like this
  register uint d = c - ((uint)'0' >> (c > (uint)'9'));
  return (c > (uint)'@') ? (chr_to_lcase_fast (c) - (uint)'a' + 10u) : d;
}

// -----------------------------------------------------------------------------
// Convert a numeric value to its hexadecimal digit character
static inline uint chr_xdig_from_int (uint i)
{
#if 1
  register bint x = (i > 9u);
  return i + (uint)'0' + ((x << 3) - x);
#else
  return ((i < 10u) ? (i + (uint)'0') : (i + (uint)'A' - 10u));
#endif
}

// -----------------------------------------------------------------------------

#endif
