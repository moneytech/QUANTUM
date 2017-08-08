// =============================================================================
// <integer/convert/decimal/deserialize/explicit/i64.c>
//
// 64-bit+ decimal string to integer conversion template.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

if (true)
{
  #include "intro.c"

#if T(VALID) && (!CPU(UNALIGNED_ACCESS)\
|| !HAVE(INT64) || !HAVE(INT32) || !HAVE(INT16))
  // Vectorization is not available or is not feasible
  int_from_str (val, str, str + len, {goto invalid;});
  goto outro;
#endif

#if CPU(SSE2)
  // 16 digits
  if (len >= 16u)
  {
  #if T(VALID)
    int_from_dig (val, str, 16, 0,
    {
      val = int_from_dig15v (str, n);
      str += n;

      goto invalid;
    });
  #else
    val = int_from_dig16 (str);
  #endif

    str += 16u;
    len -= 16u;

  #if T(SIGN)
    goto digits2;
  #else
    goto digits4;
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
    int_from_digi (val, str, 8, 0, {goto skip;});
  #else
    int_from_digi (val, str, 8, 100000000u, {goto skip;});
  #endif
#else
  #if CPU(SSE2)
    val = int_from_dig8 (str);
  #else
    val = (val * 100000000u) + int_from_dig8 (str);
  #endif
#endif

    str += 8u;
    len -= 8u;
  }

  // Remaining 4 digits
digits4:
  if (len >= 4u)
  {
#if T(VALID)
    int_from_digi (val, str, 4, 10000u, {goto skip;});
#else
    val = (val * 10000u) + int_from_dig4 (str);
#endif

    str += 4u;
    len -= 4u;
  }

  // Remaining 2 digits
digits2:
  if (len >= 2u)
  {
#if T(VALID)
    int_from_digi (val, str, 2, 100u, {goto skip;});
#else
    val = (val * 100u) + int_from_dig2 (str);
#endif

    str += 2u;
    len -= 2u;
  }

  // Last digit
  if (len != 0)
  {
#if T(VALID)
    if (unlikely (!chr_is_dig (*str))) goto invalid;
#endif

    val = (val * 10u) + chr_dig_to_int (*str);

#if T(VALID)
    str++;
#endif
  }

  #include "outro.c"
}

// -----------------------------------------------------------------------------

#include "outro.h"
