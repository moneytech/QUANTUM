// =============================================================================
// <string/string/rcopy/generic.c>
//
// Portable code for copying the contents of a buffer in reverse direction.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../support/intro.h"

// -----------------------------------------------------------------------------

#define t_copyb7(x) do\
{               \
  if ((x) & 4u) \
  {             \
    d -= 4u;    \
    s -= 4u;    \
                \
    d[3] = s[3];\
    d[2] = s[2];\
    d[1] = s[1];\
    d[0] = s[0];\
  }             \
                \
  if ((x) & 2u) \
  {             \
    d -= 2u;    \
    s -= 2u;    \
                \
    d[1] = s[1];\
    d[0] = s[0];\
  }             \
                \
  if ((x) & 1u) \
  {             \
    *--d = *--s;\
  }       \
} while (0)

#define t_copyb3(x) do\
{               \
  if ((x) & 2u) \
  {             \
    d -= 2u;    \
    s -= 2u;    \
                \
    d[1] = s[1];\
    d[0] = s[0];\
  }             \
                \
  if ((x) & 1u) \
  {             \
    *--d = *--s;\
  }       \
} while (0)

#define t_copyb1(x) do\
{               \
  if (x)        \
  {             \
    *--d = *--s;\
  }       \
} while (0)

// -----------------------------------------------------------------------------

#define t_copyw7(x) do\
{              \
  if ((x) & 4u)\
  {            \
    d -= 4u;   \
    s -= 4u;   \
               \
    *(u32*)d = *(const u32*)s;\
  }            \
               \
  if ((x) & 2u)\
  {            \
    d -= 2u;   \
    s -= 2u;   \
               \
    *(u16*)d = *(const u16*)s;\
  }            \
               \
  if ((x) & 1u)\
  {         \
    *d = *s;\
  }       \
} while (0)

#define t_copyw3(x) do\
{              \
  if ((x) & 2u)\
  {            \
    d -= 2;    \
    s -= 2;    \
               \
    *(u16*)d = *(const u16*)s;\
  }            \
               \
  if ((x) & 1u)\
  {         \
    *d = *s;\
  }       \
} while (0)

// -----------------------------------------------------------------------------

#if (T_CHAR_BIT == 8) && HAVE(INT32) && HAVE(INT16)
  #define t_tail7 t_copyw7
#else
  #define t_tail7 t_copyb7
#endif

#if (T_CHAR_BIT == 8) && HAVE(INT16)
  #define t_tail3 t_copyw3
#else
  #define t_tail3 t_copyb3
#endif

#define t_tail1 t_copyb1

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
  t_char* d = dst + size;
  const t_char* s = src + size;

#if CPU(UNALIGNED_ACCESS) && (T_CHAR_BIT == 8)\
&& ((T_WORD_BIT == 16) || (T_WORD_BIT == 32) || (T_WORD_BIT == 64))

  #if T(PREALIGN)
    #if (T_WORD_BIT == 16)
      size_t x = (uintptr_t)d & 1u;
    #else
      size_t x = (uintptr_t)d & (sizeof (t_word) - 1u);
    #endif

    if (unlikely (x >= size)) goto tail;

    #if (T_WORD_BIT == 64)
      t_copyb7 (x);
    #elif (T_WORD_BIT == 32)
      t_copyb3 (x);
    #elif (T_WORD_BIT == 16)
      t_copyb1 (x);
    #endif

    size_t i = size - x;
  #else
    size_t i = size;
  #endif

  size_t n = i & (sizeof (t_word) - 1u);

  while (i > n)
  {
    i -= sizeof (t_word);
    *(t_word*)(d + i) = *(const t_word*)(s + i);
  }

tail:
  #if (T_WORD_BIT == 64)
    t_tail7 (n);
  #elif (T_WORD_BIT == 32)
    t_tail3 (n);
  #elif (T_WORD_BIT == 16)
    t_tail1 (n);
  #endif

#elif (T_CHAR_BIT == 8) && (T_WORD_BIT == 16)

  size_t x = (uintptr_t)d & 1u;

  if (unlikely (x >= size)) goto tail;

  t_copyb1 (x);

  size_t i = size - x;
  size_t n = i & 1u;

  if (likely ((uintptr_t)s & 1u)) while (i > n)
  {
    i -= 4u;

    d[i + 3] = s[i + 3];
    d[i + 2] = s[i + 2];
    d[i + 1] = s[i + 1];
    d[i + 0] = s[i + 0];
  }
  else while (i > n)
  {
    i -= 4u;

    *(u16*)(d + i + 2) = *(const u16*)(s + i + 2);
    *(u16*)(d + i + 0) = *(const u16*)(s + i + 0);
  }

