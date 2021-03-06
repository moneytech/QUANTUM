// =============================================================================
// <string/string/rcompare/generic.c>
//
// Portable code for comparing the contents of two buffers in reverse direction.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../support/intro.h"

// -----------------------------------------------------------------------------

#if !T(ICASE)
  #define t_chr_to_case nop
#endif

// -----------------------------------------------------------------------------

#if CPU(LITTLE_ENDIAN)
  #define t_shl <<
  #define t_shr >>
#else
  #define t_shl >>
  #define t_shr <<
#endif

// -----------------------------------------------------------------------------

if (true)
{
  const t_char* b1 = buf1;
  const t_char* b2 = buf2;

  size_t i = size;

#if !T(ICASE) && CPU(UNALIGNED_ACCESS) && (T_CHAR_BIT == 8)\
&& ((T_WORD_BIT == 16) || (T_WORD_BIT == 32) || (T_WORD_BIT == 64))

  size_t n;

  #if T(PREALIGN)
    #if (T_WORD_BIT == 16)
      size_t x = (uintptr_t)(b1 + i) & 1u;
    #else
      size_t x = (uintptr_t)(b1 + i) & (sizeof (t_word) - 1u);
    #endif

    if (unlikely (x >= size)) goto tail;

    n = size - x;

    #if (T_WORD_BIT == 16)
      if (likely (x != 0))
    #else
      while (i != n)
    #endif
    {
      i--;

      if (b1[i] != b2[i])
      {
    #if T(EQUALITY)
        return false;
    #elif T(SIMILARITY)
        return (size - i) - 1u;
    #else
        return (int)b1[i] - (int)b2[i];
    #endif
      }
    }
  #endif

  n = i & (sizeof (t_word) - 1u);

  while (i > n)
  {
    i -= sizeof (t_word);

    if (*(const t_word*)(b1 + i) != *(const t_word*)(b2 + i))
    {
  #if T(EQUALITY)
      return false;
  #else
      goto match;
  #endif
    }
  }

#elif !T(ICASE) && (T_CHAR_BIT == 8) && (T_WORD_BIT == 16)

  size_t x = (uintptr_t)(b1 + i) & 1u;

  if (unlikely (x >= size)) goto tail;

  size_t n = size - x;

  if (likely (i != n))
  {
    i--;

    if (b1[i] != b2[i])
    {
  #if T(EQUALITY)
      return false;
  #elif T(SIMILARITY)
      return (size - i) - 1u;
  #else
      return (int)b1[i] - (int)b2[i];
  #endif
    }
  }

  if (likely ((uintptr_t)(b2 + i) & 1u)) goto tail;
  else
  {
    n = i & 1u;

    while (i > n)
    {
      i -= 2u;

      if (*(const u16*)(b1 + i) != *(const u16*)(b2 + i))
      {
  #if T(EQUALITY)
        return false;
  #else
        goto match;
  #endif
      }
    }
  }

#elif !T(ICASE) && (T_CHAR_BIT == 8) && (T_WORD_BIT == 32)

  size_t x = (uintptr_t)(b1 + i) & 3u;

  if (unlikely (x >= size)) goto tail;

  size_t n = size - x;

  while (i != n)
  {
    i--;

    if (b1[i] != b2[i])
    {
  #if T(EQUALITY)
      return false;
  #elif T(SIMILARITY)
      return (size - i) - 1u;
  #else
      return (int)b1[i] - (int)b2[i];
  #endif
    }
  }

  n = i & 3u;

  if (likely (i > n)) switch ((uintptr_t)(b2 + i) & 3u)
  {
    case 0:
    {
      do
      {
        i -= 4u;

        if (*(const u32*)(b1 + i) != *(const u32*)(b2 + i))
        {
  #if T(EQUALITY)
          return false;
  #else
          goto match;
  #endif
        }
      }
      while (i > n);

      break;
    }
    case 1:
    {
      u32 s1 = *(const u32*)(b2 + i - 1);

      do
      {
        i -= 4u;

        u32 s2 = *(const u32*)(b2 + i - 1);

        if (*(const u32*)(b1 + i) != (s1 t_shl 24) | (s2 t_shr 8))
        {
  #if T(EQUALITY)
          return false;
  #else
          goto match;
  #endif
        }

        s1 = s2;
      }
      while (i > n);

      break;
    }
    case 2:
    {
      u32 s1 = *(const u32*)(b2 + i - 2);

      do
      {
        i -= 4u;

        u32 s2 = *(const u32*)(b2 + i - 2);

        if (*(const u32*)(b1 + i) != (s1 t_shl 16) | (s2 t_shr 16))
        {
  #if T(EQUALITY)
          return false;
  #else
          goto match;
  #endif
        }

        s1 = s2;
      }
      while (i > n);

      break;
    }
    case 3:
    {
      u32 s1 = *(const u32*)(b2 + i - 3);

      do
      {
        i -= 4u;

        u32 s2 = *(const u32*)(b2 + i - 3);

        if (*(const u32*)(b1 + i) != (s1 t_shl 8) | (s2 t_shr 24))
        {
  #if T(EQUALITY)
          return false;
  #else
          goto match;
  #endif
        }

        s1 = s2;
      }
      while (i > n);

      break;
    }
  }

#elif !T(ICASE) && (T_CHAR_BIT == 8) && (T_WORD_BIT == 64)

  size_t x = (uintptr_t)(b1 + i) & 7u;

  if (unlikely (x >= size)) goto tail;

  size_t n = size - x;

  while (i != n)
  {
    i--;

    if (b1[i] != b2[i])
    {
  #if T(EQUALITY)
      return false;
  #elif T(SIMILARITY)
      return (size - i) - 1u;
  #else
      return (int)b1[i] - (int)b2[i];
  #endif
    }
  }

  n = i & 7u;

  if (likely ((uintptr_t)(b2 + i) & 7u)) while (i > n)
  {
    i -= 8u;

    u64 w;

  #if CPU(LITTLE_ENDIAN)
    w = ((u64)(b2[i + 7]) << 56)
      | ((u64)(b2[i + 6]) << 48)
      | ((u64)(b2[i + 5]) << 40)
      | ((u64)(b2[i + 4]) << 32)
      | ((u64)(b2[i + 3]) << 24)
      | ((u64)(b2[i + 2]) << 16)
      | ((u64)(b2[i + 1]) << 8)
      | ((u64)(b2[i + 0]));
  #else
    w = ((u64)(b2[i + 7]))
      | ((u64)(b2[i + 6]) << 8)
      | ((u64)(b2[i + 5]) << 16)
      | ((u64)(b2[i + 4]) << 24)
      | ((u64)(b2[i + 3]) << 32)
      | ((u64)(b2[i + 2]) << 40)
      | ((u64)(b2[i + 1]) << 48)
      | ((u64)(b2[i + 0]) << 56);
  #endif

    if (*(const u64*)(b1 + i) != w)
    {
  #if T(EQUALITY)
      return false;
  #else
      goto match;
  #endif
    }
  }
  else while (i > n)
  {
    i -= 8u;

    if (*(const u64*)(b1 + i) != *(const u64*)(b2 + i))
    {
  #if T(EQUALITY)
      return false;
  #else
      goto match;
  #endif
    }
  }

#endif

tail:
  while (i != 0)
  {
    i--;

    if (b1[i] != b2[i])
    {
      t_char c1 = t_chr_to_case (b1[i]);
      t_char c2 = t_chr_to_case (b2[i]);

#if T(ICASE)
      if (c1 != c2)
#endif
      {
#if T(EQUALITY)
        return false;
#elif T(SIMILARITY)
        return (size - i) - 1u;
#else
        return (int)c1 - (int)c2;
#endif
      }
    }
  }

#if T(EQUALITY)
  return true;
#elif T(SIMILARITY)
  return size;
#else
  return 0;
#endif

#if !T(EQUALITY)
match:
  while (true)
  {
    if (b1[i] != b2[i])
    {
  #if T(SIMILARITY)
      return (size - i) - 1u;
  #else
      return (int)b1[i] - (int)b2[i];
  #endif
    }

    i++;
  }
#endif
}

// -----------------------------------------------------------------------------

#undef T_PREALIGN

#undef T_EQUALITY
#undef T_SIMILARITY

#undef T_ICASE
#undef t_chr_to_case

// -----------------------------------------------------------------------------

#undef t_shl
#undef t_shr

// -----------------------------------------------------------------------------

#include "../../support/outro.h"
