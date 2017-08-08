// =============================================================================
// <string/misc/clone/generic.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../support/intro.h"

// -----------------------------------------------------------------------------

if (true)
{
  t_char* out = (t_char*)t_mem_alloc (arr_size (out, len));

  if (unlikely (out == null)) return null;

  t_str_copy (out, buf, len);

  return out;
}

// -----------------------------------------------------------------------------

#undef t_mem_alloc
#undef t_str_copy

// -----------------------------------------------------------------------------

#include "../../support/outro.h"
