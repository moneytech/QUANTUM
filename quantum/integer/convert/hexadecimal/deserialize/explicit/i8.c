// =============================================================================
// <integer/convert/hexadecimal/deserialize/explicit/i8.c>
//
// 8-bit+ hexadecimal string to integer conversion template.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "intro.h"

// -----------------------------------------------------------------------------

if (true)
{
  #include "intro.c"

#if T(VALID)
  int_from_xstr (val, str, str + len, {goto invalid;});
#else
  int_from_xstr (val, str, str + len, {;});
#endif

  #include "outro.c"
}

// -----------------------------------------------------------------------------

#include "outro.h"
