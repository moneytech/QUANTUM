// =============================================================================
// <integer/convert/hexadecimal/serialize/basic/i8.c>
//
// 8-bit+ integer to hexadecimal string conversion template.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

if (true)
{
  #include "intro.c"

#if (INT_FAST8_BIT == 8)
  b = int_tail_xdig2 (b, uv, lc);
#else
  b = int_div_xdig (b, uv, lc);
#endif

  #include "outro.c"
}

// -----------------------------------------------------------------------------

#include "outro.h"
