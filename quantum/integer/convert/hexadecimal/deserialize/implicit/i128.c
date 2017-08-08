// =============================================================================
// <integer/convert/hexadecimal/deserialize/implicit/i128.c>
//
// 128-bit+ hexadecimal null-terminated string to integer conversion template.
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
  #if T(UNEVEN)
    int_from_xstr (val, str, str + T_MAXDIG - 1, {c = *str; goto invalid;});
  #else
    int_from_xstr (val, str, str + T_MAXDIG, {c = *str; goto invalid;});
  #endif

  goto outro;
#endif

  // Parse until the alignment is satisfied
#if CPU(SSE2)
  if (!ptr_aligned (16u, str))
  {
    t_stri_align (16u);
    goto digits16;
  }
#else
  t_stri_align (8u);
#endif

#if CPU(SSE2)
  // 32 digits
  #if CPU(64BIT)
    if (true)
    {
      int_from_xdig (val, str, 32, 0,
      {
        val = int_from_xdig31v (str, n);

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

digits16:
  // 16 digits
  #if T(VALID)
    while (len < T_MAXDIG - 16u)
  #else
    while (true)
  #endif
  {
    int_from_xdig (val, str, 16, 64,
    {
      val = int_from_xdig15v (str, n);

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
    int_from_xdigi (val, str, 8, 32, {goto skip;});

    str += 8u;

#if T(VALID)
    len += 8u;
#endif
  }

#if T(VALID)
  // Remaining 4 digits
  if (len < T_MAXDIG - 4u)
  {
    int_from_xdigi (val, str, 4, 16, {goto skip;});

    str += 4u;
    len += 4u;
  }

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
