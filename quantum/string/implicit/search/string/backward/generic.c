// =============================================================================
// <string/implicit/search/string/backward/generic.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../../../support/intro.h"

// -----------------------------------------------------------------------------

if (true)
{
  return t_str_rfind_sub (str, t_stri_length (str), sub, t_stri_length (sub));
}

// -----------------------------------------------------------------------------

#undef t_stri_length

#undef T_ICASE
#undef t_str_rfind_sub

// -----------------------------------------------------------------------------

#include "../../../../support/outro.h"
