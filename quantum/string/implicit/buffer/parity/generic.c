// =============================================================================
// <string/implicit/buffer/parity/generic.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../../support/intro.h"

// -----------------------------------------------------------------------------

#if !T(ICASE)
  #define t_chr_to_case nop
#endif

// -----------------------------------------------------------------------------

if (true)
{
  size_t i = 0;
  size_t n = 0;

#if T(LIMIT)
  for (i; i != max; i++)
#else
  for (i; i; i++)
#endif
  {
    t_char c1 = str1[i];
    t_char c2 = str2[i];

    if (unlikely ((c1 == '\0') || (c2 == '\0'))) break;

#if T(ICASE)
    c1 = t_chr_to_case (c1);
    c2 = t_chr_to_case (c2);
#endif

    n += (c1 == c2);
  }

  return n;
}

// -----------------------------------------------------------------------------

#undef T_LIMIT

#undef T_ICASE
#undef t_chr_to_case

// -----------------------------------------------------------------------------

#include "../../../support/outro.h"
