// =============================================================================
// <string/implicit/buffer/reverse/generic.c>
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

  t_str_reverse (str, len);

  return str + len;
}

// -----------------------------------------------------------------------------

#undef t_str_reverse

#undef T_LIMIT
#undef t_stri_nlength
#undef t_stri_length

// -----------------------------------------------------------------------------

#include "../../../support/outro.h"
