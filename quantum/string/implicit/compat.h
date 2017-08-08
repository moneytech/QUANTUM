// =============================================================================
// <string/implicit/compat.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_F357DAC8806C4DD5BAE9B9D01EC5F4A4
#define H_F357DAC8806C4DD5BAE9B9D01EC5F4A4

// -----------------------------------------------------------------------------

#include "../../stdlib/string.h"
#include "buffer.h"

// -----------------------------------------------------------------------------
// The usage of these two functions is highly discouraged
// -----------------------------------------------------------------------------

static inline char_t* stri_concat (char_t* restrict dst, const char_t* restrict src)
{
  #define t_stri_length stri_length
  #define t_stri_copy stri_copy

  #include "buffer/concat/generic.c"
}

static inline char_t* stri_nconcat (char_t* restrict dst, const char_t* restrict src, size_t max)
{
  #define T_LIMIT
  #define t_stri_length stri_length
  #define t_stri_ncopy stri_ncopy

  #include "buffer/concat/generic.c"
}

// -----------------------------------------------------------------------------

#if NO(STDLIB)
extern size_t stri_span_chr_set (const char_t* str, const char_t* set);
#else
static inline size_t stri_span_chr_set (const char_t* str, const char_t* set)
{
  return strcspn (str, set);
}
#endif

extern size_t stri_ispan_chr_set (const char_t* str, const char_t* set);

// -----------------------------------------------------------------------------

#if NO(STDLIB)
extern size_t stri_span_not_chr_set (const char_t* str, const char_t* set);
#else
static inline size_t stri_span_not_chr_set (const char_t* str, const char_t* set)
{
  return strspn (str, set);
}
#endif

extern size_t stri_ispan_not_chr_set (const char_t* str, const char_t* set);

// -----------------------------------------------------------------------------

#endif
