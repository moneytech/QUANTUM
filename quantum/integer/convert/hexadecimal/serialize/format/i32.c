// =============================================================================
// <integer/convert/hexadecimal/serialize/format/i32.c>
//
// 32-bit+ integer to hexadecimal string formatting template.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

if (true)
{
  #include "intro.c"

#if CPU(SSE2)
  if (len == 8u)
  {
    int_to_xdig8f (ptr + len - 8, uv & 0xFFFFFFFFu, lc);
    goto outro;
  }
#endif

#if CPU(SSE2)
  if (len > 3u)
#else
  while (len > 3u)
#endif
  {
    int_to_xdig4f (ptr + len - 4, uv & 0xFFFFu, lc);
    uv <<= 16;

    len -= 4u;
  }

  int_tail_xdig3 (ptr, uv, lc);

  #include "outro.c"
}

// -----------------------------------------------------------------------------

#include "outro.h"
