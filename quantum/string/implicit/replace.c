// =============================================================================
// <string/implicit/replace.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../core.h"
#include "../../swar.h"
#include "../../character.h"
#include "search.h"

#include "replace.h"

// -----------------------------------------------------------------------------
// Character
// -----------------------------------------------------------------------------

char_t* stri_replace_chr (char_t* str, char_t old, char_t new)
{
  #include "replace/character/generic.c"
}

char_t* stri_ireplace_chr (char_t* str, char_t old, char_t new)
{
  #define T_ICASE
  #define t_chr_to_case chr_to_lcase

  #include "replace/character/generic.c"
}

// -----------------------------------------------------------------------------
// Character set
// -----------------------------------------------------------------------------

char_t* stri_replace_chr_set (char_t* str, const char_t* old, const char_t* new)
{
  #include "replace/set/character/generic.c"
}

char_t* stri_ireplace_chr_set (char_t* str, const char_t* old, const char_t* new)
{
  #define T_ICASE
  #define t_chr_to_case chr_to_lcase

  #include "replace/set/character/generic.c"
}
