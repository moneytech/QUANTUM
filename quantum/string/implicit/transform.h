// =============================================================================
// <string/implicit/transform.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_D1472FA91C0B48B8A56AA23F92999838
#define H_D1472FA91C0B48B8A56AA23F92999838

// -----------------------------------------------------------------------------

#include "../../character.h"

// -----------------------------------------------------------------------------
// Case conversion
// -----------------------------------------------------------------------------
// To upper case
static inline char_t* stri_to_ucase (char_t* str)
{
  #define t_chr_to_case chr_to_ucase

  #include "transform/case/generic.c"
}

// -----------------------------------------------------------------------------
// To lower case
static inline char_t* stri_to_lcase (char_t* str)
{
  #define t_chr_to_case chr_to_lcase

  #include "transform/case/generic.c"
}

// -----------------------------------------------------------------------------

#endif
