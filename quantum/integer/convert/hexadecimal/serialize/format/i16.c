// =============================================================================
// <integer/convert/hexadecimal/serialize/format/i16.c>
//
// 16-bit+ integer to hexadecimal string formatting template.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

if (true)
{
  #include "intro.c"

  while (len > 1u)
  {
    int_to_xdig2f (ptr + len - 2, uv & 0xFFu, lc);
    uv <<= 8;

    len -= 2u;
  }

  if (len != 0) *ptr = chr_xdig_from_int (uv) | lc;

  #include "outro.c"
}

// -----------------------------------------------------------------------------

#include "outro.h"