tail:
  t_tail3 (n);

#elif (T_CHAR_BIT == 8) && (T_WORD_BIT == 32)

  size_t x = (uintptr_t)d & 3u;

  if (unlikely (x >= size)) goto tail;

  t_copyb3 (x);

  size_t i = size - x;
  size_t n = i & 3u;

  if (likely (i > n)) switch ((uintptr_t)s & 3u)
  {
    case 0:
    {
      do
      {
        i -= 4u;
        *(u32*)(d + i) = *(const u32*)(s + i);
      }
      while (i > n);

      break;
    }
    case 1:
    {
      u32 s1 = *(const u32*)(s + i - 1);

      do
      {
        i -= 4u;
        u32 s2 = *(const u32*)(s + i - 1);
        *(u32*)(d + i) = (s1 t_shl 24) | (s2 t_shr 8);
        s1 = s2;
      }
      while (i > n);

      break;
    }
    case 2:
    {
      u32 s1 = *(const u32*)(s + i - 2);

      do
      {
        i -= 4u;
        u32 s2 = *(const u32*)(s + i - 2);
        *(u32*)(d + i) = (s1 t_shl 16) | (s2 t_shr 16);
        s1 = s2;
      }
      while (i > n);

      break;
    }
    case 3:
    {
      u32 s1 = *(const u32*)(s + i - 3);

      do
      {
        i -= 4u;
        u32 s2 = *(const u32*)(s + i - 3);
        *(u32*)(d + i) = (s1 t_shl 8) | (s2 t_shr 24);
        s1 = s2;
      }
      while (i > n);

      break;
    }
  }

tail:
  t_tail3 (n);

#elif (T_CHAR_BIT == 8) && (T_WORD_BIT == 64)

  size_t x = (uintptr_t)d & 7u;

  if (unlikely (x >= n)) goto tail;

  t_copyb7 (x);

  size_t i = size - x;
  size_t n = i & 7u;

  if (likely ((uintptr_t)s & 7u)) while (i > n)
  {
    i -= 8u;

  #if CPU(LITTLE_ENDIAN)
    *(u64*)(d + i)
    = ((u64)(s[i + 7]) << 56)
    | ((u64)(s[i + 6]) << 48)
    | ((u64)(s[i + 5]) << 40)
    | ((u64)(s[i + 4]) << 32)
    | ((u64)(s[i + 3]) << 24)
    | ((u64)(s[i + 2]) << 16)
    | ((u64)(s[i + 1]) << 8)
    | ((u64)(s[i + 0]));
  #else
    *(u64*)(d + i)
    = ((u64)(s[i + 7]))
    | ((u64)(s[i + 6]) << 8)
    | ((u64)(s[i + 2]) << 16)
    | ((u64)(s[i + 4]) << 24)
    | ((u64)(s[i + 3]) << 32)
    | ((u64)(s[i + 2]) << 40)
    | ((u64)(s[i + 1]) << 48)
    | ((u64)(s[i + 0]) << 56);
  #endif
  }
  else while (i > n)
  {
    i -= 8u;
    *(u64*)d = *(const u64*)s;
  }

tail:
  t_tail7 (n);

#else

  size_t i = size;
  size_t n = size & 3u;

  while (i > n)
  {
    i -= 4u;

    d[i + 3] = s[i + 3];
    d[i + 2] = s[i + 2];
    d[i + 1] = s[i + 1];
    d[i + 0] = s[i + 0];
  }

  t_copyb3 (n);

#endif
}

// -----------------------------------------------------------------------------

#undef T_PREALIGN

// -----------------------------------------------------------------------------

#undef t_copyb7
#undef t_copyb3
#undef t_copyb1

#undef t_copyw7
#undef t_copyw3

#undef t_tail7
#undef t_tail3
#undef t_tail1

// -----------------------------------------------------------------------------

#undef t_shl
#undef t_shr

// -----------------------------------------------------------------------------

#include "../../support/outro.h"
