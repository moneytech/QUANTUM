// =============================================================================
// <integer/convert/hexadecimal/serialize/basic/i32.c>
//
// 32-bit+ integer to hexadecimal string conversion template.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

if (true)
{
  #include "intro.c"

#if CPU(SSE2)
  if (uv >= 0x10000000u)
  {
    int_to_xdig8f (b, uv, lc);
    b += 8;

    goto outro;
  }
#endif

  b = int_div_xdig4 (b, uv, lc);

  #include "outro.c"
}

// -----------------------------------------------------------------------------

#include "outro.h"
