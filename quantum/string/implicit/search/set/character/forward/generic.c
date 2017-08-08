// =============================================================================
// <string/implicit/search/set/character/forward/generic.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../../../../support/intro.h"

// -----------------------------------------------------------------------------

#if !T(ICASE)
  #define t_chr_to_case nop
#endif

// -----------------------------------------------------------------------------

if (true)
{
#if T(TOKEN)
  t_char* str = *st;
  t_char* b = str;
#else
  const t_char* b = str;
#endif

#if T(LIMIT)
    const t_char* e = str + max;

    while ((b != e) && (*b != '\0'))
#else
    while (*b != '\0')
#endif
  {
    const t_char* s = set;

    while (*s != '\0')
    {
      if (t_chr_to_case (*b) == t_chr_to_case (*s))
      {
#if T(INVERT)
        goto next;
#else
  #if T(INDEX)
        *idx = (size_t)(s - set);
  #endif

  #if T(TOKEN)
        *b = '\0';
        *st = b + 1;

        return str;
  #elif T(SPAN)
        return (size_t)(b - str);
  #else
        return (t_char*)b;
  #endif
#endif
      }

      s++;
    }

#if T(INVERT)
  #if T(SPAN)
      return (size_t)(b - str);
  #else
      return (t_char*)b;
  #endif
#endif

next:
    b++;
  }

#if T(SPAN)
  return (size_t)(b - str);
#else
  return null;
#endif
}

// -----------------------------------------------------------------------------

#undef T_TOKEN
#undef T_INDEX

#undef T_SPAN
#undef T_LIMIT
#undef T_INVERT

#undef T_ICASE
#undef t_chr_to_case

// -----------------------------------------------------------------------------

#include "../../../../../support/outro.h"
