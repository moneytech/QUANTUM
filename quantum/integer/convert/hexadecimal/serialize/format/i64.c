// =============================================================================
// <integer/convert/hexadecimal/serialize/format/i64.c>
//
// 64-bit+ integer to hexadecimal string formatting template.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

if (true)
{
  #include "intro.c"

#if CPU(SSE2)
  if (len == 16u)
  {
    int_to_xdig16f (ptr + len - 16, uv & 0xFFFFFFFFFFFFFFFFu, lc);
    goto outro;
  }
#endif

#if CPU(SSE2)
  if (len > 7u)
#else
  while (len > 7u)
#endif
  {
    int_to_xdig8f (ptr + len - 8, uv & 0xFFFFFFFFu, lc);
    uv <<= 32;

    len -= 8u;
  }

  int_tail_xdig4 (ptr, uv, lc);

  #include "outro.c"
}

// -----------------------------------------------------------------------------

#include "outro.h"
