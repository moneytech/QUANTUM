// =============================================================================
// <string/string/compare/generic.c>
//
// Portable code for comparing the contents of two buffers.
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

  size_t i = 0;

#if !T(ICASE) && CPU(UNALIGNED_ACCESS) && (T_CHAR_BIT == 8)\
&& ((T_WORD_BIT == 16) || (T_WORD_BIT == 32) || (T_WORD_BIT == 64))

  #if T(PREALIGN)
    #if (T_WORD_BIT == 16)
      size_t x = (uintptr_t)b1 & 1u;
    #else
      size_t x = (sizeof (t_word) - ((uintptr_t)b1 & (sizeof (t_word) - 1u))) & (sizeof (t_word) - 1u);
    #endif

    if (unlikely (x >= size)) goto tail;

    #if (T_WORD_BIT == 16)
      if (likely (x != 0))
    #else
      while (i != x)
    #endif
    {
      if (b1[i] != b2[i])
      {
    #if T(EQUALITY)
        return false;
    #elif T(SIMILARITY)
        return i;
    #else
        return (int)b1[i] - (int)b2[i];
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

  size_t x = (uintptr_t)b1 & 1u;

  if (unlikely (x >= size)) goto tail;

  if (likely (x != 0))
  {
    if (*b1 != *b2)
    {
  #if T(EQUALITY)
      return false;
  #elif T(SIMILARITY)
      return i;
  #else
      return (int)*b1 - (int)*b2;
  #endif
    }

    i++;
  }

  if (likely ((uintptr_t)(b2 + i) & 1u)) goto tail;
  else
  {
    size_t n = size_align_floor (2u, size - i);

    for (i; i < n; i += 2u)
    {
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

  size_t x = (4u - ((uintptr_t)b1 & 3u)) & 3u;

  if (unlikely (x >= size)) goto tail;

  for (i; i != x; i++) if (b1[i] != b2[i])
  {
  #if T(EQUALITY)
    return false;
  #elif T(SIMILARITY)
    return i;
  #else
    return (int)b1[i] - (int)b2[i];
  #endif
  }

  size_t n = size_align_floor (4u, size - i);

  if (likely (n != 0)) switch ((uintptr_t)(b2 + i) & 3u)
  {
    case 0:
    {
      do
      {
        if (*(const u32*)(b1 + i) != *(const u32*)(b2 + i))
        {
  #if T(EQUALITY)
          return false;
  #else
          goto match;
  #endif
        }

        i += 4u;
      }
      while (i < n);

      break;
    }
    case 1:
    {
      u32 s1 = *(const u32*)(b2 + i - 1);

      do
      {
        u32 s2 = *(const u32*)(b2 + i + 4 - 1);

        if (*(const u32*)(b1 + i) != (s1 t_shr 8) | (s2 t_shl 24))
        {
  #if T(EQUALITY)
          return false;
  #else
          goto match;
  #endif
        }

        s1 = s2;

        i += 4u;
      }
      while (i < n);

      break;
    }
    case 2:
    {
      u32 s1 = *(const u32*)(b2 + i - 2);

      do
      {
        u32 s2 = *(const u32*)(b2 + i + 4 - 2);

        if (*(const u32*)(b1 + i) != (s1 t_shr 16) | (s2 t_shl 16))
        {
  #if T(EQUALITY)
          return false;
  #else
          goto match;
  #endif
        }

        s1 = s2;

        i += 4u;
      }
      while (i < n);

      break;
    }
    case 3:
    {
      u32 s1 = *(const u32*)(b2 + i - 3);

      do
      {
        u32 s2 = *(const u32*)(b2 + i + 4 - 3);

        if (*(const u32*)(b1 + i) != (s1 t_shr 24) | (s2 t_shl 8))
        {
  #if T(EQUALITY)
          return false;
  #else
          goto match;
  #endif
        }

        s1 = s2;

        i += 4u;
      }
      while (i < n);

      break;
    }
  }

#elif !T(ICASE) && (T_CHAR_BIT == 8) && (T_WORD_BIT == 64)

  size_t x = (8u - ((uintptr_t)b1 & 7u)) & 7u;

  if (unlikely (x >= size)) goto tail;

  for (i; i != x; i++) if (b1[i] != b2[i])
  {
  #if T(EQUALITY)
    return false;
  #elif T(SIMILARITY)
    return i;
  #else
    return (int)b1[i] - (int)b2[i];
  #endif
  }

  size_t n = size_align_floor (8u, size - i);

  if (likely ((uintptr_t)(b2 + i) & 7u)) for (i; i < n; i += 8u)
  {
    u64 w;

  #if CPU(LITTLE_ENDIAN)
    w = ((u64)(b2[i + 0]))
      | ((u64)(b2[i + 1]) << 8)
      | ((u64)(b2[i + 2]) << 16)
      | ((u64)(b2[i + 3]) << 24)
      | ((u64)(b2[i + 4]) << 32)
      | ((u64)(b2[i + 5]) << 40)
      | ((u64)(b2[i + 6]) << 48)
      | ((u64)(b2[i + 7]) << 56);
  #else
    w = ((u64)(b2[i + 0]) << 56)
      | ((u64)(b2[i + 1]) << 48)
      | ((u64)(b2[i + 2]) << 40)
      | ((u64)(b2[i + 3]) << 32)
      | ((u64)(b2[i + 4]) << 24)
      | ((u64)(b2[i + 5]) << 16)
      | ((u64)(b2[i + 6]) << 8)
      | ((u64)(b2[i + 7]));
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
  else for (i; i < n; i += 8u)
  {
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
  for (i; i != size; i++) if (b1[i] != b2[i])
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
      return i;
#else
      return (int)c1 - (int)c2;
#endif
    }
  }

#if T(EQUALITY)
  return true;
#elif T(SIMILARITY)
  return i;
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
      return i;
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
