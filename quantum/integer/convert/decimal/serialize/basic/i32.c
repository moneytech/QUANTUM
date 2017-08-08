// =============================================================================
// <integer/convert/decimal/serialize/basic/i32.c>
//
// 32-bit+ integer to decimal string conversion template.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

if (true)
{
  #include "intro.c"

#if (INT_FAST32_BIT == 32) && CPU(64BIT)
  if (uv >= 100000000u)
  {
    uint q = uv / 100000000u;
    u32 r = uv % 100000000u;

    b = int_tail_dig2 (b, q);

    int_to_dig8 (b, r);
    b += 8;

    goto outro;
  }
#endif

  b = int_div_dig4 (b, uv);

  #include "outro.c"
}

// -----------------------------------------------------------------------------

#include "outro.h"
