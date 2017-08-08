// =============================================================================
// <string/implicit/misc/trim/generic.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../../support/intro.h"

// -----------------------------------------------------------------------------

if (true)
{
  t_char* s = t_stri_ltrim (str);
  size_t n = (size_t)(t_stri_rtrim (s) - s);

  t_str_move_left (str, s, n + 1u);

  return str + n;
}

// -----------------------------------------------------------------------------

#undef t_stri_ltrim
#undef t_stri_rtrim
#undef t_str_move_left

// -----------------------------------------------------------------------------

#include "../../../support/outro.h"
