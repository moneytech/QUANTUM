// =============================================================================
// <string/implicit/buffer/postfix/generic.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../../../support/intro.h"

// -----------------------------------------------------------------------------

#if T(LIMIT)
  #define t_min2 min2
#else
  #define t_min2(a, b) (a)
#endif

// -----------------------------------------------------------------------------

if (true)
{
  size_t len1 = t_stri_length (str1);
  size_t len2 = t_stri_length (str2);

  if (len1 < len2)
  {
    len1 = t_min2 (len1, max);
    return t_str_postfix (str1, str2 + (len2 - len1), len1);
  }

  len2 = t_min2 (len2, max);
  return t_str_postfix (str1 + (len1 - len2), str2, len2);
}

// -----------------------------------------------------------------------------

#undef T_LIMIT
#undef t_stri_length
#undef t_min2

#undef T_ICASE
#undef t_str_postfix

// -----------------------------------------------------------------------------

#include "../../../support/outro.h"
