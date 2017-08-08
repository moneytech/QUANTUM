// =============================================================================
// <string/replace/string/generic.c>
//
// Portable code for replacing a byte sequence with another in a buffer.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../support/intro.h"

// -----------------------------------------------------------------------------

if (true)
{
  if (unlikely (subsz == 0))
  {
#if T(REMOVE)
    return bufsz;
#else
    return;
#endif
  }

  const t_char* b = buf;
  size_t bsz = bufsz;

  const t_char* s = old;
  size_t ssz = subsz;

  t_char c = s[0];
  t_char* p;

  s++;
  ssz--;

  while ((bsz > ssz) && ((p = t_str_find_chr (b, bsz, c)) != null))
  {
    if (t_str_equal (p + 1, s, ssz))
    {
      bsz -= (size_t)(p - b) + 1u + ssz;

#if T(REMOVE)
      t_str_copy (p, p + 1 + ssz, bsz);
      b = p;
#else
      t_str_copy (p, new, 1u + ssz);
      b = p + 1 + ssz;
#endif
    }
    else
    {
      p++;
      bsz -= (size_t)(p - b);
      b = p;
    }
  }

#if T(REMOVE)
  return (size_t)(b - buf) + bsz;
#endif
}

// -----------------------------------------------------------------------------

#undef T_ICASE
#undef t_str_find_chr
#undef t_str_equal

#undef T_REMOVE
#undef t_str_copy

// -----------------------------------------------------------------------------

#include "../../support/outro.h"
