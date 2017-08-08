// =============================================================================
// <integer/convert/decimal/deserialize/implicit/i32.c>
//
// 32-bit+ decimal null-terminated string to integer conversion template.
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
  int_from_str (val, str, str + T_MAXDIG - 1, {c = *str; goto invalid;});
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
    int_from_digi (val, str, 4, 10000u, {goto skip;});

    str += 4u;

#if T(VALID)
    len += 4u;
#endif
  }

#if T(VALID)
  // Remaining 2 digits
  if (len < T_MAXDIG - 2u)
  {
    int_from_digi (val, str, 2, 100u, {goto skip;});

    str += 2u;
    len += 2u;
  }

  // Last digit
  if (len != T_MAXDIG - 1u)
  {
    c = *str;

    if (unlikely (!chr_is_dig (c))) goto invalid;

    val = (val * 10u) + chr_dig_to_int (c);

    str++;
  }
#endif

  #include "outro.c"
}

// -----------------------------------------------------------------------------

#include "outro.h"
