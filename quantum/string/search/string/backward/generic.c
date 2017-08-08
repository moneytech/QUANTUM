// =============================================================================
// <string/search/string/backward/generic.c>
//
// Portable code for searching the contents of a buffer
// for a byte sequence in reverse direction.
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
    return (t_char*)(buf + bufsz);
#endif
  }

  size_t bsz = bufsz;

#if T(INVERT)

  const t_char* b = buf + bufsz;

  while (bsz >= subsz)
  {
    b -= subsz;
    bsz -= subsz;

    if (!t_str_equal (b, sub, subsz))
    {
  #if T(SPAN)
      return (bufsz - (size_t)(b - buf)) - subsz;
  #else
      return (t_char*)b;
  #endif
    }
  }

  if (likely (bsz != 0))
  {
  #if T(SPAN)
    return (bufsz - (size_t)(b - buf)) - subsz;
  #else
    return (t_char*)b;
  #endif
  }

#else // T(INVERT) ][

  const t_char* b = buf;

  const t_char* s = sub;
  size_t ssz = subsz;

  t_char c = s[0];
  const t_char* p;

  s++;
  ssz--;

  while ((bsz > ssz) && ((p = t_str_rfind_chr (b, c, bsz)) != null))
  {
    if (t_str_equal (p + 1, s, ssz))
    {
  #if T(SPAN)
      return (bufsz - (size_t)(p - b)) - subsz;
  #else
      return (t_char*)p;
  #endif
    }

    bsz = (size_t)(p - b);
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
#undef t_str_rfind_chr
#undef t_str_equal

// -----------------------------------------------------------------------------

#include "../../../support/outro.h"
