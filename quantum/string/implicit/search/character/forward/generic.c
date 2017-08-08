// =============================================================================
// <string/implicit/search/character/forward/generic.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../../../support/intro.h"

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
#if T(TOKEN)
  t_char* str = *st;
#endif

#if !T(ICASE) && (T_CHAR_BIT == 8)\
&& ((T_WORD_BIT == 16) || (T_WORD_BIT == 32) || (T_WORD_BIT == 64))

  t_word v = (T_WORD_MAX / T_CHAR_MAX) * chr;

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
      if (unlikely (str[i] == '\0'))
      {
    #if T(SPAN)
        return i;
    #else
        return null;
    #endif
      }

      if (str[i] t_cmp chr)
      {
    #if T(TOKEN)
        str[i] = '\0';
        *st = str + (i + 1u);

        return str;
    #elif T(SPAN)
        return i;
    #else
        return (t_char*)(str + i);
    #endif
      }

      i++;
    }

    n = size_align_floor (sizeof (t_word), max - i);

    for (i; i < n; i += sizeof (t_word))
    {
      t_word w = *(const t_word*)(str + i);

    #if T(INVERT)
      if (w != v) goto tail;
    #else
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
    #endif
    }

tail:
    #if T(LIMIT)
      for (i; i != max; i++)
    #else
      for (i; i; i++)
    #endif
    {
      if (unlikely (str[i] == '\0')) break;

      if (str[i] t_cmp chr)
      {
    #if T(TOKEN)
        str[i] = '\0';
        *st = str + (i + 1u);

        return str;
    #elif T(SPAN)
        return i;
    #else
        return (t_char*)(str + i);
    #endif
      }
    }

    #if T(SPAN)
      return i;
    #else
      return null;
    #endif

  #else // T(LIMIT) ][

    #if T(TOKEN)
      t_char* s = str;
    #else
      const t_char* s = str;
    #endif

    const t_char* p = ptr_align_ceil (sizeof (t_word), str);

    #if (T_WORD_BIT == 16)
      if (likely (s != p))
    #else
      while (s != p)
    #endif
    {
      if (unlikely (*s == '\0'))
      {
    #if T(SPAN)
        return (size_t)(s - str);
    #else
        return null;
    #endif
      }

      if (*s t_cmp chr)
      {
    #if T(TOKEN)
        *s = '\0';
        *st = s + 1;

        return str;
    #elif T(SPAN)
        return (size_t)(s - str);
    #else
        return (t_char*)s;
    #endif
      }

      s++;
    }

    while (true)
    {
      t_word w = *(const t_word*)s;

    #if T(INVERT)
      if (w != v) goto tail;
    #else
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
    #endif
    }

tail:
    while (true)
    {
      if (unlikely (*s == '\0'))
      {
    #if T(SPAN)
        return (size_t)(s - str);
    #else
        return null;
    #endif
      }

      if (*s t_cmp chr)
      {
    #if T(TOKEN)
        *s = '\0';
        *st = s + 1;

        return str;
    #elif T(SPAN)
        return (size_t)(s - str);
    #else
        return (t_char*)s;
    #endif
      }

      s++;
    }

  #endif // !T(LIMIT)

#else

  #if T(TOKEN)
    t_char* s = str;
  #else
    const t_char* s = str;
  #endif

  t_char c = t_chr_to_case (chr);

  #if T(LIMIT)
    const t_char* e = str + max;

    while (s != e)
  #else
    while (true)
  #endif
  {
    if (unlikely (*s == '\0')) break;

    if (t_chr_to_case (*s) t_cmp c)
    {
  #if T(TOKEN)
      *s = '\0';
      *st = s + 1;

      return str;
  #elif T(SPAN)
      return (size_t)(s - str);
  #else
      return (t_char*)s;
  #endif
    }

    s++;
  }

  #if T(SPAN)
    return (size_t)(s - str);
  #else
    return null;
  #endif

#endif
}

// -----------------------------------------------------------------------------

#undef T_TOKEN

#undef T_SPAN
#undef T_LIMIT

#undef T_ICASE
#undef t_chr_to_case

#undef T_INVERT
#undef t_cmp

// -----------------------------------------------------------------------------

#include "../../../../support/outro.h"
