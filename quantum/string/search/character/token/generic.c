// =============================================================================
// <string/search/character/token/generic.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../../support/intro.h"

// -----------------------------------------------------------------------------

if (true)
{
  t_char* buf = st->buf;
  size_t len = st->len;

  t_char* ptr = t_str_find_chr (buf, len, chr);
  if (ptr == null) return t_str_null;

  st->buf = ptr + 1;
  st->len = len - (size_t)(st->buf - buf);

  return t_str_make (buf, (size_t)(ptr - buf));
}

// -----------------------------------------------------------------------------

#undef T_ICASE
#undef t_str_find_chr

// -----------------------------------------------------------------------------

#include "../../../support/outro.h"
