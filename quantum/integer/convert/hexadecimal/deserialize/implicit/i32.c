// =============================================================================
// <integer/convert/hexadecimal/deserialize/implicit/i32.c>
//
// 32-bit+ hexadecimal null-terminated string to integer conversion template.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "intro.h"

// -----------------------------------------------------------------------------

if (true)
{
  #include "intro.c"

#if T(VALID) && (!HAVE(INT32) || !HAVE(INT16))
  // Vectorization is not available or is not feasible
  #if T(UNEVEN)
    int_from_xstr (val, str, str + T_MAXDIG - 1, {c = *str; goto invalid;});
  #else
    int_from_xstr (val, str, str + T_MAXDIG, {c = *str; goto invalid;});
  #endif

  goto outro;
#endif

  // Parse until the alignment is satisfied
  t_stri_align (4u);

  // 4 digits
#if T(VALID)
  while (len < T_MAXDIG - 4u)
#else
  while (true)
#endif
  {
    int_from_xdigi (val, str, 4, 16, {goto skip;});

    str += 4u;

#if T(VALID)
    len += 4u;
#endif
  }

#if T(VALID)
  // Remaining 2 digits
  if (len < T_MAXDIG - 2u)
  {
    int_from_xdigi (val, str, 2, 8, {goto skip;});

    str += 2u;
    len += 2u;
  }

  // Last digit
  if (len != T_MAXDIG - 1u)
  {
    c = *str;

    if (unlikely (!chr_is_xdig (c))) goto invalid;

    val = (val << 4) + chr_xdig_to_int_fast (c);

    str++;
  }
#endif

  #include "outro.c"
}

// -----------------------------------------------------------------------------

#include "outro.h"
