// =============================================================================
// <string/search/set/character/backward/generic.c>
//
// Portable code for searching the contents of a buffer
// for a set of bytes in reverse direction.
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
  const t_char* b = buf + bufsz;
  const t_char* es = set + setsz;

next:
  while (b != buf)
  {
    b--;

    const t_char* s = set;

    while (s != es)
    {
      if (t_chr_to_case (*b) == t_chr_to_case (*s))
      {
#if T(INVERT)
        goto next;
#else
  #if T(INDEX)
        *idx = (size_t)(s - set);
  #endif

  #if T(SPAN)
        return (bufsz - (size_t)(b - buf)) - 1u;
  #else
        return (t_char*)b;
  #endif
#endif
      }

      s++;
    }

#if T(INVERT)
  #if T(SPAN)
    return (bufsz - (size_t)(b - buf)) - 1u;
  #else
    return (t_char*)b;
  #endif
#endif
  }

#if T(SPAN)
  return bufsz;
#else
  return null;
#endif
}

// -----------------------------------------------------------------------------

#undef T_SPAN
#undef T_INVERT
#undef T_INDEX

#undef T_ICASE
#undef t_chr_to_case

// -----------------------------------------------------------------------------

#include "../../../../support/outro.h"
