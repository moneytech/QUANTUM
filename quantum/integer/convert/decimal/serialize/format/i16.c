// =============================================================================
// <integer/convert/decimal/serialize/format/i16.c>
//
// 16-bit+ integer to decimal string formatting template.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

if (true)
{
  #include "intro.c"

  while (len > 1u)
  {
    int_to_dig2 (ptr + len - 2, uv % 100u);
    uv /= 100u;

    len -= 2u;
  }

  if (len != 0) *ptr = chr_dig_from_int (uv);

  #include "outro.c"
}

// -----------------------------------------------------------------------------

#include "outro.h"
