// =============================================================================
// <string/search/string/token/generic.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../../support/intro.h"

// -----------------------------------------------------------------------------

if (true)
{
  t_char* buf = st->buf;

  size_t len = st->len;
  if (unlikely (len == 0)) return t_str_null;

  t_char* ptr = t_str_find_sub (buf, len, sub, subsz);
  if (ptr == null) return t_str_null;

  st->buf = ptr + subsz;
  st->len = len - (size_t)(st->buf - buf);

  return t_str_make (buf, (size_t)(ptr - buf));
}

// -----------------------------------------------------------------------------

#undef T_ICASE
#undef t_str_find_sub

// -----------------------------------------------------------------------------

#include "../../../support/outro.h"
