// =============================================================================
// <string/search.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../core.h"
#include "../swar.h"
#include "../character.h"

#include "types.h"
#include "buffer.h"

#include "search.h"

// -----------------------------------------------------------------------------
// Character
// -----------------------------------------------------------------------------

#if NO(STDLIB)
char_t* str_find_chr (const char_t* buf, size_t size, char_t chr)
{
  #define T_PREALIGN

  #include "search/character/forward/generic.c"
}
#endif

char_t* str_ifind_chr (const char_t* buf, size_t size, char_t chr)
{
  #define T_ICASE
  #define t_chr_to_case chr_to_lcase

  #include "search/character/forward/generic.c"
}

// -----------------------------------------------------------------------------

#if NO(STDLIB) || !HAVE(MEMRCHR)
char_t* str_rfind_chr (const char_t* buf, size_t size, char_t chr)
{
  #define T_PREALIGN

  #include "search/character/backward/generic.c"
}
#endif

char_t* str_rifind_chr (const char_t* buf, size_t size, char_t chr)
{
  #define T_ICASE
  #define t_chr_to_case chr_to_lcase

  #include "search/character/backward/generic.c"
}

// -----------------------------------------------------------------------------

str_t str_token_chr (str_t* st, char_t chr)
{
  #define t_str_find_chr str_find_chr

  #include "search/character/token/generic.c"
}

str_t str_itoken_chr (str_t* st, char_t chr)
{
  #define T_ICASE
  #define t_str_find_chr str_ifind_chr

  #include "search/character/token/generic.c"
}

// -----------------------------------------------------------------------------
// String
// -----------------------------------------------------------------------------

#if NO(STDLIB) || !HAVE(MEMMEM)
char_t* str_find_sub (const char_t* buf, size_t bufsz
, const char_t* sub, size_t subsz)
{
  #define t_str_find_chr str_find_chr
  #define t_str_equal str_equal

  #include "search/string/forward/generic.c"
}
#endif

char_t* str_ifind_sub (const char_t* buf, size_t bufsz
, const char_t* sub, size_t subsz)
{
  #define T_ICASE
  #define t_str_find_chr str_ifind_chr
  #define t_str_equal str_iequal

  #include "search/string/forward/generic.c"
}

// -----------------------------------------------------------------------------

#if NO(STDLIB) || !HAVE(MEMRMEM)
char_t* str_rfind_sub (const char_t* buf, size_t bufsz
, const char_t* sub, size_t subsz)
{
  #define t_str_rfind_chr str_rfind_chr
  #define t_str_equal str_equal

  #include "search/string/backward/generic.c"
}
#endif

char_t* str_rifind_sub (const char_t* buf, size_t bufsz
, const char_t* sub, size_t subsz)
{
  #define T_ICASE
  #define t_str_rfind_chr str_rifind_chr
  #define t_str_equal str_iequal

  #include "search/string/backward/generic.c"
}

// -----------------------------------------------------------------------------

str_t str_token_sub (str_t* st, const char_t* sub, size_t subsz)
{
  #define t_str_find_sub str_find_sub

  #include "search/string/token/generic.c"
}

str_t str_itoken_sub (str_t* st, const char_t* sub, size_t subsz)
{
  #define T_ICASE
  #define t_str_find_sub str_ifind_sub

  #include "search/string/token/generic.c"
}

// -----------------------------------------------------------------------------
// Character set
// -----------------------------------------------------------------------------

char_t* str_find_chr_set (const char_t* buf, size_t bufsz
, const char_t* set, size_t setsz)
{
  #include "search/set/character/forward/generic.c"
}

char_t* str_ifind_chr_set (const char_t* buf, size_t bufsz
, const char_t* set, size_t setsz)
{
  #define T_ICASE
  #define t_chr_to_case chr_to_lcase

  #include "search/set/character/forward/generic.c"
}

// -----------------------------------------------------------------------------

char_t* str_rfind_chr_set (const char_t* buf, size_t bufsz
, const char_t* set, size_t setsz)
{
  #include "search/set/character/backward/generic.c"
}

char_t* str_rifind_chr_set (const char_t* buf, size_t bufsz
, const char_t* set, size_t setsz)
{
  #define T_ICASE
  #define t_chr_to_case chr_to_lcase

  #include "search/set/character/backward/generic.c"
}

// -----------------------------------------------------------------------------

str_t str_token_chr_set (str_t* st, const char_t* set, size_t setsz)
{
  #define t_str_find_chr_set str_find_chr_set

  #include "search/set/character/token/generic.c"
}

str_t str_itoken_chr_set (str_t* st, const char_t* set, size_t setsz)
{
  #define T_ICASE
  #define t_str_find_chr_set str_ifind_chr_set

  #include "search/set/character/token/generic.c"
}

// -----------------------------------------------------------------------------
// String set
// -----------------------------------------------------------------------------

char_t* str_find_sub_set (const char_t* buf, size_t bufsz
, const str_const_t* set, size_t setsz, size_t* idx)
{
  #define t_str_equal str_equal
  #define T_INDEX

  #include "search/set/string/forward/generic.c"
}

char_t* str_ifind_sub_set (const char_t* buf, size_t bufsz
, const str_const_t* set, size_t setsz, size_t* idx)
{
  #define T_ICASE
  #define t_chr_to_case chr_to_lcase
  #define t_str_equal str_iequal

  #define T_INDEX

  #include "search/set/string/forward/generic.c"
}

// -----------------------------------------------------------------------------

char_t* str_rfind_sub_set (const char_t* buf, size_t bufsz
, const str_const_t* set, size_t setsz, size_t* idx)
{
  #define t_str_equal str_equal
  #define T_INDEX

  #include "search/set/string/backward/generic.c"
}

char_t* str_rifind_sub_set (const char_t* buf, size_t bufsz
, const str_const_t* set, size_t setsz, size_t* idx)
{
  #define T_ICASE
  #define t_chr_to_case chr_to_lcase
  #define t_str_equal str_iequal

  #define T_INDEX

  #include "search/set/string/backward/generic.c"
}

// -----------------------------------------------------------------------------

str_t str_token_sub_set (str_t* st, const str_const_t* set, size_t setsz)
{
  #define t_str_find_sub_set str_find_sub_set

  #include "search/set/string/token/generic.c"
}

str_t str_itoken_sub_set (str_t* st, const str_const_t* set, size_t setsz)
{
  #define T_ICASE
  #define t_str_find_sub_set str_ifind_sub_set

  #include "search/set/string/token/generic.c"
}
