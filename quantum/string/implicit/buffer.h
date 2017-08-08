// =============================================================================
// <string/implicit/buffer.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_FC0901F69EB74562B1BBC6B5FF9BCD99
#define H_FC0901F69EB74562B1BBC6B5FF9BCD99

// -----------------------------------------------------------------------------

#include "../../stdlib/string.h"
#include "../../posix/strings.h"
#include "../buffer.h"

#include "macros.h"

// -----------------------------------------------------------------------------
// Equivalent of `strlen()`
// -----------------------------------------------------------------------------

#if NO(STDLIB)
extern size_t stri_length (const char_t* str);
#else
static inline size_t stri_length (const char_t* str)
{
  return strlen (str);
}
#endif

#if NO(STDLIB) || !HAVE(STRNLEN)
extern size_t stri_nlength (const char_t* str, size_t max);
#else
static inline size_t stri_nlength (const char_t* str, size_t max)
{
  return strnlen (str, max);
}
#endif

// -----------------------------------------------------------------------------

extern char_t* stri_copy (char_t* restrict dst, const char_t* restrict src);
extern char_t* stri_ncopy (char_t* restrict dst, const char_t* restrict src, size_t max);

// -----------------------------------------------------------------------------

extern char_t* stri_fill (char_t* str, char_t chr);
extern char_t* stri_nfill (char_t* str, char_t chr, size_t max);

// -----------------------------------------------------------------------------
// Zero out the whole string
extern char_t* stri_zero (char_t* str);
extern char_t* stri_nzero (char_t* str, size_t max);

// -----------------------------------------------------------------------------
// Equivalent of `strcmp()`
// -----------------------------------------------------------------------------

#if NO(STDLIB)
extern int stri_compare (const char_t* str1, const char_t* str2);
#else
static inline int stri_compare (const char_t* str1, const char_t* str2)
{
  return strcmp (str1, str2);
}
#endif

// -----------------------------------------------------------------------------
// Equivalent of `strncmp()`
// -----------------------------------------------------------------------------

#if NO(STDLIB)
extern int stri_ncompare (const char_t* str1, const char_t* str2, size_t max);
#else
static inline int stri_ncompare (const char_t* str1, const char_t* str2, size_t max)
{
  return strncmp (str1, str2, max);
}
#endif

// -----------------------------------------------------------------------------
// Equivalent of `strcasecmp()`
// -----------------------------------------------------------------------------

#if NO(STDLIB) || !HAVE(STRCASECMP)
extern int stri_icompare (const char_t* str1, const char_t* str2);
#else
static inline int stri_icompare (const char_t* str1, const char_t* str2)
{
  return strcasecmp (str1, str2);
}
#endif

// -----------------------------------------------------------------------------
// Equivalent of `strncasecmp()`
// -----------------------------------------------------------------------------

#if NO(STDLIB) || !HAVE(STRNCASECMP)
extern int stri_nicompare (const char_t* str1, const char_t* str2, size_t max);
#else
static inline int stri_nicompare (const char_t* str1, const char_t* str2, size_t max)
{
  return strncasecmp (str1, str2, max);
}
#endif

// -----------------------------------------------------------------------------

#if NO(STDLIB)
extern bint stri_equal (const char_t* str1, const char_t* str2);
#else
static inline bint stri_equal (const char_t* str1, const char_t* str2)
{
  return strequ (str1, str2);
}
#endif

#if NO(STDLIB)
extern bint stri_nequal (const char_t* str1, const char_t* str2, size_t max);
#else
static inline bint stri_nequal (const char_t* str1, const char_t* str2, size_t max)
{
  return strnequ (str1, str2, max);
}
#endif

// -----------------------------------------------------------------------------

#if NO(STDLIB) || !HAVE(STRCASECMP)
extern bint stri_iequal (const char_t* str1, const char_t* str2);
#else
static inline bint stri_iequal (const char_t* str1, const char_t* str2)
{
  return strcaseequ (str1, str2);
}
#endif

#if NO(STDLIB) || !HAVE(STRNCASECMP)
extern bint stri_niequal (const char_t* str1, const char_t* str2, size_t max);
#else
static inline bint stri_niequal (const char_t* str1, const char_t* str2, size_t max)
{
  return strncaseequ (str1, str2, max);
}
#endif

// -----------------------------------------------------------------------------

extern size_t stri_prefix (const char_t* str1, const char_t* str2);
extern size_t stri_nprefix (const char_t* str1, const char_t* str2, size_t max);

// -----------------------------------------------------------------------------

extern size_t stri_iprefix (const char_t* str1, const char_t* str2);
extern size_t stri_niprefix (const char_t* str1, const char_t* str2, size_t max);

// -----------------------------------------------------------------------------

static inline size_t stri_postfix (const char_t* str1, const char_t* str2)
{
  #define t_stri_length stri_length
  #define t_str_postfix str_postfix

  #include "buffer/postfix/generic.c"
}

static inline size_t stri_npostfix (const char_t* str1, const char_t* str2, size_t max)
{
  #define T_LIMIT
  #define t_stri_length stri_length
  #define t_str_postfix str_postfix

  #include "buffer/postfix/generic.c"
}

// -----------------------------------------------------------------------------

static inline size_t stri_ipostfix (const char_t* str1, const char_t* str2)
{
  #define t_stri_length stri_length

  #define T_ICASE
  #define t_str_postfix str_ipostfix

  #include "buffer/postfix/generic.c"
}

static inline size_t stri_nipostfix (const char_t* str1, const char_t* str2, size_t max)
{
  #define T_LIMIT
  #define t_stri_length stri_length

  #define T_ICASE
  #define t_str_postfix str_ipostfix

  #include "buffer/postfix/generic.c"
}

// -----------------------------------------------------------------------------

extern size_t stri_parity (const char_t* str1, const char_t* str2);
extern size_t stri_nparity (const char_t* str1, const char_t* str2, size_t max);

// -----------------------------------------------------------------------------

extern size_t stri_iparity (const char_t* str1, const char_t* str2);
extern size_t stri_niparity (const char_t* str1, const char_t* str2, size_t max);

// -----------------------------------------------------------------------------

static inline char_t* stri_reverse (char_t* str)
{
  #define t_str_reverse str_reverse
  #define t_stri_length stri_length

  #include "buffer/reverse/generic.c"
}

static inline char_t* stri_nreverse (char_t* str, size_t max)
{
  #define t_str_reverse str_reverse

  #define T_LIMIT
  #define t_stri_nlength stri_nlength

  #include "buffer/reverse/generic.c"
}

// -----------------------------------------------------------------------------

#endif
