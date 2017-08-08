// =============================================================================
// <string/implicit/misc/clone/generic.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../../support/intro.h"

// -----------------------------------------------------------------------------

if (true)
{
#if T(LIMIT)
  size_t len = t_stri_nlength (str, max);
#else
  size_t len = t_stri_length (str);
#endif

  t_char* out = (t_char*)t_mem_alloc (arr_size (out, len + 1u));
  if (out == null) return null;

  t_str_copy (out, str, len);
  out[len] = '\0';

  return out;
}

// -----------------------------------------------------------------------------

#undef t_mem_alloc
#undef t_str_copy

#undef T_LIMIT
#undef t_stri_nlength
#undef t_stri_length

// -----------------------------------------------------------------------------

#include "../../../support/outro.h"
