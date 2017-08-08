// =============================================================================
// <string/replace/set/character/generic.c>
//
// Portable code for replacing a set of bytes with another in a buffer.
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
  t_char* b = buf;

  const t_char* eb = buf + bufsz;
  const t_char* es = old + setsz;

#if T(REMOVE)
next:
#endif
  while (b != eb)
  {
    const t_char* s = old;

    while (s != es)
    {
      if (t_chr_to_case (*b) == t_chr_to_case (*s))
      {
#if T(REMOVE)
        t_str_copy (b, b + 1, (size_t)(eb - b) - 1u);
        eb--;

        goto next;
#else
        *b = new[s - old];
#endif

        break;
      }

      s++;
    }

    b++;
  }

#if T(REMOVE)
  return (size_t)(eb - b);
#endif
}

// -----------------------------------------------------------------------------

#undef T_ICASE
#undef t_chr_to_case

#undef T_REMOVE
#undef t_str_copy

// -----------------------------------------------------------------------------

#include "../../../support/outro.h"
