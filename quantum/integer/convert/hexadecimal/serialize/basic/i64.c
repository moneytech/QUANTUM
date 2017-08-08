// =============================================================================
// <integer/convert/hexadecimal/serialize/basic/i64.c>
//
// 64-bit+ integer to hexadecimal string conversion template.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

if (true)
{
  #include "intro.c"

#if CPU(SSE2)
  if (uv >= 0x1000000000000000u)
  {
    int_to_xdig16f (b, uv, lc);
    b += 16;

    goto outro;
  }
#endif

  b = int_div_xdig8 (b, uv, lc);

  #include "outro.c"
}

// -----------------------------------------------------------------------------

#include "outro.h"
