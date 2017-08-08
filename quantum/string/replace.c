// =============================================================================
// <string/replace.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../core.h"
#include "../swar.h"
#include "../character.h"

#include "types.h"
#include "buffer.h"
#include "search.h"

#include "replace.h"

// -----------------------------------------------------------------------------
// Character
// -----------------------------------------------------------------------------

void str_replace_chr (char_t* buf, size_t size, char_t old, char_t new)
{
  #define T_PREALIGN
  #define t_str_find_chr str_find_chr

  #include "replace/character/generic.c"
}

void str_ireplace_chr (char_t* buf, size_t size, char_t old, char_t new)
{
  #define T_ICASE
  #define t_chr_to_case chr_to_lcase
  #define t_str_find_chr str_ifind_chr

  #include "replace/character/generic.c"
}

// -----------------------------------------------------------------------------
// String
// -----------------------------------------------------------------------------

void str_replace_sub (char_t* buf, size_t bufsz
, const char_t* old, const char_t* new, size_t subsz)
{
  #define t_str_copy str_copy
  #define t_str_find_chr str_find_chr
  #define t_str_equal str_equal

  #include "replace/string/generic.c"
}

void str_ireplace_sub (char_t* buf, size_t bufsz
, const char_t* old, const char_t* new, size_t subsz)
{
  #define t_str_copy str_copy

  #define T_ICASE
  #define t_str_find_chr str_ifind_chr
  #define t_str_equal str_iequal

  #include "replace/string/generic.c"
}

// -----------------------------------------------------------------------------
// Character set
// -----------------------------------------------------------------------------

void str_replace_chr_set (char_t* buf, size_t bufsz
, const char_t* old, const char_t* new, size_t setsz)
{
  #include "replace/set/character/generic.c"
}

void str_ireplace_chr_set (char_t* buf, size_t bufsz
, const char_t* old, const char_t* new, size_t setsz)
{
  #define T_ICASE
  #define t_chr_to_case chr_to_lcase

  #include "replace/set/character/generic.c"
}

// -----------------------------------------------------------------------------
// String set
// -----------------------------------------------------------------------------

void str_replace_sub_set (char_t* buf, size_t bufsz
, const str_const_t* old, const char_t* const* new, size_t setsz)
{
  #define t_str_copy str_copy
  #define t_str_equal str_equal

  #include "replace/set/string/generic.c"
}

void str_ireplace_sub_set (char_t* buf, size_t bufsz
, const str_const_t* old, const char_t* const* new, size_t setsz)
{
  #define t_str_copy str_copy

  #define T_ICASE
  #define t_chr_to_case chr_to_lcase
  #define t_str_equal str_iequal

  #include "replace/set/string/generic.c"
}
