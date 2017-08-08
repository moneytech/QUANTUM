// =============================================================================
// <string/replace/set/string/generic.c>
//
// Portable code for replacing a set of byte sequences with another in a buffer.
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
  vla (t_char, cset, setsz);
  size_t i = setsz;

  while (i--)
  {
    if (unlikely (old[i].len == 0)) cset[i] = '\0';
    else cset[i] = old[i].buf[0];
  }

  t_char* b = buf;

  const t_char* eb = buf + bufsz;
  const t_char* es = cset + setsz;

next:
  while (b != eb)
  {
    const t_char* s = cset;

    while (s != es)
    {
      if (t_chr_to_case (*b) == t_chr_to_case (*s))
      {
        if (unlikely (old[i].len == 0)) goto skip;

        size_t i = (size_t)(s - cset);
        size_t sz = bufsz - (size_t)(b - buf);

        if ((sz >= old[i].len) && t_str_equal (b + 1, old[i].buf + 1, old[i].len - 1u))
        {
#if T(REMOVE)
          t_str_copy (b, b + old[i].len, (size_t)(eb - b) - old[i].len);
          eb -= old[i].len;
#else
          t_str_copy (b, new[i], old[i].len);
          b += old[i].len;
#endif

          goto next;
        }
      }

skip:
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
#undef t_str_equal

#undef T_REMOVE
#undef t_str_copy

// -----------------------------------------------------------------------------

#include "../../../support/outro.h"
