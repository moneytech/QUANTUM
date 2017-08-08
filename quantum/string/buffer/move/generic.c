// =============================================================================
// <string/buffer/move/generic.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../support/intro.h"

// -----------------------------------------------------------------------------

if (true)
{
  // Copy from right to left
  if (likely (dst < src)) t_str_move_left (dst, src, size);

  // Copy from left to right
  else t_str_move_right (dst, src, size);
}

// -----------------------------------------------------------------------------

#undef t_str_move_left
#undef t_str_move_right

// -----------------------------------------------------------------------------

#include "../../support/outro.h"
