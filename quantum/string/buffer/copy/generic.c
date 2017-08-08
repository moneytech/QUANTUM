// =============================================================================
// <string/string/copy/generic.c>
//
// Portable code for copying the contents of one buffer to another.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../support/intro.h"

// -----------------------------------------------------------------------------

#if T(RESTRICT)
  #define t_noalias restrict
#else
  #define t_noalias
#endif

// -----------------------------------------------------------------------------

#define t_copyb7(x) do\
{               \
  if ((x) & 4u) \
  {             \
    d[0] = s[0];\
    d[1] = s[1];\
    d[2] = s[2];\
    d[3] = s[3];\
                \
    d += 4u;    \
    s += 4u;    \
  }             \
                \
  if ((x) & 2u) \
  {             \
    d[0] = s[0];\
    d[1] = s[1];\
               \
    d += 2u;   \
    s += 2u;   \
  }            \
               \
  if ((x) & 1u)\
  {         \
    *d = *s;\
          \
    d++;  \
    s++;  \
  }       \
} while (0)

#define t_copyb3(x) do\
{               \
  if ((x) & 2u) \
  {             \
    d[0] = s[0];\
    d[1] = s[1];\
               \
    d += 2u;   \
    s += 2u;   \
  }            \
               \
  if ((x) & 1u)\
  {         \
    *d = *s;\
          \
    d++;  \
    s++;  \
  }       \
} while (0)

#define t_copyb1(x) do\
{           \
  if (x)    \
  {         \
    *d = *s;\
          \
    d++;  \
    s++;  \
  }       \
} while (0)

// -----------------------------------------------------------------------------

