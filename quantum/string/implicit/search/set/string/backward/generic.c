// =============================================================================
// <string/implicit/search/set/string/backward/generic.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../../../../support/intro.h"

// -----------------------------------------------------------------------------

if (true)
{
  size_t idx;
  size_t num = arri_length ((const void* const*)set);

  vla (str_const_t, strs, num);

  for (size_t i = 0; i < num; i++)
  {
    strs[i].buf = set[i];
    strs[i].len = t_stri_length (set[i]);
  }

  return t_str_rfind_sub_set (str, t_stri_length (str), strs, num, &idx);
}

// -----------------------------------------------------------------------------

#undef t_stri_length

#undef T_ICASE
#undef t_str_rfind_sub_set

// -----------------------------------------------------------------------------

#include "../../../../../support/outro.h"
