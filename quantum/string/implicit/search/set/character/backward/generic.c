// =============================================================================
// <string/implicit/search/set/character/backward/generic.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../../../../support/intro.h"

// -----------------------------------------------------------------------------

if (true)
{
  return t_str_rfind_chr_set (str, t_stri_length (str), set, t_stri_length (set));
}

// -----------------------------------------------------------------------------

#undef t_stri_length

#undef T_ICASE
#undef t_str_rfind_chr_set

// -----------------------------------------------------------------------------

#include "../../../../../support/outro.h"
