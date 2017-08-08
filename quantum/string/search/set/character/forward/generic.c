// =============================================================================
// <string/search/set/character/forward/generic.c>
//
// Portable code for searching the contents of a buffer
// for a set of bytes.
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
  const t_char* b = buf;

  const t_char* eb = buf + bufsz;
  const t_char* es = set + setsz;

  while (b != eb)
  {
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
        return (size_t)(b - buf);
  #else
        return (t_char*)b;
  #endif
#endif
      }

      s++;
    }

#if T(INVERT)
  #if T(SPAN)
    return (size_t)(b - buf);
  #else
    return (t_char*)b;
  #endif
#endif

next:
    b++;
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
