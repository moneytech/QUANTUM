// =============================================================================
// <integer/convert/decimal/serialize/basic/i64.c>
//
// 64-bit+ integer to decimal string conversion template.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

if (true)
{
  #include "intro.c"

#if (INT_FAST64_BIT == 64) && CPU(64BIT)
  if (uv >= 10000000000000000u)
  {
    uint q = uv / 10000000000000000u;
    u64 r = uv % 10000000000000000u;

  #ifdef T_SIGN
    b = int_tail_dig3 (b, q);
  #else
    b = int_tail_dig4 (b, q);
  #endif

    int_to_dig16 (b, r);
    b += 16;

    goto outro;
  }
#endif

  b = int_div_dig8 (b, uv);

  #include "outro.c"
}

// -----------------------------------------------------------------------------

#include "outro.h"
