// =============================================================================
// <integer/convert/decimal/serialize/format/i32.c>
//
// 32-bit+ integer to decimal string formatting template.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

if (true)
{
  #include "intro.c"

#if (INT_FAST32_BIT == 32) && CPU(64BIT)
  if (len > 7u)
  {
    int_to_dig8 (ptr + len - 8, uv % 100000000u);
    uv /= 100000000u;

    len -= 8u;

    int_tail_dig2 (ptr, uv);

    goto outro;
  }
#endif

#if (INT_FAST32_BIT == 32) && CPU(64BIT)
  if (len > 3u)
#else
  while (len > 3u)
#endif
  {
    int_to_dig2 (ptr + len - 2, uv % 100u);
    uv /= 100u;

    int_to_dig2 (ptr + len - 4, uv % 100u);
    uv /= 100u;

    len -= 4u;
  }

  int_tail_dig2 (ptr, uv);

  #include "outro.c"
}

// -----------------------------------------------------------------------------

#include "outro.h"
