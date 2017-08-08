// =============================================================================
// <string/implicit/buffer/compare/generic.c>
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

#if T(LIMIT)
  for (i; i != max; i++)
#else
  for (i; i; i++)
#endif
  {
    t_char c1 = str1[i];
    t_char c2 = str2[i];

    if (c1 != c2)
    {
  #if T(ICASE)
      c1 = t_chr_to_case (c1);
      c2 = t_chr_to_case (c2);

      if (c1 != c2)
  #endif
      {
  #if T(EQUALITY)
        return false;
  #elif T(SIMILARITY)
        return i;
  #else
        return (int)c1 - (int)c2;
  #endif
      }
    }

    if (unlikely (c1 == '\0'))
    {
  #if T(EQUALITY)
      return true;
  #elif T(SIMILARITY)
      return i;
  #else
      return 0;
  #endif
    }
  }

#if !T(LIMIT)
  assume_unreachable();
#endif

#if T(EQUALITY)
  return true;
#elif T(SIMILARITY)
  return i;
#else
  return 0;
#endif
}

// -----------------------------------------------------------------------------

#undef T_EQUALITY
#undef T_SIMILARITY

#undef T_LIMIT

#undef T_ICASE
#undef t_chr_to_case

// -----------------------------------------------------------------------------

#include "../../../support/outro.h"
