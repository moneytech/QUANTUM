// =============================================================================
// <string/buffer/reverse_copy/generic.c>
//
// Portable code for copying the contents of one buffer into another
// reversing the order of bytes in the process.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../support/intro.h"

// -----------------------------------------------------------------------------

if (true)
{
  t_char* restrict d = dst;

  const t_char* restrict ed = dst + size;
  const t_char* restrict es = src + size;

#if (T_CHAR_BIT == 8) && ((T_WORD_BIT == 16) || (T_WORD_BIT == 32) || (T_WORD_BIT == 64))

  #if (CPU(UNALIGNED_ACCESS) && T(PREALIGN)) || !CPU(UNALIGNED_ACCESS)
    #if (T_WORD_BIT == 16)
      size_t x = (uintptr_t)d & 1u;
    #else
      size_t x = (sizeof (t_word) - ((uintptr_t)d & (sizeof (t_word) - 1u))) & (sizeof (t_word) - 1u);
    #endif

    if (unlikely (x >= size)) goto tail;

    const t_char* restrict p = d + x;

    #if (T_WORD_BIT == 16)
      if (likely (x != 0))
    #else
      while (d != p)
    #endif
    {
      *d++ = *--es;
    }

    #if !CPU(UNALIGNED_ACCESS)
      if (likely ((uintptr_t)es & (sizeof (t_word) - 1u)))
      {
        p = d + size_align_floor (4u, size - x);

        while (d != p)
        {
          es -= 4;

          d[0] = es[3];
          d[1] = es[2];
          d[2] = es[1];
          d[3] = es[0];

          d += 4;
        }

        goto tail;
      }
    #endif

    p = d + size_align_floor (sizeof (t_word), size - x);

    while (d != p)
  #else
    const t_char* restrict p = d + size_align_floor (sizeof (t_word), size);

    while (d != p)
  #endif
  {
    es -= sizeof (t_word);

  #if (T_WORD_BIT == 16)
    *(t_word* restrict)d = bswap16 (*(t_word* restrict)es);
  #elif (T_WORD_BIT == 32)
    *(t_word* restrict)d = bswap32 (*(t_word* restrict)es);
  #elif (T_WORD_BIT == 64)
    *(t_word* restrict)d = bswap64 (*(t_word* restrict)es);
  #endif

    d += sizeof (t_word);
  }

#else

  const t_char* restrict p = d + size_align_floor (4u, size);

  while (d != p)
  {
    es -= 4;

    d[0] = es[3];
    d[1] = es[2];
    d[2] = es[1];
    d[3] = es[0];

    d += 4;
  }

#endif

tail:
  while (d != ed) *d++ = *--es;
}

// -----------------------------------------------------------------------------

#undef T_PREALIGN

// -----------------------------------------------------------------------------

#include "../../support/outro.h"
