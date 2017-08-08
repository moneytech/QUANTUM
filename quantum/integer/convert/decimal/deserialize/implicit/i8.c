// =============================================================================
// <integer/convert/decimal/deserialize/implicit/i8.c>
//
// 8-bit+ decimal null-terminated string to integer conversion template.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "intro.h"

// -----------------------------------------------------------------------------

if (true)
{
  #include "intro.c"

#if T(VALID)
  int_from_str (val, str, str + T_MAXDIG - 1, {c = *str; goto invalid;});
#else
  int_from_stri (val, str, {goto done;});
#endif

  #include "outro.c"
}

// -----------------------------------------------------------------------------

#include "outro.h"
