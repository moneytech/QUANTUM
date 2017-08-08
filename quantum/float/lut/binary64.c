// =============================================================================
// <float/lut/binary64.c>
//
// Generate the lookup table of positive base 10 IEEE 754 binary64 exponents.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include <stdio.h>

// -----------------------------------------------------------------------------

#define DOUBLE_EXP10_MAX 308

// -----------------------------------------------------------------------------

int main (int argc, char** argv)
{
  printf ("static const double dbl_pow10_tbl[%d] = {\n", DOUBLE_EXP10_MAX + 1);

  for (unsigned i = 0, k = 2u; i <= DOUBLE_EXP10_MAX; i++)
  {
    for (unsigned j = 0; j < k; j++) putchar (' ');

    printf ("1e%d", i);

    if (i == DOUBLE_EXP10_MAX) printf ("};\n", 0);
    else if ((i + 1u) % 10u == 0) printf (",\n", 0);
    else printf (", ", 0);

    if (i == 9u) k--;
    else if (i == 99u) k--;
  }

  return 0;
}
