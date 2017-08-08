// =============================================================================
// <string/implicit/compat.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../core.h"
#include "../../character.h"

#include "compat.h"

// -----------------------------------------------------------------------------

#if NO(STDLIB)
size_t* stri_span_chr_set (const char_t* str, const char_t* set)
{
  #define T_SPAN

  #include "search/set/character/forward/generic.c"
}
#endif

size_t stri_ispan_chr_set (const char_t* str, const char_t* set)
{
  #define T_SPAN

  #define T_ICASE
  #define t_chr_to_case chr_to_lcase

  #include "search/set/character/forward/generic.c"
}

// -----------------------------------------------------------------------------

#if NO(STDLIB)
size_t stri_span_not_chr_set (const char_t* str, const char_t* set)
{
  #define T_INVERT
  #define T_SPAN

  #include "search/set/character/forward/generic.c"
}
#endif

size_t stri_ispan_not_chr_set (const char_t* str, const char_t* set)
{
  #define T_INVERT
  #define T_SPAN

  #define T_ICASE
  #define t_chr_to_case chr_to_lcase

  #include "search/set/character/forward/generic.c"
}
