// =============================================================================
// <string/implicit/replace/set/character/generic.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../../../support/intro.h"

// -----------------------------------------------------------------------------

#if !T(ICASE)
  #define t_chr_to_case nop
#endif

// -----------------------------------------------------------------------------

if (true)
{
  t_char* s = str;

  #if T(LIMIT)
    const t_char* e = str + max;

    while (s != e)
  #else
    while (true)
  #endif
  {
    if (*s == '\0') break;

    const t_char* o = old;

    while (*o != '\0')
    {
      if (t_chr_to_case (*s) == t_chr_to_case (*o))
      {
        *s = new[o - old];
        goto next;
      }

      o++;
    }

next:
    s++;
  }

  return s;
}

// -----------------------------------------------------------------------------

#undef T_LIMIT

#undef T_ICASE
#undef t_chr_to_case

// -----------------------------------------------------------------------------

#include "../../../../support/outro.h"
