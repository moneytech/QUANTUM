// =============================================================================
// <integer/convert/decimal/deserialize/explicit/i8.c>
//
// 8-bit+ decimal string to integer conversion template.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

if (true)
{
  #include "intro.c"

#if T(VALID)
  int_from_str (val, str, str + len, {goto invalid;});
#else
  int_from_str (val, str, str + len, {;});
#endif

  #include "outro.c"
}

// -----------------------------------------------------------------------------

#include "outro.h"
