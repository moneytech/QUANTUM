// =============================================================================
// <integer/convert/decimal/serialize/lut.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include <stdio.h>

// -----------------------------------------------------------------------------

int main (int argc, char** argv)
{
  printf ("static const char_t int_dig_tbl[%u] = {\n", 200u);

  for (unsigned i = 0; i < 200u; i++)
  {
    putchar ('\'');
    putchar ('0' + ((i % 2u) ? ((i / 2u) % 10u) : ((i / 2u) / 10u)));
    putchar ('\'');

    if (((i + 1u) % 20u) == 0)
    {
      if (i == 199u)
      {
        putchar ('}');
        putchar (';');
        putchar ('\n');
      }
      else
      {
        putchar (',');
        putchar ('\n');
      }
    }
    else
    {
      putchar (',');
      putchar (' ');
    }
  }

  return 0;
}
