// =============================================================================
// <string/search/string/forward/generic.c>
//
// Portable code for searching the contents of a buffer
// for a byte sequence.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../../support/intro.h"

// -----------------------------------------------------------------------------

if (true)
{
  if (unlikely (subsz == 0))
  {
#if T(SPAN)
    return 0;
#else
    return (t_char*)buf;
#endif
  }

  const t_char* b = buf;
  size_t bsz = bufsz;

#if T(INVERT)

  while (bsz >= subsz)
  {
    if (!t_str_equal (b, sub, subsz))
    {
  #if T(SPAN)
      return (size_t)(b - buf);
  #else
      return (t_char*)b;
  #endif
    }

    b += subsz;
    bsz -= subsz;
  }

  if (likely (bsz != 0))
  {
  #if T(SPAN)
    return (size_t)(b - buf);
  #else
    return (t_char*)b;
  #endif
  }

#else // T(INVERT) ][

  const t_char* s = sub;
  size_t ssz = subsz;

  t_char c = s[0];
  const t_char* p;

  s++;
  ssz--;

  while ((bsz > ssz) && ((p = t_str_find_chr (b, bsz, c)) != null))
  {
    p++;

    if (t_str_equal (p, s, ssz))
    {
      p--;

  #if T(SPAN)
      return (size_t)(b - buf);
  #else
      return (t_char*)p;
  #endif
    }

    bsz -= (size_t)(p - b);
    b = p;
  }

#endif // !T(INVERT)

#if T(SPAN)
  return bufsz;
#else
  return null;
#endif
}

// -----------------------------------------------------------------------------

#undef T_SPAN
#undef T_INVERT

#undef T_ICASE
#undef t_str_find_chr
#undef t_str_equal

// -----------------------------------------------------------------------------

#include "../../../support/outro.h"
