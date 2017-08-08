// =============================================================================
// <integer/convert/decimal/serialize/basic/i8.c>
//
// 8-bit+ integer to decimal string conversion template.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

if (true)
{
  #include "intro.c"

#if (INT_FAST8_BIT == 8)
  b = int_tail_dig3 (b, uv);
#else
  b = int_div_dig (b, uv);
#endif

  #include "outro.c"
}

// -----------------------------------------------------------------------------

#include "outro.h"
