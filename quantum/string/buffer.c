// =============================================================================
// <string/buffer.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../core.h"
#include "../bswap.h"
#include "../character.h"

#include "buffer.h"

// -----------------------------------------------------------------------------

#if NO(STDLIB)
void str_copy (char_t* restrict dst, const char_t* restrict src, size_t size)
{
  #define T_PREALIGN
  #define T_RESTRICT

  #include "buffer/copy/generic.c"
}
#endif

// -----------------------------------------------------------------------------

#if NO(STDLIB)
void str_move_left (char_t* dst, const char_t* src, size_t size)
{
  // Destination and source are the same
  if (unlikely (dst == src)) return;

  #define T_PREALIGN

  #include "buffer/copy/generic.c"
}
#endif

#if NO(STDLIB)
void str_move_right (char_t* dst, const char_t* src, size_t size)
{
  if (unlikely (dst == src)) return;

  #define T_PREALIGN

  #include "buffer/rcopy/generic.c"
}
#endif

#if NO(STDLIB)
void str_move (char_t* dst, const char_t* src, size_t size)
{
  #define t_str_move_left str_move_left
  #define t_str_move_right str_move_right

  #include "buffer/move/generic.c"
}
#endif

// -----------------------------------------------------------------------------

#if NO(STDLIB)
void str_fill (char_t* buf, size_t size, char_t chr)
{
  #define T_PREALIGN

  #include "buffer/fill/generic.c"
}
#endif

#if NO(STDLIB)
void str_zero (char_t* buf, size_t size)
{
  #define T_PREALIGN
  #define T_ZERO

  #include "buffer/fill/generic.c"
}
#endif

// -----------------------------------------------------------------------------

#if NO(STDLIB)
bint str_equal (const char_t* buf1, const char_t* buf2, size_t size)
{
  #define T_PREALIGN
  #define T_EQUALITY

  #include "buffer/compare/generic.c"
}
#endif

bint str_iequal (const char_t* buf1, const char_t* buf2, size_t size)
{
  #define T_EQUALITY

  #define T_ICASE
  #define t_chr_to_case chr_to_lcase

  #include "buffer/compare/generic.c"
}

// -----------------------------------------------------------------------------

#if NO(STDLIB)
int str_compare (const char_t* buf1, const char_t* buf2, size_t size)
{
  #define T_PREALIGN

  #include "buffer/compare/generic.c"
}
#endif

int str_icompare (const char_t* buf1, const char_t* buf2, size_t size)
{
  #define T_ICASE
  #define t_chr_to_case chr_to_lcase

  #include "buffer/compare/generic.c"
}

// -----------------------------------------------------------------------------

size_t str_prefix (const char_t* buf1, const char_t* buf2, size_t size)
{
  #define T_PREALIGN
  #define T_SIMILARITY

  #include "buffer/compare/generic.c"
}

size_t str_iprefix (const char_t* buf1, const char_t* buf2, size_t size)
{
  #define T_SIMILARITY

  #define T_ICASE
  #define t_chr_to_case chr_to_lcase

  #include "buffer/compare/generic.c"
}

// -----------------------------------------------------------------------------

size_t str_postfix (const char_t* buf1, const char_t* buf2, size_t size)
{
  #define T_PREALIGN
  #define T_SIMILARITY

  #include "buffer/rcompare/generic.c"
}

size_t str_ipostfix (const char_t* buf1, const char_t* buf2, size_t size)
{
  #define T_SIMILARITY

  #define T_ICASE
  #define t_chr_to_case chr_to_lcase

  #include "buffer/rcompare/generic.c"
}

// -----------------------------------------------------------------------------

size_t str_parity (const char_t* buf1, const char_t* buf2, size_t size)
{
  #define T_PREALIGN

  #include "buffer/parity/generic.c"
}

size_t str_iparity (const char_t* buf1, const char_t* buf2, size_t size)
{
  #define T_ICASE
  #define t_chr_to_case chr_to_lcase

  #include "buffer/parity/generic.c"
}

// -----------------------------------------------------------------------------

void str_reverse (char_t* buf, size_t size)
{
  #define T_PREALIGN

  #include "buffer/reverse/generic.c"
}

// -----------------------------------------------------------------------------

void str_swap (char_t* restrict buf1, char_t* restrict buf2, size_t size)
{
  #define T_PREALIGN

  #include "buffer/swap/generic.c"
}
