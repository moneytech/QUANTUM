// =============================================================================
// <string/implicit/misc.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_E1257C907C7A4222B37E3233EDA905D4
#define H_E1257C907C7A4222B37E3233EDA905D4

// -----------------------------------------------------------------------------

#include "../../character.h"
#include "../buffer.h"
#include "buffer.h"

// -----------------------------------------------------------------------------
// Trim whitespace at the start and at the end of a null-terminated string
// -----------------------------------------------------------------------------
// Trim from left
static inline char_t* stri_ltrim (const char_t* str)
{
  #define t_chr_is_wspace_zero chr_is_wspace_zero

  #include "misc/ltrim/generic.c"
}

// -----------------------------------------------------------------------------
// Trim from right
static inline char_t* stri_rtrim (char_t* str)
{
  #define t_stri_length stri_length
  #define t_chr_is_wspace chr_is_wspace

  #include "misc/rtrim/generic.c"
}

// -----------------------------------------------------------------------------
// Trim from both left and right and slide the data to the left
static inline char_t* stri_trim (char_t* str)
{
  #define t_stri_ltrim stri_ltrim
  #define t_stri_rtrim stri_rtrim
  #define t_str_move_left str_move_left

  #include "misc/trim/generic.c"
}

// -----------------------------------------------------------------------------
// Duplicate a null-terminated string
// -----------------------------------------------------------------------------

static inline char_t* stri_clone (const char_t* str)
{
#if NO(STDLIB) || !HAVE(STRDUP)
  #define t_mem_alloc mem_alloc
  #define t_str_copy str_copy
  #define t_stri_length stri_length

  #include "misc/clone/generic.c"
#else
  return strdup (str);
#endif
}

static inline char_t* stri_nclone (const char_t* str, size_t max)
{
#if NO(STDLIB) || !HAVE(STRNDUP)
  #define t_mem_alloc mem_alloc
  #define t_str_copy str_copy

  #define T_LIMIT
  #define t_stri_nlength stri_nlength

  #include "misc/clone/generic.c"
#else
  return strndup (str, max);
#endif
}

// -----------------------------------------------------------------------------

#endif
