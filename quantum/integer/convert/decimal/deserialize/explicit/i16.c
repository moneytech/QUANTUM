// =============================================================================
// <integer/convert/decimal/deserialize/explicit/i16.c>
//
// 16-bit+ decimal string to integer conversion template.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

if (true)
{
  #include "intro.c"

#if T(VALID) && (!CPU(UNALIGNED_ACCESS) || !HAVE(INT16))
  // Vectorization is not available or is not feasible
  int_from_str (val, str, str + len, {goto invalid;});
  goto outro;
#endif

  // 2 digits
  while (len >= 2u)
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
