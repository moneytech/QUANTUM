// =============================================================================
// <integer/convert/hexadecimal/deserialize/explicit/i32.c>
//
// 32-bit+ hexadecimal string to integer conversion template.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "intro.h"

// -----------------------------------------------------------------------------

if (true)
{
  #include "intro.c"

#if T(VALID) && (!CPU(UNALIGNED_ACCESS) || !HAVE(INT32) || !HAVE(INT16))
  // Vectorization is not available or is not feasible
  int_from_xstr (val, str, str + len, {goto invalid;});
  goto outro;
#endif

  // 4 digits
  while (len >= 4u)
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
