// =============================================================================
// <character/transform.h>
//
// Transform individual characters.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_A90E8B04A0394D60AA92E0B47F8B1396
#define H_A90E8B04A0394D60AA92E0B47F8B1396

// -----------------------------------------------------------------------------
// Transform a hexadecimal digit character to lower case:
// [A-F] -> [a-f] ([0-9] unaffected)
static inline uint chr_xdig_to_lcase (uint c)
{
  return c | ((c & 0x40u) >> 1);
}

// -----------------------------------------------------------------------------
// Transform a hexadecimal digit character to upper case:
// [a-f] -> [A-F] ([0-9] unaffected)
static inline uint chr_xdig_to_ucase (uint c)
{
  return c ^ (c & (c >> 1) & 0x20u);
}

// -----------------------------------------------------------------------------
// Equivalent of `toupper()`: transform an ASCII character to upper case
static inline uint chr_to_ucase (uint c)
{
  return c ^ (chr_is_lcase (c) << 5);
}

// -----------------------------------------------------------------------------
// Equivalent of `tolower()`: transform an ASCII character to lower case
static inline uint chr_to_lcase (uint c)
{
  return c | (chr_is_ucase (c) << 5);
}

// -----------------------------------------------------------------------------

#endif
