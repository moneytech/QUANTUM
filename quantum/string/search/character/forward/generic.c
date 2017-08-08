// =============================================================================
// <string/search/character/forward/generic.c>
//
// Portable code for searching the contents of a buffer
// for a particular byte.
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
  const t_char* b = buf;

#if !T(ICASE) && (T_CHAR_BIT == 8)\
&& ((T_WORD_BIT == 16) || (T_WORD_BIT == 32) || (T_WORD_BIT == 64))

  size_t i = 0;
  t_word v = (T_WORD_MAX / T_CHAR_MAX) * chr;

  #if (CPU(UNALIGNED_ACCESS) && T(PREALIGN)) || !CPU(UNALIGNED_ACCESS)
    #if (T_WORD_BIT == 16)
      size_t x = (uintptr_t)b & 1u;
    #else
      size_t x = (sizeof (t_word) - ((uintptr_t)b & (sizeof (t_word) - 1u))) & (sizeof (t_word) - 1u);
    #endif

    if (unlikely (x >= size)) goto tail;

    #if (T_WORD_BIT == 16)
      if (likely (x != 0))
    #else
      while (i != x)
    #endif
    {
      if (b[i] t_cmp chr)
      {
    #if T(SPAN)
        return i;
    #else
        return (t_char*)(b + i);
    #endif
      }

      i++;
    }

    size_t n = size_align_floor (sizeof (t_word), size - i);

    for (i; i < n; i += sizeof (t_word))
  #else
    size_t n = size_align_floor (sizeof (t_word), size);

    for (i; i != n; i += sizeof (t_word))
  #endif
  {
    t_word w = *(const t_word*)(b + i);

  #if T(INVERT)
    if (w != v) goto match;
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
  for (i; i != size; i++) if (b[i] t_cmp chr)
  {
  #if T(SPAN)
    return i;
  #else
    return (t_char*)(b + i);
  #endif
  }

match:
  while (true)
  {
    if (b[i] t_cmp chr)
    {
  #if T(SPAN)
      return i;
  #else
      return (t_char*)(b + i);
  #endif
    }

    i++;
  }

#else

  const t_char* e = buf + size;
  t_char c = t_chr_to_case (chr);

  while (b != e)
  {
    if (t_chr_to_case (*b) t_cmp c)
    {
  #if T(SPAN)
      return (size_t)(b - buf);
  #else
      return (t_char*)b;
  #endif
    }

    b++;
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
