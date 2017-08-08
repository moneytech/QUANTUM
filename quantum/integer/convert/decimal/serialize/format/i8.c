// =============================================================================
// <integer/convert/decimal/serialize/format/i8.c>
//
// 8-bit+ integer to decimal string formatting template.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

if (true)
{
  #include "intro.c"

#if (INT_FAST8_BIT == 8)
  int_tail_dig2 (ptr, uv);
#else
  while (len--)
  {
    ptr[len] = chr_dig_from_int (uv % 10u);
    uv /= 10u;
  }
#endif

  #include "outro.c"
}

// -----------------------------------------------------------------------------

#include "outro.h"
