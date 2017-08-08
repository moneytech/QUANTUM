// =============================================================================
// <integer/convert/decimal/deserialize/implicit/i128.c>
//
// 128-bit+ decimal null-terminated string to integer conversion template.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "intro.h"

// -----------------------------------------------------------------------------

if (true)
{
  #include "intro.c"

#if T(VALID) && (!HAVE(INT64) || !HAVE(INT32) || !HAVE(INT16))
  // Vectorization is not available or is not feasible
  int_from_str (val, str, str + T_MAXDIG - 1, {c = *str; goto invalid;});
  goto outro;
#endif

  // Parse until the alignment is satisfied
#if CPU(SSE2)
  t_stri_align (16u);
#else
  t_stri_align (8u);
#endif

#if CPU(SSE41) && CPU(64BIT)
  // 32 digits
  if (true)
  {
    int_from_dig (val, str, 32, 10000000000000000u * 10000000000000000u,
    {
      val = int_from_dig31v (str, n);

  #if T(VALID)
      c = str[n];
      str += n;

      goto invalid;
  #else
      goto done;
  #endif
    });

    str += 32u;

  #if T(VALID)
    len += 32u;
  #endif
  }
#endif

#if CPU(SSE2)
  // 16 digits
  #if T(VALID)
    while (len < T_MAXDIG - 16u)
  #else
    while (true)
  #endif
  {
    int_from_dig (val, str, 16, 10000000000000000u,
    {
      val = int_from_dig15v (str, n);

  #if T(VALID)
      c = str[n];
      str += n;

      goto invalid;
  #else
      goto done;
  #endif
    });

    str += 16u;

  #if T(VALID)
    len += 16u;
  #endif
  }
#endif

  // 8 digits
#if T(VALID)
  while (len < T_MAXDIG - 8u)
#else
  while (true)
#endif
  {
    int_from_digi (val, str, 8, 100000000u, {goto skip;});

    str += 8u;

#if T(VALID)
    len += 8u;
#endif
  }

#if T(VALID)
  // Remaining 4 digits
  if (len < T_MAXDIG - 4u)
  {
    int_from_digi (val, str, 4, 10000u, {goto skip;});

    str += 4u;
    len += 4u;
  }

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
