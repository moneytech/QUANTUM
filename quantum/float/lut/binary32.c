// =============================================================================
// <float/lut/binary32.c>
//
// Generate the lookup table of positive base 10 IEEE 754 binary32 exponents.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include <stdio.h>

// -----------------------------------------------------------------------------

#define FLOAT_EXP10_MAX 38

// -----------------------------------------------------------------------------

int main (int argc, char** argv)
{
  printf ("static const float flt_pow10_tbl[%d] = {\n", FLOAT_EXP10_MAX + 1);

  for (unsigned i = 0, k = 1u; i <= FLOAT_EXP10_MAX; i++)
  {
    for (unsigned j = 0; j < k; j++) putchar (' ');

    printf ("1e%d", i);

    if (i == FLOAT_EXP10_MAX) printf ("};\n", 0);
    else if ((i + 1u) % 10u == 0) printf (",\n", 0);
    else printf (", ", 0);

    if (i == 9u) k--;
  }

  return 0;
}
