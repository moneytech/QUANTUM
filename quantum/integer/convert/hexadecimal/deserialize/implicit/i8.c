// =============================================================================
// <integer/convert/hexadecimal/deserialize/implicit/i8.c>
//
// 8-bit+ hexadecimal null-terminated string to integer conversion template.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "intro.h"

// -----------------------------------------------------------------------------

if (true)
{
  #include "intro.c"

#if T(VALID)
  #if T(UNEVEN)
    int_from_xstr (val, str, str + T_MAXDIG - 1, {c = *str; goto invalid;});
  #else
    int_from_xstr (val, str, str + T_MAXDIG, {c = *str; goto invalid;});
  #endif
#else
  int_from_xstri (val, str, {goto done;});
#endif

  #include "outro.c"
}

// -----------------------------------------------------------------------------

#include "outro.h"
