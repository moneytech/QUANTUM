// =============================================================================
// <integer/convert/decimal/deserialize/implicit/i16.c>
//
// 16-bit+ decimal null-terminated string to integer conversion template.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "intro.h"

// -----------------------------------------------------------------------------

if (true)
{
  #include "intro.c"

#if T(VALID) && !HAVE(INT16)
  // Vectorization is not available or is not feasible
  int_from_str (val, str, str + T_MAXDIG - 1, {c = *str; goto invalid;});
  goto outro;
#endif

  // Parse until the alignment is satisfied
  t_stri_align (2u);

  // 2 digits
#if T(VALID)
  while (len < T_MAXDIG - 2u)
#else
  while (true)
#endif
  {
    int_from_digi (val, str, 2, 100u, {goto skip;});

    str += 2u;

#if T(VALID)
    len += 2u;
#endif
  }

#if T(VALID)
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
