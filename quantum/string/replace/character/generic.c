// =============================================================================
// <string/replace/character/generic.c>
//
// Portable code for replacing a particular byte with another in a buffer.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../support/intro.h"

// -----------------------------------------------------------------------------

#if !T(ICASE)
  #define t_chr_to_case nop
#endif

// -----------------------------------------------------------------------------

if (true)
{
#if T(REMOVE)

  const t_char* b = buf;
  size_t bsz = size;

  t_char* p;

  while ((bsz != 0) && ((p = t_str_find_chr (b, bsz, chr)) != null))
  {
    bsz -= (size_t)(p - b) + 1u;
    t_str_copy (p, p + 1, bsz);
    b = p;
  }

  return (size_t)(b - buf) + bsz;

#elif !T(ICASE) && (T_CHAR_BIT == 8)\
&& ((T_WORD_BIT == 16) || (T_WORD_BIT == 32) || (T_WORD_BIT == 64))

  size_t j;
  size_t i = 0;

  t_word v = (T_WORD_MAX / T_CHAR_MAX) * old;

  #if (CPU(UNALIGNED_ACCESS) && T(PREALIGN)) || !CPU(UNALIGNED_ACCESS)
    #if (T_WORD_BIT == 16)
      size_t x = (uintptr_t)buf & 1u;
    #else
      size_t x = (sizeof (t_word) - ((uintptr_t)buf & (sizeof (t_word) - 1u))) & (sizeof (t_word) - 1u);
    #endif

    if (unlikely (x >= size)) goto tail;

    #if (T_WORD_BIT == 16)
      if (likely (x != 0))
    #else
      while (i != x)
    #endif
    {
      if (buf[i] == old) buf[i] = new;
      i++;
    }

    size_t n = size_align_floor (sizeof (t_word), size - i);

resume:
    for (i; i < n; i += sizeof (t_word))
  #else
    size_t n = size_align_floor (sizeof (t_word), size);

resume:
    for (i; i != n; i += sizeof (t_word))
  #endif
  {
    t_word w = *(t_word*)(buf + i);

  #if (T_WORD_BIT == 16)
    if (swar_has_zero2 (w - v)) goto match;
  #elif (T_WORD_BIT == 32)
    if (swar_has_zero4 (w - v)) goto match;
  #elif (T_WORD_BIT == 64)
    if (swar_has_zero8 (w - v)) goto match;
  #endif
  }

tail:
  for (i; i != size; i++) if (buf[i] == old) buf[i] = new;

  return;

match:
  j = i + sizeof (t_word);

  do
  {
    if (buf[i] == old) buf[i] = new;
    i++;
  }
  while (i != j);

  goto resume;

#else

  t_char* b = buf;
  const t_char* e = buf + size;

  t_char c = t_chr_to_case (old);

  while (b != e)
  {
    if (t_chr_to_case (*b) == c) *b = new;
    b++;
  }

#endif
}

// -----------------------------------------------------------------------------

#undef T_PREALIGN

#undef T_ICASE
#undef t_chr_to_case
#undef t_str_find_chr

#undef T_REMOVE
#undef t_str_copy

// -----------------------------------------------------------------------------

#include "../../support/outro.h"
