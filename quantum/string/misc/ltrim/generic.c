// =============================================================================
// <string/misc/ltrim/generic.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../support/intro.h"

// -----------------------------------------------------------------------------

if (true)
{
  const t_char* end = buf + len;

  while (buf != end)
  {
    if (!t_chr_is_wspace (*buf)) break;
    buf++;
  }

  return (size_t)(end - buf);
}

// -----------------------------------------------------------------------------

#undef t_chr_is_wspace

// -----------------------------------------------------------------------------

#include "../../support/outro.h"
