// =============================================================================
// <string/transform/case/generic.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../support/intro.h"

// -----------------------------------------------------------------------------

if (true)
{
  t_char* s = buf;
  const t_char* e = buf + len;

  while (s != e) *s++ = t_chr_to_case (*s);
}

// -----------------------------------------------------------------------------

#undef t_chr_to_case

// -----------------------------------------------------------------------------

#include "../../support/outro.h"
