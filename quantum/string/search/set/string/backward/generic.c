// =============================================================================
// <string/search/set/string/backward/generic.c>
//
// Portable code for searching the contents of a buffer
// for a set of byte sequences in reverse direction.
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
#if T(INVERT)

  const t_char* b = buf + bufsz;
  size_t bsz = bufsz;

  while (true)
  {
    size_t l = 0;

    for (size_t i = 0; i < setsz; i++)
    {
      if ((bsz >= set[i].len)
      && t_str_equal (b - set[i].len, set[i].buf, set[i].len))
      {
        l = set[i].len;
        break;
      }
    }

    if (l == 0)
    {
  #if T(SPAN)
      return bufsz - (size_t)(b - buf);
  #else
      return (bsz == 0) ? null : (t_char*)b;
  #endif
    }

    b -= l;
    bsz -= l;
  }

#else // T(INVERT) ][

  vla (t_char, cset, setsz);
  size_t i = setsz;

  while (i--)
  {
    if (unlikely (set[i].len == 0))
    {
  #if T(SPAN)
      return 0;
  #else
      return (t_char*)(buf + bufsz);
  #endif
    }

    cset[i] = set[i].buf[0];
  }

  const t_char* es = cset + setsz;
  size_t bsz = bufsz;

  while (bsz != 0)
  {
    bsz--;

    const t_char* s = cset;

    while (s != es)
    {
      if (t_chr_to_case (buf[bsz]) == t_chr_to_case (*s))
      {
        size_t i = (size_t)(s - cset);
        size_t sz = bufsz - bsz;

        if ((sz >= set[i].len)
        && t_str_equal (buf + bsz + 1, set[i].buf + 1, set[i].len - 1u))
        {
  #if T(INDEX)
          *idx = i;
  #endif

  #if T(SPAN)
          return (bufsz - bsz) - set[i].len;
  #else
          return (t_char*)(buf + bsz);
  #endif
        }
      }

      s++;
    }
  }

  #if T(SPAN)
    return bufsz;
  #else
    return null;
  #endif

#endif // !T(INVERT)
}

// -----------------------------------------------------------------------------

#undef T_SPAN
#undef T_INVERT
#undef T_INDEX

#undef T_ICASE
#undef t_chr_to_case
#undef t_str_equal

// -----------------------------------------------------------------------------

#include "../../../../support/outro.h"
