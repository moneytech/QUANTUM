// =============================================================================
// <string/transform.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_A852015213AD42A582E848EB493F45F4
#define H_A852015213AD42A582E848EB493F45F4

// -----------------------------------------------------------------------------

#include "../character.h"

// -----------------------------------------------------------------------------
// Case conversion
// -----------------------------------------------------------------------------
// To upper case
static inline void str_to_ucase (char_t* buf, size_t len)
{
  #define t_chr_to_case chr_to_ucase

  #include "transform/case/generic.c"
}

// -----------------------------------------------------------------------------
// To lower case
static inline void str_to_lcase (char_t* buf, size_t len)
{
  #define t_chr_to_case chr_to_lcase

  #include "transform/case/generic.c"
}

// -----------------------------------------------------------------------------

#endif
