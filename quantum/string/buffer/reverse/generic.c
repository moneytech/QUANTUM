// =============================================================================
// <string/buffer/reverse/generic.c>
//
// Portable code for reversing the order of bytes in a buffer.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../support/intro.h"

// -----------------------------------------------------------------------------

if (true)
{
  t_char* m = buf;
  t_char* e = buf + size;

#if (T_CHAR_BIT == 8) && ((T_WORD_BIT == 16) || (T_WORD_BIT == 32) || (T_WORD_BIT == 64))

  #if (CPU(UNALIGNED_ACCESS) && T(PREALIGN)) || !CPU(UNALIGNED_ACCESS)
    #if (T_WORD_BIT == 16)
      size_t x = (uintptr_t)m & 1u;
    #else
      size_t x = (sizeof (t_word) - ((uintptr_t)m & (sizeof (t_word) - 1u))) & (sizeof (t_word) - 1u);
    #endif

    if (unlikely (x >= size)) goto tail;

    t_char* p = buf + x;

    #if (T_WORD_BIT == 16)
      if (likely (x != 0))
    #else
      while (m != p)
    #endif
    {
      t_char b = *m;
      *m++ = *--e;
      *e = b;
    }

    #if !CPU(UNALIGNED_ACCESS)
      if (likely ((uintptr_t)e & (sizeof (t_word) - 1u)))
      {
        p += size_align_floor (4u, (size - x) / 2u);

        while (m != p)
        {
          t_char b0 = m[0];
          t_char b1 = m[1];
          t_char b2 = m[2];
          t_char b3 = m[3];

          e -= 4;

          m[0] = e[3];
          m[1] = e[2];
          m[2] = e[1];
          m[3] = e[0];

          m += 4;

          e[3] = b0;
          e[2] = b1;
          e[1] = b2;
          e[0] = b3;
        }

        goto tail;
      }
    #endif

    p += size_align_floor (sizeof (t_word), (size - x) / 2u);

    while (m != p)
  #else
    t_char* p = m + size_align_floor (sizeof (t_word), size / 2u);

    while (m != p)
  #endif
  {
    t_word w = *(t_word*)m;

    e -= sizeof (t_word);

  #if (T_WORD_BIT == 16)
    *(t_word*)m = bswap16 (*(t_word*)e);
    *(t_word*)e = bswap16 (w);
  #elif (T_WORD_BIT == 32)
    *(t_word*)m = bswap32 (*(t_word*)e);
    *(t_word*)e = bswap32 (w);
  #elif (T_WORD_BIT == 64)
    *(t_word*)m = bswap64 (*(t_word*)e);
    *(t_word*)e = bswap64 (w);
  #endif

    m += sizeof (t_word);
  }

#else

  t_char* p = m + size_align_floor (4u, size / 2u);

  while (m != p)
  {
    t_char b0 = m[0];
    t_char b1 = m[1];
    t_char b2 = m[2];
    t_char b3 = m[3];

    e -= 4;

    m[0] = e[3];
    m[1] = e[2];
    m[2] = e[1];
    m[3] = e[0];

    m += 4;

    e[3] = b0;
    e[2] = b1;
    e[1] = b2;
    e[0] = b3;
  }

#endif

tail:
  while (m != e)
  {
    t_char b = *m;
    *m++ = *--e;
    *e = b;
  }
}

// -----------------------------------------------------------------------------

#undef T_PREALIGN

// -----------------------------------------------------------------------------

#include "../../support/outro.h"
