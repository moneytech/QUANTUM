// =============================================================================
// <string/implicit/search/set/string/forward/generic.c>
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
  t_char* s = str;
#else
  const t_char* s = str;
#endif

  size_t c = arri_length ((const void* const*)set);
  vla (size_t, lset, c);

#if !T(INVERT)
  vla (t_char, cset, c);
#endif

  size_t i = c;

  while (i--)
  {
    size_t len = lset[i] = stri_length (set[i]);

#if !T(INVERT)
    if (unlikely (len == 0))
    {
  #if T(TOKEN)
      return null;
  #elif T(SPAN)
      return 0;
  #else
      return (t_char*)s;
  #endif
    }

    cset[i] = t_chr_to_case (set[i][0]);
#endif
  }

#if T(INVERT)

  while (true)
  {
    size_t l = 0;

    for (i = 0; i != c; i++)
    {
      size_t len = lset[i];

  #if T(LIMIT)
      if (t_stri_nprefix (s, max, set[i]) == lset[i])
  #else
      if (t_stri_prefix (s, set[i]) == lset[i])
  #endif
      {
        l = lset[i];
        break;
      }
    }

    if (l == 0)
    {
  #if T(SPAN)
      return (size_t)(s - str);
  #else
      return (*s == '\0') ? null : (t_char*)s;
  #endif
    }

    s += l;

  #if T(LIMIT)
    max -= l;
  #endif
  }

#else // T(INVERT) ][

  #if T(LIMIT)
    const chat_t* e = s + max;

    while ((s != e) && (*s != '\0'))
  #else
    while (*s != '\0')
  #endif
  {
    for (i = 0; i != c; i++)
    {
      if (t_chr_to_case (*s) == cset[i])
      {
  #if T(LIMIT)
        size_t p = t_stri_nprefix (s, max, set[i]);
  #else
        size_t p = t_stri_prefix (s, set[i]);
  #endif

        if (set[i][p] == '\0')
        {
  #if T(INDEX)
          *idx = i;
  #endif

  #if T(TOKEN)
          *s = '\0';
          *st = s + p;

          return str;
  #elif T(SPAN)
          return (size_t)(s - str);
  #else
          return (t_char*)s;
  #endif
        }
      }
    }

    s++;
  }

#endif // !T(INVERT)

#if T(SPAN)
  return (size_t)(s - str);
#else
  return null;
#endif
}

// -----------------------------------------------------------------------------

#undef T_TOKEN
#undef T_INDEX

#undef T_SPAN
#undef T_INVERT

#undef T_ICASE
#undef t_chr_to_case
#undef t_stri_prefix

#undef T_LIMIT
#undef t_stri_nprefix

// -----------------------------------------------------------------------------

#include "../../../../../support/outro.h"
