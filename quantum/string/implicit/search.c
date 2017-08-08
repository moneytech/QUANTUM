// =============================================================================
// <string/implicit/search.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../core.h"
#include "../../swar.h"
#include "../../character.h"
#include "buffer.h"

#include "search.h"

// -----------------------------------------------------------------------------
// Character
// -----------------------------------------------------------------------------

#if NO(STDLIB)
char_t* stri_find_chr (const char_t* str, char_t chr)
{
  #include "search/character/forward/generic.c"
}
#endif

char_t* stri_ifind_chr (const char_t* str, const char_t chr)
{
  #define T_ICASE
  #define t_chr_to_case chr_to_lcase

  #include "search/character/forward/generic.c"
}

// -----------------------------------------------------------------------------

char_t* stri_token_chr (char_t** st, char_t chr)
{
  #define T_TOKEN

  #include "search/character/forward/generic.c"
}

char_t* stri_itoken_chr (char_t** st, char_t chr)
{
  #define T_TOKEN

  #define T_ICASE
  #define t_chr_to_case chr_to_lcase

  #include "search/character/forward/generic.c"
}

// -----------------------------------------------------------------------------
// String
// -----------------------------------------------------------------------------

#if NO(STDLIB)
char_t* stri_find_sub (const char_t* str, const char_t* sub)
{
  #define t_stri_find_chr stri_find_chr
  #define t_stri_prefix stri_prefix

  #include "search/string/forward/generic.c"
}
#endif

char_t* stri_ifind_sub (const char_t* str, const char_t* sub)
{
  #define T_ICASE
  #define t_stri_find_chr stri_ifind_chr
  #define t_stri_prefix stri_iprefix

  #include "search/string/forward/generic.c"
}

// -----------------------------------------------------------------------------

char_t* stri_token_sub (char_t** st, const char_t* sub)
{
  #define T_TOKEN

  #define t_stri_find_chr stri_find_chr
  #define t_stri_prefix stri_prefix

  #include "search/string/forward/generic.c"
}

char_t* stri_itoken_sub (char_t** st, const char_t* sub)
{
  #define T_TOKEN

  #define T_ICASE
  #define t_stri_find_chr stri_ifind_chr
  #define t_stri_prefix stri_iprefix

  #include "search/string/forward/generic.c"
}

// -----------------------------------------------------------------------------
// Character set
// -----------------------------------------------------------------------------

#if NO(STDLIB)
char_t* stri_find_chr_set (const char_t* str, const char_t* set)
{
  #include "search/set/character/forward/generic.c"
}
#endif

char_t* stri_ifind_chr_set (const char_t* str, const char_t* set)
{
  #define T_ICASE
  #define t_chr_to_case chr_to_lcase

  #include "search/set/character/forward/generic.c"
}

// -----------------------------------------------------------------------------

char_t* stri_token_chr_set (char_t** st, const char_t* set)
{
  #define T_TOKEN

  #include "search/set/character/forward/generic.c"
}

char_t* stri_itoken_chr_set (char_t** st, const char_t* set)
{
  #define T_TOKEN

  #define T_ICASE
  #define t_chr_to_case chr_to_lcase

  #include "search/set/character/forward/generic.c"
}

// -----------------------------------------------------------------------------
// String set
// -----------------------------------------------------------------------------

char_t* stri_find_sub_set (const char_t* str, const char_t* const* set)
{
  #define t_stri_prefix stri_prefix

  #include "search/set/string/forward/generic.c"
}

char_t* stri_ifind_sub_set (const char_t* str, const char_t* const* set)
{
  #define T_ICASE
  #define t_chr_to_case chr_to_lcase
  #define t_stri_prefix stri_iprefix

  #include "search/set/string/forward/generic.c"
}

// -----------------------------------------------------------------------------

char_t* stri_token_sub_set (char_t** st, const char_t* const* set)
{
  #define T_TOKEN
  #define t_stri_prefix stri_prefix

  #include "search/set/string/forward/generic.c"
}

char_t* stri_itoken_sub_set (char_t** st, const char_t* const* set)
{
  #define T_TOKEN

  #define T_ICASE
  #define t_chr_to_case chr_to_lcase
  #define t_stri_prefix stri_iprefix

  #include "search/set/string/forward/generic.c"
}
