// =============================================================================
// <string/implicit/replace/character/generic.c>
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
#if !T(ICASE) && (T_CHAR_BIT == 8)\
&& ((T_WORD_BIT == 16) || (T_WORD_BIT == 32) || (T_WORD_BIT == 64))

  t_word v = (T_WORD_MAX / T_CHAR_MAX) * old;

  #if T(LIMIT)

    size_t i = 0;

    #if (T_WORD_BIT == 16)
      size_t n = (uintptr_t)str & 1u;
    #else
      size_t n = (sizeof (t_word) - ((uintptr_t)str & (sizeof (t_word) - 1u))) & (sizeof (t_word) - 1u);
    #endif

    if (unlikely (n >= max)) goto tail;

    #if (T_WORD_BIT == 16)
      if (likely (n != 0))
    #else
      while (i != n)
    #endif
    {
      if (unlikely (str[i] == '\0')) return str + i;
      if (str[i] == old) str[i] = new;
      i++;
    }

    n = size_align_floor (sizeof (t_word), max - i);

    for (i; i < n; i += sizeof (t_word))
    {
      t_word w = *(t_word*)(str + i);

    #if (T_WORD_BIT == 16)
      if (unlikely (swar_has_zero2 (w))) goto tail;
      if (swar_has_zero2 (w - v)) goto tail;
    #elif (T_WORD_BIT == 32)
      if (unlikely (swar_has_zero4 (w))) goto tail;
      if (swar_has_zero4 (w - v)) goto tail;
    #elif (T_WORD_BIT == 64)
      if (unlikely (swar_has_zero8 (w))) goto tail;
      if (swar_has_zero8 (w - v)) goto tail;
    #endif
    }

tail:
    for (i; i != max; i++)
    {
      if (unlikely (str[i] == '\0')) break;
      if (str[i] == old) str[i] = new;
    }

    return str + i;

  #else // T(LIMIT) ][

    t_char* s = str;
    const t_char* p = ptr_align_ceil (sizeof (t_word), str);

    #if (T_WORD_BIT == 16)
      if (likely (s != p))
    #else
      while (s != p)
    #endif
    {
      if (unlikely (*s == '\0')) return s;
      if (*s == old) *s = new;
      s++;
    }

    while (true)
    {
      t_word w = *(t_word*)s;

    #if (T_WORD_BIT == 16)
      if (unlikely (swar_has_zero2 (w))) goto tail;
      if (swar_has_zero2 (w - v)) goto tail;
    #elif (T_WORD_BIT == 32)
      if (unlikely (swar_has_zero4 (w))) goto tail;
      if (swar_has_zero4 (w - v)) goto tail;
    #elif (T_WORD_BIT == 64)
      if (unlikely (swar_has_zero8 (w))) goto tail;
      if (swar_has_zero8 (w - v)) goto tail;
    #endif
    }

tail:
    while (true)
    {
      if (unlikely (*s == '\0')) return s;
      if (*s == old) *s = new;
      s++;
    }

  #endif // !T(LIMIT)

#else

  t_char* s = str;
  t_char c = t_chr_to_case (old);

  #if T(LIMIT)
    const t_char* e = str + max;

    while (s != e)
  #else
    while (true)
  #endif
  {
    if (*s == '\0') break;
    if (t_chr_to_case (*s) == c) *s = new;
    s++;
  }

  return s;

#endif
}

// -----------------------------------------------------------------------------

#undef T_LIMIT

#undef T_ICASE
#undef t_chr_to_case

// -----------------------------------------------------------------------------

#include "../../../support/outro.h"
