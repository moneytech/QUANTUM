// =============================================================================
// <string/implicit/buffer/copy/generic.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../../support/intro.h"

// -----------------------------------------------------------------------------

if (true)
{
#if T(LIMIT)
  if (unlikely (max == 0)) return (*src == '\0') ? dst : null;
#endif

  size_t i = 0;

#if CPU(UNALIGNED_ACCESS) && (T_CHAR_BIT == 8)\
&& ((T_WORD_BIT == 16) || (T_WORD_BIT == 32) || (T_WORD_BIT == 64))

  #if (T_WORD_BIT == 16)
    size_t n = (uintptr_t)src & 1u;
  #else
    size_t n = (sizeof (t_word) - ((uintptr_t)src & (sizeof (t_word) - 1u))) & (sizeof (t_word) - 1u);
  #endif

  #if T(LIMIT)
    if (unlikely (n >= max)) goto tail;
  #endif

  #if (T_WORD_BIT == 16)
    if (likely (n != 0))
  #else
    while (i != n)
  #endif
  {
    t_char c = src[i];
    dst[i] = c;

    if (unlikely (c == '\0')) return dst + i;

    i++;
  }

  #if T(LIMIT)
    n = size_align_floor (sizeof (t_word), max - i);

    for (i; i < n; i += sizeof (t_word))
  #else
    for (i; i; i += sizeof (t_word))
  #endif
  {
    t_word w = *(const t_word* restrict)(src + i);

  #if (T_WORD_BIT == 16)
    if (unlikely (swar_has_zero2 (w))) goto tail;
  #elif (T_WORD_BIT == 32)
    if (unlikely (swar_has_zero4 (w))) goto tail;
  #elif (T_WORD_BIT == 64)
    if (unlikely (swar_has_zero8 (w))) goto tail;
  #endif

    *(t_word* restrict)(dst + i) = w;
  }

tail:
#endif

#if T(LIMIT)
  for (i; i != max; i++)
#else
  for (i; i; i++)
#endif
  {
    t_char c = src[i];
    dst[i] = c;

    if (unlikely (c == '\0')) return dst + i;
  }

#if T(LIMIT)
  dst[max - 1] = '\0';

  return null;
#endif
}

// -----------------------------------------------------------------------------

#undef T_LIMIT

// -----------------------------------------------------------------------------

#include "../../../support/outro.h"
