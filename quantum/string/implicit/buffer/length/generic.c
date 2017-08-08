// =============================================================================
// <string/implicit/buffer/length/generic.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../../support/intro.h"

// -----------------------------------------------------------------------------

if (true)
{
#if (T_CHAR_BIT == 8) && ((T_WORD_BIT == 16) || (T_WORD_BIT == 32) || (T_WORD_BIT == 64))

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
      if (unlikely (str[i] == '\0')) return i;
      i++;
    }

    n = size_align_floor (sizeof (t_word), max - i);

    for (i; i < n; i += sizeof (t_word))
    {
      t_word w = *(const t_word*)(str + i);

    #if (T_WORD_BIT == 16)
      if (unlikely (swar_has_zero2 (w))) goto tail;
    #elif (T_WORD_BIT == 32)
      if (unlikely (swar_has_zero4 (w))) goto tail;
    #elif (T_WORD_BIT == 64)
      if (unlikely (swar_has_zero8 (w))) goto tail;
    #endif
    }

tail:
    for (i; i != max; i++) if (unlikely (str[i] == '\0')) break;

    return i;

  #else // T(LIMIT) ][

    const t_char* s = str;
    const t_char* p = ptr_align_ceil (sizeof (t_word), str);

    #if (T_WORD_BIT == 16)
      if (likely (s != p))
    #else
      while (s != p)
    #endif
    {
      if (unlikely (*s == '\0')) return (size_t)(s - str);
      s++;
    }

    while (true)
    {
      t_word w = *(const t_word*)s;

    #if (T_WORD_BIT == 16)
      if (unlikely (swar_has_zero2 (w))) goto tail;
    #elif (T_WORD_BIT == 32)
      if (unlikely (swar_has_zero4 (w))) goto tail;
    #elif (T_WORD_BIT == 64)
      if (unlikely (swar_has_zero8 (w))) goto tail;
    #endif
    }

tail:
    while (true)
    {
      if (unlikely (*s == '\0')) return (size_t)(s - str);
      s++;
    }

  #endif // !T(LIMIT)

#else

  const t_char* s = str;

  while (*s != '\0') s++;

  return (size_t)(s - str);

#endif
}

// -----------------------------------------------------------------------------

#undef T_LIMIT

// -----------------------------------------------------------------------------

#include "../../../support/outro.h"
