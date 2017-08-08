// =============================================================================
// <integer/convert/hexadecimal/deserialize/explicit/i64.c>
//
// 64-bit+ hexadecimal string to integer conversion template.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "intro.h"

// -----------------------------------------------------------------------------

if (true)
{
  #include "intro.c"

#if T(VALID) && (!CPU(UNALIGNED_ACCESS)\
|| !HAVE(INT64) || !HAVE(INT32) || !HAVE(INT16))
  // Vectorization is not available or is not feasible
  int_from_xstr (val, str, str + len, {goto invalid;});
  goto outro;
#endif

#if CPU(SSE2)
  // 16 digits
  if (len == 16u)
  {
  #if T(VALID)
    int_from_xdig (val, str, 16, 0,
    {
      val = int_from_xdig15v (str, n);
      str += n;

      goto invalid;
    });

    str += 16u;
    len -= 16u;

    goto outro;
  #else
    val = int_from_xdig16 (str);
    goto done;
  #endif
  }
#endif

  // 8 digits
#if CPU(SSE2)
  if (len >= 8u)
#else
  while (len >= 8u)
#endif
  {
#if T(VALID)
  #if CPU(SSE2)
    int_from_xdigi (val, str, 8, 0, {goto skip;});
  #else
    int_from_xdigi (val, str, 8, 32, {goto skip;});
  #endif
#else
  #if CPU(SSE2)
    val = int_from_xdig8v (str);
  #else
    val = (val << 32) + int_from_xdig8v (str);
  #endif
#endif

    str += 8u;
    len -= 8u;
  }

  // Remaining 4 digits
  if (len >= 4u)
  {
#if T(VALID)
    int_from_xdigi (val, str, 4, 16, {goto skip;});
#else
    val = (val << 16) + int_from_xdig4 (str);
#endif

    str += 4u;
    len -= 4u;
  }

  // Remaining 2 digits
  if (len >= 2u)
  {
#if T(VALID)
    int_from_xdigi (val, str, 2, 8, {goto skip;});
#else
    val = (val << 8) + int_from_xdig2 (str);
#endif

    str += 2u;
    len -= 2u;
  }

  // Last digit
  if (len != 0)
  {
#if T(VALID)
    if (unlikely (!chr_is_xdig (*str))) goto invalid;
#endif

    val = (val << 4) + chr_xdig_to_int_fast (*str);

#if T(VALID)
    str++;
#endif
  }

  #include "outro.c"
}

// -----------------------------------------------------------------------------

#include "outro.h"
