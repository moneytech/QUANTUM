// =============================================================================
// <string/search/character/backward/generic.c>
//
// Portable code for searching the contents of a buffer
// for a particular byte in reverse direction.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../../support/intro.h"

// -----------------------------------------------------------------------------

#if !T(ICASE)
  #define t_chr_to_case nop
#endif

// -----------------------------------------------------------------------------

#if T(INVERT)
  #define t_cmp ==
#else
  #define t_cmp !=
#endif

// -----------------------------------------------------------------------------

if (true)
{
#if !T(ICASE) && (T_CHAR_BIT == 8)\
&& ((T_WORD_BIT == 16) || (T_WORD_BIT == 32) || (T_WORD_BIT == 64))

  const t_char* b = buf;
  size_t i = size;
  size_t n;

  #if (CPU(UNALIGNED_ACCESS) && T(PREALIGN)) || !CPU(UNALIGNED_ACCESS)
    size_t x = (uintptr_t)(b + size) & (sizeof (t_word) - 1u);

    if (unlikely (x >= size)) goto tail;

    #if (T_WORD_BIT == 16)
      if (likely (x != 0))
    #else
      n = size - x;

      while (i != n)
    #endif
    {
      i--;

      if (b[i] t_cmp chr)
      {
    #if T(SPAN)
        return (size - i) - 1u;
    #else
        return (t_char*)(b + i);
    #endif
      }
    }
  #endif

  t_word v = (T_WORD_MAX / T_CHAR_MAX) * chr;

  n = i & (sizeof (t_word) - 1u);

  while (i > n)
  {
    i -= sizeof (t_word);

    t_word w = *(const t_word*)(b + i);

  #if T(INVERT)
    if (w t_cmp v) goto match;
  #else
    #if (T_WORD_BIT == 16)
      if (swar_has_zero2 (w - v)) goto match;
    #elif (T_WORD_BIT == 32)
      if (swar_has_zero4 (w - v)) goto match;
    #elif (T_WORD_BIT == 64)
      if (swar_has_zero8 (w - v)) goto match;
    #endif
  #endif
  }

tail:
  while (i != 0)
  {
    i--;

    if (b[i] t_cmp chr)
    {
  #if T(SPAN)
      return (size - i) - 1u;
  #else
      return (t_char*)(b + i);
  #endif
    }
  }

match:
  while (true)
  {
    if (b[i] t_cmp chr)
    {
  #if T(SPAN)
      return (size - i) - 1u;
  #else
      return (t_char*)(b + i);
  #endif
    }

    i++;
  }

#else

  const t_char* b = buf + size;
  t_char c = t_chr_to_case (chr);

  while (b != buf)
  {
    if (t_chr_to_case (*--b) t_cmp c)
    {
  #if T(SPAN)
      return (size_t)((buf + size) - b) - 1u;
  #else
      return (t_char*)b;
  #endif
    }
  }

#endif

#if T(SPAN)
  return size;
#else
  return null;
#endif
}

// -----------------------------------------------------------------------------

#undef T_PREALIGN
#undef T_SPAN

#undef T_ICASE
#undef t_chr_to_case

#undef T_INVERT
#undef t_cmp

// -----------------------------------------------------------------------------

#include "../../../support/outro.h"
