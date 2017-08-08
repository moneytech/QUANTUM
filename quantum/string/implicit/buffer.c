// =============================================================================
// <string/implicit/buffer.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../core.h"
#include "../../swar.h"
#include "../../character.h"

#include "buffer.h"

// -----------------------------------------------------------------------------

#if NO(STDLIB)
size_t stri_length (const char_t* str)
{
  #include "buffer/length/generic.c"
}
#endif

#if NO(STDLIB) || !HAVE(STRNLEN)
size_t stri_nlength (const char_t* str, size_t max)
{
  #define T_LIMIT

  #include "buffer/length/generic.c"
}
#endif

// -----------------------------------------------------------------------------

char_t* stri_copy (char_t* restrict dst, const char_t* restrict src)
{
  #include "buffer/copy/generic.c"
}

char_t* stri_ncopy (char_t* restrict dst, const char_t* restrict src, size_t max)
{
  #define T_LIMIT

  #include "buffer/copy/generic.c"
}

// -----------------------------------------------------------------------------

char_t* stri_fill (char_t* str, char_t chr)
{
  #include "buffer/fill/generic.c"
}

char_t* stri_nfill (char_t* str, char_t chr, size_t max)
{
  #define T_LIMIT

  #include "buffer/fill/generic.c"
}

// -----------------------------------------------------------------------------

char_t* stri_zero (char_t* str)
{
  #define T_ZERO

  #include "buffer/fill/generic.c"
}

char_t* stri_nzero (char_t* str, size_t max)
{
  #define T_ZERO
  #define T_LIMIT

  #include "buffer/fill/generic.c"
}

// -----------------------------------------------------------------------------

#if NO(STDLIB)
int stri_compare (const char_t* str1, const char_t* str2)
{
  #include "buffer/compare/generic.c"
}
#endif

#if NO(STDLIB)
int stri_ncompare (const char_t* str1, const char_t* str2, size_t max)
{
  #define T_LIMIT

  #include "buffer/compare/generic.c"
}
#endif

// -----------------------------------------------------------------------------

#if NO(STDLIB) || !HAVE(STRCASECMP)
int stri_icompare (const char_t* str1, const char_t* str2)
{
  #define T_ICASE
  #define t_chr_to_case chr_to_lcase

  #include "buffer/compare/generic.c"
}
#endif

#if NO(STDLIB) || !HAVE(STRNCASECMP)
int stri_nicompare (const char_t* str1, const char_t* str2, size_t max)
{
  #define T_LIMIT

  #define T_ICASE
  #define t_chr_to_case chr_to_lcase

  #include "buffer/compare/generic.c"
}
#endif

// -----------------------------------------------------------------------------

#if NO(STDLIB)
bint stri_equal (const char_t* str1, const char_t* str2)
{
  #define T_EQUALITY

  #include "buffer/compare/generic.c"
}
#endif

#if NO(STDLIB)
bint stri_nequal (const char_t* str1, const char_t* str2, size_t max)
{
  #define T_EQUALITY
  #define T_LIMIT

  #include "buffer/compare/generic.c"
}
#endif

// -----------------------------------------------------------------------------

#if NO(STDLIB) || !HAVE(STRCASECMP)
bint stri_iequal (const char_t* str1, const char_t* str2)
{
  #define T_EQUALITY

  #define T_ICASE
  #define t_chr_to_case chr_to_lcase

  #include "buffer/compare/generic.c"
}
#endif

#if NO(STDLIB) || !HAVE(STRNCASECMP)
bint stri_niequal (const char_t* str1, const char_t* str2, size_t max)
{
  #define T_EQUALITY
  #define T_LIMIT

  #define T_ICASE
  #define t_chr_to_case chr_to_lcase

  #include "buffer/compare/generic.c"
}
#endif

// -----------------------------------------------------------------------------

size_t stri_prefix (const char_t* str1, const char_t* str2)
{
  #define T_SIMILARITY

  #include "buffer/compare/generic.c"
}

size_t stri_nprefix (const char_t* str1, const char_t* str2, size_t max)
{
  #define T_SIMILARITY
  #define T_LIMIT

  #include "buffer/compare/generic.c"
}

// -----------------------------------------------------------------------------

size_t stri_iprefix (const char_t* str1, const char_t* str2)
{
  #define T_SIMILARITY

  #define T_ICASE
  #define t_chr_to_case chr_to_lcase

  #include "buffer/compare/generic.c"
}

size_t stri_niprefix (const char_t* str1, const char_t* str2, size_t max)
{
  #define T_SIMILARITY
  #define T_LIMIT

  #define T_ICASE
  #define t_chr_to_case chr_to_lcase

  #include "buffer/compare/generic.c"
}

// -----------------------------------------------------------------------------

size_t stri_parity (const char_t* str1, const char_t* str2)
{
  #include "buffer/parity/generic.c"
}

size_t stri_nparity (const char_t* str1, const char_t* str2, size_t max)
{
  #define T_LIMIT

  #include "buffer/parity/generic.c"
}

// -----------------------------------------------------------------------------

size_t stri_iparity (const char_t* str1, const char_t* str2)
{
  #define T_ICASE
  #define t_chr_to_case chr_to_lcase

  #include "buffer/parity/generic.c"
}

size_t stri_niparity (const char_t* str1, const char_t* str2, size_t max)
{
  #define T_LIMIT

  #define T_ICASE
  #define t_chr_to_case chr_to_lcase

  #include "buffer/parity/generic.c"
}
