// =============================================================================
// <string/search/set/string/token/generic.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../../../support/intro.h"

// -----------------------------------------------------------------------------

if (true)
{
  size_t idx;

  t_char* buf = st->buf;
  size_t len = st->len;

  t_char* ptr = t_str_find_sub_set (buf, len, set, setsz, &idx);
  if ((ptr == null) || (ptr == buf)) return t_str_null;

  st->buf = ptr + set[idx].len;
  st->len = len - (size_t)(st->buf - buf);

  return t_str_make (buf, (size_t)(ptr - buf));
}

// -----------------------------------------------------------------------------

#undef T_ICASE
#undef t_str_find_sub_set

// -----------------------------------------------------------------------------

#include "../../../../support/outro.h"
