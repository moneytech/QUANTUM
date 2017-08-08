// =============================================================================
// <string/implicit/buffer/concat/generic.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../../support/intro.h"

// -----------------------------------------------------------------------------

if (true)
{
#if T(LIMIT)
  size_t len = t_stri_length (dst);

  if (max < len) return null;

  return t_stri_ncopy (dst + len, src, max - len);
#else
  return t_stri_copy (dst + t_stri_length (dst), src);
#endif
}

// -----------------------------------------------------------------------------

#undef T_LIMIT
#undef t_stri_length
#undef t_stri_ncopy
#undef t_stri_copy

// -----------------------------------------------------------------------------

#include "../../../support/outro.h"