#define t_copyw7(x) do\
{              \
  if ((x) & 4u)\
  {            \
    *(u32* t_noalias)d = *(const u32* t_noalias)s;\
               \
    d += 4u;   \
    s += 4u;   \
  }            \
               \
  if ((x) & 2u)\
  {            \
    *(u16* t_noalias)d = *(const u16* t_noalias)s;\
               \
    d += 2u;   \
    s += 2u;   \
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
    *(u16* t_noalias)d = *(const u16* t_noalias)s;\
               \
    d += 2u;   \
    s += 2u;   \
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
  t_char* t_noalias d = dst;
  const t_char* t_noalias s = src;

#if CPU(UNALIGNED_ACCESS) && (T_CHAR_BIT == 8)\
&& ((T_WORD_BIT == 16) || (T_WORD_BIT == 32) || (T_WORD_BIT == 64))

  // CPU is capable of unaligned memory access
  #if T(PREALIGN)
    #if (T_WORD_BIT == 16)
      size_t x = (uintptr_t)d & 1u;
    #else
      size_t x = (sizeof (t_word) - ((uintptr_t)d & (sizeof (t_word) - 1u))) & (sizeof (t_word) - 1u);
    #endif

    if (unlikely (x >= size)) goto tail;

    // Prevent compiler (mis)optimization for byte-by-byte copies.
    // Without this optimising compilers (GCC) replace byte copies with
    // a call to `memcpy()`, which we wanted to avoid in the first place:
    // https://gcc.gnu.org/bugzilla/show_bug.cgi?id=56888
    #if (T_WORD_BIT == 64)
      t_copyb7 (x);
    #elif (T_WORD_BIT == 32)
      t_copyb3 (x);
    #elif (T_WORD_BIT == 16)
      t_copyb1 (x);
    #endif

    size_t n = size_align_floor (sizeof (t_word), size - x);
  #else
    size_t n = size_align_floor (sizeof (t_word), size);
  #endif

  for (size_t i = 0; i != n; i += sizeof (t_word))
  {
    *(t_word* t_noalias)(d + i) = *(const t_word* t_noalias)(s + i);
  }

  d += n;
  s += n;

  n = size - n;

tail:
  #if (T_WORD_BIT == 64)
    t_tail7 (n);
  #elif (T_WORD_BIT == 32)
    t_tail3 (n);
  #elif (T_WORD_BIT == 16)
    t_tail1 (n);
  #endif

#elif (T_CHAR_BIT == 8) && (T_WORD_BIT == 16)

  // Copy whole words if both addresses are aligned,
  // unroll for 4 bytes at a time
  size_t x = (uintptr_t)d & 1u;

  if (unlikely (x >= size)) goto tail;

  t_copyb1 (x);

  size_t n = size_align_floor (4u, size - x);

  if (likely ((uintptr_t)s & 1u)) for (size_t i = 0; i != n; i += 4u)
  {
    d[i + 0] = s[i + 0];
    d[i + 1] = s[i + 1];
    d[i + 2] = s[i + 2];
    d[i + 3] = s[i + 3];
  }
  else for (size_t i = 0; i != n; i += 4u)
  {
    *(u16* t_noalias)(d + i + 0) = *(const u16* t_noalias)(s + i + 0);
    *(u16* t_noalias)(d + i + 2) = *(const u16* t_noalias)(s + i + 2);
  }

  d += n;
  s += n;

  n = size - n;

tail:
  t_tail3 (n);

#elif (T_CHAR_BIT == 8) && (T_WORD_BIT == 32)

  // Copy whole words by fusing them from two aligned word reads, if necessary
  size_t x = (4u - ((uintptr_t)d & 3u)) & 3u;

  if (unlikely (x >= size)) goto tail;

  t_copyb3 (x);

  size_t i = 0;
  size_t n = size_align_floor (4u, size - x);

  if (likely (n != 0)) switch ((uintptr_t)s & 3u)
  {
    // `s` is aligned
    case 0:
    {
      do
      {
        *(u32* t_noalias)(d + i) = *(const u32* t_noalias)(s + i);
        i += 4u;
      }
      while (i != n);

      break;
    }
    // `s` is one byte off
    case 1:
    {
      u32 s1 = *(const u32* t_noalias)(s + i - 1);

      do
      {
        u32 s2 = *(const u32* t_noalias)(s + i + 4 - 1);
        *(u32* t_noalias)(d + i) = (s1 t_shr 8) | (s2 t_shl 24);
        s1 = s2;
        i += 4u;
      }
      while (i != n);

      break;
    }
    // `s` is two bytes off
    case 2:
    {
      u32 s1 = *(const u32* t_noalias)(s + i - 2);

      do
      {
        u32 s2 = *(const u32* t_noalias)(s + i + 4 - 2);
        *(u32* t_noalias)(d + i) = (s1 t_shr 16) | (s2 t_shl 16);
        s1 = s2;
        i += 4u;
      }
      while (i != n);

      break;
    }
    // `s` is three bytes off
    case 3:
    {
      u32 s1 = *(const u32* t_noalias)(s + i - 3);

      do
      {
        u32 s2 = *(const u32* t_noalias)(s + i + 4 - 3);
        *(u32* t_noalias)(d + i) = (s1 t_shr 24) | (s2 t_shl 8);
        s1 = s2;
        i += 4u;
      }
      while (i != n);

      break;
    }
  }

  d += n;
  s += n;

  n = size - n;

tail:
  t_tail3 (n);

#elif (T_CHAR_BIT == 8) && (T_WORD_BIT == 64)

  // Copy whole words by constructing them from eight byte reads, if necessary
  size_t x = (8u - ((uintptr_t)d & 7u)) & 7u;

  if (unlikely (x >= size)) goto tail;

  t_copyb7 (x);

  size_t n = size_align_floor (8u, size - x);

  if (likely ((uintptr_t)s & 7u)) for (size_t i = 0; i != n; i += 8u)
  {
  #if CPU(LITTLE_ENDIAN)
    *(u64* t_noalias)(d + i)
    = ((u64)(s[i + 0]))
    | ((u64)(s[i + 1]) << 8)
    | ((u64)(s[i + 2]) << 16)
    | ((u64)(s[i + 3]) << 24)
    | ((u64)(s[i + 4]) << 32)
    | ((u64)(s[i + 5]) << 40)
    | ((u64)(s[i + 6]) << 48)
    | ((u64)(s[i + 7]) << 56);
  #else
    *(u64* t_noalias)(d + i)
    = ((u64)(s[i + 0]) << 56)
    | ((u64)(s[i + 1]) << 48)
    | ((u64)(s[i + 2]) << 40)
    | ((u64)(s[i + 3]) << 32)
    | ((u64)(s[i + 4]) << 24)
    | ((u64)(s[i + 5]) << 16)
    | ((u64)(s[i + 6]) << 8)
    | ((u64)(s[i + 7]));
  #endif
  }
  else for (size_t i = 0; i != n; i += 8u)
  {
    *(u64* t_noalias)(d + i) = *(const u64* t_noalias)(s + i);
  }

  d += n;
  s += n;

  n = size - n;

tail:
  t_tail7 (n);

#else

  // Generic byte-by-byte copy unrolled 4 times
  size_t n = size_align_floor (4u, size);

  for (size_t i = 0; i != n; i += 4u)
  {
    d[i + 0] = s[i + 0];
    d[i + 1] = s[i + 1];
    d[i + 2] = s[i + 2];
    d[i + 3] = s[i + 3];
  }

  d += n;
  s += n;

  n = size - n;

  t_copyb3 (n);

#endif
}

// -----------------------------------------------------------------------------

#undef T_PREALIGN

#undef T_RESTRICT
#undef t_noalias

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
