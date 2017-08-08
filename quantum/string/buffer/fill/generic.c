// =============================================================================
// <string/string/fill/generic.c>
//
// Portable code for filling the contents of a buffer
// with a particular byte value.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../support/intro.h"

// -----------------------------------------------------------------------------

#define t_fillb7(x) do\
{              \
  if ((x) & 4u)\
  {            \
    b[0] = chr;\
    b[1] = chr;\
    b[2] = chr;\
    b[3] = chr;\
               \
    b += 4u;   \
  }            \
               \
  if ((x) & 2u)\
  {            \
    b[0] = chr;\
    b[1] = chr;\
               \
    b += 2u;   \
  }            \
               \
  if ((x) & 1u)\
  {            \
    *b++ = chr;\
  }       \
} while (0)

#define t_fillb3(x) do\
{              \
  if ((x) & 2u)\
  {            \
    b[0] = chr;\
    b[1] = chr;\
               \
    b += 2u;   \
  }            \
               \
  if ((x) & 1u)\
  {            \
    *b++ = chr;\
  }       \
} while (0)

#define t_fillb1(x) do\
{              \
  if (x)       \
  {            \
    *b++ = chr;\
  }       \
} while (0)

// -----------------------------------------------------------------------------

#define t_fillw7(x) do\
{                \
  if ((x) & 4u)  \
  {              \
    *(u32*)b = v;\
    b += 4u;     \
  }              \
                 \
  if ((x) & 2u)  \
  {              \
    *(u16*)b = v;\
    b += 2u;   \
  }            \
               \
  if ((x) & 1u)\
  {          \
    *b = chr;\
  }       \
} while (0)

#define t_fillw3(x) do\
{                \
  if ((x) & 2u)  \
  {              \
    *(u16*)b = v;\
    b += 2u;   \
  }            \
               \
  if ((x) & 1u)\
  {          \
    *b = chr;\
  }       \
} while (0)

// -----------------------------------------------------------------------------

#if (T_CHAR_BIT == 8) && HAVE(INT32) && HAVE(INT16)
  #define t_tail7 t_fillw7
#else
  #define t_tail7 t_fillb7
#endif

#if (T_CHAR_BIT == 8) && HAVE(INT16)
  #define t_tail3 t_fillw3
#else
  #define t_tail3 t_fillb3
#endif

#define t_tail1 t_fillb1

// -----------------------------------------------------------------------------

if (true)
{
  t_char* b = buf;

#if T(ZERO)
  const t_char chr = 0;
#endif

#if (T_CHAR_BIT == 8) && ((T_WORD_BIT == 16) || (T_WORD_BIT == 32) || (T_WORD_BIT == 64))

  #if T(ZERO)
    const t_word v = 0;
  #else
    t_word v = (T_WORD_MAX / T_CHAR_MAX) * chr;
  #endif

  #if (CPU(UNALIGNED_ACCESS) && T(PREALIGN)) || !CPU(UNALIGNED_ACCESS)
    #if (T_WORD_BIT == 16)
      size_t x = (uintptr_t)b & 1u;
    #else
      size_t x = (sizeof (t_word) - ((uintptr_t)b & (sizeof (t_word) - 1u))) & (sizeof (t_word) - 1u);
    #endif

    if (unlikely (x >= size)) goto tail;

    #if (T_WORD_BIT == 64)
      t_fillb7 (x);
    #elif (T_WORD_BIT == 32)
      t_fillb3 (x);
    #elif (T_WORD_BIT == 16)
      t_fillb1 (x);
    #endif

    size_t n = size_align_floor (sizeof (t_word), size - x);
  #else
    size_t n = size_align_floor (sizeof (t_word), size);
  #endif

  for (size_t i = 0; i != n; i += sizeof (t_word)) *(t_word*)(b + i) = v;

  b += n;
  n = size - n;

tail:
  #if (T_WORD_BIT == 64)
    t_tail7 (n);
  #elif (T_WORD_BIT == 32)
    t_tail3 (n);
  #elif (T_WORD_BIT == 16)
    t_tail1 (n);
  #endif

#else

  size_t n = size_align_floor (4u, size);

  for (size_t i = 0; i != n; i += 4u)
  {
    b[i + 0] = chr;
    b[i + 1] = chr;
    b[i + 2] = chr;
    b[i + 3] = chr;
  }

  b += n;
  n = size - n;

  t_fillb3 (n);

#endif
}

// -----------------------------------------------------------------------------

#undef T_PREALIGN
#undef T_ZERO

// -----------------------------------------------------------------------------

#undef t_fillb7
#undef t_fillb3
#undef t_fillb1

#undef t_fillw7
#undef t_fillw3

#undef t_tail7
#undef t_tail3
#undef t_tail1

// -----------------------------------------------------------------------------

#include "../../support/outro.h"
