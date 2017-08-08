// =============================================================================
// <integer/convert/hexadecimal/serialize/format/i8.c>
//
// 8-bit+ integer to hexadecimal string formatting template.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

if (true)
{
  #include "intro.c"

#if (INT_FAST8_BIT == 8)
  int_tail_xdig2 (ptr, uv, lc);
#else
  while (len--)
  {
    ptr[len] = chr_xdig_from_int (uv & 0xFu) | lc;
    uv <<= 4;
  }
#endif

  #include "outro.c"
}

// -----------------------------------------------------------------------------

#include "outro.h"
