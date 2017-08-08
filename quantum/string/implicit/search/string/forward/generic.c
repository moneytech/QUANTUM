// =============================================================================
// <string/implicit/search/string/forward/generic.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../../../support/intro.h"

// -----------------------------------------------------------------------------

if (true)
{
#if T(INVERT)
  size_t l = stri_length (sub);

  if (unlikely (l == 0))
  {
  #if T(SPAN)
    return 0;
  #else
    return (t_char*)str;
  #endif
  }

  const t_char* s = str;

  while (true)
  {
    size_t p = t_stri_prefix (s, sub);

    if (p != l)
    {
  #if T(SPAN)
      return (size_t)(s - str);
  #else
      return (t_char*)s;
  #endif
    }

    s += l;
  }

#else // T(INVERT) ][

  #if T(TOKEN)
    t_char* str = *st;
    t_char* s;
  #else
    const t_char* s;
  #endif

  t_char c = *sub++;

  if (unlikely (c == '\0'))
  {
  #if T(TOKEN)
    return null;
  #elif T(SPAN)
    return 0;
  #else
    return (t_char*)str;
  #endif
  }

  while (true)
  {
  #if T(LIMIT)
    s = t_stri_nfind_chr (str, max, c);
  #else
    s = t_stri_find_chr (str, c);
  #endif

    if (s == null) break;

  #if T(LIMIT)
    max -= (size_t)(s - str) + 1u;

    if (max == 0) break;
  #endif

    str = s + 1;

  #if T(LIMIT)
    size_t p = t_stri_nprefix (str, max, sub);
  #else
    size_t p = t_stri_prefix (str, sub);
  #endif

    if (sub[p] == '\0')
    {
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

#endif // !T(INVERT)

#if T(SPAN)
  return (size_t)(s - str);
#else
  return null;
#endif
}

// -----------------------------------------------------------------------------

#undef T_TOKEN

#undef T_SPAN
#undef T_INVERT

#undef T_ICASE
#undef t_stri_find_chr
#undef t_stri_prefix

#undef T_LIMIT
#undef t_stri_nfind_chr
#undef t_stri_nprefix

// -----------------------------------------------------------------------------

#include "../../../../support/outro.h"
