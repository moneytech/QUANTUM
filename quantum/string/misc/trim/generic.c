// =============================================================================
// <string/misc/trim/generic.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../support/intro.h"

// -----------------------------------------------------------------------------

if (true)
{
  size_t l = t_str_ltrim (buf, len);
  size_t r = t_str_rtrim (buf + l, len - l);

  t_str_move_left (buf, buf + l, r);

  return r;
}

// -----------------------------------------------------------------------------

#undef t_str_ltrim
#undef t_str_rtrim
#undef t_str_move_left

// -----------------------------------------------------------------------------

#include "../../support/outro.h"
