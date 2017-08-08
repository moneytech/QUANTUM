// =============================================================================
// <string/string/parity/generic.c>
//
// Portable code for calculating the number of equal bytes between two buffers.
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
  const t_char* b1 = buf1;
  const t_char* b2 = buf2;

  size_t num = 0;
  size_t i = 0;
  size_t j;

#if !T(ICASE) && (T_CHAR_BIT == 8)\
&& ((T_WORD_BIT == 16) || (T_WORD_BIT == 32) || (T_WORD_BIT == 64))

  #if (CPU(UNALIGNED_ACCESS) && T(PREALIGN)) || !CPU(UNALIGNED_ACCESS)
    #if (T_WORD_BIT == 16)
      size_t x = (uintptr_t)b1 & 1u;
    #else
      size_t x = (sizeof (t_word) - ((uintptr_t)b1 & (sizeof (t_word) - 1u))) & (sizeof (t_word) - 1u);
    #endif

    if (unlikely (x >= size)) goto tail;

    #if (T_WORD_BIT == 16)
      if (likely (x != 0))
    #else
      while (i != x)
    #endif
    {
      num += (b1[i] == b2[i]);
      i++;
    }

    #if !CPU(UNALIGNED_ACCESS)
      if (likely ((uintptr_t)(b2 + i) & (sizeof (t_word) - 1u))) goto tail;
    #endif

    size_t n = size_align_floor (sizeof (t_word), size - i);

resume:
    for (i; i < n; i += sizeof (t_word))
  #else
    size_t n = size_align_floor (sizeof (t_word), size);

resume:
    for (i; i != n; i += sizeof (t_word))
  #endif
  {
    if (*(const t_word*)(b1 + i) != *(const t_word*)(b2 + i)) goto match;
    num += sizeof (t_word);
  }

#endif

tail:
  for (i; i != size; i++)
  {
    t_char c1 = t_chr_to_case (b1[i]);
    t_char c2 = t_chr_to_case (b2[i]);

    num += (c1 == c2);
  }

  return num;

#if !T(ICASE)
match:
  j = i + sizeof (t_word);

  do
  {
    num += (b1[i] == b2[i]);
    i++;
  }
  while (i != j);

  goto resume;
#endif
}

// -----------------------------------------------------------------------------

#undef T_PREALIGN

#undef T_ICASE
#undef t_chr_to_case

// -----------------------------------------------------------------------------

#include "../../support/outro.h"
