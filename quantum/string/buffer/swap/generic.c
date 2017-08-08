// =============================================================================
// <string/string/swap/generic.c>
//
// Portable code for exchanging the contents of two buffers
// without using an intermediate buffer.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../support/intro.h"

// -----------------------------------------------------------------------------

if (true)
{
  t_char* p1 = buf1;
  t_char* p2 = buf2;

  size_t i = 0;

#if (T_CHAR_BIT == 8) && ((T_WORD_BIT == 16) || (T_WORD_BIT == 32) || (T_WORD_BIT == 64))

  #if (CPU(UNALIGNED_ACCESS) && T(PREALIGN)) || !CPU(UNALIGNED_ACCESS)
    #if (T_WORD_BIT == 16)
      size_t x = (uintptr_t)p1 & 1u;
    #else
      size_t x = (sizeof (t_word) - ((uintptr_t)p1 & (sizeof (t_word) - 1u))) & (sizeof (t_word) - 1u);
    #endif

    if (unlikely (x >= size)) goto tail;

    #if (T_WORD_BIT == 16)
      if (likely (x != 0))
    #else
      while (i != x)
    #endif
    {
      t_char b = p1[i];
      p1[i] = p2[i];
      p2[i] = b;

      i++;
    }

    #if !CPU(UNALIGNED_ACCESS)
      if (likely ((uintptr_t)(p2 + i) & (sizeof (t_word) - 1u)))
      {
        size_t n = size_align_floor (4u, size - i);

        for (i; i < n; i += 4u)
        {
          t_char b0 = p1[i + 0];
          t_char b1 = p1[i + 1];
          t_char b2 = p1[i + 2];
          t_char b3 = p1[i + 3];

          p1[i + 0] = p2[i + 0];
          p1[i + 1] = p2[i + 1];
          p1[i + 2] = p2[i + 2];
          p1[i + 3] = p2[i + 3];

          p2[i + 0] = b0;
          p2[i + 1] = b1;
          p2[i + 2] = b2;
          p2[i + 3] = b3;
        }

        goto tail;
      }
    #endif

    size_t n = size_align_floor (sizeof (t_word), size - i);

    for (i; i < n; i += sizeof (t_word))
  #else
    size_t n = size_align_floor (sizeof (t_word), size);

    for (i; i != n; i += sizeof (t_word))
  #endif
  {
    t_word w = *(t_word*)(p1 + i);
    *(t_word*)(p1 + i) = *(t_word*)(p2 + i);
    *(t_word*)(p2 + i) = w;
  }

#else

  size_t n = size_align_floor (4u, size);

  for (i; i != n; i += 4u)
  {
    t_char b0 = p1[i + 0];
    t_char b1 = p1[i + 1];
    t_char b2 = p1[i + 2];
    t_char b3 = p1[i + 3];

    p1[i + 0] = p2[i + 0];
    p1[i + 1] = p2[i + 1];
    p1[i + 2] = p2[i + 2];
    p1[i + 3] = p2[i + 3];

    p2[i + 0] = b0;
    p2[i + 1] = b1;
    p2[i + 2] = b2;
    p2[i + 3] = b3;
  }

#endif

tail:
  for (i; i != size; i++)
  {
    t_char b = p1[i];
    p1[i] = p2[i];
    p2[i] = b;
  }
}

// -----------------------------------------------------------------------------

#undef T_PREALIGN

// -----------------------------------------------------------------------------

#include "../../support/outro.h"
