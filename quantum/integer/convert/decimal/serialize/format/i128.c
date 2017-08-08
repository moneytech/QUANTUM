// =============================================================================
// <integer/convert/decimal/serialize/format/i128.c>
//
// 128-bit+ integer to decimal string formatting template.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

if (true)
{
  #include "intro.c"

#if CPU(SSE2)
  while (len > 15u)
  {
    int_to_dig16 (ptr + len - 16, uv % 10000000000000000u);
    uv /= 10000000000000000u;

    len -= 16u;
  }
#endif

#if CPU(SSE2)
  if (len > 7u)
#else
  while (len > 7u)
#endif
  {
    int_to_dig2 (ptr + len - 2, uv % 100u);
    uv /= 100u;

    int_to_dig2 (ptr + len - 4, uv % 100u);
    uv /= 100u;

    int_to_dig2 (ptr + len - 6, uv % 100u);
    uv /= 100u;

    int_to_dig2 (ptr + len - 8, uv % 100u);
    uv /= 100u;

    len -= 8u;
  }

  int_tail_dig4 (ptr, uv);

  #include "outro.c"
}

// -----------------------------------------------------------------------------

#include "outro.h"
